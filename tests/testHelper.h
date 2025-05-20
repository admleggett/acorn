#pragma once
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>

class TestHelper {
public:
    static std::string toHex(const std::vector<uint8_t>& data) {
        std::ostringstream oss;
        for (auto b : data) {
            oss << std::hex << std::setw(2) << std::setfill('0') << (int)b;
        }
        return oss.str();
    }
};

// Macro for hex equality assertion
// This macro compares two byte arrays and prints the expected and actual values in hex format
#define EXPECT_HEX_EQ(val1, val2) \
EXPECT_EQ(TestHelper::toHex(val1), TestHelper::toHex(val2)) \
<< "Expected: " << TestHelper::toHex(val2) << "\nActual:   " << TestHelper::toHex(val1)
