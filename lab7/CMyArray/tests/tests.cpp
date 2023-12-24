#define CATCH_CONFIG_MAIN
#include "../../../../../catch2/catch.hpp"
#include "../CMyArray.cpp"

TEST_CASE("MyArrayConstructorsTests")
{
    SECTION("Init Empty Array")
    {
        const CMyArray<int> arr;
        REQUIRE(arr.Size() == 0);
    }

    SECTION("Copy constructor")
    {
        CMyArray<std::string> arr1;
        arr1.PushBack("1");
        arr1.PushBack("2");
        arr1.PushBack("3");
        CMyArray<std::string> arr2(arr1);

        REQUIRE(arr1.Size() == 3);
        REQUIRE(arr1.Size() == arr2.Size());

        for (size_t i = 0; i < arr1.Size(); ++i)
        {
            REQUIRE(arr1[i] == arr2[i]);
        }
    }

    SECTION("Copy Assignment Constructor")
    {
        CMyArray<std::string> arr1;
        arr1.PushBack("1");
        arr1.PushBack("2");
        arr1.PushBack("3");
        CMyArray<std::string> arr2 = arr1;

        REQUIRE(arr1.Size() == 3);
        REQUIRE(arr1.Size() == arr2.Size());

        for (size_t i = 0; i < arr1.Size(); ++i)
        {
            REQUIRE(arr1[i] == arr2[i]);
        }
    }

    SECTION("Init List Constructor")
    {
        CMyArray<std::string> arr = { "1", "2", "3" };
        std::string str;
        auto result = std::accumulate(arr.begin(), arr.end(), str);

        REQUIRE(result == "123");
    }

    SECTION("Init List Constructor with reverse iterators")
    {
        CMyArray<std::string> arr = { "0", "1", "2", "3" };
        REQUIRE(arr.Size() == 4);
        std::string result;
        for (auto i = arr.rbegin(); i != arr.rend(); ++i)
        {
            result += *i;
        }

        REQUIRE(result == "3210");
    }

    SECTION("Copy Self")
    {
        CMyArray<std::string> arr;
        arr.PushBack("1");
        arr.PushBack("2");
        arr.PushBack("3");
        arr = arr;

        REQUIRE(arr.Size() == 3);
        REQUIRE(arr[0] == "1");
        REQUIRE(arr[1] == "2");
        REQUIRE(arr[2] == "3");
    }

    SECTION("Move Constructor")
    {
        CMyArray<std::string> arr1;
        arr1.PushBack("1");
        arr1.PushBack("2");
        arr1.PushBack("3");

        REQUIRE(arr1.Size() == 3);

        CMyArray<std::string> arr2(std::move(arr1));

        REQUIRE(arr1.Size() == 0);
        REQUIRE("1" == arr2[0]);
        REQUIRE("2" == arr2[1]);
        REQUIRE("3" == arr2[2]);
        REQUIRE(arr2.Size() == 3);
    }

    SECTION("Move Assignment Constructor")
    {
        CMyArray<std::string> arr1;
        arr1.PushBack("1");
        arr1.PushBack("2");
        arr1.PushBack("3");

        REQUIRE(arr1.Size() == 3);

        CMyArray<std::string> arr2 = std::move(arr1);

        REQUIRE(arr1.Size() == 0);
        REQUIRE("1" == arr2[0]);
        REQUIRE("2" == arr2[1]);
        REQUIRE("3" == arr2[2]);
        REQUIRE(arr2.Size() == 3);
    }
}

TEST_CASE("Push Back MethodsTests")
{
    SECTION("Push And Check If Exists")
    {
        CMyArray<int> arr;
        arr.PushBack(5);

        REQUIRE(arr[0] == 5);
        REQUIRE(arr.Size() == 1);
    }

    SECTION("Push Multiple Times And CHeck")
    {
        CMyArray<int> arr;
        arr.PushBack(3);
        arr.PushBack(2);
        arr.PushBack(1);
        arr.PushBack(0);

        REQUIRE(arr.Size() == 4);
        for (int i = 0; i < 4; ++i)
        {
            REQUIRE(arr[i] == int(arr.Size()) - 1 - i);
        }
    }

    SECTION("Push Strings And Concatenate Them")
    {
        CMyArray<char> arr;
        char ch = 'a';
        std::string result;
        for (size_t i = 0; i < 26; ++i)
        {
            arr.PushBack(ch);
            ch++;
            result += arr[i];
        }

        REQUIRE(arr.Size() == 26);
        REQUIRE(result == "abcdefghijklmnopqrstuvwxyz");
    }
}

TEST_CASE("Square Brackets Operator Overloading")
{
    SECTION("Change Value Of First Element")
    {
        CMyArray<int> arr;
        arr.PushBack(10);
        REQUIRE(arr[0] == 10);
        arr[0] = 20;
        REQUIRE(arr[0] == 20);
    }

    SECTION("Not Throws When In Range")
    {
        CMyArray<int> arr;
        arr.PushBack(123);
        REQUIRE(arr[0]);
    }

    SECTION("Throws When Out Of Range Empty Array")
    {
        CMyArray<int> arr;
        REQUIRE_THROWS(arr[0]);
    }

    SECTION("Throws When Out Of Range")
    {
        CMyArray<int> arr;
        arr.PushBack(12345);
        REQUIRE_THROWS(arr[1]);
    }
}

TEST_CASE("Clear Methods Tests")
{
    SECTION("Clear Empty")
    {
        CMyArray<int> arr;
        REQUIRE(arr.Size() == 0);
        arr.Clear();
        REQUIRE(arr.Size() == 0);
    }

    SECTION("Clear Not Empty")
    {
        CMyArray<std::string> arr;
        arr.PushBack("a");
        arr.PushBack("b");
        arr.PushBack("c");

        REQUIRE(arr.Size() == 3);
        arr.Clear();
        REQUIRE(arr.Size() == 0);
    }
}

TEST_CASE("Resize Method Tests")
{
    SECTION("Resize Empty")
    {
        CMyArray<int> arr;
        arr.Resize(100);
        REQUIRE(arr.Size() == 100);
        for (size_t i = 0; i < 100; ++i)
        {
            REQUIRE(arr[i] == 0);
        }
    }

    SECTION("Resize To Smaller Value")
    {
        CMyArray<int> arr;
        arr.PushBack(1);
        arr.PushBack(2);
        arr.PushBack(3);
        arr.Resize(2);

        REQUIRE(arr[0] == 1);
        REQUIRE(arr[1] == 2);
        REQUIRE(arr.Size() == 2);
        REQUIRE_THROWS(arr[2]);

    }

    SECTION("Resize To Bigger Value")
    {
        CMyArray<int> arr;
        arr.PushBack(1);
        arr.PushBack(2);
        arr.PushBack(3);
        arr.Resize(5);

        REQUIRE(arr[0] == 1);
        REQUIRE(arr[1] == 2);
        REQUIRE(arr[2] == 3);
        REQUIRE(arr[3] == 0);
        REQUIRE(arr[4] == 0);
        REQUIRE(arr.Size() == 5);

    }

    SECTION("Throws when increment end iterator")
    {
        CMyArray<std::string> arr = { "0", "1", "2", "3" };

        REQUIRE_THROWS(++arr.rend());
        REQUIRE_THROWS(++arr.end());
    }
}
