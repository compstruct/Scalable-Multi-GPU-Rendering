/**
 *
 * @file PrimitiveClipper.h
 *
 * Define the PrimitiveClipper box class.
 *
 * This class simulates the primitive redistribution in GPUpd (Micro 2017).
 *
 */
 
#include "PrimitiveExchanger.h"
#include "PrimitiveExchangerStateInfo.h"
#include "PrimitiveAssemblyRequest.h"
#include "GPUMath.h"
#include "GPUSimulator.h"

#include <set>
#include <sstream>

using namespace gpu3d;

bool PrimitiveExchanger::underSyncing = false;
std::vector<u32bit> PrimitiveExchanger::freeExchangedIndexBufferEntries = std::vector<u32bit>();

PrimitiveExchanger::PrimitiveExchanger(u32bit gpuId, char *gpuPrefix,
    u32bit numGPUs_, u32bit multiGPUExecMode_, u32bit execRound_, bool runahead_,
    bool gpupdBatchEnabled_, u32bit gpupdBatchThreshold_, u32bit interGPUBusWidth_, u32bit interGPUBusLat_,
    u32bit trCycle, u32bit peUnits, u32bit p2gLat, u32bit startLat, u32bit cpdDrawCommBatchSize_,
    u32bit peTriangleInputBufferSize_, u32bit mappedInfoReadBufferSize_, u32bit exchangedIndexBufferSize_,
    u32bit displayW, u32bit displayH, u32bit scanW, u32bit scanH, bool allResultsOnChip_,
    char *name, Box *parent) :
    
    numGPUs(numGPUs_), multiGPUExecMode(multiGPUExecMode_), execRound(execRound_), runahead(runahead_),
    gpupdBatchEnabled(gpupdBatchEnabled_), gpupdBatchThreshold(gpupdBatchThreshold_),
    interGPUBusWidth(interGPUBusWidth_), interGPUBusLat(interGPUBusLat_),
    trianglesCycle(trCycle), primitiveExchangerUnits(peUnits),
    p2gMappingLat(p2gLat), startLatency(startLat), cpdDrawCommBatchSize(cpdDrawCommBatchSize_),
    peTriangleInputBufferSize(peTriangleInputBufferSize_), mappedInfoReadBufferSize(mappedInfoReadBufferSize_),
    exchangedIndexBufferSize(exchangedIndexBufferSize_), swapCommReceived(false),
    drawCommsInPE(0), mappedDrawComms(0), syncedDrawComms(0), exchangedDrawComms(0),
    allResultsOnChip(allResultsOnChip_), numReceivedTris(0), Box(gpuId, name, parent)
{
    if (gpuId == 0) freeExchangedIndexBufferEntries.resize(numGPUs, exchangedIndexBufferSize);

    DynamicObject *defaultState[1];

    /*  Check parameters. */
    GPU_ASSERT(
        if (numGPUs > 8*sizeof(unsigned int))
            panic("PrimitiveExchanger", "PrimitiveExchanger", "Exceed the supported maximum number of GPUs.");

        if (trianglesCycle != primitiveExchangerUnits)
            panic("PrimitiveExchanger", "PrimitiveExchanger",
		  "Number of primitive exchanger units must be the same that the triangles per cycle in current implementation.");
        if (peTriangleInputBufferSize <= (3 * trianglesCycle))
            panic("PrimitiveExchanger", "PrimitiveExchanger",
		  "Primitive exchanger triangle buffer too small for input latency and throughput.");

	if (interGPUBusWidth < 3*sizeof(unsigned int))
	    panic("PrimitiveExchanger", "PrimitiveExchanger", "BW of inter-GPU bus has to be enough to send three indexes of a triangle.");
	if (GPU_MOD(interGPUBusWidth, sizeof(unsigned int)) != 0)
	    panic("PrimitiveExchanger", "PrimitiveExchanger", "BW of inter-GPU bus has to be multiple times of the index size.");
    )

    primitiveExchangerCommand = newInputSignal("PrimitiveExchangerCommand", 1, 1, gpuPrefix);
    primitiveExchangerState = newOutputSignal("PrimitiveExchangerCommandState", 1, 1, gpuPrefix);
    defaultState[0] = new PrimitiveExchangerStateInfo(PE_READY);
    primitiveExchangerState->setData(defaultState);
    primitiveExchangerMappedDrawComms = newOutputSignal("PrimitiveExchangerMappedDrawComms", 1, 1, gpuPrefix);
    primitiveExchangerSyncedDrawComms = newOutputSignal("PrimitiveExchangerSyncedDrawComms", 1, 1, gpuPrefix);

    if (numGPUs > 1 && multiGPUExecMode == GPUPD && execRound == 1) {
        primitiveExchangerInput = newInputSignal("PrimitiveExchangerInput", trianglesCycle, 1, gpuPrefix);
        primitiveExchangerRequest = newOutputSignal("PrimitiveExchangerRequest", 1, 1, gpuPrefix);
    } else {
        primitiveExchangerInput = NULL;
	primitiveExchangerRequest = NULL;
    }

    primitiveMappingStart = newInputSignal("PrimitiveMappingExecution", primitiveExchangerUnits, p2gMappingLat, gpuPrefix);
    primitiveMappingEnd = newOutputSignal("PrimitiveMappingExecution", primitiveExchangerUnits, p2gMappingLat, gpuPrefix);

    redistributedStreamAddress[0].resize(cpdDrawCommBatchSize, 0);
    p2gMappingAddress[0].resize(cpdDrawCommBatchSize, 0);
    mappedTrianglesPerBatch[0].resize(cpdDrawCommBatchSize, 0);
    sizeOfStoredIndexes[0].resize(cpdDrawCommBatchSize, 0);
    exchangedIndexWriteSize[0].resize(cpdDrawCommBatchSize, 0);
    exchangedIndexWriteCoalescer[0] = new u8bit*[cpdDrawCommBatchSize];
    idealMappedInfoBuffer[0].resize(cpdDrawCommBatchSize, std::vector<IdealMappedInfoBufferEntry>());
    for (u32bit i = 0; i < cpdDrawCommBatchSize; i++)
	exchangedIndexWriteCoalescer[0][i] = new u8bit[MAX_TRANSACTION_SIZE];
    // Duplicate resources for runahead execution
    if (runahead) {
        redistributedStreamAddress[1].resize(cpdDrawCommBatchSize, 0);
        p2gMappingAddress[1].resize(cpdDrawCommBatchSize, 0);
        mappedTrianglesPerBatch[1].resize(cpdDrawCommBatchSize, 0);
        sizeOfStoredIndexes[1].resize(cpdDrawCommBatchSize, 0);
        exchangedIndexWriteSize[1].resize(cpdDrawCommBatchSize, 0);
        exchangedIndexWriteCoalescer[1] = new u8bit*[cpdDrawCommBatchSize];
        idealMappedInfoBuffer[1].resize(cpdDrawCommBatchSize, std::vector<IdealMappedInfoBufferEntry>());
        for (u32bit i = 0; i < cpdDrawCommBatchSize; i++)
	    exchangedIndexWriteCoalescer[1][i] = new u8bit[MAX_TRANSACTION_SIZE];
    }

    mapperMemoryRequest = newOutputSignal("PEMapperMemoryRequest", 1, 1, gpuPrefix);
    mapperMemoryData    = newInputSignal("PEMapperMemoryData", 2, 1, gpuPrefix);
    syncerMemoryRequest = newOutputSignal("PESyncerMemoryRequest", 1, 1, gpuPrefix);
    syncerMemoryData    = newInputSignal("PESyncerMemoryData", 2, 1, gpuPrefix);

    char signalPrefix[32];
    indexExchangeOut = new Signal*[numGPUs];
    indexExchangeIn = new Signal*[numGPUs];
    for (u32bit gpuIndex = 0; gpuIndex < numGPUs; gpuIndex++) {
	if (gpuIndex == gpuId) {
            sprintf(signalPrefix, "GPU%dTo%d", gpuId, gpuIndex);
            indexExchangeOut[gpuIndex] = newOutputSignal("indexExchange", exchangedIndexBufferSize, 1, signalPrefix);
            sprintf(signalPrefix, "GPU%dTo%d", gpuIndex, gpuId);
            indexExchangeIn[gpuIndex] = newInputSignal("indexExchange", exchangedIndexBufferSize, 1, signalPrefix);
	} else {
            sprintf(signalPrefix, "GPU%dTo%d", gpuId, gpuIndex);
            indexExchangeOut[gpuIndex] = newOutputSignal("indexExchange", interGPUBusWidth/sizeof(unsigned int),
			                                 (allResultsOnChip ? 1 : interGPUBusLat), signalPrefix);
            sprintf(signalPrefix, "GPU%dTo%d", gpuIndex, gpuId);
            indexExchangeIn[gpuIndex] = newInputSignal("indexExchange", interGPUBusWidth/sizeof(unsigned int),
			                               (allResultsOnChip ? 1 : interGPUBusLat), signalPrefix);
	}
    }

    lastPECommand = new PrimitiveExchangerCommand(PECOM_RESET);

    peTriangleInputBuffer = new TriangleSetupInput*[peTriangleInputBufferSize];
    GPU_ASSERT(
        if (peTriangleInputBuffer == NULL)
            panic("PrimitiveExchanger", "PrimitiveExchanger", "Error allocating the triangle input buffer.");	
    )
    for (u32bit i = 0; i < peTriangleInputBufferSize; i++) {
        peTriangleInputBuffer[i] = NULL;
    }

    currentBatch = 0;
    currentFrame = 0;

    mapperMemState = MS_NONE;
    currentMappedBatch = 0;
    sizeOfStoredMappedInfo = 0;
    mapperStoreTransCycles = 0;
    mapperCurrentTicket = 0;
    mapperFreeTickets = MAX_MEMORY_TICKETS;

    syncerMemState = MS_NONE;
    currentSyncedBatch = 0;
    sizeOfReadMappedInfo = 0;
    syncerReadTransCycles = 0;
    syncerStoreTransCycles = 0;
    syncerCurrentTicket = 0;
    syncerFreeTickets = MAX_MEMORY_TICKETS;

    currentExchangedBatch = 0;
    exchangedGPUs = 0;
    interGPUSyncTransCycles = 0;
    syncerMemReorder.clear();
    
    mappedInfoReadBuffer.resize(mappedInfoReadBufferSize);
    for (u32bit i = 0; i < mappedInfoReadBufferSize; i++) {
	mappedInfoReadBuffer[i].last = false;
	mappedInfoReadBuffer[i].size = 0;
        mappedInfoReadBuffer[i].data = new u8bit[MAX_TRANSACTION_SIZE];
    }

    exchangedIndexBuffer.resize(exchangedIndexBufferSize);
    for (u32bit i = 0; i < exchangedIndexBufferSize; i++) {
        exchangedIndexBuffer[i].last = false;
        exchangedIndexBuffer[i].batchId = 0;
        exchangedIndexBuffer[i].index = 0;
    }

    exchangedIndexesInGPUpd = NULL;

    displayWidth = displayW;
    displayHeight = displayH;
    scanWidth = scanW;
    scanHeight = scanH;
    peEmu = PrimitiveExchangerEmulator();

    if (gpupdBatchEnabled) {
        currentReceiveGPUpdBatch = 0;
        currentMapGPUpdBatch = 0;
        currentExchangeGPUpdBatch = 0;
        memset(firstDrawCommPerGPUpdBatch, 0, 2*sizeof(u32bit));
        memset(numDrawsPerGPUpdBatch, 0, 2*sizeof(u32bit));
        memset(readyToExchange, 0, 2*sizeof(bool));
    }

    inputs = &getSM(gpuId).getNumericStatistic("InputTriangles", u32bit(0), "PrimitiveExchanger", "PE");
    recvIndexes = &getSM(gpuId).getNumericStatistic("ReceivedIndexes", u32bit(0), "PrimitiveExchanger", "PE");
    inputsMappedToOtherGPUs = &getSM(gpuId).getNumericStatistic("NumberOfInputTrianglesMappedToOtherGPUs", u32bit(0), "PrimitiveExchanger", "PE");
    inputsMappedToMultipleGPUs = &getSM(gpuId).getNumericStatistic("NumberOfInputTrianglesMappedToMultipleGPUs", u32bit(0), "PrimitiveExchanger", "PE");
    numSentGPUs = &getSM(gpuId).getNumericStatistic("NumberOfMappedGPUs", u32bit(0), "PrimitiveExchanger", "PE");
    syncCycles = &getSM(gpuId).getNumericStatistic("NumberOfSyncCycles", u32bit(0), "PrimitiveExchanger", "PE");
    backPressureFail = &getSM(gpuId).getNumericStatistic("BackPressureFail", u32bit(0), "PrimitiveExchanger", "PE");
    mappedInfoReadFail = &getSM(gpuId).getNumericStatistic("MappedInfoReadFail", u32bit(0), "PrimitiveExchanger", "PE");
    sequentialWait = &getSM(gpuId).getNumericStatistic("SequentialWait", u32bit(0), "PrimitiveExchanger", "PE");
    loadImbalanceWait = &getSM(gpuId).getNumericStatistic("LoadImbalanceWait", u32bit(0), "PrimitiveExchanger", "PE");
    noFreeMappedInfoReadBufferEntries = &getSM(gpuId).getNumericStatistic("NoFreeMappedInfoReadBufferEntries", u32bit(0), "PrimitiveExchanger", "PE");
    interGPUSyncTrafficLoad = &getSM(gpuId).getNumericStatistic("InterGPUSyncTrafficLoad", u32bit(0), "PrimitiveExchanger", "PE");

    globalInputs = &getSM().getNumericStatistic("InputTriangles", u32bit(0), "PrimitiveExchanger", "PE");
    globalRecvIndexes = &getSM().getNumericStatistic("ReceivedIndexes", u32bit(0), "PrimitiveExchanger", "PE");
    globalInputsMappedToOtherGPUs = &getSM().getNumericStatistic("NumberOfInputTrianglesMappedToOtherGPUs", u32bit(0), "PrimitiveExchanger", "PE");
    globalInputsMappedToMultipleGPUs = &getSM().getNumericStatistic("NumberOfInputTrianglesMappedToMultipleGPUs", u32bit(0), "PrimitiveExchanger", "PE");
    globalNumSentGPUs = &getSM().getNumericStatistic("NumberOfMappedGPUs", u32bit(0), "PrimitiveExchanger", "PE");
    globalSyncCycles = &getSM().getNumericStatistic("NumberOfSyncCycles", u32bit(0), "PrimitiveExchanger", "PE");
    globalBackPressureFail = &getSM().getNumericStatistic("BackPressureFail", u32bit(0), "PrimitiveExchanger", "PE");
    globalMappedInfoReadFail = &getSM().getNumericStatistic("MappedInfoReadFail", u32bit(0), "PrimitiveExchanger", "PE");
    globalSequentialWait = &getSM().getNumericStatistic("SequentialWait", u32bit(0), "PrimitiveExchanger", "PE");
    globalLoadImbalanceWait = &getSM().getNumericStatistic("LoadImbalanceWait", u32bit(0), "PrimitiveExchanger", "PE");
    globalNoFreeMappedInfoReadBufferEntries = &getSM().getNumericStatistic("NoFreeMappedInfoReadBufferEntries", u32bit(0), "PrimitiveExchanger", "PE");
    globalInterGPUSyncTrafficLoad = &getSM().getNumericStatistic("InterGPUSyncTrafficLoad", u32bit(0), "PrimitiveExchanger", "PE");

    state = PE_RESET;
}

PrimitiveExchanger::~PrimitiveExchanger()
{
    delete [] peTriangleInputBuffer;
    
    for (u32bit i = 0; i < mappedInfoReadBufferSize; i++) {
	delete mappedInfoReadBuffer[i].data;
	mappedInfoReadBuffer[i].data = NULL;
    }

    delete [] exchangedIndexWriteCoalescer[0];
    if (runahead)
        delete [] exchangedIndexWriteCoalescer[1];

    idealMappedInfoBuffer[0].clear();
    idealMappedInfoBuffer[1].clear();
}

void PrimitiveExchanger::clock(u64bit cycle) {
    PrimitiveExchangerCommand *peComm;
    MemoryTransaction *memTrans;
    
    TriangleSetupInput *tsInput;
    u32bit triRequest;
    
    TriangleSetupInput *mappedInput;
    u32bit mappedInfo[4];
    u32bit mappedInfoWriteAddr, mappedInfoWriteSize;
    u8bit mappedInfoWriteCoalescer[MAX_TRANSACTION_SIZE];
    
    u32bit *numTrianglesForSyncing;
    u32bit mappedInfoReadAddr, mappedInfoReadSize;

    QuadFloat *vAttr1, *vAttr2, *vAttr3;
    u32bit index1, index2, index3;
    std::set<u32bit>::iterator iter;
    std::set<u32bit> mappedGPUIds;
    std::bitset<8*sizeof(u32bit)> mappedGPUs;
    
    bool lastMappedInfo;
    u32bit mappedInfoExchangeSize;
    u8bit *mappedInfoExchangeData;
    u32bit consumedInterGPUbw;
    bool canExchange;
    std::vector<u32bit> exchangedIndexes;

    bool lastIndexExchanged;
    u32bit exchangedIndexSrcGPU;
    u32bit exchangedIndexWriteBatch;
    u32bit exchangedIndexWriteAddr;
    u8bit *indexWriteCoalescer;
    u32bit *indexCoalescerWriteSize;

    std::vector<IdealMappedInfoBufferEntry> idealBuffer;
    
    u32bit i, gpuIndex, processedSize;

    indexOwner owner;

    u32bit drawIdInGPUpdBatch;

    GPU_DEBUG_BOX(
        printf("PrimitiveExchanger => Clock %lld.\n", cycle);		    
    )

    while(mapperMemoryData->read(cycle, (DynamicObject *&) memTrans)) {
        processMapperMemoryTransaction(memTrans);
    }

    while(syncerMemoryData->read(cycle, (DynamicObject *&) memTrans)) {
        processSyncerMemoryTransaction(memTrans);
    }

    switch (state) {
	case PE_RESET:
            GPU_DEBUG_BOX(
                printf("PrimitiveExchanger => RESET state.\n");		    
            )
            
            redistributedStreamAddress[0].resize(cpdDrawCommBatchSize, 0);
            redistributedStreamAddress[1].resize(cpdDrawCommBatchSize, 0);
            p2gMappingAddress[0].resize(cpdDrawCommBatchSize, 0);
            p2gMappingAddress[1].resize(cpdDrawCommBatchSize, 0);

	    hRes = 400;
	    vRes = 400;
	    d3d9PixelCoordinates = false;
	    iniX = 0;
	    iniY = 0;
	    width = 400;
	    height = 400;
	    scissorTest = false;
	    scissorIniX = 0;
	    scissorIniY = 0;
	    scissorWidth = 400;
	    scissorHeight = 400;

	    if (gpupdBatchEnabled) {
	        currentReceiveGPUpdBatch = 0;
                currentMapGPUpdBatch = 0;
	        currentExchangeGPUpdBatch = 0;
                memset(firstDrawCommPerGPUpdBatch, 0, 2*sizeof(u32bit));
                memset(numDrawsPerGPUpdBatch, 0, 2*sizeof(u32bit));
                memset(readyToExchange, 0, 2*sizeof(bool));
	    }

	    state = PE_READY;

	    break;
	case PE_READY:
            GPU_DEBUG_BOX(
                printf("PrimitiveExchanger => READY state.\n");		    
            )

            if (primitiveExchangerCommand->read(cycle, (DynamicObject*&) peComm))
		processCommand(peComm);

	    break;
	case PE_DRAW:
            GPU_DEBUG_BOX(
                printf("PrimitiveExchanger => DRAW state.\n");		    
            )

	    // request triangle inputs from Clipper
	    if (reservedEntries + mappedTriangles < peTriangleInputBufferSize) {
	        triRequest = GPU_MIN(peTriangleInputBufferSize - reservedEntries - mappedTriangles, trianglesCycle);
		primitiveExchangerRequest->write(cycle, new PrimitiveAssemblyRequest(triRequest));
		reservedEntries += triRequest;
	    }

	    // Check whether we can begin the primitive exchanging
	    if (!underSyncing && (swapCommReceived || (!gpupdBatchEnabled && mappedDrawComms >= cpdDrawCommBatchSize) ||
		(gpupdBatchEnabled && readyToExchange[currentExchangeGPUpdBatch] && mappedDrawComms >= numDrawsPerGPUpdBatch[currentExchangeGPUpdBatch]))) {
                if (GPUSimulator::gpuSync->synced(gpuId) == false) {
		    GPUSimulator::gpuSync->sync(gpuId, GPU_PE_MAPPER_SYNC);
		} else {
		    loadImbalanceWait->inc();
		    globalLoadImbalanceWait->inc();
		    if (!runahead || swapCommReceived || (!gpupdBatchEnabled && (drawCommsInPE + syncedDrawComms) == 2*cpdDrawCommBatchSize) ||
			(gpupdBatchEnabled && readyToExchange[0] && readyToExchange[1])) {
		        syncCycles->inc();
		        globalSyncCycles->inc();
		    }
		}

	        if (GPUSimulator::gpuSync->allGPUSynced()) {
		    GPUSimulator::gpuSync->exitSync(gpuId);

		    if (GPUSimulator::gpuSync->allGPUSynced() == false)
		        underSyncing = true;
	        }
	    }

	    if (syncerReadTransCycles > 0) {
		syncerReadTransCycles--;

		if (syncerReadTransCycles == 0) {
		    receivedMappedInfoEntries++;
		    syncerFreeTickets++;
		}
	    }

	    if (syncerStoreTransCycles > 0) {
	        syncerStoreTransCycles--;

		if (syncerStoreTransCycles == 0)
		    syncerFreeTickets++;
	    }

	    // Primitive exchanging among different GPUs
	    if (underSyncing) {
		// Receive indexes from other GPUs and write them into memory
		for (gpuIndex = 0; gpuIndex < numGPUs; gpuIndex++) {
		    while (indexExchangeIn[gpuIndex]->read(cycle, (DynamicObject *&)peComm)) {
		        if (peComm->isLast()) {
		    	    exchangedIndexBuffer[nextExchangedIndexRecvEntry].last = true;
		    	    exchangedIndexBuffer[nextExchangedIndexRecvEntry].srcGPU = gpuIndex;
		    	    exchangedIndexBuffer[nextExchangedIndexRecvEntry].batchId = peComm->getCurrentExchangeBatchId();

		    	    nextExchangedIndexRecvEntry = GPU_MOD(nextExchangedIndexRecvEntry + 1, exchangedIndexBufferSize);
		    	    receivedExchangedIndexes++;
		        } else {
		    	    exchangedIndexes = peComm->getExchangedIndexes();
                            GPU_ASSERT(
		                if (exchangedIndexes.size() < 3)
	                            panic("PrimitiveExchanger", "clock", "Did not get 3 indexes for a triangle.");
		            )

			    owner.gpuId = gpuId;
			    owner.frameId = currentFrame;
			    owner.batchId = peComm->getCurrentExchangeBatchId();
			    GPU_ASSERT(
			        if (exchangedIndexesInGPUpd->count(owner) == 0)
	                            panic("PrimitiveExchanger", "clock", "should have allocated an entry for this owner.");
			    )

		    	    for (i = 0; i < 3; i++)
			    {
                                exchangedIndexesInGPUpd->at(owner).push_back(exchangedIndexes[i]);

		    	        exchangedIndexBuffer[nextExchangedIndexRecvEntry].last = false;
		    	        exchangedIndexBuffer[nextExchangedIndexRecvEntry].srcGPU = gpuIndex;
		    	        exchangedIndexBuffer[nextExchangedIndexRecvEntry].batchId = peComm->getCurrentExchangeBatchId();
		    	        exchangedIndexBuffer[nextExchangedIndexRecvEntry].index = exchangedIndexes[i];
		    	        nextExchangedIndexRecvEntry = GPU_MOD(nextExchangedIndexRecvEntry + 1, exchangedIndexBufferSize);
		    	        receivedExchangedIndexes++;
				
				recvIndexes->inc();
				globalRecvIndexes->inc();
		    	    }
		        }
		        delete peComm;
		    }
		}
		
		// Store received indexes into memory
		if (receivedExchangedIndexes > 0 && (allResultsOnChip ||
		    ((syncerMemState & MS_WRITE_ACCEPT) != 0 && syncerStoreTransCycles == 0 && syncerFreeTickets > 0)))
		{
		    indexWriteCoalescer = NULL;
		    indexCoalescerWriteSize = NULL;
		    lastIndexExchanged = false;
		    while (receivedExchangedIndexes > 0) {
		        receivedExchangedIndexes--;
		    	exchangedIndexWriteBatch = exchangedIndexBuffer[nextExchangedIndexStoreEntry].batchId;
		        exchangedIndexSrcGPU = exchangedIndexBuffer[nextExchangedIndexStoreEntry].srcGPU;
			if (exchangedIndexSrcGPU == gpuId || !allResultsOnChip)
		            freeExchangedIndexBufferEntries[gpuId]++;

		        if (!exchangedIndexBuffer[nextExchangedIndexStoreEntry].last) {
			    if (!allResultsOnChip) {
				if (!gpupdBatchEnabled) {
		                    if (!runahead || GPU_MOD(exchangedIndexWriteBatch, 2 * cpdDrawCommBatchSize) < cpdDrawCommBatchSize) {
			                indexWriteCoalescer = exchangedIndexWriteCoalescer[0][GPU_MOD(exchangedIndexWriteBatch, cpdDrawCommBatchSize)];
			                indexCoalescerWriteSize = &(exchangedIndexWriteSize[0][GPU_MOD(exchangedIndexWriteBatch, cpdDrawCommBatchSize)]);
			            } else {
			                indexWriteCoalescer = exchangedIndexWriteCoalescer[1][GPU_MOD(exchangedIndexWriteBatch, cpdDrawCommBatchSize)];
			                indexCoalescerWriteSize = &(exchangedIndexWriteSize[1][GPU_MOD(exchangedIndexWriteBatch, cpdDrawCommBatchSize)]);
			            }
				} else {
				    drawIdInGPUpdBatch = exchangedIndexWriteBatch - firstDrawCommPerGPUpdBatch[currentExchangeGPUpdBatch];
			            indexWriteCoalescer = exchangedIndexWriteCoalescer[currentExchangeGPUpdBatch][drawIdInGPUpdBatch];
			            indexCoalescerWriteSize = &(exchangedIndexWriteSize[currentExchangeGPUpdBatch][drawIdInGPUpdBatch]);
				}

		    	        (*((u32bit*)(indexWriteCoalescer + (*indexCoalescerWriteSize)))) = exchangedIndexBuffer[nextExchangedIndexStoreEntry].index;
			        (*indexCoalescerWriteSize) += sizeof(u32bit);
			    }
			    nextExchangedIndexStoreEntry = GPU_MOD(nextExchangedIndexStoreEntry + 1, exchangedIndexBufferSize);

			    if (!allResultsOnChip && (*indexCoalescerWriteSize) == MAX_TRANSACTION_SIZE) break;
		        } else {
			    lastIndexExchanged = true;
		    	    exchangedDrawComms++;

		            if ((!swapCommReceived && !gpupdBatchEnabled && GPU_MOD(exchangedDrawComms, cpdDrawCommBatchSize) == 0) ||
		                (!swapCommReceived && gpupdBatchEnabled && GPU_MOD(exchangedDrawComms, numDrawsPerGPUpdBatch[currentExchangeGPUpdBatch]) == 0) ||
		    	        (swapCommReceived && GPU_MOD(exchangedDrawComms, syncedDrawComms + mappedDrawComms) == 0)) {
		    	        GPU_ASSERT(
		    	            if ((!gpupdBatchEnabled && (exchangedGPUs + 1) != exchangedDrawComms / cpdDrawCommBatchSize &&
		    	                 (exchangedGPUs + 1) != exchangedDrawComms / (syncedDrawComms + mappedDrawComms)) ||
		    	                (gpupdBatchEnabled && (exchangedGPUs + 1) != exchangedDrawComms / numDrawsPerGPUpdBatch[currentExchangeGPUpdBatch] &&
		    	                 (exchangedGPUs + 1) != exchangedDrawComms / (syncedDrawComms + mappedDrawComms)))
		    	                panic("PrimitiveExchange", "clock", "GPU should do the synchronziation one by one.");
		    	        )
		                exchangedGPUs++;
			    }

		            nextExchangedIndexStoreEntry = GPU_MOD(nextExchangedIndexStoreEntry + 1, exchangedIndexBufferSize);
			    if (!allResultsOnChip) break;
			}
		    }
		   
		    if (!allResultsOnChip && indexCoalescerWriteSize && ((*indexCoalescerWriteSize == MAX_TRANSACTION_SIZE) ||
			(lastIndexExchanged && exchangedIndexSrcGPU == (numGPUs - 1))))
		    {
			if (!gpupdBatchEnabled) {
		            if (!runahead || GPU_MOD(exchangedIndexWriteBatch, 2 * cpdDrawCommBatchSize) < cpdDrawCommBatchSize) {
		                exchangedIndexWriteAddr = redistributedStreamAddress[0][GPU_MOD(exchangedIndexWriteBatch, cpdDrawCommBatchSize)] +
		    	    	                      sizeOfStoredIndexes[0][GPU_MOD(exchangedIndexWriteBatch, cpdDrawCommBatchSize)];
		                sizeOfStoredIndexes[0][GPU_MOD(exchangedIndexWriteBatch, cpdDrawCommBatchSize)] += (*indexCoalescerWriteSize);
		            } else {
		                exchangedIndexWriteAddr = redistributedStreamAddress[1][GPU_MOD(exchangedIndexWriteBatch, cpdDrawCommBatchSize)] +
		    	    	                      sizeOfStoredIndexes[1][GPU_MOD(exchangedIndexWriteBatch, cpdDrawCommBatchSize)];
		                sizeOfStoredIndexes[1][GPU_MOD(exchangedIndexWriteBatch, cpdDrawCommBatchSize)] += (*indexCoalescerWriteSize);
		            }
			} else {
		            drawIdInGPUpdBatch = exchangedIndexWriteBatch - firstDrawCommPerGPUpdBatch[currentExchangeGPUpdBatch];
		            exchangedIndexWriteAddr = redistributedStreamAddress[currentExchangeGPUpdBatch][drawIdInGPUpdBatch] +
		    	                          sizeOfStoredIndexes[currentExchangeGPUpdBatch][drawIdInGPUpdBatch];
		            sizeOfStoredIndexes[currentExchangeGPUpdBatch][drawIdInGPUpdBatch] += (*indexCoalescerWriteSize);
			}

		        memTrans = new MemoryTransaction(
		            MT_WRITE_DATA,
		    	    exchangedIndexWriteAddr,
		    	    (*indexCoalescerWriteSize),
		    	    indexWriteCoalescer,
		    	    PRIMITIVESYNCER,
		    	    syncerCurrentTicket++);

			(*indexCoalescerWriteSize) = 0;
		        syncerFreeTickets--;
		        syncerMemoryRequest->write(cycle, memTrans);
		        syncerStoreTransCycles += memTrans->getBusCycles();
		    }

		    if (!allResultsOnChip && exchangedIndexSrcGPU == (numGPUs - 1) && lastIndexExchanged) {
		        // have got the last exchanged index
			if (!gpupdBatchEnabled) {
		            if (!runahead || GPU_MOD(exchangedIndexWriteBatch, 2 * cpdDrawCommBatchSize) < cpdDrawCommBatchSize) {
			        sizeOfStoredIndexes[0][GPU_MOD(exchangedIndexWriteBatch, cpdDrawCommBatchSize)] = 0;
			    } else {
			        sizeOfStoredIndexes[1][GPU_MOD(exchangedIndexWriteBatch, cpdDrawCommBatchSize)] = 0;
			    }
			} else {
		            drawIdInGPUpdBatch = exchangedIndexWriteBatch - firstDrawCommPerGPUpdBatch[currentExchangeGPUpdBatch];
			    sizeOfStoredIndexes[currentExchangeGPUpdBatch][drawIdInGPUpdBatch] = 0;
			}
		    }
		}

	        // Send mapped info to other GPUs
                if (interGPUSyncTransCycles > 0)
		    interGPUSyncTransCycles--;

		for (consumedInterGPUbw = 0; (consumedInterGPUbw < interGPUBusWidth) && (interGPUSyncTransCycles == 0);)
		{
		    // not reasonable, but to make sure you will make full use of the inter-GPU BW
		    // do not care how many mappedInfoReadBuffer entries you can process in one cycle
		    if ((freeMappedInfoReadBufferEntries < mappedInfoReadBufferSize) && (exchangedGPUs == gpuId) &&
		        (mappedInfoReadBuffer[nextMappedInfoExchangeEntry].size == mappedInfoReadBuffer[nextMappedInfoExchangeEntry].received))
		    {
			GPU_ASSERT(
			    if (!allResultsOnChip && receivedMappedInfoEntries == 0 && mappedInfoReadBuffer[nextMappedInfoExchangeEntry].last == false)
	                        panic("PrimitiveExchanger", "clock", "no received mapped info, should not begin exchanging.");
			)

		        lastMappedInfo = mappedInfoReadBuffer[nextMappedInfoExchangeEntry].last;
		        mappedInfoExchangeSize = mappedInfoReadBuffer[nextMappedInfoExchangeEntry].size;
		        mappedInfoExchangeData = mappedInfoReadBuffer[nextMappedInfoExchangeEntry].data;
		        processedSize = mappedInfoReadBuffer[nextMappedInfoExchangeEntry].processed;
		       
		        canExchange = true;
	                exchangedIndexes.clear();
		        mappedGPUIds.clear();

		        if (lastMappedInfo) {
		    	    for (gpuIndex = 0; gpuIndex < numGPUs; gpuIndex++) {
		    	        canExchange = canExchange && (freeExchangedIndexBufferEntries[gpuIndex] > 0);
		    	        if (!canExchange) break;
                                    
		    	        mappedGPUIds.insert(gpuIndex);
		    	    }
			    // add a dummy index
			    exchangedIndexes.push_back(0);
		        } else {
		            mappedGPUs = std::bitset<8*sizeof(u32bit)>( *(((u32bit*)(mappedInfoExchangeData + processedSize)) + 3) );
		            for (gpuIndex = 0; gpuIndex < numGPUs; gpuIndex++) {
		                if (mappedGPUs.test(gpuIndex)) {
		    	            canExchange = canExchange && (freeExchangedIndexBufferEntries[gpuIndex] >= 3);
                                    if (!canExchange) break;

		            	    mappedGPUIds.insert(gpuIndex);
		                }
		            }

		    	    if (canExchange) {
		                index1 = *((u32bit*)(mappedInfoExchangeData + processedSize));
		                index2 = *(((u32bit*)(mappedInfoExchangeData + processedSize)) + 1);
		                index3 = *(((u32bit*)(mappedInfoExchangeData + processedSize)) + 2);
		    	        
		                exchangedIndexes.push_back(index1);
		                exchangedIndexes.push_back(index2);
		                exchangedIndexes.push_back(index3);
		    	    }
		        }
		        
		        if (canExchange) {
		            for (iter = mappedGPUIds.begin(); iter != mappedGPUIds.end(); iter++) {
		    	        peComm = new PrimitiveExchangerCommand(lastMappedInfo, currentExchangedBatch, exchangedIndexes);
		    	        indexExchangeOut[*iter]->write(cycle, peComm);

			        if (*iter == gpuId || !allResultsOnChip)	
				    freeExchangedIndexBufferEntries[*iter] -= exchangedIndexes.size();

				if (*iter != gpuId) {
				    consumedInterGPUbw += (exchangedIndexes.size() * sizeof(unsigned int));
				    interGPUSyncTrafficLoad->inc(exchangedIndexes.size() * sizeof(unsigned int));
				    globalInterGPUSyncTrafficLoad->inc(exchangedIndexes.size() * sizeof(unsigned int));
				}
		            }

		    	    if (!lastMappedInfo) {
		                processedSize += 4*sizeof(u32bit);	
		    	        mappedInfoReadBuffer[nextMappedInfoExchangeEntry].processed = processedSize;
		    	    }

		    	    if (processedSize == mappedInfoExchangeSize) {
		                if (lastMappedInfo) {
		    	    	    printf("B_%d_%d", gpuId, currentExchangedBatch);
		    	    	    currentExchangedBatch++;
		    	        }
		                   
		    	        nextMappedInfoExchangeEntry = GPU_MOD(nextMappedInfoExchangeEntry + 1, mappedInfoReadBufferSize);
	                        freeMappedInfoReadBufferEntries++;
		    	        if (!(lastMappedInfo || allResultsOnChip)) {
		    	    	    GPU_ASSERT(
		    	    	        if (receivedMappedInfoEntries == 0)
		    	    	            panic("PrimitiveExchanger", "clock",
		    	    		          "could not exchange indexes before receive mapped info from memory.");
		    	    	    )
		    	            receivedMappedInfoEntries--;
		    	        }
		    	    }
		        } else {
		            backPressureFail->inc();
			    globalBackPressureFail->inc();
			    break;
			}
		    } else {
			if (exchangedGPUs == gpuId) {
			    mappedInfoReadFail->inc();
			    globalMappedInfoReadFail->inc();
			} else if (exchangedGPUs < gpuId) {
			    sequentialWait->inc();
			    globalSequentialWait->inc();
			}
		        break;
	            }
		}

		if (!allResultsOnChip)
		    interGPUSyncTransCycles = (u32bit)ceil(f32bit(consumedInterGPUbw)/f32bit(interGPUBusWidth));

		// Load mapped info from memory
		if ((mappedDrawComms > 0) && (freeMappedInfoReadBufferEntries > 0) && ((!gpupdBatchEnabled && syncedDrawComms < cpdDrawCommBatchSize) ||
		    (gpupdBatchEnabled && syncedDrawComms < numDrawsPerGPUpdBatch[currentExchangeGPUpdBatch])))
		{
		    if (!gpupdBatchEnabled) {
		        if (!runahead || GPU_MOD(currentSyncedBatch, 2*cpdDrawCommBatchSize) < cpdDrawCommBatchSize)
		        {
		            mappedInfoReadAddr = p2gMappingAddress[0][GPU_MOD(currentSyncedBatch, cpdDrawCommBatchSize)] + sizeOfReadMappedInfo;
		            numTrianglesForSyncing = &(mappedTrianglesPerBatch[0][GPU_MOD(currentSyncedBatch, cpdDrawCommBatchSize)]);
		            idealBuffer = idealMappedInfoBuffer[0][GPU_MOD(currentSyncedBatch, cpdDrawCommBatchSize)];
		        } else
		        {
		            mappedInfoReadAddr = p2gMappingAddress[1][GPU_MOD(currentSyncedBatch, cpdDrawCommBatchSize)] + sizeOfReadMappedInfo;
		            numTrianglesForSyncing = &(mappedTrianglesPerBatch[1][GPU_MOD(currentSyncedBatch, cpdDrawCommBatchSize)]);
		            idealBuffer = idealMappedInfoBuffer[1][GPU_MOD(currentSyncedBatch, cpdDrawCommBatchSize)];
		        }
		    } else {
			drawIdInGPUpdBatch = currentSyncedBatch - firstDrawCommPerGPUpdBatch[currentExchangeGPUpdBatch];
		        mappedInfoReadAddr = p2gMappingAddress[currentExchangeGPUpdBatch][drawIdInGPUpdBatch] + sizeOfReadMappedInfo;
		        numTrianglesForSyncing = &(mappedTrianglesPerBatch[currentExchangeGPUpdBatch][drawIdInGPUpdBatch]);
		        idealBuffer = idealMappedInfoBuffer[currentExchangeGPUpdBatch][drawIdInGPUpdBatch];
		    }

		    if ((*numTrianglesForSyncing) > 0 && (allResultsOnChip ||
		        ((syncerMemState & MS_READ_ACCEPT) != 0 && syncerFreeTickets > 0 && syncerStoreTransCycles == 0)))
		    {
			// Each triangle is recorded as <vertexIndex1, vertexIndex2, vertexIndex3, mappedGPUIds>
			// mappedGPUIds is represented as a bitvector
			if (*(numTrianglesForSyncing) >= (MAX_TRANSACTION_SIZE / (4*sizeof(u32bit)))) {
			    mappedInfoReadSize = MAX_TRANSACTION_SIZE;
			} else {
			    mappedInfoReadSize = (*(numTrianglesForSyncing))*4*sizeof(u32bit);
			}
			
			mappedInfoReadBuffer[nextMappedInfoReadEntry].last = false;
			mappedInfoReadBuffer[nextMappedInfoReadEntry].size = mappedInfoReadSize;
			mappedInfoReadBuffer[nextMappedInfoReadEntry].processed = 0;
			mappedInfoReadBuffer[nextMappedInfoReadEntry].addr = mappedInfoReadAddr;

			if (allResultsOnChip) {
			     mappedInfoReadBuffer[nextMappedInfoReadEntry].received = mappedInfoReadSize;
		             for (i = 0; i < mappedInfoReadSize;) {
			         *((u32bit*)(mappedInfoReadBuffer[nextMappedInfoReadEntry].data + i)) =
				     idealBuffer[idealBuffer.size() - (*numTrianglesForSyncing) + (i/(4*sizeof(u32bit)))].v1;
			         *((u32bit*)(mappedInfoReadBuffer[nextMappedInfoReadEntry].data + i + sizeof(u32bit))) =
				     idealBuffer[idealBuffer.size() - (*numTrianglesForSyncing) + (i/(4*sizeof(u32bit)))].v2;
			         *((u32bit*)(mappedInfoReadBuffer[nextMappedInfoReadEntry].data + i + 2*sizeof(u32bit))) =
				     idealBuffer[idealBuffer.size() - (*numTrianglesForSyncing) + (i/(4*sizeof(u32bit)))].v3;
			         *((u32bit*)(mappedInfoReadBuffer[nextMappedInfoReadEntry].data + i + 3*sizeof(u32bit))) =
				     idealBuffer[idealBuffer.size() - (*numTrianglesForSyncing) + (i/(4*sizeof(u32bit)))].gpus;
				 
				 i += (4*sizeof(u32bit));
			     } 	
			} else {
			    mappedInfoReadBuffer[nextMappedInfoReadEntry].received = 0;
			    syncerMemReorder[syncerCurrentTicket] = nextMappedInfoReadEntry;
	                    
			    memTrans = new MemoryTransaction(
	                        MT_READ_REQ,
	                        mappedInfoReadAddr,
	                        mappedInfoReadSize,
	                        mappedInfoReadBuffer[nextMappedInfoReadEntry].data,
	                        PRIMITIVESYNCER,
	                        syncerCurrentTicket++);

		            syncerFreeTickets--;
			    syncerMemoryRequest->write(cycle, memTrans);
			}
			
			(*numTrianglesForSyncing) -= (mappedInfoReadSize/(4*sizeof(u32bit)));
			sizeOfReadMappedInfo += mappedInfoReadSize;
			freeMappedInfoReadBufferEntries--;
			nextMappedInfoReadEntry = GPU_MOD(nextMappedInfoReadEntry + 1, mappedInfoReadBufferSize);
		    }
		        
		    if ((*numTrianglesForSyncing) == 0 && freeMappedInfoReadBufferEntries > 0) {
			mappedInfoReadBuffer[nextMappedInfoReadEntry].last = true;
			mappedInfoReadBuffer[nextMappedInfoReadEntry].size = 0;
			mappedInfoReadBuffer[nextMappedInfoReadEntry].received = 0;
			mappedInfoReadBuffer[nextMappedInfoReadEntry].processed = 0;
			
			freeMappedInfoReadBufferEntries--;
			nextMappedInfoReadEntry = GPU_MOD(nextMappedInfoReadEntry + 1, mappedInfoReadBufferSize);
		       
			if (!gpupdBatchEnabled) { 
			    if (!runahead || GPU_MOD(currentSyncedBatch, 2*cpdDrawCommBatchSize) < cpdDrawCommBatchSize) {
			        idealMappedInfoBuffer[0][GPU_MOD(currentSyncedBatch, cpdDrawCommBatchSize)].clear();
			    } else {
			        idealMappedInfoBuffer[1][GPU_MOD(currentSyncedBatch, cpdDrawCommBatchSize)].clear();
			    }
			} else {
			    drawIdInGPUpdBatch = currentSyncedBatch - firstDrawCommPerGPUpdBatch[currentExchangeGPUpdBatch];
			    idealMappedInfoBuffer[currentExchangeGPUpdBatch][drawIdInGPUpdBatch].clear();
			}

		        drawCommsInPE--;
	                mappedDrawComms--; 
		        syncedDrawComms++;
		        currentSyncedBatch++;
		        sizeOfReadMappedInfo = 0;
		    }
		} else if ((mappedDrawComms > 0) && (freeMappedInfoReadBufferEntries == 0) &&
			   ((!gpupdBatchEnabled && syncedDrawComms < cpdDrawCommBatchSize) ||
		            (gpupdBatchEnabled && syncedDrawComms < numDrawsPerGPUpdBatch[currentExchangeGPUpdBatch]))) {
		    noFreeMappedInfoReadBufferEntries->inc();
		    globalNoFreeMappedInfoReadBufferEntries->inc();
		}

		// Check whether primitive exchanging finished
		if (syncerFreeTickets == MAX_MEMORY_TICKETS &&
		    ((!swapCommReceived && !gpupdBatchEnabled && exchangedDrawComms == numGPUs * cpdDrawCommBatchSize) ||
		     (!swapCommReceived && gpupdBatchEnabled && exchangedDrawComms == numGPUs * numDrawsPerGPUpdBatch[currentExchangeGPUpdBatch]) ||
		     (swapCommReceived && mappedDrawComms == 0 && exchangedDrawComms == numGPUs * syncedDrawComms)))
		{
		    GPU_ASSERT(
		        if ((!gpupdBatchEnabled && syncedDrawComms != cpdDrawCommBatchSize) &&
		            (gpupdBatchEnabled && syncedDrawComms != numDrawsPerGPUpdBatch[currentExchangeGPUpdBatch]) &&
			    (!(swapCommReceived && mappedDrawComms == 0)))
			    panic("PrimitiveExchanger", "clock", "Primitive exchanging should have not been finished.");
		    )
		    GPU_ASSERT(
		        if (swapCommReceived && drawCommsInPE != 0)
	                    panic("PrimtiveExchanger", "clock", "Cannot get more draw commands before swap is processed.");
		    )
		    
                    if (GPUSimulator::gpuSync->synced(gpuId) == false)
	                GPUSimulator::gpuSync->sync(gpuId, GPU_PE_SYNCER_SYNC);

	            if (GPUSimulator::gpuSync->allGPUSynced()) {
		        peComm = new PrimitiveExchangerCommand(PECOM_SYNCED_DRAW_COMM);
		        peComm->setNumOfSyncedDrawComms(syncedDrawComms);
                        primitiveExchangerSyncedDrawComms->write(cycle, (DynamicObject *&)peComm);
		        
		        syncedDrawComms = 0;
			exchangedDrawComms = 0;
			exchangedGPUs = 0;

			if (gpupdBatchEnabled) {
			    numDrawsPerGPUpdBatch[currentExchangeGPUpdBatch] = 0;
			    readyToExchange[currentExchangeGPUpdBatch] = false;
			    if (runahead)
			        currentExchangeGPUpdBatch = GPU_MOD(currentExchangeGPUpdBatch + 1, 2);
			}

		        if (swapCommReceived) {
		            swapCommReceived = false;

		            currentBatch = 0;
			    currentFrame++;
		            currentMappedBatch = 0;
		            currentSyncedBatch = 0;
			    currentExchangedBatch = 0;

			    if (gpupdBatchEnabled) {
			        currentReceiveGPUpdBatch = 0;
                                currentMapGPUpdBatch = 0;
			        currentExchangeGPUpdBatch = 0;
			        memset(firstDrawCommPerGPUpdBatch, 0, 2*sizeof(u32bit));
			        memset(numDrawsPerGPUpdBatch, 0, 2*sizeof(u32bit));
			        memset(readyToExchange, 0, 2*sizeof(bool));
			    }
		           
		            state = PE_END;
		        }

	                GPUSimulator::gpuSync->exitSync(gpuId);

			if (GPUSimulator::gpuSync->allGPUSynced() == false)
			    underSyncing = false;
	            }
		}

		if (!runahead || swapCommReceived || (!gpupdBatchEnabled && (drawCommsInPE + syncedDrawComms) == 2*cpdDrawCommBatchSize) ||
		    (gpupdBatchEnabled && readyToExchange[0] && readyToExchange[1])) {
		    syncCycles->inc();
		    globalSyncCycles->inc();
		}
	    }

	    // Receive triangles from clipper
	    if (peCycles > 0) {
	        peCycles--;
	    } else {
	        while (primitiveExchangerInput->read(cycle, (DynamicObject *&) tsInput)) {
                    GPU_ASSERT(
                        if ((reservedEntries + mappedTriangles) > peTriangleInputBufferSize)
                            panic("PrimitiveExchanger", "clock", "No primitive exchanger buffer entries available.");
                    )

                    /*  Check if it is an already culled triangle.  */
                    if (tsInput->isLast())
                    {
                        GPU_DEBUG_BOX(
                            printf("PrimitiveExchanger => Last triangle (ID %d) received.\n",
                                tsInput->getTriangleID());
                        )
                    }
                    else
                    {
                        GPU_DEBUG_BOX(
                            printf("PrimitiveExchanger => Triangle (ID %d) received from Clipper.\n",
                                tsInput->getTriangleID());
                        )

		        inputs->inc();
		        globalInputs->inc();
                    }

		    primitiveMappingStart->write(cycle, tsInput, p2gMappingLat);
		    peCycles = startLatency - 1;
		} 
	    }

	    // Map triangles
	    while (primitiveMappingEnd->read(cycle, (DynamicObject *&) tsInput)) {
                GPU_ASSERT(
                    if (mappedTriangles == peTriangleInputBufferSize)
                        panic("PrimitiveExchanger", "clock", "Primitive exchanger triangle buffer is full.");
                )

		peTriangleInputBuffer[nextTriangleInputFreeEntry] = tsInput;
		
		if (!(tsInput->isLast())) {
		    vAttr1 = tsInput->getVertexAttributes(0);
		    vAttr2 = tsInput->getVertexAttributes(1);
		    vAttr3 = tsInput->getVertexAttributes(2);
		    mappedGPUIds.clear();
		    mappedGPUIds = peEmu.getMappedGPUIds(numGPUs, vAttr1, vAttr2, vAttr3, (displayWidth * scanWidth), (displayHeight * scanHeight));

		    GPU_ASSERT(
		        if (mappedGPUIds.size() == 0)
               		    panic("PrimitiveExchanger", "clock", "Each Input should be mapped to one GPU at least.");
		    )

		    for (iter = mappedGPUIds.begin(); iter != mappedGPUIds.end(); iter++) {
		        tsInput->setMappedGPUIds(*iter);

			if (*iter != gpuId) {
		            numSentGPUs->inc();
		            globalNumSentGPUs->inc();
			}
		    }

		    if ((mappedGPUIds.size() == 1 && mappedGPUIds.count(gpuId) == 0) || mappedGPUIds.size() > 1) {
		        inputsMappedToOtherGPUs->inc();
		        globalInputsMappedToOtherGPUs->inc();
		    }
		    
		    if (mappedGPUIds.size() > 1) {
		        inputsMappedToMultipleGPUs->inc();
		        globalInputsMappedToMultipleGPUs->inc();
		    }
		}
		
		mappedTriangles++;

		nextTriangleInputFreeEntry = GPU_MOD(nextTriangleInputFreeEntry + 1, peTriangleInputBufferSize);

		reservedEntries--;
	    }

	    // Store mapped results into memory
	    if (mapperStoreTransCycles > 0) {
		mapperStoreTransCycles--;

		if (mapperStoreTransCycles == 0)
		    mapperFreeTickets++;
	    }

	    if ((mappedTriangles > 0 ) && (allResultsOnChip ||
		((mapperStoreTransCycles == 0) && ((mapperMemState & MS_WRITE_ACCEPT) != 0) && (mapperFreeTickets > 0))) &&
	        ((mappedTriangles >= (MAX_TRANSACTION_SIZE / (4*sizeof(u32bit)))) || ((mappedTriangles > 0) &&
		peTriangleInputBuffer[GPU_MOD(nextMappedTriangle + mappedTriangles - 1, peTriangleInputBufferSize)]->isLast())))
	    {
	       mappedInfoWriteSize = 0;
	       if (!gpupdBatchEnabled) {
	           if (!runahead || GPU_MOD(currentMappedBatch, 2*cpdDrawCommBatchSize) < cpdDrawCommBatchSize) {
	               mappedInfoWriteAddr = p2gMappingAddress[0][GPU_MOD(currentMappedBatch, cpdDrawCommBatchSize)] + sizeOfStoredMappedInfo;
	           } else {
	               mappedInfoWriteAddr = p2gMappingAddress[1][GPU_MOD(currentMappedBatch, cpdDrawCommBatchSize)] + sizeOfStoredMappedInfo;
	           }
	       } else {
		   drawIdInGPUpdBatch = currentMappedBatch - firstDrawCommPerGPUpdBatch[currentMapGPUpdBatch];
	           mappedInfoWriteAddr = p2gMappingAddress[currentMapGPUpdBatch][drawIdInGPUpdBatch] + sizeOfStoredMappedInfo;
	       }

	       for (i = 0; (i < (MAX_TRANSACTION_SIZE / (4*sizeof(u32bit)))) && (mappedTriangles > 0); i++) {
	           mappedTriangles--;
		   
                   mappedInput = peTriangleInputBuffer[nextMappedTriangle];

		   if (mappedInput->isLast()) {
		       mappedDrawComms++;

		       peComm = new PrimitiveExchangerCommand(PECOM_MAPPED_DRAW_COMM);
		       peComm->setNumOfMappedDrawComms(1);
                       primitiveExchangerMappedDrawComms->write(cycle, (DynamicObject *&)peComm);
		       
		       delete mappedInput;
		       peTriangleInputBuffer[nextMappedTriangle] = NULL;
		       nextMappedTriangle = GPU_MOD(nextMappedTriangle + 1, peTriangleInputBufferSize);
                    
		       // End of current draw command
		       currentMappedBatch++;
		       sizeOfStoredMappedInfo = 0; 

		       if (gpupdBatchEnabled && runahead && readyToExchange[currentMapGPUpdBatch] &&
			   currentMappedBatch == (firstDrawCommPerGPUpdBatch[currentMapGPUpdBatch] + numDrawsPerGPUpdBatch[currentMapGPUpdBatch]))
			   currentMapGPUpdBatch = GPU_MOD(currentMapGPUpdBatch + 1, 2);

		       break;
		   } else {
		       mappedInput->getIndexes(mappedInfo[0], mappedInfo[1], mappedInfo[2]);
                       mappedInfo[3] = mappedInput->getMappedGPUIds();
		       memcpy(mappedInfoWriteCoalescer + mappedInfoWriteSize, (u8bit*)mappedInfo, 4*sizeof(u32bit));
		       mappedInfoWriteSize += 4*sizeof(u32bit);
		       sizeOfStoredMappedInfo += 4*sizeof(u32bit);

		       if (!gpupdBatchEnabled) {
		           if (!runahead || GPU_MOD(currentMappedBatch, 2*cpdDrawCommBatchSize) < cpdDrawCommBatchSize) {
		               mappedTrianglesPerBatch[0][GPU_MOD(currentMappedBatch, cpdDrawCommBatchSize)]++;	
		               
		               if (allResultsOnChip) {
		                   idealMappedInfoBuffer[0][GPU_MOD(currentMappedBatch, cpdDrawCommBatchSize)].push_back(
		                       IdealMappedInfoBufferEntry(mappedInfo[0], mappedInfo[1], mappedInfo[2], mappedInfo[3]));
		               }
		           } else {
		               mappedTrianglesPerBatch[1][GPU_MOD(currentMappedBatch, cpdDrawCommBatchSize)]++;	
		               
		               if (allResultsOnChip) {
		                   idealMappedInfoBuffer[1][GPU_MOD(currentMappedBatch, cpdDrawCommBatchSize)].push_back(
		                       IdealMappedInfoBufferEntry(mappedInfo[0], mappedInfo[1], mappedInfo[2], mappedInfo[3]));
		               }
		           }
		       } else {
		           drawIdInGPUpdBatch = currentMappedBatch - firstDrawCommPerGPUpdBatch[currentMapGPUpdBatch];
		           mappedTrianglesPerBatch[currentMapGPUpdBatch][drawIdInGPUpdBatch]++;	
		           
		           if (allResultsOnChip) {
		               idealMappedInfoBuffer[currentMapGPUpdBatch][drawIdInGPUpdBatch].push_back(
		                   IdealMappedInfoBufferEntry(mappedInfo[0], mappedInfo[1], mappedInfo[2], mappedInfo[3]));
		           }
		       }
		       
		       delete mappedInput;
		       peTriangleInputBuffer[nextMappedTriangle] = NULL;
		       nextMappedTriangle = GPU_MOD(nextMappedTriangle + 1, peTriangleInputBufferSize);
		   }
	       }

	       if (!allResultsOnChip && mappedInfoWriteSize > 0) {
	           memTrans = new MemoryTransaction(
	               MT_WRITE_DATA,
	               mappedInfoWriteAddr,
	               mappedInfoWriteSize,
	               mappedInfoWriteCoalescer,
	               PRIMITIVEMAPPER,
	               mapperCurrentTicket++);

		   mapperFreeTickets--;
                   mapperMemoryRequest->write(cycle, memTrans);
		   mapperStoreTransCycles += memTrans->getBusCycles();
	       }
	    }

            if (primitiveExchangerCommand->read(cycle, (DynamicObject*&) peComm))
		processCommand(peComm);

	    break;
	case PE_END:
            GPU_DEBUG_BOX(
                printf("PrimitiveExchanger => END state.\n");		    
            )

            if (primitiveExchangerCommand->read(cycle, (DynamicObject*&) peComm))
		processCommand(peComm);

	    break;
	default:
	    panic("PrimitiveExchanger", "clock", "Unsupported state.");
    }

    primitiveExchangerState->write(cycle, new PrimitiveExchangerStateInfo(state));
}

void PrimitiveExchanger::processCommand(PrimitiveExchangerCommand *peComm) {
    indexOwner owner;

    delete lastPECommand;

    lastPECommand = peComm;

    switch(peComm->getCommand()) {
        case PECOM_RESET:
            GPU_DEBUG_BOX(
                printf("PrimitiveExchanger => RESET command received.\n");		    
            )

	    redistributedStreamAddress[0].clear();
	    redistributedStreamAddress[1].clear();
	    p2gMappingAddress[0].clear();
	    p2gMappingAddress[1].clear();

	    swapCommReceived = false;

	    state = PE_RESET;

	    break;
	case PECOM_START:
            GPU_DEBUG_BOX(
                printf("PrimitiveExchanger => START command received.\n");		    
            )

	    GPU_ASSERT(
	        if ((state != PE_READY) && (state != PE_DRAW))
                    panic("PrimitiveExchanger", "processCommand", "PECOM_START only can be received in PE_READY and PE_DRAW state.");		
	    )

	    drawCommsInPE++;

	    if (gpupdBatchEnabled) {
	        numReceivedTris += GPUDriver::getGPUDriver()->getNumTrisPerBatch(currentFrame, currentBatch);
                numDrawsPerGPUpdBatch[currentReceiveGPUpdBatch]++;
	        GPU_ASSERT(
	            if (numDrawsPerGPUpdBatch[currentReceiveGPUpdBatch] > cpdDrawCommBatchSize)
	                panic("PrimitiveExchanger", "processCommand", "Please enlarge cpdDrawCommBatchSize");
	        )
	        if (numDrawsPerGPUpdBatch[currentReceiveGPUpdBatch] == 1)
	            firstDrawCommPerGPUpdBatch[currentReceiveGPUpdBatch] = currentBatch;
	        if (numReceivedTris >= gpupdBatchThreshold) {
	            numReceivedTris = 0;
	            readyToExchange[currentReceiveGPUpdBatch] = true;
	            if (runahead)
	                currentReceiveGPUpdBatch = GPU_MOD(currentReceiveGPUpdBatch + 1, 2);
	        }
	    }
	   
	    GPU_ASSERT(
	        if ((!runahead && drawCommsInPE > cpdDrawCommBatchSize) || (runahead && drawCommsInPE > 2*cpdDrawCommBatchSize))
                    panic("PrimitiveExchanger", "processCommand", "Too many draw commands have been issued.");		
	    )
       
            owner.gpuId = gpuId;
	    owner.frameId = currentFrame;
	    owner.batchId = currentBatch;
	    
            GPU_ASSERT(
	        if (exchangedIndexesInGPUpd->count(owner) != 0)
	            panic("PrimitiveExchanger", "processCommand", "should have not allocated an entry for this owner.");
	    )

	    exchangedIndexesInGPUpd->insert(std::pair<indexOwner, std::vector<u32bit> >(owner, std::vector<u32bit>()));
	   
	    peEmu.setViewport(d3d9PixelCoordinates, iniX, iniY, width, height);
	    peEmu.setScissor(hRes, vRes, scissorTest, scissorIniX, scissorIniY, scissorWidth, scissorHeight);

	    currentBatch++;

	    if (state == PE_READY) {
	        peCycles = 0;
	        mappedTriangles = 0;
	        reservedEntries = 0;
	        nextTriangleInputFreeEntry = 0;
	        nextMappedTriangle = 0;

		nextMappedInfoReadEntry = 0;
		freeMappedInfoReadBufferEntries = mappedInfoReadBufferSize;
		
		receivedMappedInfoEntries = 0;
		nextMappedInfoExchangeEntry = 0;

		nextExchangedIndexRecvEntry = 0;
		nextExchangedIndexStoreEntry = 0;
		receivedExchangedIndexes = 0;

		exchangedGPUs = 0;

	        swapCommReceived = false;

	        state = PE_DRAW;
	    }

	    break;
        case PECOM_REG_READ:
            GPU_DEBUG_BOX(
                printf("PrimitiveExchanger => REG_READ command received.\n");		    
            )

	    panic("PrimitiveExchanger", "processCommand", "REG_READ command not supported.");

	    break;
	case PECOM_REG_WRITE:
            GPU_DEBUG_BOX(
                printf("PrimitiveExchanger => REG_WRITE command received.\n");		    
            )

	    processRegisterWrite(peComm->getRegister(), peComm->getSubRegister(), peComm->getRegisterData());

	    break;
	case PECOM_END:
            GPU_DEBUG_BOX(
                printf("PrimitiveExchanger => END command received.\n");		    
            )

	    GPU_ASSERT(
	        if (state != PE_END)
                    panic("PrimitiveExchanger", "processCommand", "PECOM_END only can be received in PE_END state.");		
	    )

	    state = PE_READY;

	    break;
	case PECOM_SWAP:
            GPU_DEBUG_BOX(
                printf("PrimitiveExchanger => SWAP command received.\n");		    
            )

	    GPU_ASSERT(
	        if (drawCommsInPE > cpdDrawCommBatchSize || drawCommsInPE != mappedDrawComms)
                    panic("PrimitiveExchanger", "processCommand", "PECOM_SWAP only received while all draw commands are mapped.");		
	    )

	    swapCommReceived = true;

	    break;
	default:
	    panic("PrimitiveExchanger", "processCommand", "Unsupported command");
    }
}

void PrimitiveExchanger::processRegisterWrite(GPURegister reg, u32bit subReg, GPURegData data) {
    switch (reg) {
	case GPU_DISPLAY_X_RES:
            hRes = data.uintVal;
            break;

	case GPU_DISPLAY_Y_RES:
            vRes = data.uintVal;
            break;

	case GPU_D3D9_PIXEL_COORDINATES:
	    d3d9PixelCoordinates = data.booleanVal;
	    break;

	case GPU_VIEWPORT_INI_X:
	    iniX = data.intVal;
	    break;

	case GPU_VIEWPORT_INI_Y:
	    iniY = data.intVal;
	    break;

	case GPU_VIEWPORT_WIDTH:
	    width = data.uintVal;
	    break;

	case GPU_VIEWPORT_HEIGHT:
	    height = data.uintVal;
	    break;

	case GPU_SCISSOR_TEST:
	    scissorTest = data.booleanVal;
	    break;

	case GPU_SCISSOR_INI_X:
	    scissorIniX = data.intVal;
	    break;

	case GPU_SCISSOR_INI_Y:
	    scissorIniY = data.intVal;
	    break;

	 case GPU_SCISSOR_WIDTH:
	    scissorWidth = data.uintVal;
	    break;

	 case GPU_SCISSOR_HEIGHT:
	    scissorHeight = data.uintVal;
	    break;

         case GPU_STREAM_ADDRESS:

	     GPU_ASSERT(
	         if (subReg < MAX_STREAM_BUFFERS)
	 	    panic("PrimitiveExchanger", "processRegisterWrite", "This stream should be used for the primitive redistribution.");
	     )

	     switch((subReg - MAX_STREAM_BUFFERS) / (numGPUs * cpdDrawCommBatchSize)) {
	         case 0:
	 	     redistributedStreamAddress[0][GPU_MOD((subReg - MAX_STREAM_BUFFERS), cpdDrawCommBatchSize)] = data.uintVal; 
	             break;
	         case 1:
	 	     p2gMappingAddress[0][GPU_MOD((subReg - MAX_STREAM_BUFFERS), cpdDrawCommBatchSize)] = data.uintVal; 
	             break;
	         case 2:
	 	    GPU_ASSERT(
	 	        if (!runahead)
	 		    panic("PrimitiveExchanger", "processRegisterWrite", "Invalid Stream ID for primitive redistribution.");
	 	    )

	 	     redistributedStreamAddress[1][GPU_MOD((subReg - MAX_STREAM_BUFFERS), cpdDrawCommBatchSize)] = data.uintVal; 
	             break;
	         case 3:
	 	    GPU_ASSERT(
	 	        if (!runahead)
	 		    panic("PrimitiveExchanger", "processRegisterWrite", "Invalid Stream ID for primitive mapping.");
	 	    )

	 	     p2gMappingAddress[1][GPU_MOD((subReg - MAX_STREAM_BUFFERS), cpdDrawCommBatchSize)] = data.uintVal; 
	             break;
	         default: 
	             panic("PrimitiveExchanger", "processRegisterWrite", "Invalid stream ID.");
	     }

	     break;

	 default:
	     panic("PrimitiveExchanger", "processRegisterWrite", "Unsupported register.");
    }
}

void PrimitiveExchanger::processMapperMemoryTransaction(MemoryTransaction *memTrans)
{
    switch(memTrans->getCommand())
    {
        case MT_STATE:
	    mapperMemState = memTrans->getState();
	    break;
	case MT_READ_DATA:
	    panic("PrimitiveExchanger", "processMapperMemoryTransaction", "Mapper only stores mapped results.");
	    break;
	default:
	    panic("PrimitiveExchanger", "processMapperMemoryTransaction", "Unsupported memory transaction.");
	    break;
    }
    delete memTrans;
}

void PrimitiveExchanger::processSyncerMemoryTransaction(MemoryTransaction *memTrans)
{
    switch(memTrans->getCommand())
    {
        case MT_STATE:
	    syncerMemState = memTrans->getState();
	    break;
	case MT_READ_DATA:
	    GPU_ASSERT (
	        if (syncerReadTransCycles != 0)
                    panic("PrimitiveExchanger", "processSyncerMemoryTransaction", "Recieved memory transaction while bus was still busy.");		
	        if (syncerMemReorder.count(memTrans->getID()) == 0)
		    panic("PrimitiveExchanger", "processSyncerMemoryTransaction", "No record for this memTrans.");
	        if (mappedInfoReadBuffer[syncerMemReorder[memTrans->getID()]].received != 0)
	            panic("PrimitiveExchanger", "processSyncerMemoryTransaction", "The destination has received data.");
	        if (mappedInfoReadBuffer[syncerMemReorder[memTrans->getID()]].size != memTrans->getSize())
	            panic("PrimitiveExchanger", "processSyncerMemoryTransaction", "Received data size does not match with request.");
	        if (mappedInfoReadBuffer[syncerMemReorder[memTrans->getID()]].addr != memTrans->getAddress())
	            panic("PrimitiveExchanger", "processSyncerMemoryTransaction", "Received data address does not match with request.");
	    )

            mappedInfoReadBuffer[syncerMemReorder[memTrans->getID()]].received = memTrans->getSize();
	    syncerMemReorder.erase(memTrans->getID());
	    syncerReadTransCycles = memTrans->getBusCycles();

	    break;
	default:
	    panic("PrimitiveExchanger", "processSyncerMemoryTransaction", "Unsupported memory transaction.");
	    break;
    }
    delete memTrans;
}

u32bit PrimitiveExchanger::getTriangleCount(PrimitiveMode primitive, u32bit vertexCount)
{
    u32bit numTriangles = 0;

    if (vertexCount == 0) return 0;

    switch (primitive) {
        case TRIANGLE:
	    GPU_ASSERT(
	        if (GPU_MOD(vertexCount, 3) != 0)
		    panic("PrimitiveExchanger", "getTiangleCount", "Invalid vertex count for TRIANGLE.");
	    )

            numTriangles = vertexCount / 3;
	    break;
	case TRIANGLE_STRIP:
	    GPU_ASSERT(
	        if (vertexCount < 3)
		    panic("PrimitiveExchanger", "getTiangleCount", "Invalid vertex count for TRIANGLE_STRIP.");
	    )

	    numTriangles = vertexCount - 2;
	    break;
	case TRIANGLE_FAN:
	    GPU_ASSERT(
	        if (vertexCount < 3)
		    panic("PrimitiveExchanger", "getTiangleCount", "Invalid vertex count for TRIANGLE_FAN.");
	    )

	    numTriangles = vertexCount - 2;
	    break;
	case QUAD:
	    GPU_ASSERT(
	        if (GPU_MOD(vertexCount, 4) != 0)
		    panic("PrimitiveExchanger", "getTiangleCount", "Invalid vertex count for QUAD.");
	    )

            numTriangles = (vertexCount / 4) * 2;
	    break;
        case QUAD_STRIP:
	    GPU_ASSERT(
	        if (vertexCount < 4 || GPU_MOD(vertexCount, 2) != 0)
		    panic("PrimitiveExchanger", "getTiangleCount", "Invalid vertex count for QUAD_STRIP.");
	    )

	    numTriangles = (vertexCount/2 -1) * 2;
	    break;
	default:
	    panic("PrimtiveExchanger", "getTriangleCount", "Unsupported primitive mode.");
    }

    return numTriangles;
}

void PrimitiveExchanger::getState(std::string &stateString) {
    std::stringstream stateStream;

    stateStream.clear();

    stateStream << " state = ";

    switch(state)
    {
        case PE_RESET:
            stateStream << "PE_RESET";
            break;
        case PE_READY:
            stateStream << "PE_READY";
            break;
        case PE_DRAW:
            stateStream << "PE_DRAW";
            break;
        case PE_END:
            stateStream << "PE_END";
            break;
        default:
            stateStream << "undefined";
            break;
    }

    stateString.assign(stateStream.str());
}

void PrimitiveExchanger::setPtrOfExchangedIndexesInGPUpd(exchangedIndexesInGPUpd_t *ptr)
{
    exchangedIndexesInGPUpd = ptr;
}
