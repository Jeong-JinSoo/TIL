//클래스 템플릿의 선언과 정의의 분리 
//		템플릿 코드는 컴파일 할 때 포함되어야 한다. 헤더에 존재해야 함. ***

#include <iostream>
using namespace std;

template <typename T>
class Point
{
private:
	T xpos, ypos;
public:
	Point(T x = 0, T y = 0);
	void ShowPosition() const;
};

template <typename T>
Point<T>::Point(T x, T y) : xpos(x), ypos(y)	//Point<T>:: 범위지정	//Point:: 가 아니다.
{  }

template <typename T>
void Point<T>::ShowPosition() const
{
	cout << '[' << xpos << ", " << ypos << ']' << endl;
}


int main(void)
{
	Point<int> pos1(3, 4);		//템플릿 클래스의 객체생성시 자료형의 정보를 알려줘야 한다. (C++17 부터는 인수 추론 가능)
	pos1.ShowPosition();

	Point<double> pos2(2.4, 3.6);
	pos2.ShowPosition();

	Point<char> pos3('P', 'F');	// 좌표정보를 문자로 표시하는 상황의 표현
	pos3.ShowPosition();

	return 0;
}

//이니셜라이저를 사용해 클래스 템플릿 객체를 생성할 때 템플릿 인수 추론

//C++17에서 클래스 템플릿 객체를 생성할 때 
//	템플릿 인수를 명시하지 않더라도 자동으로 템플릿 인수를 추론하는 기능이 추가, 
//	이니셜라이저를 사용했을 때는 추론이 불가능했었습니다.

//C++20부터는 이니셜라이저를 사용해도 추론이 가능합니다.
//	std::vector v{ 1, 2, 3, 4, 5 };