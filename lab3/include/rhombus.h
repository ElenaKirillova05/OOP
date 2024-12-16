#pragma once
#include <iostream>
#include "figure.h"
#include "point.h"
#include "utils.h"

class Rhombus : public Figure
{
private:
    Point a;
    Point b;
    Point c;
    Point d;
    void check(Point aPoint, Point bPoint, Point cPoint);

public:
    Rhombus();
    Rhombus(Point aPoint, Point bPoint, Point cPoint);
    Rhombus(const Rhombus &other);
    Rhombus(Rhombus &&other);
    Rhombus &operator=(const Rhombus &other);
    Rhombus &operator=(Rhombus &&other);
    bool operator==(const Rhombus &other) const;

    Point calcCentrRotation() override;
    operator double() override;
    std::ostream &print(std::ostream &os) const override;
    std::istream &input(std::istream &is) override;

    friend std::ostream &operator<<(std::ostream &os, const Rhombus &rhombus);
    friend std::istream &operator>>(std::istream &is, Rhombus &rhombus);
};

std::ostream &operator<<(std::ostream &os, const Rhombus &rhombus);
std::istream &operator>>(std::istream &is, Rhombus &rhombus);