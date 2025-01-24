//객체 선언과 함수 선언을 구별하자.

#include <iostream>
using namespace std;

class SimpleClass
{
	int num1;
	int num2;
public:
	SimpleClass(int n1 = 0, int n2 = 0)		//생성자
	{
		num1 = n1; num2 = n2;
	}
	void ShowData()							//맴버함수
	{
		cout << num1 << ' ' << num2 << endl;
	}
};

int main(void)
{
	SimpleClass sc;						// 객체 생성. //기본 생성자
	SimpleClass sc = SimpleClass();		// 객체 생성. 

	SimpleClass sc();					// 함수의 선언 !!! ***

	SimpleClass mysc = sc1();
	mysc.ShowData();
	return 0;
}

SimpleClass sc1()						// SimpleClass 리턴하는 함수
{
	SimpleClass sc(20, 30);				// 클래스 객체 생성
	return sc;
}


//클래스의 const 함수 ------------------------------------------------------------

class SimpleClass
{
	int num1;
	int num2;
public:
	SimpleClass(int n1 = 0, int n2 = 0)
	{
		num1 = n1; num2 = n2;
	}
	void ShowData() const		//const 함수 //맴버값 변경하지 않음 ***
	{
		cout << num1 << ' ' << num2 << endl;

		num1++;					//error
	}
};