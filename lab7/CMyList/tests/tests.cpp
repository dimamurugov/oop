#define CATCH_CONFIG_MAIN
#include "../../../../../catch2/catch.hpp"
#include "../CMyList.cpp"

TEST_CASE("CMyListTests")
{
    SECTION("Init Empty List")
    {
        const CMyList<int> list;
        REQUIRE(list.GetSize() == 0);
    }

    SECTION("Init List Constructor with iterators")
    {
        CMyList<std::string> list1;
        list1.AddEnd("1");
        list1.AddEnd("2");
        list1.AddEnd("3");
        list1.AddEnd("4");
        REQUIRE(list1.GetSize() == 4);
        auto it = list1.begin();
        REQUIRE(*it == "1");
        REQUIRE(*(++it) == "2");
        REQUIRE(*(++it) == "3");
        REQUIRE(*(++it) == "4");
    }

    SECTION("Init List Constructor with reverse iterators")
    {
        CMyList<std::string> list1;
        list1.AddEnd("1");
        list1.AddEnd("2");
        list1.AddEnd("3");
        list1.AddEnd("4");
        REQUIRE(list1.GetSize() == 4);
        auto it = list1.rend();// как можно больше разбить тесты
        REQUIRE(*(--it) == "1");

    }
}

TEST_CASE("Insert element in list")
{
    SECTION("Init List Constructor with reverse iterators")
    {
        CMyList<std::string> list;
        REQUIRE(list.GetSize() == 0);
        list.Insert(list.begin(), "A");
        REQUIRE(list.GetSize() == 1);
        auto it = list.begin();
        REQUIRE(*it == "A");

        list.Insert(list.end(), "C");
        auto it2 = list.end();
        REQUIRE(list.GetSize() == 2);
        auto it3 = list.end();
        REQUIRE(*(--it3) == "C");

        list.AddEnd("D"); // приведу в порядок тесты

        auto it4 = list.begin();
        list.Insert((++it4), "B");
        REQUIRE(list.GetSize() == 4);
        REQUIRE(*(++(list.begin())) == "B");
    }
}

TEST_CASE("Delete")
{
    SECTION("Delete first")
    {
        CMyList<std::string> list;
        list.AddEnd("A");
        list.AddEnd("B");
        list.AddEnd("D");
        REQUIRE(list.GetSize() == 3);
        auto it = list.begin();
        list.Del(it);
        REQUIRE(list.GetSize() == 2);
        auto it2 = list.begin();
        REQUIRE(*it2 == "B");
    }

    SECTION("Delete end")
    {
        CMyList<std::string> list;
        list.AddEnd("A");
        list.AddEnd("B");
        list.AddEnd("D");
        REQUIRE(list.GetSize() == 3);
        auto it = list.end();
        list.Del((--it));
        REQUIRE(list.GetSize() == 2);
        auto it2 = list.end();
        REQUIRE(*(--it2) == "B");
    }

    SECTION("Delete B")
    {
        CMyList<std::string> list;
        list.AddEnd("A");
        list.AddEnd("B");
        list.AddEnd("D");
        REQUIRE(list.GetSize() == 3);
        auto it = list.begin();
        list.Del(++it);
        REQUIRE(list.GetSize() == 2);
        auto itBegin = list.begin();
        auto itEnd = list.end();
        REQUIRE(*itBegin == "A");
        REQUIRE(*(--itEnd) == "D");
    }
}