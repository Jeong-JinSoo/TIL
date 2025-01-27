// 객체 맴버에 대하여 this-> 를 써야하는 경우

#include <iostream>
using namespace std;

class TwoNumber
{
private:
	int num1;
	int num2;
public:
	TwoNumber(int num1, int num2)		//매개변수와 구분하기
	{
		this->num1 = num1;				//this->num1는 맴버변수를 의미한다
		this->num2 = num2;		
	}
		
	TwoNumber(int num1, int num2) : num1(num1), num2(num2) //맴버변수 초기화
	{
		// empty
	}		

	void Show()
	{
		cout << this->num1 << endl;
		cout << this->num2 << endl;
	}
};

int main(void)
{
	TwoNumber two(2, 4);
	two.Show();
	return 0;
}


//객체 맴버에 대하여 this 를 써야하는 경우
//		멤버 함수가 객체 자신의 주소를 리턴할 때

class Smaple {
public:
	Sample* f() {
		return this;
	}
};


//this 사용 제약 -------------------------------------

//멤버 함수가 아닌 함수에서 this 사용 불가
//		객체와의 관련성이 없기 때문
//static 멤버 함수에서 this 사용 불가
//		객체가 생기기 전에 static 함수 호출이 있을 수 있기 때문에