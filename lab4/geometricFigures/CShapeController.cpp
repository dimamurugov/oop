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
    std::cmatch matched;
    std::regex pattern(R"(([\d\.]+)\s([\d\.]+)\s([\d\.]+)\s([\d\.]+)\s)"); // ([\d\.]+)\s([\d\.]+)\s([\d\.]+)\s([\d\.]+)
    if (regex_match(points.c_str(), matched, pattern))
    {

    }
}

std::optional<ShapesType> CShapeController::GetShapeType(const std::string &str) {
    if (shapes.find(str) != shapes.end())
    {
        return shapes.at(str);
    }
    return std::nullopt;
}
