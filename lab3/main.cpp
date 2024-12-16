#include <iostream>
#include "include/point.h"
#include "include/figure.h"
#include "include/rhombus.h"
#include "include/rectangle.h"
#include "include/trapezoid.h"
#include "include/utils.h"

void addFigure(Figure **figures, int size);
void deleteFigure(Figure **figures, int size);
void printInfo(Figure **figures, int size);
void getTotalArea(Figure **figures, int size);

int main()
{
    int size;
    std::cout << "Input array size: " << std::endl;
    std::cin >> size;

    Figure **figures = new Figure *[size];
    for (int i = 0; i < size; i++)
        figures[i] = nullptr;

    bool work = true;

    while (work)
    {
        std::cout << "Input action index:" << std::endl;
        std::cout << "0 - Exit" << std::endl;
        std::cout << "1 - Info" << std::endl;
        std::cout << "2 - Total area" << std::endl;
        std::cout << "3 - Add figure" << std::endl;
        std::cout << "4 - Delete figure" << std::endl;

        int action;
        std::cin >> action;

        switch (action)
        {
        case 0:
            std::cout << "Good Bye!" << std::endl;
            work = false;
            break;

        case 1:
            printInfo(figures, size);
            break;

        case 2:
            getTotalArea(figures, size);
            break;

        case 3:
            addFigure(figures, size);
            break;
        case 4:
            deleteFigure(figures, size);
            break;

        default:
            std::cout << "Unknown action: " << action << std::endl;
        }
    }

    for (int i = 0; i < size; i++)
        delete figures[i];
    delete[] figures;

    return 0;
}

void addFigure(Figure **figures, int size)
{
    Figure *figureToAdd = nullptr;

    bool work = true;

    while (work)
    {
        std::cout << "Input figure type to add: " << std::endl;
        std::cout << "0 - Cancel" << std::endl;
        std::cout << "1 - Rectangle" << std::endl;
        std::cout << "2 - Rhombus" << std::endl;
        std::cout << "3 - Trapezoid" << std::endl;

        int figureType;
        std::cin >> figureType;

        bool skip = false;

        switch (figureType)
        {
        case 0:
            return;

        case 1:
            figureToAdd = new Rectangle;
            break;

        case 2:
            figureToAdd = new Rhombus;
            break;

        case 3:
            figureToAdd = new Trapezoid;
            break;

        default:
            std::cout << "Unknown figure type: " << figureType << std::endl;
            skip = true;
        }

        if (skip)
            continue;

        try
        {
            std::cin >> *figureToAdd;
            work = false;
        }
        catch (const std::exception &error)
        {
            delete figureToAdd;
            std::cout << error.what() << std::endl;
        }
    }

    int index = -1;
    while (index < 0 || index >= size)
    {
        std::cout << "Input index from 0 to " << (size - 1) << ": ";
        std::cin >> index;
    }

    delete figures[index];
    figures[index] = figureToAdd;

    std::cout << "Figure is successfully added" << std::endl;
}

void deleteFigure(Figure **figures, int size)
{
    int index = -1;
    while (index < 0 || index >= size)
    {
        std::cout << "Input index from 0 to " << (size - 1) << ": ";
        std::cin >> index;
    }

    if (figures[index] == nullptr)
    {
        std::cout << "No figure by index " << index << std::endl;
        return;
    }

    delete figures[index];

    for (int i = index; i < size - 1; i++)
    {
        figures[i] = figures[i + 1];
    }

    figures[size - 1] = nullptr;

    std::cout << "Figure successfully deleted, other figures were moved on its place" << std::endl;
}

void printInfo(Figure **figures, int size)
{
    std::cout << "Figures (empty places are skipped): " << std::endl;

    for (int i = 0; i < size; i++)
    {
        if (figures[i] == nullptr)
            continue;
        std::cout << "Figure's index:" << i << std::endl;
        std::cout << *figures[i];
        std::cout << "Rotation center: " << figures[i]->calcCentrRotation() << std::endl;
        std::cout << "Area: " << static_cast<double>(*figures[i]) << std::endl;
    }
}

void getTotalArea(Figure **figures, int size)
{
    
    for (int i = 0; i < size; i++)
    {
        if (figures[i] == nullptr)
            continue;
        double totalArea = 0.0;
        totalArea += static_cast<double>(*figures[i]);
    }
    std::cout << "Total area is " << totalorder << std::endl;
}