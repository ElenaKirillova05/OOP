#include <iostream>
#include <cmath>
#include <limits>
#include <stdexcept>
#include "../include/rhombus.h"
#include "../include/point.h"
#include "../include/utils.h"

void Rhombus::check(Point aPoint, Point bPoint, Point cPoint)
{
    Point ab = bPoint - aPoint;
    Point bc = bPoint - cPoint;
    Point dPoint = aPoint + cPoint - bPoint;
    Point ac = aPoint - cPoint;
    Point bd = bPoint - dPoint;
    double diagonal1 = ac.abs();
    double diagonal2 = bd.abs();
    if (!Utils::eqDouble(ab.abs(), bc.abs()) || Utils::eqDouble(diagonal1, 0.0) || Utils::eqDouble(diagonal2, 0.0))
    {
        throw std::invalid_argument("Invalid coordinates, it can't be a Rhombus");
    }
};

Rhombus::Rhombus() : a{Point(1.0, 0.0)}, b{Point()}, c{Point(0.0, 1.0)}, d{Point(1.0)} {};

Rhombus::Rhombus(Point aPoint, Point bPoint, Point cPoint) : a{aPoint}, b{bPoint}, c{cPoint}, d{aPoint + cPoint - bPoint}
{
    check(aPoint, bPoint, cPoint);
}

Rhombus::Rhombus(const Rhombus &other) : Rhombus(other.a, other.b, other.c) {}
Rhombus::Rhombus(Rhombus &&other) : Rhombus(other.a, other.b, other.c) {}

Rhombus &Rhombus::operator=(const Rhombus &other)
{
    if (this == &other)
        return *this;
    a = other.a;
    b = other.b;
    c = other.c;
    d = other.d;
    return *this;
}

Rhombus &Rhombus::operator=(Rhombus &&other)
{
    a = other.a;
    b = other.b;
    c = other.c;
    d = other.d;
    return *this;
}

bool Rhombus::operator==(const Rhombus &other) const
{
    return (Utils::eqDouble((a - b).abs(), (other.a - other.b).abs()) &&
            (Utils::eqDouble((a - c).abs(), (other.a - other.c).abs()) ||
             Utils::eqDouble((a - c).abs(), (other.b - other.d).abs())));
}

std::istream &Rhombus::input(std::istream &is)
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

std::ostream &Rhombus::print(std::ostream &os) const
{

    os << "Rhombus have coordinates:" << std::endl;
    os << a;
    os << b;
    os << c;
    os << d << std::endl;
    return os;
}

Point Rhombus::calcCentrRotation()
{
    Point CentrRotation = (a + b + c + d) * (1.0 / 4.0);
    return CentrRotation;
};

Rhombus::operator double()
{
    Point ac = a - c;
    Point bd = b - d;
    double diagonal1 = ac.abs();
    double diagonal2 = bd.abs();
    return (diagonal1 * diagonal2 * 0.5);
};

std::ostream &operator<<(std::ostream &os, const Rhombus &rhombus)
{
    return rhombus.print(os);
};

std::istream &operator>>(std::istream &is, Rhombus &rhombus)
{
    return rhombus.input(is);
};