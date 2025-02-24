// 템플릿 매개변수의 디폴트 값 ------------------------------------------
//		타입 매개변수도 변수이기 때문에 디폴트 값 지정이 가능하다.

#include <iostream>
using namespace std;

template <typename T = int>		//디폴트 템플릿 인수 int
class MyClass
{
	T data;
public:
	MyClass(T a) : data(a) { }
	void Prn() { cout << data << endl; }
};

int main()
{
	MyClass<> obj(1.5);			//<> 
	obj.Prn();


	//MyClass obj(1.5);			//double
}

// 예시 // 템플릿[template] 매개변수의 디폴트 값 ---------------------------

#include <iostream>
#include <string>

template <typename T>
struct Compare {
	bool operator()(const T& a, const T& b) const { return a < b; }
};

template <typename T, typename Comp = Compare<T>>  //디폴트 템플릿 인자를 이용
T Min(T a, T b) {
	Comp comp;				// 원소 비교, Comp 라는 객체가 이를 수행 
	if (comp(a, b)) {
		return a;
	}
	return b;
}

int main() {
	int a = 3, b = 5;
	std::cout << "Min " << a << " , " << b << " :: " << Min(a, b) << std::endl;

	std::string s1 = "abc", s2 = "def";
	std::cout << "Min " << s1 << " , " << s2 << " :: " << Min(s1, s2)
		<< std::endl;
}



