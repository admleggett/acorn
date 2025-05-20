#ifndef CLASSBYTECODE_H
#define CLASSBYTECODE_H


#include "classFileHeader.h"
#include "constantPool.h"
#include "classHeaderInfo.h"
#include <vector>
#include <cstdint>
#include <memory>

class ClassByteCode : public ByteCodeSerializable {
public:
    ClassByteCode(std::shared_ptr<ClassFileHeader> fileHeader,
                  std::shared_ptr<ConstantPool> constantPool,
                  std::shared_ptr<ClassHeaderInfo> classHeader)
        : fileHeader(std::move(fileHeader)),
          constantPool(std::move(constantPool)),
          classHeader(std::move(classHeader)) {}

    std::vector<uint8_t> serialize() const {
        std::vector<uint8_t> bytes;
        auto append = [&](const std::vector<uint8_t>& part) {
            bytes.insert(bytes.end(), part.begin(), part.end());
        };
        append(fileHeader->serialize());
        append(constantPool->serialize());
        append(classHeader->serialize());
        // append other parts as needed
        return bytes;
    }
private:
    std::shared_ptr<ClassFileHeader> fileHeader;
    std::shared_ptr<ConstantPool> constantPool;
    std::shared_ptr<ClassHeaderInfo> classHeader;
    // Add other members as needed
};

#endif //CLASSBYTECODE_H
