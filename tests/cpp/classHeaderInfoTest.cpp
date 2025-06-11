#include <gtest/gtest.h>
#include "model/classHeaderInfo.h"
#include "testHelper.h"

TEST(ClassHeaderInfoTest, SerializeProducesExpectedHex) {
    // Example values
    ClassHeaderInfo header(
        0x0021, // flags: public, super
        0x0001, // this_class
        0x0003, // super_class
        0x0000, // interfaces_count
        0x0000, // fields_count
        0x0000 // methods_count
    );

    // Expected bytes: 00 21 00 01 00 03 00 00 00 00 00 00
    std::vector<uint8_t> expected = {
        0x00, 0x21, 0x00, 0x01, 0x00, 0x03,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    };

    auto actual = header.serialize();
    EXPECT_HEX_EQ(actual, expected);
}
