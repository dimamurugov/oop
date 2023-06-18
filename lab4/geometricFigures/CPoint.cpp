#include <vector>
#include "CPoint.h"

CPoint::CPoint(double x, double y) : m_x(x), m_y(y) {}

std::vector<double> CPoint::GetPoint() const {
    std::vector<double> points = {m_x, m_y};
    return points;
}
