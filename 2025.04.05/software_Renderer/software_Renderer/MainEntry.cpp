#include <Windows.h>
#include <d2d1.h>

#include "GDIRenderer.h"
#include "testdirectinput.h"
#include "SoundSystem.h"

GDIRenderer* gdiRenderer;
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

int windowsizeL = 680;
int windowsizeH = 680;

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR    lpCmdLine, _In_ int       nCmdShow)
{
	///(���� �� �����츦) ���
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;					///������ ���ν���
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 3);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = L"WindowClass";
	wcex.hIconSm = NULL;

	RegisterClassExW(&wcex);

	///(�� �����츦) ����
	HWND hWnd = CreateWindowW(L"WindowClass", L"Program Title", WS_OVERLAPPEDWINDOW,
		200, 200, 200 + windowsizeL, 200 + windowsizeH, nullptr, nullptr, hInstance, nullptr);

	//������ �ڵ��� ���� �߿� (�̰� �������� �׸��� �׷�)
	if (!hWnd)
	{
		return FALSE;
	}

	gdiRenderer = new GDIRenderer(&hWnd);
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	InputSystem* cinput = InputSystem::GetInstance();
	cinput->Initialize(hInstance, hWnd, 680, 680);


	///���ѷ���(�ȿ� �޽��� ������ ���� �������� ���Ե�)

	///�޼��� ����
	MSG msg;
	while (true)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)break;
			DispatchMessage(&msg);
		}
		else
		{
			gdiRenderer->beginRender();
			gdiRenderer->Render();
			gdiRenderer->EndRender();
		}
	}

	return 0;
}

extern float camposx;
extern float camposy;
extern float camposz;

extern bool convertcam;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;

	switch (message)
	{
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		case WM_PAINT:
			hdc = BeginPaint(hWnd, &ps);
			EndPaint(hWnd, &ps);
			break;

		case WM_KEYDOWN:
			if (wParam == VK_UP)
			{
				camposy += 1;
			}
			if (wParam == VK_DOWN)
			{
				camposy -= 1;
			}
			if (wParam == VK_LEFT)
			{
				camposx += 1;
			}
			if (wParam == VK_RIGHT)
			{
				camposx -= 1;
			}
			if (wParam == VK_END)
			{
				camposz -= 1;
			}
			if (wParam == VK_HOME)
			{
				camposz += 1;
			}
			if (wParam == VK_SPACE)
			{
				convertcam = ((convertcam == false) ? true : false);
			}
				break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}