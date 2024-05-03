#define CATCH_CONFIG_MAIN
#include "../../../../../catch2/catch.hpp"
#include "../CMyList.cpp"

TEST_CASE("Init list")
{
    SECTION("Init int empty List")
    {
        const CMyList<int> list;
        REQUIRE(list.GetSize() == 0);
    }

    SECTION("Init string empty List")
    {
        const CMyList<std::string> list;
        REQUIRE(list.GetSize() == 0);
    }
}

TEST_CASE("AddEnd")
{
    SECTION("Add end in empty list")
    {
        CMyList<std::string> list1;
        list1.AddEnd("1");
        REQUIRE(list1.GetSize() == 1);
    }

    SECTION("Add end 3 element in empty list")
    {
        CMyList<std::string> list1;
        list1.AddEnd("1");
        list1.AddEnd("2");
        list1.AddEnd("3");
        REQUIRE(list1.GetSize() == 3);
    }
}

TEST_CASE("AddBegin")
{
    SECTION("Add begin in empty list")
    {
        CMyList<std::string> list1;
        list1.AddBegin("1");
        REQUIRE(list1.GetSize() == 1);
    }

    SECTION("Add begin 3 element in empty list")
    {
        CMyList<std::string> list1;
        list1.AddBegin("1");
        list1.AddBegin("2");
        list1.AddBegin("3");
        REQUIRE(list1.GetSize() == 3);
    }
}

TEST_CASE("Node")
{
    SECTION("Constructor")
    {
        Node<std::string> node{};
        node.Construct("1");
        REQUIRE(*(node.Get()) == "1");
    }

    SECTION("Get")
    {
        Node<std::string> node{};
        node.Construct("1");
        REQUIRE(*(node.Get()) == "1");
    }

    SECTION("Destroy")
    {
        Node<std::string> node{};
        node.Construct("1");
        REQUIRE(*node.Get() == "1");
        node.Destroy();
        REQUIRE(*node.Get() == "1");
    }
}

TEST_CASE("iterator")
{
    SECTION("get begin element")
    {
        CMyList<std::string> list;
        list.AddEnd("1");
        list.AddEnd("2");
        list.AddEnd("3");
        auto iter = list.begin();
        REQUIRE(*iter == "1");
    }

    SECTION("rbegin")
    {
        CMyList<std::string> list;
        list.AddEnd("1");
        list.AddEnd("2");
        list.AddEnd("3");
        auto iter = list.rbegin();
        REQUIRE(*(iter) == "3");
    }

    SECTION("rend")
    {
        CMyList<std::string> list;
        list.AddEnd("1");
        list.AddEnd("2");
        list.AddEnd("3");
        auto iter = list.rend();
        REQUIRE(*(--iter) == "1");
    }

    SECTION("get end element")
    {
        CMyList<std::string> list;
        list.AddEnd("1");
        list.AddEnd("2");
        list.AddEnd("3");
        auto iter = list.end();
        REQUIRE(*(--iter) == "3");
    }

    SECTION("operator++")
    {
        CMyList<std::string> list;
        list.AddEnd("1");
        list.AddEnd("2");
        list.AddEnd("3");
        auto iter = list.begin();
        REQUIRE(*iter == "1");
        REQUIRE(*(++iter) == "2");
    }

    SECTION("operator++ with sentinel")
    {
        CMyList<std::string> list;
        list.AddEnd("1");
        auto iter = list.begin();
        REQUIRE_THROWS(*(++iter));
    }

    SECTION("operator--")
    {
        CMyList<std::string> list;
        list.AddEnd("1");
        list.AddEnd("2");
        list.AddEnd("3");
        auto iter = list.end();
        REQUIRE(*(--iter) == "3");
    }

    SECTION("operator-- with sentinel")
    {
        CMyList<std::string> list;
        list.AddEnd("1");
        auto iter = list.begin();
        REQUIRE_THROWS(*(--iter));
    }

    SECTION("++operator (pre)")
    {
        CMyList<std::string> list;
        list.AddEnd("1");
        list.AddEnd("2");
        auto iter = list.begin();
        REQUIRE(*iter == "1");
        REQUIRE(*(iter++) == "1");

        REQUIRE(*iter == "2");
    }

    SECTION("++operator (pre) with sentinel")
    {
        CMyList<std::string> list;
        list.AddEnd("1");
        list.AddEnd("2");
        auto iter = list.end();
        REQUIRE_THROWS(*(iter++) == "1");
    }

    SECTION("operator-- (pre)")
    {
        CMyList<std::string> list;
        list.AddEnd("1");
        list.AddEnd("2");
        list.AddEnd("3");
        auto iter = list.end();
        auto iter2 = iter--;
        REQUIRE(*(--iter2) == "3");
    }

    SECTION("operator-- (pre) with sentinel")
    {
        CMyList<std::string> list;
        list.AddEnd("1");
        list.AddEnd("2");
        list.AddEnd("3");
        auto iter = list.begin();
        REQUIRE_THROWS(*(iter--));
    }
}

TEST_CASE("begin")
{
    SECTION("Add begin in empty list")
    {
        CMyList<std::string> list1;
        list1.AddBegin("1");
        REQUIRE(list1.GetSize() == 1);
    }

    SECTION("Add begin 3 element in empty list")
    {
        CMyList<std::string> list1;
        list1.AddBegin("1");
        list1.AddBegin("2");
        list1.AddBegin("3");
        REQUIRE(list1.GetSize() == 3);
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
        auto it = list.begin();
        list.Del(it);
        auto it2 = list.begin();
        REQUIRE(list.GetSize() == 2);
        REQUIRE(*it2 == "B");
    }

    SECTION("Delete end")
    {
        CMyList<std::string> list;
        list.AddEnd("A");
        list.AddEnd("B");
        list.AddEnd("D");
        auto it = list.end();
        list.Del((--it));
        auto it2 = list.end();
        REQUIRE(list.GetSize() == 2);
        REQUIRE(*(--it2) == "B");
    }

    SECTION("try Delete sentinel")
    {
        CMyList<std::string> list;
        list.AddEnd("A");
        list.AddEnd("B");
        list.AddEnd("D");
        auto it = list.end();
        REQUIRE_THROWS(list.Del(it));
    }
}

TEST_CASE("Insert")
{
    SECTION("Insert in begin")
    {
        CMyList<std::string> list;
        REQUIRE(list.GetSize() == 0);
        list.Insert(list.begin(), "A");
        REQUIRE(list.GetSize() == 1);
    }

    SECTION("Insert in end")
    {
        CMyList<std::string> list;
        list.AddBegin("A");
        list.Insert(list.end(), "C");
        REQUIRE(*(++list.begin()) == "C");
    }

    SECTION("Insert in middle")
    {
        CMyList<std::string> list;
        list.AddEnd("A");
        list.AddEnd("C");
        list.Insert(++list.begin(), "B");
        REQUIRE(*(++list.begin()) == "B");
    }
}