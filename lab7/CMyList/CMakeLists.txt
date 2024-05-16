cmake_minimum_required(VERSION 3.23)
project(CMyList)

set(CMAKE_CXX_STANDARD 20)

add_executable(CMyList main.cpp CMyList.cpp CMyList.h)

# Tests
add_subdirectory(tests)