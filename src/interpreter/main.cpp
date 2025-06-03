#include <iostream>
#include "interpreter.h"

int main(const int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <source.aco>" << std::endl;
        return 1;
    }
    const std::string sourceFile = argv[1];

    CompilerApplication compilerApp;
    const auto interpreter = std::make_unique<Interpreter>(compilerApp);
    return interpreter->run(sourceFile);
}
