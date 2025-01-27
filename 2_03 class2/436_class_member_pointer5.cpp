//클래스에 임베디드된 함수포인터를 호출하는 방법

#include <iostream>
using namespace std;

class fruit
{
public:
    void (fruit::* ff)(void);
    void apple() { cout << "apple" << endl; }
    void berry() { cout << "berry" << endl; }
};

int main()
{
    fruit x;
    void (fruit:: * f)(void);
    f = &fruit::apple;
    x.ff = &fruit::berry;
    (x.*f)();
    (x.*x.ff)();
    return 0;
}