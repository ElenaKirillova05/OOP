#pragma once 
#include <iostream>
#include "point.h"
#include "utils.h"
#include "concepts.h"


template <Integral T>
class Figure{
    public:
        virtual Point<double> calcCentrRotation() = 0;
        virtual operator double() = 0;
        virtual std::ostream& print (std::ostream& os) const = 0;
        virtual std::istream& input (std::istream& is) = 0;
        virtual ~Figure() {};

        friend std::ostream& operator<< (std::ostream& os, const Figure<T> &figure){
            return figure.print(os);
        };
        friend std::istream& operator>> (std::istream& is, Figure<T> &figure){
            return figure.input(is);
        };
};