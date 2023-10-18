#include <vector>
#include <valarray>
#include "CPoint.h"

CPoint::CPoint(double x, double y) : m_x(x), m_y(y) {}

std::vector<double> CPoint::GetPoint() const {
    std::vector<double> points = {m_x, m_y};
    return points;
}

double CPoint::GetLineLength(CPoint endPoint) const {
    auto startPoint = CPoint::GetPoint();
    auto endPointCoordinates = endPoint.GetPoint();
    double length = sqrt(pow(endPointCoordinates[0] - startPoint[0], 2)+pow(endPointCoordinates[1] - startPoint[1], 2));
    return length;
}
