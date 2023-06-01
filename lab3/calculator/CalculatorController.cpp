#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <limits>
#include <cmath>
#include <iomanip>
#include "CalculatorController.h"

CalculatorController::CalculatorController() = default;

std::optional<Command> CalculatorController::GetCommand(const std::string& commandLine)
{
    if (commands.find(commandLine) != commands.end())
    {
        return commands.at(commandLine);
    }
    return std::nullopt;
}

std::optional<Operator> CalculatorController::GetOperator(char symbol)
{
    if (operators.find(symbol) != operators.end())
    {
        return operators.at(symbol);
    }
    return std::nullopt;
}

bool CalculatorController::CheckBusyIdentifier(const std::string &identifier) {
    return getValue(identifier) != std::numeric_limits<double>::quiet_NaN();
}

bool CalculatorController::CheckNameIdentifier(const std::string &identifier) {
    return isdigit(identifier[0]);
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
    ExpressionElements elements = {std::nullopt, std::nullopt, std::nullopt};

    for (char symbol : line)
    {
        if (symbol == ' ')
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

    switch (elements.command.value()) {
        case Command::VAR:
            InitVariable(elements.identifier.value());
            break;
        case Command::PRINT:
            Print(elements.identifier.value());
            break;
        case Command::LET:
            AssignValue(elements.identifier.value(), elements.value.value());
            break;
        case Command::PRINT_VARS:
            PrintVars();
            break;
        case Command::PRINT_FNS:
            PrintFns();
            break;
        case Command::FN:
            InitFunction(elements.identifier.value(), elements.value.value());
            break;
        default:
            std::cout << COMMOND_NOT_FOUND;
    }
}

void CalculatorController::InitVariable(const std::string &identifier) {
    if (!CheckBusyIdentifier(identifier))
    {
        std::cout << FUNCTION_ALREADY_EXISTS;
        return;
    }

    if (CheckNameIdentifier(identifier))
    {
        std::cout << NAME_NOT_START_WITH_NUMBER;
        return;
    }

    AddVariables(identifier, std::numeric_limits<double>::quiet_NaN());
}

void CalculatorController::AddVariables(const std::string &identifier, double value) {
    m_variables[identifier] = value;
}

void CalculatorController::Print(const std::string &identifier) {
    double value = getValue(identifier);

    if (value != std::numeric_limits<double>::quiet_NaN())
    {
        std::cout << std::fixed << std::setprecision(2) << value << std::endl;
    } else {
        std::cout << VARIABLE_NOT_FOUND;
    }
}

void CalculatorController::AssignValue(const std::string &identifier, const std::string &value) {
    if (getValue(identifier) != std::numeric_limits<double>::quiet_NaN())
    {
        InitVariable(identifier);
    }

    std::stringstream stringAppeal(value);
    double valueVariables;

    stringAppeal >> valueVariables;
    if (stringAppeal.eof()) {
        AddVariables(identifier, valueVariables);
        return;
    }

    if (getValue(value) != std::numeric_limits<double>::quiet_NaN()) {
        AddVariables(identifier, getValue(value));
    }
}

void CalculatorController::InitFunction(const std::string &identifier, const std::string &value) {
    if (!CheckBusyIdentifier(identifier))
    {
        std::cout << FUNCTION_ALREADY_EXISTS;
        return;
    }

    if (CheckNameIdentifier(identifier))
    {
        std::cout << NAME_NOT_START_WITH_NUMBER;
        return;
    }

    std::string stringCommand;
    std::string firstArgument;
    std::string secondArgument;
    std::optional<Operator> functionOperator;

    for (char symbol : value)
    {
        if (GetOperator(symbol) && !functionOperator)
        {
            firstArgument = stringCommand;
            functionOperator = GetOperator(symbol);
            stringCommand = "";
            continue;
        }

        stringCommand.push_back(symbol);

    }

    if (stringCommand != "")
    {
        secondArgument = stringCommand;
    }

    if (!functionOperator.has_value())
    {
        AddFunction(identifier, new Function(
                m_calculator,
                std::nullopt,
                secondArgument,
                "",
                std::numeric_limits<double>::quiet_NaN()
        ));
    } else {
        AddFunction(identifier, new Function(
                m_calculator,
                functionOperator,
                firstArgument,
                secondArgument,
                std::numeric_limits<double>::quiet_NaN()
        ));
    }

}

void CalculatorController::PrintVars() {
    for(auto iter{m_variables.begin()}; iter != m_variables.end(); iter++)
    {
        std::cout << iter->first << ": " << std::fixed << std::setprecision(2) << iter->second << std::endl;
    }
}

double CalculatorController::getValue(const std::string &identifier) {
    if (m_variables.count(identifier)) {
        return m_variables[identifier];
    }

    if (m_functions.count(identifier)) {
        std::string firstArgument = m_functions[identifier]->m_firstArgument;
        std::string secondArgument = m_functions[identifier]->m_secondArgument;

        double firstValue = getValue(firstArgument);
        double secondValue = getValue(secondArgument);
        return m_functions[identifier]->getValue(firstValue, secondValue);
    }

    return std::numeric_limits<double>::quiet_NaN();
}

void CalculatorController::AddFunction(std::string identifier, Function* function) {
    m_functions[identifier] = function;
}

void CalculatorController::PrintFns() {
    for(auto iter{m_functions.begin()}; iter != m_functions.end(); iter++)
    {
        double firstArgument = getValue(iter->second->m_firstArgument);
        double secondArgument = getValue(iter->second->m_secondArgument);

        std::cout << iter->first << ": " << std::fixed << std::setprecision(2) << iter->second->getValue(firstArgument, secondArgument) << std::endl;
    }
}


