#include "byteCodeWriter.h"
#include <fstream>
#include <vector>
#include <cstdint>
#include <memory>

#include "codeAttribute.h"
#include "constantFieldInfo.h"
#include "constantIntegerInfo.h"
#include "constantMethodInfo.h"
#include "constantNameAndTypeInfo.h"
#include "model/classFileHeader.h"
#include "model/constantClassInfo.h"
#include "model/constantUtf8Info.h"
#include "model/constantPool.h"
#include "model/classHeaderInfo.h"
#include "model/classByteCode.h"

ByteCodeWriter::ByteCodeWriter(std::string className) : className_(std::move(className)) {}

void ByteCodeWriter::write(const std::vector<std::string>& tokens, const std::string& outputFile) const
{
    // Write a minimal, valid Java class file (empty class)
    std::ofstream outFile(outputFile, std::ios::binary);
    if (!outFile) {
        throw std::runtime_error("Could not open output file for writing.");
    }

    //lambda to write a byteCodeSerializable object
    auto write = [&](const ByteCodeSerializable& entry) {
        auto bytes = entry.serialize();
        outFile.write(reinterpret_cast<const char*>(bytes.data()), bytes.size());
    };

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

    //get the 2nd token which should be the integer constant to print
    auto intValue = std::stoi(tokens[1]);

    auto intConstant = std::make_shared<ConstantIntegerInfo>(intValue);
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

    write(byteCode);
    outFile.close();
    if (!outFile) {
        throw std::runtime_error("Error writing to output file.");
    }

}
