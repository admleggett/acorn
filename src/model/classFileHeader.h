/**
* @file classFileHeader.h
* @brief Header file for the ClassFileHeader class.
* @details This class represents the header of a Java class file.
* It inherits from ByteCodeSerializable to provide serialization functionality.
*/
#ifndef CLASSFILEHEADER_H
#define CLASSFILEHEADER_H
#include "byteCodeSerializable.h"
#include "bigEndianUtil.h"

// ClassFileHeader.h
class ClassFileHeader : public ByteCodeSerializable {
public:
    explicit ClassFileHeader(
            uint16_t minor_version = 0, uint16_t major_version = 52)
        : minor_version_(minor_version), major_version_(major_version) {}

    [[nodiscard]] std::vector<uint8_t> serialize() const override {
        std::vector<uint8_t> bytes;
        BigEndianUtil::appendUint32(bytes, magic); // magic
        BigEndianUtil::appendUint16(bytes, minor_version_);
        BigEndianUtil::appendUint16(bytes, major_version_);
        return bytes;
    }
private:
    uint32_t magic = 0xCAFEBABE; // Magic number for Java class files
    uint16_t minor_version_;
    uint16_t major_version_;
};

#endif //CLASSFILEHEADER_H
