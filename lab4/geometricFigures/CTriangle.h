#ifndef GEOMETRICFIGURES_CTRIANGLE_H
#define GEOMETRICFIGURES_CTRIANGLE_H

#include <vector>
#include <string>
#include <iomanip>
#include <utility>
#include <cmath>
#include "CPoint.h"
#include "ISolidShape.h"

class CTriangle : public ISolidShape  {
public:
    explicit CTriangle(std::vector<CPoint> points, ColorTypes colors);
    // написать const методы правильно (они пишутся справо)
    const std::optional<uint32_t> GetFillColor() override;
    const double GetArea() override;
    const double GetPerimeter() override;
    const std::string ToString() override;
    const std::optional<uint32_t> GetOutlineColor() override;
    const CPoint GetVertex1();
    const CPoint GetVertex2();
    const CPoint GetVertex3();
private:
    const double CalculateArea();
    std::vector<CPoint> m_points;
    ColorTypes m_colors;
    // устронить дублирование кода
    static std::string GetStringColor(uint32_t color);
    static std::string Format(double f);
};


#endif //GEOMETRICFIGURES_CTRIANGLE_H
