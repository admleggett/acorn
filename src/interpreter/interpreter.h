#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "../compilerApplication.h"

class Interpreter {

public:
    explicit Interpreter(CompilerApplication& app);
    ~Interpreter() = default;

    int run(std::string sourceFile);

private:
    CompilerApplication& compilerApp;
};



#endif //INTERPRETER_H
