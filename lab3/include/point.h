#pragma once 
#include <iostream> 
#include <fstream> 
#include <math.h> 

class Point { 
    private: 
        double x; 
        double y; 

    public: 
        Point (); 
        Point (double xValue, double yValue); 
        Point (double value); 
        Point (const Point &other); 
        Point& operator= (const Point &other);
        Point &operator= (Point &&other); 
        Point operator+ (const Point &other) const; 
        Point operator- (const Point &other) const; 
        Point operator* (double number) const;
        double operator* (const Point &other) const;
        bool operator== (const Point &other) const;
        double abs (); 
        double getX (); 
        double getY (); 

        friend std::ostream& operator<< (std::ostream& os, const Point &point); 
        friend std::istream& operator>> (std::istream& is, Point &point); 
}; 

std::ostream& operator<< (std::ostream& os, const Point &point); 
std::istream& operator>> (std::istream& is, Point &point);