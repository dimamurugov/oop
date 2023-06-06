#include <regex>
#include <iostream>
#include "CShapeController.h"

void CShapeController::LineExecution(const std::string &line) {
    std::string stringCommand;
    std::cmatch matched;
    std::regex regex("^(rectangle|triangle|circle)(\\s)((([0-9]*(\\.[0-9]+)?)(\\s)){1,4})(((\\w{6})(\\s?)){1,2})$");
    std::string line2 = "rectangle 10.3 20.15 30.7 40.4 ff0000 00ff00";
    if (regex_match(line2.c_str(), matched, regex))
    {
        for (int i = 0; i < matched.size(); ++i) {
            std::cout << i << ' ' << matched[i] << std::endl;
        }
    }
}
