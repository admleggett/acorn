/**
 * @file constantClassInfo.h
 * @brief Header file for the ConstantClassInfo class.
 * @details This class represents an entry in the constant pool of a Java class file.
 * It inherits from ByteCodeSerializable to provide serialization functionality.
 */
#ifndef CONSTANTCLASSINFO_H
#define CONSTANTCLASSINFO_H

#include <memory>
#include "bigEndianUtil.h"
#include "constantPoolEntry.h"

class ConstantClassInfo : public ConstantPoolEntry {

public:

    explicit ConstantClassInfo(uint16_t nameIndex)
        : nameIndex(nameIndex) {}

    [[nodiscard]] std::vector<uint8_t> serialize() const override {
        std::vector<uint8_t> bytes;
        // The tag to create a class is 07.
        // The class constant pool entry is three bytes.
        // One for the tag and two for an index pointing to a UTF8 entry in the constant pool.
        bytes.push_back(getTagAsUint8_t());
        auto nameIndexBytes = BigEndianUtil::toBigEndianBytes(nameIndex);
        bytes.insert(bytes.end(), nameIndexBytes.begin(), nameIndexBytes.end());
        return bytes;
    }

    [[nodiscard]] Tag getTag() const override {
        return Tag::CLASS;
    }

private:
    uint16_t nameIndex;





};

#endif //CONSTANTCLASSINFO_H
