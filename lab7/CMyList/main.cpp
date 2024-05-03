#include <iostream>
#include "CMyList.h"

int main()
{
    CMyList<int> list;
    list.AddEnd(1);
    list.AddEnd(2);
    list.AddEnd(3);
    std::cout << list.GetSize() << std::endl;
    auto iter = list.GetSize();
    std::cout << list2.GetSize() << std::endl;

    return 0;
}