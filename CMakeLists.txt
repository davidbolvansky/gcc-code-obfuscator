project(gcc-code-obfuscator)
cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_COMPILER g++)
set(CMAKE_CXX_STANDARD 14)

execute_process(
    COMMAND g++ -print-file-name=plugin
    OUTPUT_VARIABLE GCC_PLUGIN_DIR
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

if(NOT GCC_PLUGIN_DIR)
    message(FATAL_ERROR "Failed to determine GCC_PLUGIN_DIR")
endif()

file(GLOB_RECURSE SOURCES "src/*.cpp")

add_library(gcc-code-obfuscator SHARED ${SOURCES})
target_include_directories(gcc-code-obfuscator PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src ${GCC_PLUGIN_DIR}/include)
target_compile_options(gcc-code-obfuscator PRIVATE -fno-rtti)
set_target_properties(gcc-code-obfuscator PROPERTIES PREFIX "")
