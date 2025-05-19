/**
 * @file constantUtf8Info.h
 * @brief Header file for the ConstantUtf8Info class.
 * @details This class represents a UTF-8 constant in the constant pool of a Java class file.
 * It inherits from ByteCodeSerializable to provide serialization functionality.
 */
#ifndef CONSTANTUTF8INFO_H
#define CONSTANTUTF8INFO_H
#include <memory>
#include "byteCodeSerializable.h"
#include "bigEndianUtil.h"


class ConstantUtf8Info : public ByteCodeSerializable {
public:

    static constexpr uint8_t TAG = 1;

    explicit ConstantUtf8Info(std::string str)
        : value(std::make_unique<std::string>(std::move(str))) {}

    [[nodiscard]] std::vector<uint8_t> serialize() const override {
        std::vector<uint8_t> bytes;
        bytes.push_back(TAG); // tag for Utf8
        BigEndianUtil::appendUint16(bytes, static_cast<uint16_t>(value->size()));
        return bytes;
    }

private:
    std::unique_ptr<std::string> value;
};


#endif //CONSTANTUTF8INFO_H
