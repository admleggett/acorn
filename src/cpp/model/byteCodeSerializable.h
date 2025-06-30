/**
* @file byteCodeSerializable.h
* @brief This file contains the definition of the ByteCodeSerializable class.
* @details The ByteCodeSerializable class is an abstract base class that provides a
* pure virtual function for serializing objects to a bytecode format. It is intended to be
* used as a base class for other classes that need to implement serialization functionality.
*/
#ifndef BYTECODESERIALIZABLE_H
#define BYTECODESERIALIZABLE_H

#include <vector>
#include <cstdint>

class ByteCodeSerializable {
public:
    virtual ~ByteCodeSerializable() = default;
    [[nodiscard]] virtual std::vector<uint8_t> serialize() const = 0;

    //helper function to debug a byte array as hex
    static void printHex(const std::vector<uint8_t>& bytes) {
        for (const auto& byte : bytes) {
            printf("%02x ", byte);
        }
        printf("\n");
    }
};

#endif //BYTECODESERIALIZABLE_H
