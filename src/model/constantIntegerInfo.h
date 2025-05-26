/**
 * @file codeAttribute.h
 * @brief This file contains the definition of the ConstantIntegerInfo class.
 * @details The ConstantIntegerInfo class represents an integer constant in the constant pool of a Java class file.
 *
 */
#ifndef CONSTANTINTEGERINFO_H
#define CONSTANTINTEGERINFO_H

#include "bigEndianUtil.h"
#include <cstdint>
#include <vector>

class ConstantIntegerInfo : public ConstantPoolEntry {
public:
    explicit ConstantIntegerInfo(int32_t value) : value_(value) {}

    std::vector<uint8_t> serialize() const override {
        std::vector<uint8_t> bytes;
        bytes.push_back(0x03); // tag for Integer
        BigEndianUtil::appendUint32(bytes, static_cast<uint32_t>(value_));
        return bytes;
    }
    Tag getTag() const override {
        return Tag::INTEGER;
    }

    std::string key() const override {
        return tagToString(getTag()) + ":" + std::to_string(value_);
    }

private:
    int32_t value_;
};

#endif // CONSTANTINTEGERINFO_H
