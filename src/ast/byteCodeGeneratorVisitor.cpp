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
    auto className = std::make_shared<ConstantUtf8Info>("java/lang/System");
    // add the class name to the constant pool
    auto classNameIdx = this->constantPool.intern(className);
    // create a constant class info entry for the class
    auto classEntry = std::make_shared<ConstantClassInfo>(classNameIdx);
    // Add the class entry into the constant pool
    auto classEntryIdx = this->constantPool.intern(classEntry);

    // 2. The class of the field (java/io/PrintStream)
    auto fieldClassName = std::make_shared<ConstantUtf8Info>("java/io/PrintStream");
    auto fieldClassNameIdx = this->constantPool.intern(fieldClassName);

    // 3. The field name (out)
    auto fieldName = std::make_shared<ConstantUtf8Info>("out");
    auto fieldNameIdx = this->constantPool.intern(fieldName);
    // 4. The field descriptor (Ljava/io/PrintStream;)
    auto fieldDesc = std::make_shared<ConstantUtf8Info>("Ljava/io/PrintStream;");
    auto fieldDescIdx = this->constantPool.intern(fieldDesc);

    // 5. The name and type of the field (out:Ljava/io/PrintStream;) indexed by a name and type info entry
    auto nameAndType = std::make_shared<ConstantNameAndTypeInfo>(fieldNameIdx, fieldDescIdx);
    auto nameAndTypeIdx = this->constantPool.intern(nameAndType);

    // 6. The field reference - class: java/lang/System, name and type: out:Ljava/io/PrintStream;
    auto fieldRef = std::make_shared<ConstantFieldInfo>(classEntryIdx, nameAndTypeIdx);
    auto fieldRefIdx = this->constantPool.intern(fieldRef);

    // 7. The method name (println)
    auto methodName = std::make_shared<ConstantUtf8Info>("println");
    auto methodNameIdx = this->constantPool.intern(methodName);

    // 8. The method descriptor ((I)V)
    auto methodDesc = std::make_shared<ConstantUtf8Info>("(I)V");
    auto methodDescIdx = this->constantPool.intern(methodDesc);

    // 9. The name and type of the method (println:(I)V) indexed by a name and type info entry
    auto methodNameAndType = std::make_shared<ConstantNameAndTypeInfo>(methodNameIdx, methodDescIdx);
    auto methodNameAndTypeIdx = this->constantPool.intern(methodNameAndType);

    // 10. The class of the method (java/io/PrintStream)
    auto methodClassEntry = std::make_shared<ConstantClassInfo>(fieldClassNameIdx);
    auto methodClassEntryIdx = this->constantPool.intern(methodClassEntry);

    // 11. The method reference - class: java/io/PrintStream, name and type: println:(I)V
    auto methodRef = std::make_shared<ConstantMethodInfo>(methodClassEntryIdx, methodNameAndTypeIdx);
    auto methodRefIdx = this->constantPool.intern(methodRef);

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
    auto entry = std::make_shared<ConstantIntegerInfo>(node.getValue());
    // Add the entry into the constant pool
    auto idx = this->constantPool.intern(entry);
    // Add the ldc instruction to the code vector
    code.push_back(0x12); // ldc instruction opcode - 12
    // Add the index of the constant integer to the code vector
    code.push_back(static_cast<uint8_t>(idx)); // single byte index
}
