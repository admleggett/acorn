#ifndef CONSTANTFIELDINFO_H
#define CONSTANTFIELDINFO_H
#include <cstdint>

#include "bigEndianUtil.h"
#include "constantPoolEntry.h"

class ConstantFieldInfo : public ConstantPoolEntry
{
public:
    explicit ConstantFieldInfo(uint16_t classIdx, uint16_t nameTypeIdx)
        : classNameIdx(classIdx), nameAndTypeIdx(nameTypeIdx) {}

    [[nodiscard]] std::vector<uint8_t> serialize() const override
    {
        return serializeWithTagAndIndices({classNameIdx, nameAndTypeIdx});
    }

    [[nodiscard]] Tag getTag() const override
    {
        return Tag::FIELD_REF;
    }


private:
    uint16_t classNameIdx;
    uint16_t nameAndTypeIdx;
};

#endif //CONSTANTFIELDINFO_H
