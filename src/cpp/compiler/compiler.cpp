#include "compiler.h"

#include <iostream>

Compiler::Compiler(std::unique_ptr<Scanner> scanner, std::unique_ptr<ByteCodeWriter> writer, std::unique_ptr<Parser> parser)
: scanner_(std::move(scanner)), writer_(std::move(writer)), parser_(std::move(parser)) {}


void Compiler::compile(const std::string& outputFile) const
{
    auto statements = parser_->parse();
    writer_->write(statements, outputFile);
}
