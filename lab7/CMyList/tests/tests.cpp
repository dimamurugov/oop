#define CATCH_CONFIG_MAIN
#include "../../../../../catch2/catch.hpp"
#include "../CMyList.cpp"

TEST_CASE("MyArrayConstructorsTests")
{
    SECTION("Init Empty Array")
    {
        const CMyList<int> arr;
        REQUIRE(arr.Size() == 0);
    }

    SECTION("Copy constructor")
    {
        CMyList<std::string> list1;
        list1.AddEnd("1");
        list1.AddEnd("2");
        list1.AddEnd("3");
        CMyList<std::string> list2(list1);

        REQUIRE(list1.Size() == 3);

        REQUIRE(list1.Size() == list2.Size());
        auto i = list1.begin();
        auto j = list2.begin();
        while (i < list1.end()) {
            REQUIRE(*i == *j);

            ++i;
            ++j;
        }
    }

    SECTION("Copy Assignment Constructor")
    {
        CMyList<std::string> list1;
        list1.AddEnd("1");
        list1.AddEnd("2");
        list1.AddEnd("3");
        CMyList<std::string> list2 = list1;

        REQUIRE(list1.Size() == 3);
        REQUIRE(list1.Size() == list2.Size());
        auto i = list1.begin();
        auto j = list2.begin();
        while (i < list1.end()) {
            REQUIRE(*i == *j);

            ++i;
            ++j;
        }
    }

    SECTION("Init List Constructor with iterators")
    {
        CMyList<std::string> list1;
        list1.AddEnd("1");
        list1.AddEnd("2");
        list1.AddEnd("3");
        list1.AddEnd("4");
        REQUIRE(list1.Size() == 4);
        std::string result;
        for (auto i = list1.begin(); i != list1.end(); ++i)
        {
            result += *i;
        }

        REQUIRE(result == "1234");
    }

    SECTION("Init List Constructor with reverse iterators")
    {
        CMyList<std::string> list1;
        list1.AddEnd("1");
        list1.AddEnd("2");
        list1.AddEnd("3");
        list1.AddEnd("4");
        REQUIRE(list1.Size() == 4);
        std::string result;
        for (auto i = list1.rbegin(); i != list1.rend(); ++i)
        {
            result += *i;
        }

        REQUIRE(result == "4321");
    }
}

TEST_CASE("Push Back MethodsTests")
{
    SECTION("Push And Check If Exists")
    {
        CMyList<int> list;
        list.AddEnd(5);

        REQUIRE(list.GetElement(0) == 5);
        REQUIRE(list.Size() == 1);
    }

    SECTION("Push Strings And Concatenate Them")
    {
        CMyList<char> list;
        char ch = 'a';
        std::string result;
        for (size_t i = 0; i < 26; ++i)
        {
            list.AddEnd(ch);
            ch++;
            result += list.GetElement(i);
        }

        REQUIRE(list.Size() == 26);
        REQUIRE(result == "abcdefghijklmnopqrstuvwxyz");
    }
}

TEST_CASE("Square Brackets Operator Overloading")
{
    SECTION("Change Value Of First Element")
    {
        CMyList<int> list;
        list.AddEnd(10);
        REQUIRE(*list.begin() == 10);
        list.Insert(20, 0);
        REQUIRE(*list.begin() == 20);
    }

    SECTION("Throws When Out Of Range Empty List")
    {
        CMyList<int> list;
        REQUIRE_THROWS(list.GetElement(0));
    }

    SECTION("Throws When Out Of Range")
    {
        CMyList<int> list;
        list.AddEnd(12345);
        REQUIRE_THROWS(list.GetElement(1));
    }
}

TEST_CASE("Clear Methods Tests")
{
    SECTION("Clear Empty")
    {
        CMyList<int> list;
        REQUIRE(list.Size() == 0);
        list.Clear();
        REQUIRE(list.Size() == 0);
    }

    SECTION("Clear Not Empty")
    {
        CMyList<std::string> list;
        list.AddEnd("a");
        list.AddEnd("b");
        list.AddEnd("c");

        REQUIRE(list.Size() == 3);
        list.Clear();
        REQUIRE(list.Size() == 0);
    }
}

TEST_CASE("Insert")
{
    SECTION("Insert 'F' ")
    {
        CMyList<std::string> list;
        list.AddEnd("a");
        list.AddEnd("b");
        list.AddEnd("c");
        REQUIRE(list.GetElement(1) == "b");
        list.Insert("F", 1);
        REQUIRE(list.GetElement(1) == "F");
    }

    SECTION("Insert wrong index ")
    {
        CMyList<std::string> list;
        list.AddEnd("a");
        list.AddEnd("b");
        list.AddEnd("c");
        REQUIRE(list.GetElement(1) == "b");
        list.Insert("F", 111);
        REQUIRE_THROWS(list.GetElement(111) == "b");
    }

    SECTION("Insert element in end list")
    {
        CMyList<std::string> list;
        list.AddEnd("a");
        list.AddEnd("b");
        list.AddEnd("c");
        REQUIRE(list.GetElement(2) == "c");
        list.Insert("F", 2);
        REQUIRE(list.GetElement(2) == "F");
    }

    SECTION("Insert element in end list")
    {
        CMyList<std::string> list;
        list.AddEnd("a");
        list.AddEnd("b");
        list.AddEnd("c");
        list.Insert("F", 3);
        REQUIRE(list.GetElement(3) == "F");
    }
}
