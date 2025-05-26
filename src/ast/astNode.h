#ifndef ASTNODE_H
#define ASTNODE_H

class ASTVisitor; // Forward declaration

class ASTNode {
public:
    virtual ~ASTNode() = default;
    virtual void accept(ASTVisitor& visitor) = 0;
};


#endif //ASTNODE_H
