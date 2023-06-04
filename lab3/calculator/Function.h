#ifndef CALCULATOR_FUNCTION_H
#define CALCULATOR_FUNCTION_H

#include <string>
#include <optional>
#include <map>
#include "commonType.h"

class Function
{
public:
    Function(
            std::optional<Operator> functionOperator,
            std::string firstArgument,
            std::string secondArgument,
            double value
    );
    void CalculateExpression(double firstArgument, double secondArgument);
    double getValue(double firstArgument, double secondArgument);
    const std::string m_firstArgument;
    const std::string m_secondArgument;
private:
    std::optional<Operator> m_functionOperator;
    double m_value;
};


#endif //CALCULATOR_FUNCTION_H
