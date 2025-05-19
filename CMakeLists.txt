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
add_executable(integrationTest
        tests/compilerIntegrationTest.cpp
        src/scanner.cpp
        src/byteCodeWriter.cpp
        src/compiler.cpp
)
target_include_directories(integrationTest PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${CMAKE_CURRENT_SOURCE_DIR}/src/model
)
target_link_libraries(integrationTest gtest_main)

add_test(NAME CompilerIntegrationTest COMMAND integrationTest)
