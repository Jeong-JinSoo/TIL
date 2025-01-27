//https://learn.microsoft.com/ko-kr/cpp/cpp/pointer-to-member-operators-dot-star-and-star?view=msvc-170

//멤버에 대한 포인터 연산자 : .* 및 ->*

#include <iostream>
using namespace std;

class Testpm {
public:
    void m_func1() { cout << "m_func1\n"; }
    int m_num;
};

// Define derived types pmfn and pmd.
// These types are pointers to members m_func1() and
// m_num, respectively.
void (Testpm::* pmfn)() = &Testpm::m_func1;
int Testpm::* pmd = &Testpm::m_num;

int main() {
    Testpm ATestpm;
    Testpm* pTestpm = new Testpm;

    // Access the member function
    (ATestpm.*pmfn)();
    (pTestpm->*pmfn)();   // Parentheses required since * binds
    // less tightly than the function call.

// Access the member data
    ATestpm.*pmd = 1;
    pTestpm->*pmd = 2;

    cout << ATestpm.*pmd << endl
        << pTestpm->*pmd << endl;
    delete pTestpm;
}


//상속의 경우 
// expre_Expressions_with_Pointer_Member_Operators2.cpp

class BaseClass {
public:
    BaseClass() {} // Base class constructor.
    void Func1() {}
};

class Derived : public BaseClass {
public:
    Derived() {}  // Derived class constructor.
    void Func2() {}
};

void (BaseClass::* pmfnFunc1)() = &BaseClass::Func1;
void (Derived::* pmfnFunc2)() = &Derived::Func2;

int main() {
    BaseClass ABase;
    Derived ADerived;

    (ABase.*pmfnFunc1)();   // OK: defined for BaseClass.
    //(ABase.*pmfnFunc2)();   // Error: cannot use base class to access pointers to members of derived classes.

    (ADerived.*pmfnFunc1)();   // OK: Derived is unambiguously derived from BaseClass.
    (ADerived.*pmfnFunc2)();   // OK: defined for Derived.
}