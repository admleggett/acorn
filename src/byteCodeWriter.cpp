#include "byteCodeWriter.h"

ByteCodeWriter::ByteCodeWriter(std::string className) : className_(std::move(className)) {}

void ByteCodeWriter::write(const std::vector<std::string>& tokens, const std::string& outputFile) {
    // TODO: Implement Java bytecode generation and file writing
}
