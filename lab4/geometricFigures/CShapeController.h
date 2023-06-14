#ifndef GEOMETRICFIGURES_CSHAPECONTROLLER_H
#define GEOMETRICFIGURES_CSHAPECONTROLLER_H

#include <string>
#include <map>
#include <optional>
#include "CRectangle.h"
#include "CTriangle.h"
#include "CCircle.h"
#include "CLineSegment.h"

enum class CommandType
{
    RECTANGLE,
    TRIANGLE,
    CIRCLE,
    LINE_SEGMENT,
    PRINT_MAX_AREA,
    PRINT_MIN_PERIMETER
};

struct Params {
    std::optional<CommandType> shapeType;
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
    const std::string SHAPES_ARRAY_EMPTY = "Shapes array is empty!\n";
    const std::string MIN_PERIMETER = "Min Perimeter: \n";
    const std::string MAX_AREA = "Max Area: \n";
}

namespace {
    const std::map<std::string, CommandType> command = {
            { "rectangle", CommandType::RECTANGLE },
            { "triangle", CommandType::TRIANGLE },
            { "circle", CommandType::CIRCLE },
            { "line", CommandType::LINE_SEGMENT },
            { "printMaxArea", CommandType::PRINT_MAX_AREA },
            { "printMinPerimeter", CommandType::PRINT_MIN_PERIMETER },
    };
}

class CShapeController {
public:
    void LineExecution(const std::string &line);
    void InitRectangle(std::vector<double> arguments, std::optional<std::vector<uint32_t>> colors);
    void InitTriangle(std::vector<double> arguments, std::optional<std::vector<uint32_t>> colors);
    void InitCircle(std::vector<double> arguments, std::optional<std::vector<uint32_t>> colors);
    void InitLineSegment(std::vector<double> arguments, std::optional<std::vector<uint32_t>> colors);
    static std::optional<CommandType> GetCommandType(const std::string& str);
    static std::optional<std::vector<double>> ParseArguments(const std::string& arguments);
    static std::optional<std::vector<uint32_t>> ParseColors(const std::string& colors);
    void PrintMaxAreaShape();
    void PrintMinPerimeterShape();
private:
    // хранить отдельный вектор для каждой фигуры
    // нужен индекс для сохранения порядка создания
    std::vector<CRectangle> m_rectangles;
    std::vector<CTriangle> m_triangles;
    std::vector<CCircle> m_circles;
    std::vector<CLineSegment> m_lineSegment;
    std::vector<IShape *> m_shape;
};

#endif //GEOMETRICFIGURES_CSHAPECONTROLLER_H
