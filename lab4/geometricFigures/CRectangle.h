#ifndef GEOMETRICFIGURES_CRECTANGLE_H
#define GEOMETRICFIGURES_CRECTANGLE_H

#include <vector>
#include <iostream>
#include <iomanip>
#include "ISolidShape.h"
#include "CPoint.h"

class CRectangle : public ISolidShape {
public:
    explicit CRectangle(CPoint point, double width, double height, std::vector<uint32_t> colors);
    const std::optional<uint32_t> GetFillColor() override;
    const double GetArea() override;
    const double GetPerimeter() override;
    const std::string ToString() override;
    const double GetWidth() const;
    const double GetHeight() const;
    const CPoint GetLeftTop();
    const CPoint GetRightBottom();
    const std::optional<uint32_t> GetOutlineColor() override;
private:
    CPoint m_pointLeftTop;
    double m_width;
    double m_height;
    std::vector<uint32_t> m_colors;
    static std::string GetStringColor(uint32_t color);

    static std::string Format(double f);
};

#endif //GEOMETRICFIGURES_CRECTANGLE_H
