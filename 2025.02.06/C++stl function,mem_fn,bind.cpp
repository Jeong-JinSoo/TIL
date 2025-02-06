Callable
Callable이란, 이름 그대로 나타내듯 호출(Call) 할 수 있는 모든 것을 의미한다. 대표적인 예시로 함수를 들 수 있다.
하지만 C++에서는 ()를 붙여서 호출 할 수 있는 모든 것을 Callable이라고 정의 한다.
예를 들어

#include <iostream>


struct S {
	void operator()(int a, int b) { std::cout << "a + b = " << a + b << std::endl; }
};

int main() {
	S some_obj;

	some_obj(3, 5);
}

여기서 same_obj는 함수 일까? 아니다. 하지만 same_obj클래스 S의 객체이다. 그러나 same_obj는 함수처럼 ()를
이용해서 호출 할 수 있다. (실제로는 same_obj.operator()(3, 5)를 한것이고.)

또 다른 예시로 람다 함수를 보자.

#include <iostream>

int main() {
	auto f = [](int a, int b) { std::cout << "a + b = " << a + b << std::endl; };
	f(3, 5);
}

f역시 일반적인 함수의 꼴은 하고 있지는 않지만, ()를 통해서 호출 할 수 있기에 Callable이라 할 수 있다.

std::function
C++에서는 이러한 Callable들을 객체의 형태로 보관 할 수 있는 std::function이라는 클래스를 제공한다.
C에서의 함수 포인터는 진짜 함수들만 보관할 수 있는 객체라고 볼 수 있다면, 이 std::function의 경우 함수 뿐만이
아니라 모든 Callable들을 보관 할 수 있는 객체이다.
이 std::function을 어떻게 사용할 수 있는지 아래의 예시를 통해 보자.

#include <functional>
#include <iostream>
#include <string>

int some_func1(const std::string& a) {
	std::cout << "Func1 호출! " << a << std::endl;
	return 0;
}

struct S {
	void operator()(char c) { std::cout << "Func2 호출! " << c << std::endl; }
};

int main() {
	std::function<int(const std::string&)> f1 = some_func1;
	std::function<void(char)> f2 = S();
	std::function<void()> f3 = []() { std::cout << "Func3 호출! " << std::endl; };

	f1("hello");
	f2('c');
	f3();
}

일단 위와 같이 function 객체를 정의하는 부분부터 살펴보자. function객체는 템플릿 인자로 전달 받을 함수의
타입을 갖게 된다. 여기서 함수의 타입이라 하면, 리턴값과 함수의 인자들을 말한다.

따라서 예를 들어 some_func1의 경우 int를 리턴하며, 인자로 const string&을 받기 때문에 위와 같이
std::function<int(const stirng&)>의 형태로 정의된다.

한편 Functor인 클래스 S의 객체의 경우 단순히 S의 객체를 전달해도 이를 마치 함수 인양 받게 된다. S의 경우
operator()가 인자로 char을 받고 리턴타입이 void이므로 std::function<void(char)>로 표현 할수 있게 된다.

마지막으로 람다 함수의 경우 마찬가지로 리턴값이 없고 인자를 받지 않기 때문에 std::function<void()>로 정의된다.

이렇듯 std::function은 c++의 모든 Callable을 마음대로 보관 할 수 있는 유용한 객체이다. 만약 함수 포인터로
이를 구현하려고 했다면 Functor와 같은 경우를 성공적으로 보관 하기 어렵겠지.

멤버 함수를 가지는 std::function
앞서 function은 일반적은 Callable 들을 쉽게 보관 할 수 있었지만, 멤버 함수들의 경우 이야기가 조금 달라진다.
왜냐하면, 멤버 함수 내에서 this의 경우 자신을 호출한 객체를 의미하기 때문에, 만일 멤버 함수를 그냥 function에
넣게 된다면 this가 무엇인지 알 수 없는 문제가 발생하게 된다.

예시를 보자
#include <functional>
#include <iostream>
#include <string>

class A {
	int c;

public:
	A(int c) : c(c) {}
	int some_func() { std::cout << "내부 데이터 : " << c << std::endl; }
};

int main() {
	A a(5);
	std::function<int()> f1 = a.some_func;
}
이걸 컴파일 하면 다음과 같은 오류가 발생한다.

-----------------------------------------------------------------------------
test2.cc: In function 'int main()' :
	test2.cc : 17 : 26 : error : invalid use of non - static member function 'int A::some_func()'
	std::function<int()> f1 = a.some_func;
~~^ ~~~~~~~~
test2.cc:10 : 9 : note : declared here
int some_func() {
	^ ~~~~~~~~
-----------------------------------------------------------------------------
왜냐면 f1을 호출 했을때, 함수의 입장에서는 자신을 호출하는 객체가 무엇인지 알 길이 없기 때문에 C를 참조 하였을 때
어떤 객체의 c인지를 알 수 없다. 따라서 이 경우 f1에 a에 관한 정보도 추가로 전달해야 한다.

그렇다면 이를 어떻게 해야 할까? 사실 멤버 함수들은 구현 상 자신을 호출한 객체를 인자로 암묵적으로 받고 있다.
따라서 이를 받는 function은 아래와 같은 형태로 나타나야 한다.

#include <functional>
#include <iostream>
#include <string>

class A {
		int c;

public:
	A(int c) : c(c) {}
	int some_func() {
		std::cout << "비상수 함수: " << ++c << std::endl;
		return c;
	}

	int some_const_function() const {
		std::cout << "상수 함수: " << c << std::endl;
		return c;
	}

	static void st() {}
	};

	int main() {
		A a(5);
		std::function<int(A&)> f1 = &A::some_func;
		std::function<int(const A&)> f2 = &A::some_const_function;

		f1(a);
		f2(a);
	}

std::function<int(A&)> f1 = &A::some_func;
std::function<int(const A&)> f2 = &A::some_const_function;

위와 같이 원래 인자에 추가적으로 객체를 받는 인자를 전달해주면 된다. 이 때 상수 함수의 경우 당여니 상수 형태로
인자를 받아야 하고 (cosnt A&), 반면에 상수 함수가 아닌 경우 단순히 A&의 형태로 인자를 받으면 된다.

참고로 이전의 함수들과는 다르게 &A::some_func와 같이 함수의 이름 만으로는 그 주소값을 전달 할 수 없다. 이는 C++
언어 규칙 떄문에 그런것으로, 멤버 함수가 아닌 모든 함수들의 경우 함수의 이름이 함수의 주소값으로 암시적 변환이
일어나지만, 멤버 함수의 경우 암시적 변환이 발생하지 않으므로 & 연산자를 통해 명시적으로 주소의 값을 전달 해줘야 한다.

따라서 아래와 같이 호출하고자 하는 객체를 인자로 전달해주면 마치 해당 객체의 멤버 함수를 호출한 것과 같은 효과를
낼 수 있다.

멤버 함수들을 함수 객체로 - mem_fn
예를 들어서 vector들을 가지는 vector가 있을 때, 각각의 vector들의 크기들을 벡터로 만들어 주는 코드를 생각해보자.

#include <algorithm>
#include <functional>
#include <iostream>
#include <vector>
using std::vector;

int main() {
	vector<int> a(1);
	vector<int> b(2);
	vector<int> c(3);
	vector<int> d(4);

	vector<vector<int>> container;
	container.push_back(b);
	container.push_back(d);
	container.push_back(a);
	container.push_back(c);

	vector<int> size_vec(4);
	std::transform(container.begin(), container.end(), size_vec.begin(),
		&vector<int>::size);
	for (auto itr = size_vec.begin(); itr != size_vec.end(); ++itr) {
		std::cout << "벡터 크기 :: " << *itr << std::endl;
	}
}

transform 함수는 <algorithm> 라이브러리에 있는 함수인데, 각 원소들에 대해 인자로 전달된 함수를 실행시킨 다음
그 결과를 전달된 컨테이너에 넣어준다. 함수 정의를 살짝 살펴보면 아래와 같다.

template <class InputIt, class OutputIt, class UnaryOperation>
OutputIt transform(InputIt first1, InputIt last1, OutputIt d_first,
	UnaryOperation unary_op) {
	while (first1 != last1) {
		*d_first++ = unary_op(*first1);
		first1++;
	}
	return d_first;
}

여기서 문제는 해당 함수를 아래와 같이 호출한다는 점이다.
* d_first++ = unary_op(*first1);

unray_op 가 맴버 함수가 아닐 경우 위와 같이 호출해도 괜찮다. 하지만 문제는 unary_op가 멤버 함수일 경우이다.
위 코드를 컴파일 하면 아래와 같은 오루가 발생한다.
-----------------------------------------------------------------------------
In file included from / usr / include / c++ / 7 / algorithm:62 : 0,
from test2.cc : 5 :
	/ usr / include / c++ / 7 / bits / stl_algo.h : In instantiation of '_OIter std::transform(_IIter, _IIter, _OIter, _UnaryOperation) [with _IIter = __gnu_cxx::__normal_iterator<std::vector<int>*, std::vector<std::vector<int> > >; _OIter = __gnu_cxx::__normal_iterator<int*, std::vector<int> >; _UnaryOperation = long unsigned int (std::vector<int>::*)() const noexcept]' :
	test2.cc : 21 : 85 : required from here
	/ usr / include / c++ / 7 / bits / stl_algo.h : 4306 : 24 : error : must use '.*' or '->*' to call pointer - to - member function in '__unary_op (...)', e.g. '(... ->* __unary_op) (...)'
	* __result = __unary_op(*__first);
~~~~~~~~~~^ ~~~~~~~~~
---------------------------------------------------------------------------- -

어째서 일까? 이 역시 전달된 size 함수가 멤버 함수여서 발생하는 문제이다.위 템플릿에 & vector<int>::size가
들어간다면 해당 unary_op를 호출하는 부분은 아래와 같이 변환된다.

unary(*first1);

이것이

& vector<int>::size(*first);

꼴로 되는데, 멤버 함수의 경우

(*first).(*&vector<int>::size)

혹은

first->(*&vector<int>::size)

와 같이 호출해야 한다. (이는 C++의 규칙이라고 생각하면 된다.)
따라서 이를 위해서는 제대로 std::function으로 변환해서 전달해줘야 한다.

#include <algorithm>
#include <functional>
#include <iostream>
#include <vector>
using std::vector;

int main() {
	vector<int> a(1);
	vector<int> b(2);
	vector<int> c(3);
	vector<int> d(4);

	vector<vector<int>> container;
	container.push_back(a);
	container.push_back(b);
	container.push_back(c);
	container.push_back(d);

	std::function<size_t(const vector<int>&)> sz_func = &vector<int>::size;

	vector<int> size_vec(4);
	std::transform(container.begin(), container.end(), size_vec.begin(), sz_func);
	for (auto itr = size_vec.begin(); itr != size_vec.end(); ++itr) {
		std::cout << "벡터 크기 :: " << *itr << std::endl;
	}
}

하지만 매번 위 처럼 function 객체를 빠로 만들어서 전달 하는 것은 번거로운 일이다. 따라서 C++ 개발자들은
라이브러리에 위 function 객체를 리턴 해버리는 함수를 추가했다.

#include <algorithm>
#include <functional>
#include <iostream>
#include <vector>
using std::vector;

int main() {
	vector<int> a(1);
	vector<int> b(2);
	vector<int> c(3);
	vector<int> d(4);

	vector<vector<int>> container;
	container.push_back(a);
	container.push_back(b);
	container.push_back(c);
	container.push_back(d);

	vector<int> size_vec(4);
	transform(container.begin(), container.end(), size_vec.begin(),
		std::mem_fn(&vector<int>::size));
	for (auto itr = size_vec.begin(); itr != size_vec.end(); ++itr) {
		std::cout << "벡터 크기 :: " << *itr << std::endl;
	}
}

위 코드를 실행 해보면 mem_fn 함수는 이름 그대로, 전달된 멤버 함수를 function객체로 예쁘게 만들어서 리턴한다.
**주의 사항**
참고로 mem_fn 은 그리 자주 쓰이지는 않는데, 람다 함수로도 동일한 작업을 수행할 수 있기 때문이다.위 코드의
경우 mem_fn(&vector<int>::size) 대신에[](const auto& v) { return v.size() } 를 전달해도 동일한 작업을
수행한다. mem_fn 을 사용하기 위해서는 <functional> 헤더를 추가해야 하지만 람다함수는 그냥 쓸 수 있으니 좀
더 편리한 면이 있다.물론, 코드 길이 면에서는 mem_fn 을 사용하는 것이 좀더 깔끔한 편이고..

std::bind
함수 객체 생성 시 인자를 특정한 것으로 지정 할 수 도 있다. 
아래의 예제를 보자.

#include <functional>
#include <iostream>

void add(int x, int y) {
	std::cout << x << " + " << y << " = " << x + y << std::endl;
}

void subtract(int x, int y) {
	std::cout << x << " - " << y << " = " << x - y << std::endl;
}
int main() {
	auto add_with_2 = std::bind(add, 2, std::placeholders::_1);
	add_with_2(3);

	// 두 번째 인자는 무시된다.
	add_with_2(3, 4);

	auto subtract_from_2 = std::bind(subtract, std::placeholders::_1, 2);
	auto negate =
		std::bind(subtract, std::placeholders::_2, std::placeholders::_1);

	subtract_from_2(3);  // 3 - 2 를 계산한다.
	negate(4, 2);        // 2 - 4 를 계산한다
}

bind 함수는 이름 그대로 원래 함수에 특정인자를 붙여(bind) 준다. 예를 들어서
std::bind(add, 2, std::placeholders::_1);
의 경우 add라는 함수에 첫번째 인자로 2를 bind 시켜주고, 두 번째 인자로는 새롭게 만들어진 함수 객체의 첫번째
인자를 전달 해준다. 따라서

---------------------------------------------------------------
add_with_2(3);
---------------------------------------------------------------

를 했을때, 원래 add 함수의 첫번째 인자로는 2가 들어가게 되고, 두번째 인자로는 add_with_2의 첫 번째 인자인
3이 들어간다. 만약에

---------------------------------------------------------------
add_with_2(3, 4);
---------------------------------------------------------------

처럼 인자를 여러개 전달 하더라도 위에 것들은 무시 된다.

---------------------------------------------------------------
auto negate = std::bind(subtract, std::placeholders::_2, std::placeholders::_1);
---------------------------------------------------------------

위 경우는 어떨까? negate 함수는 첫 번째 인자와 두 번째 인자의 순서를 바꿔서 subtract 함수를 호출하게 된다.
즉 negate(3,5)를 호출할 경우 실제로는 subtract(5,3)이 호출된다.
placeholders의 _1, _2들은 일일히 정의된 객체들이다. 그 개수는 라이브러리 마다 다른데, libstdc++의 경우
_1부터 _29까지 정의되어 있다.

한 가지 주의 할 점은, 레퍼런스를 인자로 받는 함수들의 경우이다.

#include <functional>
#include <iostream>

struct S {
	int data;
	S(int data) : data(data) { std::cout << "일반 생성자 호출!" << std::endl; }
	S(const S& s) {
		std::cout << "복사 생성자 호출!" << std::endl;
		data = s.data;
	}

	S(S&& s) {
		std::cout << "이동 생성자 호출!" << std::endl;
		data = s.data;
	}
};

void do_something(S& s1, const S& s2) { s1.data = s2.data + 3; }

int main() {
	S s1(1), s2(2);

	std::cout << "Before : " << s1.data << std::endl;

	// s1 이 그대로 전달된 것이 아니라 s1 의 복사본이 전달됨!
	auto do_something_with_s1 = std::bind(do_something, s1, std::placeholders::_1);
	do_something_with_s1(s2);

	std::cout << "After :: " << s1.data << std::endl;
}

do_somthing 함수의 경우 첫번째 인자의 data를 두 번째인자의 data + 3으로 만들어 주지만, 실제로
do_somthing_with_sl함수를 실행하였을 때 첫번째 인자로 s1을 전달 했음에도 불구하고 s1의 data가 바뀌지 않음을
알 수 있다.

그 이유는 위 생성자 호출 메세지에서 확인 할 수 있듯이, bind 함수로 인자가 복사 되서 전달되기 때문이다. 따라서
이를 해결 하기 위해서는 명시적으로 s1의 레퍼런스를 전달해줘야 한다.

#include <functional>
#include <iostream>

struct S {
	int data;
	S(int data) : data(data) { std::cout << "일반 생성자 호출!" << std::endl; }
	S(const S& s) {
		std::cout << "복사 생성자 호출!" << std::endl;
		data = s.data;
	}

	S(S&& s) {
		std::cout << "이동 생성자 호출!" << std::endl;
		data = s.data;
	}
};

void do_something(S& s1, const S& s2) { s1.data = s2.data + 3; }

int main() {
	S s1(1), s2(2);

	std::cout << "Before : " << s1.data << std::endl;

	// s1 이 그대로 전달된 것이 아니라 s1 의 복사본이 전달됨!
	auto do_something_with_s1 =
		std::bind(do_something, std::ref(s1), std::placeholders::_1);
	do_something_with_s1(s2);

	std::cout << "After :: " << s1.data << std::endl;
}

와 같이 실제로 s1의 값이 잘 바뀌었음을 알 수 있다. ref 함수는 전달 받은 인자를 복사 가능한 레퍼런스로 변환
해준다. 따라서 bind 함수 안으로 s1의 레퍼런스가 잘 전달 될 수 있게 된다. 

참고로 const 레퍼런스의 경우 cref 함수를 호출하면 된다.