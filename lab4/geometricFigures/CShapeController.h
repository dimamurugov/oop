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
    CREATE_RECTANGLE,
    CREATE_TRIANGLE,
    CREATE_CIRCLE,
    CREATE_LINE_SEGMENT,
    PRINT_MAX_AREA,
    PRINT_MIN_PERIMETER
};

struct Params {
    std::optional<CommandType> commandType;
    std::optional<std::string> peaks;
    std::optional<std::string> colors;
};

namespace
{
    // перенести в cpp файл
    const int CONSTANT_COLOR = 8;
    const int CONSTANT_ARGUMENTS = 3;
    const int CONSTANT_COMMAND_TYPE = 1;
    const int CONSTANT_RECTANGLE_X = 0;
    const int CONSTANT_RECTANGLE_Y = 1;
    const int CONSTANT_RECTANGLE_WIDTH = 2;
    const int CONSTANT_RECTANGLE_HEIGHT = 3;
    const int CONSTANT_LINE_SEGMENT_X1 = 0;
    const int CONSTANT_LINE_SEGMENT_Y1 = 1;
    const int CONSTANT_LINE_SEGMENT_X2 = 2;
    const int CONSTANT_LINE_SEGMENT_Y2 = 3;
    const int CONSTANT_CIRCLE_X = 0;
    const int CONSTANT_CIRCLE_Y = 1;
    const int CONSTANT_CIRCLE_RADIUS = 2;
    const std::string REGEX_VALIDATE_ARGUMENTS = R"(^([\d\.]+)\s([\d\.]*)\s?([\d\.]*)\s?([\d\.]*)\s?([\d\.]*)\s?([\d\.]*)\s?$)";
    const std::string REGEX_COMMAND_LINE = R"(^(rectangle|triangle|circle|line|printMaxArea|printMinPerimeter)(\s|$)((([0-9]*(\.[0-9]+)?)(\s?)){0,6})(((\w{6})(\s?)){0,2})$)";
    // R"(^(rectangle|triangle|circle|line|printMaxArea|printMinPerimeter)(\s|$)((([0-9]*(\.[0-9]+)?)(\s?)){0,6})(((\w{6})(\s?)){0,2})$)";
    // new R"(^(rectangle|triangle|circle|line|printMaxArea|printMinPerimeter)(\s|$)((([-0-9]*(\.[0-9]+)?)(\s?)){0,6})(((\w{6})(\s?)){0,2})$)"
    const std::string REGEX_VALIDATE_COLOR = "^([1,2,3,4,5,6,7,8,9,0,a,b,c,d,e,f]{6})\\s?([1,2,3,4,5,6,7,8,9,0,a,b,c,d,e,f]{6})?$";
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
            { "rectangle", CommandType::CREATE_RECTANGLE },
            { "triangle", CommandType::CREATE_TRIANGLE },
            { "circle", CommandType::CREATE_CIRCLE },
            { "line", CommandType::CREATE_LINE_SEGMENT },
            { "printMaxArea", CommandType::PRINT_MAX_AREA },
            { "printMinPerimeter", CommandType::PRINT_MIN_PERIMETER },
    };
}

class CShapeController {
public:
    void LineExecution(const std::string &line);
    void InitRectangle(std::vector<double> arguments, std::vector<uint32_t> colors);
    void InitTriangle(std::vector<double> arguments, std::vector<uint32_t> colors);
    void InitCircle(std::vector<double> arguments, std::vector<uint32_t> colors);
    void InitLineSegment(std::vector<double> arguments, std::vector<uint32_t> colors);
    static std::optional<CommandType> GetCommandType(const std::string& str);
    static std::optional<std::vector<double>> ParseArguments(const std::string& arguments);
    static std::vector<uint32_t> ParseColors(const std::string& colors);
    void PrintMaxAreaShape();
    void PrintMinPerimeterShape();
private:
    std::vector<IShape *> m_shape;
};

#endif //GEOMETRICFIGURES_CSHAPECONTROLLER_H
