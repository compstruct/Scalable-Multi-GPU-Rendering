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
 * $RCSfile: FragmentFIFO.cpp,v $
 * $Revision: 1.28 $
 * $Author: vmoya $
 * $Date: 2006-12-12 17:41:15 $
 *
 * Fragment FIFO implementation file (unified shaders version).
 *
 */


/**
 *
 *  @file FragmentFIFO.cpp
 *
 *  This file implements the Fragment FIFO class (unified shaders version).
 *
 *  The Fragment FIFO class implements the Fragment FIFO simulation box.
 *
 *  This class implements a Fragment FIFO simulation box.  The Fragment FIFO stores
 *  and directs stamps of fragments from the rasterizer to the Interpolator and Shader
 *  units.  It also stores shaded fragments and sends them Z Stencil Test.
 *
 */

#include "FragmentFIFO.h"
#include "RasterizerCommand.h"
#include "ROPStatusInfo.h"
#include "RasterizerStateInfo.h"
#include "FFIFOStateInfo.h"
#include "ShaderStateInfo.h"
#include "ConsumerStateInfo.h"
#include "ROPStatusInfo.h"
#include <sstream>

using namespace gpu3d;
using namespace std;

u32bit **FragmentFIFO::freeSyncIn = NULL;
u32bit **FragmentFIFO::syncedStampUnits = NULL;
std::vector<std::vector<bool> > FragmentFIFO::allStampsReceivedForSync = std::vector<std::vector<bool> >();

/*  Fragment FIFO constructor.  */
FragmentFIFO::FragmentFIFO(u32bit gpuId, u32bit numGPUs_, u32bit multiGPUExecMode_, bool compSchedEnabled_,
    bool idealComp_, u32bit interGPUBusWidth_, u32bit interGPUBusLat_,
    char *gpuPrefix, u32bit hzStampsC, u32bit stampCycle, bool unified, bool shSetup, u32bit trCycle,
    u32bit trLat, u32bit nVSh, u32bit nFSh, u32bit shInCycle, u32bit shOutCycle, u32bit thGroup,
    u32bit maxShOutLat, u32bit interp, u32bit shInQSz, u32bit shOutQSz, u32bit shInBSz, bool shTileDistro,
    u32bit vInQSz, u32bit vOutQSz, u32bit trInQSz, u32bit trOutQSz, u32bit rastQSz, u32bit testQSz, u32bit intQSz,
    u32bit shaderQSz, u32bit syncQSz, u32bit interGPUSyncQSz, f32bit dummyFragsGenPossibility_,
    char **vshPrefix, char **fshPrefix, u32bit nStampUnits, char **suPrefixes, char *name, Box *parent) :

    numGPUs(numGPUs_), multiGPUExecMode(multiGPUExecMode_), compSchedEnabled(compSchedEnabled_),
    idealComp(idealComp_), interGPUBusWidth(interGPUBusWidth_), interGPUBusLat(interGPUBusLat_),
    hzStampsCycle(hzStampsC), stampsCycle(stampCycle), unifiedModel(unified), shadedSetup(shSetup),
    trianglesCycle(trCycle), triangleLat(trLat), numVShaders(nVSh), numFShaders(nFSh), shInputsCycle(shInCycle),
    shOutputsCycle(shOutCycle), threadGroup(thGroup), fshOutLatency(maxShOutLat),
    interpolators(interp), shInputBatchSize(shInBSz),
    tiledShDistro(shTileDistro), vShadedQueueSz(vOutQSz), triangleInQueueSz(trInQSz),
    triangleOutQueueSz(trOutQSz), rastQueueSz(rastQSz), testQueueSz(testQSz), intQueueSz(intQSz), shQueueSz(shaderQSz),
    syncQueueSz(syncQSz), interGPUSyncQueueSz(interGPUSyncQSz), numStampUnits(nStampUnits),
    compMode(false), dummyFragsGenPossibility(dummyFragsGenPossibility_),
    //shInputQSize(shInQSz), shOutputQSize(shOutQSz), vInputQueueSz(vInQSz),
    Box(gpuId, name, parent)

{
    u32bit i;
    u32bit j;
    DynamicObject *defaultState[1];

    shInputQSize = shInQSz * nStampUnits;
    shOutputQSize = shOutQSz * nStampUnits;
    vInputQueueSz = thGroup + 2 * nVSh;

    /*  Check parameters.  */
    GPU_ASSERT(
        if (hzStampsCycle == 0)
            panic("FragmentFIFO", "FragmentFIFO", "At least one stamp must be recieved from HZ per cycle.");
        if (stampsCycle == 0)
            panic("FragmentFIFO", "FragmentFIFO", "At least one stamp must be processed per cycle.");
        if (shInputsCycle == 0)
            panic("FragmentFIFO", "FragmentFIFO", "At least one shader input per cycle required.");
        if (shOutputsCycle == 0)
            panic("FragmentFIFO", "FragmentFIFO", "At least one shader output per cycle required.");
        if (threadGroup < STAMP_FRAGMENTS)
            panic("FragmentFIFO", "FragmentFIFO", "A thread group must be at least the size of a fragment quad.");
        if ((threadGroup > STAMP_FRAGMENTS) && (GPU_MOD(threadGroup, STAMP_FRAGMENTS) != 0))
            panic("FragmentFIFO", "FragmentFIFO", "A thread group must be multiple of a fragment quad.");
        if (fshOutLatency == 0)
            panic("FragmentFIFO", "FragmentFIFO", "Shader output signal latency must be at least 1.");
        if (interpolators == 0)
            panic("FragmentFIFO", "FragmentFIFO", "At least one attribute interpolator unit required.");
        if (shInputQSize < (numStampUnits * threadGroup * 2))
            panic("FragmentFIFO", "FragmentFIFO", "Required minimum size for shader input queue is 2 * SUs * thGroup.");
        if (shOutputQSize < (numStampUnits * threadGroup * 2))
            panic("FragmentFIFO", "FragmentFIFO", "Required minimum size for shader output queue is 2 * SUs * thGroup.");
        if (unifiedModel && (vInputQueueSz < (threadGroup + 2 * numVShaders)))
            panic("FragmentFIFO", "FragmentFIFO", "Vertex Input Queue requires as many entries as a shader group plus the number of vertex inputs per cycle by the latency.");
        if (unifiedModel && (vShadedQueueSz < threadGroup))
            panic("FragmentFIFO", "FragmentFIFO", "Vertex Shaded Queue requires as many entries as a shader group.");
        if (shadedSetup && !unifiedModel)
            panic("FragmentFIFO", "FragmentFIFO", "Triangle setup on shaders only supported for unified shader model.");
        if (shadedSetup && (trianglesCycle == 0))
            panic("FragmentFIFO", "FragmentFIFO", "At least one triangle must be received per cycle from Triangle Setup.");
        if (shadedSetup && (triangleLat == 0))
            panic("FragmentFIFO", "FragmentFIFO", "Triangle signals latency from Triangle Setup must be at least one cycle.");
        if (shadedSetup && (triangleInQueueSz < (threadGroup + (1 + triangleLat) * trianglesCycle)))
            panic("FragmentFIFO", "FragmentFIFO", "Triangle input queue requires at least the size of a shader thread group plus triangle input bw and latency entries.");
        if (shadedSetup && (triangleInQueueSz < ((1 + triangleLat) * trianglesCycle)))
            panic("FragmentFIFO", "FragmentFIFO", "Triangle input queue requires at least triangle signal latency by the number of triangles that can received per cycle entries.");
        if (shadedSetup && (triangleOutQueueSz < threadGroup))
            panic("FragmentFIFO", "FragmentFIFO", "Triangle output queue requires at least the size of a shader input group entries.");
        if (shadedSetup && (triangleOutQueueSz < ((1 + triangleLat) * trianglesCycle)))
            panic("FragmentFIFO", "FragmentFIFO", "Triangle output queue requires at least triangle signal latency by the number of triangles that can received per cycle entries.");
	if (rastQueueSz == 0)
            panic("FragmentFIFO", "FragmentFIFO", "Post HZ stamp queue requires at least 1 entry.");
        if (testQueueSz == 0)
            panic("FragmentFIFO", "FragmentFIFO", "Post Z test stamp queue requires at least 1 entry.");
        if (intQueueSz < (threadGroup/4))
            panic("FragmentFIFO", "FragmentFIFO", "Post interpolation stamp queue requires at a thread group equivalent of fragments.");
        if (shQueueSz == 0)
            panic("FragmentFIFO", "FragmentFIFO", "Post shading stamp queue requires at least 1 entry.");
        if (syncQueueSz == 0)
            panic("FragmentFIFO", "FragmentFIFO", "Synchronization stamp queue requires at least 1 entry.");
        if (interGPUSyncQueueSz == 0)
            panic("FragmentFIFO", "FragmentFIFO", "Inter-GPU synchronization stamp queue requires at least 1 entry.");
        if (numStampUnits == 0)
            panic("FragmentFIFO", "FragmentFIFO", "FFIFO must be attached to at least one stamp unit.");
        if (GPU_MOD(shInputBatchSize, threadGroup) != 0)
            panic("FragmentFIFO", "FragmentFIFO", "Shader input work batch size must be a multiple of the size of a shader thread group.");
    )

GPU_TEX_TRACE(
    char filename[128];
    sprintf(filename, "fragTrace.txt.gz");
    fragTrace.open(filename, fstream::out);
    fragTrace << "Tracing started" << endl;
)

    /*  Create statistics.  */
    inputs = &getSM(gpuId).getNumericStatistic("InputFragments", u32bit(0), "FFIFOU", "FFU");
    outputs = &getSM(gpuId).getNumericStatistic("OutputFragments", u32bit(0), "FFIFOU", "FFU");
    interpolated = &getSM(gpuId).getNumericStatistic("InterpolatedFragments", u32bit(0), "FFIFOU", "FFU");
    shadedFrag = &getSM(gpuId).getNumericStatistic("ShadedFragments", u32bit(0), "FFIFOU", "FFU");
    inVerts = &getSM(gpuId).getNumericStatistic("InputVertices", u32bit(0), "FFIFOU", "FFU");
    outVerts = &getSM(gpuId).getNumericStatistic("OutputVertices", u32bit(0), "FFIFOU", "FFU");
    shVerts = &getSM(gpuId).getNumericStatistic("ShadedVertices", u32bit(0), "FFIFOU", "FFU");
    inTriangles = &getSM(gpuId).getNumericStatistic("InputTriangles", u32bit(0), "FFIFOU", "FFU");
    outTriangles = &getSM(gpuId).getNumericStatistic("OutputTriangles", u32bit(0), "FFIFOU", "FFU");
    shTriangles = &getSM(gpuId).getNumericStatistic("ShadedTriangles", u32bit(0), "FFIFOU", "FFU");
    rastGLevel = &getSM(gpuId).getNumericStatistic("RastStampQueuesOccupation", u32bit(0), "FFIFOU", "FFU");
    testGLevel = &getSM(gpuId).getNumericStatistic("TestStampQueuesOccupation", u32bit(0), "FFIFOU", "FFU");
    intGLevel = &getSM(gpuId).getNumericStatistic("IntStampQueuesOccupation", u32bit(0), "FFIFOU", "FFU");
    shadedGLevel = &getSM(gpuId).getNumericStatistic("ShadedStampQueuesOccupation", u32bit(0), "FFIFOU", "FFU");
    vertInLevel = &getSM(gpuId).getNumericStatistic("VertexInputQueueOccupation", u32bit(0), "FFIFOU", "FFU");
    vertOutLevel = &getSM(gpuId).getNumericStatistic("VertexOutputQueueOccupation", u32bit(0), "FFIFOU", "FFU");
    trInLevel = &getSM(gpuId).getNumericStatistic("TriangleInputQueueOccupation", u32bit(0), "FFIFOU", "FFU");
    trOutLevel = &getSM(gpuId).getNumericStatistic("TriangleOutputQueueOccupation", u32bit(0), "FFIFOU", "FFU");
    interGPUSyncTrafficLoad = &getSM(gpuId).getNumericStatistic("InterGPUSyncTrafficLoad", u32bit(0), "FFIFOU", "FFU");
    interGPUSyncCannotSend = &getSM(gpuId).getNumericStatistic("InterGPUSyncCannotSend", u32bit(0), "FFIFOU", "FFU");
    interGPUSyncTransCycleStall = &getSM(gpuId).getNumericStatistic("InterGPUSyncTransCycleStall", u32bit(0), "FFIFOU", "FFU");
    waitIntStalls = &getSM(gpuId).getNumericStatistic("WaitInterpolatorStall", u32bit(0), "FFIFOU", "FFU");
    numStampsToInt = &getSM(gpuId).getNumericStatistic("AverageNumStampsToInterpolator", u32bit(0), "FFIFOU", "FFU");
    numZSTUnitsSendRastStampsTo = &getSM(gpuId).getNumericStatistic("NumberOfZSTUnitsSendRastStampsTo", u32bit(0), "FFIFOU", "FFU");
    numRastStampsToZSTUnit = &getSM(gpuId).getNumericStatistic("NumberOfRastStampsToZSTUnit", u32bit(0), "FFIFOU", "FFU");
    numZSTUnitsSendShadedStampsTo = &getSM(gpuId).getNumericStatistic("NumberOfZSTUnitsSendShadedStampsTo", u32bit(0), "FFIFOU", "FFU");
    numShadedStampsToZSTUnit = &getSM(gpuId).getNumericStatistic("NumberOfShadedStampsToZSTUnit", u32bit(0), "FFIFOU", "FFU");
    numZSTUnitsReceiveStampsFrom = &getSM(gpuId).getNumericStatistic("NumberOfZSTUnitsReceiveStampsFrom", u32bit(0), "FFIFOU", "FFU");
    numStampsFromZSTUnit = &getSM(gpuId).getNumericStatistic("NumberOfStampsFromZSTUnit", u32bit(0), "FFIFOU", "FFU");
    numRastStamps = &getSM(gpuId).getNumericStatistic("NumberOfReceivedRastStamps", u32bit(0), "FFIFOU", "FFU");
    numFragsPassZTest = &getSM(gpuId).getNumericStatistic("NumberOfFragmentsPassZTest", u32bit(0), "FFIFOU", "FFU");
    numFragsPassZTestInCompMode = &getSM(gpuId).getNumericStatistic("NumberOfFragmentsPassZTestInCompMode", u32bit(0), "FFIFOU", "FFU");
    numFragsNotPassZTest = &getSM(gpuId).getNumericStatistic("NumberOfFragmentsNotPassZTest", u32bit(0), "FFIFOU", "FFU");
    numFragsNotPassZTestInCompMode = &getSM(gpuId).getNumericStatistic("NumberOfFragmentsNotPassZTestInCompMode", u32bit(0), "FFIFOU", "FFU");
    numFragsPassZTestEarlyZ = &getSM(gpuId).getNumericStatistic("NumberOfFragmentsPassZTestEarlyZ", u32bit(0), "FFIFOU", "FFU");
    numFragsPassZTestEarlyZInCompMode = &getSM(gpuId).getNumericStatistic("NumberOfFragmentsPassZTestEarlyZInCompMode", u32bit(0), "FFIFOU", "FFU");
    numFragsNotPassZTestEarlyZ = &getSM(gpuId).getNumericStatistic("NumberOfFragmentsNotPassZTestEarlyZ", u32bit(0), "FFIFOU", "FFU");
    numFragsNotPassZTestEarlyZInCompMode = &getSM(gpuId).getNumericStatistic("NumberOfFragmentsNotPassZTestEarlyZInCompMode", u32bit(0), "FFIFOU", "FFU");
    numDummyFrags = &getSM(gpuId).getNumericStatistic("NumberOfDummyFragments", u32bit(0), "FFIFOU", "FFU");

    globalInputs = &getSM().getNumericStatistic("InputFragments", u32bit(0), "FFIFOU", "FFU");
    globalOutputs = &getSM().getNumericStatistic("OutputFragments", u32bit(0), "FFIFOU", "FFU");
    globalInterpolated = &getSM().getNumericStatistic("InterpolatedFragments", u32bit(0), "FFIFOU", "FFU");
    globalShadedFrag = &getSM().getNumericStatistic("ShadedFragments", u32bit(0), "FFIFOU", "FFU");
    globalInVerts = &getSM().getNumericStatistic("InputVertices", u32bit(0), "FFIFOU", "FFU");
    globalOutVerts = &getSM().getNumericStatistic("OutputVertices", u32bit(0), "FFIFOU", "FFU");
    globalShVerts = &getSM().getNumericStatistic("ShadedVertices", u32bit(0), "FFIFOU", "FFU");
    globalInTriangles = &getSM().getNumericStatistic("InputTriangles", u32bit(0), "FFIFOU", "FFU");
    globalOutTriangles = &getSM().getNumericStatistic("OutputTriangles", u32bit(0), "FFIFOU", "FFU");
    globalShTriangles = &getSM().getNumericStatistic("ShadedTriangles", u32bit(0), "FFIFOU", "FFU");
    globalRastGLevel = &getSM().getNumericStatistic("RastStampQueuesOccupation", u32bit(0), "FFIFOU", "FFU");
    globalTestGLevel = &getSM().getNumericStatistic("TestStampQueuesOccupation", u32bit(0), "FFIFOU", "FFU");
    globalIntGLevel = &getSM().getNumericStatistic("IntStampQueuesOccupation", u32bit(0), "FFIFOU", "FFU");
    globalShadedGLevel = &getSM().getNumericStatistic("ShadedStampQueuesOccupation", u32bit(0), "FFIFOU", "FFU");
    globalVertInLevel = &getSM().getNumericStatistic("VertexInputQueueOccupation", u32bit(0), "FFIFOU", "FFU");
    globalVertOutLevel = &getSM().getNumericStatistic("VertexOutputQueueOccupation", u32bit(0), "FFIFOU", "FFU");
    globalTrInLevel = &getSM().getNumericStatistic("TriangleInputQueueOccupation", u32bit(0), "FFIFOU", "FFU");
    globalTrOutLevel = &getSM().getNumericStatistic("TriangleOutputQueueOccupation", u32bit(0), "FFIFOU", "FFU");
    globalInterGPUSyncTrafficLoad = &getSM().getNumericStatistic("InterGPUSyncTrafficLoad", u32bit(0), "FFIFOU", "FFU");
    globalInterGPUSyncCannotSend = &getSM().getNumericStatistic("InterGPUSyncCannotSend", u32bit(0), "FFIFOU", "FFU");
    globalInterGPUSyncTransCycleStall = &getSM().getNumericStatistic("InterGPUSyncTransCycleStall", u32bit(0), "FFIFOU", "FFU");
    globalWaitIntStalls = &getSM().getNumericStatistic("WaitInterpolatorStall", u32bit(0), "FFIFOU", "FFU");
    globalNumStampsToInt = &getSM().getNumericStatistic("AverageNumStampsToInterpolator", u32bit(0), "FFIFOU", "FFU");
    globalNumZSTUnitsSendRastStampsTo = &getSM().getNumericStatistic("NumberOfZSTUnitsSendRastStampsTo", u32bit(0), "FFIFOU", "FFU");
    globalNumRastStampsToZSTUnit = &getSM().getNumericStatistic("NumberOfRastStampsToZSTUnit", u32bit(0), "FFIFOU", "FFU");
    globalNumZSTUnitsSendShadedStampsTo = &getSM().getNumericStatistic("NumberOfZSTUnitsSendShadedStampsTo", u32bit(0), "FFIFOU", "FFU");
    globalNumShadedStampsToZSTUnit = &getSM().getNumericStatistic("NumberOfShadedStampsToZSTUnit", u32bit(0), "FFIFOU", "FFU");
    globalNumZSTUnitsReceiveStampsFrom = &getSM().getNumericStatistic("NumberOfZSTUnitsReceiveStampsFrom", u32bit(0), "FFIFOU", "FFU");
    globalNumStampsFromZSTUnit = &getSM().getNumericStatistic("NumberOfStampsFromZSTUnit", u32bit(0), "FFIFOU", "FFU");
    globalNumRastStamps = &getSM().getNumericStatistic("NumberOfReceivedRastStamps", u32bit(0), "FFIFOU", "FFU");
    globalNumFragsPassZTest = &getSM().getNumericStatistic("NumberOfFragmentsPassZTest", u32bit(0), "FFIFOU", "FFU");
    globalNumFragsPassZTestInCompMode = &getSM().getNumericStatistic("NumberOfFragmentsPassZTestInCompMode", u32bit(0), "FFIFOU", "FFU");
    globalNumFragsNotPassZTest = &getSM().getNumericStatistic("NumberOfFragmentsNotPassZTest", u32bit(0), "FFIFOU", "FFU");
    globalNumFragsNotPassZTestInCompMode = &getSM().getNumericStatistic("NumberOfFragmentsNotPassZTestInCompMode", u32bit(0), "FFIFOU", "FFU");
    globalNumFragsPassZTestEarlyZ = &getSM().getNumericStatistic("NumberOfFragmentsPassZTestEarlyZ", u32bit(0), "FFIFOU", "FFU");
    globalNumFragsPassZTestEarlyZInCompMode = &getSM().getNumericStatistic("NumberOfFragmentsPassZTestEarlyZInCompMode", u32bit(0), "FFIFOU", "FFU");
    globalNumFragsNotPassZTestEarlyZ = &getSM().getNumericStatistic("NumberOfFragmentsNotPassZTestEarlyZ", u32bit(0), "FFIFOU", "FFU");
    globalNumFragsNotPassZTestEarlyZInCompMode = &getSM().getNumericStatistic("NumberOfFragmentsNotPassZTestEarlyZInCompMode", u32bit(0), "FFIFOU", "FFU");
    globalNumDummyFrags = &getSM().getNumericStatistic("NumberOfDummyFragments", u32bit(0), "FFIFOU", "FFU");

    /*  Create signals with Hierarchical Z.  */

    /*  Stamp input signal from Hierarchical/Early Z box.  */
    hzInput = newInputSignal("HZOutput", hzStampsCycle * STAMP_FRAGMENTS, 1, gpuPrefix);

    /*  Create state signal to the Hierarchical/Early Z box.  */
    ffStateHZ = newOutputSignal("FFIFOStateHZ", 1, 1, gpuPrefix);

    /*  Create default state signal value.  */
    defaultState[0] = new FFIFOStateInfo(FFIFO_READY);

    /*  Set default signal value.  */
    ffStateHZ->setData(defaultState);

    /*  Calculate the number of stamps per thread group.  */
    stampsPerGroup = threadGroup / STAMP_FRAGMENTS;

    /*  Create signals with Interpolator box.  */

    /*  Create input stamp signal to Interpolator box.  */
    interpolatorInput = newOutputSignal("InterpolatorInput", stampsCycle * stampsPerGroup* STAMP_FRAGMENTS, 1, gpuPrefix);

    /*  Create output stamp signal from the Interpolator box.  */
    interpolatorOutput = newInputSignal("InterpolatorOutput", stampsCycle * stampsPerGroup * STAMP_FRAGMENTS, 1, gpuPrefix);


    /*  Create signals with Z Stencil Test.  */

    /*  Check number Z Stencil unit attached and prefixes.  */
    GPU_ASSERT(
        if (numStampUnits < 1)
            panic("FragmentFIFO", "FragmentFIFO", "At least one Z Stencil unit must be attached.");
        if (suPrefixes == NULL)
            panic("FragmentFIFO", "FragmentFIFO", "Z Stencil prefix array required.");
        for(i = 0; i < numStampUnits; i++)
            if (suPrefixes[i] == NULL)
                panic("FragmentFIFO", "FragmentFIFO", "Z Stencil prefix missing.");
    )

    /*  Allocate arrays of signals with the Z Stencil Test and Color Write units.  */
    zStencilInput = new Signal*[numStampUnits];
    zStencilOutput = new Signal*[numStampUnits];
    zStencilSyncOutput = new Signal*[numStampUnits];
    zStencilState = new Signal*[numStampUnits];
    fFIFOZSTState = new Signal*[numStampUnits];
    fFIFOZSTSyncState = new Signal*[numStampUnits];
    
    cWriteInput = new Signal*[numStampUnits];
    cWriteSyncInput = new Signal*[numStampUnits];
    cWriteSyncOutput = new Signal*[numStampUnits];
    cWriteState = new Signal*[numStampUnits];
    cWriteSyncState = new Signal*[numStampUnits];
    fFIFOCWSyncState = new Signal*[numStampUnits];

    /*  Check allocation.  */
    GPU_ASSERT(
        if (zStencilInput == NULL)
            panic("FragmentFIFO", "FragmentFIFO", "Error allocating z stencil input signal array.");

        if (zStencilOutput == NULL)
            panic("FragmentFIFO", "FragmentFIFO", "Error allocating z stencil output signal array.");

        if (zStencilSyncOutput == NULL)
            panic("FragmentFIFO", "FragmentFIFO", "Error allocating z stencil sync output signal array.");

        if (zStencilState == NULL)
            panic("FragmentFIFO", "FragmentFIFO", "Error allocating z stencil state signal array.");

        if (fFIFOZSTState == NULL)
            panic("FragmentFIFO", "FragmentFIFO", "Error allocating to z stencil signal array.");

        if (fFIFOZSTSyncState == NULL)
            panic("FragmentFIFO", "FragmentFIFO", "Error allocating to z stencil sync signal array.");

        if (cWriteInput == NULL)
            panic("FragmentFIFO", "FragmentFIFO", "Error allocating color write input signal array.");

        if (cWriteSyncInput == NULL)
            panic("FragmentFIFO", "FragmentFIFO", "Error allocating color write sync input signal array.");

        if (cWriteSyncOutput == NULL)
            panic("FragmentFIFO", "FragmentFIFO", "Error allocating color write sync output signal array.");

        if (cWriteState == NULL)
            panic("FragmentFIFO", "FragmentFIFO", "Error allocating color write state signal array.");
        
        if (cWriteSyncState == NULL)
            panic("FragmentFIFO", "FragmentFIFO", "Error allocating color write sync state signal array.");
        
	if (fFIFOCWSyncState == NULL)
            panic("FragmentFIFO", "FragmentFIFO", "Error allocating to color write sync signal array.");
    )

    /*  Calculate the number of stamps sent to each unit.  */
    stampsPerUnit = GPU_MAX(u32bit(1), stampsCycle / numStampUnits);


    /*  Create the signals with the attached Z Stencil and Color Write units.  */
    for(i = 0; i < numStampUnits; i++)
    {
        /*  Create input stamp signal to Z Stencil Test.  */
        zStencilInput[i] = newOutputSignal("ZStencilInput", stampsPerUnit * STAMP_FRAGMENTS, 1, suPrefixes[i]);
        
        /*  Create output stamp signal to Z Stencil Test.  */
        zStencilOutput[i] = newInputSignal("ZStencilOutput", stampsPerUnit * STAMP_FRAGMENTS, 1, suPrefixes[i]);
        
	zStencilSyncOutput[i] = newInputSignal("ZStencilSyncOutput", stampsPerUnit * STAMP_FRAGMENTS, 1, suPrefixes[i]);

        /*  Create state signal from Z Stencil Test.  */
        zStencilState[i] = newInputSignal("ZStencilState", 1, 1, suPrefixes[i]);
        
        /*  Create state signal to Z Stencil Test.  */
        fFIFOZSTState[i] = newOutputSignal("FFIFOZStencilState", 1, 1, suPrefixes[i]);
        
        /*  Create default state signal value.  */
        defaultState[0] = new ROPStatusInfo(ROP_READY);

        /*  Set default signal value.  */
        fFIFOZSTState[i]->setData(defaultState);

	fFIFOZSTSyncState[i] = newOutputSignal("FFIFOZStencilSyncState", 1, 1, suPrefixes[i]);
        defaultState[0] = new ROPStatusInfo(ROP_READY);
        fFIFOZSTSyncState[i]->setData(defaultState);

        /*  Create input stamp signal to Color Write.  */
        cWriteInput[i] = newOutputSignal("ColorWriteInput", stampsPerUnit * STAMP_FRAGMENTS, 1, suPrefixes[i]);
        
	cWriteSyncInput[i] = newOutputSignal("ColorWriteSyncInput", stampsPerUnit * STAMP_FRAGMENTS, 1, suPrefixes[i]);

        cWriteSyncOutput[i] = newInputSignal("ColorWriteSyncOutput", stampsPerUnit * STAMP_FRAGMENTS, 1, suPrefixes[i]);

        /*  Create state signal from Color Write.  */
        cWriteState[i] = newInputSignal("ColorWriteFFIFOState", 1, 1, suPrefixes[i]);
        
        /*  Create state signal from Color Write sync.  */
        cWriteSyncState[i] = newInputSignal("ColorWriteFFIFOSyncState", 1, 1, suPrefixes[i]);
        
	fFIFOCWSyncState[i] = newOutputSignal("FFIFOColorWriteSyncState", 1, 1, suPrefixes[i]);
        defaultState[0] = new ROPStatusInfo(ROP_READY);
        fFIFOCWSyncState[i]->setData(defaultState);

    }

    /*  Check shader model.  */
    if (unifiedModel)
    {
        /*  Create signals for the virtual vertex shaders.  */

        /*  Check number of virtual vertex shaders and shader prefixes.  */
        GPU_ASSERT(
            if (numVShaders == 0)
                panic("FragmentFIFO", "FragmentFIFO", "No virtual vertex shader defined.");
            if (vshPrefix == NULL)
                panic("FragmentFIFO", "FragmentFIFO", "No prefixes for the Vertex Shader signals.");

            for(i = 0; i < numVShaders; i++)
                if (vshPrefix[i] == NULL)
                    panic("FragmentFIFO", "FragmentFIFO", "Undefined Vertex Shader prefix.");
        )


        /*  Allocate array of signals for the virtual vertex shaders.  */
        vertexInput = new Signal*[numVShaders];
        vertexOutput = new Signal*[numVShaders];
        vertexState = new Signal*[numVShaders];
        vertexConsumer = new Signal*[numVShaders];

        /*  Check allocation.  */
        GPU_ASSERT(
            if (vertexInput == NULL)
                panic("FragmentFIFO", "FragmentFIFO", "Error allocating array of vertex input signals from Streamer Loader.");
            if (vertexOutput == NULL)
                panic("FragmentFIFO", "FragmentFIFO", "Error allocating array of vertex output signals to Streamer Commit.");
            if (vertexState == NULL)
                panic("FragmentFIFO", "FragmentFIFO", "Error allocating array of state signals to Streamer Loader.");
            if (vertexConsumer == NULL)
                panic("FragmentFIFO", "FragmentFIFO", "Error allocating array of state signals from Streamer Commit.");
        )

        /*  Create signals for with each shader.  */
        for(i = 0; i < numVShaders; i++)
        {
            /*  Create vertex input signal from Streamer Loader.  */
            vertexInput[i] = newInputSignal("ShaderCommand", 1, 1, vshPrefix[i]);

            /*  Create vertex output signal to Streamer Commit.  */
            vertexOutput[i] = newOutputSignal("ShaderOutput", 1, fshOutLatency, vshPrefix[i]);

            /*  Create state signal to Streamer Loader.  */
            vertexState[i] = newOutputSignal("ShaderState", 1, 1, vshPrefix[i]);

            /*  Create default state signal value.  */
            defaultState[0] = new ShaderStateInfo(SH_READY);

            /*  Set default signal value.  */
            vertexState[i]->setData(defaultState);

            /*  Create state signal from Streamer Commit.  */
            vertexConsumer[i] = newInputSignal("ConsumerState", 1, 1, vshPrefix[i]);
        }

        /*  Check if triangle setup is performed in the shader.  */
        if (shadedSetup)
        {
            /*  Create triangle shader input signal from Triangle Setup.  */
            triangleInput = newInputSignal("TriangleShaderInput", trianglesCycle, triangleLat, gpuPrefix);

            /*  Create triangle shader output signal to Triangle Setup.  */
            triangleOutput = newOutputSignal("TriangleShaderOutput", trianglesCycle, triangleLat, gpuPrefix);

            /*  Create triangle shader state signal to Triangle Setup.  */
            triangleState = newOutputSignal("TriangleShaderState", 1, 1, gpuPrefix);

            /*  Create default state signal value.  */
            defaultState[0] = new ShaderStateInfo(SH_READY);

            /*  Set default signal value.  */
            triangleState->setData(defaultState);
        }
    }

    /*  Create array of signals with the fragment shaders.  */

    /*  Check number of fragment shaders attached and shader prefixes.  */
    GPU_ASSERT(
        if (numFShaders == 0)
            panic("FragmentFIFO", "FragmentFIFO", "No Fragment Shader attached.");
        if (fshPrefix == NULL)
            panic("FragmentFIFO", "FragmentFIFO", "No prefixes for the Fragment Shader signals.");

        for(i = 0; i < numFShaders; i++)
            if (fshPrefix[i] == NULL)
                panic("FragmentFIFO", "FragmentFIFO", "Undefined Fragment Shader prefix.");
    )


    /*  Allocate array of signals to the shaders.  */
    shaderInput = new Signal*[numFShaders];
    shaderOutput = new Signal*[numFShaders];
    shaderState = new Signal*[numFShaders];
    ffStateShader = new Signal*[numFShaders];

    /*  Check allocation.  */
    GPU_ASSERT(
        if (shaderInput == NULL)
            panic("FragmentFIFO", "FragmentFIFO", "Error allocating array of stamp input signals to the Shader unit");
        if (shaderOutput == NULL)
            panic("FragmentFIFO", "FragmentFIFO", "Error allocating array of stamp output signals from the Shader unit");
        if (shaderState == NULL)
            panic("FragmentFIFO", "FragmentFIFO", "Error allocating array of state signals from the Shader unit");
        if (ffStateShader == NULL)
            panic("FragmentFIFO", "FragmentFIFO", "Error allocating array of Fragment FIFO state signals to the Shader unit");
    )

    /*  Create signals each shader.  */
    for(i = 0; i < numFShaders; i++)
    {
        /*  Create stamp input signal to the Shader.  */
        shaderInput[i] = newOutputSignal("ShaderCommand", shInputsCycle, 1, fshPrefix[i]);

        /*  Create stamp output signal from the Shader.  */
        shaderOutput[i] = newInputSignal("ShaderOutput", shOutputsCycle, fshOutLatency, fshPrefix[i]);

        /*  Create state signal from the Shader.  */
        shaderState[i] = newInputSignal("ShaderState", 1, 1, fshPrefix[i]);

       /*  Create state signal to the Shader.  */
        ffStateShader[i] = newOutputSignal("ConsumerState", 1, 1, fshPrefix[i]);

        /*  Create default state signal value.  */
        defaultState[0] = new ConsumerStateInfo(CONS_READY);

        /*  Set default signal value.  */
        ffStateShader[i]->setData(defaultState);
    }

    /*  Create signals with the main rasterizer box.  */

    /*  Create command signal from the main rasterizer box.  */
    fFIFOCommand = newInputSignal("FFIFOCommand", 1, 1, gpuPrefix);

    /*  Create state signal to the main rasterizer box.  */
    fFIFOState = newOutputSignal("FFIFOState", 1, 1, gpuPrefix);

    /*  Create default signal value.  */
    defaultState[0] = new RasterizerStateInfo(RAST_RESET);

    /*  Set default signal value.  */
    fFIFOState->setData(defaultState);


    /*  Allocate space for the vertex consumer states.  */
    consumerState = new ConsumerState[numVShaders];

    /*  Check allocation.  */
    GPU_ASSERT(
        if (consumerState == NULL)
            panic("FragmentFIFO", "FragmentFIFO", "Error allocating array for the Streamer Commit states.");
    )

    /*  Allocate space for the shader states.  */
    shState = new ShaderState[numFShaders];

    /*  Check allocation.  */
    GPU_ASSERT(
        if (shState == NULL)
            panic("FragmentFIFO", "FragmentFIFO", "Error allocating array for the fragment shader states.");
    )

    /*  Allocate space for the Z Stencil states.  */
    zstState = new ROPState[numStampUnits];

    /*  Check allocation.  */
    GPU_ASSERT(
        if (zstState == NULL)
            panic("FragmentFIFO", "FragmentFIFO", "Error allocating array for the Z Stencil Test states.");
    )

    /*  Allocate space for the Color Write states.  */
    cwState = new ROPState[numStampUnits];
    cwSyncState = new ROPState[numStampUnits];

    /*  Check allocation.  */
    GPU_ASSERT(
        if (cwState == NULL)
            panic("FragmentFIFO", "FragmentFIFO", "Error allocating array for the ColorWrite states.");
        if (cwSyncState == NULL)
            panic("FragmentFIFO", "FragmentFIFO", "Error allocating array for the ColorWrite sync states.");
    )

    /*  Check shader model.  */
    if (unifiedModel)
    {
        /*  Allocate vertex queues.  */
        inputVertexQueue = new ShaderInput*[vInputQueueSz];
        shadedVertexQueue = new ShaderInput*[vShadedQueueSz];

        /*  Check allocation.  */
        GPU_ASSERT(
            if (inputVertexQueue == NULL)
                panic("FragmentFIFO", "FragmentFIFO", "Error allocating vertex input queue.");
            if (shadedVertexQueue == NULL)
                panic("FragmentFIFO", "FragmentFIFO", "Error allocating shaded vertex output queue.");
        )

        /*  Check if triangle setup on the shaders is enabled.  */
        if (shadedSetup)
        {
            /*  Allocate the input triangle queue.  */
            triangleInQueue = new ShaderInput*[triangleInQueueSz];

            /*  Allocate the triangle output queue.  */
            triangleOutQueue = new ShaderInput*[triangleOutQueueSz];

            /*  Check allocation.  */
            GPU_ASSERT(
                if (triangleInQueue == NULL)
                    panic("FragmentFIFO", "FragmentFIFO", "Error allocating triangle input queue.");
                if (triangleOutQueue == NULL)
                    panic("FragmentFIFO", "FragmentFIFO", "Error allocating triangle output queue.");
            )
        }
    }

    /*  Allocate fragment queues.  */

    /*  Allocate queue for stamps generated in Fragment Generation.  */
    rastQueue = new FragmentInput***[numStampUnits];
    nextRast = new u32bit[numStampUnits];
    nextFreeRast = new u32bit[numStampUnits];
    rastStamps = new u32bit[numStampUnits];
    freeRast = new u32bit[numStampUnits];

    /*  Check allocation.  */
    GPU_ASSERT(
        if (rastQueue == NULL)
            panic("FragmentFIFO", "FragmentFIFO", "Error allocating rasterizer stamp queue.");
        if (nextRast == NULL)
            panic("FragmentFIFO", "FragmentFIFO", "Error allocating per unit next rasterizer stamp pointer array.");
        if (nextFreeRast == NULL)
            panic("FragmentFIFO", "FragmentFIFO", "Error allocating per unit next free rasterizer queue entry pointer array.");
        if (rastStamps == NULL)
            panic("FragmentFIFO", "FragmentFIFO", "Error allocating per unit rasterizer stamps counter array.");
        if (freeRast == NULL)
            panic("FragmentFIFO", "FragmentFIFO", "Error allocating per unit free rasterizer queue entry counter array.");
    )

    /*  Allocate queue for stamps after early z test.  */
    testQueue = new FragmentInput***[numStampUnits];
    nextTest = new u32bit[numStampUnits];
    nextFreeTest = new u32bit[numStampUnits];
    testStamps = new u32bit[numStampUnits];
    freeTest = new u32bit[numStampUnits];

    /*  Check allocation.  */
    GPU_ASSERT(
        if (testQueue == NULL)
            panic("FragmentFIFO", "FragmentFIFO", "Error allocating after early Z test stamp queue.");
        if (nextTest == NULL)
            panic("FragmentFIFO", "FragmentFIFO", "Error allocating per unit next tested stamp pointer array.");
        if (nextFreeTest == NULL)
            panic("FragmentFIFO", "FragmentFIFO", "Error allocating per unit next free z tested queue entry pointer array.");
        if (testStamps == NULL)
            panic("FragmentFIFO", "FragmentFIFO", "Error allocating per unit z tested stamps counter array.");
        if (freeTest == NULL)
            panic("FragmentFIFO", "FragmentFIFO", "Error allocating per unit free z tested queue entry counter array.");
    )

    /*  Allocate queue for stamps interpolated in the Interpolator.  */
    intQueue = new FragmentInput***[numStampUnits];
    nextInt = new u32bit[numStampUnits];
    nextFreeInt = new u32bit[numStampUnits];
    intStamps =  new u32bit[numStampUnits];
    freeInt = new u32bit[numStampUnits];
    lastStampInterpolated = new bool[numStampUnits];

    /*  Check allocation.  */
    GPU_ASSERT(
        if (intQueue == NULL)
            panic("FragmentFIFO", "FragmentFIFO", "Error allocating interpolator stamp queue.");
        if (nextInt == NULL)
            panic("FragmentFIFO", "FragmentFIFO", "Error allocating per unit next interpolated stamp pointer array.");
        if (nextFreeInt == NULL)
            panic("FragmentFIFO", "FragmentFIFO", "Error allocating per unit next free interpolated queue entry pointer array.");
        if (intStamps == NULL)
            panic("FragmentFIFO", "FragmentFIFO", "Error allocating per unit z interpolated stamps counter array.");
        if (freeInt == NULL)
            panic("FragmentFIFO", "FragmentFIFO", "Error allocating per unit free interpolated queue entry counter array.");
        if (lastStampInterpolated == NULL)
            panic("FragmentFIFO", "FragmentFIFO", "Error allocating per unit last stamp interpolated flag.");
    )


    /*  Allocate shaded stamp structures for the stamp units.  */
    shQueue = new FragmentInput***[numStampUnits];
    shaded = new bool*[numStampUnits];
    nextShaded = new u32bit[numStampUnits];
    nextFreeSh = new u32bit[numStampUnits];
    shadedStamps = new u32bit[numStampUnits];
    freeShaded = new u32bit[numStampUnits];
    lastShaded = new bool[numStampUnits];

    /*  Check allocation.  */
    GPU_ASSERT(
        if (shQueue == NULL)
            panic("FragmentFIFO", "FragmentFIFO", "Error allocating stamp units shaded stamp queue.");
        if (shaded == NULL)
            panic("FragmentFIFO", "FragmentFIFO", "Error allocating stamp units shaded flag array.");
        if (nextShaded == NULL)
            panic("FragmentFIFO", "FragmentFIFO", "Error allocating stamp units next shaded stamp pointer array.");
        if (nextFreeSh == NULL)
            panic("FragmentFIFO", "FragmentFIFO", "Error allocating stamp units next free shaded queue pointer array.");
        if (shadedStamps == NULL)
            panic("FragmentFIFO", "FragmentFIFO", "Error allocating stamp units shaded stamps counter array.");
        if (freeShaded == NULL)
            panic("FragmentFIFO", "FragmentFIFO", "Error allocating stamp units free shaded queue counter array.");
        if (lastShaded == NULL)
            panic("FragmentFIFO", "FragmentFIFO", "Error allocating stamp unit shaded queues flag array marking last stamp enqueued.");
    )

    syncQueueIn = new FragmentInput***[numStampUnits];
    nextSyncIn = new u32bit[numStampUnits];
    nextFreeSyncIn = new u32bit[numStampUnits];
    syncInStamps = new u32bit[numStampUnits];
    if (freeSyncIn == NULL)
        freeSyncIn = new u32bit*[numGPUs];
    freeSyncIn[gpuId] = new u32bit[numStampUnits];

    idealSyncQueueIn.resize(numStampUnits, std::queue<FragmentInput*>());

    if (syncedStampUnits == NULL)
	syncedStampUnits = new u32bit*[numGPUs];
    syncedStampUnits[gpuId] = new u32bit[numGPUs];

    GPU_ASSERT(
   	if (syncQueueIn == NULL)
            panic("FragmentFIFO", "FragmentFIFO", "Error allocating inter-GPU synchronization input queue.");
        if (nextSyncIn == NULL)
            panic("FragmentFIFO", "FragmentFIFO", "Error allocating per unit next sync input stamp pointer array.");
        if (nextFreeSyncIn == NULL)
            panic("FragmentFIFO", "FragmentFIFO", "Error allocating per unit next free sync input queue entry pointer array.");
        if (syncInStamps == NULL)
            panic("FragmentFIFO", "FragmentFIFO", "Error allocating per unit sync input stamps counter array.");
        if (freeSyncIn == NULL)
            panic("FragmentFIFO", "FragmentFIFO", "Error allocating per unit free sync input queue entry counter array.");
        if (freeSyncIn[gpuId] == NULL)
            panic("FragmentFIFO", "FragmentFIFO", "Error allocating per unit free sync input queue entry counter array for this GPU.");
	if (syncedStampUnits == NULL || syncedStampUnits[gpuId] == NULL)
	    panic("FragmentFIFO", "FragmentFIFO", "Error allocating the number of finished stamp units.");
    )

    syncQueueOutZST = new FragmentInput***[numStampUnits];
    nextSyncOutZST = new u32bit[numStampUnits];
    nextFreeSyncOutZST = new u32bit[numStampUnits];
    syncOutStampsZST =  new u32bit[numStampUnits];
    freeSyncOutZST = new u32bit[numStampUnits];
    
    syncQueueOutCW = new FragmentInput***[numStampUnits];
    nextSyncOutCW = new u32bit[numStampUnits];
    nextFreeSyncOutCW = new u32bit[numStampUnits];
    syncOutStampsCW =  new u32bit[numStampUnits];
    freeSyncOutCW = new u32bit[numStampUnits];

    GPU_ASSERT(
   	if (syncQueueOutZST == NULL)
            panic("FragmentFIFO", "FragmentFIFO", "Error allocating inter-GPU synchronization output queue for ZST.");
        if (nextSyncOutZST == NULL)
            panic("FragmentFIFO", "FragmentFIFO", "Error allocating per unit next sync output stamp pointer array for ZST.");
        if (nextFreeSyncOutZST == NULL)
            panic("FragmentFIFO", "FragmentFIFO", "Error allocating per unit next free sync output queue entry pointer array for ZST.");
        if (syncOutStampsZST == NULL)
            panic("FragmentFIFO", "FragmentFIFO", "Error allocating per unit sync output stamps counter array for ZST.");
        if (freeSyncOutZST == NULL)
            panic("FragmentFIFO", "FragmentFIFO", "Error allocating per unit free sync output queue entry counter array for ZST.");
   	
	    if (syncQueueOutCW == NULL)
            panic("FragmentFIFO", "FragmentFIFO", "Error allocating inter-GPU synchronization output queue for CW.");
        if (nextSyncOutCW == NULL)
            panic("FragmentFIFO", "FragmentFIFO", "Error allocating per unit next sync output stamp pointer array for CW.");
        if (nextFreeSyncOutCW == NULL)
            panic("FragmentFIFO", "FragmentFIFO", "Error allocating per unit next free sync output queue entry pointer array for CW.");
        if (syncOutStampsCW == NULL)
            panic("FragmentFIFO", "FragmentFIFO", "Error allocating per unit sync output stamps counter array for CW.");
        if (freeSyncOutCW == NULL)
            panic("FragmentFIFO", "FragmentFIFO", "Error allocating per unit free sync output queue entry counter array for CW.");
    )

    /*  Allocate per stamp unit rasterizer stamp queue structures.  */
    for(i = 0; i < numStampUnits; i++)
    {
        /*  Allocate per stamp unit queue for stamps rasterized.  */
        rastQueue[i] = new FragmentInput**[rastQueueSz];

        /*  Allocate per stamp unit queue for stamps z tested.  */
        testQueue[i] = new FragmentInput**[testQueueSz];

        /*  Allocate per stamp unit queue for stamps interpolated.  */
        intQueue[i] = new FragmentInput**[intQueueSz];

        /*  Allocate per stamp unit queue for stamps shaded in the Fragment Shader units.  */
        shQueue[i] = new FragmentInput**[shQueueSz];

	syncQueueIn[i] = new FragmentInput**[interGPUSyncQueueSz];

	syncQueueOutZST[i] = new FragmentInput**[syncQueueSz];
	
	syncQueueOutCW[i] = new FragmentInput**[syncQueueSz];

        /*  Allocate shaded flag for shaded queue (if have been completely shaded and received).  */
        shaded[i] = new bool[shQueueSz];

        /*  Check allocation.  */
        GPU_ASSERT(
            if (rastQueue[i] == NULL)
                panic("FragmentFIFO", "FragmentFIFO", "Error allocating rasterizer stamp queue for stamp unit.");
            if (testQueue[i] == NULL)
                panic("FragmentFIFO", "FragmentFIFO", "Error allocating z tested stamp queue for stamp unit.");
            if (intQueue[i] == NULL)
                panic("FragmentFIFO", "FragmentFIFO", "Error allocating interpolated stamp queue for stamp unit.");
            if (shQueue[i] == NULL)
                panic("FragmentFIFO", "FragmentFIFO", "Error allocating shader stamp queue for stamp unit.");
            if (syncQueueIn[i] == NULL)
                panic("FragmentFIFO", "FragmentFIFO", "Error allocating inter-GPU synchronization input queue for stamp unit.");
            if (syncQueueOutZST[i] == NULL)
                panic("FragmentFIFO", "FragmentFIFO", "Error allocating inter-GPU synchronization output queue for ZST stamp unit.");
            if (syncQueueOutCW[i] == NULL)
                panic("FragmentFIFO", "FragmentFIFO", "Error allocating inter-GPU synchronization output queue for CW stamp unit.");
            if (shaded[i] == NULL)
                panic("FragmentFIFO", "FragmentFIFO", "Error allocating shaded flag array for shaded queue for stamp unit.");
        )

        /*  Allocate rasterized queue stamps.  */
        for(j = 0; j < rastQueueSz; j++)
        {
            /*  Allocate a stamp.  */
            rastQueue[i][j] = new FragmentInput*[STAMP_FRAGMENTS];

            /*  Check allocation.  */
            GPU_ASSERT(
                if (rastQueue[i][j] == NULL)
                    panic("FragmentFIFO", "FragmentFIFO", "Error allocating stamp for the rasterizer queue.");
            )
        }

        /*  Allocate early tested stamps.  */
        for(j = 0; j < testQueueSz; j++)
        {
            /*  Allocate a stamp.  */
            testQueue[i][j] = new FragmentInput*[STAMP_FRAGMENTS];

            /*  Check allocation.  */
            GPU_ASSERT(
                if (testQueue[i][j] == NULL)
                    panic("FragmentFIFO", "FragmentFIFO", "Error allocating stamp for the early z tested stamp queue.");
            )
        }

        /*  Allocate interpolated stamps.  */
        for(j = 0; j < intQueueSz; j++)
        {
            /*  Allocate a stamp.  */
            intQueue[i][j] = new FragmentInput*[STAMP_FRAGMENTS];

            /*  Check allocation.  */
            GPU_ASSERT(
                if (intQueue[i][j] == NULL)
                    panic("FragmentFIFO", "FragmentFIFO", "Error allocating stamp for the interpolated queue.");
            )
        }
        /*  Allocate shaded queue stamps.  */
        for(j = 0; j < shQueueSz; j++)
        {
            /*  Allocate a stamp.  */
            shQueue[i][j] = new FragmentInput*[STAMP_FRAGMENTS];

            /*  Check allocation.  */
            GPU_ASSERT(
                if (shQueue[i][j] == NULL)
                    panic("FragmentFIFO", "FragmentFIFO", "Error allocating stamp for the shaded queue.");
            )
        }

        for (j = 0; j < interGPUSyncQueueSz; j++)
        {
            syncQueueIn[i][j] = new FragmentInput*[STAMP_FRAGMENTS];
            
            GPU_ASSERT(
                if (syncQueueIn[i][j] == NULL)
                    panic("FragmentFIFO", "FragmentFIFO", "Error allocating stamp for the inter-GPU synchronization input queue.");
            )
        }
	
	for (j = 0; j < syncQueueSz; j++)
	{
	    syncQueueOutZST[i][j] = new FragmentInput*[STAMP_FRAGMENTS];
	    
	    syncQueueOutCW[i][j] = new FragmentInput*[STAMP_FRAGMENTS];
            
	    GPU_ASSERT(
                if (syncQueueOutZST[i][j] == NULL)
                    panic("FragmentFIFO", "FragmentFIFO", "Error allocating stamp for the ZST inter-GPU synchronization output queue.");
                if (syncQueueOutCW[i][j] == NULL)
                    panic("FragmentFIFO", "FragmentFIFO", "Error allocating stamp for the CW inter-GPU synchronization output queue.");
            )
	}
    }

    syncFragIn = new Signal*[numGPUs];
    syncFragOut = new Signal*[numGPUs];
    char syncSignalPrefix[64];
    for (u32bit gpuIndex = 0; gpuIndex < numGPUs; gpuIndex++) {
        if (gpuIndex != gpuId) {
	    sprintf(syncSignalPrefix, "GPU%dToGPU%d", gpuIndex, gpuId);
	    syncFragIn[gpuIndex] = newInputSignal("FragmentSync", stampsPerUnit * numStampUnits * STAMP_FRAGMENTS, (idealComp ? 1 : interGPUBusLat), syncSignalPrefix);
	    sprintf(syncSignalPrefix, "GPU%dToGPU%d", gpuId, gpuIndex);
	    syncFragOut[gpuIndex] = newOutputSignal("FragmentSync", stampsPerUnit * numStampUnits * STAMP_FRAGMENTS, (idealComp ? 1 : interGPUBusLat), syncSignalPrefix);
	} else {
	    syncFragIn[gpuIndex] = NULL;
	    syncFragOut[gpuIndex] = NULL;
	}
    }
    interGPUSyncTransCycles = 0;

    /*  Allocate shader batch queues.  */
    shaderInputQ = new ShaderInput**[numFShaders];
    nextShaderInput = new u32bit[numFShaders];
    nextFreeShInput = new u32bit[numFShaders];
    numShaderInputs = new u32bit[numFShaders];
    numFreeShInputs = new u32bit[numFShaders];
    shaderOutputQ = new ShaderInput**[numFShaders];
    nextShaderOutput = new u32bit[numFShaders];
    nextFreeShOutput = new u32bit[numFShaders];
    numShaderOutputs = new u32bit[numFShaders];
    numFreeShOutputs = new u32bit[numFShaders];
    batchedShInputs = new u32bit[numFShaders];

    /*  Check allocation.  */
    GPU_ASSERT(
        if (shaderInputQ == NULL)
            panic("FragmentFIFO", "FragmentFIFO", "Error allocating shader input queue.");
        if (nextShaderInput == NULL)
            panic("FragmentFIFO", "FragmentFIFO", "Error allocating per shader next shader input pointers.");
        if (nextFreeShInput == NULL)
            panic("FragmentFIFO", "FragmentFIFO", "Error allocating per shader next free shader input queue entry pointers.");
        if (numShaderInputs == NULL)
            panic("FragmentFIFO", "FragmentFIFO", "Error allocating per shader shader inputs counters.");
        if (numFreeShInputs == NULL)
            panic("FragmentFIFO", "FragmentFIFO", "Error allocating per shader shader input queue free entries counters.");
        if (shaderOutputQ == NULL)
            panic("FragmentFIFO", "FragmentFIFO", "Error allocating shader output queue.");
        if (nextShaderOutput == NULL)
            panic("FragmentFIFO", "FragmentFIFO", "Error allocating per shader next shader output pointers.");
        if (nextFreeShOutput == NULL)
            panic("FragmentFIFO", "FragmentFIFO", "Error allocating per shader next free shader output queue entry pointers.");
        if (numShaderOutputs == NULL)
            panic("FragmentFIFO", "FragmentFIFO", "Error allocating per shader shader output counters.");
        if (numFreeShOutputs == NULL)
            panic("FragmentFIFO", "FragmentFIFO", "Error allocating per shader shader output queue free entries counters.");
        if (batchedShInputs == NULL)
            panic("FragmentFIFO", "FragmentFIFO", "Error allocating per shader batched shader inputs counters.");
    )

    /*  Allocate per shader queues.  */
    for(i = 0; i < numFShaders; i++)
    {
        shaderInputQ[i] = new ShaderInput*[shInputQSize];
        shaderOutputQ[i] = new ShaderInput*[shOutputQSize];

        /*  Check allocation.  */
        GPU_ASSERT(
            if (shaderInputQ[i] == NULL)
                panic("FragmentFIFO", "FragmentFIFO", "Error allocating per shader unit shader input queue.");
            if (shaderOutputQ[i] == NULL)
                panic("FragmentFIFO", "FragmentFIFO", "Error allocating per shader unit shader output queue.");
        )
    }
    
    //  Allocate shader stall detection state.
    lastCycleShInput = new u64bit[numFShaders];
    lastCycleShOutput = new u64bit[numFShaders];
    shaderElements = new u32bit[numFShaders];
    lastCycleZSTIn = new u64bit[numStampUnits];
    lastCycleCWIn = new u64bit[numStampUnits];
    
    //  Check allocation.
    GPU_ASSERT(
        if (lastCycleShInput == NULL)
            panic("FragmentFIFO", "FragmentFIFO", "Error allocating per shader last cycle shader input sent register.");
        if (lastCycleShOutput == NULL)
            panic("FragmentFIFO", "FragmentFIFO", "Error allocating per shader last cycle shader output received register.");
        if (shaderElements == NULL)
            panic("FragmentFIFO", "FragmentFIFO", "Error allocating per shader elements in the shader counter.");
        if (lastCycleZSTIn == NULL)
            panic("FragmentFIFO", "FragmentFIFO", "Error allocating per ROP unit last cycle an input was sent to ZST register.");
        if (lastCycleCWIn == NULL)
            panic("FragmentFIFO", "FragmentFIFO", "Error allocating per ROP unit last cycle an input was sent to CW register.");
    )

    /*  Create dummy last rasterizer command.  */
    lastRSCommand = new RasterizerCommand(RSCOM_RESET);

    batchCounter = 0;
    frameCounter = 0;

    if (gpuId == 0) {
        allStampsReceivedForSync.resize(numGPUs);
	for (i = 0; i < numGPUs; i++)
	    allStampsReceivedForSync[i].resize(numStampUnits, false);
    }

    /*  Set initial state to reset.  */
    state = RAST_RESET;
}

//  Fragment FIFO destructor
FragmentFIFO::~FragmentFIFO()
{
GPU_TEX_TRACE(
    fragTrace << "Tracing finished" << endl;
    fragTrace.close();
)
    
}

/*  Simulation function.  */
void FragmentFIFO::clock(u64bit cycle)
{
    RasterizerCommand *rastCommand;
    ROPStatusInfo *zstStateInfo;
    ROPStatusInfo *cwStateInfo;
    ROPStatusInfo *cwSyncStateInfo;
    ShaderStateInfo *shStateInfo;
    ConsumerStateInfo *consumerStateInfo;
    u32bit i;
    u32bit minFreeRast;
    char buffer[64];
  
    GPU_DEBUG_BOX(
        printf("FragmentFIFO => Clock %lld.\n", cycle);
    )

    /*  Check shader model.  */
    if (unifiedModel)
    {
        /*  Receive state from Streamer Commit.  */
        for(i = 0; i < numVShaders; i++)
        {
            /*  Read state from Streamer Commit.  */
            if (vertexConsumer[i]->read(cycle, (DynamicObject *&) consumerStateInfo))
            {
                /*  Get state.  */
                consumerState[i] = consumerStateInfo->getState();

                /*  Process last vertex sent to primitive assembly from Streamer Commit.  */
                if (consumerState[i] == CONS_LAST_VERTEX_COMMIT)
                {
//printf("FFIFO: Last vertex input sent signal received in cycle %d\n", cycle); 
                     /*  Set last vertex commit flag in Fragment FIFO Unit.  */
                     lastVertexCommit = TRUE;
                     
                     /*  Last vertex state implicitly means ready state.  */
                     consumerState[i] = CONS_READY;
                }
                else if (consumerState[i] == CONS_FIRST_VERTEX_IN)
                {
//printf("FFIFO: First vertex input sent signal received in cycle %d\n", cycle);
                     /*  Reset last vertex commit flag in Fragment FIFO Unit.  */
                     lastVertexCommit = FALSE;
 
                     /*  Last vertex state implicitly means ready state.  */
                     consumerState[i] = CONS_READY;
                }


                /*  Delete carrier object.  */
                delete consumerStateInfo;
            }
            else
            {
                sprintf(buffer, "State signal from Streamer Commit consumer state signal %d lost data.", i);
                panic("FragmentFIFO", "clock", buffer);
            }
        }
    }

    /*  Receive state from the Fragment Shaders.  */
    for(i = 0; i < numFShaders; i++)
    {
        /*  Read state from Fragment Shader.  */
        if (shaderState[i]->read(cycle, (DynamicObject *&) shStateInfo))
        {
            /*  Get state.  */
            shState[i] = shStateInfo->getState();

            /*  Delete carrier object.  */
            delete shStateInfo;
        }
        else
        {
            sprintf(buffer, "State signal from Fragment Shader %d lost data.", i);
            panic("FragmentFIFO", "clock", buffer);
        }
    }

    /*  Receive state from the Z Stencil Test units.  */
    for (i = 0; i < numStampUnits; i++)
    {
        if (zStencilState[i]->read(cycle, (DynamicObject *&) zstStateInfo))
        {
            /*  Get Z Stencil State.  */
            zstState[i] = zstStateInfo->getState();

            /*  Delete carrier object.  */
            delete zstStateInfo;
        }
        else
        {
            panic("FragmentFIFO", "clock", "Missing state signal from Z Stencil Test.");
        }
    }

    /*  Receive state from the Color Write units.  */
    for (i = 0; i < numStampUnits; i++)
    {
        if (cWriteState[i]->read(cycle, (DynamicObject *&) cwStateInfo))
        {
            /*  Get Color Write State.  */
            cwState[i] = cwStateInfo->getState();

            /*  Delete carrier object.  */
            delete cwStateInfo;
        }
        else
        {
            panic("FragmentFIFO", "clock", "Missing state signal from Color Write.");
        }
        
	if (cWriteSyncState[i]->read(cycle, (DynamicObject *&) cwSyncStateInfo))
        {
            /*  Get Color Write sync State.  */
            cwSyncState[i] = cwSyncStateInfo->getState();

            /*  Delete carrier object.  */
            delete cwSyncStateInfo;
        }
        else
        {
            panic("FragmentFIFO", "clock", "Missing sync state signal from Color Write.");
        }
    }

/*if ((cycle > 5024880) && (GPU_MOD(cycle, 1000) == 0))
{
printf("FF %lld => state %d rastStamps %d ztestedStamps %d interpolatedStamps %d\n", cycle,
state, allRastStamps, allTestStamps, allIntStamps);
for(i = 0; i < numStampUnits; i++)
printf("FF => unit queue %d => rast %d test %d int %d shaded %d\n",
i, rastStamps[i], testStamps[i], intStamps[i], shadedStamps[i]);
for(i = 0; i < numFShaders; i++)
printf("FF => shader unit %d => input q %d output q %d\n", i, numShaderInputs[i], numShaderOutputs[i]);
printf("FF => vertex in q %d vertex out q %d\n", vertexInputs, shadedVertices);
printf("FF => state ");
switch(state)
{
    case RAST_RESET:    printf("RESET\n"); break;
    case RAST_READY:    printf("READY\n"); break;
    case RAST_DRAWING:  printf("DRAWING\n"); break;
    case RAST_END:      printf("END\n"); break;
}
}*/

    receiveSyncFragments(cycle);

    /*  Simulate current cycle.  */
    switch(state)
    {
        case RAST_RESET:

            GPU_DEBUG_BOX(
                printf("FragmentFIFO => RESET state.\n");
            )

            /*  Reset state.  */

            /*  Check if unified shader model is enabled.  */
            if (unifiedModel)
            {
                /*  Reset vertex queues pointers.  */
                nextInputVertex = nextFreeInput = nextShadedVertex = nextFreeShVertex = 0;

                /*  Reset vertex queues counters.  */
                vertexInputs = shadedVertices = 0;
                freeInputs = vInputQueueSz;
                freeShVertices = vShadedQueueSz;

                /*  Check if triangle setup on the shaders is enabled.  */
                if (shadedSetup)
                {
                    /*  Reset triangle queue pointers.  */
                    nextInputTriangle = nextFreeInTriangle = nextOutputTriangle = nextFreeOutTriangle = 0;

                    /*  Reset triangle queue counters.  */
                    freeInputTriangles = triangleInQueueSz;
                    freeOutputTriangles = triangleOutQueueSz;
                    inputTriangles = outputTriangles = 0;
                }
            }

            /*  Reset per stamp unit rasterized, z tested and shaded stamp pointers and counters.  */
            for(i = 0; i < numStampUnits; i++)
            {
                freeRast[i] = rastQueueSz;
                freeTest[i] = testQueueSz;
                freeShaded[i] = shQueueSz;
	        freeSyncIn[gpuId][i] = interGPUSyncQueueSz;
		freeSyncOutZST[i] = syncQueueSz;
		freeSyncOutCW[i] = syncQueueSz;

                rastStamps[i] = testStamps[i] = shadedStamps[i] = 0;
                nextRast[i] = nextFreeRast[i] = nextTest[i] = nextFreeTest[i] = nextShaded[i] = nextFreeSh[i] = 0;
                freeInt[i] = intQueueSz;
                intStamps[i] = nextInt[i] = nextFreeInt[i] = 0;
		syncInStamps[i] = syncOutStampsZST[i] = syncOutStampsCW[i] = 0;
	        nextSyncIn[i] = nextFreeSyncIn[i] = 0;
		nextSyncOutZST[i] = nextFreeSyncOutZST[i] = 0;
		nextSyncOutCW[i] = nextFreeSyncOutCW[i] = 0;
            }

	    for (i = 0; i < numGPUs; i++)
	        syncedStampUnits[gpuId][i] = 0;

            /*  Updated rasterized, z tested  and interpolated stamps global counters.  */
            allRastStamps = allTestStamps = allIntStamps = 0;
	    allSyncInStamps = allSyncOutStampsZST = allSyncOutStampsCW= 0;

            /*  Reset shader input/output batch queues pointers and counters.  */
            for(i = 0; i < numFShaders; i++)
            {
                nextShaderInput[i] = nextFreeShInput[i] = 0;
                numShaderInputs[i] = 0;
                numFreeShInputs[i] = shInputQSize;
                nextShaderOutput[i] = nextFreeShOutput[i] = 0;
                numShaderOutputs[i] = 0;
                numFreeShOutputs[i] = shOutputQSize;
                batchedShInputs[i] = 0;
                
                //  Stall state.
                lastCycleShInput[i] = cycle;
                lastCycleShOutput[i] = cycle;
                shaderElements[i] = 0;
                
            }
            nextFreeShInQ = nextSendShInQ = nextProcessShOutQ = 0;
            inputFragments = outputFragments = 0;

            /*  Reset early Z test flag.  */
            earlyZ = TRUE;
            //earlyZ = FALSE;

            /*  Reset active fragment attributes.  */
            for(i = 0; i < MAX_FRAGMENT_ATTRIBUTES; i++)
            {
                fragmentAttributes[i] = FALSE;
            }

            //  Reset the render target state.
            for(u32bit rt = 0; rt < MAX_RENDER_TARGETS; rt++)
            {
                rtEnable[rt] = false;
		blend[rt] = false;
                colorMaskR[rt] = true;
                colorMaskG[rt] = true;
                colorMaskB[rt] = true;
                colorMaskA[rt] = true;
            }
            
            //  Backbuffer/render target 0 enabled by default.
            rtEnable[0] = true;

            /*  Reset last vertex input flag.  */
            lastVertexInput = FALSE;

            /*  Reset last vertex commit flag.  */
            lastVertexCommit = FALSE;

            /*  Reset last triangle flag.  */
            lastTriangle = false;

	    depthMask = true;
	    depthTest = false;
	    zStencilBufferDefined = true;

	    compMode = false;

            /*  Change to ready state.  */
            state = RAST_READY;

            break;

        case RAST_READY:

            /*  Ready state.  */

            GPU_DEBUG_BOX(
                printf("FragmentFIFO => READY state.\n");
            )

            /*  Process commands from the Rasterizer.  */
            if (fFIFOCommand->read(cycle, (DynamicObject *&) rastCommand))
                processCommand(rastCommand, cycle);

            /*  Vertex processing is not synchronized with the FFIFO state which is part of the
                the fragment group.  */

            /*  Check shader model.  */
            if (unifiedModel)
            {
                /*  Send vertices to Streamer Commit.  */
                sendVertices(cycle);

                /*  Receive outputs from the shaders.  */
                receiveShaderOutput(cycle);

                /*  Distribute shader outputs to the propper shaded queues.  */
                distributeShaderOutput(cycle);

                /*  Receive input vertices from Streamer Loader.  */
                receiveVertices(cycle);

                /*  Determine if there vertices to shade.  */
                if ((vertexInputs >= threadGroup) || ((vertexInputs > 0) && lastVertexInput && !lastVertexCommit) ||
                    ((vertexInputs > 0) && ((cycle - lastVertexGroupCycle) > VERTEX_CYCLE_THRESHOLD)))
                {
                    shadeVertices(cycle);
                }

                /*  Send shader inputs to the shader units.   */
                sendShaderInputs(cycle);
            }

            break;

        case RAST_DRAWING:

            /*  Draw state.  */

            GPU_DEBUG_BOX(
                printf("FragmentFIFO => Drawing state.\n");
            )

            /*  Check if early z is enabled.  */
            if (earlyZ)
            {
                /*  Send stamps to Color Write.  */
                sendStampsColorWrite(cycle);
            }
            else
            {
                /*  Send stamps to Color Write.  */
                sendTestedStampsColorWrite(cycle);

                /*  Receive stamps from early Z Stencil Test.  */
                endEarlyZ(cycle);

                /*  Send stamps to Z Stencil Test.  */
                sendStampsZStencil(cycle);
            }

            /*  Check shader model.  */
            if (unifiedModel)
            {
                /*  Check if triangle setup on shaders is enabled.  */
                if (!shadedSetup)
                {
                    /*  Send vertices to Streamer Commit.  */
                    sendVertices(cycle);

                    /*  Receive outputs from the shaders.  */
                    receiveShaderOutput(cycle);

                    /*  Distribute shader outputs to the propper shaded queues.  */
                    distributeShaderOutput(cycle);

                    /*  Receive input vertices from Streamer Loader.  */
                    receiveVertices(cycle);

                    /*  Determine what to send next, vertices or fragments.  */
                    if ((vertexInputs >= threadGroup) || ((vertexInputs > 0) && lastVertexInput && !lastVertexCommit) ||
                        ((vertexInputs > 0) && ((cycle - lastVertexGroupCycle) > VERTEX_CYCLE_THRESHOLD)))
                    {
                        shadeVertices(cycle);
                    }
                    else
                    {
                        /*  Shade stamps.  */
                        shadeStamps(cycle);
                    }

                    /*  Send shader inputs to the shader units.   */
                    sendShaderInputs(cycle);
                }
                else
                {
                    /*  Send triangles to triangle setup.  */
                    sendTriangles(cycle);

                    /*  Send vertices to Streamer Commit.  */
                    sendVertices(cycle);

                    /*  Receive outputs from the shaders.  */
                    receiveShaderOutput(cycle);

                    /*  Distribute shader outputs to the propper shaded queues.  */
                    distributeShaderOutput(cycle);

                    /*  Receive triangle inputs from Triangle Setup.  */
                    receiveTriangles(cycle);

                    /*  Receive input vertices from Streamer Loader.  */
                    receiveVertices(cycle);

                    /*  Determine what to send next: vertices, triangles or fragments.  */
                    if ((vertexInputs >= threadGroup) || ((vertexInputs > 0) && lastVertexInput && !lastVertexCommit) ||
                        ((vertexInputs > 0) && ((cycle - lastVertexGroupCycle) > VERTEX_CYCLE_THRESHOLD)))
                    {
                        shadeVertices(cycle);
                    }
                    else if ((inputTriangles >= threadGroup) || ((inputTriangles > 0) && lastTriangle))
                    {
                        shadeTriangles(cycle);
                    }
                    else
                    {
                        /*  Shade stamps.  */
                        shadeStamps(cycle);
                    }

                    /*  Send shader inputs to the shader units.   */
                    sendShaderInputs(cycle);
                }
            }
            else
            {
                /*  Receive outputs from the shaders.  */
                receiveShaderOutput(cycle);

                /*  Distribute shader outputs to the propper shaded queues.  */
                distributeShaderOutput(cycle);

                /*  Shade stamps.  */
                shadeStamps(cycle);

                /*  Send shader inputs to the shader units.   */
                sendShaderInputs(cycle);
            }

            /*  Receive stamps from the Interpolator.  */
            endInterpolation(cycle);

	    /*  Check if early z is enabled.  */
            if (earlyZ)
            {
                /*  Send stamps to the interpolator.  */
                startInterpolationEarlyZ(cycle);

                /*  Receive stamps from early Z Stencil Test.  */
                endEarlyZ(cycle);

                /*  Sends stamps to Early Z Stencil Test.  */
                startEarlyZ(cycle);
            }
            else
            {
                /*  Send stamps to the Interpolator.  */
                startInterpolation(cycle);
            }

            /*  Receive stamps from fragment generation (Hierarchical/Early Z).  */
            receiveStamps(cycle);

            break;

	case RAST_COMP:

	    processInputSyncFragments(cycle);

	    sendSyncFragmentsToOtherGPU(cycle);

	    endGenerationOfCWSyncFragments(cycle);

	    sendTestedStampsColorWrite(cycle);

            sendZSTSyncFragmentsColorWrite(cycle);

	    endEarlyZ(cycle);

	    endGenerationOfZSTSyncFragments(cycle);

	    if (notLastSyncReceive == 0 && notLastSyncSent == 0) {
		for (i = 0; i < numStampUnits; i++) {
                    GPU_ASSERT(
		        if (freeSyncIn[gpuId][i] != interGPUSyncQueueSz || syncInStamps[i] != 0 || nextSyncIn[i] != nextFreeSyncIn[i] || !idealSyncQueueIn[i].empty())
	                    panic(getName(), "clock", "some input sync fragments have not been processed");
		    )

		    nextSyncIn[i] = nextFreeSyncIn[i] = 0;
		}

		for (i = 0; i < numGPUs; i++) {
		    GPU_ASSERT(
		        if (anyRtBlend || i != gpuId) {
			    if (syncedStampUnits[gpuId][i] != numStampUnits)
			        panic(getName(), "clock", "some stamp units have not finished sync yet");
			}
		    )

		    syncedStampUnits[gpuId][i] = 0;
		}

		std::cout << "Debug: " << getName() << " finished comp @" << cycle << std::endl;

	        state = RAST_COMP_END;
	    }

	    break;

	case RAST_COMP_END:

            /*  Process commands from the Rasterizer.  */
            if (fFIFOCommand->read(cycle, (DynamicObject *&) rastCommand))
                processCommand(rastCommand, cycle);
	    
	    break;

        case RAST_END:

            /*  End state.  */
            GPU_DEBUG_BOX(
                printf("FragmentFIFO => END state.\n");
            )

            /*  Wait for END command from the Rasterizer.  */
            if (fFIFOCommand->read(cycle, (DynamicObject *&) rastCommand))
                processCommand(rastCommand, cycle);

            /*  Check shader model.  */
            if (unifiedModel)
            {
                /*  Send vertices to Streamer Commit.  */
                sendVertices(cycle);

                /*  Receive outputs from the shaders.  */
                receiveShaderOutput(cycle);

                /*  Distribute shader outputs to the propper shaded queues.  */
                distributeShaderOutput(cycle);

                /*  Receive input vertices from Streamer Loader.  */
                receiveVertices(cycle);

                /*  Determine if there vertices to shade.  */
                if ((vertexInputs >= threadGroup) || ((vertexInputs > 0) && lastVertexInput && !lastVertexCommit) ||
                    ((vertexInputs > 0) && ((cycle - lastVertexGroupCycle) > VERTEX_CYCLE_THRESHOLD)))
                {
                    shadeVertices(cycle);
                }

                /*  Send shader inputs to the shader units.   */
                sendShaderInputs(cycle);
            }

            break;

        default:
            panic("FragmentFIFO", "clock", "Unsupported FragmentFIFO state.");
            break;
    }

    /*  Send state to the main rasterizer box.  */
    fFIFOState->write(cycle, new RasterizerStateInfo(state));

    /*  Calculate the minimum number of free entries in the rasterized stamp queues.  */
    for(i = 1, minFreeRast = freeRast[0]; i < numStampUnits; i++)
        minFreeRast = GPU_MIN(minFreeRast, freeRast[i]);

    /*  Send state to Hierarchical unit.  */
    if (minFreeRast >= (2 * hzStampsCycle))
    {
        /*  Create state carrier and send to signal.  */
        ffStateHZ->write(cycle, new FFIFOStateInfo(FFIFO_READY));
    }
    else
    {
        /*  Create state carrier and send to signal.  */
        ffStateHZ->write(cycle, new FFIFOStateInfo(FFIFO_BUSY));
    }

    /*  Check shader model.  */
    if (unifiedModel)
    {
        /*  Send state to Streamer Loader.  */
        for(i = 0; i < numVShaders; i++)
        {
            vertexState[i]->write(cycle,
                new ShaderStateInfo((freeInputs == vInputQueueSz)?SH_EMPTY:
                    ((freeInputs >= (2 * numVShaders))?SH_READY:SH_BUSY))
                );
        }

        /*  Check if triangle setup in shaders is enabled.  */
        if (shadedSetup)
        {
            /*  Send state to Triangle Setup.  */
            triangleState->write(cycle, new ShaderStateInfo(
                (freeInputTriangles >= ((1 + triangleLat) * trianglesCycle))?SH_READY:SH_BUSY)
                );
        }
    }

    /*  Send state to Fragment Shader units.  */
    for(i = 0; i < numFShaders; i++)
    {
        /*  NOTE:  MUST BE IMPLEMENTED YET!!!!  TYPES OF STATE CARRIER ARE DIFFERENT!!   */
        /*  Send current state to the Fragment Shader.  */
        ffStateShader[i]->write(cycle, new ConsumerStateInfo(CONS_READY));
    }

    /*  Send state to the Z Stencil Test units.  */
    for(i = 0; i < numStampUnits; i++)
    {
        /*  Check if there is enough free entries in the early z tested queue.  */
        if (freeTest[i] > (2 * stampsPerUnit))
        {
            /*  Send current state to a Z Stencil Test unit.  */
            fFIFOZSTState[i]->write(cycle, new ROPStatusInfo(ROP_READY));
        }
        else
        {
            /*  Send current state to a Z Stencil Test unit.  */
            fFIFOZSTState[i]->write(cycle, new ROPStatusInfo(ROP_BUSY));
        }
	
	/*  Check if there is enough free entries in the ZST sync output queue.  */
        if (freeSyncOutZST[i] > (2 * stampsPerUnit))
        {
            /*  Send current state to a Z Stencil Test unit.  */
            fFIFOZSTSyncState[i]->write(cycle, new ROPStatusInfo(ROP_READY));
        }
        else
        {
            /*  Send current state to a Z Stencil Test unit.  */
            fFIFOZSTSyncState[i]->write(cycle, new ROPStatusInfo(ROP_BUSY));
        }
	
	/*  Check if there is enough free entries in the CW sync output queue.  */
        if (freeSyncOutCW[i] > (2 * stampsPerUnit))
        {
            /*  Send current state to a color write unit.  */
            fFIFOCWSyncState[i]->write(cycle, new ROPStatusInfo(ROP_READY));
        }
        else
        {
            /*  Send current state to a color write unit.  */
            fFIFOCWSyncState[i]->write(cycle, new ROPStatusInfo(ROP_BUSY));
        }
    }


    /*  Update statistics.  */
    rastGLevel->inc(allRastStamps);
    testGLevel->inc(allTestStamps);
    intGLevel->inc(allIntStamps);
    globalRastGLevel->inc(allRastStamps);
    globalTestGLevel->inc(allTestStamps);
    globalIntGLevel->inc(allIntStamps);
    
    for(i = 0; i < numStampUnits; i++) {
        shadedGLevel->inc(shadedStamps[i]);
        globalShadedGLevel->inc(shadedStamps[i]);
    }
    
    vertInLevel->inc(vertexInputs);
    vertOutLevel->inc(shadedVertices);
    trInLevel->inc(inputTriangles);
    trOutLevel->inc(outputTriangles);
    globalVertInLevel->inc(vertexInputs);
    globalVertOutLevel->inc(shadedVertices);
    globalTrInLevel->inc(inputTriangles);
    globalTrOutLevel->inc(outputTriangles);
}


/*  Processes a rasterizer command.  */
void FragmentFIFO::processCommand(RasterizerCommand *command, u64bit cycle)
{
    u32bit i;
    u32bit j;
    u32bit activeAttributes;
    indexOwner owner;
    kdTreeInfo kdInfo;

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
                printf("FragmentFIFO => RESET command received.\n");
            )

            /*  Change to reset state.  */
            state = RAST_RESET;

            break;

        case RSCOM_DRAW:
            /*  Draw command from the Rasterizer main box.  */

            GPU_DEBUG_BOX(
                printf("FragmentFIFO %lld => DRAW command received.\n", cycle);
            )


            /*  Check current state.  */
            GPU_ASSERT(
                if (state != RAST_READY)
                    panic("FragmentFIFO", "processCommand", "DRAW command can only be received in READY state.");
            )

            /*  Reset per stamp unit rasterized, z tested and shaded queue counters and pointers.  */
            for(i = 0; i < numStampUnits; i++)
            {
                freeRast[i] = rastQueueSz;
                freeTest[i] = testQueueSz;
                freeShaded[i] = shQueueSz;
                rastStamps[i] = testStamps[i] = shadedStamps[i] = 0;
                freeInt[i] = intQueueSz;
                intStamps[i] = nextInt[i] = nextFreeInt[i] = 0;

                /*  Reset shaded flags.  */
                for(j = 0; j < shQueueSz; j++)
                    shaded[i][j] = FALSE;

                nextRast[i] = nextFreeRast[i] = nextTest[i] = nextFreeTest[i] =
                nextShaded[i] = nextFreeSh[i] = 0;

                lastShaded[i] = FALSE;

                /*  Reset last stamp interpolated flag.  */
                lastStampInterpolated[i] = false;
            }

            /*  Updated rasterized, z tested  and interpolated stamps global counters.  */
            allRastStamps = allTestStamps = allIntStamps = 0;

            /*  Reset next rasterized queue from where to send stamps to interpolator (early z disabled).  */
            nextRastUnit = 0;

            /*  Reset next z tested queue from where to send stamps to interpolator (early z enabled).  */
            nextTestUnit = 0;

            /*  Reset next interpolated queue from which to send stamps to the shader.  */
            nextIntUnit = 0;

            /*  Reset number of Z Stencil Test units waiting for last fragment.  */
            notLastSent = numStampUnits;

            /*  Last fragment not received.  */
            lastFragment = FALSE;

            /*  Reset triangle related flags, counters and pointers.  */
            lastTriangle = false;
            nextInputTriangle = nextFreeInTriangle = nextOutputTriangle = nextFreeOutTriangle = 0;
            inputTriangles = outputTriangles = 0;
            freeInputTriangles = triangleInQueueSz;
            freeOutputTriangles = triangleOutQueueSz;

            /*  Reset shader input/output batch queues pointers and counters.  */
            //for(i = 0; i < numFShaders; i++)
            //{
            //    nextShaderInput[i] = nextFreeShInput[i] = 0;
            //    numShaderInputs[i] = 0;
            //    numFreeShInputs[i] = shInputQSize;
            //    nextShaderOutput[i] = nextFreeShOutput[i] = 0;
            //    numShaderOutputs[i] = 0;
            //    numFreeShOutputs[i] = shOutputQSize;
            //}
            //nextFreeShInQ = nextSendShInQ = nextProcessShOutQ = 0;

            /*  Reset number of fragments sent and received from the shaders.  */
            inputFragments = outputFragments = 0;

            /*  Reset fragment counter.  */
            fragmentCounter = 0;

            /*  Count the number of active interpolators.  */
            for(i = 0, activeAttributes = 0; i < MAX_FRAGMENT_ATTRIBUTES; i++)
                if (fragmentAttributes[i])
                    activeAttributes++;

            /*  Reset first vertex issued flag.  */
            firstVertex = false;

            /*  Calculate the number of cycles interpolating a stamp of fragments.  */
            interpCycles = (u32bit) ceil((double) activeAttributes / (double) interpolators);

            /*  Reset interpolator wait cycle counter.  */
            waitIntCycles = 0;

	    batchCounter = command->getBatchCounter();
	    frameCounter = command->getFrameCounter();

            /*  Change to drawing state.  */
            state = RAST_DRAWING;

            break;

        case RSCOM_COMP:
            /*  COMP command from the Rasterizer main box.  */

            GPU_DEBUG_BOX(
                printf("FragmentFIFO %lld => COMP command received.\n", cycle);
            )


            /*  Check current state.  */
            GPU_ASSERT(
                if (state != RAST_READY)
                    panic("FragmentFIFO", "processCommand", "COMP command can only be received in READY state.");
            )

	    owner.gpuId = gpuId;
	    owner.frameId = frameCounter;
	    owner.batchId = batchCounter;
	    GPU_ASSERT(
		if (GPUDriver::getGPUDriver()->getKDTreeIndexesInSortLast()->count(owner) == 0)
		    panic(getName(), "processCommand", "cannot find kdInfo");
	    )
	    kdInfo = GPUDriver::getGPUDriver()->getKDTreeIndexesInSortLast()->at(owner);
	    anyRtBlend = kdInfo.anyRtBlend;
	    bypassCW = !kdInfo.anyRtCWrite;
	    //bypassCW = !colorMaskR[0] && !colorMaskG[0] && !colorMaskB[0] && !colorMaskA[0];
	    bypassZST = !zStencilBufferDefined || !kdInfo.anyZTest || !depthMask;

	    GPU_ASSERT(
		if (anyRtBlend && bypassCW)
		    panic(getName(), "processCommand", "if any rt blend, bypassCW should be false");
	    )

	    std::cout << "Debug: "<< getName() << " begin comp @" << cycle
	              << " frame " << frameCounter << " batch " << batchCounter
	              << " bypassZST " << (bypassZST ? "T" : "F")
		      << " bypassCW " << (bypassCW ? "T" : "F") << " blend " << (anyRtBlend ? "T" : "F")
		      << std::endl;

	    if (bypassCW && bypassZST) {
		state = RAST_COMP_END;
	    } else {
	        // since some input sync frags are received before receiving RSCOM_COMP, metadata of syncInQueue is set after comp is done
                for(i = 0; i < numStampUnits; i++)
                {
                    freeTest[i] = testQueueSz;
                    testStamps[i] = 0;
	            freeSyncOutZST[i] = freeSyncOutCW[i] = syncQueueSz;
	            syncOutStampsZST[i] = syncOutStampsCW[i] = 0;

                    nextTest[i] = nextFreeTest[i] = 0;
	            nextSyncOutZST[i] = nextFreeSyncOutZST[i] = 0;
	            nextSyncOutCW[i] = nextFreeSyncOutCW[i] = 0;
                }

	        allTestStamps = 0;
	        allSyncInStamps = 0;
	        allSyncOutStampsZST = 0;
	        allSyncOutStampsCW = 0;
           
	        if (anyRtBlend) {
	            notLastSyncReceive = numStampUnits * numGPUs;
	            notLastSyncSent = numStampUnits * numGPUs;
	        } else { 
	            notLastSyncReceive = numStampUnits * (numGPUs - 1);
	            notLastSyncSent = numStampUnits * (numGPUs - 1);
	        }
                
                state = RAST_COMP;
	    }

	    break;

        case RSCOM_END:
            /*  End command received from Rasterizer main box.  */

            GPU_DEBUG_BOX(
                printf("FragmentFIFO => END command received.\n");
            )


            /*  Check current state.  */
            GPU_ASSERT(
                if ((state != RAST_END) && (state != RAST_CLEAR_END) && (state != RAST_COMP_END))
                    panic("FragmentFIFO", "processCommand", "END command can only be received in END state.");
            )

            /*  Change to ready state.  */
            state = RAST_READY;

            break;

        case RSCOM_REG_WRITE:
            /*  Write register command from the Rasterizer main box.  */

            GPU_DEBUG_BOX(
                printf("FragmentFIFO => REG_WRITE command received.\n");
            )

            /*  Check current state.  */
            GPU_ASSERT(
                if (state != RAST_READY)
                    panic("FragmentFIFO", "processCommand", "REGISTER WRITE command can only be received in READY state.");
            )

            /*  Process register write.  */
            processRegisterWrite(command->getRegister(),
                command->getSubRegister(), command->getRegisterData());

            break;

        default:
            panic("FragmentFIFO", "proccessCommand", "Unsupported command.");
            break;
    }
}


/*  Processes a register write.  */
void FragmentFIFO::processRegisterWrite(GPURegister reg, u32bit subreg, GPURegData data)
{
    /*  Process register write.  */
    switch(reg)
    {
        case GPU_EARLYZ:

            /*  Set early Z test flag.  */
            earlyZ = data.booleanVal;

            GPU_DEBUG_BOX(
                printf("FragmentFIFO => Write GPU_EARLY_Z = %s.\n",
                    data.booleanVal?"ENABLED":"DISABLED");
            )

            break;

        case GPU_FRAGMENT_INPUT_ATTRIBUTES:
            /*  Write the active fragment attributes register.  */

            /*  Check fragment attribute identifier range.  */
            GPU_ASSERT(
                if (subreg >= MAX_FRAGMENT_ATTRIBUTES)
                    panic("FragmentFIFO", "processRegisterWrite", "Fragment attribute identifier out of range.");
            )

            /*  Write the fragment attribute active flag.  */
            fragmentAttributes[subreg] = data.booleanVal;

            GPU_DEBUG_BOX(
                printf("FragmentFIFO => Write GPU_FRAGMENT_INPUT_ATTRIBUTES[%d] = %s.\n",
                    subreg, data.booleanVal?"ACTIVE":"INACTIVE");
            )

            break;

        case GPU_STENCIL_TEST:

            /*  Write the stencil test enable flag register.  */
            stencilTest = data.booleanVal;

            GPU_DEBUG_BOX(
                printf("FragmentFIFO => GPU_STENCIL_TEST = %s.\n", data.booleanVal?"ENABLED":"DISABLED");
            )

            break;

        case GPU_DEPTH_TEST:

            /*  Write the depth test enable flag register.  */
            depthTest = data.booleanVal;

            GPU_DEBUG_BOX(
                printf("FragmentFIFO => GPU_DEPTH_TEST = %s.\n", data.booleanVal?"ENABLED":"DISABLED");
            )

            break;

        case GPU_ZSTENCILBUFFER_DEFINED:

            zStencilBufferDefined = data.booleanVal;

            GPU_DEBUG_BOX(
                printf("FragmentFIFO => GPU_ZSTENCILBUFFER_DEFINED = %s.\n", data.booleanVal?"ENABLED":"DISABLED");
            )

            break;

        case GPU_DEPTH_MASK:

            /*  Write the depth mask flag register.  */
            depthMask = data.booleanVal;

            GPU_DEBUG_BOX(
                printf("FragmentFIFO => GPU_DEPTH_MASK = %s.\n", data.booleanVal?"ENABLED":"DISABLED");
            )

            break;

        case GPU_RENDER_TARGET_ENABLE:

            //  Write the render target enable register.
            rtEnable[subreg] = data.booleanVal;

            GPU_DEBUG_BOX(
                printf("FragmentFIFO => GPU_RENDER_TARGET_ENABLE[%d] = %s.\n", subreg, data.booleanVal?"TRUE":"FALSE");
            )

            break;

        case GPU_COLOR_BLEND:

            blend[subreg] = data.booleanVal;

            GPU_DEBUG_BOX(
                printf("FragmentFIFO => GPU_COLOR_BLEND[%d] = %s.\n", subreg, data.booleanVal?"TRUE":"FALSE");
            )

            break;

        case GPU_COLOR_MASK_R:

            //  Write the red component mask register.
            colorMaskR[subreg] = data.booleanVal;

            GPU_DEBUG_BOX(
                printf("FragmentFIFO => GPU_COLOR_MASK_R[%d] = %s.\n", subreg, data.booleanVal?"TRUE":"FALSE");
            )

            break;

        case GPU_COLOR_MASK_G:

            //  Write the green component mask register.
            colorMaskG[subreg] = data.booleanVal;

            GPU_DEBUG_BOX(
                printf("FragmentFIFO => GPU_COLOR_MASK_G[%d] = %s.\n", subreg, data.booleanVal?"TRUE":"FALSE");
            )

            break;

        case GPU_COLOR_MASK_B:

            //  Write the blue component mask register.
            colorMaskB[subreg] = data.booleanVal;

            GPU_DEBUG_BOX(
                printf("FragmentFIFO => GPU_COLOR_MASK_B[%d] = %s.\n", subreg, data.booleanVal?"TRUE":"FALSE");
            )

            break;

        case GPU_COLOR_MASK_A:

            //  Write the alpha component mask register.
            colorMaskA[subreg] = data.booleanVal;

            GPU_DEBUG_BOX(
                printf("FragmentFIFO => GPU_COLOR_MASK_A[%d] = %s.\n", subreg, data.booleanVal?"TRUE":"FALSE");
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
            panic("FragmentFIFO", "processRegisterWrite", "Unsupported register.");
            break;
    }

}

/*  Receives vertices from Streamer Loader.  */
void FragmentFIFO::receiveVertices(u64bit cycle)
{
    u32bit i;
    ShaderInput *shInput;
    u32bit lastVertexReceived = false;

    /*  Receive shader inputs from Streamer Loader.  */
    for(i = 0; i < numVShaders; i++)
    {
        /*  Check if there is an input from Streamer Loader.  */
        if (vertexInput[i]->read(cycle, (DynamicObject *&) shInput))
        {
            /*  Check there are free vertex input queue entries.  */
            GPU_ASSERT(
                if (freeInputs == 0)
                    panic("FragmentFIFO", "receiveVertices", "No free vertex input queue entry.");

                if (lastVertexCommit)
                    panic("FragmentFIFO", "receiveVertices", "Vertex received after last vertex commit.");
            )

            GPU_DEBUG_BOX(
                printf("FragmentFIFO %lld => Received vertex input for entry %d from virtual vertex shader signal %d stored at %d\n",
                    cycle, shInput->getEntry(), i, nextFreeInput);
            )

            /*  Store vertex input in the vertex input queue.  */
            inputVertexQueue[nextFreeInput] = shInput;

            /*  Store if last vertex input was received.  */
            lastVertexReceived = lastVertexReceived || shInput->isLast();

            /*  Update number of free vertex input queue entries.  */
            freeInputs--;

            /*  Update number of input vertices.  */
            vertexInputs++;

            /*  Update pointer to the next free vertex input queue entry.  */
            nextFreeInput = GPU_MOD(nextFreeInput + 1, vInputQueueSz);

            /*  Update first vertex in current batch flag.  */
            if (!firstVertex)
            {
                /*  First vertex received.  */
                firstVertex = true;

                /*  Reset cycle counter from last vertex group issued time.  */
                lastVertexGroupCycle = cycle;
            }

            /*  Update statistics.  */
            inVerts->inc();
            globalInVerts->inc();
        }
    }

    /*  Set if the last vertex in the batch was received from any of the shader signals.  */
    lastVertexInput = lastVertexReceived;
}

/*  Receives triangles from TriangleSetup.  */
void FragmentFIFO::receiveTriangles(u64bit cycle)
{
    ShaderInput *shInput;

    /*  Receive triangle inputs from Triangle Setup.  */
    while (triangleInput->read(cycle, (DynamicObject *&) shInput))
    {
        /*  Check there are free triangle input queue entries.  */
        GPU_ASSERT(
            if (freeInputTriangles == 0)
                panic("FragmentFIFO", "receiveTriangle", "No free triangle input queue entry.");
        )

        GPU_DEBUG_BOX(
            printf("FragmentFIFO => Received triangle input from Triangle Setup to be stored at %d\n",
                nextFreeInTriangle);
        )

        /*  Store triangle input in the triangle input queue.  */
        triangleInQueue[nextFreeInTriangle] = shInput;

        /*  Store if last batch triangle was received.  */
        lastTriangle = shInput->isLast();

        /*  Update number of free triangle input queue entries.  */
        freeInputTriangles--;

        /*  Update number of input triangles.  */
        inputTriangles++;

        /*  Update pointer to the next free triangle input queue entry.  */
        nextFreeInTriangle = GPU_MOD(nextFreeInTriangle + 1, triangleInQueueSz);

        /*  Update statistics.  */
        inTriangles->inc();
        globalInTriangles->inc();
    }
}


/*  Receives stamps from fragment generation.  */
void FragmentFIFO::receiveStamps(u64bit cycle)
{
    bool receivedFragment;
    bool lastStamp;
    FragmentInput *frInput;
    FragmentInput *clonedFrInput;
    u32bit i;
    u32bit j;
    u32bit k;
    u32bit unit;
    u32bit numStamps = 0;

    lastStamp = FALSE;

    /*  Receive stamps from Fragment Generation.  */
    for(i = 0; i < hzStampsCycle; i++)
    {
        /*  Reset received fragment flag.  */
        receivedFragment = TRUE;

        /*  Receive fragments in a stamp.  */
        for(j = 0; (j < STAMP_FRAGMENTS) && receivedFragment; j++)
        {
            /*  Get fragment from Fragment Generation.  */
            receivedFragment = hzInput->read(cycle, (DynamicObject *&) frInput);

            /*  Check if a fragment has been received.  */
            if (receivedFragment)
            {
                /*  Retrieve stamp unit for the fragment.  */
                unit = frInput->getStampUnit();

                /*  Check if fragment is last.  */
                if (frInput->getFragment() != NULL)
                {
                    /*  Store fragment in the current stamp.  */
                    rastQueue[unit][nextFreeRast[unit]][j] = frInput;

		    if (frInput->getDebug()) {
		        FILE *debug = fopen("debugHZOut.txt", "a+");
		        fprintf(debug, "GPU[%d] cycle %lld HZ results (tri = %d tile = (%d, %d), x = %d, y = %d, z = %d) culled = %s\n",
		        	gpuId, cycle, frInput->getTriangleID(), frInput->getTileID().getX(), frInput->getTileID().getY(),
		        	frInput->getFragment()->getX(), frInput->getFragment()->getY(), frInput->getFragment()->getZ(),
		        	frInput->isCulled() ? "T" : "F");
		        QuadFloat* attributes = frInput->getAttributes();
	                for (u32bit index = 0; attributes && index < MAX_FRAGMENT_ATTRIBUTES; index++) {
                            fprintf(debug, "attrib[%d] = { %f, %f, %f, %f }\n", index,
	                            attributes[index][0], attributes[index][1],
                                    attributes[index][2], attributes[index][3]);
	                }
		        fflush(debug);
		        fclose(debug);
		    }
                }
                else
                {
                    /*  Check if early z is enabled.  */
                    //if (earlyZ)
                    //{
                        /*  Store fragment in the current stamp.  */
                        //rastQueue[unit][nextFreeRast[unit]][j] = frInput;

                        /*  Clone last fragment.  */
                        for(k = 0; k < numStampUnits; k++)
                        {
                            clonedFrInput = new FragmentInput(frInput->getTriangleID(),
                                frInput->getSetupTriangle(), NULL, frInput->getTileID(), k);
                            clonedFrInput->copyParentCookies(*frInput);

                            /*  Store cloned fragment in the rasterized queue.  */
                            rastQueue[k][nextFreeRast[k]][j] = clonedFrInput;
                        }

                        /*  Last fragment signal received.  */
                        lastStamp = TRUE;

                        /*  Delete original last fragment.  */
                        delete frInput;
                    //}
                    //else
                    //{
                    //    /*  Store fragment in the current stamp.  */
                    //    rastQueue[unit][nextFreeRast[unit]][j] = frInput;
                    //}
                }

                /*  Update fragment counter.  */
                fragmentCounter++;

                /*  Update statistics.  */
                inputs->inc();
                globalInputs->inc();
            }
        }

        /*  Check if a whole stamp has been received.  */
        GPU_ASSERT(
            if (!receivedFragment && (j > 1))
                panic("FragmentFIFO", "receiveStamps", "Missing fragments in a stamp.");
        )

        /*  Check if a stamp has been received.  */
        if (receivedFragment)
        {
            GPU_ASSERT(
                if (lastFragment)
                    panic("FragmentFIFO", "receiveStamps", "Stamp received after last stamp.");
            )

            if (!lastStamp)
            {
                GPU_ASSERT(
                    if (freeRast[unit] == 0)
                        panic("FragmentFIFO", "receiveStamps", "Not enough room in the rasterizer queue for incoming stamp.");
                )

                GPU_DEBUG_BOX(
                    printf("FragmentFIFO => Received stamp from Hierarchical Z.  Stored in rasterized queue %d position %d.\n",
                        unit, nextFreeRast[unit]);
                )

                /*  Update rasterizer queue free entry pointer.  */
                nextFreeRast[unit] = GPU_MOD(nextFreeRast[unit] + 1, rastQueueSz);

                /*  Update rasterizer queue counter.  */
                rastStamps[unit]++;

                /*  Update number of stamps in all the rasterizer queues.  */
                allRastStamps++;

                /*  Update free rasterizer queue entry counter.  */
                freeRast[unit]--;
            }
            else
            {
                for(k = 0; k < numStampUnits; k++)
                {
                    GPU_ASSERT(
                        if (freeRast[k] == 0)
                            panic("FragmentFIFO", "receiveStamps", "Not enough room in the rasterizer queue for incoming stamp.");
                    )

                    GPU_DEBUG_BOX(
                        printf("FragmentFIFO => Received last stamp from Hierarchical Z.  Stored in %d.\n", nextFreeRast[k]);
                    )

                    /*  Update rasterizer queue free entry pointer.  */
                    nextFreeRast[k] = GPU_MOD(nextFreeRast[k] + 1, rastQueueSz);

                    /*  Update rasterizer queue counter.  */
                    rastStamps[k]++;

                    /*  Update number of stamps in all the rasterizer queues.  */
                    allRastStamps++;

                    /*  Update free rasterizer queue entry counter.  */
                    freeRast[k]--;
                }

                /*  Last fragment processed.  */
                lastFragment = TRUE;
            }

	    numStamps++;
        }
    }

    numRastStamps->incavg(numStamps);
    globalNumRastStamps->incavg(numStamps);
}

/*  Receive stamps from interpolation unit.  */
void FragmentFIFO::endInterpolation(u64bit cycle)
{
    FragmentInput *frInput;
    bool receivedFragment;
    u32bit i;
    u32bit j;
    u32bit unit;
    u32bit shUnit;

    /*  Receive stamps from the interpolator.  */
    for(i = 0; i < stampsCycle * stampsPerGroup; i++)
    {
        /*  Reset received fragment flag.  */
        receivedFragment = TRUE;

        /*  Receive fragments in a stamp.  */
        for(j = 0; (j < STAMP_FRAGMENTS) && receivedFragment; j++)
        {
            /*  Get fragment from Interpolator.  */
            receivedFragment = interpolatorOutput->read(cycle, (DynamicObject *&) frInput);

            /*  Check if a fragment has been received.  */
            if (receivedFragment)
            {
                /*  Retrieve stamp unit for the fragment.  */
                unit = frInput->getStampUnit();

                /*  Store fragment in the current stamp.  */
                intQueue[unit][nextFreeInt[unit]][j] = frInput;

                /*  Check if fragment is last.  */
                if ((j == 0) && (frInput->getFragment() == NULL))
                {
                    /*  Set last stamp passed interpolation flag.  */
                    lastStampInterpolated[unit] = true;
                }
                else
                {
                    /*  Check no stamp is received after the last one.  */
                    GPU_ASSERT(
                        if ((j == 0) && (lastStampInterpolated[unit]))
                            panic("FragmentFIFO", "endInterpolation", "Stamp received from interpolator after last stamp.");
                    )
                }

                /*  Calculate the shader unit to which the fragment will be assigned.  */
                //shUnit = frInput->getTileID().assignInterleaved(numFShaders);
                shUnit = frInput->getTileID().assignMorton(numFShaders);

                /*  Assign fragment to the calculated unit.  */
                frInput->setShaderUnit(shUnit);

		if (frInput->getFragment() && frInput->getDebug()) {
		    char filename[32];
		    sprintf(filename, "debugIntOut%d.txt", unit);
		    FILE *debug = fopen(filename, "a+");
		    fprintf(debug, "GPU[%d] cycle %lld Interpolator result (tri = %d tile = (%d, %d), x = %d, y = %d, z = %d) shader = %d unit = %d entry = %d culled = %s\n",
		    	gpuId, cycle, frInput->getTriangleID(), frInput->getTileID().getX(), frInput->getTileID().getY(),
		    	frInput->getFragment()->getX(), frInput->getFragment()->getY(), frInput->getFragment()->getZ(),
			shUnit, unit, nextFreeInt[unit],
		    	frInput->isCulled() ? "T" : "F");
		    QuadFloat* attributes = frInput->getAttributes();
	            for (u32bit index = 0; attributes && index < MAX_FRAGMENT_ATTRIBUTES; index++) {
                        fprintf(debug, "attrib[%d] = { %f, %f, %f, %f }\n", index,
	                        attributes[index][0], attributes[index][1],
                                attributes[index][2], attributes[index][3]);
	            }
		    fflush(debug);
		    fclose(debug);
		}

                /*  Update statistics.  */
                interpolated->inc();
                globalInterpolated->inc();
            }
        }

        /*  Check if a whole stamp has been received.  */
        GPU_ASSERT(
            if (!receivedFragment && (j > 1))
                panic("FragmentFIFO", "endInterpolation", "Missing fragments in a stamp.");
        )

        /*  Check if a stamp has been received.  */
        if (receivedFragment)
        {
            GPU_DEBUG_BOX(
                printf("FragmentFIFO => Received interpolated stamp from Interpolator.  Stored in interpolated queue %d position %d.\n",
                    unit, nextFreeInt[unit]);
            )

            /*  Update interpolator queue free entry pointer.  */
            nextFreeInt[unit] = GPU_MOD(nextFreeInt[unit] + 1, intQueueSz);

            /*  Update interpolator queue counter.  */
            intStamps[unit]++;

            /*  Update global number of interpolated stamps.  */
            allIntStamps++;
        }
    }
}

/*  Sends stamps from rasterizer queue to interpolator.  */
void FragmentFIFO::startInterpolation(u64bit cycle)
{
    bool sentStamp;
    u32bit visited;
    u32bit i;
    u32bit j;
    TileIdentifier currentTile;

    /*  Update wait cycles counter.  */
    if (waitIntCycles > 0)
        waitIntCycles--;

    /*  Check if the interpolator can receive stamps.  */
    if (waitIntCycles == 0)
    {
        /*  Reset stamp sent to the interpolator flag.  */
        sentStamp = FALSE;

        /*  Visited rasterized queues.  */
        /*  Search for a rasterized queue with stamps.  */
        for(visited = 0; (visited < numStampUnits) && (allRastStamps > 0) &&
            ((rastStamps[nextRastUnit] == 0) || (freeInt[nextRastUnit] == 0)); visited++)
        {
            nextRastUnit = GPU_MOD(nextRastUnit + 1, numStampUnits);
        }

        for(i = 0; (i < stampsCycle * stampsPerGroup) && (rastStamps[nextRastUnit] > 0) && (freeInt[nextRastUnit] > 0); i++)
        {
            GPU_DEBUG_BOX(
                printf("FragmentFIFO => Sending stamp from unit %d stored at %d to Interpolator.\n", nextRastUnit,
                nextRast[nextRastUnit]);
            )

            /*  Get the tile identifier for the current stamp.  */
            currentTile = rastQueue[nextRastUnit][nextRast[nextRastUnit]][0]->getTileID();

            /*  Send stamp to the interpolator.  */
            for(j = 0; j < STAMP_FRAGMENTS; j++)
            {
                /*  Send fragment to the Interpolator.  */
                interpolatorInput->write(cycle, rastQueue[nextRastUnit][nextRast[nextRastUnit]][j]);
            }

            /*  Update number of stamps to send to interpolator.  */
            rastStamps[nextRastUnit]--;

            /*  Update number of stamps in all the rasterizer queues.  */
            allRastStamps--;

            /*  Update number of free queue entries.  */
            freeRast[nextRastUnit]++;

            /*  Update pointer to the next rasterized stamp.  */
            nextRast[nextRastUnit] = GPU_MOD(nextRast[nextRastUnit] + 1, rastQueueSz);

            /*  Update number of free interpolator queue entries.  */
            freeInt[nextRastUnit]--;

            /*  Set stamp sent to the interpolator flag.  */
            sentStamp = TRUE;

            /*  Check if the tile has changed after the current stamp.  */
            if ((rastStamps[nextRastUnit] > 0) &&
                (currentTile != rastQueue[nextRastUnit][nextRast[nextRastUnit]][0]->getTileID()))
            {
                /*  Skip to the next rasterizer unit for fragments to interpolate.  */
                nextRastUnit = GPU_MOD(nextRastUnit + 1, numStampUnits);
                visited++;
            }

            /*  Search for a rasterized queue with stamps.  */
            for(; (visited < numStampUnits) && (allRastStamps > 0) &&
                ((rastStamps[nextRastUnit] == 0) || (freeInt[nextRastUnit] == 0)); visited++)
            {
                nextRastUnit = GPU_MOD(nextRastUnit + 1, numStampUnits);
            }
        }

	numStampsToInt->incavg(i);
	globalNumStampsToInt->incavg(i);

        /*  Check if a stamp was sent to the interpolator.  */
        if (sentStamp)
            waitIntCycles = interpCycles;
    } else {
	waitIntStalls->inc();
	globalWaitIntStalls->inc();
    }
}

/*  Sends stamps from early z test queue to interpolator.  */
void FragmentFIFO::startInterpolationEarlyZ(u64bit cycle)
{
    bool sentStamp;
    u32bit visited;
    u32bit i;
    u32bit j;
    TileIdentifier currentTile(0,0);


    /*  Update wait cycles counter.  */
    if (waitIntCycles > 0)
        waitIntCycles--;

    /*  Check if the interpolator can receive stamps.  */
    if (waitIntCycles == 0)
    {
        /*  Reset stamp sent to the interpolator flag.  */
        sentStamp = FALSE;

        /*  Search for a z tested queue with stamps.  */
        for(visited = 0; (visited < numStampUnits) && (allTestStamps > 0) &&
            ((testStamps[nextTestUnit] == 0) || (freeInt[nextTestUnit] == 0)); visited++)
        {
            nextTestUnit = GPU_MOD(nextTestUnit + 1, numStampUnits);
        }

        for(i = 0; (i < stampsCycle * stampsPerGroup) && (testStamps[nextTestUnit] > 0) && (freeInt[nextTestUnit] > 0);)
        {
            GPU_DEBUG_BOX(
                printf("FragmentFIFO => Sending stamp from unit %d stored at %d to Interpolator.\n",
                    nextTestUnit, nextTest[nextTestUnit]);
            )

            /*  Get the tile identifier for the current stamp.  */
            currentTile = testQueue[nextTestUnit][nextTest[nextTestUnit]][0]->getTileID();

            /*  Send stamp to the interpolator.  */
            for(j = 0; j < STAMP_FRAGMENTS; j++)
            {
                /*  Send fragment to the Interpolator.  */
                interpolatorInput->write(cycle, testQueue[nextTestUnit][nextTest[nextTestUnit]][j]);
            }

            /*  Update number of stamps issued in current cycle.  */
            i++;

            /*  Update number of stamps to send to interpolator.  */
            testStamps[nextTestUnit]--;

            /*  Update global number of z tested stamps.  */
            allTestStamps--;

            /*  Update number of free queue entries.  */
            freeTest[nextTestUnit]++;

            /*  Update pointer to the next stamp to send in the queue.  */
            nextTest[nextTestUnit] = GPU_MOD(nextTest[nextTestUnit] + 1, testQueueSz);

            /*  Update number of free interpolator queue entries.  */
            freeInt[nextTestUnit]--;

            /*  Set stamp sent to the interpolator flag.  */
            sentStamp = TRUE;

            /*  Check if the tile has changed after the current stamp.  */
            if ((testStamps[nextTestUnit] > 0) &&
                (currentTile != testQueue[nextTestUnit][nextTest[nextTestUnit]][0]->getTileID()))
            {
                /*  Skip to the next unit z tested queue for fragments to interpolate.  */
                nextTestUnit = GPU_MOD(nextTestUnit + 1, numStampUnits);
                visited++;
            }

            /*  Search for a z tested queue with stamps.  */
            for(; (visited < numStampUnits) && (allTestStamps > 0) &&
                ((testStamps[nextTestUnit] == 0) || (freeInt[nextTestUnit] == 0)); visited++)
            {
                nextTestUnit = GPU_MOD(nextTestUnit + 1, numStampUnits);
            }
        }

	numStampsToInt->incavg(i);
	globalNumStampsToInt->incavg(i);

        /*  Check if a stamp was sent to the interpolator.  */
        if (sentStamp)
            waitIntCycles = interpCycles;
    } else {
	waitIntStalls->inc();
	globalWaitIntStalls->inc();
    }
}

/*  Sends stamps to early z test from rasterizer queue.  */
void FragmentFIFO::startEarlyZ(u64bit cycle)
{
    u32bit unit;
    u32bit i;
    u32bit j;
    u32bit numZSTUnitsHaveNoStamps;

    /*  Sends rasterized stamps to all Z Stencil Test units.  */
    for(unit = 0; unit < numStampUnits; unit++)
    {
//printf("FF %lld => startEarlyZ rastStamps[%d] = %d zstState[%d] = %d stampsPerUnit %d\n",
//    cycle, unit, rastStamps[unit], unit, zstState[unit], stampsPerUnit);

	if (rastStamps[unit] == 0 && zstState[unit] == ROP_READY)
	    numZSTUnitsHaveNoStamps++;

        /*  Send n stamps to a Z Stencil Test unit.  */
        for(i = 0; (rastStamps[unit] > 0) && (zstState[unit] == ROP_READY) && (i < stampsPerUnit); i++)
        {
            GPU_DEBUG_BOX(
                printf("FragmentFIFO => Sending rasterized stamp for unit %d at %d to Z Stencil Test unit %d.\n",
                    unit, nextRast[unit], unit);
            )

            /*  Send stamp to Z Stencil Test.  */
            for(j = 0; j < STAMP_FRAGMENTS; j++)
            {
                /*  Send fragment to Z Stencil Test.  */
                zStencilInput[unit]->write(cycle, rastQueue[unit][nextRast[unit]][j]);

	        FragmentInput* frInput = rastQueue[unit][nextRast[unit]][j];
	        if (frInput->getFragment() && frInput->getDebug()) {
	            char filename[32];
	            sprintf(filename, "debugZSTIn%d.txt", unit);
	            FILE *debug = fopen(filename, "a+");
	            fprintf(debug, "GPU[%d] cycle %lld ZST earlyZ input (tri = %d tile = (%d, %d), x = %d, y = %d, z = %d) unit = %d entry = %d culled = %s\n",
	            	gpuId, cycle, frInput->getTriangleID(), frInput->getTileID().getX(), frInput->getTileID().getY(),
	            	frInput->getFragment()->getX(), frInput->getFragment()->getY(), frInput->getFragment()->getZ(),
	        	unit, nextRast[unit],
	            	frInput->isCulled() ? "T" : "F");
	            QuadFloat* attributes = frInput->getAttributes();
	            for (u32bit index = 0; attributes && index < MAX_FRAGMENT_ATTRIBUTES; index++) {
                        fprintf(debug, "attrib[%d] = { %f, %f, %f, %f }\n", index,
	                        attributes[index][0], attributes[index][1],
                                attributes[index][2], attributes[index][3]);
	            }
	            fflush(debug);
	            fclose(debug);
	        }

                /*  Update statistics.  */
                //outputs->inc();
            }
            
            //  Update the last cycle an input was sent to ZStencilTest.
            lastCycleZSTIn[unit] = cycle;

            /*  Update pointer to next rasterized stamp.  */
            nextRast[unit] = GPU_MOD(nextRast[unit] + 1, rastQueueSz);

            /*  Update number of free entries in the rasterized stamp queue.  */
            freeRast[unit]++;

            /*  Update number of rasterized stamps.  */
            rastStamps[unit]--;

            /*  Update global number of rasterized stamps.  */
            allRastStamps--;
        }

	numRastStampsToZSTUnit->incavg(i);
	globalNumRastStampsToZSTUnit->incavg(i);
    }

    numZSTUnitsSendRastStampsTo->incavg(numStampUnits - numZSTUnitsHaveNoStamps);
    globalNumZSTUnitsSendRastStampsTo->incavg(numStampUnits - numZSTUnitsHaveNoStamps);
}

/*  Receive stamps from early z test.  */
void FragmentFIFO::endEarlyZ(u64bit cycle)
{
    FragmentInput *frInput;
    bool receivedFragment;
    bool cullStamp;
    u32bit unit;
    u32bit i;
    u32bit j;
    u32bit numStamps;
    u32bit numZSTUnitsHaveNoStamps;

    u32bit cloneFrom;
    Fragment *fr = NULL;
    QuadFloat *attrib = NULL;
    Fragment *clonedFr = NULL;
    FragmentInput *clonedFrInput = NULL;

    /*  Receive rasterized stamps from all Z Stencil Test units.  */
    for(unit = 0; unit < numStampUnits; unit++)
    {
	numStamps = 0;

        /*  Receive n stamps from a Z Stencil Test unit.  */
        for(i = 0;  i < stampsPerUnit; i++)
        {
            /*  Reset received fragment flag.  */
            receivedFragment = TRUE;

            /*  Receive fragments in a stamp.  */
            for(j = 0; (j < STAMP_FRAGMENTS) && receivedFragment; j++)
            {
                /*  Get fragment from Z Stencil Test.  */
                receivedFragment = zStencilOutput[unit]->read(cycle, (DynamicObject *&) frInput);

                /*  Check if a fragment has been received.  */
                if (receivedFragment)
                {
                    /*  Store fragment in the current stamp.  */
                    testQueue[unit][nextFreeTest[unit]][j] = frInput;
		    
		    if (frInput->getFragment() && frInput->getDebug()) {
		        char filename[32];
		        sprintf(filename, "debugZSTOut%d.txt", unit);
		        FILE *debug = fopen(filename, "a+");
		        fprintf(debug, "GPU[%d] cycle %lld ZST results (tri = %d tile = (%d, %d), x = %d, y = %d, z = %d) unit = %d entry = %d culled = %s\n",
		        	gpuId, cycle, frInput->getTriangleID(), frInput->getTileID().getX(), frInput->getTileID().getY(),
		        	frInput->getFragment()->getX(), frInput->getFragment()->getY(), frInput->getFragment()->getZ(),
		        	unit, nextFreeTest[unit],
		        	frInput->isCulled() ? "T" : "F");
		        QuadFloat* attributes = frInput->getAttributes();
	                for (u32bit index = 0; attributes && index < MAX_FRAGMENT_ATTRIBUTES; index++) {
                            fprintf(debug, "attrib[%d] = { %f, %f, %f, %f }\n", index,
	                            attributes[index][0], attributes[index][1],
                                    attributes[index][2], attributes[index][3]);
	                }
		        fflush(debug);
		        fclose(debug);
		    }
                }
            }

            /*  Check if a whole stamp has been received.  */
            GPU_ASSERT(
                if (!receivedFragment && (j > 1))
                    panic("FragmentFIFO", "endEarlyZ", "Missing fragments in a stamp.");
            )

            /*  Check if a stamp has been received.  */
            if (receivedFragment)
            {
		GPU_ASSERT(
		    if (testQueue[unit][nextFreeTest[unit]][0]->getType() != FRAG_NORMAL &&
		        testQueue[unit][nextFreeTest[unit]][0]->getType() != FRAG_COMP_IN)
                        panic(getName(), "endEarlyZ", "invalid fragment type");
		)

                /*  Check if last fragment received.  */
                if (testQueue[unit][nextFreeTest[unit]][0]->getFragment() == NULL)
                {
                    GPU_ASSERT(
                        if (freeTest == 0)
                            panic("FragmentFIFO", "endEarlyZ", "Early Z tested stamp queue is full.");
                    )

                    GPU_DEBUG_BOX(
                        printf("FragmentFIFO => Receive early z tested stamp from unit %d at Z Stencil Test unit to be stored at %d.\n",
                            unit, nextFreeTest[unit]);
                    )

                    /*  Update early z tested queue free entry pointer.  */
                    nextFreeTest[unit] = GPU_MOD(nextFreeTest[unit] + 1, testQueueSz);

                    /*  Update early z tested queue counter.  */
                    testStamps[unit]++;

                    /*  Update globlar z tested stamps counters.  */
                    allTestStamps++;

                    /*  Update number of free entries in the early z tested stamp queue.  */
                    freeTest[unit]--;
                }
                else
                {
                    /*  Determine if the stamp must be culled.  */
                    for(j = 0, cullStamp = TRUE; j < STAMP_FRAGMENTS; j++)
                        cullStamp = cullStamp && testQueue[unit][nextFreeTest[unit]][j]->isCulled();

	            if (numGPUs > 1 && multiGPUExecMode == SORT_LAST && compMode &&
		        testQueue[unit][nextFreeTest[unit]][0]->getType() == FRAG_NORMAL &&
		 	dummyFragsGenPossibility > 0) {

			for (j = 0; j < STAMP_FRAGMENTS; j++) {
			    if (testQueue[unit][nextFreeTest[unit]][j]->isCulled() && (rand() % 100)/100.0 < dummyFragsGenPossibility) {
			        testQueue[unit][nextFreeTest[unit]][j]->setCull(false);
			        testQueue[unit][nextFreeTest[unit]][j]->setDummyGenAfterZTest(true);

			        numDummyFrags->inc();
			        globalNumDummyFrags->inc();

				cullStamp = false;
			    }
			}
		    }

                    /*  Check if the stamp is culled.  */
                    if (cullStamp)
                    {
			if (testQueue[unit][nextFreeTest[unit]][0]->getType() == FRAG_NORMAL) {
			    numFragsNotPassZTest->inc(STAMP_FRAGMENTS); 
			    globalNumFragsNotPassZTest->inc(STAMP_FRAGMENTS);
			    if (earlyZ) {
			        numFragsNotPassZTestEarlyZ->inc(STAMP_FRAGMENTS); 
			        globalNumFragsNotPassZTestEarlyZ->inc(STAMP_FRAGMENTS);
			    }

			    if (numGPUs > 1 && multiGPUExecMode == SORT_LAST && compMode) {
			        numFragsNotPassZTestInCompMode->inc(STAMP_FRAGMENTS);
			        globalNumFragsNotPassZTestInCompMode->inc(STAMP_FRAGMENTS);
			        if (earlyZ) {
			            numFragsNotPassZTestEarlyZInCompMode->inc(STAMP_FRAGMENTS); 
			            globalNumFragsNotPassZTestEarlyZInCompMode->inc(STAMP_FRAGMENTS);
			        }
			    }
			}

                        /*  Delete the stamp.  */
                        for(j = 0; j < STAMP_FRAGMENTS; j++)
                        {
                            /*  Delete attributes of culled stamps.  */
                            if (!earlyZ || testQueue[unit][nextFreeTest[unit]][j]->getType() == FRAG_COMP_IN)
                            {
                                QuadFloat *attributes;

                                /*  Get the pointer to the fragment attribute array.  */
                                attributes = testQueue[unit][nextFreeTest[unit]][j]->getAttributes();

                                /*  If attributes were allocated for the fragment delete them.  */
                                if (attributes != NULL)
                                    delete[] attributes;
                            }

                            delete testQueue[unit][nextFreeTest[unit]][j]->getFragment();
                            delete testQueue[unit][nextFreeTest[unit]][j];
                        }
                    }
                    else
                    {
                        GPU_ASSERT(
                            if (freeTest[unit] == 0)
                                panic("FragmentFIFO", "endEarlyZ", "Early Z tested stamp queue is full.");
                        )

                        GPU_DEBUG_BOX(
                            printf("FragmentFIFO => Receive early z tested stamp from Z Stencil Test unit %d to be stored at %d.\n",
                                unit, nextFreeTest[unit]);
                        )

			if (testQueue[unit][nextFreeTest[unit]][0]->getType() == FRAG_NORMAL) {
                            for(j = 0; j < STAMP_FRAGMENTS; j++) {
		                if (!testQueue[unit][nextFreeTest[unit]][j]->isCulled()) {
			            numFragsPassZTest->inc();
			            globalNumFragsPassZTest->inc();
			            if (earlyZ) {
			                numFragsPassZTestEarlyZ->inc(); 
			                globalNumFragsPassZTestEarlyZ->inc();
			            }

			            if (numGPUs > 1 && multiGPUExecMode == SORT_LAST && compMode) {
					numFragsPassZTestInCompMode->inc();
					globalNumFragsPassZTestInCompMode->inc();
			                if (earlyZ) {
			                    numFragsPassZTestEarlyZInCompMode->inc(); 
			                    globalNumFragsPassZTestEarlyZInCompMode->inc();
			                }
				    }
		                } else {
			            numFragsNotPassZTest->inc();
			            globalNumFragsNotPassZTest->inc();
			            if (earlyZ) {
			                numFragsNotPassZTestEarlyZ->inc(); 
			                globalNumFragsNotPassZTestEarlyZ->inc();
			            }

			            if (numGPUs > 1 && multiGPUExecMode == SORT_LAST && compMode) {
					numFragsNotPassZTestInCompMode->inc();
					globalNumFragsNotPassZTestInCompMode->inc();
			                if (earlyZ) {
			                    numFragsNotPassZTestEarlyZInCompMode->inc(); 
			                    globalNumFragsNotPassZTestEarlyZInCompMode->inc();
			                }
				    }
				}
			    }

			    //if (numGPUs > 1 && multiGPUExecMode == SORT_LAST && compMode && freeTest[unit] > 1 &&
			    //    dummyFragsGenPossibility > 0 && (rand() % 100)/100.0 < dummyFragsGenPossibility) {

			    //    cloneFrom = nextFreeTest[unit];

			    //	nextFreeTest[unit] = GPU_MOD(nextFreeTest[unit] + 1, testQueueSz);
			    //	testStamps[unit]++;
			    //	allTestStamps++;
			    //	freeTest[unit]--;
			    //    
			    //    for (j = 0 ; j < STAMP_FRAGMENTS; j++) {
			    //        frInput = testQueue[unit][cloneFrom][j];
			    //        fr = frInput->getFragment();
			    //        if (frInput->getAttributes()) {
			    //            attrib = new QuadFloat[MAX_FRAGMENT_ATTRIBUTES];
			    //            memcpy(attrib, frInput->getAttributes(), sizeof(QuadFloat)*MAX_FRAGMENT_ATTRIBUTES);
			    //        }

			    //        clonedFr = new Fragment(fr->getTriangle(), fr->getX(), fr->getY(), fr->getZ(), fr->getCoordinates(), fr->isInsideTriangle());
			    //	    clonedFrInput = new FragmentInput(frInput->getTriangleID(), frInput->getSetupTriangle(),
			    //    		                      clonedFr, frInput->getTileID(), frInput->getStampUnit());
			    //        clonedFrInput->setAttributes(attrib);
			    //        clonedFrInput->setDummyGenAfterZTest(true);
			    //	    testQueue[unit][nextFreeTest[unit]][j] = clonedFrInput;

			    //        if (!clonedFrInput->isCulled()) {
			    //	        numDummyFrags->inc();
			    //	        globalNumDummyFrags->inc();

			    //	        numFragsPassZTest->inc();
			    //	        globalNumFragsPassZTest->inc();
			    //        }
			    //    }
			    //}
			}

                        /*  Update early z tested queue free entry pointer.  */
                        nextFreeTest[unit] = GPU_MOD(nextFreeTest[unit] + 1, testQueueSz);

                        /*  Update early z tested queue counter.  */
                        testStamps[unit]++;

                        /*  Update number of z tested stamps.  */
                        allTestStamps++;

                        /*  Update number of free entries in the early z tested stamp queue.  */
                        freeTest[unit]--;
                    }
                }

		numStamps++;
            }
        }

	if (numStamps == 0)
	    numZSTUnitsHaveNoStamps++;

	numStampsFromZSTUnit->incavg(numStamps);
	globalNumStampsFromZSTUnit->incavg(numStamps);
    }

    numZSTUnitsReceiveStampsFrom->incavg(numStampUnits - numZSTUnitsHaveNoStamps);
    globalNumZSTUnitsReceiveStampsFrom->incavg(numStampUnits - numZSTUnitsHaveNoStamps);
}

/*  Shades stamps.  */
void FragmentFIFO::shadeStamps(u64bit cycle)
{
    u32bit i;
    u32bit j;
    u32bit k;
    ShaderInput *shInput;
    FragmentInput *frInput;
    u32bit unit;
    u32bit visitedSU;
    u32bit visitedSH;
    bool freeShadedQ;
    bool lastStamp;
    bool addPadding;
    QuadFloat *lastStampAttribs[4] = { NULL, NULL, NULL, NULL };
    QuadFloat *paddingAttributes;

    /*  Reset number of visited shader queues.  */
    visitedSH = 0;
    visitedSU = 0;

    /*  Search for a interpolated queue with enough interpolated stamps and
        with enough free entries in the corresponding shaded stamp queue.  */
    for(; (visitedSU < numStampUnits) && (((intStamps[nextIntUnit] < stampsPerGroup) &&
        (!(lastStampInterpolated[nextIntUnit] && intStamps[nextIntUnit] > 0)))
        || (freeShaded[nextIntUnit] < stampsPerGroup));
        visitedSU++)
    {
        /*  Skip to the next interpolated stamp queue.  */
        nextIntUnit = GPU_MOD(nextIntUnit + 1, numStampUnits);
    }

    /*  Search for a shader input queue with empty entries.  */
    //for(; (visitedSH < numFShaders) && (numFreeShInputs[nextFreeShInQ] < threadGroup);
    //    visitedSH++)
    //{
    //    nextFreeShInQ = GPU_MOD(nextFreeShInQ + 1, numFShaders);
    //}

    /*  Check if tiled distribution of fragments to the shader units is enabled.  */
    if (tiledShDistro && (intStamps[nextIntUnit] > 0))
    {
        /*  Get the shader unit for the shader unit assigned to the fragment stamp.  */
        nextFreeShInQ = intQueue[nextIntUnit][nextInt[nextIntUnit]][0]->getShaderUnit();
    }

    /*  Send interpolated fragments to the shader.  */
    for(; (visitedSU < numStampUnits) && ((intStamps[nextIntUnit] >= stampsPerGroup) ||
        (lastStampInterpolated[nextIntUnit] && intStamps[nextIntUnit] > 0)) &&
        (freeShaded[nextIntUnit] >= stampsPerGroup) && (numFreeShInputs[nextFreeShInQ] >= threadGroup);)
    {
        /*  Retrieve unit for the whole thread group (use first fragment).  */
        unit = intQueue[nextIntUnit][nextInt[nextIntUnit]][0]->getStampUnit();

        /*  Check unit.  */
        GPU_ASSERT(
            if (unit != nextIntUnit)
                panic("FragmentFIFO", "shadeStamps", "Trying to shade a stamp from a different unit.");
        )

        /*  Store a whole thread group to the shader input queue.  */
        for(lastStamp = false, addPadding = false, j = 0; (j < stampsPerGroup) &&
            ((!lastStamp) || addPadding); j++)
        {
            /*  Store a stamp in the shader input queue.  */
            for(k = 0; k < STAMP_FRAGMENTS; k++)
            {
                /*  Check for last stamp in the interpolated stamp queue.  */
                lastStamp |= ((k == 0) && (intQueue[nextIntUnit][nextInt[nextIntUnit]][k]->getFragment() == NULL));

                /*  Check if last stamp isn't the first stamp in the group.  */
                addPadding |= (lastStamp && j > 0);
                //addPadding = lastStamp;

                /*  Check if the current stamps is the last one.  */
                if (addPadding)
                {
                    /*  Create a fake shader input to fill the thread group.  */

                    GPU_DEBUG_BOX(
                        printf("FragmentFIFO => Creating fake shader input for padding.\n");
                    )

                    /*  Create attributes for fake fragment.  */
                    paddingAttributes = new QuadFloat[MAX_FRAGMENT_ATTRIBUTES];

                    if (lastStampAttribs[k] != NULL)
                    {
                        /*  Copy attribute values from previous stamp.  */
                        memcpy(paddingAttributes, lastStampAttribs[k], sizeof(QuadFloat) * MAX_FRAGMENT_ATTRIBUTES);
                    }
                    else
                    {
                        memset(paddingAttributes, 0, sizeof(QuadFloat) * MAX_FRAGMENT_ATTRIBUTES);
                    }

                    /*  Create fake fragment.  */
                    shInput = new ShaderInput(0, numStampUnits, 0,
                        paddingAttributes, SHIM_FRAGMENT);

                    GPU_TEX_TRACE(
                        for(int ii = 0; ii < 2; ii++)
                            fragTrace << u32bit(paddingAttributes[POSITION_ATTRIBUTE][ii]) << " ";
                        fragTrace << "1 " << nextFreeShInQ << endl;
                    )

                    /*  Set as killed (fake input, ignore when received).  */
                    shInput->setKilled();

                    /*  Set shader input as fragment.  */
                    shInput->setAsFragment();

                    /*  Copy cookies.  */
                    shInput->copyParentCookies(*intQueue[nextIntUnit][nextInt[nextIntUnit]][k]);
                }
                else if (!lastStamp)
                {

                    GPU_TEX_TRACE(
                        QuadFloat *attr;
                        attr = intQueue[nextIntUnit][nextInt[nextIntUnit]][k]->getAttributes();
                        for(int ii = 0; ii < 2; ii++)
                            fragTrace << u32bit(attr[POSITION_ATTRIBUTE][ii]) << " ";
                        fragTrace << intQueue[nextIntUnit][nextInt[nextIntUnit]][k]->isCulled() << " " << nextFreeShInQ << endl;
                    )

                    /*  Create shader input object.  */
                    //shInput = new ShaderInput(fragmentCounter, nextIntUnit, nextFreeSh[nextIntUnit],
                    //    intQueue[nextIntUnit][nextInt[nextIntUnit]][k]->getAttributes());
                    u32bit fragTriangleID = intQueue[nextIntUnit][nextInt[nextIntUnit]][k]->getTriangleID();
                    u32bit fragX = intQueue[nextIntUnit][nextInt[nextIntUnit]][k]->getFragment()->getX();
                    u32bit fragY = intQueue[nextIntUnit][nextInt[nextIntUnit]][k]->getFragment()->getY();
                    bool fragDebug = intQueue[nextIntUnit][nextInt[nextIntUnit]][k]->getDebug();
                    shInput = new ShaderInput(ShaderInputID(fragTriangleID, fragX, fragY), nextIntUnit, nextFreeSh[nextIntUnit],
                        intQueue[nextIntUnit][nextInt[nextIntUnit]][k]->getAttributes());
		    if (fragDebug) shInput->setDebug(true);

		    shInput->setBatchCounter(intQueue[nextIntUnit][nextInt[nextIntUnit]][k]->getBatchCounter());
		    shInput->setFrameCounter(intQueue[nextIntUnit][nextInt[nextIntUnit]][k]->getFrameCounter());

                    /*  Copy cookies.  */
                    shInput->copyParentCookies(*intQueue[nextIntUnit][nextInt[nextIntUnit]][k]);

                    /*  Set shader input as fragment.  */
                    shInput->setAsFragment();

                    /*  Store fragment in the propper shader queue.  */
                    shQueue[nextIntUnit][nextFreeSh[nextIntUnit]][k] = intQueue[nextIntUnit][nextInt[nextIntUnit]][k];

                    /*  Keep the pointers to the attributes for the last stamp queue in the shader queue.  */
                    lastStampAttribs[k] = intQueue[nextIntUnit][nextInt[nextIntUnit]][k]->getAttributes();
                }

                /*  Check for the last fragment sent to the shader.  */
                //if (lastStamp && (j == (stampsPerGroup - 1)) && (k == (STAMP_FRAGMENTS - 1)))
                //{
                    /*  Mark the fragment as the last one to be sent to the shader.  */
                //    shInput->setLast(true);
                //}

                /*  Check if an input must be queued in the shader input queue.  */
                if (!lastStamp || addPadding)
                {
                    GPU_DEBUG_BOX(
                        printf("FragmentFIFO => Storing fragment into shader input queue %d position %d from interpolated queue %d position %d\n",
                            nextFreeShInQ, nextFreeShInput[nextFreeShInQ], nextIntUnit, nextInt[nextIntUnit]);
                    )

                    /*  Store shader input.  */
                    shaderInputQ[nextFreeShInQ][nextFreeShInput[nextFreeShInQ]] = shInput;

                    /*  Update pointer to the next free entry in the shader input queue.  */
                    nextFreeShInput[nextFreeShInQ] = GPU_MOD(nextFreeShInput[nextFreeShInQ] + 1, shInputQSize);
                }
            }

            /*  Check for last stamp, keep it until it can be sent to the shader.  */
            if (!lastStamp)
            {
                /*  Update pointer to the next interpolated stamp.  */
                nextInt[nextIntUnit] = GPU_MOD(nextInt[nextIntUnit] + 1, intQueueSz);

                /*  Update pointer to the next free shaded stamp queue entry.  */
                nextFreeSh[nextIntUnit] = GPU_MOD(nextFreeSh[nextIntUnit] + 1, shQueueSz);
            }
        }

        /*  Check for last stamp.   Add last stamp to the end of the shaded queue.  */
        if (lastStamp)
        {
            /*  Check last stamp isn't already queued in the shaded stamp queue.  */
            GPU_ASSERT(
                if (lastShaded[nextIntUnit])
                    panic("FragmentFIFO", "shadeStamps", "Trying to queue again the last stamp into the shaded stamp queue.");
            )

            /*  Copy last stamp to the unit shaded stamp queue.  */
            for(k = 0; k < STAMP_FRAGMENTS; k++)
            {
                /*  Move last stamp to shaded stamp queue.  */
                frInput = intQueue[nextIntUnit][nextInt[nextIntUnit]][k];
                shQueue[nextIntUnit][nextFreeSh[nextIntUnit]][k] = frInput;
            }

            /*  Set shaded queue entry as shaded.  */
            shaded[nextIntUnit][nextFreeSh[nextIntUnit]] = TRUE;

            /*  Update global number of interpolated stamps.  */
            allIntStamps -= intStamps[nextIntUnit];

            /*  Update number of free interpolated stamp entries.  */
            freeInt[nextIntUnit] += intStamps[nextIntUnit];

            /*  Update number of free shaded stamp entries.  */
            freeShaded[nextIntUnit] -= intStamps[nextIntUnit];

            /*  Update number of shaded stamps.  */
            shadedStamps[nextIntUnit] += intStamps[nextIntUnit];

            /*  Update number of interpolated stamps.  */
            intStamps[nextIntUnit] = 0;

            /*  Update pointer to the next interpolated stamp.  */
            nextInt[nextIntUnit] = GPU_MOD(nextInt[nextIntUnit] + 1, intQueueSz);

            /*  Update pointer to the next free shaded stamp queue entry.  */
            nextFreeSh[nextIntUnit] = GPU_MOD(nextFreeSh[nextIntUnit] + 1, shQueueSz);

            /*  Set shaded queue last stamp queued flag.  */
            lastShaded[nextIntUnit] = TRUE;
        }
        else
        {
            /*  Update number of interpolated stamps.  */
            intStamps[nextIntUnit] -= stampsPerGroup;

            /*  Update global number of interpolated stamps.  */
            allIntStamps -= stampsPerGroup;

            /*  Update number of free interpolated stamp entries.  */
            freeInt[nextIntUnit] += stampsPerGroup;

            /*  Update number of shaded stamps.  */
            shadedStamps[nextIntUnit] += stampsPerGroup;

            /*  Update number of free shaded stamp entries.  */
            freeShaded[nextIntUnit] -=stampsPerGroup;
        }

        /*  Check if a thread group was sent.  */
        if (!lastStamp || addPadding)
        {
            /*  Update number of free entries in the shader input queue.  */
            numFreeShInputs[nextFreeShInQ] -= threadGroup;

            /*  Update number of shader inputs in the queue.  */
            numShaderInputs[nextFreeShInQ] += threadGroup;

            /*  Update number of fragments sent to the shader.  */
            inputFragments += threadGroup;

            /*  Update number of batched shader inputs for the shader unit.  */
            batchedShInputs[nextFreeShInQ] += threadGroup;
        }

        /*  Skip to the next interpolated stamp queue.  */
        if (tiledShDistro)
        {
            nextIntUnit = GPU_MOD(nextIntUnit + 1, numStampUnits);
            visitedSU++;
        }

        /*  Search for a interpolated queue with enough interpolated stamps and
            with enough free entries in the corresponding shaded stamp queue.  */
        for(; (visitedSU < numStampUnits) && (((intStamps[nextIntUnit] < stampsPerGroup) &&
            (!(lastStampInterpolated[nextIntUnit] && intStamps[nextIntUnit] > 0))) ||
            (freeShaded[nextIntUnit] < stampsPerGroup));
            visitedSU++)
        {
            /*  Skip to the next interpolated stamp queue.  */
            nextIntUnit = GPU_MOD(nextIntUnit + 1, numStampUnits);
        }

        /*  Check if tiled distribution of fragments to the shader units is enabled.  */
        if (tiledShDistro && (intStamps[nextIntUnit] > 0))
        {
            /*  Get the shader unit for the shader unit assigned to the fragment stamp.  */
            nextFreeShInQ = intQueue[nextIntUnit][nextInt[nextIntUnit]][0]->getShaderUnit();
        }
        else
        {
            /*  Check if a whole shader input batch has been assigned to the current unit.  */
            if (batchedShInputs[nextFreeShInQ] >= shInputBatchSize)
            {
                /*  Reset current unit shader input batch counter.  */
                batchedShInputs[nextFreeShInQ] = 0;

                /*  Assign a batch to the next shader unit batch.  */
                nextFreeShInQ = GPU_MOD(nextFreeShInQ + 1, numFShaders);
            }
        }

        /*  Check if the stamp unit for the next thread group has changed.  */
        //if ((intStamps[nextIntUnit] > 0) &&
        //    (unit != intQueue[nextIntUnit][nextInt[nextIntUnit]][0]->getStampUnit()))
        //{
        //    /*  Skip to the next shader.  */
        //    nextFreeShInQ = GPU_MOD(nextFreeShInQ + 1, numFShaders);
        //    visitedSH++;
        //}

        ///*  Search for a shader input queue with empty entries.  */
        //for(; (visitedSH < numFShaders) && (numFreeShInputs[nextFreeShInQ] < threadGroup);
        //    visitedSH++)
        //{
        //    nextFreeShInQ = GPU_MOD(nextFreeShInQ + 1, numFShaders);
        //}
    }
}

/*  Receives shaded outputs from the shaders.  */
void FragmentFIFO::receiveShaderOutput(u64bit cycle)
{
    u32bit i;
    u32bit j;
    bool outputFromShader;
    ShaderInput *shOutput;
    ShaderInputMode outputMode;
    u32bit numOutputs;

    /*  Receive shaded fragments from the shaders.  */
    for(i = 0; i < numFShaders; i++)
    {
        outputFromShader = true;
        numOutputs = 0;

        /*  Receive fragments from a shader.  */
        //for(j = 0, outputFromShader = TRUE; (j < shOutputsCycle) && outputFromShader; j++)
        //{
            while(shaderOutput[i]->read(cycle, (DynamicObject *&) shOutput))
            {
                ///*  Determine if it is a vertex or a fragment output.  */
                //if (j == 0)
                //{
                    /*  Get type of shader output for the would group/stamp.  */
                    outputMode = shOutput->getInputMode();
                //}

                /*  Check that type does not change in the middle of a group.  */
                //GPU_ASSERT(
                //    if ((!unifiedModel) && (outputMode != SHIM_FRAGMENT))
                //        panic("FragmentFIFO", "receiveShaderOutput", "Non fragment shader output for non unified shader architecture.");
                //    if ((j > 0) && (outputMode != shOutput->getInputMode()))
                //        panic("FragmentFIFO", "receiveShaderOutput", "Shader output type changed.");
                //)

                GPU_DEBUG_BOX(
                    printf("FragmentFIFO => Received shader output type %s from shader unit %d to be stored at output queue entry %d\n",
                        (outputMode == SHIM_FRAGMENT)?"F":((outputMode == SHIM_VERTEX)?"V":"F"), i, nextFreeShOutput[i]);
                )
                
                //  Update last cycle shader output was received.
                lastCycleShOutput[i] = cycle;

                //  Update the number of shader processing elements in the shader.
                shaderElements[i]--;
            
                /*  Store shader output in the queue.  */
                shaderOutputQ[i][nextFreeShOutput[i]] = shOutput;

		if (shOutput->getDebug()) {
		    char filename[32];
		    sprintf(filename, "debugShOut%d.txt", i);
	            FILE * debug = fopen(filename, "a+");
	            fprintf(debug, "GPU[%d] cycle %lld receiveShaderOutputs (triID = %d, fragX = %d, fragY = %d) shader = %d unit = %d entry = %d killed = %s\n",
	                    gpuId, cycle,
			    shaderOutputQ[i][nextFreeShOutput[i]]->getShaderInputID().id.fragmentID.triangle,
	            	    shaderOutputQ[i][nextFreeShOutput[i]]->getShaderInputID().id.fragmentID.x,
	                    shaderOutputQ[i][nextFreeShOutput[i]]->getShaderInputID().id.fragmentID.y,
			    i,
			    shaderOutputQ[i][nextFreeShOutput[i]]->getUnit(),
			    shaderOutputQ[i][nextFreeShOutput[i]]->getEntry(),
			    shaderOutputQ[i][nextFreeShOutput[i]]->getKill() ? "T" : "F");
	            QuadFloat* attributes = shaderOutputQ[i][nextFreeShOutput[i]]->getAttributes();
	            for (u32bit index = 0; index < MAX_FRAGMENT_ATTRIBUTES; index++) {
                        fprintf(debug, "attrib[%d] = { %f, %f, %f, %f }\n", index,
	                        attributes[index][0], attributes[index][1],
                                attributes[index][2], attributes[index][3]);
	            }
	            fflush(debug);
	            fclose(debug);
	        }
                
		/*  Update pointer to the next free shader output queue entry.  */
                nextFreeShOutput[i] = GPU_MOD(nextFreeShOutput[i] + 1, shOutputQSize);

                /*  Update number of outputs received.  */
                numOutputs++;
            }
        //    else
        //    {
        //        /*  Check if first fragment in a stamp.  */
        //        if (j == 0)
        //        {
        //            /*  No shaded fragments expected from this shader this cycle.  */
        //            outputFromShader = FALSE;
        //        }
        //        else
        //        {
        //            panic("FragmentFIFO", "receiveShaderOutput", "Missing shaded output in group from shader.");
        //        }
        //    }
        //}

        /*  Check if there was output from this shader.  */
        if (outputFromShader)
        {
            /*  Update number of outputs in the shader queue.  */
            numShaderOutputs[i] += numOutputs;

            GPU_ASSERT(
                if (numShaderOutputs[i] > shOutputQSize)
                {
printf("FF %lld => numShaderOutput[%d] = %d | shOutputQSz %d \n", cycle, i,   numShaderOutputs[i], shOutputQSize);
                    panic("FragmentFIFO", "receiveShaderOutput", "Shader output queue overflow.");
                }
            )

            /*  Update number of free entries in the shader output queue. */
            numFreeShOutputs[i] -= shOutputsCycle;
        }
    }
}

/*  Distributes the shader outputs to the propper shaded (vertex, triangle or fragment) queues.  */
void FragmentFIFO::distributeShaderOutput(u64bit cycle)
{
    ShaderInput *shOutput;
    ShaderInputMode outputMode;
    u32bit shadedEntry;
    u32bit shadedUnit;
    bool culled;
    u32bit i;
    u32bit j;

    /*  Search for the next shader output queue with outputs.  */
    //for(i = 0; (i < numFShaders) && (numShaderOutputs[nextProcessShOutQ] == 0); i++)
    //    nextProcessShOutQ = GPU_MOD(nextProcessShOutQ + 1, numFShaders);

    /*  Process shader outputs in each shader queue.  */
    for(i = 0; i < numFShaders; i++)
    {
        /*  Check if there is any output for this queue.  */
        if (numShaderOutputs[i] > 0)
        {
            /*  Get the input mode for the first output.  */
            shOutput = shaderOutputQ[i][nextShaderOutput[i]];
            outputMode = shOutput->getInputMode();

            /*  Check group shader output type.  */
            switch(outputMode)
            {
                case SHIM_FRAGMENT:

                    /*  Check if there is a stamp worth of fragment outputs.  */
                    while ((numShaderOutputs[i] >= STAMP_FRAGMENTS) && (outputMode == SHIM_FRAGMENT))
                    {
                        /*  Process a stamp of fragments.  */
                        for(j = 0; j < STAMP_FRAGMENTS; j++)
                        {
                            GPU_DEBUG_BOX(
                                printf("FragmentFIFO => Processing shaded fragment from output queue %d position %d to be stored at stamp unit queue %d position %d\n",
                                    i, nextShaderOutput[i], shOutput->getUnit(), shOutput->getEntry());
                            )

                            /*  Get the next shader output.  */
                            shOutput = shaderOutputQ[i][nextShaderOutput[i]];
                            outputMode = shOutput->getInputMode();

                            /*  Check that all the fragments received for a stamp go to the same stamp unit and
                                queue entry (same stamp!!).  All fragments in a stamp must end at the same time.  */
                            GPU_ASSERT(
                                if (j == 0)
                                {
                                    shadedEntry = shOutput->getEntry();
                                    shadedUnit = shOutput->getUnit();
                                }
                                else
                                    if ((shadedEntry != shOutput->getEntry()) || (shadedUnit != shOutput->getUnit()))
                                        panic("FragmentFIFO", "distributeShaderOutput", "Fragments outputs for the current stamp come from different stamps units.");
                                if (outputMode != SHIM_FRAGMENT)
                                    panic("FragmentFIFO", "distributeShaderOutput", "Non fragment shader output in the middle of a fragment stamp. ");
                            )

                            /*  Check of fake (padding) fragments.  */
                            if ((shadedUnit == numStampUnits) && (shadedEntry == 0))
                            {
                                GPU_DEBUG_BOX(
                                    printf("FragmentFIFO => Removing fake fragment ouput queue %d position %d\n",
                                        i, nextShaderOutput[i]);
                                )

                                /*  Delete fake fragment attributes.  */
                                delete[] shOutput->getAttributes();
                            }
                            else
                            {
                                /*  Set fragments as culled if the shader input was aborted/killed.  */
                                culled = shQueue[shadedUnit][shadedEntry][j]->isCulled() || shOutput->getKill();

                                //printf("FF => distributing fragment to shader unit %d entry %d in quad position %d culled %s killed %s final %s\n",
                                //shadedUnit, shadedEntry, j, shQueue[shadedUnit][shadedEntry][j]->isCulled()?"T":"F",
				//shOutput->getKill()?"T":"F",
                                //culled?"T":"F");
                                
                                /*if ((shQueue[shadedUnit][shadedEntry][j]->getFragment()->getX() == 281) &&
                                    (shQueue[shadedUnit][shadedEntry][j]->getFragment()->getY() == 472))
                                {
                                QuadFloat *attrib = shOutput->getAttributes();
                                printf("FFIFO (%lld) => Pixel (%d, %d) -> O<ShOutput>[1] = {%f, %f, %f, %f}\n", cycle,
                                    shQueue[shadedUnit][shadedEntry][j]->getFragment()->getX(),
                                    shQueue[shadedUnit][shadedEntry][j]->getFragment()->getY(),
                                    attrib[1][0], attrib[1][1], attrib[1][2], attrib[1][3]);
                                attrib = shQueue[shadedUnit][shadedEntry][j]->getAttributes();
                                printf("FFIFO (%lld) => Pixel (%d, %d) -> O<ShadedQ>[1] = {%f, %f, %f, %f}\n", cycle,
                                    shQueue[shadedUnit][shadedEntry][j]->getFragment()->getX(),
                                    shQueue[shadedUnit][shadedEntry][j]->getFragment()->getY(),
                                    attrib[1][0], attrib[1][1], attrib[1][2], attrib[1][3]);
                                }*/
                                //{
                                //    printf("FFIFO => Cull mask for fragment at (%d, %d) triID %d is %s (orig) %s (kill) %s (final)\n", 82, 890,
                                //        shQueue[shadedUnit][shadedEntry][j]->getTriangleID(),
                                //        shQueue[shadedUnit][shadedEntry][j]->isCulled() ? "T" : "F",
                                //        shOutput->getKill() ? "T" : "F",
                                //        culled ? "T" : "F");       
                                //}

                                /*  NOTE FRAGMENTS OUTPUT ATTRIBUTES ARE ALREADY COPIED BY THE SHADER INTO
                                    THE FRAGMENT INPUT ATTRIBUTE ARRAY.  */

                                /*  Set fragment cull flag.  */
                                shQueue[shadedUnit][shadedEntry][j]->setCull(culled);

                                /*  Set stamp as shaded.  */
                                shaded[shadedUnit][shadedEntry] = TRUE;

                                /*  Calculate and set the number of cycles the fragment spent in the shader unit.  */
                                shQueue[shadedUnit][shadedEntry][j]->setShaderLatency(
                                    (u32bit) (cycle - shQueue[shadedUnit][shadedEntry][j]->getStartCycleShader())
                                    );
                            }

                            /*  Update statistics.  */
                            shadedFrag->inc();
                            globalShadedFrag->inc();

                            /*  Update pointer to the next shader output to process.  */
                            nextShaderOutput[i] = GPU_MOD(nextShaderOutput[i] + 1, shOutputQSize);

                            /*  Delete shader output object.  */
                            delete shOutput;
                        }

                        /*  Update number of shader outputs remaining in the queue.  */
                        numFreeShOutputs[i] += STAMP_FRAGMENTS;

                        /*  Update the number of free entries in the shader output queue.  */
                        numShaderOutputs[i] -= STAMP_FRAGMENTS;

                        /*  Update number of received shaded fragments.  */
                        outputFragments += STAMP_FRAGMENTS;

                        /*  Get the next shader output.  */
                        if (numShaderOutputs[i] > 0)
                        {
                            /*  Get the next shader output.  */
                            shOutput = shaderOutputQ[i][nextShaderOutput[i]];
                            outputMode = shOutput->getInputMode();
                        }
                    }

                    break;

                case SHIM_TRIANGLE:

                    /*  Process all the consecutive triangle outputs in the shader output queue.  */
                    while ((numShaderOutputs[i] > 0) && (outputMode == SHIM_TRIANGLE))
                    {
                        /*  Check for triangle outputs used for shader group padding.  */
                        if (shOutput->getKill())
                        {
                            GPU_DEBUG_BOX(
                                printf("FragmentFIFO => Removing pad triangle output from shader output queue %d position %d.\n",
                                    i, nextShaderOutput[i]);
                            )

                            /*  Update number of free triangle output queue entries.  */
                            freeOutputTriangles++;

                            /*  Delete triangle attribute array.  */
                            delete[] shOutput->getAttributes();

                            /*  Delete shader input.  */
                            delete shOutput;
                        }
                        else
                        {
                            GPU_DEBUG_BOX(
                                printf("FragmentFIFO => Storing shaded triangle from shader output queue %d position %d into triangle queue position %d.\n",
                                    i, nextShaderOutput[i], nextFreeOutTriangle);
                            )

                            /*  Store triangle output in the triangle output queue.  */
                            triangleOutQueue[nextFreeOutTriangle] = shOutput;

                            /*  Update pointer to the next free triangle output queue entry.  */
                            nextFreeOutTriangle = GPU_MOD(nextFreeOutTriangle + 1, triangleOutQueueSz);

                            /*  Update number of triangle outputs.  */
                            outputTriangles++;
                        }

                        /*  Update statistics.  */
                        shTriangles->inc();
                        globalShTriangles->inc();

                        /*  Update number of shader outputs remaining in the queue.  */
                        numFreeShOutputs[i]++;

                        /*  Update the number of free entries in the shader output queue.  */
                        numShaderOutputs[i]--;

                        /*  Update pointer to the next shader output to process.  */
                        nextShaderOutput[i] = GPU_MOD(nextShaderOutput[i] + 1, shOutputQSize);

                        /*  Get the next shader output.  */
                        if (numShaderOutputs[i] > 0)
                        {
                            shOutput = shaderOutputQ[i][nextShaderOutput[i]];
                            outputMode = shOutput->getInputMode();
                        }
                    }

                    break;

                case SHIM_VERTEX:

                    /*  Vertex output.  */

                    /*  Process all the consecutive vertex outputs in the shader output queue.  */
                    while ((numShaderOutputs[i] > 0) && (outputMode == SHIM_VERTEX))
                    {
                        /*  Check if fake (killed) vertex input used to complete vertex input group.  */
                        if (shOutput->getKill() && (!shOutput->isLast()))
                        {
                            GPU_DEBUG_BOX(
                                printf("FragmentFIFO => Removing fake vertex from shader output queue %d position %d\n",
                                    i, nextShaderOutput[i]);
                            )

                            /*  Update number of free shaded vertices queue entries.  */
                            freeShVertices++;

                            /*  Delete vertex attribute array.  */
                            delete[] shOutput->getAttributes();

                            /*  Delete shader output.  */
                            delete shOutput;
                        }
                        else
                        {
                            GPU_DEBUG_BOX(
                                printf("FragmentFIFO => Storing shaded vertex from shader output queue %d position %d at vertex queue position %d\n",
                                    i, nextShaderOutput[i], nextFreeShVertex);
                            )

                            /*  Store vertex output in the shader vertex queue.  */
                            shadedVertexQueue[nextFreeShVertex] = shOutput;

                            /*  Update pointer to the next free shaded vertex queue entry.  */
                            nextFreeShVertex = GPU_MOD(nextFreeShVertex + 1, vShadedQueueSz);

                            /*  Update number of shaded vertices.  */
                            shadedVertices++;
                        }

                        /*  Update statistics.  */
                        shVerts->inc();
                        globalShVerts->inc();

                        /*  Update number of shader outputs remaining in the queue.  */
                        numFreeShOutputs[i]++;

                        /*  Update the number of free entries in the shader output queue.  */
                        numShaderOutputs[i]--;

                        /*  Update pointer to the next shader output to process.  */
                        nextShaderOutput[i] = GPU_MOD(nextShaderOutput[i] + 1, shOutputQSize);

                        /*  Get the next shader output.  */
                        if (numShaderOutputs[i] > 0)
                        {
                            shOutput = shaderOutputQ[i][nextShaderOutput[i]];
                            outputMode = shOutput->getInputMode();
                        }
                    }

                    break;

                default:

                    panic("FragmentFIFO", "receiveShaderOutput", "Undefined shader output mode.");
                    break;
            }
        }
    }

}

/*  Sends shader inputs to the shader units.  */
void FragmentFIFO::sendShaderInputs(u64bit cycle)
{
    u32bit i;
    u32bit j;
    u32bit k;
    u32bit frEntry;
    u32bit frUnit;

    /*  Send inputs to the shaders.  */
    for(i = 0; i < numFShaders; i++)
    {
        GPU_ASSERT(
            if (numShaderInputs[i] > shInputQSize)
                panic("FragmentFIFO", "sendShaderInputs", "Shader input queue overflow.");
        )

        /*  Sends inputs to a shader if inputs available.  */
        for(j = 0; (numShaderInputs[i] > 0) && (shState[i] != SH_BUSY) &&
            (j < shInputsCycle); j++)
        {
            GPU_DEBUG_BOX(
                printf("FragmentFIFO => Sending shader input for shader %d queue position %d\n",
                    i, nextShaderInput[i]);
            )

            /*  Send input to the shader unit.  */
            shaderInput[i]->write(cycle, shaderInputQ[i][nextShaderInput[i]]);

	    if (!shaderInputQ[i][nextShaderInput[i]]->getKill() &&
	        shaderInputQ[i][nextShaderInput[i]]->getDebug()) {
	        char filename[32];
	        sprintf(filename, "debugShIn%d.txt", i);
	        FILE * debug = fopen(filename, "a+");
	        fprintf(debug, "GPU[%d] cycle %lld sendShaderInputs (triID = %d, fragX = %d, fragY = %d) shader = %d unit = %d entry = %d killed = %s\n",
	                gpuId, cycle,
	        	shaderInputQ[i][nextShaderInput[i]]->getShaderInputID().id.fragmentID.triangle,
	        	shaderInputQ[i][nextShaderInput[i]]->getShaderInputID().id.fragmentID.x,
	                shaderInputQ[i][nextShaderInput[i]]->getShaderInputID().id.fragmentID.y,
	                i,
	        	shaderInputQ[i][nextShaderInput[i]]->getUnit(),
	        	shaderInputQ[i][nextShaderInput[i]]->getEntry(),
	        	shaderInputQ[i][nextShaderInput[i]]->getKill() ? "T" : "F");
	        QuadFloat* attributes = shaderInputQ[i][nextShaderInput[i]]->getAttributes();
	        for (u32bit index = 0; index < MAX_FRAGMENT_ATTRIBUTES; index++) {
                    fprintf(debug, "attrib[%d] = { %f, %f, %f, %f }\n", index,
	                    attributes[index][0], attributes[index][1],
                            attributes[index][2], attributes[index][3]);
	        }
	        fflush(debug);
	        fclose(debug);
	    }

            //  Update the cycle of the last shader input sent to the shader unit.
            lastCycleShInput[i] = cycle;
            
            //  Update the number of shader processing elements in the shader.
            shaderElements[i]++;
            
            /*  Check the shader input mode for fragments.  */
            if (shaderInputQ[i][nextShaderInput[i]]->getInputMode() == SHIM_FRAGMENT
                && !shaderInputQ[i][nextShaderInput[i]]->getKill())
            {
                /*  Get fragment entry and unit.  */
                frEntry = shaderInputQ[i][nextShaderInput[i]]->getEntry();
                frUnit = shaderInputQ[i][nextShaderInput[i]]->getUnit();

                /*  We assume that all the fragments in a stamp share the same start cycle.  */
                for(k = 0; k < STAMP_FRAGMENTS; k++)
                {
                    /*  Set the start cycle inside the shader.  */
                    shQueue[frUnit][frEntry][k]->setStartCycleShader(cycle);
                }
            }

            /*  Update pointer to the next shader input to send to the unit.  */
            nextShaderInput[i] = GPU_MOD(nextShaderInput[i] + 1, shInputQSize);

            /*  Update number of free shader input queue entries.  */
            numFreeShInputs[i]++;

            /*  Update number of shader inputs in the queue.  */
            numShaderInputs[i]--;
        }
    }
}


/*  Shades triangles.  */
void FragmentFIFO::shadeTriangles(u64bit cycle)
{
    u32bit i;
    ShaderInput *shInput;

    /*  Check if a group of input triangles is not complete.  */
    if ((inputTriangles < threadGroup) && (freeInputTriangles >= (threadGroup - inputTriangles)))
    {
        /*  Check the last batch triangle was received.  */
        GPU_ASSERT(
            if (!lastTriangle)
                panic("FragmentFIFO", "shadeTriangles", "Only last group of triangle inputs can be uncomplete.");
        )

        /*  Add fake triangle inputs.  */
        for(i = inputTriangles; i < threadGroup; i++)
        {
            GPU_DEBUG_BOX(
                printf("FragmentFIFO => Adding triangle for pading at position %d.\n", nextFreeInTriangle);
            )

            /*  Create fake shader input.  */
            shInput = new ShaderInput(0, 0, 0, new QuadFloat[MAX_TRIANGLE_ATTRIBUTES], SHIM_TRIANGLE);

            /*  Set as killed (fake input, ignore when received).  */
            shInput->setKilled();

            /*  Store input in the triangle input queue.  */
            triangleInQueue[nextFreeInTriangle] = shInput;

            /*  Update number of triangle inputs in the queue.  */
            inputTriangles++;

            /*  Update number of free triangle input queue entries.  */
            freeInputTriangles--;

            /*  Update pointer to the next free input vertex queue entry.  */
            nextFreeInTriangle = GPU_MOD(nextFreeInTriangle + 1, triangleInQueueSz);
        }

        /*  Unset last batch triangle flag.  */
        lastTriangle = FALSE;
    }

    /*  Search for the next shader input queue with enough free entries.  */
    //for(i = 0; (i < numFShaders) && (numFreeShInputs[nextFreeShInQ] < threadGroup); i++)
    //    nextFreeShInQ = GPU_MOD(nextFreeShInQ + 1, numFShaders);

    /*  Send input vertices to the shader.  */
    if((inputTriangles >= threadGroup) && (freeOutputTriangles >= threadGroup) &&
        (numFreeShInputs[nextFreeShInQ] >= threadGroup))
    {
        /*  Send the triangle input attributes of a group of triangle inputs to the shader.  */
        for(i = 0; i < threadGroup; i++)
        {
            GPU_DEBUG_BOX(
                printf("FragmentFIFO => Sending triangle input stored at %d to shader input queue %d position %d.\n",
                    nextInputTriangle, nextFreeShInQ, nextFreeShInput[nextFreeShInQ]);
            )

            /*  Send triangle input to the shader.  */
            shaderInputQ[nextFreeShInQ][nextFreeShInput[nextFreeShInQ]] = triangleInQueue[nextInputTriangle];

            /*  Update pointer to the next input triangle.  */
            nextInputTriangle = GPU_MOD(nextInputTriangle + 1, triangleInQueueSz);

            /*  Update pointer to the next free entry in the shader input queue.  */
            nextFreeShInput[nextFreeShInQ] = GPU_MOD(nextFreeShInput[nextFreeShInQ] + 1, shInputQSize);
        }

        /*  Update number of triangle inputs in the queue.  */
        inputTriangles -= threadGroup;

        /*  Update number of free triangle input queue entries.  */
        freeInputTriangles += threadGroup;

        /*  Update number of free triangle output queue entries.  */
        freeOutputTriangles -= threadGroup;

        /*  Update number of shader inputs to send to the shader.  */
        numShaderInputs[nextFreeShInQ] += threadGroup;

        /*  Update number of shader inputs assigned to the current shader unit batch.  */
        batchedShInputs[nextFreeShInQ] += threadGroup;

        /*  Update number of free entries in the shader input queue.  */
        numFreeShInputs[nextFreeShInQ] -= threadGroup;

        /*  Skip to the next shader for better work distribution.  */
        nextFreeShInQ = GPU_MOD(nextFreeShInQ + 1, numFShaders);

        ///*  Check if a whole shader input batch was assigned to the shader unit batch.  */
        //if (batchedShInputs[nextFreeShInQ] >= shInputBatchSize)
        //{
        //    /*  Reset current unit input batch counter.  */
        //    batchedShInputs[nextFreeShInQ] = 0;
        //
        //    /*  Skip to the next shader input queue.  */
        //    nextFreeShInQ = GPU_MOD(nextFreeShInQ + 1, numFShaders);
        //}
    }
}

/*  Shades vertices.  */
void FragmentFIFO::shadeVertices(u64bit cycle)
{
    u32bit i;
    ShaderInput *shInput;

    /*  Check if a group of input vertices is not complete.  */
    if ((vertexInputs < threadGroup) && (freeInputs >= (threadGroup - vertexInputs)))
    {   
        /*  Add fake vertex inputs.  */
        for(i = vertexInputs; i < threadGroup; i++)
        {
            GPU_DEBUG_BOX(
                printf("FragmentFIFO => Adding vertex for pading at position %d.\n", nextFreeInput);
            )

            /*  Create fake shader input.  */
            shInput = new ShaderInput(0, 0, 0, new QuadFloat[MAX_VERTEX_ATTRIBUTES]);

            /*  Set as vertex input.  */
            shInput->setAsVertex();

            /*  Set as killed (fake input, ignore when received).  */
            shInput->setKilled();

            /*  Set as not last (fake input, ignore when received).  */
            shInput->setLast(false);

            /*  Store input in the queue.  */
            inputVertexQueue[nextFreeInput] = shInput;

            /*  Update number of vertex inputs in the queue.  */
            vertexInputs++;

            /*  Update number of free input vertex queue entries.  */
            freeInputs--;

            /*  Update pointer to the next free input vertex queue entry.  */
            nextFreeInput = GPU_MOD(nextFreeInput + 1, vInputQueueSz);
        }

        /*  Unset last vertex input flag.  */
        lastVertexInput = FALSE;
    }

    /*  Search for the next shader input queue with enough free entries.  */
    //for(i = 0; (i < numFShaders) && (numFreeShInputs[nextFreeShInQ] < threadGroup); i++)
    //    nextFreeShInQ = GPU_MOD(nextFreeShInQ + 1, numFShaders);

    /*  Send input vertices to the shader.  */
    if((vertexInputs >= threadGroup) && (freeShVertices >= threadGroup) &&
        (numFreeShInputs[nextFreeShInQ] >= threadGroup))
    {
        /*  Send the vertex input attributes of a group of input vertices to the shader.  */
        for(i = 0; i < threadGroup; i++)
        {
            GPU_DEBUG_BOX(
                printf("FragmentFIFO => Sending vertex input stored at %d to shader input queue %d position %d.\n",
                    nextInputVertex, nextFreeShInQ, nextFreeShInput[nextFreeShInQ]);
            )

            /*  Set shader input as a vertex input.  */
            inputVertexQueue[nextInputVertex]->setAsVertex();

            /*  Send input to the shader.  */
            shaderInputQ[nextFreeShInQ][nextFreeShInput[nextFreeShInQ]] = inputVertexQueue[nextInputVertex];

            /*  Update pointer to the next input vertex.  */
            nextInputVertex = GPU_MOD(nextInputVertex + 1, vInputQueueSz);

            /*  Update pointer to the next free entry in the shader input queue.  */
            nextFreeShInput[nextFreeShInQ] = GPU_MOD(nextFreeShInput[nextFreeShInQ] + 1, shInputQSize);
        }

        /*  Update number of input vertices in the queue.  */
        vertexInputs -= threadGroup;

        /*  Update number of free input vertex queue entries.  */
        freeInputs += threadGroup;

        /*  Update number of free shaded vertex queue entries.  */
        freeShVertices -= threadGroup;

        /*  Update number of shader inputs in the queue.  */
        numShaderInputs[nextFreeShInQ] += threadGroup;

        /*  Update number of shader inputs assigned to the current shader unit batch.  */
        batchedShInputs[nextFreeShInQ] += threadGroup;

        /*  Update number of free entries in the shader input queue.  */
        numFreeShInputs[nextFreeShInQ] -= threadGroup;

        /*  Update cycle counter from last vertex group issued to the shaders.  */
        lastVertexGroupCycle = cycle;

        /*  Skip to the next shader input queue for better work distribution.  */
        nextFreeShInQ = GPU_MOD(nextFreeShInQ + 1, numFShaders);

        ///*  Check if a whole shader input batch was assigned to the shader unit batch.  */
        //if (batchedShInputs[nextFreeShInQ] >= shInputBatchSize)
        //{
        //    /*  Reset current unit input batch counter.  */
        //    batchedShInputs[nextFreeShInQ] = 0;
        //
        //    /*  Skip to the next shader input queue.  */
        //    nextFreeShInQ = GPU_MOD(nextFreeShInQ + 1, numFShaders);
        //}
    }
}

/*  Sends shaded stamps to the Z Stencil unit.  */
void FragmentFIFO::sendStampsZStencil(u64bit cycle)
{
    u32bit i;
    u32bit j;
    u32bit unit;
    u32bit numZSTUnitsHaveNoStamps;

    /*  Sends shaded stamps to all Z Stencil Test units.  */
    for(unit = 0; unit < numStampUnits; unit++)
    {
	if (shadedStamps[unit] == 0 && zstState[unit] == ROP_READY)
	    numZSTUnitsHaveNoStamps++;

        for(i = 0; (shadedStamps[unit] > 0) && (zstState[unit] == ROP_READY) && (i < stampsPerUnit); i++)
        {
            /*  Check if stamp is shaded.  */
            if (shaded[unit][nextShaded[unit]])
            {
                GPU_DEBUG_BOX(
                    printf("FragmentFIFO => Sending shaded stamp for unit %d at %d to Z Stencil Test unit %d.\n",
                        unit, nextShaded[unit], unit);
                )

                /*  Check end of the batch (last fragment).  */
                if (shQueue[unit][nextShaded[unit]][0]->getFragment() == NULL)
                {
                    /*  Check if all the fragments sent to the shader have been received back.  */
                    if (inputFragments == outputFragments)
                    {
                        /*  Send stamp to Z Stencil Test.  */
                        for(j =0; j < STAMP_FRAGMENTS; j++)
                        {
                            /*  Send fragment to Color Write.  */
                            zStencilInput[unit]->write(cycle, shQueue[unit][nextShaded[unit]][j]);

                            /*  Update statistics.  */
                            outputs->inc();
                            globalOutputs->inc();
                        }

                        //  Update the last cycle an input was sent to ZStencilTest.
                        lastCycleZSTIn[unit] = cycle;
                        
                        /*  Reset shaded flag.  */
                        shaded[unit][nextShaded[unit]] = FALSE;

                        /*  Update number of shaded stamps.  */
                        shadedStamps[unit]--;

                        /*  Update number of Z Stencil Test units that are waiting for last stamp/fragment.  */
                        //notLastSent--;

                        /*  If all the Z Stencil units received the last stamp.  */
                        //if (notLastSent == 0)
                        //{
                        //    /*  Change to END state.  */
                        //    state = RAST_END;
                        //}
                    }
                }
                else
                {
                   /*  Send stamp to Z Stencil Test.  */
                    for(j = 0; j < STAMP_FRAGMENTS; j++)
                    {
                        /*  Send fragment to Color Write.  */
                        zStencilInput[unit]->write(cycle, shQueue[unit][nextShaded[unit]][j]);

		        FragmentInput* frInput = shQueue[unit][nextShaded[unit]][j];
		        if (frInput->getDebug()) {
			    char filename[32];
			    sprintf(filename, "debugZSTIn%d.txt", unit);
		            FILE *debug = fopen(filename, "a+");
		            fprintf(debug, "GPU[%d] cycle %lld ZST shaded input (tri = %d tile = (%d, %d), x = %d, y = %d, z = %d) shader = %d unit = %d entry = %d culled = %s\n",
		            	gpuId, cycle, frInput->getTriangleID(), frInput->getTileID().getX(), frInput->getTileID().getY(),
		            	frInput->getFragment()->getX(), frInput->getFragment()->getY(), frInput->getFragment()->getZ(),
				frInput->getShaderUnit(), unit, nextShaded[unit],
		            	frInput->isCulled() ? "T" : "F");
		            QuadFloat* attributes = frInput->getAttributes();
	                    for (u32bit index = 0; attributes && index < MAX_FRAGMENT_ATTRIBUTES; index++) {
                                fprintf(debug, "attrib[%d] = { %f, %f, %f, %f }\n", index,
	                                attributes[index][0], attributes[index][1],
                                        attributes[index][2], attributes[index][3]);
	                    }
		            fflush(debug);
		            fclose(debug);
		        }

                        /*  Update statistics.  */
                        outputs->inc();
                        globalOutputs->inc();
                    }

                    //  Update the last cycle an input was sent to ZStencilTest.
                    lastCycleZSTIn[unit] = cycle;
                    
                    /*  Reset shaded flag.  */
                    shaded[unit][nextShaded[unit]] = FALSE;

                    /*  Update pointer to next shaded stamp.  */
                    nextShaded[unit] = GPU_MOD(nextShaded[unit] + 1, shQueueSz);

                    /*  Update number of shaded stamps.  */
                    shadedStamps[unit]--;

                    /*  Update number of free entries in the shaded stamp queue.  */
                    freeShaded[unit]++;
                }
            }
        }

	numShadedStampsToZSTUnit->incavg(i);
	globalNumShadedStampsToZSTUnit->incavg(i);
    }

    numZSTUnitsSendShadedStampsTo->incavg(numStampUnits - numZSTUnitsHaveNoStamps);
    globalNumZSTUnitsSendShadedStampsTo->incavg(numStampUnits - numZSTUnitsHaveNoStamps);
}


/*  Sends shaded stamps to the Color Write unit.  */
void FragmentFIFO::sendStampsColorWrite(u64bit cycle)
{
    u32bit i;
    u32bit j;
    u32bit unit;

    /*  Sends shaded stamps to all Color Write units.  */
    for(unit = 0; unit < numStampUnits; unit++)
    {

        for(i = 0; (shadedStamps[unit] > 0) && (cwState[unit] == ROP_READY) && (i < stampsPerUnit); i++)
        {
            /*  Check if stamp is shaded.  */
            if (shaded[unit][nextShaded[unit]])
            {
                GPU_DEBUG_BOX(
                    printf("FragmentFIFO => Sending shaded stamp for unit %d at %d to Color Write unit %d.\n",
                        unit, nextShaded[unit], unit);
                )

                /*  Check end of the batch (last fragment).  */
                if (shQueue[unit][nextShaded[unit]][0]->getFragment() == NULL)
                {
                    /*  Check if all the fragments sent to the shader have been already received.  */
                    if (inputFragments == outputFragments)
                    {
                        /*  Send stamp to Color Write.  */
                        for(j = 0; j < STAMP_FRAGMENTS; j++)
                        {
                            /*  Send fragment to Color Write.  */
                            cWriteInput[unit]->write(cycle, shQueue[unit][nextShaded[unit]][j]);

                            /*  Update statistics.  */
                            outputs->inc();
                            globalOutputs->inc();
                        }

                        //  Update the last cycle an input was sent to Color Write.
                        lastCycleCWIn[unit] = cycle;
                        
                        /*  Reset shaded flag.  */
                        shaded[unit][nextShaded[unit]] = FALSE;

                        /*  Update number of Color Write units that are waiting for last stamp/fragment.  */
                        notLastSent--;

                        /*  If all the Color Write units received the last stamp.  */
                        if (notLastSent == 0)
                        {
                            /*  Change to END state.  */
                            state = RAST_END;
                        }
                    }
                }
                else
                {
                    /*  Send stamp to Color Write Test.  */
                    for(j = 0; j < STAMP_FRAGMENTS; j++)
                    {
                        /*  Send fragment to Color Write.  */
                        cWriteInput[unit]->write(cycle, shQueue[unit][nextShaded[unit]][j]);

                        /*  Update statistics.  */
                        outputs->inc();
                        globalOutputs->inc();
			
			if (shQueue[unit][nextShaded[unit]][j]->getDebug()) {
			    char filename[32];
			    sprintf(filename, "debugCWIn%d.txt", unit);
		            FILE *debug = fopen(filename, "a+");
		            fprintf(debug, "GPU[%d] cycle %lld FragmentFIFO => CW shaded input (tri = %d, tile = (%d, %d), x = %d, y = %d, z = %d) shader = %d unit = %d entry = %d culled = %s.\n",
                                    gpuId, cycle,
			    	    shQueue[unit][nextShaded[unit]][j]->getTriangleID(),
			    	    shQueue[unit][nextShaded[unit]][j]->getTileID().getX(),
			    	    shQueue[unit][nextShaded[unit]][j]->getTileID().getY(),
		            	    shQueue[unit][nextShaded[unit]][j]->getFragment()->getX(),
			    	    shQueue[unit][nextShaded[unit]][j]->getFragment()->getY(),
			    	    shQueue[unit][nextShaded[unit]][j]->getFragment()->getZ(),
			    	    shQueue[unit][nextShaded[unit]][j]->getShaderUnit(), unit, nextShaded[unit],
			    	    shQueue[unit][nextShaded[unit]][j]->isCulled() ? "T" : "F");
			    QuadFloat* attributes = shQueue[unit][nextShaded[unit]][j]->getAttributes();
                            for (i = 0; i < MAX_FRAGMENT_ATTRIBUTES; i++) {
                                fprintf(debug, "attrib[%d] = { %f, %f, %f, %f }\n", i,
		                       attributes[i][0], attributes[i][1],
                                       attributes[i][2], attributes[i][3]);
		            }
		            fflush(debug);
		            fclose(debug);
		        }
                    }

                    //  Update the last cycle an input was sent to Color Write.
                    lastCycleCWIn[unit] = cycle;
                        
                    /*  Reset shaded flag.  */
                    shaded[unit][nextShaded[unit]] = FALSE;

                    /*  Update pointer to next shaded stamp.  */
                    nextShaded[unit] = GPU_MOD(nextShaded[unit] + 1, shQueueSz);

                    /*  Update number of shaded stamps.  */
                    shadedStamps[unit]--;

                    /*  Update number of free entries in the shaded stamp queue.  */
                    freeShaded[unit]++;
                }
            }
        }
    }
}

/*  Sends z tested stamps to the Color Write unit.  */
void FragmentFIFO::sendTestedStampsColorWrite(u64bit cycle)
{
    u32bit i;
    u32bit j;
    u32bit unit;

    /*  Sends tested stamps to all Color Write units.  */
    for(unit = 0; unit < numStampUnits; unit++)
    {
        for(i = 0; (testStamps[unit] > 0) && (i < stampsPerUnit) && cwState[unit] == ROP_READY; i++)
        {
            GPU_DEBUG_BOX(
                printf("FragmentFIFO => Sending z tested stamp for unit %d at tested queue position %d to Color Write.\n",
                    unit, nextTest[unit]);
            )

            /*  Check end of the batch (last fragment).  */
            if (testQueue[unit][nextTest[unit]][0]->getFragment() == NULL)
            {
                /*  Send stamp to Color Write.  */
                for(j = 0; j < STAMP_FRAGMENTS; j++)
                {
                    /*  Send fragment to Color Write.  */
                    cWriteInput[unit]->write(cycle, testQueue[unit][nextTest[unit]][j]);

                    /*  Update statistics.  */
                    outputs->inc();
                    globalOutputs->inc();
                }

                //  Update the last cycle an input was sent to Color Write.
                lastCycleCWIn[unit] = cycle;
                
                /*  Update number of tested stamps.  */
                testStamps[unit]--;

                /*  Update global number of tested stamps.  */
                allTestStamps--;

                /*  Update number of free entries in the tested stamp queue.  */
                freeTest[unit]++;

                /*  Update number of Color Write units that are waiting for last stamp/fragment.  */
                notLastSent--;

                /*  If all the Color Write units received the last stamp.  */
                if (notLastSent == 0 && testQueue[unit][nextTest[unit]][0]->getType() == FRAG_NORMAL)
                {
                    /*  Change to END state.  */
                    state = RAST_END;
                }
                
		if (testQueue[unit][nextTest[unit]][0]->getType() == FRAG_COMP_IN)
		   notLastSyncReceive--;

		/*  Update pointer to next tested stamp.  */
                nextTest[unit] = GPU_MOD(nextTest[unit] + 1, testQueueSz);
            }
            else
            {
                /*  Send stamp to Color Write Test.  */
                for(j = 0; j < STAMP_FRAGMENTS; j++)
                {
                    /*  Send fragment to Color Write.  */
                    cWriteInput[unit]->write(cycle, testQueue[unit][nextTest[unit]][j]);

                    /*  Update statistics.  */
                    outputs->inc();
                    globalOutputs->inc();
		    
		    if (testQueue[unit][nextTest[unit]][j]->getDebug()) {
	                char filename[32];
		        sprintf(filename, "debugCWIn%d.txt", unit);
		        FILE *debug = fopen(filename, "a+");
		        fprintf(debug, "GPU[%d] cycle %lld FragmentFIFO => CW ZST input at (tri = %d, tile = (%d, %d), x = %d, y = %d, z = %d).\n",
                                gpuId, cycle,
		        	testQueue[unit][nextTest[unit]][j]->getTriangleID(),
		        	testQueue[unit][nextTest[unit]][j]->getTileID().getX(),
		        	testQueue[unit][nextTest[unit]][j]->getTileID().getY(),
		        	testQueue[unit][nextTest[unit]][j]->getFragment()->getX(),
		        	testQueue[unit][nextTest[unit]][j]->getFragment()->getY(),
		        	testQueue[unit][nextTest[unit]][j]->getFragment()->getZ());
		        QuadFloat* attributes = testQueue[unit][nextTest[unit]][j]->getAttributes();
                        for (i = 0; i < MAX_FRAGMENT_ATTRIBUTES; i++) {
                            fprintf(debug, "attrib[%d] = { %f, %f, %f, %f }\n", i,
		                   attributes[i][0], attributes[i][1],
                                   attributes[i][2], attributes[i][3]);
		        }
		        fflush(debug);
		        fclose(debug);
		    }	
                }

                //  Update the last cycle an input was sent to Color Write.
                lastCycleCWIn[unit] = cycle;
                
                /*  Update pointer to next tested stamp.  */
                nextTest[unit] = GPU_MOD(nextTest[unit] + 1, testQueueSz);

                /*  Update number of tested stamps.  */
                testStamps[unit]--;

                /*  Update global number of tested stamps.  */
                allTestStamps--;

                /*  Update number of free entries in the tested stamp queue.  */
                freeTest[unit]++;
            }
        }
    }
}

/*  Send triangles to Triangle Setup.  */
void FragmentFIFO::sendTriangles(u64bit cycle)
{
    u32bit i;

    /*  Send setup triangles to Triangle Setup.  */
    for(i = 0; (i < trianglesCycle) && (outputTriangles > 0); i++)
    {
        GPU_DEBUG_BOX(
            printf("FragmentFIFO => Sending setup triangle at %d to Triangle Setup.\n", nextOutputTriangle);
        )

        /*  Send next setup triangle to Triangle Setup.  */
        triangleOutput->write(cycle, triangleOutQueue[nextOutputTriangle]);

        /*  Update  pointer to the next triangle output.  */
        nextOutputTriangle = GPU_MOD(nextOutputTriangle + 1, triangleOutQueueSz);

        /*  Update number of triangle outputs.  */
        outputTriangles--;

        /*  Update number of free triangle output queue entries.  */
        freeOutputTriangles++;

        /*  Update statistics.  */
        outTriangles->inc();
        globalOutTriangles->inc();
    }
}


/*  Send vertices to Streamer Commit.  */
void FragmentFIFO::sendVertices(u64bit cycle)
{
    u32bit i;

    /*  Act as N virtual vertex shaders.  There is only one consumer (and
        with the current implementation should be always sending ready as
        pre reserves vertex storage).  */
    for(i = 0; (i < numVShaders) && (shadedVertices > 0) && (consumerState[i] == CONS_READY); i++)
    {
        GPU_DEBUG_BOX(
            printf("FragmentFIFO %lld => Sending vertex for entry %d at %d to shader %d.\n",
             cycle, shadedVertexQueue[nextShadedVertex]->getEntry(), nextShadedVertex, i);
        )

        /*  Send next vertex through the next virtual shader signal.  */
        vertexOutput[i]->write(cycle, shadedVertexQueue[nextShadedVertex]);

        /*  Update  pointer to the next shaded vertex.  */
        nextShadedVertex = GPU_MOD(nextShadedVertex + 1, vShadedQueueSz);

        /*  Update number of shaded vertices.  */
        shadedVertices--;

        /*  Update number of free shaded vertex queue entries.  */
        freeShVertices++;

        /*  Update statistics.  */
        outVerts->inc();
        globalOutVerts->inc();
    }
}

void FragmentFIFO::getState(string &stateString)
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
        case RAST_COMP:
            stateStream << "RAST_COMP";
            break;
        case RAST_COMP_END:
            stateStream << "RAST_COMP_END";
            break;
        case RAST_END:
            stateStream << "RAST_END";
            break;
        case RAST_CLEAR:
            stateStream << "RAST_CLEAR";
            break;
        case RAST_CLEAR_END:
            stateStream << "RAST_CLEAR_END";
            break;
        default:
            stateStream << "undefined";
            break;
    }

    u32bit allShaderInputs = 0;
    for(int i = 0; i < numFShaders; i++)
        allShaderInputs += numShaderInputs[i];

    u32bit allShadedStamps = 0;
    for(int i = 0; i < numStampUnits; i++)
        allShadedStamps += shadedStamps[i];

    stateStream << " | Rasterizer Stamps = " << allRastStamps;
    stateStream << " | Test Stamps = " << allTestStamps;
    stateStream << " | Interpolator Stamps = " << allIntStamps;
    stateStream << " | Shader Inputs = " << allShaderInputs;

for(int i = 0; i < numStampUnits; i++)
{
stateStream << " | Next Shaded Stamp[" << i << "] = " << shaded[i][nextShaded[i]];
stateStream << " | CW State[" << i <<"] = " << cwState[i];
}

    stateString.assign(stateStream.str());
}


//  Detects stalls conditions in the Fragment FIFO.
void FragmentFIFO::detectStall(u64bit cycle, bool &active, bool &stalled)
{
    //  Stall detection is implemented.
    active = true;

    bool shaderUnitsStalled = true;

    //  Calculate the number of shader outputs that are waiting.
    
    //  Detect stalls on the shader units.
    for(u32bit sh = 0; (sh < numFShaders) && shaderUnitsStalled; sh++)
    {
        //  Detect stall on shader inputs waiting to be sent to the shader unit.
        shaderUnitsStalled = shaderUnitsStalled && (numShaderInputs[sh] > 0) && ((cycle - lastCycleShInput[sh]) > STALL_CYCLE_THRESHOLD);
        
        //  Detect stall on shader outputs waiting to be received from the shader unit.
        shaderUnitsStalled = shaderUnitsStalled && (shaderElements[sh] > 0) && ((cycle - lastCycleShOutput[sh]) > STALL_CYCLE_THRESHOLD);        
    }
    
    bool ropUnitStalled = true;
    
    //  Detect stalls in the input to the ROPs.
    for(u32bit rop = 0; (rop < numStampUnits) && ropUnitStalled; rop++)
    {
        //  Check what fragment processing data path is being used.
        if (earlyZ)
        {
            //  Detect stall on the inputs waiting to be sent to StencilTest.
            ropUnitStalled = ropUnitStalled && (rastStamps[rop] > 0) && ((cycle - lastCycleZSTIn[rop]) > STALL_CYCLE_THRESHOLD);
            
            //  Detect stall on the inputs waiting to be sent to Color Write.  Color Write waits for all the fragments
            //  to finish in the shaders before sending the last stamp mark.
            ropUnitStalled = ropUnitStalled && (shadedStamps[rop] > 1) && (shaded[rop][nextShaded[rop]]) && ((cycle - lastCycleCWIn[rop]) > STALL_CYCLE_THRESHOLD);
        }
        else
        {
            //  Detect stall on the inputs waiting to be sent to ZStencilTest.  ZStencil test waits for all the fragments
            //  to finish in the shaders before sending the last stamp mark.
            ropUnitStalled = ropUnitStalled && (shadedStamps[rop] > 1) && (shaded[rop][nextShaded[rop]]) && ((cycle - lastCycleZSTIn[rop]) > STALL_CYCLE_THRESHOLD);
            
            //  Detect stall on the inputs waiting to be sent to Color Write.
            ropUnitStalled = ropUnitStalled && (testStamps[rop] > 0) && ((cycle - lastCycleCWIn[rop]) > STALL_CYCLE_THRESHOLD);
        }
    }
    
    stalled = shaderUnitsStalled && ropUnitStalled;
}

void FragmentFIFO::stallReport(u64bit cycle, string &stallReport)
{
    stringstream reportStream;
    
    reportStream << "Fragment FIFO stall report for cycle " << cycle << endl;
    reportStream << "------------------------------------------------------------" << endl;
    reportStream << " Stall Threashold = " << STALL_CYCLE_THRESHOLD << endl;
    
    for(u32bit sh = 0; sh < numFShaders; sh++)
    {
        reportStream << " Shader Unit = " << sh << endl;
        reportStream << "   Inputs Waiting = " << numShaderInputs[sh] << " | Last Cycle Input Sent = " << lastCycleShInput[sh];
        reportStream << " Cycles Since Last Input Sent = " << (cycle - lastCycleShInput[sh]) << endl;
        reportStream << "   Elements Being Shaded = " << shaderElements[sh] << " | Last Cycle Output Received = " << lastCycleShOutput[sh];
        reportStream << " Cycles Since Last Output Received = " << (cycle - lastCycleShOutput[sh]) << endl;
    }              
    
    for(u32bit rop = 0; rop < numStampUnits; rop++)
    {
        if (earlyZ)
        {
            reportStream << " ROP Unit = " << rop << " | Early Z Active" << endl;
            reportStream << "   ZST Inputs Waiting = " << rastStamps[rop] << " | Last Cycle Input Sent = " << lastCycleZSTIn[rop];
            reportStream << " Cycles Since Last Input Sent = " << (cycle - lastCycleZSTIn[rop]) << endl;
            reportStream << "   CW Inputs Waiting = " << shadedStamps[rop] << " | Last Cycle Input Sent = " << lastCycleCWIn[rop];
            reportStream << " Cycles Since Last Input Sent = " << (cycle - lastCycleCWIn[rop]) << endl;
        }
        else
        {
            reportStream << " ROP Unit = | Early Z Not Active" << rop << endl;
            reportStream << "   ZST Inputs Waiting = " << shadedStamps[rop] << " | Last Cycle Input Sent = " << lastCycleZSTIn[rop];
            reportStream << " Cycles Since Last Input Sent = " << (cycle - lastCycleZSTIn[rop]) << endl;
            reportStream << "   CW Inputs Waiting = " << testStamps[rop] << " | Last Cycle Input Sent = " << lastCycleCWIn[rop];
            reportStream << " Cycles Since Last Input Sent = " << (cycle - lastCycleCWIn[rop]) << endl;
        }
    }

    stallReport.assign(reportStream.str());
}

void FragmentFIFO::endGenerationOfZSTSyncFragments(u64bit cycle)
{
    FragmentInput *frInput;
    bool receivedFragment;
    bool cullStamp;
    u32bit unit;
    u32bit i, j;

    for (unit = 0; unit < numStampUnits; unit++) {
        for (i = 0; i < stampsPerUnit; i++) {
	    receivedFragment = true;

	    for (j = 0; j < STAMP_FRAGMENTS && receivedFragment; j++) {
	        receivedFragment = zStencilSyncOutput[unit]->read(cycle, (DynamicObject *&)frInput);

		if (receivedFragment) {
                    GPU_ASSERT(
		        if (frInput->getType() != FRAG_SYNC_OUT && frInput->getType() != FRAG_COMP_OUT)
			    panic(getName(), "endGenerationOfZSTSyncFragments", "invalid fragment type");
		    )

		    syncQueueOutZST[unit][nextFreeSyncOutZST[unit]][j] = frInput;
		}
	    }

            /*  Check if a whole stamp has been received.  */
            GPU_ASSERT(
                if (!receivedFragment && (j > 1))
                    panic("FragmentFIFO", "endGenerationOfZSTSyncFragments", "Missing fragments in a stamp.");
            )
	    
	    if (receivedFragment) {
                for (j = 0, cullStamp = true; j < STAMP_FRAGMENTS; j++)
		    cullStamp = cullStamp && syncQueueOutZST[unit][nextFreeSyncOutZST[unit]][j]->isCulled();

		GPU_ASSERT(
		    if (cullStamp && syncQueueOutZST[unit][nextFreeSyncOutZST[unit]][0]->getFragment() == NULL)
   		        panic("FragmentFIFO", "endGenerationOfZSTSyncFragment", "null fragment should not be culled");
		)

	        if (cullStamp) {
		    for (j = 0; j < STAMP_FRAGMENTS; j++) {
		        QuadFloat *attrib = syncQueueOutZST[unit][nextFreeSyncOutZST[unit]][j]->getAttributes();
		        Fragment *fr = syncQueueOutZST[unit][nextFreeSyncOutZST[unit]][j]->getFragment();
			if (attrib) delete [] attrib;
			if (fr) delete fr;
			delete syncQueueOutZST[unit][nextFreeSyncOutZST[unit]][j];
		    }
		} else {
                    nextFreeSyncOutZST[unit] = GPU_MOD(nextFreeSyncOutZST[unit] + 1, syncQueueSz);
		    syncOutStampsZST[unit]++;
		    allSyncOutStampsZST++;
		    freeSyncOutZST[unit]--;
		}
	    }
	}
    }
}

void FragmentFIFO::sendZSTSyncFragmentsColorWrite(u64bit cycle)
{
    if (bypassCW)
	return;

    u32bit unit;
    u32bit i, j;

    for (unit = 0; unit < numStampUnits; unit++) {
        for (i = 0; (i < stampsPerUnit) && (cwSyncState[unit] == ROP_READY); i++) {
	    if (syncOutStampsZST[unit] > 0) {
	        for (j = 0; j < STAMP_FRAGMENTS; j++) {
	            cWriteSyncInput[unit]->write(cycle, syncQueueOutZST[unit][nextSyncOutZST[unit]][j]);
	        }

	        nextSyncOutZST[unit] = GPU_MOD(nextSyncOutZST[unit] + 1, syncQueueSz);
	        syncOutStampsZST[unit]--;
	        allSyncOutStampsZST--;
	        freeSyncOutZST[unit]++;
	    }
	}
    }
}

void FragmentFIFO::endGenerationOfCWSyncFragments(u64bit cycle)
{
    FragmentInput *frInput;
    bool receivedFragment;
    bool cullStamp;
    u32bit unit;
    u32bit i, j;

    for (unit = 0; unit < numStampUnits; unit++) {
        for (i = 0; i < stampsPerUnit; i++) {
	    receivedFragment = true;

	    for (j = 0; j < STAMP_FRAGMENTS && receivedFragment; j++) {
	        receivedFragment = cWriteSyncOutput[unit]->read(cycle, (DynamicObject *&)frInput);

		if (receivedFragment) {
                    GPU_ASSERT(
		        if (frInput->getType() != FRAG_SYNC_OUT && frInput->getType() != FRAG_COMP_OUT)
			    panic(getName(), "endGenerationOfCWSyncFragments", "invalid fragment type");
		    )

		    syncQueueOutCW[unit][nextFreeSyncOutCW[unit]][j] = frInput;
		}
	    }

            /*  Check if a whole stamp has been received.  */
            GPU_ASSERT(
                if (!receivedFragment && (j > 1))
                    panic("FragmentFIFO", "endGenerationOfCWSyncFragments", "Missing fragments in a stamp.");
            )
	    
	    if (receivedFragment) {
                for (j = 0, cullStamp = true; j < STAMP_FRAGMENTS; j++)
		    cullStamp = cullStamp && syncQueueOutCW[unit][nextFreeSyncOutCW[unit]][j]->isCulled();

		GPU_ASSERT(
		    if (cullStamp && syncQueueOutCW[unit][nextFreeSyncOutCW[unit]][0]->getFragment() == NULL)
   		        panic("FragmentFIFO", "endGenerationOfCWSyncFragment", "null fragment should not be culled");
		)

	        if (cullStamp) {
		    for (j = 0; j < STAMP_FRAGMENTS; j++) {
		        QuadFloat *attrib = syncQueueOutCW[unit][nextFreeSyncOutCW[unit]][j]->getAttributes();
		        Fragment *fr = syncQueueOutCW[unit][nextFreeSyncOutCW[unit]][j]->getFragment();
			if (attrib) delete [] attrib;
			if (fr) delete fr;
			delete syncQueueOutCW[unit][nextFreeSyncOutCW[unit]][j];
		    }
		} else {
                    nextFreeSyncOutCW[unit] = GPU_MOD(nextFreeSyncOutCW[unit] + 1, syncQueueSz);
		    syncOutStampsCW[unit]++;
		    allSyncOutStampsCW++;
		    freeSyncOutCW[unit]--;
		}
	    }
	}
    }
}

void FragmentFIFO::sendSyncFragmentsToOtherGPU(u64bit cycle)
{
    u32bit unit;
    u32bit i, j;
    u32bit destGPUId;
    bool canSent;
    bool allStampsReceived;

    u32bit *syncOutStamps = syncOutStampsCW;
    FragmentInput ****syncQueueOut = syncQueueOutCW;
    u32bit *nextSyncOut = nextSyncOutCW;
    u32bit *freeSyncOut = freeSyncOutCW;
    u32bit *allSyncOutStamps = &allSyncOutStampsCW;
    if (bypassCW) {
	syncOutStamps = syncOutStampsZST;
	syncQueueOut = syncQueueOutZST;
	nextSyncOut = nextSyncOutZST;
	freeSyncOut = freeSyncOutZST;
	allSyncOutStamps = &allSyncOutStampsZST;
    } 

    if (interGPUSyncTransCycles > 0) {
	interGPUSyncTransCycles--;

        if (interGPUSyncTransCycles > 0) {
	    interGPUSyncTransCycleStall->inc();
	    globalInterGPUSyncTransCycleStall->inc();
	    return;
	}
    }

    u32bit consumedInterGPUbw, fragDataSize;
    consumedInterGPUbw = 0;

    for (unit = 0; unit < numStampUnits; unit++) {
	for (i = 0; i < stampsPerUnit; i++) {
	    if (syncOutStamps[unit] > 0) {
	        switch (state) {
	            case RAST_COMP:
	                canSent = true;
			destGPUId = syncQueueOut[unit][nextSyncOut[unit]][0]->getDestGPUId();
	                canSent = canSent && (idealComp || freeSyncIn[destGPUId][unit] > 0) && (syncedStampUnits[destGPUId][gpuId] < numStampUnits);
	                
                        GPU_ASSERT(
			    if (destGPUId == gpuId && !anyRtBlend)
		                panic(getName(), "sendSyncFragmentsToOtherGPU", "should not blend with self if rtBlend is disabled");
			)

	                if (canSent) {
			    bool cullStamp = true;
			    for (j = 0; j < STAMP_FRAGMENTS; j++) {
				syncQueueOut[unit][nextSyncOut[unit]][j]->setType(FRAG_COMP_IN);
				if (destGPUId == gpuId) {
				    if (idealComp) {
					idealSyncQueueIn[unit].push(syncQueueOut[unit][nextSyncOut[unit]][j]);
		                        cullStamp = cullStamp && idealSyncQueueIn[unit].back()->isCulled();
				    } else {
			                syncQueueIn[unit][nextFreeSyncIn[unit]][j] = syncQueueOut[unit][nextSyncOut[unit]][j];
		                        cullStamp = cullStamp && syncQueueIn[unit][nextFreeSyncIn[unit]][j]->isCulled();
				    }
				} else {
			            syncFragOut[destGPUId]->write(cycle, syncQueueOut[unit][nextSyncOut[unit]][j]);
				    fragDataSize = syncQueueOut[unit][nextSyncOut[unit]][i]->getSize();
				    consumedInterGPUbw += fragDataSize;
				    interGPUSyncTrafficLoad->inc(fragDataSize);
				    globalInterGPUSyncTrafficLoad->inc(fragDataSize);
				}
			    }
		           
			    if (destGPUId == gpuId) { 
				GPU_ASSERT(
		                    if (cullStamp)
		                        panic(getName(), "sendSyncFragmentsToOtherGPU", "sync fragments should not be culled");
		                )

				if (!idealComp)
		                    nextFreeSyncIn[unit] = GPU_MOD(nextFreeSyncIn[unit] + 1, interGPUSyncQueueSz);
		                syncInStamps[unit]++;
		                allSyncInStamps++;
			    } else {
				// 4-byte metadata for pixel coord, 2 bytes for x and 2 bytes for y
				consumedInterGPUbw += 4;
				interGPUSyncTrafficLoad->inc(4);
				globalInterGPUSyncTrafficLoad->inc(4);
			    }
			   
			    if (!idealComp) 
		                freeSyncIn[destGPUId][unit]--;

			    if (syncQueueOut[unit][nextSyncOut[unit]][0]->getFragment() == NULL) {
				notLastSyncSent--;
				syncedStampUnits[destGPUId][gpuId]++;
			        
				if (compSchedEnabled) {
			            allStampsReceivedForSync[destGPUId][unit] = true;
			            allStampsReceived = true;
			            for (j = 0; j < numStampUnits; j++)
					allStampsReceived = allStampsReceived && allStampsReceivedForSync[destGPUId][j];
			            if (allStampsReceived) {
					std::cout << "GPU " << destGPUId << " received all stamps from GPU " << gpuId
						  << " @cycle " << cycle
						  << std::endl;
			                for (j = 0; j < numStampUnits; j++)
					    allStampsReceivedForSync[destGPUId][j] = false;

					GPUDriver::getGPUDriver()->getCompSched()->resetReceiving(destGPUId);
			            }
			        }
			    }

			    nextSyncOut[unit] = GPU_MOD(nextSyncOut[unit] + 1, syncQueueSz);
			    syncOutStamps[unit]--;
			    *allSyncOutStamps--;
			    freeSyncOut[unit]++;
	                } else {
			    interGPUSyncCannotSend->inc();
			    globalInterGPUSyncCannotSend->inc();
			}

	                break;
	            default:
	                panic(getName(), "sendSyncFragmentsToOtherGPU", "invalid state");
	        }
	    }
	}
    }

    if (!idealComp)
        interGPUSyncTransCycles = (u32bit)ceil(f32bit(consumedInterGPUbw)/f32bit(interGPUBusWidth));
}

void FragmentFIFO::receiveSyncFragments(u64bit cycle)
{
    u32bit unit; 
    u32bit i, j; 
    u32bit srcGPUId;
    bool receivedFragment;
    bool cullStamp;
    FragmentInput *frInput;
    bool allStampsReceived;
    std::vector<bool> cullStampForIdealComp;

    for (srcGPUId = 0; srcGPUId < numGPUs; srcGPUId++) {
        if (srcGPUId != gpuId) {
            for (i = 0; i < stampsPerUnit * numStampUnits; i++) {
    	        receivedFragment = true;
		if (idealComp)
		    cullStampForIdealComp.resize(STAMP_FRAGMENTS, false);

    	        for (j = 0; j < STAMP_FRAGMENTS && receivedFragment; j++) {
    	            receivedFragment = syncFragIn[srcGPUId]->read(cycle, (DynamicObject *&)frInput);

    	            if (receivedFragment) {
    	                GPU_ASSERT(
    	            	    if (frInput->getType() != FRAG_SYNC_IN && frInput->getType() != FRAG_COMP_IN)
    	            	        panic(getName(), "receiveSyncFragments", "invalid fragment type");
    	                )

		        unit = frInput->getStampUnit();
			if (idealComp) {
			    cullStampForIdealComp[j] = frInput->isCulled();
			    idealSyncQueueIn[unit].push(frInput);
			} else
    	                    syncQueueIn[unit][nextFreeSyncIn[unit]][j] = frInput;
    	            }
    	        }

                /*  Check if a whole stamp has been received.  */
                GPU_ASSERT(
                    if (!receivedFragment && (j > 1))
                        panic("FragmentFIFO", "receiveSyncFragments", "Missing fragments in a stamp.");
                )

    	        if (receivedFragment) {
                    for (j = 0, cullStamp = true; j < STAMP_FRAGMENTS; j++)
			if (idealComp)
			    cullStamp = cullStamp && cullStampForIdealComp[j];
			else
    	                    cullStamp = cullStamp && syncQueueIn[unit][nextFreeSyncIn[unit]][j]->isCulled();

    	            GPU_ASSERT(
    	                if (cullStamp)
    	                    panic("FragmentFIFO", "receiveSyncFragments", "sync fragments should not be culled");
    	            )

		    if (!idealComp)
    	                nextFreeSyncIn[unit] = GPU_MOD(nextFreeSyncIn[unit] + 1, interGPUSyncQueueSz);
    	            syncInStamps[unit]++;
    	            allSyncInStamps++;
    	        }
            }
        }
    }
}

void FragmentFIFO::processInputSyncFragments(u64bit cycle)
{
    u32bit unit;
    u32bit i, j;
    FragmentInput *lastFr;

    for (unit = 0; unit < numStampUnits; unit++) {
        for (i = 0; i < stampsPerUnit && syncInStamps[unit] > 0; i++) {
	    if (idealComp) {
                if (idealSyncQueueIn[unit].front()->getType() == FRAG_COMP_IN) {
                    bool canSent = (!bypassZST && zstState[unit] == ROP_READY) || (bypassZST && cwState[unit] == ROP_READY);
                    if (!canSent)
                        break;

                    for (j = 0; j < STAMP_FRAGMENTS; j++) {
	                if (bypassZST)
                            cWriteInput[unit]->write(cycle, idealSyncQueueIn[unit].front());
			else
                            zStencilInput[unit]->write(cycle, idealSyncQueueIn[unit].front());
			
			if (j == 0)
			    lastFr = idealSyncQueueIn[unit].front();
			idealSyncQueueIn[unit].pop();
                    }

                    if ((bypassZST || bypassCW) && lastFr->getFragment() == NULL)
                        notLastSyncReceive--;
                } else {
                    panic("FragmentFIFO", "processInputSyncFragments", "current implementation only support FRAG_COMP_IN");
                }
	    } else {
                if (syncQueueIn[unit][nextSyncIn[unit]][0]->getType() == FRAG_COMP_IN) {
                    bool canSent = (!bypassZST && zstState[unit] == ROP_READY) || (bypassZST && cwState[unit] == ROP_READY);
                    if (!canSent)
                        break;

                    for (j = 0; j < STAMP_FRAGMENTS; j++) {
	                if (bypassZST)
                            cWriteInput[unit]->write(cycle, syncQueueIn[unit][nextSyncIn[unit]][j]);
                        else
                            zStencilInput[unit]->write(cycle, syncQueueIn[unit][nextSyncIn[unit]][j]);
                    }

                    if ((bypassZST || bypassCW) && syncQueueIn[unit][nextSyncIn[unit]][0]->getFragment() == NULL)
                        notLastSyncReceive--;
                } else {
                    panic("FragmentFIFO", "processInputSyncFragments", "current implementation only support FRAG_COMP_IN");
                }
	    }

	    if (!idealComp) {
                nextSyncIn[unit] = GPU_MOD(nextSyncIn[unit] + 1, interGPUSyncQueueSz);
                freeSyncIn[gpuId][unit]++;
	    }
            syncInStamps[unit]--;
            allSyncInStamps--;
        }
    }
}
