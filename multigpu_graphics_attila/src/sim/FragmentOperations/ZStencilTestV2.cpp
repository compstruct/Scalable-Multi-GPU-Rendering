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
 * $RCSfile: ZStencilTestV2.cpp,v $
 * $Revision: 1.8 $
 * $Author: vmoya $
 * $Date: 2007-12-17 19:54:58 $
 *
 * Z Stencil Test box implementation file.
 *
 */

/**
 *
 *  @file ZStencilTestV2.cpp
 *
 *  This file implements the Z Stencil Test box.
 *
 *  This class implements the Z and Stencil test stages of the GPU pipeline.
 *
 */

#include "ZStencilTestV2.h"
#include "MemoryTransaction.h"
#include "RasterizerStateInfo.h"
#include "ROPStatusInfo.h"
#include "HZUpdate.h"
#include "ColorBlockStateInfo.h"
#include "GPUMath.h"
#include "GPU.h" // Access to STAMP_FRAGMENTS
#include <sstream>

using namespace gpu3d;

std::map<u32bit, std::set<u32bit> > ZStencilTestV2::zFightedDraws = std::map<u32bit, std::set<u32bit> >();

/*  Z Stencil Test box constructor.  */
ZStencilTestV2::ZStencilTestV2(u32bit gpuId, u32bit numGPUs, u32bit multiGPUExecMode, u32bit stampId, u32bit numStamps,
    u32bit displayWidth, u32bit displayHeight, u32bit overWidth, u32bit overHeight,
    u32bit scanWidth, u32bit scanHeight, u32bit genWidth, u32bit genHeight,
    bool zComprDisabled, u32bit cacheWays, u32bit cacheLines, u32bit stampsPerLine,
    u32bit portWidth, bool extraReadP, bool extraWriteP, u32bit cacheReqQSz, u32bit inputReqQSz, u32bit outputReqQSz,
    u32bit numStampUnits, u32bit zBlocks, u32bit blocksPerCycle, u32bit comprCycles, u32bit decomprCycles,
    u32bit zInQSize, u32bit zFetchQSize, u32bit zReadQSize, u32bit zOpQSize, u32bit zWriteQSize,
    u32bit zTestRate, u32bit testLat, bool hzUpdDisabled, u32bit updateLatency,  u32bit blockLatency,
    FragmentOpEmulator &fragEmu, RasterizerEmulator &rastEmul, u32bit syncCommQueueSize,
    u32bit zSyncInQSize, u32bit zSyncFetchQSize, u32bit zSyncReadQSize,
    u32bit interGPUBusWidth_, u32bit interGPUBusLat_, bool profileForSortLast_, bool compSchedEnabled_,
    char *name, char *prefix, Box *parent) :

    disableZCompression(zComprDisabled), zCacheWays(cacheWays), zCacheLines(cacheLines),
    stampsLine(stampsPerLine), cachePortWidth(portWidth), extraReadPort(extraReadP), extraWritePort(extraWriteP),
    disableHZUpdate(hzUpdDisabled), hzUpdateLatency(updateLatency),  blockStateLatency(blockLatency), rastEmu(rastEmul),
    blocksCycle(blocksPerCycle), zStencilBufferDefined(true),
    //firstStencilDump(true),
    GenericROP(gpuId, numGPUs, multiGPUExecMode, stampId, numStamps, zTestRate, testLat,
        displayWidth, displayHeight, overWidth, overHeight, scanWidth, scanHeight, genWidth, genHeight,
        numStampUnits, zInQSize, zFetchQSize, zReadQSize, zOpQSize, zWriteQSize,
        fragEmu, syncCommQueueSize, zSyncInQSize, zSyncFetchQSize, zSyncReadQSize,
	interGPUBusWidth_, interGPUBusLat_, profileForSortLast_, compSchedEnabled_,
        strdup(std::string("ZStencilTest").c_str()),
	strdup(std::string("ZST").c_str()),
	name, prefix, parent)

{
    DynamicObject *defaultState[1];
    u32bit freeQueueSize;
    char fullName[64];
    char postfix[32];

    //  Check parameters.
    GPU_ASSERT(
        if (zCacheWays < 1)
            panic("ZStencilTest", "ZStencilTest", "Z Cache requires at least 1 way.");
        if (zCacheLines < 1)
            panic("ZStencilTest", "ZStencilTest", "Z Cache requires at least 1 line.");
        if (stampsLine < 1)
            panic("ZStencilTest", "ZStencilTest", "Z Cache requires at least one stamp per line.");
        if (cachePortWidth == 0)
            panic("ZStencilTest", "ZStencilTest", "Z Cache ports must be at least 1 byte wide.");
        if ((!disableZCompression) && (stampsLine < 16))
            panic("ZStencilTest", "ZStencilTest", "Z Compression only supported for 8x8 fragment tiles and 256 byte cache lines.");
        if (disableZCompression && !disableHZUpdate)
            panic("ZStencilTest", "ZStencilTest", "HZ update requires Z compression.");
        if (hzUpdateLatency < 1)
            panic("ZStencilTest", "ZStencilTest", "HZ update signal latency must be 1 or greater.");
    )

    //  Create the full name and postfix for the statistics.
    sprintf(fullName, "%s::%s", prefix, name);
    sprintf(postfix, "ZST-%s", prefix);

    //  Create statistics.
    outputs = &getSM(gpuId).getNumericStatistic("OutputFragments", u32bit(0), fullName, postfix);
    tested = &getSM(gpuId).getNumericStatistic("TestedFragments", u32bit(0), fullName, postfix);
    passed = &getSM(gpuId).getNumericStatistic("PassedFragments", u32bit(0), fullName, postfix);
    failed = &getSM(gpuId).getNumericStatistic("FailedFragments", u32bit(0), fullName, postfix);
    updatesHZ = &getSM(gpuId).getNumericStatistic("UpdatesHZ", u32bit(0), fullName, postfix);
    totFrags = &getSM(gpuId).getNumericStatistic("TotalReceivedFragments", u32bit(0), fullName, postfix);

    globalOutputs = &getSM().getNumericStatistic("OutputFragments", u32bit(0), fullName, postfix);
    globalTested = &getSM().getNumericStatistic("TestedFragments", u32bit(0), fullName, postfix);
    globalPassed = &getSM().getNumericStatistic("PassedFragments", u32bit(0), fullName, postfix);
    globalFailed = &getSM().getNumericStatistic("FailedFragments", u32bit(0), fullName, postfix);
    globalUpdatesHZ = &getSM().getNumericStatistic("UpdatesHZ", u32bit(0), fullName, postfix);
    globalTotFrags = &getSM().getNumericStatistic("TotalReceivedFragments", u32bit(0), fullName, postfix);

    //  Create signals.


    //  Create signals with the main Rasterizer box.

    //  Create command signal from the main Rasterizer box.
    rastCommand = newInputSignal("ZStencilTestCommand", 1, 1, prefix);

    //  Create state signal to the main Rasterizer box.
    rastState = newOutputSignal("ZStencilTestRasterizerState", 1, 1, prefix);

    //  Create default signal value.
    defaultState[0] = new RasterizerStateInfo(RAST_RESET);

    //  Set default signal value.
    rastState->setData(defaultState);
    
    //  Create fragment and state signals with consumer stage (Fragment FIFO box).

    //  Create output fragments signal to FragmentFIFO box.
    outFragmentSignal = newOutputSignal("ZStencilOutput", numStamps * STAMP_FRAGMENTS, 1, prefix);
    
    syncOutFragmentSignal = newOutputSignal("ZStencilSyncOutput", numStamps * STAMP_FRAGMENTS, 1, prefix);

    //  Create state signal from Fragment FIFO Boxt.  */
    consumerStateSignal = newInputSignal("FFIFOZStencilState", 1, 1, prefix);
    
    consumerSyncStateSignal = newInputSignal("FFIFOZStencilSyncState", 1, 1, prefix);

    // Create fragment and state signals with producer stage (Fragment FIFO bos).

    //  Create input fragment signal from Fragment FIFO.
    inFragmentSignal = newInputSignal("ZStencilInput", numStamps * STAMP_FRAGMENTS, 1, prefix);
    
    syncInFragmentSignal = NULL;

    //  Create state signal to Fragment FIFO.
    ropStateSignal = newOutputSignal("ZStencilState", 1, 1, prefix);

    //  Create default signal value.
    defaultState[0] = new ROPStatusInfo(ROP_READY);

    //  Set default signal value.
    ropStateSignal->setData(defaultState);

    //  Create state signal to Fragment FIFO.
    ropSyncStateSignal = NULL;

    //  Create signals with Memory Controller box.

    /*  Create request signal to the Memory Controller.  */
    memRequest = newOutputSignal("ZStencilTestMemoryRequest", 1, 1, prefix);

    //  Create data signal from the Memory Controller.
    memData = newInputSignal("ZStencilTestMemoryData", 2, 1, prefix);


    //  Create signals that simulate the blend latency.

    //  Create start signal for test operation.
    operationStart = newOutputSignal("ZStencilTest", 1, testLat, prefix);

    //  Create end signal for test operation.
    operationEnd = newInputSignal("ZStencilTest", 1, testLat, prefix);


    //  Create signal with Hierarchical Z.

    //  Create update signal to the Hierarchical Z box.
    hzUpdate = newOutputSignal("HZUpdate", 1, hzUpdateLatency, prefix);

    //  Create signal with the DAC.

    //  Create block state info signal to the DAC.
    blockStateDAC = newOutputSignal("ZStencilBlockState", 1, blockStateLatency, prefix);

    interGPUSync = new Signal*[numGPUs];
    interGPUSyncBackPressure = new Signal*[numGPUs];

    char signalPrefix[16];
    for (u32bit gpuIndex = 0; gpuIndex < numGPUs; gpuIndex++) {
	if (gpuIndex == gpuId) {
	    interGPUSync[gpuIndex] = NULL;
	    interGPUSyncBackPressure[gpuIndex] = NULL;
	} else {
            sprintf(signalPrefix, "GPU%dTo%dZST%d", gpuIndex, gpuId, stampId);
            interGPUSync[gpuIndex] = newInputSignal("ZStencilSync", interGPUBusWidth/sizeof(unsigned int),
			                            interGPUBusLat, signalPrefix);
            sprintf(signalPrefix, "GPU%dZST%dTo%d", gpuId, stampId, gpuIndex);
            interGPUSyncBackPressure[gpuIndex] = newOutputSignal("ZStencilSyncBackPressure", 1, 1, signalPrefix);
	}
    }

    //  Currently only S8D24 format supported for the stencil and depth buffer.
    bytesPixel[0] = 4;
    
    //
    //  !!!NOTE: A cache line contains a number of stamps from
    //  the same tile.  The stamps in a line must be in sequential
    //  lines.  !!!
    //
    bytesLine = stampsLine * STAMP_FRAGMENTS * bytesPixel[0];

    //  Calculate the line shift and mask.
    lineShift = GPUMath::calculateShift(bytesLine);
    lineMask = GPUMath::buildMask(zCacheLines);

    //   Calculate stamp unit stride in block (gen tiles).
    u32bit strideUnit = u32bit(ceil((scanWidth * scanHeight) / f32bit (genWidth * genHeight)));

    GPU_ASSERT(
        if (GPU_MOD(zBlocks, numStampUnits) != 0)
	    panic("ZStencilTestV2", "ZStencilTestV2", "Invalid number of zBlocks");
    )

    //  Initialize Z cache.
    zCache = new ZCacheV2(
        gpuId,
	numGPUs,
	stampId,
        zCacheWays,                 /*  Number of ways in the Z Cache.  */
        zCacheLines,                /*  Number of lines per way.  */
        bytesLine,                  /*  Stamps per line.  */
        1 + (extraReadPort?1:0),    /*  Read ports.  */
        1 + (extraWritePort?1:0),   /*  Write ports.  */
        cachePortWidth,             /*  Width of the z cache ports (bytes).  */
        cacheReqQSz,                /*  Size of the memory request queue.  */
        inputReqQSz,                /*  Size of the input request queue.  */
        outputReqQSz,               /*  Size of the output request queue.  */
        disableZCompression,        /*  Disables Z Compression and HZ update.  */
        numStampUnits,              /*  Number of stamp units in the GPU.  */
        strideUnit,                 /*  Stamp unit stride in blocks.  */
        (zBlocks/numStampUnits),    /*  Number of Z blocks in the state memory.  */
        blocksCycle,                /*  Number of Z blocks cleared per cycle.  */
        comprCycles,                /*  Number of cycles to compress a Z block.  */
        decomprCycles,              /*  Number of cycles to decompress a Z block.  */
	pixelMapper,
	activeBuffer,
	bufferAddress,
	bufferAddressForComp,
	equation,
	srcRGB,
	dstRGB,
	srcAlpha,
	dstAlpha,
        postfix                     /*  Postfix for the cache statistics.  */
        );

    //  Set ROP cache.
    ropCache = zCache;

    //  Calculate the total number of stamps that can be in the Z Stencil Test pipeline
    freeQueueSize = zInQSize + zFetchQSize + zReadQSize + testLat + zOpQSize + zWriteQSize +
	            zSyncInQSize + zSyncFetchQSize + zSyncReadQSize;
    freeQueue.resize(freeQueueSize);

    //  Initialize free stamp queue entries.
    for(int i = 0; i < freeQueueSize; i++)
    {
        ROPQueue *freeStamp;

        //  Allocate a new Z stamp queue entry.
        freeStamp = new ROPQueue;

        //  Allocate the buffer for Z Stencil buffer data.
        freeStamp->data = new u8bit[STAMP_FRAGMENTS * MAX_MSAA_SAMPLES * bytesPixel[0]];

        //  Allocate the mask for the Z Stencil buffer data.
        freeStamp->mask = new bool[STAMP_FRAGMENTS * MAX_MSAA_SAMPLES * bytesPixel[0]];

        //  Add the created stamp containter to the free queue.
        freeQueue.add(freeStamp);
    }

    //  Create a dummy initial rasterizer command.
    lastRSCommand = new RasterizerCommand(RSCOM_RESET);

    //  Validation mode is disabled by default.
    validationMode = false;

    //  Debug/log.
    traceFragment = false;
    watchFragmentX = 0;
    watchFragmentY = 0;

    pixelMapper[0].setupUnit(numStampUnits, 0);

    //  Set initial state to reset.
    state = RAST_RESET;
}


//  Function called from the the Generic ROP clock after updating the cache.
void ZStencilTestV2::postCacheUpdate(u64bit cycle)
{
    u32bit hzBlock;
    u32bit hzBlockZ;

    //  Check updates for Hierarchical Z from the Z cache.
    if ((!disableHZUpdate) && zCache->updateHZ(hzBlock, hzBlockZ))
    {
        GPU_DEBUG_BOX(
            printf("ZStencilTest => Sending update to Hierarchical Z.  Block %x Z %x\n",
                hzBlock, hzBlockZ);
        )

        //  Send update to the Hierarchical Z.
        hzUpdate->write(cycle, new HZUpdate(hzBlock, hzBlockZ));

        //  Update statistics.
        updatesHZ->inc();
        globalUpdatesHZ->inc();
    }
}

//  Function called from the Generic ROP clock in reset state.
void ZStencilTestV2::reset()
{
    //  Reset Z Stencil registers to default values.
    hRes = 400;
    vRes = 400;
    startX = 0;
    startY = 0;
    width = 400;
    height = 400;
    clearDepth = 0x00ffffff;
    clearDepthForComp = 0x00ffffff;
    clearStencil = 0x00;
    modifyDepth = false;
    stencilTest = false;
    stencilFunction = GPU_ALWAYS;
    stencilReference = 0x00;
    stencilTestMask = 0xff;
    stencilUpdateMask = 0xff;
    stencilFail = STENCIL_KEEP;
    depthFail = STENCIL_KEEP;
    depthPass = STENCIL_KEEP;
    zTest = false;
    depthFunction = GPU_LESS;
    depthMask =  true;
    multisampling = false;
    msaaSamples = 2;
    compression = true;
    
    //  By default set Z buffer at 4 MB.
    zBuffer = 0x600000;

    //  Set the ROP data buffer address.
    bufferAddress[0] = zBuffer;
    bufferAddressForComp[0] = zBuffer;
    stateBufferAddress = 0x00000000;
    
    for(u32bit b = 0; b < MAX_RENDER_TARGETS; b++) {
        activeBuffer[b] = false;
	writeR[b] = writeG[b] = writeB[b] = writeA[b] = true;
	srcRGB[b] = BLEND_ONE;
	dstRGB[b] = BLEND_ONE;
	srcAlpha[b] = BLEND_ZERO;
	dstAlpha[b] = BLEND_ZERO;
    }
    activeBuffer[0] = true;
    numActiveBuffers = 1;

    //  Set bypass and enable read flags.
    bypassROP[0] = !(zTest || stencilTest);
    readDataROP[0] = true;

    memoryCycles = 0;
    nextWriteTicket = 0;

    near = 0.0;

    testedFragments = 0;

    batchCounter = 0;
    frameCounter = 0;
}

//  This function is called when a stamp exits from the operation latency signal.
void ZStencilTestV2::operateStamp(u64bit cycle, ROPQueue *stamp)
{
    Fragment *fr;
    QuadFloat *attrib;
    u32bit inputDepth[STAMP_FRAGMENTS * MAX_MSAA_SAMPLES];
    bool sampleCullMask[STAMP_FRAGMENTS * MAX_MSAA_SAMPLES];
    bool overwriteDepthMask[STAMP_FRAGMENTS * MAX_MSAA_SAMPLES];
    int i;
    
    bool traceFragmentMatch = false;

    FILE *debugfile = NULL;
    
    //  Get the input depth data from the fragments.
    for(i = 0; i < STAMP_FRAGMENTS; i++)
    {
        //  Get fragment attributes.
        attrib = stamp->stamp[i]->getAttributes();

        //  Get fragment.
        fr = stamp->stamp[i]->getFragment();

        //  Check if fragment tracing is enabled.
        if (traceFragment)
        {
            //  Detect the fragment to trace.
            traceFragmentMatch = traceFragmentMatch || (fr->getX() == watchFragmentX) && (fr->getY() == watchFragmentY);
                
        }
        
        //  Check if the current fragment matches the fragment to trace.
        if (traceFragmentMatch)
        {
            printf("%s => Start processing pixel (%d, %d) triangle ID %d\n", getName(), fr->getX(),
                fr->getY(), stamp->stamp[i]->getTriangleID());
        }

        //  Check if fragment depth was modified by the fragment shader.
        if (modifyDepth && stamp->stamp[i]->getType() != FRAG_COMP_IN)
        {
            //  Check if multisampling is enabled.
            if (!multisampling)
            {
                //  Convert modified fragment depth to integer format.
                inputDepth[i] = rastEmu.convertZ(GPU_CLAMP(attrib[POSITION_ATTRIBUTE][3], 0.0f, 1.0f));
	        //overwriteDepthMask[i] = zCache->compMode && !zCache->anyRtBlend && (inputDepth[i] != rastEmu.convertZ(near));
		overwriteDepthMask[i] = false;

    	        //if (fr->getX() == 172 && fr->getY() == 146) {
    	        //    debugfile = fopen("comp_zst_debug.txt", "a+");
    	        //    fprintf(debugfile, "%s cycle %lld frame %d batch %d pixel (%d, %d) f %d type %d modifyDepth T attrib %f input_depth %08x ",
	        //	    getName(), cycle, frameCounter, batchCounter, fr->getX(), fr->getY(), i,
		//	    stamp->stamp[i]->getType(), attrib[POSITION_ATTRIBUTE][3], inputDepth[i]);
    	        //}
            }
            else
            {
                //  Get pointer to the coverage mask for the fragment.
                bool *fragmentCoverage = fr->getMSAACoverage();

                //  Convert modified fragment depth to integer format.
                inputDepth[i * msaaSamples] = rastEmu.convertZ(GPU_CLAMP(attrib[POSITION_ATTRIBUTE][3], 0.0f, 1.0f));
                sampleCullMask[i * msaaSamples] = !fragmentCoverage[0];
		// current composition implementation does not support multi-sampling
	        overwriteDepthMask[i * msaaSamples] = false;

                //  Copy Z sample values from the fragment z value computed in the shader.
                for(u32bit j = 1; j < msaaSamples; j++)
                {
		    // Xiaowei:  I think this is buggy, index should be j*msaaSamples+i.
		    // Currently, all benchmark assume no msaaSampling, so this bug has no impact 
                    inputDepth[i * msaaSamples + j] = inputDepth[i * msaaSamples];
                    sampleCullMask[i * msaaSamples + j] = !fragmentCoverage[j];
	            overwriteDepthMask[i * msaaSamples + j] = overwriteDepthMask[i * msaaSamples];
                }
            }
        }
        else
        {
            //  Check if multisampling is enabled.
            if (!multisampling)
            {
                //  Copy input z from the fragment.
                inputDepth[i] = fr->getZ();
	        //overwriteDepthMask[i] = zCache->compMode && !zCache->anyRtBlend && (inputDepth[i] != rastEmu.convertZ(near));
		overwriteDepthMask[i] = false;

    	        //if (fr->getX() == 172 && fr->getY() == 146) {
    	        //    debugfile = fopen("comp_zst_debug.txt", "a+");
    	        //    fprintf(debugfile, "%s cycle %lld frame %d batch %d pixel (%d, %d) f %d type %d modifyDepth F input_depth %08x zTest %s stencilTest %s depthMask %s compMode %s overwriteDepthMask %s ",
	        //	    getName(), cycle, frameCounter, batchCounter, fr->getX(), fr->getY(), i,
		//	    stamp->stamp[i]->getType(), inputDepth[i], zTest ? "T" : "F",
		//	    stencilTest ? "T" : "F", depthMask ? "T" : "F", zCache->compMode ? "T" : "F",
		//	    overwriteDepthMask[i] ? "T" : "F");
    	        //}
            }
            else
            {
                //  Get pointer to the Z samples for the fragment.
                u32bit *fragmentZSamples = fr->getMSAASamples();
                
                //  Get pointer to the coverage mask for the fragment.
                bool *fragmentCoverage = fr->getMSAACoverage();
                
		//  Copy Z sample values.
                for(u32bit j = 0; j < msaaSamples; j++)
                {
		    // Xiaowei:  I think this is buggy, index should be j*msaaSamples+i.
		    // Currently, all benchmark assume no msaaSampling, so this bug has no impact 
                    inputDepth[i * msaaSamples + j] = fragmentZSamples[j];
                    sampleCullMask[i * msaaSamples + j] = !fragmentCoverage[j];
		    // current composition implementation does not support multi-sampling
	            overwriteDepthMask[i * msaaSamples + j] = false;
                }
            }
        }

        //  Check if multisampling is enabled.
        if (!multisampling)
        {
            //  Build write mask for the stamp.
            stamp->mask[i * bytesPixel[0] + 3] = (stencilUpdateMask == 0)?false:true;
            stamp->mask[i * bytesPixel[0] + 2] =
            stamp->mask[i * bytesPixel[0] + 1] =
            stamp->mask[i * bytesPixel[0] + 0] = depthMask || overwriteDepthMask[i];

	    if (!zCache->compMode && (!zCache->backgroundDraw || testedFragments > 0) && depthMask && (!zTest || depthFunction == GPU_ALWAYS)) {
	        if (testedFragments == 0)
	            zCache->backgroundDraw = ((inputDepth[i] & 0x00ffffff) == 0x00ffffff);
	        else
		    zCache->backgroundDraw = zCache->backgroundDraw && ((inputDepth[i] & 0x00ffffff) == 0x00ffffff);

	        testedFragments++;
	    }
        }
        else
        {
            //  Create write mask for all the samples in the stamp.
            for(u32bit j = 0; j < msaaSamples; j++)
            {
                //  Build write mask for the stamp.
                stamp->mask[(i * msaaSamples + j) * bytesPixel[0] + 3] = (stencilUpdateMask == 0)?false:true;
                stamp->mask[(i * msaaSamples + j) * bytesPixel[0] + 2] =
                stamp->mask[(i * msaaSamples + j) * bytesPixel[0] + 1] =
                stamp->mask[(i * msaaSamples + j) * bytesPixel[0] + 0] = depthMask || overwriteDepthMask[i * msaaSamples + j];
            }
        }
    }

    GPU_DEBUG_BOX(
    //if ((stamp->stamp[0]->getFragment()->getX() == 0) && (stamp->stamp[0]->getFragment()->getY() == 144))
    //{
        cout << "<< ZStencilTestV2::operateStamp >>" << endl;
        cout << "Depth Test = " << zTest << " | Depth Function = " << depthFunction << " | Depth Mask = " << depthMask << endl;
        cout << "Stencil Test = " << stencilTest << " | Stencil Function = " << stencilFunction;
        cout << " | Stencil Reference = " << u32bit(stencilReference) << " | Stencil Test Mask = " << u32bit(stencilTestMask) << endl;
        cout << "Stencil Update Mask = " << u32bit(stencilUpdateMask) << " | Stencil Fail Function = " << stencilFail;
        cout << " | Depth Fail Function = " << depthFail << " | Depth Pass Function = " << depthPass << endl;
        cout << "Input Depth = ";
        for(int j = 0; j < STAMP_FRAGMENTS * ((multisampling) ? msaaSamples : 1); j++)
            cout << hex << inputDepth[j] << " ";
        cout << endl;
        cout << "Buffer Address = " << hex << stamp->address << dec << endl;
        cout << "Buffer Depth = ";
        for(int j = 0; j < STAMP_FRAGMENTS * ((multisampling) ? msaaSamples : 1); j++)
            cout << hex << ((u32bit *) stamp->data)[j] << " ";
        cout << endl;
        cout << "Cull Mask = ";
        for(int j = 0; j < STAMP_FRAGMENTS * ((multisampling) ? msaaSamples : 1); j++)
            cout << stamp->culled[j] << " ";
        cout << endl;
        cout << "Write Mask = ";
        for(int j = 0; j < STAMP_FRAGMENTS * ((multisampling) ? msaaSamples : 1); j++)
        {
            cout << stamp->mask[j * bytesPixel[0]] << " " << stamp->mask[j * bytesPixel[0] + 1] << " ";
            cout << stamp->mask[j * bytesPixel[0] + 2] << " " << stamp->mask[j * bytesPixel[0] + 3] << " | ";
        }
        cout << endl;
    //}
    )

    FragmentQuadMemoryUpdateInfo quadMemUpdate;
    bool anyNotAlreadyCulled;

    //  Check if multisampling is enabled
    if (!multisampling)
    {
        //  Check if validation mode is enabled.
        if (validationMode)
        {
            //  Check if there are unculled fragments in the quad.
            anyNotAlreadyCulled = false;
            for(u32bit f = 0; (f < STAMP_FRAGMENTS) && !anyNotAlreadyCulled; f++)
                anyNotAlreadyCulled = anyNotAlreadyCulled || !stamp->culled[f];

            //  Store the information for the quad if there is a valid fragment.
            if (anyNotAlreadyCulled)
            {
                //  Set the quad identifier to the top left fragment of the quad.
                quadMemUpdate.fragID.x = stamp->stamp[0]->getFragment()->getX();
                quadMemUpdate.fragID.y = stamp->stamp[0]->getFragment()->getY();
                quadMemUpdate.fragID.triangleID = stamp->stamp[0]->getTriangleID();
                
                quadMemUpdate.fragID.sample = 0;

                //  Copy the input (z computed for fragment) and read data (z/stencil from the z stencil buffer) for
                //  the quad.
                for(u32bit qw = 0; qw < ((bytesPixel[0] * 4) >> 3); qw++)
                {
                    ((u64bit *) quadMemUpdate.inData)[qw] = ((u64bit *) inputDepth)[qw];
                    ((u64bit *) quadMemUpdate.readData)[qw] = ((u64bit *) stamp->data)[qw];
                }

                if (traceFragmentMatch)
                {
                    printf("%s (%lld) => Read Data from @(%08x, %d, %d) : %08x %08x %08x %08x\n", getName(), cycle,
                        stamp->address[0], stamp->way[0], stamp->line[0],
                        ((u32bit *) quadMemUpdate.readData)[0], ((u32bit *) quadMemUpdate.readData)[1],
                        ((u32bit *) quadMemUpdate.readData)[2], ((u32bit *) quadMemUpdate.readData)[3]);
                }
            }
        }

	bool zFighted[STAMP_FRAGMENTS];
	for (u32bit f = 0; f < STAMP_FRAGMENTS; f++)
	    zFighted[f] = ((inputDepth[f] & 0x00ffffff) == (*((u32bit*)(stamp->data) + f) & 0x00ffffff));

	if (debugfile) {
	    fprintf(debugfile, "data %08x ", *((u32bit*)stamp->data));
	}

        //  Perform Stencil and Z tests.
        frEmu.stencilZTest(inputDepth, (u32bit *) stamp->data, stamp->culled, overwriteDepthMask);
	zCache->recordWriteForComp(0, stamp->address[0], stamp->culled);

	if (debugfile) {
	    fprintf(debugfile, "results %08x culled %s blockState %d dirty %s\n",
		    *((u32bit*)stamp->data), stamp->culled[0] ? "T" : "F",
		    zCache->getAddrBlockState(stamp->address[0]).getState(),
		    zCache->getAddrBlockState(stamp->address[0]).dirty ? "T" : "F");
	}

	for (u32bit f = 0; f < STAMP_FRAGMENTS; f++) {
	    if (stamp->culled[f] || !depthMask)
		continue;

	    if (zFighted[f] && (zFightingInfo.count(stamp->address[0] + bytesPixel[0] * f) == 0))
	        continue;

	    std::set<u32bit> &fightedDraws = zFightingInfo[stamp->address[0] + bytesPixel[0] * f];

	    if (!zFighted[f])
	        fightedDraws.clear();

	    fightedDraws.insert(batchCounter);

	    if (fightedDraws.size() > 1) {
		std::set<u32bit>::iterator drawIt;
		for (drawIt = fightedDraws.begin(); drawIt != fightedDraws.end(); drawIt++) {
		    if (*drawIt == batchCounter)
			continue;

		    zFightedDraws[*drawIt].insert(batchCounter);
		    zFightedDraws[batchCounter].insert(*drawIt);
		}
	    }
	}

        if (validationMode)
        {
            //  Check if the current fragment matches the fragment to trace.
            if (traceFragmentMatch)
            {
                printf("%s => Checking if pixel (%d, %d) triangle ID %d must be added to Memory Update Map.\n", getName(), watchFragmentX,
                    watchFragmentY, stamp->stamp[0]->getTriangleID());
            }
            
            //  Check if there are unculled fragments in the quad.
            anyNotAlreadyCulled = false;
            for(u32bit f = 0; (f < STAMP_FRAGMENTS) && !anyNotAlreadyCulled; f++)
                anyNotAlreadyCulled = anyNotAlreadyCulled || !stamp->culled[f];

            //  Store information for the quad and add to the z/stencil memory update map.
            if (anyNotAlreadyCulled)
            {
                //  Store the result z and stencil results for the quad.
                for(u32bit qw = 0; qw < ((bytesPixel[0] * 4) >> 3); qw++)
                    ((u64bit *) quadMemUpdate.writeData)[qw] = ((u64bit *) stamp->data)[qw];
                    
                //  Store the write mask for the quad after the write.
                for(u32bit b = 0; b < (STAMP_FRAGMENTS * bytesPixel[0]); b++)
                    quadMemUpdate.writeMask[b] = stamp->mask[b];
                    
                //  Store the write mask for the quad after write.
                for(u32bit f = 0; f < STAMP_FRAGMENTS; f++)
                    quadMemUpdate.cullMask[f] = stamp->culled[f];
                    
                //  Store the information for the quad in the z stencil memory update map.
                zstencilMemoryUpdateMap.insert(make_pair(quadMemUpdate.fragID, quadMemUpdate));

                //  Check if the current fragment matches the fragment to trace.
                if (traceFragmentMatch)
                {
                    printf("%s => Adding pixel (%d, %d) triangle ID %d to Memory Update Map.\n", getName(), watchFragmentX,
                        watchFragmentY, stamp->stamp[0]->getTriangleID());
                }
            }
        }
    }
    else
    {
        //  Create cull mask for the samples
        
        //  Perform Stencil and Z tests for all the stamps.
        for(u32bit i = 0; i < msaaSamples; i++)
            frEmu.stencilZTest(&inputDepth[i * STAMP_FRAGMENTS],
                               (u32bit *) &stamp->data[i * STAMP_FRAGMENTS * bytesPixel[0]],
                               &sampleCullMask[i * STAMP_FRAGMENTS],
			       &overwriteDepthMask[i * STAMP_FRAGMENTS]);
                               
        //  Update coverage mask for all the fragments in the stamp.
        for(u32bit i = 0; i < STAMP_FRAGMENTS; i++)
        {
            //  Get pointer to the coverage mask for the fragment.
            bool *fragmentCoverage = stamp->stamp[i]->getFragment()->getMSAACoverage();
            
            bool allSamplesCulled = true;
            
            //  Update coverage mask for the sample.
            for(u32bit j = 0; j < msaaSamples; j++)
            {
                fragmentCoverage[j] = !sampleCullMask[i * msaaSamples + j];
                
                //  Check if all the samples in the fragment were culled.
                allSamplesCulled = allSamplesCulled && sampleCullMask[i * msaaSamples + j];
            }
            
            //  Set cull mask for the fragment.
            stamp->culled[i] = allSamplesCulled;
        }
    }

    if (debugfile) {
	fflush(debugfile);
	fclose(debugfile);
    }
    
    GPU_DEBUG_BOX(
    //if ((stamp->stamp[0]->getFragment()->getX() == 0) && (stamp->stamp[0]->getFragment()->getY() == 144))
    //{
        cout << "<< ZStencilTestV2::operateStamp >>" << endl;
        cout << "Final Depth = ";
        for(int j = 0; j < STAMP_FRAGMENTS * ((multisampling) ? msaaSamples : 1); j++)
            cout << hex << ((u32bit *) stamp->data)[j] << " ";
        cout << endl;
        cout << "Final Cull Mask = ";
        for(int j = 0; j < STAMP_FRAGMENTS * ((multisampling) ? msaaSamples : 1); j++)
            cout << stamp->culled[j] << " ";
        cout << endl;
        cout << "Final Write Mask = ";
        for(int j = 0; j < STAMP_FRAGMENTS * ((multisampling) ? msaaSamples : 1); j++)
        {
            cout << stamp->mask[j * bytesPixel[0]] << " " << stamp->mask[j * bytesPixel[0] + 1] << " ";
            cout << stamp->mask[j * bytesPixel[0] + 2] << " " << stamp->mask[j * bytesPixel[0] + 3] << " | ";
        }
        cout << endl;
    //}
    )

    //  Update statistics.
    tested->inc(STAMP_FRAGMENTS);
    globalTested->inc(STAMP_FRAGMENTS);
    for(i = 0; i < STAMP_FRAGMENTS; i++)
    {
        if (stamp->culled[i]) {
            failed->inc();
            globalFailed->inc();
        } else {
            passed->inc();
            globalPassed->inc();
	}
    }
}

//  This function is called for stamps
void ZStencilTestV2::postWriteProcess(u64bit cycle, ROPQueue *stamp)
{
    //  NOTE:  STAMPS TO BE SENT TO CONSUMER STAGE MUST COME IN ORDER
    //    THIS MEANS THAT IT MAY NOT WORK IF BATCHES WITH Z-STENCIL
    //    ENABLED AND BATCHES WITH Z-STENCIL DISABLED ARE PIPELINED.  */

    //  Update fragment culled flags and send the stamp fragments to the consumer stage.
    for(int i = 0; i < STAMP_FRAGMENTS; i++)
    {
        //  Set the fragment new cull value.
        stamp->stamp[i]->setCull(stamp->culled[i]);

        //  Send stamp to the consumer stage (Fragment FIFO).
        outFragmentSignal->write(cycle, stamp->stamp[i]);

        //  Update statistics.
        outputs->inc();
        globalOutputs->inc();
    }

    //  Delete the stamp container.
    delete[] stamp->stamp;
}

//  This function is called by the generic ROP clock in the flush state.
void ZStencilTestV2::flush(u64bit cycle)
{
    u32bit zStencilBufferScanTiles;
    u32bit zStencilBufferBlocks;
    ROPBlockState *zStencilBlockState;
    ColorBlockStateInfo *zStencilBlockStateInfo;

    //u32bit resWidth, resHeight;
    //pixelMapper[0].getResolution(resWidth, resHeight);

    //  Check if the flush of the z and stencil cache has finished.
    if (!endFlush)
    {
        //  Continue flushing the cache.
        if(!zCache->flush())
        {
            //  Compute the number of scan tiles that form the frame buffer.
            //zStencilBufferScanTiles = (u32bit)(ceil(resWidth / f32bit(genH * scanH * genH * STAMP_HEIGHT))) *
            //                          (u32bit)(ceil(resHeight / f32bit(genW * scanW * genW * STAMP_WIDTH))) * genH * genW;

	    zStencilBufferScanTiles = pixelMapper[0].computeNumOfScanTiles();
                                           
            //  Multiply by the number of blocks in a scan tile based on the surface format and the number 
            //  of MSAA samples.  Then divide by the number of stamp units.
            zStencilBufferBlocks = u32bit(ceil((zStencilBufferScanTiles * (bytesPixel[0] >> 2) *
                                               (multisampling ? msaaSamples : 1) * scanH * scanW) / f32bit(numStampUnits)));

            //  Allocate the color block states.
            zStencilBlockState = new ROPBlockState[zStencilBufferBlocks];

            //  Check allocation.
            GPU_ASSERT(
                if (zStencilBlockState == NULL)
                    panic("ZStencilTest", "swap", "Error allocating z stencil block state memory.");
            )

            //  Get the z stencil block states.
            zCache->copyBlockStateMemory(zStencilBlockState, zStencilBufferBlocks);

            //  Create object for the DAC.
            zStencilBlockStateInfo = new ColorBlockStateInfo(zStencilBlockState, zStencilBufferBlocks);

            //  Copy cookies from the last command from the Command Processor.
            zStencilBlockStateInfo->copyParentCookies(*lastRSCommand);

            //  Add a cookie level.
            zStencilBlockStateInfo->addCookie();

            //  Send z stencil buffer block state to the DAC.
            blockStateDAC->write(cycle, zStencilBlockStateInfo);

            //  Set flush end.
            endFlush = true;
        }
    }
    else
    {
        //printf("%s => End of flush.  Cycle %lld\n", getName(), cycle);
        //  End of flush.
        state = RAST_END;
    }
}

//  This function is called by the generic ROP clock in the swap state.
void ZStencilTestV2::swap(u64bit cycle)
{
    u32bit zStencilBufferScanTiles;
    u32bit zStencilBufferBlocks;
    ROPBlockState *zStencilBlockState;
    ColorBlockStateInfo *zStencilBlockStateInfo;

    //u32bit resWidth, resHeight;
    //pixelMapper[0].getResolution(resWidth, resHeight);

    //  Check if the flush of the color cache has finished.
    if (!endFlush)
    {
        //  Continue flushing the cache.
        if(!zCache->flush())
        {
            //  Compute the number of scan tiles that form the frame buffer.
            //zStencilBufferScanTiles = (u32bit)(ceil(resWidth / f32bit(genH * scanH * genH * STAMP_HEIGHT))) *
            //                          (u32bit)(ceil(resHeight / f32bit(genW * scanW * genW * STAMP_WIDTH))) * genH * genW;
                                           
	    zStencilBufferScanTiles = pixelMapper[0].computeNumOfScanTiles();
                                           
            //  Multiply by the number of blocks in a scan tile based on the surface format and the number 
            //  of MSAA samples.  Then divide by the number of stamp units.
            zStencilBufferBlocks = u32bit(ceil((zStencilBufferScanTiles * (bytesPixel[0] >> 2) *
                                               (multisampling ? msaaSamples : 1) * scanH * scanW) / f32bit(numStampUnits)));

            //  Allocate the color block states.
            zStencilBlockState = new ROPBlockState[zStencilBufferBlocks];

            //  Check allocation.
            GPU_ASSERT(
                if (zStencilBlockState == NULL)
                    panic("ZStencilTest", "swap", "Error allocating z stencil block state memory.");
            )

            //  Get the z stencil block states.
            zCache->copyBlockStateMemory(zStencilBlockState, zStencilBufferBlocks);

            //  Create object for the DAC.
            zStencilBlockStateInfo = new ColorBlockStateInfo(zStencilBlockState, zStencilBufferBlocks);

            //  Copy cookies from the last command from the Command Processor.
            zStencilBlockStateInfo->copyParentCookies(*lastRSCommand);

            //  Add a cookie level.
            zStencilBlockStateInfo->addCookie();

            //  Send z stencil buffer block state to the DAC.
            blockStateDAC->write(cycle, zStencilBlockStateInfo);

            //  Set cycles for copying the z stencil buffer block state to the DAC.
            copyStateCycles = (u32bit) ceil((f32bit) zStencilBufferBlocks / (f32bit) blocksCycle);

            //  Set flush end.
            endFlush = TRUE;
        }
    }
    else
    {
        //  Check if copying color block state memory to the DAC.
        if (copyStateCycles > 0)
        {
            //  Update cycle counter.
            copyStateCycles--;

            //  Check if end of the copy.
            if (copyStateCycles == 0)
            {
//printf("ZStencilTest => End of swap.  Cycle %lld\n", cycle);

		batchCounter = 0;
		frameCounter++;

                //  End of swap.
                state = RAST_END;
            }
        }
    }
}

//  This function is called by the generic ROP clock in the clear state.
void ZStencilTestV2::clear()
{
    //  Check if the Z cache has finished the clear.
    if (!zCache->clear(clearDepth, clearStencil))
    {
        //  Change to end state.
        state = RAST_END;
    }
}

//  This function is called by the Generic ROP clock when a batch processing is finished.
void ZStencilTestV2::endBatch(u64bit cycle)
{
    //  Send empty last stamp to consumer stage.
    for(int i = 0; i < STAMP_FRAGMENTS; i++)
    {
        //  Send stamp to Color Write.
        outFragmentSignal->write(cycle, lastBatchStamp.stamp[i]);

        //  Update statistics.
        outputs->inc();
        globalOutputs->inc();
    }

    //  Delete the stamp container.
    delete[] lastBatchStamp.stamp;
}

//  Processes a rasterizer command.
void ZStencilTestV2::processCommand(RasterizerCommand *command, u64bit cycle)
{
    u32bit samples;

    //  Delete last command.
    delete lastRSCommand;

    //  Store current command as last received command.
    lastRSCommand = command;

    //  Process command.
    switch(command->getCommand())
    {
        case RSCOM_RESET:
            //  Reset command from the Rasterizer main box.

            GPU_DEBUG_BOX(
                printf("%s => RESET command received.\n", getName());
            )

            //  Change to reset state.
            state = RAST_RESET;

            break;

        case RSCOM_DRAW:
            //  Draw command from the Rasterizer main box.

            GPU_DEBUG_BOX(
                printf("%s (%lld) => DRAW command received.\n", getName(), cycle);
            )

            //  Check current state.
            GPU_ASSERT(
                if (state != RAST_READY)
                    panic("ZStencilTest", "processRegisterWrite", "DRAW command can only be received in READY state.");
            )

            //  Configure Z test emulation.
            frEmu.configureZTest(depthFunction, depthMask);
            frEmu.setZTest(zTest);

            //  Configure stencil test emulation.
            frEmu.configureStencilTest(stencilFunction, stencilReference,
                stencilTestMask, stencilUpdateMask, stencilFail,
                depthFail, depthPass);
            frEmu.setStencilTest(stencilTest);

            //  Set display parameters in the Pixel Mapper.
            //samples = multisampling ? msaaSamples : 1;
	    //if (zStencilBufferDefined)
            //pixelMapper[0].setupDisplay(hRes, vRes, STAMP_WIDTH, STAMP_WIDTH, genW, genH, scanW, scanH, overW, overH,
            //    displayW, displayH, samples, bytesPixel[0]);

            //  Reset triangle counter.
            triangleCounter = 0;

            //  Reset batch fragment counter.
            fragmentCounter = 0;

            //  Reset previous processed triangle.
            currentTriangle = (u32bit) -1;

            //  Last batch fragment no received yet.
            lastFragment = FALSE;

	    testedFragments = 0;

	    batchCounter = command->getBatchCounter();
	    frameCounter = command->getFrameCounter();

	    if (profileForSortLast && stampId == 0) {
	        FILE *ZTestInfoFile = fopen("zTestInfo.obj", "a+");
		fprintf(ZTestInfoFile, "d %d %d %s %d %s %d %s 0x%02x\n", frameCounter, batchCounter,
			zTest ? "T" : "F", depthFunction, stencilTest ? "T" : "F", stencilFunction,
			depthMask ? "T" : "F", stencilUpdateMask);
		fflush(ZTestInfoFile);
		fclose(ZTestInfoFile);
	    }

            //  Change to drawing state.
            state = RAST_DRAWING;

            break;

        case RSCOM_END:
            //  End command received from Rasterizer main box.

            GPU_DEBUG_BOX(
                printf("%s => END command received.\n", getName());
            )

            //  Check current state.
            GPU_ASSERT(
                if (state != RAST_END)
                    panic("ZStencilTest", "processCommand", "END command can only be received in END state.");
            )

            //  Change to ready state.
            state = RAST_READY;

            break;

        case RSCOM_REG_WRITE:
            //  Write register command from the Rasterizer main box.

            GPU_DEBUG_BOX(
                printf("%s => REG_WRITE command received.\n", getName());
            )

            //  Check current state.
            GPU_ASSERT(
                if (state != RAST_READY)
                    panic("ZStencilTest", "processCommand", "REGISTER WRITE command can only be received in READY state.");
            )

            //  Process register write.
            processRegisterWrite(command->getRegister(),
                command->getSubRegister(), command->getRegisterData());

            break;

        case RSCOM_DUMP_DEPTH:
        case RSCOM_DUMP_STENCIL:
            
            //  DUMP BUFFER command.

            GPU_DEBUG_BOX(
                printf("%s => DUMP_BUFFER command received.\n", getName());
            )

            //  Check current state.
            GPU_ASSERT(
                if (state != RAST_READY)
                    panic("ZStencilTest", "processCommand", "DUMP_BUFFER command can only be received in READY state.");
            )

            //  Reset Z cache flush flag.
            endFlush = false;

            //  Change state to swap state.
            state = RAST_SWAP;

            break;

       case RSCOM_FLUSH:
            //  Flush Z Stencil caches command.

            GPU_DEBUG_BOX(
                printf("%s => FLUSH command received.\n", getName());
            )

            //  Check current state.
            GPU_ASSERT(
                if (state != RAST_READY)
                    panic("ZSTencilTest", "processCommand", "FLUSH command can only be received in READY state.");
            )

	    if (profileForSortLast && stampId == 0) {
	        FILE *blendInfoFile = fopen("blendInfo.obj", "a+");
		if (batchCounter == 0)
		    fprintf(blendInfoFile, "syncZStencil %d %d\n", frameCounter, batchCounter);
		else
		    fprintf(blendInfoFile, "syncZStencil %d %d\n", frameCounter, batchCounter + 1);
		fflush(blendInfoFile);
		fclose(blendInfoFile);
	    }

            //  Reset color cache flush flag.
            endFlush = false;

            //  Change state to swap state.
            state = RAST_FLUSH;

            break;

       case RSCOM_SAVE_STATE:
            //  Save state Z Stencil caches command.

            GPU_DEBUG_BOX(
                printf("%s => SAVE_STATE command received.\n", getName());
            )

            //  Check current state.
            GPU_ASSERT(
                if (state != RAST_READY)
                    panic("ZSTencilTest", "processCommand", "SAVE_STATE command can only be received in READY state.");
            )

            //  Reset color cache flush flag.
            endFlush = false;

            //  Change state to save state state.
            state = RAST_SAVE_STATE;

            break;

       case RSCOM_RESTORE_STATE:
            //  Restore state Z Stencil caches command.

            GPU_DEBUG_BOX(
                printf("%s => RESTORE_STATE command received.\n", getName());
            )

            //  Check current state.
            GPU_ASSERT(
                if (state != RAST_READY)
                    panic("ZSTencilTest", "processCommand", "RESTORE_STATE command can only be received in READY state.");
            )

            //  Reset color cache flush flag.
            endFlush = false;

            //  Change state to restore state state.
            state = RAST_RESTORE_STATE;

            break;

       case RSCOM_RESET_STATE:
            //  Reset block state Z Stencil caches command.

            GPU_DEBUG_BOX(
                printf("%s => RESET_STATE command received.\n", getName());
            )

            //  Check current state.
            GPU_ASSERT(
                if (state != RAST_READY)
                    panic("ZSTencilTest", "processCommand", "RESET_STATE command can only be received in READY state.");
            )

            //  Reset color cache flush flag.
            endFlush = false;

            //  Change state to reset block state state.
            state = RAST_RESET_STATE;

            break;

       case RSCOM_CLEAR_ZSTENCIL_BUFFER:
            //  Clear Z and stencil buffer command.

            //  WARNING:
            //
            //  THIS IMPLEMENATION ONLY SUPPORTS CLEARING BOTH THE Z AND STENCIL BUFFER
            //  AT THE SAME TIME
            //

            GPU_DEBUG_BOX(
                printf("%s => CLEAR_ZSTENCIL_BUFFER command received.\n", getName());
            )

            //  Check current state.
            GPU_ASSERT(
                if (state != RAST_READY)
                    panic("ZStencilTest", "processCommand", "CLEAR command can only be received in READY state.");
            )

            //  Clear the Z cache as any info there will be invalid now.
            zCache->clear(clearDepth, clearStencil);

            //  Change to clear state.
            state = RAST_CLEAR;

            break;

       case RSCOM_CLEARROPBUFFER_FOR_COMP:
            //  Clear Z and stencil buffer command.

            //  WARNING:
            //
            //  THIS IMPLEMENATION ONLY SUPPORTS CLEARING BOTH THE Z AND STENCIL BUFFER
            //  AT THE SAME TIME
            //

            GPU_DEBUG_BOX(
                printf("%s => CLEARROPBUFFER_FOR_COMP command received.\n", getName());
            )

            //  Check current state.
            GPU_ASSERT(
                if (state != RAST_READY)
                    panic("ZStencilTest", "processCommand", "CLEARROPBUFFER_FOR_COMP command can only be received in READY state.");
            )

            //  Clear the Z cache as any info there will be invalid now.
            zCache->clearForComp(clearDepthForComp);

            //  Change to clear state.
            state = RAST_CLEAR_FOR_COMP;

            break;

	case RSCOM_SYNC_STENCIL:

            //  Sync the color buffer block state.
            
            GPU_DEBUG_BOX(
                printf("ZStencilTest-%s (%lld) => RSCOM_SYNC_STENCIL command received.\n", getName(), cycle);
            )
            
            //  Check current state.
            GPU_ASSERT(
                if (state != RAST_END)
                    panic("ZStencilTest", "processCommand", " RSCOM_SYNC_STENCIL command can only be received in END state.");
            )
            
	    state = RAST_SYNC;

	    break;

	case RSCOM_COMP:

            //  Inter-GPU synchronization.
            
            GPU_DEBUG_BOX(
                printf("ZStencilTest-%s (%lld) => RSCOM_COMP command received.\n", getName(), cycle);
            )
            
            //  Check current state.
            GPU_ASSERT(
                if (state != RAST_READY)
                    panic("ZStencilTest", "processCommand", " RSCOM_COMP command can only be received in READY state.");
            )
          
	    bypassZST = !zStencilBufferDefined || !kdInfo.anyZTest || !depthMask;
	    bypassCW = !kdInfo.anyRtCWrite;
	    GPU_ASSERT(
	        if (zCache->anyRtBlend && bypassCW)
	            panic(getName(), "processCommand", "if any rt blend, bypassCW should be false");
	    )
	    
	    std::cout << "Debug: " << getName() << " begin comp @" << cycle << " bypassCW " << (bypassCW ? "T" : "F")
		      << " defined " << (zStencilBufferDefined ? "T" : "F") << " anyZTest " << (kdInfo.anyZTest ? "T" : "F")
		      << " blend " << (zCache->anyRtBlend ? "T" : "F") << " mask " << (depthMask ? "T" : "F")
		      << std::endl;

	    if (bypassZST) {
		zCache->compMode = false;
		state = RAST_END;
	    } else {
                overSyncX = 0;
	        overSyncY = 0;
	        scanSyncX = 0;
	        scanSyncY = 0;
	        genSyncX = 0;
	        genSyncY = 0;
	        stampSyncX = 0;
	        stampSyncY = 0;
	        generatedStamps = 0;
	        allStampsReadForSync[gpuId][stampId] = false;
	        allStampsSentForSync[gpuId][stampId] = false;

		if (zCache->anyRtBlend) {
	            notLastSyncSent = numGPUs;
	            notLastSyncReceive = numGPUs;
		} else {
	            notLastSyncSent = numGPUs - 1;
	            notLastSyncReceive = numGPUs - 1;
		}

	        //nextInQueue = &syncInQueue;
	        //nextFetchQueue = &syncFetchQueue;
	        nextInQueue = &syncQueue;
	        nextFetchQueue = &syncQueue;

		readDataROPForComp = true;
	       
	        if (compSchedEnabled) {
	            GPUDriver::getGPUDriver()->getCompSched()->setAnyRtBlend(gpuId, zCache->anyRtBlend);
		    GPUDriver::getGPUDriver()->getCompSched()->setSendToGPU(gpuId);
		} else {
	            nextSyncReadingGPU[gpuId] = 0;
	            if (gpuId == 0 && !zCache->anyRtBlend)
	                nextSyncReadingGPU[gpuId]++;
		}

	        state = RAST_COMP;
	    }

	    break;

        default:
            panic("ZStencilTest", "proccessCommand", "Unsupported command.");
            break;
    }
}

//  Processes a gpu register write.
void ZStencilTestV2::processRegisterWrite(GPURegister reg, u32bit subreg,
    GPURegData data)
{
    u32bit samples;
    //  Process register write.
    switch(reg)
    {
        case GPU_DISPLAY_X_RES:
            //  Write display horizontal resolution register.
            hRes = data.uintVal;

            samples = multisampling ? msaaSamples : 1;
	    if (zStencilBufferDefined)
            pixelMapper[0].setupDisplay(hRes, vRes, STAMP_WIDTH, STAMP_WIDTH, genW, genH, scanW, scanH, overW, overH,
                displayW, displayH, samples, bytesPixel[0]);
            
	    GPU_DEBUG_BOX(
                printf("%s => Write GPU_DISPLAY_X_RES = %d.\n", getName(), hRes);
            )

            break;

        case GPU_DISPLAY_Y_RES:
            //  Write display vertical resolution register.
            vRes = data.uintVal;

            samples = multisampling ? msaaSamples : 1;
	    if (zStencilBufferDefined)
            pixelMapper[0].setupDisplay(hRes, vRes, STAMP_WIDTH, STAMP_WIDTH, genW, genH, scanW, scanH, overW, overH,
                displayW, displayH, samples, bytesPixel[0]);
            
            GPU_DEBUG_BOX(
                printf("%s => Write GPU_DISPLAY_Y_RES = %d.\n", getName(), vRes);
            )

            break;

        case GPU_VIEWPORT_INI_X:
            //  Write viewport initial x coordinate register.
            startX = data.intVal;

            GPU_DEBUG_BOX(
                printf("%s => Write GPU_VIEWPORT_INI_X = %d.\n", getName(), startX);
            )

            break;

        case GPU_VIEWPORT_INI_Y:
            //  Write viewport initial y coordinate register.
            startY = data.intVal;

            GPU_DEBUG_BOX(
                printf("%s => Write GPU_VIEWPORT_INI_Y = %d.\n", getName(), startY);
            )

            break;

        case GPU_VIEWPORT_WIDTH:
            //  Write viewport width register.
            width = data.uintVal;

            GPU_DEBUG_BOX(
                printf("%s => Write GPU_VIEWPORT_WIDTH = %d.\n", getName(), width);
            )

            break;

        case GPU_VIEWPORT_HEIGHT:
            //  Write viewport height register.
            height = data.uintVal;

            GPU_DEBUG_BOX(
                printf("%s => Write GPU_VIEWPORT_HEIGHT = %d.\n", getName(), height);
            )

            break;

        case GPU_Z_BUFFER_CLEAR:
        
            //  Write depth clear value.
            clearDepth = data.uintVal;

            GPU_DEBUG_BOX(
                printf("%s => Write GPU_Z_BUFFER_CLEAR = %x.\n", getName(), clearDepth);
            )

            break;

        case GPU_COMP_Z_BUFFER_CLEAR:
        
            //  Write depth clear value.
            clearDepthForComp = data.uintVal;

            GPU_DEBUG_BOX(
                printf("%s => Write GPU_COMP_Z_BUFFER_CLEAR = %x.\n", getName(), clearDepthForComp);
            )

            break;

        case GPU_STENCIL_BUFFER_CLEAR:

            //  Write stencil clear value.
            clearStencil = (u8bit) (data.uintVal & 0xff);

            GPU_DEBUG_BOX(
                printf("%s => Write GPU_STENCIL_BUFFER_CLEAR = %x.\n", getName(), clearStencil);
            )

            break;

        case GPU_Z_BUFFER_BIT_PRECISSION:

            //  Write z buffer bit precission register.
            depthPrecission = data.uintVal;

            GPU_DEBUG_BOX(
                printf("%s => Write GPU_Z_BUFFER_BIT_PRECISSION = %x.\n", getName(), depthPrecission);
            )

            break;

        case GPU_ZSTENCILBUFFER_ADDR:
            //  Write z and stencil buffer address register.
            zBuffer = data.uintVal;

            //  Set Z buffer address in the Z cache.
            zCache->swap(zBuffer);

            //  Set ROP data buffer address.
            bufferAddress[0] = zBuffer;

            GPU_DEBUG_BOX(
                printf("%s => Write GPU_ZSTENCILBUFFER_ADDR = %08x.\n", getName(), zBuffer);
            )

            break;

        case GPU_COMP_ZSTENCILBUFFER_ADDR:
            //  Write z and stencil buffer address register.
            zCompBuffer = data.uintVal;

            //  Set Z buffer address in the Z cache.
            //zCache->swapForComp(zCompBuffer);

	    bufferAddressForComp[0] = zCompBuffer;

            GPU_DEBUG_BOX(
                printf("%s => Write GPU_COMP_ZSTENCILBUFFER_ADDR = %08x.\n", getName(), zBuffer);
            )

            break;

        case GPU_ZSTENCIL_STATE_BUFFER_MEM_ADDR:

            //  Set ROP block state buffer address.
            stateBufferAddress = data.uintVal;

            //  Set block state buffer address in the z cache.
            zCache->setStateAddress(stateBufferAddress);

            GPU_DEBUG_BOX(
                printf("%s => Write GPU_ZSTENCIL_STATE_BUFFER_MEM_ADDR = %x\n", getName(), stateBufferAddress);
            )

            break;

        case GPU_MULTISAMPLING:
        
            //  Write Multisampling enable flag.
            multisampling = data.booleanVal;
            
            GPU_DEBUG_BOX(
                printf("%s => Write GPU_MULTISAMPLING = %s\n", getName(), multisampling?"TRUE":"FALSE");
            )
            
            //  Update z cache state.
            if (multisampling)
                zCache->setMSAASamples(msaaSamples);
            else
                zCache->setMSAASamples(1);
                           
            break;
            
        case GPU_MSAA_SAMPLES:
        
            //  Write MSAA z samples per fragment register.
            msaaSamples = data.uintVal;
            
            GPU_DEBUG_BOX(
                printf("%s => Write GPU_MSAA_SAMPLES = %d\n", getName(), msaaSamples);
            )

            //  Update z cache state.
            if (multisampling)
                zCache->setMSAASamples(msaaSamples);
            else
                zCache->setMSAASamples(1);

            break;            
            
        case GPU_MODIFY_FRAGMENT_DEPTH:

            //  Write fragment shader modifies depth flag.
            modifyDepth = data.booleanVal;

            GPU_DEBUG_BOX(
                printf("%s => Write GPU_MODIFY_FRAGMENT_DEPTH = %s\n", getName(), modifyDepth?"TRUE":"FALSE");
            )

            break;

        case GPU_STENCIL_TEST:

            //  Write stencil enabla flag register.
            stencilTest = data.booleanVal;

            //  Update bypass ROP flag.
            bypassROP[0] = !(zTest || stencilTest);

            GPU_DEBUG_BOX(
                printf("%s => Write GPU_STENCIL_TEST = %s.\n", getName(), stencilTest?"TRUE":"FALSE");
            )

            break;

	case GPU_ZSTENCILBUFFER_DEFINED:

	    zStencilBufferDefined = data.booleanVal;
           
            samples = multisampling ? msaaSamples : 1;
	    if (zStencilBufferDefined)
            pixelMapper[0].setupDisplay(hRes, vRes, STAMP_WIDTH, STAMP_WIDTH, genW, genH, scanW, scanH, overW, overH,
                displayW, displayH, samples, bytesPixel[0]);
            
	    break;

        case GPU_STENCIL_FUNCTION:

            //  Write Stencil function register.
            stencilFunction = data.compare;

            GPU_DEBUG_BOX(
                printf("%s => Write GPU_STENCIL_FUNCTION = ", getName());

                switch(stencilFunction)
                {
                    case GPU_NEVER:
                        printf("NEVER.\n");
                        break;

                    case GPU_ALWAYS:
                        printf("ALWAYS.\n");
                        break;

                    case GPU_LESS:
                        printf("LESS.\n");
                        break;

                    case GPU_LEQUAL:
                        printf("LEQUAL.\n");
                        break;

                    case GPU_EQUAL:
                        printf("EQUAL.\n");
                        break;

                    case GPU_GEQUAL:
                        printf("GEQUAL.\n");
                        break;

                    case GPU_GREATER:
                        printf("GREATER.\n");
                        break;

                    case GPU_NOTEQUAL:
                        printf("NOTEQUAL.\n");

                    default:
                        panic("ZStencilTest", "processRegisterWrite", "Undefined compare function mode");
                        break;
                }
            )

            break;

        case GPU_STENCIL_REFERENCE:

            //  Write stencil reference value register.
            stencilReference = (u8bit) (data.uintVal & 0xff);

            GPU_DEBUG_BOX(
                printf("%s => Write GPU_STENCIL_REFERENCE = %x.\n", getName(), stencilReference);
            )

            break;

        case GPU_STENCIL_COMPARE_MASK:

            //  Write stencil compare mask.
            stencilTestMask = (u8bit) (data.uintVal & 0xff);

            GPU_DEBUG_BOX(
                printf("%s => Write GPU_STENCIL_COMPARE_MASK = %x.\n", getName(), stencilTestMask);
            )

            break;

        case GPU_STENCIL_UPDATE_MASK:

            //  Write stencil update mask.
            stencilUpdateMask = (u8bit) (data.uintVal & 0xff);

            GPU_DEBUG_BOX(
                printf("%s => Write GPU_STENCIL_UPDATE_MASK = %x.\n", getName(), stencilUpdateMask);
            )

            break;

        case GPU_STENCIL_FAIL_UPDATE:

            //  Write stencil fail update function.
            stencilFail = data.stencilUpdate;

            GPU_DEBUG_BOX(
                printf("%s => Write GPU_STENCIL_FAIL_UPDATE = ", getName());

                switch(stencilFail)
                {
                    case STENCIL_KEEP:
                        printf("KEEP.\n");
                        break;

                    case STENCIL_ZERO:
                        printf("ZERO.\n");
                        break;

                    case STENCIL_REPLACE:
                        printf("REPLACE.\n");
                        break;

                    case STENCIL_INCR:
                        printf("INCREMENT.\n");
                        break;

                    case STENCIL_DECR:
                        printf("DECREMENT.\n");
                        break;

                    case STENCIL_INVERT:
                        printf("INVERT.\n");
                        break;

                    case STENCIL_INCR_WRAP:
                        printf("INCREMENT AND WRAP.\n");
                        break;

                    case STENCIL_DECR_WRAP:
                        printf("DECREMENT AND WRAP.\n");
                        break;

                    default:
                        panic("ZStencilTest", "processRegisterWrite", "Undefined stencil update function");
                        break;
                }
            )

            break;

	case GPU_DEPTH_RANGE_NEAR:
	    near = data.f32Val;

	    break;

        case GPU_DEPTH_FAIL_UPDATE:

            //  Write depth fail update function.
            depthFail = data.stencilUpdate;

            GPU_DEBUG_BOX(
                printf("%s => Write GPU_DEPTH_FAIL_UPDATE = ", getName());

                switch(depthFail)
                {
                    case STENCIL_KEEP:
                        printf("KEEP.\n");
                        break;

                    case STENCIL_ZERO:
                        printf("ZERO.\n");
                        break;

                    case STENCIL_REPLACE:
                        printf("REPLACE.\n");
                        break;

                    case STENCIL_INCR:
                        printf("INCREMENT.\n");
                        break;

                    case STENCIL_DECR:
                        printf("DECREMENT.\n");
                        break;

                    case STENCIL_INVERT:
                        printf("INVERT.\n");
                        break;

                    case STENCIL_INCR_WRAP:
                        printf("INCREMENT AND WRAP.\n");
                        break;

                    case STENCIL_DECR_WRAP:
                        printf("DECREMENT AND WRAP.\n");
                        break;

                    default:
                        panic("ZStencilTest", "processRegisterWrite", "Undefined stencil update function");
                        break;
                }
            )

            break;

        case GPU_DEPTH_PASS_UPDATE:

            //  Write depth pass stencil update function.
            depthPass = data.stencilUpdate;

            GPU_DEBUG_BOX(
                printf("%s => Write GPU_DEPTH_PASS_UPDATE = ", getName());

                switch(depthPass)
                {
                    case STENCIL_KEEP:
                        printf("KEEP.\n");
                        break;

                    case STENCIL_ZERO:
                        printf("ZERO.\n");
                        break;

                    case STENCIL_REPLACE:
                        printf("REPLACE.\n");
                        break;

                    case STENCIL_INCR:
                        printf("INCREMENT.\n");
                        break;

                    case STENCIL_DECR:
                        printf("DECREMENT.\n");
                        break;

                    case STENCIL_INVERT:
                        printf("INVERT.\n");
                        break;

                    case STENCIL_INCR_WRAP:
                        printf("INCREMENT AND WRAP.\n");
                        break;

                    case STENCIL_DECR_WRAP:
                        printf("DECREMENT AND WRAP.\n");
                        break;

                    default:
                        panic("ZStencilTest", "processRegisterWrite", "Undefined stencil update function");
                        break;
                }
            )

            break;

        case GPU_DEPTH_TEST:

            //  Write depth test enable register.
            zTest = data.booleanVal;

            //  Update bypass ROP flag.
            bypassROP[0] = !(zTest || stencilTest);

            GPU_DEBUG_BOX(
                printf("%s => Write GPU_DEPTH_TEST = %s.\n", getName(), zTest?"TRUE":"FALSE");
            )

            break;

        case GPU_DEPTH_FUNCTION:

            //  Write depth compare function register.
            depthFunction = data.compare;

            GPU_DEBUG_BOX(
                printf("%s => Write GPU_DEPTH_FUNCTION = ", getName());

                switch(depthFunction)
                {
                    case GPU_NEVER:
                        printf("NEVER.\n");
                        break;

                    case GPU_ALWAYS:
                        printf("ALWAYS.\n");
                        break;

                    case GPU_LESS:
                        printf("LESS.\n");
                        break;

                    case GPU_LEQUAL:
                        printf("LEQUAL.\n");
                        break;

                    case GPU_EQUAL:
                        printf("EQUAL.\n");
                        break;

                    case GPU_GEQUAL:
                        printf("GEQUAL.\n");
                        break;

                    case GPU_GREATER:
                        printf("GREATER.\n");
                        break;

                    case GPU_NOTEQUAL:
                        printf("NOTEQUAL.\n");
                        break;

                    default:
                        panic("ZStencilTest", "processRegisterWrite", "Undefined compare function mode");
                        break;
                }
            )

            break;

        case GPU_DEPTH_MASK:

            //  Write depth update mask register.
            depthMask = data.booleanVal;

	    zCache->depthMask = depthMask;

            GPU_DEBUG_BOX(
                printf("%s => Write GPU_DEPTH_MASK = %s.\n", getName(), depthMask?"TRUE":"FALSE");
            )

            break;

        case GPU_ZSTENCIL_COMPRESSION:
        
            //  Write z/stencil compression enable/disable register.
            compression = data.booleanVal;
            
            //  Set color compression flag in the Z Stencil Cache.
            zCache->setCompression(compression);

            GPU_DEBUG_BOX(
                printf("%s => Write GPU_ZSTENCIL_COMPRESSION = %s\n", getName(), compression ? "TRUE" : "FALSE");
            )
            
            break;

	case GPU_COLOR_BLEND:
       
            //zCache->setRtBlend(subreg, data.booleanVal);	

            GPU_DEBUG_BOX(
                printf("%s => Write GPU_COLOR_BLEND[%d] = %s.\n", getName(), subreg, data.booleanVal?"ENABLED":"DISABLED");
            )

	    break;

        case GPU_COLOR_MASK_R:
        
            //  Write red component write mask register.
            writeR[subreg] = data.booleanVal;

            GPU_DEBUG_BOX(
                printf("%s => Write GPU_COLOR_MASK_R[%d] = %s.\n", getName(), subreg, writeR[subreg]?"ENABLED":"DISABLED");
            )

            break;

        case GPU_COLOR_MASK_G:
        
            //  Write green component write mask register.
            writeG[subreg] = data.booleanVal;

            GPU_DEBUG_BOX(
                printf("%s => Write GPU_COLOR_MASK_G[%d] = %s.\n", getName(), subreg, writeG[subreg]?"ENABLED":"DISABLED");
            )

            break;

        case GPU_COLOR_MASK_B:

            //  Write blue component write mask register.
            writeB[subreg] = data.booleanVal;

            GPU_DEBUG_BOX(
                printf("%s => Write GPU_COLOR_MASK_B[%d] = %s.\n", getName(), subreg, writeB[subreg]?"ENABLED":"DISABLED");
            )

            break;

        case GPU_COLOR_MASK_A:

            //  Write alpha component write mask register.
            writeA[subreg] = data.booleanVal;

            GPU_DEBUG_BOX(
                printf("%s => Write GPU_COLOR_MASK_A[%d] = %s.\n", getName(), subreg, writeA[subreg]?"ENABLED":"DISABLED");
            )

            break;

	case GPU_BLEND_EQUATION:
	    
	    equation[subreg] = data.blendEquation;

	    break;

	case GPU_BLEND_SRC_RGB:
	    
	    srcRGB[subreg] = data.blendFunction;
	    srcAlpha[subreg] = data.blendFunction;
	    if (data.blendFunction == BLEND_SRC_ALPHA)
		srcAlpha[subreg] = BLEND_ONE;

	    break;

	case GPU_BLEND_DST_RGB:
	    
	    dstRGB[subreg] = data.blendFunction;
	    dstAlpha[subreg] = data.blendFunction;
	    if (data.blendFunction == BLEND_DST_ALPHA)
		dstAlpha[subreg] = BLEND_ONE;

	    break;

        default:
            panic("ZStencilTest", "processRegisterWrite", "Unsupported register.");
            break;
    }
}

//  List the debug commands supported by the Command Processor
void ZStencilTestV2::getCommandList(std::string &commandList)
{
    commandList.append("tracefragment - Traces the execution of the defined fragment.\n");
}

//  Execute a debug command
void ZStencilTestV2::execCommand(stringstream &commandStream)
{
    string command;

    commandStream >> ws;
    commandStream >> command;

    if (!command.compare("tracefragment"))
    {
        commandStream >> ws;
        
        if (commandStream.eof())
        {
            cout << "Usage : tracefragment <on | off> <x> <y>" << endl;
        }
        else
        {
            string enableParam;
            bool enableFTrace;
            
            commandStream >> enableParam;
            
            bool error = false;
            if (!enableParam.compare("on"))
                enableFTrace = true;
            else if (!enableParam.compare("off"))
                enableFTrace = false;
            else
            {
                error = true;
                cout << getName() << ">> Usage : tracefragment <on | off> <x> <y>" << endl;
            }
            
            commandStream >> ws;
            
            if (commandStream.eof())
            {
                cout << getName() << " >> Usage : tracefragment <on | off> <x> <y>" << endl;
            }
            else
            {
                commandStream >> watchFragmentX;
                commandStream >> ws;
                
                if (commandStream.eof())
                {
                    cout << getName() << " >> Usage : tracefragment <on | off> <x> <y>" << endl;
                }
                else
                {
                    commandStream >> watchFragmentY;
                    
                    traceFragment = enableFTrace;
                    
                    if (enableFTrace)
                        cout << getName() << " >> Enabling fragment trace for coordinate (" << watchFragmentX << ", " << watchFragmentY << ")." << endl;
                    else
                        cout << getName() << " >> Disabling fragment trace." << endl;
                }
            }
        }
    }    
    else
    {
        cout << "Unsupported box command >> " << command;

        while (!commandStream.eof())
        {
            commandStream >> command;
            cout << " " << command;
        }

        cout << endl;
    }
}

void ZStencilTestV2::saveBlockStateMemory()
{
    zCache->saveBlockStateMemory();
}

void ZStencilTestV2::loadBlockStateMemory()
{
    zCache->loadBlockStateMemory();
}

void ZStencilTestV2::setValidationMode(bool enable)
{
    validationMode = enable;
}

FragmentQuadMemoryUpdateMap &ZStencilTestV2::getZStencilUpdateMap()
{
    return zstencilMemoryUpdateMap;
}

void ZStencilTestV2::sync(u64bit cycle, MemState memState)
{
    RasterizerSyncCommand *rastSyncComm;
    MemoryTransaction *memTrans;
    u32bit i;
    u32bit size;
    u32bit offset;
    bool syncCommProcessed;
    u32bit unitStride;
    u32bit block;
    u32bit k;

    if (memoryCycles > 0) {
        memoryCycles--;
    }

    for (i = 0; i < numGPUs; i++) {
	if (nextSyncGPUID == gpuId || numSyncCommQueueFreeEntries[nextSyncGPUID] == syncCommQueueSzPerGPU)
            nextSyncGPUID = GPU_MOD(nextSyncGPUID + 1, numGPUs);
	else
	    break;
    }

    if (i == numGPUs) return;

    rastSyncComm = syncCommQueue[nextSyncGPUID][nextSyncRead[nextSyncGPUID]];
    syncCommProcessed = false;

    if (rastSyncComm->last) {
        // update the number of synced GPUs
        numSyncedGPUs++;
	syncCommProcessed = true;
    } else {
        /*  Update the color buffer state table.  Each stamp unit modifies its assigned scan tiles.  */
        unitStride = scanH * scanW;
	block = rastSyncComm->block;
        k = (block / (unitStride * numStampUnits)) * unitStride + GPU_MOD(block, unitStride);
                
        if (rastSyncComm->size == 0) {
    	    // update block state
            ropCache->updateBlockState(k, rastSyncComm->blockState);
	    syncCommProcessed = true;
        } else if (ropCache->getMemoryCycles() == 0 && memoryCycles == 0 && (memState & MS_WRITE_ACCEPT) != 0) {
    	    // update memory
    	    size = GPU_MIN(MAX_TRANSACTION_SIZE, rastSyncComm->size - rastSyncComm->written);
    	    offset = rastSyncComm->written;
                
    	    memTrans = new MemoryTransaction(
    	        MT_WRITE_DATA,
    	        rastSyncComm->address + offset,
                size,
    	        (rastSyncComm->data) + offset,
                ZSTENCILTEST,
    	        stampId,
    	        nextWriteTicket++);

    	    memTrans->setSync(true);

    	    memRequest->write(cycle, memTrans);

    	    memoryCycles = memTrans->getBusCycles();

    	    rastSyncComm->written += size;

    	    if (rastSyncComm->written == rastSyncComm->size) {
                ropCache->updateBlockState(k, rastSyncComm->blockState);
	        syncCommProcessed = true;
            }
        }
    }

    if (syncCommProcessed) {
        nextSyncRead[nextSyncGPUID] = GPU_MOD(nextSyncRead[nextSyncGPUID] + 1, syncCommQueueSzPerGPU);
	numSyncCommQueueFreeEntries[nextSyncGPUID]++;
        interGPUSyncBackPressure[nextSyncGPUID]->write(cycle, rastSyncComm);
	numProcessed[nextSyncGPUID]++;
	nextSyncGPUID = GPU_MOD(nextSyncGPUID + 1, numGPUs);
    }

    if (numSyncedGPUs == numGPUs - 1 && memoryCycles == 0) {
	numSyncedGPUs = 0;
	nextSyncGPUID = 0;
	for (u32bit i = 0; i < numGPUs; i++) {
	    nextSyncRead[i] = 0;
	    nextSyncWrite[i] = 0;
	    numSyncCommQueueFreeEntries[i] = syncCommQueueSzPerGPU;
	    numReceived[i] = 0;
	    numProcessed[i] = 0;
	} 
        state = RAST_END;
    }
}

void ZStencilTestV2::blit(u64bit cycle)
{
    panic("ZStencilTestV2", "blit", "should not be called");
}

void ZStencilTestV2::dumpZFightingInfo()
{
    if (!profileForSortLast || stampId != 0)
	return;

    FILE *zFightingInfoFile = fopen("zFightingInfo.obj", "a+");
    std::map<u32bit, std::set<u32bit> >::iterator zFightedDrawsIt;
    std::set<u32bit>::iterator drawIt;
    for (zFightedDrawsIt = zFightedDraws.begin(); zFightedDrawsIt != zFightedDraws.end(); zFightedDrawsIt++) {
	fprintf(zFightingInfoFile, "%d ", zFightedDrawsIt->first);
	for (drawIt = zFightedDrawsIt->second.begin(); drawIt != zFightedDrawsIt->second.end(); drawIt++)
            fprintf(zFightingInfoFile, "%d ", *drawIt);
	fprintf(zFightingInfoFile, "\n");
    }
    fflush(zFightingInfoFile);
    fclose(zFightingInfoFile);
}

void ZStencilTestV2::clearForComp(u64bit cycle)
{
    if (!zCache->clearForComp(clearDepthForComp)) {
	indexOwner owner;
	owner.gpuId = gpuId;
	owner.frameId = frameCounter;
	owner.batchId = batchCounter + 1;
	GPU_ASSERT(
	    if (GPUDriver::getGPUDriver()->getKDTreeIndexesInSortLast()->count(owner) == 0)
	        panic(getName(), "processCommand", "cannot find kdInfo");
	)
	kdInfo = GPUDriver::getGPUDriver()->getKDTreeIndexesInSortLast()->at(owner);

	zCache->anyRtBlend = kdInfo.anyRtBlend;
	
        std::cout << "Debug: " << getName() << " cleared ROPBuffers @ " << cycle
                  << " frame " << frameCounter << " batch " << (batchCounter + 1)
                  << " backgroundDraw " << (zCache->backgroundDraw ? "T" : "F")
		  << " anyRtBlend " << (zCache->anyRtBlend ? "T" : "F")
                  << std::endl;

	zCache->compMode = true;
	zCache->backgroundDraw = false;

	state = RAST_END;
    }
}

void ZStencilTestV2::comp(u64bit cycle) {
    u32bit i;

    if (compSchedEnabled)
	GPUDriver::getGPUDriver()->getCompSched()->setSendToGPU(gpuId);

    terminateCompStamp(cycle);

    writeCompStamp(cycle);

    endOperation(cycle);

    startOperation(cycle);

    readCompStamp(cycle);

    fetchCompStamp(cycle);

    receiveStamps(cycle);

    if (allStampsReadForSync[gpuId][stampId]) {
        overSyncX = 0;
	overSyncY = 0;
	scanSyncX = 0;
	scanSyncY = 0;
	genSyncX = 0;
	genSyncY = 0;
	stampSyncX = 0;
	stampSyncY = 0;

	bool allStampsRead = true;
	bool allStampsSent = true;
	for (i = 0; i < numStampUnits; i++) {
	    allStampsRead = allStampsRead && allStampsReadForSync[gpuId][i];
	    allStampsSent = allStampsSent && allStampsSentForSync[gpuId][i];
	}
	if (allStampsRead && allStampsSent) {
	    std::cout << getName() << " sent all stamps to GPU " << nextSyncReadingGPU[gpuId]
		      << " @cycle " << cycle << std::endl;
	    for (i = 0; i < numStampUnits; i++) {
	        allStampsReadForSync[gpuId][i] = false;
	        allStampsSentForSync[gpuId][i] = false;
	    }

            if (compSchedEnabled) {	    
	        GPUDriver::getGPUDriver()->getCompSched()->resetSending(gpuId);
	    } else {
	        nextSyncReadingGPU[gpuId]++;
	        if (nextSyncReadingGPU[gpuId] == gpuId && !zCache->anyRtBlend)
	            nextSyncReadingGPU[gpuId]++;
	    }
	}
    }

    if (allStampsReadForSync[gpuId][stampId])
	return;

    if (compSchedEnabled) {
        if (GPUDriver::getGPUDriver()->getCompSched()->isSending(gpuId)) {
	    nextSyncReadingGPU[gpuId] = GPUDriver::getGPUDriver()->getCompSched()->getSendToGPU(gpuId);
            readStampForOtherGPUs(cycle, nextSyncReadingGPU[gpuId]);
	}
    } else if (nextSyncReadingGPU[gpuId] < numGPUs && (!zCache->anyRtBlend || notLastSyncReceive <= (numGPUs - gpuId)))
        readStampForOtherGPUs(cycle, nextSyncReadingGPU[gpuId]);
}

void ZStencilTestV2::generateCompFragments(u64bit cycle, ROPQueue *stamp)
{
    u32bit *depth = (u32bit*)stamp->data;

    for (u32bit rt = 0, activeRT = 0; activeRT < numActiveBuffers; rt++, activeRT++) {
	for (; !activeBuffer[rt] && rt < MAX_RENDER_TARGETS; rt++);

	GPU_ASSERT(
	    if (rt == MAX_RENDER_TARGETS)
	        panic("ZStencilTestV2", "generateCompFragments", "Expected an active render target.");
	)

        for (u32bit i = 0; i < STAMP_FRAGMENTS; i++) {
            if (!multisampling) {
                stamp->stamp[i]->getFragment()->setZ(depth[i] & 0x00ffffff);
                if ((depth[i] == 0xdeadcafe || depth[i] == clearDepthForComp) && bypassCW)
                    stamp->stamp[i]->setCull(true);

		stamp->stamp[i]->incSize(4);

                //if (stamp->stamp[0]->getFragment()->getX() == 172 && stamp->stamp[0]->getFragment()->getY() == 146) {
                //    FILE *debugfile = fopen("comp_zst_debug.txt", "a+");
                //    fprintf(debugfile, "%s cycle %lld frame %d batch %d generate (%d, %d) for comp depth %08x culled %s\n",
            	//	    getName(), cycle, frameCounter, batchCounter, stamp->stamp[i]->getFragment()->getX(),
            	//	    stamp->stamp[i]->getFragment()->getY(), depth[i], stamp->stamp[i]->isCulled() ? "T" : "F");
                //    fflush(debugfile);
                //    fclose(debugfile);
                //}
            } else {
                panic(getName(), "generateCompFragments", "current implementation do not support multisampling");
            }
        }

    }
}

void ZStencilTestV2::postCompWriteProcess(u64bit cycle, ROPQueue *stamp)
{
    u32bit i;
    QuadFloat *attrib;
    Fragment *fr;

    switch(stamp->stamp[0]->getType()) {
        case FRAG_COMP_IN:
            for (i = 0; i < STAMP_FRAGMENTS; i++) {
		if (bypassCW) {
		    attrib = stamp->stamp[i]->getAttributes();
		    fr = stamp->stamp[i]->getFragment();

		    if (fr) delete fr;
		    if (attrib) delete [] attrib;
		    delete stamp->stamp[i];
		} else {
                    stamp->stamp[i]->setCull(stamp->culled[i]);
		    outFragmentSignal->write(cycle, stamp->stamp[i]);
		}
            }

	    break;

	case FRAG_COMP_OUT:
            for (i = 0; i < STAMP_FRAGMENTS; i++) {
		syncOutFragmentSignal->write(cycle, stamp->stamp[i]);
            }

	    break;

	default:
	    panic(getName(), "postCompWriteProcess", "invalid fragment type");
    }

    delete [] stamp->stamp;
}
