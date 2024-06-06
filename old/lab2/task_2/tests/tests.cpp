#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../DecodeHtmlFunctions.h"

TEST_CASE("Test: Get decoded html element")
{
    SECTION("Get decoded html element: '<'")
    {
        auto result = GetDecodedHtmlElement("&lt;");
        REQUIRE(result == '<');
    }
    SECTION("Get decoded html element: '>'")
    {
        auto result = GetDecodedHtmlElement("&gt;");
        REQUIRE(result == '>');
    }
    SECTION("Get decoded html element: '&'")
    {
        auto result = GetDecodedHtmlElement("&amp;");
        REQUIRE(result == '&');
    }
    SECTION("Get decoded html element: '\"'")
    {
        auto result = GetDecodedHtmlElement("&quot;");
        REQUIRE(result == '\"');
    }
    SECTION("Get decoded html element: '\''")
    {
        auto result = GetDecodedHtmlElement("&apos;");
        REQUIRE(result == '\'');
    }
    SECTION("Get decoded html element: unknown")
    {
        auto result = GetDecodedHtmlElement("&l3t;");
        REQUIRE(result == std::nullopt);
    }
}

TEST_CASE("Test: Html decode")
{
    SECTION("Decode empty string")
    {
        // упростить тесты избавиться от переменных
        std::string initialHtml;
        std::string expectedHtml;
        std::string result = HtmlDecode(initialHtml);
        REQUIRE(result == expectedHtml);
    }
    SECTION("Decode string without html element")
    {
        std::string initialHtml = "Hello world";
        std::string expectedHtml = "Hello world";
        std::string result = HtmlDecode(initialHtml);
        REQUIRE(result == expectedHtml);
    }
    SECTION("Decode string with breaking html element")
    {
        std::string initialHtml = "&gt Hello  world; ";
        std::string expectedHtml = "&gt Hello  world; ";
        std::string result = HtmlDecode(initialHtml);
        REQUIRE(result == expectedHtml);
    }
    SECTION("Decode string with unfinished html element")
    {
        std::string initialHtml = "Hello world &gt";
        std::string expectedHtml = "Hello world &gt";
        std::string result = HtmlDecode(initialHtml);
        REQUIRE(result == expectedHtml);
    }
    SECTION("Decode string with only char amp")
    {
        std::string initialHtml = "&";
        std::string expectedHtml = "&";
        std::string result = HtmlDecode(initialHtml);
        REQUIRE(result == expectedHtml);
    }
    SECTION("Decode string with only multi char amp")
    {
        std::string initialHtml = "&&&&&";
        std::string expectedHtml = "&&&&&";
        std::string result = HtmlDecode(initialHtml);
        REQUIRE(result == expectedHtml);
    }
    SECTION("Decode string with only char ';'")
    {
        std::string initialHtml = ";";
        std::string expectedHtml = ";";
        std::string result = HtmlDecode(initialHtml);
        REQUIRE(result == expectedHtml);
    }
    SECTION("Decode string with only multi char ';'")
    {
        std::string initialHtml = ";;;";
        std::string expectedHtml = ";;;";
        std::string result = HtmlDecode(initialHtml);
        REQUIRE(result == expectedHtml);
    }
    SECTION("Decode string with html element on center")
    {
        std::string initialHtml = "Hello &lt; world";
        std::string expectedHtml = "Hello < world";
        std::string result = HtmlDecode(initialHtml);
        REQUIRE(result == expectedHtml);
    }
    SECTION("Decode string with html element on start")
    {
        std::string initialHtml = "&gt;Hello world";
        std::string expectedHtml = ">Hello world";
        std::string result = HtmlDecode(initialHtml);
        REQUIRE(result == expectedHtml);
    }
    SECTION("Decode string with html element on end")
    {
        std::string initialHtml = "Hello world&amp;";
        std::string expectedHtml = "Hello world&";
        std::string result = HtmlDecode(initialHtml);
        REQUIRE(result == expectedHtml);
    }
    SECTION("Decode encoded string \" Cat &lt;says&gt; &quot;Meow&quot;. M&apos; \"")
    {
        std::string initialHtml = "Hello world&amp;";
        std::string expectedHtml = "Hello world&";
        std::string result = HtmlDecode(initialHtml);
        REQUIRE(result == expectedHtml);
    }
}
