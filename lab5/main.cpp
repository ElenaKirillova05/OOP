#include "include/vector.h"
#include "include/memory.h"
#include <iostream>
#include <string>

struct ComplexType {
    int id;
    std::string name;

    ComplexType(int id, std::string name) : id(id), name(std::move(name)) {}
};

int main() {
    MemoryResource memory_resource;

    // Пример с простыми типами
    Vector<int> intVector(&memory_resource);
    intVector.push_back(10);
    intVector.push_back(20);
    intVector.push_back(30);

    std::cout << "Integer Vector: ";
    for (int value : intVector) {
        std::cout << value << " ";
    }
    std::cout << std::endl;

    // Пример со сложными типами
    Vector<ComplexType> complexVector(&memory_resource);
    complexVector.push_back(ComplexType(1, "Alice"));
    complexVector.push_back(ComplexType(2, "Bob"));

    std::cout << "Complex Vector:" << std::endl;
    for (const auto& obj : complexVector) {
        std::cout << "ID: " << obj.id << ", Name: " << obj.name << std::endl;
    }

    return 0;
}