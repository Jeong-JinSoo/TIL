//객체의 멤버 포인터
#include <iostream>

class A {
public:
	int n;
	A(int n) : n(n) {}
};

int main() {
	int A::* pn = &A::n;	// 맴버데이타에 대한 포인터  //객체생성 전에 선언 가능

	A a(3);
	std::cout << "a.n   : " << a.n << std::endl;
	std::cout << "a.*pn : " << a.*pn << std::endl;
}

//일반 멤버함수는 포인터에 어떻게 넣지? --------------------------------------------

// 핵심 1. 일반함수 포인터에 멤버함수의 주소를 담을 수 없다.
// 핵심 2. 일반 함수 포인터에 static 멤버함수의 주소를 담을 수 있다.
// 핵심 3. 멤버 함수 포인터 모양과 사용법 .*   

#include <iostream>
using namespace std;

class Dialog
{
public:
    void Close() { cout << "Close" << endl; }
};

void foo(int a) { cout << a << endl; }

int main()
{
    void(*f1)(int) = foo;
    //void(*f1)(int) = &foo;                    //이것도 허용됨
    f1(1);
    //(*f1)(1);                                 //ok

    //void(*f2)() = &Dialog::Close;             //error this 가 추가되는 함수
    void(Dialog:: * f2)() = &Dialog::Close;      //멤버함수 포인터
    //f2();                                     //error 객체(this)가 없다.

    Dialog dlg;
    //dlg.f2();         //dlg.Close의 의미 하지만 f2라는 멤버를 찾게 된다.
    //dlg.*f2()         //".*" Pointer to mementer operator 연산자 우선순위 문제..
    (dlg.*f2)();

}

/*
//원래 클래스 안에서 선언된 변수는 클래스 범위연산자가 생략
class A
{
    int a;                //int A::a;
}


void foo() {} ;

class A
{
    void (*p1)();         // 서로 다른 의미의 선언 (외부 함수를 가르킬수 있는 포인터 변수)
    //void (*A::p1)();    // 위의 void (*p)();의 선언과 동일합니다 아래와 혼동하지 마시길...
    void (A::* p2)();     // 서로 다른 의미의 선언 (A클래스의 멤버 함수를 가르킬수 있는 포인터 변수)

    vodi print1() { }

    void Init()
    {
        p1 = foo;         //정상작동
        p2 = &A::print1;  //정상작동
    }
}
*/