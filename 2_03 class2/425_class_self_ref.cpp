//자신 참조 반환
//		자신을 그대로 반환, 연속 호출이 가능.

#include <iostream>
using namespace std;

class CTest
{
private:
	int num;
public:
	CTest(int n) : num(n)
	{
		cout << "객체생성" << endl;
	}
	CTest& Adder(int n)			//CTest& 
	{
		num += n;
		return *this;			//*this 로 반환 ***
	}
	CTest& ShowNumber()			//CTest&
	{
		cout << num << endl;
		return *this;			//*this 로 반환
	}
};

int main(void)
{
	CTest obj(3);
	CTest& ref = obj.Adder(2);		//obj 참조 리턴

	obj.ShowNumber();
	ref.ShowNumber();

	ref.Adder(1).ShowNumber().Adder(2).ShowNumber(); //자신 참조 반환

	return 0;
}
