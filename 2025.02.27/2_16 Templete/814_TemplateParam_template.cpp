//템플릿 중첩 ( 템플릿을 템플릿 인수로 사용 )
//		템플릿 클래스도 하나의 타입이다.
//		템플릿끼리 중첩이 가능하다
//		템플릿 선언문의 타입 인수에 또 다른 템플릿이 들어갈 수 있다.

#include <iostream>
using namespace std;

template <typename T>
class PosValue
{
private:
	int x, y;
	T value;

public:
	PosValue() : x(0), y(0), value(0) {}
	PosValue(int x, int y, T v) : x(x), y(y), value(v) {}
	void outvalue()
	{
		cout << x << " " << y << " " << value << endl;
	}
};

template <typename T>
class Wrapper
{
private:
	T member;
public:
	void set(T v) { member = v; }
	T get() { return member; }
};

int main()
{
	Wrapper<PosValue<char> >wrap;				// 템플릿 타입 사용
	wrap.set(PosValue<char>(10, 10, 'a'));

	PosValue<char> pc = wrap.get();
	pc.outvalue();

}

//템플릿을 중첩할때는 두 괄호 사이에 공백을 넣어 연산자가 아님을 분명히 해야한다. >>
//비쥬얼 스튜디오에서는 이런 에러를 잡아줘서 띄워쓰든 붙여쓰든 에러가 뜨지는 않는다.

//중첩이 가능하려면 
//두 클래스가 임의 타입에 대해 잘 작동하도록 충분히 일반화되어야 하며 
//생성자, 대입 연산자 등 모든 장치가 제대로 마련되어 있어야 한다.


//템플릿 템플릿 파라미터 -----------------------------------------------
//		템플릿 파라미터로 템플릿을 사용하는 것
//		template<..., template<TemplateTypeParams> class ParameterName, ...>