//객체배열 생성, 소멸 예제  -------------------------------------------------------------

#include <cstdlib>
#include <iostream>
using namespace std;

class Circle 
{
    int radius;
public:
    Circle();
    Circle(int r);
    ~Circle();
    void setRadius(int r) { radius = r; }
    double getArea() { return 3.14 * radius * radius; }
};

Circle::Circle() {
    radius = 1;    
    //cout << "생성자 " << radius << endl;
}
Circle::Circle(int r) {
    radius = r;    
    //cout << "생성자 " << radius << endl;
}
Circle::~Circle() {
    //cout << "소멸자 " << radius << endl;
}

// 객체 3개를 배열로 선언하고 각각 반지름 2,3,5로 설정후 넓이를 출력하세요.
    //Circle pArray[3]

int main()
{
    Circle pArray[3] = { Circle(2), Circle(3), Circle(5) };

    for (int i = 0; i < 3; i++) {
        cout << pArray[i].getArea() << endl;
    }
}

//객체의 포인터에 동적 생성 -------------------------------------------------------------

// 객체를 동적으로 할당하여, 각각 반지름 2,3,5로 설정후 넓이를 출력하세요.
    //Circle* pArray = new Circle[3];
    //Circle* pArray[3] = { new Circle(), new Circle(), new Circle() };

int main(int argc, char* argv[])
{
    Circle* pArray = new Circle[3];     //동적할당 : 객체배열생성 //heap 영역에 3개짜리 객체 배열 생성
    pArray[0].setRadius(2);
    pArray[1].setRadius(3);
    pArray[2].setRadius(5);
    for (int i = 0; i < 3; i++) {
        cout << pArray[i].getArea() << endl;
    }
    delete[] pArray;                    //객체배열 반환


    //Circle* pArray[3] { new Circle(2),  new Circle(3),  new Circle(5) };    //객체포인터 배열 
    //for (int i = 0; i < 3; i++) {
    //    cout << pArray[i]->getArea() << endl;
    //}
    //delete pArray[0];
    //delete pArray[1];
    //delete pArray[2];


    //system("PAUSE");
    return EXIT_SUCCESS;
}
