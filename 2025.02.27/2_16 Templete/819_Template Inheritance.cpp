//클래스 템플릿의 상속(Class Template Inheritance)

#include <iostream>
#include <string>

template <class T>
struct Empty {
	typedef T type;					// 템플릿의 매개변수로 제공하는 타입을 선언
	virtual void Display() = 0;
};

// 위 클래스 템플릿을 상속받는 Optimized 클래스를 선언
template <class T>
class Optimized : public Empty<T> {
private:	
	typename Empty<T>::type data;	// Empty 클래스 템플릿이 제공하는 타입을 사용하기 위해 typename 지정자를 사용

public:
	Optimized(typename Empty<T>::type dataValue)
		: data(dataValue) { }

	typename Empty<T>::type GetData() const {
		return data;
	}

	virtual void Display() final;
};

template <class T> 
void Optimized<T>::Display() {
	std::cout << "Optimized : " << data << std::endl;
}

int main() {
	Optimized<int> optimized(100);
	std::cout << "Empty Object : " << optimized.GetData() << std::endl;
	optimized.Display();

	Empty<std::string>::type str = "문자열 입력";  //string str
	std::cout << str << std::endl;
}


/*
template<typename T>
using Empty_t = typename Empty<T>::type;
*/