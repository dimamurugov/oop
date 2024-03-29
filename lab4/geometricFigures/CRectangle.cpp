#include <optional>
#include "CRectangle.h"


CRectangle::CRectangle(CPoint pointLeftTop, double width, double height, ColorTypes colors) :
    m_width(width),
    m_height(height),
    m_colors(colors),
    m_pointLeftTop(pointLeftTop)
{
    if (width <= 0 || height <= 0) {
        throw "Length and height cannot be less than or equal to zero!\n";
    }
}

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
    std::vector leftPoints = m_pointLeftTop.GetPoint();
    std::vector rightPoints = GetRightBottom().GetPoint();
    std::string leftPoint = "Left Top: " + Format(leftPoints[0]) + DELIMITER + Format(leftPoints[1]) + "\n";
    std::string rightPoint = "Right Top: " + Format(rightPoints[0]) + DELIMITER + Format(rightPoints[1]) + "\n";
    auto outLineColor = GetOutlineColor();
    auto fillColor = GetFillColor();
    std::string message = shape + perimeter + area + leftPoint + rightPoint;

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
    return m_colors.outlineColor;
}

const std::optional<uint32_t> CRectangle::GetFillColor() {
    return m_colors.outlineColor;
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
