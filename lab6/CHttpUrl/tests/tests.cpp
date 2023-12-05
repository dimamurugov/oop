#define CATCH_CONFIG_MAIN
#include "../../../../../catch2/catch.hpp"
#include "../CHttpUrl.h"

using namespace url;

TEST_CASE("Positive tests")
{
    SECTION("Init class")
    {
        CHttpUrl url("https://ya.ru");
        REQUIRE(url.GetURL() == "https://ya.ru/");

        CHttpUrl url2("ya.ru", "/directory/document.format",  url::protocols::Protocol::HTTP, 8080);
        REQUIRE(url2.GetURL() == "http://ya.ru:8080/directory/document.format");

        CHttpUrl url3("ya.ru", "/directory/document.format",  url::protocols::Protocol::HTTP);
        REQUIRE(url3.GetURL() == "http://ya.ru/directory/document.format");

        CHttpUrl url4("ya.ru", "/directory/document.format",  url::protocols::Protocol::HTTP, 80);
        REQUIRE(url4.GetURL() == "http://ya.ru/directory/document.format");
    }

    SECTION("Construct in args without port view")
    {
        SECTION("Check default http port")
        {
            CHttpUrl url(
                    "testdomain.test",
                    "/directory/document.format",
                    protocols::Protocol::HTTP);
            REQUIRE(url.GetURL() == "http://testdomain.test/directory/document.format");
            REQUIRE(url.GetPort() == 80);
        }
        SECTION("Check default https port")
        {
            CHttpUrl url(
                    "testdomain.test",
                    "/directory/document.format",
                    protocols::Protocol::HTTPS);
            REQUIRE(url.GetURL() == "https://testdomain.test/directory/document.format");
            REQUIRE(url.GetPort() == 443);
        }
    }

    SECTION("Construct in string url view")
    {
        SECTION("Http url without port")
        {
            CHttpUrl url("http://testdomain.test/directory/document.format");
            REQUIRE(url.GetProtocol() == protocols::Protocol::HTTP);
            REQUIRE(url.GetDomain() == "testdomain.test");
            REQUIRE(url.GetPort() == 80);
            REQUIRE(url.GetDocument() == "/directory/document.format");
        }
        SECTION("Http url with port")
        {
            CHttpUrl url("http://testdomain.test:8080/directory/document.format");
            REQUIRE(url.GetProtocol() == protocols::Protocol::HTTP);
            REQUIRE(url.GetDomain() == "testdomain.test");
            REQUIRE(url.GetPort() == 8080);
            REQUIRE(url.GetDocument() == "/directory/document.format");
        }
        SECTION("Https url without port")
        {
            CHttpUrl url("https://testdomain.test/directory/document.format");
            REQUIRE(url.GetProtocol() == protocols::Protocol::HTTPS);
            REQUIRE(url.GetDomain() == "testdomain.test");
            REQUIRE(url.GetPort() == 443);
            REQUIRE(url.GetDocument() == "/directory/document.format");
        }
        SECTION("Https url with port")
        {
            CHttpUrl url("https://testdomain.test:8080/directory/document.format");
            REQUIRE(url.GetProtocol() == protocols::Protocol::HTTPS);
            REQUIRE(url.GetDomain() == "testdomain.test");
            REQUIRE(url.GetPort() == 8080);
            REQUIRE(url.GetDocument() == "/directory/document.format");
        }
        SECTION("url with empty document")
        {
            CHttpUrl url("http://testdomain.test");
            REQUIRE(url.GetProtocol() == protocols::Protocol::HTTP);
            REQUIRE(url.GetDomain() == "testdomain.test");
            REQUIRE(url.GetPort() == 80);
            REQUIRE(url.GetDocument() == "/");

            CHttpUrl url2("http://testdomain.test/");
            REQUIRE(url2.GetProtocol() == protocols::Protocol::HTTP);
            REQUIRE(url2.GetDomain() == "testdomain.test");
            REQUIRE(url2.GetPort() == 80);
            REQUIRE(url2.GetDocument() == "/");
        }
    }
}

TEST_CASE("Negative tests")
{
    SECTION("Counstruct exceptions")
    {
        REQUIRE_THROWS(CHttpUrl(""));
        REQUIRE_THROWS(CHttpUrl("ftp://test.test"));
        REQUIRE_THROWS(CHttpUrl("ftp://"));
        REQUIRE_THROWS(CHttpUrl("http://test.test:0"));
        REQUIRE_THROWS(CHttpUrl("http://test.test:65536"));
        REQUIRE_THROWS(CHttpUrl("http://test.test:9999999999"));
        REQUIRE_THROWS(CHttpUrl("", "/", protocols::Protocol::HTTP));
    }
}