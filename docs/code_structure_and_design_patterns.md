# Code Structure and Design Patterns

## Code Structure

The codebase is organised as follows

- `ast`: Folder that contains the abstract syntax tree (AST) related classes. Uses the Visitor pattern to traverse and manipulate the AST.
- `model`: Folder that contains classes related to the Java class file format.
- `interpreter`: Folder that contains the main entry point for the Acorn interpreter which compiles and runs Acorn source code (by invoking the JVM).
- `compiler.cpp` and `compiler.h`: Implementation of the Compiler class, responsible for compiling source code into bytecode.
- `byteCodeWriter.cpp` and `byteCodeWriter.h`: Implementation of the ByteCodeWriter class, responsible for writing bytecode to a file.
- `parser.cpp` and `parser.h`: Implementation of the Parser class, responsible for parsing a sequence of tokens into an AST.
- `scanner.cpp` and `scanner.h`: Implementation of the Scanner class, responsible for tokenizing Acorn source code.
- `main.cpp`: The main entry point for the Acorn compiler

### C++ Style Guide

The codebase uses modern C++ (C++17, as specified in the `CMakeLists.txt`) and follows idiomatic memory management practices:

- **Smart Pointers:** Ownership and lifetime of dynamically allocated objects are managed using smart pointers such as `std::shared_ptr` and `std::unique_ptr`. This eliminates manual memory management and helps prevent memory leaks and dangling pointers.
- **RAII Principle:** Resource Acquisition Is Initialization (RAII) is followed, ensuring resources are released automatically when objects go out of scope.
- **No Raw `new`/`delete`:** Direct use of `new` and `delete` is avoided in favor of smart pointers and standard containers.

Example:
```cpp
// Using std::shared_ptr for shared ownership
std::shared_ptr<ClassFileHeader> fileHeader = std::make_shared<ClassFileHeader>(...);
std::shared_ptr<ConstantPool> constantPool = std::make_shared<ConstantPool>(...);
auto classByteCode = std::make_shared<ClassByteCode>(fileHeader, constantPool, ...);
```


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

### Composite Pattern

The model classes in the `model` folder use the Composite pattern to represent and serialize
the hierarchical structure of a Java class file in byte code form. 

Each model class implements a common interface (`ByteCodeSerializable`), which defines a `serialize()` method. 
The top-level class (`ClassByteCode`) delegates serialization to its child components (such as `ClassFileHeader`, `ConstantPool`, etc.),
each of which also implements `ByteCodeSerializable`. 
This delegation continues recursively, allowing the entire byte structure to be built from its parts.





