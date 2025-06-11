/**
 * @file constantUtf8Info.h
 * @brief Header file for the ConstantUtf8Info class.
 * @details This class represents a UTF-8 constant in the constant pool of a Java class file.
 * It inherits from ByteCodeSerializable to provide serialization functionality.
 */
#ifndef CONSTANTUTF8INFO_H
#define CONSTANTUTF8INFO_H
#include <memory>
#include "bigEndianUtil.h"
#include "constantPoolEntry.h"


class ConstantUtf8Info : public ConstantPoolEntry {

public:

    explicit ConstantUtf8Info(std::string str)
        : value(std::make_unique<std::string>(std::move(str))) {}

    [[nodiscard]] std::vector<uint8_t> serialize() const override {
        std::vector<uint8_t> bytes;
        // add the tag
        bytes.push_back(getTagAsUint8_t());
        // add the number of bytes in the string
        // the string is UTF-8 encoded, so we need to use the length of the string
        BigEndianUtil::appendUint16(bytes, static_cast<uint16_t>(value->size()));
        //the value needs to be serialized of course
        bytes.insert(bytes.end(), value->begin(), value->end());
        return bytes;
    }

    [[nodiscard]] Tag getTag() const override {
        return Tag::UTF8;
    }

    std::string key() const override {
        return tagToString(getTag()) + ":" + *(this->value);
    }

private:
    std::unique_ptr<std::string> value;
};


#endif //CONSTANTUTF8INFO_H
