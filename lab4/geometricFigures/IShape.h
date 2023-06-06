#ifndef GEOMETRICFIGURES_ISHAPE_H
#define GEOMETRICFIGURES_ISHAPE_H


#include <string>

class IShape {
public:
    virtual double GetArea() = 0;
    virtual double GetPerimeter() = 0;
    virtual std::string ToString() = 0;
    virtual uint32_t GetOutlineColor() = 0;
};


#endif //GEOMETRICFIGURES_ISHAPE_H
