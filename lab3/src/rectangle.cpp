#include <iostream>
#include <cmath>
#include <limits>
#include <stdexcept>
#include "../include/rectangle.h"
#include "../include/point.h"
#include "../include/utils.h"

void Rectangle::check(Point aPoint, Point bPoint, Point cPoint)
{
    Point ab = bPoint - aPoint;
    Point bc = bPoint - cPoint;
    Point dPoint = aPoint + cPoint - bPoint;
    Point ac = aPoint - cPoint;
    Point bd = bPoint - dPoint;
    double diagonal1 = ac.abs();
    double diagonal2 = bd.abs();
    if (!Utils::eqDouble((ab * bc), 0) || Utils::eqDouble(diagonal1, 0.0) || Utils::eqDouble(diagonal2, 0.0))
    {
        throw std::invalid_argument("Invalid coordinates, it can't be a Rectangle");
    }
};

Rectangle::Rectangle() : a{Point()}, b{Point(0.0, 1.0)}, c{Point(1.0)}, d{Point(1.0, 0.0)} {};

Rectangle::Rectangle(Point aPoint, Point bPoint, Point cPoint) : a{aPoint}, b{bPoint}, c{cPoint}, d{aPoint + cPoint - bPoint}
{
    check(aPoint, bPoint, cPoint);
}

Rectangle::Rectangle(const Rectangle &other) : Rectangle(other.a, other.b, other.c) {}
Rectangle::Rectangle(Rectangle &&other) : Rectangle(other.a, other.b, other.c) {}

Rectangle &Rectangle::operator=(const Rectangle &other)
{
    if (this == &other)
        return *this;
    a = other.a;
    b = other.b;
    c = other.c;
    d = other.d;
    return *this;
}

Rectangle &Rectangle::operator=(Rectangle &&other)
{
    a = other.a;
    b = other.b;
    c = other.c;
    d = other.d;
    return *this;
}

bool Rectangle::operator==(const Rectangle &other) const
{
    return ((Utils::eqDouble((a - b).abs(), (other.a - other.b).abs()) ||
             Utils::eqDouble((a - b).abs(), (other.b - other.c).abs())) &&
            (Utils::eqDouble((b - c).abs(), (other.b - other.c).abs()) ||
             Utils::eqDouble((b - c).abs(), (other.a - other.b).abs())));
}
std::istream &Rectangle::input(std::istream &is)
{

    std::cout << "Input a: ";
    is >> a;
    std::cout << "\tInput b: ";
    is >> b;
    std::cout << "\tInput c: ";
    is >> c;
    std::cout << std::endl;

    d = a + c - b;

    check(a, b, c);
    return is;
};

std::ostream &Rectangle::print(std::ostream &os) const
{
    os << "Rectangle have coordinates:" << std::endl;
    os << a;
    os << b;
    os << c;
    os << d << std::endl;
    return os;
}

Point Rectangle::calcCentrRotation()
{
    Point CentrRotation = (a + b + c + d) * (1.0 / 4.0);
    return CentrRotation;
};

Rectangle::operator double()
{
    Point ab = b - a;
    Point bc = b - c;
    double width = ab.abs();
    double lenght = bc.abs();
    return (width * lenght);
};

std::ostream &operator<<(std::ostream &os, const Rectangle &rectangle)
{
    return rectangle.print(os);
};

std::istream &operator>>(std::istream &is, Rectangle &rectangle)
{
    return rectangle.input(is);
};