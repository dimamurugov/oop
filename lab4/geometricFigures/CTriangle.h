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
    explicit CTriangle(std::vector<CPoint> points, std::vector<uint32_t> colors);
    uint32_t GetFillColor() override;
    double GetArea() override;
    double GetPerimeter() override;
    std::string ToString() override;
    uint32_t GetOutlineColor() override;
    CPoint GetVertex1();
    CPoint GetVertex2();
    CPoint GetVertex3();
private:
    std::vector<CPoint> m_points;
    std::vector<uint32_t> m_colors;
    static std::string GetStringColor(uint32_t color);
};


#endif //GEOMETRICFIGURES_CTRIANGLE_H
