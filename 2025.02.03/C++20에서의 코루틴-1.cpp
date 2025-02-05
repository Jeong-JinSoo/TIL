// C++���� �Ϲ������� �Լ��� ȣ���ϸ� ���� �� �� ���� ����ǰ� ����ȴ�.
// �ڷ�ƾ�� �̿� �ٸ��� �Ͻ� ����(Suspend)�ϰ� �簳(Resume)�� �� �ִ� �Լ��̴�.
// �Ͻ������ϰ� �簳�� ���� �ʿ��� ������ ���� ����ȴ�.
// 
// �ڷ�ƾ�� �Ͻ������� ���� ������ ����Ѵ�.
// co_await -�Ͻ� ���� �ϰ� ������� ȣ���ڿ��� �ѱ��.
// co_yield -�Ͻ� ���� �ϰ� ������� ȣ���ڿ��� �ѱ��.�̶� ���� ���� �����Ѵ�.
// co_retrun - ���������� �����ϰ� ������� ȣ���ڿ��� �ѱ��.�̋� ���� ���� �����Ѵ�.
// 
// �ڷ�ƾ �Լ�, �ڷ�ƾ ��ü, �ڷ�ƾ �ڵ�, promise ��ü
// �Լ��� ��쿡�� ���� ���� ȣ���ڰ� �ٷ� ���� ���� �� �ִ�.�ڷ�ƾ�� �Ͻ������� �簳�� �ؾ� �ϰ�,
//  �Ͻ� ������ ���¿��� ���� ���� �޾ƾ� �ϱ� ������ ���� ��ü���� �����Ͽ� �����Ѵ�.
// 
// �ڷ�ƾ �Լ� - �Լ� ����.�Լ� ������ co_await, co_yield, co_return�� ����ȴ�.
//  (�Լ� ������ �ش� Ű���� ���� �ۼ��ϸ� �ڷ�ƾ �Լ��� ��޵ȴ�.)
// �ڷ�ƾ ��ü - �ڷ�ƾ �Լ� ȣ���ڿ� ������ ����� �ϸ�, �ڷ�ƾ �ڵ��� �����Ѵ�.
// �ڷ�ƾ �ڵ� - promise ��ü�� �����Ѵ�.�ַ� �ڷ�ƾ �Լ��� �簳�ϴµ� ����Ѵ�.
// promise ��ü - �ڷ�ƾ �Լ��� �Ͻ����� ����� �����ϰ�, �ڷ�ƾ �Լ����� co_yield, co_return���� ��
//  yield_value()�� retrun_value()�� �����͸� ���� �޴´�.
// 
// co_await
// co_await�� �ڷ�ƾ �Լ��� �Ͻ� �����ϰ� ������� ȣ���ڿ��� �ѱ��.
// ������ �Ͻ����� �� ���� �ϴ� �⺻���� �ڷ�ƾ����, promise ��ü, �ڷ�ƾ �ڵ�� ������ �ڷ�ƾ ��ü��
//  �̸� ����ϴ� �ڷ�ƾ �Լ��� �����Ǿ� �ִ�.
//
// #1 : �Լ� ���ο� co_await�� ����� �ڷ�ƾ �Լ��Դϴ�. co_await�� �Ҷ����� �Լ��� �Ͻ� �����ϰ� ������� ȣ���ڿ��� �ѱ�ϴ�.
// #2 : �ڷ�ƾ ��ü�Դϴ�. #3�� �ڷ�ƾ �ڵ��� �����ϸ�, �Ͻ� ������ �ڷ�ƾ�� m_Handler.resume()���� �ܺο��� �簳�� �� �ְ� �մϴ�.���� ��Ī�� promise_type�� ���� Ÿ���� �־�� �մϴ�.
// #3 : �ڷ�ƾ �ڵ��Դϴ�.�ڷ�ƾ ��ü�� �Ҹ��ڿ��� destroy()�˴ϴ�.
// #4 : promise ��ü �Դϴ�.get_return_object()�� �ڷ�ƾ ��ü�� �����մϴ�.
// #5 : �ڷ�ƾ �Լ��� �����Ҷ� �Ͻ� ������ ��� �� ������ �����մϴ�.�� �������� suspend_always�� ����Ͽ� �����Ҷ� �Ͻ� �����ϵ��� �����߽��ϴ�.
// #6 : �ڷ�ƾ �Լ��� �����Ҷ� �Ͻ� ������ ��� �� ������ �����մϴ�.�� �������� suspend_always�� ����Ͽ� �����Ҷ� �Ͻ� �����ϵ��� �����߽��ϴ�.

// �ڷ�ƾ ��ü
class MyCoroutine
{ // #2
public:
	struct MyPromise;
	using promise_type = myPromise; // #2. ��Ī�� promise_type�� ���� Ÿ���� �־�� �Ѵ�.
private:
	std::coroutine_handle<promise_type> m_Handler; // #3. �ڷ�ƾ �ڵ�
public:
	std::coroutine(std::corotine_handle<promise_type> handler) : m_Handler(handler) {}
	~MyCorotine()
	{
		if (m_Handler)
		{
			m_Handler.destory(); // #3. �ڷ�ƾ ��ü���� �Ҹ��ؾ� �Ѵ�.
		}
	}

	MyCoroutine(const MyCoroutine&) = delete;
	MyCoroutine(MyCoroutine&&) = delete;
	MyCoroutine& operator =(const MyCoroutine&) = delete;
	MyCoroutine& operator =(MyCoroutine&&) = delete;

	void Resume() const
	{	// #2. �Ͻ� ������ �ڷ�ƾ�� �簳�Ѵ�.
		if (!m_Handler.done())
		{	// �ڷ�ƾ�� ������� �ʾҴٸ�
			m_Handler.resume();	// �簳�մϴ�.
		}
	}

	//Promise ��ü
	struct MyPromise
	{ // #4
		MyPromise() = default;
		~MyPromise() = default;
		MyPromise(const MyPromise&) = delete;
		MyPromise& operator = (const MyPromise&) = delete;
		MyPromise& operator =(MyPromise&&) = delete;

		MyCoroutine get_return_object()
		{	// #4. �ڷ�ƾ ��ü�� �����Ѵ�.
			return MyCoroutine{ std::coroutine_handle<MyPromise>::from_promise(*this) }
		}

		auto inital_suspend()
		{
			return std::suspend_always{};
		}	// #5. �ڷ�ƾ �Լ� ���� �ʱ��� �Ͻ� ���� ����.

		auto final_suspend() noexcept
		{
			return std::suspend_always{};
		}	// #6. �ڷ�ƾ �Լ� ����� �Ͻ����� ����.

		void unhandled_exception() {} // ���� �߻��� ȣ��ȴ�.
	};
};

// �ڷ�ƾ �Լ�
MyCoroutine CoroutineFunc() {  // MyCoroutine ��ü�� ����ϴ� �ڷ�ƾ �Լ� 
	std::cout << "CoroutineFunc #1" << std::endl;
	co_await std::suspend_always{}; // #1
	std::cout << "CoroutineFunc #2" << std::endl;
	co_await std::suspend_always{}; // #1
	std::cout << "CoroutineFunc #3" << std::endl;
}

// ��� ���� ������ ���� �����ϸ�,
std::cout << "Call #1" << std::endl;
MyCoroutine object = CoroutineFunc();
std::cout << "Call #2" << std::endl;

// �Ʒ��� ���� CoroutineFunc()�� ��� ���뵵 ������� �ʴ´�. �̴� #5���� initial_suspend()����
// suspend_always{}�� �Ͽ� ���� �ʱ⿡ �Ͻ������� �صױ� �����̴�.

Output = 
Call #1
Call #2

// ���� ������ ���� Resume()�� ����� �Ѵ�.
MyCoroutine obj = CoroutineFunc();

std::cout << "Call #1" << std::endl;
obj.Resume(); // CoroutineFunc #1

std::cout << "Call #2" << std::endl;
obj.Resume(); // CoroutineFunc #2

std::cout << "Call #3" << std::endl;
obj.Resume(); // CoroutineFunc #3

// �׷��� ȣ������ ����� CorotineFunc()�� ������ ����Ǵ� ���� Ȯ�� �� �� �ִ�.
Call #1 // ȣ���� ���� 
CoroutineFunc #1 // �ڷ�ƾ �Լ� �簳
Call #2 // ȣ���� ����
CoroutineFunc #2 // �ڷ�ƾ �Լ� �簳
Call #3 // ȣ���� ����
CoroutineFunc #3 // �ڷ�ƾ �Լ� �簳