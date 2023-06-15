#ifndef GEOMETRICFIGURES_ISHAPE_H
#define GEOMETRICFIGURES_ISHAPE_H

#include <string>
#include <limits>

namespace {
    const int NUMBER_OF_DIGITS_IN_COLOR = 6;
    const std::string DELIMITER = " ";
    const uint32_t UINT32_T_MAX = std::numeric_limits<uint32_t>::max();
}

class IShape {
public:
    virtual double GetArea() = 0;
    virtual double GetPerimeter() = 0;
    virtual std::string ToString() = 0;
    virtual uint32_t GetOutlineColor() = 0;
};


#endif //GEOMETRICFIGURES_ISHAPE_H
