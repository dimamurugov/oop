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

namespace {
    const std::map<char, Operator> operators = {
            { '+', Operator::ADDITION },
            { '-', Operator::SUBTRACTION },
            { '*', Operator::MULTIPLICATION },
            { '/', Operator::DIVISION },
    };
}