//객체 배열  //객체의 포인터
#include <iostream>
using namespace std;

class Point
{
	int x, y;
public:

	Point(int x = 0, int y = 0)
	{
		this->x = x;
		this->y = y;
		cout << x << "," << y << endl;
	}

	Point(const Point& p)		//복사 생성자 //값 복사하는 경우에 호출
	{
		this->x = p.x;
		this->y = p.y;
		cout << "복사생성자" << endl;
	}
};
int main()
{
	//객체 배열 선언하기
	Point array[5];

	//객체 배열 생성하면서 초기화
	Point arr[5]{ 10,20,30 };							//정적생성 //생성하면서 초기화 //Point(10) 가능
	//Point arr[5]{ Point(10),Point(20),Point(30) };


	//객체의 포인터에 동적 생성
	Point* p1 = new Point[5];							//동적생성
	Point* p2 = new Point[5]{ {10,10}, 20, 30, 40 };	//생성하면서 초기화	//Point(10,10) 가능


	//객체 포인터의 배열 - 포인터이므로 동적 생성하여 할당
	Point* parr[5];
	for (int i = 0; i < 5; i++) {
		parr[i] = new Point(i * 10, i * 10);
	}

	//객체의 복사 생성 
	Point x1(1, 2);
	Point x2 = x1;  //복사 생성자 (특수맴버함수)
}

/*
// 객체를 배열로 선언하세요 //배열을 포인터로 지정하세요.

class MyClass
{
	int num = 0;
public:
	MyClass(int a) : num(a)	{
	}
	void Show()	{
		cout << num << endl;
	}
};

int main(void)
{
	MyClass array[4] = {		//배열을 배열로 지정
		MyClass(1), MyClass(2), MyClass(3), MyClass(4)
	};

	MyClass* pClass = array;	//배열을 포인터로 지정

	(*pClass).Show();	
	pClass->Show();				//포인터로 맴버 접근 ***
	(pClass + 1)->Show();

	return 0;
}

*/