��ü ȭ������ ��ȯ

������ ��ü ȭ������ ����� ���� ������, ���α׷��� �� ���� ���� ������ �����ϰ� �� ���� �ڵ带 �߰��ؾ� �Ѵ�.

�� ���������� �� ������ �ٷ��. ù°, ȭ�� �ػ󵵸� �۷ι�ȭ�ϴ� ����� �̸� �����ϴ� ������ ���캻��. ��°, â�� ��ü
ȭ����� ��ȯ�ϰ� �ٽ� ���� ���·� �ǵ����� ��Ŀ������ �ٷ��.

ȭ�� ũ�� ����
	DirectX ����� ���� ���α׷����� ���� ȭ�� ũ�⸦ �˾ƾ� �ϴ� ���� �Լ��� ����ü�� ���ϰ� �� ���̴�. �̴� ���߿�
	�ػ󵵸� �����ϱ�� ������ ��, Ư�� ��Ÿ�� �߿� �����ϱ�� ������ �� ���ŷο� �� �ִ�. ������ ���α׷� ��ü���� ȭ
	�� ũ�⸦ ǥ��ȭ �ϴ� ������ ����� �ٷ��.
	
	����, �츮�� ���α׷� �� ���� �� ���� ���ù��� �߰��ؾ� �Ѵ�. �̴� ȭ�� �ʺ�� ȭ�� ���̸� ��Ÿ����.

// ȭ�� �ػ� ���� 
#define SCREEN_WIDTH 800 
#define SCREEN_HEIGHT 600

	���� �ܰ�� ���α׷��� ���� â�� �ʺ�� ���̸� �����ϴ� ���̴�. ���ݱ��� Ʃ�丮�󿡼��� �ΰ��� �־�����, ��� �Ŀ�
	�� �ٸ� ���� ���� �ɰ��̴�. 

hWnd = CreateWindowEx(NULL,
      L"WindowClass",
      L"Direct3D ���α׷�",
      WS_OVERLAPPEDWINDOW,
      300, 300,
      SCREEN_WIDTH, SCREEN_HEIGHT, // â�� �� �ػ󵵷� ���� <-- �߰��Ȱ�
      NULL,
      NULL,
      hInstance,
      NULL);

----------------------------------------------

viewport.TopLeftX = 0;
viewport.TopLeftY = 0;
viewport.Width = SCREEN_WIDTH;
viewport.Height = SCREEN_HEIGHT;

���� ���������� ��Ÿ�� �߿� ȭ�� ũ�⸦ ������ �� ���� ��ü���� ȭ�� ũ�⸦ �����ϴ� ����� ���� �ٷ��.
��κ��� PC���� Ư�� �ػ󵵰� �ִµ�, �� �� ���� �Ϲ����� �ػ󵵸� ���� ǥ���� �� �� �ִ�.

[�ػ�]        [�ȼ�]          	[���̵彺ũ��]
800 x 600	    480, 000	    �ƴϿ�
1024 x 768	    786, 432	    �ƴϿ�
1152 x 864	    995, 328	    �ƴϿ�
1280 x 1024	    1, 310, 720	    �ƴϿ�
1600 x 1200	    1, 920, 000	    �ƴϿ�
1440 x 900	    1, 296, 000	    ��
1680 x 1050	    1, 764, 000	    ��
1920 x 1080	    2, 073, 600	    ��
1920 x 1200	    2, 304, 000	    ��

��ü ȭ�� ���� ����
    ���� ��� �ֿ� ������ ��üȭ�� ���� �÷��� ������, ���� ���ӿ��� ��ü ȭ��� â ��� ���̸� ��ȯ �� �� �ִ� ���
    �� ���ԵǾ� �ִ�. �⺻������ ��üȭ���� ��������, ����ڰ� �� ���̸� ���� ��ȯ �� �� �ֱ⸦ �ٶ���. �̴� �׻�
    Alt-Enter Ű�� ����Ͽ� ����ȴ�.

    ��ü ȭ������ ���׷���Ʈ �� ���� ��� �۾��� �ؾ��Ѵ�.

    1. ����� ������ â�� �����Ѵ�.
    2. ����۸� Ư�� ũ��� �����Ѵ�.
    3. CleanD3D() �Լ��� �����Ͽ� ���� �� ��üȭ���� ����.

-----------------

    1. â�� ����� ������ �����Ѵ�.
        â�� ����� �����Ϸ��� ������ �����ϴµ� ���� WINDOWCLASSEX ����ü�� ��� �� �ϳ��� �ּ��� �ޱ⸸ �ϸ� ��
        ��. �̷��� �ϸ� ������ �״�� �����ǹǷ� ������ ���۵Ǳ� �� 1~2�� ���� â���� ǥ�õ��� �ʴ´�.(������ ������
        ���� ���̰� �ϴµ� �߿�....?)
        // wc.hbr��� = (HBRUSH)COLOR_WINDOW;

    2. �� ���۸� Ư�� ũ��� �����Ѵ�.
        ��������, DirectX�� ���ο� ȭ�� �ػ󵵸� �˷��� �Ѵ�. �̴� ���� �������� ���� scd ����ü�� �� ���� ������ ����
        ���ν� �̷������.
	void initD3D(HWND hWnd)
    {
    	DXGI_SWAP_CHAIN_DESC scd; // �پ��� ���� ü�� ������ �����ϴ� ����ü ���� 
    
    	ZeroMemory(&scd, sizeof(DXGI_SWAP_CHAIN_DESC)); // ����� ���� ����ü ����� 
    
    	scd.BufferCount = 1; // �� ���� �ϳ� 
    	scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM; // 32��Ʈ ���� ��� 
    	scd.BufferDesc.Width = SCREEN_WIDTH; // �� ���� �ʺ� ����          <-- �߰�
    	scd.BufferDesc.Height = SCREEN_HEIGHT; // �� ���� ���� ����        <-- �߰�
    	scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT; // ���� ü�� ��� ��� 
    	scd.OutputWindow = hWnd; // ����� â 
    	scd.SampleDesc.Count = 1; // ��Ƽ ���� �� 
    	scd.SampleDesc.Quality = 0; // ��Ƽ ���� ǰ�� ���� 
    	scd.Windowed = TRUE; // â ���/��ü ȭ�� ��� 
    
    	// ...

    3. Alt-Enter�� ����ϸ� DirectX�� �ڵ����� ��ȯ�ǵ��� �����Ѵ�.
        �� �ܰ�� �ſ� �����ϴ�. �츮�� �ؾ� �� ���� scd ����ü�� �÷��׸� �߰��ϴ� ���̴�. �������� �츮�� ���� ó��
        �ȴ�. �� �÷��׸� DXGI_SWAP_CHAIN_DEC�� Flags ����� ���� �� �ִ�.

	void initD3D(HWND hWnd)
	{
		DXGI_SWAP_CHAIN_DESC scd; // �پ��� ���� ü�� ������ �����ϴ� ����ü ���� 

		ZeroMemory(&scd, sizeof(DXGI_SWAP_CHAIN_DESC)); // ����� ���� ����ü ����� 

		scd.BufferCount = 1; // �� ���� �ϳ� 
		scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM; // 32��Ʈ ���� ��� 
		scd.BufferDesc.Width = SCREEN_WIDTH; // �� ���� �ʺ� ���� 
		scd.BufferDesc.Height = SCREEN_HEIGHT; // �� ���� ���� ���� 
		scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT; // ���� ü�� ��� ��� 
		scd.OutputWindow = hWnd; // ����� â 
		scd.SampleDesc.Count = 1; // ��Ƽ ���� �� 
		scd.SampleDesc.Quality = 0; // ��Ƽ ���� ǰ�� ���� 
		scd.Windowed = TRUE; // â ���/��ü ȭ�� ��� 
		scd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH; // ��ü ȭ�� ��ȯ ���        <-- �߰�

		// ...
    
    4. CleanD3D()�Լ��� �����Ͽ� ���� �� ��ü ȭ���� ����.
        Direct3D�� ������ ��ü ȭ�� ��忡�� ���� �� ����. �̴� ��׶��忡�� �߻��ϴ� Ư�� ������ ���� �����̴�. ��
        �ٸ��� �������� â ��忡 �ִ��� Ȯ���ؾ� �Ѵ�. �̸� ���� SetFullScreenState() �Լ��� ��� �� �� �ִ�. ����
        �� CleanD3D() �Լ��� ������ ����.

	// �� �Լ��� Direct3D�� COM�� �����մϴ�. 
	void CleanD3D(void)
	{
		swapchain->SetFullscreenState(FALSE, NULL); // â ���� ��ȯ�մϴ�

		// ��� ���� COM ��ü�� �ݰ� �����մϴ�. 
			swapchain->Release();
		backbuffer->Release();
		dev->Release();
		devcon->Release();
	}

    �Լ��� ù ��° �Ű������� ��ȯ�Ϸ��� �����̴�. FALSE�� â ��带 ��Ÿ���� TRUE�� ��ü ȭ�� ��带 ��Ÿ����.

    �� ��° �Ű������� ����� ���� ��͸� ���� �� �� �ִ� ����̴�. �̴� ���� ����͸� ����ϴ� Ư�� ��ʿ� ����
    �ϴ�. �׷��� ���� ��� ���ӿ����� �̰��� NULL�� �����ϸ� �ùٸ� ����Ͱ� ���õȴ�.

    ������ Main.cpp �����̴�.

		// �⺻ Windows ��� ���ϰ� Direct3D ��� ������ �����մϴ�. 
#include <windows.h> 
#include <windowsx.h> 
#include <d3d11.h> 
#include <d3dx11.h> 
#include <d3dx10.h> 

// Direct3D ���̺귯�� ������ �����մϴ�. 
#pragma comment (lib, "d3d11.lib") 
#pragma comment (lib, "d3dx11.lib") 
#pragma comment (lib, "d3dx10.lib") 

// ȭ�� �ػ󵵸� �����մϴ� 
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

// ���� ���� 
IDXGISwapChain* swapchain; // ���� ü�� �������̽��� ���� ������ 
ID3D11Device* dev; // Direct3D ��ġ �������̽��� ���� ������ 
ID3D11DeviceContext* devcon; // Direct3D ��ġ ���ؽ�Ʈ ID3D11RenderTargetView *backbuffer�� ���� ������ 
ID3D11RenderTargetView* backbuffer; // �� ���ۿ� ���� ������ 

// �Լ� ������Ÿ�� 
void InitD3D(HWND hWnd); // Direct3D�� �����ϰ� �ʱ�ȭ�մϴ� 
void RenderFrame(void); // ���� �������� �������մϴ� 
void CleanD3D(void); // Direct3D�� �ݰ� �޸𸮸� �����մϴ� 

// WindowProc �Լ� ������Ÿ�� 
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);


// ��� Windows ���α׷��� ������ 
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
	// wc.hbrBackground = (HBRUSH)COLOR_WINDOW; // �� �̻� �ʿ� ����
	wc.lpszClassName = L"WindowClass";

	RegisterClassEx(&wc);

	RECT wr = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	AdjustWindowRect(&wr, WS_OVERLAPPEDWINDOW, FALSE);

	hWnd = CreateWindowEx(NULL,
		L"WindowClass",
		L"ù ��° Direct3D ���α׷�",
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

		// Direct3D ���� �� �ʱ�ȭ 
		InitD3D(hWnd);

	// ���� ������ �̵�: 

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

	// DirectX �� COM ���� 
	CleanD3D();

	return msg.wParam;
}


// �̰��� ���α׷��� �⺻ �޽��� ó�����Դϴ� 
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


// �� �Լ��� Direct3D�� �ʱ�ȭ�ϰ� ����� �� �ֵ��� �غ��մϴ�. 
void InitD3D(HWND hWnd)
{
	// ���� ü�ο� ���� ������ ������ ����ü�� ����ϴ�. 
	DXGI_SWAP_CHAIN_DESC scd;

	// ����� ����ü�� ����ϴ�. 
	ZeroMemory(&scd, sizeof(DXGI_SWAP_CHAIN_DESC));

	// ���� ü�� ������ ä��ϴ�. struct 
	scd.BufferCount = 1; // �� ���� �ϳ� 
	scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM; // 32��Ʈ ���� ��� 
	scd.BufferDesc.Width = SCREEN_WIDTH; // �� ���� �ʺ� �����մϴ�. 
	scd.BufferDesc.Height = SCREEN_HEIGHT; // �� ���� ���̸� �����մϴ�.
	scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT; // ���� ü���� ����ϴ� ��� 
	scd.OutputWindow = hWnd; // ����� â 
	scd.SampleDesc.Count = 4; // ��Ƽ���� �� 
	scd.Windowed = TRUE; // â ���/��ü ȭ�� ��� 
	scd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH; // ��ü ȭ�� ��ȯ ���

	// scd ����ü�� ������ ����Ͽ� ��ġ, ��ġ ���ؽ�Ʈ �� ���� ü�� ���� 
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


	// �� ������ �ּҸ� �����ɴϴ� 
	ID3D11Texture2D* pBackBuffer;
	swapchain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);

	// �� ���� �ּҸ� ����Ͽ� ���� Ÿ���� �����մϴ� 
	dev->CreateRenderTargetView(pBackBuffer, NULL, &backbuffer);
	pBackBuffer->Release();

	// ���� Ÿ���� �� ���۷� �����մϴ� 
	devcon->OMSetRenderTargets(1, &backbuffer, NULL);


	// ����Ʈ�� �����մϴ� 
	D3D11_VIEWPORT viewport;
	ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));

	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.Width = SCREEN_WIDTH;
	viewport.Height = SCREEN_HEIGHT;

	devcon->RSSetViewports(1, &viewport);
}


// �� �Լ��� ���� �������� �������ϴ� �� ���˴ϴ�. 
void RenderFrame(void)
{
	// �� ���۸� ���� �Ķ������� ����ϴ�. 
	devcon->ClearRenderTargetView(backbuffer, D3DXCOLOR(0.0f, 0.2f, 0.4f, 1.0f));

	// ���⼭ �� ���ۿ��� 3D �������� �����մϴ� 

	// �� ���ۿ� ����Ʈ ���۸� ��ȯ�մϴ�. 
	swapchain->Present(0, 0);
}


// �� �Լ��� Direct3D�� COM�� �����մϴ�. 
void CleanD3D(void)
{
	swapchain->SetFullscreenState(FALSE, NULL); // â ���� ��ȯ�մϴ�

	// ��� ���� COM ��ü�� �ݰ� �����մϴ�. 
		swapchain->Release();
	backbuffer->Release();
	dev->Release();
	devcon->Release();
}