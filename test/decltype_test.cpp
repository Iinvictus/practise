/**
 * @file decltype_test.cpp
 * @author your name (you@domain.com)
 * @brief decltype test
 * @version 0.1
 * @date 2021-11-20
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <iostream>

template <typename T1, typename T2>
T2 add1(T1 a, T2 b) {
    return a + b;
}

template <typename T1, typename T2>
auto add2(T1 a, T2 b) -> decltype(a + b) {
    return a + b;
}

int main() {
    std::cout << typeid(add1(1, 1.8)).name() << add1(1, 1.8) << '\n';
    std::cout << typeid(add1(1.8, 1)).name() << add1(1.8, 1) << '\n';

    std::cout << typeid(add2(1, 1.8)).name() << add2(1, 1.8) << '\n';
    std::cout << typeid(add2(1.8, 1)).name() << add2(1.8, 1) << '\n';
}