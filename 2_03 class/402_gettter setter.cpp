// 정보은닉
//		변수는 가급적 private 로 보호해야 클래스가 안전.

// getter, setter

#include <iostream>
#include <cstring>
using namespace std;

class Player
{
public:
	int hp = 100;
	int ap = 10;
};

int main()
{
	Player player;
	player.hp = 1000;		//hp 가 100 을 넘지 않아야 한다면?  

	return 0;
}

// getter, setter -------------------------------------------------
class Player
{
private:
	int hp = 100;					//private 으로 변경
	int ap = 10;			
public:
	int		get_hp() { return hp; }		//getter
	void	set_hp(int n) { hp = n; }	//setter
};

int main()
{
	Player player;	
	player.set_hp(100);	
	cout << player.get_hp() << endl;

	player.set_hp(1000);		//잘못된 데이타를 입력한 경우, 대처 가능

	return 0;
}

/*
//함수를 통해 간접 접근하면, 잘못 입력한 경우 함수에서 체크가 가능하다. //클래스 오용 방지

	void set_hp(int n) { 
		if (n > 100) return;
		hp = n; 
	}
*/