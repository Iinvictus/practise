/**
 * @file test.cpp
 * @author your name (you@domain.com)
 * @brief 测试
 * @version 0.1
 * @date 2021-11-18
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <iostream>
#include <memory>

class Entity {
 public:
    Entity() { std::cout << "Entity()" << '\n'; }
    Entity(const Entity&) { std::cout << "Entity(const Entity&)" << '\n'; }
    Entity(Entity&&) { std::cout << "Entity(Entity&&)" << '\n'; }
};

Entity simple() {
    // 直接将 entity 构造在调用者的栈中
    Entity entity;
    return entity;
}

Entity simpleWithMove() {
    // move 影响了返回值优化
    Entity entity;
    return std::move(entity);
}

Entity simpleWithCondition(int n) {
    // 因为有两个entity，无法将其构造在调用方的栈中
    Entity entity1;
    Entity entity2;
    if (n % 2) return entity1;
    return entity2;
}

void test_const_cast() {
    // 用于调用非const但对指针参数没有副作用的第三方方法时，临时去除const属性
    const int a1 = 10;
    const int *b1 = &a1;
    int *c1 = const_cast<int*>(b1);
    *c1 = 20;  // Invalid and Undefined Behavior!
    std::cout << "*c1:" << *c1 << " *b1:" << *b1 << " a1:" << a1 << '\n';

    int a2 = 10;
    const int *b2 = &a2;
    int *c2 = const_cast<int*>(b2);
    *c2 = 20;  // Valid
    std::cout << "*c2:" << *c2 << " *b2:" << *b2 << " a2:" << a2 << '\n';
}

void test_return() {
    std::cout << "----------simple----------\n";
    auto entity1 = simple();
    std::cout << "----------simpleWithMove----------\n";
    auto entity2 = simpleWithMove();
    std::cout << "----------simpleWithCondition----------\n";
    auto entity3 = simpleWithCondition(42);
}

void test_move() {
    // TODO(zhuifeng): test different between unique_ptr and make_unique
    // std::unique_ptr<int> ptr1 = std::unique_ptr<int>(new int (10));
    std::unique_ptr<int> ptr1 = std::make_unique<int>(10);
    std::cout << *ptr1 << '\n';
    std::unique_ptr<int> ptr2 = std::move(ptr1);
    std::cout << "ptr1 is " << (ptr1 ? "not nullptr" : "empty") << '\n';
    std::cout << *ptr2 << '\n';
}

int main() {
    test_const_cast();
}