//생성자 위임 (Delegating constructors)
//      같은 클래스 내에서 생성자가 다른 생성자를 호출하는 것
//      특정 멤버만 다양한 값으로 초기화 하고 싶을 때 사용

#include <iostream>
using namespace std;

class Student
{
private:
    int m_id;
    string m_name;

public:
    Student(const string& name_in)
        : Student(0, name_in)           // 위임 생성자
    {}

    Student(const int& id_in, const string& name_in)
        : m_id(id_in), m_name(name_in)
    {}
};

// init 멤버 함수
//      모든 멤버들을 싹 다 초기화 해주는 멤버 함수를 만들고 생성자마다 이를 각각 다르게 호출하는 방법

class Student
{
private:
    int m_id;
    string m_name;

public:
    Student(const string& name_in)
        // : Student(0, name_in)
    {
        init(0, name_in);
    }

    Student(const int& id_in, const string& name_in)
        // : m_id(id_in), m_name(name_in)
    {
        init(id_in, name_in);
    }

    void init(const int& id_in, const string& name_in))
    {
        m_id = id_in;
        m_name = name_in;
    }
};

//Init() 함수는 멤버 변수의 값을 할당할 뿐이다. 
//이 방식으로는 const 또는 reference 변수와 같이 초기값이 필요한 멤버를 초기화할 수 없다.