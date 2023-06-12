#ifndef GEOMETRICFIGURES_CCIRCLE_H
#define GEOMETRICFIGURES_CCIRCLE_H


#include <string>
#include <vector>
#include <optional>
#include "CPoint.h"
#include "ISolidShape.h"

class CCircle : public ISolidShape {
public:
    explicit CCircle(CPoint point, double radius, std::vector<std::string> colors);
    std::string GetFillColor() override;
    double GetArea() override;
    double GetPerimeter() override;
    std::string ToString() override;
    std::string GetOutlineColor() override;
    CPoint GetCenter();
    double GetRadius() const;
private:
    CPoint m_center;
    double m_radius;
    std::vector<std::string> m_colors;
};


#endif //GEOMETRICFIGURES_CCIRCLE_H
