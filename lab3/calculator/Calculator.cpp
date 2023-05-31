#include "Calculator.h"

Calculator::Calculator() = default;

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
