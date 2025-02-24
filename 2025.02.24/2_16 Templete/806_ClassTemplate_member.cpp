//멤버 함수를 한 번 더 템플릿화하기
//		클래스 템플릿에 있는 멤버 함수를 또 다시 템플릿화할 수 있다.

#include <iostream>
using namespace std;

template <typename T>
class A
{
    T    value_;
public:
    A(const T& input) : value_(input) { }
    
    void print() {
        cout << value_ << endl;
    }

    template <typename TT>      // 멤버 함수 템플릿
    void doSomething() {
        cout << typeid(T).name() << " " << typeid(TT).name() << endl;
    }
};

int main()
{
    A<int> a_int(123);
    a_int.print();
    a_int.doSomething<float>();
}


//char 타입을 int 타입으로 형변환하여 출력하기

#include <iostream>
using namespace std;

template <typename T>
class A
{
    T value_;
public:
    A(const T& input) : value_(input) {}

    void print() {
        cout << value_ << endl;
    }

    template <typename TT>
    void doSomething(const TT& input) {                     //
        cout << typeid(T).name() << " to " << typeid(TT).name() << endl;
        cout << (TT)value_ << endl;
    }
};

int main()
{
    A<char> a_char('A');
    a_char.print();
    a_char.doSomething(int());

    //함수 템플릿은 함수명 옆에 <int>를 명시하는 대신 
    //인자로 int 타입의 값을 넣으면 파라미터가 알아서 들어간다.
}