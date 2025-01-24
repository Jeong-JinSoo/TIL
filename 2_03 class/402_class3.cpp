// 1:1 배틀
// 플레이어, 몬스터 서로 공격하여 승패를 가리는 프로그램

#include <iostream>
#include <cstring>
using namespace std;

class Monster;	//전방선언	

class Player
{
public:
	int hp = 100;
	int ap = 10;
public:
	void Attack(Monster& m);
};

class Monster
{
public:
	int hp = 100;
	int ap = 10;
public:
	void Attack(Player& p);
};

void Player::Attack(Monster& m) { m.hp -= ap; }
void Monster::Attack(Player& p) { p.hp -= ap; }

int main()
{
	Player player;
	Monster monster;
	string winner = "";

	while (true)			//battle
	{
		player.Attack(monster);
		if (monster.hp <= 0) { winner = "player"; break; }
		monster.Attack(player);
		if (player.hp <= 0) { winner = "monster"; break; }
	}
	cout << "Winner : " << winner;
	return 0;
}


//상호 참조하는 경우하는 경우 
//맴버에 접근이 가능하도록 클래스를 선언해야 한다.

//가급적 연관 시키지 마라. 의존 관계를 만들지 마라.

//파일 분리와 헤더파일 활용

