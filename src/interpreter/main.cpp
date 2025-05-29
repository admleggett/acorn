#include <iostream>
#include "../compilerApplication.h"

int main(const int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <source.aco>" << std::endl;
        return 1;
    }
    std::string sourceFile = argv[1];
    //invoke the compiler with the source file
    CompilerApplication compilerApp;
    auto clazz = compilerApp.compile(sourceFile);
    //launch the Java Virtual Machine to run the compiled class

    //@TODO: Handle the case where the class file is not found or cannot be executed
    //@TODO: Update to use the JNI to run the class instead of using system()
    int result = std::system(("java " + clazz).c_str());
    return result == 0 ? 0 : 1;
}
