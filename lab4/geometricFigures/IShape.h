#ifndef GEOMETRICFIGURES_ISHAPE_H
#define GEOMETRICFIGURES_ISHAPE_H


#include <string>

class IShape {
public:
    virtual double GetArea() = 0;
    virtual double GetPerimeter() = 0;
    virtual std::string ToString() = 0;
    // должен быть uint32_t
    virtual std::string GetOutlineColor() = 0;
};


#endif //GEOMETRICFIGURES_ISHAPE_H
