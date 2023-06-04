#ifndef CALCULATOR_CALCULATOR_H
#define CALCULATOR_CALCULATOR_H
#include <limits>
#include <map>
#include <string>
#include "commonType.h"

namespace {
    const std::string NAME_NOT_START_WITH_NUMBER = "The name must not start with a number!\n";
    const std::string NOT_RECURSIVE_FUNCTION = "Can't declare a recursive function!\n";
}

struct function {
    std::string m_firstArgument;
    std::string m_secondArgument;
    std::optional<Operator> functionOperator;
    double value;
};

class Calculator
{
public:
    Calculator();
    static std::optional<Operator> GetOperator(char symbol);
    static double Addition(double firstOperator, double secondOperator);
    static double Subtraction(double firstOperator, double secondOperator);
    static double Multiplication(double firstOperator, double secondOperator);
    static double Division(double firstOperator, double secondOperator);
    void InitVariable(const std::string &identifier);
    void InitFunction(const std::string& identifier, const std::string &value);
    void AddVariables(const std::string &identifier, double value);
    void AssignValue(const std::string& identifier, const std::string &value);
    double getValue(const std::string &identifier);
    double CalculateExpression(double firstArgument, double secondArgument, std::optional<Operator> functionOperator);
    std::map<std::string, double> getVariables();
    std::map<std::string, double> getFunctions();
    bool ValidateIdentifier(const std::string &identifier);
private:
    std::map<std::string, double> m_variables;
    std::map<std::string, function*> m_functions;
};

#endif //CALCULATOR_CALCULATOR_H
// может быть print у calculator и у Controller