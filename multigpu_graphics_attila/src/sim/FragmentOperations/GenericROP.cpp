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
 * $RCSfile: GenericROP.cpp,v $
 * $Revision: 1.10 $
 * $Author: vmoya $
 * $Date: 2008-02-22 18:32:47 $
 *
 * Generic ROP box implementation file.
 *
 */

/**
 *
 *  @file GenericROP.cpp
 *
 *  This file implements the Generic ROP box.
 *
 *  This class implements a generic ROP pipeline that will be used
 *  to implement the Z Stencil and Color Write stages of the GPU pipeline.
 *
 */

#include "GenericROP.h"
#include "MemoryTransaction.h"
#include "RasterizerStateInfo.h"
#include "ROPOperation.h"
#include "ROPStatusInfo.h"
#include "GPUMath.h"
#include "GPU.h" // Access to STAMP_FRAGMENTS

#include <sstream>

using namespace gpu3d;

using gpu3d::tools::Queue;

std::vector<std::vector<bool> > GenericROP::allStampsReadForSync = std::vector<std::vector<bool> >();
std::vector<std::vector<bool> > GenericROP::allStampsSentForSync = std::vector<std::vector<bool> >();
std::vector<u32bit> GenericROP::nextSyncReadingGPU = std::vector<u32bit>();

/*  Generic ROP box constructor.  */
GenericROP::GenericROP(

    u32bit gpuId, u32bit numGPUs_, u32bit multiGPUExecMode_, u32bit stampId_,
    //  Rate and latency parameters
    u32bit numStamps, u32bit ropOpRate, u32bit ropLat,

    //  Buffer parameters
    u32bit displayWidth, u32bit displayHeight,
    u32bit overWidth, u32bit overHeight,
    u32bit scanWidth, u32bit scanHeight,
    u32bit genWidth, u32bit genHeight,

    u32bit numStampUnits_,

    //  Cache parameters
    //u32bit cacheWays, u32bit cacheLines, u32bit stampsPerLine, u32bit portWidth, bool extraReadP,
    //bool extraWriteP, u32bit cacheReqQSz, u32bit inputReqQSz, u32bit outputReqQSz, u32bit blocks,
    //u32bit blocksCycle, u32bit comprCycles, u32bit decomprCycles, bool comprDisabled,

    //  Queue parameters
    u32bit inQSz, u32bit fetchQSz, u32bit readQSz, u32bit opQSz, u32bit writeQSz,

    //  Emulator classes
    FragmentOpEmulator &fragEmu, u32bit syncCommQueueSize,
    u32bit syncInQSz, u32bit syncFetchQSz, u32bit syncReadQSz,
    u32bit interGPUBusWidth_, u32bit interGPUBusLat_,
    bool profileForSortLast_, bool compSchedEnabled_,

    //  Other parameters
    char *stageName, char *stageShortName, char *name, char *prefix, Box *parent) :

    numGPUs(numGPUs_), multiGPUExecMode(multiGPUExecMode_), stampId(stampId_),
    numSyncedGPUs(0),
    stampsCycle(numStamps), ropRate(ropOpRate), ropLatency(ropLat),

    displayH(displayHeight), displayW(displayWidth),
    overH(overHeight), overW(overWidth),
    scanH((u32bit) ceil(scanHeight / (f32bit) genHeight)), scanW((u32bit) ceil(scanWidth / (f32bit) genWidth)),
    genH(genHeight / STAMP_HEIGHT), genW(genWidth / STAMP_WIDTH),

    numStampUnits(numStampUnits_),

    inQueueSize(inQSz), fetchQueueSize(fetchQSz), readQueueSize(readQSz), opQueueSize(opQSz),
    writeQueueSize(writeQSz),

    frEmu(fragEmu), syncCommQueueSzPerGPU(syncCommQueueSize),
    syncInQueueSize(syncInQSz), syncFetchQueueSize(syncFetchQSz), syncReadQueueSize(syncReadQSz),
    interGPUBusWidth(interGPUBusWidth_), interGPUBusLat(interGPUBusLat_),
    profileForSortLast(profileForSortLast_), compSchedEnabled(compSchedEnabled_),

    batchCounter(0), frameCounter(0),

    ropName(stageName), ropShortName(stageShortName), Box(gpuId, name, parent)

{
    char fullName[64];
    char postfix[32];

    /*  Check parameters.  */
    GPU_ASSERT(
        if (stampsCycle == 0)
            panic(ropName, ropName, "At least a stamp must be received per cycle.");
        if (displayW == 0)
            panic(ropName, ropName, "Display tile must be at least 1 scan tile wide.");
        if (displayH == 0)
            panic(ropName, ropName, "Display tile must be at least 1 scan tile high.");
        if (overW == 0)
            panic(ropName, ropName, "Over scan tile must be at least 1 scan tile wide.");
        if (overH == 0)
            panic(ropName, ropName, "Over scan tile must be at least 1 scan tile high.");
        if (scanW == 0)
            panic(ropName, ropName, "Scan tile must be at least 1 generation tile wide.");
        if (scanH == 0)
            panic(ropName, ropName, "Scan tile must be at least 1 generation tile high.");
        if (genW == 0)
            panic(ropName, ropName, "Scan tile must be at least 1 stamp wide.");
        if (genH == 0)
            panic(ropName, ropName, "Scan tile must be at least 1 stamp high.");

        if (inQueueSize < 2 * stampsCycle)
            panic(ropName, ropName, "ROP input stamp queue requires at least two entries.");
        if (fetchQueueSize < 1)
            panic(ropName, ropName, "ROP fetch stamp queue requires at least one entry.");
        if (readQueueSize < 1)
            panic(ropName, ropName, "ROP read stamp queue requires at least one entry.");
        if (opQueueSize < ropLatency)
            panic(ropName, ropName, "ROP operation stamp queue requires at least as many entries as the ROP operation latency.");
        if (writeQueueSize < 1)
            panic(ropName, ropName, "ROP written stamp queue requires at least one entry.");
        if (syncInQueueSize < 2 * stampsCycle)
            panic(ropName, ropName, "ROP sync input stamp queue requires at least two entries.");
        if (syncFetchQueueSize < 1)
            panic(ropName, ropName, "ROP sync fetch stamp queue requires at least one entry.");
        if (syncFetchQueueSize != syncInQueueSize)
            panic(ropName, ropName, "Current implementation requires syncFetchQueueSize to be same as syncInQueueSize.");
        if (syncReadQueueSize < 1)
            panic(ropName, ropName, "ROP sync read stamp queue requires at least one entry.");
        if (syncReadQueueSize != syncInQueueSize)
            panic(ropName, ropName, "Current implementation requires syncReadQueueSize to be same as syncInQueueSize.");

        if (ropRate == 0)
            panic(ropName, ropName, "ROP operation rate must be at least 1.");
        if (ropLatency < 1)
            panic(ropName, ropName, "ROP operation latency must be 1 or greater.");
    )

    /*  Create the full name and postfix for the statistics.  */
    sprintf(fullName, "%s::%s", prefix, name);
    sprintf(postfix, "%s-%s", ropShortName, prefix);

    /*  Create statistics.  */
    inputs = &getSM(gpuId).getNumericStatistic("InputFragments", u32bit(0), fullName, postfix);
    operated = &getSM(gpuId).getNumericStatistic("OperatedFragments", u32bit(0), fullName, postfix);
    outside = &getSM(gpuId).getNumericStatistic("OutsideFragments", u32bit(0), fullName, postfix);
    culled = &getSM(gpuId).getNumericStatistic("CulledFragments", u32bit(0), fullName, postfix);
    readTrans = &getSM(gpuId).getNumericStatistic("ReadTransactions", u32bit(0), fullName, postfix);
    writeTrans = &getSM(gpuId).getNumericStatistic("WriteTransactions", u32bit(0), fullName, postfix);
    readBytes = &getSM(gpuId).getNumericStatistic("ReadBytes", u32bit(0), fullName, postfix);
    writeBytes = &getSM(gpuId).getNumericStatistic("WriteBytes", u32bit(0), fullName, postfix);
    fetchOK = &getSM(gpuId).getNumericStatistic("FetchOK", u32bit(0), fullName, postfix);
    fetchFail = &getSM(gpuId).getNumericStatistic("FetchFailed", u32bit(0), fullName, postfix);
    allocateOK = &getSM(gpuId).getNumericStatistic("AllocateOK", u32bit(0), fullName, postfix);
    allocateFail = &getSM(gpuId).getNumericStatistic("AllocateFailed", u32bit(0), fullName, postfix);
    readOK = &getSM(gpuId).getNumericStatistic("ReadOK", u32bit(0), fullName, postfix);
    readFail = &getSM(gpuId).getNumericStatistic("ReadFailed", u32bit(0), fullName, postfix);
    writeOK = &getSM(gpuId).getNumericStatistic("WriteOK", u32bit(0), fullName, postfix);
    writeFail = &getSM(gpuId).getNumericStatistic("WriteFailed", u32bit(0), fullName, postfix);
    rawDep = &getSM(gpuId).getNumericStatistic("RAWDependence", u32bit(0), fullName, postfix);
    ropOpBusy = &getSM(gpuId).getNumericStatistic("ROPOperatorBusy", u32bit(0), fullName, postfix);
    consumerBusy = &getSM(gpuId).getNumericStatistic("ConsumerBusy", u32bit(0), fullName, postfix);
    inputEmpty = &getSM(gpuId).getNumericStatistic("InputQEmpty", u32bit(0), fullName, postfix);
    fetchEmpty = &getSM(gpuId).getNumericStatistic("FetchQEmpty", u32bit(0), fullName, postfix);
    readEmpty = &getSM(gpuId).getNumericStatistic("ReadQEmpty", u32bit(0), fullName, postfix);
    opEmpty = &getSM(gpuId).getNumericStatistic("OperationQEmpty", u32bit(0), fullName, postfix);
    writeEmpty = &getSM(gpuId).getNumericStatistic("WriteQEmpty", u32bit(0), fullName, postfix);
    fetchFull = &getSM(gpuId).getNumericStatistic("FetchQFullStall", u32bit(0), fullName, postfix);
    readFull = &getSM(gpuId).getNumericStatistic("ReadQFullStall", u32bit(0), fullName, postfix);
    opFull = &getSM(gpuId).getNumericStatistic("OperationQFullStall", u32bit(0), fullName, postfix);
    writeFull = &getSM(gpuId).getNumericStatistic("WriteQFullStall", u32bit(0), fullName, postfix);
    numDummyFrags = &getSM(gpuId).getNumericStatistic("NumberOfDummyFragments", u32bit(0), fullName, postfix);

    globalInputs = &getSM().getNumericStatistic("InputFragments", u32bit(0), fullName, postfix);
    globalOperated = &getSM().getNumericStatistic("OperatedFragments", u32bit(0), fullName, postfix);
    globalOutside = &getSM().getNumericStatistic("OutsideFragments", u32bit(0), fullName, postfix);
    globalCulled = &getSM().getNumericStatistic("CulledFragments", u32bit(0), fullName, postfix);
    globalReadTrans = &getSM().getNumericStatistic("ReadTransactions", u32bit(0), fullName, postfix);
    globalWriteTrans = &getSM().getNumericStatistic("WriteTransactions", u32bit(0), fullName, postfix);
    globalReadBytes = &getSM().getNumericStatistic("ReadBytes", u32bit(0), fullName, postfix);
    globalWriteBytes = &getSM().getNumericStatistic("WriteBytes", u32bit(0), fullName, postfix);
    globalFetchOK = &getSM().getNumericStatistic("FetchOK", u32bit(0), fullName, postfix);
    globalFetchFail = &getSM().getNumericStatistic("FetchFailed", u32bit(0), fullName, postfix);
    globalAllocateOK = &getSM().getNumericStatistic("AllocateOK", u32bit(0), fullName, postfix);
    globalAllocateFail = &getSM().getNumericStatistic("AllocateFailed", u32bit(0), fullName, postfix);
    globalReadOK = &getSM().getNumericStatistic("ReadOK", u32bit(0), fullName, postfix);
    globalReadFail = &getSM().getNumericStatistic("ReadFailed", u32bit(0), fullName, postfix);
    globalWriteOK = &getSM().getNumericStatistic("WriteOK", u32bit(0), fullName, postfix);
    globalWriteFail = &getSM().getNumericStatistic("WriteFailed", u32bit(0), fullName, postfix);
    globalRawDep = &getSM().getNumericStatistic("RAWDependence", u32bit(0), fullName, postfix);
    globalRopOpBusy = &getSM().getNumericStatistic("ROPOperatorBusy", u32bit(0), fullName, postfix);
    globalConsumerBusy = &getSM().getNumericStatistic("ConsumerBusy", u32bit(0), fullName, postfix);
    globalInputEmpty = &getSM().getNumericStatistic("InputQEmpty", u32bit(0), fullName, postfix);
    globalFetchEmpty = &getSM().getNumericStatistic("FetchQEmpty", u32bit(0), fullName, postfix);
    globalReadEmpty = &getSM().getNumericStatistic("ReadQEmpty", u32bit(0), fullName, postfix);
    globalOpEmpty = &getSM().getNumericStatistic("OperationQEmpty", u32bit(0), fullName, postfix);
    globalWriteEmpty = &getSM().getNumericStatistic("WriteQEmpty", u32bit(0), fullName, postfix);
    globalFetchFull = &getSM().getNumericStatistic("FetchQFullStall", u32bit(0), fullName, postfix);
    globalReadFull = &getSM().getNumericStatistic("ReadQFullStall", u32bit(0), fullName, postfix);
    globalOpFull = &getSM().getNumericStatistic("OperationQFullStall", u32bit(0), fullName, postfix);
    globalWriteFull = &getSM().getNumericStatistic("WriteQFullStall", u32bit(0), fullName, postfix);
    globalNumDummyFrags = &getSM().getNumericStatistic("NumberOfDummyFragments", u32bit(0), fullName, postfix);

    //
    //  WARNING
    //
    //  Signal creation and related initializations must be performed in the
    //  derived class constructor
    //


    //
    //  WARNING.
    //
    //  The ROP Cache should be created and initialized in the derived class
    //  constructor from a Cache class derived from the generic ROP cache class.
    //


    string queueName;

    //  Set queue names.
    queueName.clear();
    queueName.append("InputStampQueue");
    queueName.append(postfix);
    inQueue.setName(queueName);
    queueName.clear();
    queueName.append("FetchStampQueue");
    queueName.append(postfix);
    fetchQueue.setName(queueName);
    queueName.clear();
    queueName.append("ReadStampQueue");
    queueName.append(postfix);
    readQueue.setName(queueName);
    queueName.clear();
    queueName.append("OpStampQueue");
    queueName.append(postfix);
    opQueue.setName(queueName);
    queueName.clear();
    queueName.append("WriteStampQueue");
    queueName.append(postfix);
    writeQueue.setName(queueName);
    queueName.append("FreeStampQueue");
    queueName.append(postfix);
    freeQueue.setName(queueName);
    
    queueName.clear();
    queueName.append("SyncInputStampQueue");
    queueName.append(postfix);
    syncInQueue.setName(queueName);
    queueName.clear();
    queueName.append("SyncFetchStampQueue");
    queueName.append(postfix);
    syncFetchQueue.setName(queueName);
    queueName.clear();
    queueName.append("SyncReadStampQueue");
    queueName.append(postfix);
    syncReadQueue.setName(queueName);
    queueName.clear();
    queueName.append("SyncStampQueue");
    queueName.append(postfix);
    syncQueue.setName(queueName);

    //  Create and initialize the ROP stage queues.
    inQueue.resize(inQueueSize);
    fetchQueue.resize(fetchQueueSize);
    readQueue.resize(readQueueSize);
    opQueue.resize(opQueueSize);
    writeQueue.resize(writeQueueSize);

    syncQueueSize = syncInQueueSize + syncFetchQueueSize + syncReadQueueSize;
    syncInQueue.resize(syncInQueueSize);
    syncFetchQueue.resize(syncFetchQueueSize);
    syncReadQueue.resize(syncReadQueueSize);
    syncQueue.resize(syncQueueSize);
    
    //
    //  WARNING:
    //
    //  The free stamp queue must be initialized in the derived class
    //  constructor.
    //
    //

    //  Calculate the total number of stamps in the free stamp queue.
    u32bit freeQueueSize = inQueueSize + fetchQueueSize + readQueueSize + ropLatency + opQueueSize + writeQueueSize +
			   syncInQueueSize + syncFetchQueueSize + syncReadQueueSize;


    //  Calculate the size of the CAM used to detect RAW dependences in the
    //  ROP pipeline.
    sizeCAM = readQueueSize + ropLatency + opQueueSize;

    //  Initialize the read non-written CAM for RAW dependence detection.
    rawCAM.clear();
    rawCAM.resize(sizeCAM);

    //  Initialize the read non-written CAM.
    for(int i = 0; i < rawCAM.size(); i++)
        rawCAM[i] = NULL;

    //  Initialize RAW CAM counters and pointers.
    freeCAM = firstCAM = 0;
    stampsCAM = 0;
    
    memoryCycles = 0;
    nextWriteTicket = 0;

    syncCommQueue = new RasterizerSyncCommand**[numGPUs];
    for (u32bit i = 0; i < numGPUs; i++) {
        syncCommQueue[i] = new RasterizerSyncCommand*[syncCommQueueSzPerGPU];
	for (u32bit j = 0; j < syncCommQueueSzPerGPU; j++) {
	    syncCommQueue[i][j] = NULL;
	}
    }

    nextSyncRead = new u32bit[numGPUs];
    nextSyncWrite = new u32bit[numGPUs];
    numSyncCommQueueFreeEntries = new u32bit[numGPUs];
    numReceived = new u32bit[numGPUs];
    numProcessed = new u32bit[numGPUs];
    for (u32bit i = 0; i < numGPUs; i++) {
	nextSyncRead[i] = 0;
	nextSyncWrite[i] = 0;
        numSyncCommQueueFreeEntries[i] = syncCommQueueSzPerGPU;
	numReceived[i] = 0;
	numProcessed[i] = 0;
    }

    //
    //  WARNING:
    //
    //  Who can initialize the free queue?  Only the derived classes know the specific ROPQueue
    //  element size.

    //  Initialize the ROP Queue objects in the free stamp queue.
    //for(i = 0; i < freeQueueSize; i++)
    //    freeQueue.add(new ROPQueue);

    currInQueue = NULL;
    currFetchQueue = NULL;
    nextInQueue = NULL;
    nextFetchQueue = NULL;

    if (gpuId == 0 && stampId == 0) {
	allStampsReadForSync.resize(numGPUs);
	allStampsSentForSync.resize(numGPUs);
	nextSyncReadingGPU.resize(numGPUs);
	for (u32bit i = 0; i < numGPUs; i++) {
	    allStampsReadForSync[i].resize(numStampUnits, false);
	    allStampsSentForSync[i].resize(numStampUnits, false);
	}
    }

    //  Set initial state to reset.
    state = RAST_RESET;
}

/*  Generic ROP simulation function.  */
void GenericROP::clock(u64bit cycle)
{
    MemoryTransaction *memTrans;
    RasterizerCommand *rastComm;
    RasterizerSyncCommand *rastSyncComm;
    ROPStatusInfo *consumerStateInfo;
    ROPStatusInfo *consumerSyncStateInfo;
    u32bit gpuIndex;

    GPU_DEBUG_BOX(
        printf("%s => Clock %lld\n", getName(), cycle);
    )

    //  Receive state from Memory Controller.
    while(memData->read(cycle, (DynamicObject *&) memTrans))
        processMemoryTransaction(cycle, memTrans);

    memTrans = NULL;

    //  Update ROP cache structures.
    memTrans = ropCache->update(cycle, memoryState);

    //  Call the specific post cache update/clock function.
    postCacheUpdate(cycle);

    //  Check if a memory transaction was generated.
    if (memTrans != NULL)
    {
        //  Send memory transaction to the Memory Controller.
        memRequest->write(cycle, memTrans);

        //  Update statistics.
        switch(memTrans->getCommand())
        {
            case MT_READ_REQ:

                readTrans->inc();
                globalReadTrans->inc();
                break;

            case MT_WRITE_DATA:

                writeTrans->inc();
                writeBytes->inc(memTrans->getSize());
                globalWriteTrans->inc();
                globalWriteBytes->inc(memTrans->getSize());
                break;

            default:
                panic(getName(), "clock", "Unknown memory transaction.");
        }
    }

    //  Check if there is a consumer stage attached to the Generic ROP pipeline
    //  that receives processed fragments from the Generic ROP.
    if (consumerStateSignal != NULL)
    {
        //  Receive state from the consumer stage.
        if (consumerStateSignal->read(cycle, (DynamicObject *&) consumerStateInfo))
        {
            //  Get consumer state.
            consumerState = consumerStateInfo->getState();

            //  Delete state container object.
            delete consumerStateInfo;
        }
        else
        {
            panic(getName(), "clock", "Missing state signal from consumer stage.");
        }
    }
    else
    {
        //  No consumer so always ready to process written stamps.
        consumerState = ROP_READY;
    }

    //  Receive sync state from the consumer stage.
    if (consumerSyncStateSignal->read(cycle, (DynamicObject *&) consumerSyncStateInfo))
    {
        //  Get consumer sync state.
        consumerSyncState = consumerSyncStateInfo->getState();

        //  Delete state container object.
        delete consumerSyncStateInfo;
    }
    else
    {
        panic(getName(), "clock", "Missing sync state signal from consumer stage.");
    }
    
    for (gpuIndex = 0; gpuIndex < numGPUs; gpuIndex++) {
        if (gpuIndex != gpuId && numSyncCommQueueFreeEntries[gpuIndex] > 0) {
	    while (interGPUSync[gpuIndex]->read(cycle, (DynamicObject *&)rastSyncComm)) {
                syncCommQueue[gpuIndex][nextSyncWrite[gpuIndex]] = rastSyncComm;
		nextSyncWrite[gpuIndex] = GPU_MOD(nextSyncWrite[gpuIndex] + 1, syncCommQueueSzPerGPU);
		numSyncCommQueueFreeEntries[gpuIndex]--;
		numReceived[gpuIndex]++;
	    }
	}
    }

    //  Simulate current cycle.
    switch(state)
    {
        case RAST_RESET:

            //  Reset state.

            GPU_DEBUG_BOX(
                printf("%s => Reset state.\n", getName());
            )

            //  Call the specific reset function.
            reset();

            //  Reset the ROP cache.
            ropCache->reset();
            ropCache->setBytesPerPixel(bytesPixel[0]);
            ropCache->setCompression(compression);
            ropCache->update(cycle, memoryState);

            //  Set ROP buffer address in the Z cache.
            ropCache->swap(bufferAddress[0]);

            //  Reset rop operation start cycle counter.
            ropCycles = 0;

            //  Change state to ready.
            state = RAST_READY;

            break;

        case RAST_READY:

            //  Ready state.

            GPU_DEBUG_BOX(
                printf("%s => Ready state.\n", getName());
            )

            //  Receive and process a rasterizer command.
            if(rastCommand->read(cycle, (DynamicObject *&) rastComm))
            {
                //  Call the specific process command function
                processCommand(rastComm, cycle);
            }

            break;

        case RAST_DRAWING:

            //  Draw state.

            GPU_DEBUG_BOX(
                printf("%s => Drawing state.\n", getName());
            )

            //  Check end of the batch.
            if (lastFragment && freeQueue.full() && (memTrans == NULL))
            {
                GPU_DEBUG_BOX(
                    printf("%s (%p) => Sending last stamp\n", getName(), this);
                )

                //  Call the specific end batch function of the derived class.
                endBatch(cycle);

                //  Change state to end.
                state = RAST_END;
            }

            //  Terminate the processing of the stamp.
            terminateStamp(cycle);

            //  Write stamp
            writeStamp(cycle);

            //  End ROP operation
            endOperation(cycle);

            //  Start ROP operation
            startOperation(cycle);

            //  Read stamp data
            readStamp(cycle);

            //  Fetch stamp data
            fetchStamp(cycle);

            //  Receive stamps.
            receiveStamps(cycle);

            break;

        case RAST_END:

            /*  End of batch state.  */

            GPU_DEBUG_BOX(
                printf("ZStencilTest => End state.\n");
            )

            /*  Wait for end command.  */
            if (rastCommand->read(cycle, (DynamicObject *&) rastComm))
                processCommand(rastComm, cycle);

            break;

        case RAST_SWAP:

            /*  Swap buffer state.  */

            GPU_DEBUG_BOX(
                printf("%s => Swap state.\n", getName());
            )

            swap(cycle);

            break;

        case RAST_FLUSH:

            //  ROP Flush state.

            GPU_DEBUG_BOX(
                printf("%s => Flush state.\n", getName());
            )

            flush(cycle);

            break;

        case RAST_SAVE_STATE:

            //  ROP Save State state.

            GPU_DEBUG_BOX(
                printf("%s => Save State state.\n", getName());
            )

            //  Check if the save state request has finished.
            if (!endFlush)
            {
                //  Continue saving the block state info into memory.
                if(!ropCache->saveState())
                {
                    //  Set flush end.
                    endFlush = true;
                }
            }
            else
            {
                //  End of save state.
                state = RAST_END;
            }

            break;

        case RAST_RESTORE_STATE:

            //  ROP Restore State state.

            GPU_DEBUG_BOX(
                printf("%s => Restore State state.\n", getName());
            )

            //  Check if the restore state request has finished.
            if (!endFlush)
            {
                //  Continue saving the block state info into memory.
                if(!ropCache->restoreState())
                {
                    //  Set flush end.
                    endFlush = true;
                }
            }
            else
            {
                //printf("%s (%lld) => End of RAST_RESTORE_STATE.\n", getName(), cycle);
                //  End of swap.
                state = RAST_END;
            }

            break;

        case RAST_RESET_STATE:
                   
            //  ROP Reset Block State state.

            GPU_DEBUG_BOX(
                printf("%s => Reset Block State state.\n", getName());
            )

            //  Check if the reset block state request has finished.
            if (!endFlush)
            {
                //  Continue reset of the block state until it has finished..
                if(!ropCache->resetState())
                {
                    //  Set flush end.
                    endFlush = true;
                }
            }
            else
            {
                //  End of swap.
                state = RAST_END;
            }

            break;
        
        case RAST_CLEAR:

            //  Clear Z and stencil buffer state.

            GPU_DEBUG_BOX(
                printf("%s => Clear state.\n", getName());
            )

            //  Call the specific clear function
            clear();

            break;
	
        case RAST_CLEAR_FOR_COMP:

            //  Clear Z and stencil buffer state.

            GPU_DEBUG_BOX(
                printf("%s => Clear state for comp.\n", getName());
            )

            //  Call the specific clear function
            clearForComp(cycle);

            break;
	
	case RAST_SYNC:
	    // Inter-GPU synchronization for colorBuffer and zstBuffer
	    
            GPU_DEBUG_BOX(
                printf("%s => Sync state.\n", getName());
            )
        
            GPU_ASSERT(
                if (memTrans != NULL)
                    panic("GenericROP", "clock", "ropCache should have been flushed in state RAST_SYNC");	    
            )

            sync(cycle, memoryState);
            
	    break;

	case RAST_COMP:
	    // Inter-GPU composition for colorBuffer and zstBuffer
	    
            GPU_DEBUG_BOX(
                printf("%s => Comp state.\n", getName());
            )
      
	    currInQueue = nextInQueue;
	    currFetchQueue = nextFetchQueue;

	    comp(cycle);

            if ((notLastSyncSent == 0) && (notLastSyncReceive == 0) && (memTrans == NULL)) {
		GPU_ASSERT(
		    if (!freeQueue.full())
                     	panic(getName(), "clock", "free queue should be full now");
		    if (!compFetchingPoses.empty())
		        panic(getName(), "clock", "compFetchingPoses should be empty now");
		    if (!compReadingPoses.empty())
		        panic(getName(), "clock", "compReadingPoses should be empty now");
		    if (!compTerminatingPoses.empty())
		        panic(getName(), "clock", "compTerminatingPoses should be empty now");
		)
                
		currInQueue = NULL;
                currFetchQueue = NULL;
                nextInQueue = NULL;
                nextFetchQueue = NULL;

		ropCache->compMode = false;

                state = RAST_END;
		std::cout << "Debug: " << getName() << " finished comp @" << cycle << std::endl;
	    }

	    break;

	case RAST_BLIT:
	    
            GPU_DEBUG_BOX(
                printf("%s => Blit state.\n", getName());
            )
       
            blit(cycle);
            
	    break;

        default:

            panic(getName(), "clock", "Unsupported state.");
            break;

    }

    //  Send current state to stage that produces the fragments to be processed
    //    by the ROP stage.
    if (inQueue.items() < (inQueueSize - (2 * stampsCycle)))
    {
        GPU_DEBUG_BOX(
            printf("%s => Sending READY.\n", getName());
        )

        //  Send a ready signal.
        ropStateSignal->write(cycle, new ROPStatusInfo(ROP_READY));
    }
    else
    {
        GPU_DEBUG_BOX(
            printf("%s => Sending BUSY.\n", getName());
        )

        //  Send a busy signal.
        ropStateSignal->write(cycle, new ROPStatusInfo(ROP_BUSY));
    }

    if (ropSyncStateSignal) {
        //if (syncInQueue.items() < (syncInQueueSize - (2 * stampsCycle)))
        if (syncQueue.items() < (syncQueueSize - (2 * stampsCycle)))
        {
            GPU_DEBUG_BOX(
                printf("%s => Sending READY for sync.\n", getName());
            )

            //  Send a ready signal.
            ropSyncStateSignal->write(cycle, new ROPStatusInfo(ROP_READY));
        }
        else
        {
            GPU_DEBUG_BOX(
                printf("%s => Sending BUSY for sync.\n", getName());
            )

            //  Send a busy signal.
            ropSyncStateSignal->write(cycle, new ROPStatusInfo(ROP_BUSY));
        }
    }

    //  Send current rasterizer state.
    rastState->write(cycle, new RasterizerStateInfo(state));
}


//  Processes a stamp.
void GenericROP::processStamp(u64bit cycle)
{
    Fragment *fr;
    QuadFloat *attrib;
    u32bit address;
    s32bit x, y;
    u32bit i;
    bool cullStamp;
    ROPQueue *currentStamp;
    bool cullSyncStamp;
    u32bit offset;

    //  Get a free queue object from the free queue
    if (!freeQueue.empty())
        currentStamp = freeQueue.pop();
    else
        panic(getName(), "processStamp", "No free queue objects.");

    //  Keep the stamp in the queue.
    currentStamp->stamp = stamp;

    //  Get first stamp fragment.
    fr = stamp[0]->getFragment();

    //  NOTE: ALL THE FRAGMENTS IN THE LAST STAMP MUST BE NULL.

    //  Check if first fragment exists (not last fragment).
    if (fr != NULL)
    {
        //
        //  WARNNING
        //  Z BUFFER AND COLOR BUFFER COULD USE DIFFERENT MEMORY LAYOUTS, SO THEY MAY HAVE
        //  TO USE DIFFERENT FUNCTIONS TO CALCULATE THE ADDRESS.  FOR NOW WE ARE USING
        //  THE SAME FUNCTION.
        //
        //  IF IT IS ALWAYS THE SAME ADDRESS IT WOULD BE BETTER TO CALCULATE THE ADDRESS
        //  AT RASTERIZATION AND STORE IT AS A FRAGMENT PARAMETER.
        //

        //  Get fragment attributes.
        //attrib = stamp[0]->getAttributes();

        //  Get fragment position.
        //x = (s32bit) attrib[POSITION_ATTRIBUTE][0];
        //y = (s32bit) attrib[POSITION_ATTRIBUTE][1];
        x = fr->getX();
        y = fr->getY();

	cullSyncStamp = (stamp[0]->getType() == FRAG_COMP_OUT);
	offset = 0;
        //  Compute the addresses for all the active output buffers.
        for(u32bit b = 0, current = 0; b < numActiveBuffers; b++, current++)
        {
            //  Search for the next active buffer.
            for (;(!activeBuffer[current]) && (current < MAX_RENDER_TARGETS); current++);
            
            GPU_ASSERT(
                if (current == MAX_RENDER_TARGETS)
                    panic("GenericROP", "processStamp", "Expected an active output buffer.");
            )
	   
	    currentStamp->offset[current] = offset;
	    if (!multisampling)
		offset += STAMP_FRAGMENTS * bytesPixel[current];
	    else
		panic(getName(), "processStamp", "current implementation cannot support multisampling");
            
            address = pixelMapper[current].computeAddress(x, y);

            //  Add the current ROP buffer base address.
	    if (ropCache->compMode && !strcmp(ropName, "ColorWrite") && ropCache->anyRtBlend &&
		(stamp[0]->getType() == FRAG_NORMAL || stamp[0]->getType() == FRAG_COMP_OUT ||
		 (compSchedEnabled && stamp[0]->getType() == FRAG_COMP_IN &&
		  GPUDriver::getGPUDriver()->getCompSched()->compWithCompBuffer(stamp[0]->getSrcGPUId(), gpuId))))
                address += bufferAddressForComp[current];
	    else
                address += bufferAddress[current];

            //  Set ROP buffer address for the stamp.
            currentStamp->address[current] = address;

	    if (!strcmp(ropName, "ZStencilTest"))
	        cullSyncStamp = cullSyncStamp && !ropCache->getAddrBlockState(address).dirty;
	    else
	        cullSyncStamp = cullSyncStamp && !ropCache->getAddrBlockStateForComp(current, address).dirty;

            //if (stamp[0]->getFragment() && stamp[0]->getFragment()->getX() == 172 && stamp[0]->getFragment()->getY() == 146) { 
            //    FILE *debugfile = fopen("comp_generic_debug.txt", "a+");
            //    fprintf(debugfile, "%s cycle %lld frame %d batch %d process frag (%d, %d) type %d current %d bypassROP %s bytesPixel %d addr 0x%x bufferAddr 0x%x bufferAddrForComp 0x%x frameBufferSize 0x%x compState %d state %d compMode %s anyRtBlend %s cullSyncStamp %s\n",
	    //    	getName(), cycle, frameCounter, batchCounter, stamp[0]->getFragment()->getX(), stamp[0]->getFragment()->getY(),
	    //	        stamp[0]->getType(), current, bypassROP[current] ? "T" : "F",
	    //    	bytesPixel[current], address,
	    //    	bufferAddress[current], bufferAddressForComp[current],
	    //    	pixelMapper[current].computeFrameBufferSize(),
	    //    	ropCache->getAddrBlockStateForComp(current, address).getState(),
	    //    	ropCache->getAddrBlockState(address).getState(),
	    //    	ropCache->compMode ? "T" : "F", ropCache->anyRtBlend ? "T" : "F",
	    //    	cullSyncStamp ? "T" : "F");
            //    fflush(debugfile);
            //    fclose(debugfile);
            //}
        }

        //  Reset output buffer counter.
        currentStamp->nextBuffer = 0;
	currentStamp->nextCompFetchBuffer = 0;
	currentStamp->nextCompReadBuffer = 0;
        
        //  Reset multisampling counter.
        currentStamp->nextSample = 0;
        
        //  Store the stamp fragment data in the ROP queue entry.
        for(i = 0; (i < STAMP_FRAGMENTS) && (!lastFragment || stamp[0]->getType() != FRAG_NORMAL); i++)
        {
            //  Get stamp fragment.
            fr = stamp[i]->getFragment();

            //  Check if fragment is NULL.
            GPU_ASSERT(
                if (fr == NULL)
                    panic(getName(), "processStamp", "NULL fragment not in last stamp.");
            )

            //if ((fr->getX() == 82) && (fr->getY() == 890))
            //{
            //printf("%s => Fragment (%d, %d) triangleID %d passed through here, culled %s\n", getName(), 82, 890,
            //stamp[i]->getTriangleID(), stamp[i]->isCulled() ? "T" : "F");
            //}

            //if (!strcmp(ropName, "ColorWrite") && stamp[i]->getDebug()) {
            if (!strcmp(ropName, "ZStencilTest") && stamp[i]->getDebug()) {
	        char filename[32];
	        //sprintf(filename, "debugCWProcStamp%d.txt", stampId);
	        sprintf(filename, "debugZSTProcStamp%d.txt", stampId);
		s32bit v1, v2, v3;
		fr->getTriangle()->getIndexes(v1, v2, v3);
	        FILE *debugfile = fopen(filename, "a+");
                fprintf(debugfile, "GPU[%d] %s => cycle %lld batch %d processStamp (%d, %d) triangleID %d indexes (%d, %d, %d) culled %s\n",
	        	gpuId, getName(), cycle, batchCounter, 
	        	fr->getX(), fr->getY(), stamp[i]->getTriangleID(),
			v1, v2, v3, stamp[i]->isCulled() ? "T" : "F");
                for(u32bit b = 0, current = 0; b < numActiveBuffers; b++, current++) {
                    for(;(!activeBuffer[current]) && (current < MAX_RENDER_TARGETS); current++);
	            fprintf(debugfile, "addr[%d] = 0x%x ", current, currentStamp->address[current]);
	        }
	        fprintf(debugfile, "\n");
	        QuadFloat* attributes = stamp[i]->getAttributes();
		if (attributes) {
                    for (u32bit j = 0; j < MAX_FRAGMENT_ATTRIBUTES; j++) {
                        fprintf(debugfile, "attrib[%d] = { %f, %f, %f, %f }\n", j,
	                        attributes[j][0], attributes[j][1],
                                attributes[j][2], attributes[j][3]);
	            }
		}
	        fflush(debugfile);
	        fclose(debugfile);
	    }

            //  Set fragment cull flag in the stamp.
            currentStamp->culled[i] = stamp[i]->isCulled();

            //  Check if the fragment is culled.
            if (!stamp[i]->isCulled())
            {
                //  Not last fragment and fragment inside the triangle.

                //  Get fragment attributes.
                //attrib = stamp[i]->getAttributes();

                GPU_DEBUG_BOX(
                    //  Get fragment position.
                    //x = (s32bit) attrib[POSITION_ATTRIBUTE][0];
                    //y = (s32bit) attrib[POSITION_ATTRIBUTE][1];
                    x = fr->getX();
                    y = fr->getY();
                    printf("%s => Received Fragment Not Culled (%d, %d) Inside? %s.\n",
                        getName(), x, y, fr->isInsideTriangle()?"IN":"OUT");
                )
            }
            else
            {
                //  Fragment culled.
                GPU_DEBUG_BOX(
                    printf("%s => Received Fragment Culled (%d, %d) Inside? %s.\n",
                        getName(),
                        fr->getX(), fr->getY(),
                        fr->isInsideTriangle()?"IN":"OUT");
                )

                //  Update statistics.
                outside->inc();
                globalOutside->inc();
            }
        }

        //  Calculate if the stamp should be culled (all fragments masked).
        for(i = 0, cullStamp = TRUE; i < STAMP_FRAGMENTS; i++)
            cullStamp = cullStamp && currentStamp->culled[i];

        //if (stamp[0]->getFragment() && stamp[0]->getFragment()->getX() == 172 && stamp[0]->getFragment()->getY() == 146) {
        //    FILE *debugfile = fopen("comp_generic_debug.txt", "a+");
        //    fprintf(debugfile, "%s cycle %lld frame %d batch %d process frag (%d, %d) type %d culled %s cullStamp %s cullSyncStamp %s\n",
	//	    getName(), cycle, frameCounter, batchCounter, stamp[0]->getFragment()->getX(), stamp[0]->getFragment()->getY(),
	//	    stamp[0]->getType(), currentStamp->culled[0] ? "T" : "F", cullStamp ? "T" : "F", cullSyncStamp ? "T" : "F");
        //    fflush(debugfile);
        //    fclose(debugfile);
        //}

        //  Check if the whole stamp can be culled.
        if (!cullStamp && !cullSyncStamp)
        {
            //  The stamp can not be culled

            //  Add the stamp to the input queue.
	    switch (stamp[0]->getType()) {
		case FRAG_NORMAL:
		case FRAG_COMP_IN:
		    inQueue.add(currentStamp);
		    break;

		case FRAG_COMP_OUT:
		    compFetchingPoses.push(syncQueue.add(currentStamp));
		    break;

		default:
		    panic(getName(), "processStamp", "invalid fragment type");
	    }
        }
        else
        {

            //  Stamp can be culled.
            GPU_DEBUG_BOX(
                printf("%s => Culling whole stamp.\n", getName());
            )

            //  Delete stamp.
            for(i = 0; i < STAMP_FRAGMENTS; i++)
            {
                //  Get fragment.
                fr = stamp[i]->getFragment();

                //  Get fragment attribute.
                attrib = stamp[i]->getAttributes();

                //  Delete fragment.
                delete fr;

                //  Delete attributes.
                delete[] attrib;

                //  Delete fragment input.
                delete stamp[i];

                //  Update statistics.
                culled->inc();
                globalCulled->inc();
            }

            //  Delete stamp.
            delete[] stamp;

	    stamp = NULL;

            //  Return stamp queue object to the free queue.
            freeQueue.add(currentStamp);
        }
    }
    else
    {
        //  WARNING
        //  THE LAST STAMP MUST ALWAYS BE THE LAST STAMP IN A BATCH.
        //  IT IS STORED IN THE LAST QUEUE ENTRY.
        //

	switch (stamp[0]->getType()) {
	    case FRAG_NORMAL:
                //  Last fragment/stamp received.
                lastFragment = TRUE;

                //  Set last batch stamp data.
                lastBatchStamp.lastStamp = true;
                lastBatchStamp.stamp = stamp;

                //  Return the stamp queue object to the free queue.
                freeQueue.add(currentStamp);

                GPU_DEBUG_BOX(
                    printf("%s (%p) => Received last stamp\n", getName(), this);
                )
		break;

	    case FRAG_COMP_IN:
		inQueue.add(currentStamp);
		break;

	    case FRAG_COMP_OUT:
		compFetchingPoses.push(syncQueue.add(currentStamp));
		break;

	    default:
		panic(getName(), "processStamp", "invalid null fragment type");
	}
    }
}

//  Receive stamps from the producer stage.
void GenericROP::receiveStamps(u64bit cycle)
{
    FragmentInput *frInput;
    bool receivedFragment;
    int i, j;

    GPU_DEBUG_BOX(
        cout << getName() << " => Waiting for " << stampsCycle << " stamps" << endl;
    )

    //  Receive N stamps from the producer stage
    for(i = 0; i < stampsCycle; i++)
    {
        //  Allocate the current stamp.
        stamp = new FragmentInput*[STAMP_FRAGMENTS];

        //  Reset received fragment flag
        receivedFragment = true;

        //  Receive all the fragments from a stamp.
        for(j = 0; (j < STAMP_FRAGMENTS) && receivedFragment; j++)
        {
            //*  Get fragment from producer stage input signal.
            receivedFragment = inFragmentSignal->read(cycle, (DynamicObject *&) frInput);
       
            //  Check if a fragment has been received.
            if (receivedFragment)
            {
                GPU_DEBUG_BOX(
                    cout << getName() << " => Received fragment " << j << " for stamp " << i << endl;
                )

                // Store fragment in the current stamp.
                stamp[j] = frInput;

                //  Count triangles.
                if (frInput->getTriangleID() != currentTriangle && frInput->getType() == FRAG_NORMAL)
                {
                    //  Change current triangle.
                    currentTriangle = frInput->getTriangleID();

                    //  Update triangle counter.
                    triangleCounter++;
                }

                //  Update fragment counter.
		if (frInput->getType() == FRAG_NORMAL) {
                    fragmentCounter++;
		    totFrags->inc();
		    globalTotFrags->inc();
		}

                //  Update statistics.
                inputs->inc();
                globalInputs->inc();
            }
        }

        //  Check if a whole stamp has been received.
        GPU_ASSERT(
            if (!receivedFragment && (j > 1))
                panic(getName(), "receiveStamps", "Missing fragments in a stamp from input queue.");
        )

        //  Check if a stamp has been received.
        if (receivedFragment)
        {
            //  Process the received stamp.
            processStamp(cycle);
        }
        else
        {
            delete[] stamp;
        }
    }

    if (syncInFragmentSignal) {
        for (i = 0; i < stampsCycle; i++) {
            stamp = new FragmentInput*[STAMP_FRAGMENTS];
            receivedFragment = true;
            
            for(j = 0; (j < STAMP_FRAGMENTS) && receivedFragment; j++) {
                receivedFragment = syncInFragmentSignal->read(cycle, (DynamicObject *&) frInput);
                if (receivedFragment) {
		    GPU_ASSERT(
            	        if (frInput->getType() != FRAG_COMP_OUT)
            	            panic(getName(), "receiveStamps", "invalid fragment type");
            	    )
            	    
                    stamp[j] = frInput;
                }
            }
            
            GPU_ASSERT(
                if (!receivedFragment && (j > 1))
                    panic(getName(), "receiveStamps", "Missing fragments in a stamp from sync input queue.");
            )

            if (receivedFragment) {
                processStamp(cycle);
            } else {
                delete [] stamp;
            }
        }
    }
}

//  Fetch data for the current input stamp.
void GenericROP::fetchStamp(u64bit cycle)
{
    ROPQueue *currentStamp;

    //  Check if there are stamps in the input stamp queue waiting to be fetched.
    if (!inQueue.empty())
    {
        //  Get the current stamp from the head of the input stamp queue.
        currentStamp = inQueue.head();

        //  Check if bypass flag for the ROP stage is enabled or disabled.
        if (!bypassROP[currentStamp->nextBuffer])
        {
            //  Check if read data flag is enabled.
            if (readDataROP[currentStamp->nextBuffer])
            {
                //  The stamp requires to read data from the ROP buffer before processing.

                //  Check if the fetch stamp queue has free entries.
                if (!fetchQueue.full())
                {
                    bool fetchResult;
                    
                    //  Check if multisampling is enabled.
                    if (!multisampling)
                    {
                        //  Try to fetch data for the next stamp in the queue.
                        fetchResult = ropCache->fetch(currentStamp->address[currentStamp->nextBuffer],
                                                      currentStamp->way[currentStamp->nextBuffer],
                                                      currentStamp->line[currentStamp->nextBuffer],
                                                      currentStamp->stamp[0]);
                    }
                    else
                    {
                        //  Try to fetch data for the next stamp in the queue.
                        fetchResult = ropCache->fetch(currentStamp->address[currentStamp->nextBuffer],
                                                      currentStamp->way[currentStamp->nextBuffer],
                                                      currentStamp->line[currentStamp->nextBuffer],
                                                      currentStamp->stamp[0], msaaSamples);
                    }
                    
                    //  Check result of the fetch operation.
                    if (fetchResult)
                    {
                        GPU_DEBUG_BOX(
                            printf("%s => Fetched stamp at %x to cache line (%d, %d) for buffer %d\n", getName(),
                                currentStamp->address[currentStamp->nextBuffer],
                                currentStamp->way[currentStamp->nextBuffer],
                                currentStamp->line[currentStamp->nextBuffer],
                                currentStamp->nextBuffer);
                        )
                        
                        //if (!strcmp(ropName, "ColorWrite") && currentStamp->stamp[0]->getDebug()) {
                        if (!strcmp(ropName, "ZStencilTest") && currentStamp->stamp[0]->getDebug()) {
		            char filename[32];
		            //sprintf(filename, "debugCWFetchStamp%d.txt", stampId);
		            sprintf(filename, "debugZSTFetchStamp%d.txt", stampId);
	                    FILE *debugfile = fopen(filename, "a+");
			    for (u32bit stampIndex = 0; stampIndex < STAMP_FRAGMENTS; stampIndex++) {
			        fprintf(debugfile, "GPU[%d] %s => cycle %lld batch %d fetchStamp (%d, %d) triangle ID %d culled %s sample %d addr 0x%x\n",
					gpuId, getName(), cycle, batchCounter, currentStamp->stamp[stampIndex]->getFragment()->getX(),
					currentStamp->stamp[stampIndex]->getFragment()->getY(),
					currentStamp->stamp[stampIndex]->getTriangleID(),
					currentStamp->stamp[stampIndex]->isCulled() ? "T" : "F",
					multisampling ? msaaSamples : 1,
					currentStamp->address[currentStamp->nextBuffer]);
			    }
	                    fflush(debugfile);
	                    fclose(debugfile);
			}

                        //  Update the pointer to the next output buffer.
                        for(currentStamp->nextBuffer++;
                            (!activeBuffer[currentStamp->nextBuffer]) && (currentStamp->nextBuffer < MAX_RENDER_TARGETS);
                            currentStamp->nextBuffer++);
                        
                        //  Check if data fetched for all the active buffers.
                        if (currentStamp->nextBuffer == MAX_RENDER_TARGETS)
                        {
                            //  Fetch was succesful.  Add stamp to the fetched stamp queue.
                            fetchQueue.add(currentStamp);

                            //  Remove stamp from the input stamp queue.
                            inQueue.remove();

                            //  Reset the pointer to the next output buffer.
                            currentStamp->nextBuffer = 0;
                        }
                                               
                        //  Update statistics.  */
                        fetchOK->inc();
                        globalFetchOK->inc();
                    }
                    else
                    {
                        //  Update statistics.
                        fetchFail->inc();
                        globalFetchFail->inc();
                    }
                }
                else
                {
                    //  Update statistics.
                    fetchFull->inc();
                    globalFetchFull->inc();
                }
            }
            else
            {
                //  Read data flag is disabled so we have to allocate a line in the write buffer

                //  Check if the read stamp queue is full.
                if (!readQueue.full())
                {
                    bool allocateResult;
                    
                    //  Check if multisampling is enabled.
                    if (!multisampling)
                    {
                        //  Try to allocate a cache (buffer mode) line.
                        allocateResult = ropCache->allocate(currentStamp->address[currentStamp->nextBuffer],
                                                            currentStamp->way[currentStamp->nextBuffer],
                                                            currentStamp->line[currentStamp->nextBuffer],
                                                            currentStamp->stamp[0]);
                    }                                                            
                    else
                    {
                        //  Try to allocate a cache (buffer mode) line.
                        allocateResult = ropCache->allocate(currentStamp->address[currentStamp->nextBuffer],
                                                            currentStamp->way[currentStamp->nextBuffer],
                                                            currentStamp->line[currentStamp->nextBuffer],
                                                            currentStamp->stamp[0], msaaSamples);
                    }

                    //  Check result of the allocate operation.
                    if (allocateResult)
                    {
                        GPU_DEBUG_BOX(
                            printf("%s => Allocating cache line (%d, %d) for stamp at %x buffer %d.\n",
                                getName(), currentStamp->way[currentStamp->nextBuffer], currentStamp->line[currentStamp->nextBuffer],
                                currentStamp->address[currentStamp->nextBuffer], currentStamp->nextBuffer);
                        )

                        //if (!strcmp(ropName, "ColorWrite") && currentStamp->stamp[0]->getDebug()) {
                        if (!strcmp(ropName, "ZStencilTest") && currentStamp->stamp[0]->getDebug()) {
		            char filename[32];
		            sprintf(filename, "debugZSTFetchStamp%d.txt", stampId);
	                    FILE *debugfile = fopen(filename, "a+");
			    for (u32bit stampIndex = 0; stampIndex < STAMP_FRAGMENTS; stampIndex++) {
			        fprintf(debugfile, "GPU[%d] %s => cycle %lld batch %d allocateStamp (%d, %d) triangle ID %d culled %s sample %d addr 0x%x\n",
					gpuId, getName(), cycle, batchCounter, currentStamp->stamp[stampIndex]->getFragment()->getX(),
					currentStamp->stamp[stampIndex]->getFragment()->getY(),
					currentStamp->stamp[stampIndex]->getTriangleID(),
					currentStamp->stamp[stampIndex]->isCulled() ? "T" : "F",
					multisampling ? msaaSamples : 1,
					currentStamp->address[currentStamp->nextBuffer]);
			    }
	                    fflush(debugfile);
	                    fclose(debugfile);
			}

                        //  Update the pointer to the next output buffer.
                        for(currentStamp->nextBuffer++;
                            (!activeBuffer[currentStamp->nextBuffer]) && (currentStamp->nextBuffer < MAX_RENDER_TARGETS);
                            currentStamp->nextBuffer++);

                        //  Check if data fetched for all the active buffers.
                        if (currentStamp->nextBuffer == MAX_RENDER_TARGETS)
                        {
                            // Add current stamp to the read stamp queue.
                            readQueue.add(currentStamp);

                            //  Remove current stamp from the input stamp queue.
                            inQueue.remove();
                            
                            //  Reset the pointer to the next output buffer.
                            currentStamp->nextBuffer = 0;
                        }

                        //  Update statistics.
                        allocateOK->inc();
                        globalAllocateOK->inc();
                    }
                    else
                    {
                        //  Update statistics.
                        allocateFail->inc();
                        globalAllocateFail->inc();
                    }
                }
                else
                {
                    //  Update statistics.
                    readFull->inc();
                    globalReadFull->inc();
                }
            }
        }
        else
        {
            //  Bypass flag is enabled so the stamp is bypassed to the final stage
            //  of the pipeline.

            //  Check if the written stamp queue is full.
            if (!writeQueue.full())
            {
                GPU_DEBUG_BOX(
                    printf("%s => Bypassing stamp to the next stage.\n", getName());
                )

                //  Add stamp to the written stamp queue.
                writeQueue.add(currentStamp);

                //  Remove stamp from the input stamp queue.
                inQueue.remove();
            }
            else
            {
                //  Update statistics.
                writeFull->inc();
                globalWriteFull->inc();
            }
        }
    }
    else
    {
        //  Update statistics.
        inputEmpty->inc();
        globalInputEmpty->inc();
    }
}

//  Try to read data for the stamp in the head of the fetched stamp queue.
void GenericROP::readStamp(u64bit cycle)
{
    bool waitWrite;
    ROPQueue *currentStamp;

    //  Check if there are stamps waiting to be read.
    if (!fetchQueue.empty())
    {
        //  Get current fetched stamp.
        currentStamp = fetchQueue.head();

        // Reset wait flag.
        waitWrite = false;

        //  Check if a stamp to the same address is present in the ROP pipeline ahead of the
        //  the current stamp.

        //  Search the RAW dependece CAM for the current stamp address.
        for(int i = firstCAM, n = stampsCAM; n > 0; n--, i = GPU_MOD(i + 1, sizeCAM))
        {
            //  Check stamp address against CAM stamp address
            if ((currentStamp->address[currentStamp->nextBuffer] == rawCAM[i]->address[currentStamp->nextBuffer]) &&
                 (currentStamp != rawCAM[i]))
            {
                GPU_DEBUG_BOX(
                    printf("%s => Reading a stamp at %x before writing it.\n", getName(),
                        currentStamp->address[currentStamp->nextBuffer]);
                )

                //  Stall the pipeline until the stamp in the CAM writes the data to.
                waitWrite = TRUE;
            }
        }

        //  Check if the pipeline must stall because a RAW dependence.
        if (!waitWrite)
        {
            //  Check if there are free entries in the read stamp queue.
            if (!readQueue.full())
            {
                //  Check if multisampling is enabled.
                if (!multisampling)
                {
                    //  Try to read data for the current fetched stamp.
                    if (ropCache->read(currentStamp->address[currentStamp->nextBuffer],
                                       currentStamp->way[currentStamp->nextBuffer],
                                       currentStamp->line[currentStamp->nextBuffer],
                                       STAMP_FRAGMENTS * bytesPixel[currentStamp->nextBuffer],
                                       //&currentStamp->data[STAMP_FRAGMENTS * bytesPixel[currentStamp->nextBuffer] * currentStamp->nextBuffer]))
                                       &currentStamp->data[currentStamp->offset[currentStamp->nextBuffer]]))
                    {
                        GPU_DEBUG_BOX(
                            printf("%s => Reading stamp at %x for buffer %d\n", getName(),
                                currentStamp->address[currentStamp->nextBuffer], currentStamp->nextBuffer);
                        )

                        //if (!strcmp(ropName, "ColorWrite") && currentStamp->stamp[0]->getDebug()) {
                        if (!strcmp(ropName, "ZStencilTest") && currentStamp->stamp[0]->getDebug()) {
                        //if (currentStamp->stamp[0]->getFragment()->getX() == 172 && currentStamp->stamp[0]->getFragment()->getY() == 146) {
		            char filename[32];
		            sprintf(filename, "debugZSTReadStamp%d.txt", stampId);
	                    FILE *debugfile = fopen(filename, "a+");
			    for (u32bit stampIndex = 0; stampIndex < STAMP_FRAGMENTS; stampIndex++) {
			        fprintf(debugfile, "GPU[%d] %s => cycle %lld batch %d readStamp (%d, %d) triangle ID %d culled %s addr 0x%x size %d\n",
					gpuId, getName(), cycle, batchCounter, currentStamp->stamp[stampIndex]->getFragment()->getX(),
					currentStamp->stamp[stampIndex]->getFragment()->getY(),
					currentStamp->stamp[stampIndex]->getTriangleID(),
					currentStamp->stamp[stampIndex]->isCulled() ? "T" : "F",
					currentStamp->address[currentStamp->nextBuffer],
					STAMP_FRAGMENTS * bytesPixel[currentStamp->nextBuffer]);
			    }
			    for (u32bit wordIndex = 0; wordIndex < STAMP_FRAGMENTS * bytesPixel[currentStamp->nextBuffer] / 4; wordIndex++) {
			        fprintf(debugfile, "data[%d] = 0x%08x ", wordIndex,
					*((u32bit*)(currentStamp->data) +
					 //STAMP_FRAGMENTS * bytesPixel[currentStamp->nextBuffer] * currentStamp->nextBuffer / 4 +
					 currentStamp->offset[currentStamp->nextBuffer] / 4 +
					 wordIndex));
			    }
			    fprintf(debugfile, "\n");
	                    fflush(debugfile);
	                    fclose(debugfile);
			}

                        //  Check if the stamp must be added to the RAW CAM.
                        if (currentStamp->nextBuffer == 0)
                        {
                            //  Check that the RAW CAM vector is not full.
                            GPU_ASSERT(
                                if (stampsCAM == sizeCAM)
                                    panic(getName(), "readStamp", "RAW dependence CAM is full.");
                            )

                            //  Add stamp to the RAW CAM.
                            rawCAM[freeCAM] = currentStamp;
                            stampsCAM++;
                            freeCAM = GPU_MOD(freeCAM + 1, sizeCAM);
                        }

                        //  Update the pointer to the next output buffer.
                        for(currentStamp->nextBuffer++;
                            (!activeBuffer[currentStamp->nextBuffer]) && (currentStamp->nextBuffer < MAX_RENDER_TARGETS);
                            currentStamp->nextBuffer++);

                        //  Check if data fetched for all the active buffers.
                        if (currentStamp->nextBuffer == MAX_RENDER_TARGETS)
                        {
                            //  Add stamp to the read stamp queue.
                            readQueue.add(currentStamp);

                            //  Remove stamp from the fetch queue.
                            fetchQueue.remove();
                            //  Reset the pointer to the next output buffer.
                            currentStamp->nextBuffer = 0;
                        }
                        
                        //  Update statistics.
                        readOK->inc();
                        globalReadOK->inc();
                    }
                    else
                    {
                        /*  Update statistics.  */
                        readFail->inc();
                        globalReadFail->inc();
                    }
                }
                else
                {
                    //  Compute the data offset for the current read operation.
                    u32bit dataOffset = currentStamp->nextSample * bytesPixel[currentStamp->nextBuffer] * STAMP_FRAGMENTS +
                                        currentStamp->nextBuffer * msaaSamples * bytesPixel[currentStamp->nextBuffer] * STAMP_FRAGMENTS;
                    
                    //  Compute the address for the current read operation.
                    u32bit readAddress = currentStamp->address[currentStamp->nextBuffer] +
                                         currentStamp->nextSample * bytesPixel[currentStamp->nextBuffer] * STAMP_FRAGMENTS;
                    
                    //  Try to read data for the current fetched stamp.
                    if (ropCache->read(readAddress,
                                       currentStamp->way[currentStamp->nextBuffer],
                                       currentStamp->line[currentStamp->nextBuffer],
                                       STAMP_FRAGMENTS * bytesPixel[currentStamp->nextBuffer],
                                       &currentStamp->data[dataOffset]))
                    {
                        GPU_DEBUG_BOX(
                            printf("%s => Reading sample %d for stamp at %x for buffer %d\n", getName(), currentStamp->nextSample,
                                currentStamp->address[currentStamp->nextBuffer], currentStamp->nextBuffer);
                        )

                        //if (!strcmp(ropName, "ColorWrite") && currentStamp->stamp[0]->getDebug()) {
                        if (!strcmp(ropName, "ZStencilTest") && currentStamp->stamp[0]->getDebug()) {
                        //if (currentStamp->stamp[0]->getFragment()->getX() == 172 && currentStamp->stamp[0]->getFragment()->getY() == 146) {
		            char filename[32];
		            sprintf(filename, "debugZSTReadStamp%d.txt", stampId);
	                    FILE *debugfile = fopen(filename, "a+");
			    for (u32bit stampIndex = 0; stampIndex < STAMP_FRAGMENTS; stampIndex++) {
			        fprintf(debugfile, "GPU[%d] %s => cycle %lld batch %d readStamp (%d, %d) triangle ID %d culled %s sample %d addr 0x%x size %d\n",
					gpuId, getName(), cycle, batchCounter, currentStamp->stamp[stampIndex]->getFragment()->getX(),
					currentStamp->stamp[stampIndex]->getFragment()->getY(),
					currentStamp->stamp[stampIndex]->getTriangleID(),
					currentStamp->stamp[stampIndex]->isCulled() ? "T" : "F",
					currentStamp->nextSample,
					readAddress,
					STAMP_FRAGMENTS * bytesPixel[currentStamp->nextBuffer]);
			    }
			    for (u32bit wordIndex = 0; wordIndex < STAMP_FRAGMENTS * bytesPixel[currentStamp->nextBuffer] / 4; wordIndex++) {
			        fprintf(debugfile, "data[%d] = 0x%08x ", wordIndex,
					*((u32bit*)(currentStamp->data) + dataOffset /4 + wordIndex));
			    }
			    fprintf(debugfile, "\n");
	                    fflush(debugfile);
	                    fclose(debugfile);
			}

                        //  Check if the stamp must be added to the RAW CAM.
                        if (currentStamp->nextSample == 0)
                        {
                            //  Check that the RAW CAM vector is not full.
                            GPU_ASSERT(
                                if (stampsCAM == sizeCAM)
                                    panic(getName(), "readStamp", "RAW dependence CAM is full.");
                            )

                            //  Add stamp to the RAW CAM.
                            rawCAM[freeCAM] = currentStamp;
                            stampsCAM++;
                            freeCAM = GPU_MOD(freeCAM + 1, sizeCAM);
                        }

                        //  Update samples read for the stamp.
                        currentStamp->nextSample++;
                        
                        //  Check if all the sample data was read.
                        if (currentStamp->nextSample == msaaSamples)
                        {
                            //  Reset multisampling counter.
                            currentStamp->nextSample = 0;
                            
                            //  Update the pointer to the next output buffer.
                            for(currentStamp->nextBuffer++;
                                (!activeBuffer[currentStamp->nextBuffer]) && (currentStamp->nextBuffer < MAX_RENDER_TARGETS);
                                currentStamp->nextBuffer++);

                            //  Check if data fetched for all the active buffers.
                            if (currentStamp->nextBuffer == MAX_RENDER_TARGETS)
                            {
                                //  Add stamp to the read stamp queue.
                                readQueue.add(currentStamp);

                                //  Remove stamp from the fetch queue.
                                fetchQueue.remove();
                                
                                //  Reset the pointer to the next output buffer.
                                currentStamp->nextBuffer = 0;
                            }
                        }
                        
                        
                        /*  Update statistics.  */
                        readOK->inc();
                        globalReadOK->inc();
                    }
                    else
                    {
                        /*  Update statistics.  */
                        readFail->inc();
                        globalReadFail->inc();
                    }
                }
            }
            else
            {
                //  Update statistics.
                readFull->inc();
                globalReadFull->inc();
            }
        }
        else
        {
            //  Update statistics.
            rawDep->inc();
            globalRawDep->inc();
        }
    }
    else
    {
        //  Update statistics.
        fetchEmpty->inc();
        globalFetchEmpty->inc();
    }
}

//  Start ROP operation for the stamp in the head of the read queue.
void GenericROP::startOperation(u64bit cycle)
{
    ROPQueue *currentStamp;
    ROPOperation *ropOperation;

    //  Update cycles until the next stamp can be operated
    if (ropCycles > 0)
    {
        ropCycles--;
    }

    //  Check if a new stamp can start to operate
    if (ropCycles == 0)
    {
        //  Check if there stamps in the read stamp queue.
        if (!readQueue.empty())
        {
            //  Check if the operation stamp queue has free entries.
            if (opQueue.items() <= (opQueueSize - ropLatency))
            {
                //  Get next stamp from the read stamp queue.
                currentStamp = readQueue.head();

                //  Send stamp through the ROP operation latency signal.

                //  Create ROP operation object.
                ropOperation = new ROPOperation(currentStamp);

                //  Copy parent command cookies.
                ropOperation->copyParentCookies(*currentStamp->stamp[0]);

                //  Remove the fragment level cookie.
                ropOperation->removeCookie();

                //  Start test operation.  */
                operationStart->write(cycle, ropOperation);

                //  Check if multisampling is enabled.
                if (!multisampling)
                {
                    //  Set start test cycle counter.
                    ropCycles = ropRate * numActiveBuffers;
                }
                else
                {
                    //  Set start test cycle counter.
                    ropCycles = ropRate * msaaSamples * numActiveBuffers;
                }
                
                //  Remove current stamp from the head of the read stamp queue.
                readQueue.remove();
            }
            else
            {
                //  Update statistics.
                opFull->inc();
                globalOpFull->inc();
            }

        }
        else
        {
            //  Update statistics.
            readEmpty->inc();
            globalReadEmpty->inc();
        }
    }
    else
    {
        //  Update statistics.
        ropOpBusy->inc();
        globalRopOpBusy->inc();
    }
}

//  End ROP operation for a stamp
void GenericROP::endOperation(u64bit cycle)
{
    ROPOperation *ropOperation;
    ROPQueue *currentStamp;

    //  Check end of test operation.
    if (operationEnd->read(cycle, (DynamicObject *&) ropOperation))
    {
        //  Get processed stamp.
        currentStamp = ropOperation->getROPStamp();
    
        //  Delete ROP operation object.
        delete ropOperation;
    
        GPU_DEBUG_BOX(
            printf("%s => Finished ROP operation on stamp.\n", getName());
        )
    
        //  Call the operate stamp function for the derived classes.
        //if (currentStamp->stamp[0]->getType() == FRAG_NORMAL)
        if (currentStamp->stamp[0]->getFragment() != NULL)
            operateStamp(cycle, currentStamp);
    
        //if (!strcmp(ropName, "ColorWrite") && currentStamp->stamp[0]->getDebug()) {
        if (!strcmp(ropName, "ZStencilTest") && currentStamp->stamp[0]->getDebug()) {
            char filename[32];
            sprintf(filename, "debugZSTEndOperation%d.txt", stampId);
            FILE *debugfile = fopen(filename, "a+");
            for (u32bit stampIndex = 0; stampIndex < STAMP_FRAGMENTS; stampIndex++) {
                fprintf(debugfile, "GPU[%d] %s => cycle %lld batch %d endOperation (%d, %d) triangle ID %d culled %s\n",
        		gpuId, getName(), cycle, batchCounter, currentStamp->stamp[stampIndex]->getFragment()->getX(),
        		currentStamp->stamp[stampIndex]->getFragment()->getY(),
        		currentStamp->stamp[stampIndex]->getTriangleID(),
        		currentStamp->stamp[stampIndex]->isCulled() ? "T" : "F");
                QuadFloat* attributes = currentStamp->stamp[stampIndex]->getAttributes();
        	    if (attributes) {
                    for (u32bit j = 0; j < MAX_FRAGMENT_ATTRIBUTES; j++) {
                        fprintf(debugfile, "attrib[%d] = { %f, %f, %f, %f }\n", j,
                                attributes[j][0], attributes[j][1],
                                attributes[j][2], attributes[j][3]);
                    }
        	    }
            }
            //for (u32bit wordIndex = 0;
            //    	wordIndex < MAX_RENDER_TARGETS * STAMP_FRAGMENTS * MAX_MSAA_SAMPLES * MAX_BYTES_PER_COLOR / 4;
            //    	wordIndex++) {
            //    fprintf(debugfile, "data[%d] = 0x%08x ", wordIndex, *((u32bit*)(currentStamp->data) + wordIndex));
            //}
            //fprintf(debugfile, "\n");
            fflush(debugfile);
            fclose(debugfile);
        }
    
        GPU_ASSERT(
            if (opQueue.full())
                panic(getName(), "endOperation", "Operated stamp queue full.");
        )
    
        //  Add stamp to the operated stamp queue.
        opQueue.add(currentStamp);
    
        //  Update statistics.
        operated->inc();
        globalOperated->inc();
    }
}

//  Write stamp data into the buffer.
void GenericROP::writeStamp(u64bit cycle)
{
    ROPQueue *currentStamp;

    //  Check if the operated stamp queue is empty.
    if (!opQueue.empty())
    {
        //  Check if the written stamp queue has free entries.
        if (!writeQueue.full())
        {
            //  Get current stamp from the head of the operated stamp queue.
            currentStamp = opQueue.head();

            //  Check if multisampling is enabled.
            if (!multisampling)
            {
		for (u32bit j = 0; j < STAMP_FRAGMENTS; j++) {
		    if (currentStamp->stamp[j]->getDummyGenAfterZTest())
		        memset(currentStamp->mask + currentStamp->offset[currentStamp->nextBuffer] + j * bytesPixel[currentStamp->nextBuffer], 0, bytesPixel[currentStamp->nextBuffer]);
		}

                //  Try to write the stamp data.
                if (ropCache->write(currentStamp->address[currentStamp->nextBuffer],
                                    currentStamp->way[currentStamp->nextBuffer],
                                    currentStamp->line[currentStamp->nextBuffer],
                                    STAMP_FRAGMENTS * bytesPixel[currentStamp->nextBuffer],
                                    //&currentStamp->data[currentStamp->nextBuffer * STAMP_FRAGMENTS * bytesPixel[currentStamp->nextBuffer]],
                                    //&currentStamp->mask[currentStamp->nextBuffer * STAMP_FRAGMENTS * bytesPixel[currentStamp->nextBuffer]]))
                                    &currentStamp->data[currentStamp->offset[currentStamp->nextBuffer]],
                                    &currentStamp->mask[currentStamp->offset[currentStamp->nextBuffer]]))
                {
                    GPU_DEBUG_BOX(
                        printf("%s => Writing stamp at %x for buffer %d\n", getName(),
                            currentStamp->address[currentStamp->nextBuffer], currentStamp->nextBuffer);
                        printf("%s => Written data :", getName());
                        for(u32bit b = 0; b < STAMP_FRAGMENTS * bytesPixel[currentStamp->nextBuffer]; b++)
                            printf(" %02x", currentStamp->data[currentStamp->offset[currentStamp->nextBuffer] + b]);
                            //printf(" %02x", currentStamp->data[currentStamp->nextBuffer * STAMP_FRAGMENTS * bytesPixel[currentStamp->nextBuffer] + b]);
                        printf("\n");
                        printf("%s => Write mask :", getName());
                        for(u32bit b = 0; b < STAMP_FRAGMENTS * bytesPixel[currentStamp->nextBuffer]; b++)
                            printf(" %d", currentStamp->mask[currentStamp->nextBuffer * STAMP_FRAGMENTS * bytesPixel[currentStamp->nextBuffer] + b]);
                        printf("\n");                            
                    )

		    for (u32bit j = 0; currentStamp->nextBuffer == 0 && j < STAMP_FRAGMENTS; j++) {
		        if (currentStamp->stamp[j]->getDummyGenAfterZTest()) {
			    numDummyFrags->inc();
			    globalNumDummyFrags->inc();
			}
		    }

                    //if (!strcmp(ropName, "ColorWrite") &&
                    //if (currentStamp->stamp[0]->getFragment()->getX() == 172 && currentStamp->stamp[0]->getFragment()->getY() == 146) {
                    if (!strcmp(ropName, "ZStencilTest") &&
		        (currentStamp->stamp[0]->getDebug())) {// ||
		         //(ropCache->line2address(currentStamp->way[currentStamp->nextBuffer], currentStamp->line[currentStamp->nextBuffer]) >= 0xe0e6800 &&
		          //ropCache->line2address(currentStamp->way[currentStamp->nextBuffer], currentStamp->line[currentStamp->nextBuffer]) <= 0xe0e6a00))) {
	                char filename[32];
	                //sprintf(filename, "debugCWWriteStamp%d.txt", stampId);
	                sprintf(filename, "debugZSTWriteStamp%d.txt", stampId);
	                FILE *debugfile = fopen(filename, "a+");
	                for (u32bit stampIndex = 0; stampIndex < STAMP_FRAGMENTS; stampIndex++) {
	                    fprintf(debugfile, "GPU[%d] %s => cycle %lld batch %d writestamp (%d, %d) triangle ID %d culled %s readData %s rt %d addr %x tag %x size %d\n",
	            		gpuId, getName(), cycle, batchCounter,
		        	currentStamp->stamp[stampIndex]->getFragment()->getX(),
	            		currentStamp->stamp[stampIndex]->getFragment()->getY(),
	            		currentStamp->stamp[stampIndex]->getTriangleID(),
	            		currentStamp->stamp[stampIndex]->isCulled() ? "T" : "F",
		        	readDataROP[currentStamp->nextBuffer] ? "T" : "F",
		        	currentStamp->nextBuffer,
		        	currentStamp->address[currentStamp->nextBuffer],
		        	ropCache->line2address(currentStamp->way[currentStamp->nextBuffer], currentStamp->line[currentStamp->nextBuffer]),
		        	STAMP_FRAGMENTS * bytesPixel[currentStamp->nextBuffer]);
	                }
	                for (u32bit wordIndex = 0;
	            	     wordIndex < STAMP_FRAGMENTS * bytesPixel[currentStamp->nextBuffer]/ 4;
	            	     wordIndex++) {
	                    fprintf(debugfile, "data[%d] = 0x%08x mask[%d] = 0x%08x ",
		                    wordIndex,
		        	    *((u32bit*)(currentStamp->data) +
		        	     currentStamp->offset[currentStamp->nextBuffer] / 4 +
		        	     //currentStamp->nextBuffer * STAMP_FRAGMENTS * bytesPixel[currentStamp->nextBuffer] / 4 +
		        	     wordIndex),
		        	    wordIndex,
		        	    *((u32bit*)(currentStamp->mask) +
		        	     currentStamp->offset[currentStamp->nextBuffer] / 4 +
		        	     //currentStamp->nextBuffer * STAMP_FRAGMENTS * bytesPixel[currentStamp->nextBuffer] / 4 +
		        	     wordIndex));
	                }
	                fprintf(debugfile, "\n");
	                fflush(debugfile);
	                fclose(debugfile);
                    }

                    //  Update the pointer to the next output buffer.
                    for(currentStamp->nextBuffer++;
                        (!activeBuffer[currentStamp->nextBuffer]) && (currentStamp->nextBuffer < MAX_RENDER_TARGETS);
                        currentStamp->nextBuffer++);

                    //  Check if data fetched for all the active buffers.
                    if (currentStamp->nextBuffer == MAX_RENDER_TARGETS)
                    {
                        //  Add stamp to the written stamp queue.
                        writeQueue.add(currentStamp);

                        //  Remove stamp from the operated stamp queue.
                        opQueue.remove();

                        //  Check if ROP data read is enabled and RAW CAM is in use.
                        if (readDataROP[0])
                        {
                            GPU_ASSERT(
                                if (stampsCAM == 0)
                                    panic(getName(), "writeStamp", "RAW CAM vector empty.");
                                if (rawCAM[firstCAM] == NULL)
                                    panic(getName(), "writeStamp", "Unitialized RAW CAM entry accessed.");
                            )

                            //  Remove stamp from the RAW CAM vector.
                            rawCAM[firstCAM] = NULL;
                            firstCAM = GPU_MOD(firstCAM + 1, sizeCAM);
                            stampsCAM--;
                        }
                        
                        //  Reset the pointer to the next output buffer.
                        currentStamp->nextBuffer = 0;
                    }
                    
                    //  Update statistics.
                    writeOK->inc();
                    globalWriteOK->inc();
                }
                else
                {
                    //  Update statistics.
                    writeFail->inc();
                    globalWriteFail->inc();
                }
            }
            else
            {
                //  Compute the address for the write operation.
                u32bit writeAddress = currentStamp->address[currentStamp->nextBuffer] +
                                      currentStamp->nextSample * STAMP_FRAGMENTS * bytesPixel[currentStamp->nextBuffer];
                
                //  Compute the data offset for the write operation;
                u32bit dataOffset = currentStamp->nextSample * STAMP_FRAGMENTS * bytesPixel[currentStamp->nextBuffer] +
                                    msaaSamples * STAMP_FRAGMENTS * bytesPixel[currentStamp->nextBuffer] * currentStamp->nextBuffer;
                
		for (u32bit j = 0; j < STAMP_FRAGMENTS; j++) {
		    if (currentStamp->stamp[j]->getDummyGenAfterZTest())
		        memset(currentStamp->mask + dataOffset + j * bytesPixel[currentStamp->nextBuffer], 0, bytesPixel[currentStamp->nextBuffer]);
		}


                //  Try to write the stamp data.
                if (ropCache->write(writeAddress,
                                    currentStamp->way[currentStamp->nextBuffer],
                                    currentStamp->line[currentStamp->nextBuffer],
                                    STAMP_FRAGMENTS * bytesPixel[currentStamp->nextBuffer],
                                    &currentStamp->data[dataOffset],
                                    &currentStamp->mask[dataOffset]))
                {
                    GPU_DEBUG_BOX(
                        printf("%s => Writing sample %d for stamp at %x for buffer %d\n", getName(),
                            currentStamp->nextSample, currentStamp->address[currentStamp->nextBuffer], currentStamp->nextBuffer);
                    )

		    for (u32bit j = 0; currentStamp->nextBuffer == 0 && currentStamp->nextSample == 0 && j < STAMP_FRAGMENTS; j++) {
		        if (currentStamp->stamp[j]->getDummyGenAfterZTest()) {
			    numDummyFrags->inc();
			    globalNumDummyFrags->inc();
			}
		    }

                    //if (!strcmp(ropName, "ColorWrite") &&
                    //if (currentStamp->stamp[0]->getFragment()->getX() == 172 && currentStamp->stamp[0]->getFragment()->getY() == 146) {
                    if (!strcmp(ropName, "ZStencilTest") &&
		        (currentStamp->stamp[0]->getDebug())) {// ||
		         //(ropCache->line2address(currentStamp->way[currentStamp->nextBuffer], currentStamp->line[currentStamp->nextBuffer]) >= 0xe0e6800 &&
		          //ropCache->line2address(currentStamp->way[currentStamp->nextBuffer], currentStamp->line[currentStamp->nextBuffer]) <= 0xe0e6a00))) {
	                char filename[32];
	                //sprintf(filename, "debugCWWriteStamp%d.txt", stampId);
	                sprintf(filename, "debugZSTWriteStamp%d.txt", stampId);
	                FILE *debugfile = fopen(filename, "a+");
	                for (u32bit stampIndex = 0; stampIndex < STAMP_FRAGMENTS; stampIndex++) {
	                    fprintf(debugfile, "GPU[%d] %s => cycle %lld batch %d writestamp (%d, %d) triangle ID %d culled %s readData %s rt %d sample %d addr %x tag %x size %d\n",
	            		gpuId, getName(), cycle, batchCounter,
		        	currentStamp->stamp[stampIndex]->getFragment()->getX(),
	            		currentStamp->stamp[stampIndex]->getFragment()->getY(),
	            		currentStamp->stamp[stampIndex]->getTriangleID(),
	            		currentStamp->stamp[stampIndex]->isCulled() ? "T" : "F",
		        	readDataROP[currentStamp->nextBuffer] ? "T" : "F",
		        	currentStamp->nextBuffer,
		        	currentStamp->nextSample,
		        	writeAddress,
		        	ropCache->line2address(currentStamp->way[currentStamp->nextBuffer], currentStamp->line[currentStamp->nextBuffer]),
		        	STAMP_FRAGMENTS * bytesPixel[currentStamp->nextBuffer]);
	                }
	                for (u32bit wordIndex = 0;
	            		wordIndex < STAMP_FRAGMENTS * bytesPixel[currentStamp->nextBuffer]/ 4;
	            		wordIndex++) {
	                    fprintf(debugfile, "data[%d] = 0x%08x mask[%d] = 0x%08x ",
		                    wordIndex, *((u32bit*)(currentStamp->data) + dataOffset / 4 + wordIndex),
		        	    wordIndex, *((u32bit*)(currentStamp->mask) + dataOffset / 4 + wordIndex));
	                }
	                fprintf(debugfile, "\n");
	                fflush(debugfile);
	                fclose(debugfile);
                    }

                    //  Update samples written for the stamp.
                    currentStamp->nextSample++;
                    
                    //  Check if all the sample data for the stamp was written.
                    if (currentStamp->nextSample == msaaSamples)
                    {
                        //  Reset multisampling counter.
                        currentStamp->nextSample = 0;
                    
                        //  Update the pointer to the next output buffer.
                        for(currentStamp->nextBuffer++;
                            (!activeBuffer[currentStamp->nextBuffer]) && (currentStamp->nextBuffer < MAX_RENDER_TARGETS);
                            currentStamp->nextBuffer++);

                        //  Check if data fetched for all the active buffers.
                        if (currentStamp->nextBuffer == MAX_RENDER_TARGETS)
                        {
                            //  Add stamp to the written stamp queue.
                            writeQueue.add(currentStamp);

                            //  Remove stamp from the operated stamp queue.
                            opQueue.remove();

                            //  Check if ROP data read is enabled and RAW CAM is in use.
                            if (readDataROP[0])
                            {
                                GPU_ASSERT(
                                    if (stampsCAM == 0)
                                        panic(getName(), "writeStamp", "RAW CAM vector empty.");
                                    if (rawCAM[firstCAM] == NULL)
                                        panic(getName(), "writeStamp", "Unitialized RAW CAM entry accessed.");
                                )

                                //  Remove stamp from the RAW CAM vector.
                                rawCAM[firstCAM] = NULL;
                                firstCAM = GPU_MOD(firstCAM + 1, sizeCAM);
                                stampsCAM--;
                            }
                            
                            //  Update pointer to the next output buffer.
                            currentStamp->nextBuffer = 0;
                        }
                    }
                    
                    /*  Update statistics.  */
                    writeOK->inc();
                    globalWriteOK->inc();
                }
                else
                {
                    //  Update statistics.
                    writeFail->inc();
                    globalWriteFail->inc();
                }
            }
        }
        else
        {
            //  Update statistics.
            writeFull->inc();
            globalWriteFull->inc();
        }
    }
    else
    {
        //  Update statistics.
        opEmpty->inc();
        globalOpEmpty->inc();
    }
}

//  Terminate the processing the stamp and remove it from the pipeline.
void GenericROP::terminateStamp(u64bit cycle)
{
    ROPQueue *currentStamp;
    bool processed;

    //  Check if the written stamp queue has stamps to process.
    if (!writeQueue.empty())
    {
        //  Check if the consumer stage is ready.
        if (consumerState == ROP_READY)
        {
            //  Get current stamp from the head of the written stamp queue.
            currentStamp = writeQueue.head();

            //  Call the specific function for post write processing from the derived class.
            postWriteProcess(cycle, currentStamp);

            //  Remove the stamp from the written stamp queue.
            writeQueue.remove();

            //  Add stamp to the free queue.
            freeQueue.add(currentStamp);

            if ((numGPUs == 1 && multiGPUExecMode == FRAME_DUP && !strcmp(ropName, "ColorWrite") && state != RAST_SYNC && state != RAST_COMP) ||
                (numGPUs > 1 && multiGPUExecMode == SORT_LAST && !strcmp(ropName, "ColorWrite") && state != RAST_SYNC && state != RAST_COMP &&
	         GPUDriver::getGPUDriver()->getGPUSchedInfo()->isScheduledToThisGPU(frameCounter, batchCounter, gpuId))) {
	        GPUDriver::getGPUDriver()->getGPUSchedInfo()->incNumProcessedFragments(frameCounter, batchCounter, gpuId);
	    }
            if (!strcmp(ropName, "ColorWrite") && state != RAST_SYNC && state != RAST_COMP) {
	        GPUDriver::getGPUDriver()->getGPUSchedInfo()->profileProcessedFragments(batchCounter, gpuId);
	    }
        }
        else
        {
            //  Update statistics.
            consumerBusy->inc();
            globalConsumerBusy->inc();
        }
    }
    else
    {
        //  Update statistics.
        writeEmpty->inc();
        globalWriteEmpty->inc();
    }
}

void GenericROP::readStampForOtherGPUs(u64bit cycle, u32bit displayGPUId)
{
    Fragment *frag = NULL;
    u32bit overTileRowWidth, overTileRows;
    u32bit stampStartX, stampStartY;
    u32bit overTileId, scanTileId, scanTileIdInOverTile, genTileId, genTileIdInScanTile, stampTileId;
    u32bit stampUnit;
    u32bit stampX, stampY;
    u32bit displayTileId;
    bool skip;
    QuadFloat *attrib = NULL;
    u32bit i;

    //for (i = 0; i < stampsCycle && syncInQueue.items() < syncInQueueSize;) {
    for (i = 0; i < stampsCycle && syncQueue.items() < syncQueueSize;) {
	if (generatedStamps == pixelMapper[0].computeNumOfScanTiles() * scanW * scanH * genW * genH) {
            stamp = new FragmentInput*[STAMP_FRAGMENTS];
            for (stampY = 0; stampY < STAMP_HEIGHT; stampY++) {
		for (stampX = 0; stampX < STAMP_WIDTH; stampX++) {
                    stamp[stampY * STAMP_WIDTH + stampX] = new FragmentInput(0, 0, NULL, TileIdentifier(0, 0), stampId);
                    stamp[stampY * STAMP_WIDTH + stampX]->setSrcGPUId(gpuId);
		    
		    switch (state) {
		       case RAST_SYNC:
                           stamp[stampY * STAMP_WIDTH + stampX]->setType(FRAG_SYNC_OUT);
                           stamp[stampY * STAMP_WIDTH + stampX]->setDestGPUId(numGPUs);
			   break;
		       case RAST_COMP:
                           stamp[stampY * STAMP_WIDTH + stampX]->setType(FRAG_COMP_OUT);
                           stamp[stampY * STAMP_WIDTH + stampX]->setDestGPUId(displayGPUId);
			   break;
		       default:
			   panic(getName(), "readStampForOtherGPUs", "invalid state for last sync fragments");
		    }
		}
            }

            processStamp(cycle);

	    generatedStamps = 0;
	    allStampsReadForSync[gpuId][stampId] = true;
	    if (!compSchedEnabled)
		allStampsSentForSync[gpuId][stampId] = true;

	    bool allStampsRead = true;
	    for (u32bit j = 0; j < numStampUnits; j++)
	        allStampsRead = allStampsRead && allStampsReadForSync[gpuId][j];
	    if (allStampsRead)
	        std::cout << getName() << " read all stamps to GPU " << displayGPUId
	    	          << " @cycle " << cycle << std::endl;

	    return;
	}

        stampStartX = overW * scanW * genW * STAMP_WIDTH * overSyncX +
                      scanW * genW * STAMP_WIDTH * scanSyncX +
                      genW * STAMP_WIDTH * genSyncX +
                      STAMP_WIDTH * stampSyncX;
        
        stampStartY = overH * scanH * genH * STAMP_HEIGHT * overSyncY +
                      scanH * genH * STAMP_HEIGHT * scanSyncY +
                      genH * STAMP_HEIGHT * genSyncY +
                      STAMP_HEIGHT * stampSyncY;

        if (stampStartX < hRes && stampStartY < vRes) {
            stampUnit = pixelMapper[0].mapToUnit(stampStartX, stampStartY);
            displayTileId = pixelMapper[0].mapToDisplayTile(stampStartX, stampStartY, GPUPD, numGPUs);
	    skip = (stampUnit != stampId) || (GPU_MOD(displayTileId, numGPUs) != displayGPUId);

	    if (!skip) {
		stamp = new FragmentInput*[STAMP_FRAGMENTS];
                for (stampY = 0; stampY < STAMP_HEIGHT; stampY++) {
	            for (stampX = 0; stampX < STAMP_WIDTH; stampX++) {
	                frag = new Fragment(stampStartX + stampX, stampStartY + stampY);
                        stamp[stampY * STAMP_WIDTH + stampX] = new FragmentInput(0, 0, frag, TileIdentifier(0, 0), stampUnit);
                        stamp[stampY * STAMP_WIDTH + stampX]->setSrcGPUId(gpuId);

		        switch (state) {
		           case RAST_SYNC:
                               stamp[stampY * STAMP_WIDTH + stampX]->setType(FRAG_SYNC_OUT);
                               stamp[stampY * STAMP_WIDTH + stampX]->setDestGPUId(numGPUs);
		               break;
		           case RAST_COMP:
			       attrib = new QuadFloat[MAX_FRAGMENT_ATTRIBUTES];
			       memset(attrib, 0, sizeof(QuadFloat)*MAX_FRAGMENT_ATTRIBUTES);
                               stamp[stampY * STAMP_WIDTH + stampX]->setAttributes(attrib);
                               stamp[stampY * STAMP_WIDTH + stampX]->setType(FRAG_COMP_OUT);
                               stamp[stampY * STAMP_WIDTH + stampX]->setDestGPUId(displayGPUId);
		               break;
		           default:
		               panic(getName(), "readStampForOtherGPUs", "invalid state for sync fragments");
		        }
	            }
                }

                processStamp(cycle);
            
		//if (stampStartX == 172 && stampStartY == 146) {
		//    FILE *debugfile = fopen("comp_generic_debug.txt", "a+");
		//    fprintf(debugfile, "%s cycle %lld frame %d batch %d read (%d, %d) for state %d nextSyncReadingGPU %d notLastSyncSent %d notLastSyncReceive %d generatedStamps %d allStamps %d cullSyncStamp %s\n",
		//    	    getName(), cycle, frameCounter, batchCounter, stampStartX, stampStartY, state, nextSyncReadingGPU[gpuId],
		//    	    notLastSyncSent, notLastSyncReceive, generatedStamps,
		//    	    pixelMapper[0].computeNumOfScanTiles() * scanW * scanH * genW * genH,
		//    	    (stamp == NULL ? "T" : "F"));
    		//    fflush(debugfile);
    		//    fclose(debugfile);
		//}

	    	if (stamp != NULL)
		    i++;
	    }
        }
        
        generatedStamps++;
	
        pixelMapper[0].getOverTileInfo(overTileRowWidth, overTileRows);
        
	overTileId = generatedStamps/(overW * overH * scanW * scanH * genW * genH);
        overSyncY = overTileId/overTileRowWidth;
        overSyncX = GPU_MOD(overTileId, overTileRowWidth);
        
        scanTileId = generatedStamps/(scanW * scanH * genW * genH);
	scanTileIdInOverTile = GPU_MOD(scanTileId, (overW * overH));
        scanSyncY = scanTileIdInOverTile/overW;
        scanSyncX = GPU_MOD(scanTileIdInOverTile, overW);
        
        genTileId = generatedStamps/(genW * genH);
	genTileIdInScanTile = GPU_MOD(genTileId, (scanW * scanH));
        genSyncY = genTileIdInScanTile/scanW;
        genSyncX = GPU_MOD(genTileIdInScanTile, scanW);
        
        stampTileId = GPU_MOD(generatedStamps, (genW * genH));
        stampSyncY = stampTileId/genW;
        stampSyncX = GPU_MOD(stampTileId, genH);
    }
}

void GenericROP::fetchCompStamp(u64bit cycle)
{
    GPU_ASSERT(
        if (compFetchingPoses.size() > syncQueue.items())
	    panic(getName(), "fetchCompStamp", "fetched more stamps than received");
    )

    ROPQueue *currentStamp;
    bool cacheResult = false;

    if (currInQueue == &inQueue) {
	if (inQueue.empty() && !compFetchingPoses.empty()) {
	    currInQueue = &syncQueue;
	    nextInQueue = currInQueue;
	}
    } else if (currInQueue == &syncQueue) {
	if (compFetchingPoses.empty() && !inQueue.empty()) {
            currInQueue = &inQueue;
	    nextInQueue = currInQueue;
	}
    } else {
        panic(getName(), "fetchCompStamp", "invalid input queue");
    }

    if (currInQueue == &inQueue) {
	if (inQueue.empty())
	    return;

        currentStamp = inQueue.head();
	if (currentStamp->stamp[0]->getFragment() == NULL) {
            if (!fetchQueue.full()) {
	        GPU_ASSERT(
	            if (currentStamp->stamp[0]->getType() != FRAG_COMP_IN)
	                panic(getName(), "fetchCompStamp", "invalid type for this null fragment in inQueue");
	        )

	        fetchQueue.add(currentStamp);
	        inQueue.remove();
	    } else if (!compFetchingPoses.empty())
		nextInQueue = &syncQueue;
	} else {
	    if (!multisampling) {
	        if (readDataROPForComp) {
	    	    if (!fetchQueue.full()) {
                        cacheResult = ropCache->fetch(currentStamp->address[currentStamp->nextBuffer],
                                                      currentStamp->way[currentStamp->nextBuffer],
                                                      currentStamp->line[currentStamp->nextBuffer],
                                                      currentStamp->stamp[0]);

	                if (cacheResult) {
                            //  Update the pointer to the next output buffer.
                            for (currentStamp->nextBuffer++;
                                 (!activeBuffer[currentStamp->nextBuffer]) && (currentStamp->nextBuffer < MAX_RENDER_TARGETS);
                                 currentStamp->nextBuffer++);
                            
                            //  Check if data fetched for all the active buffers.
                            if (currentStamp->nextBuffer == MAX_RENDER_TARGETS)
                            {
                                //  Fetch was succesful.  Add stamp to the fetched stamp queue.
                                fetchQueue.add(currentStamp);

                                //  Remove stamp from the input stamp queue.
                                inQueue.remove();
                        
                                //  Reset the pointer to the next output buffer.
                                currentStamp->nextBuffer = 0;
                            }
	    	        }
	    	    }
	        } else {
	    	    if (!readQueue.full()) {
                        cacheResult = ropCache->allocate(currentStamp->address[currentStamp->nextBuffer],
                                                         currentStamp->way[currentStamp->nextBuffer],
                                                         currentStamp->line[currentStamp->nextBuffer],
                                                         currentStamp->stamp[0]);
	                if (cacheResult) {
                            //  Update the pointer to the next output buffer.
                            for (currentStamp->nextBuffer++;
                                 (!activeBuffer[currentStamp->nextBuffer]) && (currentStamp->nextBuffer < MAX_RENDER_TARGETS);
                                 currentStamp->nextBuffer++);
                            
                            //  Check if data fetched for all the active buffers.
                            if (currentStamp->nextBuffer == MAX_RENDER_TARGETS)
                            {
                                //  Fetch was succesful.  Add stamp to the fetched stamp queue.
                                readQueue.add(currentStamp);

                                //  Remove stamp from the input stamp queue.
                                inQueue.remove();
                        
                                //  Reset the pointer to the next output buffer.
                                currentStamp->nextBuffer = 0;
                            }
	    	        }
	    	    }
	        }
                
		//if (!strcmp(ropName, "ZStencilTest") && gpuId == 0 && stampId == 1 && batchCounter == 364) {
                //    FILE *debugfile = fopen("debugFetchCompStamp.txt", "a+");
                //    fprintf(debugfile, "%s cycle %lld batch %d inQueue fetch (%d %d) inQ %d fetchQ %d fetchPoses %d readPoses %d terminatePoses %d fetchResult %s nextBuffer %d addr 0x%x way %d line %d\n",
                //    	getName(), cycle, batchCounter,
		//	currentStamp->stamp[0]->getFragment()->getX(), currentStamp->stamp[0]->getFragment()->getY(),
		//	inQueue.items(), fetchQueue.items(),
		//	compFetchingPoses.size(), compReadingPoses.size(), compTerminatingPoses.size(),
		//	fetchResult ? "T" : "F", currentStamp->nextBuffer, currentStamp->address[currentStamp->nextBuffer],
		//	currentStamp->way[currentStamp->nextBuffer], currentStamp->line[currentStamp->nextBuffer]);
                //    fflush(debugfile);
                //    fclose(debugfile);
                //}
	
                if (!cacheResult && !compFetchingPoses.empty())
                    nextInQueue = &syncQueue;
	    } else {
		panic(getName(), "fetchCompStamp", "current implementation does not support multisampling");
	    }
	}
    } else if (currInQueue == &syncQueue) {
	if (compFetchingPoses.empty())
	    return;

	u32bit compFetchingPos = compFetchingPoses.front();
        currentStamp = *syncQueue.lookup(compFetchingPos);
	if (currentStamp->stamp[0]->getFragment() == NULL) {
	    GPU_ASSERT(
		if (currentStamp->stamp[0]->getType() != FRAG_COMP_OUT)
		    panic(getName(), "fetchCompStamp", "invalid type for this null fragment in syncQueue");
	    )
	    compReadingPoses.push(compFetchingPos);
	    compFetchingPoses.pop();

	    if (compSchedEnabled)
	        allStampsSentForSync[gpuId][stampId] = true;
	} else {
	    if (!multisampling) {
                cacheResult = ropCache->fetch(currentStamp->address[currentStamp->nextCompFetchBuffer],
                                              currentStamp->way[currentStamp->nextCompFetchBuffer],
                                              currentStamp->line[currentStamp->nextCompFetchBuffer],
                                              currentStamp->stamp[0]);
                
		if (cacheResult) {
                    //if (!strcmp(ropName, "ZStencilTest") && gpuId == 0 && stampId == 1 && batchCounter == 364) {
                    //    FILE *debugfile = fopen("debugFetchCompStamp.txt", "a+");
                    //    fprintf(debugfile, "%s cycle %lld batch %d syncQueue fetch (%d %d) inQ %d fetchQ %d fetchPos %d fetchPoses %d readPoses %d terminatePoses %d fetchResult %s nextBuffer %d addr 0x%x way %d line %d\n",
                    //    	getName(), cycle, batchCounter,
		    //	        currentStamp->stamp[0]->getFragment()->getX(), currentStamp->stamp[0]->getFragment()->getY(),
		    //	        inQueue.items(), fetchQueue.items(), compFetchingPos,
		    //	        compFetchingPoses.size(), compReadingPoses.size(), compTerminatingPoses.size(),
		    //	        cacheResult ? "T" : "F", currentStamp->nextCompFetchBuffer, currentStamp->address[currentStamp->nextCompFetchBuffer],
		    //	        currentStamp->way[currentStamp->nextCompFetchBuffer], currentStamp->line[currentStamp->nextCompFetchBuffer]);
                    //    fflush(debugfile);
                    //    fclose(debugfile);
                    //}
	
		    if (currentStamp->nextCompFetchBuffer == 0)
	                compReadingPoses.push(compFetchingPos);

                    for (currentStamp->nextCompFetchBuffer++;
                         (!activeBuffer[currentStamp->nextCompFetchBuffer]) && (currentStamp->nextCompFetchBuffer < MAX_RENDER_TARGETS);
                        currentStamp->nextCompFetchBuffer++);
                    
                    if (currentStamp->nextCompFetchBuffer == MAX_RENDER_TARGETS) {
			compFetchingPoses.pop();
                        currentStamp->nextCompFetchBuffer = 0;
                    }
                } else if (!inQueue.empty()) {
                    nextInQueue = &inQueue;
                }
	    } else {
		panic(getName(), "fetchCompStamp", "current implementation does not support multisampling");
	    }
	}
    } else {
	panic(getName(), "fetchCompStamp", "invalid input queue");
    }
}

void GenericROP::readCompStamp(u64bit cycle)
{
    GPU_ASSERT(
        if (compReadingPoses.size() > syncQueue.items())
	    panic(getName(), "readCompStamp", "read more stamps than received");
    )

    ROPQueue *currentStamp;
    bool readResult = false;
    bool waitWrite = false;
    u32bit i, n;

    if (currFetchQueue == &fetchQueue) {
	if ((fetchQueue.empty() || readQueue.full()) && !compReadingPoses.empty()) {
	    currFetchQueue = &syncQueue;
	    nextFetchQueue = currFetchQueue;
	}
    } else if (currFetchQueue == &syncQueue) {
	if (compReadingPoses.empty() && !fetchQueue.empty() && !readQueue.full()) {
	    currFetchQueue = &fetchQueue;
	    nextFetchQueue = currFetchQueue;
	}
    } else {
        panic(getName(), "readCompStamp", "invalid fetch queue");
    }

    if (currFetchQueue == &fetchQueue) {
        if (fetchQueue.empty() || readQueue.full())
	    return;

        currentStamp = fetchQueue.head();
        if (currentStamp->stamp[0]->getFragment() == NULL) {	
	    GPU_ASSERT(
		if (currentStamp->stamp[0]->getType() != FRAG_COMP_IN)
    		    panic(getName(), "endOperation", "invalid type for this null fragment");
	    )
	    
	    readQueue.add(currentStamp);
	    fetchQueue.remove();
	    return;
	}
	
	if (!multisampling) {
            waitWrite = false;

	    for (i = firstCAM, n = stampsCAM; n > 0; n--, i = GPU_MOD(i + 1, sizeCAM)) {
	        if (currentStamp->address[currentStamp->nextBuffer] == rawCAM[i]->address[currentStamp->nextBuffer] &&
	            currentStamp != rawCAM[i]) {
	            waitWrite = true;
	        }
	    }

	    if (!waitWrite) {
                readResult = ropCache->read(currentStamp->address[currentStamp->nextBuffer],
                                            currentStamp->way[currentStamp->nextBuffer],
                                            currentStamp->line[currentStamp->nextBuffer],
                                            STAMP_FRAGMENTS * bytesPixel[currentStamp->nextBuffer],
                                            //&currentStamp->data[STAMP_FRAGMENTS * bytesPixel[currentStamp->nextBuffer] * currentStamp->nextBuffer]);
                                            &currentStamp->data[currentStamp->offset[currentStamp->nextBuffer]]);

	        if (readResult) {
                    //if (currentStamp->stamp[0]->getFragment()->getX() == 172 && currentStamp->stamp[0]->getFragment()->getY() == 146) {
	            //    char filename[32];
	            //    sprintf(filename, "debugZSTReadStamp%d.txt", stampId);
	            //    FILE *debugfile = fopen(filename, "a+");
	    	    //    for (u32bit stampIndex = 0; stampIndex < STAMP_FRAGMENTS; stampIndex++) {
	    	    //        fprintf(debugfile, "GPU[%d] %s => cycle %lld batch %d inQueue readCompStamp (%d, %d) triangle ID %d culled %s rt %d addr 0x%x size %d\n",
	    	    //        	    gpuId, getName(), cycle, batchCounter,
	    	    //        	    currentStamp->stamp[stampIndex]->getFragment()->getX(),
	    	    //        	    currentStamp->stamp[stampIndex]->getFragment()->getY(),
	    	    //        	    currentStamp->stamp[stampIndex]->getTriangleID(),
	    	    //        	    currentStamp->stamp[stampIndex]->isCulled() ? "T" : "F",
	    	    //        	    currentStamp->nextBuffer,
	    	    //        	    currentStamp->address[currentStamp->nextBuffer],
	    	    //        	    STAMP_FRAGMENTS * bytesPixel[currentStamp->nextBuffer]);
	    	    //    }
	    	    //    for (u32bit wordIndex = 0; wordIndex < STAMP_FRAGMENTS * bytesPixel[currentStamp->nextBuffer] / 4; wordIndex++) {
	    	    //        fprintf(debugfile, "data[%d] = 0x%08x ", wordIndex,
	    	    //        	    *((u32bit*)(currentStamp->data) +
	    	    //        	    currentStamp->offset[currentStamp->nextBuffer] / 4 +
	    	    //        	    //STAMP_FRAGMENTS * bytesPixel[currentStamp->nextBuffer] * currentStamp->nextBuffer / 4 +
	    	    //        	    wordIndex));
	    	    //    }
	    	    //    fprintf(debugfile, "\n");
	            //    fflush(debugfile);
	            //    fclose(debugfile);
	    	    //}

                    if (currentStamp->nextBuffer == 0) {
	    	        rawCAM[freeCAM] = currentStamp;
	    	        stampsCAM++;
	    	        freeCAM = GPU_MOD(freeCAM + 1, sizeCAM);
	    	    }

	            //  Update the pointer to the next output buffer.
                    for(currentStamp->nextBuffer++;
                        (!activeBuffer[currentStamp->nextBuffer]) && (currentStamp->nextBuffer < MAX_RENDER_TARGETS);
                        currentStamp->nextBuffer++);

                    //  Check if data fetched for all the active buffers.
                    if (currentStamp->nextBuffer == MAX_RENDER_TARGETS)
                    {
                        //  Add stamp to the read stamp queue.
                        readQueue.add(currentStamp);

                        //  Remove stamp from the fetch queue.
                        fetchQueue.remove();
                        
	        	    //  Reset the pointer to the next output buffer.
                        currentStamp->nextBuffer = 0;
                    }
	        }
	    }
	    
            //if (!strcmp(ropName, "ZStencilTest") && gpuId == 0 && stampId == 1 && batchCounter == 364) {
            //    FILE *debugfile = fopen("debugReadCompStamp.txt", "a+");
            //    fprintf(debugfile, "%s cycle %lld batch %d fetchQ read fetchQ %d readQ %d fetchPoses %d readPoses %d terminatePoses %d waitWrite %s readResult %s nextBuffer %d addr 0x%x way %d line %d\n",
            //    	    getName(), cycle, batchCounter,
            //	    fetchQueue.items(), readQueue.items(),
	    //	    compFetchingPoses.size(), compReadingPoses.size(), compTerminatingPoses.size(),
	    //	    waitWrite ? "T" : "F", readResult ? "T" : "F", currentStamp->nextBuffer,
	    //	    currentStamp->address[currentStamp->nextBuffer],
	    //	    currentStamp->way[currentStamp->nextBuffer], currentStamp->line[currentStamp->nextBuffer]);
            //    fflush(debugfile);
            //    fclose(debugfile);
            //}
	
	    if ((waitWrite || !readResult) && !compReadingPoses.empty()) {
	        nextFetchQueue = &syncQueue;
	    }
	} else {
	    panic(getName(), "readCompStamp", "current implementation does not support multisampling");
	}
    } else if (currFetchQueue == &syncQueue) {
	if (compReadingPoses.empty())
	    return;

	u32bit compReadingPos = compReadingPoses.front();
	currentStamp = *syncQueue.lookup(compReadingPos);
	if (currentStamp->stamp[0]->getFragment() == NULL) {
	    GPU_ASSERT(
		if (currentStamp->stamp[0]->getType() != FRAG_COMP_OUT)
    		    panic(getName(), "readCompStamp", "invalid type for this null fragment in syncQueue");
	    )

	    compTerminatingPoses.push(compReadingPos);
	    compReadingPoses.pop();	    
	} else {
	    if (!multisampling) {
		if (compFetchingPoses.empty() || compReadingPoses.front() != compFetchingPoses.front() ||
		    currentStamp->nextCompReadBuffer < currentStamp->nextCompFetchBuffer)
                    readResult = ropCache->read(currentStamp->address[currentStamp->nextCompReadBuffer],
                                                currentStamp->way[currentStamp->nextCompReadBuffer],
                                                currentStamp->line[currentStamp->nextCompReadBuffer],
                                                STAMP_FRAGMENTS * bytesPixel[currentStamp->nextCompReadBuffer],
                                                //&currentStamp->data[STAMP_FRAGMENTS * bytesPixel[currentStamp->nextCompReadBuffer] * currentStamp->nextCompReadBuffer]);
                                                &currentStamp->data[currentStamp->offset[currentStamp->nextCompReadBuffer]]);
		else
		    readResult = false;
                
		if (readResult) {
                    //if (!strcmp(ropName, "ZStencilTest") && gpuId == 0 && stampId == 1 && batchCounter == 364) {
                    //    FILE *debugfile = fopen("debugReadCompStamp.txt", "a+");
                    //    fprintf(debugfile, "%s cycle %lld batch %d syncQ read fetchQ %d readQ %d fetchPos %d readPos %d fetchPoses %d readPoses %d terminatePoses %d readResult %s nextCompFetchBuffer %d nextCompReadBuffer %d addr 0x%x way %d line %d\n",
                    //    	getName(), cycle, batchCounter,
                    //            fetchQueue.items(), readQueue.items(), compFetchingPoses.front(), compReadingPos,
		    //            compFetchingPoses.size(), compReadingPoses.size(), compTerminatingPoses.size(),
		    //            readResult ? "T" : "F", currentStamp->nextCompFetchBuffer, currentStamp->nextCompReadBuffer,
		    //            currentStamp->address[currentStamp->nextCompReadBuffer],
		    //            currentStamp->way[currentStamp->nextCompReadBuffer], currentStamp->line[currentStamp->nextCompReadBuffer]);
                    //    fflush(debugfile);
                    //    fclose(debugfile);
                    //}
	
                    //if (currentStamp->stamp[0]->getFragment()->getX() == 172 && currentStamp->stamp[0]->getFragment()->getY() == 146) {
		    //    char filename[32];
		    //    sprintf(filename, "debugZSTReadStamp%d.txt", stampId);
	            //    FILE *debugfile = fopen(filename, "a+");
		    //    for (u32bit stampIndex = 0; stampIndex < STAMP_FRAGMENTS; stampIndex++) {
		    //        fprintf(debugfile, "GPU[%d] %s => cycle %lld batch %d syncQueue readCompStamp (%d, %d) triangle ID %d culled %s rt %d addr 0x%x size %d\n",
		    //		gpuId, getName(), cycle, batchCounter,
		    //		currentStamp->stamp[stampIndex]->getFragment()->getX(),
		    //		currentStamp->stamp[stampIndex]->getFragment()->getY(),
		    //		currentStamp->stamp[stampIndex]->getTriangleID(),
		    //		currentStamp->stamp[stampIndex]->isCulled() ? "T" : "F",
		    //		currentStamp->nextCompReadBuffer,
		    //		currentStamp->address[currentStamp->nextCompReadBuffer],
		    //		STAMP_FRAGMENTS * bytesPixel[currentStamp->nextCompReadBuffer]);
		    //    }
		    //    for (u32bit wordIndex = 0; wordIndex < STAMP_FRAGMENTS * bytesPixel[currentStamp->nextCompReadBuffer] / 4; wordIndex++) {
		    //        fprintf(debugfile, "data[%d] = 0x%08x ", wordIndex,
		    //		*((u32bit*)(currentStamp->data) +
		    //		 currentStamp->offset[currentStamp->nextCompReadBuffer] / 4 +
		    //		 //STAMP_FRAGMENTS * bytesPixel[currentStamp->nextCompReadBuffer] * currentStamp->nextCompReadBuffer / 4 +
		    //		 wordIndex));
		    //    }
		    //    fprintf(debugfile, "\n");
	            //    fflush(debugfile);
	            //    fclose(debugfile);
		    //}

                    ropCache->unreserve(currentStamp->way[currentStamp->nextCompReadBuffer],
                        		currentStamp->line[currentStamp->nextCompReadBuffer]);
                    for(currentStamp->nextCompReadBuffer++;
                        (!activeBuffer[currentStamp->nextCompReadBuffer]) && (currentStamp->nextCompReadBuffer < MAX_RENDER_TARGETS);
                        currentStamp->nextCompReadBuffer++);
                    
		    if (currentStamp->nextCompReadBuffer == MAX_RENDER_TARGETS) {
	                compTerminatingPoses.push(compReadingPos);
			compReadingPoses.pop();
                        currentStamp->nextCompReadBuffer = 0;
                    }
                } else {
		    if (!fetchQueue.empty() && !readQueue.full())
			nextFetchQueue = &fetchQueue;
		}
	    } else {
		panic(getName(), "readCompStamp", "current implementation does not support multisampling");
	    }
	}
    } else {
        panic(getName(), "readCompStamp", "invalid fetch queue");
    }
}

//void GenericROP::fetchCompStamp(u64bit cycle)
//{
//    ROPQueue *currentStamp;
//    tools::Queue<ROPQueue*> *fetchQ = NULL;
//    bool fetchResult;
//    bool consumerQueueFull = false;
//
//    if (currInQueue == &inQueue) {
//	if ((inQueue.empty() || fetchQueue.full()) && !syncInQueue.empty() && !syncFetchQueue.full()) {
//	    currInQueue = &syncInQueue;
//	    fetchQ = &syncFetchQueue;
//	    nextInQueue = currInQueue;
//	} else {
//            fetchQ = &fetchQueue;
//	    consumerQueueFull = fetchQueue.full();
//	}
//    } else if (currInQueue == &syncInQueue) {
//	if ((syncInQueue.empty() || syncFetchQueue.full()) && !inQueue.empty() && !fetchQueue.full()) {
//            currInQueue = &inQueue;
//	    fetchQ = &fetchQueue;
//	    nextInQueue = currInQueue;
//	} else {
//            fetchQ = &syncFetchQueue;
//	    consumerQueueFull = syncFetchQueue.full();
//	}
//    } else {
//        panic(getName(), "fetchCompStamp", "invalid input queue");
//    }
//
//    if (!currInQueue->empty()) {
//	if (!consumerQueueFull) {
//            currentStamp = currInQueue->head();
//
//	    if (currentStamp->stamp[0]->getFragment() == NULL) {
//	        GPU_ASSERT(
//	    	    if (currentStamp->stamp[0]->getType() != FRAG_COMP_IN && currentStamp->stamp[0]->getType() != FRAG_COMP_OUT)
//    	    	        panic(getName(), "fetchCompStamp", "invalid type for this null fragment");
//	        )
//	
//	    	fetchQ->add(currentStamp);
//	    	currInQueue->remove();
//	    } else {
//		if (!multisampling) {
//		    if (currInQueue == &inQueue) {
//		        if (!bypassROP[currentStamp->nextBuffer]) {
//			    if (readDataROP[currentStamp->nextBuffer])
//                                fetchResult = ropCache->fetch(currentStamp->address[currentStamp->nextBuffer],
//                                                              currentStamp->way[currentStamp->nextBuffer],
//                                                              currentStamp->line[currentStamp->nextBuffer],
//                                                              currentStamp->stamp[0]);
//			    else
//                                fetchResult = ropCache->allocate(currentStamp->address[currentStamp->nextBuffer],
//                                                                 currentStamp->way[currentStamp->nextBuffer],
//                                                                 currentStamp->line[currentStamp->nextBuffer],
//                                                                 currentStamp->stamp[0]);
//			} else {
//			    if (!writeQueue.full()) {
//			        writeQueue.add(currentStamp);
//			        inQueue.remove();
//				return;
//			    } else {
//				 fetchResult = false;
//			    }
//			}
//		    } else {
//			if (!bypassROP[currentStamp->nextBuffer]) {
//                            fetchResult = ropCache->fetch(currentStamp->address[currentStamp->nextBuffer],
//                                                          currentStamp->way[currentStamp->nextBuffer],
//                                                          currentStamp->line[currentStamp->nextBuffer],
//                                                          currentStamp->stamp[0]);
//			} else {
//			    if (!syncReadQueue.full()) {
//				syncReadQueue.add(currentStamp);
//				syncInQueue.remove();
//				return;
//			    }
//			    else {
//				fetchResult = false;
//			    }
//			}
//		   }
//		} else {
//		    panic(getName(), "fetchCompStamp", "current implementation does not support multisampling");
//		}
//
//                if (!strcmp(ropName, "ColorWrite") && gpuId == 5 && stampId == 1 && batchCounter == 745) {
//                    FILE *debugfile = fopen("debugFetchCompStamp.txt", "a+");
//                    fprintf(debugfile, "%s cycle %lld batch %d fetch (%d %d) rt %d inQueue %s inQ %d fetchQ %d syncInQ %d syncFetchQ %d syncReadQ %d fetchResult %s nextBuffer %d addr 0x%x way %d line %d\n",
//                    	getName(), cycle, batchCounter,
//			currentStamp->stamp[0]->getFragment()->getX(), currentStamp->stamp[0]->getFragment()->getY(), currentStamp->nextBuffer,
//			(currInQueue == &inQueue ? "T" : "F"), inQueue.items(), fetchQueue.items(),
//			syncInQueue.items(), syncFetchQueue.items(), syncReadQueue.items(),
//			fetchResult ? "T" : "F", currentStamp->nextBuffer, currentStamp->address[currentStamp->nextBuffer],
//			currentStamp->way[currentStamp->nextBuffer], currentStamp->line[currentStamp->nextBuffer]);
//                    fflush(debugfile);
//                    fclose(debugfile);
//                }
//	
//		if (fetchResult) {
//                    //  Update the pointer to the next output buffer.
//                    for(currentStamp->nextBuffer++;
//                        (!activeBuffer[currentStamp->nextBuffer]) && (currentStamp->nextBuffer < MAX_RENDER_TARGETS);
//                        currentStamp->nextBuffer++);
//                    
//		    //  Check if data fetched for all the active buffers.
//                    if (currentStamp->nextBuffer == MAX_RENDER_TARGETS)
//                    {
//                        //  Fetch was succesful.  Add stamp to the fetched stamp queue.
//	    	        fetchQ->add(currentStamp);
//
//                        //  Remove stamp from the input stamp queue.
//                        currInQueue->remove();
//
//                        //  Reset the pointer to the next output buffer.
//                        currentStamp->nextBuffer = 0;
//                    }
//		} else if (currentStamp->nextBuffer == 0) {
//		    if (currInQueue == &inQueue && !syncInQueue.empty()) {
//		        nextInQueue = &syncInQueue;
//		    }
//		    
//		    if (currInQueue == &syncInQueue && !inQueue.empty()) {
//		        nextInQueue = &inQueue;
//		    }
//		}
//	    }
//	}
//    }
//}
//
//void GenericROP::readCompStamp(u64bit cycle)
//{
//    ROPQueue *currentStamp;
//    tools::Queue<ROPQueue*> *readQ = NULL;
//    bool readResult;
//    bool waitWrite;
//    u32bit i, n;
//
//    if (currFetchQueue == &fetchQueue) {
//	if ((fetchQueue.empty() || readQueue.full()) && !syncFetchQueue.empty() && !syncReadQueue.full()) {
//	    currFetchQueue = &syncFetchQueue;
//	    readQ = &syncReadQueue;
//	    nextFetchQueue = currFetchQueue;
//	} else {
//            readQ = &readQueue;
//	}
//    } else if (currFetchQueue == &syncFetchQueue) {
//	if ((syncFetchQueue.empty() || syncReadQueue.full()) && !fetchQueue.empty() && !readQueue.full()) {
//	    currFetchQueue = &fetchQueue;
//	    readQ = &readQueue;
//	    nextFetchQueue = currFetchQueue;
//	} else {
//            readQ = &syncReadQueue;
//	}
//    } else {
//        panic(getName(), "readCompStamp", "invalid fetch queue");
//    }
//	
//    if (!strcmp(ropName, "ColorWrite") && gpuId == 5 && stampId == 1 && batchCounter == 745) {
//        FILE *debugfile = fopen("debugReadCompStamp.txt", "a+");
//        fprintf(debugfile, "%s cycle %lld batch %d read fetchQ %s fetchQ %d readQ %d syncFetchQ %d syncReadQ %d\n",
//        	getName(), cycle, batchCounter,
//    	        (currFetchQueue == &fetchQueue ? "T" : "F"), fetchQueue.items(), readQueue.items(),
//    	        syncFetchQueue.items(), syncReadQueue.items());
//        fflush(debugfile);
//        fclose(debugfile);
//    }
//	
//    if (!currFetchQueue->empty()) {
//        if (!readQ->full()) {
//	    currentStamp = currFetchQueue->head();
//
//	    if (currentStamp->stamp[0]->getFragment() == NULL) {
//	        GPU_ASSERT(
//	    	    if (currentStamp->stamp[0]->getType() != FRAG_COMP_IN && currentStamp->stamp[0]->getType() != FRAG_COMP_OUT)
//    	    	        panic(getName(), "readCompStamp", "invalid type for this null fragment");
//	        )
//
//	    	readQ->add(currentStamp);
//	    	currFetchQueue->remove();
//	    } else {
//                waitWrite = false;
//
//		if (currFetchQueue == &fetchQueue) {
//		    for (i = firstCAM, n = stampsCAM; n > 0; n--, i = GPU_MOD(i + 1, sizeCAM)) {
//		        if (currentStamp->address[currentStamp->nextBuffer] == rawCAM[i]->address[currentStamp->nextBuffer] &&
//			    currentStamp != rawCAM[i]) {
//			    waitWrite = true;
//			}
//		    }
//		}
//
//		if (!waitWrite) {
//		    if (!multisampling) {
//                        readResult = ropCache->read(currentStamp->address[currentStamp->nextBuffer],
//                                                    currentStamp->way[currentStamp->nextBuffer],
//                                                    currentStamp->line[currentStamp->nextBuffer],
//                                                    STAMP_FRAGMENTS * bytesPixel[currentStamp->nextBuffer],
//                                                    &currentStamp->data[STAMP_FRAGMENTS * bytesPixel[currentStamp->nextBuffer] * currentStamp->nextBuffer]);
//
//		        if (readResult && currFetchQueue == &syncFetchQueue) {
//	                    ropCache->unreserve(currentStamp->way[currentStamp->nextBuffer],
//	                        		currentStamp->line[currentStamp->nextBuffer]);
//		        }
//		    } else {
//		        panic(getName(), "readCompStamp", "current implementation does not support multisampling");
//		    }
//               
//	            if (readResult) {
//                        //if (currentStamp->stamp[0]->getFragment()->getX() == 320 && currentStamp->stamp[0]->getFragment()->getY() == 650) {
//		        //    char filename[32];
//		        //    sprintf(filename, "debugZSTReadStamp%d.txt", stampId);
//	                //    FILE *debugfile = fopen(filename, "a+");
//			//    for (u32bit stampIndex = 0; stampIndex < STAMP_FRAGMENTS; stampIndex++) {
//			//        fprintf(debugfile, "GPU[%d] %s => cycle %lld batch %d readCompStamp (%d, %d) triangle ID %d culled %s addr 0x%x size %d\n",
//			//		gpuId, getName(), cycle, batchCounter, currentStamp->stamp[stampIndex]->getFragment()->getX(),
//			//		currentStamp->stamp[stampIndex]->getFragment()->getY(),
//			//		currentStamp->stamp[stampIndex]->getTriangleID(),
//			//		currentStamp->stamp[stampIndex]->isCulled() ? "T" : "F",
//			//		currentStamp->address[currentStamp->nextBuffer],
//			//		STAMP_FRAGMENTS * bytesPixel[currentStamp->nextBuffer]);
//			//    }
//			//    for (u32bit wordIndex = 0; wordIndex < STAMP_FRAGMENTS * bytesPixel[currentStamp->nextBuffer] / 4; wordIndex++) {
//			//        fprintf(debugfile, "data[%d] = 0x%08x ", wordIndex,
//			//		*((u32bit*)(currentStamp->data) +
//			//		 STAMP_FRAGMENTS * bytesPixel[currentStamp->nextBuffer] * currentStamp->nextBuffer / 4 +
//			//		 wordIndex));
//			//    }
//			//    fprintf(debugfile, "\n");
//	                //    fflush(debugfile);
//	                //    fclose(debugfile);
//			//}
//
//                        if (currFetchQueue == &fetchQueue && currentStamp->nextBuffer == 0) {
//			    rawCAM[freeCAM] = currentStamp;
//			    stampsCAM++;
//			    freeCAM = GPU_MOD(freeCAM + 1, sizeCAM);
//			}
//
//		        //  Update the pointer to the next output buffer.
//                        for(currentStamp->nextBuffer++;
//                            (!activeBuffer[currentStamp->nextBuffer]) && (currentStamp->nextBuffer < MAX_RENDER_TARGETS);
//                            currentStamp->nextBuffer++);
//
//                        //  Check if data fetched for all the active buffers.
//                        if (currentStamp->nextBuffer == MAX_RENDER_TARGETS)
//                        {
//                            //  Add stamp to the read stamp queue.
//                            readQ->add(currentStamp);
//
//                            //  Remove stamp from the fetch queue.
//                            currFetchQueue->remove();
//                            
//		    	    //  Reset the pointer to the next output buffer.
//                            currentStamp->nextBuffer = 0;
//                        }
//		    } else if (currentStamp->nextBuffer == 0) {
//		        if (currFetchQueue == &fetchQueue && !syncFetchQueue.empty()) {
//		            nextFetchQueue = &syncFetchQueue;
//		        }
//		        
//		        if (currFetchQueue == &syncFetchQueue && !fetchQueue.empty()) {
//		            nextFetchQueue = &fetchQueue;
//		        }
//		    }
//		}
//	    }
//	}
//    }
//}

void GenericROP::writeCompStamp(u64bit cycle)
{
    ROPQueue *currentStamp;
    bool writeResult;

    if (!opQueue.empty()) {
        if (!writeQueue.full()) {
	    currentStamp = opQueue.head();

	    if (currentStamp->stamp[0]->getFragment() == NULL) {
	        GPU_ASSERT(
	    	    if (currentStamp->stamp[0]->getType() != FRAG_COMP_IN)
    	    	        panic(getName(), "writeCompStamp", "invalid type for this null fragment");
	        )
	    
	    	writeQueue.add(currentStamp);
	    	opQueue.remove();
	    } else {
	        if (!multisampling) {
                    writeResult = ropCache->write(currentStamp->address[currentStamp->nextBuffer],
                                                  currentStamp->way[currentStamp->nextBuffer],
                                                  currentStamp->line[currentStamp->nextBuffer],
                                                  STAMP_FRAGMENTS * bytesPixel[currentStamp->nextBuffer],
                                                  //&currentStamp->data[currentStamp->nextBuffer * STAMP_FRAGMENTS * bytesPixel[currentStamp->nextBuffer]],
                                                  //&currentStamp->mask[currentStamp->nextBuffer * STAMP_FRAGMENTS * bytesPixel[currentStamp->nextBuffer]]);
                                                  &currentStamp->data[currentStamp->offset[currentStamp->nextBuffer]],
                                                  &currentStamp->mask[currentStamp->offset[currentStamp->nextBuffer]]);
	        } else {
	            panic(getName(), "writeCompStamp", "current implementation does not support multisampling");
	        }

		if (writeResult) {
                    //if (currentStamp->stamp[0]->getFragment()->getX() == 172 && currentStamp->stamp[0]->getFragment()->getY() == 146) {
	            //    char filename[32];
	            //    sprintf(filename, "debugZSTWriteStamp%d.txt", stampId);
	            //    FILE *debugfile = fopen(filename, "a+");
	            //    for (u32bit stampIndex = 0; stampIndex < STAMP_FRAGMENTS; stampIndex++) {
	            //        fprintf(debugfile, "GPU[%d] %s => cycle %lld batch %d writeCompStamp (%d, %d) triangle ID %d culled %s readData %s rt %d addr %x tag %x size %d\n",
	            //		gpuId, getName(), cycle, batchCounter,
		    //    	currentStamp->stamp[stampIndex]->getFragment()->getX(),
	            //		currentStamp->stamp[stampIndex]->getFragment()->getY(),
	            //		currentStamp->stamp[stampIndex]->getTriangleID(),
	            //		currentStamp->stamp[stampIndex]->isCulled() ? "T" : "F",
		    //    	readDataROP[currentStamp->nextBuffer] ? "T" : "F",
		    //    	currentStamp->nextBuffer,
		    //    	currentStamp->address[currentStamp->nextBuffer],
		    //    	ropCache->line2address(currentStamp->way[currentStamp->nextBuffer], currentStamp->line[currentStamp->nextBuffer]),
		    //    	STAMP_FRAGMENTS * bytesPixel[currentStamp->nextBuffer]);
	            //    }
	            //    for (u32bit wordIndex = 0;
	            //	     wordIndex < STAMP_FRAGMENTS * bytesPixel[currentStamp->nextBuffer]/ 4;
	            //	     wordIndex++) {
	            //        fprintf(debugfile, "data[%d] = 0x%08x mask[%d] = 0x%08x ",
		    //                wordIndex,
		    //    	    *((u32bit*)(currentStamp->data) +
		    //    	     currentStamp->offset[currentStamp->nextBuffer] / 4 +
		    //    	     //currentStamp->nextBuffer * STAMP_FRAGMENTS * bytesPixel[currentStamp->nextBuffer] / 4 +
		    //    	     wordIndex),
		    //    	    wordIndex,
		    //    	    *((u32bit*)(currentStamp->mask) +
		    //    	     currentStamp->offset[currentStamp->nextBuffer] / 4 +
		    //    	     //currentStamp->nextBuffer * STAMP_FRAGMENTS * bytesPixel[currentStamp->nextBuffer] / 4 +
		    //    	     wordIndex));
	            //    }
	            //    fprintf(debugfile, "\n");
	            //    fflush(debugfile);
	            //    fclose(debugfile);
                    //}

                    //  Update the pointer to the next output buffer.
                    for(currentStamp->nextBuffer++;
                        (!activeBuffer[currentStamp->nextBuffer]) && (currentStamp->nextBuffer < MAX_RENDER_TARGETS);
                        currentStamp->nextBuffer++);

                    //  Check if data fetched for all the active buffers.
                    if (currentStamp->nextBuffer == MAX_RENDER_TARGETS)
                    {
			if (readDataROPForComp) {
                            GPU_ASSERT(
                                if (stampsCAM == 0)
                                    panic(getName(), "writeCompStamp", "RAW CAM vector empty.");
                                if (rawCAM[firstCAM] == NULL)
                                    panic(getName(), "writeCompStamp", "Unitialized RAW CAM entry accessed.");
                            )

			    rawCAM[firstCAM] = NULL;
			    firstCAM = GPU_MOD(firstCAM + 1, sizeCAM);
			    stampsCAM--;
			}

                        //  Add stamp to the written stamp queue.
                        writeQueue.add(currentStamp);

                        //  Remove stamp from the operated stamp queue.
                        opQueue.remove();

                        //  Reset the pointer to the next output buffer.
                        currentStamp->nextBuffer = 0;
                    }
                    
		}
	    }
	}
    }
}

void GenericROP::terminateCompStamp(u64bit cycle)
{
    ROPQueue *currentStamp;

    //if (!syncReadQueue.empty()) {
    //    if (consumerSyncState == ROP_READY) {
    //        currentStamp = syncReadQueue.head();

    //        GPU_ASSERT(
    //    	if (currentStamp->stamp[0]->getType() != FRAG_COMP_OUT)
    //    	    panic(getName(), "terminateCompStamp", "invalid output fragment type");
    //        )

    //        if (currentStamp->stamp[0]->getFragment()) {
    //    	generateCompFragments(cycle, currentStamp);
    //        	
    //    	postCompWriteProcess(cycle, currentStamp);
    //            freeQueue.add(currentStamp);
    //            syncReadQueue.remove();

    //            currentStamp->nextBuffer = 0;
    //        } else {
    //        	postCompWriteProcess(cycle, currentStamp);
    //            freeQueue.add(currentStamp);
    //            syncReadQueue.remove();

    //    	notLastSyncSent--;
    //        }
    //    }
    //}

    if (!compTerminatingPoses.empty()) {
        if (consumerSyncState == ROP_READY) {
	    u32bit compTerminatingPos = compTerminatingPoses.front();
            currentStamp = *syncQueue.lookup(compTerminatingPos);

            GPU_ASSERT(
                if (compTerminatingPoses.size() > syncQueue.items())
                    panic(getName(), "terminateCompStamp", "terminate more stamps than received");
		if (currentStamp != syncQueue.head())
		    panic(getName(), "terminateCompStamp", "stamps are terminated out-of-order");
	    )

	    if (currentStamp->stamp[0]->getFragment()) {
		generateCompFragments(cycle, currentStamp);

		postCompWriteProcess(cycle, currentStamp);
                freeQueue.add(currentStamp);
                syncQueue.remove();

		currentStamp->nextCompFetchBuffer = 0;
		currentStamp->nextCompReadBuffer = 0;
	    } else {
	    	postCompWriteProcess(cycle, currentStamp);
	        freeQueue.add(currentStamp);
	        syncQueue.remove();

		notLastSyncSent--;
	    }

	    compTerminatingPoses.pop();
	}
    }

    if (!writeQueue.empty()) {
	if (consumerState == ROP_READY) {
            currentStamp = writeQueue.head();

	    GPU_ASSERT(
	        if (currentStamp->stamp[0]->getType() != FRAG_COMP_IN)
	            panic(getName(), "terminateCompStamp", "invalid input fragment type");
	    )

	    if (currentStamp->stamp[0]->getFragment() == NULL)
		notLastSyncReceive--;
		
	    postCompWriteProcess(cycle, currentStamp);
	    writeQueue.remove();
	    freeQueue.add(currentStamp);
	}
    }
}
//  Processes a memory transaction.
void GenericROP::processMemoryTransaction(u64bit cycle,
    MemoryTransaction *memTrans)
{
    //  Get transaction type.
    switch(memTrans->getCommand())
    {
        case MT_STATE:

            //  Received state of the Memory controller.
            memoryState = memTrans->getState();

            GPU_DEBUG_BOX(
                printf("%s => Memory Controller State = %d\n", getName(), memoryState);
            )

            break;

        default:

            GPU_DEBUG_BOX(
                printf("%s => Memory Transaction to the Cache.\n", getName());
            )

            //  Update statistics.
            readBytes->inc(memTrans->getSize());
            globalReadBytes->inc(memTrans->getSize());

            //  Let the rop cache process any other transaction.
            ropCache->processMemoryTransaction(memTrans);

            break;
    }

    //  Delete processed memory transaction.
    delete memTrans;
}

void GenericROP::getState(string &stateString)
{
    stringstream stateStream;

    stateStream.clear();

    stateStream << " state = ";

    switch(state)
    {
        case RAST_RESET:
            stateStream << "RAST_RESET";
            break;
        case RAST_READY:
            stateStream << "RAST_READY";
            break;
        case RAST_DRAWING:
            stateStream << "RAST_DRAW";
            break;
        case RAST_END:
            stateStream << "RAST_END";
            break;
        case RAST_CLEAR:
            stateStream << "RAST_CLEAR";
            break;
        case RAST_CLEAR_FOR_COMP:
            stateStream << "RAST_CLEAR_FOR_COMP";
            break;
        case RAST_CLEAR_END:
            stateStream << "RAST_CLEAR_END";
            break;
        case RAST_SWAP:
            stateStream << "RAST_SWAP";
            break;
        default:
            stateStream << "undefined";
            break;
    }

    /*stateStream << " | Fragment Counter = " << fragmentCounter;
    stateStream << " | Triangle Counter = " << triangleCounter;
    stateStream << " | Last Fragment = " << lastFragment;
    stateStream << " | Fetch Stamps = " << fetchStamps;
    stateStream << " | Read Stamps = " << readStamps;
    stateStream << " | Test Stamps = " << testStamps;
    stateStream << " | Write Stamps = " << writeStamps;
    stateStream << " | Color Stamps = " << colorStamps;*/

    stateString.assign(stateStream.str());
}


void GenericROP::stallReport(u64bit cycle, string &stallReport)
{
    stringstream reportStream;
    
    reportStream << " " << getName() << " stall report for cycle " << cycle << endl;
    reportStream << "------------------------------------------------------------" << endl;


    reportStream << "InputQueue = " << inQueue.items() << " | FetchQueue = " << fetchQueue.items();
    reportStream << " | ReadQueue = " << readQueue.items() << " | OpQueue = " << opQueue.items() << " | writeQueue = " << writeQueue.items();
    reportStream << endl << endl;
    
    string report;
    
    ropCache->stallReport(cycle, report);
    
    reportStream << report;
    
    stallReport.assign(reportStream.str());
}

