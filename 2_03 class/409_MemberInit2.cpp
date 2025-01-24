//객체 초기화 방식

#include <iostream> 
using namespace std;

class Player
{
    string nickname = "";                               //1
    int level = 0;
public:
    Player() { }
    Player(int l): level(l) { }
    Player(string n, int l) : nickname(n), level(l)     //2
    {
        nickname = n, level = l;                        //3
    }

    ~Player() { }   // 소멸자

    void Prn() {
        cout << nickname << " " << level;
    }
};

void main()
{
    int num = 5;            //초기화 방식
    int num(5);         
    int num{ 5 };

    Player p;               //객체 초기화 방식
    Player p{};
    Player p(1);
    Player p{ 1 };
    Player p("player",1);
    Player p{ "player",1 };
}

