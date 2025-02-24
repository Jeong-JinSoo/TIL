#include <iostream>

//가변 길이 템플릿 (Variadic template)

template <typename T>
void print(T arg) {
	std::cout << arg << std::endl;
}

template <typename T, typename... Types>	//템플릿 파리미터 팩(parameter pack) 
void print(T arg, Types... args) {			//함수 파라미터 팩
	std::cout << arg << ", ";
	print(args...);							//파라미터 팩 확장			
}

int main() {
	print(1, 3.1, "abc");
	print(1, 2, 3, 4, 5, 6, 7);
}


/*
//sizeof 연산자는 인자의 크기를 리턴하지만
//파라미터 팩에 sizeof... 을 사용할 경우 전체 인자의 개수를 리턴하게 됩니다

	#include <iostream>
	
	int sum_all() { return 0; }					// 재귀 호출 종료를 위한 베이스 케이스

	template <typename... Ints>
	int sum_all(int num, Ints... nums) {
		return num + sum_all(nums...);			//재귀 함수 형태로 구성
	}

	template <typename... Ints>
	double average(Ints... nums) {
		return static_cast<double>(sum_all(nums...)) / sizeof...(nums);
	}

	int main() {
		// (1 + 4 + 2 + 3 + 10) / 5
		std::cout << average(1, 4, 2, 3, 10) << std::endl;
	}
*/

/*
//Fold Expression ------------------------------------------------------------------------

//가변 길이 템플릿은 매우 편리하지만 한 가지 단점이 있다.
//재귀 함수 형태로 구성해야 하기 때문에, 반드시 재귀 호출 종료를 위한 함수를 따로 만들어야 한다는 것
//C++17 에 새로 도입된 Fold 형식을 사용한다면 이를 훨씬 간단하게 표현

	#include <iostream>

	template <typename... Ints>
	int sum_all(Ints... nums) {
		return (... + nums);   //return ((((1 + 4) + 2) + 3) + 10);
	}

	int main() {
		// 1 + 4 + 2 + 3 + 10
		std::cout << sum_all(1, 4, 2, 3, 10) << std::endl;
	}

	//--------------------------------------
	#include <iostream>

	template <typename Int, typename... Ints>
	Int diff_from(Int start, Ints... nums) {
		return (start - ... - nums);
	}

	int main() {
		std::cout << diff_from(100, 1, 4, 2, 3, 10) << std::endl;	// 100 - 1 - 4 - 2 - 3 - 10
	}

	//--------------------------------------
	#include <iostream>

	class A {
	public:
		void do_something(int x) const {
			std::cout << "Do something with " << x << std::endl;
		}
	};

	template <typename T, typename... Ints>
	void do_many_things(const T& t, Ints... nums) {
		(t.do_something(nums), ...);  // 각각의 인자들에 대해 do_something 함수들을 호출한다.
	}
	int main() {
		A a;
		do_many_things(a, 1, 3, 2, 4);
	}

*/


/*
//문자열 합치기 예제 --------------------------------------

#include <cstring>
#include <iostream>
#include <string>
using namespace std;

size_t GetStringSize(const char* s) { return strlen(s); }
size_t GetStringSize(const string& s) { return s.size(); }

template <typename Str, typename... Strs>
size_t GetStringSize(const Str& s, Strs... strs) {
	return GetStringSize(s) + GetStringSize(strs...);
}

void AppendToString(string* concat_str) { return; }

template <typename Str, typename... Strs>
void AppendToString(string* concat_str, const Str& s, Strs... strs) {
	concat_str->append(s);
	AppendToString(concat_str, strs...);
}

template <typename Str, typename... Strings>
string StrCat(const Str& s, Strings... strs)
{
	size_t total_size = GetStringSize(s, strs...); // 먼저 합쳐질 문자열의 총 길이를 구한다.

	string concat_str;
	concat_str.reserve(total_size);	// reserve 를 통해 미리 공간을 할당해 놓는다.

	concat_str = s;
	AppendToString(&concat_str, strs...);

	return concat_str;
}

int main() {
	// string 과 const char* 을 혼합해서 사용 가능하다.
	cout << StrCat(string("this"), " ", "is", " ", string("a"),
		" ", string("sentence"));
}
*/
