// C++에서 일반적으로 함수는 호출하면 리턴 할 때 까지 실행되고 종료된다.
// 코루틴은 이와 다르게 일시 정지(Suspend)하고 재개(Resume)할 수 있는 함수이다.
// 일시정지하고 재개를 위해 필요한 정보는 힙에 저장된다.
// 
// 코루틴은 일시정지를 위해 다음을 사용한다.
// co_await -일시 정지 하고 제어권을 호출자에게 넘긴다.
// co_yield -일시 정지 하고 제어권을 호출자에게 넘긴다.이때 리턴 값을 전달한다.
// co_retrun - 최종적으로 종료하고 제어권을 호출자에게 넘긴다.이떄 리턴 값을 전달한다.
// 
// 코루틴 함수, 코루틴 개체, 코루틴 핸들, promise 개체
// 함수의 경우에는 리턴 값을 호출자가 바로 전달 받을 수 있다.코루틴은 일시정지와 재개를 해야 하고,
//  일시 정지한 상태에서 값을 전달 받아야 하기 떄문에 여러 개체들이 협력하여 동작한다.
// 
// 코루틴 함수 - 함수 본문.함수 내에서 co_await, co_yield, co_return로 제어된다.
//  (함수 본문에 해당 키워드 들을 작성하면 코루틴 함수로 취급된다.)
// 코루틴 개체 - 코루틴 함수 호출자와 데이터 통신을 하며, 코루틴 핸들을 관리한다.
// 코루틴 핸들 - promise 개체를 관리한다.주로 코루틴 함수를 재개하는데 사용한다.
// promise 개체 - 코루틴 함수의 일시정지 방법을 제공하고, 코루틴 함수에서 co_yield, co_return했을 때
//  yield_value()나 retrun_value()로 데이터를 전달 받는다.
// 
// co_await
// co_await는 코루틴 함수를 일시 정지하고 제어권을 호출자에게 넘긴다.
// 다음은 일시정지 후 제개 하는 기본적인 코루틴으로, promise 개체, 코루틴 핸들로 구성된 코루틴 개체와
//  이를 사용하는 코루틴 함수로 구성되어 있다.

// 코루틴 개체
class MyCoroutine
{ // #2
public:
	struct MyPromise;
	using promise_type = myPromise; // #2. 명칭이 promise_type인 종속 타입이 있어야 합니다.
private:
	std::coroutine_handle<promise_type> m_Handler; // #3. 코루틴 핸들
public:
	std::coroutine(std::corotine_handle<promise_type> handler) : m_Handler(handler) {}
};