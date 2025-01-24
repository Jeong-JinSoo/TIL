//클래스 멤버 변수 초기화
//	변수 초기화를 하지 않으면 쓰래기값으로 설정됨, 초기화 하자. 

#include <iostream>
using namespace std;

struct MyStruct
{
	int val;
};

class MyClass
{
public:
	int val;
};

int main(void)
{
	MyStruct mystruct;
	cout << mystruct.val << endl;			//error

	MyClass myclass;
	cout << myclass.val << endl;			//error

	return 0;
}


//클래스 멤버 변수 초기화 방법 3가지 ------------------------------------------------------
//	1) 멤버변수 정의시 초기화 하기
//	2) 생성자에서 초기화 하기
//	3) 생성자에서 초기화 리스트로 초기화 하기 ( 맴버 이니셜라이저 )

class ClassA {
public:
	int var1 = 10;									//1.멤버변수 정의시 초기화	

	initClass() {
		var1 = 10;									//2.생성자에서 초기화 // Default 생성자 
	}

	initClass(int var) {							//2.생성자에서 초기화 // 생성자 오버로딩
		var1 = var;
	}

	initClass(int v1, int v2) : var1(v1), var2(v2)	//3.초기화 리스트 사용 
	{}
};

//초기화 우선 순위(메모리 할당, 처리 순서) ------------------------------------------

class Something
{
private:
	int m_i - 100;							// 1번 
	double m_d = 12.34;
public:
	Something() : m_i{ 10 }, m_d{ 3.14 }	// 2번 
	{
		m_i = 3;							// 3번
		m_d = 3.0f;
	}
}
//우선순위는 1번 < 2번 < 3번 순서이다. ***

//생성자 멤버 초기화 목록 -------------------------------------------------------------

class Something
{
private:
	int m_i;
	double m_d;
	char m_c;
	int m_arr[5];

public:
	Something() : m_i{ 10 }, m_d{ 3.14 }, m_c{ 'a' }, m_arr{ 1, 2, 3, 4, 5 }	// { } 초기화
	{
		//
	}
}

//다른 클래스를 멤버로 가질 때 --------------------------------------------------------

class ABC
{
private:
	int m_abc;
public:
	ABC(const int& n) : m_abc = n { 
	}
}

class Something
{
private:
	int m_i;
	double m_d;
	char m_c;
	int m_arr[5];
	ABC abc;		//다른 클래스 타입의 객체를 멤버로 가질 때

public:
	Something()
		: m_i{ 10 }, m_d{ 3.14 }, m_c{ 'a' }, m_arr{ 1, 2, 3, 4, 5 }, abc{ m_i - 1 }
		//ABC의 생성자를 불러와 ABC abc{9}; 으로 넘어가게 된다. abc(9)
	{ }
}



//상속 받은 클래스의 경우 처리 순서 ---------------------------------------

//생성자의 인수를 받는 부분
//생성자 초기화 리스트 부분
//		메모리를 할당 받는다.
//		부모 생성자를 호출한다. 부모로부터 상속받은 멤버들을 초기화
//자신의 생성자{} 중괄호 부분 처리
//		자신만의 멤버들을 초기화한다.

//1 메모리 할당(생성자 초기화 리스트에 있는 자기 자신 멤버들은 쓰레기값만 들어있는 상태)
//2 부모 생성자 호출(물려 받은 멤버는 할당 + 초기화까지 완료)
//3 초기화(생성자 초기화 리스트에 있는 자기 자신 멤버들 초기화)
//4 자신의 생성자 내부 { } 중괄호 부분 처리