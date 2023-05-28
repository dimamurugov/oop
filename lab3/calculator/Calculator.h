#ifndef CALCULATOR_CALCULATOR_H
#define CALCULATOR_CALCULATOR_H
#include <limits>

class Calculator
{
public:
    Calculator();
    static double Addition(double firstOperator, double secondOperator);
    static double Subtraction(double firstOperator, double secondOperator);
    static double Multiplication(double firstOperator, double secondOperator);
    static double Division(double firstOperator, double secondOperator);
};


#endif //CALCULATOR_CALCULATOR_H
