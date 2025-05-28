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
    void write(const std::vector<std::string>& tokens, const std::string& outputFile) const;
    //write the vector of ASTNode statements to the output file
    void write(const std::vector<std::unique_ptr<ASTNode>>& statements, const std::string& outputFile) const;

private:
    std::string className_;
};

#endif //BYTECODEWRITER_H
