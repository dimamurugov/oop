#ifndef GEOMETRICFIGURES_ISOLIDSHAPE_H
#define GEOMETRICFIGURES_ISOLIDSHAPE_H

#include "IShape.h"

class ISolidShape: public IShape {
public:
    virtual std::string GetFillColor() = 0;
};


#endif //GEOMETRICFIGURES_ISOLIDSHAPE_H
