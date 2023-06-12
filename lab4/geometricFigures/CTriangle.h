#ifndef GEOMETRICFIGURES_CTRIANGLE_H
#define GEOMETRICFIGURES_CTRIANGLE_H

#include <vector>
#include <string>
#include "CPoint.h"
#include "ISolidShape.h"

class CTriangle : public ISolidShape  {
public:
    explicit CTriangle(std::vector<CPoint> points, std::vector<std::string> colors);
    std::string GetFillColor() override;
    double GetArea() override;
    double GetPerimeter() override;
    std::string ToString() override;
    std::string GetOutlineColor() override;
    CPoint GetVertex1();
    CPoint GetVertex2();
    CPoint GetVertex3();
private:
    std::vector<CPoint> m_points;
    std::vector<std::string> m_colors;
};


#endif //GEOMETRICFIGURES_CTRIANGLE_H
