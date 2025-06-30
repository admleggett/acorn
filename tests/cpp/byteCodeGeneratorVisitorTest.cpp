#include <gtest/gtest.h>
#include "ast/byteCodeGeneratorVisitor.h"
#include "ast/printNode.h"
#include "ast/intLiteralNode.h"
#include "model/constantPool.h"

TEST (ByteCodeGeneratorVisitorTest, VisitPrintNodeGeneratesBytecode) {
    ConstantPool constantPool;
    std::vector<uint8_t> code;
    ByteCodeGeneratorVisitor visitor(constantPool, code);

    // Create a PrintNode with an IntLiteralNode as its value
    auto intLiteralNode = std::make_unique<IntLiteralNode>(42);
    PrintNode printNode(std::move(intLiteralNode));

    // Visit the PrintNode
    printNode.accept(visitor);

    // Check that the code vector is not empty (indicating bytecode was generated)
    EXPECT_FALSE(code.empty());
}
