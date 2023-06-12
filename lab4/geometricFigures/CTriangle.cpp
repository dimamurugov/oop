#include "CTriangle.h"
#include <utility>
#include <cmath>

CTriangle::CTriangle(std::vector<CPoint> points, std::vector<std::string> colors) :
    m_points(std::move(points)),
    m_colors(std::move(colors)) {
}

double CTriangle::GetArea() {
    auto vertex1 = GetVertex1().GetPoints();
    auto vertex2 = GetVertex2().GetPoints();
    auto vertex3 = GetVertex3().GetPoints();

    auto square = 0.5*fabs((vertex2[0]-vertex1[0])*(vertex3[1]-vertex1[1])-(vertex3[0]-vertex1[0])*(vertex2[1]-vertex1[1]));
    return square;
}

double CTriangle::GetPerimeter() {
    auto vertex1 = GetVertex1().GetPoints();
    auto vertex2 = GetVertex2().GetPoints();
    auto vertex3 = GetVertex3().GetPoints();

    auto firstSide = sqrt(pow(vertex2[0]-vertex1[0], 2)+pow(vertex2[1]-vertex1[1], 2));
    auto secondSide = sqrt(pow(vertex3[0]-vertex1[0], 2)+pow(vertex3[1]-vertex1[1], 2));
    auto thirdSide = sqrt(pow(vertex3[0]-vertex2[0], 2)+pow(vertex3[1]-vertex2[1], 2));
    auto perimeter = firstSide + secondSide + thirdSide;
    return perimeter;
}

std::string CTriangle::ToString() {
    std::string shape = "Shape: Triangle\n";
    std::string perimeter = "Perimeter: " + std::to_string(GetPerimeter()) + "\n";
    std::string area = "Area: "  + std::to_string(GetArea()) + "\n";
    std::string outlineColor = "Outline color: " + GetOutlineColor() + "\n";
    std::string fillColor = "Fill color: " + GetFillColor() + "\n";
    auto vertex1 = GetVertex1().GetPoints();
    auto vertex2 = GetVertex2().GetPoints();
    auto vertex3 = GetVertex3().GetPoints();
    std::string vertexA = "vertex A: " + std::to_string(vertex1[0]) + " " + std::to_string(vertex1[1]) + "\n";
    std::string vertexB = "vertex B: " + std::to_string(vertex2[0]) + " " + std::to_string(vertex2[1]) + "\n";
    std::string vertexC = "vertex C: " + std::to_string(vertex3[0]) + " " + std::to_string(vertex3[1]) + "\n";
    return shape + perimeter + area + outlineColor + fillColor + vertexA + vertexB + vertexC;
}

std::string CTriangle::GetOutlineColor() {
    return m_colors[0];
}

std::string CTriangle::GetFillColor() {
    return m_colors[1];
}

CPoint CTriangle::GetVertex1() {
    return m_points[0];
}

CPoint CTriangle::GetVertex2() {
    return m_points[1];
}

CPoint CTriangle::GetVertex3() {
    return m_points[2];
}
