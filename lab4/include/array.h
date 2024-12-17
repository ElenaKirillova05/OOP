#pragma once 
#include <iostream>
#include "point.h"
#include "utils.h"
#include "concepts.h"
#include <stdexcept>

template <class T>
class Array{
    private:
        static const std::size_t DEFAULT_EXTEND = 10;
        static constexpr bool IS_ARRAY_OF_PTR = std::is_pointer_v<T>;
        std::size_t size;
        std::size_t capacity;

        std::unique_ptr<T[]> data{nullptr};

        void extend(){
            if (capacity == 0){
                data = std::make_unique<T[]>(DEFAULT_EXTEND);
                capacity = DEFAULT_EXTEND;
                return;
            }
            if (capacity < 1000){
                capacity += capacity;}
            else capacity += 500;
            std::unique_ptr<T[]> newData = std::make_unique<T[]>(capacity);
            for (int i = 0; i < size; i++){
                newData[i] = std::move(data[i]);
            }
            if constexpr (IS_ARRAY_OF_PTR) freeLinks();
            data.reset();
            data = std::move(newData);
        }
    public:
        Array(): size{0}, capacity{0}{}
        Array(const Array<T> &other){
            capacity = other.capacity;
            size = other.size;
            if (other.capacity == 0) return;
            data = std::make_unique<T[]>(other.capacity);
            for (int i = 0; i < other.size; i++){
                data[i] = other.data[i];
            }
        }
        Array(Array<T> &&other){
            data = std::move(other.data);
            size = other.size;
            capacity = other.capacity;

            other.size = 0;
            other.capacity = 0;
        }
        Array<T>& operator= (const Array<T> &other){
            if (this != &other) {
            if constexpr (IS_ARRAY_OF_PTR) freeLinks();
            data.reset();

            size = other.size;
            capacity = other.capacity;

            if (other.capacity == 0) return *this;
            data = std::make_unique<T[]>(other.capacity);
            for (int i = 0; i < other.size; i++){
                data[i] = other.data[i];
            }}
            return *this;
        }
        Array<T>& operator= (Array<T> &&other){
            if (capacity != 0){
                if constexpr (IS_ARRAY_OF_PTR) freeLinks();
                data.reset();
            }
            data = std::move(other.data);
            size = other.size;
            capacity = other.capacity;

            other.size = 0;
            other.capacity = 0;

            return *this;
        }

        bool operator== (const Array<T> &other){
            if (size != other.size) return false;
            for (int i = 0; i < size; i++){
                if (data[i] != other.data[i]) return false;
            }
            return true;
        }

        ~Array () {
            if constexpr (IS_ARRAY_OF_PTR) freeLinks();
        };

        T& operator[] (std::size_t index) {
            if (index >= size){
                throw std::out_of_range("The index out of range of elements");
            }
            return data[index];
        }

        const T& operator[](std::size_t index) const {
        if (index >= size) {
            throw std::out_of_range("Index out of range of elements");
        }
        return data[index];
    }
        void append(T &newElement){
            if (size >= capacity) extend();
            data[size] = newElement;
            size++;
        }

        void append(T &&newElement){
            if (size >= capacity) extend();
            data[size] = std::move(newElement);
            size++;
        }


        void append(const Array<T> &other){
            while (size + other.size - 1 >= capacity) extend();
            int index = 0;
            for (std::size_t i = size; i < size + other.size; i++){
            data[i] = other.data[index];
            size++;
            index++;
            }
        }

        void deleteOnIndex (std::size_t index) {
            if (index >= size){
                throw std::out_of_range("Index out of range of elements");
            }
    
            if constexpr (IS_ARRAY_OF_PTR) delete data[index];
            for (int i = index; i < size - 1; i++){
            data[index] = std::move(data[index + 1]);}
            size--;
        }

        void freeLinks(){
            for (int i = 0; i < size; i++){
                delete data[i];
            }
        }

        std::size_t getSize() const{
             return size; 
        }
};