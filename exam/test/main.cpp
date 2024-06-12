#include <iostream>
#include <vector>

int main() {
    // это чо типо US
    std::vector<int> test = {1, 2, 3, 4};
    test[5] = 5;

    for (int i = 0; i < test.size() + 1; ++i) {
        std::cout << test[i] << std::endl;
    }

    // Утечка памяти
    char *pointer = nullptr;
    pointer = new char[100];
    pointer = new char[100];
    delete pointer;
    return 0;

    // Аварийное завершение программы
}
