#ifndef CALCULATOR_CALCULATORCONTROLLER_H
#define CALCULATOR_CALCULATORCONTROLLER_H

#include <map>
#include <optional>
#include <functional>
#include "Calculator.h"

enum class Command
{
    VAR,
    PRINT,
    LET,
    PRINT_VARS,
    PRINT_FNS,
    FN,
};

struct ExpressionElements {
    std::optional<Command> command;
    std::optional<std::string> identifier;
    std::optional<std::string> value;
};

namespace {
    const std::map<std::string, Command> commands = {
            { "var", Command::VAR },
            { "print", Command::PRINT },
            { "let", Command::LET },
            { "printvars", Command::PRINT_VARS },
            { "printfns", Command::PRINT_FNS },
            { "fn", Command::FN },
    };
    const std::string FILE_NOT_FOUND = "File not found!\n";
    const std::string COMMAND_NOT_FOUND = "Command not found!\n";
    const std::string VARIABLE_NOT_FOUND = "Variable not found!\n";
    const char DELIMITER = ' ';
}

class CalculatorController
{
public:
    explicit CalculatorController(Calculator& calculator);
    static std::optional<Command> GetCommand(const std::string& line);
    void PrintVars();
    void PrintFns();
    void Print(const std::string& identifier);
    void ReadFile(const std::string &filePath);
    void LineExecution(const std::string &line);

private:
    Calculator m_calculator;
//    std::map<std::string, double> m_variables;
//    std::map<std::string, Function*> m_functions;
};


#endif //CALCULATOR_CALCULATORCONTROLLER_H
