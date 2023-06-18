#include <optional>
#include "CRectangle.h"


CRectangle::CRectangle(CPoint pointLeftTop, double width, double height, std::vector<uint32_t> colors) :
    m_width(width),
    m_height(height),
    m_colors{colors},
    m_pointLeftTop(pointLeftTop)
{}

const double CRectangle::GetArea() {
    return m_width * m_height;
}

const double CRectangle::GetPerimeter() {
    return 2 * (m_width + m_height);
}

std::string CRectangle::GetStringColor(uint32_t color) {
    std::stringstream stream;
    stream << std::setfill('0') << std::setw(NUMBER_OF_DIGITS_IN_COLOR)
           << std::hex << color;

    return stream.str();
}

std::string CRectangle::Format(double f) {
    std::ostringstream ss;
    ss.precision(4);
    ss << f;
    return ss.str();
}

const std::string CRectangle::ToString() {
    std::string shape = "Shape: Rectangle\n";
    std::string perimeter = "Perimeter: " + Format(GetPerimeter()) + "\n";
    std::string area = "Area: "  + Format(GetArea()) + "\n";
    std::vector points = m_pointLeftTop.GetPoint();
    std::string point = "Left Top: " + Format(points[0]) + DELIMITER + Format(points[1]) + "\n";
    auto outLineColor = GetOutlineColor();
    auto fillColor = GetFillColor();
    std::string message = shape + perimeter + area + point;

    if (outLineColor.has_value()) {
        std::string outlineColorString = "Outline color: " + GetStringColor(outLineColor.value()) + "\n";
        message += outlineColorString;
    }
    if (fillColor.has_value()) {
        std::string fillColorString = "Fill color: " +  GetStringColor(fillColor.value()) + "\n";
        message += fillColorString;
    }
    return message;
}

const std::optional<uint32_t> CRectangle::GetOutlineColor() {
    if (m_colors.empty()) {
        return std::nullopt;
    }
    return m_colors[0];
}

const std::optional<uint32_t> CRectangle::GetFillColor() {
    if (m_colors.size() < 2) {
        return std::nullopt;
    }
    return m_colors[1];
}

const CPoint CRectangle::GetRightBottom() {
    auto leftTop = m_pointLeftTop.GetPoint();
    double x = leftTop[0] + m_width;
    double y = leftTop[1] - m_height;
    CPoint rightBottom(x, y);
    return rightBottom;
}

const CPoint CRectangle::GetLeftTop() {
    return m_pointLeftTop;
}

const double CRectangle::GetWidth() const {
    return m_width;
}

const double CRectangle::GetHeight() const {
    return m_height;
}
