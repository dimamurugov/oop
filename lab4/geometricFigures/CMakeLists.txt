cmake_minimum_required(VERSION 3.21)
project(geometricFigures)

set(CMAKE_CXX_STANDARD 17)

add_executable(geometricFigures
        CPoint.cpp
        CPoint.h
        IShape.h
        ISolidShape.h
        main.cpp CShapeController.cpp CShapeController.h CRectangle.cpp CRectangle.h CTriangle.cpp CTriangle.h CCircle.cpp CCircle.h CLineSegment.cpp CLineSegment.h)

# Tests
add_subdirectory(tests)