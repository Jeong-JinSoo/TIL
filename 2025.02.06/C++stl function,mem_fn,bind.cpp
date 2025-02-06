Callable
Callable�̶�, �̸� �״�� ��Ÿ���� ȣ��(Call) �� �� �ִ� ��� ���� �ǹ��Ѵ�. ��ǥ���� ���÷� �Լ��� �� �� �ִ�.
������ C++������ ()�� �ٿ��� ȣ�� �� �� �ִ� ��� ���� Callable�̶�� ���� �Ѵ�.
���� ���

#include <iostream>


struct S {
	void operator()(int a, int b) { std::cout << "a + b = " << a + b << std::endl; }
};

int main() {
	S some_obj;

	some_obj(3, 5);
}

���⼭ same_obj�� �Լ� �ϱ�? �ƴϴ�. ������ same_objŬ���� S�� ��ü�̴�. �׷��� same_obj�� �Լ�ó�� ()��
�̿��ؼ� ȣ�� �� �� �ִ�. (�����δ� same_obj.operator()(3, 5)�� �Ѱ��̰�.)

�� �ٸ� ���÷� ���� �Լ��� ����.

#include <iostream>

int main() {
	auto f = [](int a, int b) { std::cout << "a + b = " << a + b << std::endl; };
	f(3, 5);
}

f���� �Ϲ����� �Լ��� ���� �ϰ� ������ ������, ()�� ���ؼ� ȣ�� �� �� �ֱ⿡ Callable�̶� �� �� �ִ�.

std::function
C++������ �̷��� Callable���� ��ü�� ���·� ���� �� �� �ִ� std::function�̶�� Ŭ������ �����Ѵ�.
C������ �Լ� �����ʹ� ��¥ �Լ��鸸 ������ �� �ִ� ��ü��� �� �� �ִٸ�, �� std::function�� ��� �Լ� �Ӹ���
�ƴ϶� ��� Callable���� ���� �� �� �ִ� ��ü�̴�.
�� std::function�� ��� ����� �� �ִ��� �Ʒ��� ���ø� ���� ����.

#include <functional>
#include <iostream>
#include <string>

int some_func1(const std::string& a) {
	std::cout << "Func1 ȣ��! " << a << std::endl;
	return 0;
}

struct S {
	void operator()(char c) { std::cout << "Func2 ȣ��! " << c << std::endl; }
};

int main() {
	std::function<int(const std::string&)> f1 = some_func1;
	std::function<void(char)> f2 = S();
	std::function<void()> f3 = []() { std::cout << "Func3 ȣ��! " << std::endl; };

	f1("hello");
	f2('c');
	f3();
}

�ϴ� ���� ���� function ��ü�� �����ϴ� �κк��� ���캸��. function��ü�� ���ø� ���ڷ� ���� ���� �Լ���
Ÿ���� ���� �ȴ�. ���⼭ �Լ��� Ÿ���̶� �ϸ�, ���ϰ��� �Լ��� ���ڵ��� ���Ѵ�.

���� ���� ��� some_func1�� ��� int�� �����ϸ�, ���ڷ� const string&�� �ޱ� ������ ���� ����
std::function<int(const stirng&)>�� ���·� ���ǵȴ�.

���� Functor�� Ŭ���� S�� ��ü�� ��� �ܼ��� S�� ��ü�� �����ص� �̸� ��ġ �Լ� �ξ� �ް� �ȴ�. S�� ���
operator()�� ���ڷ� char�� �ް� ����Ÿ���� void�̹Ƿ� std::function<void(char)>�� ǥ�� �Ҽ� �ְ� �ȴ�.

���������� ���� �Լ��� ��� ���������� ���ϰ��� ���� ���ڸ� ���� �ʱ� ������ std::function<void()>�� ���ǵȴ�.

�̷��� std::function�� c++�� ��� Callable�� ������� ���� �� �� �ִ� ������ ��ü�̴�. ���� �Լ� �����ͷ�
�̸� �����Ϸ��� �ߴٸ� Functor�� ���� ��츦 ���������� ���� �ϱ� ��ư���.

��� �Լ��� ������ std::function
�ռ� function�� �Ϲ����� Callable ���� ���� ���� �� �� �־�����, ��� �Լ����� ��� �̾߱Ⱑ ���� �޶�����.
�ֳ��ϸ�, ��� �Լ� ������ this�� ��� �ڽ��� ȣ���� ��ü�� �ǹ��ϱ� ������, ���� ��� �Լ��� �׳� function��
�ְ� �ȴٸ� this�� �������� �� �� ���� ������ �߻��ϰ� �ȴ�.

���ø� ����
#include <functional>
#include <iostream>
#include <string>

class A {
	int c;

public:
	A(int c) : c(c) {}
	int some_func() { std::cout << "���� ������ : " << c << std::endl; }
};

int main() {
	A a(5);
	std::function<int()> f1 = a.some_func;
}
�̰� ������ �ϸ� ������ ���� ������ �߻��Ѵ�.

-----------------------------------------------------------------------------
test2.cc: In function 'int main()' :
	test2.cc : 17 : 26 : error : invalid use of non - static member function 'int A::some_func()'
	std::function<int()> f1 = a.some_func;
~~^ ~~~~~~~~
test2.cc:10 : 9 : note : declared here
int some_func() {
	^ ~~~~~~~~
-----------------------------------------------------------------------------
�ֳĸ� f1�� ȣ�� ������, �Լ��� ���忡���� �ڽ��� ȣ���ϴ� ��ü�� �������� �� ���� ���� ������ C�� ���� �Ͽ��� ��
� ��ü�� c������ �� �� ����. ���� �� ��� f1�� a�� ���� ������ �߰��� �����ؾ� �Ѵ�.

�׷��ٸ� �̸� ��� �ؾ� �ұ�? ��� ��� �Լ����� ���� �� �ڽ��� ȣ���� ��ü�� ���ڷ� �Ϲ������� �ް� �ִ�.
���� �̸� �޴� function�� �Ʒ��� ���� ���·� ��Ÿ���� �Ѵ�.

#include <functional>
#include <iostream>
#include <string>

class A {
		int c;

public:
	A(int c) : c(c) {}
	int some_func() {
		std::cout << "���� �Լ�: " << ++c << std::endl;
		return c;
	}

	int some_const_function() const {
		std::cout << "��� �Լ�: " << c << std::endl;
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

���� ���� ���� ���ڿ� �߰������� ��ü�� �޴� ���ڸ� �������ָ� �ȴ�. �� �� ��� �Լ��� ��� �翩�� ��� ���·�
���ڸ� �޾ƾ� �ϰ� (cosnt A&), �ݸ鿡 ��� �Լ��� �ƴ� ��� �ܼ��� A&�� ���·� ���ڸ� ������ �ȴ�.

����� ������ �Լ������ �ٸ��� &A::some_func�� ���� �Լ��� �̸� �����δ� �� �ּҰ��� ���� �� �� ����. �̴� C++
��� ��Ģ ������ �׷�������, ��� �Լ��� �ƴ� ��� �Լ����� ��� �Լ��� �̸��� �Լ��� �ּҰ����� �Ͻ��� ��ȯ��
�Ͼ����, ��� �Լ��� ��� �Ͻ��� ��ȯ�� �߻����� �����Ƿ� & �����ڸ� ���� ��������� �ּ��� ���� ���� ����� �Ѵ�.

���� �Ʒ��� ���� ȣ���ϰ��� �ϴ� ��ü�� ���ڷ� �������ָ� ��ġ �ش� ��ü�� ��� �Լ��� ȣ���� �Ͱ� ���� ȿ����
�� �� �ִ�.

��� �Լ����� �Լ� ��ü�� - mem_fn
���� �� vector���� ������ vector�� ���� ��, ������ vector���� ũ����� ���ͷ� ����� �ִ� �ڵ带 �����غ���.

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
		std::cout << "���� ũ�� :: " << *itr << std::endl;
	}
}

transform �Լ��� <algorithm> ���̺귯���� �ִ� �Լ��ε�, �� ���ҵ鿡 ���� ���ڷ� ���޵� �Լ��� �����Ų ����
�� ����� ���޵� �����̳ʿ� �־��ش�. �Լ� ���Ǹ� ��¦ ���캸�� �Ʒ��� ����.

template <class InputIt, class OutputIt, class UnaryOperation>
OutputIt transform(InputIt first1, InputIt last1, OutputIt d_first,
	UnaryOperation unary_op) {
	while (first1 != last1) {
		*d_first++ = unary_op(*first1);
		first1++;
	}
	return d_first;
}

���⼭ ������ �ش� �Լ��� �Ʒ��� ���� ȣ���Ѵٴ� ���̴�.
* d_first++ = unary_op(*first1);

unray_op �� �ɹ� �Լ��� �ƴ� ��� ���� ���� ȣ���ص� ������. ������ ������ unary_op�� ��� �Լ��� ����̴�.
�� �ڵ带 ������ �ϸ� �Ʒ��� ���� ���簡 �߻��Ѵ�.
-----------------------------------------------------------------------------
In file included from / usr / include / c++ / 7 / algorithm:62 : 0,
from test2.cc : 5 :
	/ usr / include / c++ / 7 / bits / stl_algo.h : In instantiation of '_OIter std::transform(_IIter, _IIter, _OIter, _UnaryOperation) [with _IIter = __gnu_cxx::__normal_iterator<std::vector<int>*, std::vector<std::vector<int> > >; _OIter = __gnu_cxx::__normal_iterator<int*, std::vector<int> >; _UnaryOperation = long unsigned int (std::vector<int>::*)() const noexcept]' :
	test2.cc : 21 : 85 : required from here
	/ usr / include / c++ / 7 / bits / stl_algo.h : 4306 : 24 : error : must use '.*' or '->*' to call pointer - to - member function in '__unary_op (...)', e.g. '(... ->* __unary_op) (...)'
	* __result = __unary_op(*__first);
~~~~~~~~~~^ ~~~~~~~~~
---------------------------------------------------------------------------- -

��°�� �ϱ�? �� ���� ���޵� size �Լ��� ��� �Լ����� �߻��ϴ� �����̴�.�� ���ø��� & vector<int>::size��
���ٸ� �ش� unary_op�� ȣ���ϴ� �κ��� �Ʒ��� ���� ��ȯ�ȴ�.

unary(*first1);

�̰���

& vector<int>::size(*first);

�÷� �Ǵµ�, ��� �Լ��� ���

(*first).(*&vector<int>::size)

Ȥ��

first->(*&vector<int>::size)

�� ���� ȣ���ؾ� �Ѵ�. (�̴� C++�� ��Ģ�̶�� �����ϸ� �ȴ�.)
���� �̸� ���ؼ��� ����� std::function���� ��ȯ�ؼ� ��������� �Ѵ�.

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
		std::cout << "���� ũ�� :: " << *itr << std::endl;
	}
}

������ �Ź� �� ó�� function ��ü�� ���� ���� ���� �ϴ� ���� ���ŷο� ���̴�. ���� C++ �����ڵ���
���̺귯���� �� function ��ü�� ���� �ع����� �Լ��� �߰��ߴ�.

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
		std::cout << "���� ũ�� :: " << *itr << std::endl;
	}
}

�� �ڵ带 ���� �غ��� mem_fn �Լ��� �̸� �״��, ���޵� ��� �Լ��� function��ü�� ���ڰ� ���� �����Ѵ�.
**���� ����**
����� mem_fn �� �׸� ���� �������� �ʴµ�, ���� �Լ��ε� ������ �۾��� ������ �� �ֱ� �����̴�.�� �ڵ���
��� mem_fn(&vector<int>::size) ��ſ�[](const auto& v) { return v.size() } �� �����ص� ������ �۾���
�����Ѵ�. mem_fn �� ����ϱ� ���ؼ��� <functional> ����� �߰��ؾ� ������ �����Լ��� �׳� �� �� ������ ��
�� ���� ���� �ִ�.����, �ڵ� ���� �鿡���� mem_fn �� ����ϴ� ���� ���� ����� ���̰�..

std::bind
�Լ� ��ü ���� �� ���ڸ� Ư���� ������ ���� �� �� �� �ִ�. 
�Ʒ��� ������ ����.

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

	// �� ��° ���ڴ� ���õȴ�.
	add_with_2(3, 4);

	auto subtract_from_2 = std::bind(subtract, std::placeholders::_1, 2);
	auto negate =
		std::bind(subtract, std::placeholders::_2, std::placeholders::_1);

	subtract_from_2(3);  // 3 - 2 �� ����Ѵ�.
	negate(4, 2);        // 2 - 4 �� ����Ѵ�
}

bind �Լ��� �̸� �״�� ���� �Լ��� Ư�����ڸ� �ٿ�(bind) �ش�. ���� ��
std::bind(add, 2, std::placeholders::_1);
�� ��� add��� �Լ��� ù��° ���ڷ� 2�� bind �����ְ�, �� ��° ���ڷδ� ���Ӱ� ������� �Լ� ��ü�� ù��°
���ڸ� ���� ���ش�. ����

---------------------------------------------------------------
add_with_2(3);
---------------------------------------------------------------

�� ������, ���� add �Լ��� ù��° ���ڷδ� 2�� ���� �ǰ�, �ι�° ���ڷδ� add_with_2�� ù ��° ������
3�� ����. ���࿡

---------------------------------------------------------------
add_with_2(3, 4);
---------------------------------------------------------------

ó�� ���ڸ� ������ ���� �ϴ��� ���� �͵��� ���� �ȴ�.

---------------------------------------------------------------
auto negate = std::bind(subtract, std::placeholders::_2, std::placeholders::_1);
---------------------------------------------------------------

�� ���� ���? negate �Լ��� ù ��° ���ڿ� �� ��° ������ ������ �ٲ㼭 subtract �Լ��� ȣ���ϰ� �ȴ�.
�� negate(3,5)�� ȣ���� ��� �����δ� subtract(5,3)�� ȣ��ȴ�.
placeholders�� _1, _2���� ������ ���ǵ� ��ü���̴�. �� ������ ���̺귯�� ���� �ٸ���, libstdc++�� ���
_1���� _29���� ���ǵǾ� �ִ�.

�� ���� ���� �� ����, ���۷����� ���ڷ� �޴� �Լ����� ����̴�.

#include <functional>
#include <iostream>

struct S {
	int data;
	S(int data) : data(data) { std::cout << "�Ϲ� ������ ȣ��!" << std::endl; }
	S(const S& s) {
		std::cout << "���� ������ ȣ��!" << std::endl;
		data = s.data;
	}

	S(S&& s) {
		std::cout << "�̵� ������ ȣ��!" << std::endl;
		data = s.data;
	}
};

void do_something(S& s1, const S& s2) { s1.data = s2.data + 3; }

int main() {
	S s1(1), s2(2);

	std::cout << "Before : " << s1.data << std::endl;

	// s1 �� �״�� ���޵� ���� �ƴ϶� s1 �� ���纻�� ���޵�!
	auto do_something_with_s1 = std::bind(do_something, s1, std::placeholders::_1);
	do_something_with_s1(s2);

	std::cout << "After :: " << s1.data << std::endl;
}

do_somthing �Լ��� ��� ù��° ������ data�� �� ��°������ data + 3���� ����� ������, ������
do_somthing_with_sl�Լ��� �����Ͽ��� �� ù��° ���ڷ� s1�� ���� �������� �ұ��ϰ� s1�� data�� �ٲ��� ������
�� �� �ִ�.

�� ������ �� ������ ȣ�� �޼������� Ȯ�� �� �� �ֵ���, bind �Լ��� ���ڰ� ���� �Ǽ� ���޵Ǳ� �����̴�. ����
�̸� �ذ� �ϱ� ���ؼ��� ��������� s1�� ���۷����� ��������� �Ѵ�.

#include <functional>
#include <iostream>

struct S {
	int data;
	S(int data) : data(data) { std::cout << "�Ϲ� ������ ȣ��!" << std::endl; }
	S(const S& s) {
		std::cout << "���� ������ ȣ��!" << std::endl;
		data = s.data;
	}

	S(S&& s) {
		std::cout << "�̵� ������ ȣ��!" << std::endl;
		data = s.data;
	}
};

void do_something(S& s1, const S& s2) { s1.data = s2.data + 3; }

int main() {
	S s1(1), s2(2);

	std::cout << "Before : " << s1.data << std::endl;

	// s1 �� �״�� ���޵� ���� �ƴ϶� s1 �� ���纻�� ���޵�!
	auto do_something_with_s1 =
		std::bind(do_something, std::ref(s1), std::placeholders::_1);
	do_something_with_s1(s2);

	std::cout << "After :: " << s1.data << std::endl;
}

�� ���� ������ s1�� ���� �� �ٲ������ �� �� �ִ�. ref �Լ��� ���� ���� ���ڸ� ���� ������ ���۷����� ��ȯ
���ش�. ���� bind �Լ� ������ s1�� ���۷����� �� ���� �� �� �ְ� �ȴ�. 

����� const ���۷����� ��� cref �Լ��� ȣ���ϸ� �ȴ�.