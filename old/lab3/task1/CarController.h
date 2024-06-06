#pragma once
#include "Car.h"
#include <sstream>
#include <iostream>
#include <string>

enum class Command
{
    INFO,
    ENGINE_ON,
    ENGINE_OFF,
    SET_GEAR,
    SET_SPEED
};

namespace {
    const int MIN_GEAR = -1;
    const std::map<std::string, Command> commands = {
            { "Info", Command::INFO },
            { "EngineOn", Command::ENGINE_ON },
            { "EngineOff", Command::ENGINE_OFF },
            { "SetGear", Command::SET_GEAR },
            { "SetSpeed", Command::SET_SPEED },
    };

    const int MAX_GEAR = 5;

    const int REVERSE_GEAR = -1;
    const int NEUTRAL_GEAR = 0;
    const int FIRST_GEAR = 1;

    const int DIRECTION_BACKWARD = -1;
    const int NO_DIRECTION = 0;

    const std::string ENGINE = "Engine: ";
    const std::string DIRECTION = "Direction: ";
    const std::string SPEED = "Speed: ";
    const std::string GEAR = "GEAR: ";
    const std::string ON = "On";
    const std::string OFF = "Off";
    const std::string BACKWARD = "Backward\n";
    const std::string WITHOUT_DIRECTION = "Without direction\n";
    const std::string FORWARD = "Forward\n";

    const std::string SUCCESS_TURNED_ON = "The engine is turned on successfully!\n";
    const std::string FAILED_TURNED_ON = "The engine is already turned on!\n";
    const std::string SUCCESS_TURNED_OFF = "The engine is turned off successfully!\n";
    const std::string ALREADY_TURNED_OFF = "The engine is already off!\n";
    const std::string SHUTDOWN_ERROR = "shutdown error!\n";
    const std::string GEAR_CANNOT_SET = " gear can\'t be set\n";
    const std::string GEAR_SET = " gear set\n";
    const std::string SPEED_CANNOT_SET = " speed can\'t be set\n";
    const std::string SPEED_SET = " speed set\n";
    const std::string ENGINE_OFF = "engine turned off\n";

    const std::string COMMAND_NOT_EXIST= "This command does not exist\n";
    const std::string INCORRECT_GEAR_FORMAT = "Incorrect gear parameter format\n";
    const std::string INCORRECT_SPEED_FORMAT = "Incorrect speed parameter format\n";
    const std::string CANNOT_SHUTDOWN_ENGINE_WHEN_SPEED_GEAR_ZERO = "can\'t shutdown engine when speed or gear are not at 0\n";
    const std::string GEAR_NOT_EXIST = "this gear does not exist in the car\n";
    const std::string CANNOT_SET_NON_NEUTRAL_GEAR_WHEN_ENGINE_OFF = "impossible to switch to a non-neutral gear when the engine is off\n";
    const std::string CANNOT_SET_FORWARD_GEAR_WHEN_DRIVING_BACKWARD = "impossible to switch to forward gear when driving backward\n";
    const std::string CANNOT_SET_REVERSE_GEAR_WHEN_NOT_REST = "Switch to reverse gear allowed after stop\n";
    const std::string GEAR_NOT_SUPPORT_SPEED = "the gear doesn\'t support the current speed\n";
    const std::string CANNOT_INCREASE_SPEED_IN_NEUTRAL_GEAR = "can't increase the speed in neutral gear\n";
    const std::string SPEED_OUT_OF_RANGE_OF_GEAR = "the speed is out of the range of gear\n";
}

// Зачем делать класс
// лучше, сделать поле хранящая ссылку на автомобиль и все методы завзять на ссылку
class CarController
{
private:
    static Car m_car;
public:
    CarController();
    static void PrintInfo();
    static void ExecuteCommand(const std::string& userAppeal);
    static bool GetCommand(std::stringstream& stringAppeal, Command& command);
    static void PrintEngineInfo();
    static void PrintDirectionInfo();
    static void PrintSpeedInfo();
    static void PrintGearInfo();
    static void getCarInfo();
    static bool TurnOnEngine();
    static bool TurnOffEngine();
    static bool SetGear(int gear);
    static bool SetSpeed(int speed);
};
