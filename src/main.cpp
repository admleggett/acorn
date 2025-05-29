#include <iostream>
#include <memory>
#include "parser.h"
#include "scanner.h"
#include "byteCodeWriter.h"
#include "compiler.h"
#include "compilerApplication.h"

int main(const int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <source.aco>" << std::endl;
        return 1;
    }

    const std::string sourceFile = argv[1];

    CompilerApplication compiler;

    compiler.compile(sourceFile);

    return 0;
}