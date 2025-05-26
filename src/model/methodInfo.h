/**
 * @file methodInfo.h
 * @brief this file contains the definition of the MethodInfo class.
 * @details MethodInfo represents a method in a Java class file.
 */
#ifndef METHODINFO_H
#define METHODINFO_H

#include <vector>
#include <memory>
#include "byteCodeSerializable.h"
#include "bigEndianUtil.h"

class MethodInfo : public ByteCodeSerializable {
public:
    MethodInfo(uint16_t accessFlags, uint16_t nameIdx, uint16_t descIdx,
               const std::vector<std::shared_ptr<ByteCodeSerializable>>& attrs)
        : accessFlags(accessFlags), nameIndex(nameIdx), descriptorIndex(descIdx), attributes(attrs) {}

    [[nodiscard]] std::vector<uint8_t> serialize() const override {
        std::vector<uint8_t> bytes;
        BigEndianUtil::appendUint16(bytes, accessFlags);
        BigEndianUtil::appendUint16(bytes, nameIndex);
        BigEndianUtil::appendUint16(bytes, descriptorIndex);
        // if attributes not empty then serialize them
        // and append the count of attributes
        if (!attributes.empty())
        {
            BigEndianUtil::appendUint16(bytes, static_cast<uint16_t>(attributes.size()));
            for (const auto& attr : attributes) {
                auto attrBytes = attr->serialize();
                bytes.insert(bytes.end(), attrBytes.begin(), attrBytes.end());
            }
        }
        return bytes;
    }

private:
    uint16_t accessFlags;
    uint16_t nameIndex;
    uint16_t descriptorIndex;
    std::vector<std::shared_ptr<ByteCodeSerializable>> attributes;
};

#endif //METHODINFO_H
