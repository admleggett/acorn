#include "byteCodeWriter.h"
#include <fstream>
#include <vector>
#include <cstdint>
#include "model/classFileHeader.h"

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


    // --- CONSTANT POOL SETUP ---
    // Indices:
    // 1: Class_info (our class), name_index=2
    // 2: Utf8 (our class name)
    // 3: Class_info (java/lang/Object), name_index=4
    // 4: Utf8 ("java/lang/Object")
    // 5: Utf8 ("main")
    // 6: Utf8 ("([Ljava/lang/String;)V")
    // 7: Utf8 ("Code")

    const char* objName = "java/lang/Object";
    size_t objNameLen = 16;
    const char* mainName = "main";
    size_t mainNameLen = 4;
    const char* mainDesc = "([Ljava/lang/String;)V";
    size_t mainDescLen = 22;
    const char* codeName = "Code";
    size_t codeNameLen = 4;

    // Magic number
    //write_u4(0xCAFEBABE);
    // Minor version (0), Major version (52 = Java 8)
    //write_u2(0);
    //write_u2(52);
    ClassFileHeader header;
    write(header);


    // Constant pool count (8: 1 unused, 2 class entries, 2 utf8 entries, 3 for main method)
    write_u2(8);

    // #1: Class_info (tag 7), name_index = 2 (our class)
    outFile.put(7);
    write_u2(2);

    // #2: Utf8_info (tag 1), length, bytes (our class name)
    outFile.put(1);
    write_u2(className_.size());
    outFile.write(className_.c_str(), className_.size());

    // #3: Class_info (tag 7), name_index = 4 (java/lang/Object)
    outFile.put(7);
    write_u2(4);

    // #4: Utf8_info (tag 1), length, bytes ("java/lang/Object")
    outFile.put(1);
    write_u2(objNameLen);
    outFile.write(objName, objNameLen);

    // #5: Utf8_info (tag 1), length, bytes ("main")
    outFile.put(1);
    write_u2(mainNameLen);
    outFile.write(mainName, mainNameLen);

    // #6: Utf8_info (tag 1), length, bytes ("([Ljava/lang/String;)V")
    outFile.put(1);
    write_u2(mainDescLen);
    outFile.write(mainDesc, mainDescLen);

    // #7: Utf8_info (tag 1), length, bytes ("Code")
    outFile.put(1);
    write_u2(codeNameLen);
    outFile.write(codeName, codeNameLen);

    // --- CLASS HEADER ---
    write_u2(0x0021); // public, super
    write_u2(1);      // this_class: #1
    write_u2(3);      // super_class: #3

    write_u2(0);      // interfaces_count
    write_u2(0);      // fields_count

    // --- METHODS ---
    write_u2(1);      // methods_count

    // Method: public static void main(String[] args)
    write_u2(0x0009); // access_flags: public static
    write_u2(5);      // name_index: #5 ("main")
    write_u2(6);      // descriptor_index: #6 ("([Ljava/lang/String;)V")
    write_u2(1);      // attributes_count

    // Attribute: Code
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
    write_u2(0); // attributes_count

    outFile.close();
}
