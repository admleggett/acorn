/**
* @file bigEndianUtil.h
* @brief This file contains the definition of the BigEndianUtil class.
* @details The BigEndianUtil class provides utility functions for working with big-endian byte order.
*/
#ifndef BIGENDIANUTIL_H
#define BIGENDIANUTIL_H
#include <vector>
#include <cstdint>
#include <string>

class BigEndianUtil {
public:
    static void appendUint16(std::vector<uint8_t>& out, uint16_t value) {
        out.push_back(value >> 8);
        out.push_back(value & 0xFF);
    }

    static void appendUint32(std::vector<uint8_t>& out, uint32_t value)
    {
        out.push_back(value >> 24);
        out.push_back((value >> 16) & 0xFF);
        out.push_back((value >> 8) & 0xFF);
        out.push_back(value & 0xFF);
    }

    static void appendString(std::vector<uint8_t>& out, const std::string& str) {
        appendUint16(out, static_cast<uint16_t>(str.size()));
        out.insert(out.end(), str.begin(), str.end());
    }
};
#endif //BIGENDIANUTIL_H
