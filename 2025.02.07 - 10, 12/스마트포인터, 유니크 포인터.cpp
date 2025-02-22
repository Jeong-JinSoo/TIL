[스마트 포인터]

스마트포인터는 c++의 특별한 클래스 타입으로, 포인터처럼 동작하지만 스스로 메모리를 관리한다.
이는 메모리 누수를 방지하고, 메모리 관리의 복잡성을 줄여준다. 스마트 포인터는 객체가 더 이상 필요하지 않을 때
자동으로 삭제하며, 이러한 기능 때문에 '스마트'라고 부른다. 스마트 포인터의 필요성, 사용 이유, 그리고 작동 
원리에 대해 자세히 알아보도록 하자.

1. 스마트 포인터란?

스마트 포인터(smart pointer)는 C++에서 제공하는 포인터의 한 형태이다.
그러나 일반 포인터와는 다르게 '스마트'한 기능을 가지고 있다. 그렇다면 이 '스마트'한 기능이 뭘까?
바로 자동 메모리 관리이다.

일반적으로 c++에서 동적 메모리를 할당하면 프로그래머는 그 메모리를 직접 해제해야 한다. 이를 잊어버리면 메모리
누수가 발생하게 되고, 이는 프로그램의 성능을 저하시키는 주요한 원인이 된다. 또한 메모리를 해제한 후에 그
메모리를 다시 사용하려고 하는 '잘못된 해제(dangling reference)'문제도 발생할 수 있다. 이런 문제들은
프로그래밍을 복잡하게 만드는 요인 중 하나이다.

이를 해결하기 위해 등장한 것이 스마트 포인터로, 스마트 포인터는 포인터가 가리키는 메모리를 자동으로 해제하는
역할을 한다. 즉, 프로그래머는 메모리 관리에 대해 크게 신경 쓸 필요가 없다.

ex)
#include <memory>

int main()
{
	std::unique_ptr<int> smart_ptr(new int(10));
	return 0;
}

위 예제에서 std::unique_ptr<int>는 int 타입의 스마트 포인터이다.이 스마트 포인터는 new int(10)을 통해
동적으로 할당된 메모리를 가리키고 있다.그러나 가장 중요한 점은 main 함수가 끝나고 samrt_ptr이 사라질 때,
smart_ptr이 가리키는 메모리도 자동으로 해제된다는 것이다.이렇게 해서 프로그래머는 메모리 해제를 신경 쓸
필요가 없게 된다.

스마트 포인터는 이러한 메모리 관리 외에도 소유권(ownership) 개념을 도입하여 자원을 안전하게 공유하거나
이동시키는 데도 사용된다. << --이건 다음에

2. 스마트 포인터의 필요성과 사용이유

스마트 포인터의 필요성과 사용 이유를 이해하려면 먼저 C++의 메모리 관리 체계와 그에 따른 문제점을 이해해야
한다.C++에서는 동적 메모리 할당과 해제를 직접 관리해야 한다.new를 통해 동적으로 메모리를 할당하면 반드시
delete를 통해 그 메모리를 해제해야 한다.

ex)
int* ptr = new int(10); // 메모리 할당
delete ptr; // 메모리 해제

그런데 이런 방식에는 두가지 큰 문제가 있다.

첫번째는 메모리 누수이다.동적으로 할당한 메모리를 해제하기 않고 잊어버리면 그 메모리는 계속 시스템에 할당된
상태로 남게된다.이렇게 되면 메모리 사용량이 증가하고, 결국은 시스테메의 성능을 저하시키는 문제가 발생한다.

두번째 문제는 해제 후 사용(dangling pointer)이다.이미 해제된 메모리를 계속 사용하려는 경우에 발생한다.이는
데이터 손실이나 시스템 충돌을 일으킬 수 있는 심각한 문제이다.

ex)
int* ptr = new int(10);
delete ptr;
*ptr = 20; // 잘못된 해제 후 사용

이처럼 동적 메모리 관리는 프로그래밍의 복잡성을 증가시키고, 실수로 인한 오류 가능성을 높인다.이를 해결하기
위해 등장한 것이 바로 스마트 포인터이다.스마트 포인터는 포인터가 가리키는 메모리를 자동으로 해제해 주기 때문에
위와 같은 문제를 효과적으로 방지 할 수 있다.

ex)
std::unique_ptr<int> smart_ptr(new int(10)); // 메모리 할당
// 메모리 해제는 필요 없음

스마트 포인터를 사용하면 메모리를 직접 관리하는 수고를 덜 수 있다. 또한 메모리 누수나 해제 후 사용과 같은 실수를
예방 할 수 있다. 이러한 이유로, C++에서는 가능한 한 스마트 포인터를 사용하는 것이 권장 된다.

이외에도 스마트 포인터는 메모리 이외의 리소스를 관리 하는 데에도 사용 할 수 있다. 파일, 네트워크 연결, 뮤텍스
등의 리소스를 안전하게 관리하기 위해 스마트 포인터를 사용 할 수 있다.

3. 스마트 포인터의 작동 원리

스마트 포인터는 포인터처럼 동작하지만, 메모리를 직접 관리하는 것이 아니라 RAII(resource Acquistion Is
Inintialization) 이라는 원칙을 사용해 메모리를 자동으로 관리한다. RAII는 객체의 수명이 그 객체가 소유한
자원의 수명과 동일하게 관리되는 것을 의미 한다. 즉, 객체가 생성 될 때 자원을 할당하고, 객체가 소멸 될 때
자원을 해제 한다.

스마트 포인터는 기본적으로 템플릿 클래스로, 포인터와 같은 방식으로 사용 할 수 있다. 그러나 스마트 포인터 객체가
소멸 될 때, 스마트 포인터가 가리키는 메모리를 자동으로 해제한다. 이렇게 해서 프로그래머가 메모리 해제를
잊어 버리는 문제를 예방 할 수 있다.

ex)
std::unique_ptr<int> smart_ptr(new int(10)); // 사믙 포인터 생성
// 스마트 포인터가 소멸되면 메모리는 자동으로 해제된다.

스마트 포인터의 작동 원리를 이해하기 위해서는 C++의 생성자와 소멸자에 대한 이해가 필요하다.생성자는 객체가
생성될 때 호출되고, 소멸자는 객체가 소멸될 떄 호출된다.스마트 포인터의 경우 생성자에서 메모리를 할당하고,
소멸자에서 메모리를 해제한다.

스마트 포인터는 내부적으로 '원시 포인터(raw pointer)'를 보관하고 있다.이 원시 포인터는 스마트 포인터가
가리키는 실제 메모리를 가리킨다.그러나 사용자는 이 원시 포인터에 직접 접근 할 수 없으며, 스마트 포인터가 제공
하는 인터페이스를 통해서만 메모리에 접근 할 수 있다.

ex)
std::unique_ptr<int> smart_ptr(new int(10));
*smart_ptr = 20; // 스마트 포인터를 통해 메모리에 접근

스마트 포인터는 또한 '소유권(ownership)' 개념을 도입하여, 동일한 메모리에 대한 접근을 관리한다.
예를 들어, std::unique_ptr는 이름에서도 할 수 있듯이, 단 하나의 스마트 포인터만이 메모리를 소유 할 수 있다.
이는 메모리 해제를 보다 안전하게 만들어 준다.

스마트 포인터는 이러한 방식으로 메모리 관리의 부담을 줄여준다. 이제 이해 하기 어려웠던 포인터의 개념을 좀 더
쉽게 다룰 수 있게 된다.

[스마트 포인터의 종류]

C++의 스마트 포인터는 다양한 종류가 있으며, 각각이 메모리 관리를 지원하는 독특한 방식을 가지고 있다.
이번 장에서는 네가지 주요 스마트 포인터 - std::auto_ptr, std::unique_ptr, std::shared_ptr, std::weak_ptr
을 살펴보자. 이중 std::auto_ptr은 C++11 이후로 deprecated(사용이 권장되지 않는)되었으나 이해를 위해
포함시켰다. 나머지 세가지 스마트포인터는 메모리 소유권을 다루는 방식이 서로 다르므로 상황에 맞게 적절히 사용하는
것이 중요하다.

1. std::auto_ptr
std::auto_ptr은 현재 C++11부터 deprecated(사용이 권장되지 않는)상태이며, 이후에 배울 std::unique_ptr이 그 
기능을 대체하게 된다. 하지만 여전히 이해를 돕기 위해 std::auto_ptr에 대해 간략히 설명하고자 한다.

std::quto_ptr은 이름에서도 알 수 있듯이 자동 포인터를 의미한다. 이것은 자동 메모리 관리를 지원하는 첫 번째
스마트 포인터로, 스코프가 끝날 때 자동으로 소멸자를 호출하여 메모리를 해제한다.

ex)
#include <memory>

void auto_ptr_exmple()
{
	std::auto_ptr<int> ptr(new int);
	*ptr = 10;
	std::cout << *ptr << std::_Fnv1a_append_value;
} // 여기서 ptr은 범위를 벗어나 제거된다. 메모리는 자동으로 해제된다.

그러나 std::auto_ptr에는 치명적인 문제가 있다. 그것은 복사 연산을 허용한다는 점으로, 이러한 복사 연산은 동일한
메모리를 가리키는 두 개의 스마트 포인터를 만들 수 있음을 의미하는데, 이는 두 포인터가 동일한 메모리를 해제하려고
할 때 문제를 야기 할 수 있다. 이러한 이유로 std::auto_ptr은 C++11에서 deprecated되었으며, 대신
std::unique_ptr이 도입되었다.

ex)
#include <memory>

void auto_ptr_problem()
{
	std::auto_ptr<int> ptr1(new int);
	*ptr1 = 10;

	std::auto_ptr<int> ptr2 = ptr1; // ptr1이 ptr2에 복사된다.

	std::cout << *ptr2 << std::endl; // 이건 제대로 동작한다.
	std::cout << *ptr1 << std::endl; // 정의되지 않는 동작
}

위의 코드에서 볼 수 있듯이, ptr1이 ptr2로 복사되면서 문제가 발생한다. ptr1은 복사된 후에 null로 설정되며,
ptr2가 이제 동일한 메모리를 가리키게 된다. 이것은 두개의 포인터가 동일한 메모리를 관리하고 있는 상황을 만든다.
이 상황에서 ptr1을 사용하려고 하면 예상하지 못한 동작이 발생하게 된다.

즉, std::auto_ptr은 소유권을 복사하는 대신 이전 소유자에서 새로운 소유자로 이동한다. 이것은 다른 스마트
포인터, 특히 std::unique_ptr에서 볼 수 있는 복사 대신 이동(move)의 아이디어를 반영하는 초기의 시도였다.

이러한 문제점 때문에, std::auto_ptr은 더 이상 사용되지 않으며, 대신 std::unique_ptr 또는 std::shared_ptr는
참조 카운팅을 통해 여러개의 스마트 포인터가 동일한 자원을 안전하게 공유 할 수 있도록 한다.

그래도 std::auto_ptr에 대해 알아두면 스마트 포인터의 작동 원리와 발전 과정을 이해하는데 도움이 될 수 있다. 
이것이 C++의 첫번째 스마트 포인터였고, 후속 버전에서 개선되고 확장된 개념을 제공하므로, 이러한 관점에서
std::auto_ptr을 이해하면 도움이 된다. 그러나 실제 코드에서는 std::auto_ptr대신 std::unique_ptr나
std::shared_ptr을 사용하도록 권장한다.

2. std::unique_ptr

std::unique_ptr은 이름에서 알 수 있듯이, '유일한' 포인터이다. 죽, 동일한 메모리를 가리키는 두개의 
std::unique_ptr인스턴스가 동시에 존재할 수 없다. 이러한 특성은 메모리 누수와 같은 일반적인 문제를 방지하는데
도음이 된다.

ex)

std::unique_ptr<int> ptr1(new int(5));
std::unique_ptr<int> ptr2 = ptr1; //컴파일 에러!

위의 코드에서, ptr1을 ptr2로 복사하려고 했다. 하지만, 이것은 std::unique_ptr의 핵심 원칙에 위반되므로
컴파일러는 이를 허용하지 않는다. 그러나 std::unique_ptr은 '이동' 이라는 개념을 사용하여 포인터의 소유권을 이전
할 수 있다. 이것이 어떻게 작동 하는지 살펴보자.

ex)

std::unique_ptr<int> ptr1(new int(5));
std::unique_ptr<int> ptr2 = std::move(ptr1); // 컴파일 ok

이 경우, std::move 함수를 사용하여 ptr1에서 ptr2로 소유권을 '이동' 시켰다. 이로 인해 ptr1은 이제 null이 되고,
ptr2는 이전에 ptr1이 가리켰던 메모리를 가리키게 된다.

이러한 특성은 std::unique_ptr이 자원의 '유일한' 소유자임을 보장한다. 이것은 메모리 관리를 더욱 안전하고 예측
가능하게 만드는 중요한 속성이다.

std::unique_ptr은 이러한 속성 덕분에 다양한 유스케이스에서 유용하게 사용된다. 예를 들어, 함수에서 동적으로
할당된 메모리를 반환할 때, std::unique_ptr를 사용하면 호출자가 반환된 메모리의 소유권을 명확하게 이해 할 수
있으며, 메모리의 누수의 위험을 크게 줄일 수 있다.

ex)

std::unique_ptr<int> creatInt(int value)
{
	return std::unique_ptr<int>(new int value));
}

void useInt()
{
	std::unique_ptr<int> ptr = createInt(5);
	// 여기서 ptr은 createInt에서 반환된 메모리를 소유한다.
	// ptr이 범위를 벗어날 때, 메모리는 자동으로 해제된다.
}

이처럼, std::unique_ptr은 C++에서 안전하고 효과적인 메모리 관리를 가능하게 하는 강력한 도구이다.

3. std::shared_ptr

std::shared_ptr는 그 이름에서 알 수 있듯이 메모리에 대한 '공유' 소유권을 제공하는 스마트 포인터이다.이는 여러
std::shared_ptr인스턴스가 동일한 메모리를 가리킬 수 있음을 의미한다.그렇다면 어떻게 메모리 누수를 방지할까 ?
이것이 std::shared_ptr의 핵심 적인 부분이다.내부적으로 레퍼런스 카운팅을 수행하여, 메모리를 가리키는
std::shared_ptr 인스턴스를 추적한다.

ex)
std::shared_ptr<int ptr1(new int(5));
std::shared_ptr<int> ptr2 = ptr1;

ptr1과 ptr2 모두 동일한 메모리를 가리키며, 레퍼런스 카운트는 2이다.이 예제에서 ptr1을 ptr2로 복사했고, 둘 다
동일한 메모리를 가리킨다.각각의 std::shared_ptr는 이 메모리에 대한 공유 소유권을 가지며, 레퍼런스 카운트를
통해 이를 관리한다.이 경우, 레퍼런스 카운트는 2가 된다.

std::shared_ptr의 중요한 특징은, 레퍼런스 카운트가 0이 되면 특시 메모리가 해제된다는 점이다.이는 다음과 같이
동작한다.

ex)

{
	std::shared_ptr<int> ptr1(new int(5));
	{
		std::shared_ptr<int> ptr2 = ptr1;
		// ptr1과 ptr2는 모두 동일한 메모리를 가리키며, 레퍼런스 카운트는 2이다.
	}	// ptr2가 범위를 벗어나므로, 레퍼런스 카운트는 1로 감소한다.
	// ptr1이 여전히 메모리를 가리키고 있으므로, 메모리는 유지된다.
}	// ptr1이 범위를 벗어나면, 레퍼런스 카운트가 0이 되고 메모리가 해제된다.

따라서 std::chared_ptr은 여러 객체가 동일한 리소스를 안전하게 공유 할 수 있도록 해준다.그러나 이것은 반드시
필요한 경우에만 사용해야 한다.불필요한 레퍼런스 카운팅은 성능을 저하시킨다.또한 std::shared_ptr은 순환 참조
문제를 야기 할 수 있다.이 문제는 std::weak_ptr을 통해 해결 할 수 있다.

4. std::weak_ptr

std::weak_ptr는 std::shared_ptr의 중요한 동반자이며, 스마트 포인터가 순환 참조와 같은 문제에 대처하는 데 큰
도움을 준다.기본적으로 std::weak_ptr은 std::shared_ptr와 유사하지만, 가리키는 객체의 수명에 영량을 주지
않는 '약한' 참조를 제공한다는 점에서 다르다.이는 순환 참조를 피하는데 유용하다.

순환 참조는 두 객체가 서로를 참조하고, 둘다 std::shared_ptr를 사용하여 참조를 유지하는 경우에 발생한다.이
경우, 두 객체 모두 레퍼런스 카운트가 절대 0이 되지 않아 메모리 누수가 발생한다.

ex)

struct B;
struct A
{
	std::shared_ptr<B> b_ptr;
};

sruct B
{
	std::shared_ptr<A> a_ptr;
};

std::shared_ptr<A> a(new A());
std::shared_ptr<B> b(new B());

a->b_ptr = b;
b->a_ptr = a; // 순환 참조 생성

위 예제에서, A와 B객체는 서로를 참조하므로 순환 참조가 발생한다.레퍼런스 카운트가 절대로 0이 되지 않으므로 메모리가
누수된다.이 문제를 해결하려면 std::weak_ptr을 사용한다.

ex)

struct B;
struct A
{
	std::shared_ptr<B> b_ptr;
};

struct B
{
	std::weak_ptr<A> a_ptr; // 약한 참조 사용
};

std::shared_ptr<A> a(new A());
std::shared_ptr<A> a(new B());

a->b_ptr = b;
b->a_ptr = a;

*두 예제의 차이는 strct B에서 사용된것이 shared_ptr이냐 weak_ptr이냐의 차이뿐이다.a_ptr

이제 B는 std::weak_ptr를 사용하여 A를 하므로, 순환 참조가 발생하지 않는다. A가 파괴되면 std::weak_ptr은 lock() 함수를
사용하여 std::shared_ptr로 변환 할 수 있다. 이 함수는 해당 객체가 여전히 존재하는 경우에만 st::shared_ptr를 반환하므로,
메모리를 안전하게 접근 할 수 있습니다.

ex)

if (std::shared_ptr<A> a_locked = b->a_ptr.lock())
{
	// 객체가 여전히 존재하므로 안전하게 접근 할 수 있다.
}

else
{
	// 객체가 이미 파괴되었다.
}

따라서 std::weak_ptr은 순환 참조와 같은 복잡한 문제를 해결하는데 있어서 std::shated_ptr와 함께 중요한 역할을 한다.

[std::unique_ptr에 대해]

std::unique_ptr는 C++11부터 제공되는 스마트 포인터의 한 종류이다. 이 스마트 포인터는 단이 소유권 모델을 구현한다. 즉,
std::unique_ptr는 메모리 블록을 독점적으로 소유하고, 복사는 허용되지 않는다. 이러한 특성은 메모리 누수를 예방하고, 자원을
안전하게 관리하는 데 매우 유용하다. 또한 std::unique_ptr를 사용하는 것이 좋다.

1. std::unique_ptr의 정의와 특징
std::unique_ptr는 C++11에서 도입된 스마트포인터 중 하나로, 이 포인터는 "유일한 소유권" 모델을 따른다. 이말은, 한번에 한
std::unique_ptr만이 특정 객체를 소유 할 수 있다는 뜻이다. 이러한 속서은 단일 소유가 보장되어야 하는 시스템 리소스 관리에
적합하다.

ex)

#include <memory>
#include <iostream>

class MyClass
{
public:
	MyClass() { std::cout << "MyCLass constructed\n"; }
	~MyClass() { std::cout << "MyClass destroyed\n"; }
};

int main()
{
	std::unique_ptr<MyClass> ptr1(new MyClass);
}

위 예제 코드에서 std::unique_ptr은 MyClass인스턴스를 소유한다.프로그램이 main함수의 범위를 벗어나면, std::unique_ptr는
자동으로 소유한 객체를 삭제한다.이 떄문에 명시적으로 delete를 호출할 필요가 없다.

특히 중요한 점은 std::uniaue_ptr은 복사를 허용하지 않는다는 것이다.즉, 다른 std::unique_ptr로 부터 소유권을 가져 올 수
없다.대신, std::move함수를 사용해 소유권을 이전(transfer) 할 수 있다.

ex)

std::Unique_ptr<MyClass> ptr2 = std::move(ptr1);

위 코드는 ptr1이 가지고 있던 소유권을 ptr2에게 이전한다. 이제 ptr1은 더이상 객체를 소유하지 않고, ptr2는 객체의 새로운
소유자가 된다. 이렇게 std::unique_ptr은 런타임에서 안전하게 객체의 소유권을 이전하는 것을 가능케 한다.

한편, std::unique_ptr은 성능 비용이 거의 없다. 이는 std::unique_ptr이 내부적으로 일반 포인터를 사용해 객체를 추적하기
때문이다. 따라서, std::unique_ptr은 안전한 리소스 관리와 효율성을 동시에 달성하는 데 도음이 된다.

2. std::unique_ptr의 기본 사용법
 std::unique_ptr을 사용하는 것은 매우 간단하다. 다음은 std::unique_ptr의 기본 사용 방법에 대한 몇가지 예를 보여주는 C++
코드이다.

ex)

#include <memory>
#include <iostream>

class MyClass
{
public:
	MyClass(int value) : value_(value) { }
	void PrintValue() { std::cout << "Value: " << value_ << "\n"; }
private:
	int value_;
};

int main()
{
	std::unique_ptr<MyClass> ptr1(new MyClass(5));
	ptr1->PrintValue();

	std::unique_ptr<MyClass>ptr2 = std::make_unique<MyClass>(10);
	ptr2->PrintValue();

	// std:: unique_ptr<MyClass> ptr3 = ptr2; // 이건 컴파일 에러를 만든다.
	std::unique_ptr<MyClass>ptr3 = std::move(ptr2); // ptr2의 소유권이 ptr3로 옮겨진다.
	ptr3->PrintValue();

	return 0;
}

첫 번째 예제에서는 std::unique_ptr가 동적으로 할당된 MyClass객체를 소유한다.이 때문에 명시적으로 delete를 호출할 필요가
없다.std::unique_ptr가 범위를 벗어나면 자동으로 메모리를 해제한다.

두번째 예제에서는 std::make_unique 함수를 사용하여 std::unique_ptr를 생성합니다.이 방법이 좋은 이유는, 이 함수는 객체
생성과 메모리 할당을 하나의 연산으로 결합하므로, 예외 안정성을 높일 수 있기 때문이다.

세번쨰 예제에서는 소유권 이전을 시연하고 있다.std::unique_ptr는 복사가 허용되지 않지만, std::move를 사용하여 소유권을
다른 std::unique_ptr로 이전 할 수 있다.

마지막으로 std::unique_ptr는 객체의 멤버 함수에 적근하기 위해 일반 포인터처럼->연산자를 사용 할 수 있다.

std::unique_ptr은 C++의 중요한 특징인 RAII(Resource Acquisition Is Initialization)패턴의 일부로, 동적 메모리를 안전하게
관리하는데 도움이 된다.

3. std::unique_ptr와 소유권

std::unique_ptr의 핵심적인 특징 중 하나는 소유권(ownership) 개념이다.std::unique_ptr은 소유하고 있는 동적 메모리에 대한
독접적인 소유권을 가지고 있다.이는 다른 std::unique_ptr 객체가 같은 메모리를 소유하도록 허용하지 않는다는 것을 의미한다.

ex)
std::unique_ptr<int> ptr1(new int(5)) // ptr1은 이제 메모리를 소유한다.
std::unique_ptr<int> ptr2 = ptr1; // 컴파일 에러! unipue_ptr을 카피 할 수 없다.

이것은 std::unique_ptr이 복사 생성자와 복사 대입 연산자를 삭제(즉, 사용 불가 하게 만듬)하기 떄문이다.
이로 인해 std::unique_ptr의 복사가 막히므로, 하나의 std::unique_ptr만이 특정 메모리를 소유 할 수 있다.

하지만, std::unique_ptr은 소유권을 다른 std::unique_ptr로 이전(transfer)시키는 것은 가능하다.이는 std::move를
통해 수행된다.

ex)
std::unique_ptr<int> ptr1(new int(5));
std::unique_ptr<int> ptr2 = std::move(ptr1);

위 예제에서 std::move를 사용하면 ptr1은 소유권을 ptr2로 이전시키고, 이제 더이상 메모리를 소유하고 있지 않다. ptr2가 이제 그
메모리를 소유하고 있으므로, ptr2가 범위를 벗어나면 해당 메모리는 자동으로 해제된다.

이러한 소유권 이전 특성으로 인해 std::unique_ptr은 자원의 소유와 생명주기를 명확하게 관리할 수 있으며, 메모리 누수를
방지하는데 도움이 된다. 이러한 송권 모델은 C++의 자원 관리 전략인 RAII와 잘 어울린다.

4. std::unique_ptr의 예제코드와 활용법

std::unique_ptr를 이해하는데 필요한 핵심 개념과 기본적인 사용법에 대해 알아보자. std::unique_ptr은 독점적 소유권을
가지는 스마트 포인터 이며, 이는 하나의 std::unique_ptr만이 특정 메모리를 소유 할 수 있음을 의미하며, 이 소유권을 다른
std::unique_ptr로 이전(또는 이동)시킬 수 있다.

이러한 속성은 std::unique_ptr가 특히 할당된 메모리를 관리하는데 유용하다. 이것은 C++에서 자주 발생하는 문제 중 하나인 메모리
누수를 방지하고 자원을 효율적으로 관리하는 데 도움이 된다.

이제 std::unique_ptr의 활용법을 살펴보자.

ex) 기본 사용법)
#include <memory>

int main()
{
	std::unique_ptr<int> ptr(new int(5)); // 동적으로 int를 할당하고, ptr이 그것을 소유하게 함
	// 이제 ptr은 동적으로 할당된 int를 가리킨다.
	// ptr이 범위를 벗어나면 자동으로 메모리를 해제한다.
}

ex) 소유권 이전)
#include<memory>

int main()
{
	std::unique_ptr<int> ptr1(new int(5)); // 동적으로 int를 할당하고, ptr1이 그것을 소유하게 함
	std::unique_ptr<int> ptr2;	// 아직 아무것도 소유하지 않음

	ptr2 = std::move(ptr1); // ptr1의 소유권을 ptr2로 이전
	// 이제 ptr2는 동적으로 할당된 int를 소유하고, ptr1은 아무것도 소유하고 있지 않다.
	// ptr2가 범위를 벗어나면 자동으로 메모리를 해제한다.
}

이 예제에서는 std::unique_ptr의 소유권을 이전하는 방법을 보여준다. std::move를 사용하여 ptr1의 소유권을 ptr2로 이전하고 있다. 이제
ptr2가 메모리를 소유하고 있으므로, ptr2가 범위를 벗어나면 해당 메모리는 자동으로 해제된다.

또한 std::unique_ptr는 커스텀 deleters를 지원한다. 이는 std::unique_ptr가 메모리를 해제하는 방법을 사용하자가 정의 할 수 있음을 의미한다.
예를 들어, 파일 핸들이나 네트워크 소켓과 같은 것들.

ex) 커스텀 delete

#include<memory>
#include<cstdio>

struct FileDeleter
{
	void operator()(std::FILE* file) const
	{
		if (file)
		{
			std::fclose(file);
		}
	}
};

int main()
{
	std::unique_ptr<std::FILE, FileDeleter> filePtr(std::fopen("myfile.txt", "r"));
	// 이제 filePtr은 myfile.txt를 가리키는 파일 핸들을 소유한다.
	// filePtr이 범위를 벗어나면 스스로 커스텀 deleter가 호춯되어 파일이 자동으로 닫힌다.
}
 
이처럼 std::unique_ptr은 자원을 효율적으로 관리하는 데 매우 유용한 도구이다. C++ 프로그래밍에서 자원관리는 중요한 주제이며
std::unique_ptr는 이 문제를 해결하는 데 도움이 된다.

5. std::unique_ptr 예외 처리

C++에서는 예외 처리가 중요한 부분을 차지한다. 그 중 std::uniqur_ptr와 예외 처리를 함꼐 다루는 방법에 대해 이야기 해보자. std::unique_ptr
는 소유하고 있는 메모리를 자동으로 해제하는 특성 때문에, 이는 예외가 발생했을 때 메모리 누수를 방지하는데 큰 도움이 된다.

ex)

#include <iostream>
#include <memory>

void MyFunction()
{
	std::unique_ptr<int> ptr(new int(5)); // 동적으로 int를 할당하고, ptr이 그것을 소유하게 함

	// 여기서 예외가 발생한다고 가정하자.
	throw std::runtime_error("An error occurred!");

	// ptr은 스코프를 벗어나는 순간 메모리를 자동으로 해제한다.
	// 예외가 발생하더라도, 메모리 누수는 발생하지 않는다.
}

int main()
{
	try
	{
		MyFunction();
	}

	catch (const std::exception& e)
	{
		std::cout << "Caught exception: " << e.what() << "\n";
	}
}

이 예제에서, MyFunction 함수 안에서 std::unique_ptr가 생성되었다. 이 std::unique_ptr는 동적으로 할당된 int를 소유하고 있다. 그리고 
함수안에서 예외가 발생하면, std::unique_ptr은 자동으로 소유하고 있는 메모리를 해제한다. 이 떄문에 예외가 발생하더라도 메모리 누수는
발생하지 않는다.

그런데 여기서 주의할 점이 있다. std::unique_ptr를 다른 함수에 전달하거나, 함수에서 반환받을 때는 소유권 이전에 대한 이해가 필요하다.
std::unique_ptr의 복사 생성자와 복자 대입 연산자는 삭제되어 있으므로, std::unique_ptr를 직접 복사하는 것은 불가능하다. 대신 std::move를
사용하여 std::unique_ptr의 소유권을 이전해야 한다.

다음은 std::unique_ptr를 함수에 전달하고 반환하는 방법에 대한 예제이다.

ex)

#include <memory>

std::unique_ptr<int> CreateUniquePtr()
{
	// std::Unique_ptr를 직접 잔환하면, 소유권이 이전된다.
	// 이 때문에 함수가 끝난 후에도 메모리 누수는 발생하지 않는다.
	return std::unique_ptr<int>(new int(5));
}

void UseUniquePtr(std::unique_ptr<int> ptr)
{
	// 함수가 전달된 std::unique_ptr는 이 함수 안에서만 유효하다.
	// 함수가 끝난 후에는 자동으로 메모리가 해제된다.
}

int main()
{
	std::unique_ptr<int> ptr = CreateUniquePtr();
	UseUniquePtr(std::move(ptr));	// std::unique_ptr를 함수에 전달 할 때는 std::move를 사용해야 한다.

	// 이제 ptr는 nullptr이다. 소유권이 UseUniquePtr  함수에 이전되었기 때문이다.
}

이 예제에서는 CreateUniquePtr함수가 std::unique_ptr를 반환하고, UseUniquePtr 함수가 std::unique_ptr를 매개 변수로 받는다. 이 두 경우
모두, std::unique_ptr를 함수에 전달 할 때는 std::move를 사용했다.

이처럼 std::unique_ptr는 예외 처리와 함께 사용 될 떄 특히 유용하다. 메모리 누수를 장비하고, 코드의 안전성을 향상 할 수 있다.

[std::shared_ptr에 대해]

std::shared_ptr는 C++의 스마트 포인터 중 하나로, 여러 곳에서 동시에 소유할 수 있는 메모리를 가리키는 포인터이다.이 포인터가 가리키는
메모리는 참조 횟수를 세어, 마지막 std::shared_ptr이 소멸할 때 해제된다.메모리 해제를 자동으로 처리하므로, 개발자가 직접 메모리를
관리하는데 드는 시간과 노력을 줄일 수 있다.이로 인해 코드의 안정성이 향상되며, 메모리 누수의 가능성을 줄일 수 있다.

1. std::shared_ptr의 정의와 특징

std::shared_ptr은 C++표준 라이브러리의 스마트 포인터 중 하나로서, 참조 카운팅(reference counting)방식을 사용하여 동적 메모리를 관리한다.
그 이름에서 알 수 있듯이, std::shared_ptr은 여러개의 스마트 포인터가 같은 객체를 '공유' 할 수 있게 해주는 것이 주요 특징이다.

이 스마트 포인터는 내부적으로 두 가지 주요 구성 요소를 가지고 있다. 하나는 가리키는 실제 객체 대한 포인터이고, 또 다른 하나는 '제어 블록'
이라고 불리우는, 참조 카운터와 관련된 정보를 유지하는 부분이다.

std::shared_ptr이 복사되거나 다른 객체로 이동 될 때, 이 참조 카운터가 업데이트되며, 참조 카운터가 0이 될 떄 실제 객체가 삭제된다.

ex)

#include <iostream>
#include <memory>

struct Foo
{
	Foo() { std::cout << "Foo::Foo\n"; }
	~Foo() { std::cout << "Foo::~Foo\n"; }
	void bar() { std::cout << "Foo::bar\n" }
};

int main()
{
	std::shared_ptr<Foo> ptr1 = std::make_shared<Foo>();
	std::cout << "ptr (use count" << ptr1.use_count() << ") at " << ptr1.get() << '\n';
	
	{
		std::shared_ptr<Foo> ptr2 = ptr1;
		f(ptr2);
	}
	
	// 여기서 ptr2의 소멸자가 호출되지만, 참조 카운터가 1이므로 아직 Foo 객체는 삭제되지 않는다.
	std::cout << "ptr1 (use count " << ptr1.use_count() << ") at " << ptr1.get() << '\n';

}	// Foo::~Foo가 이 지점에서 호출된다.

위 코드에서 볼 수 있듯이, std::shared_ptr을 사용하면 동적 메모리의 생명주기를 안전하게 관리할 수 있다.더군다나, 코드가 복잡해지고 여러
함수와 객체가 같은 메모리에 접근해야 할 때, 이러한 스마트 포인터의 이점은 더욱 두드러진다.

다만, std::shared_ptr을 사용할 때 주의 할 점은 순환 참조 문제이다.서로가 서로를 가리키는 std::shared_ptr객체가 생성되면, 참조 카운터가
절대 0이 되지 않아 메모리 누수가 발생한다.이런 상황을 막기 위해 '약한 포인터'인 std::weak_ptr를 사용 할 수 있다.

2. std::shared_ptr의 기본 사용법

std::shared_ptr을 사용하는 기본적인 방법에 대해 알아보자.먼저, 이 스마트 포인터 객체는 다음과 같이 생성할 수 있다.

ex)

std::shared_ptr<int> p1(new int(5));
std::shared_ptr<int> p2 = std::make_shared<int>(5);

여기서 std::make_shared를 사용하는 방법이 더 선호 되는데, 이유는 두가지이다.첫째, std::make_shared를 사용하면 메모리 할당이 한번만
이루어져 성능을 향상 할 수 있다.둘째, 이 방식은 예외 안정성을 보장한다.

ex)

foo(std::shared_ptr<int>(new int(5)), function_may_throw());

위 코드에서 function_may_throw()이 예외를 발생 시키면, 이미 할당된 new int(5)에 대한 메모리 누수가 발생할 수 있습니다.
반면, std::make_shared를 사용하면 이러한 문제를 방지할 수 있다.

ex)
foo(std::make_shared<int>(new int(5), function_may_throw()); // 더 안전하고 선호되는 방식

std::shared_ptr 객체는 다른 스마트 포인터나 일반 포인터로부터 복사하거나 이동할 수 있다.이때 참조 카운터가 적절히 조정된다.

ex)
std::shared_ptr<int> p3 = p2; //p3과 p2는 같은 객체를 가리키며, 참조 카운트는 2이다.

다음으로, std::shared_ptr는 일반 포인터처럼 동작하며, 멤버 접근 연산자(->)와 역참조 연산자(*)를 사용 할 수 있다.

ex)
std::shared_ptr<std::string> p4 = std::make_shared<std::string>("Hello, World!");
std::cout << *p4 << '\n';
std::cout << p4-> size() << '\n' 

std::shared_ptr을 사용하면 메모리 관리에 대한 걱정 없이 공유소유를 표현 할 수 있다.

3. std::shared_ptr와 참조 카운팅

std::shared_ptr의 핵심적인 특징 중 하나는 "참조 카운팅"이다. 참조 카운팅이란 std::shared_ptr객체가 생성되거나 이미 존재하는
std::shared_ptr객체를 복사하면, 참조 카운트는 증가하며, std::shared_ptr 객체가 소멸되거나 다른 리소스를 가리키게 될 때 참조 카운트는
감소한다.

ex)
std::shared_ptr<int> p1 =  std::make_shared<int>(5);
std::shared_ptr<int> p2 = p1 // p1을 복사하면 참조 카운트가 증가한다.

std::cout << "p1 use cout: " << p1.use_count() << '\n'
std::cout << "p2 use cout: " << p2.use_count() << '\n'

참조 카운트는 std::shared_ptr의 use_count() 메서드를 통해 알 수 있다. 하지만 이 메서드는 디버깅이나 학습 목적 외에 사용을 권장하지 않는데,
그 이유는 use_count()의 반환 값이 순간적인 상태를 반영하기 떄문에 멀티스레드 환경에서는 신뢰 할 수 업시 때문이다.

std::shared_ptr가 참조 카운트를 관리하는 방식 덕분에, 공유하는 모든 std::shared_ptr 객체가 사라지면, 즉 참조 카운트가 0이 되면 자동으로
메모리가 해제된다. 이렇게 되면 메모리 누수를 걱정할 필요가 없다.

ex)
{
	std::shared_ptr<int> p3 = std::makesared<int>(10);
	{
		std::shared_ptr<int> p4 = p3;
	}

	std::cout << *p3 << '\n';
}

이것이 바로 std:: shared_ptr와 참조 카운팅의 기본적인 원리이다. 이런 특성 덕분에 std::shared_ptr은 C++에서 자원 공유를 표헌하는 강력한
도구이다.

4. std::shared_ptr의 예제코드와 활용법

이제 실제로 std::shared_ptr을 어떻게 사용하는지 살펴볼 차례이다. 아래 예제를 통해 기본적인 사용방법을 살펴본다.

ex)
#include <iostram>
#include <memory>

class MyObject
{
public:
	MyObject() { std::cout << "Object created!\n"; }
	~MyObject() { std::cout << "Object destroyed!\n" }
};

int main()
{
	std::shared_ptr<MyObject> ptr1 = std::make_shared<MyObject>();
	{
		std::shared_ptr<MyObject> ptr2 = ptr1;
	}

	return 0;
}

위 예제에서 MyObject라는 간다난 클래스를 생성했다. 이 클래스를 생성자와 소멸자에는 객체의 생성과 소멸을 알리는 메시지를 출력하는 코드가
들어 있다.

main 함수에서는 std::make_shared 함수를 이용하여 MyObejct객체를 생성하고 std::shared_ptr에 할당했다. 그리고 내부 블록에서 ptr1을 복사하여
ptr2를 생성한다. 이렇게 되면 ptr1과 ptr2는 동일한 MyObject 객체를 가리키며, 참조 카운트는 2가 된다.

내부 블록이 종료되면 ptr2가 소멸되고 참조 카운트는 1로 줄어든다. 하지만 여전히 ptr1이 MyObject객체를 가리키고 있으므로 객체는 소멸되지
않는다. main함수가 종료되면 ptr1이 소멸되고 참조 카운트가 0이 되어, 이 시점에서 MyObject 객체가 소멸된다.

이처럼 std::shared_ptr를 사용하면 자동으로 참조 카운트를 관리 해 주기 떄문에, 우리는 명시적으로 메모리를 해제해 주는 코드를 작성할 필요가
없습니다. 또한 참조 카운트가 0이 되는 시점에서 객체가 소멸되므로 메모리 누수를 방지 할 수 있다.

이 외에도 std::shared_ptr는 원시 포인터 처럼 사용 할 수 있다. 즉, *연산자를 이용하여 객체에 접근 할 수 있고, -> 연산자를 이용하여 객체의
멤버에 접근 할 수 있다. 

ex)
#include <iostream>
#include <memory>

class MyObject
{
public:
	MyObject(int val) : value(val) {}
	int value;
};

int main()
{
	std::shared_ptr<MyObject> ptr = std::make_shared<MyObject>(10);
	std::cout << "Value" << ptr->value << "\n";
	return 0;
}

위 예제이서는 MyObject 객체에 value라는 멤버 변수를 추가했다.그리고 std::make_shared 함수를 이용하여 MyObject객체를 생성할 때 value를
초기화 했다.이후 ptr->value를 이용하여 value에 접근하였다.

따라서 std::shared_ptr를 이용하면 메모리 관리를 자동화 할 수 있으면서도 원시 포인터와 유사한 방식으로 코드를 작성 할 수 있다.이러한 특성
덕분에 std::shared_ptr는 C++에서 자주 사용되는 스마트 포인터 중 하나이다.

5. std::shared_ptr 예외 처리

C++에서 예외처리는 중요한 부분...(아까 했던 이야기)
이는 메모리 관리와 밀접한 관련이 있는데, std::shared_ptr은 이러한 문제를 처리하는데 유용한 도구이다.

[예외와 메모리 누수]

먼저, 예외와 메모리 누수에 대한 문제를 이해 해 보자.

#inlcude <iostream>
#include <stdexcept>

class MyObject
{
public:
	MyObject() {std::cout << "Object created!\n" }
	~MyObject() {std::cout << "Object destroyed!\n" }
};

void riskyFunction()
{
	MyObject* obj = new MyObject();
	throw std::runtime_error("Exception occurred!");
	delete obj
}

int main()
{
	try
	{
		riskyFUntion();
	}

	catch (const std::exception& e)
	{
		std::cerr << "Caight exception: " << e.what() << '\n';
	}

	return 0;
}

위의 riskyFunction에서는 MyObject를 동적으로 생성하고, 이후에 예외를 발생시킨다.예외가 발생하면 delete obj; 코드는 실행되지 않고, 이로
인해 메모리 누수가 발생한다.

[std::shared_ptr를 사용한 안전한 코드]

std::shared_ptr을 사용하면 위와 같은 문제를 쉽게 해결 할 수 있다. std::shared_ptr을 사용하여 객체를 생성하면, std::shared_ptr이 자동으로
메모리를 관리하므로 명시적으로 delete를 호출할 필요가 없다. 이를 통해 메모리 누수를 방지 할 수 있다.

ex)
#include <iostream>
#include <stdexcept>
#include <memory>

class MyObject
{
public:
	MyObject() { std::cout << "Object created!\n"; }
	~MyObject() { std::cout << "Object destroyed!\n"; }
};

void safeFunction()
{
	std::shared_ptr<MyObject> obj = std::make_shared<MyObject>();
	throw std::runtime_error("Exception occurred!"):
}

int main()
{
	try {
		safeFunction();
	}

	catch (const std::exception& e)
	{
		std:: cerr << "Caught exception: " << e.what << "\n"
	}

	return 0;
}

위 코드에서 safeFUnction은 std::shared_ptr을 사용하여 MyObject를 생성한다. 이후 예외가 발생하더라도 std::shared_ptr이 소멸 될 때,
MyObject가 자동으로 삭제되므로 메모리 누수가 발생하지 않는다.

이처럼 std::shared_ptr은 예외 안정성을 강화하는데 유용하다. 이 도구를 사용하면 예외 상황에서도 메모리 누수를 방지하고, 코드를 더 안전하게
만들 수 있다.

[std::weak_ptr에 대해]

std::weak_ptr는 C++ 스마트 포인터 중 하나로, std::shared_ptr와 같이 참조 카운팅을 사용하지만, 참조 카운트에 영향을 주지 않는다. 이는 순환
참조 문제를 방지하기 위해 사용된다. 순환 참조란 서로가 서로를 참조하는 상황으로, 스마트 포인터가 자동으로 메모리를 해제하지 못하게 만든다.
std::weak_ptr를 사용하면 이러한 문제를 피할 수 있다.

weak_ptr의 정의와 특징

C++의 스마트 포인터 중 하나인 std::weak_ptr는 이름에서도 알 수 있듯이, '약한 포인터'를 의미 한다. 이 포인터는 std::shared_ptr와 연동되어
작동하며, 가장 큰 특징은 참조 카운트에 영향을 미치지 않는다는 것이다. 즉, std::weak_ptr이 가리키는 객체를 참조하는 동안에는 해당 객체가
메모리에서 사라지지 않지만, 참조 카운트에는 반영되지 않아 std::shared_ptr처럼 메모리 해제에 영향을 미치지 않는다.

이 특징은 순환 참조 문제를 해결하는데 아주 중요한 역할을 한다. 순환 참조는 두 객체가 서로 참조 할 때 생기는 문제로, 이런 상황에서는 각 개체의
참조 카운터가 0이 되지 않아 영원히 메모리에서 해제되지 않는 문제가 발생한다. std::weak_ptr이 소멸되었을 때 객체는 메모리에서 해제된다.

ex)
#include <iostream>
#include <memory>

struct MyClass
{
	std::weak_ptr<MtClass> ptr;
	~MyClass() { std::cout << "MyClass destroyed\n"; }
};

int main()
{
	std::shared_ptr<MyClass> sp = std::make_shared<MyClass>();
	sp->ptr = sp;

	return 0;
}

이 코드에서는, MyClass 객체가 자신을 가리키는 weak_ptr을 멤버로 가지고 있다. 메인 함수에서는 shared_ptr을 생성하고, 이 shared_ptr이 자신을
가리키게 한다. 그러나 이 경우에도 MyClass 객체는 프로그램이 종료 될 때 정상적으로 해제된다. 이것은 weak_ptr이 참조 카운트에 반영되지 않기
떄문이다.

이렇게 std::weak_ptr은 std::shared_ptr과 함께 사용하여 순환 참조 문제를 해결하는데 아주 중요한 도구이다. 

참조 카운트에 반영되지 않는 std::Weak_ptr의 특성 떄문에, weak_ptr가 가리키는 객체를 직접 접근 할 수는 없다. 이를 위해서는 std::shared_ptr로
변환해야 하는데, 이 과정을 '락(lock)'이라고 한다. std::weak_ptr의 lock메서드를 호출하여 std::shared_ptr를 얻을 수 있다.

ex)

#include <iostream>
#include <memory>

int main()
{
	std::shared_ptr<int> sp = std::make_shared<int>(123);
	std::weak_ptr<int> wp = sp;

	if (std::shared_ptr<int> locked = wp.lock())
	{
		std::cout << " *locked" << *locked << '\n';
	}

	else
	{
		std::cout << "wp is expired\n";
	}

	return 0;
}

이 코드에서는, 먼저 shared_ptr을 생성하고, 이를 weak_ptr로 복사한다.그런 다음 lock 메서드를 사용하여 weak_ptr에서 shared_ptr를 얻고, 이를
통해 객체에 접근 한다.이 방법으로 객체가 아직 메모리에 있는지 확인 할 수 있다.만약 객체가 메모리에서 해제되었다면, lock 메서드는 빈
shared_ptr를 반환한다.

따라서, std::weak_ptr는 객체가 아직 메모리에 있는지 확인하는 데 사용 할 수 있는 훌룡한 도구이다.std::shared_ptr와 함께 사용하면, 메모리
누수를 방지하고, 객체의 생명 주기를 안전하게 관리 할 수 있다.

주목할 점은, std::weak_ptr는 객체에 접근 하기 전에 항상 lock 메서드를 호출하여 객체가 아직 메모리에 있는지 확인해야 한다는 것이다.이는
std::weak_ptr의 핵심적인 특성이자 사용방법이다.

2. weak_ptr의 기본 사용법

C++의 std::weak_ptr는 공유된 소유권(std::shared_ptr)의 문제를 해결하기 위해 도입된 스마트 포인터이다.이 스마트 포인터는 참조 카운팅을
증가시키지 않아 순환 참조 문제를 방지 할 수 있다.하지만, std::weak_ptr는 객체에 대한 '약한' 참조만을 제공하므로, 객체에 직접 접근하려면 먼저
std::shared_pr로 변환해야 한다.이를 '락(lock)'이라고 부른다.

먼저, std::weak_ptr을 생성하는 방법이다.std::weak_ptr는 기본적으로 std::shared_ptr 에서 생성된다.

ex)
std::shared_ptr<int> sp(new int(10));
std::weak_ptr<int> wp(sp));

위의 코드에서 wp는 sp가 소유한 객체를 가리키지만, 이는 '약한' 참조이므로 sp의 참조 카운트를 증가시키지 않는다. 즉, wp는 객체의 소유권을 가지지
않는다.

객체에 접근 하려면, 먼저 std::shared_ptr로 변환해야 한다. 이를 위해 std::weak_ptr의 lock메서드를 사용한다.

ex)

if (std::shared_ptr<int>sp = wp.lock()) // lock 메서드로 shared_ptr획득
{
	//객체에 접근
}

lock 메서드는 해당 객체가 아직 메모리에 있을 때 std::shared_ptr룰 반환하며, 그렇지 않을 때는 빈 std::shared_ptr를 반환한다. 따라서 lock
메서드를 사용하여 객체가 메모리에 있는지 확인 할 수 있다.

또한 std::weak_ptr는 expired 메소드를 제공하여 객체가 메모리에 있는지 확인 할 수 있다.

ex)
if (wp.expired())
{
	// 객체는 더 이상 메모리에 없음
}

하지만, 이 메소드는 객체의 상태를 확인하고 객체에 접근하는 사이에 객체가 해제 될 수 있으므로, 안전한 객체 접근을 위해서는 항상 lock 메서드를
사용해야 한다.

3. weak_ptr와 순환 참조 문제

스마트 포인터는 메모리 관리를 현하게 해주지만, std::shared_ptr를 사용할 때 주의 해야 할 주요한 문제가 있다.바로 '순환참조(circular
reference)' 문제이다. 이 문제는 서로가 서로를 참조하는 두개의 std::shared_ptr 객체가 있을 떄 발생한다. 이렇게 되면 참조 카운트는 결코 0이
될 수 없으므로, 이러한 객체들은 메모리에서 절대 해제되지 않게 된다.이것이 바로 메모리 누수(memory leak)를 일으키는 원인이 된다.

이 문제를 해결하기 위해서 std::weak_ptr가 등장했다.std::weak_ptr는 std::shared_ptr와 달리 참조 카운트를 증가시키지 않기 때문에 순환 참조를
방지 할 수 있다.

4. weak_ptr의 예제 코드와 활용법
weak_ptr는 std::shared_ptr와 함께 사용되여 순호나 참조 문제를 해결하고, 특정 객체가 여전히 메모리에 존재하는지 판단 할 수 있는 방법을 제공
한다.그렇다면 이제 std::weak_ptr의 기본적인 사용법과 예제 코드를 통해 실제로 어떻게 활용할 수 있는지 알아보자.

먼저, std::weak_ptr는 기본적으로 std::shared_ptr에서 생성된다.

ex)
std::shared_ptr<int> sp(new int(10));
std::weak_ptr<int> wp = sp;

위의 코드에서 wp는 sp로 부터 생성된 std::weak_ptr이다.이때 wp는 sp가 가리키는 메모리에 대한 약한 참조(weak reference)를 가지게 된다.그러나
wp는 참조 카운트를 증가시키지 않으므로, sp가 소멸되면 wp는 더 이상 유효한 참조를 가지지 않게 된다.

그럼에도 불구하고 wp를 통해 안전하게 메모리에 접근하려면 어떻게 해야 할까요 ? 여기서는 std::weak_ptr의 lock함수를 사용 할 수 있다.lock 함수는
std::shared_ptr를 반환하며, 이 std::shared_ptr를 통해 안전하게 메모리에 접근 할 수 있다.

ex)
std::shared_ptr<int> sp(new int(10));
std::weak_ptr<int> wp = sp;

if (auto p = wp.lock()) //wp가 유효한지 확인하고, 유효하다면 shared_ptr를 얻는다.
{	// 안전하게 메모리에 접근 할 수 있다.
	std::cout << *p << std::endl;
}
else
{	// wp가 더이상 유효하지 않는 상태
	std::cout << "wp is no longer valid << std::endl";
}

5. weak_ptr 예외 처리

C++에서 std::weak_ptr를 사용하면서 예외 처리를 적절히 하는 것은 매우 종요하다.이는 weak_ptr가 가리키는 메모리에 접근 할 수 없을 때 생기는
예외 상황을 처리하기 위함이다.

std::weak_ptr는 std::shared_ptr가 가리키는 메모리에 대한 약한 참조를 가지므로, std::shared_ptr가 소멸 되면 std::weak_ptr는 더이상 유효한
참조를 가지지 않게 된다.이렇게 std::weak_ptr가 더 이상 유효하지 않은 상태에서 메모리에 접근하려고 하면 문제가 발생한다.

std::weak_ptr에서 제공하는 lock 함수를 이용하면 안전하게 메모리에 접근 할 수 있다.lock 함수는 std::shared_ptr를 반환하며, 이 std::shared_ptr
를 통해 메모리에 접근 할 수 있다.만약 std::weak_ptr가 유효하지 않다면 lock 함수는 nullptr를 가리키는 std::shared_ptr를 반환한다.

ex)
std::shared_ptr<int> sp(new int()10);
std::weak_ptr<int>wp = sp;

sp.reset();	// sp를 reset하여 메모리를 해제한다.

if (auto p = wp.lock())
{
	std::cout << *p << std::endl;
}

else
{
	std::cout << "wp is no longer valid" << std::endl;
}

위의 코드에서 wp.lock()은 std::shared_ptr를 반환한다. 만약 wp가 유효하다면 이 std::shared_ptr를 통해 메모리에 안전하게 접근 할 수 있다.
반면 wp가 더 이상 유효하지 않다면, lock 함수는 nullptr를 가리키는 std::shared_ptr를 반환하므로 안전하게 예외 상황을 처리 할 수 있다.

이처럼 std::weak_ptr는 lock 함수를 통해 안전하게 메모리에 접근 할 수 있게 해 주며, 더 이상 유효하지 않는 참조에 대한 예외 상황을 적절히 처리
할 수 있다. 이러한 기능은 메모리 관리를 더욱 안전하고 효율적으로 만들어 준다.

마지막으로, std::weak_ptr는 수환 참조와 같은 문제를 방지하면서도 동시에 안전하게 메모리를 관리 할 수 있게 해주는 매우 유용한 도구이다. 이를
적절히 활용하여 프로그램의 안정성을 높일 수 있다.

[사용자 정의 스마트 포인터]
C++에서는 사용자 정의 스마트 포인터를 생성하여 프로그램의 특정 요구사항을 충족시킬 수 있다. 사용자 정의 스마트 포인터는 기본 제공되는
std::unique_ptr, std::shared_ptr, std::weak_ptr등으로 충분하지 않은 경우에 유용하게 사용 할 수 있다. 이를 만들기 위해서는 연산자 오버로딩,
생성자와 소멸자의 적절한 사용, 복사 생성자와 복사 대입 연산자의 관리 등에 대한 깊은 이해가 필요하다. 사용자 정의 스마트 포인터는 메모리 뿐
아니라, 네트워크 연결이나 파일 핸들 등 다양한 자원을 관리 하는 데에도 활용 할 수 있다.

1. 사용자 정의 스마트 포인터 구현하기

우선, 사용자 정의 스마트 포인터가 필요한 이유를 알아보자. C++의 STL라이브러리는 이미 스마트 포인터 라이브러리를 제공하지만, 때로는 특정 요구
사항을 충족하기 위해 사용자 정의 스마트 포인터를 만드는 것이 필요하다.

사용자 정의 므사트 포인터를 만드는 기본적인 원칙은 소유권 정책을 구현하는 것이다. 즉, 언제 메로리를 할당하고, 언제 메모리를 해제할지에 대한
로직을 만드는 것이다. 이것은 포인터의 생명주기를 관리하는 기능을 갖춘 클래스를 구현함으로써 달성 할 수 있다.

가장 기본적인 사용자 정의 스마트 포인터의 구현은 다음과 같다.

ex)