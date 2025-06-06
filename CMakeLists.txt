cmake_minimum_required(VERSION 3.16.3)
project(acorn)

# Fix for jni headers not being found by CLion IDE
unset(CMAKE_CXX_IMPLICIT_INCLUDE_DIRECTORIES)

set(CMAKE_CXX_STANDARD 17)

add_library(acornlib
        src/scanner.cpp
        src/parser.cpp
        src/byteCodeWriter.cpp
        src/compiler.cpp
        src/ast/byteCodeGeneratorVisitor.cpp
        src/interpreter/interpreter.cpp
        src/interpreter/jniJvmLauncher.cpp
)
find_package(Java REQUIRED)
find_package(JNI REQUIRED)

target_include_directories(acornlib PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${CMAKE_CURRENT_SOURCE_DIR}/src/model
        ${CMAKE_CURRENT_SOURCE_DIR}/src/ast
        ${CMAKE_CURRENT_SOURCE_DIR}/src/interpreter
        ${JNI_INCLUDE_DIRS}
)

target_link_libraries(acornlib PRIVATE ${JNI_LIBRARIES})

add_executable(acornc src/main.cpp)
add_executable(acorn src/interpreter/main.cpp)

# Link the acornc executable with the acornlib library
target_link_libraries(acornc PRIVATE acornlib)
# Link the acorn executable with the acornlib library
target_link_libraries(acorn PRIVATE acornlib)


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
        tests/classByteCodeTest.cpp
        tests/mainTest.cpp
        tests/scannerTest.cpp
        tests/byteCodeGeneratorVisitorTest.cpp
        tests/byteCodeWriterTest.cpp
)

option(ENABLE_ASAN "Enable Address Sanitizer" OFF)

if(ENABLE_ASAN)
    message(STATUS "Building with AddressSanitizer enabled")
    if(MSVC)
        target_compile_options(GTest PRIVATE /fsanitize=address)
        message(STATUS "Note: For MSVC, you may need to set _NO_DEBUG_HEAP=1 environment variable")
    else()
        target_compile_options(GTest PRIVATE -fsanitize=address -fno-omit-frame-pointer)
        target_link_options(GTest PRIVATE -fsanitize=address)
    endif()
endif()

target_include_directories(GTest PRIVATE
        $<TARGET_PROPERTY:acornlib,INCLUDE_DIRECTORIES>
        ${CMAKE_CURRENT_SOURCE_DIR}/tests
)

target_link_libraries(GTest PRIVATE acornlib gtest gtest_main)

add_test(NAME AllTests COMMAND GTest)