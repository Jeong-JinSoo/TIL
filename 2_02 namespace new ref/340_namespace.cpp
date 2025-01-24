//namespace 이름공간
//		충돌 문제를 해결하기 위해
//		모든 식별자(변수, 함수, 형식 등의 이름)가 고유하도록 보장하는 코드 영역을 정의한다.

#include <iostream>
using namespace std;

namespace A			//소속, 범위 //이름공간
{
	int n1;
	int n2;
}
namespace B   
{
	int n1;
	int n2;
}

namespace AAA		//소속, 범위 //이름공간
{
	namespace BBB	//네임스페이스 안에 네임스페이스
	{
		namespace CCC
		{
			int num1;		//num1 = 20; 할당하기
			int num2;
		}
	}
}

int main(void)
{
	A::n1 = 0;						//:: 범위지정 연산자 //스코프 분석 연산자
	B::n1 = 0;


	AAA::BBB::CCC::num1 = 20;		//네임스페이스 안에 네임스페이스
	AAA::BBB::CCC::num2 = 30;

	namespace ABC = AAA::BBB::CCC;  //네임스페이스 별칭  // 간단히 줄이기

	cout << ABC::num1 << endl;
	cout << ABC::num2 << endl;

	return 0;
}

// 접근해서 사용해 보세요. //f() //B 의 a = 5;

namespace MyNamespace
{
	int number = 1;

	void func() { }

	class A {
	public:
		int a = 0;
		void f() { }		
	};

	struct B {
		int a = 0;			
	};
}

//C++은 표준 라이브러리의 모든 기능을 std namespace라는 특별한 영역으로 옮겼다.
using namespace std;
//모든 표준 템플릿 라이브러리는 단일 네임스페이스 std:: 아래에 있다.
std::cout << "Hello world!";