//call by reference	//참조 전달 

#include <iostream>
using namespace std;

void SwapByRef2(int &ref1, int& ref2)
{
	int temp = ref1;
	ref1 = ref2;
	ref2 = temp;
}

int main(void)
{
	int val1 = 10;
	int val2 = 20;

	SwapByRef2(val1, val2); //매개변수의 형태로 구분하지 말자
	cout << "val1: " << val1 << endl;
	cout << "val2: " << val2 << endl;
	return 0;
}

/*
// 절대값을 구하는 함수 작성하기 -------------

	#include <iostream>
	using namespace std;

	void absolute(int &a)	// 참조 호출
	{
		if (a < 0) a = -a;
	}
	void absolute(int *a)	// 주소 호출
	{
		if (*a < 0) *a = -(*a);
	}

	int main(void)
	{
		int a = -1;

		cout << a << endl;

		absolute(a);	// 1번 참조 호출
		cout << a << endl;

		absolute(&a);	// 2번 주소 호출
		cout << a << endl;

		return 0;
	}


// 함수 오버로드의 경우 주의 

#include <iostream>
using namespace std;

void func(int a) { }
void func(int& a) { }

int main(void)
{
	int a = 1;

	func(a);		//error

	return 0;
}

*/