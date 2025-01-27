//클래스 인스턴스 전달, 반환	//Pass by Reference //Call by Reference

#include <iostream>
using namespace std;

class MyClass
{
	int num = 0;
public:
	MyClass(int a) : num(a)	{ }
	void Add() { ++num; }
	void Show() { cout << num << endl; }
};

MyClass FuncByValue(MyClass obj)
{
	obj.Add();
	return obj;
}
MyClass* FuncByAddress(MyClass* obj)
{
	obj->Add();
	return obj;
}
MyClass& FuncByReference(MyClass& obj)
{
	obj.Add();
	return obj;
}

int main(void)
{
	MyClass x(1);
	//x.Show();

	//MyClass* pClass = &x;
	//pClass->Show();
	//(*pClass).Show();

	MyClass a = FuncByValue(x); a.Show();
	MyClass* b = FuncByAddress(&x); b->Show();
	MyClass& c = FuncByReference(x); c.Show();
	
	return 0;
}

