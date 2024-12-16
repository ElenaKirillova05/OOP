#pragma once
#include <iostream>
#include "figure.h"
#include "point.h"
#include "utils.h"

class Rectangle : public Figure
{
private:
    Point a;
    Point b;
    Point c;
    Point d;
    void check(Point aPoint, Point bPoint, Point cPoint);

public:
    Rectangle();
    Rectangle(Point aPoint, Point bPoint, Point cPoint);
    Rectangle(const Rectangle &other);
    Rectangle(Rectangle &&other);
    Rectangle &operator=(const Rectangle &other);
    Rectangle &operator=(Rectangle &&other);
    bool operator==(const Rectangle &other) const;

    Point calcCentrRotation() override;
    operator double() override;
    std::ostream &print(std::ostream &os) const override;
    std::istream &input(std::istream &is) override;

    friend std::ostream &operator<<(std::ostream &os, const Rectangle &rectangle);
    friend std::istream &operator>>(std::istream &is, Rectangle &rectangle);
};

std::ostream &operator<<(std::ostream &os, const Rectangle &rectangle);
std::istream &operator>>(std::istream &is, Rectangle &rectangle);