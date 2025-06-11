/**
 * file: byteCodeGeneratorVisitor.h
 * brief: Declaration of the ByteCodeGeneratorVisitor class.
 * details: The ByteCodeGeneratorVisitor class is responsible for generating bytecode from the AST nodes.
 * It inherits from ASTVisitor and implements the visit methods for specific node types.
 */
#ifndef BYTECODEGENERATORVISITOR_H
#define BYTECODEGENERATORVISITOR_H
#include "astVisitor.h"
#include "constantPool.h"


class ByteCodeGeneratorVisitor : public ASTVisitor{

public:
    ByteCodeGeneratorVisitor(ConstantPool& constantPool, std::vector<uint8_t>& code)
        : constantPool(constantPool), code(code) {}

    void visit(PrintNode& node) override;
    void visit(IntLiteralNode& node) override;

private:
    ConstantPool& constantPool;
    std::vector<uint8_t>& code;

};



#endif //BYTECODEGENERATORVISITOR_H
