//함수 템플릿를 부분적으로 특화시킬 수 없습니다
//하지만, 함수의 오버로딩을 통해 부분적으로 특화시키는 것과 비슷한 효과를 낼수 있습니다

#include <iostream>
using namespace std;

template <class T, class U> T foo(U obj)		//기본템플릿
{
	cout << obj << endl;

	return (T)obj;
}
//template <class U> void foo<void, U>(U obj)		//오류(부분템플릿 허용 안됨)
//{
//	cout << obj << endl;
//}
template <class T> T foo(int obj)				//가능(함수 오버로딩)
{
	cout << obj << endl;
	return (T)obj;
}

int main(void)
{
	cout << foo<int, double>(1.5) << endl;
	cout << foo<double>(1.5) << endl;
	return 0;
}

// 함수 선택 순서 정리
//
//1. 일반함수와 템플릿이 있을때 일반 함수가 우선 
//2. 템플릿중에서 가장 적합한 템플릿 선택
//3. 선택한 템플릿에 특수화가 있다면 특수화 우선 적용

/*

#include <iostream>
using namespace std;

template <class T> void foo(T obj) { cout << "void foo(T obj)" << endl; }
template <class T> void foo(T* obj) { cout << "void foo(T* obj)" << endl; }
template <>		   void foo(int* obj) { cout << "void foo(int* obj)" << endl; }

//template <class T> void foo(T obj) { cout << "void foo(T obj)" << endl; }
//template <>		   void foo(int* obj) { cout << "void foo(int* obj)" << endl; }
//template <class T> void foo(T* obj) { cout << "void foo(T* obj)" << endl; }

int main(void)
{
	int a = 0;
	foo<int>(&a);	// ???
	return 0;
}

*/