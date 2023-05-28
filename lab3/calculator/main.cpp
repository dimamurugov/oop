#include <iostream>
#include <optional>
#include "Calculator.h"
#include "CalculatorController.h"
#include "Storage.h"

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
    if (!filePath.has_value())
    {
        return EXIT_FAILURE;
    }
    Calculator calculator;
    CalculatorController calculatorController;
    calculatorController.ReadFile(filePath.value());

    return EXIT_SUCCESS;
}
