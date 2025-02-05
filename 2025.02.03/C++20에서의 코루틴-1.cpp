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
//
// #1 : 함수 내부에 co_await를 사용한 코루틴 함수입니다. co_await를 할때마다 함수를 일시 정지하고 제어권을 호출자에게 넘깁니다.
// #2 : 코루틴 개체입니다. #3의 코루틴 핸들을 관리하며, 일시 정지한 코루틴을 m_Handler.resume()으로 외부에서 재개할 수 있게 합니다.또한 명칭이 promise_type인 종속 타입이 있어야 합니다.
// #3 : 코루틴 핸들입니다.코루틴 개체의 소멸자에서 destroy()됩니다.
// #4 : promise 개체 입니다.get_return_object()로 코루틴 개체를 생성합니다.
// #5 : 코루틴 함수를 시작할때 일시 정지를 어떻게 할 것인지 지정합니다.본 예에서는 suspend_always를 사용하여 시작할때 일시 정지하도록 설정했습니다.
// #6 : 코루틴 함수를 종료할때 일시 정지를 어떻게 할 것인지 지정합니다.본 예에서는 suspend_always를 사용하여 종료할때 일시 정지하도록 설정했습니다.

// 코루틴 개체
class MyCoroutine
{ // #2
public:
	struct MyPromise;
	using promise_type = myPromise; // #2. 명칭이 promise_type인 종속 타입이 있어야 한다.
private:
	std::coroutine_handle<promise_type> m_Handler; // #3. 코루틴 핸들
public:
	std::coroutine(std::corotine_handle<promise_type> handler) : m_Handler(handler) {}
	~MyCorotine()
	{
		if (m_Handler)
		{
			m_Handler.destory(); // #3. 코루틴 개체에서 소멸해야 한다.
		}
	}

	MyCoroutine(const MyCoroutine&) = delete;
	MyCoroutine(MyCoroutine&&) = delete;
	MyCoroutine& operator =(const MyCoroutine&) = delete;
	MyCoroutine& operator =(MyCoroutine&&) = delete;

	void Resume() const
	{	// #2. 일시 정지된 코루틴을 재개한다.
		if (!m_Handler.done())
		{	// 코루틴이 종료되지 않았다면
			m_Handler.resume();	// 재개합니다.
		}
	}

	//Promise 개체
	struct MyPromise
	{ // #4
		MyPromise() = default;
		~MyPromise() = default;
		MyPromise(const MyPromise&) = delete;
		MyPromise& operator = (const MyPromise&) = delete;
		MyPromise& operator =(MyPromise&&) = delete;

		MyCoroutine get_return_object()
		{	// #4. 코루틴 개체를 리턴한다.
			return MyCoroutine{ std::coroutine_handle<MyPromise>::from_promise(*this) }
		}

		auto inital_suspend()
		{
			return std::suspend_always{};
		}	// #5. 코루틴 함수 실행 초기의 일시 정지 상태.

		auto final_suspend() noexcept
		{
			return std::suspend_always{};
		}	// #6. 코루틴 함수 종료시 일시정지 상태.

		void unhandled_exception() {} // 예외 발생시 호출된다.
	};
};

// 코루틴 함수
MyCoroutine CoroutineFunc() {  // MyCoroutine 개체를 사용하는 코루틴 함수 
	std::cout << "CoroutineFunc #1" << std::endl;
	co_await std::suspend_always{}; // #1
	std::cout << "CoroutineFunc #2" << std::endl;
	co_await std::suspend_always{}; // #1
	std::cout << "CoroutineFunc #3" << std::endl;
}

// 상기 예를 다음과 같이 실행하면,
std::cout << "Call #1" << std::endl;
MyCoroutine object = CoroutineFunc();
std::cout << "Call #2" << std::endl;

// 아래와 같이 CoroutineFunc()의 어떠한 내용도 실행되지 않는다. 이는 #5에서 initial_suspend()에서
// suspend_always{}를 하여 실행 초기에 일시정지를 해뒀기 때문이다.

Output = 
Call #1
Call #2

// 따라서 다음과 같이 Resume()을 해줘야 한다.
MyCoroutine obj = CoroutineFunc();

std::cout << "Call #1" << std::endl;
obj.Resume(); // CoroutineFunc #1

std::cout << "Call #2" << std::endl;
obj.Resume(); // CoroutineFunc #2

std::cout << "Call #3" << std::endl;
obj.Resume(); // CoroutineFunc #3

// 그러면 호출자의 내용과 CorotineFunc()이 번갈아 실행되는 것을 확인 할 수 있다.
Call #1 // 호출자 실행 
CoroutineFunc #1 // 코루틴 함수 재개
Call #2 // 호출자 실행
CoroutineFunc #2 // 코루틴 함수 재개
Call #3 // 호출자 실행
CoroutineFunc #3 // 코루틴 함수 재개