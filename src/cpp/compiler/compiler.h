/**
 * @file compiler.h
 * @brief Declaration of the Compiler class.
 * @details The Compiler class is responsible for compiling source code into bytecode using a scanner, parser, and bytecode writer.
 */
#ifndef COMPILER_H
#define COMPILER_H

#include <memory>
#include "scanner.h"
#include "parser.h"
#include "byteCodeWriter.h"

class Compiler {
public:
    Compiler(std::unique_ptr<Scanner> scanner, std::unique_ptr<ByteCodeWriter> writer, std::unique_ptr<Parser> parser);

    void compile(const std::string& outputFile) const;
private:
    std::unique_ptr<Scanner> scanner_;
    std::unique_ptr<ByteCodeWriter> writer_;
    std::unique_ptr<Parser> parser_;
};

#endif //COMPILER_H
