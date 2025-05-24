/**
 * @file classHeaderInfo.h
 * @brief Header file for the ClassHeaderInfo class.
 * @details This class represents a Java class file header.
 * It inherits from ByteCodeSerializable to provide serialization functionality.
 */
#ifndef CLASSHEADERINFO_H
#define CLASSHEADERINFO_H

#include "byteCodeSerializable.h"
#include "bigEndianUtil.h"

class ClassHeaderInfo : public ByteCodeSerializable {
public:
    ClassHeaderInfo(
        uint16_t flags,
        uint16_t this_class,
        uint16_t super_class,
        uint16_t interfaces_count,
        uint16_t fields_count,
        uint16_t methods_count
    )
        : flags_(flags), this_class_(this_class), super_class_(super_class),
          interfaces_count_(interfaces_count), fields_count_(fields_count),
          methods_count_(methods_count) {}

    [[nodiscard]] std::vector<uint8_t> serialize() const override {
        std::vector<uint8_t> bytes;
        BigEndianUtil::appendUint16(bytes, flags_);
        BigEndianUtil::appendUint16(bytes, this_class_);
        BigEndianUtil::appendUint16(bytes, super_class_);
        BigEndianUtil::appendUint16(bytes, interfaces_count_);
        BigEndianUtil::appendUint16(bytes, fields_count_);
        BigEndianUtil::appendUint16(bytes, methods_count_);
        return bytes;
    }
private:
    uint16_t flags_;
    uint16_t this_class_;
    uint16_t super_class_;
    uint16_t interfaces_count_;
    uint16_t fields_count_;
    uint16_t methods_count_;
};


#endif //CLASSHEADERINFO_H
