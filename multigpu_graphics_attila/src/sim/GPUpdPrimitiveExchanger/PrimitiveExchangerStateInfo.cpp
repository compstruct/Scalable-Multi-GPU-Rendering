#include "PrimitiveExchangerStateInfo.h"

using namespace gpu3d;

PrimitiveExchangerStateInfo::PrimitiveExchangerStateInfo(PrimitiveExchangerState newState) :
    state(newState)
{
    setColor(state);
    setTag("PeSteIn");
}

PrimitiveExchangerState PrimitiveExchangerStateInfo::getState()
{
    return state;
}
