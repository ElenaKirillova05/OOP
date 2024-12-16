#include <iostream>
#include "../include/point.h"
#include "../include/utils.h"

Point::Point() : x{0}, y{0} {}
Point::Point(double xValue, double yValue) : x{xValue}, y{yValue} {}
Point::Point(double value) : Point(value, value) {}
Point::Point(const Point &other) : Point(other.x, other.y) {}

Point &Point::operator=(const Point &other)
{
    if (this == &other)
        return *this;
    x = other.x;
    y = other.y;
    return *this;
}


Point &Point::operator= (Point &&other){
    x = other.x;
    y = other.y;
    return *this;
}

bool Point::operator==(const Point &other) const
{
    return (Utils::eqDouble(x, other.x) && Utils::eqDouble(y, other.y));
}

Point Point::operator+(const Point &other) const
{
    return Point(x + other.x, y + other.y);
}

Point Point::operator-(const Point &other) const
{
    return Point(x - other.x, y - other.y);
}

Point Point::operator*(double number) const
{
    return Point(number * x, number * y);
}

double Point::operator*(const Point &other) const
{
    return (x * other.x + y * other.y);
}

double Point::abs()
{
    return sqrt(x * x + y * y);
}

double Point::getX()
{
    return x;
}

double Point::getY()
{
    return y;
}

std::ostream &operator<<(std::ostream &os, const Point &point)
{
    os << "(" << point.x << "; " << point.y << ")";
    return os;
}

std::istream &operator>>(std::istream &is, Point &point)
{
    double x, y;

    std::cout << "(Input x: ";
    is >> x;
    std::cout << " Input y: ";
    is >> y;
    std::cout << ")" << std::endl;

    point.x = x;
    point.y = y;

    return is;
}