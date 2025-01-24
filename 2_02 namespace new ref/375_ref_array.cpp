//C 스타일 배열을 참조로 전달하면, 포인터로 변하는 것 피하는게 가능

#include <iostream>

void printElements(int(&arr)[4])    //명시적으로 매개 변수에서 배열의 크기를 정의해야 한다.
{
    int length{ sizeof(arr) / sizeof(arr[0]) };  // we can now do this since the array won't decay

    for (int i{ 0 }; i < length; ++i)
    {
        std::cout << arr[i] << std::endl;
    }
}

int main()
{
    int arr[]{ 99, 20, 14, 80 };    //배열을 참조로 전달하기

    printElements(arr);

    return 0;
}


//참조형의 또 다른 장점은 중첩된 데이터에를 쉽게 접근할 수 있게 한다

struct Something {
    int value1;
    float value2;
};
struct Other {
    Something something;
    int otherValue;
};
Other other;

int main()
{
    int& ref = other.something.value1;
    ref = 5;    //other.something.value1 = 5;
}