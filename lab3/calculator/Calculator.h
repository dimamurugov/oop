#ifndef CALCULATOR_CALCULATOR_H
#define CALCULATOR_CALCULATOR_H
#include <limits>
#include <map>
#include <string>
#include <optional>

namespace {
    const std::string NAME_NOT_START_WITH_NUMBER = "The name must not start with a number!\n";
    const std::string NOT_RECURSIVE_FUNCTION = "Can't declare a recursive function!\n";
    const std::string IDENTIFICATOR_ALREADY_TAKEN = "Identifier already taken!\n";
}

enum class Operator
{
    ADDITION,
    SUBTRACTION,
    MULTIPLICATION,
    DIVISION
};

const std::map<char, Operator> operators = {
        { '+', Operator::ADDITION },
        { '-', Operator::SUBTRACTION },
        { '*', Operator::MULTIPLICATION },
        { '/', Operator::DIVISION },
};

struct function {
    std::string firstArgument;
    std::string secondArgument;
    std::optional<Operator> functionOperator;
    double value;
};
// Сделать констатные методы которые не изменяют состояние объекта
class Calculator
{
public:
    Calculator();
    static std::optional<Operator> GetOperator(char symbol);
    // публичные методы
    static double Addition(double firstOperator, double secondOperator);
    static double Subtraction(double firstOperator, double secondOperator);
    static double Multiplication(double firstOperator, double secondOperator);
    static double Division(double firstOperator, double secondOperator);
    void InitVariable(const std::string &identifier);
    void InitFunction(const std::string& identifier, const std::string &value);
    void AddVariables(const std::string &identifier, double value);
    void AssignValue(const std::string& identifier, const std::string &value);
    double GetValue(const std::string &identifier);
    // Лучше не делать функции которые принимают параметры в итоге которые могут не прийти
    static double CalculateExpression(double firstArgument, double secondArgument, std::optional<Operator> functionOperator);
    std::map<std::string, double> GetVariables();
    std::map<std::string, double> GetFunctions();
    static bool ValidateIdentifier(const std::string &identifier);
    // osExisintIdentifier
    bool CheckBusyIdentifier(const std::string &identifier);
private:
    std::map<std::string, double> m_variables;
    std::map<std::string, function*> m_functions;
};

#endif //CALCULATOR_CALCULATOR_H
