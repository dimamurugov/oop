#ifndef GEOMETRICFIGURES_ISHAPE_H
#define GEOMETRICFIGURES_ISHAPE_H

#include <string>
#include <limits>
// объявить константы inlint а namespace убрать
namespace {
    const int NUMBER_OF_DIGITS_IN_COLOR = 6;
    const std::string DELIMITER = " ";
}

// название не то
struct ColorTypes {
    std::optional<uint32_t> outlineColor;
    std::optional<uint32_t> fillColor;
};

class IShape {
public:
    // const необхоидмо справа после круглых скобочек - для чего?
    virtual const double GetArea() = 0;// что означает =0 у виртуального метода?
    virtual const double GetPerimeter() = 0;
    virtual const std::string ToString() = 0;
    virtual const std::optional<uint32_t> GetOutlineColor() = 0;
    virtual ~IShape() = default; // выяснить для чего нужен виртуальный деструктор и где
};


#endif //GEOMETRICFIGURES_ISHAPE_H
