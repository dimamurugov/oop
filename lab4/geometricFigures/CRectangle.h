#ifndef GEOMETRICFIGURES_CRECTANGLE_H
#define GEOMETRICFIGURES_CRECTANGLE_H

#include <vector>
#include "ISolidShape.h"
#include "CPoint.h"

class CRectangle : public ISolidShape {
public:
    explicit CRectangle(CPoint &point, std::vector<double>& sides, std::vector<std::string>& colors);
    std::uint32_t GetFillColor() override;
    double GetArea() override;
    double GetPerimeter() override;
    std::string ToString() override;
    uint32_t GetOutlineColor() override;
private:
    CPoint m_point;
    std::vector<double> m_sides;
    std::vector<std::string> m_colors;
};

#endif //GEOMETRICFIGURES_CRECTANGLE_H
