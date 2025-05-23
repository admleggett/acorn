#pragma once
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
#include <fstream>

class TestHelper {
public:
    static std::string toHex(const std::vector<uint8_t>& data) {
        std::ostringstream oss;
        for (auto b : data) {
            oss << std::hex << std::setw(2) << std::setfill('0') << (int)b;
        }
        return oss.str();
    }

    static std::vector<uint8_t> readHexTextFile(const std::string& path) {
        std::ifstream file(path);
        //throw error if file not found
        if (!file) {
            throw std::runtime_error("Could not open file: " + path);
        }

        std::vector<uint8_t> bytes;
        std::string token;
        while (file >> token) {
            // Skip non-hex tokens (e.g., line numbers, colons)
            if (token.find_first_not_of("0123456789abcdefABCDEF") != std::string::npos)
                continue;
            if (token.length() == 4) { // e.g., "cafe"
                bytes.push_back(static_cast<uint8_t>(std::stoul(token.substr(0, 2), nullptr, 16)));
                bytes.push_back(static_cast<uint8_t>(std::stoul(token.substr(2, 2), nullptr, 16)));
            } else if (token.length() == 2) {
                bytes.push_back(static_cast<uint8_t>(std::stoul(token, nullptr, 16)));
            }
        }
        return bytes;
    }
};

// Macro for hex equality assertion
// This macro compares two byte arrays and prints the expected and actual values in hex format
#define EXPECT_HEX_EQ(val1, val2) \
EXPECT_EQ(TestHelper::toHex(val1), TestHelper::toHex(val2)) \
<< "Expected: " << TestHelper::toHex(val2) << "\nActual:   " << TestHelper::toHex(val1)
