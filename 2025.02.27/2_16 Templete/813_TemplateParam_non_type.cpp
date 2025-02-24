//형식이 아닌 템플릿 매개변수 (값 매개 변수) - Non-type Templates Parameters
// 
//		템플릿 매개변수에는 자료형이 아닌, 변수의 선언이 올 수 있습니다. 
//		해당 변수에 디폴트 지정도 가능.


#include <iostream>

template <typename T, int num>						//non-type template parameter - num 
T add_num(T t) {
	return t + num;
}

int main() {
	int x = 3;
	std::cout << "x : " << add_num<int, 5>(x) << std::endl;  //template arguments - 5
}

/*
// STL array -------------------------------------------------

	#include <iostream>
	#include <array>				//array

	template <typename T>
	void print_array(const T& arr) {
		for (int i = 0; i < arr.size(); i++)
			std::cout << arr[i] << " ";
		std::cout << std::endl;
	}

	int main() {
		std::array<int, 5> arr = { 1, 2, 3, 4, 5 };
		std::array<int, 7> arr2 = { 1, 2, 3, 4, 5, 6, 7 };
		std::array<int, 3> arr3 = { 1, 2, 3 };

		print_array(arr);		//array 배열과 크기 전달 가능
		print_array(arr2);
		print_array(arr3);
	}

*/

#include <iostream>
using namespace std;

template <typename T = int, int len = 7>	// 기본값 사용
class SimpleArray
{
private:
	T arr[len];
public:

	T& operator[] (int idx)
	{
		return arr[idx];
	}
	T& operator=(const T& ref)
	{
		for (int i = 0; i < len; i++)
			arr[i] = ref.arr[i];
	}
};

int main(void)
{
	SimpleArray<int,5> array;			// 5  

	SimpleArray<> arr;					// <> 써주어야 한다. 인수전달 없으면 기본값 사용
	for (int i = 0; i < 7; i++)
		arr[i] = i + 1;

	for (int i = 0; i < 7; i++)
		cout << arr[i] << " ";
	cout << endl;

	return 0;
}

/*
함수 템플릿에도
	비타입 인수를 사용할 수 있되 형식인수 목록에 상수가 올 수 없으므로, 비타입 인수는 본체에서만 사용할 수 있다.
	비타입 인수는 함수 호출시에 인수로 전달되는 것이 아니어서
	함수명 다음에 sub<5>(); 식으로 인수의 값을 명시적으로 지정한다.
	함수 템플릿의 비타입 인수는 실용성이 떨어지며 일부 컴파일러는 지원하지 않는다.


	#include <iostream>
	using namespace std;

	template <typename T,int n = 0>
	class MyClass
	{
		T data;
	public:
		MyClass(T a) : data(a) { }
		void Prn() { cout << data << " " <<  n << endl; }
	};

	template <typename T, int n = 0>
	void foo(T data ) {
		cout << data << " " << n << endl;
	}

	int main()
	{
		MyClass<int, 5> obj(1);
		obj.Prn();

		foo<int, 5>(1);
		foo<int>(1);
	}
*/

/*
 
//템플릿 값 매개변수 인자로 전달할 수 있는 타입

	정수 타입들(bool, char, int, long 등등) ( float 과 double 은 제외 )
	포인터 타입
	enum 타입
	std::nullptr_t(널 포인터)


//템플릿의 비타입 인수에서의 클래스 사용

	기존의 C++에서는 비타입 인수에서 클래스를 사용할 수 없었는데,
	C++20부터는 드디어 가능해졌다.

	대신 해당 클래스는 operator== 를 구현해야 하고,
	해당 연산자의 반환 타입은 bool으로 변환할 수 있어야 하고,
	이 조건을 해당 클래스의 부모 클래스들과 부모 클래스들의 non-static 멤버들도 만족해야 하며,
	mutable 또는 volatile 지정자가 붙은 non-static 멤버들이 없어야 합니다.
	TMP를 할 때 유용.
*/

