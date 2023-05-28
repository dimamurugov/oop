#pragma once
#include <string>
#include <optional>

enum class Operator
{
    ADDITION,
    SUBTRACTION,
    MULTIPLICATION,
    DIVISION
};

struct FunctionElements {
    std::string firstArgument;
    std::string secondArgument;
    std::optional<Operator> functionOperator;
    double value;
};

namespace {
    const std::map<char, Operator> operators = {
            { '+', Operator::ADDITION },
            { '-', Operator::DIVISION },
            { '*', Operator::MULTIPLICATION },
            { '/', Operator::SUBTRACTION },
    };
}