//class를 사용하여 간단하게 표현, 
//성능(코드길이)에서 생산성(대규모,협업)으로 

#include <cstdio>

//제작자의 코드
class USERDATA
{
public:						//접근통제 (자유도 낮추고, 오남용 방지)
	//멤버 변수 선언
	int nAge;
	char szName[32];

	//멤버 함수 선언 및 정의
	void Print(void)
	{		
		printf("%d, %s\n", nAge, szName);	
		//nAge와 szName은 Print() 함수의 지역변수가 아니다!
	}
};

//사용자의 코드				//public 맴버 사용 
int main(void)
{
	USERDATA user = { 10, "철수" };
	user.Print();

	return 0;
}




