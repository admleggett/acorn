/**
 * @file constantPool.h
 * @brief Header file for the ConstantPool class.
 * @details A container for constant pool entries in a Java class file.
 */
#ifndef CONSTANTPOOL_H
#define CONSTANTPOOL_H

#include "constantPoolEntry.h"
#include "byteCodeSerializable.h"
#include "bigEndianUtil.h"

class ConstantPool : public ByteCodeSerializable {


public:
    void addEntry(const std::shared_ptr<ConstantPoolEntry>& entry) {
        entries.push_back(entry);
    }
    [[nodiscard]] std::vector<uint8_t> serialize() const override {
        std::vector<uint8_t> bytes;

        //add the size of the constant pool
        BigEndianUtil::appendUint16(bytes, static_cast<uint16_t>(entries.size() + 1)); // +1 for the unused entry

        for (const auto& entry : entries) {
            auto entryBytes = entry->serialize();
            bytes.insert(bytes.end(), entryBytes.begin(), entryBytes.end());
        }
        return bytes;
    }

    [[nodiscard]] size_t size() const {
        return entries.size();
    }

    [[nodiscard]] const std::shared_ptr<ConstantPoolEntry>& getEntry(size_t index) const {
        return entries.at(index);
    }

private:
    std::vector<std::shared_ptr<ConstantPoolEntry>> entries;

};



#endif //CONSTANTPOOL_H
