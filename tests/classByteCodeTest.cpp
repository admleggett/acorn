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
    auto fileHeader = std::make_shared<ClassFileHeader>();
    auto constantPool = std::make_shared<ConstantPool>();
    auto classHeader = std::make_shared<ClassHeaderInfo>(
        0x0021, // flags
        1,      // this_class
        3,      // super_class
        0,      // interfaces_count
        0,      // fields_count
        1      // methods_count
    );
    auto methodInfo = std::make_shared<MethodInfo>(
        0x0001, // access_flags
        2,      // name_index
        3,      // descriptor_index
        std::vector<std::shared_ptr<ByteCodeSerializable>>()
    );

    ClassByteCode byteCode(fileHeader, constantPool, classHeader, methodInfo);
    std::vector<uint8_t> bytes = byteCode.serialize();

    EXPECT_FALSE(bytes.empty());
    // Optionally, check the size or specific content if you know the expected output
}

// verify that the hex contained in the file is the same as the one generated
TEST(ClassByteCodeTest, SerializeMatchesExpectedHex) {
    ClassFileHeader header;

    // create a constant pool with entries for the classname and the superclass
    auto classInfo = std::make_shared<ConstantClassInfo>(2);
    auto className = std::make_shared<ConstantUtf8Info>("Acorn");
    auto superClassInfo = std::make_shared<ConstantClassInfo>(4);
    auto superClassName = std::make_shared<ConstantUtf8Info>("java/lang/Object");
    auto javaLangSystemInfo = std::make_shared<ConstantClassInfo>(6);
    auto javaLangSystemName = std::make_shared<ConstantUtf8Info>("java/lang/System");
    auto javaIoPrintStreamInfo = std::make_shared<ConstantClassInfo>(8);
    auto javaIoPrintStreamName = std::make_shared<ConstantUtf8Info>("java/io/PrintStream");
    auto outFieldRef = std::make_shared<ConstantFieldInfo>(5, 10);
    auto nameAndType = std::make_shared<ConstantNameAndTypeInfo>(11, 12);
    auto outFieldName = std::make_shared<ConstantUtf8Info>("out");
    auto outFieldDesc = std::make_shared<ConstantUtf8Info>("Ljava/io/PrintStream;");
    auto methodRef = std::make_shared<ConstantMethodInfo>(7, 14);
    auto methodNameAndType = std::make_shared<ConstantNameAndTypeInfo>(15, 16);
    auto methodName = std::make_shared<ConstantUtf8Info>("println");
    auto methodType = std::make_shared<ConstantUtf8Info>("(I)V");
    auto mainName = std::make_shared<ConstantUtf8Info>("main");
    auto mainDesc = std::make_shared<ConstantUtf8Info>("([Ljava/lang/String;)V");
    auto codeName = std::make_shared<ConstantUtf8Info>("Code");
    auto intConstant = std::make_shared<ConstantIntegerInfo>(10);
    auto javaLangSystemOutput = std::make_shared<ConstantClassInfo>(8);


    ConstantPool constantPool;
    constantPool.addEntry(classInfo); // #1
    constantPool.addEntry(className); // #2
    constantPool.addEntry(superClassInfo); // #3
    constantPool.addEntry(superClassName); // #4
    constantPool.addEntry(javaLangSystemInfo); // #5
    constantPool.addEntry(javaLangSystemName); // #6
    constantPool.addEntry(javaIoPrintStreamInfo); // #7
    constantPool.addEntry(javaIoPrintStreamName); // #8
    constantPool.addEntry(outFieldRef); // #9
    constantPool.addEntry(nameAndType); // #10
    constantPool.addEntry(outFieldName); // #11
    constantPool.addEntry(outFieldDesc); // #12
    constantPool.addEntry(methodRef); // #13
    constantPool.addEntry(methodNameAndType); // #14
    constantPool.addEntry(methodName); // #15
    constantPool.addEntry(methodType); // #16
    constantPool.addEntry(mainName); // #17
    constantPool.addEntry(mainDesc); // #18
    constantPool.addEntry(codeName); // #19
    constantPool.addEntry(intConstant); // #20
    constantPool.addEntry(javaLangSystemOutput); // #21

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

    MethodInfo mainMethod(
        0x0009, // access_flags: public static
        17,     // name_index: #17 ("main")
        18,     // descriptor_index: #18 ("([Ljava/lang/String;)V")
        {std::make_shared<CodeAttribute>(codeAttribute)}      // attributes
    );

    ClassByteCode byteCode(std::make_shared<ClassFileHeader>(header),
    std::make_shared<ConstantPool>(constantPool),
    std::make_shared<ClassHeaderInfo>(classHeader),
    std::make_shared<MethodInfo>(mainMethod));

    std::vector<uint8_t> bytes = byteCode.serialize();
    auto filePath = g_testArgs[1] + "/Acorn_class.hex"; // Path to the expected hex file
    auto expectedBytes = TestHelper::readHexTextFile(filePath);
    EXPECT_HEX_EQ(bytes, expectedBytes);
}
