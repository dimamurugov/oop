#define CATCH_CONFIG_MAIN
#include "../../../../../catch2/catch.hpp"

#include "../Calculator.h"
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

    std::cout << "Function: GetOperator" << std::endl;
    SECTION("GetOperator")
    {
        Calculator calculator;
        REQUIRE(calculator.GetOperator('+') == operators.at('+'));
    }

    std::cout << "Function: GetOperator" << std::endl;
    SECTION("GetOperator")
    {
        Calculator calculator;
        REQUIRE(calculator.GetOperator('-') == operators.at('-'));
    }

    std::cout << "Function: GetOperator" << std::endl;
    SECTION("GetOperator")
    {
        Calculator calculator;
        REQUIRE(calculator.GetOperator('*') == operators.at('*'));
    }

    std::cout << "Function: GetOperator" << std::endl;
    SECTION("GetOperator")
    {
        Calculator calculator;
        REQUIRE(calculator.GetOperator('/') == operators.at('/'));
    }

    std::cout << "Function: GetOperator" << std::endl;
    SECTION("GetOperator")
    {
        Calculator calculator;
        REQUIRE(calculator.GetOperator('D') == std::nullopt);
    }

    std::cout << "Function: AssignValue with var" << std::endl;
    SECTION("AssignValue")
    {
        Calculator calculator;
        double value = 10;
        double value2 = 20;
        calculator.AddVariables("x", value);
        calculator.AddVariables("y", value2);
        calculator.AssignValue("x", "y");
        double result = 20;
        REQUIRE(calculator.GetValue("y") == result);
    }

    std::cout << "Function: AssignValue without var" << std::endl;
    SECTION("AssignValue")
    {
        Calculator calculator;
        calculator.AssignValue("x", "20");
        double result = 20;
        REQUIRE(calculator.GetValue("x") == result);
    }

    std::cout << "Function: GetValue" << std::endl;
    SECTION("getValue")
    {
        Calculator calculator;
        double value = 10;
        calculator.AddVariables("test_1", value);
        double result = 10;
        REQUIRE(calculator.GetValue("test_1") == result);
    }

    std::cout << "Function: InitFunction" << std::endl;
    SECTION("InitFunction")
    {
        Calculator calculator;
        double value = 10;
        double value2 = 20;
        calculator.AddVariables("x", value);
        calculator.AddVariables("y", value2);
        calculator.InitFunction("XPlusY", "x+y");
        double result = 30;
        REQUIRE(calculator.GetValue("XPlusY") == result);
    }

    std::cout << "Function: InitFunction with wrong name" << std::endl;
    SECTION("InitFunction")
    {
        Calculator calculator;
        double value = 10;
        double value2 = 20;
        calculator.AddVariables("x", value);
        calculator.AddVariables("y", value2);
        calculator.InitFunction("2XPlusY", "x+y");
        double result = calculator.GetValue("XPlusY");
        REQUIRE(result != result);
    }

    std::cout << "Function: InitFunction with busy name" << std::endl;
    SECTION("InitFunction")
    {
        Calculator calculator;
        double value = 10;
        double value2 = 20;
        calculator.AddVariables("x", value);
        calculator.AddVariables("y", value2);
        calculator.InitFunction("XPlusY", "x+y");
        calculator.InitFunction("XPlusY", "x-y");
        double result = 10;
        REQUIRE(calculator.GetValue("XPlusY") != result);
    }

    std::cout << "Function: InitFunction with busy name" << std::endl;
    SECTION("InitFunction")
    {
        Calculator calculator;
        double value = 10;
        double value2 = 20;
        calculator.AddVariables("x", value);
        calculator.AddVariables("y", value2);
        calculator.InitFunction("XPlusY", "x+XPlusY");
        double result = calculator.GetValue("XPlusY");
        REQUIRE(result != result);
    }

    std::cout << "Function: InitFunction with busy name" << std::endl;
    SECTION("InitFunction")
    {
        Calculator calculator;
        double value = 10;
        calculator.AddVariables("x", value);
        calculator.InitFunction("XPlusY", "x");
        double result = 10;
        REQUIRE(calculator.GetValue("XPlusY") == result);
    }

    std::cout << "Function: InitVariable" << std::endl;
    SECTION("InitVariable")
    {
        Calculator calculator;
        calculator.InitVariable("x");
        double result = calculator.GetValue("x");
        REQUIRE(result != result);
    }

    std::cout << "Function: InitVariable with wrong name" << std::endl;
    SECTION("InitVariable")
    {
        Calculator calculator;
        calculator.InitVariable("x");
        calculator.InitVariable("2");
        double result = calculator.GetValue("2");
        REQUIRE(result != result);
    }

    std::cout << "Function: CalculateExpression" << std::endl;
    SECTION("CalculateExpression")
    {
        Calculator calculator;
        double first = 10;
        double second = 20;
        double value = calculator.CalculateExpression(first, second, std::nullopt);
        double result = 20;
        REQUIRE(value == result);
    }

    std::cout << "Function: CalculateExpression +" << std::endl;
    SECTION("CalculateExpression")
    {
        Calculator calculator;
        double first = 10;
        double second = 20;
        std::optional<Operator> op = calculator.GetOperator('+');
        double value = calculator.CalculateExpression(first, second, op.value());
        double result = 30;
        REQUIRE(value == result);
    }

    std::cout << "Function: CalculateExpression -" << std::endl;
    SECTION("CalculateExpression")
    {
        Calculator calculator;
        double first = 20;
        double second = 10;
        std::optional<Operator> op = calculator.GetOperator('-');
        double value = calculator.CalculateExpression(first, second, op.value());
        double result = 10;
        REQUIRE(value == result);
    }

    std::cout << "Function: CalculateExpression *" << std::endl;
    SECTION("CalculateExpression")
    {
        Calculator calculator;
        double first = 2;
        double second = 2;
        std::optional<Operator> op = calculator.GetOperator('*');
        double value = calculator.CalculateExpression(first, second, op.value());
        double result = 4;
        REQUIRE(value == result);
    }

    std::cout << "Function: CalculateExpression /" << std::endl;
    SECTION("CalculateExpression")
    {
        Calculator calculator;
        double first = 4;
        double second = 2;
        std::optional<Operator> op = calculator.GetOperator('/');
        double value = calculator.CalculateExpression(first, second, op.value());
        double result = 2;
        REQUIRE(value == result);
    }

    std::cout << "Function: GetVariables" << std::endl;
    SECTION("GetVariables")
    {
        Calculator calculator;
        calculator.AddVariables("x", 10);
        std::map<std::string, double> result;
        result["x"] = 10;
        REQUIRE(calculator.GetVariables() == result);
    }
}

TEST_CASE("Testing class CalculatorController")
{
    std::cout << "Function: GetCommand var" << std::endl;
    SECTION("GetVariables")
    {
        Calculator calculator;
        CalculatorController calculatorController(calculator);
        REQUIRE(calculatorController.GetCommand("var") != std::nullopt);
    }

    std::cout << "Function: GetCommand let" << std::endl;
    SECTION("GetVariables")
    {
        Calculator calculator;
        CalculatorController calculatorController(calculator);
        REQUIRE(calculatorController.GetCommand("let") != std::nullopt);
    }

    std::cout << "Function: GetCommand fn" << std::endl;
    SECTION("GetVariables")
    {
        Calculator calculator;
        CalculatorController calculatorController(calculator);
        REQUIRE(calculatorController.GetCommand("fn") != std::nullopt);
    }

    std::cout << "Function: GetCommand print" << std::endl;
    SECTION("GetVariables")
    {
        Calculator calculator;
        CalculatorController calculatorController(calculator);
        REQUIRE(calculatorController.GetCommand("print") != std::nullopt);
    }

    std::cout << "Function: GetCommand printvars" << std::endl;
    SECTION("GetVariables")
    {
        Calculator calculator;
        CalculatorController calculatorController(calculator);
        REQUIRE(calculatorController.GetCommand("printvars") != std::nullopt);
    }

    std::cout << "Function: GetCommand printfns" << std::endl;
    SECTION("GetVariables")
    {
        Calculator calculator;
        CalculatorController calculatorController(calculator);
        REQUIRE(calculatorController.GetCommand("printfns") != std::nullopt);
    }
//
//    std::cout << "Function: CalculateExpression Subtraction" << std::endl;
//    SECTION("CalculateExpression")
//    {
//        Calculator calculator;
//        std::optional<Operator> functionOperator = operators.at('-');
//        Function function(
//                calculator,
//                functionOperator,
//                "first secondArgument",
//                "second firstArgument",
//                std::numeric_limits<double>::quiet_NaN()
//        );
//
//        double firstArg = 6;
//        double secondArg = 2;
//        double result = 4;
//        function.CalculateExpression(firstArg, secondArg);
//        REQUIRE(function.getValue(firstArg, secondArg) == result);
//    }
//
//    std::cout << "Function: CalculateExpression DIVISION" << std::endl;
//    SECTION("CalculateExpression")
//    {
//        Calculator calculator;
//        std::optional<Operator> functionOperator = operators.at('/');
//        Function function(
//                calculator,
//                functionOperator,
//                "first secondArgument",
//                "second firstArgument",
//                std::numeric_limits<double>::quiet_NaN()
//        );
//
//        double firstArg = 6;
//        double secondArg = 2;
//        double result = 3;
//        function.CalculateExpression(firstArg, secondArg);
//        REQUIRE(function.getValue(firstArg, secondArg) == result);
//    }
//
//    std::cout << "Function: CalculateExpression MULTIPLICATION" << std::endl;
//    SECTION("CalculateExpression")
//    {
//        Calculator calculator;
//        std::optional<Operator> functionOperator = operators.at('*');
//        Function function(
//                calculator,
//                functionOperator,
//                "first secondArgument",
//                "second firstArgument",
//                std::numeric_limits<double>::quiet_NaN()
//        );
//
//        double firstArg = 6;
//        double secondArg = 2;
//        double result = 12;
//        function.CalculateExpression(firstArg, secondArg);
//        REQUIRE(function.getValue(firstArg, secondArg) == result);
//    }
}

//TEST_CASE("Testing class CalculatorController")
//{
//    std::cout << "Function: GetCommand" << std::endl;
//    SECTION("GetCommand")
//    {
//        CalculatorController calculatorController;
//        REQUIRE(calculatorController.GetCommand("var") == commands.at("var"));
//    }
//
//    std::cout << "Function: GetCommand" << std::endl;
//    SECTION("GetCommand")
//    {
//        CalculatorController calculatorController;
//        REQUIRE(calculatorController.GetCommand("print") == commands.at("print"));
//    }
//
//    std::cout << "Function: GetCommand" << std::endl;
//    SECTION("GetCommand")
//    {
//        CalculatorController calculatorController;
//        REQUIRE(calculatorController.GetCommand("let") == commands.at("let"));
//    }
//
//    std::cout << "Function: GetCommand" << std::endl;
//    SECTION("GetCommand")
//    {
//        CalculatorController calculatorController;
//        REQUIRE(calculatorController.GetCommand("printvars") == commands.at("printvars"));
//    }
//
//    std::cout << "Function: GetCommand" << std::endl;
//    SECTION("GetCommand")
//    {
//        CalculatorController calculatorController;
//        REQUIRE(calculatorController.GetCommand("printfns") == commands.at("printfns"));
//    }
//
//    std::cout << "Function: GetCommand" << std::endl;
//    SECTION("GetCommand")
//    {
//        CalculatorController calculatorController;
//        REQUIRE(calculatorController.GetCommand("fn") == commands.at("fn"));
//    }
//
//    std::cout << "Function: GetCommand without command" << std::endl;
//    SECTION("GetCommand")
//    {
//        CalculatorController calculatorController;
//        REQUIRE(calculatorController.GetCommand("Diman") == std::nullopt);
//    }
//
//    std::cout << "Function: getValue from function" << std::endl;
//    SECTION("getValue")
//    {
//        CalculatorController calculatorController;
//        double value = 10;
//        calculatorController.AddVariables("x", value);
//        calculatorController.AddVariables("y", value);
//        calculatorController.InitFunction("XplusY", "x+y");
//        double result = 20;
//        REQUIRE(calculatorController.getValue("XplusY") == result);
//        double result2 = calculatorController.getValue("XplusssY");
//        REQUIRE(result != result2);
//    }
//
//    std::cout << "Function: InitFunction " << std::endl;
//    SECTION("InitFunction")
//    {
//        CalculatorController calculatorController;
//        double value = 10;
//        calculatorController.AddVariables("x", value);
//        calculatorController.InitFunction("XPlusY", "x");
//        double result = 10;
//        REQUIRE(calculatorController.getValue("XPlusY") == result);
//    }
//}