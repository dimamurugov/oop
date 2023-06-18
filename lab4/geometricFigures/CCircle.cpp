#include "CCircle.h"

#define M_PI 3.14159265358979323846

CCircle::CCircle(CPoint point, double radius, std::vector<uint32_t> colors) :
    m_center(point),
    m_radius(radius),
    m_colors(std::move(colors)) {}

const std::optional<uint32_t> CCircle::GetFillColor() {
    if (m_colors.size() < 2) {
        return std::nullopt;
    }
    return m_colors[1];
}

const double CCircle::GetArea() {
    return M_PI*pow(m_radius,2);
}

const double CCircle::GetPerimeter() {
    return 2*M_PI*m_radius;
}

const std::string CCircle::GetStringColor(uint32_t color) {
    std::stringstream stream;
    stream << std::setfill('0')
           << std::setw(NUMBER_OF_DIGITS_IN_COLOR)
           << std::hex << color;
    return stream.str();
}

std::string CCircle::Format(double f) {
    std::ostringstream ss;
    ss.precision(4);
    ss << f;
    return ss.str();
}

const std::string CCircle::ToString() {
    std::string shape = "Shape: Circle\n";
    std::string perimeter = "Perimeter: " + Format(GetPerimeter()) + "\n";
    std::string area = "Area: "  + Format(GetArea()) + "\n";
    std::string radius = "Radius: " + Format(GetRadius()) + "\n";
    auto centerPoint = GetCenter().GetPoint();
    std::string center = "Center X:" + Format(centerPoint[0]) + " " + Format(centerPoint[1]) + "\n";
    std::string message = shape + perimeter + area + radius + center;
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

const std::optional<uint32_t> CCircle::GetOutlineColor() {
    if (m_colors.empty()) {
        return std::nullopt;
    }
    return m_colors[0];
}

const CPoint CCircle::GetCenter() {
    return m_center;
}

const double CCircle::GetRadius() const {
    return m_radius;
}
