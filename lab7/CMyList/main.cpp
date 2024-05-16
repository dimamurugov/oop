#include <iostream>
#include "CMyList.h"

int main()
{
    CMyList<int> list;
//    list.AddEnd(1);
//    list.AddEnd(2);
//    list.AddEnd(3);

//    CMyList<int> list2;
//    CMyList<int> list3;
//    list2 = list; // копирования
//    list3 = std::move(list);
    // auto list2 = list; // копирование
    // auto list3 = CMyList<int>(); // перемещение
    std::cout << list.GetSize() << std::endl;
//    std::cout << list3.GetSize() << std::endl;
    // std::cout << list3.GetSize() << std::endl;
    return 0;
}