//캡슐화
//	데이터추상화란 현실세계의 사물을 데이터적인 측면과 기능적인 측면으로 구분한 후 
//	프로그램에서 데이터는 변수로 기능은 함수로 정의하는 것을 말한다. 
//	그리고 이렇게 만들어진 멤버변수와 멤버함수를 하나로 묶는 작업을 캡슐화라 한다.

//정보은닉
//	정보은닉은 외부에서 내부를 들여다 볼 수 없도록 하는 개념으로, 
//	다른 객체가 private 섹션에 정의된 데이터 값을 직접 참조하거나 접근할 수 없고, 
//	멤버에 접근하기 위해서는 public 섹션에 정의된 메소드(멤버함수)를 통하여 객체에 요청해야 한다.


//예제 )
//	소비자가 과일장수에게 사과2개를 구매한다
//	클래스 구성 Buyer, Seller //함수 구성 Trade();
//	구매전과 후의 구매자와 판매자의 사과 갯수를 출력하라

#include <iostream>
#include <cstring>
using namespace std;

class CBuyer  //객체로 데이타와 기능을 캡슐화
{

public:
	int money = 1000;
	int apple_num = 0;

public:
	void Buy(int _money, int _apple_num)
	{
		money -= _money;
		apple_num += _apple_num;
	}
};

class CSeller  
{

public:
	int money = 0;
	int apple_num = 10;

public:
	void Sell(int _money, int _apple_num)
	{
		money += _money;
		apple_num -= _apple_num;
	}
};

void Trade(CBuyer &buyer, CSeller &seller, int price, int num )
{
	buyer.Buy(price, num);
	seller.Sell(price, num);
}

int main()
{
	CBuyer buyer = { 1000, 0 };
	CSeller seller; 
	seller.money = 0; seller.apple_num = 10;	
	
	cout << "거래전" << endl;
	cout << "구매자 사과 갯수: " << buyer.apple_num << endl;
	cout << "판매자 사과 갯수: " << seller.apple_num << endl;

	//거래 //소비자가 과일장수에게 사과2개를 구매한다
	Trade(buyer, seller, 200, 2);

	cout << "거래후" << endl;
	cout << "구매자 사과 갯수: " << buyer.apple_num << endl;
	cout << "판매자 사과 갯수: " << seller.apple_num << endl;

	return 0;
}

//위 코드 변수를 private 으로 숨겨보세요.


//정의하고자 하는 문제의 분석 - 데이타(변수), 기능(함수), 객체(클래스)
//클래스를 어떻게 정의할 것인가? - 관련된 것끼리 묶음 (추상화), 캡슐화와 정보은닉
//클래스 관계를 구성하기 - 1.인자전달(연관), 2.관련클래스 선언(구성), 3.콘트롤러(집합.메니저)

//프로그램 설계 요령
// 
// 입출력, 내용처리, 프로세서 진행 을 분리하라
// MVC - model, view, controll - 어떤 대상을 어떻게 처리하고 어떻게 보여줄 것인가?
// UI, Contents, Manager, Display, Resource, Rule


//추가 예제
// 
// 4칙연산을 하는 Calculator 클래스 설계
// 게임 플레이어가 몬스터를 사냥한다. 
// 사냥전과 후의 플레이어와 몬스터의 HP를 출력하라