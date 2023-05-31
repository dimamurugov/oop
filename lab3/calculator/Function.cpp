#include <iostream>
#include "Function.h"

Function::Function(
        Calculator calculator,
        std::optional<Operator> functionOperator,
        std::string firstArgument,
        std::string secondArgument,
        double value)
    : m_calculator(calculator),
    m_functionOperator(functionOperator),
    m_firstArgument(firstArgument),
    m_secondArgument(secondArgument),
    m_value(value)
{}

void Function::CalculateExpression(double firstArgument, double secondArgument) {
    std::cout << firstArgument << std::endl;
    if (m_functionOperator.has_value())
    {
        std::cout << secondArgument << std::endl;
        switch (m_functionOperator.value()) {
            case Operator::ADDITION:
                std::cout << "test: " << Calculator::Addition(firstArgument, secondArgument) << std::endl;
                m_value = Calculator::Addition(firstArgument, secondArgument);
                break;
            case Operator::SUBTRACTION:
                m_value = Calculator::Subtraction(firstArgument, secondArgument);
                break;
            case Operator::DIVISION:
                m_value = Calculator::Division(firstArgument, secondArgument);
                break;
            case Operator::MULTIPLICATION:
                m_value = Calculator::Multiplication(firstArgument, secondArgument);
                break;
        }
    } else
    {
        m_value = firstArgument;
    }
}

double Function::getValue(double firstArgument, double secondArgument) {
    Function::CalculateExpression(firstArgument, secondArgument);
    return m_value;
}

