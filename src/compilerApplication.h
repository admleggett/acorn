/**
 * @file compilerApplication.h
 * @brief Declaration of the CompilerApplication class.
 * @details The CompilerApplication class is responsible for compiling a source file into bytecode.
 */
#ifndef COMPILERAPPLICATION_H
#define COMPILERAPPLICATION_H

#include <iostream>
#include <memory>
#include <string>
#include "parser.h"
#include "scanner.h"
#include "byteCodeWriter.h"
#include "compiler.h"

class ICompilerApplication
{
public:
    virtual ~ICompilerApplication() = default;
    virtual std::string compile(std::string sourceFile) = 0;
};

class CompilerApplication : public ICompilerApplication
{

public:

    std::string compile(std::string sourceFile) override{

        auto sourceFileName = sourceFile.substr(sourceFile.find_last_of("/\\") + 1);

        auto dotPos = sourceFileName.find_last_of('.');

        if (dotPos != std::string::npos) {
            sourceFileName = sourceFileName.substr(0, dotPos);
        }

        if (!sourceFileName.empty()) {
            sourceFileName[0] = std::toupper(sourceFileName[0]);
        }

        auto className = sourceFileName;
        auto classFileName = className + ".class";
        // Create a scanner to read the source file
        auto scanner = std::make_unique<Scanner>(sourceFile);

        // Create a parser to parse the tokens from the scanner
        auto parser = std::make_unique<Parser>(scanner->tokenize());

        // Create a bytecode writer to write the generated bytecode
        auto writer = std::make_unique<ByteCodeWriter>(className);

        // Create a compiler instance with the scanner, parser, and writer
        Compiler compiler(std::move(scanner), std::move(writer), std::move(parser));
        // Compile the source file to bytecode

        compiler.compile(classFileName);

        return className;
    }

};

#endif
