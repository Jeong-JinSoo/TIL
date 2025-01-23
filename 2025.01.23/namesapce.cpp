// namespace 이름공간
//	충돌 문제를 해결하기 위해
//	모든 식별자(변수, 함수, 형식 등의 이름)가 고유하도록 보장하는 코드 영역을 정의한다.

// C++에서는 변수, 함수 구조체, 클래스 등을 서루 구분하기 위해서 이름으로 사용되는 다양한 내부 식별자(idenrifier)를 가지고 있다.
// 하지만 프로그램이 복잡해지고 여러 라이브러리가 포함될수록 내부 식별자 간에 충돌할 가능성도 그만큼 커진다.
// 이러한 이름 충돌 문제를 C++에서는 네임스페이스(namespace)를 통해 해결하고 있다.

// C++에서 네임스페이스란 내부 식별자에 사용될 수 있는 유효범위를 제공하는 선언적 영역을 의미한다.

// 네임스페이스의 정의
// C++에서는 namespace키워드를 사용하여 사용자가 새로운 네임스페이스를 정의 할 수 있다.
// 이러한 네임스페이스는 전역 위치뿐만 아니라 다른 네임스페이스 내에서도 정의 될 수 있다.
// 하지만 블록 내에서는 정의 될 수 없으며, 기본적으로 외부 연결을 가지게 된다.
// 일반적으로 namespace는 (class선언 할때와 같이) 헤더파일에서 정의 된다.

// C++에서는 전역 네임스페이스(global namespace)라고 하는 파일 수준의 선언 영역이 존재한다.
// 일반적으로 식별자의 네임스페이스가 명시되지 않으면, 전역 네임스페이스에 자동으로 포함되게 된다.
// 또한 C++ 표준 라이브러리 타입과 함수들은 std 네임스페이스 또는 그 속에 중첩된 네임스페이스에 선언되어 있다.

#include<iostream>
using namespace std;

namespace A		// 소속, 범위 //이름공간
{
	int n1;
	int n2;
}
namespace B
{
	int n1;
	int n2;
}

namespace AAA	// 소속, 범위 // 이름공간
{
	namespace BBB	// 네임스페이스 안에 네임스페이스
	{
		namespace CCC
		{
			int num1;
			int num2;
		}
	}
}

// 네임스페이스로의 접근
// 네임스페이스를 정의한 후에는 해당 네임스페이스로 접근 할 수 있는 방법이 필요하다.
// 네임스페이스에 접근하기 위해서는 범위지정 연산자(::, scope resolution operator)를 사용하여,
// 해당 이름을 특정 네임스페이스로 제한하면된다.

int main(void)
{
	A::n1 = 0;
	B::n1 = 0;

	AAA::BBB::CCC::num1 = 20;
	AAA::BBB::CCC::num2 - 30;

	namespace ABC = AAA::BBB::CCC;	// 별칭 // 간단히 줄이기

	cout << ABC::num1 << endl;
	cout << ABC::num2 << endl;

	return 0;
}

// 접근해서 사용해보자 // f() // B의 a = 5
namespace MyNamespace
{
	intnumber = 1;

	void finc() { }

	class A
	{
	public:
		int a = 0;
		void f()
		{

		}
	};

	struct B
	{
		int a = 0;
	};
}

// C++은 표준 라이브러리의 모든 기능을 std::namespace라는 특별한 영역으로 옮겼다.
using namespace std;
// 모든 표준 템플릿 라이브러리는 단일 네임스페이스 std:: 아래에 있다.
std::cout << "Hello world!";

// using 지시자 (directive)
// using 지시자는 명시한 네임스페이스에 속한 이름을 모두 가져와 범위 지정 연산자를 사용하지 않고도 사용할 수 있게 해준다.
// 전역 범위에서 사용된 using 지시자는 해당 네임스페이스의 모든 이름을 전역적으로 사용 할 수 있게 만들어 준다.
// 또한, 블록내에서 사용된 using 지시자는 해당 들록에서만 해당 네임스페이스의 모든 이름을 사용 할 수 있게 해준다.

using namespace AAA;

// using 선언 (declaration)
// using 지시자가 명시한 네임스페이스의 모든 이름을 사용 할 수 있게 했다면,
// using 선언은 단 하나의 이름만을 범위 지정 연산자를 사용하지 않고도 사용 할 수 있게 해준다.
// 또한, using 지시자와 마찬가지로 using 선언이 나타나는 언선으 ㅣ영역에서만 해당 이름을 사용 할 수 있게 해준다.

using AAA::BBB;