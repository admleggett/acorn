cmake_minimum_required(VERSION 3.16.3)
project(acorn)

set(CMAKE_CXX_STANDARD 17)

add_executable(acornc
        src/main.cpp
        src/scanner.cpp
        src/byteCodeWriter.cpp
        src/compiler.cpp
)

target_include_directories(acornc PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${CMAKE_CURRENT_SOURCE_DIR}/src/model
)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

# Test sources
add_executable(GTest
        tests/compilerIntegrationTest.cpp
        tests/constantPoolTest.cpp
        tests/classHeaderInfoTest.cpp
        src/scanner.cpp
        src/byteCodeWriter.cpp
        src/compiler.cpp
)
target_include_directories(GTest PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${CMAKE_CURRENT_SOURCE_DIR}/src/model
        ${CMAKE_CURRENT_SOURCE_DIR}/tests
)
target_link_libraries(GTest gtest_main)

# add all tests to the test suite
add_test(NAME CompilerIntegrationTest COMMAND GTest)
add_test(NAME ConstantPoolTest COMMAND GTest)
add_test(NAME ClassHeaderInfoTest COMMAND GTest)
