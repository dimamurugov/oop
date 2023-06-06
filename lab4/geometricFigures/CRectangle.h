#ifndef GEOMETRICFIGURES_CRECTANGLE_H
#define GEOMETRICFIGURES_CRECTANGLE_H

#include <vector>
#include "ISolidShape.h"
#include "CPoint.h"

class CRectangle : public ISolidShape {
    CRectangle(std::vector<CPoint>& peaks);
private:
    std::vector<CPoint> m_peaks; // peaks -> вершины
};

#endif //GEOMETRICFIGURES_CRECTANGLE_H
