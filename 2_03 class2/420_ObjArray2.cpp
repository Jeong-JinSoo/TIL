//객체 배열을 포인터로 전달하기 
#include <iostream>
using namespace std;

class MyClass
{
    int num = 0;
public:
    MyClass(int a) : num(a) {
    }
    void Show() {
        cout << num << endl;
    }
};

//void ShowClass(MyClass* pClass, int count);

int main(void)
{
    MyClass array[4] = {                                //객체 배열
        MyClass(1), MyClass(2), MyClass(3), MyClass(4) 
    };	  
    //array[0].Show();

    MyClass* pClass = array;                            //객체 포인터 


    ShowClass(array, sizeof(array) / sizeof(MyClass));  //객체 배열을 포인터로 전달해보자 ***
    return 0;
}

//void ShowClass(MyClass* pClass, int count)  //객체 배열을 포인터로 전달
//{
//    for (size_t i = 0; i < count; i++)
//    {
//        (pClass + i)->Show();
//    }
//}