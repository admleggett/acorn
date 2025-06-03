#include "interpreter.h"

#include "jniJvmLauncher.h"
#include "systemJvmLauncher.h"

Interpreter::Interpreter(CompilerApplication& app) : compilerApp(app) {
    // Constructor implementation
}

int Interpreter::run(std::string sourceFile) {

    // Compile the source file using the CompilerApplication
    auto clazz = compilerApp.compile(sourceFile);
    //SystemJvmLauncher jvmLauncher;
    JniJvmLauncher jvmLauncher;
    // Launch the JVM with the compiled class
    return jvmLauncher.launch(clazz);
}