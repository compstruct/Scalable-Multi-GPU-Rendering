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
 * $RCSfile: GenericROP.h,v $
 * $Revision: 1.7 $
 * $Author: vmoya $
 * $Date: 2007-12-17 19:54:58 $
 *
 * Generic ROP box definition file.
 *
 */

/**
 *
 *  @file GenericROP.h
 *
 *  This file defines the Generic ROP box.
 *
 *  This class implements a Generic ROP pipeline that will be used to implement
 *  the Z Stencil and Color Write stages of the GPU.
 *
 */


#ifndef _GENERICROP_

#define _GENERICROP_

#include "GPUTypes.h"
#include "support.h"
#include "Box.h"
#include "ROPCache.h"
#include "GPU.h"
#include "RasterizerState.h"
#include "RasterizerCommand.h"
#include "MemoryControllerDefs.h"
#include "FragmentInput.h"
#include "FragmentOpEmulator.h"
#include "RasterizerEmulator.h"
#include "toolsQueue.h"
#include "PixelMapper.h"
#include "GPUDriver.h"
#include <queue>

namespace gpu3d
{

/**
 *
 *  Defines a Generic ROP Queue entry.
 *
 *  A Generic ROP queue entry stores information related with a fragment stamp
 *  that must be processed.
 *
 *  The generic information includes the memory address from a buffer associated
 *  with the stamp, the a way, line and offset inside the ROP cache and the array
 *  storing the fragments in the stamp.
 *
 */

class ROPQueue
{

public:

    u32bit address[MAX_RENDER_TARGETS]; /**<  Adddres in the buffer where to store the stamp fragments.  */
    u32bit way[MAX_RENDER_TARGETS];     /**<  Way of the ROP cache where to store the stamp.  */
    u32bit line[MAX_RENDER_TARGETS];    /**<  Line of the ROP cache where to store the stamp.  */
    u32bit offset[MAX_RENDER_TARGETS];
    FragmentInput **stamp;              /**<  Pointer to the fragments in the stamp.  */
    bool culled[STAMP_FRAGMENTS];       /**<  Array of cull flags for each fragment in the stamp.  */
    bool lastStamp;                     /**<  Flag that stores if the current stamp is the last in a batch.  */
    u8bit *data;                        /**<  Buffer for storing data to be read or written for the stamp.  */
    bool *mask;                         /**<  Stores the write mask for the stamp. */
    u32bit nextSample;                  /**<  Stores an index to the next group of samples to process for MSAA.  */
    u32bit nextBuffer;                  /**<  Stores an index to the next buffer to process.  */
    u32bit nextCompFetchBuffer;
    u32bit nextCompReadBuffer;
};


/**
 *
 *  Defines the state reported by the ROP unit to the producer stage/unit in the GPU pipeline
 *  that is sending stamps to the ROP stage.
 *
 */

enum ROPState
{
    ROP_READY,      /**<  ROP can receive stamps.  */
    ROP_BUSY        /**<  ROP can not receive stamps.  */
};

/**
 *
 *  This class implements the simulation of the pipeline of a generic ROP stage.
 *  The Generic ROP class is to be used to derive the specific ROP stages
 *  Z Stencil Test and Color Write of the GPU pipeline.
 *
 *  This class inherits from the Box class that offers basic simulation support.
 *
 */

class GenericROP : public Box
{
private:

    /*  Generic ROP rate and latency parameters.  */
    u32bit stampsCycle;         /**<  Number of stamps that can be received per cycle.  */
    u32bit ropRate;             /**<  Rate at which stamps are operated (minimum cycles between two stamps).  */
    u32bit ropLatency;          /**<  ROP operation latency in cycles.  */

    /*  Generic ROP queue parameters.  */
    u32bit inQueueSize;         /**<  Size of the input stamp queue.  */
    u32bit fetchQueueSize;      /**<  Size of the fetched stamp queue.  */
    u32bit readQueueSize;       /**<  Size of the read stamp queue.  */
    u32bit opQueueSize;         /**<  Size of the operation stamp queue.  */
    u32bit writeQueueSize;      /**<  Size of the written stamp queue.  */
    u32bit syncInQueueSize;
    u32bit syncFetchQueueSize;
    u32bit syncReadQueueSize;
    u32bit syncQueueSize;

    /*  Generic ROP stage name.*/
    char *ropName;              /**<  Name of the ROP stage.  */
    char *ropShortName;         /**<  Short name/abbreviature for the specific ROP stage.  */

    /*  Generic ROP state.  */
    MemState memoryState;       /**<  Current memory controller state.  */
    bool receivedFragment;      /**<  If a fragment has been received in the current cycle.  */

    /*  Generic ROP counters.  */
    u32bit ropCycles;           /**<  Cycles until the next stamp can be operated.  */
    u32bit inputCycles;         /**<  Cycles until the next input can be received.  */

    //  ROP CAM for RAW dependence detection.
    std::vector<ROPQueue*> rawCAM;      /**<  Vector that stores pointers to the stamps that are being processed after the read stage and before the write stage for RAW dependence detection .  */
    u32bit sizeCAM;                     /**<  Number of entries in the read non-written stamp CAM.  */
    u32bit stampsCAM;                   /**<  Number of stamps in the read non written stamp CAM.  */
    u32bit firstCAM;                    /**<  Pointer to the first entry in the read non written stamp CAM.  */
    u32bit freeCAM;                     /**<  Pointer to the next free entry in the read non-written stamp CAM.  */

    /*  Configurable buffers.  */
    FragmentInput **stamp;      /**<  Stores last receveived stamp.  */

    /*  Statistics.  */
    GPUStatistics::Statistic *inputs;       /**<  Input fragments.  */
    GPUStatistics::Statistic *operated;     /**<  Operated fragments.  */
    GPUStatistics::Statistic *outside;      /**<  Outside triangle/viewport fragments.  */
    GPUStatistics::Statistic *culled;       /**<  Culled for non test related reasons.  */
    GPUStatistics::Statistic *readTrans;    /**<  Read transactions to memory.  */
    GPUStatistics::Statistic *writeTrans;   /**<  Write transactions to memory.  */
    GPUStatistics::Statistic *readBytes;    /**<  Bytes read from memory.  */
    GPUStatistics::Statistic *writeBytes;   /**<  Bytes written to memory.  */
    GPUStatistics::Statistic *fetchOK;      /**<  Succesful fetch operations.  */
    GPUStatistics::Statistic *fetchFail;    /**<  Failed fetch operations.  */
    GPUStatistics::Statistic *allocateOK;   /**<  Succesful allocate operations.  */
    GPUStatistics::Statistic *allocateFail; /**<  Failed allocate operations.  */
    GPUStatistics::Statistic *readOK;       /**<  Sucessful read operations.  */
    GPUStatistics::Statistic *readFail;     /**<  Failed read operations.  */
    GPUStatistics::Statistic *writeOK;      /**<  Sucessful write operations.  */
    GPUStatistics::Statistic *writeFail;    /**<  Failed write operations.  */
    GPUStatistics::Statistic *rawDep;       /**<  Blocked read accesses because of read after write dependence between stamps.  */
    GPUStatistics::Statistic *ropOpBusy;    /**<  Counts cycles in which the ROP Operator is busy and can not start processing a new stamp.  */
    GPUStatistics::Statistic *consumerBusy; /**<  Counts cycles in which the consumer stage is busy and can not receive processeds tamps from the Generic ROP.  */
    GPUStatistics::Statistic *inputEmpty;   /**<  Counts unused cycles when the input queue is empty.  */
    GPUStatistics::Statistic *fetchEmpty;   /**<  Counts unused cycles when the fetch queue is empty.  */
    GPUStatistics::Statistic *readEmpty;    /**<  Counts unused cycles when the read queue is empty.  */
    GPUStatistics::Statistic *opEmpty;      /**<  Counts unused cycles when the operated queue is empty.  */
    GPUStatistics::Statistic *writeEmpty;   /**<  Counts unused cycles when the written queue is empty.  */
    GPUStatistics::Statistic *fetchFull;    /**<  Counts stall cycles when fetch stamp queue is full.  */
    GPUStatistics::Statistic *readFull;     /**<  Counts stall cycles when read stamp queue is full.  */
    GPUStatistics::Statistic *opFull;       /**<  Counts stall cycles when operation stamp queue is full.  */
    GPUStatistics::Statistic *writeFull;    /**<  Counts stall cycles when written stamp queue is full.  */
    GPUStatistics::Statistic *numDummyFrags;

    GPUStatistics::Statistic *globalInputs;       /**<  Input fragments.  */
    GPUStatistics::Statistic *globalOperated;     /**<  Operated fragments.  */
    GPUStatistics::Statistic *globalOutside;      /**<  Outside triangle/viewport fragments.  */
    GPUStatistics::Statistic *globalCulled;       /**<  Culled for non test related reasons.  */
    GPUStatistics::Statistic *globalReadTrans;    /**<  Read transactions to memory.  */
    GPUStatistics::Statistic *globalWriteTrans;   /**<  Write transactions to memory.  */
    GPUStatistics::Statistic *globalReadBytes;    /**<  Bytes read from memory.  */
    GPUStatistics::Statistic *globalWriteBytes;   /**<  Bytes written to memory.  */
    GPUStatistics::Statistic *globalFetchOK;      /**<  Succesful fetch operations.  */
    GPUStatistics::Statistic *globalFetchFail;    /**<  Failed fetch operations.  */
    GPUStatistics::Statistic *globalAllocateOK;   /**<  Succesful allocate operations.  */
    GPUStatistics::Statistic *globalAllocateFail; /**<  Failed allocate operations.  */
    GPUStatistics::Statistic *globalReadOK;       /**<  Sucessful read operations.  */
    GPUStatistics::Statistic *globalReadFail;     /**<  Failed read operations.  */
    GPUStatistics::Statistic *globalWriteOK;      /**<  Sucessful write operations.  */
    GPUStatistics::Statistic *globalWriteFail;    /**<  Failed write operations.  */
    GPUStatistics::Statistic *globalRawDep;       /**<  Blocked read accesses because of read after write dependence between stamps.  */
    GPUStatistics::Statistic *globalRopOpBusy;    /**<  Counts cycles in which the ROP Operator is busy and can not start processing a new stamp.  */
    GPUStatistics::Statistic *globalConsumerBusy; /**<  Counts cycles in which the consumer stage is busy and can not receive processeds tamps from the Generic ROP.  */
    GPUStatistics::Statistic *globalInputEmpty;   /**<  Counts unused cycles when the input queue is empty.  */
    GPUStatistics::Statistic *globalFetchEmpty;   /**<  Counts unused cycles when the fetch queue is empty.  */
    GPUStatistics::Statistic *globalReadEmpty;    /**<  Counts unused cycles when the read queue is empty.  */
    GPUStatistics::Statistic *globalOpEmpty;      /**<  Counts unused cycles when the operated queue is empty.  */
    GPUStatistics::Statistic *globalWriteEmpty;   /**<  Counts unused cycles when the written queue is empty.  */
    GPUStatistics::Statistic *globalFetchFull;    /**<  Counts stall cycles when fetch stamp queue is full.  */
    GPUStatistics::Statistic *globalReadFull;     /**<  Counts stall cycles when read stamp queue is full.  */
    GPUStatistics::Statistic *globalOpFull;       /**<  Counts stall cycles when operation stamp queue is full.  */
    GPUStatistics::Statistic *globalWriteFull;    /**<  Counts stall cycles when written stamp queue is full.  */
    GPUStatistics::Statistic *globalNumDummyFrags;

    /*  Private functions.  */

    /**
     *
     *  Processes a memory transaction.
     *
     *  @param cycle The current simulation cycle.
     *  @param memTrans The memory transaction to process
     *
     */

    void processMemoryTransaction(u64bit cycle, MemoryTransaction *memTrans);


    /**
     *
     *  Processes the stamp that has been just received.
     *  If the stamp can not be culled it's added to the input stamp queue.
     *
     */

    void processStamp(u64bit cycle);


    /**
     *
     *  Tries to write data for an operated stamp that is in the head of the operation
     *  stamp queue.
     *  If the operation is succesful the stamp is moved to the written stamp queue.
     *
     */

    void writeStamp(u64bit cycle);

    /**
     *
     *  Terminate the processing the current written stamp and remove it from the pipeline.
     *
     *  @param cycle Current simulation cycle.
     *
     */

    void terminateStamp(u64bit cycle);

protected:

    u32bit numGPUs;
    u32bit multiGPUExecMode;
    u32bit stampId;
    u32bit interGPUBusWidth;
    u32bit interGPUBusLat;
    bool profileForSortLast;
    bool compSchedEnabled;

    u32bit syncCommQueueSzPerGPU;
    RasterizerSyncCommand*** syncCommQueue;
    u32bit* numSyncCommQueueFreeEntries;
    u32bit* nextSyncRead;
    u32bit* nextSyncWrite;
    u32bit nextSyncGPUID;
    u32bit numSyncedGPUs;
    u32bit memoryCycles;
    u32bit nextWriteTicket;
    u32bit* numReceived;
    u32bit* numProcessed;

    /*  Generic ROP signals.  */
    Signal *rastCommand;        /**<  Command signal from the Rasterizer main box.  */
    Signal *rastState;          /**<  State signal to the Rasterizer main box.  */
    Signal *inFragmentSignal;   /**<  Fragment input signal from GPU stage/unit producing fragments for the ROP stage.  */
    Signal *syncInFragmentSignal;
    Signal *outFragmentSignal;  /**<  Fragment output signal to the GPU stage/unit consuming fragments from the ROP stage.  */
    Signal *syncOutFragmentSignal;
    Signal *ropStateSignal;     /**<  State signal to the GPU stage/unit producing fragments for the ROP stage.  */
    Signal *ropSyncStateSignal;
    Signal *consumerStateSignal;/**<  State signal from the GPU stage/unit consuming fragments from the ROP stage.  */
    Signal *consumerSyncStateSignal;
    Signal *memRequest;         /**<  Memory request signal to the Memory Controller.  */
    Signal *memData;            /**<  Memory data signal from the Memory Controller.  */
    Signal *operationStart;     /**<  Start signal for the simulation of the ROP operation latency.  */
    Signal *operationEnd;       /**<  End signal for the simulation of the ROP operation latency.  */

    Signal **interGPUSync;
    Signal **interGPUSyncBackPressure;

    /*  Generic ROP registers.  */
    u32bit hRes;                                /**<  Display horizontal resolution.  */
    u32bit vRes;                                /**<  Display vertical resolution.  */
    s32bit startX;                              /**<  Viewport initial x coordinate.  */
    s32bit startY;                              /**<  Viewport initial y coordinate.  */
    u32bit width;                               /**<  Viewport width.  */
    u32bit height;                              /**<  Viewport height.  */
    u32bit bufferAddress[MAX_RENDER_TARGETS];   /**<  Start address in memory of the current ROP buffer.  */
    u32bit stateBufferAddress;                  /**<  Start address in memory of the current ROP block state buffer.  */
    bool multisampling;                         /**<  Flag that stores if MSAA is enabled.  */
    u32bit msaaSamples;                         /**<  Number of MSAA Z samples generated per fragment when MSAA is enabled.  */
    u32bit bytesPixel[MAX_RENDER_TARGETS];      /**<  Bytes per fragment/pixel.  */
    bool compression;                           /**<  Flag to enable or disable buffer compression.  */

    /*  Generic ROP buffer parameters.  */
    u32bit displayW;            /**<  Display tile width in scan tiles.  */
    u32bit displayH;            /**<  Display tile height in scan tiles.  */
    u32bit overW;               /**<  Over scan tile width in scan tiles.  */
    u32bit overH;               /**<  Over scan tile height in scan tiles.  */
    u32bit scanW;               /**<  Scan tile width in generation tiles.  */
    u32bit scanH;               /**<  Scan tile height in generation tiles.  */
    u32bit genW;                /**<  Generation tile width in stamps.  */
    u32bit genH;                /**<  Generation tile height in stamps.  */

    u32bit overSyncX;
    u32bit overSyncY;
    u32bit scanSyncX;
    u32bit scanSyncY;
    u32bit genSyncX;
    u32bit genSyncY;
    u32bit stampSyncX;
    u32bit stampSyncY;
    u32bit generatedStamps;
    static std::vector<std::vector<bool> > allStampsReadForSync;
    static std::vector<std::vector<bool> > allStampsSentForSync;
    static std::vector<u32bit> nextSyncReadingGPU;
    u32bit notLastSyncSent;
    u32bit notLastSyncReceive;
    bool bypassZST;
    bool bypassCW;
    bool readDataROPForComp;
    kdTreeInfo kdInfo;

    u32bit numStampUnits;

    u32bit bufferAddressForComp[MAX_RENDER_TARGETS]; // render targets for image composition
    
    /*  Reference to the ROP emulator classes.  */
    FragmentOpEmulator &frEmu;  /**<  Reference to the fragment operation emulator object.  */

    //  Pixel mapper.
    bool activeBuffer[MAX_RENDER_TARGETS];          /**< Defines if an output buffer is active.  */
    u32bit numActiveBuffers;                        /**< Number of output buffers active.  */
    PixelMapper pixelMapper[MAX_RENDER_TARGETS];    /**< Maps pixels to memory addresses and processing units.  */
    
    /*  Generic ROP state.  */
    RasterizerState state;                  /**<  Current box state.  */
    ROPState consumerState;                 /**<  Current state of the consumer state that receives fragments processed by the ROP stage.  */
    ROPState consumerSyncState;
    u32bit currentTriangle;                 /**<  Identifier of the current triangle being processed (used to count triangles).  */
    bool endFlush;                          /**<  Flag that signals the end of the ROP cache flush.  */
    bool bypassROP[MAX_RENDER_TARGETS];     /**<  Bypass flag, set to true if the stamp must bypass the ROP stage without processing.  */
    bool readDataROP[MAX_RENDER_TARGETS];   /**<  Read data flag, set to true if the stamp has to read data from the buffer before processing.  */
    bool lastFragment;                      /**<  Last batch fragment flag.  */

    /*  Generic ROP Last Stamp container.  */
    ROPQueue lastBatchStamp;    /**<  Stores the information about the last batch stamp.  */

    /*  Generic ROP counters.  */
    u32bit triangleCounter;     /**<  Number of processed triangles.  */
    u32bit fragmentCounter;     /**<  Number of fragments processed in the current batch.  */
    u32bit frameCounter;        /**<  Counts the number of rendered frames.  */
    u32bit batchCounter;

    /*  ROP queues.  */
    tools::Queue<ROPQueue*> freeQueue;  /**<  Stores free ROPQueue entry objects.  */
    tools::Queue<ROPQueue*> inQueue;    /**<  Input stamp queue.  Stores stamps received from a previous GPU stage.  */
    tools::Queue<ROPQueue*> fetchQueue; /**<  Fetched stamp queue.  Stores stamps for which data has been fetched from memory.  */
    tools::Queue<ROPQueue*> readQueue;  /**<  Read stamp queue.   Stores stamps for which data has been read from memory.  */
    tools::Queue<ROPQueue*> opQueue;    /**<  Operation stamp queue.  Stores stamps that have finished the ROP operation.  */
    tools::Queue<ROPQueue*> writeQueue; /**<  Write stamp queue.  Stores stamps for which data has been written into memory.  */
    
    tools::Queue<ROPQueue*> syncInQueue;
    tools::Queue<ROPQueue*> syncFetchQueue;
    tools::Queue<ROPQueue*> syncReadQueue;
    tools::AddressableQueue<ROPQueue*> syncQueue;
    
    //tools::Queue<ROPQueue*> *currInQueue;
    //tools::Queue<ROPQueue*> *currFetchQueue;
    //tools::Queue<ROPQueue*> *nextInQueue;
    //tools::Queue<ROPQueue*> *nextFetchQueue;
    tools::GenericQueue *currInQueue;
    tools::GenericQueue *currFetchQueue;
    tools::GenericQueue *nextInQueue;
    tools::GenericQueue *nextFetchQueue;

    std::queue<u32bit> compTerminatingPoses;
    std::queue<u32bit> compFetchingPoses;
    std::queue<u32bit> compReadingPoses;
    
    /*  ROP cache and associated constants.  */
    ROPCache *ropCache;         /**<  Pointer to the ROP cache.  */
    u32bit stampMask;           /**<  Logical mask for the offset of a stamp inside a ROP cache line.  */

    GPUStatistics::Statistic *totFrags;
    
    GPUStatistics::Statistic *globalTotFrags;

    /**
     *
     *  Performs any remaining tasks after the stamp data has been written.
     *  The function should read, process and remove the stamp at the head of the
     *  written stamp queue.
     *
     *  This function is a pure virtual function and must be implemented by all the
     *  derived classes.
     *
     *  @param cycle Current simulation cycle.
     *  @param stamp Pointer to a stamp that has been written to the ROP data buffer
     *  and needs processing.
     *
     */

    virtual void postWriteProcess(u64bit cycle, ROPQueue *stamp) = 0;

    /**
     *
     *  To be called after calling the update/clock function of the ROP Cache.
     *
     *  This function is a pure virtual function and must be implemented by all the
     *  derived classes.
     *
     *  @param cycle Current simulation cycle.
     *
     */

    virtual void postCacheUpdate(u64bit cycle) = 0;

    /**
     *
     *  This function is called when the ROP stage is in the the reset state.
     *
     *  This function is a pure virtual function and must be implemented by all the
     *  derived classes.
     *
     */

    virtual void reset() = 0;

    /**
     *
     *  This function is called when the ROP stage is in the flush state.
     *
     *  This function is a pure virtual function and must be implemented by all the
     *  derived classes.
     *
     *  @param cycle Current simulation cycle.
     *
     */

    virtual void flush(u64bit cycle) = 0;
    
    /**
     *
     *  This function is called when the ROP stage is in the swap state.
     *
     *  This function is a pure virtual function and must be implemented by all the
     *  derived classes.
     *
     *  @param cycle Current simulation cycle.
     *
     */

    virtual void swap(u64bit cycle) = 0;

    /**
     *
     *  This function is called when the ROP stage is in the clear state.
     *
     *  This function is a pure virtual function and must be implemented by all the
     *  derived classes.
     *
     */

    virtual void clear() = 0;
    
    /**
     *
     *  Receives stamps from a producer stage through the input fragment signal.
     *  Calls the processStamp function if a stamp is received.
     *
     *  @param cycle Current simulation cycle.
     *
     */

    void receiveStamps(u64bit cycle);

    /**
     *
     *  Tries to fetch data for the stamp that is in the head of the input stamp queue.
     *  If succesful the stamp is moved to the fetch queue.
     *
     *  If the bypass flag is enabled the stamp is moved to the written queue queue.
     *
     *  If the read flag is disabled then it tries to allocate space in the write buffer
     *  for the stamp and if the operation is succesful the stamp is moved to the read
     *  stamp queue.
     *
     */

    void fetchStamp(u64bit cycle);

    /**
     *
     *  Tries to read data for the stamp that is in the head of the fetched stamp queue.
     *  If the operation is succesful the stamp is moved to read stamp queue.
     *
     */

    void readStamp(u64bit cycle);
    
    /**
     *
     *  Starts the ROP operation for the stamp in the head of the read stamp queue.
     *  The stamp is sent through the ROP operation latency signal and removed
     *  from the read stamp queue.
     *
     *  @param cycle Current simulation cycle.
     *
     */

    void startOperation(u64bit cycle);

    /**
     *
     *  Ends the ROP operation for a stam.
     *  The stamp is received from the ROP operation latency signal and added to the operation
     *  stamp queue.
     *
     *  @param cycle Current simulation cycle.
     *
     */

    void endOperation(u64bit cycle);

    /**
     *
     *  This function is called when a stamp is received at the end of the ROP operation
     *  latency signal and before it is queued in the operated stamp queue.
     *
     *  This function is a pure virtual function and must be implemented by all the
     *  derived classes.
     *
     *  @param cycle Current Simulation cycle.
     *  @param stamp Pointer to the ROP queue entry for the stamp that has to be operated.
     *
     */

    virtual void operateStamp(u64bit cycle, ROPQueue *stamp) = 0;

    /**
     *
     *  This function is called when all the stamps but the last one have been processed.
     *
     *  This function is a pure virtual function and must be implemented by all the
     *  derived classes.
     *
     *  @param cycle Current simulation cycle.
     *
     */

    virtual void endBatch(u64bit cycle) = 0;

    /**
     *
     *  Processes a rasterizer command.
     *
     *  Pure virtual function.  Must be implemented by all the derived classes.
     *
     *  @param command The rasterizer command to process.
     *  @param cycle Current simulation cycle.
     *
     */

    virtual void processCommand(RasterizerCommand *command, u64bit cycle) = 0;

    /**
     *
     *  Processes a register write.
     *
     *  Pure virtual function.  Must be implemented by all the derived classes.
     *
     *  @param reg The ROP stage register to write.
     *  @param subreg The register subregister to writo to.
     *  @param data The data to write to the register.
     *
     */

    virtual void processRegisterWrite(GPURegister reg, u32bit subreg, GPURegData data) = 0;

    /**
     *
     * Inter-GPU synchronization
     *
     */
    
    virtual void sync(u64bit cycle, MemState memState) = 0;
    virtual void blit(u64bit cycle) = 0;
    
    virtual void clearForComp(u64bit cycle) = 0;
    virtual void comp(u64bit cycle) = 0; 
    virtual void generateCompFragments(u64bit cycle, ROPQueue *stamp) = 0;
    virtual void postCompWriteProcess(u64bit cycle, ROPQueue *stamp) = 0;

    void readStampForOtherGPUs(u64bit cycle, u32bit displayGPUId);
    void fetchCompStamp(u64bit cycle);
    void readCompStamp(u64bit cycle);
    void writeCompStamp(u64bit cycle);
    void terminateCompStamp(u64bit cycle);

public:

    /**
     *
     *  Generic ROP box constructor.
     *
     *  Creates and initializes a new Generic ROP box object.
     *
     *  @param stampsCycle Number of stamps per cycle.
     *  @param operationRate Rate at which stamp are operated (cycles between two stamps that are operated by the ROP).
     *  @param operationLatency ROP operation latency in cycles.
     *
     *  @param overW Over scan tile width in scan tiles (may become a register!).
     *  @param overH Over scan tile height in scan tiles (may become a register!).
     *  @param scanW Scan tile width in fragments.
     *  @param scanH Scan tile height in fragments.
     *  @param genW Generation tile width in fragments.
     *  @param genH Generation tile height in fragments.
     *
     *
     *  @param inQSz Input stamp queue size (in entries/stamps).
     *  @param fetchQSz Fetched stamp queue size (in entries/stamps).
     *  @param readQSz Read stamp queue size (in entries/stamps).
     *  @param opQSz Operated stamp queue size (in entries/stamps).
     *  @param writeQSz Written stamp queue size (in entries/stamps).
     *
     *  @param frEmu Reference to the Fragment Operation Emulator object.
     *
     *  @param ropName Name of the ROP stage.
     *  @param ropShortName Shorter/abbreviature of the ROP stage name.
     *  @param name The box name.
     *  @param prefix String used to prefix the box signals names.
     *  @param parent The box parent box.
     *
     *  @return A new Generic Box object.
     *
     */

    GenericROP(

	u32bit gpuId, u32bit numGPUs, u32bit multiGPUExecMode, u32bit stampId,
        //  Rate and latency parameters
        u32bit stampsCycle, u32bit operationRate, u32bit operationLatency,

        //  ROP buffer parameters
        u32bit displayW, u32bit displayH, u32bit overW, u32bit overH, u32bit scanW, u32bit scanH, u32bit genW, u32bit genH,

	u32bit numStampUnits,

        //  ROP queue parameters
        u32bit inQSz, u32bit fetchQSz, u32bit readQSz, u32bit opQSz, u32bit writeQSz,

        //  Emulator classes associated with the Generic ROP pipeline
        FragmentOpEmulator &frOp, u32bit syncCommQueueSize,

	u32bit syncInQSz, u32bit syncFetchQSz, u32bit syncReadQSz,

	u32bit interGPUBusWidth, u32bit interGPUBusLat,

	bool profileForSortLast, bool compSchedEnabled,

        //  Other parameters
        char *ropName, char *ropShortName, char *name, char *prefix = 0, Box* parent = 0);

    /**
     *
     *  Generic ROP simulation function.
     *
     *  Simulates a cycle of the Generic ROP box.
     *
     *  @param cycle The cycle to simulate of the Generic ROP box.
     *
     */

    void clock(u64bit cycle);

    /**
     *
     *  Returns a single line string with state and debug information about the
     *  Generic ROP box.
     *
     *  @param stateString Reference to a string where to store the state information.
     *
     */

    void getState(string &stateString);

    /**
     *
     *  Writes into a string a report about the stall condition of the box.
     *
     *  @param cycle Current simulation cycle.
     *  @param stallReport Reference to a string where to store the stall state report for the box.
     *
     */
     
    void stallReport(u64bit cycle, string &stallReport);
    
};

} // namespace gpu3d

#endif

