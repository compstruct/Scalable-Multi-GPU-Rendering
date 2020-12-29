#ifndef _PRIMITIVEEXCHANGERCOMMAND_
#define _PRIMITIVEEXCHANGERCOMMAND_

#include "DynamicObject.h"
#include "GPU.h"
#include "GPUTypes.h"
#include "support.h"

#include <vector>

namespace gpu3d
{

enum PECommand
{
    PECOM_RESET,
    PECOM_REG_WRITE,
    PECOM_REG_READ,
    PECOM_START,
    PECOM_END,
    PECOM_SWAP,
    PECOM_MAPPED_DRAW_COMM,
    PECOM_SYNCED_DRAW_COMM,
    PECOM_INDEX_EXCHANGE
};

class PrimitiveExchangerCommand : public DynamicObject
{
private:
    PECommand command;
    GPURegister reg;
    u32bit subReg;
    GPURegData data;
    
    bool last;
    u32bit indexExchangeBatchId;
    std::vector<u32bit> exchangedIndexes; 

public:
    PrimitiveExchangerCommand(PECommand comm);
    PrimitiveExchangerCommand(GPURegister reg, u32bit subReg, GPURegData data);
    PrimitiveExchangerCommand(bool last, u32bit batchId, std::vector<u32bit> indexes);
    PrimitiveExchangerCommand(u32bit releasedEntries);
    PECommand getCommand() const { return command; }
    GPURegister getRegister() const { return reg; }
    u32bit getSubRegister() const { return subReg; }
    GPURegData getRegisterData() const { return data; } 

    void setNumOfMappedDrawComms(u32bit numOfMappedDrawComms);
    u32bit getNumOfMappedDrawComms() const;
    void setNumOfSyncedDrawComms(u32bit numOfSyncedDrawComms);
    u32bit getNumOfSyncedDrawComms() const;
    bool isLast() const;
    u32bit getCurrentExchangeBatchId() const;
    std::vector<u32bit> getExchangedIndexes() const; 
}; 

}

#endif
