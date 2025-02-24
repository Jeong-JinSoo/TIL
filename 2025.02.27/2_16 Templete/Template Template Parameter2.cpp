#include <iostream>
#include <string>
#include <deque>

//템플릿 인수로 템플릿 전달 -----------------------------------------------

template <typename T, typename Container>
class Stack
{
private:
    Container m_Container;

public:
    // You can use forwarding reference for the better performance
    void Push(T const& value) {}
    // Some member functions
    // ...
};

int main()
{    
    Stack<int, std::deque<int>> stack;

    // the element type 'int' is specified twice
}


//템플릿 템플릿 파라미터 -----------------------------------------------

template <typename T, template <typename> class Container = std::deque>
class Stack
{
private:
    Container<T> m_Container;

public:
    // You can use forwarding reference for the better performance
    void Push(T const& value) {}

    // Some member functions
    // ...
};

int main()
{
    Stack<int, std::deque> stack;
}