#include "PrimitiveExchangerEmulator.h"
#include "support.h"
#include "GPUMath.h"
#include <cstdio>

using namespace gpu3d;

PrimitiveExchangerEmulator::PrimitiveExchangerEmulator()
{
    d3d9PixelCoordinates = false;
    x0 = 0;
    y0 = 0;
    w = 400;
    h = 400;
    windowWidth = 400;
    windowHeight = 400;
    scissorX0 = 0;
    scissorY0 = 0;
    scissorW = 400;
    scissorH = 400;
}

void PrimitiveExchangerEmulator::setViewport(bool useD3D9PixelCoords, s32bit x, s32bit y, u32bit width, u32bit height)
{
    d3d9PixelCoordinates = useD3D9PixelCoords;
    x0 = x;
    y0 = y;
    w = width;
    h = height;
}

void PrimitiveExchangerEmulator::setScissor(u32bit wWidth, u32bit wHeight, bool scissor, s32bit scx0, s32bit scy0, u32bit scw, u32bit sch)
{
    windowWidth = wWidth;
    windowHeight = wHeight;

    if (scissor) {
        scissorX0 = GPU_MAX(scx0, 0);
	scissorY0 = GPU_MAX(scy0, 0);
	scissorW = GPU_MIN(scw, windowWidth - scissorX0);
	scissorH = GPU_MIN(sch, windowHeight - scissorY0);
    } else {
        scissorX0 = 0;
	scissorY0 = 0;
	scissorW = windowWidth;
	scissorH = windowHeight;
    }
}

std::set<u32bit> PrimitiveExchangerEmulator::getMappedGPUIds(u32bit numGPUs, QuadFloat *vAttr1, QuadFloat *vAttr2, QuadFloat *vAttr3,
		                                             u32bit displayTileW, u32bit displayTileH)
{
    s32bit xMin, yMin, zMin;
    s32bit xMax, yMax, zMax;
    u32bit numDisplayTilesInhRes;
    u32bit mappedDisplayTileId;
    u32bit mappedGPUId;
    std::set<u32bit> mappedGPUIds;

    if (d3d9PixelCoordinates)
    {
        vAttr1[POSITION_ATTRIBUTE][1] = -vAttr1[POSITION_ATTRIBUTE][1];
        vAttr2[POSITION_ATTRIBUTE][1] = -vAttr2[POSITION_ATTRIBUTE][1];
        vAttr3[POSITION_ATTRIBUTE][1] = -vAttr3[POSITION_ATTRIBUTE][1];
    }

    GPUMath::boundingBox(vAttr1[POSITION_ATTRIBUTE], vAttr2[POSITION_ATTRIBUTE], vAttr3[POSITION_ATTRIBUTE], x0, y0, w, h,
		         xMin, xMax, yMin, yMax, zMin, zMax);

    xMin = GPU_MIN(GPU_MAX(xMin, scissorX0), scissorX0 + s32bit(scissorW));
    xMax = GPU_MAX(GPU_MIN(xMax, scissorX0 + s32bit(scissorW)), scissorX0);
    yMin = GPU_MIN(GPU_MAX(yMin, scissorY0), scissorY0 + s32bit(scissorH));
    yMax = GPU_MAX(GPU_MIN(yMax, scissorY0 + s32bit(scissorH)), scissorY0);

    mappedGPUIds = std::set<u32bit>();
    numDisplayTilesInhRes = (u32bit) ceil((f32bit)windowWidth / (f32bit)displayTileW);

    for (u32bit y = yMin/displayTileH; y <= yMax/displayTileH; y++) {
        for (u32bit x = xMin/displayTileW; x <= xMax/displayTileW; x++) {
	    mappedDisplayTileId = x + numDisplayTilesInhRes * y;
	    mappedGPUId = GPU_MOD(mappedDisplayTileId, numGPUs);
	    mappedGPUIds.insert(mappedGPUId);
	}
    }

    return mappedGPUIds;
}
