#include <iostream>

using std::cin;			//개별 객체의 사용 선언
using std::cout;
using std::endl;

//using namespace std;	//이렇게 하나만 선언 가능

int main(void)
{
	int num = 20;
	cout << "Hello World!" << endl;
	cout << "Hello " << "World!" << endl;
	cout << num << ' ' << 'A';
	cout << ' ' << 3.14 << endl;
	return 0;
}