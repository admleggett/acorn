cmake_minimum_required(VERSION 3.16.3)
project(acorn)

# Fix for jni headers not being found by CLion IDE
unset(CMAKE_CXX_IMPLICIT_INCLUDE_DIRECTORIES)

set(CMAKE_CXX_STANDARD 17)

option(USING_JNI "Enable JNI support" ON)

add_library(acornlib
        src/cpp/scanner.cpp
        src/cpp/parser.cpp
        src/cpp/byteCodeWriter.cpp
        src/cpp/compiler.cpp
        src/cpp/ast/byteCodeGeneratorVisitor.cpp
        src/cpp/interpreter/interpreter.cpp
        src/cpp/interpreter/jniJvmLauncher.cpp
)

if(USING_JNI)
    find_package(Java REQUIRED)
    find_package(JNI REQUIRED)
    target_compile_definitions(acornlib PRIVATE HAVE_JNI_H)
    target_include_directories(acornlib PRIVATE ${JNI_INCLUDE_DIRS})
    target_link_libraries(acornlib PRIVATE ${JNI_LIBRARIES})
endif()

target_include_directories(acornlib PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src/cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/cpp/model
        ${CMAKE_CURRENT_SOURCE_DIR}/src/cpp/ast
        ${CMAKE_CURRENT_SOURCE_DIR}/src/cpp/interpreter
)

add_executable(acornc src/cpp/main.cpp)
add_executable(acorn src/cpp/interpreter/main.cpp)

# Link the acornc executable with the acornlib library
target_link_libraries(acornc PRIVATE acornlib)
# Link the acorn executable with the acornlib library
target_link_libraries(acorn PRIVATE acornlib)

####################################
# Java compilation setup
####################################
if(USING_JNI)
    include(UseJava)

    find_package(Java REQUIRED COMPONENTS Development)
    set(CMAKE_JAVA_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

    #compile the Java files in the src/java directory
    file(GLOB JAVA_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/java/acorn/loader/*.java)
    message(STATUS "Java sources: ${JAVA_SOURCES}")
    add_jar(acornlib_java
        SOURCES ${JAVA_SOURCES}
        OUTPUT_NAME acornlib
    )
endif ()


####################################
# Unit tests setup
####################################

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

file(GLOB TEST_SOURCES tests/cpp/*.cpp)

add_executable(GTest ${TEST_SOURCES})

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
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/cpp
)

target_link_libraries(GTest PRIVATE acornlib gtest gtest_main gmock gmock_main)

set(TEST_RESOURCES_DIR "${CMAKE_CURRENT_SOURCE_DIR}/tests/cpp/resources")

#add_test(NAME AllTests COMMAND GTest ${TEST_RESOURCES_DIR})
include(GoogleTest)
gtest_discover_tests(GTest
    EXTRA_ARGS "${TEST_RESOURCES_DIR}"
)