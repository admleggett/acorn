#ifndef CONSTANTMETHODINFO_H
#define CONSTANTMETHODINFO_H

#include "bigEndianUtil.h"
#include "constantPoolEntry.h"

class ConstantMethodInfo : public ConstantPoolEntry
{
public:
    ConstantMethodInfo(uint16_t classIdx, uint16_t nameTypeIdx)
        : classIndex(classIdx), nameAndTypeIndex(nameTypeIdx) {}

    [[nodiscard]] std::vector<uint8_t> serialize() const override
    {
        return serializeWithTagAndIndices({classIndex, nameAndTypeIndex});
    }

    [[nodiscard]] Tag getTag() const override
    {
        return Tag::METHOD_REF;
    }

private:
    uint16_t classIndex;
    uint16_t nameAndTypeIndex;
};

#endif // CONSTANTMETHODINFO_H

