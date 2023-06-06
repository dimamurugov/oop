cmake_minimum_required(VERSION 3.21)
project(geometricFigures)

set(CMAKE_CXX_STANDARD 14)

add_executable(geometricFigures
        CPoint.cpp
        CPoint.h
        IShape.cpp
        IShape.h
        ISolidShape.cpp
        ISolidShape.h
        main.cpp)
