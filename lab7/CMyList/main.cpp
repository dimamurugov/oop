#include <iostream>
#include "CMyList.h"

int main()
{
//    CMyList<std::string> list1;
//    list1.AddEnd("1");
//    list1.AddEnd("2");
//    list1.AddEnd("3");
//
//    CMyList<std::string> list2(list1);
//    list2.AddEnd("4");

    CMyList<std::string> list;
    list.AddEnd("a");
    list.AddEnd("b");
    list.AddEnd("c");
    std::cout << list.GetSize() << std::endl;
//    list.Insert("F", 3);
//    list.GetElement(3);
    // REQUIRE(list.GetElement(3) == "F");

//    auto i = list1.begin();
//    auto j = list2.begin();
//
//    while (i < list1.end()) {
//        std::cout << *i << std::endl;
//        std::cout << *j << std::endl;
//
//        ++i;
//        ++j;
//    }
}