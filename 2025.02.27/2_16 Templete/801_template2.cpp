//둘 이상의 형(Type)에 대해 템플릿 선언하기

#include <iostream>
using namespace std;

template <class T1, class T2>	//형식매개변수는 여러개 정의하는 것이 가능하다.
void ShowData(double num)
{
	cout << (T1)num << ", " << (T2)num << endl;
}

int main(void)
{
	ShowData<char, int>(65);
	ShowData<char, int>(67);
	ShowData<char, double>(68.9);
	ShowData<short, double>(69.2);
	ShowData<short, double>(70.4);

	return 0;
}

/*

// 형식매개변수의 자동 추론   //T, U 연산의 결과에 따라 자동으로 결정

template <typename T, typename U>
decltype(auto) Max(T lhs, U rhs) {	return (lhs > rhs ? lhs : rhs); }

int main(void)
{
	cout << Max(1, 1.2);    //int, double  
	return 0;
}

*/