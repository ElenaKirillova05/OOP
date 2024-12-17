#include <gtest/gtest.h>
#include <stdexcept>
#include "../include/point.h"
#include "../include/figure.h"
#include "../include/rhombus.h"
#include "../include/rectangle.h"
#include "../include/trapezoid.h"
#include "../include/array.h"

TEST(UtilsTest, testeqDouble)
{
    double a = 3.0;
    double b = 2.0;
    double c = 5.0;
    bool result = Utils::eqDouble(a + b, c);
    ASSERT_TRUE(result == true);
}


TEST(UtilsTest, testSTriangle)
{
    double a = 3.0;
    double b = 4.0;
    double c = 5.0;
    double s = 6.0;
    bool result = Utils::eqDouble(s, Utils::STriangle(a, b, c));
    ASSERT_TRUE(result == true);
}

TEST(PointTest, testConctructorAndEquality)
{
    Point<double> a;
    Point b(0.0, 0.0);
    bool result = (a == b);
    ASSERT_TRUE(result == true);
}

TEST(PointTest, getterY) {
    Point point(2.0, 3.0);
    double getYRes = point.getY();

    ASSERT_TRUE(getYRes == 3.0);
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

TEST(PointTest, testSubstraction)
{
    Point a(1.0, 1.0);
    Point b(1.0, 2.0);
    Point c(2.0, 3.0);
    Point d = c - b;
    bool result = (a == d);
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


TEST(TrapezoidTest, ConstructorTrapezoid) {
    Trapezoid<double> trapezoid;
    Point a(0.0), b(1.0), c(2.0, 1.0), d(3.0, 0.0);
    Trapezoid t(a, b, c, d);
    bool result = (trapezoid == t);
    ASSERT_TRUE(result == true);
}


TEST(TrapezoidTest, EqTrapezoid1) {
    Point a1(0.0, 0.0), b1(3.0, 4.0), c1(5.0, 4.0), d1(8.0, 0.0);
    Point a2(0.0, 0.0), b2(3.0, 4.0), c2(5.0, 4.0), d2(8.0, 0.0);
    Point a3(0.0, 0.0), b3(3.0, -4.0), c3(5.0, -4.0), d3(8.0, 0.0);
    Trapezoid trapezoid1(a1, b1, c1, d1);
    Trapezoid trapezoid2(a2, b2, c2, d2);
    Trapezoid trapezoid3(a3, b3, c3, d3);
    bool result = trapezoid1 == trapezoid2;
    ASSERT_TRUE(result == true);
}

TEST(TrapezoidTest, Center) {
    Point a(0.0), b(4.0, 0.0), c(3.0, 2.0), d(1.0, 2.0);
    Trapezoid trapezoid(a, b, c, d);
    Point realCenter(2.0, 1.0);
    Point center = trapezoid.calcCentrRotation();
    bool result = (center == realCenter);
    ASSERT_TRUE(result == true);
}

TEST(RectangleTest, ConstructorRectangle) {
    Rectangle<double> rectangle;
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

TEST(RectangleTest, Center) {
    Point a(0.0, 0.0), b(4.0, 0.0), c(4.0, 2.0);
    Rectangle rectangle(a, b, c);
    Point realCenter(2.0, 1.0);
    Point center = rectangle.calcCentrRotation();
    bool result = (center == realCenter);
    ASSERT_TRUE(result == true);
}

TEST(RhombusTest, ConstructorRhombus) {
    Rhombus<double> rhombus;
    Point a(1.0, 0.0), b(0.0, 0.0), c(0.0, 1.0);
    Rhombus r(a, b, c);
    bool result = (rhombus == r);
    ASSERT_TRUE(result == true);
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



TEST(RhombusTest, Center) {
    Point a(1, 0), b(2, 1), c(3, 0);
    Rhombus rhombus(a, b, c);
    Point realCenter(2.0, 0.0);
    Point center = rhombus.calcCentrRotation();
    bool result = (center == realCenter);
    ASSERT_TRUE(result == true);
}



TEST(ArrayTest, Move) {
    Array<int> array;

    array.append(1);
    array.append(2);

    Array<int> copyArray{std::move(array)};

    int firstElem = copyArray[0];
    int secondElem = copyArray[1];
    int length = copyArray.getSize();
    int lengthSrc = array.getSize();    

   bool result = firstElem == 1 && secondElem == 2 && length == 2 && lengthSrc == 0;
    ASSERT_TRUE(result == true);
}


TEST(ArrayTest, AssigmentMove) {
    Array<int> array;

    array.append(1);
    array.append(2);

    Array<int> copyArray = std::move(array);

    int firstElem = copyArray[0];
    int secondElem = copyArray[1];
    int length = copyArray.getSize();
    int lengthSrc = array.getSize();    
   bool result = (firstElem == 1 && secondElem == 2 && length == 2 && lengthSrc == 0);
    ASSERT_TRUE(result == true); 
}



TEST(ArrayTest, CmpEqualLength) {
    Array<int> array;

    array.append(1);
    array.append(2);
    array.append(3);

    Array<int> array2;

    array2.append(1);
    array2.append(2);

    bool result = array == array2;

    ASSERT_TRUE(result == false);
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}