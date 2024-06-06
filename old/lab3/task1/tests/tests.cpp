#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"

#include "../Car.h"
#include "../CarController.h"

TEST_CASE("Testing class Car")
{
    std::cout << "Function: IsTurnedOn" << std::endl;
    SECTION("Engine is working after TurnOnEngine")
     {
        Car car;
        car.TurnOnEngine();
        REQUIRE(car.IsTurnedOn() == true);
    }

    std::cout << "Function: TurnOnEngine" << std::endl;
    SECTION("Engine turning on failed if was already turned on")
    {
        Car car;
        car.TurnOnEngine();
        REQUIRE(car.TurnOnEngine() == false);
    }

    std::cout << "Function: TurnOffEngine" << std::endl;
    SECTION("Engine is not turned off when car is moving on neutral gear")
    {
        Car car;
        car.TurnOnEngine();
        car.SetGear(1);
        car.SetSpeed(10);
        car.SetGear(0);
        REQUIRE(car.TurnOffEngine() == false);
    }

    SECTION("Engine is not turned off when car is on neutral gear")
    {
        Car car;
        car.TurnOnEngine();
        car.SetGear(1);
        REQUIRE(car.TurnOffEngine() == false);
    }

    SECTION("Engine is turned off when car is not moving and on neutral gear")
    {
        Car car;
        car.TurnOnEngine();
        REQUIRE(car.TurnOffEngine() == true);
    }

    std::cout << "Function: GetDirection" << std::endl;
    SECTION("Direction -1 after start moving backward")
    {
        Car car;
        car.TurnOnEngine();
        car.SetGear(-1);
        car.SetSpeed(11);
        REQUIRE(car.GetDirection() == -1);
    }

    std::cout << "Function: SetSpeed" << std::endl;
    SECTION("Setting Speed up failed on neutral gear when car is not moving")
    {
        Car car;
        car.TurnOnEngine();
        REQUIRE(car.SetSpeed(10) == false);
    }

    SECTION("Setting Speed up failed on neutral gear when car is moving")
    {
        Car car;
        car.TurnOnEngine();
        car.SetGear(1);
        car.SetSpeed(10);
        car.SetGear(0);
        REQUIRE(car.SetSpeed(11) == false);
    }

    SECTION("Setting Speed failed when speed not in range of gear")
    {
        Car car;
        car.TurnOnEngine();
        car.SetGear(1);
        REQUIRE(car.SetSpeed(500) == false);
    }

    SECTION("Setting Speed success when speed in range of gear")
    {
        Car car;
        car.TurnOnEngine();
        car.SetGear(1);
        REQUIRE(car.SetSpeed(10) == true);
    }

    std::cout << "Function: SetGear" << std::endl;
    SECTION("Setting gear failing after creating car")
    {
        Car car;
        REQUIRE(car.SetGear(-1) == false);
    }

    SECTION("Setting gear success when speed is in range of gear")
    {
        Car car;
        car.TurnOnEngine();
        car.SetGear(1);
        car.SetSpeed(30);
        REQUIRE(car.SetGear(2) == true);
    }

    SECTION("Setting gear failed when speed is not in range of gear")
    {
        Car car;
        car.TurnOnEngine();
        car.SetGear(1);
        car.SetSpeed(10);
        REQUIRE(car.SetGear(2) == false);
    }
}

TEST_CASE("Testing class CarController")
{
    std::cout << "Function: GetCommand" << std::endl;
    SECTION("Command = Info")
    {
        CarController controller;
        std::stringstream stringCommand("Info");
        Command command;
        REQUIRE(controller.GetCommand(stringCommand, command) == true);
        REQUIRE(command == Command::INFO);
    }

    SECTION("Incorrect command = SetGear1")
    {
        CarController controller;
        std::stringstream stringCommand("SetGear1");
        Command command;
        REQUIRE(controller.GetCommand(stringCommand, command) == false);
    }

    SECTION("Correct command = SetGear 1")
    {
        CarController controller;
        std::stringstream stringCommand("SetGear 1");
        Command command;
        REQUIRE(controller.GetCommand(stringCommand, command) == true);
        REQUIRE(command == Command::SET_GEAR);
    }

    std::cout << "Function: TurnOnEngine" << std::endl;
    SECTION("Engine turn on if was turned off")
    {
        CarController controller;
        Car car;
        REQUIRE(controller.TurnOnEngine(car) == true);
    }

    std::cout << "Function: TurnOffEngine" << std::endl;
    SECTION("Engine is turned off when car is not moving and on neutral gear")
    {
        CarController controller;
        Car car;
        car.TurnOnEngine();
        car.SetGear(1);
        car.SetSpeed(10);
        car.SetGear(0);
        REQUIRE(controller.TurnOffEngine(car) == false);
    }

    SECTION("Engine is not turned off when car is not on neutral gear")
    {
        CarController controller;
        Car car;
        car.TurnOnEngine();
        car.SetGear(1);
        REQUIRE(controller.TurnOffEngine(car) == false);
    }

    SECTION("Engine is turned off when car is not moving and on neutral gear")
    {
        CarController controller;
        Car car;
        car.TurnOnEngine();
        REQUIRE(controller.TurnOffEngine(car) == true);
    }

    SECTION("Engine turning off success if was already turned off")
    {
        CarController controller;
        Car car;
        REQUIRE(controller.TurnOffEngine(car) == true);
    }

    std::cout << "Function: SetSpeed" << std::endl;
    SECTION("Setting Speed up failed on neutral gear when car is not moving")
    {
        CarController controller;
        Car car;
        car.TurnOnEngine();
        REQUIRE(controller.SetSpeed(car, 10) == false);
    }

    SECTION("Setting Speed up failed on neutral gear when car is moving")
    {
        CarController controller;
        Car car;
        car.TurnOnEngine();
        car.SetGear(1);
        car.SetSpeed(10);
        car.SetGear(0);
        REQUIRE(controller.SetSpeed(car, 11) == false);
    }

    SECTION("Setting Speed failed when speed not in range of gear")
    {
        CarController controller;
        Car car;
        car.TurnOnEngine();
        car.SetGear(1);
        REQUIRE(controller.SetSpeed(car, 500) == false);
    }

    SECTION("Setting Speed success when speed in range of gear")
    {
        CarController controller;
        Car car;
        car.TurnOnEngine();
        car.SetGear(1);
        REQUIRE(controller.SetSpeed(car, 10) == true);
    }

    std::cout << "Function: SetGear" << std::endl;
    SECTION("Setting gear failing after creating car")
    {
        CarController controller;
        Car car;
        REQUIRE(controller.SetGear(car, -1) == false);
    }

    SECTION("Setting gear success when speed is in range of gear")
    {
        CarController controller;
        Car car;
        car.TurnOnEngine();
        car.SetGear(1);
        car.SetSpeed(30);
        REQUIRE(controller.SetGear(car, 2) == true);
    }

    SECTION("Setting gear failed when speed is not in range of gear")
    {
        CarController controller;
        Car car;
        car.TurnOnEngine();
        car.SetGear(1);
        car.SetSpeed(10);
        REQUIRE(controller.SetGear(car, 2) == false);
    }
}