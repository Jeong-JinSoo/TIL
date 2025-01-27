//객체의 배열과 객체포인터의 배열 //예시

#include <iostream>
#include <cstring>
using namespace std;

class CPerson
{
private:
	char* name;
	int age;
public:
	CPerson()
	{
		name = NULL;
		age = 0;
		//cout << "called CPerson()" << endl;
	}
	CPerson(char* myname, int myage)
	{
		int len = strlen(myname) + 1;
		name = new char[len]; strcpy_s(name, len, myname);
		age = myage;
	}
	~CPerson()
	{
		delete[] name;
		//cout << "called destructor!" << endl;
	}

	void SetInfo(char* myname, int myage) {
		name = myname;
		age = myage;
	}
	void ShowInfo() const {
		cout << "이름: " << name << ", " << "나이: " << age << endl;
	}

};


int main(void)
{
	CPerson parr[3];	//객체 배열

	char namestr[100];
	char* strptr;
	int age;

	for (int i = 0; i < 3; i++)
	{
		cout << "이름: "; cin >> namestr;
		cout << "나이: "; cin >> age;

		strptr = new char[strlen(namestr) + 1];			//new //delete 하는 곳 확인하세요.
		strcpy_s(strptr, strlen(namestr) + 1, namestr);
		parr[i].SetInfo(strptr, age);
	}

	parr[0].ShowInfo();
	parr[1].ShowInfo();
	parr[2].ShowInfo();

	return 0;
}


int main(void)
{
	CPerson* parr[3];		//객체포인터의 배열

	char namestr[100];
	int age;

	for (int i = 0; i < 3; i++)
	{
		cout << "이름: ";	cin >> namestr;
		cout << "나이: ";	cin >> age;

		parr[i] = new CPerson(namestr, age);	// 객체 동적생성
	}

	parr[0]->ShowInfo();
	parr[1]->ShowInfo();
	parr[2]->ShowInfo();

	delete parr[0];
	delete parr[1];
	delete parr[2];

	return 0;
}