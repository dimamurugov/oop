#ifndef GEOMETRICFIGURES_CSHAPECONTROLLER_H
#define GEOMETRICFIGURES_CSHAPECONTROLLER_H

#include <string>
#include <map>
#include <optional>

enum class ShapesType
{
    RECTANGLE,
    TRIANGLE,
    CIRCLE
};

struct Params {
    std::optional<ShapesType> shapeType;
    std::optional<std::string> peaks;
    std::optional<std::string> colors;
};

namespace {
    const std::map<std::string, ShapesType> shapes = {
            { "rectangle", ShapesType::RECTANGLE },
            { "triangle", ShapesType::TRIANGLE },
            { "circle", ShapesType::CIRCLE },
    };
}

class CShapeController {
public:
    static void LineExecution(const std::string &line);
    static void InitRectangle(const std::string &points, std::string colors);
    static std::optional<ShapesType> GetShapeType(const std::string& str);
private:
    std::map<int, double> m_rectangles;
};

#endif //GEOMETRICFIGURES_CSHAPECONTROLLER_H
