cmake_minimum_required(VERSION 3.23)
project(calculator)

set(CMAKE_CXX_STANDARD 17)

add_executable(calculator main.cpp calculator.cpp calculator.h CalculatorController.cpp CalculatorController.h)
