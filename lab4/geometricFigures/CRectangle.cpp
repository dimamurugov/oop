#include "CRectangle.h"


CRectangle::CRectangle(CPoint point, double width, double height, std::vector<std::string> colors) :
    m_width(width),
    m_height(height),
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
