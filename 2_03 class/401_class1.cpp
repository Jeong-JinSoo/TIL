//접근 제어자 (Access Modifier)
// 
// class 맴버 접근 -  private, public 

#include <iostream>
using namespace std;

class ClassName  	     //키워드 class
{
    int n = 0;          //멤버 변수
    void func() {}      //멤버 함수
}


class MyClass  	        //키워드 class  // MyClass 라는 새로운 자료형
{		                //중괄호 - 클래스 선언의 시작과 끝
private:	            //접근지정자 - 자신의 클래스에서 사용 가능, private 이 기본.
    int num1 = 0;	    //멤버변수 - 클래스를 구성하는 멤버변수의 선언
public:		            //접근지정자 - 클래스 외부에서 제어를 가능하도록 하기 위한 public 
    int num2 = 0;
    void Show();	    //멤버함수 - 클래스를 구성하는 멤버함수의 원형 선언
};		                //세미콜론 - 클래스 선언의 마침을 알리는 세미콜론

void MyClass::Show()    //클래스 외부에 멤버함수 정의하기 // 범위지정연산자 ::  ***
{
    cout << num1 << endl;
}

int main()
{
    MyClass myclass;    //클래스 객체 선언    
    myclass.Show();     //객체의 맴버 접근     // private public 변경해 보자.
    cout << myclass.num1 << endl;
    cout << myclass.num2 << endl;
    
	return 0;
}

//C++ 언어에서는 
//      클래스 안에 정의한 속성들을 '데이터 멤버'(data member)라고 부르고, 
//      메소드를 '멤버 함수'(member function)라고 부른다.

//멤버 초기화는
//      = 연산자를 이용한 복사 초기화 방식  int x = 5;  을 지원
//      {}를 이용한 유니폼 초기화 방식    int x{ 5 };  을 지원하지만
//      ()를 이용한 직접 초기화방식은 지원하지 않는다.
