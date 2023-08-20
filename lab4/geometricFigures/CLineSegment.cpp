#include "CLineSegment.h"

#include <valarray>

CLineSegment::CLineSegment(std::vector<CPoint> points, ColorTypes colors) :
    m_colors(colors),
    m_points(std::move(points)) {
}

const std::string CLineSegment::GetStringColor(uint32_t color) {
    std::stringstream stream;
    stream << std::setfill('0')
           << std::setw(NUMBER_OF_DIGITS_IN_COLOR)
           << std::hex << color;
    return stream.str();
}

std::string CLineSegment::Format(double f) {
    std::ostringstream ss;
    ss.precision(4);
    ss << f;
    return ss.str();
}

const std::string CLineSegment::ToString() {
    std::string shape = "Shape: LineSegment\n";
    std::string perimeter = "Perimeter: " + Format(GetPerimeter()) + "\n";
    std::vector<double> startPoint = GetStartPoint().GetPoint();
    std::vector<double> endPoint = GetEndPoint().GetPoint();
    std::string startPont = "Start point: " + Format(startPoint[0]) + DELIMITER + Format(startPoint[1]) + "\n";//endl
    std::string endPont = "Start point: " + Format(endPoint[0]) + DELIMITER + Format(endPoint[1]) + "\n";
    auto outLineColor = GetOutlineColor();
    std::string message = shape + perimeter + startPont + endPont;

    if (outLineColor.has_value()) {
        std::string outlineColorString = "Outline color: " + GetStringColor(outLineColor.value()) + "\n";
        message = message + outlineColorString;
    }
    return message;
}

const double CLineSegment::GetPerimeter() {
    auto startPoint = GetStartPoint().GetPoint();
    auto endPoint = GetEndPoint().GetPoint();
    // Вынести в функцию между двумя точками
     double length = sqrt(pow(endPoint[0] - startPoint[0], 2)+pow(endPoint[1] - startPoint[1], 2));
    return length;
}

const std::optional<uint32_t> CLineSegment::GetOutlineColor() {
    return m_colors.outlineColor;
}

const CPoint CLineSegment::GetStartPoint() {
    return m_points[0];
}

const CPoint CLineSegment::GetEndPoint() {
    return m_points[1];
}

const double CLineSegment::GetArea() {
    return 0;
}
