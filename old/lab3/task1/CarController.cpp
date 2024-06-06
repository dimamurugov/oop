#include "CarController.h"

CarController::CarController() = default;

void CarController::ExecuteCommand(Car& car, const std::string& userCommand)
{
    std::stringstream stringCommand(userCommand);
    Command command;

    if (CarController::GetCommand(stringCommand, command))
    {
        switch (command)
        {
            case Command::INFO:
                CarController::getCarInfo(m_car);
                break;

            case Command::ENGINE_ON:
                CarController::TurnOnEngine(m_car);
                break;

            case Command::ENGINE_OFF:
                CarController::TurnOffEngine(m_car);
                break;

            case Command::SET_GEAR:
                int gear;
                if (stringCommand >> gear)
                {
                    CarController::SetGear(m_car, gear);
                    break;
                }
                std::cout << INCORRECT_GEAR_FORMAT;
                break;

            case Command::SET_SPEED:
                int speed;
                if (stringCommand >> speed)
                {
                    CarController::SetSpeed(m_car, speed);
                    break;
                }
                std::cout << INCORRECT_SPEED_FORMAT;
                break;
            default:
                break;
        }
    }
    else
    {
        std::cout << COMMAND_NOT_EXIST;
    }
}

bool CarController::GetCommand(std::stringstream& commandLine, Command& command)
{
    std::string stringCommand;
    commandLine >> stringCommand;
    if (commands.find(stringCommand) != commands.end())
    {
        command = commands.at(stringCommand);
        return true;
    }
    return false;
}

void CarController::PrintEngineInfo()
{
    std::cout << ENGINE;
    if (m_car.IsTurnedOn())
    {
        std::cout << ON;
    }
    else
    {
        std::cout << OFF;
    }
    std::cout << std::endl;
}

void CarController::PrintDirectionInfo()
{
    std::cout << DIRECTION;
    switch (m_car.GetDirection())
    {
        case -1:
            std::cout << BACKWARD;
            break;
        case 0:
            std::cout << WITHOUT_DIRECTION;
            break;
        case 1:
            std::cout << FORWARD;
            break;
        default:
            break;
    }
}

void CarController::PrintSpeedInfo()
{
    std::cout << SPEED << m_car.GetSpeed() << std::endl;
}

void CarController::PrintGearInfo()
{
    std::cout << GEAR << m_car.GetGear() << std::endl;
}

void CarController::getCarInfo()
{
    CarController::PrintEngineInfo(m_car);
    CarController::PrintDirectionInfo(m_car);
    CarController::PrintSpeedInfo(m_car);
    CarController::PrintGearInfo(m_car);
}

bool CarController::TurnOnEngine()
{
    if (m_car.TurnOnEngine()) {
        std::cout << SUCCESS_TURNED_ON;
        return true;
    };
    std::cout << FAILED_TURNED_ON;
    return false;
}

bool CarController::TurnOffEngine()
{
    if (!m_car.IsTurnedOn())
    {
        std::cout << ALREADY_TURNED_OFF;
        return true;
    }
    if (m_car.GetSpeed() == 0 && m_car.GetGear() == 0)
    {
        m_car.TurnOffEngine();
        std::cout << SUCCESS_TURNED_OFF;
        return true;
    }
    std::cout << SHUTDOWN_ERROR << CANNOT_SHUTDOWN_ENGINE_WHEN_SPEED_GEAR_ZERO;
    return false;
}

bool CarController::SetGear(int gear)
{
    if (gear < MIN_GEAR || gear > MAX_GEAR)
    {
        std::cout << gear << GEAR_CANNOT_SET << GEAR_NOT_EXIST;
        return false;
    }
    if (!m_car.IsTurnedOn() && gear != NEUTRAL_GEAR)
    {
        std::cout << gear << GEAR_CANNOT_SET << CANNOT_SET_NON_NEUTRAL_GEAR_WHEN_ENGINE_OFF;
        return false;
    }
    if (gear == FIRST_GEAR && m_car.GetDirection() == DIRECTION_BACKWARD)
    {
        std::cout << gear << GEAR_CANNOT_SET << CANNOT_SET_FORWARD_GEAR_WHEN_DRIVING_BACKWARD;
        return false;
    }
    if (gear == REVERSE_GEAR && m_car.GetDirection() != NO_DIRECTION)
    {
        std::cout << gear << GEAR_CANNOT_SET << CANNOT_SET_REVERSE_GEAR_WHEN_NOT_REST;
        return false;
    }

    if (m_car.SetGear(gear))
    {
        std::cout << gear << GEAR_SET;
        return true;
    }
    std::cout << gear << GEAR_CANNOT_SET << GEAR_NOT_SUPPORT_SPEED;
    return false;
}

bool CarController::SetSpeed(int speed)
{
    if (!m_car.IsTurnedOn())
    {
        std::cout << speed << SPEED_CANNOT_SET << ENGINE_OFF;
        return false;
    }
    if ((m_car.GetGear() == NEUTRAL_GEAR && speed > m_car.GetSpeed()) || speed < 0)
    {
        std::cout << speed << SPEED_CANNOT_SET << CANNOT_INCREASE_SPEED_IN_NEUTRAL_GEAR;
        return false;
    }
    if (m_car.SetSpeed(speed))
    {
        std::cout << speed << SPEED_SET;
        return true;
    }

    std::cout << speed << SPEED_CANNOT_SET << SPEED_OUT_OF_RANGE_OF_GEAR;
    return false;
}

void CarController::PrintInfo()
{
    std::cout << "Commands:" << std::endl
              << "\"Info\"" << std::endl
              << "\"EngineOn\"" << std::endl
              << "\"EngineOff\"" << std::endl
              << "\"SetGear <n>\"" << std::endl
              << "\"SetSpeed <n>\"" << std::endl;
}

//0.7