#include "byteCodeGeneratorVisitor.h"
#include <iostream>

#include "model/constantIntegerInfo.h"
#include "printNode.h"
#include "intLiteralNode.h"


void ByteCodeGeneratorVisitor::visit(PrintNode& node) {
    //Print requires multiple constant pool entries
    // 1. The class of the method to call (java/lang/System)
    // 2. The method to call (println)
    // 3. The field to access (java/lang/System.out)
    // 4. The type of the field (Ljava/io/PrintStream;)
    // 5. The integer value to print (as an IntLiteralNode)

    node.getValue()->accept(*this); // Visit the value node
}

void ByteCodeGeneratorVisitor::visit(IntLiteralNode& node) {
    // create a ConstantIntegerInfo entry with the value
    auto entry = std::make_shared<ConstantIntegerInfo>(node.getValue());
    // Add the entry into the constant pool
    auto idx = this->constantPool.intern(entry);
    // Add the ldc instruction to the code vector
    code.push_back(0x12); // ldc instruction opcode - 12
    // Add the index of the constant integer to the code vector
    BigEndianUtil::appendUint16(code, idx); // Append the index of the constant integer to the code vector
}
