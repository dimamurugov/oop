#include <iostream>
#include <iterator>
#include "CShapeController.h"

int main() {
    std::string str;
    CShapeController controller;
    while (getline(std::cin, str))
    {
        controller.LineExecution(str);
    }
    return EXIT_SUCCESS;
}
