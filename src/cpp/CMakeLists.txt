option(USING_JNI "Enable JNI support" ON)

add_library(acornlib
        compiler/scanner.cpp
        compiler/parser.cpp
        compiler/byteCodeWriter.cpp
        compiler/compiler.cpp
        ast/byteCodeGeneratorVisitor.cpp
        interpreter/interpreter.cpp
        interpreter/jniJvmLauncher.cpp
)

if(USING_JNI)
    find_package(Java REQUIRED)
    find_package(JNI REQUIRED)
    target_compile_definitions(acornlib PRIVATE HAVE_JNI_H)
    target_include_directories(acornlib PRIVATE ${JNI_INCLUDE_DIRS})
    target_link_libraries(acornlib PRIVATE ${JNI_LIBRARIES})
endif()

target_include_directories(acornlib PRIVATE
        .
        compiler
        model
        ast
        interpreter
)

add_executable(acornc main.cpp)
add_executable(acorn interpreter/main.cpp)

# Link the acornc executable with the acornlib library
target_link_libraries(acornc PRIVATE acornlib)
# Link the acorn executable with the acornlib library
target_link_libraries(acorn PRIVATE acornlib)
