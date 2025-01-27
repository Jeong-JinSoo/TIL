//멤버함수 포인터
#include <iostream>
using namespace std;

class fruit
{
public:
	void apple() { cout << "apple" << endl; }
	void berry() { cout << "berry" << endl; }
};

int main()
{
	fruit x, * y;
	void (fruit:: * f)(void);		//멤버함수 포인터
	
	f = &fruit::apple;
	(x.*f)();						//멤버함수 포인터 사용

	f = &fruit::berry;
	y = new fruit;
	(y->*f)();
	

	delete y;
}
