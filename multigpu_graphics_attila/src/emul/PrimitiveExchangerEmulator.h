#ifndef _PRIMITIVEEXCHANGEREMULATOR_
#define _PRIMITIVEEXCHANGEREMULATOR_

#include "GPUTypes.h"
#include "GPU.h"
#include <set>

namespace gpu3d
{

class PrimitiveExchangerEmulator {
private:
    bool d3d9PixelCoordinates;
    s32bit x0;
    s32bit y0;
    u32bit w;
    u32bit h;

    u32bit windowWidth;
    u32bit windowHeight;
    s32bit scissorX0;
    s32bit scissorY0;
    u32bit scissorW;
    u32bit scissorH;

public:
    PrimitiveExchangerEmulator();
    void setViewport(bool d3d9PixelCoords, s32bit x, s32bit y, u32bit w, u32bit h);
    void setScissor(u32bit wWdith, u32bit wHeight, bool scissor, s32bit x, s32bit y, u32bit w, u32bit h);
    std::set<u32bit> getMappedGPUIds(u32bit numGPUs, QuadFloat *v1, QuadFloat *v2, QuadFloat *v3, u32bit displayTileW, u32bit displayTileH);
};

}

#endif
