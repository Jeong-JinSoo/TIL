// nested_class_template1.cpp //MSDN

#include <iostream>
using namespace std;

class X
{
    template <class T>                  //template
    struct Y {
        T m_t;
        Y(T t) : m_t(t) { }
    };

    Y<int> yInt;
    Y<char> yChar;

public:
    X(int i, char c) : yInt(i), yChar(c) { }
    void print() {
        cout << yInt.m_t << " " << yChar.m_t << endl;
    }
};

int main()
{
    X x(1, 'a');
    x.print();
}


// nested_class_template2.cpp// compile with: /EHsc

#include <iostream>
using namespace std;

template <class T>                      //template
class X
{
    template <class U> class Y          //template
    {
        U* u;
    public:
        Y();
        U& Value();
        void print();
        ~Y();
    };

    Y<int> y;
public:
    X(T t) { y.Value() = t; }
    void print() { y.print(); }
};

template <class T>
template <class U>
X<T>::Y<U>::Y() {
    cout << "X<T>::Y<U>::Y()" << endl;
    u = new U();
}

template <class T>
template <class U>
U& X<T>::Y<U>::Value() {
    return *u;
}

template <class T>
template <class U>
void X<T>::Y<U>::print() {
    cout << this->Value() << endl;
}

template <class T>
template <class U>
X<T>::Y<U>::~Y() {
    cout << "X<T>::Y<U>::~Y()" << endl;
    delete u;
}

int main()
{
    X<int>* xi = new X<int>(10);
    X<char>* xc = new X<char>('c');
    xi->print();
    xc->print();
    delete xi;
    delete xc;
}

