// private 생성자 
//		- 생성자가 private이라는 것은 외부에서의 객체 생성을 허용하지 않겠다는 뜻이다.

#include <iostream>
using namespace std;

class ClassA
{
private:
	int num;
public:
	ClassA() : num(0) {}

	void ShowNum() const {	cout << num << endl; }

	ClassA& CreateInitObj(int n) const {
		ClassA* ptr = new ClassA(n);			// 동적할당
		return *ptr;
	}
private:
	ClassA(int n) : num(n) {}					// private 생성자 
};

int main(void)
{
	ClassA base;
	base.ShowNum();

	ClassA base(1);								//private 이므로 error

	ClassA& obj1 = base.CreateInitObj(3);		//함수를 이용해 생성, 객체 참조로 그대로 받음.
	obj1.ShowNum();
	ClassA& obj2 = base.CreateInitObj(12);
	obj2.ShowNum();

	delete& obj1;								// 함수에서 할당된 것은 해제해야 한다. 
	delete& obj2;

	return 0;
}

//싱글톤 패턴 등에서 활용. 조사해 보세요.