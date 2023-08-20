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

class CShapeController {
public:
    void LineExecution(const std::string &line);
    void InitRectangle(std::vector<double> arguments, ColorTypes colors);
    void InitTriangle(std::vector<double> arguments, ColorTypes colors);
    void InitCircle(std::vector<double> arguments, ColorTypes colors);
    void InitLineSegment(std::vector<double> arguments, ColorTypes colors);
    static std::optional<CommandType> GetCommandType(const std::string& str);
    static std::optional<std::vector<double>> ParseArguments(const std::string& arguments);
    static ColorTypes ParseColors(const std::string& colors);
    void PrintMaxAreaShape();
    void PrintMinPerimeterShape();
private:
    std::vector<IShape *> m_shape;
};

#endif //GEOMETRICFIGURES_CSHAPECONTROLLER_H
