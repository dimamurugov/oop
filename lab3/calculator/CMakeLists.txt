cmake_minimum_required(VERSION 3.21)
project(calculator)

set(CMAKE_CXX_STANDARD 17)

add_executable(Calculator main.cpp Calculator.cpp Calculator.h CalculatorController.cpp CalculatorController.h Function.cpp Function.h Storage.cpp Storage.h commonType.h)

# Tests
add_subdirectory(tests)