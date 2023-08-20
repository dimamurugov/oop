#include <regex>
#include <iostream>
#include "CShapeController.h"
#include "CTriangle.h"
#include "CCircle.h"
#include "CLineSegment.h"

namespace
{
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
    const std::string REGEX_VALIDATE_ARGUMENTS = R"(^(-?[\d\.]+)\s(-?[\d\.]*)\s?(-?[\d\.]*)\s?(-?[\d\.]*)\s?(-?[\d\.]*)\s?(-?[\d\.]*)\s?$)";
    const std::string REGEX_COMMAND_LINE = R"(^(rectangle|triangle|circle|line|printMaxArea|printMinPerimeter)(\s|$)((([0-9-]*(\.[0-9]+)?)(\s?)){0,6})(((\w{6})(\s?)){0,2})$)";
    const std::string REGEX_VALIDATE_COLOR = "^([1,2,3,4,5,6,7,8,9,0,a,b,c,d,e,f]{6}|null)\\s?([1,2,3,4,5,6,7,8,9,0,a,b,c,d,e,f]{6})?$";
    const std::string NOT_NUMBER = "It's not a number!\n";
    const std::string INCORRECT_POINTS_TRIANGLE = "Incorrect coordinates for Triangle!\n";
    const std::string INCORRECT_POINTS_CIRCLE = "Incorrect number of coordinates for a circle!\n";
    const std::string INCORRECT_POINTS_LINE_SEGMENT = "Invalid number of coordinates for segment!\n";
    const std::string NOT_READ_COMMAND = "Couldn't read command!\n";
    const std::string SHAPES_ARRAY_EMPTY = "Shapes array is empty!\n";
    const std::string MIN_PERIMETER = "Min Perimeter: \n";
    const std::string MAX_AREA = "Max Area: \n";

    const std::map<std::string, CommandType> command = {
            { "rectangle", CommandType::CREATE_RECTANGLE },
            { "triangle", CommandType::CREATE_TRIANGLE },
            { "circle", CommandType::CREATE_CIRCLE },
            { "line", CommandType::CREATE_LINE_SEGMENT },
            { "printMaxArea", CommandType::PRINT_MAX_AREA },
            { "printMinPerimeter", CommandType::PRINT_MIN_PERIMETER },
    };
}

void CShapeController::LineExecution(const std::string &line) {
    std::cmatch matched;
    std::regex pattern(REGEX_COMMAND_LINE);
    if (!regex_match(line.c_str(), matched, pattern))
    {
        std::cout << NOT_READ_COMMAND;
        return;
    }
    Params params = {std::nullopt, std::nullopt, std::nullopt};
    params.commandType = GetCommandType(matched[CONSTANT_COMMAND_TYPE]);
    params.peaks = matched[CONSTANT_ARGUMENTS];
    params.colors = matched[CONSTANT_COLOR];
    auto arguments = ParseArguments(params.peaks.value());
    auto colorsParsed = ParseColors(params.colors.value());
    switch (params.commandType.value())
    {
        case CommandType::CREATE_RECTANGLE:
            InitRectangle(arguments.value(), colorsParsed);
            break;
        case CommandType::CREATE_TRIANGLE:
            InitTriangle(arguments.value(), colorsParsed);
            break;
        case CommandType::CREATE_CIRCLE:
            InitCircle(arguments.value(), colorsParsed);
            break;
        case CommandType::CREATE_LINE_SEGMENT:
            InitLineSegment(arguments.value(), colorsParsed);
            break;
        case CommandType::PRINT_MAX_AREA:
            PrintMaxAreaShape();
            break;
        case CommandType::PRINT_MIN_PERIMETER:
            PrintMinPerimeterShape();
    }
}

// Переименовать
void CShapeController::InitRectangle(std::vector<double> arguments, ColorTypes colors) {
   double x = arguments[CONSTANT_RECTANGLE_X];
   double y = arguments[CONSTANT_RECTANGLE_Y];
   double width = arguments[CONSTANT_RECTANGLE_WIDTH];
   double height = arguments[CONSTANT_RECTANGLE_HEIGHT];
   CPoint point(x, y);

    try {
        // утечка памяти
        auto rectangle = new CRectangle(point, width, height, colors);
        m_shape.push_back(rectangle);
    } catch (const char* e) {
        std::cout << e << std::endl;
    }
}

std::optional<CommandType> CShapeController::GetCommandType(const std::string &str) {
    auto it = command.find(str);
    if (it != command.end()) {
       return it->second;
    }
    return std::nullopt;
}

std::optional<std::vector<double>> CShapeController::ParseArguments(const std::string &arguments) {
    std::cmatch matched;
    std::regex pattern(REGEX_VALIDATE_ARGUMENTS);
    std::vector<double> numbers;
    if (!regex_match(arguments.c_str(), matched, pattern))
    {
        return std::nullopt;
    }

    for (int i = 1; i < matched.size(); ++i) {
        std::stringstream ss(matched[i]);
        double side;
        ss >> side;
        if (matched[i] == "") {
            break;
        }
        if (!ss.eof()) {
            std::cout << NOT_NUMBER;
            return std::nullopt;
        }
        numbers.push_back(side);
    }
    return numbers;
}

void CShapeController::InitTriangle(std::vector<double> arguments, ColorTypes colors) {
    if (arguments.size() < 6) {
        std::cout << INCORRECT_POINTS_TRIANGLE;
        return;
    }
    std::vector<CPoint> points;
    for (int i = 0; i < arguments.size(); i=i+2) {
        double x = arguments[i];
        double y = arguments[i + 1];
        CPoint point(x, y);
        points.push_back(point);
    }
    try {
        auto triangle = new CTriangle(points, colors);
        // использовать умные указатели -
        m_shape.push_back(triangle);
    } catch (const char* e) {
        std::cout << e << std::endl;
    }
}

ColorTypes CShapeController::ParseColors(const std::string &line) {
    std::cmatch matched;
    std::regex pattern(REGEX_VALIDATE_COLOR);
    ColorTypes colors;

    if (regex_match(line.c_str(), matched, pattern)) {
        std::string outlineColor = matched[1];
        std::string fillColor = matched[2];
        std::vector<std::optional<uint32_t>> stringColors;

        for (int i = 1; i < matched.size(); ++i) {
            std::string color = matched[i];

            if (!color.empty()) {
                uint32_t colorValue = stoi(color, nullptr, 16);
                stringColors.emplace_back(colorValue);
            } else {
                stringColors.emplace_back(std::nullopt);
            }
        }

        colors = {stringColors[0], stringColors[1]};
    }

    return colors;
}

void CShapeController::InitLineSegment(std::vector<double> arguments, ColorTypes colors) {
    if (arguments.size() < 4) {
        std::cout << INCORRECT_POINTS_LINE_SEGMENT;
        return;
    }

    double x1 = arguments[CONSTANT_LINE_SEGMENT_X1];
    double y1 = arguments[CONSTANT_LINE_SEGMENT_Y1];
    double x2 = arguments[CONSTANT_LINE_SEGMENT_X2];
    double y2 = arguments[CONSTANT_LINE_SEGMENT_Y2];

    CPoint startPoint = {x1, y1};
    CPoint endPoint = {x2, y2};
    std::vector<CPoint> points = {startPoint, endPoint};
    try {
        auto lineSegment = new CLineSegment(points, colors);
        m_shape.push_back(lineSegment);
    } catch (const char* e) {
        std::cout << e << std::endl;
    }
}

void CShapeController::InitCircle(std::vector<double> arguments, ColorTypes colors) {
    if (arguments.size() < 2) {
        std::cout << INCORRECT_POINTS_CIRCLE;
        return;
    }

    double x = arguments[CONSTANT_CIRCLE_X];
    double y = arguments[CONSTANT_CIRCLE_Y];
    double radius = arguments[CONSTANT_CIRCLE_RADIUS];

    CPoint center = {x, y};
    try {
        auto circle = new CCircle(center, radius, colors);
        m_shape.push_back(circle);
    } catch (const char* e) {
        std::cout << e << std::endl;
    }
}

// Воспользоваться стандартным алгоритмом
void CShapeController::PrintMaxAreaShape() {
    if (m_shape.empty()) {
        std::cout << SHAPES_ARRAY_EMPTY;
        return;
    }
    std::vector<double> shapeAreas;
    for (int i = 0; i < m_shape.size(); ++i) {
        shapeAreas.push_back(m_shape[i]->GetArea());
    }

    std::cout << *max_element(shapeAreas.begin(), shapeAreas.end());

    int indexShapeWithMaxArea = 0;
    double maxArea = m_shape[0]->GetArea();

    for (int i = 1; i < m_shape.size(); ++i) {
        auto area = m_shape[i]->GetArea();
        if (area > maxArea) {
            indexShapeWithMaxArea = i;
        }
    }

    std::cout << MAX_AREA;
    std::cout << m_shape[indexShapeWithMaxArea]->ToString();
}

// Воспользоваться стандартным алгоритмом
void CShapeController::PrintMinPerimeterShape() {
    if (m_shape.empty()) {
        std::cout << SHAPES_ARRAY_EMPTY;
        return;
    }

    int indexShapeWithMinPerimeter = 0;
    double minPerimeter = m_shape[0]->GetPerimeter();

    for (int i = 1; i < m_shape.size(); ++i) {
        auto perimeter = m_shape[i]->GetPerimeter();

        if (perimeter < minPerimeter) {
            indexShapeWithMinPerimeter = i;
        }
    }
    std::cout << MIN_PERIMETER;
    std::cout << m_shape[indexShapeWithMinPerimeter]->ToString();
}
