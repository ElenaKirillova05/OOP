#pragma once 
#include <iostream> 
#include <fstream> 
#include <math.h> 
#include <concepts>
#include "utils.h"
#include "concepts.h"

template <Integral T>
class Point { 
    private: 
        T x; 
        T y; 

    public: 
        Point() : x{0}, y{0} {}
        Point(T xValue, T yValue) : x{xValue}, y{yValue} {}
        Point(T value) : Point(value, value) {}
        Point(const Point<T> &other) : Point(other.x, other.y) {}

        Point<T> &operator=(const Point<T> &other)
        {
            if (this == &other)
                return *this;
            x = other.x;
            y = other.y;
            return *this;
        }


        Point<T> &operator= (Point<T> &&other){
            x = other.x;
            y = other.y;
            return *this;
        }

        bool operator==(const Point<T> &other) const
        {
            return (Utils::eqDouble(x, other.x) && Utils::eqDouble(y, other.y));
        }

        Point<T> operator+(const Point<T> &other) const
        {
            return Point(x + other.x, y + other.y);
        }

        Point<T> operator-(const Point<T> &other) const
        {
            return Point(x - other.x, y - other.y);
        }

        Point<T> operator*(T number) const
        {
            return Point(number * x, number * y);
        }

        T operator*(const Point &other) const
        {
            return (x * other.x + y * other.y);
        }

        double abs()
        {
            return sqrt(x * x + y * y);
        }

        T getX()
        {
            return x;
        }

        T getY()
        {
            return y;
        }

        friend std::ostream &operator<<(std::ostream &os, const Point<T> &point)
        {
            os << "(" << point.x << "; " << point.y << ")";
            return os;
        }

        friend std::istream &operator>>(std::istream &is, Point<T> &point)
        {
            T x, y;

            std::cout << "(Input x: ";
            is >> x;
            std::cout << " Input y: ";
            is >> y;
            std::cout << ")" << std::endl;

            point.x = x;
            point.y = y;

            return is;
    } 
    }; 