//레퍼런스를 리턴하는 함수

#include <iostream>

using std::cout;
using std::endl;

int& increment(int& val)		//레퍼런스를 리턴
{
	val++;
	return val;
}

int main(void)
{
	int n = 10;
	int& ref = increment(n);     //참조인지 알려면 함수의 원형 선언 확인해야 한다
	cout << " n : " << n << endl;
	cout << "ref: " << ref << endl;
	return 0
}


/*
//레퍼런스를 리턴하는 잘못된 형태의 함수

	#include <iostream>
	using std::cout;
	using std::endl;

	int& function(void)
	{
		int val = 10;
		return val;		//지역변수는 레퍼런스로 리턴 할 수 없다
	}

	int main(void)
	{
		int &ref = function();
		cout << ref << endl;
		return 0;
	}
*/
