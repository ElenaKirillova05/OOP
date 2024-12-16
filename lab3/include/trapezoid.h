#pragma once
#include <iostream>
#include "figure.h"
#include "point.h"
#include "utils.h"

class Trapezoid : public Figure
{
private:
    Point a;
    Point b;
    Point c;
    Point d;
    void check(Point aPoint, Point bPoint, Point cPoint, Point dPoint);
    void isIsosceles(Point aPoint, Point bPoint, Point cPoint, Point dPoint);

public:
    Trapezoid();
    Trapezoid(Point aPoint, Point bPoint, Point cPoint, Point dPoint);
    Trapezoid(const Trapezoid &other);
    Trapezoid(Trapezoid &&other);
    Trapezoid &operator=(const Trapezoid &other);
    Trapezoid &operator=(Trapezoid &&other);
    bool operator==(const Trapezoid &other) const;

    Point calcCentrRotation() override;
    operator double() override;
    std::ostream &print(std::ostream &os) const override;
    std::istream &input(std::istream &is) override;

    friend std::ostream &operator<<(std::ostream &os, const Trapezoid &trapezoid);
    friend std::istream &operator>>(std::istream &is, Trapezoid &trapezoid);
};

std::ostream &operator<<(std::ostream &os, const Trapezoid &trapezoid);
std::istream &operator>>(std::istream &is, Trapezoid &trapezoid);