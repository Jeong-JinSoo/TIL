//템플릿 템플릿 파라미터

#include <iostream>
using namespace std;

template <typename T>
class ClassA
{
public:
    void Show() { cout << "ClassA::Show" << endl; }
};

template <typename T, template <typename T> class Class >   //
class ClassB
{
private:
    Class<T> m_obj;
public:
    void Show() { cout << "ClassB::Show" << endl; m_obj.Show(); }
};

int main()
{
    ClassB<int, ClassA> obj; obj.Show();
}