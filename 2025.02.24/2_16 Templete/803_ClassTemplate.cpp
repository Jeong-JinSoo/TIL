//클래스 템플릿 - 클래스 맴버의 변수 타입에 대하여 선언

#include <iostream>
using namespace std;

template <typename T>
class CTest
{
public:
	CTest(T param) : ndata(param) { }
	~CTest() { }

	void SetData(T val) { ndata = val; };
	T GetData() { return ndata; };

private:
	T ndata;
};

int main(void)
{
	CTest<int> a(1);
	//CTest a(1);					//C++17
	cout << a.GetData() << endl;

	CTest<float> b(1.5f);
	cout << b.GetData() << endl;

	return 0;
}

//클래스 템플릿의 선언과 정의의 분리 -------------------
template <typename T>
class Point
{
private:
	T xpos, ypos;
public:
	Point(T x = 0, T y = 0);
	void ShowPosition() const;
};

template <typename T>									// template <typename T>
Point<T>::Point(T x, T y) : xpos(x), ypos(y) {  }		// Point<T>::

template <typename T>
void Point<T>::ShowPosition() const {
	cout << '[' << xpos << ", " << ypos << ']' << endl;
}

int main(void)
{
	Point<int> pos1(3, 4);
	pos1.ShowPosition();

	Point<double> pos2(2.4, 3.6);
	pos2.ShowPosition();

	// 좌표 정보를 문자로 표시
	Point<char> pos3('P', 'F');
	pos3.ShowPosition();

	return 0;
}


//연습 ----------------------------------------

#include <iostream>           
using namespace std;

class Data {
private:
	int value;
public:
	Data(int v);
	void CopyData(int& v);
	int GetData();
};

Data::Data(int v) { value = v; }
void Data::CopyData(int& v) { value = v; }
int Data::GetData() { return value; }

void main()
{
	int a = 10;
	Data obj1(10);	obj1.CopyData(a); cout << obj1.GetData() << endl;

}
/*
#include <iostream>
using namespace std;
// Data<TYPE, ARG_TYPE>
template <typename TYPE, typename ARG_TYPE>
class Data {
	TYPE value;
public:
	Data(TYPE v);
	void CopyData(ARG_TYPE v);
	TYPE GetData();
};

template <typename TYPE, typename ARG_TYPE>
Data<TYPE, ARG_TYPE>::Data(TYPE v) { value = v; }
template <typename TYPE, typename ARG_TYPE>
void Data<TYPE, ARG_TYPE>::CopyData(ARG_TYPE v) { value = v; }
template <typename TYPE, typename ARG_TYPE>
TYPE Data<TYPE, ARG_TYPE>::GetData() { return value; }

void main()
{
	int a = 10;
	Data<int, int&> obj1(10);    cout << obj1.GetData() << endl;
	obj1.CopyData(a);    cout << obj1.GetData() << endl;

	double b = 3.4;
	Data<double, double&> obj2(1.5);    cout << obj2.GetData() << endl;
	obj2.CopyData(b);    cout << obj2.GetData() << endl;
}

*/