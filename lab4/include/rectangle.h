#pragma once
#include <iostream>
#include "figure.h"
#include "point.h"
#include "utils.h"
#include "concepts.h"
#include <memory>

template <Integral T>
class Rectangle : public Figure<T> {
private:
    std::unique_ptr<Point<T>> a;
    std::unique_ptr<Point<T>> b;
    std::unique_ptr<Point<T>> c;
    std::unique_ptr<Point<T>> d;

    void check(Point<T> aPoint, Point<T> bPoint, Point<T> cPoint) {
        Point<T> ab = bPoint - aPoint;
        Point<T> bc = bPoint - cPoint;
        Point<T> dPoint = aPoint + cPoint - bPoint;
        Point<T> ac = aPoint - cPoint;
        Point<T> bd = bPoint - dPoint;
        double diagonal1 = ac.abs();
        double diagonal2 = bd.abs();
        if (!Utils::eqDouble((ab * bc), 0) || Utils::eqDouble(diagonal1, 0.0) || Utils::eqDouble(diagonal2, 0.0)) {
            throw std::invalid_argument("Invalid coordinates, it can't be a Rectangle");
        }
    }

protected:
    std::istream& input(std::istream& is) override {
        Point<T> Pointa, Pointb, Pointc;
        std::cout << "Input a: ";
        is >> Pointa;
        std::cout << "\tInput b: ";
        is >> Pointb;
        std::cout << "\tInput c: ";
        is >> Pointc;
        std::cout << std::endl;

        Point<T> Pointd = Pointa + Pointc - Pointb;

        check(Pointa, Pointb, Pointc);

        *a = Pointa;
        *b = Pointb;
        *c = Pointc;
        *d = Pointd;

        return is;
    }

    std::ostream& print(std::ostream& os) const override {
        os << "Rectangle have coordinates:" << std::endl;
        os << *a;
        os << *b;
        os << *c;
        os << *d << std::endl;
        return os;
    }

public:
    Rectangle() : a(std::make_unique<Point<T>>()), b(std::make_unique<Point<T>>(0.0, 1.0)), c(std::make_unique<Point<T>>(1.0)), d(std::make_unique<Point<T>>(1.0, 0.0)) {}

    Rectangle(Point<T>&& aPoint, Point<T>&& bPoint, Point<T>&& cPoint) {
        Point<T> dPoint = aPoint + cPoint - bPoint;
        check(aPoint, bPoint, cPoint);
        a = std::make_unique<Point<T>>(aPoint);
        b = std::make_unique<Point<T>>(bPoint);
        c = std::make_unique<Point<T>>(cPoint);
        d = std::make_unique<Point<T>>(dPoint);
    }
    
    Rectangle(Point<T>& aPoint, Point<T>& bPoint, Point<T>& cPoint) {
        Point<T> dPoint = aPoint + cPoint - bPoint;
        check(aPoint, bPoint, cPoint);
        a = std::make_unique<Point<T>>(aPoint);
        b = std::make_unique<Point<T>>(bPoint);
        c = std::make_unique<Point<T>>(cPoint);
        d = std::make_unique<Point<T>>(dPoint);
    }


    Rectangle(const Rectangle& other) 
        : a(std::make_unique<Point<T>>(*other.a)), b(std::make_unique<Point<T>>(*other.b)), c(std::make_unique<Point<T>>(*other.c)), d(std::make_unique<Point<T>>(*other.d)) {}

    Rectangle(Rectangle&& other) noexcept 
        : a(std::move(other.a)), b(std::move(other.b)), c(std::move(other.c)), d(std::move(other.d)) {}

    Rectangle& operator=(const Rectangle& other) {
        if (this == &other)
            return *this;
        *a = *other.a;
        *b = *other.b;
        *c = *other.c;
        *d = *other.d;
        return *this;
    }

    Rectangle& operator=(Rectangle&& other) noexcept {
        a.reset();
        b.reset();
        c.reset();
        d.reset();
        a = std::move(other.a);
        b = std::move(other.b);
        c = std::move(other.c);
        d = std::move(other.d);
        return *this;
    }

    bool operator==(const Rectangle& other) const {
        return ((Utils::eqDouble((*a - *b).abs(), (*other.a - *other.b).abs()) ||
                Utils::eqDouble((*a - *b).abs(), (*other.b - *other.c).abs())) &&
                (Utils::eqDouble((*b - *c).abs(), (*other.b - *other.c).abs()) ||
                Utils::eqDouble((*b - *c).abs(), (*other.a - *other.b).abs())));
    }

    Point<double> calcCentrRotation() override {
        Point<double> aDouble(a->getX(),a->getY());
        Point<double> bDouble(b->getX(),b->getY());
        Point<double> cDouble(c->getX(),c->getY());
        Point<double> dDouble(d->getX(),d->getY());
        Point<double> CentrRotation = (aDouble + bDouble + cDouble + dDouble) * (1.0 / 4.0);
        return CentrRotation;
    }

    operator double() override {
        Point<T> ab = *b - *a;
        Point<T> bc = *b - *c;
        double width = ab.abs();
        double length = bc.abs();
        return (width * length);
    }

    friend std::ostream& operator<<(std::ostream& os, const Rectangle& rectangle) {
        return rectangle.print(os);
    }

    friend std::istream& operator>>(std::istream& is, Rectangle& rectangle) {
        return rectangle.input(is);
    }
};