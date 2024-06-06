cmake_minimum_required(VERSION 3.23)
project(compare)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXE_LINKER_FLAGS ${CMAKE_EXE_LINKER_FLAGS} "-static")

add_executable(compare main.cpp)
