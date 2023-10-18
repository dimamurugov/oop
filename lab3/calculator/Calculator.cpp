#include <sstream>
#include <iostream>
#include "Calculator.h"

Calculator::Calculator() = default;

void Calculator::InitVariable(const std::string &identifier) {
    if (!ValidateIdentifier(identifier))
    {
        std::cout << NAME_NOT_START_WITH_NUMBER;
        return;
    }

    if (!CheckBusyIdentifier(identifier))
    {
        std::cout << IDENTIFICATOR_ALREADY_TAKEN;
        return;
    }
    AddVariables(identifier, std::numeric_limits<double>::quiet_NaN());
}

void Calculator::AddVariables(const std::string &identifier, double value) {
    m_variables[identifier] = value;
}

double Calculator::Addition(double firstOperator, double secondOperator) {
    return firstOperator + secondOperator;
}

double Calculator::Subtraction(double firstOperator, double secondOperator) {
    return firstOperator - secondOperator;
}

double Calculator::Division(double firstOperator, double secondOperator) {
    if (secondOperator != 0) {
        return firstOperator / secondOperator;
    }

    return std::numeric_limits<double>::quiet_NaN();
}

double Calculator::Multiplication(double firstOperator, double secondOperator) {
    return firstOperator * secondOperator;
}

void Calculator::AssignValue(const std::string &identifier, const std::string &value) {
    if (CheckBusyIdentifier(identifier)) {
        InitVariable(identifier);
    }

    std::stringstream stringAppeal(value);
    double valueVariables;

    stringAppeal >> valueVariables;
    if (stringAppeal.eof()) {
        AddVariables(identifier, valueVariables);
        return;
    }

    if (GetValue(value) != std::numeric_limits<double>::quiet_NaN()) {
        AddVariables(identifier, GetValue(value));
    }
}

double Calculator::GetValue(const std::string &identifier) {
    // использовать итератор если необходимо несколько раз обратися к одному элементу
    if (m_variables.count(identifier)) {
        return m_variables[identifier];
    }

    if (m_functions.count(identifier)) {
        std::string firstArgument = m_functions[identifier]->firstArgument;
        std::string secondArgument = m_functions[identifier]->secondArgument;

        double firstValue = GetValue(firstArgument);
        double secondValue = GetValue(secondArgument);
        m_functions[identifier]->value = CalculateExpression(firstValue, secondValue, m_functions[identifier]->functionOperator);
        return m_functions[identifier]->value;
    }
    return std::numeric_limits<double>::quiet_NaN();
}

std::map<std::string, double> Calculator::GetVariables() {
    return m_variables;
}
// парсинг строк не должен быть в калькуляторе
void Calculator::InitFunction(const std::string &identifier, const std::string &value) {
    // если объявить функцию с символ(-) показывается сообщение о рекурсивности
    if (!ValidateIdentifier(identifier))
    {
        std::cout << NAME_NOT_START_WITH_NUMBER;
        return;
    }

    if (!CheckBusyIdentifier(identifier))
    {
        std::cout << IDENTIFICATOR_ALREADY_TAKEN;
        return;
    }
    // упростить
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
    if (!stringCommand.empty())
    {
        secondArgument = stringCommand;
    }

    if (firstArgument == identifier || secondArgument == identifier)
    {
        std::cout << NOT_RECURSIVE_FUNCTION;
        return;
    }

    if (!functionOperator.has_value())
    {
        // в этом задании не нужно использовать new и delete
        m_functions[identifier] = new function {
            "",
            secondArgument,
            std::nullopt,
            std::numeric_limits<double>::quiet_NaN()
        };
    } else {
        m_functions[identifier] = new function {
            firstArgument,
            secondArgument,
            functionOperator,
            std::numeric_limits<double>::quiet_NaN()
        };
    }

}
// 0.6
std::optional<Operator> Calculator::GetOperator(char symbol) {
    // возвращать итератор
    if (operators.find(symbol) != operators.end())
    {
        return operators.at(symbol);
    }
    return std::nullopt;
}

double Calculator::CalculateExpression(double firstArgument, double secondArgument, std::optional<Operator> functionOperator) {
    if (functionOperator.has_value())
    {
        switch (functionOperator.value()) {
            case Operator::ADDITION:
                return Calculator::Addition(firstArgument, secondArgument);
            case Operator::SUBTRACTION:
                return Calculator::Subtraction(firstArgument, secondArgument);
            case Operator::DIVISION:
                return Calculator::Division(firstArgument, secondArgument);
            case Operator::MULTIPLICATION:
                return Calculator::Multiplication(firstArgument, secondArgument);
        }
    }

    return secondArgument;
}

std::map<std::string, double> Calculator::GetFunctions() {
    std::map<std::string, double> calculatedFunction;
    for(auto iter{m_functions.begin()}; iter != m_functions.end(); iter++)
    {
        calculatedFunction[iter->first] = GetValue(iter->first);
    }

    return calculatedFunction;
}

bool Calculator::ValidateIdentifier(const std::string &identifier) {
    // если пустая строка
    return !isdigit(identifier[0]);
}

bool Calculator::CheckBusyIdentifier(const std::string &identifier) {
    return !(m_variables.count(identifier) | m_functions.count(identifier));
}
