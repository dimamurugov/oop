#ifndef GEOMETRICFIGURES_ISOLIDSHAPE_H
#define GEOMETRICFIGURES_ISOLIDSHAPE_H

#include <optional>
#include "IShape.h"

class ISolidShape : public IShape {
public:
    virtual const std::optional<uint32_t> GetFillColor() = 0;
    ~ISolidShape() override = default;
};


#endif //GEOMETRICFIGURES_ISOLIDSHAPE_H
