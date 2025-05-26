/**
 * @file classByteCode.h
 * @brief This file contains the definition of the ClassByteCode class.
 * @details ClassByteCode is a concrete implementation of ByteCodeSerializable that represents a Java class file's bytecode.
 * It includes all constituent parts of a class file, such as the class file header, constant pool, class header info, and method info.
 *
 */
#ifndef CLASSBYTECODE_H
#define CLASSBYTECODE_H


#include "classFileHeader.h"
#include "constantPool.h"
#include "classHeaderInfo.h"
#include <vector>
#include <cstdint>
#include <iostream>
#include <memory>
#include "bigEndianUtil.h"
#include "methodInfo.h"

class ClassByteCode : public ByteCodeSerializable {
public:
    ClassByteCode(std::shared_ptr<ClassFileHeader> fileHeader,
                  std::shared_ptr<ConstantPool> constantPool,
                  std::shared_ptr<ClassHeaderInfo> classHeader,
                  std::shared_ptr<MethodInfo> methodInfo)
        : fileHeader(std::move(fileHeader)),
          constantPool(std::move(constantPool)),
          classHeader(std::move(classHeader)),
            methodInfo(std::move(methodInfo)) {}

    [[nodiscard]] std::vector<uint8_t> serialize() const override {
        std::vector<uint8_t> bytes;
        auto append = [&](const std::vector<uint8_t>& part) {
            bytes.insert(bytes.end(), part.begin(), part.end());
        };
        append(fileHeader->serialize());
        append(constantPool->serialize());
        append(classHeader->serialize());
        append(methodInfo->serialize());
        // append other parts as needed

        //append the attributes count
        BigEndianUtil::appendUint16(bytes, attributes_count_);

        //if debug print to std out as hex
        //if (debug) {
        //std::cout << "Serialized ClassByteCode: ";
        //printHex(bytes);
        //}

        return bytes;
    }
private:
    std::shared_ptr<ClassFileHeader> fileHeader;
    std::shared_ptr<ConstantPool> constantPool;
    std::shared_ptr<ClassHeaderInfo> classHeader;
    std::shared_ptr<MethodInfo> methodInfo;
    // Add other members as needed
    uint16_t attributes_count_ = 0; // Placeholder for attributes count, if needed
};

#endif //CLASSBYTECODE_H
