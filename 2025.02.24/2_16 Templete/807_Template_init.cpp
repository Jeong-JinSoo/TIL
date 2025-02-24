//기본형의 0 초기화
// 
//int, char, double이나 포인터 형 같은 기본형(fundamental type)에는 
//기본값으로 초기화 하는 생성자가 없습니다
//템플릿형 변수도 마찬가지 입니다.

#include <iostream>

template<typename T>
void foo()
{
    T x;            // T가 기본 자료형이면 정의 되지 않은 값을 가진다
}

//기본형에 대해서도 0(bool은 false) 초기화 하는 기본 생성자를 명시적으로 호출 할 수 있다 ***

template<typename T>
void foo()
{
    T x = T();      //기본형이면 0또는 false를 갖는다
}

//클래스 템플릿의 멤버가 제대로 초기화 위해 기본 생성자 정의 가능하다

template <typename T>
class MyClass
{
private:
    T x;
public:
    MyClass() : x()  //기본형 x초기화 된다
    {}
};

//예시 //클래스 템플릿의 멤버 초기화

#include <iostream>

constexpr int MAX = 500;

template<class T>
class List {
private:
    T data[MAX];
    size_t size;
public:
    List() :size(0), data() {}      //data 가 초기화 된다.

    void InsertData(const T& d) {
        data[size++] = d;
    }
    void InsertData(const T&& d) {
        data[size++] = d;
    }
    void DisPlay()const {
        for (size_t i = 0; i < size; ++i)
            std::cout << data[i] << " ";
        std::cout << "\n";
    }

};

int main() {
    List<int> list;
    list.InsertData(5);
    list.InsertData(6);
    list.InsertData(8);
    list.InsertData(9);
    list.DisPlay();
}


//---------------------------------------------------------------------------

//함수 템플릿의 참조자(reference) 파라미터로 '문자열'을 전달하면 오동작을 합니다

template <typename T>
inline T const& max(T const& a, T const& b) //참조자 파라미터
{
    return  a < b ? b : a;
}

int main()
{
    std::string s = "apple";
    ::max("apple", "peach");    // 같은 타입        char const [6]
    ::max("apple", "tomato");   // ERROR: 다른 타입
    ::max("apple", s);          // ERROR: 다른 타입
}

//문자열 리터럴의 길이에 따라 각기 다른 배열형으로 정의 된다는 것이 문제
//"apple"과 "peach" char const [6] 데이터형 가지고, "tomato"는 char const [7] 데이터형

#include <typeinfo>
#include <iostream>

template <typename T>
void ref(T const& x) {
    std::cout << "x in ref(T const&): " << typeid(x).name() << '\n';
}

template <typename T>
void nonref(T x) {
    std::cout << "x in non ref(T):    " << typeid(x).name() << '\n';
}

int main()
{
    ref("hello");
    nonref("hello");
}

//-----------------------------------------------------------------
#include <typeinfo>
#include <iostream>
template <typename T1, typename T2>
void func(const T1& a, const T2* b)     
{
    std::cout << typeid(a).name() << std::endl;
    std::cout << typeid(b).name() << std::endl;
}

int main()
{
    func("apple", "apple");  // 문자열 파라미터 //타입은?
}