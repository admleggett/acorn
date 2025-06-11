/**
 * @file byteCodeWriter.h
 * @brief Declaration of the ByteCodeWriter class.
 *
 * @details The ByteCodeWriter class is responsible for writing bytecode to a file using a vector of ASTNode statements.
 */
#ifndef BYTECODEWRITER_H
#define BYTECODEWRITER_H

#include <string>
#include <vector>
#include <fstream>
#include <cstdint>
#include "model/byteCodeSerializable.h"
#include "ast/astNode.h"
#include <memory>

class ByteCodeWriter {
public:
    explicit ByteCodeWriter(std::string className);
    //write the vector of ASTNode statements to the output file
    void write(const std::vector<std::unique_ptr<ASTNode>>& statements, const std::string& outputFile) const;

private:
    std::string className_;
};

#endif //BYTECODEWRITER_H
