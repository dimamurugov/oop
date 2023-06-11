#ifndef GEOMETRICFIGURES_CSHAPECONTROLLER_H
#define GEOMETRICFIGURES_CSHAPECONTROLLER_H

#include <string>
#include <map>
#include <optional>
#include "CRectangle.h"

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

namespace
{
    const std::string NOT_NUMBER = "It's not a number!\n";
}

namespace {
    const std::map<std::string, ShapesType> shapes = {
            { "rectangle", ShapesType::RECTANGLE },
            { "triangle", ShapesType::TRIANGLE },
            { "circle", ShapesType::CIRCLE },
    };
}

class CShapeController {
public:
    void LineExecution(const std::string &line);
    void InitRectangle(const std::string &points, std::string colors);
    static std::optional<ShapesType> GetShapeType(const std::string& str);
    static std::optional<std::vector<double>> ParseArguments(const std::string& arguments);
    static std::optional<std::vector<std::string>> ParseColors(const std::string& colors);
private:
    // хранить отдельный вектор для каждой фигуры
    // нужен индекс для сохранения порядка создания
    std::vector<CRectangle> m_rectangles;
};

#endif //GEOMETRICFIGURES_CSHAPECONTROLLER_H
