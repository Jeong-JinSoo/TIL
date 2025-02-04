// �ڷ�ƾ �Լ��� �Ͻ����� ����� �����ϰ�, �ڷ�ƾ �Լ����� co_yield, co_return���� �� 
// yield_value()�� return_value()�� �����͸� ���� �޴´�.

// ����ڰ� ���� �ؾ� �ϴ� �ʼ� ��� �Լ��� ������ ����.
// (��Ⱑ�� ��ü(AwaitableType)�� �Ͻ����� ����� �����Ѵ�.)

// �⺻ ������								- class�� �翬�� �־�� �ϴ� ��
// CoroutineObjectType get_return_object()	- �ڷ�ƾ ��ü�� �����Ͽ� �����Ѵ�.
// AwaitableType initial_suspend()			- �ڷ�ƾ �Լ� ���� �ʱ��� �Ͻ����� ���¸� �����Ѵ�.
// AwaitableType final_suspend() noexcept	- �ڷ�ƾ �Լ� ����� �Ͻ� ���� ���¸� �����Ѵ�.
// void unhandled_exception()				- �ڷ�ƾ �Լ����� ���� �߻��� ȣ��ȴ�.

// ����, co_return, co_yield��� ���ο� ���� ���� �Լ��� ���������� �����Ѵ�.

// void return_void()						- �ڷ�ƾ �Լ����� co_return; �� ȣ��ȴ�.
// void return_value(ValuType val)			- �ڷ�ƾ �Լ����� co_return val; �� ȣ��ȴ�.
// AwaitableType yield_value(ValueType val)	- �ڷ�ƾ �Լ����� co_yield val; �� ȣ��ȴ�.

// ��� ���� ��ü(suspend_always�� suspend_never)
// ��� ���� ��ü�� ���� ��� �Լ��� ������ ��ü�̴�.

// await_ready()	- ����� �غ� �Ǿ����� ����. false�� �����ϸ� await_suspend()�� ȣ���Ѵ�.
// await_suspend()	- �ڷ�ƾ�� ���� �簳�� �Ҹ��� �����Ѵ�.
// await_resume()	- co_await�� ����� �����Ѵ�.

// stl������ ���� 2���� �̸� ���ǵ� ��� ���� ��ü�� �����Ѵ�.

// suspend_always	- await_ready()���� �׻� false�� �����ϸ�, ����Ѵ�.
// suspend_never	- awiat_ready()���� �׻� true�� �����ϸ�, ������� �ʴ´�.

// co_awiat���� initial_suspend()�� suspend_always�� �̿��ߴ�.
auto initial_suspend() {return std::suspend_always{};} // #5. �ڷ�ƾ �Լ� ���� �ʱ��� �Ͻ� ���� �����Դϴ�.

// �̿� ���� �ڷ�ƾ �Լ��� ȣ������ ���� �Ͻ� ������ �Ǿ� ����ó�� Resume()�� ȣ�� �߾���.

MyCoroutine obj = CoroutineFunc();

std::cout << "Call #1" << std::endl;
obj.Resume(); // �ڷ�ƾ �Լ��� ȣ�����ڸ��� �Ͻ� �����ϹǷ� Resume()�� ȣ���մϴ�.

std::cout << "Call #2" << std::endl;
obj.Resume();

std::cout << "Call #3" << std::endl;
obj.Resume();

// ������

// Call #1 // ȣ���� ���� 
// CoroutineFunc #1 // �ڷ�ƾ �Լ� �簳
// Call #2 // ȣ���� ����
// CoroutineFunc #2 // �ڷ�ƾ �Լ� �簳
// Call #3 // ȣ���� ����
// CoroutineFunc #3 // �ڷ�ƾ �Լ� �簳

// �Ʒ��� initial_suspend()�� suspend_never�� ����� �����̴�. �ڷ�ƾ �Լ��� �������� ���� �Ͻ����� ���� 
// �ʰ� co_awiat�� ���� �� ���� ����ǹǷ�, ȣ��Ǵ� ������ �������� �޶�����.

// �ڷ�ƾ ��ü
class MyCoroutine {
	// ...�߷� ...
public:
	// ...�߷� ...

	// Promise ��ü
	struct MyPromise {
		// ... �߷� ...
		auto initial_suspend() { return std::suspend_never{}; } // �ڷ�ƾ �Լ� ���� �ʱ��� �Ͻ� ���� �����Դϴ�.
		auto final_suspend() noexcept { return std::suspend_always{}; }
		void unhandled_exception() {}
	};
};
// �ڷ�ƾ �Լ�
MyCoroutine CoroutineFunc() {
	std::cout << "CoroutineFunc #1" << std::endl; // #1. ���� ����� �Ͻ� ���� ���� �ʰ� ����˴ϴ�.
	co_await std::suspend_always{}; // #2. �Ͻ� ���� �մϴ�.
	std::cout << "CoroutineFunc #2" << std::endl;
	co_await std::suspend_always{}; // �Ͻ� ���� �մϴ�.
	std::cout << "CoroutineFunc #3" << std::endl;
}

// ������ ���� CoroutineFunc()�� �����ϸ�, CoroutineFunc()�� #1�� ����� ���� #2���� �Ͻ������Ѵ�.

MyCoroutine obj = CoroutineFunc(); // CoroutineFunc #1

std::cout << "Call #1" << std::endl;
obj.Resume(); // CoroutineFunc #2

std::cout << "Call #2" << std::endl;
obj.Resume(); // CoroutineFunc #3

std::cout << "Call #3" << std::endl;

// ���� ����� �Ʒ��� ����.
CoroutineFunc #1
Call #1
CoroutineFunc #2
Call #2
CoroutineFunc #3
Call #3

//Promise ��ü�� ���� ó��
// �ڷ�ƾ �Լ����� ���ܰ� �߻��ϸ�, Ư���� try-catch()���� �ʾƵ� promise ��ü�� unhandled_exception()�Լ���
// ȣ��ȴ�. �̶� �ڷ�ƾ�� ����Ǿ����Ƿ�, Resume()�� m_Handler.resume()�� ȣ����� �ʵ��� m_Handler.done()
// ���� ���� �˻縦 �ؾ��Ѵ�.

// �ڷ�ƾ ��ü
class MyCoroutine {
public:
	// ...�߷� ...
public:
	// ...�߷� ...
	void Resume() const {
		if (!m_Handler.done()) { // ���ܰ� �߻��Ǹ� �ڷ�ƾ�� ����˴ϴ�.  
			m_Handler.resume(); // ���� m_Handler.resume(); �� ȣ����� �ʵ��� �մϴ�.
		}
	}
	// ...�߷� ...

	// Promise ��ü
	struct MyPromise {
		// ...�߷� ...
		auto initial_suspend() { return std::suspend_always{}; }
		auto final_suspend() noexcept { return std::suspend_always{}; }
		void unhandled_exception() { std::cout << "Coroutine : unhandled_exception" << std::endl; } // ���� �߻��� ȣ��˴ϴ�. 
	};
};

// �ڷ�ƾ �Լ�
MyCoroutine CoroutineFunc() {
	std::cout << "CoroutineFunc #1" << std::endl;
	throw 1; // ������ ���ܸ� �߻���ŵ�ϴ�.
	co_await std::suspend_always{}; // ���ܰ� �߻��Ͽ� ���̻� ������� �ʽ��ϴ�.
	std::cout << "CoroutineFunc #2" << std::endl; // ���ܰ� �߻��Ͽ� ���̻� ������� �ʽ��ϴ�.
	co_await std::suspend_always{}; // ���ܰ� �߻��Ͽ� ���̻� ������� �ʽ��ϴ�.
	std::cout << "CoroutineFunc #3" << std::endl; // ���ܰ� �߻��Ͽ� ���̻� ������� �ʽ��ϴ�.
}

MyCoroutine obj = CoroutineFunc();

std::cout << "Call #1" << std::endl;
obj.Resume(); // CoroutineFunc #1 ��� �� ���ܸ� �߻��մϴ�.

std::cout << "Call #2" << std::endl;
obj.Resume(); // CoroutineFunc #2 -> ������� �ʽ��ϴ�.

std::cout << "Call #3" << std::endl;
obj.Resume(); // CoroutineFunc #3 -> ������� �ʽ��ϴ�.

// ���� ����� ������ ����. ���� �߻��� unhandled_exception()�� �ۼ��� ������ ����ǰ�, �ڷ�ƾ��
// �簳���� �ʴ´�.
CoroutineFunc #1
Coroutine : unhandled_exception
Call #2
Call #3

// ���� ȣ���ڿ��� ���ܸ� �ް� �ʹٸ�, unhandled_exception()���� throw;�� ���ܸ� �����ϸ� �ȴ�.
// �ڷ�ƾ ��ü
class MyCoroutine {
public:
	// ...�߷� ...
public:
	// ...�߷� ...
	void Resume() const {
		if (!m_Handler.done()) { // ���ܰ� �߻��Ǹ� �ڷ�ƾ�� ����˴ϴ�.  
			m_Handler.resume(); // ���� m_Handler.resume(); �� ȣ����� �ʵ��� �մϴ�.
		}
	}
	// ...�߷� ...

	// Promise ��ü
	struct MyPromise {
		// ...�߷� ...
		auto initial_suspend() { return std::suspend_always{}; }
		auto final_suspend() noexcept { return std::suspend_always{}; }
		void unhandled_exception() { throw; } // ���ܸ� ���� �մϴ�. 
	};
};

// �ڷ�ƾ �Լ�
MyCoroutine CoroutineFunc() {
	std::cout << "CoroutineFunc #1" << std::endl;
	throw 1; // ������ ���ܸ� �߻���ŵ�ϴ�.
	co_await std::suspend_always{}; // ���ܰ� �߻��Ͽ� ���̻� ������� �ʽ��ϴ�.
	std::cout << "CoroutineFunc #2" << std::endl; // ���ܰ� �߻��Ͽ� ���̻� ������� �ʽ��ϴ�.
	co_await std::suspend_always{}; // ���ܰ� �߻��Ͽ� ���̻� ������� �ʽ��ϴ�.
	std::cout << "CoroutineFunc #3" << std::endl; // ���ܰ� �߻��Ͽ� ���̻� ������� �ʽ��ϴ�.
}

try {
	MyCoroutine obj = CoroutineFunc();

	std::cout << "Call #1" << std::endl;
	obj.Resume(); // CoroutineFunc #1 ��� �� ���ܸ� �߻��մϴ�.

	std::cout << "Call #2" << std::endl; // ���ܰ� �߻��Ͽ� ���̻� ������� �ʽ��ϴ�.
	obj.Resume(); // ���ܰ� �߻��Ͽ� ���̻� ������� �ʽ��ϴ�.

	std::cout << "Call #3" << std::endl; // ���ܰ� �߻��Ͽ� ���̻� ������� �ʽ��ϴ�.
	obj.Resume(); // ���ܰ� �߻��Ͽ� ���̻� ������� �ʽ��ϴ�.
}
catch (const int&) {
	std::cout << "Coroutine : throw 1;" << std::endl;
}

// ���� ����� ������ ����. ���ܸ� ������ ���ķδ� ȣ������ �Լ��� ������� �ʴ´�.
CoroutineFunc #1
Coroutine : throw 1; // ���ܰ� �߻��� ���ķδ� ȣ������ �Լ��� ������� �ʽ��ϴ�.