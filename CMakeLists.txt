cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(compiler VERSION 1.0)


add_executable(compiler main.cpp src/scanner.cpp src/parser.cpp)

target_include_directories(compiler PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)