#include "CCircle.h"
#include <cmath>

#define M_PI 3.14159265358979323846

CCircle::CCircle(CPoint point, double radius, std::vector<std::string> colors) :
    m_center(point),
    m_radius(radius),
    m_colors(colors) {}

std::string CCircle::GetFillColor() {
    return m_colors[1];
}

double CCircle::GetArea() {
    return M_PI*pow(m_radius,2);
}

double CCircle::GetPerimeter() {
    return 2*M_PI*m_radius;
}

std::string CCircle::ToString() {
    std::string shape = "Shape: Circle\n";
    std::string perimeter = "Perimeter: " + std::to_string(GetPerimeter()) + "\n";
    std::string area = "Area: "  + std::to_string(GetArea()) + "\n";
    std::string outlineColor = "Outline color: " + m_colors[0] + "\n";
    std::string fillColor = "Fill color: " + m_colors[1] + "\n";
    std::string radius = "Radius: " + std::to_string(GetRadius()) + "\n";
    auto centerPoint = GetCenter().GetPoints();
    std::string center = "Center X:" + std::to_string(centerPoint[0]) + " " + std::to_string(centerPoint[1]) + "\n";
    return shape + perimeter + area + outlineColor + fillColor + radius + center;
}

std::string CCircle::GetOutlineColor() {
    return m_colors[0];
}

CPoint CCircle::GetCenter() {
    return m_center;
}

double CCircle::GetRadius() const {
    return m_radius;
}
