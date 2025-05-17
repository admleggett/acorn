#include <gtest/gtest.h>
#include <memory>
#include "scanner.h"
#include "byteCodeWriter.h"
#include "compiler.h"

class CompilerIntegrationTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Prepare a simple source string for testing
        source = "print 10";
        scanner = std::make_unique<Scanner>(source);
        writer = std::make_unique<ByteCodeWriter>("Acorn");
    }

    std::string source;
    std::unique_ptr<Scanner> scanner;
    std::unique_ptr<ByteCodeWriter> writer;
};

TEST_F(CompilerIntegrationTest, CompilesWithoutThrowing) {
    Compiler compiler(std::move(scanner), std::move(writer));
    EXPECT_NO_THROW(compiler.compile("Acorn.class"));
}
