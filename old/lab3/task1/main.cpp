#include <iostream>
#include "Car.h"
#include "CarController.h"

int main()
{
    // Метод для контроллера который вводит справку

    Car car;
    CarController controller;
    controller.PrintInfo();

    std::string userCommand;
    while (getline(std::cin, userCommand))
    {
        controller.ExecuteCommand(car, userCommand);
    }
    return 0;
}