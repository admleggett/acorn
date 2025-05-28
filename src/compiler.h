#ifndef COMPILER_H
#define COMPILER_H

#include <memory>
#include "scanner.h"
#include "parser.h"
#include "byteCodeWriter.h"

class Compiler {
public:
    Compiler(std::unique_ptr<Scanner> scanner, std::unique_ptr<ByteCodeWriter> writer, std::unique_ptr<Parser> parser);

    void compile(const std::string& outputFile);
private:
    std::unique_ptr<Scanner> scanner_;
    std::unique_ptr<ByteCodeWriter> writer_;
    std::unique_ptr<Parser> parser_;
};

#endif //COMPILER_H
