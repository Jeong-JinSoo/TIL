// 객체의 크기를 출력해 보기 

#include <iostream>
using namespace std;

class CTest
{
	int num;
public:
	CTest() : num(0) {
	}
	CTest(int n) : num(n) {
	}
	void ShowData()	{
		cout << num << endl;
	}
};

int main(void)
{
	CTest x;
	cout << sizeof(x) << endl; // ??
}


//클래스의 크기는 맴버 변수의 사이즈 이다. ***

//함수의 크기는 객체의 크기와 무관하다. ***

//구조체 맴버 맞춤(struct member alignment)에 의해 크기가 맴버의 크기 합과 다를 수도 있다.
//	구조체가 가진 자료형 중 가장 큰 자료형이 기준이 되어 메모리에 공간이 잡힌다.
//	구조체에 선언된 변수의 순서대로 메모리에 저장한다
//	#pragma pack(push, 1)와 #pragma pack(pop)를 사용한다.
//	#pragma pack(push, 1)를 사용하게 되면 구조체의 기본 단위가 1byte가 된다

	struct Test1
	{
		char a;
		short c;
		int b;
	};

	struct Test2
	{
		char a;
		int b;
		short c;
	};

	int main()
	{
		cout << sizeof(Test1) << endl;
		cout << sizeof(Test2) << endl;

		return 0;
	}

// virtual 선언하면 사이즈가 증가한다. (가상테이블의 포인터 사이즈)


/*

//----------------------------------------------------------------------
//클래스 또는 구조체가 사이즈 0이 될 경우 서로 다른 2개의 인스턴스가 같은 주소를 가질 수 있게 되므로, 
//텅 빈 클래스 또는 구조체라도 최소 1바이트 이상의 크기를 가진다. (C++)

#include <iostream>
using namespace std;

class Class {
};

int main() {
	Class objClass;
	cout << "Size of object is = " << sizeof(objClass) << endl;
	cout << "Address of object is = " << &objClass << endl;
	return 0;
}
//----------------------------------------------------------------------
//개체가 차지하는 메모리가 데이터 멤버와 기본 멤버의 합계임

template <typename T>
class CPoint {
public:
	T m_x;
	T m_y;
};

int main() {
	CPoint<int> objPoint;
	cout << "Size of object is = " << sizeof(objPoint) << endl;
	cout << "Address of object is = " << &objPoint << endl;
	return 0;
}
//----------------------------------------------------------------------
#include <iostream>
using namespace std;

class CPoint {
public:
	int m_ix;
	int m_iy;
	virtual ~CPoint() { };		//가상 함수 추가
};

int main() {
	CPoint objPoint;
	cout << "Size of Class = " << sizeof(objPoint) << endl;
	cout << "Address of Class = " << &objPoint << endl;
	return 0;
}

//----------------------------------------------------------------------
//가상 함수를 클래스에 추가할 때마다 가상 포인터가 메모리 구조의 첫 번째 위치에 추가된다
//가상 포인터는 가상 테이블이라고 하는 테이블의 주소를 저장

#include <iostream>
using namespace std;

class CPoint {
public:
	int m_ix;
	int m_iy;
	CPoint(const int p_ix = 0, const int p_iy = 0) :
		m_ix(p_ix), m_iy(p_iy) {
	}
	int getX() const {	return m_ix; }
	int getY() const {	return m_iy; }
	virtual ~CPoint() { };
};

int main() {
	CPoint objPoint(5, 10);

	int* pInt = (int*)&objPoint;
	*(pInt+1) = 100;	// want to change the value of x
	*(pInt+2) = 200;	// want to change the value of y

	cout << "X = " << objPoint.getX() << endl;
	cout << "Y = " << objPoint.getY() << endl;

	return 0;
}
//----------------------------------------------------------------------


*/
