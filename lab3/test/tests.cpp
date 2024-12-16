#include <gtest/gtest.h>
#include <stdexcept>
#include "../include/point.h"
#include "../include/figure.h"
#include "../include/rhombus.h"
#include "../include/rectangle.h"
#include "../include/trapezoid.h"

TEST(UtilsTest, testeqDouble)
{
    double a = 3.0;
    double b = 2.0;
    double c = 5.0;
    bool result = Utils::eqDouble(a + b, c);
    ASSERT_TRUE(result == true);
}

TEST(UtilsTest, testeqDoubleFalse)
{
    double a = 3.0;
    double b = 2.0;
    double c = 5.1;
    bool result = Utils::eqDouble(a + b, c);
    ASSERT_TRUE(result == false);
}


TEST(PointTest, testConctructorAndEquality)
{
    Point a = Point();
    Point b(0.0, 0.0);
    bool result = (a == b);
    ASSERT_TRUE(result == true);
}

TEST(PointTest, testEqualityFalse)
{
    Point a(1.0, 2.0);
    Point b(1.0);
    bool result = (a == b);
    ASSERT_TRUE(result == false);
}

TEST(PointTest, testSummarize)
{
    Point a(1.0, 1.0);
    Point b(1.0, 2.0);
    Point c = a + b;
    Point d(2.0, 3.0);
    bool result = (c == d);
    ASSERT_TRUE(result == true);
}



TEST(PointTest, testProductNumber)
{
    Point a(1.0, 3.0);
    Point b = a * 3;
    Point c(3.0, 9.0);
    bool result = (b == c);
    ASSERT_TRUE(result == true);
}


TEST(PointTest, testPosAbs) {
    Point p1(3, 4);
    bool result = Utils::eqDouble(p1.abs(), 5.0);
    ASSERT_TRUE(result == true);
}


TEST(PointTest, testNegAbs) {
    Point p1(-3, -4);
    bool result = Utils::eqDouble(p1.abs(), 5.0);
    ASSERT_TRUE(result == true);
}


TEST(PointTest, testZerosAbs) {
    Point p1(0.0, 0.0);
    bool result = Utils::eqDouble(p1.abs(), 0.0);
    ASSERT_TRUE(result == true);
}


TEST(PointTest, testCopy) {
    Point p1(1.0, 2.0);
    Point p2(2.0, 2.0);
    Point p3 = p1;
    bool result = (p1 == p3);
    bool result1 = (p2 == p3);
    ASSERT_TRUE(result == true);
    ASSERT_TRUE(result1 == false);
}

TEST(TrapezoidTest, ConstructorTrapezoid) {
    Trapezoid trapezoid = Trapezoid();
    Point a(0.0, 0.0), b(1.0, 1.0), c(2.0, 1.0), d(3.0, 0.0);
    Trapezoid t(a, b, c, d);
    bool result = (trapezoid == t);
    ASSERT_TRUE(result == true);
}


TEST(TrapezoidTest, ValidTrapezoid) {
    Point a(0.0, 0.0), b(4.0, 0.0), c(3.0, 2.0), d(1.0, 2.0);
    EXPECT_NO_THROW({
        Trapezoid t(a, b, c, d);
    });
}

TEST(TrapezoidTest, EqTrapezoid1) {
    Point a1(0.0), b1(1.0), c1(2.0, 1.0), d1(3.0, 0.0);
    Point a2(0.0), b2(1.0), c2(2.0, 1.0), d2(3.0, 0.0);
    Point a3(0.0), b3(1.0, -1.0), c3(2.0, -1.0), d3(3.0, 0.0);
    Point a4(0.0), b4(1.0), c4(3.0, 1.0), d4(4.0, 0.0);
    Trapezoid trapezoid1(a1, b1, c1, d1);
    Trapezoid trapezoid2(a2, b2, c2, d2);
    Trapezoid trapezoid3(a3, b3, c3, d3);
    Trapezoid trapezoid4(a4, b4, c4, d4);
    bool result = trapezoid1 == trapezoid2;
    ASSERT_TRUE(result == true);
}



TEST(TrapezoidTest, ConstructorAndArea) {
    Point a(0.0, 0.0), b(4.0, 0.0), c(3.0, 2.0), d(1.0, 2.0);
    Trapezoid trapezoid(a, b, c, d);
    bool result = Utils::eqDouble((double)(trapezoid), 6.0);
    bool result1 = Utils::eqDouble((double)(trapezoid), 5.0);
    ASSERT_TRUE(result == true);
    ASSERT_TRUE(result1 == false);
}

TEST(TrapezoidTest, validCenter) {
    Point a(0.0), b(4.0, 0.0), c(3.0, 2.0), d(1.0, 2.0);
    Trapezoid trapezoid(a, b, c, d);
    Point realCenter(2.0, 1.0);
    Point center = trapezoid.calcCentrRotation();
    bool result = (center == realCenter);
    ASSERT_TRUE(result == true);
}


TEST(RectangleTest, ConstructorRectangle) {
    Rectangle rectangle = Rectangle();
    Point a(0.0, 0.0), b(1.0, 0.0), c(1.0, 1.0);
    Rectangle r(a, b, c);
    bool result = (rectangle == r);
    ASSERT_TRUE(result == true);
}


TEST(RectangleTest, ValidRectangle) {
    Point a(0.0, 0.0), b(1.0, 1.0), c(2.0, 0.0);
    EXPECT_NO_THROW({
        Rectangle r(a, b, c);
    });
}


TEST(RectangleTest, EqRectangle1) {
    Point a1(0.0, 0.0), b1(0.0, 1.0), c1(2.0, 1.0);
    Point a2(0.0, 1.0), b2(0.0, 2.0), c2(2.0, 2.0);
    Point a3(0.0, 0.0), b3(0.0, 2.0), c3(1.0, 2.0);
    Point a4(0.0, 0.0), b4(1.0, 0.0), c4(1.0, 1.0);
    Rectangle rectangle1(a1, b1, c1);
    Rectangle rectangle2(a2, b2, c2);
    Rectangle rectangle3(a3, b3, c3);
    Rectangle rectangle4(a4, b4, c4);
    bool result = rectangle1 == rectangle2;
    ASSERT_TRUE(result == true);
}


TEST(RectangleTest, ConstructorAndArea) {
    Point a(0.0, 0.0), b(4.0, 0.0), c(4.0, 2.0);
    Rectangle rectangle(a, b, c);
    bool result = Utils::eqDouble((double)(rectangle), 8.0);
    ASSERT_TRUE(result == true);
}

TEST(RectangleTest, Center) {
    Point a(0.0, 0.0), b(4.0, 0.0), c(4.0, 2.0);
    Rectangle rectangle(a, b, c);
    Point realCenter(2.0, 1.0);
    Point center = rectangle.calcCentrRotation();
    bool result = (center == realCenter);
    ASSERT_TRUE(result == true);
}

TEST(RhombusTest, ConstructorRhombus) {
    Rhombus rhombus = Rhombus();
    Point a(1.0, 0.0), b(0.0, 0.0), c(0.0, 1.0);
    Rhombus r(a, b, c);
    bool result = (rhombus == r);
    ASSERT_TRUE(result == true);
}


TEST(RhombusTest, ValidRhombus) {
    Point a(0.0, 0.0), b(1.0, 1.0), c(2.0, 0.0);
    EXPECT_NO_THROW({
        Rhombus r(a, b, c);
    });
}

TEST(RhombusTest, EqRhombus1) {
    Point a1(0.0, 0.0), b1(2.0, 1.0), c1(4.0, 0.0);
    Point a2(0.0, 1.0), b2(1.0, 3.0), c2(0.0, 5.0);
    Point a3(0.0, 1.0), b3(1.0, 3.0), c3(0.0, 5.0);
    Point a4(0.0, 0.0), b4(1.0, 1.0), c4(2.0, 0.0);
    Rhombus rhombus1(a1, b1, c1);
    Rhombus rhombus2(a2, b2, c2);
    Rhombus rhombus3(a3, b3, c3);
    Rhombus rhombus4(a4, b4, c4);
    bool result = rhombus1 == rhombus2;
    ASSERT_TRUE(result == true);
}

TEST(RhombusTest, ConstructorAndArea) {
    Point a(1.0, 0.0), b(2.0, 1.0), c(3.0, 0.0);
    Rhombus rhombus(a, b, c);
    bool result = Utils::eqDouble((double)(rhombus), 2.0);
    ASSERT_TRUE(result == true);
}

TEST(RhombusTest, Center) {
    Point a(1, 0), b(2, 1), c(3, 0);
    Rhombus rhombus(a, b, c);
    Point realCenter(2.0, 0.0);
    Point center = rhombus.calcCentrRotation();
    bool result = (center == realCenter);
    ASSERT_TRUE(result == true);
}


int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}