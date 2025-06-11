#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "jvmLauncher.h"
#include "../compilerApplication.h"

class Interpreter {

public:
    explicit Interpreter(std::unique_ptr<ICompilerApplication> compilerApp,
                        std::unique_ptr<IJvmLauncher> jvmLauncher);
    ~Interpreter() = default;

    [[nodiscard]] int run(const std::string& sourceFile) const;

private:
    std::unique_ptr<ICompilerApplication> compilerApp_;
    std::unique_ptr<IJvmLauncher> jvmLauncher_;
};



#endif //INTERPRETER_H
