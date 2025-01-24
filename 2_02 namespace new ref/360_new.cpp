//메모리 관리와 메모리의 동적 할당  // malloc free ***


/*
//전역변수나 지역변수로 문자열을 담아둘수 없는 경우. 동적 할당 필요.

	char name[30];

	void ReadUserName(void)
	{
		printf("What's your name? ");
		cin >> name;
	}

	int main(void)
	{
		ReadUserName();	printf("name1: %s \n", name);
		ReadUserName();	printf("name2: %s \n", name);
		printf("again name1: %s \n", name);
		printf("again name2: %s \n", name);
		return 0;
	}

	//-----------------------------------------------
	char* ReadUserName(void)
	{
		char* name = (char*)malloc(sizeof(char) * 30);
		printf("What's your name? ");
		//gets(name);
		cin >> name;
		return name;
	}

	int main(void)
	{
		char* name1;
		char* name2;
		name1 = ReadUserName();	printf("name1: %s \n", name1);
		name2 = ReadUserName();	printf("name2: %s \n", name2);
		printf("again name1: %s \n", name1);
		printf("again name2: %s \n", name2);
		free(name1);
		free(name2);
		return 0;
	}
*/

#include <stdio.h>
#include <stdlib.h>

#include <iostream>
using namespace std;

int main(void)
{
	// C: malloc free -----------------------------------------
	{
		int* ptr1 = (int*)malloc(sizeof(int));
		int* ptr2 = (int*)malloc(sizeof(int) * 7);
		int i;

		*ptr1 = 20;
		for (i = 0; i < 7; i++)	ptr2[i] = i + 1;

		printf("%d \n", *ptr1);
		for (i = 0; i < 7; i++)	printf("%d ", ptr2[i]);

		free(ptr1);
		free(ptr2);
	}
	// C++ : new delete ---------------------------------------
	{
		int* ptr1 = new int;
		int* ptr2 = new int[7];

		*ptr1 = 20;
		for (int i = 0; i < 7; i++)		ptr2[i] = i + 1;

		printf("%d \n", *ptr1);
		for (int i = 0; i < 7; i++)		printf("%d ", ptr2[i]);

		delete ptr1;
		delete[] ptr2;
	}

	return 0;
}

/*
// malloc, realloc ----------------------------------------------------------------

malloc()
	함수선언: void* malloc(size_t size);
	malloc은 size만큼의 메모리를 할당하고(초기화 없이) 해당 힙 영역을 반환합니다.

	int* ptr = malloc(10 * sizeof(int));

calloc()
	함수선언: void* calloc(size_t nelements, size_t bytes);
	calloc는 num* size만큼의 메모리를 할당하고 해당 힙 영역을 0으로 초기화하여 반환합니다.

	int* ptr = calloc(10, sizeof(int));

realloc()
	함수선언: void *realloc(void *block, size_t size);
	realloc은 malloc이나 calloc으로 할당받은 메모리의 사이즈를 변경할 때 사용한다.
	

	//-------------------------------------------------------------
	#include <stdio.h>
	#include <stdlib.h>

	int main() {
		int *pi1;
		int *pi2;

		pi1 = (int *)malloc(sizeof(int) * 3); //할당
		printf("malloc : %d %d %d\n", pi1[0], pi1[1], pi1[2]);

		pi2 = (int *)calloc(3, sizeof(int)); //할당
		printf("calloc : %d %d %d\n", pi2[0], pi2[1], pi2[2]);

		free(pi1);		//메모리 해제
		free(pi2);		//메모리 해제
	}

	//-------------------------------------------------------------
	#include <stdio.h>
	#include <stdlib.h>

	int main()
	{
		int i;
		int *pi = (int *)malloc(sizeof(int) * 3);	//4x3 메모리 할당
		for (i = 0; i < 3; i++)	pi[i] = i * 4;
		for (i = 0; i < 3; i++)
			printf("pi[%d] : memory %d %d\n", i, &pi[i], pi[i]);
		printf("-----------------------------\n");

		pi = (int *)realloc(pi,sizeof(int) * 5);	//4x5 메모리 재할당
		for (i = 3; i < 5; i++)	pi[i] = i * 4;
		for (i = 0; i < 5; i++)
			printf("pi[%d] : memory %d %d\n", i, &pi[i], pi[i]);
		printf("-----------------------------\n");

		free(pi);	//메모리 해제
	}

*/
