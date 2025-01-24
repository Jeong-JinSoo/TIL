// 매크로(macro)
// 정해진 순서에 따라 어떻게
// 특정한 입력 시퀀스 (문자열을 가리키기도 함)가 출력 시퀀스로 '매핑' 되어야 하는지를
// 정의하는 규칙이나 패턴
//
// 반복 처리, 오류발생 줄임.
// 복잡하거나 반복되는 작업을 단순화 하거나 자동화 하기 위한 목적으로 주로 이용
// ex) 자주 사용하는 여러개의 명령어를 묶어서 하나의 키 입력 동작으로 만듬

// 중요한건 이 모든 과정은 컴파일 타임에 확정 되어 일어난다는 점이고, 따라서 함수와 같은 용도를 기대하긴 어렵다.

// 매크로 확장 문자열에는 공백을 포함할 수 없다.
// #define은 전처리 과정에서 치환되므로 메모리 공간에 할당되지 않는다. -> 주소 접근이 불가능하다

// 매크로 상수는 다음과 같이 정의된다.
# define 매크로이름 값 // 전처리기 문의 끝에는 ; 을 붙이지 않는다.

#include <iostream>
using namespace std;

#define NAME "홍길동"
#define AGE 24
#define PRINT cout << "address" << endl;

int main(void)
{
	cout << NAME endl;
	cout << AGE << endl;
	PRINT;
}

// #ifdef
// 매크로가 정의되어 있는가 아닌가에 따라서 코드를 포함할지 말지 결정하는 전처리기 명령 -> 조건부 컴파일
// #ifdef와 #endif 사이에 코드를 작성한다.
// define되는 것이 무것이냐에 따라 간단히 무엇을 컴파일 할 것인지를 나타낼 떄 유용히 사용된다.
// #else를 사용 할 수 있다.

#include <iostream>
#define A
using namespace std;

int main()
{
 #ifdef A
	cout << "Define_A";
#else
	cout << "None_Defined_A";
#endif
#ifdef B
	cout << "Define_B";
#endif
	return 0;
}

// 매크로 함수
// 매크로를 이용하여 #define에 인수로 함수의 정의를 전달함으로써,
// 함수처럼 동작하는 매크로 함수를 만들 수 있다.
// 일반 함수와 달리 단순 치환만 하기 때문에 일반 함수와 완벽히 똑같이 동작하지는 않는다.
//  -> 인수타입 신경X
// 매크로 함수를 사용하여 여러개의 명령문을 동시에 포함 할 수 있다.
// 함수 호출에 의한 성능 저하가 발생하지 않고, 프로그램 실행속도가 빨라진다.
// 정확한 함수의 구현이 어려운 탓에 디버깅이 어렵고, 함수 크기가 클수록 가독성이 떨어진다는 단점이 있다.
// -> 따라서 크기가 비교적 작은 간단한 함수를 대체하는데 사용하는 것이 좋다.

// 매크로 함수는 다음과 같이 정의한다.
#define 함수명(인자) 치환식

// ex) 제곱함수
#include <iostream>
#define square(x) x * x // 매크로 함수 정의
using namespace std;

int main()
{
	cout << square(3) << endl;
	return 0;
}
// output : 9
// 
// square라는 이름의 매크로 함수를 생성하였고, 인자로는 x를 받는다. 그리고 인자 x를 x*x로 치환한다.
// 여기서 매크로 함수는 컴파일 되기 전에 전처리에 의해 3*3으로 치환된다.

// 매크로 함수의 유의 점
#include <iostream>
#define square(x) x * x // 매크로 함수 정의
using namespace std;

int main()
{
	cout << square(3+1) << endl;
	return 0;
}
// output : 7
// 
// square 함수는 제곱 기능을 하기 떄문에 3+1=4의 제곱인 16이 나올것 같지만 7이 나온다.
// 이는 전처리기에서 square(3+1)이 다음과 같이 치환되기 때문이다.
// x * x = 3 + 1 * 3 + 1 = 3 + 3 + 1 = 7
// 3 + 1 을 계산하기도 전에  x = 3 + 1로 치환 하였기 때문에 7이라는 결과가 나타났다.
// 이런 경우에는 다음과 같이 바꿔 주어야 한다.
#include <iostream>
#define square(x) (x) * (x)
using namespace std;

int main() {
	cout << square(3 + 1) << endl;
	return 0;
}
// output : 16
//
//이 경우 전처리기에서 치환 할때 (3+1)*(3+1)로 처리되기 때문에 정상적으로 정답이 16이 나왔다.

// 전처리 지시자를 활용한 매크로 함수
// #을 이용한 매크로 함수
#include <iostream>
#define printString(str) cout << #str;
using namespace std;

int main()
{
	printString(Hello);
	return 0;
}
// output : Hello

// #은 어떠한 인자 앞에 붙으면 해당 인자를 문자열로 바꾸어 버린다.
// ##을 이용한 매크로 함수
#include <iostream>
#define Comb(a, b) a ## b;
using namespace std;

int main() {
	int Comb(x, y);
	xy = 3;
	cout << xy << endl;
	return 0;
}
// output : 3

// ##을 받은 인자들을 하나로 합치는 기능을 수행한다.
// 위 코드에서는 x와 y를 합쳐 xy의 이름으로 int 자료형을 생성하였다.