//C++14 //C++17
 
//Nontype Class Template Parameters -----------------------------------------------------------------
// 
//  지난 포스팅의 스택 구현과는 달리 크기가 고정된 배열을 사용하도록 스택을 구현할 수 있습니다.
//  이런 경우에는 프로그래머나 표준 컨테이너가 수행해야하는 메모리 관리 측면에서 이점이 있습니다.
//  다만, 스택에 맞는 크기를 결정하는 것은 매우 어렵습니다.
//  크기가 작으면 메모리가 빨리 가득 찰 것이고, 크기가 너무 크다면 메모리가 낭비될 수 있습니다.
//  따라서, 가장 좋은 방법은 스택을 만들 때 필요한 최대 크기를 명시하도록 하는 것 입니다.
//  이를 위해서 스택의 최대 크기를 템플릿 파라미터로 정의할 수 있습니다.

/* stacknontype.hpp */
#pragma once
#include <array>
#include <cassert>

template<typename T, std::size_t Maxsize>
class Stack
{
private:
    std::array<T, Maxsize> elems; // elements
    std::size_t numElems;         // current number of elements

public:
    Stack();
    void push(T const& elem);
    void pop();
    T const& top() const;
    bool empty() const {
        return numElems == 0;
    }
    std::size_t size() const {
        return numElems;
    }
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

//여기서 사용된 두 번째 템플릿 파라미터 Maxsize는 스택 요소의 내부 배열 크기를 나타냅니다.
//이 템플릿 파라미터는 push()에서 스택이 가득 찼는지 검사할 때도 사용됩니다.

//이 클래스를 사용하려면 요소의 타입뿐만 아니라 최대 크기로 명시해주어야 합니다.

#include "stacknontype.hpp"
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

//각 템플릿 인스턴스는 자신만의 타입을 가지므로, 
//int20Stack과 int40Stack은 서로 다른 타입입니다. 따라서 서로 간의 암묵적 또는 명시적 형 변환은 불가능합니다.

//이렇게 정의한 Stack의 템플릿 파라미터의 기본값을 명시할 수도 있습니다.

template<typename T = int, std::size_t Maxsize = 100>
class Stack {
    
};
//좋은 설계 관점에서 위에서 사용한 기본값은 적절하지 않을 수 있습니다(일반적인 스택의 의미를 생각하면).
//따라서, 프로그래머가 항상 두 인자를 명시하게 하는 편이 더 낫습니다.



//Nontype Function Template Parameters -----------------------------------------------------------------
//
//  함수 템플릿에서도 타입이 아닌 템플릿 파라미터를 정의할 수 있습니다.

#include <iostream>
#include <algorithm>
#include <vector>

template<int Val, typename T>
T addValue(T x)
{
    return x + Val;
}

int main()
{
    std::transform(source.begin(), source.end(), dest.begin(),
        addValue<5, int>);            // operation //타입을 추론하려면 완전한 타입이 필요합니다.
}

//템플릿 파라미터가 앞서 나오는 템플릿 파라미터로부터 추론된다고 지정할 수도 있습니다. 
template<auto Val, typename T = decltype(Val)>
T foo();

//전달된 값이 전달된 타입과 같은 타입을 갖도록 강제할 수도 있습니다.
template<typename T, T Val = T{} >
T bar();



//Restrictions for Nontype Template Parameters -----------------------------------------------------------------
// 
//  타입이 아닌 템플릿 파라미터에는 몇 가지 제약 사항이 있습니다.
//  일반적으로 오직 상수 정수인 값(열거형 포함)이거나, 
//  객체 / 함수 / 멤버에 대한 포인터, 객체나 함수에 대한 lvalue reference 또는 std::nullptr_t 이어야 합니다.


//부동소수점 숫자나 클래스 타입의 객체는 타입이 아닌 템플릿 파라미터로 사용될 수 없습니다.
//예를 들면, 다음과 같습니다.

template<double VAT>        // ERROR: floating-point values are not
double process(double v)    //        allowed as template parameters
{
    return v * VAT;
}

template<std::string name>  // ERROR: class-type objects are not
class MyClass {
    //allowed as template parameters
    //...
};

//포인터나 참조자를 템플릿 인자로 전달할 때, 
//객체는 문자열 리터럴(string literal), 임시 객체, 또는 멤버와 다른 하위 객체이어서는 안됩니다.

//또한, C++17 이전의 모든 C++ 버전에서는 이러한 제약 사항들이 완화되어 있기 때문에 아래와 같이 추가적인 제약 사항이 적용됩니다.
//  C++11에서 객체는 external link를 가져야 합니다
//  C++17에서 객체는 external or internal link를 가져야 합니다
//  따라서, 아래의 코드는 불가능 합니다.

template<char const* name>
class MyClass {
    //...
};

MyClass<"hello"> x;                 // ERROR: string liternal "hello" not allowed

//하지만, 아래와 같이 우회하여 사용할 순 있습니다 (C++ 버전에 따라 다르긴 합니다).

extern char const s03[] = "hi";     // external linkage
char const a11[] = "hi";            // internal linkage

int main()
{
    MyClass<s03> m03;               // OK (all version)
    MyClass<s11> m11;               // OK since C++11
    static char const s17[] = "hi"; // no linkage
    MyClass<s17> m17;               // OK since C++17
}

//main 내에서 3개의 상수 문자 배열이 모두 "hi"로 초기화되고, 이 객체가 char const* 로 선언되는 템플릿 파라미터로 사용됩니다.



//Avoiding Invalid Expressions -----------------------------------------------------------------
//
//  타입이 아닌 템플릿 파라미터를 위한 인자는 compile-time expression 이기만 하면 됩니다.
//  예를 들어, 아래와 같이 사용해야 합니다.

template<int I, bool B>
class C;
//...

C<sizeof(int) + 4, sizeof(int) == 4> c;


//그러나 아래 코드와 같이 operator>를 사용하려면 '>'가 인자 목록 끝을 나타내게 되므로 전체 표현식을 괄호로 둘러싸야 합니다.

C < 42, sizeof(int) > 4 > c;    // ERROR: first > ends the template argument list
C<42, (sizeof(int) > 4)> c;     // OK


//Template Parameter Type auto ----------------------------------------------------------------------
// 
//  C++17부터는 nontype 파라미터에 허용되는 어떠한 타입도 받아들일 수 있도록 nontype 템플릿 파라미터를 정의할 수 있습니다.
//  이 특성을 사용하면 위에서 살펴본 크기 고정 스택 클래스를 조금 더 제너릭하게 만들 수 있습니다.

/* stackauto.hpp */
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

//위의 정의처럼 placeholder type인 auto를 사용하여 정의하면 
//아직 지정되지 않은 타입의 값으로 Maxsize를 사용할 수 있습니다.
//타입이 아닌 템플릿 파라미터 타입에 허용된 어떠한 타입은 무엇이든지 여기에 사용할 수 있습니다.


//템플릿 정의 내부에서 값과 타입을 모두 사용할 수 있습니다.

    std::array<T, Maxsize> elems;
    using size_type = decltype(Maxsize);

//이러한 타입을 size()의 리턴 타입으로도 사용할 수 있습니다.

//물론, C++14에서부터는 컴파일러가 리턴 타입을 추론하도록 auto를 사용할 수도 있습니다.

    auto size() const {
        return numElems;
    }


//이렇게 정의한 클래스는 다음과 같이 사용할 수 있습니다.
//아래 코드는 std::is_same_v로 인해 C++17에서부터 컴파일 및 실행 가능합니다.

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

//여기서 int20Stack에는 20u (unsigned int)가 전달되었고, stringStack에서는 40 (int)이 전달되었습니다.
//따라서, 내부에서 사용하는 크기의 타입이 서로 다르므로, size1과 size2의 타입 또한 다릅니다.
//이는 std::is_same_v 타입 특질을 사용하여 검사하고 있으며, 출력 결과는 다음과 같습니다.


//그리고 문자열을 상수 배열로 전달할 수 있기 때문에 아래의 코드도 사용 가능합니다.

#include <iostream>

template<auto T> // take value of any possible nontype parameter (since C++17)
class Message
{
public:
    void print() {
        std::cout << T << '\n';
    }
};

int main()
{
    Message<42> msg1;
    msg1.print();       // initialize with int 42 and print that value

    static char const s[] = "hello";
    Message<s> msg2;    // initialize with char const[6] "hello"
    msg2.print();       // and print that value
}
