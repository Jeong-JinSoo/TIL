전체 화면으로 전환

게임을 전체 화면으로 만드는 것은 쉽지만, 프로그램의 몇 가지 세부 사항을 변경하고 몇 줄의 코드를 추가해야 한다.

이 수업에서는 두 가지를 다룬다. 첫째, 화면 해상도를 글로벌화하는 방법과 이를 수행하는 이유를 살펴본다. 둘째, 창을 전체
화면모드로 전환하고 다시 원래 상태로 되돌리는 메커니즘을 다룬다.

화면 크기 설정
	DirectX 경험과 게임 프로그래밍을 통해 화면 크기를 알아야 하는 많은 함수와 구조체를 접하게 될 것이다. 이는 나중에
	해상도를 변경하기로 결정할 때, 특히 런타임 중에 변경하기로 결정할 때 번거로울 수 있다. 지금은 프로그램 전체에서 화
	면 크기를 표준화 하는 간단한 방법을 다룬다.
	
	먼저, 우리는 프로그램 맨 위의 두 개의 지시문을 추가해야 한다. 이는 화면 너비와 화면 높이를 나타낸다.

// 화면 해상도 정의 
#define SCREEN_WIDTH 800 
#define SCREEN_HEIGHT 600

	다음 단계는 프로그램을 통해 창의 너비와 높이를 지정하는 것이다. 지금까지 튜토리얼에서는 두개만 있었지만, 잠시 후에
	또 다른 것을 보게 될것이다. 

hWnd = CreateWindowEx(NULL,
      L"WindowClass",
      L"Direct3D 프로그램",
      WS_OVERLAPPEDWINDOW,
      300, 300,
      SCREEN_WIDTH, SCREEN_HEIGHT, // 창을 새 해상도로 설정 <-- 추가된것
      NULL,
      NULL,
      hInstance,
      NULL);

----------------------------------------------

viewport.TopLeftX = 0;
viewport.TopLeftY = 0;
viewport.Width = SCREEN_WIDTH;
viewport.Height = SCREEN_HEIGHT;

이후 수업에서는 런타임 중에 화면 크기를 변경항 후 게임 전체에서 화면 크기를 유지하는 방법에 대해 다룬다.
대부분의 PC에는 특정 해상도가 있는데, 그 중 가장 일반적인 해상도를 다음 표에서 볼 수 있다.

[해상도]        [픽셀]          	[와이드스크린]
800 x 600	    480, 000	    아니요
1024 x 768	    786, 432	    아니요
1152 x 864	    995, 328	    아니요
1280 x 1024	    1, 310, 720	    아니요
1600 x 1200	    1, 920, 000	    아니요
1440 x 900	    1, 296, 000	    예
1680 x 1050	    1, 764, 000	    예
1920 x 1080	    2, 073, 600	    예
1920 x 1200	    2, 304, 000	    예

전체 화면 모드로 변경
    거의 모든 주요 게임이 전체화면 모드로 플레이 되지만, 많은 게임에는 전체 화면과 창 모드 사이를 전환 할 수 있는 기능
    이 포함되어 있다. 기본적으로 전체화면을 원하지만, 사용자가 둘 사이를 쉽게 전환 할 수 있기를 바란다. 이는 항상
    Alt-Enter 키를 사용하여 수행된다.

    전체 화면으로 업그레이트 할 때는 몇가지 작업을 해야한다.

    1. 배경이 없도록 창을 수정한다.
    2. 백버퍼를 특정 크기로 설정한다.
    3. CleanD3D() 함수를 수정하여 닫을 때 전체화면을 끈다.

-----------------

    1. 창을 배경이 없도록 수정한다.
        창의 배경을 제거하려면 배경색을 설정하는데 사용된 WINDOWCLASSEX 구조체의 멤버 중 하나에 주석을 달기만 하면 된
        다. 이렇게 하면 배경색이 그대로 유지되므로 게임이 시작되기 전 1~2초 동안 창으로 표시되지 않는다.(게임을 전문적
        으로 보이게 하는데 중요....?)
        // wc.hbr배경 = (HBRUSH)COLOR_WINDOW;

    2. 백 버퍼를 특정 크기로 설정한다.
        다음으로, DirectX에 새로운 화면 해상도를 알려야 한다. 이는 지난 수업에서 만든 scd 구조체에 몇 가지 변경을 가함
        으로써 이루어진다.
	void initD3D(HWND hWnd)
    {
    	DXGI_SWAP_CHAIN_DESC scd; // 다양한 스왑 체인 정보를 보관하는 구조체 생성 
    
    	ZeroMemory(&scd, sizeof(DXGI_SWAP_CHAIN_DESC)); // 사용을 위해 구조체 지우기 
    
    	scd.BufferCount = 1; // 백 버퍼 하나 
    	scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM; // 32비트 색상 사용 
    	scd.BufferDesc.Width = SCREEN_WIDTH; // 백 버퍼 너비 설정          <-- 추가
    	scd.BufferDesc.Height = SCREEN_HEIGHT; // 백 버퍼 높이 설정        <-- 추가
    	scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT; // 스왑 체인 사용 방법 
    	scd.OutputWindow = hWnd; // 사용할 창 
    	scd.SampleDesc.Count = 1; // 멀티 샘플 수 
    	scd.SampleDesc.Quality = 0; // 멀티 샘플 품질 수준 
    	scd.Windowed = TRUE; // 창 모드/전체 화면 모드 
    
    	// ...

    3. Alt-Enter를 사용하면 DirectX가 자동으로 전환되도록 설정한다.
        이 단계는 매우 간단하다. 우리가 해야 할 일은 scd 구조체에 플래그를 추가하는 것이다. 나머지는 우리를 위해 처리
        된다. 이 플래그를 DXGI_SWAP_CHAIN_DEC의 Flags 멤버에 넣을 수 있다.

	void initD3D(HWND hWnd)
	{
		DXGI_SWAP_CHAIN_DESC scd; // 다양한 스왑 체인 정보를 보관하는 구조체 생성 

		ZeroMemory(&scd, sizeof(DXGI_SWAP_CHAIN_DESC)); // 사용을 위해 구조체 지우기 

		scd.BufferCount = 1; // 백 버퍼 하나 
		scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM; // 32비트 색상 사용 
		scd.BufferDesc.Width = SCREEN_WIDTH; // 백 버퍼 너비 설정 
		scd.BufferDesc.Height = SCREEN_HEIGHT; // 백 버퍼 높이 설정 
		scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT; // 스왑 체인 사용 방법 
		scd.OutputWindow = hWnd; // 사용할 창 
		scd.SampleDesc.Count = 1; // 멀티 샘플 수 
		scd.SampleDesc.Quality = 0; // 멀티 샘플 품질 수준 
		scd.Windowed = TRUE; // 창 모드/전체 화면 모드 
		scd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH; // 전체 화면 전환 허용        <-- 추가

		// ...
    
    4. CleanD3D()함수를 수정하여 닫을 때 전체 화면을 끈다.
        Direct3D는 실제로 전체 화면 모드에서 닫을 수 없다. 이는 백그라운드에서 발생하는 특정 스레딩 문제 때문이다. 올
        바르게 닫으려면 창 모드에 있는지 확인해야 한다. 이를 위해 SetFullScreenState() 함수를 사용 할 수 있다. 새로
        운 CleanD3D() 함수는 다음과 같다.

	// 이 함수는 Direct3D와 COM을 정리합니다. 
	void CleanD3D(void)
	{
		swapchain->SetFullscreenState(FALSE, NULL); // 창 모드로 전환합니다

		// 모든 기존 COM 객체를 닫고 해제합니다. 
			swapchain->Release();
		backbuffer->Release();
		dev->Release();
		devcon->Release();
	}

    함수의 첫 번째 매개변수는 전환하려는 상태이다. FALSE는 창 모드를 나타내고 TRUE는 전체 화면 모드를 나타낸다.

    두 번째 매개변수는 사용할 비디오 어뎁터를 선택 할 수 있는 기능이다. 이는 여러 모니터를 사용하는 특정 사례에 유용
    하다. 그러나 거의 모든 게임에서는 이것을 NULL로 설정하면 올바른 어댑터가 선택된다.

    다음은 Main.cpp 전문이다.

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

// 화면 해상도를 정의합니다 
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

// 전역 선언 
IDXGISwapChain* swapchain; // 스왑 체인 인터페이스에 대한 포인터 
ID3D11Device* dev; // Direct3D 장치 인터페이스에 대한 포인터 
ID3D11DeviceContext* devcon; // Direct3D 장치 컨텍스트 ID3D11RenderTargetView *backbuffer에 대한 포인터 
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
	// wc.hbrBackground = (HBRUSH)COLOR_WINDOW; // 더 이상 필요 없음
	wc.lpszClassName = L"WindowClass";

	RegisterClassEx(&wc);

	RECT wr = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
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

	// 메인 루프로 이동: 

	MSG msg;

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


// 이것은 프로그램의 기본 메시지 처리기입니다 
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
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
	scd.BufferDesc.Width = SCREEN_WIDTH; // 백 버퍼 너비를 설정합니다. 
	scd.BufferDesc.Height = SCREEN_HEIGHT; // 백 버퍼 높이를 설정합니다.
	scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT; // 스왑 체인을 사용하는 방법 
	scd.OutputWindow = hWnd; // 사용할 창 
	scd.SampleDesc.Count = 4; // 멀티샘플 수 
	scd.Windowed = TRUE; // 창 모드/전체 화면 모드 
	scd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH; // 전체 화면 전환 허용

	// scd 구조체의 정보를 사용하여 장치, 장치 컨텍스트 및 스왑 체인 생성 
	D3D11CreateDeviceAndSwapChain(NULL,
		D3D_DRIVER_TYPE_HARDWARE,
		NULL,
		NULL,
		NULL,
		NULL,
		D3D11_SDK_VERSION,
		&scd,
		&swapchain,
		&dev,
		NULL,
		&devcon);


	// 백 버퍼의 주소를 가져옵니다 
	ID3D11Texture2D* pBackBuffer;
	swapchain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);

	// 백 버퍼 주소를 사용하여 렌더 타겟을 생성합니다 
	dev->CreateRenderTargetView(pBackBuffer, NULL, &backbuffer);
	pBackBuffer->Release();

	// 렌더 타겟을 백 버퍼로 설정합니다 
	devcon->OMSetRenderTargets(1, &backbuffer, NULL);


	// 뷰포트를 설정합니다 
	D3D11_VIEWPORT viewport;
	ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));

	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.Width = SCREEN_WIDTH;
	viewport.Height = SCREEN_HEIGHT;

	devcon->RSSetViewports(1, &viewport);
}


// 이 함수는 단일 프레임을 렌더링하는 데 사용됩니다. 
void RenderFrame(void)
{
	// 백 버퍼를 진한 파란색으로 지웁니다. 
	devcon->ClearRenderTargetView(backbuffer, D3DXCOLOR(0.0f, 0.2f, 0.4f, 1.0f));

	// 여기서 백 버퍼에서 3D 렌더링을 수행합니다 

	// 백 버퍼와 프런트 버퍼를 전환합니다. 
	swapchain->Present(0, 0);
}


// 이 함수는 Direct3D와 COM을 정리합니다. 
void CleanD3D(void)
{
	swapchain->SetFullscreenState(FALSE, NULL); // 창 모드로 전환합니다

	// 모든 기존 COM 객체를 닫고 해제합니다. 
		swapchain->Release();
	backbuffer->Release();
	dev->Release();
	devcon->Release();
}