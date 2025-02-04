// 코루틴 함수의 일시정지 장법을 지정하고, 코루틴 함수에서 co_yield, co_return했을 때 
// yield_value()나 return_value()로 데이터를 전달 받는다.

// 사용자가 정의 해야 하는 필수 멤버 함수는 다음과 같다.
// (대기가능 개체(AwaitableType)는 일시정지 방법을 결정한다.)

// 기본 생성자								- class에 당연히 있어야 하는 것
// CoroutineObjectType get_return_object()	- 코루틴 개체를 생성하여 리턴한다.
// AwaitableType initial_suspend()			- 코루틴 함수 실행 초기의 일시정시 상태를 리턴한다.
// AwaitableType final_suspend() noexcept	- 코루틴 함수 종료시 일시 정지 상태를 리턴한다.
// void unhandled_exception()				- 코루틴 함수에서 예외 발생시 호출된다.

// 또한, co_return, co_yield사용 여부에 따라 다음 함수를 선택적으로 구현한다.

// void return_void()						- 코루틴 함수에서 co_return; 시 호출된다.
// void return_value(ValuType val)			- 코루틴 함수에서 co_return val; 시 호출된다.
// AwaitableType yield_value(ValueType val)	- 코루틴 함수에서 co_yield val; 시 호출된다.

// 대기 가능 개체(suspend_always와 suspend_never)
// 대기 가능 개체는 다음 멤버 함수를 구현한 개체이다.

// await_ready()	- 결과가 준비 되었는지 여부. false를 리턴하면 await_suspend()를 호출한다.
// await_suspend()	- 코루틴의 실행 재개나 소멸을 결정한다.
// await_resume()	- co_await의 결과를 제공한다.

// stl에서는 다음 2가지 미리 정의된 대기 가능 개체를 제공한다.

// suspend_always	- await_ready()에서 항상 false를 리턴하며, 대기한다.
// suspend_never	- awiat_ready()에서 항상 true를 리턴하며, 대기하지 않는다.

// co_awiat에서 initial_suspend()시 suspend_always를 이용했다.
auto initial_suspend() {return std::suspend_always{};} // #5. 코루틴 함수 실행 초기의 일시 정지 상태입니다.

// 이에 따라 코루틴 함수를 호출하자 마자 일시 정지가 되어 다음처럼 Resume()을 호출 했었다.

MyCoroutine obj = CoroutineFunc();

std::cout << "Call #1" << std::endl;
obj.Resume(); // 코루틴 함수를 호출하자마자 일시 정지하므로 Resume()을 호출합니다.

std::cout << "Call #2" << std::endl;
obj.Resume();

std::cout << "Call #3" << std::endl;
obj.Resume();

// 실행결과

// Call #1 // 호출자 실행 
// CoroutineFunc #1 // 코루틴 함수 재개
// Call #2 // 호출자 실행
// CoroutineFunc #2 // 코루틴 함수 재개
// Call #3 // 호출자 실행
// CoroutineFunc #3 // 코루틴 함수 재개

// 아래는 initial_suspend()시 suspend_never를 사용한 예시이다. 코루틴 함수를 시작하자 마자 일시정지 하지 
// 않고 co_awiat를 만날 때 까지 실행되므로, 호출되는 순서가 이전과는 달라진다.

// 코루틴 개체
class MyCoroutine {
	// ...중략 ...
public:
	// ...중략 ...

	// Promise 개체
	struct MyPromise {
		// ... 중략 ...
		auto initial_suspend() { return std::suspend_never{}; } // 코루틴 함수 실행 초기의 일시 정지 상태입니다.
		auto final_suspend() noexcept { return std::suspend_always{}; }
		void unhandled_exception() {}
	};
};
// 코루틴 함수
MyCoroutine CoroutineFunc() {
	std::cout << "CoroutineFunc #1" << std::endl; // #1. 최초 실행시 일시 정지 하지 않고 실행됩니다.
	co_await std::suspend_always{}; // #2. 일시 정지 합니다.
	std::cout << "CoroutineFunc #2" << std::endl;
	co_await std::suspend_always{}; // 일시 정지 합니다.
	std::cout << "CoroutineFunc #3" << std::endl;
}

// 다음과 같이 CoroutineFunc()이 실행하면, CoroutineFunc()의 #1이 실행된 다음 #2에서 일시정지한다.

MyCoroutine obj = CoroutineFunc(); // CoroutineFunc #1

std::cout << "Call #1" << std::endl;
obj.Resume(); // CoroutineFunc #2

std::cout << "Call #2" << std::endl;
obj.Resume(); // CoroutineFunc #3

std::cout << "Call #3" << std::endl;

// 실행 결과는 아래와 같다.
CoroutineFunc #1
Call #1
CoroutineFunc #2
Call #2
CoroutineFunc #3
Call #3

//Promise 개체의 예외 처리
// 코루틴 함수에서 예외가 발생하면, 특별히 try-catch()하지 않아도 promise 개체의 unhandled_exception()함수가
// 호출된다. 이때 코루틴이 종료되었으므로, Resume()시 m_Handler.resume()이 호출되지 않도록 m_Handler.done()
// 으로 조건 검사를 해야한다.

// 코루틴 개체
class MyCoroutine {
public:
	// ...중략 ...
public:
	// ...중략 ...
	void Resume() const {
		if (!m_Handler.done()) { // 예외가 발생되면 코루틴은 종료됩니다.  
			m_Handler.resume(); // 따라서 m_Handler.resume(); 이 호출되지 않도록 합니다.
		}
	}
	// ...중략 ...

	// Promise 개체
	struct MyPromise {
		// ...중략 ...
		auto initial_suspend() { return std::suspend_always{}; }
		auto final_suspend() noexcept { return std::suspend_always{}; }
		void unhandled_exception() { std::cout << "Coroutine : unhandled_exception" << std::endl; } // 예외 발생시 호출됩니다. 
	};
};

// 코루틴 함수
MyCoroutine CoroutineFunc() {
	std::cout << "CoroutineFunc #1" << std::endl;
	throw 1; // 억지로 예외를 발생시킵니다.
	co_await std::suspend_always{}; // 예외가 발생하여 더이상 실행되지 않습니다.
	std::cout << "CoroutineFunc #2" << std::endl; // 예외가 발생하여 더이상 실행되지 않습니다.
	co_await std::suspend_always{}; // 예외가 발생하여 더이상 실행되지 않습니다.
	std::cout << "CoroutineFunc #3" << std::endl; // 예외가 발생하여 더이상 실행되지 않습니다.
}

MyCoroutine obj = CoroutineFunc();

std::cout << "Call #1" << std::endl;
obj.Resume(); // CoroutineFunc #1 출력 후 예외를 발생합니다.

std::cout << "Call #2" << std::endl;
obj.Resume(); // CoroutineFunc #2 -> 실행되지 않습니다.

std::cout << "Call #3" << std::endl;
obj.Resume(); // CoroutineFunc #3 -> 실행되지 않습니다.

// 실행 결과는 다음과 같다. 예외 발생시 unhandled_exception()에 작성된 내용이 실행되고, 코루틴은
// 재개되지 않는다.
CoroutineFunc #1
Coroutine : unhandled_exception
Call #2
Call #3

// 만약 호출자에서 예외를 받고 싶다면, unhandled_exception()에서 throw;로 예외를 전파하면 된다.
// 코루틴 개체
class MyCoroutine {
public:
	// ...중략 ...
public:
	// ...중략 ...
	void Resume() const {
		if (!m_Handler.done()) { // 예외가 발생되면 코루틴은 종료됩니다.  
			m_Handler.resume(); // 따라서 m_Handler.resume(); 이 호출되지 않도록 합니다.
		}
	}
	// ...중략 ...

	// Promise 개체
	struct MyPromise {
		// ...중략 ...
		auto initial_suspend() { return std::suspend_always{}; }
		auto final_suspend() noexcept { return std::suspend_always{}; }
		void unhandled_exception() { throw; } // 예외를 전파 합니다. 
	};
};

// 코루틴 함수
MyCoroutine CoroutineFunc() {
	std::cout << "CoroutineFunc #1" << std::endl;
	throw 1; // 억지로 예외를 발생시킵니다.
	co_await std::suspend_always{}; // 예외가 발생하여 더이상 실행되지 않습니다.
	std::cout << "CoroutineFunc #2" << std::endl; // 예외가 발생하여 더이상 실행되지 않습니다.
	co_await std::suspend_always{}; // 예외가 발생하여 더이상 실행되지 않습니다.
	std::cout << "CoroutineFunc #3" << std::endl; // 예외가 발생하여 더이상 실행되지 않습니다.
}

try {
	MyCoroutine obj = CoroutineFunc();

	std::cout << "Call #1" << std::endl;
	obj.Resume(); // CoroutineFunc #1 출력 후 예외를 발생합니다.

	std::cout << "Call #2" << std::endl; // 예외가 발생하여 더이상 실행되지 않습니다.
	obj.Resume(); // 예외가 발생하여 더이상 실행되지 않습니다.

	std::cout << "Call #3" << std::endl; // 예외가 발생하여 더이상 실행되지 않습니다.
	obj.Resume(); // 예외가 발생하여 더이상 실행되지 않습니다.
}
catch (const int&) {
	std::cout << "Coroutine : throw 1;" << std::endl;
}

// 실행 결과는 다음과 같다. 예외를 전파한 이후로는 호출자의 함수도 실행되지 않는다.
CoroutineFunc #1
Coroutine : throw 1; // 예외가 발생한 이후로는 호출자의 함수도 실행되지 않습니다.