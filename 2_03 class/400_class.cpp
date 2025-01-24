//객체지향
//	같은 종류에 속하는 멤버변수(데이터)와 멤버함수(기능)를 동일한 클래스에 포함하여 하나의 객체로 선언하고, 
//	서로 다른 객체간의 메시지 교환에 주안점을 두어 사용자 정보를 원활하게 처리하는 방법

//절차지향 -> 객체지향
//	대규모 프로그램 - 성능보다 효율적인 처리가 중요해짐 
//	함수				-> 클래스 ( printf -> cout )
//	잘 사용하는 것	-> 객체를 잘 만들고, 쉽게 사용
//  기계 중심 처리   -> 사람의 사고체계 방식으로 
// 
//	클래스 - 설계(추상,개념)와 구현(실체)의 분리 
//	추상화, 캡슐화, 관계 (상속성, 다형성) 


//캡슐화

#include <iostream>
#include <cstring>
using namespace std;

class CPlayer	// CPlayer 라는 class 로 데이타와 기능을 캡슐화 - 객체를 생성해서 사용. 
{
public:					//접근 제어자 (Access Modifier)

	int level = 0;		//데이터 멤버 (Data Members)
	int exp;
	int posx, posy;
	int hp;
	int ap;

	void Init()			//멤버 함수 (Member Functions)
	{
		level = 1;
	}
	void Move()	{
	}
	bool Attack() {
	}
};

class CMonster  //CMonster라는 객체로 데이타와 기능을 캡슐화
{
public:
	int posx, posy;
	int hp;
	int ap;
	void Init()	{ }
	void Move()	{ }
	bool Attack() { }
};

int main()
{
	CPlayer myhero;		//CPlayer 클래스로 myhero 인스턴스 객체 생성

	cout << myhero.level << endl;
	myhero.Init();
	cout << myhero.level << endl;

	CMonster mob01;		// 객체생성
	CMonster mob02;
	
	return 0;
}

//------------------------------------------------------------
class MyClass {};

int main()
{
	MyClass mc1;					//자동 객체 생성

	MyClass* mc2 = new MyClass;		//동적 객체 생성
	delete mc2
}

//객체 지향의 특징
// 
//추상화 - 공통요소를 하나의 개념으로 정의, 필요한 정보만을 중심으로 간소화.
//캡슐화 - 객체에 필요한 데이터나 기능(메소드)을 책임이 있는 객체에 그룹화시켜주는 것
//상속성 - 상위 클래스의 기능을 하위 클래스가 사용할 수 있는 개념, 중복되는 코드의 재사용성
//다형성 - 추상화된 개념이 다양하게 쓰이도록 객체간 관계를 유연하게 하는 기능
//	     - 하나의 인터페이스로 다양한 구현

//객체지향 5가지 원칙 (SOLID)
//SRP(Single Responsibility Principle) : 단일 책임 원칙
//OCP(Open - Closed Principle) : 개방 폐쇄 원칙
//LSP(Liskov Substitution Principle) : 리스코프 치환 원칙
//ISP(Interface Segragation Principle) : 인터페이스 분리 원칙
//DIP(Dependency Inversion Principle) : 의존관계 역전 원칙
