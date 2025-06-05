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
        std::cout << "g_testArgs:";
        for (const auto& arg : g_testArgs) {
            std::cout << " [" << arg << "]";
        }
        std::cout << std::endl;

        ASSERT_GT(g_testArgs.size(), 1) << "Test data path argument missing!";
        auto filePath = g_testArgs[1] + "/valid.aco";
        std::cout << "filePath: " << filePath << std::endl;

        scanner = std::make_unique<Scanner>(filePath);
        std::cout << "Scanner created" << std::endl;

        writer = std::make_unique<ByteCodeWriter>("Acorn");
        std::cout << "ByteCodeWriter created" << std::endl;

        parser = std::make_unique<Parser>(scanner->tokenize());
        std::cout << "Parser created" << std::endl;
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
