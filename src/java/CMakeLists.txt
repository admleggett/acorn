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