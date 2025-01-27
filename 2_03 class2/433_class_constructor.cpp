// 생성자와 소멸자

//객체선언 및 생성자 정의할 때 주의사항

//생성자
//  클래스이름과 동일한 함수이름을 사용 (멤버변수와 유사하게 매개변수를 선언)
//  리턴값이 없는 함수로 구성

//  반드시 하나 이상의 생성자가 필요, 정의 안하면 기본생성자 암시적 생성.
//  디폴트 생성자는 없고, 클래스에 적어도 하나의 생성자가 포함되어 있을 경우 
//  - 디폴트 생성자를 직접 정의해야 사용 가능.

//소멸자는 오버로드 불가, 즉 하나. 


//객체를 선언하고 초기화 할 때 괄호()를 사용함.
//  전달인자가 없는 객체를 선언할 경우는	- Func func;				
//  오해하기 쉬운 호출함수와 객체선언		- Func func() & Func func;	***


//클래스 객체의 선언과 초기화는 구조체 변수의 초기화 방식과 유사하지만 
//각각의 구조체 변수와 클래스 객체의 선언 및 초기화 형식은 아래와 같다.
//	구조체 변수의 선언 및 초기화 : Func func = { 멤버변수의 초기화 값 };
//	클래스 객체의 선언 및 초기화 : Func func(멤버변수의 초기화 값);


#include <iostream>
#include <cstring>
using namespace std;

class CTest
{
private:				//멤버변수의 외부접근을 막는 것을 가리켜 정보은닉이라 한다
	int nData;
public:
	CTest() : nData(0)	//생성자 //자동 호출,반환형식 없음 //디폴트 생성자 //new 할당시 호출
	{
		cout << "Test()" << endl;
	}
	~CTest()			//소멸자 //객체소멸 시 자동으로 호출 //디폴트 소멸자 //delete 
	{
		cout << "~Test()" << endl;
	}
};

void main(void)
{
	CTest a;					// 일반적 객체의 선언

	CTest* test = new CTest;	// 동적 생성
	delete test;	

	//CTest a = CTest();		// CTest() 임시객체
}

/*
// 전역으로 선언한 경우 ------------------------------------------

	CTest a;					//메인보다 먼저 생성되는 클래스 생성자. ***

	int main(void)
	{
		cout << "main" << endl;
		return 0;
	}

// 클래스 객체 초기화 ------------------------------------------

	class CTest
	{
	public:
		int n = 1;;
		CTest() {};
		CTest(int a) { n = a; };
	};
	int main()
	{
		CTest a;
		//CTest a();			//주의 !!
		//CTest a{};
		//CTest a = CTest();
		cout << a.n << endl;

		CTest b(2);
		//CTest b{ 2 };
		//CTest b = CTest(2);
		cout << b.n << endl;
	}

*/