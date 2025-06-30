#include <iostream>
#include <string>
#include <spdlog/spdlog.h>
#include "interpreter.h"
#include "jniJvmLauncher.h"


int main(const int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <source.aco> [--debug]" << std::endl;
        return 1;
    }

    std::string sourceFile = argv[1];
    bool debug = false;

    for (int i = 2; i < argc; ++i) {
        if (std::string(argv[i]) == "--debug") {
            debug = true;
        }
    }

    spdlog::set_level(debug ? spdlog::level::debug : spdlog::level::err);

    auto compilerApp = std::make_unique<CompilerApplication>();
    auto jvmLauncher = std::make_unique<JniJvmLauncher>();
    const auto interpreter =
        std::make_unique<Interpreter>(std::move(compilerApp), std::move(jvmLauncher));

    return interpreter->run(sourceFile);
}
