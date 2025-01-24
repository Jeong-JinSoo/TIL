#include <iostream>

namespace Player			//중첩 선언도 가능하다.
{
	void Func1(void);
}
namespace Player			//중첩 선언도 가능하다.
{
	void Func2(void);
}

namespace Monster
{
	void Func1(void);			// 선언
}

int main(void)
{
	Player::Func1();
	return 0;
}


void Player::Func1(void)		// 정의할때 범위지정을 한다.
{
	std::cout << "Player::Func1" << std::endl;
	Func2();					// 동일 이름공간
	Monster::Func1();			// 다른 이름공간
}

void Player::Func2(void)		
{
	std::cout << "Player::Func2" << std::endl;
}

void Monster::Func1(void)
{
	std::cout << "Monster::Func1" << std::endl;
}