#include <iostream>
#include "CMyString.h"

int main() {
    std::string test {"12345"};
    std::cout << test.length() << std::endl;
    std::cout << test.capacity() << std::endl;

//    CMyString str;
//    std::cout << str.GetLength() << std::endl;
    return 0;
}
