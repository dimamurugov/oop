#include <sstream>
#include <iostream>
#include "Calculator.h"

Calculator::Calculator() = default;
// логика должна лежать в калькуляторе (Функции, переменные)

void Calculator::InitVariable(const std::string &identifier) {
    //validation first
//    if (CheckNameIdentifier(identifier))//rename
//    {
//        std::cout << NAME_NOT_START_WITH_NUMBER;
//        return;
//    }

//    if (!CheckBusyIdentifier(identifier))
//    {
//        std::cout << FUNCTION_ALREADY_EXISTS;//rename
//        return;
//    }

    AddVariables(identifier, std::numeric_limits<double>::quiet_NaN());
}

void Calculator::AddVariables(const std::string &identifier, double value) {
//    if (CheckNameIdentifier(identifier))// снова вызывается
//    {
//        std::cout << NAME_NOT_START_WITH_NUMBER;
//        return;
//    }

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
    if (getValue(identifier) != std::numeric_limits<double>::quiet_NaN()) {
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

double Calculator::getValue(const std::string &identifier) {
    if (m_variables.count(identifier)) {
        return m_variables[identifier];
    }

    if (m_functions.count(identifier)) {
        std::string firstArgument = m_functions[identifier]->m_firstArgument;
        std::string secondArgument = m_functions[identifier]->m_secondArgument;

        double firstValue = getValue(firstArgument);
        double secondValue = getValue(secondArgument);
        m_functions[identifier]->value = CalculateExpression(firstValue, secondValue, m_functions[identifier]->functionOperator);
        return m_functions[identifier]->value;
    }
    return std::numeric_limits<double>::quiet_NaN();
}

std::map<std::string, double> Calculator::getVariables() {
    return m_variables;
}

void Calculator::InitFunction(const std::string &identifier, const std::string &value) {
    if (!ValidateIdentifier(identifier))
    {
        return;
    }

//    if (!CheckBusyIdentifier(identifier))
//    {
//        std::cout << FUNCTION_ALREADY_EXISTS;
//        return;
//    }

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

    if (firstArgument == identifier || secondArgument == identifier)
    {
        std::cout << NOT_RECURSIVE_FUNCTION;
        return;
    }

    if (!functionOperator.has_value())
    {
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

std::optional<Operator> Calculator::GetOperator(char symbol) {
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

std::map<std::string, double> Calculator::getFunctions() {
    std::map<std::string, double> calculatedFunction;
    for(auto iter{m_functions.begin()}; iter != m_functions.end(); iter++)
    {
        calculatedFunction[iter->first] = getValue(iter->first);
    }

    return calculatedFunction;
}

bool Calculator::ValidateIdentifier(const std::string &identifier) {
    if (isdigit(identifier[0]))
    {
        std::cout << NAME_NOT_START_WITH_NUMBER;
        return false;
    }

    return true;
}
