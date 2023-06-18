#include <iostream>
#include "CTriangle.h"

CTriangle::CTriangle(std::vector<CPoint> points, std::vector<uint32_t> colors) :
    m_points(std::move(points)),
    m_colors(std::move(colors)) {
}

const double CTriangle::GetArea() {
    auto vertex1 = GetVertex1().GetPoint();
    auto vertex2 = GetVertex2().GetPoint();
    auto vertex3 = GetVertex3().GetPoint();

    auto square = 0.5*fabs((vertex2[0]-vertex1[0])*(vertex3[1]-vertex1[1])-(vertex3[0]-vertex1[0])*(vertex2[1]-vertex1[1]));
    return square;
}

const double CTriangle::GetPerimeter() {
    auto vertex1 = GetVertex1().GetPoint();
    auto vertex2 = GetVertex2().GetPoint();
    auto vertex3 = GetVertex3().GetPoint();

    auto firstSide = sqrt(pow(vertex2[0]-vertex1[0], 2)+pow(vertex2[1]-vertex1[1], 2));
    auto secondSide = sqrt(pow(vertex3[0]-vertex1[0], 2)+pow(vertex3[1]-vertex1[1], 2));
    auto thirdSide = sqrt(pow(vertex3[0]-vertex2[0], 2)+pow(vertex3[1]-vertex2[1], 2));
    auto perimeter = firstSide + secondSide + thirdSide;
    return perimeter;
}

std::string CTriangle::GetStringColor(uint32_t color) {
    std::stringstream stream;
    stream << std::setfill('0')
           << std::setw(NUMBER_OF_DIGITS_IN_COLOR)
           << std::hex << color;
    return stream.str();
}

std::string CTriangle::Format(double f) {
    std::ostringstream ss;
    ss.precision(4);
    ss << f;
    return ss.str();
}

const std::string CTriangle::ToString() {
    std::string shape = "Shape: Triangle\n";
    std::string perimeter = "Perimeter: " + Format(GetPerimeter()) + "\n";
    std::string area = "Area: " + Format(GetArea()) + "\n";
    auto vertex1 = GetVertex1().GetPoint();
    auto vertex2 = GetVertex2().GetPoint();
    auto vertex3 = GetVertex3().GetPoint();
    std::string vertexA = "vertex A: " + Format(vertex1[0]) + DELIMITER + Format(vertex1[1]) + "\n";
    std::string vertexB = "vertex B: " + Format(vertex2[0]) + DELIMITER + Format(vertex2[1]) + "\n";
    std::string vertexC = "vertex C: " + Format(vertex3[0]) + DELIMITER + Format(vertex3[1]) + "\n";
    std::string message = shape + perimeter + area + vertexA + vertexB + vertexC;
    auto outLineColor = GetOutlineColor();
    auto fillColor = GetFillColor();
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

const std::optional<uint32_t> CTriangle::GetOutlineColor() {
    if (m_colors.empty()) {
        return std::nullopt;
    }
    return m_colors[0];
}

const std::optional<uint32_t> CTriangle::GetFillColor() {
    if (m_colors.size() < 2) {
        return std::nullopt;
    }
    return m_colors[1];
}

const CPoint CTriangle::GetVertex1() {
    return m_points[0];
}

const CPoint CTriangle::GetVertex2() {
    return m_points[1];
}

const CPoint CTriangle::GetVertex3() {
    return m_points[2];
}
