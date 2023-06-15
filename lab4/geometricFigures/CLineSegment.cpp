#include "CLineSegment.h"

#include <valarray>

CLineSegment::CLineSegment(std::vector<CPoint> points, std::vector<uint32_t> colors) :
    m_colors(std::move(colors)),
    m_points(std::move(points)) {}

std::string CLineSegment::GetStringColor(uint32_t color) {
    std::stringstream stream;
    stream << std::setfill('0')
           << std::setw(NUMBER_OF_DIGITS_IN_COLOR)
           << std::hex << color;
    return stream.str();
}

std::string CLineSegment::ToString() {
    std::string shape = "Shape: LineSegment\n";
    std::string perimeter = "Perimeter: " + std::to_string(GetPerimeter()) + "\n";
    std::vector<double> startPoint = GetStartPoint().GetPoints();
    std::vector<double> endPoint = GetEndPoint().GetPoints();
    std::string startPont = "Start point: " + std::to_string(startPoint[0]) + DELIMITER + std::to_string(startPoint[1]) + "\n";
    std::string endPont = "Start point: " + std::to_string(endPoint[0]) + DELIMITER + std::to_string(endPoint[1]) + "\n";
    auto outLineColor = GetOutlineColor();
    std::string message = shape + perimeter + startPont + endPont;

    if (outLineColor != UINT32_T_MAX) {
        std::string outlineColorString = "Outline color: " + GetStringColor(outLineColor) + "\n";
        message = message + outlineColorString;
    }
    return message;
}

double CLineSegment::GetPerimeter() {
    auto startPoint = GetStartPoint().GetPoints();
    auto endPoint = GetEndPoint().GetPoints();
    double length = sqrt(pow(endPoint[0] - startPoint[0], 2)+pow(endPoint[1] - startPoint[1], 2));
    return length;
}

uint32_t CLineSegment::GetOutlineColor() {
    if (m_colors.empty()) {
        return std::numeric_limits<uint32_t>::max();
    }
    return m_colors[0];
}

CPoint CLineSegment::GetStartPoint() {
    return m_points[0];
}

CPoint CLineSegment::GetEndPoint() {
    return m_points[1];
}

double CLineSegment::GetArea() {
    return 0;
}
