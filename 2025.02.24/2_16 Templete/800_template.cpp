// 제네릭 프로그래밍 (generic programming)
//		데이터 형식에 의존하지 않고, 
//		하나의 값이 여러 다른 데이터 타입들을 가질 수 있는 기술에 중점을 두어 
//		재사용성을 높일 수 있는 프로그래밍 방식이
// 
// 템플릿 : C++에서 제네릭 프로그래밍을 위해 제공하는 핵심 도구
//		코드를 재사용할 수 있게 작성

#include <iostream>
using namespace std;


// 자료형만 다른 여러 함수 // 너무 많은 오버로드 
int Add(int num1, int num2) {	return num1 + num2; }
float Add(float num1, float num2) { return num1 + num2; }
double Add(double num1, double num2) { return num1 + num2; }

// 템플릿으로 자료형(형식)에 따라 생성해서 사용하라. ***

// 템플릿 (함수 템플릿) 선언 및 정의
//		<매개변수> 로 형식을 받아서 처리 - 형식 매개변수 (Type Parameter)

template <typename T>	//T 는 '형식 매개변수'  //template <class T> 도 같은 표현 ***
T Add(T num1, T num2)
{
	return num1 + num2;
}

int main(void)
{
	Add<int>(1, 2);						//int 형식으로 사용 ***
	cout << Add<double>(2.9, 3.7) << endl;	// <> 생략가능  // 전달되는 인수로 추정 

	cout << Add(15, 20) << endl;		// 컴파일러는 이를 다음과 같이 해석한다. Add<int>(15, 20);
	cout << Add(3.2f, 3.2f) << endl;	// Add<float>
	cout << Add(3.14, 2.75) << endl;	// Add<double>

	return 0;
}

/*
//함수 템플릿과 템플릿 함수를 구분하라 -------------------------------------------------------

//함수 템플릿 : 템플릿 정의

	template <typename T>		
	T Add(T num1, T num2)
	{
		return num1 + num2;
	}

//템플릿 함수 : 컴파일러가 생성하는 템플릿 기반의 함수

	Add(1, 1);							//사용하면    // 컴파일할 때 

	int Add<int>(int num1, int num2)	//템플릿 함수생성 (템플릿 구체화) - 인스턴스화
	{
		return num1 + num2;
	}	
*/

//템플릿 인스턴스화(구체화) ---------------------------------------------------------------
//		컴파일러가 템플릿에서 클래스 또는 함수를 생성하는 프로세스를 템플릿 인스턴스화(구체화)라고 합니다 

//템플릿 인스턴스화(template instantiation) 
//      컴파일러가 함수(클래스) 틀(Template)로 부터 실제 C++ 함수(클래스)를 만들어 내는 과정 
// 
//      함수가 호출(사용)되면 ***
//		컴파일러는 ***
//		모든 인스턴스를 T 사용자가 지정하거나 컴파일러에서 추론하는 구체적인 형식 인수로 바꿉니다.


//템플릿으로 바꿔보세요. ----------------------

void Print(int n) { cout << n < endl; }

//template <typename T>
//void Print(T n) { cout << n < endl; }

//템플릿으로 바꿔보세요. ----------------------

int Max(int lhs, int rhs) {
	return (lhs > rhs ? lhs : rhs);
}

//template <typename T>
//T Max(T lhs, T rhs) {
//	return (lhs > rhs ? lhs : rhs);
//}