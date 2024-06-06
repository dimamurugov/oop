cmake_minimum_required(VERSION 3.21)
project(task_1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXE_LINKER_FLAGS ${CMAKE_EXE_LINKER_FLAGS} "-static")

add_executable(task_1 main.cpp Functions.cpp Functions.h)

# Tests
add_subdirectory(tests)