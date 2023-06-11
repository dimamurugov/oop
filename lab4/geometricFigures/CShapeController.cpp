#include <regex>
#include <iostream>
#include "CShapeController.h"

void CShapeController::LineExecution(const std::string &line) {
    std::cmatch matched;
    std::regex pattern(R"(^(rectangle|triangle|circle)(\s)((([0-9]*(\.[0-9]+)?)(\s)){1,4})(((\w{6})(\s?)){1,2})$)");

    if (regex_match(line.c_str(), matched, pattern))
    {
        Params params = {std::nullopt, std::nullopt, std::nullopt};
        params.shapeType = GetShapeType(matched[1]);
        params.peaks = matched[3];
        params.colors = matched[8];

        switch (params.shapeType.value())
        {
            case ShapesType::RECTANGLE:
                InitRectangle(params.peaks.value(), params.colors.value());
                break;
            case ShapesType::TRIANGLE:
            case ShapesType::CIRCLE:
                break;
        }
    }
}

//        for (int i = 0; i < matched.size(); ++i) {
//            std::cout << i << ' ' << matched[i] << std::endl;
//        }

void CShapeController::InitRectangle(const std::string &points, std::string colors) {
   auto arguments = ParseArguments(points);
   auto colorsParsed = ParseColors(colors);
   if (arguments.has_value()) {
       double x = arguments.value()[0];
       double y = arguments.value()[1];
       double width = arguments.value()[2];
       double height = arguments.value()[3];
       CPoint point(x, y);
       CRectangle rectangle(point, width, height, colorsParsed.value());
       m_rectangles.push_back(rectangle);
   }
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
    std::regex pattern(R"(([\d\.]+)\s([\d\.]+)\s([\d\.]+)\s([\d\.]+)\s)");
    std::vector<double> numbers;
    if (regex_match(arguments.c_str(), matched, pattern))
    {
        for (int i = 1; i < matched.size(); ++i) {
            std::stringstream ss(matched[i]);
            double side;
            ss >> side;

            if (!ss.eof()) {
                std::cout << NOT_NUMBER;
                return std::nullopt;
            }

            numbers.push_back(side);
        }
    }
    return numbers;
}

std::optional<std::vector<std::string>> CShapeController::ParseColors(const std::string &line) {
    // можно улучшить регуляркой
    std::vector<std::string> colors;
    std::string delimiter = " ";
    std::string firstColor = line.substr(0, line.find(delimiter));
    std::string secondColor = line.substr(line.find(delimiter));
    colors.push_back(firstColor);
    colors.push_back(secondColor);
    return colors;
}
