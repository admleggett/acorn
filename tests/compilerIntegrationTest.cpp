#include <gtest/gtest.h>
#include <memory>
#include "scanner.h"
#include "parser.h"
#include "byteCodeWriter.h"
#include "compiler.h"

// Declare the global variable
extern std::vector<std::string> g_testArgs;

class CompilerIntegrationTest : public ::testing::Test {

protected:
    void SetUp() override {
        // Prepare a simple source string for testing
        auto filePath = g_testArgs[1] + "/valid.aco";
        scanner = std::make_unique<Scanner>(filePath);
        writer = std::make_unique<ByteCodeWriter>("Acorn");
        parser = std::make_unique<Parser>(scanner->tokenize());
    }

    std::string source;
    std::unique_ptr<Scanner> scanner;
    std::unique_ptr<ByteCodeWriter> writer;
    std::unique_ptr<Parser> parser;
};

TEST_F(CompilerIntegrationTest, CompilesWithoutThrowing) {
    Compiler compiler(std::move(scanner), std::move(writer), std::move(parser));
    EXPECT_NO_THROW(compiler.compile("Acorn.class"));
    //assert that the Acorn.class file exists
    std::ifstream classFile("Acorn.class");
    EXPECT_TRUE(classFile.good());
}
