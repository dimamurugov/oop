#include <regex>
#include <iostream>
#include "CShapeController.h"
#include "CTriangle.h"
#include "CCircle.h"
#include "CLineSegment.h"

void CShapeController::LineExecution(const std::string &line) {
    std::cmatch matched;
    std::regex pattern(R"(^(rectangle|triangle|circle|line)(\s)((([0-9]*(\.[0-9]+)?)(\s)){1,6})(((\w{6})(\s?)){1,2})$)");

    if (regex_match(line.c_str(), matched, pattern))
    {
        Params params = {std::nullopt, std::nullopt, std::nullopt};
        params.shapeType = GetShapeType(matched[1]);
        params.peaks = matched[3];
        params.colors = matched[8];
        auto arguments = ParseArguments(params.peaks.value());
        auto colorsParsed = ParseColors(params.colors.value());

        switch (params.shapeType.value())
        {
            case ShapesType::RECTANGLE:
                InitRectangle(arguments.value(), colorsParsed.value());
                break;
            case ShapesType::TRIANGLE:
                InitTriangle(arguments.value(), colorsParsed.value());
                break;
            case ShapesType::CIRCLE:
                InitCircle(arguments.value(), colorsParsed.value());
                break;
            case ShapesType::LINE_SEGMENT:
                InitLineSegment(arguments.value(), colorsParsed.value());
                break;
        }
    } else {
        std::cout << NOT_READ_COMMAND;
    }
}

//        for (int i = 0; i < matched.size(); ++i) {
//            std::cout << i << ' ' << matched[i] << std::endl;
//        }

void CShapeController::InitRectangle(std::vector<double> arguments, std::optional<std::vector<uint32_t>> colors) {
   double x = arguments[0];
   double y = arguments[1];
   double width = arguments[2];
   double height = arguments[3];
   CPoint point(x, y);
   if (width <= 0 || height <= 0) {
       std::cout << SIDE_CANNOT_BE_ZERO;
       return;
   }
   CRectangle rectangle(point, width, height, colors.value());
   std::cout << rectangle.ToString() << std::endl;
   m_rectangles.push_back(rectangle);
}

std::optional<ShapesType> CShapeController::GetShapeType(const std::string &str) {
    if (shapes.find(str) != shapes.end())
    {
        return shapes.at(str);
    }
    return std::nullopt;
}

std::optional<std::vector<double>> CShapeController::ParseArguments(const std::string &arguments) {
    std::cmatch matched;
    std::regex pattern(R"(^([\d\.]+)\s([\d\.]*)\s?([\d\.]*)\s?([\d\.]*)\s?([\d\.]*)\s?([\d\.]*)\s?$)");
    std::vector<double> numbers;
    if (regex_match(arguments.c_str(), matched, pattern))
    {
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
    } else {
        std::cout << INCORRECT_COORDINATES_FIGURES;
    }
    return numbers;
}

void CShapeController::InitTriangle(std::vector<double> arguments, std::optional<std::vector<uint32_t>> colors) {
    if (arguments.size() < 6) {
        std::cout << INCORRECT_POINTS_TRIANGLE;
        return;
    }
    std::vector<CPoint> points;
    for (int i = 0; i < arguments.size(); i=i+2) {
        double x = arguments[i];
        double y = arguments[i + 1];

        CPoint point = {x, y};
        points.push_back(point);
    }
    CTriangle triangle(points, colors.value());
    std::cout << triangle.ToString() << std::endl;
    if (triangle.GetArea() != 0) {
        m_triangles.push_back(triangle);
    } else {
        std::cout << ITS_LINE;
    }
}

std::optional<std::vector<uint32_t>> CShapeController::ParseColors(const std::string &line) {
    std::vector<uint32_t> colors;
    std::string delimiter = " ";
    std::string firstColor = line.substr(0, line.find(delimiter));
    std::string secondColor = line.substr(line.find(delimiter));

    uint32_t firstColorValue = stoi(firstColor, 0, 16);
    uint32_t secondColorValue = stoi(secondColor, 0, 16);
    colors.push_back(firstColorValue);
    colors.push_back(secondColorValue);
    return colors;
}

void CShapeController::InitLineSegment(std::vector<double> arguments, std::optional<std::vector<uint32_t>> colors) {
    if (arguments.size() < 4) {
        std::cout << INCORRECT_POINTS_LINE_SEGMENT;
        return;
    }

    double x1 = arguments[0];
    double y1 = arguments[1];
    double x2 = arguments[2];
    double y2 = arguments[3];

    CPoint startPoint = {x1, y1};
    CPoint endPoint = {x2, y2};
    std::vector<CPoint> points = {startPoint, endPoint};
    CLineSegment lineSegment(points, colors.value());
    std::cout << lineSegment.ToString() << std::endl;
    m_lineSegment.push_back(lineSegment);
}

void CShapeController::InitCircle(std::vector<double> arguments, std::optional<std::vector<uint32_t>> colors) {
    if (arguments.size() < 2) {
        std::cout << INCORRECT_POINTS_CIRCLE;
        return;
    }

    double x = arguments[0];
    double y = arguments[1];
    double radius = arguments[2];
    if (radius <= 0) {
        std::cout << NOT_RADIUS_ZERO;
        return;
    }
    CPoint center = {x, y};
    CCircle circle(center, radius, colors.value());
    std::cout << circle.ToString();
    m_circles.push_back(circle);
}
