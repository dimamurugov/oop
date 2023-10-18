#define CATCH_CONFIG_MAIN
#include "../../../../../catch2/catch.hpp"

#include "../CPoint.h"
#include "../CCircle.h"
#include "../CLineSegment.h"
#include "../CRectangle.h"

TEST_CASE("Testing class CCircle")
{
    std::cout << "Init" << std::endl;
    SECTION("Init CCircle")
    {
        double x = 10.3;
        double y = 20.15;
        double radius = 30;
        CPoint center(x, y);
        ColorTypes colors;
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
        ColorTypes colors;
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
        ColorTypes colors;
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
        ColorTypes colors;
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
        ColorTypes colors={0x00ff00, 0x00ff00};
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
        ColorTypes colors={0x00ff00, 0x00ff00};
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
        ColorTypes colors={0x00ff00};
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
        ColorTypes colors={};
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
        ColorTypes colors ={0xff0000, 0x00ff00};
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
        ColorTypes colors={0x00ff00};
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
        ColorTypes colors={0x00ff00};
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
        ColorTypes colors={0x00ff00};
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
        ColorTypes colors={0x00ff00};
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
        ColorTypes colors={0x00ff00, 0xff0000};
        CLineSegment lineSegment(points, colors);
        REQUIRE(lineSegment.GetArea() == 0);
    }
    std::cout << "CLineSegment getPerimeter" << std::endl;
    SECTION("CLineSegment")
    {
        double x1 = 10.3;
        double y1 = 20.15;
        double x2 = 30.7;
        double y2 = 40.4;
        CPoint startPoint(x1, y1);
        CPoint endPoint(x2, y2);
        std::vector<CPoint> points = {startPoint, endPoint};
        ColorTypes colors={0x00ff00, 0xff0000};
        CLineSegment lineSegment(points, colors);
        double result = 28.74;
        REQUIRE(round(lineSegment.GetPerimeter()) == round(result));
    }
    std::cout << "CLineSegment getPerimeter" << std::endl;
    SECTION("CLineSegment")
    {
        double x1 = 10.3;
        double y1 = 20.15;
        double x2 = 30.7;
        double y2 = 40.4;
        CPoint startPoint(x1, y1);
        CPoint endPoint(x2, y2);
        std::vector<CPoint> points = {startPoint, endPoint};
        ColorTypes colors={0x00ff00};
        CLineSegment lineSegment(points, colors);
        std::string result = "Shape: LineSegment\n"
                             "Perimeter: 28.74\n"
                             "Start point: 10.3 20.15\n"
                             "Start point: 30.7 40.4\n"
                             "Outline color: 00ff00\n";
        REQUIRE(lineSegment.ToString() == result);
    }
}

TEST_CASE("Testing class CRectangle")
{
//    std::cout << "Init CRectangle" << std::endl;
//    SECTION("CRectangle")
//    {
//        double x = 10.3;
//        double y = 20.15;
//        double width = 30.7;
//        double height = 40.4;
//        CPoint point(x, y);
//        ColorTypes colors={0x00ff00};
//        CRectangle rectangle(point, width, height, colors);
//        REQUIRE(rectangle.GetLeftTop().GetPoint()[0] == x);
//    }
//    std::cout << "Area CRectangle" << std::endl;
//    SECTION("CRectangle")
//    {
//        double x = 10.3;
//        double y = 20.15;
//        double width = 30.7;
//        double height = 40.4;
//        CPoint point(x, y);
//        ColorTypes colors={0x00ff00};
//        CRectangle rectangle(point, width, height, colors);
//        double result = 1240;
//        REQUIRE(round(rectangle.GetArea()) == round(result));
//    }
//    std::cout << "Perimeter CRectangle" << std::endl;
//    SECTION("CRectangle")
//    {
//        double x = 10.3;
//        double y = 20.15;
//        double width = 30.7;
//        double height = 40.4;
//        CPoint point(x, y);
//        ColorTypes colors={0x00ff00};
//        CRectangle rectangle(point, width, height, colors);
//        double result = 142.2;
//        REQUIRE(round(rectangle.GetPerimeter()) == round(result));
//    }
//    std::cout << "Height CRectangle" << std::endl;
//    SECTION("CRectangle")
//    {
//        double x = 10.3;
//        double y = 20.15;
//        double width = 30.7;
//        double height = 40.4;
//        CPoint point(x, y);
//        ColorTypes colors={0x00ff00};
//        CRectangle rectangle(point, width, height, colors);
//        double result = 40.4;
//        REQUIRE(round(rectangle.GetHeight()) == round(result));
//    }
//    std::cout << "Height CRectangle" << std::endl;
//    SECTION("CRectangle")
//    {
//        double x = 10.3;
//        double y = 20.15;
//        double width = 30.7;
//        double height = 40.4;
//        CPoint point(x, y);
//        ColorTypes colors={0x00ff00};
//        CRectangle rectangle(point, width, height, colors);
//        double result = 30.7;
//        REQUIRE(round(rectangle.GetWidth()) == round(result));
//    }
//    std::cout << "GetOutlineColor CRectangle" << std::endl;
//    SECTION("CRectangle")
//    {
//        double x = 10.3;
//        double y = 20.15;
//        double width = 30.7;
//        double height = 40.4;
//        CPoint point(x, y);
//        ColorTypes colors={0x00ff00};
//        CRectangle rectangle(point, width, height, colors);
//        double result = 0x00ff00;
//        REQUIRE(rectangle.GetOutlineColor() == result);
//    }
//    std::cout << "GetFillColor CRectangle" << std::endl;
//    SECTION("CRectangle")
//    {
//        double x = 10.3;
//        double y = 20.15;
//        double width = 30.7;
//        double height = 40.4;
//        CPoint point(x, y);
//        ColorTypes colors={0x00ff00, 0xffff00};
//        CRectangle rectangle(point, width, height, colors);
//        double result = 0xffff00;
//        REQUIRE(rectangle.GetFillColor() == result);
//    }
}