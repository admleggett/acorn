#include "byteCodeGeneratorVisitor.h"

#include <constantClassInfo.h>
#include <constantFieldInfo.h>
#include <constantMethodInfo.h>
#include <constantNameAndTypeInfo.h>
#include <constantUtf8Info.h>
#include <iostream>

#include "model/constantIntegerInfo.h"
#include "printNode.h"
#include "intLiteralNode.h"


void ByteCodeGeneratorVisitor::visit(PrintNode& node) {
    //Print requires multiple constant pool entries
    // 1. The class of the method to call (java/lang/System)
    // create a utf8 constant entry for the class name
    std::unique_ptr<ConstantPoolEntry> className = std::make_unique<ConstantUtf8Info>("java/lang/System");
    // add the class name to the constant pool
    auto classNameIdx = this->constantPool.intern(std::move(className));
    // create a constant class info entry for the class
    std::unique_ptr<ConstantPoolEntry> classEntry = std::make_unique<ConstantClassInfo>(classNameIdx);
    // Add the class entry into the constant pool
    auto classEntryIdx = this->constantPool.intern(std::move(classEntry));

    // 2. The class of the field (java/io/PrintStream)
    std::unique_ptr<ConstantPoolEntry> fieldClassName = std::make_unique<ConstantUtf8Info>("java/io/PrintStream");
    auto fieldClassNameIdx = this->constantPool.intern(std::move(fieldClassName));

    // 3. The field name (out)
    std::unique_ptr<ConstantPoolEntry> fieldName = std::make_unique<ConstantUtf8Info>("out");
    auto fieldNameIdx = this->constantPool.intern(std::move(fieldName));
    // 4. The field descriptor (Ljava/io/PrintStream;)
    std::unique_ptr<ConstantPoolEntry> fieldDesc = std::make_unique<ConstantUtf8Info>("Ljava/io/PrintStream;");
    auto fieldDescIdx = this->constantPool.intern(std::move(fieldDesc));

    // 5. The name and type of the field (out:Ljava/io/PrintStream;) indexed by a name and type info entry
    std::unique_ptr<ConstantPoolEntry> nameAndType = std::make_unique<ConstantNameAndTypeInfo>(fieldNameIdx, fieldDescIdx);
    auto nameAndTypeIdx = this->constantPool.intern(std::move(nameAndType));

    // 6. The field reference - class: java/lang/System, name and type: out:Ljava/io/PrintStream;
    std::unique_ptr<ConstantPoolEntry> fieldRef = std::make_unique<ConstantFieldInfo>(classEntryIdx, nameAndTypeIdx);
    auto fieldRefIdx = this->constantPool.intern(std::move(fieldRef));

    // 7. The method name (println)
    std::unique_ptr<ConstantPoolEntry> methodName = std::make_unique<ConstantUtf8Info>("println");
    auto methodNameIdx = this->constantPool.intern(std::move(methodName));

    // 8. The method descriptor ((I)V)
    std::unique_ptr<ConstantPoolEntry> methodDesc = std::make_unique<ConstantUtf8Info>("(I)V");
    auto methodDescIdx = this->constantPool.intern(std::move(methodDesc));

    // 9. The name and type of the method (println:(I)V) indexed by a name and type info entry
    std::unique_ptr<ConstantPoolEntry> methodNameAndType = std::make_unique<ConstantNameAndTypeInfo>(methodNameIdx, methodDescIdx);
    auto methodNameAndTypeIdx = this->constantPool.intern(std::move(methodNameAndType));

    // 10. The class of the method (java/io/PrintStream)
    std::unique_ptr<ConstantPoolEntry> methodClassEntry = std::make_unique<ConstantClassInfo>(fieldClassNameIdx);
    auto methodClassEntryIdx = this->constantPool.intern(std::move(methodClassEntry));

    // 11. The method reference - class: java/io/PrintStream, name and type: println:(I)V
    std::unique_ptr<ConstantPoolEntry> methodRef = std::make_unique<ConstantMethodInfo>(methodClassEntryIdx, methodNameAndTypeIdx);
    auto methodRefIdx = this->constantPool.intern(std::move(methodRef));

    // add the code to the code vector
    // 1. Get static field - java/lang/System.out
    code.push_back(0xb2); // getstatic instruction opcode - 0xb2
    BigEndianUtil::appendUint16(code, fieldRefIdx); // Append the index of the field reference to the code vector
    // 2. Load the integer value onto the stack
    node.getValue()->accept(*this); // Visit the value node
    // 3. Invoke the method - println(I)V
    code.push_back(0xb6); // invokevirtual instruction opcode - 0xb6
    BigEndianUtil::appendUint16(code, methodRefIdx); // Append the index of the method name and type to the code vector

    //For now add a return instruction to the code vector
    code.push_back(0xb1); // return instruction opcode - 0xb1

}

void ByteCodeGeneratorVisitor::visit(IntLiteralNode& node) {
    // create a ConstantIntegerInfo entry with the value
    std::unique_ptr<ConstantPoolEntry> entry = std::make_unique<ConstantIntegerInfo>(node.getValue());
    // Add the entry into the constant pool
    const auto idx = this->constantPool.intern(std::move(entry));
    // Add the ldc instruction to the code vector
    code.push_back(0x12); // ldc instruction opcode - 12
    // Add the index of the constant integer to the code vector
    code.push_back(static_cast<uint8_t>(idx)); // single byte index
}
