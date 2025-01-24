//이니셜라이저를 이용한 변수 및 상수의 초기화 (콜론 초기화)

//맴버 초기화 리스트를 사용해야만 하는 경우 ***
//	1. 상수 맴버 초기화	 ( C++11 이전 ) 
//	2. 레퍼런스 맴버 초기화
//	3. 객체 맴버 초기화
//	4. 부모클래스의 맴버 초기화

//const 변수나 reference 변수의 경우 선언과 동시에 초기화 한다. (대상이 있어야 하므로)

//멤버변수로 참조자 선언하기	//const int& - 상수의 초기화

#include <iostream>
using namespace std;

class MyClass
{
public:
	int val;
	const int& num;
	//const int& num = 1;
};

int main(void)
{
	MyClass myclass;

	return 0;
}

//-----------------------------------------------------

#include <iostream>
using namespace std;

class ClassA
{
public:
	ClassA() { cout << "ClassA" << endl; }
	~ClassA() { cout << "~ClassA" << endl; }
	void Show() { cout << "ClassA Show" << endl; }
};

class ClassB
{
private:
	ClassA& ref;										//레퍼런스 맴버 //멤버변수로 참조자 선언하기
	const int& num;

public:
	ClassB(ClassA& r, const int& n) : ref(r), num(n)	//이니셜라이저를 이용한 참조변수 및 상수의 초기화
	{
		//ref = r;	//선언이 아님
		//num = n;	//변경 불가 
	}
	~ClassB() { cout << "~ClassB" << endl; }

	void Show()
	{
		ref.Show();	// ClassA::Show()
	}
};
/*
ClassB::ClassB(ClassA& r, const int& n) : ref(r), num(n)	// 정의부에 명시한다
{
}
*/
int main(void)
{
	ClassA obj1;
	obj1.Show();

	ClassB obj2(obj1, 20);
	obj2.Show();			//obj1 클래스 소멸시 오류 발생할수 있음, 주의

	return 0;
}



//참조의 경우는 선언할때 대상이 필요하다. 
//		초기화리스트를 이용한 초기화로 가능하다. ***

//이니셜라이저를 이용한 변수 및 상수의 초기화
//		멤버 이니셜라이저는 함수의 선언부가 아닌, 정의부에 명시한다.***
//		선언과 동시에 초기화 -> const, 참조형도 가능

//멤버 초기화 리스트에서만 가능한 것이 있기도 하고,
//int, bool 과 같이 primitive 자료형에서는 초기화, 대입의 성능 차이가 크지는 않지만,
//사용자가 정의한 타입의 경우에는 초기화, 대입의 비용이 많이 차이가 날 수 있다.
// 
//결론, 생성자 내부에서 초기화하는 것보다, 멤버 초기화 리스트를 사용하자. ***
