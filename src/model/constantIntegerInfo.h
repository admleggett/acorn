// constantIntegerInfo.h
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

private:
    int32_t value_;
};

#endif // CONSTANTINTEGERINFO_H
