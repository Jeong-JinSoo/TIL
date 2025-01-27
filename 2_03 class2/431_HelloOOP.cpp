//심화 학습  //C 에서 C++ 로 문법적 표현의 변화 

//구조체 + 함수 + 접근제어 -> 클래스 


#include <stdio.h>

//제작자의 코드 -------------------------------
typedef struct USERDATA
{
	int nAge;
	char szName[32];
	void(*Print)(struct USERDATA *);
} USERDATA;

void PrintData(USERDATA *pUser)
{
	printf("%d, %s\n", pUser->nAge, pUser->szName);
}

//사용자의 코드 ------------------------------
int main(void)
{
	USERDATA user = { 20, "철수", PrintData };
	//printf("%d, %s\n", user.nAge, user.szName);		//1단계
	//PrintData(&user);									//2단계 //function
	user.Print(&user);									//3단계 //맴버함수 //주소전달 - this포인터
	//user.Print();										//4단계 //class member
	return 0;
}