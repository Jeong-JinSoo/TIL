#include <iostream>
using namespace std;

void TestFunc(int)
{}

void main(void)
{
	//초기화 ----------------------------------------
	int a = 1;
	int a(1);	//C++
	int a{ 1 };	//C++11

	int b(a);	//copy
	int(10);	//이름없는 인스턴스

	//auto -----------------------------------  

	auto c(a);	

	//auto 활용 1
	//void(*pfTest)(int) = TestFunc;
	auto pfTest(TestFunc);		//형 자동 설정
		 
	//auto 활용 2
	int buffer[5] = { 0,1,2,3,4 };
	for (auto i : buffer)			//형 자동 설정
	{
		cout << i << endl;
	}

	//r-value 참조 ---------------------------
	int d = 10;			//값 할당		// l-value = r-value;
	int &r = d;			//l-value 참조	// 주소를 가지고 있는 것들.
	const int& cr = 5;	//const l-value 참조 // 상수값 수명 연장.
	int &&rr = 5;		//r-value 참조 // 임시객체에 대한 참조 //상수, 곧 사라질 대상.
}
