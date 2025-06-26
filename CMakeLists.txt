cmake_minimum_required(VERSION 3.16.3)
project(acorn)

# Fix for jni headers not being found by CLion IDE
unset(CMAKE_CXX_IMPLICIT_INCLUDE_DIRECTORIES)

set(CMAKE_CXX_STANDARD 17)

# Flag for available JNI support
option(USING_JNI "Enable JNI support" ON)

add_subdirectory(src)
add_subdirectory(tests)