#include <iostream>
#include "CMyArray.cpp"

int main() {
    CMyArray<int> arr = { 0, 1, 2, 3, 4, 5, 6, 7 };
    // CMyArray<double> arr = { 0.1, 1.1, 2.1, 3.1, 4.1, 5.1 };
    for (auto i = arr.begin(); i < arr.end(); ++i)
    {
        std::cout << *i << std::endl;
    }

    for (auto i = arr.rbegin(); i != arr.rend(); ++i)
    {
        std::cout << *i << std::endl;
    }
    return 0;
}
