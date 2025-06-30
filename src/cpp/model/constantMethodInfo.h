/**
 * @file constantMethodInfo.h
 * @brief Header file for the ConstantMethodInfo class.
 * @details This class represents a method reference in the constant pool of a Java class file.
 *
 */
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

    std::string key() const override
    {
        return tagToString(getTag()) + ":" + std::to_string(classIndex) + ":" + std::to_string(nameAndTypeIndex);
    }

private:
    uint16_t classIndex;
    uint16_t nameAndTypeIndex;
};

#endif // CONSTANTMETHODINFO_H

