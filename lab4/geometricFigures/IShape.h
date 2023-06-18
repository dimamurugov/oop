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
    // const необхоидмо справа после круглых скобочек
    virtual const double GetArea() = 0;
    virtual const double GetPerimeter() = 0;
    virtual const std::string ToString() = 0;
    virtual const std::optional<uint32_t> GetOutlineColor() = 0;
    virtual ~IShape() = default;
};


#endif //GEOMETRICFIGURES_ISHAPE_H
