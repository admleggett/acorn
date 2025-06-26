#include "interpreter.h"
#include "jniJvmLauncher.h"
#include <spdlog/spdlog.h>

Interpreter::Interpreter(std::unique_ptr<ICompilerApplication> compilerApp,
                         std::unique_ptr<IJvmLauncher> jvmLauncher)
    : compilerApp_(std::move(compilerApp)), jvmLauncher_(std::move(jvmLauncher)) {}

int Interpreter::run(const std::string& sourceFile) const
{
    spdlog::debug("Running interpreter with source file: {}", sourceFile);
    // Compile the source file using the CompilerApplication
    auto clazz = compilerApp_->compile(sourceFile);

    spdlog::debug("Interpreter running class: {}", clazz);
    // Launch the JVM with the compiled class
    return jvmLauncher_->launch(clazz);
}
