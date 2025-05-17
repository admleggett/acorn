#include "compiler.h"

Compiler::Compiler(std::unique_ptr<Scanner> scanner, std::unique_ptr<ByteCodeWriter> writer)
    : scanner_(std::move(scanner)), writer_(std::move(writer)) {}

void Compiler::compile(const std::string& outputFile) {
    auto tokens = scanner_->tokenize();
    writer_->write(tokens, outputFile);
}
