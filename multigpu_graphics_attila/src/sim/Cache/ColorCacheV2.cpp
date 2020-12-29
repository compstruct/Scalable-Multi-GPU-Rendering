/**************************************************************************
 *
 * Copyright (c) 2002 - 2011 by Computer Architecture Department,
 * Universitat Politecnica de Catalunya.
 * All rights reserved.
 *
 * The contents of this file may not b;e disclosed to third parties,
 * copied or duplicated in any form, in whole or in part, without the
 * prior permission of the authors, Computer Architecture Department
 * and Universitat Politecnica de Catalunya.
 *
 * $RCSfile: ColorCacheV2.cpp,v $
 * $Revision: 1.5 $
 * $Author: vmoya $
 * $Date: 2008-03-02 19:09:16 $
 *
 * Color Cache class implementation file.
 *
 */

/**
 *
 * @file ColorCacheV2.cpp
 *
 * Implements the Color Cache class.  This class the cache used for
 * access to the color buffer in a GPU.
 *
 */

#include "ColorCacheV2.h"
#include "GPUMath.h"
#include "FragmentOpEmulator.h"
#include <cstring>

using namespace gpu3d;

//  Color Cache class counter.  Used to create identifiers for the created Color Caches
//  that are then used to access the Memory Controller.
u32bit ColorCacheV2::cacheCounter = 0;

//  Color cache constructor.
ColorCacheV2::ColorCacheV2(u32bit gpuId, u32bit numGPUs, u32bit stampId, u32bit ways, u32bit lines, u32bit lineSz,
        u32bit readP, u32bit writeP, u32bit pWidth, u32bit reqQSize, u32bit inReqs,
        u32bit outReqs, bool comprDisabled, u32bit numStampUnits, u32bit stampUnitStride,
        u32bit maxColorBlocks, u32bit blocksPerCycle, u32bit compCycles, u32bit decompCycles,
	PixelMapper *pixelMapper, bool *activeBuffer, u32bit *bufferAddr, u32bit *bufferAddrForComp,
	BlendEquation *equation, BlendFunction *srcRGB, BlendFunction *dstRGB, BlendFunction *srcAlpha, BlendFunction *dstAlpha,
	char *postfix) :

        ROPCache(gpuId, numGPUs, ways, lines, lineSz, readP, writeP, pWidth, reqQSize,
            inReqs, outReqs, comprDisabled, numStampUnits, stampUnitStride, maxColorBlocks, blocksPerCycle, compCycles,
            decompCycles, pixelMapper, activeBuffer, bufferAddr, bufferAddrForComp,
	    equation, srcRGB, dstRGB, srcAlpha, dstAlpha,
	    COLORWRITE, strdup(std::string("ColorCacheV2").c_str()), postfix)

{
    //  Get the ROP Cache identifier.
    //cacheID = cacheCounter - gpuId * numStampUnits;
    cacheID = stampId;

    //  Update the number of created Color Caches.
    cacheCounter++;

    //  Set reset value for clear.
    for(u32bit i = 0; i < MAX_BYTES_PER_COLOR; i++)
        clearResetValue[i] = 0x00;

 }


//  Clears the color cache.
bool ColorCacheV2::clear(u8bit *color)
{
    //  Reset the cache.
    if (clearMode)
    {
        //  Check clear cycles remaining.
        if (clearCycles > 0)
        {
            //  Update clear cycles.
            clearCycles--;

            //  Check if end of clear.
            if (clearCycles == 0)
            {
                //  Set the ROP clear value register.
                for(u32bit i = 0; i < MAX_BYTES_PER_PIXEL; i++)
                    clearROPValue[i] = color[i];

                //  Unset reset mode.
                clearMode = FALSE;
            }
        }
    }
    else
    {
        //  NOTE:  SHOULD TAKE INTO ACCOUNT THE RESOLUTION SO NOT ALL
        //  BLOCKS HAD TO BE CLEARED EVEN IF UNUSED AT CURRENT RESOLUTION.  */

        //  Set clear cycles.
        clearCycles = (u32bit) ceil((f32bit) maxBlocks / (f32bit) blocksCycle);

        //  Set clear mode.
        clearMode = TRUE;

        //  Reset the cache.
        resetMode = TRUE;
    }

    return clearMode;
}

//  Copies the block state memory.
void ColorCacheV2::copyBlockStateMemory(ROPBlockState *buffer, u32bit blocks)
{
    GPU_ASSERT(
        if (blocks > maxBlocks)
            panic("ColorCache", "copyBlockSateMemory", "More blocks to copy than blocks in the state memory.");
    )

    //  Copy the block states.
    memcpy(buffer, blockState, sizeof(ROPBlockState) * blocks);
}

void ColorCacheV2::recordWriteForComp(u32bit rt, u32bit address, bool *culled)
{
    if (!compMode)
	return;

    bool cullStamp = true;
    for (u32bit i = 0; i < STAMP_FRAGMENTS; i++)
	cullStamp = cullStamp && culled[i];

    GPU_ASSERT(
	if (cullStamp)
	    panic("ColorCache", "recordWriteForComp", "Culled stamp should not reach here");
    )

    u32bit block = addressToBlockSU(address);
    blockStateForComp[rt][block].dirty = true;
}

bool ColorCacheV2::clearForComp(u8bit *colorForComp)
{
    if (clearModeForComp) {
        if (clearCycles > 0) {
	    clearCycles--;

	    if (clearCycles == 0) {
                for(u32bit i = 0; i < MAX_BYTES_PER_PIXEL; i++)
                    clearROPValueForComp[i] = colorForComp[i];

		for (u32bit rt = 0; rt < MAX_RENDER_TARGETS; rt++) {
		    for (u32bit i = 0; i < maxBlocks; i++) {
		        blockStateForComp[rt][i].state = ROPBlockState::CLEAR;
		        blockStateForComp[rt][i].dirty = false;
		    }
		}

	        clearModeForComp = false;
	    }
	}
    } else {
        clearCycles = (u32bit) ceil((f32bit) maxBlocks / (f32bit) blocksCycle);
	clearModeForComp = true;
    }

    return clearModeForComp;
}
