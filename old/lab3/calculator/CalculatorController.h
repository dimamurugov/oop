#ifndef CALCULATOR_CALCULATORCONTROLLER_H
#define CALCULATOR_CALCULATORCONTROLLER_H

#include <map>
#include <optional>
#include "Calculator.h"

enum class Command
{
    VAR,
    PRINT,
    LET,
};

struct FunctionElements {
    std::optional<Command> command;
    std::optional<std::string> identifier;
    std::optional<std::string> value;
};

namespace {
    const std::map<std::string, Command> commands = {
            { "var", Command::VAR },
            { "print", Command::PRINT },
            { "let", Command::LET },
    };
    const std::string FILE_NOT_FOUND = "File not found!\n";
}

class CalculatorController
{
private:
    static Calculator m_calculator;
public:
    explicit CalculatorController(const Calculator &calculator);
    static void ReadFile(const std::string &filePath);
    static bool GetCommand(const std::string& line, Command& command);
    static void LineExecution(const std::string &line);
};


#endif //CALCULATOR_CALCULATORCONTROLLER_H
