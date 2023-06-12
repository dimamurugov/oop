#include <iostream>
#include "CRectangle.h"


CRectangle::CRectangle(CPoint pointLeftTop, double width, double height, std::vector<std::string> colors) :
    m_width(width),
    m_height(height),
    m_colors{colors},
    m_pointLeftTop(pointLeftTop)
{}

std::string CRectangle::GetFillColor() {
    return m_colors[1];
}

double CRectangle::GetArea() {
    return m_width * m_height;
}

double CRectangle::GetPerimeter() {
    return 2 * (m_width + m_height);
}

std::string CRectangle::ToString() {
    std::string shape = "Shape: Rectangle\n";
    std::string perimeter = "Perimeter: " + std::to_string(GetPerimeter()) + "\n";
    std::string area = "Area: "  + std::to_string(GetArea()) + "\n";
    std::string outlineColor = "Outline color: " + m_colors[0] + "\n";
    std::string fillColor = "Fill color: " + m_colors[1] + "\n";
    std::vector points = m_pointLeftTop.GetPoints();
    std::string point = "Left Top: " + std::to_string(points[0]) + " " + std::to_string(points[1]) + "\n";
    return shape + perimeter + area + outlineColor + fillColor + point;
}
// должен быть uint32_t
std::string CRectangle::GetOutlineColor() {
    return m_colors[0];
}

CPoint CRectangle::GetRightBottom() {
    auto leftTop = m_pointLeftTop.GetPoints();
    double x = leftTop[0] + m_width;
    double y = leftTop[1] - m_height;
    CPoint rightBottom(x, y);
    return rightBottom;
}

CPoint CRectangle::GetLeftTop() {
    return m_pointLeftTop;
}

double CRectangle::GetWidth() const {
    return m_width;
}

double CRectangle::GetHeight() const {
    return m_height;
}
