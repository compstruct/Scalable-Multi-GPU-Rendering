#include "PrimitiveExchangerCommand.h"

using namespace gpu3d;

PrimitiveExchangerCommand::PrimitiveExchangerCommand(PECommand comm)
{
    GPU_ASSERT(
        if ((comm != PECOM_RESET) && (comm != PECOM_START) && (comm != PECOM_END) &&
	    (comm != PECOM_SWAP) && (comm != PECOM_MAPPED_DRAW_COMM) && (comm != PECOM_SYNCED_DRAW_COMM))
            panic("PrimitiveExchangerCommand", "PrimitiveExchangerCommand", "Illegal PrimitiveExchanger command.");	
    )

    command = comm;
    setColor(command);
    setTag("PECom");
}

PrimitiveExchangerCommand::PrimitiveExchangerCommand(GPURegister rReg, u32bit rSubReg, GPURegData rData)
{
    command = PECOM_REG_WRITE;
    reg = rReg;
    subReg = rSubReg;
    data = rData;

    setColor(command);
    setTag("PECom");
}

PrimitiveExchangerCommand::PrimitiveExchangerCommand(bool last_, u32bit batchId, std::vector<u32bit> indexes)
{
    command = PECOM_INDEX_EXCHANGE;
    last = last_;
    indexExchangeBatchId = batchId;
    exchangedIndexes = indexes;
 
    setColor(command);
    setTag("PECom");
}

void PrimitiveExchangerCommand::setNumOfMappedDrawComms(u32bit numOfMappedDrawComms) {
    GPU_ASSERT(
        if (command != PECOM_MAPPED_DRAW_COMM)
            panic("PrimitiveExchangerCommand", "setNumOfMappedDrawComms", "Invalid command type.");	
    )
    data.uintVal = numOfMappedDrawComms;
}

u32bit PrimitiveExchangerCommand::getNumOfMappedDrawComms() const {
    GPU_ASSERT(
        if (command != PECOM_MAPPED_DRAW_COMM)
            panic("PrimitiveExchangerCommand", "getNumOfMappedDrawComms", "Invalid command type.");	
    )
    return data.uintVal;
}

void PrimitiveExchangerCommand::setNumOfSyncedDrawComms(u32bit numOfSyncedDrawComms) {
    GPU_ASSERT(
        if (command != PECOM_SYNCED_DRAW_COMM)
            panic("PrimitiveExchangerCommand", "setNumOfSyncedDrawComms", "Invalid command type.");	
    )
    data.uintVal = numOfSyncedDrawComms;
}

u32bit PrimitiveExchangerCommand::getNumOfSyncedDrawComms() const {
    GPU_ASSERT(
        if (command != PECOM_SYNCED_DRAW_COMM)
            panic("PrimitiveExchangerCommand", "getNumOfSyncedDrawComms", "Invalid command type.");	
    )
    return data.uintVal;
}

bool PrimitiveExchangerCommand::isLast() const {
    GPU_ASSERT(
        if (command != PECOM_INDEX_EXCHANGE)
            panic("PrimitiveExchangerCommand", "isLast", "Invalid command type.");	
    )
    return last;
}

u32bit PrimitiveExchangerCommand::getCurrentExchangeBatchId() const {
    GPU_ASSERT(
        if (command != PECOM_INDEX_EXCHANGE)
            panic("PrimitiveExchangerCommand", "getCurrentExchangeBatchId", "Invalid command type.");	
    )
    return indexExchangeBatchId;
}

std::vector<u32bit> PrimitiveExchangerCommand::getExchangedIndexes() const {
    GPU_ASSERT(
        if (command != PECOM_INDEX_EXCHANGE)
            panic("PrimitiveExchangerCommand", "getExchangedIndexes", "Invalid command type.");	
    )
    return exchangedIndexes;
}
