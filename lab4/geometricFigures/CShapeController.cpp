#include <regex>
#include <iostream>
#include "CShapeController.h"
#include "CTriangle.h"
#include "CCircle.h"
#include "CLineSegment.h"

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

void CShapeController::InitRectangle(std::vector<double> arguments, std::vector<uint32_t> colors) {
   double x = arguments[CONSTANT_RECTANGLE_X];
   double y = arguments[CONSTANT_RECTANGLE_Y];
   double width = arguments[CONSTANT_RECTANGLE_WIDTH];
   double height = arguments[CONSTANT_RECTANGLE_HEIGHT];
   CPoint point(x, y);
   if (width <= 0 || height <= 0) {
       std::cout << SIDE_CANNOT_BE_ZERO;
       return;
   }
   CRectangle rectangle(point, width, height, colors);
   m_shape.push_back(new CRectangle(point, width, height, colors));
}//print с 2 числами после запятой

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

void CShapeController::InitTriangle(std::vector<double> arguments, std::vector<uint32_t> colors) {
    if (arguments.size() < 6) {
        std::cout << INCORRECT_POINTS_TRIANGLE;
        return;
    }
    std::vector<CPoint> points;
    for (int i = 0; i < arguments.size(); i=i+2) {
        double x = arguments[i];
        double y = arguments[i + 1];
        char x1 = 'c';
        CPoint point = {x1, y};
        points.push_back(point);
    }
    auto triangle = new CTriangle(points, colors);
    if (triangle->GetArea() != 0) {
        m_shape.push_back(triangle);
    } else {
        std::cout << ITS_LINE;
    }
}

std::vector<uint32_t> CShapeController::ParseColors(const std::string &line) {
    std::cmatch matched;
    std::regex pattern(REGEX_VALIDATE_COLOR);
    std::vector<std::string> stringColors;
    if (regex_match(line.c_str(), matched, pattern)) {
        for (int i = 1; i < matched.size(); ++i) {
            stringColors.push_back(matched[i]);
        }
    }
    std::vector<uint32_t> colors;
    if (stringColors.empty()) {
        return colors;
    }
    for (auto & stringColor : stringColors) {
        if (!stringColor.empty()) {
            uint32_t colorValue = stoi(stringColor, nullptr, 16);
            colors.push_back(colorValue);
        }
    }
    return colors;
}

void CShapeController::InitLineSegment(std::vector<double> arguments, std::vector<uint32_t> colors) {
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
    m_shape.push_back(new CLineSegment(points, colors));
}

void CShapeController::InitCircle(std::vector<double> arguments, std::vector<uint32_t> colors) {
    if (arguments.size() < 2) {
        std::cout << INCORRECT_POINTS_CIRCLE;
        return;
    }

    double x = arguments[CONSTANT_CIRCLE_X];
    double y = arguments[CONSTANT_CIRCLE_Y];
    double radius = arguments[CONSTANT_CIRCLE_RADIUS];
    if (radius <= 0) {
        std::cout << NOT_RADIUS_ZERO;
        return;
    }
    CPoint center = {x, y};
    m_shape.push_back(new CCircle(center, radius, colors));
}

void CShapeController::PrintMaxAreaShape() {
    if (m_shape.empty()) {
        std::cout << SHAPES_ARRAY_EMPTY;
        return;
    }

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
