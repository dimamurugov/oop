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
    const std::optional<uint32_t> GetFillColor() override;
    const double GetArea() override;
    const double GetPerimeter() override;
    const std::string ToString() override;
    const std::optional<uint32_t> GetOutlineColor() override;
    const CPoint GetCenter();
    const double GetRadius() const;
private:
    CPoint m_center;
    double m_radius;
    std::vector<uint32_t> m_colors;
    static const std::string GetStringColor(uint32_t color);
    static std::string Format(double f);
};


#endif //GEOMETRICFIGURES_CCIRCLE_H
