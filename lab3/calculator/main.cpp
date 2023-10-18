#include <iostream>
#include <optional>
#include <iterator>
#include "Calculator.h"
#include "CalculatorController.h"

std::optional<std::string> ParseCommandLine(int argc, char* argv[])
{
    if (argc < 2) {
        return std::nullopt;
    }

    if (argv[2] == "") {
        std::cout << "2 argument must not be empty!" << std::endl;
        return std::nullopt;
    }

    return argv[1];
}

int main(int argc, char* argv[]) {
    const std::optional<std::string> filePath = ParseCommandLine(argc, argv);
    Calculator calculator;
    CalculatorController calculatorController(calculator);

    if (!filePath.has_value())
    {
        std::string str;
        while (getline(std::cin, str))
        {
            calculatorController.LineExecution(str);
        }
    } else {
        calculatorController.ReadFile(filePath.value());
    }

    return EXIT_SUCCESS;
}
