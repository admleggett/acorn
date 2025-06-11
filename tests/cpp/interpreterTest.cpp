#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "interpreter/interpreter.h"
#include "interpreter/jvmLauncher.h"

class MockJvmLauncher : public IJvmLauncher
{
public:
    MOCK_METHOD(int, launch, (const std::string& clazz), (override));
};

class MockCompilerApplication : public ICompilerApplication
{
public:
   MOCK_METHOD(std::string, compile, (std::string sourceFile), (override));

};

TEST(interpreterTest, InterpreterHandlesErrorTest)
{
    std::string sourceFile = "non_existent_file.aco";
    //Create mock objects for the compiler application and JVM launcher
    auto mockJvmLauncher = std::make_unique<MockJvmLauncher>();
    auto mockCompilerApplication = std::make_unique<MockCompilerApplication>();
    //Expect calls (before moving)
    EXPECT_CALL(*mockCompilerApplication, compile(sourceFile));
    EXPECT_CALL(*mockJvmLauncher, launch(testing::_)).WillOnce(testing::Return(1));
    //invoke class under test
    Interpreter interpreter(std::move(mockCompilerApplication), std::move(mockJvmLauncher));
    int result = interpreter.run(sourceFile);
    EXPECT_EQ(result, 1); // Expect the interpreter to return an error code
}


