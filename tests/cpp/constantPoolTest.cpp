#include <gtest/gtest.h>
#include "model/constantPool.h"
#include "model/constantClassInfo.h"
#include "model/constantUtf8Info.h"
#include "testHelper.h"

TEST(ConstantPoolTest, SerializeProducesExpectedHex) {
    ConstantPool pool;
    // Add: ClassInfo(nameIndex=2), Utf8Info("Test")
    pool.addEntry(std::make_unique<ConstantClassInfo>(2));
    pool.addEntry(std::make_unique<ConstantUtf8Info>("Test"));

    // Expected bytes:
    // 00 03           // constant_pool_count = 3 (2 entries + 1)
    // 07 00 02        // tag=7 (Class), name_index=2
    // 01 00 04 54 65 73 74 // tag=1 (Utf8), length=4, "Test"

    std::vector<uint8_t> expected = {
        0x00, 0x03,
        0x07, 0x00, 0x02,
        0x01, 0x00, 0x04, 0x54, 0x65, 0x73, 0x74
    };

    auto actual = pool.serialize();
    EXPECT_HEX_EQ(actual, expected);
}
