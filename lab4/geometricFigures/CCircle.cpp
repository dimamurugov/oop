#include "CCircle.h"

#define M_PI 3.14159265358979323846

CCircle::CCircle(CPoint point, double radius, std::vector<uint32_t> colors) :
    m_center(point),
    m_radius(radius),
    m_colors(std::move(colors)) {}

uint32_t CCircle::GetFillColor() {
    return m_colors[1];
}

double CCircle::GetArea() {
    return M_PI*pow(m_radius,2);
}

double CCircle::GetPerimeter() {
    return 2*M_PI*m_radius;
}

std::string CCircle::GetStringColor(uint32_t color) {
    std::stringstream stream;
    stream << std::setfill('0')
           << std::setw(NUMBER_OF_DIGITS_IN_COLOR)
           << std::hex << color;
    return stream.str();
}

std::string CCircle::ToString() {
    std::string shape = "Shape: Circle\n";
    std::string perimeter = "Perimeter: " + std::to_string(GetPerimeter()) + "\n";
    std::string area = "Area: "  + std::to_string(GetArea()) + "\n";
    std::string outlineColor = "Outline color: " + GetStringColor(m_colors[0]) + "\n";
    std::string fillColor = "Fill color: " + GetStringColor(m_colors[1]) + "\n";
    std::string radius = "Radius: " + std::to_string(GetRadius()) + "\n";
    auto centerPoint = GetCenter().GetPoints();
    std::string center = "Center X:" + std::to_string(centerPoint[0]) + " " + std::to_string(centerPoint[1]) + "\n";
    return shape + perimeter + area + outlineColor + fillColor + radius + center;
}

uint32_t CCircle::GetOutlineColor() {
    return m_colors[0];
}

CPoint CCircle::GetCenter() {
    return m_center;
}

double CCircle::GetRadius() const {
    return m_radius;
}
