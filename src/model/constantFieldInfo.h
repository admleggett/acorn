/**
 * @file codeAttribute.h
 * @brief This file contains the definition of the ConstantFieldInfo class.
 * @details The ConstantFieldInfo class represents a field reference in the constant pool of a Java class file.
 */

#ifndef CONSTANTFIELDINFO_H
#define CONSTANTFIELDINFO_H
#include <cstdint>

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

    std::string key() const override
    {
        return tagToString(getTag()) + ":" + std::to_string(classNameIdx) + ":" + std::to_string(nameAndTypeIdx);
    }

private:
    uint16_t classNameIdx;
    uint16_t nameAndTypeIdx;
};

#endif //CONSTANTFIELDINFO_H
