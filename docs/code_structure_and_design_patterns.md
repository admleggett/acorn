# Code Structure and Design Patterns

## Code Structure

The codebase is organized into several directories, each serving a specific purpose:

- `src`: Contains the source code for the Acorn programming language.
  - `ast`: Contains the abstract syntax tree (AST) related classes.
    - `astNode.h`: Declaration of the ASTNode class, the base class for all AST nodes.
    - `astVisitor.h`: Declaration of the ASTVisitor class, an abstract base class for visiting AST nodes.
    - `byteCodeGeneratorVisitor.h` and `byteCodeGeneratorVisitor.cpp`: Implementation of the ByteCodeGeneratorVisitor class, responsible for generating bytecode from AST nodes.
    - `intLiteralNode.h`: Declaration of the IntLiteralNode class, representing integer literals in the AST.
    - `printNode.h`: Declaration of the PrintNode class, representing print statements in the AST.
  - `model`: Contains classes related to the Java class file format.
    - `classByteCode.h`: Definition of the ClassByteCode class, representing a Java class file's bytecode.
    - `classFileHeader.h`: Definition of the ClassFileHeader class, representing the header of a Java class file.
    - `constantClassInfo.h`, `constantFieldInfo.h`, `constantIntegerInfo.h`, `constantMethodInfo.h`, `constantNameAndTypeInfo.h`, `constantPool.h`, `constantPoolEntry.h`, `constantUtf8Info.h`: Definitions of various constant pool entries used in Java class files.
    - `codeAttribute.h`: Definition of the CodeAttribute class, representing the "Code" attribute in a Java class file.
    - `methodInfo.h`: Definition of the MethodInfo class, representing a method in a Java class file.
  - `interpreter`: Contains the main entry point for the Acorn interpreter.
    - `main.cpp`: Main entry point for the Acorn interpreter.
  - `compiler.cpp` and `compiler.h`: Implementation of the Compiler class, responsible for compiling source code into bytecode.
  - `byteCodeWriter.cpp` and `byteCodeWriter.h`: Implementation of the ByteCodeWriter class, responsible for writing bytecode to a file.
  - `parser.cpp` and `parser.h`: Implementation of the Parser class, responsible for parsing a sequence of tokens into an AST.
  - `scanner.cpp` and `scanner.h`: Implementation of the Scanner class, responsible for tokenizing source code.

- `tests`: Contains unit tests for the various components of the Acorn programming language.
  - `byteCodeGeneratorVisitorTest.cpp`: Unit tests for the ByteCodeGeneratorVisitor class.
  - `byteCodeWriterTest.cpp`: Unit tests for the ByteCodeWriter class.
  - `classByteCodeTest.cpp`: Unit tests for the ClassByteCode class.
  - `compilerIntegrationTest.cpp`: Integration tests for the Compiler class.
  - `constantPoolTest.cpp`: Unit tests for the ConstantPool class.
  - `scannerTest.cpp`: Unit tests for the Scanner class.

- `scripts`: Contains utility scripts.
  - `generate_bytecode.py`: Script for generating bytecode.
  - `hex2class.sh`: Script for converting hexadecimal to class files.
  - `hex2txt.sh`: Script for converting hexadecimal to text files.

## Design Patterns

The codebase employs several design patterns to achieve modularity and maintainability:

### Visitor Pattern

The Visitor pattern is used to separate algorithms from the objects on which they operate. In the Acorn codebase, the Visitor pattern is used to traverse the abstract syntax tree (AST) and perform operations on its nodes.

- `ASTNode` class: The base class for all AST nodes. It declares the `accept` method, which accepts a visitor.
- `ASTVisitor` class: An abstract base class that defines the interface for visiting AST nodes. It declares visit methods for different types of AST nodes.
- `ByteCodeGeneratorVisitor` class: A concrete implementation of the `ASTVisitor` class. It generates bytecode from the AST nodes by implementing the visit methods.

Example:
```cpp
// ASTNode.h
class ASTNode {
public:
    virtual ~ASTNode() = default;
    virtual void accept(ASTVisitor& visitor) = 0;
};

// ASTVisitor.h
class ASTVisitor {
public:
    virtual void visit(PrintNode& node) = 0;
    virtual void visit(IntLiteralNode& node) = 0;
    virtual ~ASTVisitor() = default;
};

// ByteCodeGeneratorVisitor.h
class ByteCodeGeneratorVisitor : public ASTVisitor {
public:
    void visit(PrintNode& node) override;
    void visit(IntLiteralNode& node) override;
};

// ByteCodeGeneratorVisitor.cpp
void ByteCodeGeneratorVisitor::visit(PrintNode& node) {
    // Generate bytecode for PrintNode
}

void ByteCodeGeneratorVisitor::visit(IntLiteralNode& node) {
    // Generate bytecode for IntLiteralNode
}
```

### Factory Pattern

The Factory pattern is used to create objects without specifying the exact class of the object that will be created. In the Acorn codebase, the Factory pattern is used to create instances of AST nodes.

Example:
```cpp
// Parser.cpp
std::vector<std::unique_ptr<ASTNode>> Parser::parse() {
    std::vector<std::unique_ptr<ASTNode>> statements;
    while (pos_ + 1 < tokens_.size()) {
        if (tokens_[pos_] != "print")
            throw std::runtime_error("Syntax error: expected 'print <int>'");
        int value = std::stoi(tokens_[pos_ + 1]);
        auto intNode = std::make_unique<IntLiteralNode>(value);
        statements.push_back(std::make_unique<PrintNode>(std::move(intNode)));
        pos_ += 2;
    }
    if (pos_ != tokens_.size())
        throw std::runtime_error("Syntax error: incomplete statement at end");
    return statements;
}
```

In this example, the `Parser` class uses the `std::make_unique` function to create instances of `IntLiteralNode` and `PrintNode` without specifying their exact classes.
