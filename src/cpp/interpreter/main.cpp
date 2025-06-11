#include <iostream>
#include "interpreter.h"
#include "jniJvmLauncher.h"

int main(const int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <source.aco>" << std::endl;
        return 1;
    }
    const std::string sourceFile = argv[1];

    auto compilerApp = std::make_unique<CompilerApplication>();
    auto jvmLauncher = std::make_unique<JniJvmLauncher>();
    const auto interpreter =
        std::make_unique<Interpreter>(std::move(compilerApp), std::move(jvmLauncher));
    return interpreter->run(sourceFile);
}
