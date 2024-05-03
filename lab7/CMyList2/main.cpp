#include <iostream>
#include "CMyList.h"

int main()
{
    CMyList<int> list;
    list.AddEnd(1);
    list.AddEnd(2);
//    list.AddEnd(3);
    auto it = list.end();
    std::cout << *(++it) << std::endl;


    return 0;
}