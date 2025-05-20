/**
* @file constantPoolEntry.h
* @brief Header file for the ConstantPoolEntry class.
* @details This class represents an entry in the constant pool of a Java class file.
*/
#ifndef CONSTANTPOOLENTRY_H
#define CONSTANTPOOLENTRY_H

#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include "byteCodeSerializable.h"


class ConstantPoolEntry : public ByteCodeSerializable {
public:
    enum class Tag {
        UTF8 = 1,
        CLASS = 7,
        FIELD_REF = 9,
        METHOD_REF = 10,
        STRING = 8,
        };

    virtual ~ConstantPoolEntry() = default;
    virtual Tag getTag() const = 0;

    uint8_t getTagAsUint8_t() const {
        return static_cast<uint8_t>(getTag());
    }


};


#endif //CONSTANTPOOLENTRY_H
