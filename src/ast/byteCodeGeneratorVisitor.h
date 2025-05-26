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
