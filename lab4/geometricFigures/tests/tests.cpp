#define CATCH_CONFIG_MAIN
#include "../../../../../catch2/catch.hpp"

#include "../CPoint.h"
#include "../CCircle.h"
#include "../CLineSegment.h"

TEST_CASE("Testing class CCircle")
{
    std::cout << "Init" << std::endl;
    SECTION("Init CCircle")
    {
        double x = 10.3;
        double y = 20.15;
        double radius = 30;
        CPoint center(x, y);
        std::vector<uint32_t> colors;
        CCircle circle(center, radius, colors);
        REQUIRE(circle.GetRadius() == radius);
    }
    std::cout << "CCircle Perimeter" << std::endl;
    SECTION("Init CCircle")
    {
        double x = 10.3;
        double y = 20.15;
        double radius = 30;
        double perimeter = 188.4955592154;
        CPoint center(x, y);
        std::vector<uint32_t> colors;
        CCircle circle(center, radius, colors);
        REQUIRE(round(circle.GetPerimeter()) == round(perimeter));
    }
    std::cout << "CCircle GetArea" << std::endl;
    SECTION("Init CCircle")
    {
        double x = 10.3;
        double y = 20.15;
        double radius = 30;
        double area = 2827.433388;
        CPoint center(x, y);
        std::vector<uint32_t> colors;
        CCircle circle(center, radius, colors);
        REQUIRE(round(circle.GetArea()) == round(area));
    }
    std::cout << "CCircle GetCenter" << std::endl;
    SECTION("CCircle")
    {
        double x = 10.3;
        double y = 20.15;
        double radius = 30;
        double area = 2827.433388;
        CPoint center(x, y);
        std::vector<uint32_t> colors;
        CCircle circle(center, radius, colors);
        REQUIRE(round(circle.GetCenter().GetPoint()[0]) == round(x));
    }
    std::cout << "CCircle FillColor" << std::endl;
    SECTION("Init CCircle")
    {
        double x = 10.3;
        double y = 20.15;
        double radius = 30;
        uint32_t fillColor = 0x00ff00;
        CPoint center(x, y);
        std::vector<uint32_t> colors={0x00ff00, 0x00ff00};
        CCircle circle(center, radius, colors);
        REQUIRE(circle.GetFillColor() == fillColor);
    }
    std::cout << "CCircle outlineColor" << std::endl;
    SECTION("Init CCircle")
    {
        double x = 10.3;
        double y = 20.15;
        double radius = 30;
        uint32_t outlineColor = 0x00ff00;
        CPoint center(x, y);
        std::vector<uint32_t> colors={0x00ff00, 0x00ff00};
        CCircle circle(center, radius, colors);
        REQUIRE(circle.GetOutlineColor() == outlineColor);
    }
    std::cout << "CCircle outlineColor" << std::endl;
    SECTION("Init CCircle")
    {
        double x = 10.3;
        double y = 20.15;
        double radius = 30;
        CPoint center(x, y);
        std::vector<uint32_t> colors={0x00ff00};
        CCircle circle(center, radius, colors);
        REQUIRE(!circle.GetFillColor().has_value());
    }
    std::cout << "CCircle outlineColor" << std::endl;
    SECTION("Init CCircle")
    {
        double x = 10.3;
        double y = 20.15;
        double radius = 30;
        CPoint center(x, y);
        std::vector<uint32_t> colors={};
        CCircle circle(center, radius, colors);
        REQUIRE(!circle.GetOutlineColor().has_value());
    }
    std::cout << "CCircle ToString" << std::endl;
    SECTION("Init CCircle")
    {
        double x = 10.3;
        double y = 20.15;
        double radius = 30;
        CPoint center(x, y);
        std::vector<uint32_t> colors ={0xff0000, 0x00ff00};
        CCircle circle(center, radius, colors);
        std::string result = "Shape: Circle\n"
                             "Perimeter: 188.5\n"
                             "Area: 2827\n"
                             "Radius: 30\n"
                             "Center X:10.3 20.15\n"
                             "Outline color: ff0000\n"
                             "Fill color: 00ff00\n";
        REQUIRE(circle.ToString() == result);
    }
    std::cout << "CCircle outlineColor" << std::endl;
    SECTION("Init CCircle")
    {
        double x = 10.3;
        double y = 20.15;
        double radius = 30;
        CPoint center(x, y);
        std::vector<uint32_t> colors={0x00ff00};
        CCircle circle(center, radius, colors);
        REQUIRE(!circle.GetFillColor().has_value());
    }
}

TEST_CASE("Testing class CLineSegment")
{
    std::cout << "Init CLineSegment" << std::endl;
    SECTION("CLineSegment")
    {
        double x1 = 10.3;
        double y1 = 20.15;
        double x2 = 30.7;
        double y2 = 40.4;
        CPoint startPoint(x1, y1);
        CPoint endPoint(x2, y2);
        std::vector<CPoint> points = {startPoint, endPoint};
        std::vector<uint32_t> colors={0x00ff00};
        CLineSegment lineSegment(points, colors);
        REQUIRE(lineSegment.GetStartPoint().GetPoint()[0] == x1);
    }
    std::cout << " CLineSegment" << std::endl;
    SECTION("CLineSegment")
    {
        double x1 = 10.3;
        double y1 = 20.15;
        double x2 = 30.7;
        double y2 = 40.4;
        CPoint startPoint(x1, y1);
        CPoint endPoint(x2, y2);
        std::vector<CPoint> points = {startPoint, endPoint};
        std::vector<uint32_t> colors={0x00ff00};
        CLineSegment lineSegment(points, colors);
        REQUIRE(lineSegment.GetEndPoint().GetPoint()[0] == x2);
    }
    std::cout << "CLineSegment" << std::endl;
    SECTION("CLineSegment")
    {
        double x1 = 10.3;
        double y1 = 20.15;
        double x2 = 30.7;
        double y2 = 40.4;
        CPoint startPoint(x1, y1);
        CPoint endPoint(x2, y2);
        std::vector<CPoint> points = {startPoint, endPoint};
        std::vector<uint32_t> colors={0x00ff00};
        CLineSegment lineSegment(points, colors);
        uint32_t fillColor = 0x00ff00;
        REQUIRE(lineSegment.GetOutlineColor() == fillColor);
    }
    std::cout << "CLineSegment getArea" << std::endl;
    SECTION("CLineSegment")
    {
        double x1 = 10.3;
        double y1 = 20.15;
        double x2 = 30.7;
        double y2 = 40.4;
        CPoint startPoint(x1, y1);
        CPoint endPoint(x2, y2);
        std::vector<CPoint> points = {startPoint, endPoint};
        std::vector<uint32_t> colors={0x00ff00, 0xff0000};
        CLineSegment lineSegment(points, colors);
        REQUIRE(lineSegment.GetArea() == 0);
    }
}