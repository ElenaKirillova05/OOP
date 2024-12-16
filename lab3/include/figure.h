#pragma once 
#include <iostream>
#include "point.h"
#include "utils.h"

class Figure{
    public:
        virtual Point calcCentrRotation() = 0;
        virtual operator double() = 0;
        virtual std::ostream& print (std::ostream& os) const = 0;
        virtual std::istream& input (std::istream& is) = 0;
        virtual ~Figure() {};

        friend std::ostream& operator<< (std::ostream& os, const Figure &figure);
        friend std::istream& operator>> (std::istream& is, Figure &figure);
};

std::ostream& operator<< (std::ostream& os, const Figure &figure);
std::istream& operator>> (std::istream& is, Figure &figure);