#ifndef GEOMETRICFIGURES_CCIRCLE_H
#define GEOMETRICFIGURES_CCIRCLE_H


#include <string>
#include <vector>
#include <optional>
#include <iomanip>
#include <cmath>
#include <utility>
#include "CPoint.h"
#include "ISolidShape.h"

class CCircle : public ISolidShape {
public:
    explicit CCircle(CPoint point, double radius, std::vector<uint32_t> colors);
    uint32_t GetFillColor() override;
    double GetArea() override;
    double GetPerimeter() override;
    std::string ToString() override;
    uint32_t GetOutlineColor() override;
    CPoint GetCenter();
    double GetRadius() const;
private:
    CPoint m_center;
    double m_radius;
    std::vector<uint32_t> m_colors;
    static std::string GetStringColor(uint32_t color);
};


#endif //GEOMETRICFIGURES_CCIRCLE_H
