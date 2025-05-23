#ifndef CONSTANTNAMEANDTYPEINFO_H
#define CONSTANTNAMEANDTYPEINFO_H

#include "bigEndianUtil.h"
#include "constantPoolEntry.h"

class ConstantNameAndTypeInfo : public ConstantPoolEntry
{
public:
    ConstantNameAndTypeInfo(const uint16_t nameIndex, const uint16_t typeIndex )
        : nameIndex( nameIndex ), typeIndex( typeIndex ) {}

    [[nodiscard]] std::vector<uint8_t> serialize() const override
    {
        return serializeWithTagAndIndices({nameIndex, typeIndex});
    }

    [[nodiscard]] Tag getTag() const override
    {
        return Tag::NAME_AND_TYPE;
    }

private:
    uint16_t nameIndex;
    uint16_t typeIndex;
};

#endif //CONSTANTNAMEANDTYPEINFO_H
