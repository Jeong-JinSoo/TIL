//매크로(macro)
//	정해진 순서에 따라 어떻게 
//	특정한 입력 시퀀스 (문자열을 가리키기도 함)가 출력 시퀀스로 
//	'매핑'되어야 하는지를 정의하는 규칙이나 패턴
//
//	반복 처리, 오류발생 줄임.
//	복잡하거나 반복되는 작업을 단순화하거나 자동화하기 위한 목적으로 주로 이용
//	ex) 자주 사용하는 여러 개의 명령어를 묶어서 하나의 키 입력 동작으로 만듬

#include<iostream> 
using namespace std;

#define NAME "홍길동"
#define AGE 24
#define PRINT cout << "address" <<endl;

int main(void)
{
	cout << NAME << endl;
	cout << AGE << endl;
	PRINT;
}

/*

#include <stdio.h>
#define  DIFF_ABS(X, Y)     ( (x)>(y) ? (x)-(y) : (y)-(x) ) //명확하게 선언하자

int main(void)
{
	printf("두 값의 차: %d \n", DIFF_ABS(5, 7));
	printf("두 값의 차: %g \n", DIFF_ABS(1.8, -1.4));
	return 0;
}

//매크로 #, ## ----------------------------------------------------------------

#include <stdio.h>

//a를 "a"(문자열)로 변경하는 매크로 정의.
#define STRING(a)	#a

//a와 b를 합쳐 하나로 붙여주는 매크로 정의.
#define PASTER(a, b)	a##b

int main(void)
{
	int nData = 10;
	
	printf("%d\n", nData);
	printf("%s\n", STRING(nData)); //"nData"로 처리된다.

	printf("%d\n", PASTER(nDa, ta)); //PASTER(nDa, ta)는 그냥 nData라고 쓴 것과 같다.

	return 0;
}

//매크로 예제 ------------------------------------------------------------
//		매크로는 단순 텍스트 치환이다.

	#include<iostream>
	using namespace std;

	#define 시작 {
	#define 끝 }
	#define 출력(x) cout << x <<endl;
	#define 함수(ret,fname,var) ret fname(string var)

	함수(void, 출력함수, a)
	시작
	출력(a)
	끝

	int main(void)
	시작
		출력함수("hello");
	끝

//매크로 사용의 문제점 ------------------------------------------------------
	#define SQUARE(X)   X*X

	int main(void)
	{
		int num = 20;

		// 정상적 결과 출력
		printf("Square of num: %d \n", SQUARE(num));
		printf("Square of  -5: %d \n", SQUARE(-5));
		printf("Square of 2.5: %g \n", SQUARE(2.5)); //다양한 자료형에 응용

		// 비정상적 결과 출력
		printf("Square of 3+2: %d \n", SQUARE(3 + 2));
		return 0;
	}
-------------------------------------------------------------
	#include<iostream>
	using namespace std;

	#define SQUARE(x) x*x
	//#define SQUARE(x) (x)*(x)
	//#define SQUARE(x) \
	//(x)*(x)

	int main(void)
	{
		cout << SQUARE(5) << endl;
		cout << SQUARE(2+3) << endl;
	}

//변수가 잘못 typecasting될 수 있기 때문에, #define 매크로 사용을 자제할 것을 권장한다.
//즉, 
//"#define MAX 10" 보다는 "const int MAX 10"으로 코딩하는 것이 바람직하다.
//매크로함수보다는 인라인 함수 활용하라.

*/