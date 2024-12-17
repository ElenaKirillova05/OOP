#pragma once
#include <iostream>
#include "figure.h"
#include "point.h"
#include "utils.h"
#include "concepts.h"
#include <memory>


template <Integral T>
class Trapezoid : public Figure<T>
{
    private:
        std::unique_ptr<Point<T>> a{nullptr};
        std::unique_ptr<Point<T>> b{nullptr};
        std::unique_ptr<Point<T>> c{nullptr};
        std::unique_ptr<Point<T>> d{nullptr};
        void isInscribed(Point<T> aPoint, Point<T> bPoint, Point<T> cPoint, Point<T> dPoint){
                Point<T> ab = aPoint - bPoint;
                Point<T> bc = bPoint - cPoint;
                Point<T> cd = cPoint - dPoint;
                Point<T> ad = aPoint - dPoint;
                if (!(Utils::eqDouble(ab.abs() + cd.abs(), bc.abs()+ ad.abs())))
                {   
                    std::cout << ab.abs() << " " << cd.abs() << " " << bc.abs() << " " << ad.abs() << std::endl;
                    throw std::invalid_argument("Invalid coordinates, it can't be inscribed into a circle");
                }
            };
        void check(Point<T> aPoint, Point<T> bPoint, Point<T> cPoint, Point<T> dPoint){
            Point<T> ab = bPoint - aPoint;
            Point<T> bc = bPoint - cPoint;
            Point<T> cd = cPoint - dPoint;
            Point<T> ad = aPoint - dPoint;
            Point<T> ac = aPoint - cPoint;
            Point<T> bd = bPoint - dPoint;
            double diagonal1 = ac.abs();
            double diagonal2 = bd.abs();
            bool isParallel_ab_cd(Utils::eqDouble(ab * cd, (ab.abs() * cd.abs())));
            bool isParallel_bc_ad(Utils::eqDouble(bc * ad, (bc.abs() * ad.abs())));
            if (!(isParallel_ab_cd ^ isParallel_bc_ad) || Utils::eqDouble(diagonal1, 0.0) || Utils::eqDouble(diagonal2, 0.0))
            {
                throw std::invalid_argument("Invalid coordinates, it can't be a Trapezoid");
            }
            isIsosceles(aPoint, bPoint, cPoint, dPoint);
        };
        void isIsosceles(Point<T> aPoint, Point<T> bPoint, Point<T> cPoint, Point<T> dPoint)
        {
            Point<T> ab = aPoint - bPoint;
            Point<T> bc = bPoint - cPoint;
            Point<T> cd = cPoint - dPoint;
            Point<T> ad = aPoint - dPoint;
            if ((!Utils::eqDouble(ab.abs(), cd.abs())) && (!Utils::eqDouble(bc.abs(), ad.abs())))
            {
                throw std::invalid_argument("Invalid coordinates, it can't be inscribed into a circle");
            }
        };
    protected:
        std::istream &input(std::istream &is) override
        {
            Point<T> Pointa, Pointb, Pointc, Pointd;
            std::cout << "Input a: ";
            is >> Pointa;
            std::cout << "\tInput b: ";
            is >> Pointb;
            std::cout << "\tInput c: ";
            is >> Pointc;
            std::cout << "\tInput d: ";
            is >> Pointd;
            std::cout << std::endl;
            check(Pointa, Pointb, Pointc, Pointd);
            *a = Pointa;
            *b = Pointb;
            *c = Pointc;
            *d = Pointd;
            return is;
        };

        std::ostream &print(std::ostream &os) const override
        {
            os << "Trapezoid have coordinates:" << std::endl;
            os << *a;
            os << *b;
            os << *c;
            os << *d << std::endl;

            return os;
        };
    public:
        Trapezoid() : a(std::make_unique<Point<T>>()), b(std::make_unique<Point<T>>(1.0)), c(std::make_unique<Point<T>>(2.0, 1.0)), d(std::make_unique<Point<T>>(3.0, 0.0)) {}

        Trapezoid(Point<T>& aPoint, Point<T>& bPoint, Point<T> &cPoint, Point<T>& dPoint){
        check(aPoint, bPoint, cPoint, dPoint);
        a = std::make_unique<Point<T>>(aPoint);
        b = std::make_unique<Point<T>>(bPoint);
        c = std::make_unique<Point<T>>(cPoint);
        d = std::make_unique<Point<T>>(dPoint); 
        }

        Trapezoid(Point<T>&& aPoint, Point<T>&& bPoint, Point<T>&& cPoint, Point<T>&& dPoint){
        check(aPoint, bPoint, cPoint, dPoint);
        a = std::make_unique<Point<T>>(aPoint);
        b = std::make_unique<Point<T>>(bPoint);
        c = std::make_unique<Point<T>>(cPoint);
        d = std::make_unique<Point<T>>(dPoint); 
        }

        Trapezoid(const Trapezoid& other) 
        : a(std::make_unique<Point<T>>(*other.a)), b(std::make_unique<Point<T>>(*other.b)), c(std::make_unique<Point<T>>(*other.c)), d(std::make_unique<Point<T>>(*other.d)) {}


        Trapezoid(Trapezoid &&other) : Trapezoid() {
            a = std::move(other.a);
            b = std::move(other.b);
            c = std::move(other.c);
            d = std::move(other.d);
        }

        Trapezoid &operator=(const Trapezoid &other)
        {
            if (this == &other)
                return *this;
            *a = *other.a;
            *b = *other.b;
            *c = *other.c;
            *d = *other.d;
            return *this;
        }

        Trapezoid &operator=(Trapezoid &&other) noexcept
        {   
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

        bool operator==(const Trapezoid &other) const
        {
            return (Utils::eqDouble((*a - *b).abs(), (*other.a - *other.b).abs()) && Utils::eqDouble((*b - *c).abs(), (*other.b - *other.c).abs()) &&
                    Utils::eqDouble((*c - *d).abs(), (*other.c - *other.d).abs()) && Utils::eqDouble((*a - *d).abs(), (*other.a - *other.d).abs()));
        }


        Point<double> calcCentrRotation() override
        {
            Point<double> aDouble(a->getX(),a->getY());
            Point<double> bDouble(b->getX(),b->getY());
            Point<double> cDouble(c->getX(),c->getY());
            Point<double> dDouble(d->getX(),d->getY());
            Point<double> CentrRotation = (aDouble + bDouble + cDouble + dDouble) * (1.0 / 4.0);
            return CentrRotation;
        };

        operator double() override
        {
            double ab = (*b - *a).abs();
            double bc = (*b - *c).abs();
            double cd = (*c - *d).abs();
            double ad = (*a - *d).abs();
            double ac = (*a - *c).abs();
            double bd = (*b - *d).abs();
            double Sabc = Utils::STriangle(ab, bc, ac);
            double Sacd = Utils::STriangle(ad, cd, ac);
            return (Sabc + Sacd);
        };

        friend std::ostream &operator<<(std::ostream &os, const Trapezoid &trapezoid)
        {
            return trapezoid.print(os);
        };

        friend std::istream &operator>>(std::istream &is, Trapezoid &trapezoid)
        {
            return trapezoid.input(is);
        };
        };