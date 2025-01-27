//클래스 맴버 포인터 //객체 맴버 포인터

#include <stdlib.h>
#include <iostream>

using namespace std;
class fruit
{
public:
    fruit() { f = &fruit::compare; }
    int (fruit::* f)(const int*, const int*);                       //fruit::* f //클래스 맴버 포인터
    int compare(const int* one, const int* two)
    {
        return ((*one == *two) ? 0 : *one > *two);
    }
} apple;

int funcptr(const void* one, const void* two)
{
    return ((apple.*apple.f)((const int*)one, (const int*)two));   //apple.*    //객체 맴버 포인터
};

int a[3] = { 3, 2, 1 };
int main()
{    
    cout << "before ";
    for (int i = 0; i < 3; i++) cout << a[i] << "  ";   cout << endl;
    
    qsort(a, 3, sizeof(a[0]), funcptr);

    cout << "after ";
    for (int i = 0; i < 3; i++) cout << a[i] << "  ";    cout << endl;

    return 0;
}