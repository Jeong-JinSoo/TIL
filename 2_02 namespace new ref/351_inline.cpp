#include <iostream>

//매크로와 인라인함수

inline int SQUARE(int x)
{
	return x * x;
}

int main(void)
{
	std::cout << SQUARE(5) << std::endl;
	std::cout << SQUARE(12) << std::endl;
	return 0;
}

/*
------------------------------------------------------------ -
#include<iostream>
using namespace std;

//인라인 함수
inline int Diff_ABS(int a, int b) {
    if (a > b)	return a - b;
    else 		return b - a;
}

//매크로 함수
#define DIFF_ABS(x,y) ( (x)>(y) ? (x)-(y) : (y)-(x) )

void main()
{
    cout << DIFF_ABS(5, 7) << endl;
    cout << Diff_ABS(5, 7) << endl;
    cout << DIFF_ABS(1.8, -1.4) << endl;
    cout << Diff_ABS(1.8, -1.4) << endl;
}

*/

//함수는 함수가 호출될 때마다 발생하는 일정량의 성능 오버헤드가 있다
//일반적으로 사용하는 작은 함수의 경우, 
//함수 호출에 필요한 시간이 실제로 실행하는 데 필요한 시간보다 훨씬 많은 경우가 있다.
//이로 인해 상당한 성능 저하가 발생
//컴파일러가 코드를 컴파일하면, 함수 호출이 함수 자체의 내용 복사본으로 대체되어 함수 오버헤드가 제거된다!

//자동 인라인 함수
//멤버함수의 정의가 아주 짧으면, 클래스 선언 내부에 함수를 직접 정의할 수도 있다.
//클래스 내부에 정의된 함수는 
//함수 선언 앞에 inline이 없어도 자동으로 인라인 함수가 된다.

//inline 키워드는 권장 사항일 뿐이다. ***
//인라인 함수를 알고 있어야 하지만 
//최신 컴파일러는 함수를 적절하게 인라인화 하므로 inline 키워드를 사용할 필요가 없다.


