

#ifndef CODEATTRIBUTE_H
#define CODEATTRIBUTE_H

#include <vector>
#include "byteCodeSerializable.h"
#include "bigEndianUtil.h"

class CodeAttribute : public ByteCodeSerializable {
public:
    CodeAttribute(uint16_t nameIdx,
                  uint16_t maxStack,
                  uint16_t maxLocals,
                  const std::vector<uint8_t>& code)
        : attributeNameIndex(nameIdx),
          maxStack(maxStack),
          maxLocals(maxLocals),
          code(code) {}

    std::vector<uint8_t> serialize() const override {
        std::vector<uint8_t> bytes;
        BigEndianUtil::appendUint16(bytes, attributeNameIndex);
        uint32_t attributeLength = 2 + 2 + 4 + code.size() + 2 + 0 + 2 + 0;
        BigEndianUtil::appendUint32(bytes, attributeLength);
        BigEndianUtil::appendUint16(bytes, maxStack);
        BigEndianUtil::appendUint16(bytes, maxLocals);
        BigEndianUtil::appendUint32(bytes, static_cast<uint32_t>(code.size()));
        bytes.insert(bytes.end(), code.begin(), code.end());
        BigEndianUtil::appendUint16(bytes, 0); // exception_table_length
        BigEndianUtil::appendUint16(bytes, 0); // attributes_count
        return bytes;
    }

private:
    uint16_t attributeNameIndex;
    uint16_t maxStack;
    uint16_t maxLocals;
    std::vector<uint8_t> code;
};
#endif //CODEATTRIBUTE_H
