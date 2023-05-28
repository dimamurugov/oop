
#ifndef CALCULATOR_FUNCTION_H
#define CALCULATOR_FUNCTION_H

#include <string>
#include <optional>
#include <map>
#include "commonType.h"
#include "Calculator.h"

class Function
{
public:
    Function(
            Calculator calculator,
            std::optional<Operator> functionOperator,
            std::string firstArgument,
            std::string secondArgument,
            double value
    );
    double getValue(double firstArgument, double secondArgument);
    void CalculateExpression(double firstArgument, double secondArgument);
    const std::string& m_firstArgument;
    const std::string& m_secondArgument;
private:
    std::optional<Operator> m_functionOperator;
    Calculator m_calculator;
    double m_value;
};


#endif //CALCULATOR_FUNCTION_H
