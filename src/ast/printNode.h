#ifndef PRINTNODE_H
#define PRINTNODE_H

#include <memory>
#include "astNode.h"
#include "astVisitor.h"


class PrintNode final : public ASTNode {
public:
    explicit PrintNode(std::unique_ptr<ASTNode> val) : value(std::move(val)) {}
    void accept(ASTVisitor& visitor) override { visitor.visit(*this); }
    [[nodiscard]] ASTNode* getValue() const { return value.get(); }
private:
    std::unique_ptr<ASTNode> value; // The value to be printed, can be any ASTNode type
};

#endif //PRINTNODE_H
