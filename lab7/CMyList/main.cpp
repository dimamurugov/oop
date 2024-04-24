#include <iostream>
#include "CMyList.h"

int main()
{
    CMyList<int> list;
    list.AddEnd(1);
    list.AddEnd(2);
    list.AddEnd(3);
    std::cout << list.GetSize() << std::endl;
    CMyList<int> list2 = list;
    std::cout << list2.GetSize() << std::endl;
//    auto it = list.Insert(list.begin(), "A");
//    std::cout << *it << std::endl;

    return 0;
}