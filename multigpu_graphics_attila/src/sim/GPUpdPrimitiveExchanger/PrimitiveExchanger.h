/**
 *
 * @file PrimitiveClipper.h
 *
 * Define the PrimitiveClipper box class.
 *
 * This class simulates the primitive redistribution in GPUpd (Micro 2017).
 *
 */
 
#ifndef _PRIMITIVEEXCHANGER_

#define _PRIMITIVEEXCHANGER_

#include "Box.h"
#include "GPU.h"
#include "PrimitiveExchangerCommand.h"
#include "support.h"
#include "TriangleSetupInput.h"
#include "MemoryTransaction.h"
#include "PrimitiveExchangerEmulator.h"

namespace gpu3d
{

enum PrimitiveExchangerState
{
    PE_RESET,
    PE_READY,
    PE_DRAW,
    PE_END
};

struct MappedInfoBufferEntry
{
    bool last;
    u32bit size;
    u32bit addr;
    u32bit received;
    u32bit processed;
    u8bit *data;
};

struct ExchangedIndexBufferEntry
{
    bool last;
    u32bit srcGPU;
    u32bit batchId;
    u32bit index;
};

class PrimitiveExchanger : public Box
{

private:
    Signal *primitiveExchangerCommand;          // Command signal from CommandProcessor
    Signal *primitiveExchangerState;            // State signal to CommandProcessor
    Signal *primitiveExchangerMappedDrawComms;  // Signal to tell command processor that some draw commands have finished 
    Signal *primitiveExchangerSyncedDrawComms;  // Signal to tell command processor that some draw commands have finished 
    Signal *primitiveExchangerInput;            // Input to PrimitiveExchanger
    Signal *primitiveExchangerRequest;          // Request signal to Clipper in execution round 1 of GPUPD
    Signal *primitiveMappingStart;              // Start signal to PrimitiveExchanger
    Signal *primitiveMappingEnd;                // End signal from PrimitiveExchanger
    Signal *mapperMemoryRequest;                // Store mapped results to memory
    Signal *mapperMemoryData;                   // Get memory state for storing mapped results
    Signal *syncerMemoryRequest;                // Request mapped results for redistribution
    Signal *syncerMemoryData;                   // Memory reply of mapped results for redistribution
    Signal **indexExchangeOut;
    Signal **indexExchangeIn;

    u32bit numGPUs;
    u32bit multiGPUExecMode;
    u32bit execRound;
    bool runahead;
    u32bit interGPUBusWidth;
    u32bit interGPUBusLat;

    u32bit trianglesCycle;
    u32bit primitiveExchangerUnits;
    u32bit p2gMappingLat;
    u32bit startLatency;

    PrimitiveExchangerState state;
    PrimitiveExchangerCommand *lastPECommand;

    u32bit cpdDrawCommBatchSize;
    std::vector<u32bit> redistributedStreamAddress[2];
    std::vector<u32bit> p2gMappingAddress[2];
    std::vector<u32bit> mappedTrianglesPerBatch[2];
    std::vector<u32bit> sizeOfStoredIndexes[2];

    static bool underSyncing;
    
    u32bit drawCommsInPE;
    u32bit mappedDrawComms;
    u32bit syncedDrawComms;
    u32bit exchangedDrawComms;
    bool swapCommReceived;
    u32bit interGPUSyncTransCycles;

    u32bit peCycles;
    u32bit peTriangleInputBufferSize;
    TriangleSetupInput **peTriangleInputBuffer;
    u32bit nextTriangleInputFreeEntry;
    u32bit nextMappedTriangle;
    u32bit mappedTriangles;
    u32bit reservedEntries;

    u32bit currentBatch;
    u32bit currentFrame;

    MemState mapperMemState;
    u32bit currentMappedBatch;
    u32bit sizeOfStoredMappedInfo;
    u32bit mapperStoreTransCycles;
    u32bit mapperCurrentTicket;
    u32bit mapperFreeTickets;

    MemState syncerMemState;
    u32bit currentSyncedBatch;
    u32bit sizeOfReadMappedInfo;
    u32bit syncerReadTransCycles;
    u32bit syncerStoreTransCycles;
    u32bit syncerCurrentTicket;
    u32bit syncerFreeTickets;

    u32bit mappedInfoReadBufferSize;
    u32bit freeMappedInfoReadBufferEntries;
    u32bit receivedMappedInfoEntries;
    u32bit nextMappedInfoReadEntry;
    std::vector<MappedInfoBufferEntry> mappedInfoReadBuffer;

    u32bit currentExchangedBatch;
    u32bit nextMappedInfoExchangeEntry;
    u32bit exchangedGPUs;
   
    std::vector<u32bit> exchangedIndexWriteSize[2];
    u8bit** exchangedIndexWriteCoalescer[2]; 
    u32bit exchangedIndexBufferSize;
    u32bit nextExchangedIndexRecvEntry;
    u32bit nextExchangedIndexStoreEntry;
    u32bit receivedExchangedIndexes;
    static std::vector<u32bit> freeExchangedIndexBufferEntries;
    std::vector<ExchangedIndexBufferEntry> exchangedIndexBuffer;
    std::map<u32bit, u32bit> syncerMemReorder;

    exchangedIndexesInGPUpd_t *exchangedIndexesInGPUpd;

    u32bit hRes;
    u32bit vRes;
    bool d3d9PixelCoordinates;
    u32bit iniX;
    u32bit iniY;
    u32bit width;
    u32bit height;
    bool scissorTest;
    s32bit scissorIniX;
    s32bit scissorIniY;
    u32bit scissorWidth;
    u32bit scissorHeight;
    u32bit displayWidth;
    u32bit displayHeight;
    u32bit scanWidth;
    u32bit scanHeight;
    PrimitiveExchangerEmulator peEmu;

    class IdealMappedInfoBufferEntry {
	public:
        u32bit v1;
	u32bit v2;
	u32bit v3;
	u32bit gpus;
 
	IdealMappedInfoBufferEntry(u32bit v1_, u32bit v2_, u32bit v3_, u32bit gpus_) {
	    v1 = v1_; v2= v2_; v3 = v3_; gpus = gpus_;
	}
    };

    bool allResultsOnChip;
    std::vector<std::vector<IdealMappedInfoBufferEntry> > idealMappedInfoBuffer[2];

    bool gpupdBatchEnabled;
    u32bit numReceivedTris;
    u32bit gpupdBatchThreshold;
    u32bit currentReceiveGPUpdBatch;
    u32bit currentMapGPUpdBatch;
    u32bit currentExchangeGPUpdBatch;
    u32bit firstDrawCommPerGPUpdBatch[2];
    u32bit numDrawsPerGPUpdBatch[2];
    bool readyToExchange[2];

    GPUStatistics::Statistic *inputs;
    GPUStatistics::Statistic *recvIndexes;
    GPUStatistics::Statistic *inputsMappedToOtherGPUs;
    GPUStatistics::Statistic *inputsMappedToMultipleGPUs;
    GPUStatistics::Statistic *numSentGPUs;
    GPUStatistics::Statistic *syncCycles;
    GPUStatistics::Statistic *backPressureFail;
    GPUStatistics::Statistic *mappedInfoReadFail;
    GPUStatistics::Statistic *sequentialWait;
    GPUStatistics::Statistic *loadImbalanceWait;
    GPUStatistics::Statistic *noFreeMappedInfoReadBufferEntries;
    GPUStatistics::Statistic *interGPUSyncTrafficLoad;

    GPUStatistics::Statistic *globalInputs;
    GPUStatistics::Statistic *globalRecvIndexes;
    GPUStatistics::Statistic *globalInputsMappedToOtherGPUs;
    GPUStatistics::Statistic *globalInputsMappedToMultipleGPUs;
    GPUStatistics::Statistic *globalNumSentGPUs;
    GPUStatistics::Statistic *globalSyncCycles;
    GPUStatistics::Statistic *globalBackPressureFail;
    GPUStatistics::Statistic *globalMappedInfoReadFail;
    GPUStatistics::Statistic *globalSequentialWait;
    GPUStatistics::Statistic *globalLoadImbalanceWait;
    GPUStatistics::Statistic *globalNoFreeMappedInfoReadBufferEntries;
    GPUStatistics::Statistic *globalInterGPUSyncTrafficLoad;

public:
    PrimitiveExchanger(u32bit gpuId, char *gpuPrefix, u32bit numGPUs, u32bit multiGPUExecMode, u32bit execRound, bool runahead,
		       bool gpupdBatchEnabled, u32bit gpupdBatchThreshold, u32bit interGPUBusWidth, u32bit interGPUBusLat,
		       u32bit trCycle, u32bit peUnits, u32bit p2gLat, u32bit startLat, u32bit cpdDrawCommBatchSize,
		       u32bit peTriangleInputBufferSize, u32bit mappedInfoReadBufferSize, u32bit exchangedIndexBufferSize,
		       u32bit displayW, u32bit displayH, u32bit scanW, u32bit scanH, bool allResultsOnChip,
		       char *name, Box *parent);
    ~PrimitiveExchanger();
    void clock(u64bit cycle);
    void processCommand(PrimitiveExchangerCommand *peComm);
    void processRegisterWrite(GPURegister reg, u32bit subReg, GPURegData data);
    void getState(std::string &stateString);
    void processMapperMemoryTransaction(MemoryTransaction *memTrans);
    void processSyncerMemoryTransaction(MemoryTransaction *memTrans);
    u32bit getTriangleCount(PrimitiveMode primitive, u32bit vertexCount);
    void setPtrOfExchangedIndexesInGPUpd(exchangedIndexesInGPUpd_t *ptr);
};

}

#endif
