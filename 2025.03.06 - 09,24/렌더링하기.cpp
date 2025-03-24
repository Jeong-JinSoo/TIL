프레임 렌더링

Direct3D 초기화가 끝나면 실제 렌더링을 시작할 차례이다. 렌더링 자체는 매우 쉽지만 약간의 준비 작업이 필요하다. 이 수
업에서는 빈 프레임을 계속해서 렌더링 하기 위한 모든 것을 설정한다.

관련된 설정은 간단하다.해야 할 일이 두 가지 있다.첫째, GPU에 최종 이미지를 만들 메모리의 어느 부분을 알려야 한다.(이
경우 백버퍼를 말한다.) 들째, GPU에 백 버퍼의 어느 부분에 그려야 하는지 알려야 한다.

그 작업이 끝나면 렌더링을 시작 할 수 있다.

렌더 타겟 설정

렌더링 할 위치부터 시작해본다. 당연히 백버퍼이지만, 이 시점에서 Direct3D은 이 지섬에서 실제로 그것을 알지 못한다. 백
버퍼에 바로 렌더링 하고 싶지 않을 수도 있다. 예를 들어 많은 게임이 모델 표면에 렌더링 한 다음 해당 모델을 백 버처에 렌
더링 할 수도 있다.이 기술은 다양한 효과를 낼 수 있다. Portal이 대표적인 예시인데, 먼더 포털에 렌더링 한 다음 포탈 이
미지가 전체장면을 렌더링 한다.

Direct3D에서는 렌더링 할 때 렌더타겟을 설정해야 한다. 이것은 비디오 메모리에서 렌더링 할 위치를 유지하는 간단한 COM 객
체이다. 대부분의 경우 이것은 백 버퍼 이다.

우리가 이를 수행하는 방법은 다음과 같다.

ID3D11RenderTargetView* backbuffer; // 전역 선언

// 이 함수는 Direct3D를 초기화하고 사용할 수 있도록 준비합니다 
void InitD3D(HWND hWnd)
{
	// Direct3D 초기화 
	// ... 

	// 백 버퍼의 주소를 가져옵니다 
	ID3D11Texture2D* pBackBuffer;
	swapchain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);

	// 백 버퍼 주소를 사용하여 렌더 타겟을 생성합니다 
	dev->CreateRenderTargetView(pBackBuffer, NULL, &backbuffer);
	pBackBuffer->Release();

	// 렌더 타겟을 백 버퍼로 설정합니다 
	devcon->OMSetRenderTargets(1, &backbuffer, NULL);
}

여기서는 세가지가 수행된다.
첫째, 백 버퍼의 주소를 결정한다.
둘째, 해당 주소를 사용하여 렌더 타겟을 나타내는 COM 객체를 만든다.
셋째, 해당 객체를 활성 렌더 타겟으로 설정한다.

여기에 추가된 새로운 코드들이 무슨 뜻인지 알아보자.

ID3D11RenderTargetView* backbuffer;
	이 변수는 렌더 타겟에 대한 모든 정보를 보관하는 객체에 대한 포인터이다. 우리는 백 버퍼에 렌더링 할 것이므로 이
	변수를 'backbuffer'라고 부른다.

ID3D11Texture2D *pBackBuffer;
	3D 렌더링에서 텍스처는 이미지의 다른 이름입니다. ID3D11Texture2D는 플랫 이미지를 저장하는 객체이다. 모든 COM 객
	체와 마찬가지로 먼저 포인터를 정의하고 나중에 함수가 객체를 생성한다.

swapchain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
	이건 간단하다. 이 GetBuffer() 함수가 하는 일은 스왑체인에서 백 버퍼를 찾아서 pBackBuffer 텍스처 객체를 만드는 것
	이다.

	첫 번째 배개변수는 가져올 백 버퍼의 번호이다. 이 체인에서 백 버퍼 하나만 사용하고 있으며, 백버퍼 #0이다. 따라
	서 매개변수는 0이 된다. 

	두 번째 매개변수는 ID3D11Texture2D COM 객체를 식별하는 숫자이다. 각 유형의 COM 객체에는 고유한 ID가 있으며, 이를
	사용하여 해당 객체에 대한 정보를 얻는다. 이 ID를 얻으려면 __uuidof 연산자를 사용해야 한다. 이것이 어떻게 작동하는
	지에 대한 정확한 세부 사항은 지금 중요하지 않지만, 우리가 이렇게 하는 이유는 GetBuffer() 함수가 어떤 유형의 객체를
	만들어야 하는지 알 수 있도록 하기 위해서이다.

	세 번째 매개변수에는 void*에 대한 포인터가 있다. 이 void*는 ID3D11Texture2D객체의 위치로 채워진다. void*여야 하는데,
	우리가 요청 할 수 있는 다른 유형의 객체가 있기 때문이다.

	이 특정 기능은 지금 당장은 너무 많이 건드리지 않는다. 

dev->CreateRenderTargetView(pBackBuffer, NULL, &backbuffer);
	이 함수는 렌더 타겟 객체를 생성한다. 우리는 프로그램 맨 위에 이 객체에 대한 포인터를 생성했다.

	첫 번째 매개변수는 텍스처에 대한 포인터이다. 우리 프로그램의 경우 'pBackBuffer'여야 한다.

	두 번째 매개변수는 렌더 타겟을 설명하는 구조체이다. 백 버퍼에 대해서는 이것을 채울 필요가 없다. 그냥 NULL로 설정
	한다.

	세 번째 매개변수는 객체 포인터의 주소이다. 포인터의 이름은 'backbuffer' 였으므로 '&backbuffer'를 사용한다.

pBackBuffer->Release();
	Release() 함수는 모든 메모리를 해제하고 COM객체에서 새용하는 모든 스레드를 닫는다.
	pBackbuffer 객체에 대한 작업이 끝났으므로 Release()를 실행한다. 이렇게 하면 백버퍼가 파괴되지 않고, 엑세스 하는
	데 사용한 텍스처 객체만 닫힌다.

devcon->OMSetRenderTargets(1, &backbuffer, NULL);
	이 마지막 함수는 실제로 렌더 타겟을 설정한다. 더 정확히 말하면, 여러 렌더 타겟을 설정한다.

	첫 번째 매개변수는 설정할 렌더 타겟의 수 이다. 이는 일반적으로 1이지만 더 많은 경우가 있다.

	두 번째 매개변수는 렌더 타겟 뷰 객체 목록을 가리키는 포인터이다. 우리는 하나만 가지고 있으므로, 그것은 단지 우리의
	렌더 타겟 객체(&backbuffer)의 주소일 뿐이다.

	세 번째 매개변수는 고급이며, 이것은 나중에 다룬다 지금은 NULL로 둔다.

	이 다음은 조금 복잡하다. 무슨 일이 일어나는지 이해 할 때 까지 반복해서 보는 것이 좋다. Direct3D 프로그래밍에서 여
	러번 사용되고 수정되기 때문이다.

뷰포트 설정

	이 코드 섹션은 이전 코드에 비하면 아주 간단하다. 뷰포트는 픽셀좌표를 정규화된 자표로 변환하는 방법이다. 다음 다이어
	그램은 두 가지 차이점을 보여준다.

	http://www.directxtutorial.com/Lessons/11/B1-D3DGettingStarted/3/2.png

	왼쪽에서 픽셀 좌표는 왼쪽 위 모서리에서 0,0에서 시작하여 한 번에 한 픽셀씩 증가한다. 오른쪽에서 정규화된 좌표는 백
	버퍼의 크기에 관계 없이 -1,-1에서 시작하여 1,1로 증가한다. Normalized 라는 단어는 값이 1이 될 때 까지 조정된다는
	것을 의미한다.

	-1, -1, 1, 1이 실제로 무엇과 같은지는 뷰포트에 의해 결정된다. 뷰포트는 -1, -1, 1, 1이 픽셀 좌표에서 어디에 있는지
	설정할 수 있는 구조체이다.

	뷰포트를 설정하는 코드는 다음과 같다.

	void InitD3D(HWND hWnd)
	{
		// Direct3D 초기화 
		// ... 

		// 렌더 대상 설정 
		// ... 

		// 뷰포트 설정 
		D3D11_VIEWPORT viewport;
		ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));

		viewport.TopLeftX = 0;
		viewport.TopLeftY = 0;
		viewport.Width = 800;
		viewport.Height = 600;

		devcon->RSSetViewports(1, &viewport);
	}

	여기서 설명이 필요한 유일한 줄은 마지막 줄이다.

	RSSetViewPorts()는 뷰포트 구조체를 활성화 하는 함수이다. 첫번째 매개변수는 사용 중인 뷰포트의 수이고, 두번째 매개
	변수는 사용 중인 뷰포트의 수이고 두 번째 매개변수는 뷰포트 구조체에 대한 포인터 목록의 주소이다.

	여러 뷰포트를 사용하는 것은 특정 고급 상황에서 편리하지만, 여기서는 다루지 않는다. 지금은 1과 '&viewport'가 매개
	변수에 잘 맞는다.

렌더링 프레임

	다음으로 단일 프레임을 렌더링하는 함수를 만든다. 프레임은 지금은 매우 간단하여 파란색 배경으로만 구성된다. 물론 원
	한다면 색사을 변경 할 수 있다. 이 함수의 코드는 다음과 같다.

	// 이것은 단일 프레임을 렌더링하는 데 사용되는 함수
	void RenderFrame(void)
	{
		// 백 버퍼를 진한 파란색으로 지운다.
		devcon->ClearRenderTargetView(backbuffer, D3DXCOLOR(0.0f, 0.2f, 0.4f, 1.0f));

		// 여기서 백 버퍼에서 3D 렌더링을 수행한다

		// 백 버퍼와 프런트 버퍼를 전환한다.
		swapchain->Present(0, 0);
	}

	devcon->ClearRenderTargetView()
	이것은 렌더 타겟 버퍼를 특정 색상으로 채운다. 우리의 경우, 백 버퍼를 채운다. 매우 간단하다. 매개변수는 두개 있다.
	
	첫 번째는 렌더 타겟 객체의 주소이다. 우리는 여기에 'backbuffer'를 넣었다.

	두 번째 매개변수는 백버퍼를 채우고자 하는 색상이다. 이를 위해 D3DXCOLOR라는 간단한 구조체를 사용한다. 네개의 생성
	자 매개변수는 색상을 빌드하는 데 사용된다. 처음 세개는 빨간색, 녹색, 파란색 값이고 네 번째는 알파 값이다.

	swapchain->Present()
	다음으로 Present() 함수를 호출한다. 이 함수는 백 버퍼에 그려진 모든 것이 실제로 나타나는 곳이다. 이 함수의 역할은
	기본적으로 스왑체인에서 "swap"을 수행하여 백 버퍼가 프런트 버퍼가 되도록 하는 것이다.

	두 매개변수는 모두 0으로 설정되어 있으며, 이 토튜리얼에선 많이 사용되지 않는다.

Obligatory Cleanup
	지난 수업에서 우리는 우리가 만든 각 COM 객체를 해제하여 Direct3D를 종료했다. 대부분의 COM객체에는 이 Release()함
	수가 있으며, 있다면 우리는 완료되었을 때 그것을 호출해야 한다.
	렌더 타겟 객체도 예외는 아니다.

	// 이 함수는 Direct3D와 COM을 정리한다.
	void CleanD3D()
	{
		// 모든 기존 COM 객체를 닫고 해제한다. 
		swapchain->Release();
		backbuffer->Release();
		dev->Release();
		devcon->Release();
	}

모든 COM 객체가 릴리스되도록 하는 습관을 들이는 것이 좋다. 더 많이 추가 할 수록 하나하나 기억하기 힘들어 질 수 있다.

The Finished Program
	이제 Direct3D를 실행하고 창에 간단한 빈 프레임 렌더링을 할 수 있다.
	아래 새 코드를 추가한 전체 코드가 있다. 

// 기본 Windows 헤더 파일과 Direct3D 헤더 파일을 포함합니다. 
#include <windows.h> 
#include <windowsx.h> 
#include <d3d11.h> 
#include <d3dx11.h> 
#include <d3dx10.h> 

// Direct3D 라이브러리 파일을 포함합니다. 
#pragma comment (lib, "d3d11.lib") 
#pragma comment (lib, "d3dx11.lib") 
#pragma comment (lib, "d3dx10.lib") 

// 전역 선언 
IDXGISwapChain* swapchain; // 스왑 체인 인터페이스에 대한 포인터 
ID3D11Device* dev; // Direct3D 장치 인터페이스에 대한 포인터 
ID3D11DeviceContext* devcon; // Direct3D 장치 컨텍스트에 대한 포인터 
ID3D11RenderTargetView* backbuffer; // 백 버퍼에 대한 포인터

// 함수 프로토타입 
void InitD3D(HWND hWnd); // Direct3D를 설정하고 초기화합니다 
void RenderFrame(void); // 단일 프레임을 렌더링합니다
void CleanD3D(void); // Direct3D를 닫고 메모리를 해제합니다 

// WindowProc 함수 프로토타입 
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);


// 모든 Windows 프로그램의 진입점 
int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	HWND hWnd;
	WNDCLASSEX wc;

	ZeroMemory(&wc, sizeof(WNDCLASSEX));

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hInstance;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.lpszClassName = L"WindowClass";

	RegisterClassEx(&wc);

	RECT wr = { 0, 0, 800, 600 };
	AdjustWindowRect(&wr, WS_OVERLAPPEDWINDOW, FALSE);

	hWnd = CreateWindowEx(NULL,
		L"WindowClass",
		L"첫 번째 Direct3D 프로그램",
		WS_OVERLAPPEDWINDOW,
		300,
		300,
		wr.right - wr.left,
		wr.bottom - wr.top,
		NULL,
		NULL,
		hInstance,
		NULL);

	ShowWindow(hWnd, nCmdShow);

	// Direct3D 설정 및 초기화 
	InitD3D(hWnd);

	// 메인 루프로 들어갑니다.

	MSG 메시지;

	while (TRUE)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);

			if (msg.message == WM_QUIT)
				break;
		}

		RenderFrame();
	}

	// DirectX 및 COM 정리 
	CleanD3D();

	return msg.wParam;
}

// 이것은 프로그램의 주요 메시지 처리기입니다 
LRESULT 콜백 WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_DESTROY:
		{
			PostQuitMessage(0);
			return 0;
		} break;
	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}

// 이 함수는 Direct3D를 초기화하고 사용할 수 있도록 준비합니다. 
void InitD3D(HWND hWnd)
{
	// 스왑 체인에 대한 정보를 보관할 구조체를 만듭니다. 
	DXGI_SWAP_CHAIN_DESC scd;

	// 사용할 구조체를 지웁니다. 
	ZeroMemory(&scd, sizeof(DXGI_SWAP_CHAIN_DESC));

	// 스왑 체인 설명을 채웁니다. struct 
	scd.BufferCount = 1; // 백 버퍼 하나 
	scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM; // 32비트 색상 사용 
	scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT; // 스왑 체인 사용 방법 
	scd.OutputWindow = hWnd; // 사용할 창 
	scd.SampleDesc.Count = 1; // 멀티 샘플 수 
	scd.SampleDesc.Quality = 0; // 멀티샘플 품질 수준 
	scd.Windowed = TRUE; // 창 모드/전체 화면 모드 

	// scd 구조체에 있는 정보를 사용하여 장치, 장치 컨텍스트, 스왑 체인을 생성합니다. 
	D3D11CreateDeviceAndSwapChain(NULL,
		D3D_DRIVER_TYPE_HARDWARE,
		NULL,
		NULL, NULL
		,
		NULL,
		D3D11_SDK_VERSION,
		&scd,
		&swapchain,
		&dev,
		NULL,
		&devcon);


	// 백 버퍼의 주소를 가져옵니다. 
	ID3D11Texture2D* pBackBuffer;
	swapchain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);

	// 백 버퍼 주소를 사용하여 렌더 타겟을 생성합니다. 
	dev->CreateRenderTargetView(pBackBuffer, NULL, &backbuffer);
	pBackBuffer->Release();

	// 렌더 타겟을 백 버퍼로 설정합니다. 
	devcon->OMSetRenderTargets(1, &backbuffer, NULL); // 뷰포트     D3D11_VIEWPORT를 


	설정합니다.viewport;     ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));     viewport.TopLeftX = 0;     viewport.TopLeftY = 0;     viewport.Width = 800;     viewport.Height = 600;     devcon->RSSetViewports(1, &viewport);
} // 이 함수는 단일 프레임을 렌더링하는 데 사용됩니다. void RenderFrame(void) {     // 백 버퍼를 진한 파란색으로 지웁니다.     devcon->ClearRenderTargetView(backbuffer, D3DXCOLOR(0.0f, 0.2f, 0.4f, 1.0f));     // 여기서 백 버퍼에서 3D 렌더링을 수행합니다.     // 백 버퍼와 프런트 버퍼를 전환합니다     . swapchain->Present(0, 0); }

// 이 함수는 Direct3D와 COM을 정리합니다. 
void CleanD3D(void)
{
	// 모든 기존 COM 객체를 닫고 해제합니다. 
	swapchain->Release();
	backbuffer->Release();
	dev->Release();
	devcon->Release();
}
