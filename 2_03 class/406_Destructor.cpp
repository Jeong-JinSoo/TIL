//소멸자 //동적할당과 해제

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
using namespace std;

class CPerson
{
private:
	char* name;			//포인터 선언 //동적할당과 해제
	int age;
public:
	CPerson(char* myname, int myage)
	{
		int len = strlen(myname) + 1;
		name = new char[len]; strcpy(name, myname);			//new
		age = myage;
		//cout << "called constructor!" << endl;
	}
	~CPerson()			
	{
		delete[] name;										//delete
		//cout << "called destructor!" << endl;
	}

	void ShowInfo() const
	{
		cout << "이름: " << name << endl;
		cout << "나이: " << age << endl;
	}
};

int main(void)
{
	char name1[] = "Lee dong su";
	char name2[] = "Kim min woo";
	CPerson man1(name1, 29);
	CPerson man2(name2, 41);
	man1.ShowInfo();
	man2.ShowInfo();
	return 0;
}

//RAII 패턴 
//	리소스 획득은 초기화다. (Resource Acquisition Is Initialization)
//	자원의 안전한 사용을 위해 객체가 쓰이는 스코프를 벗어나면 자원을 해제해주는 기법
//	stack에 할당된 자원은 자신의 scope가 끝나면 메모리가 해제되며 destructor가 불린다는 원리를 이용

/*

#include <iostream>
#include <cstdio>
using namespace std;

// 아래처럼 간단하게 할 수 있지만, 예외 발생하면 fclose를 호출하지 않고 종료되는 위험 존재

void UseFile() {
	FILE* file = nullptr;
	errno_t err = fopen_s(&file, "./test.txt", "w+");
	// Do something  //여기서 예외 발생하면 ????
	if(file != nullptr) fclose(file);
}

int main()
{
	UseFile();
}

// 객체로 구현 -------------------------------------------------------------------

class CFile final
{
public:
	CFile(const std::string& path)
	{
		errno_t err = fopen_s(&file_, path.c_str(), "w+");
	}
	~CFile()
	{
		fclose(file_);
	}

private:
	FILE* file_ = nullptr;
};

void UseFile() {
	string path = "./test.txt";
	CFile fileobj(path);}
*/
