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
 * $RCSfile: DAC.cpp,v $
 * $Revision: 1.32 $
 * $Author: vmoya $
 * $Date: 2008-03-02 19:09:17 $
 *
 * DAC box implementation file.
 *
 */

 /**
 *
 *  @file DAC.cpp
 *
 *  This file implements the DAC box.
 *
 *  This class implements the DAC box.  Consumes GPU memory
 *  bandwidth for displaying the current color buffer.  Outputs
 *  the color buffer to a file when a swap buffer signal is
 *  received.
 *
 */

#include "DAC.h"
#include "FragmentInput.h"
#include "RasterizerStateInfo.h"
#include "ColorBlockStateInfo.h"
#include "GPUMath.h"
#include "FragmentOpEmulator.h"
#include "DepthCompressorEmulator.h"
#include "ColorCompressorEmulator.h"
#include "ImageSaver.h"
#include "GPUSimulator.h"

using namespace gpu3d;

u8bit* DAC::colorBuffer = NULL;
u8bit* DAC::zstBuffer = NULL;

bool DAC::writeColorBufferCalled = false;
bool DAC::writeDepthBufferCalled = false;
bool DAC::writeStencilBufferCalled = false;

/*  DAC constructor.  */
DAC::DAC(u32bit gpuId, char *gpuPrefix, u32bit numGPUs_, u32bit multiGPUExecMode_,
    u32bit displayWidth, u32bit displayHeight,
    u32bit overWidth, u32bit overHeight, u32bit scanWidth, u32bit scanHeight,
    u32bit genWidth, u32bit genHeight, u32bit mortonBlockDim, u32bit mortonSBlockDim, 
    u32bit blockSz, u32bit blockLatency, u32bit blocksPerCycle, u32bit blockQSize, u32bit decompLatency, 
    u32bit nStampUnits, char **suPrefixes, u32bit startF, u64bit refresh, bool synched, bool refFrame,
    bool saveBlitSourceData, u32bit syncCommQueueSz, u32bit interGPUBusWidth_, u32bit interGPUBusLat_,
    char *name, Box *parent) :

    stateBlocks(getSM(gpuId).getNumericStatistic("ColorStateBlocksTotal", u32bit(0), "DAC", "DAC")),
    stateBlocksClear(getSM(gpuId).getNumericStatistic("ColorStateBlocksClear", u32bit(0), "DAC", "DAC")),
    stateBlocksUncompressed(getSM(gpuId).getNumericStatistic("ColorStateBlocksUncompressed", u32bit(0), "DAC", "DAC")),
    stateBlocksCompressedBest(getSM(gpuId).getNumericStatistic("ColorStateBlocksCompressedBest", u32bit(0), "DAC", "DAC")),
    stateBlocksCompressedNormal(getSM(gpuId).getNumericStatistic("ColorStateBlocksCompressedNormal", u32bit(0), "DAC", "DAC")),
    stateBlocksCompressedWorst(getSM(gpuId).getNumericStatistic("ColorStateBlocksCompressedWorst", u32bit(0), "DAC", "DAC")),
    interGPUSyncTrafficLoad(getSM(gpuId).getNumericStatistic("InterGPUSyncTrafficLoad", u32bit(0), "DAC", "DAC")),

    globalStateBlocks(getSM().getNumericStatistic("ColorStateBlocksTotal", u32bit(0), "DAC", "DAC")),
    globalStateBlocksClear(getSM().getNumericStatistic("ColorStateBlocksClear", u32bit(0), "DAC", "DAC")),
    globalStateBlocksUncompressed(getSM().getNumericStatistic("ColorStateBlocksUncompressed", u32bit(0), "DAC", "DAC")),
    globalStateBlocksCompressedBest(getSM().getNumericStatistic("ColorStateBlocksCompressedBest", u32bit(0), "DAC", "DAC")),
    globalStateBlocksCompressedNormal(getSM().getNumericStatistic("ColorStateBlocksCompressedNormal", u32bit(0), "DAC", "DAC")),
    globalStateBlocksCompressedWorst(getSM().getNumericStatistic("ColorStateBlocksCompressedWorst", u32bit(0), "DAC", "DAC")),
    globalInterGPUSyncTrafficLoad(getSM().getNumericStatistic("InterGPUSyncTrafficLoad", u32bit(0), "DAC", "DAC")),

    numGPUs(numGPUs_), multiGPUExecMode(multiGPUExecMode_),
    displayW(displayWidth), displayH(displayHeight), overH(overHeight), overW(overWidth),
    scanH((u32bit) ceil(scanHeight / (f32bit) genHeight)),
    scanW((u32bit) ceil(scanWidth / (f32bit) genWidth)), genH(genHeight / STAMP_HEIGHT), genW(genWidth / STAMP_WIDTH),
    blockSize(blockSz), blocksCycle(blocksPerCycle),
    blockStateLatency(blockLatency), blockQueueSize(blockQSize), decompressLatency(decompLatency),
    numStampUnits(nStampUnits), startFrame(startF), refreshRate(refresh), synchedRefresh(synched), refreshFrame(refFrame),
    saveBlitSourceData(saveBlitSourceData), bltTransImpl(*this),
    syncCommQueueSize(syncCommQueueSz), interGPUBusWidth(interGPUBusWidth_), interGPUBusLat(interGPUBusLat_),
    zStencilBufferDefined(true), Box(gpuId, name, parent)

{
    DynamicObject *defaultState[1];
    u32bit i, j;

    /*  Check parameters.  */
    GPU_ASSERT(
        if (overH == 0)
            panic("DAC", "DAC", "Over scan tile height (in scan tiles) must be at least 1.");
        if (overW == 0)
            panic("DAC", "DAC", "Over scan tile width (in scan tiles) must be at least 1.");
        if (scanHeight < genHeight)
            panic("DAC", "DAC", "The scan tile height (in fragments) must be at least the generation tile height.");
        if (scanWidth < genWidth)
            panic("DAC", "DAC", "The scan tile width (in fragments) must be at least the generation tile width.");
        if (scanH == 0)
            panic("DAC", "DAC", "Scan tile height (in generation tiles) must be at least 1.");
        if (scanW == 0)
            panic("DAC", "DAC", "Scan tile width (in generation tiles) must be at least 1.");
        if (genHeight < STAMP_HEIGHT)
            panic("DAC", "DAC", "The generation tile height (in fragments) must be at least the stamp tile height.");
        if (genWidth < STAMP_WIDTH)
            panic("DAC", "DAC", "The generation tile width (in fragments) must be at least the stamp tile width.");
        if (genH == 0)
            panic("DAC", "DAC", "Generation tile height (in stamps) must be at least 1.");
        if (genW == 0)
            panic("DAC", "DAC", "Generation tile width (in stamps) must be at least 1.");
        if (blockSize == 0)
            panic("DAC", "DAC", "The (uncompressed) block size can not be 0.");
        //if (blockSize < (genWidth * genHeight * bytesPixel))
        //    panic("DAC", "DAC", "The (uncompressed) block size must be a multiple of the generation tile size.");
        //if (GPU_MOD(blockSize, (genWidth * genHeight * bytesPixel)) != 0)
        //    panic("DAC", "DAC", "The (uncompressed) block size must be a multiple of the generation tile size.");
        if (blocksCycle == 0)
            panic("DAC", "DAC", "At least one color block state should be updated per cycle.");
        if (blockStateLatency == 0)
            panic("DAC", "DAC", "Block state update signal latency must be at least 1.");
        if (blockQueueSize == 0)
            panic("DAC", "DAC", "Block queue requires at least one entry.");
        if (decompressLatency == 0)
            panic("DAC", "DAC", "Decompress unit latency must be at least 1.");
        if (numStampUnits == 0)
            panic("DAC", "DAC", "At least one stamp pipe required.");
    )

    /*  Create signals.  */

    /*  Create signals with the Command Processor.  */

    /*  Create command signal from Command Processor.  */
    dacCommand = newInputSignal("DACCommand", 1, 1, gpuPrefix);

    /*  Create state signal to Command Processor.  */
    dacState = newOutputSignal("DACState", 1, 1, gpuPrefix);

    /*  Create default signal value.  */
    defaultState[0] = new RasterizerStateInfo(RAST_RESET);

    /*  Set default signal value.  */
    dacState->setData(defaultState);

    /*  Create signals with Memory Controller box.  */

    /*  Create request signal to the Memory Controller.  */
    memoryRequest = newOutputSignal("DACMemoryRequest", 1, 1, gpuPrefix);

    /*  Create data signal from the Memory Controller.  */
    memoryData = newInputSignal("DACMemoryData", 2, 1, gpuPrefix);

    /*  Create signals with Color Write units  */

    /*  Check number of attached Color WRite units.  */
    GPU_ASSERT(
        if (numStampUnits < 1)
            panic("DAC", "DAC", "At least one Color Write unit must be attached.");
        if (suPrefixes == NULL)
            panic("DAC", "DAC", "Color Write prefix array required.");
        for(i = 0; i < numStampUnits; i++)
            if (suPrefixes[i] == NULL)
                panic("DAC", "DAC", "Color Write prefix missing.");
    )


    //  Allocate the signals with the color write units.
    blockStateCW = new Signal*[numStampUnits];

    //  Check allocation.
    GPU_ASSERT(
        if (blockStateCW == NULL)
            panic("DAC", "DAC", "Error allocating array of block state signals from Color Write.");
    )

    //  Create block state signal with all the Color Write units.
    for(i = 0; i < numStampUnits; i++)
    {
        //  Create color buffer block state signal.
        blockStateCW[i] = newInputSignal("ColorBlockState", 1, blockStateLatency, suPrefixes[i]);
    }

    //  Allocate the signals with the z stencil test units.
    blockStateZST = new Signal*[numStampUnits];

    /*  Check allocation.  */
    GPU_ASSERT(
        if (blockStateZST == NULL)
            panic("DAC", "DAC", "Error allocating array of block state signals from Z Stencil Test.");
    )

    //  Create block state signal with all Z Stencil Test units.
    for(i = 0; i < numStampUnits; i++)
    {
        //  Create block state signal with Z Stencil Test unit.
        blockStateZST[i] = newInputSignal("ZStencilBlockState", 1, blockStateLatency, suPrefixes[i]);
    }

    consumedInterGPUbw = 0;
    interGPUSyncTransCycles = 0;

    char signalPrefix[16];
    // Create the inter-GPU colorBuffer sync signals
    colorSync = new Signal*[numGPUs * numStampUnits];
    colorSyncBackPressure = new Signal*[numGPUs * numStampUnits];
    for (i = 0; i < numGPUs; i++) {
        if (i == gpuId) {
	    for (j = 0; j < numStampUnits; j++) {
                colorSync[i*numStampUnits + j] = NULL;	    
                colorSyncBackPressure[i*numStampUnits + j] = NULL;
	    }
        } else {
            for (j = 0; j < numStampUnits; j++) {
                sprintf(signalPrefix, "GPU%dTo%dCW%d", gpuId, i, j);
                colorSync[i*numStampUnits + j] = newOutputSignal("ColorSync", interGPUBusWidth/sizeof(unsigned int),
				                                 interGPUBusLat, signalPrefix);
                sprintf(signalPrefix, "GPU%dCW%dTo%d", i, j, gpuId);
                colorSyncBackPressure[i*numStampUnits + j] = newInputSignal("ColorSyncBackPressure", 1, 1, signalPrefix);
	    }
        }
    }

    // Create the inter-GPU zstBuffer sync signals
    zstSync = new Signal*[numGPUs * numStampUnits];
    zstSyncBackPressure = new Signal*[numGPUs * numStampUnits];
    for (i = 0; i < numGPUs; i++) {
        if (i == gpuId) {
	    for (j = 0; j < numStampUnits; j++) {
                zstSync[i*numStampUnits + j] = NULL;	    
                zstSyncBackPressure[i*numStampUnits + j] = NULL;
            }
        } else {
            for (j = 0; j < numStampUnits; j++) {
                sprintf(signalPrefix, "GPU%dTo%dZST%d", gpuId, i, j);
                zstSync[i*numStampUnits + j] = newOutputSignal("ZStencilSync", interGPUBusWidth/sizeof(unsigned int),
				                               interGPUBusLat, signalPrefix);
                sprintf(signalPrefix, "GPU%dZST%dTo%d", i, j, gpuId);
                zstSyncBackPressure[i*numStampUnits + j] = newInputSignal("ZStencilSyncBackPressure", 1, 1, signalPrefix);
	    }
        }
    }

    numBufferedSyncData = new u32bit[numGPUs];
    nextBufferedSyncData = new u32bit[numGPUs];
    allSyncDataSent = new bool[numGPUs];

    lastSyncCommSent = new bool*[numGPUs];
    numSyncCommQueueFreeEntries = new u32bit*[numGPUs];
    numSent = new u32bit*[numGPUs];
    colorBufferBlockStateSyncComms = new ROPBlockStateSyncCommand**[numGPUs];
    numBlockStateSyncCommQueueFreeEntries = new u32bit[numGPUs];
    numBlockStateSyncCommQueueBackPressures = new u32bit[numGPUs];
    for (i = 0; i < numGPUs; i++) {
	lastSyncCommSent[i] = new bool[numStampUnits];
        numSyncCommQueueFreeEntries[i] = new u32bit[numStampUnits];
	numSent[i] = new u32bit[numStampUnits];
	colorBufferBlockStateSyncComms[i] = new ROPBlockStateSyncCommand*[syncCommQueueSz];
    }

    /*  Calculate the shift bits for block addresses.  */
    blockShift = GPUMath::calculateShift(blockSize);

    /*  Create the block request queue.  */
    blockQueue = new BlockRequest[blockQueueSize];

    /*  Check allocation.  */
    GPU_ASSERT(
        if (blockQueue == NULL)
            panic("DAC", "DAC", "Could not allocate the block request queue.\n");
    )

    /*  Allocate the block buffer.  */
    blockBuffer = new u8bit*[blockQueueSize];

    /*  Check allocation.  */
    GPU_ASSERT(
        if (blockBuffer == NULL)
            panic("DAC", "DAC", "Could not allocate the block buffer.\n");
    )

    /*  Allocate each block buffer.  */
    for (i = 0; i < blockQueueSize; i++)
    {
        /*  Allocate buffer.  */
        blockBuffer[i] = new u8bit[ColorCacheV2::UNCOMPRESSED_BLOCK_SIZE];

        /*  Check allocation.  */
        GPU_ASSERT(
            if (blockBuffer[i] == NULL)
                panic("DAC", "DAC", "Could not allocate block buffer.\n");
        )
    }

    flushedColorStampUnits.clear();
    flushedStencilStampUnits.clear();

    /*  Create buffers.  */

    /*  Set color buffer to NULL.  */
    //colorBuffer = NULL;

    //  Set z stencil buffer to NULL.
    //zstBuffer = NULL;

     // Set sync buffer to NULL
     syncBuffer = NULL;

    /*  Reset frame counter.  */
    frameCounter = startFrame;
    
    //  Reset batch counter.
    batchCounter = 0;

    /*  Reset state.  */
    state = RAST_RESET;

    /*  Reset free ticket counter.  */
    freeTickets = MAX_MEMORY_TICKETS;

    /*  Reset memory bus cycle counter.  */
    busCycles = 0;

    /*  Reset block state update cycle counter.  */
    stateUpdateCycles = 0;

    /*  Reset size of the color state buffer.  */
    colorStateBufferBlocks = 0;
    
    //  Reset size of the z stencil state buffer.
    zStencilStateBufferBlocks = 0;

    /*  Set a fake last command.  */
    lastRSCommand = new RasterizerCommand(RSCOM_RESET);

    //  Compute the size in bytes of a texture block.
    u32bit texBlockSize = 4 * (1 << (mortonBlockDim * 2));
    
    //  Set number of ROPs units in the Pixel Mapper.
    for (u32bit rt = 0; rt < MAX_RENDER_TARGETS; rt++) {
        colorPixelMapper[rt].setupUnit(numStampUnits, 0);
	rtSynced[rt] = true;
    }
    zstPixelMapper.setupUnit(numStampUnits, 0);
    
    //  Set the ticket list to the maximum number of memory tickets.
    ticketList.resize(MAX_MEMORY_TICKETS);
    
    string queueName;
    queueName.clear();
    queueName = "FreeTicketQueueDAC";
    ticketList.setName(queueName);    

    /*  Create blitter unit.  */    
    blt = new Blitter(gpuId, numGPUs, multiGPUExecMode, bltTransImpl,
                STAMP_HEIGHT, STAMP_WIDTH, genHeight / STAMP_HEIGHT, genWidth / STAMP_WIDTH, (u32bit) ceil(scanHeight / (f32bit) genHeight),
                (u32bit) ceil(scanWidth / (f32bit) genWidth), overHeight, overWidth, displayWidth, displayHeight,
                mortonBlockDim, mortonSBlockDim, texBlockSize,
                blockLatency, blocksPerCycle, blockSz, blockQSize, decompLatency, saveBlitSourceData
            );
}

/*  DAC simulation function.  */
void DAC::clock(u64bit cycle)
{
    ColorBlockStateInfo *colorBlockStateInfo;
    ROPBlockState *colorBufferStateAux;
    RasterizerCommand *rastComm;
    MemoryTransaction *memTrans;
    u32bit numBlocks;
    u32bit i;
    u32bit j;
    RasterizerState lastState;
    bool canDump;
    bool canSync;
    u32bit gpuIndex, unitIndex;

    /**  NOTE: SCREEN REFRESH (MEMORY CONSUMPTION) IS NOT IMPLEMENTED
         YET, ONLY FRAMEBUFFER READ AT SWAP (FAKE REFRESH).  A REFRESH
         RATE SHOULD BE ADDED TO THE GPU REGISTERS.  **/


    /*  Keep DAC state.  */
    lastState = state;

    GPU_DEBUG_BOX(
        printf("DAC => clock %lld.\n", cycle);
    )

    /*  Receive transactions from the memory controller.  */
    while(memoryData->read(cycle, (DynamicObject *&) memTrans))
    {
        /*  Process memory transaction.  */
        processMemoryTransaction(memTrans);
    }

    /*  Update color buffer block state update cycles.  */
    if (stateUpdateCycles > 0)
    {
        GPU_DEBUG_BOX(
            printf("DAC => Remaining update cycles %d.\n",
                stateUpdateCycles);
        )

        /*  Update cycles remaining.  */
        stateUpdateCycles--;
    }

    /*  Receive block state updates.  */
    for(i = 0; i < numStampUnits; i++)
    {
        if (blockStateCW[i]->read(cycle, (DynamicObject *&) colorBlockStateInfo))
        {
            // NOTE:  REMOVED AS A FAST FIX. (???)
            
            //  Check that the color buffer state memory is not being updated.
            //GPU_ASSERT(
            //    if (stateUpdateCycles > 0)
            //        panic("DAC", "clock", "Still updating the previous color buffer state memory.");
            //)

	    flushedColorStampUnits.insert(i);

            GPU_DEBUG_BOX(
                printf("DAC (%lld) => Received color buffer state memory from Color Write unit %d.  Blocks %d.\n",
                    cycle, i, colorBlockStateInfo->getNumBlocks());
            )

	    /*  Get number of blocks in the update object.  */
            numBlocks = colorBlockStateInfo->getNumBlocks() * numStampUnits;

            /*  Check if color buffer state was created.  */
            if ((colorBufferState == NULL) || (colorStateBufferBlocks != numBlocks))
            {
                /*  Deleting a NULL pointer shouldn't be a problem.  */
                delete[] colorBufferState;

                /*  Allocate the new buffer for the color state.  */
                colorBufferState = new ROPBlockState[numBlocks];
	
                /*  Set size of the color state buffer.  */
                colorStateBufferBlocks = numBlocks;
            }

            /*  Get the new color buffer state memory table.  */
            colorBufferStateAux = colorBlockStateInfo->getColorBufferState();

            u32bit unitStride = scanH * scanW;

            /*  Update the color buffer state table.  Each stamp unit modifies its assigned scan tiles.  */
            for(j = 0; j < numBlocks; j++)
            {
                u32bit k = (j / (unitStride * numStampUnits)) * unitStride + GPU_MOD(j, unitStride);
                
                /*  Check stamp unit.  */
                //if (blockUnit(colorPixelMapper, j) == i && GPU_MOD(blockDisplayTile(colorPixelMapper, j), numGPUs) == gpuId)
                if (blockUnit(colorPixelMapper[0], j) == i)
                    colorBufferState[j] = colorCompression ? colorBufferStateAux[k] : ROPBlockState(ROPBlockState::UNCOMPRESSED);
            }

            /*  Set the block state update cycles.  */
            stateUpdateCycles += (u32bit) ceil((f32bit) numBlocks / ((f32bit) blocksCycle * numStampUnits * numGPUs));

            /*  Delete  color buffer state memory table.  */
            delete[] colorBufferStateAux;

            /*  Delete state info object.  */
            delete colorBlockStateInfo;
        }

        if (blockStateZST[i]->read(cycle, (DynamicObject *&) colorBlockStateInfo))
        {
            /* NOTE:  REMOVED AS A FAST FIX.  */
            /*  Check that the color buffer state memory is not being updated.  */
            //GPU_ASSERT(
            //    if (stateUpdateCycles > 0)
            //        panic("DAC", "clock", "Still updating the previous color buffer state memory.");
            //)

	    flushedStencilStampUnits.insert(i);

            GPU_DEBUG_BOX(
                printf("DAC (%lld) => Received z stencil buffer state memory from Z Stencil Test unit %d. Blocks %d.\n",
                    cycle, i, colorBlockStateInfo->getNumBlocks());
            )

            //  Get number of blocks in the update object.
            numBlocks = colorBlockStateInfo->getNumBlocks() * numStampUnits;

            //  Check if z stencil buffer state was created.
            if ((zStencilBufferState == NULL) || (zStencilStateBufferBlocks != numBlocks))
            {
                //  Deleting a NULL pointer shouldn't be a problem.
                delete[] zStencilBufferState;

                //  Allocate the new buffer for the z stencil state.
                zStencilBufferState = new ROPBlockState[numBlocks];
	
                //  Set size of the z stencil state buffer.
                zStencilStateBufferBlocks = numBlocks;
            }

            //  Get the new color buffer state memory table.  */
            ROPBlockState *zStencilBufferStateAux = colorBlockStateInfo->getColorBufferState();

            u32bit unitStride = scanH * scanW;

            //  Update the z stencil buffer state table.  Each stamp unit modifies its assigned scan tiles.
            for(j = 0; j < numBlocks; j++)
            {
                u32bit k = (j / (unitStride * numStampUnits)) * unitStride + GPU_MOD(j, unitStride);
                
                //  Check stamp unit.
                //if (blockUnit(zstPixelMapper, j) == i && GPU_MOD(blockDisplayTile(zstPixelMapper, j), numGPUs) == gpuId)
                if (blockUnit(zstPixelMapper, j) == i)
                    zStencilBufferState[j] = zStencilCompression ? zStencilBufferStateAux[k] : ROPBlockState(ROPBlockState::UNCOMPRESSED);
            }

            //  Set the block state update cycles.
            stateUpdateCycles += (u32bit) ceil((f32bit) numBlocks / ((f32bit) blocksCycle * numStampUnits * numGPUs));

            //  Delete z stencil buffer state memory table.
            delete[] zStencilBufferStateAux;

            //  Delete state info object.
            delete colorBlockStateInfo;
        }
    }

    //  Simulate current cycle.
    switch(state)
    {
        case RAST_RESET:

            //  Reset state.

            GPU_DEBUG_BOX(
                printf("DAC => RESET state.\n");
            )

            //  Reset the state of the DAC unit.
            reset();

            //  Change to ready state.
            state = RAST_READY;

            break;

        case RAST_READY:
            /*  Ready state.  */

            GPU_DEBUG_BOX(
                printf("DAC => READY state.\n");
            )

            /*  Receive and process command from the Command Processor.  */
            if (dacCommand->read(cycle, (DynamicObject *&) rastComm))
                processCommand(cycle, rastComm);

            /*  Check if frame refresh/dumping must start.  */
            if (!synchedRefresh && refreshFrame && (GPU_MOD(cycle, refreshRate) == (refreshRate - 1)))
            {
                /*  Initialize frame refresh/dumping state.  */
                startRefresh();
            }

            break;

        case RAST_END:
            /*  End state.  */

            GPU_DEBUG_BOX(
                if (state == RAST_END)
                    printf("DAC => END state.\n");
            )

            /*  Wait for END command from the Command Processor.  */
            if (dacCommand->read(cycle, (DynamicObject *&) rastComm))
                processCommand(cycle, rastComm);

            break;

        case RAST_SYNC:
            /* Color buffer or ZST buffe flush state. */
	    /* In multi-GPU, after flush, read flushed data and broadcast them to other GPUs for FB sync. */

	    GPU_DEBUG_BOX(
                printf("DAC => Sync state.\n");
            )

            if (interGPUSyncTransCycles > 0) {
	        interGPUSyncTransCycles--;

		if (interGPUSyncTransCycles == 0)
		    consumedInterGPUbw = 0;
	    }

            //  Receive and process command from the Command Processor.
            if (dacCommand->read(cycle, (DynamicObject *&) rastComm))
                processCommand(cycle, rastComm);

	    switch (lastRSCommand->getCommand()) {
	        case RSCOM_SYNC_COLOR:
		    canSync = flushedColorStampUnits.size() == numStampUnits;
                    break;
		case RSCOM_SYNC_STENCIL:
		    canSync = flushedStencilStampUnits.size() == numStampUnits;
                    break;
		default:
                    panic("DAC", "clock", "Expected a dump buffer command.");
                    break;
	    }

	    if (canSync) {
                //  Update memory transmission.
                updateMemory(cycle);
                
		//  Update inter-GPU sync
	        switch (lastRSCommand->getCommand()) {
	            case RSCOM_SYNC_COLOR:
			processSyncBackPressure(cycle, colorSyncBackPressure);
	                updateSync(cycle, &ColorCompressorEmulator::getInstance(), syncBuffer, rtAddress[nextRt],
			           colorBufferState, blockSize, colorPixelMapper[nextRt], colorSync);
                        break;
	            case RSCOM_SYNC_STENCIL:
			processSyncBackPressure(cycle, zstSyncBackPressure);
	                updateSync(cycle, &DepthCompressorEmulator::getInstance(), syncBuffer, zStencilBuffer,
			           zStencilBufferState, zStencilBlockSize, zstPixelMapper, zstSync);
                        break;
	            default:
                        panic("DAC", "clock", "Expected a dump buffer command.");
                        break;
	        }

                //  Update block request stage.
                updateBlockRequest(cycle);
                
                //  Update request queue stage.
	        switch (lastRSCommand->getCommand()) {
	            case RSCOM_SYNC_COLOR:
                        updateRequestQueue(cycle, &ColorCompressorEmulator::getInstance(), rtAddress[nextRt], colorBufferSize,
				           colorBufferState, blockSize, colorPixelMapper[nextRt]);
			sendLastSyncCommand(cycle, colorSync);
                        break;
	            case RSCOM_SYNC_STENCIL:
                        updateRequestQueue(cycle, &DepthCompressorEmulator::getInstance(), zStencilBuffer, zStencilBufferSize,
				           zStencilBufferState, zStencilBlockSize, zstPixelMapper);
			sendLastSyncCommand(cycle, zstSync);
                        break;
	            default:
                        panic("DAC", "clock", "Expected a dump buffer command.");
                        break;
	        }

		if (interGPUSyncTransCycles == 0)
                    interGPUSyncTransCycles = (u32bit)ceil(f32bit(consumedInterGPUbw)/f32bit(interGPUBusWidth));

                if (numSyncedGPUs == numGPUs -1) {
		    delete[] syncBuffer;
		    syncBuffer = NULL;

	            switch (lastRSCommand->getCommand()) {
	                case RSCOM_SYNC_COLOR:
		            flushedColorStampUnits.clear();
                            break;
	                case RSCOM_SYNC_STENCIL:
	                    flushedStencilStampUnits.clear();
                            break;
	                default:
                            panic("DAC", "clock", "Expected a dump buffer command.");
                            break;
	            }

		    //FILE* debugfile = fopen("debugBlit.txt", "a+");
		    //fprintf(debugfile, "%s cycle %lld finished color sync\n", getName(), cycle);
		    //fflush(debugfile);
		    //fclose(debugfile);

	            //FILE *debugfile = fopen("debugDACSync.txt", "a+");
	            //fprintf(debugfile, "GPU[%d] cycle %lld batch %d finished sync lastRSComm %d\n",
	            //        gpuId, cycle, batchCounter, lastRSCommand->getCommand());
	            //fflush(debugfile);
	            //fclose(debugfile);
	    
		    state = RAST_END;
		}		
	    }

	    break;

        case RAST_SWAP:

            //  Swap state.

            GPU_DEBUG_BOX(
                printf("DAC => Swap state.\n");
            )

            //  Receive and process command from the Command Processor.
            if (dacCommand->read(cycle, (DynamicObject *&) rastComm))
                processCommand(cycle, rastComm);

	    if (flushedColorStampUnits.size() == numStampUnits) {
                //  Update memory transmission.
                updateMemory(cycle);
                
                //  Update block decompressor stage.
                updateDecompressor(cycle, &ColorCompressorEmulator::getInstance(), colorBuffer, clearColorData,
				   bytesPixel[0], frontBuffer, colorPixelMapper[0]);
           
                //  Update block request stage.
                updateBlockRequest(cycle);
                
                //  Update request queue stage.
                updateRequestQueue(cycle, &ColorCompressorEmulator::getInstance(), frontBuffer, colorBufferSize,
				   colorBufferState, blockSize, colorPixelMapper[0]);
                     	    
                //  Check if the full color buffer has been read.
                if ((busCycles == 0) && (numFree == blockQueueSize) && (stateUpdateCycles == 0))
                {
	            if (GPUSimulator::gpuSync->synced(gpuId) == false) {
	                GPUSimulator::gpuSync->sync(gpuId, GPU_SWAP_SYNC);
	            }

	            if (GPUSimulator::gpuSync->allGPUSynced()) {
	                if (!writeColorBufferCalled) {
                            /*  Write the ppm file with the current framebuffer.  */
                            writeColorBuffer();

                            //GPU_DEBUG_BOX(
                                printf("DAC => Cycle %lld Color Buffer Dumped.\n", cycle);
                            //)

                            //  Delete the color buffer.
                            delete[] colorBuffer;
	            	    colorBuffer = NULL;

	                    writeColorBufferCalled = true;
	                }

                        //  Update frame counter.
                        frameCounter++;
                        
                        //  Reset batch counter.
                        batchCounter = 0;

		        flushedColorStampUnits.clear();

                        //  Check if synched refresh.
                        if (synchedRefresh)
                        {
                            //  Change to end state.
                            state = RAST_END;
                        }
                        else
                        {
                            //  Change to end state.
                            state = RAST_READY;
                        }

	                GPUSimulator::gpuSync->exitSync(gpuId);

	                if (GPUSimulator::gpuSync->allGPUSynced() == false)
	        	    writeColorBufferCalled = false;
	            }
                }
	    }

            break;

        case RAST_DUMP_BUFFER:

            //  Dump buffer state.

            GPU_DEBUG_BOX(
                printf("DAC => DUMP BUFFER state.\n");
            )

            //  Receive and process command from the Command Processor.
            if (dacCommand->read(cycle, (DynamicObject *&) rastComm))
                processCommand(cycle, rastComm);

	    switch (lastRSCommand->getCommand()) {
	        case RSCOM_DUMP_COLOR:
		    canDump = flushedColorStampUnits.size() == numStampUnits;
                    break;
		case RSCOM_DUMP_DEPTH:
		case RSCOM_DUMP_STENCIL:
		    canDump = flushedStencilStampUnits.size() == numStampUnits;
                    break;
		default:
                    panic("DAC", "clock", "Expected a dump buffer command.");
                    break;
	    }

	    if (canDump) {
                //  Update memory transmission.
                updateMemory(cycle);
                
                switch(lastRSCommand->getCommand())
                {
                    case RSCOM_DUMP_COLOR:
                        //  Update block decompressor stage.
                        updateDecompressor(cycle, &ColorCompressorEmulator::getInstance(), colorBuffer, clearColorData,
	            		           bytesPixel[0], backBuffer, colorPixelMapper[0]);
                        break;
                    case RSCOM_DUMP_DEPTH:
                    case RSCOM_DUMP_STENCIL:
                        //  Update block decompressor stage.
                        updateDecompressor(cycle, &DepthCompressorEmulator::getInstance(), zstBuffer, (u8bit *) &clearZStencilData,
                                           zStencilBytesPixel, zStencilBuffer, zstPixelMapper);
                        break;
                    default:
                        panic("DAC", "clock", "Expected a dump buffer command.");
                        break;
                }
                
                //  Update block request stage.
                updateBlockRequest(cycle);
                
                switch(lastRSCommand->getCommand())
                {
                    case RSCOM_DUMP_COLOR:
                        //  Update request queue stage.
                        updateRequestQueue(cycle, &ColorCompressorEmulator::getInstance(), backBuffer,
					   colorBufferSize, colorBufferState, blockSize, colorPixelMapper[0]);
                        break;
                    case RSCOM_DUMP_DEPTH:
                    case RSCOM_DUMP_STENCIL:
                        //  Update request queue stage.
                        updateRequestQueue(cycle, &DepthCompressorEmulator::getInstance(), zStencilBuffer,
					   zStencilBufferSize, zStencilBufferState, zStencilBlockSize, zstPixelMapper);
                        break;
                    default:
                        panic("DAC", "clock", "Expected a dump buffer command.");
                        break;
                }
                        
                //  Check if the full color buffer has been read.
                if ((busCycles == 0) && (numFree == blockQueueSize) && (stateUpdateCycles == 0))
                {
	            if (GPUSimulator::gpuSync->synced(gpuId) == false) {
	                switch(lastRSCommand->getCommand()) {
	            	    case RSCOM_DUMP_COLOR:
	                        GPUSimulator::gpuSync->sync(gpuId, GPU_DUMP_COLOR_SYNC);
	            	        break;
	            	    case RSCOM_DUMP_DEPTH:
	                        GPUSimulator::gpuSync->sync(gpuId, GPU_DUMP_DEPTH_SYNC);
	            	        break;
	            	    case RSCOM_DUMP_STENCIL:
	                        GPUSimulator::gpuSync->sync(gpuId, GPU_DUMP_STENCIL_SYNC);
	            	        break;
                            default:                        
                                panic("DAC", "clock", "Expected a dump buffer command.");
                                break;
	                }
	            }
	            
	            if (GPUSimulator::gpuSync->allGPUSynced()) {
                        switch(lastRSCommand->getCommand())
                        {
                            case RSCOM_DUMP_COLOR:
                           
	            	        if (!writeColorBufferCalled) {	
                                    //  Dump the color buffer as a PPM file.
                                    writeColorBuffer();
                                    
				    printf("DAC[%d] => Cycle %lld Color Buffer Dumped.\n", gpuId, cycle);

                                    //  Delete the color buffer.
                                    delete[] colorBuffer;
	            	            colorBuffer = NULL;

	            	            writeColorBufferCalled = true;
	            	        }
	                           
			        flushedColorStampUnits.clear();	
	            	        GPUSimulator::gpuSync->exitSync(gpuId);

	                        if (GPUSimulator::gpuSync->allGPUSynced() == false)
	                            writeColorBufferCalled = false;
                                        
                                break;
                          
                            case RSCOM_DUMP_DEPTH:
                            
	            	        if (!writeDepthBufferCalled) {	
                                    //  Dump the z buffer as a PPM file.
                                    writeDepthBuffer();
                                    
                                    printf("DAC[%d] => Cycle %lld Depth Buffer Dumped.\n", gpuId, cycle);

                                    //  Delete the z stencil buffer.
                                    delete[] zstBuffer;
	            	            zstBuffer = NULL;

	            	            writeDepthBufferCalled = true;
	            	        }
	                       
			        flushedStencilStampUnits.clear();	
	            	        GPUSimulator::gpuSync->exitSync(gpuId);

	                        if (GPUSimulator::gpuSync->allGPUSynced() == false)
	                            writeDepthBufferCalled = false;
                                
                                break;
                                
                            case RSCOM_DUMP_STENCIL:
                            
	            	        if (!writeStencilBufferCalled) {	
                                    //  Dump the stencil buffer as a PPM file.
                                    writeStencilBuffer();
                                    
                                    printf("DAC[%d] => Cycle %lld Stencil Buffer Dumped.\n", gpuId, cycle);

                                    //  Delete the z stencil buffer.
                                    delete[] zstBuffer;
	            	            zstBuffer = NULL;

	            	            writeStencilBufferCalled = true;
	            	        }
	                            
			        flushedStencilStampUnits.clear();	
	            	        GPUSimulator::gpuSync->exitSync(gpuId);

	                        if (GPUSimulator::gpuSync->allGPUSynced() == false)
	                            writeStencilBufferCalled = false;
                                
                                break;
                                
                            default:                        
                                panic("DAC", "clock", "Expected a dump buffer command.");
                                break;
                        }

                        //  Change to end state.
                        state = RAST_END;
	                
	            }
                }
	    }	

            break;

        case RAST_BLIT:

            /*  Blit state.  */

            GPU_DEBUG_BOX(
                printf("DAC => Blit state.\n");
            )

            /*  Receive and process command from the Command Processor.  */
            if (dacCommand->read(cycle, (DynamicObject *&) rastComm))
                processCommand(cycle, rastComm);

	    if (!blt->currentFinished()) {
                /*  Check if memory bus is busy.  */
                if (busCycles > 0)
                {
                    /*  Update bus use counter.  */
                    busCycles--;

                    GPU_DEBUG_BOX(
                        printf("DAC %lld => Transmission in progress.  Remaining cycles %d\n",
                            cycle, busCycles);
                    )

                    /*  Check end of transmission.  */
                    if (busCycles == 0)
                    {
                        GPU_DEBUG_BOX(
                            printf("DAC => End of memory read.\n");
                        )

                        blt->receivedReadTransaction(lastTicket, lastSize);
                        
                        /*  Update block queue entry received bytes.  */
                        //blockQueue[ticket2queue[GPU_MOD(lastTicket, MAX_MEMORY_TICKETS)]].received += lastSize;

                        /*  Update free memory tickets counter.  */
                        //freeTickets++;
                    }
                }

                if (stateUpdateCycles == 0 && !bufferStateUpdatedAtBlitter && flushedColorStampUnits.size() == numStampUnits)
                {
                    //printf("DAC (%lld) => Sending color buffer state to Blitter | num block = %d\n",
		    //        cycle, address2block(colorBufferSize));
                    blt->setColorBufferState(colorBufferState, address2block(colorBufferSize));
                    bufferStateUpdatedAtBlitter = true;
		    flushedColorStampUnits.clear();

		    //FILE *debugfile = fopen("debugBlit.txt", "a+");
		    //fprintf(debugfile, "%s cycle %lld set unit %d colorBufferState[95] state = %d comprLevel = %d\n",
		    //        getName(), cycle, blockUnit(colorPixelMapper, 95),
		    //        colorBufferState[95].getState(), colorBufferState[95].getComprLevel());
		    //fflush(debugfile);
		    //fclose(debugfile);
                }
                
                blt->clock(cycle);
	    }

            if (blt->currentFinished())
            {
                GPU_DEBUG_BOX(
                    printf("DAC::Blitter %lld => End of bit blit operation.\n", cycle);
                )

	        if (GPUSimulator::gpuSync->synced(gpuId) == false) {
	            GPUSimulator::gpuSync->sync(gpuId, GPU_BLIT_SYNC);
	        }
	        
	        if (GPUSimulator::gpuSync->allGPUSynced()) {
                    blt->dumpBlitSource(frameCounter, blitCounter);
                    
                    blitCounter++;
                    
		    //FILE* debugfile = fopen("debugBlit.txt", "a+");
		    //fprintf(debugfile, "%s cycle %lld finished blit\n", getName(), cycle);
		    //fflush(debugfile);
		    //fclose(debugfile);

	            //FILE *debugfile = fopen("debugDACSync.txt", "a+");
	            //fprintf(debugfile, "GPU[%d] cycle %lld batch %d finished blit\n",
	            //        gpuId, cycle, batchCounter);
	            //fflush(debugfile);
	            //fclose(debugfile);
	    
                    /*  Change to end state.  */
                    state = RAST_END;
	            
	            GPUSimulator::gpuSync->exitSync(gpuId);
	        }
            }
                
            break;
            
        default:
            panic("DAC", "clock", "Undefined DAC state.");
            break;
    }

    /*  Send current state to the Command Processor.  */
    dacState->write(cycle, new RasterizerStateInfo(state));

    /*  Do not go to END state in unsynched mode, just send the state to Command Processor.  */
    if (!synchedRefresh && (state == RAST_END))
    {
        state = lastState;
    }
}

/*  Processes a rasterizer command.  */
void DAC::processCommand(u64bit cycle, RasterizerCommand *command)
{
    u32bit aux;
    u32bit samples;
    u32bit i, j;
    FILE *debugfile = NULL;

    /*  Delete last command.  */
    delete lastRSCommand;

    /*  Store current command as last received command.  */
    lastRSCommand = command;

    /*  Process command.  */
    switch(command->getCommand())
    {
        case RSCOM_RESET:
            /*  Reset command from the Rasterizer main box.  */

            GPU_DEBUG_BOX(
                printf("DAC => RESET command received.\n");
            )

            /*  Change to reset state.  */
            state = RAST_RESET;

            break;

        case RSCOM_END:
            /*  End command received from Rasterizer main box.  */

            GPU_DEBUG_BOX(
                printf("DAC => END command received.\n");
            )

            /*  Check current state.  */
            GPU_ASSERT(
                if ((synchedRefresh && (state != RAST_END)) || (!synchedRefresh && (state != RAST_SWAP) && (state != RAST_READY)))
                    panic("DAC", "processCommand", "END command can only be received in END state.");
            )

            /*  Check if synchronized refresh is enabled.  */
            if (synchedRefresh)
            {
                /*  Change to ready state.  */
                state = RAST_READY;
            }

            break;

        case RSCOM_REG_WRITE:
            /*  Write register command from the Rasterizer main box.  */

            GPU_DEBUG_BOX(
                printf("DAC => REG_WRITE command received.\n");
            )

             /*  Check current state.  */
            GPU_ASSERT(
                if ((state != RAST_READY) && (state != RAST_SWAP))
                    panic("DAC", "processCommand", "REGISTER WRITE command can only be received in READY state.");
            )

            /*  Process register write.  */
            processRegisterWrite(command->getRegister(),
                command->getSubRegister(), command->getRegisterData());

            break;

	case RSCOM_SYNC_COLOR:
            // Sync colorBuffer
            
	    GPU_ASSERT(
	        if (numGPUs <= 1)
                    panic("DAC", "processCommand", "this command is only for multi-GPU architecture");		
	    )

	    GPU_DEBUG_BOX(
                printf("DAC => SYNC_COLOR command received.\n");
            )

            //  Reset number of free queue entries.
            numFree = blockQueueSize;

            //  Reset number of blocks to request.
            numToRequest = 0;

            //  Reset number of blocks to decompress.
            numToDecompress = 0;

            //  Reset free, to requeuest and to decompress queue pointers.
            nextFree = nextRequest = nextDecompress = 0;

            //  Reset decompress cycles.
            decompressCycles = 0;

            //  Reset color buffer requested bytes (blocks).
            requested = 0;

	    //  Reset Sync data
	    nextRt = 0;
	    numSyncedGPUs = 0;
	    for (i = 0; i < numGPUs; i++) {
		numBufferedSyncData[i] = 0;
		nextBufferedSyncData[i] = 0;
		allSyncDataSent[i] = false;
	        
		for (j = 0; j < numStampUnits; j++) {
		    lastSyncCommSent[i][j] = false;
		    numSyncCommQueueFreeEntries[i][j] = syncCommQueueSize;
		    numSent[i][j] = 0;
		}
	    }

	    syncForBlit = lastRSCommand->getSyncForBlit();

	    if (syncForBlit) {
		nextBlockStateSyncGPUID = 0;
	        numBlockStateSyncedGPUs = 0;
		nextBlockStateSyncCommRead = 0;
		nextBlockStateSyncCommWrite = 0;
		for (i = 0; i < numGPUs; i++) {
		    numBlockStateSyncCommQueueFreeEntries[i] = syncCommQueueSize;
		    numBlockStateSyncCommQueueBackPressures[i] = syncCommQueueSize;
		}
	    }
           
            //  Compute color buffer size.
            colorBufferSize = colorPixelMapper[0].computeFrameBufferSize();
	    
	    //debugfile = fopen("debugDACSync.txt", "a+");
	    //fprintf(debugfile, "GPU[%d] cycle %lld batch %d will sync color rtAddr[0] = 0x%x colorBufferSize %d 0x%x rtEnable %s rtSynced %s\n",
	    //        gpuId, cycle, batchCounter, rtAddress[0], colorBufferSize, colorBufferSize,
	    //        rtEnable[0] ? "T" : "F", rtSynced[0] ? "T" : "F");
	    //fflush(debugfile);
	    //fclose(debugfile);
	    
            GPU_DEBUG_BOX(
                printf("DAC => Flush Buffer Address %08x | Color Buffer Size %d (%d x %d)\n", backBuffer, colorBufferSize, hRes, vRes);
            )

            //debugfile = fopen("debugBlit.txt", "a+");
	    //fprintf(debugfile, "%s cycle %lld will begin color buffer sync\n", getName(), cycle);
	    //fflush(debugfile);
	    //fclose(debugfile);

            //  Allocate space for the color buffer.
	    if (!syncBuffer)
                syncBuffer = new u8bit[colorBufferSize];
            
	    state = RAST_SYNC;
	    break;

	case RSCOM_SYNC_STENCIL:
            // Sync stencilBuffer
            
	    GPU_ASSERT(
	        if (numGPUs <= 1)
                    panic("DAC", "processCommand", "this command is only for multi-GPU architecture");		
	    )

	    GPU_DEBUG_BOX(
                printf("DAC => SYNC_ZSTENCIL command received.\n");
            )

            //  Reset number of free queue entries.
            numFree = blockQueueSize;

            //  Reset number of blocks to request.
            numToRequest = 0;

            //  Reset number of blocks to decompress.
            numToDecompress = 0;

            //  Reset free, to requeuest and to decompress queue pointers.
            nextFree = nextRequest = nextDecompress = 0;

            //  Reset decompress cycles.
            decompressCycles = 0;

            //  Reset color buffer requested bytes (blocks).
            requested = 0;

	    //  Reset Sync data
	    numSyncedGPUs = 0;
	    for (i = 0; i < numGPUs; i++) {
		numBufferedSyncData[i] = 0;
		nextBufferedSyncData[i] = 0;
		allSyncDataSent[i] = false;
	        
		for (j = 0; j < numStampUnits; j++) {
		    lastSyncCommSent[i][j] = false;
		    numSyncCommQueueFreeEntries[i][j] = syncCommQueueSize;
		    numSent[i][j] = 0;
		}
	    }
            
	    syncForBlit = lastRSCommand->getSyncForBlit();

	    GPU_ASSERT(
	        if (syncForBlit)
                   panic("DAC", "processCommand", "blit should not sync zst buffer");		
	    )

            //  Compute z stencil buffer size.
            zStencilBufferSize = zstPixelMapper.computeFrameBufferSize();
          
	    //debugfile = fopen("debugDACSync.txt", "a+");
	    //fprintf(debugfile, "GPU[%d] cycle %lld batch %d will sync zstBuffer = 0x%x zstBufferSize %d 0x%x\n",
	    //        gpuId, cycle, batchCounter, zStencilBuffer, zStencilBufferSize, zStencilBufferSize);
	    //fflush(debugfile);
	    //fclose(debugfile);
	    
            GPU_DEBUG_BOX(
                printf("DAC => Flush Buffer Address %08x | Color Buffer Size %d (%d x %d)\n", zStencilBuffer, zStencilBufferSize, hRes, vRes);
            )

            //  Allocate space for the color buffer.
	    if (!syncBuffer)
                syncBuffer = new u8bit[zStencilBufferSize];
            
            //  Set z stencil block size.
            zStencilBlockSize = blockSize;

	    state = RAST_SYNC;
	    break;

        case RSCOM_SWAP:
            /*  Swap front and back buffer command.  */

	    GPU_DEBUG_BOX(
                printf("DAC => SWAP command received.\n");
            )

            /*  Check if syncrhonized refresh.  */
            if (synchedRefresh && refreshFrame)
            {
                /*  Initialize frame refresh/dumping state.  */
                startRefresh();
            }
            else if (!refreshFrame)
            {
                /*  Update frame counter.  */
                frameCounter++;
                
                //  Reset batch counter.
                batchCounter = 0;

                /*  Change to end state.  */
                state = RAST_END;
            }
            else
            {
                /*  Change to end state.  */
                state = RAST_END;
            }

            //  Reset blit counter.
            blitCounter = 0;

            /*  Swap front and back buffer address.  */
            aux = frontBuffer;
            frontBuffer = backBuffer;
            backBuffer = aux;
            blt->setBackBufferAddress(backBuffer);

            break;

        case RSCOM_DUMP_COLOR:
        
            //  Dump the color buffer.
            
	    GPU_DEBUG_BOX(
                printf("DAC => DUMP_COLOR command received.\n");
            )

            //  Reset number of free queue entries.
            numFree = blockQueueSize;

            //  Reset number of blocks to request.
            numToRequest = 0;

            //  Reset number of blocks to decompress.
            numToDecompress = 0;

            //  Reset free, to requeuest and to decompress queue pointers.
            nextFree = nextRequest = nextDecompress = 0;

            //  Reset decompress cycles.
            decompressCycles = 0;

            //  Reset color buffer requested bytes (blocks).
            requested = 0;
            
            //  Compute color buffer size.
            colorBufferSize = colorPixelMapper[0].computeFrameBufferSize();
          
            //GPU_DEBUG_BOX(
                printf("DAC => Color Buffer Address %08x | Color Buffer Size %d (%d x %d)\n", backBuffer, colorBufferSize, hRes, vRes);
            //)

            //  Allocate space for the color buffer.
	    if (!colorBuffer)
                colorBuffer = new u8bit[colorBufferSize];

            //  Change to dump buffer state.
            state = RAST_DUMP_BUFFER;
            
            break;
            
        case RSCOM_DUMP_DEPTH:
        
            //  Dump the depth buffer.
            
	    GPU_DEBUG_BOX(
                printf("DAC => DUMP_COLOR command received.\n");
            )

            //  Reset number of free queue entries.
            numFree = blockQueueSize;

            //  Reset number of blocks to request.
            numToRequest = 0;

            //  Reset number of blocks to decompress.
            numToDecompress = 0;

            //  Reset free, to requeuest and to decompress queue pointers.
            nextFree = nextRequest = nextDecompress = 0;

            //  Reset decompress cycles.
            decompressCycles = 0;

            //  Reset color buffer requested bytes (blocks).
            requested = 0;
            
            //  Compute z stencil buffer size.
            zStencilBufferSize = zstPixelMapper.computeFrameBufferSize();
          
            GPU_DEBUG_BOX(
                printf("DAC => Z Stencil Buffer Address %08x Size %d (%d x %d)\n", zStencilBuffer, zStencilBufferSize, hRes, vRes);
            )

            //  Allocate space for the z stencil buffer.
	    if (!zstBuffer)
                zstBuffer = new u8bit[zStencilBufferSize];

            //  Set z stencil block size.
            zStencilBlockSize = blockSize;
            
            //  Set z stencil bytes per pixel.
            zStencilBytesPixel = 4;
            
            //  Set z stencil clear value.
            clearZStencilData = ((clearStencil & 0xff) << 24) | (clearDepth & 0x00ffffff);
            
            //  Change to dump buffer state.
            state = RAST_DUMP_BUFFER;

            break;
            
        case RSCOM_DUMP_STENCIL:
        
            //  Dump the stencil buffer.
            
	    GPU_DEBUG_BOX(
                printf("DAC => DUMP_STENCIL command received.\n");
            )

            //  Reset number of free queue entries.
            numFree = blockQueueSize;

            //  Reset number of blocks to request.
            numToRequest = 0;

            //  Reset number of blocks to decompress.
            numToDecompress = 0;

            //  Reset free, to requeuest and to decompress queue pointers.
            nextFree = nextRequest = nextDecompress = 0;

            //  Reset decompress cycles.
            decompressCycles = 0;

            //  Reset color buffer requested bytes (blocks).
            requested = 0;
            
            //  Compute z stencil buffer size.
            zStencilBufferSize = zstPixelMapper.computeFrameBufferSize();
          
            GPU_DEBUG_BOX(
                printf("DAC => Z Stencil Buffer Address %08x Size %d (%d x %d)\n", zStencilBuffer, zStencilBufferSize, hRes, vRes);
            )

            //  Allocate space for the z stencil buffer.
	    if (!zstBuffer)
                zstBuffer = new u8bit[zStencilBufferSize];

            //  Set z stencil block size.
            zStencilBlockSize = blockSize;
            
            //  Set z stencil bytes per pixel.
            zStencilBytesPixel = 4;
            
            //  Set z stencil clear value.
            clearZStencilData = ((clearStencil & 0xff) << 24) | (clearDepth & 0x00ffffff);

            //  Change to dump buffer state.
            state = RAST_DUMP_BUFFER;

            break;
            
        case RSCOM_BLIT:
            
            //  Blit a framebuffer region to a texture destination address.

            GPU_DEBUG_BOX(
                printf("DAC => BLIT command received at cycle %lld.\n", cycle);
            )

            /*  Initialize blitter unit */
            
            blt->startBitBlit();
            
            /*colorBufferSize = ((u32bit) ceil(vRes / (f32bit) (overH * scanH * genH * STAMP_HEIGHT))) *
                ((u32bit) ceil(hRes / (f32bit) (overW * scanW * genW * STAMP_WIDTH))) *
                overW * overH * scanW * scanH * genW * genH * STAMP_WIDTH * STAMP_HEIGHT * bytesPixel;*/
            //samples = multisampling ? msaaSamples : 1;
            //pixelMapper.setupDisplay(hRes, vRes, STAMP_WIDTH, STAMP_HEIGHT, genW, genH, scanW, scanH, overW, overH, samples, bytesPixel);
            colorBufferSize = colorPixelMapper[0].computeFrameBufferSize();
        
            bufferStateUpdatedAtBlitter = false;
            
            //debugfile = fopen("debugBlit.txt", "a+");
	    //fprintf(debugfile, "%s cycle %lld will begin blit backBufferAddr %x destAddr %x rtAddr[0] = %x colorBufferSize %d destEndAddr %x hRes %d vRes %d samples %d bytesPixel[0] %d\n",
	    //        getName(), cycle, blt->getBackBufferAddress(), blt->getBlitDestAddress(), rtAddress[0],
	    //        colorBufferSize, blt->getBlitDestAddress() + colorBufferSize, hRes, vRes, msaaSamples, bytesPixel[0]);
	    //fflush(debugfile);
	    //fclose(debugfile);

	    //debugfile = fopen("debugDACSync.txt", "a+");
	    //fprintf(debugfile, "GPU[%d] cycle %lld batch %d will begin blit backBufferAddr 0x%x destAddr 0x%x rtAddr[0] = 0x%x colorBufferSize %d 0x%x destEndAddr 0x%x hRes %d vRes %d samples %d bytesPixel[0] %d\n",
	    //        gpuId, cycle, batchCounter, blt->getBackBufferAddress(), blt->getBlitDestAddress(), rtAddress[0],
	    //        colorBufferSize, colorBufferSize, blt->getBlitDestAddress() + colorBufferSize, hRes, vRes, msaaSamples, bytesPixel[0]);
	    //fflush(debugfile);
	    //fclose(debugfile);
	    
            /*  Change state to BLIT.  */
            state = RAST_BLIT;

            break;

        case RSCOM_DRAW:
        
            //  Draw command.  Used to count draw calls.
            
            //  Update batch counter.
            batchCounter++;

            //samples = multisampling ? msaaSamples : 1;
	    //debugfile = fopen("debugDACSync.txt", "a+");
	    //fprintf(debugfile, "GPU[%d] cycle %lld will process batch %d hRes %d vRes %d samples %d bytesPixel[0] %d\n",
	    //        gpuId, cycle, batchCounter, hRes, vRes, samples, bytesPixel[0]);
	    //fflush(debugfile);
	    //fclose(debugfile);
	    
            break;
            
        case RSCOM_FRAME_CHANGE:

            //  Fake swap buffer command for draw command skipping mode.

            GPU_DEBUG_BOX(
                printf("DAC => FRAME CHANGE command received.\n");
            )

            //  Update frame counter.
            frameCounter++;
            
            //  Reset batch counter.
            batchCounter = 0;

            //  Reset blit counter.
            blitCounter = 0;

            break;

        default:
            panic("DAC", "proccessCommand", "Unsupported command.");
            break;
    }
}

/*  Processes a memory transaction.  */
void DAC::processMemoryTransaction(MemoryTransaction *memTrans)
{
    /*  Get transaction type.  */
    switch(memTrans->getCommand())
    {
        case MT_STATE:

            /*  Received state of the Memory controller.  */
            memState = memTrans->getState();

            break;

        case MT_READ_DATA:

            /*  Check if the bus is ready.  */
            GPU_ASSERT(
                if (busCycles != 0)
                    panic("DAC", "processMemoryTransaction", "Memory bus was still in use.");
            )

            /*  Get transaction size.  */
            lastSize = memTrans->getSize();

            /*  Get transaction ticket.  */
            lastTicket = memTrans->getID();

            /*  Get number of cycles.  */
            busCycles = memTrans->getBusCycles();

            break;

        default:

            panic("DAC", "processMemoryTransaction", "Unsupported memory transaction.");

            break;
    }

    /*  Delete processed memory transaction.  */
    delete memTrans;
}

/*  Process a register write.  */
void DAC::processRegisterWrite(GPURegister reg, u32bit subreg, GPURegData data)
{
    u32bit samples;
    FILE *debugfile = NULL;
    
    /*  Process register write.  */
    switch(reg)
    {
	case GPU_ZSTENCILBUFFER_DEFINED:
            zStencilBufferDefined = data.booleanVal;
            
	    //debugfile = fopen("debugDACSync.txt", "a+");
	    //fprintf(debugfile, "batch %d set zStencilBufferDefined %s hRes %d vRes %d\n",
	    //        batchCounter, zStencilBufferDefined ? "T" : "F", hRes, vRes);
	    //fflush(debugfile);
	    //fclose(debugfile);

            samples = multisampling ? msaaSamples : 1;
            if (zStencilBufferDefined)
	        zstPixelMapper.setupDisplay(hRes, vRes, STAMP_WIDTH, STAMP_HEIGHT, genW, genH, scanW, scanH, overW, overH,
				            displayW, displayH, samples, 4);

	    break;

        case GPU_DISPLAY_X_RES:
            /*  Write display horizontal resolution register.  */
            hRes = data.uintVal;
            
	    //debugfile = fopen("debugDACSync.txt", "a+");
	    //fprintf(debugfile, "batch %d set hRes as %d\n", batchCounter, hRes);
	    //fflush(debugfile);
	    //fclose(debugfile);

            blt->setDisplayXRes(hRes);
            
            GPU_DEBUG_BOX(
                printf("DAC => Write GPU_DISPLAY_X_RES = %d.\n", hRes);
            )

            //  Update the pixel mapper.
            samples = multisampling ? msaaSamples : 1;
	    for (u32bit rt = 0; rt < MAX_RENDER_TARGETS; rt++)
                colorPixelMapper[rt].setupDisplay(hRes, vRes, STAMP_WIDTH, STAMP_HEIGHT, genW, genH, scanW, scanH, overW, overH,
	    		                          displayW, displayH, samples, bytesPixel[rt]);
            if (zStencilBufferDefined)
	        zstPixelMapper.setupDisplay(hRes, vRes, STAMP_WIDTH, STAMP_HEIGHT, genW, genH, scanW, scanH, overW, overH,
				            displayW, displayH, samples, 4);

            break;

        case GPU_DISPLAY_Y_RES:
            /*  Write display vertical resolution register.  */
            vRes = data.uintVal;
            
	    //debugfile = fopen("debugDACSync.txt", "a+");
	    //fprintf(debugfile, "batch %d set vRes as %d\n", batchCounter, vRes);
	    //fflush(debugfile);
	    //fclose(debugfile);

            blt->setDisplayYRes(vRes);
            
            GPU_DEBUG_BOX(
                printf("DAC => Write GPU_DISPLAY_Y_RES = %d.\n", vRes);
            )

            //  Update the pixel mapper.
            samples = multisampling ? msaaSamples : 1;
	    for (u32bit rt = 0; rt < MAX_RENDER_TARGETS; rt++)
                colorPixelMapper[rt].setupDisplay(hRes, vRes, STAMP_WIDTH, STAMP_HEIGHT, genW, genH, scanW, scanH, overW, overH,
	    		                          displayW, displayH, samples, bytesPixel[rt]);
            if (zStencilBufferDefined)
                zstPixelMapper.setupDisplay(hRes, vRes, STAMP_WIDTH, STAMP_HEIGHT, genW, genH, scanW, scanH, overW, overH,
				            displayW, displayH, samples, 4);

            break;

        case GPU_D3D9_PIXEL_COORDINATES:
        
            //  Write use D3D9 pixel coordinates convention register.
            d3d9PixelCoordinates = data.booleanVal;
            
            //blt->setUseD3D9PixelCoordinates(d3d9PixelCoordinates);
            
            GPU_DEBUG_BOX(
                printf("DAC => Write GPU_D3D9_PIXEL_COORDINATE = %s\n", d3d9PixelCoordinates ? "TRUE" : "FALSE");
            )
            
            break;
            
        case GPU_VIEWPORT_INI_X:
            /*  Write viewport initial x coordinate register.  */
            startX = data.intVal;

            blt->setViewportStartX(startX);
            
            GPU_DEBUG_BOX(
                printf("DAC => Write GPU_VIEWPORT_INI_X = %d.\n", startX);
            )

            break;

        case GPU_VIEWPORT_INI_Y:
            /*  Write viewport initial y coordinate register.  */
            startY = data.intVal;

            blt->setViewportStartY(startY);
            
            GPU_DEBUG_BOX(
                printf("DAC => Write GPU_VIEWPORT_INI_Y = %d.\n", startY);
            )

            break;

        case GPU_VIEWPORT_WIDTH:
            /*  Write viewport width register.  */
            width = data.uintVal;

            blt->setViewportWidth(width);
            
            GPU_DEBUG_BOX(
                printf("DAC => Write GPU_VIEWPORT_WIDTH = %d.\n", width);
            )

            break;

        case GPU_VIEWPORT_HEIGHT:
            /*  Write viewport height register.  */
            height = data.uintVal;

            blt->setViewportHeight(height);
            
            GPU_DEBUG_BOX(
                printf("DAC => Write GPU_VIEWPORT_HEIGHT = %d.\n", height);
            )

            break;

        case GPU_COLOR_BUFFER_FORMAT:

            //  Write color buffer format.
            colorBufferFormat = data.txFormat;
            
            //  Aliased to render target 0.
            rtFormat[0] = colorBufferFormat;
            
            //  Set the bytes per pixel for the current color buffer format.
            switch(colorBufferFormat)
            {
                case GPU_RGBA8888:
                case GPU_RG16F:
                case GPU_R32F:
                    bytesPixel[0] = 4;
                    break;
                case GPU_RGBA16:
                case GPU_RGBA16F:
                    bytesPixel[0] = 8;
                    break;
                default:
                    panic("DAC", "processRegisterWrite", "Unsupported color buffer format.");
                    break;
            }
            
            GPU_DEBUG_BOX(
                printf("DAC => Write GPU_COLOR_BUFFER_FORMAT = ");
                switch(colorBufferFormat)
                {
                    case GPU_RGBA8888:
                        printf(" GPU_RGBA8888.\n");
                        break;
                        
                    case GPU_RG16F:
                        printf(" GPU_RG16F.\n");
                        break;

                    case GPU_R32F:
                        printf(" GPU_R32F.\n");
                        break;
                        
                    case GPU_RGBA16:
                        printf(" GPU_RGBA16.\n");
                        break;
                        
                    case GPU_RGBA16F:
                        printf(" GPU_RGBA16F.\n");
                        break;
                }
            )
            
            //  Set color buffer format in the blitter.
            blt->setColorBufferFormat(colorBufferFormat);
            
            //  Convert the float point clear color to the color buffer format.
            switch(colorBufferFormat)
            {
                case GPU_RGBA8888:
                
                    clearColorData[0] = u8bit(clearColor[0] * 255.0f);
                    clearColorData[1] = u8bit(clearColor[1] * 255.0f);
                    clearColorData[2] = u8bit(clearColor[2] * 255.0f);
                    clearColorData[3] = u8bit(clearColor[3] * 255.0f);
                    
                    break;

                case GPU_RG16F:
                
                    ((f16bit *) clearColorData)[0] = GPUMath::convertFP32ToFP16(clearColor[0]);
                    ((f16bit *) clearColorData)[1] = GPUMath::convertFP32ToFP16(clearColor[1]);
                    break;
                    
                case GPU_R32F:
                
                    ((f32bit *) clearColorData)[0] = clearColor[0];
                    break;
                
                case GPU_RGBA16:
                
                    ((u16bit *) clearColorData)[0] = u16bit(clearColor[0] * 65535.0f);
                    ((u16bit *) clearColorData)[1] = u16bit(clearColor[1] * 65535.0f);
                    ((u16bit *) clearColorData)[2] = u16bit(clearColor[2] * 65535.0f);
                    ((u16bit *) clearColorData)[3] = u16bit(clearColor[3] * 65535.0f);
                    
                    break;

                case GPU_RGBA16F:
                
                    ((f16bit *) clearColorData)[0] = GPUMath::convertFP32ToFP16(clearColor[0]);
                    ((f16bit *) clearColorData)[1] = GPUMath::convertFP32ToFP16(clearColor[1]);
                    ((f16bit *) clearColorData)[2] = GPUMath::convertFP32ToFP16(clearColor[2]);
                    ((f16bit *) clearColorData)[3] = GPUMath::convertFP32ToFP16(clearColor[3]);
                    
                    break;
                    
                default:
                    panic("DAC", "processRegisterWrite", "Unsupported color buffer format.");
                    break;
            }
            
            //  Update the pixel mapper.
            samples = multisampling ? msaaSamples : 1;
            colorPixelMapper[0].setupDisplay(hRes, vRes, STAMP_WIDTH, STAMP_HEIGHT, genW, genH, scanW, scanH, overW, overH,
				             displayW, displayH, samples, bytesPixel[0]);

            break;
            
        case GPU_COLOR_BUFFER_CLEAR:
        
            /*  Write color buffer clear color value.  */
            clearColor[0] = data.qfVal[0];
            clearColor[1] = data.qfVal[1];
            clearColor[2] = data.qfVal[2];
            clearColor[3] = data.qfVal[3];
            
            //  Convert the float point clear color to the color buffer format.
            switch(colorBufferFormat)
            {
                case GPU_RGBA8888:
                
                    clearColorData[0] = u8bit(clearColor[0] * 255.0f);
                    clearColorData[1] = u8bit(clearColor[1] * 255.0f);
                    clearColorData[2] = u8bit(clearColor[2] * 255.0f);
                    clearColorData[3] = u8bit(clearColor[3] * 255.0f);
                    
                    break;

                case GPU_RG16F:
                
                    ((f16bit *) clearColorData)[0] = GPUMath::convertFP32ToFP16(clearColor[0]);
                    ((f16bit *) clearColorData)[1] = GPUMath::convertFP32ToFP16(clearColor[1]);
                    break;
                    
                case GPU_R32F:
                
                    ((f32bit *) clearColorData)[0] = clearColor[0];
                    break;
                
                case GPU_RGBA16:
                
                    ((u16bit *) clearColorData)[0] = u16bit(clearColor[0] * 65535.0f);
                    ((u16bit *) clearColorData)[1] = u16bit(clearColor[1] * 65535.0f);
                    ((u16bit *) clearColorData)[2] = u16bit(clearColor[2] * 65535.0f);
                    ((u16bit *) clearColorData)[3] = u16bit(clearColor[3] * 65535.0f);
                    
                    break;

                case GPU_RGBA16F:
                
                    ((f16bit *) clearColorData)[0] = GPUMath::convertFP32ToFP16(clearColor[0]);
                    ((f16bit *) clearColorData)[1] = GPUMath::convertFP32ToFP16(clearColor[1]);
                    ((f16bit *) clearColorData)[2] = GPUMath::convertFP32ToFP16(clearColor[2]);
                    ((f16bit *) clearColorData)[3] = GPUMath::convertFP32ToFP16(clearColor[3]);
                    
                    break;
                    
                default:
                    panic("DAC", "processRegisterWrite", "Unsupported color buffer format.");
                    break;
            }

            blt->setClearColor(clearColor);

            GPU_DEBUG_BOX(
                printf("DAC => Write GPU_COLOR_BUFFER_CLEAR = (%f, %f, %f, %f).\n", clearColor[0], clearColor[1], clearColor[2], clearColor[3]);
            )

            break;

        case GPU_MULTISAMPLING:
        
            //  Write Multisampling enable flag.
            multisampling = data.booleanVal;
            
            GPU_DEBUG_BOX(
                printf("DAC => Write GPU_MULTISAMPLING = %s\n", multisampling?"TRUE":"FALSE");
            )
            
            //  Update the pixel mapper.
            samples = multisampling ? msaaSamples : 1;
	    for (u32bit rt = 0; rt < MAX_RENDER_TARGETS; rt++)
                colorPixelMapper[rt].setupDisplay(hRes, vRes, STAMP_WIDTH, STAMP_HEIGHT, genW, genH, scanW, scanH, overW, overH,
				                  displayW, displayH, samples, bytesPixel[rt]);
            zstPixelMapper.setupDisplay(hRes, vRes, STAMP_WIDTH, STAMP_HEIGHT, genW, genH, scanW, scanH, overW, overH,
				        displayW, displayH, samples, 4);

            blt->setMultisampling(multisampling);
                 
            break;
            
        case GPU_MSAA_SAMPLES:
        
            //  Write MSAA z samples per fragment register.
            msaaSamples = data.uintVal;
            

            GPU_DEBUG_BOX(
                printf("DAC => Write GPU_MSAA_SAMPLES = %d\n", msaaSamples);
            )

            //  Update the pixel mapper.
            samples = multisampling ? msaaSamples : 1;
	    for (u32bit rt = 0; rt < MAX_RENDER_TARGETS; rt++)
                colorPixelMapper[rt].setupDisplay(hRes, vRes, STAMP_WIDTH, STAMP_HEIGHT, genW, genH, scanW, scanH, overW, overH,
				                  displayW, displayH, samples, bytesPixel[rt]);
            zstPixelMapper.setupDisplay(hRes, vRes, STAMP_WIDTH, STAMP_HEIGHT, genW, genH, scanW, scanH, overW, overH,
				        displayW, displayH, samples, 4);

            blt->setMSAASamples(msaaSamples);
            
            break;            

        case GPU_ZSTENCIL_COMPRESSION:
        
            //  Write the z/stencil buffer compression enabled register.
            zStencilCompression = data.booleanVal;
            
            GPU_DEBUG_BOX(
                printf("DAC => Write GPU_ZSTENCIL_COMPRESSION = %s\n", zStencilCompression ? "ENABLED" : "DISABLED");
            )
            
            break;
            
        case GPU_COLOR_COMPRESSION:
        
            //  Write the color buffer compression enabled register.
            colorCompression = data.booleanVal;
            
            GPU_DEBUG_BOX(
                printf("DAC => Write GPU_COLOR_COMPRESSION = %s\n", colorCompression ? "ENABLED" : "DISABLED");
            )
            
            break;
            
        case GPU_BLIT_INI_X:
            /*  Write bit blit operation initial x coordinate register. */

            blt->setBlitIniX(data.uintVal);
            
            GPU_DEBUG_BOX(
                printf("DAC::Blitter => Write GPU_BLIT_INI_X = %x.\n", data.uintVal);
            )

            break;
            
        case GPU_BLIT_INI_Y:
            /*  Write blit initial y coordinate register. */

            blt->setBlitIniY(data.uintVal);
            
            GPU_DEBUG_BOX(
                printf("DAC::Blitter => Write GPU_BLIT_INI_Y = %x.\n", data.uintVal);
            )

            break;
            
        case GPU_BLIT_X_OFFSET:
            /*  Write bit blit operation offset x coordinate register. */

            blt->setBlitXOffset(data.uintVal);
            
            GPU_DEBUG_BOX(
                printf("DAC::Blitter => Write GPU_BLIT_X_OFFSET = %x.\n", data.uintVal);
            )

            break;
            
        case GPU_BLIT_Y_OFFSET:
            /*  Write bit blit operation offset y coordinate register. */

            blt->setBlitYOffset(data.uintVal);
            
            GPU_DEBUG_BOX(
                printf("DAC::Blitter => Write GPU_BLIT_Y_OFFSET = %x.\n", data.uintVal);
            )

            break;
                    
        case GPU_BLIT_WIDTH:
            /*  Write blit width register. */
            
            blt->setBlitWidth(data.uintVal);
            
            GPU_DEBUG_BOX(
                printf("DAC::Blitter => Write GPU_BLIT_WIDTH = %x.\n", data.uintVal);
            )

            break;
            
        case GPU_BLIT_HEIGHT:
            /*  Write blit height register. */
            
            blt->setBlitHeight(data.uintVal);

            GPU_DEBUG_BOX(
                printf("DAC::Blitter => Write GPU_BLIT_HEIGHT = %x.\n", data.uintVal);
            )

            break;
            
        case GPU_BLIT_DST_ADDRESS:
            /*  Write blit GPU memory destination address register. */
            
            blt->setDestAddress(data.uintVal);

            GPU_DEBUG_BOX(
                printf("DAC:Blitter => Write GPU_BLIT_DST_ADDRESS = %x.\n", data.uintVal);
            )

            break;

        case GPU_BLIT_DST_TX_WIDTH2:
            /*  Write blit ceiling log 2 of texture width register. */
            
            blt->setDestTextWidth2(data.uintVal);

            GPU_DEBUG_BOX(
                printf("DAC::Blitter => Write GPU_BLIT_DST_TX_WIDTH2 = %x.\n", data.txFormat);
            )

            break;
            
        case GPU_BLIT_DST_TX_FORMAT:
            /*  Write blit texture destination format register. */
            
            blt->setDestTextFormat(data.txFormat);

            GPU_DEBUG_BOX(
                printf("DAC::Blitter => Write GPU_BLIT_DST_TX_FORMAT = ");
                
                switch(data.txFormat)
                {
                    case GPU_ALPHA8:
                        printf("GPU_ALPHA8\n");
                        break;
                    case GPU_ALPHA12:
                        printf("GPU_ALPHA12\n");
                        break;
                    
                    case GPU_ALPHA16:
                        printf("GPU_ALPHA16\n");
                        break;
                    
                    case GPU_DEPTH_COMPONENT16:
                        printf("GPU_DEPTH_COMPONENT16\n");
                        break;
                    
                    case GPU_DEPTH_COMPONENT24:
                        printf("GPU_DEPTH_COMPONENT24\n");
                        break;

                    case GPU_DEPTH_COMPONENT32:
                        printf("GPU_DEPTH_COMPONENT32\n");
                        break;
                    
                    case GPU_LUMINANCE8:
                        printf("GPU_LUMINANCE8\n");
                        break;

                    case GPU_LUMINANCE8_SIGNED:
                        printf("GPU_LUMINANCE8_SIGNED\n");
                        break;

                    case GPU_LUMINANCE12:
                        printf("GPU_LUMINANCE12\n");
                        break;

                    case GPU_LUMINANCE16:
                        printf("GPU_LUMINANCE16\n");
                        break;
                    
                    case GPU_LUMINANCE4_ALPHA4:
                        printf("GPU_LUMINANCE4_ALPHA4\n");
                        break;
                        
                    case GPU_LUMINANCE6_ALPHA2:
                        printf("GPU_LUMINANCE6_ALPHA2\n");
                        break;
                        
                    case GPU_LUMINANCE8_ALPHA8:
                        printf("GPU_LUMINANCE8_ALPHA8\n");
                        break;

                    case GPU_LUMINANCE8_ALPHA8_SIGNED:
                        printf("GPU_LUMINANCE8_ALPHA8_SIGNED\n");
                        break;
                    
                    case GPU_LUMINANCE12_ALPHA4:
                        printf("GPU_LUMINANCE12_ALPHA4\n");
                        break;
                    
                    case GPU_LUMINANCE12_ALPHA12:
                        printf("GPU_LUMINANCE12_ALPHA12\n");
                        break;

                    case GPU_LUMINANCE16_ALPHA16:
                        printf("GPU_LUMINANCE16_ALPHA16\n");
                        break;

                    case GPU_INTENSITY8:
                        printf("GPU_INTENSITY8\n");
                        break;
                    
                    case GPU_INTENSITY12:
                        printf("GPU_INTENSITY12\n");
                        break;
                    
                    case GPU_INTENSITY16:
                        printf("GPU_INTENSITY16\n");
                        break;
                    case GPU_RGB332:
                        printf("GPU_RGB332\n");
                        break;

                    case GPU_RGB444:
                        printf("GPU_RGB444\n");
                        break;
                    
                    case GPU_RGB555:
                        printf("GPU_RGB555\n");
                        break;

                    case GPU_RGB565:
                        printf("GPU_RGB565\n");
                        break;

                    case GPU_RGB888:
                        printf("GPU_RGB888\n");
                        break;
                    
                    case GPU_RGB101010:
                        printf("GPU_RGB101010\n");
                        break;
                    case GPU_RGB121212:
                        printf("GPU_RGB121212\n");
                        break;
                    
                    case GPU_RGBA2222:
                        printf("GPU_RGBA2222\n");
                        break;
                    
                    case GPU_RGBA4444:
                        printf("GPU_RGBA4444\n");
                        break;
                        
                    case GPU_RGBA5551:
                        printf("GPU_RGBA5551\n");
                        break;
                    
                    case GPU_RGBA8888:
                        printf("GPU_RGBA8888\n");
                        break;
                    
                    case GPU_RGBA1010102:
                        printf("GPU_RGB1010102\n");
                        break;
                    
                    default:
                        panic("DAC", "processRegisterWrite", "Unsupported texture format.");
                        break;
                }
            )

            break;

        case GPU_BLIT_DST_TX_BLOCK:
            /*  Write blit texture destination format register. */
            
            blt->setDestTextBlock(data.txBlocking);

            GPU_DEBUG_BOX(
                printf("DAC::Blitter => Write GPU_BLIT_DST_TX_BLOCK = ");
                
                switch(data.txBlocking)
                {
                    case GPU_TXBLOCK_TEXTURE:
                        printf("GPU_TXBLOCK_TEXTURE.\n");
                        break;

                    case GPU_TXBLOCK_FRAMEBUFFER:
                        printf("GPU_TXBLOCK_FRAMEBUFFER.\n");
                        break;

                    default:
                        panic("DAC", "processRegisterWrite", "Unsupported texture blocking mode.");
                        break;
                }
            )

            break;

        case GPU_FRONTBUFFER_ADDR:
            /*  Write front color buffer address register.  */
            frontBuffer = data.uintVal;

            GPU_DEBUG_BOX(
                printf("DAC => Write GPU_FRONTBUFFER_ADDR = %08x.\n",
                    frontBuffer);
            )
            
            break;

        case GPU_BACKBUFFER_ADDR:
            /*  Write back color buffer address register.  */
            backBuffer = data.uintVal;

            GPU_DEBUG_BOX(
                printf("DAC => Write GPU_BACKBUFFER_ADDR = %08x.\n",
                    backBuffer);
            )
            
            blt->setBackBufferAddress(backBuffer);
            
            //  Aliased to render target 0.
            rtAddress[0] = backBuffer;
            
            break;

        case GPU_Z_BUFFER_CLEAR:
        
            //  Write depth clear value.
            clearDepth = data.uintVal;

            GPU_DEBUG_BOX(
                printf("DAC => Write GPU_Z_BUFFER_CLEAR = %x.\n", clearDepth);
            )

            break;

        case GPU_STENCIL_BUFFER_CLEAR:

            //  Write stencil clear value.
            clearStencil = (u8bit) (data.uintVal & 0xff);

            GPU_DEBUG_BOX(
                printf("DAC => Write GPU_STENCIL_BUFFER_CLEAR = %x.\n", clearStencil);
            )

            break;

        case GPU_Z_BUFFER_BIT_PRECISSION:

            //  Write z buffer bit precission register.
            depthPrecission = data.uintVal;

            GPU_DEBUG_BOX(
                printf("DAC => Write GPU_Z_BUFFER_BIT_PRECISSION = %x.\n", depthPrecission);
            )

            break;

        case GPU_ZSTENCILBUFFER_ADDR:
        
            //  Write z stencil buffer address register.
            zStencilBuffer = data.uintVal;

	    //debugfile = fopen("debugDACSync.txt", "a+");
	    //fprintf(debugfile, "GPU[%d] batch %d set zstBuffer = 0x%x\n", gpuId, batchCounter, data.uintVal);
	    //fflush(debugfile);
	    //fclose(debugfile);
	    
            GPU_DEBUG_BOX(
                printf("DAC => Write GPU_ZSTENCILBUFFER_ADDR = %08x.\n", zStencilBuffer);
            )

            break;

        case GPU_RENDER_TARGET_ENABLE:
        
            //  Check render target index.
            GPU_ASSERT(
                if (subreg >= MAX_RENDER_TARGETS)
                    panic("DAC", "processRegisterWrite", "Render target index out of range.");
            )

            //  Write render target enable register.
            rtEnable[subreg] = data.booleanVal;
            
	    //debugfile = fopen("debugDACSync.txt", "a+");
	    //fprintf(debugfile, "GPU[%d] batch %d set rtEnable[%d] = %s\n",
	    //        gpuId, batchCounter, subreg, data.booleanVal ? "T" : "F");
	    //fflush(debugfile);
	    //fclose(debugfile);
	    
            GPU_DEBUG_BOX(
                printf("DAC => Write GPU_RENDER_TARGET_ENABLE[%d] = %s\n", subreg, rtEnable[subreg] ? "TRUE" : "FALSE");
            )            
            
            break;

        case GPU_RENDER_TARGET_FORMAT:
        
            //  Check render target index.
            GPU_ASSERT(
                if (subreg >= MAX_RENDER_TARGETS)
                    panic("DAC", "processRegisterWrite", "Render target index out of range.");
            )

            //  Write render target format register.
            rtFormat[subreg] = data.txFormat;
            
            GPU_DEBUG_BOX(
                printf("DAC => Write GPU_RENDER_TARGET_FORMAT[%d] = ", subreg);
                switch(rtFormat[subreg])
                {
                    case GPU_RGBA8888:
                        printf(" GPU_RGBA8888.\n");
                        break;
                        
                    case GPU_RG16F:
                        printf(" GPU_RG16F.\n");
                        break;

                    case GPU_R32F:
                        printf(" GPU_R32F.\n");
                        break;
                        
                    case GPU_RGBA16:
                        printf(" GPU_RGBA16.\n");
                        break;
                        
                    case GPU_RGBA16F:
                        printf(" GPU_RGBA16F.\n");
                        break;
                    default:
                        panic("DAC", "processRegisterWrite", "Unsupported render target format.");
                        break;
                }
            )            
                
	    //  Set the bytes per pixel for the current color buffer format.
            switch(rtFormat[subreg])
            {
                case GPU_RGBA8888:
                case GPU_RG16F:
                case GPU_R32F:
                    bytesPixel[subreg] = 4;
                    break;
                case GPU_RGBA16:
                case GPU_RGBA16F:
                    bytesPixel[subreg] = 8;
                    break;
                default:
                    panic("DAC", "processRegisterWrite", "Unsupported color buffer format.");
                    break;
            }
                
            //  Render target 0 is aliased to the backbuffer.
            if (subreg == 0)
            {
                colorBufferFormat = rtFormat[0];
                
                //  Set the bytes per pixel for the current color buffer format.
                //switch(colorBufferFormat)
                //{
                //    case GPU_RGBA8888:
                //    case GPU_RG16F:
                //    case GPU_R32F:
                //        bytesPixel = 4;
                //        break;
                //    case GPU_RGBA16:
                //    case GPU_RGBA16F:
                //        bytesPixel = 8;
                //        break;
                //    default:
                //        panic("DAC", "processRegisterWrite", "Unsupported color buffer format.");
                //        break;
                //}
                
                //  Set color buffer format in the blitter.
                blt->setColorBufferFormat(colorBufferFormat);
                
                //  Convert the float point clear color to the color buffer format.
                switch(colorBufferFormat)
                {
                    case GPU_RGBA8888:
                    
                        clearColorData[0] = u8bit(clearColor[0] * 255.0f);
                        clearColorData[1] = u8bit(clearColor[1] * 255.0f);
                        clearColorData[2] = u8bit(clearColor[2] * 255.0f);
                        clearColorData[3] = u8bit(clearColor[3] * 255.0f);
                        
                        break;

                    case GPU_RG16F:
                    
                        ((f16bit *) clearColorData)[0] = GPUMath::convertFP32ToFP16(clearColor[0]);
                        ((f16bit *) clearColorData)[1] = GPUMath::convertFP32ToFP16(clearColor[1]);
                        break;
                        
                    case GPU_R32F:
                    
                        ((f32bit *) clearColorData)[0] = clearColor[0];
                        break;
                    
                    case GPU_RGBA16:
                    
                        ((u16bit *) clearColorData)[0] = u16bit(clearColor[0] * 65535.0f);
                        ((u16bit *) clearColorData)[1] = u16bit(clearColor[1] * 65535.0f);
                        ((u16bit *) clearColorData)[2] = u16bit(clearColor[2] * 65535.0f);
                        ((u16bit *) clearColorData)[3] = u16bit(clearColor[3] * 65535.0f);
                        
                        break;

                    case GPU_RGBA16F:
                    
                        ((f16bit *) clearColorData)[0] = GPUMath::convertFP32ToFP16(clearColor[0]);
                        ((f16bit *) clearColorData)[1] = GPUMath::convertFP32ToFP16(clearColor[1]);
                        ((f16bit *) clearColorData)[2] = GPUMath::convertFP32ToFP16(clearColor[2]);
                        ((f16bit *) clearColorData)[3] = GPUMath::convertFP32ToFP16(clearColor[3]);
                        
                        break;
                        
                    default:
                        panic("DAC", "processRegisterWrite", "Unsupported color buffer format.");
                        break;
                }
                
                //  Update the pixel mapper.
                //samples = multisampling ? msaaSamples : 1;
                //colorPixelMapper.setupDisplay(hRes, vRes, STAMP_WIDTH, STAMP_HEIGHT, genW, genH, scanW, scanH, overW, overH, displayW, displayH, samples, bytesPixel);
            }
            
	    //  Update the pixel mapper.
            samples = multisampling ? msaaSamples : 1;
            colorPixelMapper[subreg].setupDisplay(hRes, vRes, STAMP_WIDTH, STAMP_HEIGHT, genW, genH, scanW, scanH, overW, overH,
				                  displayW, displayH, samples, bytesPixel[subreg]);
            
            break;

        case GPU_RENDER_TARGET_ADDRESS:
        
            //  Check render target index.
            GPU_ASSERT(
                if (subreg >= MAX_RENDER_TARGETS)
                    panic("DAC", "processRegisterWrite", "Render target index out of range.");
            )

            //  Write render target address register.
            rtAddress[subreg] = data.uintVal;
	    rtSynced[subreg] = false;

	    //debugfile = fopen("debugDACSync.txt", "a+");
	    //fprintf(debugfile, "GPU[%d] batch %d set rtAddress[%d] = 0x%x\n", gpuId, batchCounter, subreg, data.uintVal);
	    //fflush(debugfile);
	    //fclose(debugfile);
	    
            GPU_DEBUG_BOX(
                printf("DAC => Write GPU_RENDER_TARGET_ADDRESS[%d] = %08x\n", subreg, rtAddress[subreg]);
            )
           
            //  Render target 0 is aliased to the back buffer.
            if (subreg == 0)
            {
                backBuffer = rtAddress[0];
                blt->setBackBufferAddress(backBuffer);
            }
            
            break;

        default:
            panic("DAC", "processRegisterWrite", "Unsupported register.");
            break;
    }

}

//  Initializes the refresh/dumping of the color buffer.
void DAC::startRefresh()
{
    //  Reset number of free queue entries.
    numFree = blockQueueSize;

    //  Reset number of blocks to request.
    numToRequest = 0;

    //  Reset number of blocks to decompress.
    numToDecompress = 0;

    //  Reset free, to requeuest and to decompress queue pointers.
    nextFree = nextRequest = nextDecompress = 0;

    //  Reset decompress cycles.  */
    decompressCycles = 0;

    /*  Reset color buffer requested bytes (blocks).  */
    requested = 0;

    //  Setup the display in the pixel mapper.
    //u32bit samples = multisampling ? msaaSamples : 1;
    //pixelMapper.setupDisplay(hRes, vRes, STAMP_WIDTH, STAMP_HEIGHT, genW, genH, scanW, scanH, overW, overH, samples, bytesPixel);
    
    //  Check if multisampling is enabled.
    /*if (!multisampling)
    {
        //  Set color buffer size.
        //  Takes into account that the color buffer is stored in tiles
        //  of stamps:
        //
        //    size = horizontal tiles x vertical tiles x tile size in bytes
        //
        colorBufferSize2 = ((u32bit) ceil(vRes / (f32bit) (overH * scanH * genH * STAMP_HEIGHT))) *
            ((u32bit) ceil(hRes / (f32bit) (overW * scanW * genW * STAMP_WIDTH))) *
            overW * overH * scanW * scanH * genW * genH * STAMP_WIDTH * STAMP_HEIGHT * bytesPixel;
    }
    else
    {
        //  Compute color buffer size for all the samples.
        colorBufferSize2 = ((u32bit) ceil(vRes / (f32bit) (overH * scanH * genH * STAMP_HEIGHT))) *
            ((u32bit) ceil(hRes / (f32bit) (overW * scanW * genW * STAMP_WIDTH))) *
            overW * overH * scanW * scanH * genW * genH * STAMP_WIDTH * STAMP_HEIGHT * bytesPixel * msaaSamples;
    }*/
    
    //  Compute color buffer size.
    colorBufferSize = colorPixelMapper[0].computeFrameBufferSize();
  
    GPU_DEBUG_BOX(
        printf("DAC => Color Buffer Size %d (%d x %d)\n",
            colorBufferSize, hRes, vRes);
    )

    /*  NOTE THERE ARE MORE EFFICIENT WAYS TO DO THIS.  */

    /*  Allocate space for the color buffer.  */
    if (!colorBuffer)
        colorBuffer = new u8bit[colorBufferSize];

    /*  Change state to SWAP.  */
    state = RAST_SWAP;
}

#define GAMMA(x) f32bit(GPU_POWER(f64bit(x), f64bit(1.0f / 2.2f)))
#define LINEAR(x) f32bit(GPU_POWER(f64bit(x), f64bit(2.2f)))
//#define GAMMA(x) (x)

//#define SAVE_AS_PNG

/*  Writes the current color buffer as a ppm file.  */
void DAC::writeColorBuffer()
{
    char filename[256];

#ifdef SAVE_AS_PNG
    static u8bit *data = 0;
    static u32bit dataSize = 0;
    
    //  Check if the buffer is large enough.
    if (dataSize < (hRes * vRes * 4))
    {
        //  Check if the old buffer must be deleted.
        if (data != NULL)
            delete[] data;
            
        //  Set the new buffer size.            
        dataSize = hRes * vRes * 4;
        
        //  Create the new buffer.
        data = new u8bit[dataSize];
    }
#endif

    if (lastRSCommand->getCommand() == RSCOM_DUMP_COLOR)
    {
        //  Create current frame filename.
        sprintf(filename, "frame%04d-batch%05d.sim", frameCounter, batchCounter);
    }
    else
    {
        //  Create current frame filename.
        sprintf(filename, "frame%04d.sim", frameCounter);
    }

    
#ifndef SAVE_AS_PNG
    FILE *fout;

    char filenamePPM[128];
    
    sprintf(filenamePPM, "%s.ppm", filename);
    
    //  Open/Create the file for the current frame.
    fout = fopen(filenamePPM, "wb");

    //  Check if the file was correctly created.
    GPU_ASSERT(
        if (fout == NULL)
            panic("DAC", "writeColorBuffer", "Error creating frame color output file.");
    )

    //  Write file header.

    //  Write magic number.
    fprintf(fout, "P6\n");

    //  Write frame size.
    fprintf(fout, "%d %d\n", hRes, vRes);

    //  Write color component maximum value.
    fprintf(fout, "255\n");
#endif    


    u8bit red = 255;
    u8bit green = 255;
    u8bit blue = 255;

    //  Check if multisampling is enabled.
    if (!multisampling)
    {    
        s32bit top = d3d9PixelCoordinates ? 0 : (vRes -1);
        s32bit bottom = d3d9PixelCoordinates ? (vRes - 1) : 0;
        s32bit nextLine = d3d9PixelCoordinates ? +1 : -1;
        
        //  Do this for the whole picture now.
        for (s32bit y = top; y != (bottom + nextLine); y = y + nextLine)
        {
            for (s32bit x = 0; x < s32bit(hRes); x++)
            {
                /**  NOTE THERE SURE ARE FASTER WAYS TO DO THIS ...  **/
                
                u32bit address = colorPixelMapper[0].computeAddress(x, y);
                
                //  Convert data from the color color buffer to 8-bit PPM format.
                switch(colorBufferFormat)
                {
                    case GPU_RGBA8888:
                        red   = colorBuffer[address];
                        green = colorBuffer[address + 1];
                        blue  = colorBuffer[address + 2];
                        break;
                        
                    case GPU_RG16F:
                        red   = u8bit(GPU_MIN(GPU_MAX(GPUMath::convertFP16ToFP32(*((u16bit *) &colorBuffer[address + 0])), 0.0f), 1.0f) * 255.0f);
                        green = u8bit(GPU_MIN(GPU_MAX(GPUMath::convertFP16ToFP32(*((u16bit *) &colorBuffer[address + 2])), 0.0f), 1.0f) * 255.0f);
                        blue  = 0;
                        break;
                        
                    case GPU_R32F:
                    
                        red   = u8bit(GPU_MIN(GPU_MAX(*((f32bit *) &colorBuffer[address]), 0.0f), 1.0f) * 255.0f);
                        green = 0;
                        blue  = 0;
                        break;

                    case GPU_RGBA16:
                        red   = u8bit(GPU_MIN(GPU_MAX((*((u16bit *) &colorBuffer[address + 0])) / 65535.0f, 0.0f), 1.0f) * 255.0f);
                        green = u8bit(GPU_MIN(GPU_MAX((*((u16bit *) &colorBuffer[address + 2])) / 65535.0f, 0.0f), 1.0f) * 255.0f);
                        blue  = u8bit(GPU_MIN(GPU_MAX((*((u16bit *) &colorBuffer[address + 4])) / 65535.0f, 0.0f), 1.0f) * 255.0f);
                        break;
                        
                    case GPU_RGBA16F:
                        red   = u8bit(GPU_MIN(GPU_MAX(GPUMath::convertFP16ToFP32(*((u16bit *) &colorBuffer[address + 0])), 0.0f), 1.0f) * 255.0f);
                        green = u8bit(GPU_MIN(GPU_MAX(GPUMath::convertFP16ToFP32(*((u16bit *) &colorBuffer[address + 2])), 0.0f), 1.0f) * 255.0f);
                        blue  = u8bit(GPU_MIN(GPU_MAX(GPUMath::convertFP16ToFP32(*((u16bit *) &colorBuffer[address + 4])), 0.0f), 1.0f) * 255.0f);
                        break;
                }
                
                //  Write color to the file.
#ifndef SAVE_AS_PNG                
                fputc((char) red, fout);
                fputc((char) green, fout);
                fputc((char) blue, fout);
#else                
                u32bit yImage = d3d9PixelCoordinates ? y : (vRes - 1) - y;
                data[(yImage * hRes + x) * 4 + 2] = red;
                data[(yImage * hRes + x) * 4 + 1] = green;
                data[(yImage * hRes + x) * 4 + 0] = blue;
                //data[(yImage * hRes + x) * 4 + 3] = alpha;
                data[(yImage * hRes + x) * 4 + 3] = 255;
#endif                
            }
        }
    }
    else
    {
        QuadFloat sampleColors[MAX_MSAA_SAMPLES];
        QuadFloat resolvedColor;
        QuadFloat referenceColor;
        QuadFloat currentColor;
        
        s32bit top = d3d9PixelCoordinates ? 0 : (vRes - 1);
        s32bit bottom = d3d9PixelCoordinates ? (vRes - 1) : 0;
        
        //  Do this for the whole picture now.
        for (s32bit y = top; y >= bottom; y--)
        {
            for(s32bit x = 0; x < s32bit(hRes); x++)
            {               
                u32bit address = colorPixelMapper[0].computeAddress(x, y);

                //  Zero resolved color.
                resolvedColor[0] = 0.0f;
                resolvedColor[1] = 0.0f;
                resolvedColor[2] = 0.0f;
                
                //  Convert data from the color color buffer 32 bit fp internal format.
                switch(colorBufferFormat)
                {
                    case GPU_RGBA8888:
                        referenceColor[0] = f32bit(colorBuffer[address + 0]) / 255.0f;
                        referenceColor[1] = f32bit(colorBuffer[address + 1]) / 255.0f;
                        referenceColor[2] = f32bit(colorBuffer[address + 2]) / 255.0f;
                        break;
                
                    case GPU_RG16F:
                        referenceColor[0] = GPUMath::convertFP16ToFP32(*((u16bit *) &colorBuffer[address + 0]));
                        referenceColor[1] = GPUMath::convertFP16ToFP32(*((u16bit *) &colorBuffer[address + 2]));
                        referenceColor[2] = 0.0f;
                        break;
                        
                    case GPU_R32F:
                        referenceColor[0] = *((f32bit *) &colorBuffer[address]);
                        referenceColor[1] = 0.0f;
                        referenceColor[2] = 0.0f;
                        break;                        
                                
                    case GPU_RGBA16:
                        referenceColor[0] = (*((u16bit *) &colorBuffer[address + 0])) / 65535.0f;
                        referenceColor[1] = (*((u16bit *) &colorBuffer[address + 2])) / 65535.0f;
                        referenceColor[2] = (*((u16bit *) &colorBuffer[address + 4])) / 65535.0f;
                        break;

                    case GPU_RGBA16F:
                        referenceColor[0] = GPUMath::convertFP16ToFP32(*((u16bit *) &colorBuffer[address + 0]));
                        referenceColor[1] = GPUMath::convertFP16ToFP32(*((u16bit *) &colorBuffer[address + 2]));
                        referenceColor[2] = GPUMath::convertFP16ToFP32(*((u16bit *) &colorBuffer[address + 4]));
                        break;
                }
                
                bool fullCoverage = true;

                //  Accumulate the color for all the samples in the pixel
                for(u32bit i = 0; i < msaaSamples; i++)
                {
                    //  Convert data from the color color buffer 32 bit fp internal format.
                    switch(colorBufferFormat)
                    {
                        case GPU_RGBA8888:
                            currentColor[0] = f32bit(colorBuffer[address + i * 4 + 0]) / 255.0f;
                            currentColor[1] = f32bit(colorBuffer[address + i * 4 + 1]) / 255.0f;
                            currentColor[2] = f32bit(colorBuffer[address + i * 4 + 2]) / 255.0f;
                            break;
                            
                        case GPU_RG16F:
                            currentColor[0] = GPUMath::convertFP16ToFP32(*((u16bit *) &colorBuffer[address + i * 4 + 0]));
                            currentColor[1] = GPUMath::convertFP16ToFP32(*((u16bit *) &colorBuffer[address + i * 4 + 2]));
                            currentColor[2] = 0.0f;
                            break;
                            
                        case GPU_R32F:
                            currentColor[0] = *((f32bit *) &colorBuffer[address + i * 4]);
                            currentColor[1] = 0.0f;
                            currentColor[2] = 0.0f;
                            break;                        

                        case GPU_RGBA16:
                            currentColor[0] = (*((u16bit *) &colorBuffer[address + i * 8 + 0])) / 65535.0f;
                            currentColor[1] = (*((u16bit *) &colorBuffer[address + i * 8 + 2])) / 65535.0f;
                            currentColor[2] = (*((u16bit *) &colorBuffer[address + i * 8 + 4])) / 65535.0f;
                            break;
                                    
                        case GPU_RGBA16F:
                            currentColor[0] = GPUMath::convertFP16ToFP32(*((u16bit *) &colorBuffer[address + i * 8 + 0]));
                            currentColor[1] = GPUMath::convertFP16ToFP32(*((u16bit *) &colorBuffer[address + i * 8 + 2]));
                            currentColor[2] = GPUMath::convertFP16ToFP32(*((u16bit *) &colorBuffer[address + i * 8 + 4]));
                            break;
                    }

                    sampleColors[i][0] = currentColor[0];
                    sampleColors[i][1] = currentColor[1];
                    sampleColors[i][2] = currentColor[2];
                    
                    resolvedColor[0] += LINEAR(currentColor[0]);
                    resolvedColor[1] += LINEAR(currentColor[1]);
                    resolvedColor[2] += LINEAR(currentColor[2]);
                    
                    fullCoverage = fullCoverage && (referenceColor[0] == currentColor[0])
                                                && (referenceColor[1] == currentColor[1])
                                                && (referenceColor[2] == currentColor[2]);
                }
                
                //  Check if there is a single sample for the pixel
                if (fullCoverage)
                {
                    //  Convert from RGBA32F (internal format) to RGBA8 (PPM format)
                    red   = u8bit(GPU_MIN(GPU_MAX(referenceColor[0], 0.0f), 1.0f) * 255.0f);
                    green = u8bit(GPU_MIN(GPU_MAX(referenceColor[1], 0.0f), 1.0f) * 255.0f);
                    blue  = u8bit(GPU_MIN(GPU_MAX(referenceColor[2], 0.0f), 1.0f) * 255.0f);
                    
                }
                else
                {
                    //  Resolve color as the average of all the sample colors.
                    resolvedColor[0] = GAMMA(resolvedColor[0] / f32bit(msaaSamples));
                    resolvedColor[1] = GAMMA(resolvedColor[1] / f32bit(msaaSamples));
                    resolvedColor[2] = GAMMA(resolvedColor[2] / f32bit(msaaSamples));

                    //  Convert from RGBA32F (internal format) to RGBA8 (PPM format)
                    red   = u8bit(GPU_MIN(GPU_MAX(resolvedColor[0], 0.0f), 1.0f) * 255.0f);
                    green = u8bit(GPU_MIN(GPU_MAX(resolvedColor[1], 0.0f), 1.0f) * 255.0f);
                    blue  = u8bit(GPU_MIN(GPU_MAX(resolvedColor[2], 0.0f), 1.0f) * 255.0f);
                }

#ifndef SAVE_AS_PNG
                //  Write pixel color into the output file.
                fputc(char(red)  , fout);
                fputc(char(green), fout);
                fputc(char(blue) , fout);
#else   //  SAVE_AS_PNG
                u32bit yImage = d3d9PixelCoordinates ? y : (vRes - 1) - y;
                data[(yImage * hRes + x) * 4 + 2] = red;
                data[(yImage * hRes + x) * 4 + 1] = green;
                data[(yImage * hRes + x) * 4 + 0] = blue;
                //data[(yImage * hRes + x) * 4 + 3] = alpha;
                data[(yImage * hRes + x) * 4 + 3] = 255;
#endif  //  SAVE_AS_PNG                    

            }                    
        }                
    }
    
#ifndef SAVE_AS_PNG    
    fclose(fout);
#else    
    ImageSaver::getInstance().savePNG(filename, hRes, vRes, data);
#endif    
}


//  Writes the current depth buffer to a file.
void DAC::writeDepthBuffer()
{
    char filename[128];

#ifdef SAVE_AS_PNG
    static u8bit *data = 0;
    static u32bit dataSize = 0;
    
    //  Check if the buffer is large enough.
    if (dataSize < (hRes * vRes * 4))
    {
        //  Check if the old buffer must be deleted.
        if (data != NULL)
            delete[] data;
            
        //  Set the new buffer size.            
        dataSize = hRes * vRes * 4;
        
        //  Create the new buffer.
        data = new u8bit[dataSize];
    }

#endif

    if (lastRSCommand->getCommand() == RSCOM_DUMP_DEPTH)
    {
        //  Create current frame filename.
        sprintf(filename, "depth%04d-batch%05d.sim", frameCounter, batchCounter);
    }
    else
    {
        //  Create current frame filename.
        sprintf(filename, "depth%04d.sim", frameCounter);
    }
    
#ifndef SAVE_AS_PNG
    
    char filenamePPM[128];

    //  Add file extension.
    sprintf(filenamePPM, "%s.ppm", filename);
    
    FILE *fout;

    //  Open/Create the file for the current frame.
    fout = fopen(filenamePPM, "wb");

    //  Check if the file was correctly created.
    GPU_ASSERT(
        if (fout == NULL)
            panic("DAC", "writeDepthBuffer", "Error creating depth output file.");
    )

    //  Write file header.

    //  Write magic number.
    fprintf(fout, "P6\n");

    //  Write frame size.  */
    fprintf(fout, "%d %d\n", hRes, vRes);

    //  Write color component maximum value.
    fprintf(fout, "255\n");
#endif

    u8bit red = 255;
    u8bit green = 255;
    u8bit blue = 255;

    //  Check if multisampling is enabled.
    if (!multisampling)
    {    
        s32bit top = d3d9PixelCoordinates ? 0 : (vRes -1);
        s32bit bottom = d3d9PixelCoordinates ? (vRes - 1) : 0;
        s32bit nextLine = d3d9PixelCoordinates ? +1 : -1;
        
        //  Do this for the whole picture now.
        for (s32bit y = top; y != (bottom + nextLine); y = y + nextLine)
        {
            for (s32bit x = 0; x < s32bit(hRes); x++)
            {
                //  Compute address of the pixel.
                u32bit address = zstPixelMapper.computeAddress(x, y);
                
                // Invert for better reading with irfan view.
                red   = zstBuffer[address + 2];
                green = zstBuffer[address + 1];
                blue  = zstBuffer[address + 0];                      
                
                //  Write color to the file.
#ifndef SAVE_AS_PNG                
                fputc((char) red, fout);
                fputc((char) green, fout);
                fputc((char) blue, fout);
#else                
                u32bit yImage = d3d9PixelCoordinates ? y : (vRes - 1) - y;
                data[(yImage * hRes + x) * 4 + 2] = red;
                data[(yImage * hRes + x) * 4 + 1] = green;
                data[(yImage * hRes + x) * 4 + 0] = blue;
                //data[(yImage * hRes + x) * 4 + 3] = alpha;
                data[(yImage * hRes + x) * 4 + 3] = 255;
#endif                
            }
        }
    }
    else
    {
    
        panic("DAC", "writeDepthBuffer", "Multisampling not supported.");
        
        QuadFloat sampleColors[MAX_MSAA_SAMPLES];
        QuadFloat resolvedColor;
        QuadFloat referenceColor;
        QuadFloat currentColor;
        
        s32bit top = d3d9PixelCoordinates ? 0 : (vRes - 1);
        s32bit bottom = d3d9PixelCoordinates ? (vRes - 1) : 0;
        
        //  Do this for the whole picture now.
        for (s32bit y = top; y >= bottom; y--)
        {
            for(s32bit x = 0; x < s32bit(hRes); x++)
            {               
                u32bit address = zstPixelMapper.computeAddress(x, y);

                //  Zero resolved color.
                resolvedColor[0] = 0.0f;
                resolvedColor[1] = 0.0f;
                resolvedColor[2] = 0.0f;
                
                //  Convert data from the color color buffer 32 bit fp internal format.
                switch(colorBufferFormat)
                {
                    case GPU_RGBA8888:
                        referenceColor[0] = f32bit(colorBuffer[address + 0]) / 255.0f;
                        referenceColor[1] = f32bit(colorBuffer[address + 1]) / 255.0f;
                        referenceColor[2] = f32bit(colorBuffer[address + 2]) / 255.0f;
                        break;
                
                    case GPU_RG16F:
                        referenceColor[0] = GPUMath::convertFP16ToFP32(*((u16bit *) &colorBuffer[address + 0]));
                        referenceColor[1] = GPUMath::convertFP16ToFP32(*((u16bit *) &colorBuffer[address + 2]));
                        referenceColor[2] = 0.0f;
                        break;
                        
                    case GPU_R32F:
                        referenceColor[0] = *((f32bit *) &colorBuffer[address]);
                        referenceColor[1] = 0.0f;
                        referenceColor[2] = 0.0f;
                        break;                        
                                
                    case GPU_RGBA16:
                        referenceColor[0] = (*((u16bit *) &colorBuffer[address + 0])) / 65535.0f;
                        referenceColor[1] = (*((u16bit *) &colorBuffer[address + 2])) / 65535.0f;
                        referenceColor[2] = (*((u16bit *) &colorBuffer[address + 4])) / 65535.0f;
                        break;

                    case GPU_RGBA16F:
                        referenceColor[0] = GPUMath::convertFP16ToFP32(*((u16bit *) &colorBuffer[address + 0]));
                        referenceColor[1] = GPUMath::convertFP16ToFP32(*((u16bit *) &colorBuffer[address + 2]));
                        referenceColor[2] = GPUMath::convertFP16ToFP32(*((u16bit *) &colorBuffer[address + 4]));
                        break;
                }
                
                bool fullCoverage = true;

                //  Accumulate the color for all the samples in the pixel
                for(u32bit i = 0; i < msaaSamples; i++)
                {
                    //  Convert data from the color color buffer 32 bit fp internal format.
                    switch(colorBufferFormat)
                    {
                        case GPU_RGBA8888:
                            currentColor[0] = f32bit(colorBuffer[address + i * 4 + 0]) / 255.0f;
                            currentColor[1] = f32bit(colorBuffer[address + i * 4 + 1]) / 255.0f;
                            currentColor[2] = f32bit(colorBuffer[address + i * 4 + 2]) / 255.0f;
                            break;
                            
                        case GPU_RG16F:
                            currentColor[0] = GPUMath::convertFP16ToFP32(*((u16bit *) &colorBuffer[address + i * 4 + 0]));
                            currentColor[1] = GPUMath::convertFP16ToFP32(*((u16bit *) &colorBuffer[address + i * 4 + 2]));
                            currentColor[2] = 0.0f;
                            break;
                            
                        case GPU_R32F:
                            currentColor[0] = *((f32bit *) &colorBuffer[address + i * 4]);
                            currentColor[1] = 0.0f;
                            currentColor[2] = 0.0f;
                            break;                        
                                    
                        case GPU_RGBA16:
                            currentColor[0] = (*((u16bit *) &colorBuffer[address + i * 8 + 0])) / 65535.0f;
                            currentColor[1] = (*((u16bit *) &colorBuffer[address + i * 8 + 2])) / 65535.0f;
                            currentColor[2] = (*((u16bit *) &colorBuffer[address + i * 8 + 4])) / 65535.0f;
                            break;

                        case GPU_RGBA16F:
                            currentColor[0] = GPUMath::convertFP16ToFP32(*((u16bit *) &colorBuffer[address + i * 8 + 0]));
                            currentColor[1] = GPUMath::convertFP16ToFP32(*((u16bit *) &colorBuffer[address + i * 8 + 2]));
                            currentColor[2] = GPUMath::convertFP16ToFP32(*((u16bit *) &colorBuffer[address + i * 8 + 4]));
                            break;
                    }

                    sampleColors[i][0] = currentColor[0];
                    sampleColors[i][1] = currentColor[1];
                    sampleColors[i][2] = currentColor[2];
                    
                    resolvedColor[0] += LINEAR(currentColor[0]);
                    resolvedColor[1] += LINEAR(currentColor[1]);
                    resolvedColor[2] += LINEAR(currentColor[2]);
                    
                    fullCoverage = fullCoverage && (referenceColor[0] == currentColor[0])
                                                && (referenceColor[1] == currentColor[1])
                                                && (referenceColor[2] == currentColor[2]);
                }
                
                //  Check if there is a single sample for the pixel
                if (fullCoverage)
                {
                    //  Convert from RGBA32F (internal format) to RGBA8 (PPM format)
                    red   = u8bit(GPU_MIN(GPU_MAX(referenceColor[0], 0.0f), 1.0f) * 255.0f);
                    green = u8bit(GPU_MIN(GPU_MAX(referenceColor[1], 0.0f), 1.0f) * 255.0f);
                    blue  = u8bit(GPU_MIN(GPU_MAX(referenceColor[2], 0.0f), 1.0f) * 255.0f);
                }
                else
                {
                    //  Resolve color as the average of all the sample colors.
                    resolvedColor[0] = GAMMA(resolvedColor[0] / f32bit(msaaSamples));
                    resolvedColor[1] = GAMMA(resolvedColor[1] / f32bit(msaaSamples));
                    resolvedColor[2] = GAMMA(resolvedColor[2] / f32bit(msaaSamples));

                    //  Convert from RGBA32F (internal format) to RGBA8 (PPM format)
                    red   = u8bit(GPU_MIN(GPU_MAX(resolvedColor[0], 0.0f), 1.0f) * 255.0f);
                    green = u8bit(GPU_MIN(GPU_MAX(resolvedColor[1], 0.0f), 1.0f) * 255.0f);
                    blue  = u8bit(GPU_MIN(GPU_MAX(resolvedColor[2], 0.0f), 1.0f) * 255.0f);
                }

#ifndef SAVE_AS_PNG
                //  Write pixel color into the output file.
                fputc(char(red)  , fout);
                fputc(char(green), fout);
                fputc(char(blue) , fout);
#else   //  SAVE_AS_PNG
                u32bit yImage = d3d9PixelCoordinates ? y : (vRes - 1) - y;
                data[(yImage * hRes + x) * 4 + 2] = red;
                data[(yImage * hRes + x) * 4 + 1] = green;
                data[(yImage * hRes + x) * 4 + 0] = blue;
                //data[(yImage * hRes + x) * 4 + 3] = alpha;
                data[(yImage * hRes + x) * 4 + 3] = 255;
#endif  //  SAVE_AS_PNG                    
            }                    
        }                
    }
    
#ifndef SAVE_AS_PNG    
    fclose(fout);
#else    
    ImageSaver::getInstance().savePNG(filename, hRes, vRes, data);
#endif    
}

void DAC::writeStencilBuffer()
{
    char filename[128];

#ifdef SAVE_AS_PNG
    static u8bit *data = 0;
    static u32bit dataSize = 0;
    
    //  Check if the buffer is large enough.
    if (dataSize < (hRes * vRes * 4))
    {
        //  Check if the old buffer must be deleted.
        if (data != NULL)
            delete[] data;
            
        //  Set the new buffer size.            
        dataSize = hRes * vRes * 4;
        
        //  Create the new buffer.
        data = new u8bit[dataSize];
    }
#endif

    if (lastRSCommand->getCommand() == RSCOM_DUMP_STENCIL)
    {
        //  Create current frame filename.
        sprintf(filename, "stencil%04d-batch%05d.sim", frameCounter, batchCounter);
    }
    else
    {
        //  Create current frame filename.
        sprintf(filename, "stencil%04d.sim", frameCounter);
    }
    
#ifndef SAVE_AS_PNG

    FILE *fout;

    char filenamePPM[128];

    //  Add extension.
    sprintf(filenamePPM, "%s.ppm", filename);
        
    //  Open/Create the file for the current frame.
    fout = fopen(filenamePPM, "wb");

    //  Check if the file was correctly created.
    GPU_ASSERT(
        if (fout == NULL)
            panic("DAC", "writeStencilBuffer", "Error creating stencil output file.");
    )

    //  Write file header.

    //  Write magic number.
    fprintf(fout, "P6\n");

    //  Write frame size.  */
    fprintf(fout, "%d %d\n", hRes, vRes);

    //  Write color component maximum value.
    fprintf(fout, "255\n");

#endif

    u8bit red = 255;
    u8bit green = 255;
    u8bit blue = 255;

    //  Check if multisampling is enabled.
    if (!multisampling)
    {    
        s32bit top = d3d9PixelCoordinates ? 0 : (vRes -1);
        s32bit bottom = d3d9PixelCoordinates ? (vRes - 1) : 0;
        s32bit nextLine = d3d9PixelCoordinates ? +1 : -1;
        
        //  Do this for the whole picture now.
        for (s32bit y = top; y != (bottom + nextLine); y = y + nextLine)
        {
            for (s32bit x = 0; x < s32bit(hRes); x++)
            {
                //  Compute address of the pixel.
                u32bit address = zstPixelMapper.computeAddress(x, y);
                
                //  Put some color to make small differences more easy to discover.
                red   = zstBuffer[address + 3];
                green = red & 0xF0;
                blue  = (red & 0x0F) << 4;
                
#ifndef SAVE_AS_PNG                
                fputc((char) red, fout);
                fputc((char) green, fout);
                fputc((char) blue, fout);
#else                
                u32bit yImage = d3d9PixelCoordinates ? y : (vRes - 1) - y;
                data[(yImage * hRes + x) * 4 + 2] = red;
                data[(yImage * hRes + x) * 4 + 1] = green;
                data[(yImage * hRes + x) * 4 + 0] = blue;
                //data[(yImage * hRes + x) * 4 + 3] = alpha;
                data[(yImage * hRes + x) * 4 + 3] = 255;
#endif                
            }
        }
    }
    else
    {
    
        panic("DAC", "writeStencilBuffer", "Multisampling not supported.");
        
        QuadFloat sampleColors[MAX_MSAA_SAMPLES];
        QuadFloat resolvedColor;
        QuadFloat referenceColor;
        QuadFloat currentColor;
        
        s32bit top = d3d9PixelCoordinates ? 0 : (vRes - 1);
        s32bit bottom = d3d9PixelCoordinates ? (vRes - 1) : 0;
        
        //  Do this for the whole picture now.
        for (s32bit y = top; y >= bottom; y--)
        {
            for(s32bit x = 0; x < s32bit(hRes); x++)
            {               
                u32bit address = zstPixelMapper.computeAddress(x, y);

                //  Zero resolved color.
                resolvedColor[0] = 0.0f;
                resolvedColor[1] = 0.0f;
                resolvedColor[2] = 0.0f;
                
                //  Convert data from the color color buffer 32 bit fp internal format.
                switch(colorBufferFormat)
                {
                    case GPU_RGBA8888:
                        referenceColor[0] = f32bit(colorBuffer[address + 0]) / 255.0f;
                        referenceColor[1] = f32bit(colorBuffer[address + 1]) / 255.0f;
                        referenceColor[2] = f32bit(colorBuffer[address + 2]) / 255.0f;
                        break;
                
                    case GPU_RG16F:
                        referenceColor[0] = GPUMath::convertFP16ToFP32(*((u16bit *) &colorBuffer[address + 0]));
                        referenceColor[1] = GPUMath::convertFP16ToFP32(*((u16bit *) &colorBuffer[address + 2]));
                        referenceColor[2] = 0.0f;
                        break;
                        
                    case GPU_R32F:
                        referenceColor[0] = *((f32bit *) &colorBuffer[address]);
                        referenceColor[1] = 0.0f;
                        referenceColor[2] = 0.0f;
                        break;                        
                                
                    case GPU_RGBA16:
                        referenceColor[0] = (*((u16bit *) &colorBuffer[address + 0])) / 65535.0f;
                        referenceColor[1] = (*((u16bit *) &colorBuffer[address + 2])) / 65535.0f;
                        referenceColor[2] = (*((u16bit *) &colorBuffer[address + 4])) / 65535.0f;
                        break;

                    case GPU_RGBA16F:
                        referenceColor[0] = GPUMath::convertFP16ToFP32(*((u16bit *) &colorBuffer[address + 0]));
                        referenceColor[1] = GPUMath::convertFP16ToFP32(*((u16bit *) &colorBuffer[address + 2]));
                        referenceColor[2] = GPUMath::convertFP16ToFP32(*((u16bit *) &colorBuffer[address + 4]));
                        break;
                }
                
                bool fullCoverage = true;

                //  Accumulate the color for all the samples in the pixel
                for(u32bit i = 0; i < msaaSamples; i++)
                {
                    //  Convert data from the color color buffer 32 bit fp internal format.
                    switch(colorBufferFormat)
                    {
                        case GPU_RGBA8888:
                            currentColor[0] = f32bit(colorBuffer[address + i * 4 + 0]) / 255.0f;
                            currentColor[1] = f32bit(colorBuffer[address + i * 4 + 1]) / 255.0f;
                            currentColor[2] = f32bit(colorBuffer[address + i * 4 + 2]) / 255.0f;
                            break;
                            
                        case GPU_RG16F:
                            currentColor[0] = GPUMath::convertFP16ToFP32(*((u16bit *) &colorBuffer[address + i * 4 + 0]));
                            currentColor[1] = GPUMath::convertFP16ToFP32(*((u16bit *) &colorBuffer[address + i * 4 + 2]));
                            currentColor[2] = 0.0f;
                            break;
                            
                        case GPU_R32F:
                            currentColor[0] = *((f32bit *) &colorBuffer[address + i * 4]);
                            currentColor[1] = 0.0f;
                            currentColor[2] = 0.0f;
                            break;                        
                                    
                        case GPU_RGBA16:
                            currentColor[0] = (*((u16bit *) &colorBuffer[address + i * 8 + 0])) / 65535.0f;
                            currentColor[1] = (*((u16bit *) &colorBuffer[address + i * 8 + 2])) / 65535.0f;
                            currentColor[2] = (*((u16bit *) &colorBuffer[address + i * 8 + 4])) / 65535.0f;
                            break;

                        case GPU_RGBA16F:
                            currentColor[0] = GPUMath::convertFP16ToFP32(*((u16bit *) &colorBuffer[address + i * 8 + 0]));
                            currentColor[1] = GPUMath::convertFP16ToFP32(*((u16bit *) &colorBuffer[address + i * 8 + 2]));
                            currentColor[2] = GPUMath::convertFP16ToFP32(*((u16bit *) &colorBuffer[address + i * 8 + 4]));
                            break;
                    }

                    sampleColors[i][0] = currentColor[0];
                    sampleColors[i][1] = currentColor[1];
                    sampleColors[i][2] = currentColor[2];
                    
                    resolvedColor[0] += LINEAR(currentColor[0]);
                    resolvedColor[1] += LINEAR(currentColor[1]);
                    resolvedColor[2] += LINEAR(currentColor[2]);
                    
                    fullCoverage = fullCoverage && (referenceColor[0] == currentColor[0])
                                                && (referenceColor[1] == currentColor[1])
                                                && (referenceColor[2] == currentColor[2]);
                }
                
                //  Check if there is a single sample for the pixel
                if (fullCoverage)
                {
                    //  Convert from RGBA32F (internal format) to RGBA8 (PPM format)
                    red   = u8bit(GPU_MIN(GPU_MAX(referenceColor[0], 0.0f), 1.0f) * 255.0f);
                    green = u8bit(GPU_MIN(GPU_MAX(referenceColor[1], 0.0f), 1.0f) * 255.0f);
                    blue  = u8bit(GPU_MIN(GPU_MAX(referenceColor[2], 0.0f), 1.0f) * 255.0f);
                }
                else
                {
                    //  Resolve color as the average of all the sample colors.
                    resolvedColor[0] = GAMMA(resolvedColor[0] / f32bit(msaaSamples));
                    resolvedColor[1] = GAMMA(resolvedColor[1] / f32bit(msaaSamples));
                    resolvedColor[2] = GAMMA(resolvedColor[2] / f32bit(msaaSamples));

                    //  Convert from RGBA32F (internal format) to RGBA8 (PPM format)
                    red   = u8bit(GPU_MIN(GPU_MAX(resolvedColor[0], 0.0f), 1.0f) * 255.0f);
                    green = u8bit(GPU_MIN(GPU_MAX(resolvedColor[1], 0.0f), 1.0f) * 255.0f);
                    blue  = u8bit(GPU_MIN(GPU_MAX(resolvedColor[2], 0.0f), 1.0f) * 255.0f);
                }

#ifndef SAVE_AS_PNG
                //  Write pixel color into the output file.
                fputc(char(red)  , fout);
                fputc(char(green), fout);
                fputc(char(blue) , fout);
#else   //  SAVE_AS_PNG
                u32bit yImage = d3d9PixelCoordinates ? y : (vRes - 1) - y;
                data[(yImage * hRes + x) * 4 + 2] = red;
                data[(yImage * hRes + x) * 4 + 1] = green;
                data[(yImage * hRes + x) * 4 + 0] = blue;
                //data[(yImage * hRes + x) * 4 + 3] = alpha;
                data[(yImage * hRes + x) * 4 + 3] = 255;
#endif  //  SAVE_AS_PNG                    
            }                    
        }                
    }
    
#ifndef SAVE_AS_PNG    
    fclose(fout);
#else    
    ImageSaver::getInstance().savePNG(filename, hRes, vRes, data);
#endif    
}

/*  Translates an address to the start of a block into a block number.  */
u32bit DAC::address2block(u32bit address)
{
    u32bit block;

    /*  Translate start block/line address to a block address.  */
    block = address >> blockShift;

    return block;
}

/*  Calculates the block assigned display tile.  */
u32bit DAC::blockDisplayTile(PixelMapper &pixelMapper, u32bit block)
{
    return pixelMapper.mapToDisplayTile(block << blockShift, GPUPD, numGPUs);
}

/*  Calculates the block assigned stamp unit.  */
u32bit DAC::blockUnit(PixelMapper &pixelMapper, u32bit block)
{
    return pixelMapper.mapToUnit(block << blockShift);
    
/*
    u32bit overTile;
    u32bit overLine;
    u32bit overX;
    u32bit overY;
    u32bit scanTile;
    u32bit scanX;
    u32bit scanY;
    u32bit x;
    u32bit y;

    //  Assignment of blocks to stamp units is done on a scan tile basis.
    //  The block address (linear memory address) is translated into framebuffer
    //  (x, y) coordinates to get the scan tile coordinates for the block.

    //if (multisampling)
    //    block = block / msaaSamples;

    //if (colorBufferFormat == GPU_RGBA16F)
    //    block = block >> 1;
        
    u32bit samples = multisampling ? msaaSamples : 1;
    u32bit colorDWords = (colorBufferFormat == GPU_RGBA16F) ? 2 : 1;
            
    //  Calculate the over tile address inside the framebuffer.
    overTile = block / (overW * scanW * overH * scanH * samples * colorDWords);

    //  Calculate size number of horizontal over tiles.
    overLine = u32bit(ceil(hRes / (f32bit(overW * scanW * genW * STAMP_WIDTH))));

    //  Calculate the block vertical and horizontal over tile coordinates inside the framebuffer.
    overX = GPU_MOD(overTile, overLine);
    overY = overTile / overLine;

    //  Calculate the scan tile address inside the over scan tile.
    scanTile = GPU_MOD(block, overW * scanW * overH * scanH * samples * colorDWords) / (scanW * scanH);

    //  Calculate the block vertical and horizontal scan tile coordinates inside the over tile (per row).
    //scanX = GPU_MOD(scanTile, overW);
    //scanY = scanTile / overW;

    //  Calculate the block vertical and horizontal scan tile coordinates inside the over tile (morton).
    scanX = 0;
    scanY = 0;
    for(u32bit i = 0; i < u32bit(GPU_CEIL2(GPU_LOG2(overW))); i++)
    {
        scanX = scanX | ((scanTile & 0x01) << i);
        scanTile = scanTile >> 1;
        scanY = scanY | ((scanTile & 0x01) << i);
        scanTile = scanTile >> 1;
    }

    //  Calculate the scan tile vertical and horizontal coordinates inside the framebuffer.
    x = scanX + overX * overW;
    y = scanY + overY * overH;

    if (numStampUnits == 1)
        return 0;

    if (numStampUnits == 2)
        return ((x + y) & 0x01);

    if (numStampUnits == 4)
        return  GPU_MOD((x & 0x01) + ((y & 0x01) << 1), numStampUnits);
        
    if ((numStampUnits == 8) || (numStampUnits == 16))
        return  GPU_MOD((x & 0x01) + ((y & 0x01) << 1) + ((x & 0x02) << 1) + ((y & 0x02) << 2), numStampUnits);
    
    //  Remove VS2005 warning.
    return 0;
*/   
}

//  Update memory transmission cycles.
void DAC::updateMemory(u64bit cycle)
{
    //  Check if memory bus is busy.
    if (busCycles > 0)
    {
        //  Update bus use counter.
        busCycles--;

        GPU_DEBUG_BOX(
            printf("DAC %lld => Transmission in progress.  Remaining cycles %d\n",
                cycle, busCycles);
        )

        //  Check end of transmission.
        if (busCycles == 0)
        {
            GPU_DEBUG_BOX(
                printf("DAC => End of memory read.\n");
            )

            //  Update block queue entry received bytes.
            blockQueue[ticket2queue[lastTicket]].received += lastSize;

            //  Add ticket to the free ticket list.
            ticketList.add(lastTicket);
            
            //  Update free memory tickets counter.
            freeTickets++;
        }
    }
}

//  Update buffer block decompressor state.
void DAC::updateDecompressor(u64bit cycle, CompressorEmulator *compressorEmulator, u8bit *dumpBuffer, 
                             u8bit *clearValue, u32bit bytesPerPixel, u32bit baseBufferAddress,
			     PixelMapper &pixelMapper)
{
    u32bit address;
    
    //  Update decompress cycles.
    if (decompressCycles > 0)
    {
        //  Update decompress cycles.
        decompressCycles--;

        GPU_DEBUG_BOX(
            printf("DAC %lld => Decompressing block.  Remaining cycles %d\n",
                cycle, decompressCycles);
        )

        //  Check if end of decompression.
        if (decompressCycles == 0)
        {
            //  Update number of blocks to decompress.
            numToDecompress--;

            //  Update pointer to the next block to decompress.
            nextDecompress = GPU_MOD(nextDecompress + 1, blockQueueSize);

            /*  Update number of free queue entries.  */
            numFree++;
        }
    }

    //  Decompress a block.
    if ((numToDecompress > 0) && (decompressCycles == 0))
    {
        //  Check that the block has been received from memory.
        if (blockQueue[nextDecompress].received == blockQueue[nextDecompress].size)
        {
            GPU_DEBUG_BOX(
                printf("DAC %lld => Decompressing block %d at address %x.\n",
                    cycle, blockQueue[nextDecompress].block, blockQueue[nextDecompress].address);
            )

            //  Update decompress cycles.
            decompressCycles = decompressLatency;

            //  Update statistic.
            stateBlocks++;
            globalStateBlocks++;
            
            const ROPBlockState& block = blockQueue[nextDecompress].state;
            
            //printf("Compressed data (%d bytes) : \n    ", blockQueue[nextDecompress].size);
            //for(u32bit d = 0; d < blockQueue[nextDecompress].size; d++)
            //printf("%02x ", blockBuffer[nextDecompress][d]);
            //printf("\n");

            //  Select compression method.
            switch (block.state)
            {
                case ROPBlockState::CLEAR:

                    GPU_DEBUG_BOX(
                        printf("DAC => CLEAR block.\n");
                    )

                    //  Compute address of the block inside the dump buffer.
                    address = blockQueue[nextDecompress].address - baseBufferAddress;
                    
                    //  Fill the block with the clear value.
		    GPU_ASSERT(
	                if (GPU_MOD(blockDisplayTile(pixelMapper, address2block(address)), numGPUs) != gpuId)
			    panic("DAC", "updateDecompressor", "block of other GPUs");
				    
		    )

                    for(u32bit i = 0; i < blockSize; i += bytesPerPixel)
                    {
                        for(u32bit j = 0; j < (bytesPerPixel >> 2); j++) {
                            *((u32bit *) &dumpBuffer[(address + i) + j * 4]) = ((u32bit *) clearValue)[j];
		        }
                    }
                    
                    //  Update statistics.
                    stateBlocksClear++;
                    globalStateBlocksClear++;
            
                    break;

                case ROPBlockState::UNCOMPRESSED:

                    GPU_DEBUG_BOX(
                        printf("DAC => UNCOMPRESSED block.\n");
                    )

                    //  Compute address of the block inside the dump buffer.
                    address = blockQueue[nextDecompress].address - baseBufferAddress;
                    
                    //  Fill the block with the read data.
		    GPU_ASSERT(
	                if (GPU_MOD(blockDisplayTile(pixelMapper, address2block(address)), numGPUs) != gpuId)
			    panic("DAC", "updateDecompressor", "block of other GPUs");
				    
		    )

                    for (u32bit i = 0; i < blockSize; i += 4) {
                        *((u32bit *) &dumpBuffer[address + i]) = *((u32bit *) &blockBuffer[nextDecompress][i]);
		    }

                    //for(u32bit i = 0, address = blockQueue[nextDecompress].address - frontBuffer;
                    //    i < blockSize; i += 4)
                    //    *((u32bit *) &colorBuffer[address + i]) = 0x000000ff;

                    //  Update statistics.
                    stateBlocksUncompressed++;
                    globalStateBlocksUncompressed++;
                    
                    break;

                case ROPBlockState::COMPRESSED:

                    GPU_DEBUG_BOX(
                        printf("DAC => COMPRESSED block with level %i.\n", block.comprLevel);
                    )

                    //  Compute address of the block inside the dump buffer.
                    address = blockQueue[nextDecompress].address - baseBufferAddress;

                    /*  Uncompress the block.  */
		    GPU_ASSERT(
	                if (GPU_MOD(blockDisplayTile(pixelMapper, address2block(address)), numGPUs) != gpuId)
			    panic("DAC", "updateDecompressor", "block of other GPUs");
				    
		    )

                    compressorEmulator->uncompress(blockBuffer[nextDecompress],  (u32bit *) &dumpBuffer[address], 
                                                   blockSize >> 2, block.getComprLevel());

                    //for(u32bit i = 0, address = blockQueue[nextDecompress].address - frontBuffer;
                    //    i < blockSize; i += 4)
                    //    *((u32bit *) &colorBuffer[address + i]) = 0x00ff00ff;
                                            
                    //  Update stat.
                    switch (block.comprLevel)
                    {
                        case 0: stateBlocksCompressedBest++;   globalStateBlocksCompressedBest++;   break;
                        case 1: stateBlocksCompressedNormal++; globalStateBlocksCompressedNormal++; break;
                        case 2: stateBlocksCompressedWorst++;  globalStateBlocksCompressedWorst++;  break;
                        default:
                            GPU_DEBUG_BOX(
                                printf("DAC => Warning: stattistics for compressor level %i not supported.\n", block.comprLevel);
                            )
                            break;                            
                    }
                    
                    break;

                default:
                    panic("DAC", "clock", "Undefined compression method.");
                    break;
            }
            //printf("DAC => Decompressed block %x state %d at address %08x\n",
            //blockQueue[nextDecompress].block, blockQueue[nextDecompress].state, blockQueue[nextDecompress].address);
            
            //printf("Uncompressed data (%d bytes) : \n    ", blockSize);
            //for(u32bit b = 0; b < blockSize; b++)
            //printf("%02x ", colorBuffer[address + b]);
            //printf("\n");
        }
    }
}

//  Update the block request stage.
void DAC::updateBlockRequest(u64bit cycle)
{
    //  Check if memory controller and the bus are ready, there are free memory tickets and there is a block to request.
    if ((numToRequest > 0) && ((memState & MS_READ_ACCEPT) != 0) && (freeTickets > 0))
    {
        //  Check there are enough memory tickets.
        //GPU_ASSERT(
        //    if (freeTickets == 0)
        //        panic("DAC", "clock", "No free memory tickets.");
        //)

        //  Determine if the block has been fully requested (check for clear blocks!!).
        if (blockQueue[nextRequest].size == blockQueue[nextRequest].requested)
        {
            GPU_DEBUG_BOX(
                printf("DAC %lld => Block %d fully requested to memory.\n",
                    cycle, blockQueue[nextRequest].block);
            )

            //  Update number of blocks to request.
            numToRequest--;

            //  Update number of blocks to decompress.
            numToDecompress++;

            //  Update pointer to the next block to request.
            nextRequest = GPU_MOD(nextRequest + 1, blockQueueSize);
        }
        else
        {
            //  Request the block to memory.

            //  Calculate transaction size.
            u32bit size = GPU_MIN(MAX_TRANSACTION_SIZE, blockQueue[nextRequest].size);

            GPU_DEBUG_BOX(
                printf("DAC %lld => Requesting memory at %x %d bytes for block %d.\n",
                    cycle, blockQueue[nextRequest].address + blockQueue[nextRequest].requested,
                    size, blockQueue[nextRequest].block);
            )

            //  Get the next free ticket.
            u32bit nextFreeTicket = ticketList.pop();
            
            //  Add queue entry to the translation table.
            ticket2queue[nextFreeTicket] = nextRequest;

            //  Create write transaction.
            MemoryTransaction *memTrans = new MemoryTransaction(
                MT_READ_REQ,
                blockQueue[nextRequest].address + blockQueue[nextRequest].requested,
                size,
                &blockBuffer[nextRequest][blockQueue[nextRequest].requested],
                DACB,
                nextFreeTicket
            );

            //  Copy cookies from the last command from the Command Processor.
            memTrans->copyParentCookies(*lastRSCommand);

            //  Add a cookie level.
            memTrans->addCookie();

            //  Send transaction to memory controller.
            memoryRequest->write(cycle, memTrans);

            //  Update requested bytes.
            blockQueue[nextRequest].requested += size;

            //  Update free ticket counter.
            freeTickets--;

            //  Determine if the block has been fully requested.
            if (blockQueue[nextRequest].size == blockQueue[nextRequest].requested)
            {
                GPU_DEBUG_BOX(
                    printf("DAC %lld => Block %d fully requested to memory.\n",
                        cycle, blockQueue[nextRequest].block);
                )

                //  Update number of blocks to request.
                numToRequest--;

                //  Update number of blocks to decompress.
                numToDecompress++;

                //  Update pointer to the next block to request.
                nextRequest = GPU_MOD(nextRequest + 1, blockQueueSize);
            }
        }
    }
}

//  Update request queue stage.
void DAC::updateRequestQueue(u64bit cycle, CompressorEmulator *compressorEmulator, u32bit baseBufferAddress, u32bit dumpBufferSize,
		             ROPBlockState *bufferBlockState, u32bit bufferBlockSize, PixelMapper &pixelMapper)
{ 
    //  Add a block to the request queue.
    if ((stateUpdateCycles == 0) && (numFree > 0) && (requested < dumpBufferSize))
    {   
        // I guess this is the easiest timing hack	
	bool skip = GPU_MOD(blockDisplayTile(pixelMapper, address2block(requested)), numGPUs) != gpuId;
	while (skip && requested < dumpBufferSize) {
            //  Update requested bytes (blocks) counter.
            requested += bufferBlockSize;
	    skip = GPU_MOD(blockDisplayTile(pixelMapper, address2block(requested)), numGPUs) != gpuId;
	}
	if (requested >= dumpBufferSize) return;

        //  Add next block to the request queue.
        blockQueue[nextFree].address = baseBufferAddress + requested;
        blockQueue[nextFree].block = address2block(requested);
        blockQueue[nextFree].state = bufferBlockState[address2block(requested)];
        blockQueue[nextFree].requested = 0;
        blockQueue[nextFree].received = 0;

        const ROPBlockState& block = blockQueue[nextFree].state;
        
        //  Set block size.
        switch(block.state)
        {
            case ROPBlockState::CLEAR:

                GPU_DEBUG_BOX(
                    printf("DAC => Adding request for CLEAR block %d\n",
                        blockQueue[nextFree].block);
                )

                blockQueue[nextFree].size = 0;

                break;

            case ROPBlockState::UNCOMPRESSED:

                GPU_DEBUG_BOX(
                    printf("DAC => Adding request for UNCOMPRESSED block %d\n",
                        blockQueue[nextFree].block);
                )

                blockQueue[nextFree].size = bufferBlockSize;

                break;

            case ROPBlockState::COMPRESSED:

                GPU_DEBUG_BOX(
                    printf("DAC => Adding request for COMPRESSED block %d with level %d\n",
                        blockQueue[nextFree].block, block.comprLevel);
                )

                blockQueue[nextFree].size = compressorEmulator->getLevelBlockSize(block.comprLevel); 

                break;

            default:
                panic("DAC", "updateRequestQueue", "Undefined block state mode.");
                break;
        }

        //  Update requested bytes (blocks) counter.
        requested += bufferBlockSize;

        //  Update number free entries.
        numFree--;

        //  Update pointer to next free entry.
        nextFree = GPU_MOD(nextFree + 1, blockQueueSize);

        //  Update number of blocks to request.
        numToRequest++;
    }
}

void DAC::processSyncBackPressure(u64bit cycle, Signal** syncBackPressureSignal)
{
    RasterizerSyncCommand* rastSyncComm;
    u32bit gpuIndex;
    u32bit unitIndex;
    u32bit i;
    bool gpuSynced;

    for (gpuIndex = 0; gpuIndex < numGPUs; gpuIndex++) {
        if (gpuIndex != gpuId) {
            for (unitIndex = 0; unitIndex < numStampUnits; unitIndex++) {
    	        if (syncBackPressureSignal[gpuIndex * numStampUnits + unitIndex]->read(cycle, (DynamicObject*&)rastSyncComm)) {
    		    numSyncCommQueueFreeEntries[gpuIndex][unitIndex]++;
		    delete rastSyncComm;

		    gpuSynced = true;
		    for (i = 0; i < numStampUnits; i++)
			gpuSynced = gpuSynced && lastSyncCommSent[gpuIndex][i] &&
				    (numSyncCommQueueFreeEntries[gpuIndex][i] == syncCommQueueSize);

		    if (gpuSynced) {
			numSyncedGPUs++;
		    }
    	        }
	    }
        }
    }
}

void DAC::updateSync(u64bit cycle, CompressorEmulator *compressorEmulator, u8bit* syncDataBuffer, u32bit baseBufferAddress,
		     ROPBlockState* syncBlockState, u32bit bufferBlockSize, PixelMapper &pixelMapper, Signal** syncSignal)
{
    bool skip;
    u32bit block;
    u32bit address;
    u32bit size;
    u32bit gpuIndex;
    u32bit unit;
    u32bit newlyConsumedbw;
    
    if (numToDecompress > 0) {
        //  Check that the block has been received from memory.
        if (blockQueue[nextDecompress].received == blockQueue[nextDecompress].size) {
            GPU_DEBUG_BOX(
                printf("DAC %lld => Syncing block %d at address %x.\n",
                    cycle, blockQueue[nextDecompress].block, blockQueue[nextDecompress].address);
            )
                
            address = blockQueue[nextDecompress].address - baseBufferAddress;

	    GPU_ASSERT(
	        if (GPU_MOD(blockDisplayTile(pixelMapper, address2block(address)), numGPUs) != gpuId)
	            panic("DAC", "updateSync", "block of other GPUs");
	    )
               
	    block = blockQueue[nextDecompress].block;
	    unit = blockUnit(pixelMapper, block);
	    size = blockQueue[nextDecompress].size;

            for (u32bit gpuIndex = 0; gpuIndex < numGPUs; gpuIndex++) {
	        if (gpuIndex != gpuId) {
                    if (numBufferedSyncData[gpuIndex] == 0 && numSyncCommQueueFreeEntries[gpuIndex][unit] > 0 && interGPUSyncTransCycles == 0) {

	                ROPBlockState* blockState = &syncBlockState[block];

	                RasterizerSyncCommand* rastSyncComm = new RasterizerSyncCommand(
	                    block, baseBufferAddress + address, size, blockBuffer[nextDecompress], new ROPBlockState(blockState), false);

	        	if (lastRSCommand->getBlit()) rastSyncComm->setBlit(true);

	                syncSignal[gpuIndex * numStampUnits + unit]->write(cycle, rastSyncComm);

	    	        // message size = data size + state size + metadata (assume meta data is 8 byte)
	    	        consumedInterGPUbw += (size + sizeof(ROPBlockState) + 8);
			
			interGPUSyncTrafficLoad.inc(size + sizeof(ROPBlockState) + 8);
			globalInterGPUSyncTrafficLoad.inc(size + sizeof(ROPBlockState) + 8);
	    		    
	        	numSyncCommQueueFreeEntries[gpuIndex][unit]--;
	        	numSent[gpuIndex][unit]++;

	                // update the pointer of the next buffered sync data	
	                nextBufferedSyncData[gpuIndex] = address2block(address) + 1;
                    } else {
                        // buffer the sync data
                        memcpy(syncDataBuffer + address, blockBuffer[nextDecompress], size);

                        // update number of buffered sync data
                        numBufferedSyncData[gpuIndex]++;
	            }
	        }
	    }

            //  Update number of blocks to sync
            numToDecompress--;

            //  Update pointer to the next block to sync
            nextDecompress = GPU_MOD(nextDecompress + 1, blockQueueSize);

            //  Update number of free entries
            numFree++;
        } 
    }

    if (interGPUSyncTransCycles > 0) return;

    do {
	newlyConsumedbw = 0;
        for (u32bit gpuIndex = 0; gpuIndex < numGPUs; gpuIndex++) {
            while (gpuIndex != gpuId && numBufferedSyncData[gpuIndex] > 0) {
                skip = GPU_MOD(blockDisplayTile(pixelMapper, nextBufferedSyncData[gpuIndex]), numGPUs) != gpuId;
                if (!skip) {
                    address = bufferBlockSize * nextBufferedSyncData[gpuIndex];
                    
                    block = address2block(address);
                    ROPBlockState* blockState = &syncBlockState[block];

                    unit = blockUnit(pixelMapper, nextBufferedSyncData[gpuIndex]);

                    if (numSyncCommQueueFreeEntries[gpuIndex][unit] == 0) break;

                    //  Set size.
                    switch(blockState->state)
                    {
                        case ROPBlockState::CLEAR:
                            size = 0;
                            break;

                        case ROPBlockState::UNCOMPRESSED:
                            size = bufferBlockSize;
                            break;

                        case ROPBlockState::COMPRESSED:
                            size = compressorEmulator->getLevelBlockSize(blockState->comprLevel); 
                            break;

                        default:
                            panic("DAC", "updateSync", "Undefined block state mode.");
                            break;
                    }

                    RasterizerSyncCommand* rastSyncComm = new RasterizerSyncCommand(
                	block, baseBufferAddress + address, size, syncDataBuffer + address, new ROPBlockState(blockState), false);

            	    if (lastRSCommand->getBlit()) rastSyncComm->setBlit(true);

                    syncSignal[gpuIndex * numStampUnits + unit]->write(cycle, rastSyncComm);

		    // message size = data size + state size + metadata (assume meta data is 8 byte)
                    consumedInterGPUbw += (size + sizeof(ROPBlockState) + 8);
		    newlyConsumedbw += (size + sizeof(ROPBlockState) + 8);
		    
		    interGPUSyncTrafficLoad.inc(size + sizeof(ROPBlockState) + 8);
		    globalInterGPUSyncTrafficLoad.inc(size + sizeof(ROPBlockState) + 8);

            	    numSyncCommQueueFreeEntries[gpuIndex][unit]--;
            	    numSent[gpuIndex][unit]++;

                    // update the number of buffered sync data	    
                    numBufferedSyncData[gpuIndex]--;

                    // update the pointer of next buffered sync data
                    nextBufferedSyncData[gpuIndex]++;

                    break;
                } else {
                    // update the pointer of next buffered sync data
                    nextBufferedSyncData[gpuIndex]++;
                }
            }
        }
    } while (newlyConsumedbw > 0 && consumedInterGPUbw < interGPUBusWidth);
}

void DAC::sendLastSyncCommand(u64bit cycle, Signal** syncSignal)
{
    RasterizerSyncCommand* rastSyncComm;
    u32bit gpuIndex;
    u32bit unitIndex;
    bool allGPUSyncDataSent;

    allGPUSyncDataSent = true;
    for (gpuIndex = 0; gpuIndex < numGPUs; gpuIndex++) {
        if (gpuIndex != gpuId && allSyncDataSent[gpuIndex]) {
            for (unitIndex = 0; unitIndex < numStampUnits; unitIndex++) {
    	        if (!lastSyncCommSent[gpuIndex][unitIndex] && numSyncCommQueueFreeEntries[gpuIndex][unitIndex] > 0)
		{
                    rastSyncComm = new RasterizerSyncCommand(true);
                    syncSignal[gpuIndex * numStampUnits + unitIndex]->write(cycle, rastSyncComm);
		    // no data and state, only meta information
		    consumedInterGPUbw += 8;
		    
		    interGPUSyncTrafficLoad.inc(8);
		    globalInterGPUSyncTrafficLoad.inc(8);
		    
		    numSent[gpuIndex][unitIndex]++;
    		    lastSyncCommSent[gpuIndex][unitIndex] = true;
    		    numSyncCommQueueFreeEntries[gpuIndex][unitIndex]--;
		    break;
    	        }
            }
	}
            
        if ((busCycles == 0) && (numFree == blockQueueSize) &&
    	    (stateUpdateCycles == 0) && (numBufferedSyncData[gpuIndex] == 0) &&
	    (allSyncDataSent[gpuIndex] == false)) {
            allGPUSyncDataSent = allGPUSyncDataSent && true;
	} else {
            allGPUSyncDataSent = allGPUSyncDataSent && false;
	}
    }

    if (allGPUSyncDataSent) {
        if (lastRSCommand->getCommand() == RSCOM_SYNC_COLOR)
	    rtSynced[nextRt] = true;

	while ((nextRt < MAX_RENDER_TARGETS - 1) && (lastRSCommand->getCommand() == RSCOM_SYNC_COLOR)) {
	    nextRt++;
	    
	    if (rtEnable[nextRt] || (!rtSynced[nextRt])) {
	        requested = 0;
		delete[] syncBuffer;
                colorBufferSize = colorPixelMapper[nextRt].computeFrameBufferSize();
	    
		//FILE *debugfile = fopen("debugDACSync.txt", "a+");
	        //fprintf(debugfile, "GPU[%d] cycle %lld batch %d will sync color rtAddr[%d] = 0x%x colorBufferSize %d 0x%x rtEnable %s rtSynced %s\n",
	        //        gpuId, cycle, batchCounter, nextRt, rtAddress[nextRt], colorBufferSize, colorBufferSize,
		//	rtEnable[nextRt] ? "T" : "F", rtSynced[nextRt] ? "T" : "F");
	        //fflush(debugfile);
	        //fclose(debugfile);
	    
		syncBuffer = new u8bit[colorBufferSize];
		for (gpuIndex = 0; gpuIndex < numGPUs; gpuIndex++) {
		    nextBufferedSyncData[gpuIndex] = 0;
		    for (unitIndex = 0; unitIndex < numStampUnits; unitIndex++) {
		        numSent[gpuIndex][unitIndex] = 0;
		    }
		}
		return;
	    }
	}

	for (gpuIndex = 0; gpuIndex < numGPUs; gpuIndex++) {
	    allSyncDataSent[gpuIndex] = true;
        }
    }
}

//  Reset the state of the DAC unit.
void DAC::reset()
{
    //  Reset DAC state and registers.
    colorBufferFormat = GPU_RGBA8888;
    for (u32bit rt = 0; rt < MAX_RENDER_TARGETS; rt++)
        bytesPixel[rt] = 4;
    hRes = 400;
    vRes = 400;
    d3d9PixelCoordinates = false;
    startX = 0;
    startY = 0;
    width = 400;
    height = 400;
    multisampling = false;
    msaaSamples = 2;
    zStencilCompression = true;
    colorCompression = true;
    
    blt->setMultisampling(multisampling);
    blt->setMSAASamples(msaaSamples);
    
    //  By default set front buffer at 1 MB
    //                 back buffer at 2 MB
    //                 z stencil buffer at 3 MBs
    frontBuffer    = 0x200000;
    backBuffer     = 0x400000;
    zStencilBuffer = 0x600000;
    
    blt->setBackBufferAddress(backBuffer);

    //  Reset clear color value.
    clearColor[0] = 0.0f;
    clearColor[1] = 0.0f;
    clearColor[2] = 0.0f;
    clearColor[3] = 1.0f;
    for(u32bit i = 0; i < MAX_BYTES_PER_COLOR; i++)
        clearColorData[0] = 0x00;
    clearColorData[3] = 0xff;
    
    //  Reset depth and stencil clear values.
    clearDepth = 0x00ffffff;
    clearStencil = 0x00;
  
    //  Set to null the current color buffer state memory.
    colorBufferState = NULL;
    
    //  Set to null the current z stencil buffer state memory.
    zStencilBufferState = NULL;

    //  Reset color buffer state memory update cycles.
    stateUpdateCycles = 0;

    //  Fill the ticket list.
    ticketList.clear();
    for(u32bit i = 0; i < MAX_MEMORY_TICKETS; i++)
        ticketList.add(i);
    
    //  Reset blitter unit.
    blt->reset();

    //  Reset blit operation counter.
    blitCounter = 0;
}


/*******************************************************************************
 *                      BLITTER TRANSACTION INTERFACE IMPLEMENTATION           *
 *******************************************************************************/

DAC::BlitterTransactionInterfaceImpl::BlitterTransactionInterfaceImpl(DAC& dac) :
    dac(dac)
{
} 

bool DAC::BlitterTransactionInterfaceImpl::sendWriteTransaction(u64bit cycle, u32bit size, u32bit address, u8bit* data, u32bit id)
{
    /*  Check if the memory controller accepts write requests.  */
    if ((dac.memState & MS_WRITE_ACCEPT) != 0)
    {
        /*  Create the new memory transaction.  */
        MemoryTransaction* memTrans = new MemoryTransaction(
            MT_WRITE_DATA,
            address,
            size,
            data,
            DACB,
            id);
            
        /*  Send memory transaction to the Memory Controller.  */
        dac.memoryRequest->write(cycle, memTrans);

        /*
        //  If there is a Dynamic Object as request source copy its cookies.
        if (writeReq.request->source != NULL)
        {
            memTrans->copyParentCookies(*writeQueue[writeReq].request->source);
            memTrans->addCookie();
        }
        */
                    
        return true;
    }
    else
    {
        /*  No memory transaction generated.  */
        return false;
    }
}

bool DAC::BlitterTransactionInterfaceImpl::sendMaskedWriteTransaction(u64bit cycle, u32bit size, u32bit address, u8bit* data, u32bit* mask, u32bit id)
{
    /*  Check if the memory controller accepts write requests.  */
    if ((dac.memState & MS_WRITE_ACCEPT) != 0)
    {
        /*  Create the new memory transaction.  */
        MemoryTransaction* memTrans = new MemoryTransaction(
            address,
            size,
            data,
            mask,
            DACB,
            id);
            
        /*  Send memory transaction to the Memory Controller.  */
        dac.memoryRequest->write(cycle, memTrans);

        /*
        //  If there is a Dynamic Object as request source copy its cookies.
        if (writeReq.request->source != NULL)
        {
            memTrans->copyParentCookies(*writeQueue[writeReq].request->source);
            memTrans->addCookie();
        }
        */
                    
        return true;
    }
    else
    {
        /*  No memory transaction generated.  */
        return false;
    }
}

bool DAC::BlitterTransactionInterfaceImpl::sendReadTransaction(u64bit cycle, u32bit size, u32bit address,
		                                               u8bit* data, u32bit ticket, u32bit requestGPUId)
{
    /*  Check if the memory controller accepts write requests.  */
    if ((dac.memState & MS_READ_ACCEPT) != 0)
    {
        /*  Create the new memory transaction.  */
        MemoryTransaction* memTrans = new MemoryTransaction(
            MT_READ_REQ,
            address,
            size,
            data,
            DACB,
            ticket);

        /*  Send memory transaction to the Memory Controller.  */
        dac.memoryRequest->write(cycle, memTrans);

        /*
        //  If there is a Dynamic Object as request source copy its cookies.
        if (writeReq.request->source != NULL)
        {
            memTrans->copyParentCookies(*writeQueue[writeReq].request->source);
            memTrans->addCookie();
        }
        */
                    
        return true;
    }
    else
    {
        /*  No memory transaction generated.  */
        return false;
    }
}

GPUStatistics::StatisticsManager& DAC::BlitterTransactionInterfaceImpl::getSM()
{
    return dac.getSM();
}

GPUStatistics::StatisticsManager& DAC::BlitterTransactionInterfaceImpl::getSM(u32bit gpuId)
{
    return dac.getSM(gpuId);
}

string DAC::BlitterTransactionInterfaceImpl::getBoxName()
{
    return string("DAC");
}
