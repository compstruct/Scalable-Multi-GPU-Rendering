#ifndef _PRIMITIVEEXCHANGERSTATEINFO_
#define _PRIMITIVEEXCHANGERSTATEINFO_

#include "DynamicObject.h"
#include "PrimitiveExchanger.h"

namespace gpu3d
{

class PrimitiveExchangerStateInfo : public DynamicObject
{
private:
    PrimitiveExchangerState state;
public:
    PrimitiveExchangerStateInfo(PrimitiveExchangerState state);
    PrimitiveExchangerState getState();
};

}

#endif
