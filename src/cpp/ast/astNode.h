/**
 * @file astNode.h
 * @brief Declaration of the ASTNode class.
 *
 * This file declares the ASTNode class, which serves as the base class for all nodes in the abstract syntax tree (AST).
 * It supports the visitor pattern for traversing the AST.
 */
#ifndef ASTNODE_H
#define ASTNODE_H

class ASTVisitor; // Forward declaration

class ASTNode {
public:
    virtual ~ASTNode() = default;
    virtual void accept(ASTVisitor& visitor) = 0;
};


#endif //ASTNODE_H
