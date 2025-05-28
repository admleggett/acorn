#include <iostream>
#include <memory>
#include "parser.h"
#include "scanner.h"
#include "byteCodeWriter.h"
#include "compiler.h"

int main(const int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <source.aco>" << std::endl;
        return 1;
    }

    std::string sourceFile = argv[1];
    auto scanner = std::make_unique<Scanner>(sourceFile);
    auto writer = std::make_unique<ByteCodeWriter>("Acorn");
    auto parser = std::make_unique<Parser>(scanner->tokenize());

    Compiler compiler(std::move(scanner), std::move(writer), std::move(parser));
    compiler.compile("Acorn.class");

    return 0;
}