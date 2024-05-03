cmake_minimum_required(VERSION 3.21)
project(CMyList2)

set(CMAKE_CXX_STANDARD 20)

add_executable(CMyList2 main.cpp)

# Tests
add_subdirectory(tests)