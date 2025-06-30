####################################
# Unit tests setup
####################################
enable_testing()

file(GLOB TEST_SOURCES *.cpp)

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
        .
)

target_link_libraries(GTest PRIVATE acornlib gtest gtest_main gmock gmock_main)

set(TEST_RESOURCES_DIR "${CMAKE_CURRENT_SOURCE_DIR}/resources")

#add_test(NAME AllTests COMMAND GTest ${TEST_RESOURCES_DIR})
include(GoogleTest)
gtest_discover_tests(GTest
        EXTRA_ARGS "${TEST_RESOURCES_DIR}"
)