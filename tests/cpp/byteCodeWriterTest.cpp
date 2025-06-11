#include "ast/intLiteralNode.h"
#include "ast/printNode.h"
#include <gtest/gtest.h>
#include "byteCodeWriter.h"

#include "testHelper.h"

// Declare the global variable
extern std::vector<std::string> g_testArgs;

TEST(ByteCodeWriterTest, WriteGeneratesValidBytecode) {
    ByteCodeWriter writer("Acorn");
    std::vector<std::string> tokens = {"print", "10"};
    std::string outputFile = "Acorn.class";

    //create empty vector of ASTNode statements
    std::vector<std::unique_ptr<ASTNode>> statements;
    // Create a PrintNode with an IntLiteralNode
    auto intNode = std::make_unique<IntLiteralNode>(10);
    statements.push_back(std::make_unique<PrintNode>(std::move(intNode)));

    EXPECT_NO_THROW(writer.write(statements, outputFile));

    // Verify the generated class file
    std::ifstream classFile(outputFile, std::ios::binary);
    EXPECT_TRUE(classFile.is_open());

    // Check if the file is not empty
    classFile.seekg(0, std::ios::end);
    EXPECT_GT(classFile.tellg(), 0);

    // verify content of the class file
    auto filePath = g_testArgs[1] + "/Acorn.clazz"; // Path to the expected class file
    //read the expected bytes from the class file
    std::ifstream clazzFile(filePath, std::ios::binary);
    std::vector<uint8_t> expectedBytes((std::istreambuf_iterator<char>(clazzFile)),
                                     std::istreambuf_iterator<char>());

    //read the class file into a vector of bytes
    classFile.seekg(0, std::ios::beg);
    std::vector<uint8_t> actualBytes((std::istreambuf_iterator<char>(classFile)),
                                     std::istreambuf_iterator<char>());
    //print the actual bytes for debugging
    EXPECT_BYTES_EQ(actualBytes, expectedBytes);
}

