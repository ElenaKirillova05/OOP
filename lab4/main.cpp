#include <iostream>
#include "include/point.h"
#include "include/rhombus.h"
#include "include/trapezoid.h"
#include "include/rectangle.h"
#include "include/array.h"
#include "include/utils.h"

int main()
{
    Array<Figure<double>*> figures;
    figures.append(new Rhombus<double>(Point(0.0, 0.0), Point(1.0, 0.0), Point(1.0, 1.0)));
    figures.append(new Rectangle<double>(Point(0.0, 0.0), Point(2.0, 0.0), Point(2.0, 1.0)));
    figures.append(new Rectangle<double>(Point(1.0, 0.0), Point(2.0, 0.0), Point(2.0, 1.0)));
    figures.append(new Trapezoid<double>(Point(0.0, 0.0), Point(3.0, 4.0), Point(5.0, 4.0), Point(8.0, 0.0)));
    double totalArea = 0.0;
    for (int i = 0; i < figures.getSize(); i++)
    {
        std::cout << "Figure's index: " << i << std::endl;
        std::cout << *figures[i];
        std::cout << "Rotation center: " << figures[i]->calcCentrRotation() << std::endl;
        std::cout << "Area: " << static_cast<double>(*figures[i]) << std::endl;
        
        totalArea += static_cast<double>(*figures[i]);
    }
    std::cout << "Total area is " << totalArea << std::endl;
    std::cout << std::endl;

    figures.deleteOnIndex(2);
    double newTotalArea = 0.0;
    for (int i = 0; i < figures.getSize(); i++)
    {
        std::cout << "Figure's index: " << i << std::endl;
        std::cout << *figures[i];
        std::cout << "Rotation center: " << figures[i]->calcCentrRotation() << std::endl;
        std::cout << "Area: " << static_cast<double>(*figures[i]) << std::endl;
        
        newTotalArea += static_cast<double>(*figures[i]);
    }
    std::cout << "Total area is " << newTotalArea << std::endl;
    std::cout << std::endl;
    Array<Rectangle<int>> recs;
    recs.append(Rectangle<int>(Point(0, 0), Point(4, 0), Point(4, 2)));
    recs.append(Rectangle<int>(Point(1, 0), Point(2, 0), Point(2, 1)));
    recs.append(Rectangle<int>(Point(0, 0), Point(5, 0), Point(5, 2)));
    recs.append(Rectangle<int>(Point(0, 0), Point(0, 5), Point(3, 5)));
    double totalAreaRecs = 0.0;
    for (int i = 0; i < figures.getSize(); i++)
    {
        std::cout << "Rectangles's index: " << i << std::endl;
        std::cout << recs[i];
        std::cout << "Rotation center: " << recs[i].calcCentrRotation() << std::endl;
        std::cout << "Area: " << static_cast<double>(recs[i]) << std::endl;
        totalAreaRecs += static_cast<double>(recs[i]);
    }
    std::cout << "Total area is " << totalAreaRecs << std::endl;
    std::cout << std::endl;
    std::cin >> recs[0];
    double newTotalAreaRecs = 0.0;
    for (int i = 0; i < recs.getSize(); i++)
    {
        std::cout << "Rectangles's index: " << i << std::endl;
        std::cout << recs[i];
        std::cout << "Rotation center: " << recs[i].calcCentrRotation() << std::endl;
        std::cout << "Area: " << static_cast<double>(recs[i]) << std::endl;
        newTotalAreaRecs += static_cast<double>(recs[i]);
    }
    std::cout << "Total area is " << newTotalAreaRecs << std::endl;
    std::cout << std::endl;
}