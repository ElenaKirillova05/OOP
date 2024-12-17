#pragma once 
#include <concepts>


template <class T> 
concept Integral = std::is_arithmetic_v<T> && std::is_signed_v<T> && requires (T a) { 
    std::is_same_v<T, char> || std::is_same_v<T, bool> || std::is_same_v<T, char16_t> || std::is_same_v<T, char32_t>; 
};