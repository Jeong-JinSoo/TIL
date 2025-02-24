/* stacknontype.hpp */
//#pragma once
#include <array>
#include <cassert>

template<typename T, std::size_t Maxsize>
class Stack
{
private:
    std::array<T, Maxsize> elems; // elements
    std::size_t numElems = 0;         // current number of elements

public:
    Stack();
    void push(T const& elem);
    void pop();
    T const& top() const;
    bool empty() const { return numElems == 0; }
    std::size_t size() const {  return numElems; }
};

template<typename T, std::size_t Maxsize>
Stack<T, Maxsize>::Stack() : numElems(0) {}

template<typename T, std::size_t Maxsize>
void Stack<T, Maxsize>::push(T const& elem)
{
    assert(numElems < Maxsize);
    elems[numElems] = elem;
    ++numElems;
}

template<typename T, std::size_t Maxsize>
void Stack<T, Maxsize>::pop()
{
    assert(!elems.empty());
    --numElems;
}

template<typename T, std::size_t Maxsize>
T const& Stack<T, Maxsize>::top() const
{
    assert(!elems.empty());
    return elems[numElems - 1];
}

//#include "stacknontype.hpp"
#include <iostream>
#include <string>

int main()
{
    Stack<int, 20> int20Stack;          // stack of up to 20 ints
    Stack<int, 40> int40Stack;          // stack of up to 40 ints
    Stack<std::string, 40> stringStack; // stack of up to 40 strings

    // manipulate stack of up to 20 ints
    int20Stack.push(7);
    std::cout << int20Stack.top() << '\n';
    int20Stack.pop();

    // manipulate stack of up to 40 strings
    stringStack.push("hello");
    std::cout << stringStack.top() << '\n';
    stringStack.pop();
}