/**
 * @file constantClassInfo.h
 * @brief Header file for the ConstantClassInfo class.
 * @details This class represents an entry in the constant pool of a Java class file.
 * It inherits from ByteCodeSerializable to provide serialization functionality.
 */
#ifndef CONSTANTCLASSINFO_H
#define CONSTANTCLASSINFO_H

#include <memory>
#include "byteCodeSerializable.h"
#include "bigEndianUtil.h"

class ConstantClassInfo : public ByteCodeSerializable {

public:

    static constexpr uint8_t TAG = 7;

    explicit ConstantClassInfo(std::string name)
        : name(std::make_unique<std::string>(std::move(name))) {}

    [[nodiscard]] std::vector<uint8_t> serialize() const override {
        std::vector<uint8_t> bytes;
        bytes.push_back(TAG); // tag for Class
        BigEndianUtil::appendUint16(bytes, static_cast<uint16_t>(name->size()));
        return bytes;
    }

private:
    std::unique_ptr<std::string> name;
};

#endif //CONSTANTCLASSINFO_H
