#include "byteCodeWriter.h"
#include <fstream>
#include <vector>
#include <cstdint>
#include <memory>
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

    // Helper lambda to write big-endian values
    auto write_u2 = [&](uint16_t v) {
        outFile.put((v >> 8) & 0xFF);
        outFile.put(v & 0xFF);
    };
    auto write_u4 = [&](uint32_t v) {
        outFile.put((v >> 24) & 0xFF);
        outFile.put((v >> 16) & 0xFF);
        outFile.put((v >> 8) & 0xFF);
        outFile.put(v & 0xFF);
    };
    //lambda to write a byteCodeSerializable object
    auto write = [&](const ByteCodeSerializable& entry) {
        auto bytes = entry.serialize();
        outFile.write(reinterpret_cast<const char*>(bytes.data()), bytes.size());
    };

    ClassFileHeader header;

    // create a constant pool with entries for the classname and the superclass
    auto classInfo = std::make_shared<ConstantClassInfo>(2);
    auto className = std::make_shared<ConstantUtf8Info>(className_);
    auto superClassInfo = std::make_shared<ConstantClassInfo>(4);
    auto superClassName = std::make_shared<ConstantUtf8Info>("java/lang/Object");
    auto mainName = std::make_shared<ConstantUtf8Info>("main");
    auto mainDesc = std::make_shared<ConstantUtf8Info>("([Ljava/lang/String;)V");
    auto codeName = std::make_shared<ConstantUtf8Info>("Code");

    ConstantPool constantPool;
    constantPool.addEntry(classInfo); // #1
    constantPool.addEntry(className); // #2
    constantPool.addEntry(superClassInfo); // #3
    constantPool.addEntry(superClassName); // #4
    constantPool.addEntry(mainName); // #5
    constantPool.addEntry(mainDesc); // #6
    constantPool.addEntry(codeName); // #7

    ClassHeaderInfo classHeader(
        0x0021, // flags: public, super
        1,      // this_class: #1 (our class)
        3,      // super_class: #3 (java/lang/Object)
        0,      // interfaces_count
        0,      // fields_count
        0,      // methods_count
        0       // attributes_count
    );

    ClassByteCode classByteCode(std::make_shared<ClassFileHeader>(header),
        std::make_shared<ConstantPool>(constantPool),
        std::make_shared<ClassHeaderInfo>(classHeader));

    write(classByteCode);

    /*
    // Method: public static void main(String[] args)
    write_u2(0x0009); // access_flags: public static
    write_u2(5);      // name_index: #5 ("main")
    write_u2(6);      // descriptor_index: #6 ("([Ljava/lang/String;)V")
    //write_u2(1);      // attributes_count

    /* Attribute: Code
    write_u2(7);      // attribute_name_index: #7 ("Code")

    // Attribute length: 12 + code_length + exception_table_length*8 + attributes_count*6
    // For empty method: max_stack=1, max_locals=1, code_length=1 (return), exception_table_length=0, attributes_count=0
    uint32_t code_length = 1;
    uint16_t max_stack = 1;
    uint16_t max_locals = 1;
    uint16_t exception_table_length = 0;
    uint16_t code_attributes_count = 0;
    uint32_t attr_len = 12 + code_length;

    write_u4(attr_len);         // attribute_length
    write_u2(max_stack);        // max_stack
    write_u2(max_locals);       // max_locals
    write_u4(code_length);      // code_length
    outFile.put(0xb1);          // return (opcode for 'return' in void method)
    write_u2(exception_table_length); // exception_table_length
    // (no exception table)
    write_u2(code_attributes_count);  // attributes_count

    // --- CLASS ATTRIBUTES ---
    //write_u2(0); // attributes_count
    outFile.close();
    */
}
