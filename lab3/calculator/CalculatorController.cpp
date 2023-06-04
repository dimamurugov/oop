#include <string>
#include <iostream>
#include <fstream>
#include <limits>
#include <iomanip>
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
    for (; getline(inputFile, line); )//while
    {
        LineExecution(line);
    }
}

void CalculatorController::LineExecution(const std::string &line) {
    std::string stringCommand;
    ExpressionElements elements = {std::nullopt, std::nullopt, std::nullopt};

    for (char symbol : line) // use regexp
    {
        if (symbol == DELIMITER)
        {
            elements.command = GetCommand(stringCommand);
            stringCommand = "";\
            continue;
        }

        if ((symbol == '=') && elements.command.has_value()) {
            elements.identifier = stringCommand;
            stringCommand = "";\
            continue;
        }

        stringCommand.push_back(symbol);
    }

    if (!elements.command.has_value()) {
        elements.command = GetCommand(stringCommand);
        stringCommand = "";
    }

    if (!elements.identifier.has_value() && !stringCommand.empty())
    {
        elements.identifier = stringCommand;
        stringCommand = "";
    }

    if (!elements.value.has_value() && !stringCommand.empty()) {
        elements.value = stringCommand;
    }

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
        default:
            std::cout << COMMAND_NOT_FOUND;// command
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


