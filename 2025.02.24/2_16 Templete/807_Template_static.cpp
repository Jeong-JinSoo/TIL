//함수 템플릿의 static 변수는 템플릿 함수 별로 독립적이다
//클래스 템플릿의 static 변수는 템플릿 클래스 별로 독립적이다! 

//함수 템플릿의 static 변수는 템플릿 함수 별로 독립적이다 -----------------------

#include <iostream>
using namespace std;

template <typename T>
void ShowStaticValue(void)
{
	static T num = 0;
	num += 1;
	cout << num << " ";
}

int main(void)
{
	ShowStaticValue<int>();
	ShowStaticValue<int>();
	ShowStaticValue<int>();
	cout << endl;

	ShowStaticValue<long>();
	ShowStaticValue<long>();
	ShowStaticValue<long>();
	cout << endl;

	return 0;
}


// 템플릿 클래스 개별 객체들 사이에서만 공유가 이뤄진다. *** -----------------------

#include <iostream>
using namespace std;

template <typename T>
class CStaticMember
{
private:
	static T mem;					//템플릿 클래스의 static 맴버

public:
	void Add(int num) { mem += num; }
	void Show() { cout << mem << endl; }
};

template <typename T> 
T CStaticMember<T>::mem = 0;		//외부에서 초기화

//template<>						
//long CStaticMember<long>::mem = 5;	//static 멤버 특수화

int main(void)
{
	CStaticMember<int> obj1;
	CStaticMember<int> obj2;
	obj1.Add(2);
	obj2.Add(3);
	obj1.Show();

	CStaticMember<long> obj3;
	CStaticMember<long> obj4;
	obj3.Add(100);
	obj4.Show();
	return 0;
}
