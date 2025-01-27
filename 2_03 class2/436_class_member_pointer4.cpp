//static 멤버함수에 접근

#include <iostream>
using namespace std;

class fruit
{
public:
	void apple()
	{
		cout << "apple" << endl;
	}
	void berry()
	{
		cout << "berry" << endl;
	}
	static void cherry(void(fruit::* func)(), fruit x)
	{
		(x.*func)();
	}
};

int main()
{
	fruit x;
	void (fruit:: * f)(void);
	f = &fruit::apple;
	(x.*f)();

	f = &fruit::berry;
	x.cherry(f, x);					//static 멤버함수에 접근
	return 0;
}

/*

#include <iostream>
using namespace std;

class fruit
{
public:
	void apple()	{		cout << "apple" << endl;	}
	void berry()	{		cout << "berry" << endl;	}
	friend void cherry(void (fruit::* func)(), fruit x)
	{
		(x.*func)();
	}
};

int main()
{
	fruit x;
	void (fruit:: * f)(void);
	f = &fruit::apple;
	(x.*f)();

	f = &fruit::berry;
	cherry(f, x);						//friend 함수에 접근
}
*/