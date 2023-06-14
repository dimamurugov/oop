#ifndef GEOMETRICFIGURES_CSHAPECONTROLLER_H
#define GEOMETRICFIGURES_CSHAPECONTROLLER_H

#include <string>
#include <map>
#include <optional>
#include "CRectangle.h"
#include "CTriangle.h"
#include "CCircle.h"
#include "CLineSegment.h"

enum class ShapesType
{
    RECTANGLE,
    TRIANGLE,
    CIRCLE,
    LINE_SEGMENT
};

struct Params {
    std::optional<ShapesType> shapeType;
    std::optional<std::string> peaks;
    std::optional<std::string> colors;
};

namespace
{
    const std::string NOT_NUMBER = "It's not a number!\n";
    const std::string NOT_COLOR = "It's not a color!\n";
    const std::string INCORRECT_POINTS_TRIANGLE = "Incorrect coordinates for Triangle!\n";
    const std::string INCORRECT_POINTS_CIRCLE = "Incorrect number of coordinates for a circle!\n";
    const std::string INCORRECT_POINTS_LINE_SEGMENT = "Invalid number of coordinates for segment!\n";
    const std::string ITS_LINE = "Vertices cannot be on the same line!\n";
    const std::string SIDE_CANNOT_BE_ZERO = "Side cannot be negative or zero!\n";
    const std::string INCORRECT_COORDINATES_FIGURES = "Incorrect coordinates or dimensions of the sides of the shape!\n";
    const std::string NOT_READ_COMMAND = "Couldn't read command!\n";
    const std::string NOT_RADIUS_ZERO = "Radius must not be zero!\n";
}

namespace {
    const std::map<std::string, ShapesType> shapes = {
            { "rectangle", ShapesType::RECTANGLE },
            { "triangle", ShapesType::TRIANGLE },
            { "circle", ShapesType::CIRCLE },
            { "line", ShapesType::LINE_SEGMENT },
    };
}

class CShapeController {
public:
    void LineExecution(const std::string &line);
    void InitRectangle(std::vector<double> arguments, std::optional<std::vector<uint32_t>> colors);
    void InitTriangle(std::vector<double> arguments, std::optional<std::vector<uint32_t>> colors);
    void InitCircle(std::vector<double> arguments, std::optional<std::vector<uint32_t>> colors);
    void InitLineSegment(std::vector<double> arguments, std::optional<std::vector<uint32_t>> colors);
    static std::optional<ShapesType> GetShapeType(const std::string& str);
    static std::optional<std::vector<double>> ParseArguments(const std::string& arguments);
    static std::optional<std::vector<uint32_t>> ParseColors(const std::string& colors);
private:
    // хранить отдельный вектор для каждой фигуры
    // нужен индекс для сохранения порядка создания
    std::vector<CRectangle> m_rectangles;
    std::vector<CTriangle> m_triangles;
    std::vector<CCircle> m_circles;
    std::vector<CLineSegment> m_lineSegment;
};

#endif //GEOMETRICFIGURES_CSHAPECONTROLLER_H
