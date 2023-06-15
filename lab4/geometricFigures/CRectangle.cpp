#include <optional>
#include <limits>
#include "CRectangle.h"


CRectangle::CRectangle(CPoint pointLeftTop, double width, double height, std::vector<uint32_t> colors) :
    m_width(width),
    m_height(height),
    m_colors{colors},
    m_pointLeftTop(pointLeftTop)
{}

double CRectangle::GetArea() {
    return m_width * m_height;
}

double CRectangle::GetPerimeter() {
    return 2 * (m_width + m_height);
}

std::string CRectangle::GetStringColor(uint32_t color) {
    std::stringstream stream;
    stream << std::setfill('0') << std::setw(NUMBER_OF_DIGITS_IN_COLOR)
           << std::hex << color;

    return stream.str();
}

std::string CRectangle::ToString() {
    std::string shape = "Shape: Rectangle\n";
    std::string perimeter = "Perimeter: " + std::to_string(GetPerimeter()) + "\n";
    std::string area = "Area: "  + std::to_string(GetArea()) + "\n";
    std::vector points = m_pointLeftTop.GetPoints();
    std::string point = "Left Top: " + std::to_string(points[0]) + DELIMITER + std::to_string(points[1]) + "\n";
    auto outLineColor = GetOutlineColor();
    auto fillColor = GetFillColor();
    std::string message = shape + perimeter + area + point;

    if (outLineColor != UINT32_T_MAX) {
        std::string outlineColorString = "Outline color: " + GetStringColor(outLineColor) + "\n";
        message += outlineColorString;
    }
    if (fillColor != UINT32_T_MAX) {
        std::string fillColorString = "Fill color: " +  GetStringColor(fillColor) + "\n";
        message += fillColorString;
    }
    return message;
}

uint32_t CRectangle::GetOutlineColor() {
    if (m_colors.empty()) {
        return std::numeric_limits<uint32_t>::max();
    }
    return m_colors[0];
}

uint32_t CRectangle::GetFillColor() {
    if (m_colors.size() < 2) {
        return std::numeric_limits<uint32_t>::max();
    }
    return m_colors[1];
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
