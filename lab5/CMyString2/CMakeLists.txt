cmake_minimum_required(VERSION 3.21)
project(CMyString2)

set(CMAKE_CXX_STANDARD 20)

add_executable(CMyString2 main.cpp CMyString.h CMyString.cpp )

# Tests
add_subdirectory(tests tests.cpp)