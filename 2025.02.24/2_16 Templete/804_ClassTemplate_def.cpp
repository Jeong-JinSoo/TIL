//클래스 템플릿(Class template)

//템플릿과 타입의 차이
//    Complex    : 템플릿 틀 자체
//    Complex<T> : 실제 타입 ***

//멤버 함수안에서는 Complex<T> 대신 Complex를 사용할 수 있다.

/*
    #include <iostream>
    using namespace std;

    template<typename T> class Complex
    {
        T re, im;
    public:
        void foo(Complex c)  // 멤버 함수에서는 OK(Complex<T> 동급으로 취급)
        {
        }
    };

    void foo(Complex c)      // 일반 함수에서는 Error
    {
    }

    void foo(Complex c)
    {
        Complex c1;         // Error
        Complex<int> c2;    // OK
    }

*/

//템플릿 관련 표기법 ---------------------------------------

//  디폴트 값 표기 ***
//      int a = 0;
//      T a = T(); // C++ 98/03
//      T a = {};  // C++11
// 
//  static memeber data 외부 표기
//  멤버 함수를 외부에 표기// 
//  클래스 템플릿의 '멤버 함수 템플릿' 표기

#include <iostream>
using namespace std;

template<typename T> class Complex
{
    T re, im;
public:
    Complex(T a = {}, T b = {}) : re(a), im(b) { }     // 디폴트 값 표기  

    static int cnt;                                     // static 멤버 데이터

    T getReal() const;                                  // 멤버 함수

    template<typename U> T func(const U& c);            // 멤버 함수 템플릿
};

// static 멤버 데이터 외부 구현
template<typename T>
int Complex<T>::cnt = 0;


// 멤버 함수 외부 구현
template<typename T>
T Complex<T>::getReal() const {
    return re;
}

// 클래스 템플릿의 멤버 함수 템플릿 구현
template<typename T> template<typename U>
T Complex<T>::func(const U& c) {
}

int main()
{
    Complex<int> c2;
}