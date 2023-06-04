#define CATCH_CONFIG_MAIN
#include "../../../../../catch2/catch.hpp"

#include "../commonType.h"
#include "../Calculator.h"
#include "../Function.h"
#include "../Function.cpp"
#include "../CalculatorController.h"
#include "../CalculatorController.cpp"

TEST_CASE("Testing class Calculator")
{
//    std::cout << "Function: Addition" << std::endl;
    SECTION("This addition")
    {
        Calculator calculator;
        REQUIRE(calculator.Addition(1,1) == 2);
    }

//    std::cout << "Function: Subtraction" << std::endl;
    SECTION("This Subtraction")
    {
        Calculator calculator;
        REQUIRE(calculator.Subtraction(2,1) == 1);
    }

//    std::cout << "Function: Division" << std::endl;
    SECTION("This Division")
    {
        Calculator calculator;
        REQUIRE(calculator.Division(4,2) == 2);
    }

//    std::cout << "Function: Division" << std::endl;
    SECTION("Division on zero")
    {
        Calculator calculator;
        double result = calculator.Division(4,0);
        REQUIRE(result != result);
    }

//    std::cout << "Function: Multiplication" << std::endl;
    SECTION("This Multiplication")
    {
        Calculator calculator;
        REQUIRE(calculator.Multiplication(4,2) == 8);
    }
}

TEST_CASE("Testing class Function")
{
//    std::cout << "init Function" << std::endl;
    SECTION("Init")
    {
        Calculator calculator;
        auto addition = static_cast<Operator>('+');
        Function function(
                calculator,
                addition,
                "first secondArgument",
                "second firstArgument",
                std::numeric_limits<double>::quiet_NaN()
        );
        REQUIRE(function.m_firstArgument == "first secondArgument");
        REQUIRE(function.m_secondArgument == "second firstArgument");
    }

//    std::cout << "Function: getValue" << std::endl;
    SECTION("getValue")
    {
        Calculator calculator;
        double value = 1;
        Function function(
                calculator,
                std::nullopt,
                "first secondArgument",
                "second firstArgument",
                value
        );

        double firstArg = 1;
        double secondArg = 1;
        REQUIRE(function.getValue(firstArg, secondArg) == 1);
    }

    std::cout << "Function: CalculateExpression Addition" << std::endl;
    SECTION("CalculateExpression")
    {
        Calculator calculator;
        double value = 1;
        std::optional<Operator> functionOperator = operators.at('+');
        Function function(
                calculator,
                functionOperator,
                "firstArgument",
                "secondArgument",
                value
        );

        double result = 4;
        double firstArg = 2;
        double secondArg = 2;
        function.CalculateExpression(firstArg, secondArg);
        REQUIRE(function.getValue(firstArg, secondArg) == result);
    }

    std::cout << "Function: CalculateExpression Subtraction" << std::endl;
    SECTION("CalculateExpression")
    {
        Calculator calculator;
        std::optional<Operator> functionOperator = operators.at('-');
        Function function(
                calculator,
                functionOperator,
                "first secondArgument",
                "second firstArgument",
                std::numeric_limits<double>::quiet_NaN()
        );

        double firstArg = 6;
        double secondArg = 2;
        double result = 4;
        function.CalculateExpression(firstArg, secondArg);
        REQUIRE(function.getValue(firstArg, secondArg) == result);
    }

    std::cout << "Function: CalculateExpression DIVISION" << std::endl;
    SECTION("CalculateExpression")
    {
        Calculator calculator;
        std::optional<Operator> functionOperator = operators.at('/');
        Function function(
                calculator,
                functionOperator,
                "first secondArgument",
                "second firstArgument",
                std::numeric_limits<double>::quiet_NaN()
        );

        double firstArg = 6;
        double secondArg = 2;
        double result = 3;
        function.CalculateExpression(firstArg, secondArg);
        REQUIRE(function.getValue(firstArg, secondArg) == result);
    }

    std::cout << "Function: CalculateExpression MULTIPLICATION" << std::endl;
    SECTION("CalculateExpression")
    {
        Calculator calculator;
        std::optional<Operator> functionOperator = operators.at('*');
        Function function(
                calculator,
                functionOperator,
                "first secondArgument",
                "second firstArgument",
                std::numeric_limits<double>::quiet_NaN()
        );

        double firstArg = 6;
        double secondArg = 2;
        double result = 12;
        function.CalculateExpression(firstArg, secondArg);
        REQUIRE(function.getValue(firstArg, secondArg) == result);
    }
}

TEST_CASE("Testing class CalculatorController")
{
    std::cout << "Function: GetCommand" << std::endl;
    SECTION("GetCommand")
    {
        CalculatorController calculatorController;
        REQUIRE(calculatorController.GetCommand("var") == commands.at("var"));
    }

    std::cout << "Function: GetCommand" << std::endl;
    SECTION("GetCommand")
    {
        CalculatorController calculatorController;
        REQUIRE(calculatorController.GetCommand("print") == commands.at("print"));
    }

    std::cout << "Function: GetCommand" << std::endl;
    SECTION("GetCommand")
    {
        CalculatorController calculatorController;
        REQUIRE(calculatorController.GetCommand("let") == commands.at("let"));
    }

    std::cout << "Function: GetCommand" << std::endl;
    SECTION("GetCommand")
    {
        CalculatorController calculatorController;
        REQUIRE(calculatorController.GetCommand("printvars") == commands.at("printvars"));
    }

    std::cout << "Function: GetCommand" << std::endl;
    SECTION("GetCommand")
    {
        CalculatorController calculatorController;
        REQUIRE(calculatorController.GetCommand("printfns") == commands.at("printfns"));
    }

    std::cout << "Function: GetCommand" << std::endl;
    SECTION("GetCommand")
    {
        CalculatorController calculatorController;
        REQUIRE(calculatorController.GetCommand("fn") == commands.at("fn"));
    }

    std::cout << "Function: GetCommand without command" << std::endl;
    SECTION("GetCommand")
    {
        CalculatorController calculatorController;
        REQUIRE(calculatorController.GetCommand("Diman") == std::nullopt);
    }

    std::cout << "Function: GetOperator" << std::endl;
    SECTION("GetOperator")
    {
        CalculatorController calculatorController;
        REQUIRE(calculatorController.GetOperator('+') == operators.at('+'));
    }

    std::cout << "Function: GetOperator" << std::endl;
    SECTION("GetOperator")
    {
        CalculatorController calculatorController;
        REQUIRE(calculatorController.GetOperator('-') == operators.at('-'));
    }

    std::cout << "Function: GetOperator" << std::endl;
    SECTION("GetOperator")
    {
        CalculatorController calculatorController;
        REQUIRE(calculatorController.GetOperator('*') == operators.at('*'));
    }

    std::cout << "Function: GetOperator" << std::endl;
    SECTION("GetOperator")
    {
        CalculatorController calculatorController;
        REQUIRE(calculatorController.GetOperator('/') == operators.at('/'));
    }

    std::cout << "Function: GetOperator" << std::endl;
    SECTION("GetOperator")
    {
        CalculatorController calculatorController;
        REQUIRE(calculatorController.GetOperator('D') == std::nullopt);
    }

    std::cout << "Function: getValue " << std::endl;
    SECTION("getValue")
    {
        CalculatorController calculatorController;
        double value = 10;
        calculatorController.AddVariables("test_1", value);
        double result = 10;
        REQUIRE(calculatorController.getValue("test_1") == result);
    }

    std::cout << "Function: getValue from function" << std::endl;
    SECTION("getValue")
    {
        CalculatorController calculatorController;
        double value = 10;
        calculatorController.AddVariables("x", value);
        calculatorController.AddVariables("y", value);
        calculatorController.InitFunction("XplusY", "x+y");
        double result = 20;
        REQUIRE(calculatorController.getValue("XplusY") == result);
        double result2 = calculatorController.getValue("XplusssY");
        REQUIRE(result != result2);
    }

    std::cout << "Function: AssignValue with var" << std::endl;
    SECTION("AssignValue")
    {
        CalculatorController calculatorController;
        double value = 10;
        double value2 = 20;
        calculatorController.AddVariables("x", value);
        calculatorController.AddVariables("y", value2);
        calculatorController.AssignValue("x", "y");
        double result = 20;
        REQUIRE(calculatorController.getValue("y") == result);
    }

    std::cout << "Function: AssignValue without var" << std::endl;
    SECTION("AssignValue")
    {
        CalculatorController calculatorController;
        calculatorController.AssignValue("x", "20");
        double result = 20;
        REQUIRE(calculatorController.getValue("x") == result);
    }

    std::cout << "Function: InitFunction" << std::endl;
    SECTION("InitFunction")
    {
        CalculatorController calculatorController;
        double value = 10;
        double value2 = 20;
        calculatorController.AddVariables("x", value);
        calculatorController.AddVariables("y", value2);
        calculatorController.InitFunction("XPlusY", "x+y");
        double result = 30;
        REQUIRE(calculatorController.getValue("XPlusY") == result);
    }

    std::cout << "Function: InitFunction " << std::endl;
    SECTION("InitFunction")
    {
        CalculatorController calculatorController;
        double value = 10;
        calculatorController.AddVariables("x", value);
        calculatorController.InitFunction("XPlusY", "x");
        double result = 10;
        REQUIRE(calculatorController.getValue("XPlusY") == result);
    }
}