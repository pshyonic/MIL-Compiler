cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(compiler VERSION 1.0)

enable_language(ASM_NASM)

add_executable(compiler main.cpp src/scanner.cpp src/parser.cpp)

add_dependencies(compiler runtime)

target_include_directories(compiler PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)


if(WIN32)
    set(RUNTIME_ASM runtime/windows/print_int_windows.asm)
else()
    set(RUNTIME_ASM runtime/linux/print_int_linux.asm)
endif()

add_library(runtime OBJECT ${RUNTIME_ASM})