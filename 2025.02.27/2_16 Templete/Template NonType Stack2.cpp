﻿/* stackauto.hpp */
#pragma once
#include <array>
#include <cassert>

template<typename T, auto Maxsize>
class Stack
{
public:
    using size_type = decltype(Maxsize);

private:
    std::array<T, Maxsize> elems;
    size_type numElems;

public:
    Stack();
    void push(T const& elem);
    void pop();
    T const& top() const;
    bool empty() const {
        return numElems == 0;
    }
    size_type size() const {
        return numElems;
    }
};

template<typename T, auto Maxsize>
Stack<T, Maxsize>::Stack() : numElems(0) {}

template<typename T, auto Maxsize>
void Stack<T, Maxsize>::push(T const& elem)
{
    assert(numElems < Maxsize);
    elems[numElems] = elem;
    ++numElems;
}

template<typename T, auto Maxsize>
void Stack<T, Maxsize>::pop()
{
    assert(!elems.empty());
    --numElems;
}

template<typename T, auto Maxsize>
T const& Stack<T, Maxsize>::top() const
{
    assert(!elems.empty());
    return elems[numElems - 1];
}

//#include "stackauto.hpp"
#include <iostream>
#include <string>

int main()
{
    Stack<int, 20u> int20Stack;
    Stack<std::string, 40> stringStack;

    int20Stack.push(7);
    std::cout << int20Stack.top() << '\n';
    auto size1 = int20Stack.size();

    stringStack.push("hello");
    std::cout << stringStack.top() << '\n';
    auto size2 = stringStack.size();

    if (!std::is_same_v<decltype(size1), decltype(size2)>) {
        std::cout << "size types differ\n";
    }
}