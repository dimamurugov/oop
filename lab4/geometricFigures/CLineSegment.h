#ifndef GEOMETRICFIGURES_CLINESEGMENT_H
#define GEOMETRICFIGURES_CLINESEGMENT_H

#include <vector>
#include <utility>
#include <iomanip>
#include "IShape.h"
#include "CPoint.h"

class CLineSegment : public IShape {
public:
    CLineSegment(std::vector<CPoint> points, std::vector<uint32_t> colors);
    double GetPerimeter() override;
    double GetArea() override;
    std::string ToString() override;
    uint32_t GetOutlineColor() override;
    CPoint GetStartPoint();
    CPoint GetEndPoint();
private:
    std::vector<CPoint> m_points;
    std::vector<uint32_t> m_colors;
    static std::string GetStringColor(uint32_t color);
};


#endif //GEOMETRICFIGURES_CLINESEGMENT_H
