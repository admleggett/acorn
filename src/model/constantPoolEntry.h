/**
* @file constantPoolEntry.h
* @brief Header file for the ConstantPoolEntry class.
* @details This class represents an entry in the constant pool of a Java class file.
*/
#ifndef CONSTANTPOOLENTRY_H
#define CONSTANTPOOLENTRY_H

#include <vector>
#include <string>
#include "byteCodeSerializable.h"
#include "bigEndianUtil.h"


class ConstantPoolEntry : public ByteCodeSerializable {
public:
    enum class Tag {
        UTF8 = 1,
        CLASS = 7,
        FIELD_REF = 9,
        METHOD_REF = 10,
        STRING = 8,
        NAME_AND_TYPE = 12,
        INTEGER = 3
        };

    virtual ~ConstantPoolEntry() = default;
    virtual Tag getTag() const = 0;
    virtual std::string key() const = 0;

    uint8_t getTagAsUint8_t() const {
        return static_cast<uint8_t>(getTag());
    }

protected:
    std::vector<uint8_t> serializeWithTagAndIndices(std::initializer_list<uint16_t> indices) const {
        std::vector<uint8_t> bytes;
        bytes.push_back(getTagAsUint8_t());
        for (auto idx : indices) {
            auto idxBytes = BigEndianUtil::toBigEndianBytes(idx);
            bytes.insert(bytes.end(), idxBytes.begin(), idxBytes.end());
        }
        return bytes;
    }

    static std::string tagToString(const Tag tag) {
        switch (tag) {
            case Tag::UTF8: return "UTF8";
            case Tag::CLASS: return "CLASS";
            case Tag::FIELD_REF: return "FIELD_REF";
            case Tag::METHOD_REF: return "METHOD_REF";
            case Tag::STRING: return "STRING";
            case Tag::NAME_AND_TYPE: return "NAME_AND_TYPE";
            case Tag::INTEGER: return "INTEGER";
            default: return "UNKNOWN";
        }
    }

};


#endif //CONSTANTPOOLENTRY_H
