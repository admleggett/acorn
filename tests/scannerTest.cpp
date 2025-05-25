#include <gtest/gtest.h>
#include "scanner.h"
#include "testHelper.h"

// Declare the global variable
extern std::vector<std::string> g_testArgs;

TEST(ScannerTest, TokenizeValidInput) {
    auto filePath = g_testArgs[1] + "/valid.aco";
    Scanner scanner(filePath);
    auto tokens = scanner.tokenize();
    std::vector<std::string> expectedTokens = {
        "print", "42",
        "print", "100",
            "print", "200"};
    EXPECT_EQ(tokens, expectedTokens);
}

TEST(ScannerTest, TokenizeInvalidInput) {
    auto filePath = g_testArgs[1] + "/invalid.aco";
    Scanner scanner(filePath);
    EXPECT_THROW(scanner.tokenize(), std::runtime_error);
}