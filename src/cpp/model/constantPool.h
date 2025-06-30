/**
 * @file constantPool.h
 * @brief Header file for the ConstantPool class.
 * @details A container for constant pool entries in a Java class file.
 */
#ifndef CONSTANTPOOL_H
#define CONSTANTPOOL_H

#include <unordered_map>

#include "constantPoolEntry.h"
#include "byteCodeSerializable.h"
#include "bigEndianUtil.h"
#include <memory>

class ConstantPool : public ByteCodeSerializable {


public:
    // Returns the index (1-based) of the entry, adding it if not present
    uint16_t intern(std::unique_ptr<ConstantPoolEntry> entry) {
        const std::string k = entry->key();
        if (const auto it = indexMap.find(k); it != indexMap.end()) {
            return it->second;
        }
        entries.push_back(std::move(entry));
        const auto idx = static_cast<uint16_t>(entries.size()); // 1-based
        indexMap[k] = idx;
        return idx;
    }

    void addEntry(std::unique_ptr<ConstantPoolEntry> entry) {
        intern(std::move(entry));
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

    [[nodiscard]] const std::unique_ptr<ConstantPoolEntry>& getEntry(const size_t index) const {
        return entries.at(index);
    }

private:
    std::vector<std::unique_ptr<ConstantPoolEntry>> entries;
    std::unordered_map<std::string, uint16_t> indexMap;

};



#endif //CONSTANTPOOL_H
