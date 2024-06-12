#define CATCH_CONFIG_MAIN
#include "../../../../../catch2/catch.hpp"
#include "../CMyString.h"

TEST_CASE("My string constructing")
{
    SECTION("Construct without any params")
    {
        CMyString str;
        REQUIRE(str.GetLength() == 0);
        REQUIRE(strcmp(str.GetStringData(), "") == 0);
    }

    SECTION("Construct without any params")
    {
        CMyString str("Hello");
        REQUIRE(str.GetLength() == 5);
        REQUIRE(strcmp(str.GetStringData(), "Hello") == 0);
    }

    SECTION("Constructing my string by chars array")
    {
        CMyString str("Hello world", 5);
        REQUIRE(str.GetLength() == 5);
        REQUIRE(strcmp(str.GetStringData(), "Hello") == 0);
    }

    SECTION("My string is equal to 'HelloWorld' with zero code char in the middle")
    {
        CMyString zeroCodeStr("Hello\0World", 11);
        REQUIRE(zeroCodeStr.GetLength() == 11);
        REQUIRE(std::equal(zeroCodeStr.GetStringData(), zeroCodeStr.GetStringData() + zeroCodeStr.GetLength(), "Hello\0World"));
    }

    SECTION("Constructing my string by stlString")
    {
        std::string stlStr("Hello");
        CMyString str(stlStr);
        REQUIRE(str.GetLength() == 5);
        REQUIRE(strcmp(str.GetStringData(), "Hello") == 0);
    }

    SECTION("my string is equal to 'HelloWorld' with zero code char in the middle")
    {
        std::string zeroCodeStlString("Hello\0World", 11);
        CMyString zeroCodeStr(zeroCodeStlString);
        REQUIRE(zeroCodeStr.GetLength() == 11);
        REQUIRE(std::equal(zeroCodeStr.GetStringData(), zeroCodeStr.GetStringData() + zeroCodeStr.GetLength(), "Hello\0World"));
    }

    SECTION("Constructing my string by another my string")
    {
        CMyString str("Hello");
        CMyString copy(str);

        REQUIRE(copy.GetLength() == 5);
        REQUIRE(strcmp(copy.GetStringData(), "Hello") == 0);
    }

    SECTION("Copy is equal to 'HelloWorld' with zero code char in the middle")
    {
        CMyString zeroCodeStr("Hello\0World", 11);
        CMyString zeroCodeCopy(zeroCodeStr);

        REQUIRE(zeroCodeCopy.GetLength() == 11);
        REQUIRE(std::equal(zeroCodeCopy.GetStringData(), zeroCodeCopy.GetStringData() + zeroCodeCopy.GetLength(), "Hello\0World"));
    }

    SECTION("Constructing my string by move constructor")
    {
        CMyString tempStr("Hello");
        CMyString str(std::move(tempStr));

        REQUIRE(tempStr.GetLength() == 0);
        REQUIRE(tempStr.GetCapacity() == 0);
        REQUIRE(str.GetLength() == 5);
        REQUIRE(strcmp(str.GetStringData(), "Hello") == 0);
    }
}

TEST_CASE("My string clearing")
{
    SECTION("Clear my string")
    {
        CMyString str("Hello");
        str.Clear();

        REQUIRE(str.GetLength() == 0);
        REQUIRE(strcmp(str.GetStringData(), "") == 0);
    }
}

TEST_CASE("Substring getting")
{
    SECTION("Take substring from middle with a length less than the rest of the string")
    {
        CMyString str("Hello big world");
        CMyString substr = str.SubString(6, 8);

        REQUIRE(substr.GetLength() == 8);
        REQUIRE(strcmp(substr.GetStringData(), "big worl") == 0);
    }

    SECTION("Take substring from middle with a length equal to the rest of the string")
    {
        CMyString str("Hello big world");
        CMyString substr = str.SubString(6, 9);

        REQUIRE(substr.GetLength() == 9);
        REQUIRE(strcmp(substr.GetStringData(), "big world") == 0);
    }

    SECTION("Take substring from middle with a length bigger than the rest of the string")
    {
        CMyString str("Hello big world");
        CMyString substr = str.SubString(6, 10);

        REQUIRE(substr.GetLength() == 9);
        REQUIRE(strcmp(substr.GetStringData(), "big world") == 0);
    }
}

TEST_CASE("Getting substring with start index greater than string length")
{
    CMyString str("Hello world");
    REQUIRE_THROWS(str.SubString(11, 1));
    REQUIRE_THROWS(str.SubString(12, 1));
}

TEST_CASE("Check opertor =")
{
    CMyString str;

    str = CMyString("My string");
    REQUIRE(strcmp(str.GetStringData(), "My string") == 0);

    str = "Some chars";
    REQUIRE(strcmp(str.GetStringData(), "Some chars") == 0);

    str = std::string("STL string");
    REQUIRE(strcmp(str.GetStringData(), "STL string") == 0);

    str = str;
    REQUIRE(strcmp(str.GetStringData(), "STL string") == 0);

    str = std::move(str);
    REQUIRE(strcmp(str.GetStringData(), "STL string") == 0);

    CMyString strToMove("Move");
    str = std::move(strToMove);
    REQUIRE(strcmp(str.GetStringData(), "Move") == 0);
}

TEST_CASE("Check operator +")
{
    CMyString str("World");

    CMyString result = CMyString("Hello") + str;
    REQUIRE(strcmp(result.GetStringData(), "HelloWorld") == 0);

    result = std::string("Hello") + str;
    REQUIRE(strcmp(result.GetStringData(), "HelloWorld") == 0);

    result = "Hello" + str;
    REQUIRE(strcmp(result.GetStringData(), "HelloWorld") == 0);
}


TEST_CASE("Check operator +=")
{
    CMyString str("Hello");
    REQUIRE(std::addressof(str += CMyString("World")) == std::addressof(str));
    REQUIRE(strcmp(str.GetStringData(), "HelloWorld") == 0);
}

TEST_CASE("Check operator ==")
{
    CMyString str("Hello");
    REQUIRE(str == CMyString("Hello"));
    REQUIRE_FALSE(str == CMyString("Helloo"));
    REQUIRE_FALSE(str == CMyString("hello"));
    REQUIRE(CMyString("") == CMyString(""));
}

TEST_CASE("Check operator !=")
{
    CMyString str("Hello");
    REQUIRE_FALSE(str != CMyString("Hello"));
    REQUIRE(str != CMyString("Helloo"));
    REQUIRE(str != CMyString("hello"));
    REQUIRE_FALSE(CMyString("") != CMyString(""));
}

TEST_CASE("Check operator >, <, >=, <=")
{
    CMyString str("Hello");

    REQUIRE(str > CMyString("Hell"));
    REQUIRE_FALSE(str > CMyString("Hello"));

    REQUIRE(str < CMyString("World"));
    REQUIRE_FALSE(str < CMyString("Apple"));

    REQUIRE(str >= CMyString("Hello"));
    REQUIRE_FALSE(str >= CMyString("World"));

    REQUIRE(str <= CMyString("Helloa"));
    REQUIRE_FALSE(str <= CMyString("Apple"));
}

TEST_CASE("Check operator []")
{
    CMyString str("My string");
    const CMyString constStr("Const my string");

    REQUIRE(str[1] == 'y');
    REQUIRE(constStr[1] == 'o');

    str[8] = 'k';
    REQUIRE(strcmp(str.GetStringData(), "My strink") == 0);

    REQUIRE_THROWS(str[9]);
    REQUIRE_THROWS(str[10]);
    REQUIRE_THROWS(constStr[15]);
    REQUIRE_THROWS(constStr[16]);
}

TEST_CASE("Check operator >> and <<")
{
    CMyString strOut("My string");
    CMyString strIn;
    std::stringstream stream = std::stringstream();
    stream << strOut;
    REQUIRE(stream.str() == "My string");
    stream >> strIn;
    REQUIRE(strcmp(strIn.GetStringData(), "My") == 0);
}

// 0.7 (1+0,5)

TEST_CASE("Iterator")
{
    SECTION("cheak ++it")
    {
        CMyString str("Hello");
        auto it = str.begin();
        REQUIRE(*it == 'H');
    }

    SECTION("cheak it++")
    {
        CMyString str("Hello");
        auto it = str.begin();
        REQUIRE(*it == 'H');
        REQUIRE(*(it++) == 'H');
        REQUIRE(*(it) == 'e');
        REQUIRE(*(++it) == 'l');
    }
}
