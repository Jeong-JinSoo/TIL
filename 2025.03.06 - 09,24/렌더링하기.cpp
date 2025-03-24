������ ������

Direct3D �ʱ�ȭ�� ������ ���� �������� ������ �����̴�. ������ ��ü�� �ſ� ������ �ణ�� �غ� �۾��� �ʿ��ϴ�. �� ��
�������� �� �������� ����ؼ� ������ �ϱ� ���� ��� ���� �����Ѵ�.

���õ� ������ �����ϴ�.�ؾ� �� ���� �� ���� �ִ�.ù°, GPU�� ���� �̹����� ���� �޸��� ��� �κ��� �˷��� �Ѵ�.(��
��� ����۸� ���Ѵ�.) ��°, GPU�� �� ������ ��� �κп� �׷��� �ϴ��� �˷��� �Ѵ�.

�� �۾��� ������ �������� ���� �� �� �ִ�.

���� Ÿ�� ����

������ �� ��ġ���� �����غ���. �翬�� �����������, �� �������� Direct3D�� �� �������� ������ �װ��� ���� ���Ѵ�. ��
���ۿ� �ٷ� ������ �ϰ� ���� ���� ���� �ִ�. ���� ��� ���� ������ �� ǥ�鿡 ������ �� ���� �ش� ���� �� ��ó�� ��
���� �� ���� �ִ�.�� ����� �پ��� ȿ���� �� �� �ִ�. Portal�� ��ǥ���� �����ε�, �մ� ���п� ������ �� ���� ��Ż ��
������ ��ü����� ������ �Ѵ�.

Direct3D������ ������ �� �� ����Ÿ���� �����ؾ� �Ѵ�. �̰��� ���� �޸𸮿��� ������ �� ��ġ�� �����ϴ� ������ COM ��
ü�̴�. ��κ��� ��� �̰��� �� ���� �̴�.

�츮�� �̸� �����ϴ� ����� ������ ����.

ID3D11RenderTargetView* backbuffer; // ���� ����

// �� �Լ��� Direct3D�� �ʱ�ȭ�ϰ� ����� �� �ֵ��� �غ��մϴ� 
void InitD3D(HWND hWnd)
{
	// Direct3D �ʱ�ȭ 
	// ... 

	// �� ������ �ּҸ� �����ɴϴ� 
	ID3D11Texture2D* pBackBuffer;
	swapchain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);

	// �� ���� �ּҸ� ����Ͽ� ���� Ÿ���� �����մϴ� 
	dev->CreateRenderTargetView(pBackBuffer, NULL, &backbuffer);
	pBackBuffer->Release();

	// ���� Ÿ���� �� ���۷� �����մϴ� 
	devcon->OMSetRenderTargets(1, &backbuffer, NULL);
}

���⼭�� �������� ����ȴ�.
ù°, �� ������ �ּҸ� �����Ѵ�.
��°, �ش� �ּҸ� ����Ͽ� ���� Ÿ���� ��Ÿ���� COM ��ü�� �����.
��°, �ش� ��ü�� Ȱ�� ���� Ÿ������ �����Ѵ�.

���⿡ �߰��� ���ο� �ڵ���� ���� ������ �˾ƺ���.

ID3D11RenderTargetView* backbuffer;
	�� ������ ���� Ÿ�ٿ� ���� ��� ������ �����ϴ� ��ü�� ���� �������̴�. �츮�� �� ���ۿ� ������ �� ���̹Ƿ� ��
	������ 'backbuffer'��� �θ���.

ID3D11Texture2D *pBackBuffer;
	3D ���������� �ؽ�ó�� �̹����� �ٸ� �̸��Դϴ�. ID3D11Texture2D�� �÷� �̹����� �����ϴ� ��ü�̴�. ��� COM ��
	ü�� ���������� ���� �����͸� �����ϰ� ���߿� �Լ��� ��ü�� �����Ѵ�.

swapchain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
	�̰� �����ϴ�. �� GetBuffer() �Լ��� �ϴ� ���� ����ü�ο��� �� ���۸� ã�Ƽ� pBackBuffer �ؽ�ó ��ü�� ����� ��
	�̴�.

	ù ��° �谳������ ������ �� ������ ��ȣ�̴�. �� ü�ο��� �� ���� �ϳ��� ����ϰ� ������, ����� #0�̴�. ����
	�� �Ű������� 0�� �ȴ�. 

	�� ��° �Ű������� ID3D11Texture2D COM ��ü�� �ĺ��ϴ� �����̴�. �� ������ COM ��ü���� ������ ID�� ������, �̸�
	����Ͽ� �ش� ��ü�� ���� ������ ��´�. �� ID�� �������� __uuidof �����ڸ� ����ؾ� �Ѵ�. �̰��� ��� �۵��ϴ�
	���� ���� ��Ȯ�� ���� ������ ���� �߿����� ������, �츮�� �̷��� �ϴ� ������ GetBuffer() �Լ��� � ������ ��ü��
	������ �ϴ��� �� �� �ֵ��� �ϱ� ���ؼ��̴�.

	�� ��° �Ű��������� void*�� ���� �����Ͱ� �ִ�. �� void*�� ID3D11Texture2D��ü�� ��ġ�� ä������. void*���� �ϴµ�,
	�츮�� ��û �� �� �ִ� �ٸ� ������ ��ü�� �ֱ� �����̴�.

	�� Ư�� ����� ���� ������ �ʹ� ���� �ǵ帮�� �ʴ´�. 

dev->CreateRenderTargetView(pBackBuffer, NULL, &backbuffer);
	�� �Լ��� ���� Ÿ�� ��ü�� �����Ѵ�. �츮�� ���α׷� �� ���� �� ��ü�� ���� �����͸� �����ߴ�.

	ù ��° �Ű������� �ؽ�ó�� ���� �������̴�. �츮 ���α׷��� ��� 'pBackBuffer'���� �Ѵ�.

	�� ��° �Ű������� ���� Ÿ���� �����ϴ� ����ü�̴�. �� ���ۿ� ���ؼ��� �̰��� ä�� �ʿ䰡 ����. �׳� NULL�� ����
	�Ѵ�.

	�� ��° �Ű������� ��ü �������� �ּ��̴�. �������� �̸��� 'backbuffer' �����Ƿ� '&backbuffer'�� ����Ѵ�.

pBackBuffer->Release();
	Release() �Լ��� ��� �޸𸮸� �����ϰ� COM��ü���� �����ϴ� ��� �����带 �ݴ´�.
	pBackbuffer ��ü�� ���� �۾��� �������Ƿ� Release()�� �����Ѵ�. �̷��� �ϸ� ����۰� �ı����� �ʰ�, ������ �ϴ�
	�� ����� �ؽ�ó ��ü�� ������.

devcon->OMSetRenderTargets(1, &backbuffer, NULL);
	�� ������ �Լ��� ������ ���� Ÿ���� �����Ѵ�. �� ��Ȯ�� ���ϸ�, ���� ���� Ÿ���� �����Ѵ�.

	ù ��° �Ű������� ������ ���� Ÿ���� �� �̴�. �̴� �Ϲ������� 1������ �� ���� ��찡 �ִ�.

	�� ��° �Ű������� ���� Ÿ�� �� ��ü ����� ����Ű�� �������̴�. �츮�� �ϳ��� ������ �����Ƿ�, �װ��� ���� �츮��
	���� Ÿ�� ��ü(&backbuffer)�� �ּ��� ���̴�.

	�� ��° �Ű������� ����̸�, �̰��� ���߿� �ٷ�� ������ NULL�� �д�.

	�� ������ ���� �����ϴ�. ���� ���� �Ͼ���� ���� �� �� ���� �ݺ��ؼ� ���� ���� ����. Direct3D ���α׷��ֿ��� ��
	���� ���ǰ� �����Ǳ� �����̴�.

����Ʈ ����

	�� �ڵ� ������ ���� �ڵ忡 ���ϸ� ���� �����ϴ�. ����Ʈ�� �ȼ���ǥ�� ����ȭ�� ��ǥ�� ��ȯ�ϴ� ����̴�. ���� ���̾�
	�׷��� �� ���� �������� �����ش�.

	http://www.directxtutorial.com/Lessons/11/B1-D3DGettingStarted/3/2.png

	���ʿ��� �ȼ� ��ǥ�� ���� �� �𼭸����� 0,0���� �����Ͽ� �� ���� �� �ȼ��� �����Ѵ�. �����ʿ��� ����ȭ�� ��ǥ�� ��
	������ ũ�⿡ ���� ���� -1,-1���� �����Ͽ� 1,1�� �����Ѵ�. Normalized ��� �ܾ�� ���� 1�� �� �� ���� �����ȴٴ�
	���� �ǹ��Ѵ�.

	-1, -1, 1, 1�� ������ ������ �������� ����Ʈ�� ���� �����ȴ�. ����Ʈ�� -1, -1, 1, 1�� �ȼ� ��ǥ���� ��� �ִ���
	������ �� �ִ� ����ü�̴�.

	����Ʈ�� �����ϴ� �ڵ�� ������ ����.

	void InitD3D(HWND hWnd)
	{
		// Direct3D �ʱ�ȭ 
		// ... 

		// ���� ��� ���� 
		// ... 

		// ����Ʈ ���� 
		D3D11_VIEWPORT viewport;
		ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));

		viewport.TopLeftX = 0;
		viewport.TopLeftY = 0;
		viewport.Width = 800;
		viewport.Height = 600;

		devcon->RSSetViewports(1, &viewport);
	}

	���⼭ ������ �ʿ��� ������ ���� ������ ���̴�.

	RSSetViewPorts()�� ����Ʈ ����ü�� Ȱ��ȭ �ϴ� �Լ��̴�. ù��° �Ű������� ��� ���� ����Ʈ�� ���̰�, �ι�° �Ű�
	������ ��� ���� ����Ʈ�� ���̰� �� ��° �Ű������� ����Ʈ ����ü�� ���� ������ ����� �ּ��̴�.

	���� ����Ʈ�� ����ϴ� ���� Ư�� ��� ��Ȳ���� ��������, ���⼭�� �ٷ��� �ʴ´�. ������ 1�� '&viewport'�� �Ű�
	������ �� �´´�.

������ ������

	�������� ���� �������� �������ϴ� �Լ��� �����. �������� ������ �ſ� �����Ͽ� �Ķ��� ������θ� �����ȴ�. ���� ��
	�Ѵٸ� ������ ���� �� �� �ִ�. �� �Լ��� �ڵ�� ������ ����.

	// �̰��� ���� �������� �������ϴ� �� ���Ǵ� �Լ�
	void RenderFrame(void)
	{
		// �� ���۸� ���� �Ķ������� �����.
		devcon->ClearRenderTargetView(backbuffer, D3DXCOLOR(0.0f, 0.2f, 0.4f, 1.0f));

		// ���⼭ �� ���ۿ��� 3D �������� �����Ѵ�

		// �� ���ۿ� ����Ʈ ���۸� ��ȯ�Ѵ�.
		swapchain->Present(0, 0);
	}

	devcon->ClearRenderTargetView()
	�̰��� ���� Ÿ�� ���۸� Ư�� �������� ä���. �츮�� ���, �� ���۸� ä���. �ſ� �����ϴ�. �Ű������� �ΰ� �ִ�.
	
	ù ��°�� ���� Ÿ�� ��ü�� �ּ��̴�. �츮�� ���⿡ 'backbuffer'�� �־���.

	�� ��° �Ű������� ����۸� ä����� �ϴ� �����̴�. �̸� ���� D3DXCOLOR��� ������ ����ü�� ����Ѵ�. �װ��� ����
	�� �Ű������� ������ �����ϴ� �� ���ȴ�. ó�� ������ ������, ���, �Ķ��� ���̰� �� ��°�� ���� ���̴�.

	swapchain->Present()
	�������� Present() �Լ��� ȣ���Ѵ�. �� �Լ��� �� ���ۿ� �׷��� ��� ���� ������ ��Ÿ���� ���̴�. �� �Լ��� ������
	�⺻������ ����ü�ο��� "swap"�� �����Ͽ� �� ���۰� ����Ʈ ���۰� �ǵ��� �ϴ� ���̴�.

	�� �Ű������� ��� 0���� �����Ǿ� ������, �� ��Ʃ���󿡼� ���� ������ �ʴ´�.

Obligatory Cleanup
	���� �������� �츮�� �츮�� ���� �� COM ��ü�� �����Ͽ� Direct3D�� �����ߴ�. ��κ��� COM��ü���� �� Release()��
	���� ������, �ִٸ� �츮�� �Ϸ�Ǿ��� �� �װ��� ȣ���ؾ� �Ѵ�.
	���� Ÿ�� ��ü�� ���ܴ� �ƴϴ�.

	// �� �Լ��� Direct3D�� COM�� �����Ѵ�.
	void CleanD3D()
	{
		// ��� ���� COM ��ü�� �ݰ� �����Ѵ�. 
		swapchain->Release();
		backbuffer->Release();
		dev->Release();
		devcon->Release();
	}

��� COM ��ü�� �������ǵ��� �ϴ� ������ ���̴� ���� ����. �� ���� �߰� �� ���� �ϳ��ϳ� ����ϱ� ����� �� �� �ִ�.

The Finished Program
	���� Direct3D�� �����ϰ� â�� ������ �� ������ �������� �� �� �ִ�.
	�Ʒ� �� �ڵ带 �߰��� ��ü �ڵ尡 �ִ�. 

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

// ���� ���� 
IDXGISwapChain* swapchain; // ���� ü�� �������̽��� ���� ������ 
ID3D11Device* dev; // Direct3D ��ġ �������̽��� ���� ������ 
ID3D11DeviceContext* devcon; // Direct3D ��ġ ���ؽ�Ʈ�� ���� ������ 
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
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.lpszClassName = L"WindowClass";

	RegisterClassEx(&wc);

	RECT wr = { 0, 0, 800, 600 };
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

	// ���� ������ ���ϴ�.

	MSG �޽���;

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

// �̰��� ���α׷��� �ֿ� �޽��� ó�����Դϴ� 
LRESULT �ݹ� WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
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
	scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT; // ���� ü�� ��� ��� 
	scd.OutputWindow = hWnd; // ����� â 
	scd.SampleDesc.Count = 1; // ��Ƽ ���� �� 
	scd.SampleDesc.Quality = 0; // ��Ƽ���� ǰ�� ���� 
	scd.Windowed = TRUE; // â ���/��ü ȭ�� ��� 

	// scd ����ü�� �ִ� ������ ����Ͽ� ��ġ, ��ġ ���ؽ�Ʈ, ���� ü���� �����մϴ�. 
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


	// �� ������ �ּҸ� �����ɴϴ�. 
	ID3D11Texture2D* pBackBuffer;
	swapchain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);

	// �� ���� �ּҸ� ����Ͽ� ���� Ÿ���� �����մϴ�. 
	dev->CreateRenderTargetView(pBackBuffer, NULL, &backbuffer);
	pBackBuffer->Release();

	// ���� Ÿ���� �� ���۷� �����մϴ�. 
	devcon->OMSetRenderTargets(1, &backbuffer, NULL); // ����Ʈ     D3D11_VIEWPORT�� 


	�����մϴ�.viewport;     ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));     viewport.TopLeftX = 0;     viewport.TopLeftY = 0;     viewport.Width = 800;     viewport.Height = 600;     devcon->RSSetViewports(1, &viewport);
} // �� �Լ��� ���� �������� �������ϴ� �� ���˴ϴ�. void RenderFrame(void) {     // �� ���۸� ���� �Ķ������� ����ϴ�.     devcon->ClearRenderTargetView(backbuffer, D3DXCOLOR(0.0f, 0.2f, 0.4f, 1.0f));     // ���⼭ �� ���ۿ��� 3D �������� �����մϴ�.     // �� ���ۿ� ����Ʈ ���۸� ��ȯ�մϴ�     . swapchain->Present(0, 0); }

// �� �Լ��� Direct3D�� COM�� �����մϴ�. 
void CleanD3D(void)
{
	// ��� ���� COM ��ü�� �ݰ� �����մϴ�. 
	swapchain->Release();
	backbuffer->Release();
	dev->Release();
	devcon->Release();
}
