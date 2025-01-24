// 참조 전달과 반환 -------------------------------------------------------------

#include <iostream>
using namespace std;

int& RefRetFuncOne(int& ref)			//참조자로 리턴, 자신을 지정.
{
	ref++;
	return ref;
}

int RefRetFuncTwo(int& ref)				//값 리턴
{
	ref++;
	return ref;
}

int main(void)
{
	int  num1 = 1;

	int& num2 = RefRetFuncOne(num1);	// &num2는 num1과 같은 주소값
	//int num2 = RefRetFuncOne(num1);	// 참조로 리턴하지만 받지 않음.
	 
	//int  num2 = RefRetFuncTwo(num1);  // 값 복사
	//int& num2 = RefRetFuncTwo(num1);  // error //int& 에 int 값을 할당할 수 없음. rvalue

	num1++;
	num2++;
	cout << "num1: " << num1 << endl;
	cout << "num2: " << num2 << endl;

	//-----------------------------------------------------------------------

	RefRetFuncOne(num1) = 3;			// OK, 함수의 반환값이 num1 자신이다.
	cout << "num1: " << num1 << endl;

	return 0;
}

/*
//참조자가 아닌 값을 리턴하는 함수를 참조자로 받기 ------------------------------

	int function() {
		int a = 5;
		return a;
	}

	int main() {
		int& c = function();        //컴파일 에러
		const int& c = function();  //상수 참조자로 받으면 컴파일 가능
		return 0;
	}

	//지역변수 a 는 함수의 리턴과 함께 소멸되기 때문에, 
	//계속 참조할 수가 없다. (Dangling reference)
*/

