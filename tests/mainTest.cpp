#include <gtest/gtest.h>

// Global variable to store command-line arguments
std::vector<std::string> g_testArgs;

// Function to initialize the global variable
void InitTestArgs(int argc, char** argv) {
    g_testArgs.assign(argv, argv + argc);
}

// Custom main function to initialize Google Test and the global variable
int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    InitTestArgs(argc, argv);
    return RUN_ALL_TESTS();
}
