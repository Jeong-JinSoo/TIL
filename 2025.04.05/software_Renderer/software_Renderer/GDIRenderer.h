#pragma once
#include <windows.h>
#include <wchar.h>
#include "Camera.h"
#include "GraphicsClass.h"
#include "testdirectinput.h"

class GDIRenderer
{
public:
	GDIRenderer(HWND* hwnd);
	~GDIRenderer();
public:
	void Initialize();
	void Render();
	void beginRender();
	void EndRender();
	void Finalize();

private:
	void DrawLine(float sposx, float sposy, float eposx, float eposy, _In_ COLORREF color);
	void DrawLine(Point spos, Point epos, _In_ COLORREF color);
	void DrawDot(float posx, float posy, _In_ COLORREF color);
	void DrawTextM(float xpos, float ypos, const wchar_t* text, ...);

private:
	HWND* phwnd;

	HDC memdc;
	RECT rect;

	HPEN hMyPen;
	HPEN hOldPen;
	HBRUSH backgroundBrush;

	HBITMAP memBitmap;
	HBITMAP oldBitmap;

	Camera cam;
	Coner coner;

	InputSystem* input;
};

