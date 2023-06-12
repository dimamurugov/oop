#include <regex>
#include <iostream>
#include "CShapeController.h"
#include "CTriangle.h"
#include "CCircle.h"

void CShapeController::LineExecution(const std::string &line) {
    std::cmatch matched;
    std::regex pattern(R"(^(rectangle|triangle|circle)(\s)((([0-9]*(\.[0-9]+)?)(\s)){1,6})(((\w{6})(\s?)){1,2})$)");

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
            case ShapesType::CIRCLE:
                InitCircle(arguments.value(), colorsParsed.value());
                break;
        }
    } else {
        std::cout << NOT_READ_COMMAND;
    }
}

//        for (int i = 0; i < matched.size(); ++i) {
//            std::cout << i << ' ' << matched[i] << std::endl;
//        }

void CShapeController::InitRectangle(std::vector<double> arguments, std::optional<std::vector<std::string>> colors) {
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
    // 1) R"((([\d\.]+)\s){1,6})"
    // 2) R"(([\d\.]+)\s([\d\.]+)\s([\d\.]+)\s([\d\.]+)\s)"
    // 3) ([\d\.]+){1,6}
    // 4) ([\d\.]+)\s(([\d\.]+)\s)?(([\d\.]+)\s)?(([\d\.]+)\s)?(([\d\.]+)\s)?(([\d\.]+)\s)?
    // 5) ([\d\.]+)(\s|$)
    // 6) ^([\d\.]+)\s([\d\.]*)\s?([\d\.]*)\s?([\d\.]*)\s?([\d\.]*)\s?([\d\.]*)\s?$
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

std::optional<std::vector<std::string>> CShapeController::ParseColors(const std::string &line) {
    // можно улучшить регуляркой - а надо ли?
    std::vector<std::string> colors;
    std::string delimiter = " ";
    std::string firstColor = line.substr(0, line.find(delimiter));
    std::string secondColor = line.substr(line.find(delimiter));


//    uint32_t color = atoi(test.c_str());
//    auto color = static_cast<uint32_t>(std::stoul(firstColor));
//    colors.push_back(color);
//    colors.push_back(static_cast<uint32_t>(std::stoul(secondColor)));

//    ss >> color;


//    if (!ss.eof()) {
//        std::cout << NOT_COLOR;
//        return std::nullopt;
//    }

    colors.push_back(firstColor);
    colors.push_back(secondColor);
    return colors;
}

void CShapeController::InitTriangle(std::vector<double> arguments, std::optional<std::vector<std::string>> colors) {
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

    if (triangle.GetArea() != 0) {
        m_triangles.push_back(triangle);
    } else {
        std::cout << ITS_LINE;
    }
}

void CShapeController::InitCircle(std::vector<double> arguments, std::optional<std::vector<std::string>> colors) {
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
