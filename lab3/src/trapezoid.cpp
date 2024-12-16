#include <iostream>
#include <cmath>
#include <limits>
#include <stdexcept>
#include "../include/trapezoid.h"
#include "../include/point.h"
#include "../include/utils.h"

void Trapezoid::check(Point aPoint, Point bPoint, Point cPoint, Point dPoint)
{
    Point ab = bPoint - aPoint;
    Point bc = bPoint - cPoint;
    Point cd = cPoint - dPoint;
    Point ad = aPoint - dPoint;
    Point ac = aPoint - cPoint;
    Point bd = bPoint - dPoint;
    double diagonal1 = ac.abs();
    double diagonal2 = bd.abs();
    bool isParallel_ab_cd(Utils::eqDouble(ab * cd, (ab.abs() * cd.abs())));
    bool isParallel_bc_ad(Utils::eqDouble(bc * ad, (bc.abs() * ad.abs())));
    if (!(isParallel_ab_cd ^ isParallel_bc_ad) || Utils::eqDouble(diagonal1, 0.0) || Utils::eqDouble(diagonal2, 0.0))
    {
        throw std::invalid_argument("Invalid coordinates, it can't be a Trapezoid");
    }
};

Trapezoid::Trapezoid() : a{Point()}, b{Point(1.0)}, c{Point(2.0, 1.0)}, d{Point(3.0, 0.0)} {};

Trapezoid::Trapezoid(Point aPoint, Point bPoint, Point cPoint, Point dPoint) : a{aPoint}, b{bPoint}, c{cPoint}, d{dPoint}
{
    check(aPoint, bPoint, cPoint, dPoint);
};

void Trapezoid::isIsosceles(Point aPoint, Point bPoint, Point cPoint, Point dPoint)
{
    Point ab = aPoint - bPoint;
    Point bc = bPoint - cPoint;
    Point cd = cPoint - dPoint;
    Point ad = aPoint - dPoint;
    if ((!Utils::eqDouble(ab.abs(), cd.abs())) && (!Utils::eqDouble(bc.abs(), ad.abs())))
    {
        throw std::invalid_argument("Invalid coordinates, center can't be found");
    }
};

Trapezoid::Trapezoid(const Trapezoid &other) : Trapezoid(other.a, other.b, other.c, other.d) {}
Trapezoid::Trapezoid(Trapezoid &&other) : Trapezoid(other.a, other.b, other.c, other.d) {}

Trapezoid &Trapezoid::operator=(const Trapezoid &other)
{
    if (this == &other)
        return *this;
    a = other.a;
    b = other.b;
    c = other.c;
    d = other.d;
    return *this;
}

Trapezoid &Trapezoid::operator=(Trapezoid &&other)
{
    a = other.a;
    b = other.b;
    c = other.c;
    d = other.d;
    return *this;
}

bool Trapezoid::operator==(const Trapezoid &other) const
{
    return (Utils::eqDouble((a - b).abs(), (other.a - other.b).abs()) && Utils::eqDouble((b - c).abs(), (other.b - other.c).abs()) &&
            Utils::eqDouble((c - d).abs(), (other.c - other.d).abs()) && Utils::eqDouble((a - d).abs(), (other.a - other.d).abs()));
}

std::istream &Trapezoid::input(std::istream &is)
{

    std::cout << "Input a: ";
    is >> a;
    std::cout << "\tInput b: ";
    is >> b;
    std::cout << "\tInput c: ";
    is >> c;
    std::cout << "\tInput d: ";
    is >> d;
    std::cout << std::endl;

    return is;
};

std::ostream &Trapezoid::print(std::ostream &os) const
{
    os << "Trapezoid have coordinates:" << std::endl;
    os << a;
    os << b;
    os << c;
    os << d << std::endl;

    return os;
};

Point Trapezoid::calcCentrRotation()
{
    isIsosceles(a, b, c, d);
    Point CentrRotation = (a + b + c + d) * (1.0 / 4.0);
    return CentrRotation;
};

Trapezoid::operator double()
{
    double ab = (b - a).abs();
    double bc = (b - c).abs();
    double cd = (c - d).abs();
    double ad = (a - d).abs();
    double ac = (a - c).abs();
    double bd = (b - d).abs();
    double Sabc = Utils::STriangle(ab, bc, ac);
    double Sacd = Utils::STriangle(ad, cd, ac);
    return (Sabc + Sacd);
};

std::ostream &operator<<(std::ostream &os, const Trapezoid &trapezoid)
{
    return trapezoid.print(os);
};

std::istream &operator>>(std::istream &is, Trapezoid &trapezoid)
{
    return trapezoid.input(is);
};