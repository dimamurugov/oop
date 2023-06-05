#include <string>
#include <iostream>
#include <fstream>
#include <limits>
#include <iomanip>
#include <regex>
#include "CalculatorController.h"

CalculatorController::CalculatorController(Calculator &calculator) : m_calculator(calculator) {};

std::optional<Command> CalculatorController::GetCommand(const std::string& commandLine)
{
    if (commands.find(commandLine) != commands.end())
    {
        return commands.at(commandLine);
    }
    return std::nullopt;
}

void CalculatorController::ReadFile(const std::string &filePath) {
    std::ifstream inputFile(filePath);
    if (!inputFile.is_open())
    {
        std::cout << FILE_NOT_FOUND;
        inputFile.close();
        return;
    }

    std::string line;
    while (getline(inputFile, line)) {
        LineExecution(line);
    }
}

void CalculatorController::LineExecution(const std::string &line) {
    std::string stringCommand;
    ExpressionElements elements = {std::nullopt, std::nullopt, std::nullopt};
    std::cmatch matched;
    std::regex regex("(printvars|printfns|var|print|let|fn)($|\\s)(\\w*)(=?)(.*)");

    if (regex_match(line.c_str(), matched, regex))
    {
        elements.command = GetCommand(matched[1]);
        elements.identifier = matched[3];
        elements.value = matched[5];

        switch (elements.command.value()) { // push to map and iterate map
            case Command::VAR:
                m_calculator.InitVariable(elements.identifier.value());
                break;
            case Command::PRINT:
                Print(elements.identifier.value());
                break;
            case Command::LET:
                m_calculator.AssignValue(elements.identifier.value(), elements.value.value());
                break;
            case Command::PRINT_VARS:
                PrintVars();
                break;
            case Command::PRINT_FNS:
                PrintFns();
                break;
            case Command::FN:
                m_calculator.InitFunction(elements.identifier.value(), elements.value.value());
                break;
        }
    } else {
        std::cout << COMMAND_NOT_FOUND;
        return;
    }
}

void CalculatorController::Print(const std::string &identifier) {
    double value = m_calculator.getValue(identifier);
    if (value != std::numeric_limits<double>::quiet_NaN())
    {
        std::cout << std::fixed << std::setprecision(2) << value << std::endl;
    } else {
        std::cout << VARIABLE_NOT_FOUND;
    }
}

void CalculatorController::PrintVars() {
    auto variables = m_calculator.getVariables();
    for(auto iter{variables.begin()}; iter != variables.end(); iter++)
    {
        std::cout << iter->first << ": " << std::fixed << std::setprecision(2) << iter->second << std::endl;
    }
}

void CalculatorController::PrintFns() {
    auto functions = m_calculator.getFunctions();
    for(auto iter{functions.begin()}; iter != functions.end(); iter++)
    {
        std::cout << iter->first << ": " << std::fixed << std::setprecision(2) << iter->second << std::endl;
    }
}


