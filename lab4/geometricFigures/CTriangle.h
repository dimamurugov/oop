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
    // избавить от векторов в инициализации
    explicit CTriangle(std::vector<CPoint> points, std::vector<uint32_t> colors);
    const std::optional<uint32_t> GetFillColor() override;
    const double GetArea() override;
    const double GetPerimeter() override;
    const std::string ToString() override;
    const std::optional<uint32_t> GetOutlineColor() override;
    const CPoint GetVertex1();
    const CPoint GetVertex2();
    const CPoint GetVertex3();
private:
    std::vector<CPoint> m_points;
    std::vector<uint32_t> m_colors;//не хранить в массиве
    static std::string GetStringColor(uint32_t color);
    static std::string Format(double f);
};


#endif //GEOMETRICFIGURES_CTRIANGLE_H
