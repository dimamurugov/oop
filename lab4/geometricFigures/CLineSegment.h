#ifndef GEOMETRICFIGURES_CLINESEGMENT_H
#define GEOMETRICFIGURES_CLINESEGMENT_H

#include <vector>
#include <utility>
#include <iomanip>
#include <optional>
#include "IShape.h"
#include "CPoint.h"

class CLineSegment : public IShape {
public:
    CLineSegment(std::vector<CPoint> points, std::vector<uint32_t> colors);
    const double GetPerimeter() override;
    const double GetArea() override;
    const std::string ToString() override;
    const std::optional<uint32_t> GetOutlineColor() override;
    const CPoint GetStartPoint();
    const CPoint GetEndPoint();
private:
    std::vector<CPoint> m_points;//opt можно хранить в разных
    std::vector<uint32_t> m_colors;
    const static std::string GetStringColor(uint32_t color);

    static std::string Format(double f);
};


#endif //GEOMETRICFIGURES_CLINESEGMENT_H
