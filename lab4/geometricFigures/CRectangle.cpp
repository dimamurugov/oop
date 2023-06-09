#include "CRectangle.h"


CRectangle::CRectangle(CPoint &point, std::vector<double> &sides, std::vector<std::string> &colors) :
    m_sides(sides),
    m_colors{colors},
    m_point(point)
{}

std::uint32_t CRectangle::GetFillColor() {
    return 0;
}

double CRectangle::GetArea() {
    return 0;
}

double CRectangle::GetPerimeter() {
    return 0;
}

std::string CRectangle::ToString() {
    return std::string();
}

uint32_t CRectangle::GetOutlineColor() {
    return 0;
}
