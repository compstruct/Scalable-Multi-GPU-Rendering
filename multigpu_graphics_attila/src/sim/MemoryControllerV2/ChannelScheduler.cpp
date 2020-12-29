/**************************************************************************
 *
 * Copyright (c) 2002 - 2011 by Computer Architecture Department,
 * Universitat Politecnica de Catalunya.
 * All rights reserved.
 *
 * The contents of this file may not be disclosed to third parties,
 * copied or duplicated in any form, in whole or in part, without the
 * prior permission of the authors, Computer Architecture Department
 * and Universitat Politecnica de Catalunya.
 *
 */

#include "ChannelScheduler.h"
#include "MemoryRequest.h"
#include "GPUMemorySpecs.h"
#include <cmath>

using namespace std;
using namespace gpu3d;
using namespace gpu3d::memorycontroller;

#ifdef GPU_DEBUG
    #undef GPU_DEBUG
#endif
//#define GPU_DEBUG(expr) { expr }
#define GPU_DEBUG(expr) {  }

SchedulerState::SchedulerState(SchedulerState::State state) : allBanksShareState(true), sharedSchedState(state), bankStates(0)
{}

SchedulerState::SchedulerState(std::vector<State>* bankStates) : allBanksShareState(false), bankStates(bankStates)
{
    GPU_ASSERT(
        if ( bankStates == 0 )
            panic("SchedulerState", "ctor", "Bank states vector == NULL!");
    )
}

SchedulerState::State SchedulerState::state(u32bit bank) const
{
    if ( allBanksShareState )
        return sharedSchedState;

    GPU_ASSERT(
        if ( bank >= bankStates->size() ) {
            stringstream ss;
            ss << "BankID out of bound. BankID=" << bank << "  bankState.size()=" << bankStates->size();
            panic("SchedulerState", "state", ss.str().c_str());
        }
    )
    return (*bankStates)[bank];
}

SchedulerState::~SchedulerState()
{
    if ( bankStates ) // delete NULL is not a problem, but... Just in case
        delete bankStates;
}

ChannelScheduler::ChannelScheduler(u32bit gpuId, u32bit schedulerId_,
		                   const char* name,  const char* prefix,
				   Box* parent, const CommonConfig& config) :
Box(gpuId, name, parent), schedulerId(schedulerId_),

        _debugString(config.debugString),
        pagePolicy(config.pagePolicy),
        //currentState(SchedulerState::AcceptNone), 
        currentState(0),
        modState(config.moduleBanks, config.burstLength, config.burstBytesPerCycle, config.memSpecs), 
        BurstLength(config.burstLength), Banks(config.moduleBanks),
        lastCmdWasRW(config.moduleBanks,false),
        setStateCalled(false),
        moduleRequestLastCycle(0),
        prefixStr(prefix),
        
        readBytesStat(getSM(gpuId).getNumericStatistic("ReadBytes", u32bit(0), "ChannelScheduler", prefix)),
        writeBytesStat(getSM(gpuId).getNumericStatistic("WriteBytes", u32bit(0), "ChannelScheduler", prefix)),
        readCmdStat(getSM(gpuId).getNumericStatistic("DDRReadCommands", u32bit(0), "ChannelScheduler", prefix)),
        writeCmdStat(getSM(gpuId).getNumericStatistic("DDRWriteCommands", u32bit(0), "ChannelScheduler", prefix)),
        activeCmdStat(getSM(gpuId).getNumericStatistic("DDRActiveCommands", u32bit(0), "ChannelScheduler", prefix)),
        prechargeCmdStat(getSM(gpuId).getNumericStatistic("DDRPrechargeCommands", u32bit(0), "ChannelScheduler", prefix)),
        totalRowHitStat(getSM(gpuId).getNumericStatistic("RowHit", u32bit(0), "ChannelScheduler", prefix)),
        readRowHitStat(getSM(gpuId).getNumericStatistic("ReadRowHit", u32bit(0), "ChannelScheduler", prefix)),
        writeRowHitStat(getSM(gpuId).getNumericStatistic("WriteRowHit", u32bit(0), "ChannelScheduler", prefix)),
        totalRowMissStat(getSM(gpuId).getNumericStatistic("RowMiss", u32bit(0), "ChannelScheduler", prefix)),
        readRowMissStat(getSM(gpuId).getNumericStatistic("ReadRowMiss", u32bit(0), "ChannelScheduler", prefix)),
        writeRowMissStat(getSM(gpuId).getNumericStatistic("WriteRowMiss", u32bit(0), "ChannelScheduler", prefix)),

        globalReadBytesStat(getSM().getNumericStatistic("ReadBytes", u32bit(0), "ChannelScheduler", prefix)),
        globalWriteBytesStat(getSM().getNumericStatistic("WriteBytes", u32bit(0), "ChannelScheduler", prefix)),
        globalReadCmdStat(getSM().getNumericStatistic("DDRReadCommands", u32bit(0), "ChannelScheduler", prefix)),
        globalWriteCmdStat(getSM().getNumericStatistic("DDRWriteCommands", u32bit(0), "ChannelScheduler", prefix)),
        globalActiveCmdStat(getSM().getNumericStatistic("DDRActiveCommands", u32bit(0), "ChannelScheduler", prefix)),
        globalPrechargeCmdStat(getSM().getNumericStatistic("DDRPrechargeCommands", u32bit(0), "ChannelScheduler", prefix)),
        globalTotalRowHitStat(getSM().getNumericStatistic("RowHit", u32bit(0), "ChannelScheduler", prefix)),
        globalReadRowHitStat(getSM().getNumericStatistic("ReadRowHit", u32bit(0), "ChannelScheduler", prefix)),
        globalWriteRowHitStat(getSM().getNumericStatistic("WriteRowHit", u32bit(0), "ChannelScheduler", prefix)),
        globalTotalRowMissStat(getSM().getNumericStatistic("RowMiss", u32bit(0), "ChannelScheduler", prefix)),
        globalReadRowMissStat(getSM().getNumericStatistic("ReadRowMiss", u32bit(0), "ChannelScheduler", prefix)),
        globalWriteRowMissStat(getSM().getNumericStatistic("WriteRowMiss", u32bit(0), "ChannelScheduler", prefix))

{
    memset(perClientRowHit, 0, sizeof(perClientRowHit));

    for ( u32bit i = 0; i < LASTGPUBUS; ++i ) {

        if ( i == MEMORYMODULE || i == SYSTEM )
            // no statistics for MEMORYMODULE & SYSTEM definitions
            continue;

        string uName = MemoryTransaction::getBusName(GPUUnit(i));

        perClientRowHit[i].totalHits = 
            & getSM(gpuId).getNumericStatistic((string("ClientRowHit_") + uName).c_str(),
                                           u32bit(0), "ChannelScheduler", prefix);
        perClientRowHit[i].readHits = 
            & getSM(gpuId).getNumericStatistic((string("ClientReadRowHit_") + uName).c_str(), 
                                           u32bit(0), "ChannelScheduler", prefix);
        perClientRowHit[i].writeHits = 
            & getSM(gpuId).getNumericStatistic((string("ClientWriteRowHit_") + uName).c_str(),
                                           u32bit(0), "ChannelScheduler", prefix);
        perClientRowHit[i].totalMisses =
            & getSM(gpuId).getNumericStatistic((string("ClientRowMiss_") + uName).c_str(), 
                                           u32bit(0), "ChannelScheduler", prefix);
        perClientRowHit[i].readMisses =
            & getSM(gpuId).getNumericStatistic((string("ClientReadRowMiss_") + uName).c_str(),
                                           u32bit(0), "ChannelScheduler", prefix);
        perClientRowHit[i].writeMisses =
            & getSM(gpuId).getNumericStatistic((string("ClientWriteRowMiss_") + uName).c_str(),
                                          u32bit(0), "ChannelScheduler", prefix);
        
	globalPerClientRowHit[i].totalHits = 
            & getSM().getNumericStatistic((string("ClientRowHit_") + uName).c_str(),
                                           u32bit(0), "ChannelScheduler", prefix);
        globalPerClientRowHit[i].readHits = 
            & getSM().getNumericStatistic((string("ClientReadRowHit_") + uName).c_str(), 
                                           u32bit(0), "ChannelScheduler", prefix);
        globalPerClientRowHit[i].writeHits = 
            & getSM().getNumericStatistic((string("ClientWriteRowHit_") + uName).c_str(),
                                           u32bit(0), "ChannelScheduler", prefix);
        globalPerClientRowHit[i].totalMisses =
            & getSM().getNumericStatistic((string("ClientRowMiss_") + uName).c_str(), 
                                           u32bit(0), "ChannelScheduler", prefix);
        globalPerClientRowHit[i].readMisses =
            & getSM().getNumericStatistic((string("ClientReadRowMiss_") + uName).c_str(),
                                           u32bit(0), "ChannelScheduler", prefix);
        globalPerClientRowHit[i].writeMisses =
            & getSM().getNumericStatistic((string("ClientWriteRowMiss_") + uName).c_str(),
                                          u32bit(0), "ChannelScheduler", prefix);
    }

    //if ( requestBandwidth == 0 )
    //    panic("ChannelScheduler", "ctor", "Request bandwidth must be at least 1");

    channelRequest = newInputSignal("ChannelRequest", 1/*requestBandwidth*/, 1, prefix);
    moduleReply = newInputSignal("DDRModuleReply", 1, 1, prefix);

    channelReply = newOutputSignal("ChannelReply", 1, 1, prefix);
    schedulerState = newOutputSignal("SchedulerState", 1, 1, prefix);
    moduleRequest = newOutputSignal("DDRModuleRequest", 1, 1, prefix);

    // set initial scheduler state
    DynamicObject* defValue[1];
    defValue[0] = new SchedulerState(SchedulerState::AcceptNone);
    schedulerState->setData(defValue);
}


/*
void ChannelScheduler::setState(SchedulerState::State state)
{
    setStateCalled = true;
    switch ( state )
    {
        case SchedulerState::AcceptBoth:
        case SchedulerState::AcceptRead:
        case SchedulerState::AcceptWrite:
        case SchedulerState::AcceptNone:
            currentState = state;
            break;
        default:
            panic("ChannelScheduler", "setState", "Unknown state");
    }
}
*/

void ChannelScheduler::setState(SchedulerState* state)
{
    setStateCalled = true;
    GPU_ASSERT(
        if ( state == 0 )
            panic("ChannelScheduler", "setState", "setState parameter cannot be a NULL pointer");
    )
    currentState = state;
}




void ChannelScheduler::clock(u64bit cycle)
{
    GPU_DEBUG( printf("%s => Clock "U64FMT".\n", getName(), cycle); )

    modState.updateState(cycle); // Update  module state

    ChannelTransaction* request;
    if ( channelRequest->read(cycle, (DynamicObject*&) request) )
    {
        GPU_DEBUG
        (
            cout << getName() << " => Channel Transaction received. "
                 "Type: " << ( request->isRead()?"READ ":"WRITE ")
                 << "Bank: " << request->getBank() << " Row: " << request->getRow()
                 << " Col: " << request->getCol() << " Size: " << request->bytes() 
                 << "\n";
        )
        // update channel transaction timestamp
        // request->setArrivalTimestamp(cycle);
        // inform to the dereived scheduler class that a request has arrived
        receiveRequest(cycle, request);
    }

    DDRBurst* readData;
    if ( moduleReply->read(cycle, (DynamicObject*&) readData) )
    {
        GPU_DEBUG(
            cout << getName() << " => Receiving DDRBurst from GDDR3 module. " 
                << (4 * readData->getSize()) << " bytes.\n";
        )
        // update channel read bytes statistic
        readBytesStat.inc(readData->getSize()*4);
        globalReadBytesStat.inc(readData->getSize()*4);
        receiveData(cycle, readData);
    }
    
    schedulerClock(cycle);

    /* 
     * At this point setState() has to have been called by the derived 
     * class (usually inside schedulerClock() 
     */

    if ( setStateCalled )
        setStateCalled = false;
    else
        panic("ChannelScheduler", "clock", "setState must be called every simulation clock");

    //SchedulerState* schedState = 0;
    switch ( currentState->state(0) )
    {
        case SchedulerState::AcceptBoth:
            //schedState = new SchedulerState(SchedulerState::AcceptBoth);
            //schedState->setColor(SchedulerState::AcceptBoth);
            currentState->setColor(SchedulerState::AcceptBoth);
            break;
        case SchedulerState::AcceptRead:
            //schedState = new SchedulerState(SchedulerState::AcceptRead);
            //schedState->setColor(SchedulerState::AcceptRead);
            currentState->setColor(SchedulerState::AcceptRead);
            break;
        case SchedulerState::AcceptWrite:
            //schedState = new SchedulerState(SchedulerState::AcceptWrite);
            //schedState->setColor(SchedulerState::AcceptWrite);
            currentState->setColor(SchedulerState::AcceptWrite);
            break;
        case SchedulerState::AcceptNone:
            //schedState = new SchedulerState(SchedulerState::AcceptNone);
            //schedState->setColor(SchedulerState::AcceptNone);
            currentState->setColor(SchedulerState::AcceptWrite);
            break;
        default:
            panic("ChannelScheduler", "clock", "Unknown state");
    }
    schedulerState->write(cycle, currentState); // send current scheduler state
    currentState = 0; // reset current state
}

void ChannelScheduler::sendReply(u64bit cycle, ChannelTransaction* reply)
{
    GPU_DEBUG( cout << getName() << " => Sending Channel Transaction completion reply.\n"; )
    strcat((char *)reply->getInfo(), " [COMPLETED]");
    channelReply->write(cycle, reply);
}

bool ChannelScheduler::sendDDRCommand(u64bit cycle, DDRCommand* ddrCmd, const ChannelTransaction* ct)
{
    // cout << "Sent DDRCommand: " << ddrCmd->toString() << "  Trans: " << ct->toString() << endl;

    bool issueCmd;

    u32bit bank = ddrCmd->getBank();


    switch ( ddrCmd->which() ) {
        case DDRCommand::Active:
            issueCmd = modState.canBeIssued(bank, DDRModuleState::C_Active);
            if ( issueCmd ) {
                activeCmdStat.inc();
                globalActiveCmdStat.inc();
                lastCmdWasRW[bank] = false;
                modState.postActive(bank, ddrCmd->getRow());
                GPU_DEBUG( 
                    cout << getName() << " => Sending ACTIVE bank=" 
                         << ddrCmd->getBank() << " row=" << ddrCmd->getRow() << ".\n";
                )
            }
            break;
        case DDRCommand::Read:
            if ( ct == 0 ) {
                panic("ChannelScheduler", "sendDDRCommand", "Channel transaction provided for "
                                                            "a DDR Read command cannot be NULL");
            }
            issueCmd = modState.canBeIssued(bank, DDRModuleState::C_Read);
            if ( issueCmd ) {
                u32bit id = ct->getRequestSource();
                if ( id == MEMORYMODULE || id == SYSTEM || id > LASTGPUBUS ) {
                    panic("ChannelScheduler", "sendDDRCommand", "Invalid unit identifier");
                } 
                readCmdStat.inc();
                globalReadCmdStat.inc();
                if ( lastCmdWasRW[bank] ) {
                    totalRowHitStat.inc();
                    globalTotalRowHitStat.inc();
                    perClientRowHit[id].totalHits->inc();
                    perClientRowHit[id].readHits->inc();
                    globalPerClientRowHit[id].totalHits->inc();
                    globalPerClientRowHit[id].readHits->inc();
                }
                else {
                    totalRowMissStat.inc();
                    globalTotalRowMissStat.inc();
                    perClientRowHit[id].totalMisses->inc();
                    perClientRowHit[id].readMisses->inc();
                    globalPerClientRowHit[id].totalMisses->inc();
                    globalPerClientRowHit[id].readMisses->inc();
                }
                lastCmdWasRW[bank] = true;
                modState.postRead(bank);
                GPU_DEBUG( 
                    cout << getName() << " => Sending READ bank=" 
                    << ddrCmd->getBank() << " col=" << ddrCmd->getColumn() << ".\n";
                )
            }
            break;
        case DDRCommand::Write:
            if ( ct == 0 ) {
                panic("ChannelScheduler", "sendDDRCommand", "Channel transaction provided for "
                                                            "a DDR Write command cannot be NULL");
            }
            issueCmd = modState.canBeIssued(bank, DDRModuleState::C_Write);
            if ( issueCmd ) {
                u32bit id = ct->getRequestSource();
                if ( id == MEMORYMODULE || id == SYSTEM || id > LASTGPUBUS ) {
                    panic("ChannelScheduler", "sendDDRCommand", "Invalid unit identifier");
                }
                writeCmdStat.inc();
                globalWriteCmdStat.inc();
                if ( lastCmdWasRW[bank] ) {
                    totalRowHitStat.inc();
                    globalTotalRowHitStat.inc();
                    perClientRowHit[id].totalHits->inc();
                    perClientRowHit[id].writeHits->inc();
                    globalPerClientRowHit[id].totalHits->inc();
                    globalPerClientRowHit[id].writeHits->inc();
                }
                else {
                    totalRowMissStat.inc();
                    globalTotalRowMissStat.inc();
                    perClientRowHit[id].totalMisses->inc();
                    perClientRowHit[id].writeMisses->inc();
                    globalPerClientRowHit[id].totalMisses->inc();
                    globalPerClientRowHit[id].writeMisses->inc();
                }
                lastCmdWasRW[bank] = true;
                writeBytesStat.inc(ddrCmd->getData()->getSize() * 4);
                globalWriteBytesStat.inc(ddrCmd->getData()->getSize() * 4);
                modState.postWrite(bank);
                GPU_DEBUG( 
                    cout << getName() << " => Sending WRITE bank=" 
                    << ddrCmd->getBank() << " col=" << ddrCmd->getColumn() << ".\n";
                )
            }
            break;
        case DDRCommand::Precharge:
            issueCmd = modState.canBeIssued(bank, DDRModuleState::C_Precharge);
            if ( issueCmd ) {
                prechargeCmdStat.inc();
                globalPrechargeCmdStat.inc();
                lastCmdWasRW[bank] = false;
                modState.postPrecharge(bank);
                GPU_DEBUG( 
                    cout << getName() << " => Sending PRECHARGE bank=";
                    if ( ddrCmd->getBank() == DDRCommand::AllBanks )
                        cout << "ALL.\n";
                    else
                        cout << ddrCmd->getBank() << ".\n";
                )
            }
            break;
            case DDRCommand::Dummy:
                // works if no command is sent at cycle 0 (expected case)
                issueCmd = cycle > moduleRequestLastCycle;
                break;
        default:
            issueCmd = false;
            panic("ChannelScheduler", "sendDDRCommand", "Unexpected DDR command");
    }

    if ( issueCmd ) {


        // cout << "Cycle=" << cycle << ".Prefix=" << prefixStr << ". ChannelScheduler::sendDDRCommand() -> " << ddrCmd->toString() << endl;
        if ( ct ) {
            ddrCmd->copyParentCookies(*ct);
            ddrCmd->addCookie();            
        }
        sprintf((char*)ddrCmd->getInfo(), "%s", ddrCmd->toString().c_str());
        moduleRequest->write(cycle, ddrCmd);
        moduleRequestLastCycle = cycle;
    }

    return issueCmd;
}
DDRCommand* ChannelScheduler::createActive(u32bit bank, u32bit row)
{
    return DDRCommand::createActive(bank, row);
}

DDRCommand* ChannelScheduler::createPrecharge(u32bit bank)
{
    return DDRCommand::createPrecharge(bank);
}

list<DDRCommand*> ChannelScheduler::transactionToCommands(const ChannelTransaction* channelTrans)
{
    list<DDRCommand*> translation;
    u32bit bank = channelTrans->getBank();
    u32bit col = channelTrans->getCol();

    // Compute BurstByte constant
    const u32bit BurstBytes = 4 * BurstLength;
    
    // Compute the number of bursts required to satisfy the request
    u32bit nBurst = channelTrans->bytes() / BurstBytes;
    bool lastMasked = ((channelTrans->bytes() % BurstBytes) != 0);
    if ( lastMasked )
        nBurst++; // Add a burst that will be partially needed (wastes bandwidth)

    if ( channelTrans->isRead() )
    {
        for ( u32bit i = 0; i < nBurst; i++ )
        {
            translation.push_back( DDRCommand::createRead(bank, col, false) );
            col +=  BurstLength;
        }
    }
    else
    {
        const u8bit* data;
        for ( u32bit i = 0; i < nBurst; i++ )
        {
            data = channelTrans->getData(i * BurstBytes);
            DDRBurst* writeBurst = new DDRBurst(BurstLength);

            if ( i == nBurst - 1 && lastMasked ) // The last one is a partial write
            {
                writeBurst->setData(data, channelTrans->bytes() % BurstBytes );
                if ( channelTrans->isMasked() )
                    writeBurst->setMask(channelTrans->getMask(i*BurstLength),
                                        (channelTrans->bytes() % BurstBytes)/4);
	
		//if (channelTrans->getRow() == 1843) {
		//    if (col >= 0 && col <= 100) {
		//        char filename[32];
                //        sprintf(filename, "debugMem.txt");
	        //        FILE *debugfile = fopen(filename, "a+");
	        //        fprintf(debugfile, "GPU[%d]Sched[%d]DDRBank[%d]: create DDRBurst row %d column %d size %d addr 0x%x command %d source %s unitID %d ID %d globalReqID %lld sync %s blit %s lastMasked\n",
	        //        	gpuId, schedulerId, bank, channelTrans->getRow(), col, channelTrans->bytes()%BurstBytes,
		//		channelTrans->getAddress(), channelTrans->getCommand(),
		//		channelTrans->getSource().c_str(), channelTrans->getUnitID(),
		//		channelTrans->getRequestID(), channelTrans->getGlobalReqID(),
		//		channelTrans->getSync() ? "T" : "F",
		//		channelTrans->getBlit() ? "T" : "F");
		//	u32bit numBytes = channelTrans->bytes()%BurstBytes;
	        //        for (u32bit byte = 0; byte < numBytes; byte++) {
	        //            fprintf(debugfile, "data[%d] = 0x%x ", byte, data[byte]);
		//	    if (channelTrans->isMasked()) {
	        //                fprintf(debugfile, "mask[%d] = 0x%x ",
		//	                byte, *((u8bit*)(channelTrans->getMask(i*BurstLength)) + byte));
		//            }
		//	}
	        //        fprintf(debugfile, "\n");
	        //        fflush(debugfile);
	        //        fclose(debugfile);
		//    }
		//}
	
		//if (channelTrans->getRow() == 1874) {
		//    if (col >= 200 && col <= 300) {
		//        char filename[32];
                //        sprintf(filename, "debugMem.txt");
	        //        FILE *debugfile = fopen(filename, "a+");
	        //        fprintf(debugfile, "GPU[%d]Sched[%d]DDRBank[%d]: create DDRBurst row %d column %d size %d addr 0x%x command %d source %s unitID %d ID %d globalReqID %lld sync %s blit %s lastMasked\n",
	        //        	gpuId, schedulerId, bank, channelTrans->getRow(), col, channelTrans->bytes()%BurstBytes,
		//		channelTrans->getAddress(), channelTrans->getCommand(),
		//		channelTrans->getSource().c_str(), channelTrans->getUnitID(),
		//		channelTrans->getRequestID(), channelTrans->getGlobalReqID(),
		//		channelTrans->getSync() ? "T" : "F",
		//		channelTrans->getBlit() ? "T" : "F");
		//	u32bit numBytes = channelTrans->bytes()%BurstBytes;
	        //        for (u32bit byte = 0; byte < numBytes; byte++) {
	        //            fprintf(debugfile, "data[%d] = 0x%x ", byte, data[byte]);
		//	    if (channelTrans->isMasked()) {
	        //                fprintf(debugfile, "mask[%d] = 0x%x ",
		//	                byte, *((u8bit*)(channelTrans->getMask(i*BurstLength)) + byte));
		//            }
		//	}
	        //        fprintf(debugfile, "\n");
	        //        fflush(debugfile);
	        //        fclose(debugfile);
		//    }
		//}
            }
            else
            {
                writeBurst->setData(data, BurstBytes);
                if ( channelTrans->isMasked() )
                    writeBurst->setMask(channelTrans->getMask(i*BurstLength));
		
		//if (channelTrans->getRow() == 1843) {
		//    if (col >= 0 && col <= 100) {
		//        char filename[32];
                //        sprintf(filename, "debugMem.txt");
	        //        FILE *debugfile = fopen(filename, "a+");
	        //        fprintf(debugfile, "GPU[%d]Sched[%d]DDRBank[%d]: create DDRBurst row %d column %d size %d addr 0x%x command %d source %s unitID %d ID %d globalReqID %lld sync %s blit %s\n",
	        //        	gpuId, schedulerId, bank, channelTrans->getRow(), col, BurstBytes,
		//		channelTrans->getAddress(), channelTrans->getCommand(),
		//		channelTrans->getSource().c_str(), channelTrans->getUnitID(),
		//		channelTrans->getRequestID(), channelTrans->getGlobalReqID(),
		//		channelTrans->getSync() ? "T" : "F",
		//		channelTrans->getBlit() ? "T" : "F");
		//	u32bit numWords = BurstBytes/4;
	        //        for (u32bit word = 0; word < numWords; word++) {
	        //            fprintf(debugfile, "data[%d] = %08x ", word, *(((u32bit*)data) + word));
		//	    if (channelTrans->isMasked()) {
	        //                fprintf(debugfile, "mask[%d] = %08x ",
		//	                word, *((channelTrans->getMask(i*BurstLength) + word)));
		//            }
		//	}
	        //        fprintf(debugfile, "\n");
	        //        fflush(debugfile);
	        //        fclose(debugfile);
		//    }
		//}
		
		//if (channelTrans->getRow() == 1874) {
		//    if (col >= 200 && col <= 300) {
		//        char filename[32];
                //        sprintf(filename, "debugMem.txt");
	        //        FILE *debugfile = fopen(filename, "a+");
	        //        fprintf(debugfile, "GPU[%d]Sched[%d]DDRBank[%d]: create DDRBurst row %d column %d size %d addr 0x%x command %d source %s unitID %d ID %d globalReqID %lld sync %s blit %s\n",
	        //        	gpuId, schedulerId, bank, channelTrans->getRow(), col, BurstBytes,
		//		channelTrans->getAddress(), channelTrans->getCommand(),
		//		channelTrans->getSource().c_str(), channelTrans->getUnitID(),
		//		channelTrans->getRequestID(), channelTrans->getGlobalReqID(),
		//		channelTrans->getSync() ? "T" : "F",
		//		channelTrans->getBlit() ? "T" : "F");
		//	u32bit numWords = BurstBytes/4;
	        //        for (u32bit word = 0; word < numWords; word++) {
	        //            fprintf(debugfile, "data[%d] = %08x ", word, *(((u32bit*)data) + word));
		//	    if (channelTrans->isMasked()) {
	        //                fprintf(debugfile, "mask[%d] = %08x ",
		//	                word, *((channelTrans->getMask(i*BurstLength) + word)));
		//            }
		//	}
	        //        fprintf(debugfile, "\n");
	        //        fflush(debugfile);
	        //        fclose(debugfile);
		//    }
		//}
            }
            translation.push_back( DDRCommand::createWrite(bank, col, writeBurst, false) );
            col += BurstLength;
        }
    }
    return translation;
}

const DDRModuleState& ChannelScheduler::moduleState() const
{
    return modState;
}

const string& ChannelScheduler::getDebugString() const
{
    return _debugString;
}

