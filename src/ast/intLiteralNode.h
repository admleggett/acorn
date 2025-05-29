/**
 * @file intLiteralNode.h
 * @brief Declaration of the IntLiteralNode class.
 * @details The IntLiteralNode class represents an integer literal in the abstract syntax tree (AST).
 */
#ifndef INTLITERALNODE_H
#define INTLITERALNODE_H

#include "astNode.h"
#include "astVisitor.h"

class IntLiteralNode final : public ASTNode {
public:
    explicit IntLiteralNode(const int v) : value(v) {}
    void accept(ASTVisitor& visitor) override { visitor.visit(*this); }
    [[nodiscard]] int getValue() const { return value; }
private:
    int value;
};

#endif //INTLITERALNODE_H
