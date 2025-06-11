/**
 * @file astVisitor.h
 * @brief Declaration of the ASTVisitor class.
 * @details The ASTVisitor class is an abstract base class that defines the interface for visiting nodes in an abstract syntax tree (AST).
 */
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
