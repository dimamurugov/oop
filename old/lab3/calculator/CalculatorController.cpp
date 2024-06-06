#include <string>
#include <iostream>
#include <fstream>
#include "CalculatorController.h"

CalculatorController::CalculatorController(const Calculator& calculator)
{
    m_calculator = calculator;
}

bool CalculatorController::GetCommand(const std::string& commandLine, Command& command)
{
    if (commands.find(commandLine) != commands.end())
    {
        command = commands.at(commandLine);
        return true;
    }
    return false;
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
    for (int lineIndex = 1; getline(inputFile, line); ++lineIndex)
    {
        LineExecution(line);
    }
}

void CalculatorController::LineExecution(const std::string &line) {
    std::string stringCommand;
    Command command;
    FunctionElements elements = {std::nullopt, std::nullopt, std::nullopt};

    for (char symbol : line)
    {
        if (symbol == ' ' && GetCommand(stringCommand, command) && !elements.command.has_value())
        {
            elements.command = command;
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

    if (!elements.identifier.has_value())
    {
        elements.identifier = stringCommand;
    } else if (!elements.value.has_value()) {
        elements.value = stringCommand;
    }
    std::cout << "===";
}
