#ifndef ASTVISITOR_H
#define ASTVISITOR_H

class PrintNode; // Forward declaration
class IntLiteralNode; // Forward declaration

class ASTVisitor {
public:
    virtual void visit(PrintNode& node) = 0;
    virtual void visit(IntLiteralNode& node) = 0;
    virtual ~ASTVisitor() = default;
};

#endif //ASTVISITOR_H
