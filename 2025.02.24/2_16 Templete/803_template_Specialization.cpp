//템플릿 특수화 - 특정 형식에 대한 템플릿의 특수화를 정의할 수 있습니다
//			특정 형식에 대해서는 별도의 기능을 수행해야하는 경우	, 
//			template <>	선언 후 개별 함수 작성

#include <iostream>
#include <cstring>
using namespace std;

template <typename T>
T Max(T a, T b)
{
	return a > b ? a : b;
}
template <>							//템플릿 특수화 //char*
char* Max(char* a, char* b)
{
	cout << "char* Max<char*>(char* a, char* b)" << endl;
	return strlen(a) > strlen(b) ? a : b;
}
template <>							//템플릿 특수화 //const char*
const char* Max(const char* a, const char* b)
{
	cout << "const char* Max<const char*>(const char* a, const char* b)" << endl;
	return strcmp(a, b) > 0 ? a : b;
}

int main(void)
{
	cout << Max(11, 15) << endl;
	cout << Max('T', 'Q') << endl;
	cout << Max(3.5, 7.5) << endl;

	cout << Max("Simple", "Best") << endl;

	char str1[] = "Simple";
	char str2[] = "Best";
	cout << Max(str1, str2) << endl;

	return 0;
}


/*
// swap 함수를 템플릿으로 정의 하고, double형에 대해서는 교환하지 않도록 특수화하세요.

	#include <iostream>
	using namespace std;

	template <typename T> void Swap(T& a, T& b);		//선언
	template <> void Swap<double>(double&, double&);	//선언

	int main(void)
	{
		int a = 2, b = 3;
		Swap(a, b);
		cout << a << " " << b << endl;

		double c = 1.234, d = 4.321;
		Swap(c, d);
		cout << c << " " << d << endl;

		return 0;
	}

	template <typename T>	//정의
	void Swap(T& a, T& b)
	{
		T temp; temp = a; a = b; b = temp;
	}

	template <> void Swap<double>(double&, double&)  //특수화
	{
		// double형은 값을 서로 바꾸지 않음.
	}
*/