#ifndef GEOMETRICFIGURES_ISOLIDSHAPE_H
#define GEOMETRICFIGURES_ISOLIDSHAPE_H

#include "IShape.h"

class ISolidShape: public IShape {
public:
    virtual uint32_t GetFillColor() = 0;
};


#endif //GEOMETRICFIGURES_ISOLIDSHAPE_H
