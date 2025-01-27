//this 포인터
//		this 포인터는 this가 사용된 객체 자신의 주소값을 정보로 담고 있는 포인터

#include <iostream>
#include <cstring>
using namespace std;

class CTest
{
	int num;
public:
	CTest(int n) : num(n)
	{
		cout << "num=" << num << ", ";
		cout << "address=" << this << endl; //히든 파라미터, 자신을 가르키는 포인터.
	}

	void ShowData()
	{
		cout << num << endl;
	}

	CTest* GetThisPointer()
	{
		return this;
	}
};

int main(void)
{
	CTest sim1(100);
	CTest* ptr1 = sim1.GetThisPointer();		//this의 주소값을 얻어온다.
	cout << ptr1 << ", ";						//출력하면 동일
	ptr1->ShowData();

	CTest sim2(200);
	CTest* ptr2 = sim2.GetThisPointer();
	cout << ptr2 << ", ";
	ptr2->ShowData();
	return 0;
}