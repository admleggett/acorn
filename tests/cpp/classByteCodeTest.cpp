#include <gtest/gtest.h>
#include "model/classByteCode.h"
#include "model/classFileHeader.h"
#include "model/constantPool.h"
#include "model/constantClassInfo.h"
#include "model/constantUtf8Info.h"
#include <memory>

#include "codeAttribute.h"
#include "constantFieldInfo.h"
#include "constantIntegerInfo.h"
#include "constantMethodInfo.h"
#include "constantNameAndTypeInfo.h"
#include "testHelper.h"

// Declare the global variable
extern std::vector<std::string> g_testArgs;

TEST(ClassByteCodeTest, SerializeProducesNonEmptyOutput) {
    auto fileHeader = std::make_unique<ClassFileHeader>();
    auto constantPool = std::make_unique<ConstantPool>();
    auto classHeader = std::make_unique<ClassHeaderInfo>(
        0x0021, // flags
        1,      // this_class
        3,      // super_class
        0,      // interfaces_count
        0,      // fields_count
        1      // methods_count
    );
    auto methodInfo = std::make_unique<MethodInfo>(
        0x0001, // access_flags
        2,      // name_index
        3,      // descriptor_index
        std::vector<std::unique_ptr<ByteCodeSerializable>>()
    );

    ClassByteCode byteCode(std::move(fileHeader), std::move(constantPool), std::move(classHeader), std::move(methodInfo));
    std::vector<uint8_t> bytes = byteCode.serialize();

    EXPECT_FALSE(bytes.empty());
    // Optionally, check the size or specific content if you know the expected output
}

// verify that the hex contained in the file is the same as the one generated
TEST(ClassByteCodeTest, SerializeMatchesExpectedHex) {
    ClassFileHeader header;

    // create a constant pool with entries for the classname and the superclass
    auto classInfo = std::make_unique<ConstantClassInfo>(2);
    auto className = std::make_unique<ConstantUtf8Info>("Acorn");
    auto superClassInfo = std::make_unique<ConstantClassInfo>(4);
    auto superClassName = std::make_unique<ConstantUtf8Info>("java/lang/Object");
    auto javaLangSystemInfo = std::make_unique<ConstantClassInfo>(6);
    auto javaLangSystemName = std::make_unique<ConstantUtf8Info>("java/lang/System");
    auto javaIoPrintStreamInfo = std::make_unique<ConstantClassInfo>(8);
    auto javaIoPrintStreamName = std::make_unique<ConstantUtf8Info>("java/io/PrintStream");
    auto outFieldRef = std::make_unique<ConstantFieldInfo>(5, 10);
    auto nameAndType = std::make_unique<ConstantNameAndTypeInfo>(11, 12);
    auto outFieldName = std::make_unique<ConstantUtf8Info>("out");
    auto outFieldDesc = std::make_unique<ConstantUtf8Info>("Ljava/io/PrintStream;");
    auto methodRef = std::make_unique<ConstantMethodInfo>(7, 14);
    auto methodNameAndType = std::make_unique<ConstantNameAndTypeInfo>(15, 16);
    auto methodName = std::make_unique<ConstantUtf8Info>("println");
    auto methodType = std::make_unique<ConstantUtf8Info>("(I)V");
    auto mainName = std::make_unique<ConstantUtf8Info>("main");
    auto mainDesc = std::make_unique<ConstantUtf8Info>("([Ljava/lang/String;)V");
    auto codeName = std::make_unique<ConstantUtf8Info>("Code");
    auto intConstant = std::make_unique<ConstantIntegerInfo>(10);
    auto javaLangSystemOutput = std::make_unique<ConstantClassInfo>(8);


    ConstantPool constantPool;
    constantPool.addEntry(std::move(classInfo));            // #1
    constantPool.addEntry(std::move(className));            // #2
    constantPool.addEntry(std::move(superClassInfo));       // #3
    constantPool.addEntry(std::move(superClassName));       // #4
    constantPool.addEntry(std::move(javaLangSystemInfo));   // #5
    constantPool.addEntry(std::move(javaLangSystemName));   // #6
    constantPool.addEntry(std::move(javaIoPrintStreamInfo));// #7
    constantPool.addEntry(std::move(javaIoPrintStreamName));// #8
    constantPool.addEntry(std::move(outFieldRef));          // #9
    constantPool.addEntry(std::move(nameAndType));          // #10
    constantPool.addEntry(std::move(outFieldName));         // #11
    constantPool.addEntry(std::move(outFieldDesc));         // #12
    constantPool.addEntry(std::move(methodRef));            // #13
    constantPool.addEntry(std::move(methodNameAndType));    // #14
    constantPool.addEntry(std::move(methodName));           // #15
    constantPool.addEntry(std::move(methodType));           // #16
    constantPool.addEntry(std::move(mainName));             // #17
    constantPool.addEntry(std::move(mainDesc));             // #18
    constantPool.addEntry(std::move(codeName));             // #19
    constantPool.addEntry(std::move(intConstant));          // #20

    ClassHeaderInfo classHeader(
        0x0021, // flags: public, super
        1,      // this_class: #1 (our class)
        3,      // super_class: #3 (java/lang/Object)
        0,      // interfaces_count
        0,      // fields_count
        1     // methods_count
    );

    CodeAttribute codeAttribute(
        19, // name_index: #19 ("Code")
        2,  // max_stack: 2 (for getstatic + ldc)
        1,  // max_locals: 1 (for main's String[] arg)
        {
            0xb2, 0x00, 0x09, // getstatic #9
            0x12, 0x14,       // ldc #20
            0xb6, 0x00, 0x0d, // invokevirtual #13
            0xb1, 0X00              // return
        }
    );

    std::vector<std::unique_ptr<ByteCodeSerializable>> attributes;
    attributes.push_back(std::make_unique<CodeAttribute>(std::move(codeAttribute)));

    MethodInfo mainMethod(
        0x0009,
        17,
        18,
        std::move(attributes)
    );

    ClassByteCode byteCode(std::make_unique<ClassFileHeader>(header),
    std::make_unique<ConstantPool>(std::move(constantPool)),
    std::make_unique<ClassHeaderInfo>(std::move(classHeader)),
    std::make_unique<MethodInfo>(std::move(mainMethod)));

    std::vector<uint8_t> bytes = byteCode.serialize();
    auto filePath = g_testArgs[1] + "/Acorn_class.hex"; // Path to the expected hex file
    auto expectedBytes = TestHelper::readHexTextFile(filePath);
    EXPECT_HEX_EQ(bytes, expectedBytes);
}
