//상수의 참조자도 가능

#include <iostream>
using namespace std;

int main(void)
{
	const int& refnum = 7;				//const 값 참조

	return 0;
}

//상수 참조(const reference)
//		const 값에 대한 포인터를 선언하는 것처럼 const 값에 대한 참조를 선언할 수 있다.
//		const& 의 경우 상수(임시값)이 참조하는 동안 유지되게 된다.
int main(void)
{
	const int value = 5;
	const int& ref = value; // ref is a reference to const value

	// const 참조는 non-const 값, const 값 및 r-value로 초기화할 수 있다.

	int x = 5;
	const int& ref1 = x;	// okay, x is a non-const l-value 

	const int y = 7;
	const int& ref2 = y;	// okay, y is a const l-value 

	const int& ref3 = 6;	// okay, 6 is an r-value
}

//상수의 참조자 //매개변수로 사용하면, 상수와 변수 모두 전달 가능

void ConstRetFunc(const int& ref)
{
	cout << ref << endl;			//ref 변경은 불가
}

int main(void)
{
	int num = 1;
	ConstRetFunc(num); 
	ConstRetFunc(7);
}

// 함수 호출에 const 사용하기 *** ------------------------------------------------
//		함수 사용할때 참조변수를 변경을 하지 않을 거라면 const 를 붙여 명확히 하자.
//		함수 사용할때 구분이 가능, 안심하고 사용할 수 있다.

void func(const int& val)	// 함수의 원형 선언만 봐도 값의 변경이 일어나지 않음을 판단 // 상수 전달도 가능
{
	cout << val;
}

// const 참조 매개 변수를 사용하여 const l-value, non-const l-value, 리터럴 및 표현식을 전달할 수 있다.

void printIt(const int& x) { }


//C++은 세 가지 종류의 참조형을 지원한다. *** ------------------------------------
// 
// non-const 값 참조형
// const 값 참조형
// r-value 참조형
{
	int d = 10;			//값 할당		// type l-value = r-value;

	int& r = d;			//l-value 참조	// 주소를 가지고 있는 것들.
	const int& cr = 5;	//const l-value 참조 // 상수값 수명 연장.
	int&& rr = 5;		//r-value 참조	// 임시객체에 대한 참조 //상수, 곧 사라질 대상.
}