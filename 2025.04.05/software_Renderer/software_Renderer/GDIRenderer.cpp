#include "GDIRenderer.h"
#include "SoundSystem.h"

float camposx = 0;
float camposy = 0;
float camposz = 0;

extern int windowsizeL;
extern int windowsizeH;

GDIRenderer::GDIRenderer(HWND* hwnd)
{
	phwnd = hwnd;

	memdc = CreateCompatibleDC(GetDC(*phwnd));
	GetClientRect(*phwnd, &rect);

	memBitmap = CreateCompatibleBitmap(memdc, rect.right, rect.bottom);
	oldBitmap = (HBITMAP)SelectObject(memdc, memBitmap);
	FillRect(memdc, &rect, (HBRUSH)GetStockObject(BLACK_BRUSH));

	input = InputSystem::GetInstance();

	backgroundBrush = CreateSolidBrush(RGB(0, 0, 0));

	cam.LookAt(Point(0, 0, 5), Point(0, 0, 0), Point(0, 1, 0));
	int aspect = 65;
	cam.CreatePerspectiveFrustum(PI(aspect), 1, 1, 1000);
	cam.SetViewPort(windowsizeH, windowsizeL);

	coner.transform.SetScale(1, 1, 1);
	//coner.transform.SetScale(0.1, 0.1, 0.1);
	coner.transform.SetPosition(0,0,0);
	coner.transform.SetRotation(0,0,0);
}

GDIRenderer::~GDIRenderer()
{

}

void GDIRenderer::Initialize()
{

}

float posx = 0;
float posy = 0;
float posz = 0;

float rot1 = 0;
float rot2 = 0;
float rot3 = 0;

bool convertcam = true;

void GDIRenderer::Render()
{
	input->Update(0);

	//coner.transform.SetPosition(camposx, camposy, camposz);
	//coner.transform.SetRotation(0, 0, 0);
	
	coner.transform.SetPosition(5, 5, 0);
	coner.transform.SetRotation(camposx, camposy, camposz);

	Point camtarget(camposx, camposy,camposz);
	
	cam.Update();
	coner.Update(cam.GetView(), cam.GetProj(), cam.GetViewPort());

	Point middledot;
	Point dot[8];

	middledot = coner.UpdateVertex(-1);
	dot[0] = coner.UpdateVertex(0);
	dot[1] = coner.UpdateVertex(1);
	dot[2] = coner.UpdateVertex(2);
	dot[3] = coner.UpdateVertex(3);
	dot[4] = coner.UpdateVertex(4);
	dot[5] = coner.UpdateVertex(5);
	dot[6] = coner.UpdateVertex(6);
	dot[7] = coner.UpdateVertex(7);

	for (int i = 0; i < 36; i += 3)
	{
		DrawLine(dot[coner.ReturnIndex(i)], dot[coner.ReturnIndex(i + 1)] , RGB(255, 255, 255));
		DrawLine(dot[coner.ReturnIndex(i + 1)], dot[coner.ReturnIndex(i + 2)], RGB(255, 255, 255));
		DrawLine(dot[coner.ReturnIndex(i + 2)], dot[coner.ReturnIndex(i)], RGB(255, 255, 255));

		DrawLine(middledot.x - 5, middledot.y + 5, middledot.x + 5, middledot.y - 5, RGB(255, 255, 255));
		DrawLine(middledot.x + 5, middledot.y + 5, middledot.x - 5, middledot.y - 5, RGB(255, 255, 255));
	}


	Matrix mat = coner.finalTransform;         
	Matrix viewmat = cam.GetView() * cam.GetProj()/* * cam.GetViewPort()*/ ;
	camtarget = viewmat.PointmultiplyMatrix(camtarget);
	
	int num = 15;
	DrawTextM(0, num * 1, L" camtarget.x: %.2f, camtarget.y: %.2f ///  middledot.x: % .2f, middledot.y : % .2f", camtarget.x, camtarget.y, middledot.x, middledot.y);
	DrawTextM(0, num * 0, L" X: %2f, Y: %2f Z: %2f", camposx, camposy, camposz);
	
	DrawTextM(0, num * 2, L"최종행렬");
	DrawTextM(0, num * 3, L" %.2f\t %.2f\t %.2f\t %.2f", mat.a1, mat.a2, mat.a3, mat.a4);
	DrawTextM(0, num * 4, L" %.2f\t %.2f\t %.2f\t %.2f", mat.b1, mat.b2, mat.b3, mat.b4);
	DrawTextM(0, num * 5, L" %.2f\t %.2f\t %.2f\t %.2f", mat.c1, mat.c2, mat.c3, mat.c4);
	DrawTextM(0, num * 6, L" %.2f\t %.2f\t %.2f\t %.2f", mat.d1, mat.d2, mat.d3, mat.d4);
	DrawTextM(0, num * 7, L"%.2f", mat.GetDet());


	DrawTextM(200, num * 2, L"뷰 * 뷰포트 행렬");
	DrawTextM(200, num * 3, L" %.2f\t %.2f\t %.2f\t %.2f", viewmat.a1, viewmat.a2, viewmat.a3, viewmat.a4);
	DrawTextM(200, num * 4, L" %.2f\t %.2f\t %.2f\t %.2f", viewmat.b1, viewmat.b2, viewmat.b3, viewmat.b4);
	DrawTextM(200, num * 5, L" %.2f\t %.2f\t %.2f\t %.2f", viewmat.c1, viewmat.c2, viewmat.c3, viewmat.c4);
	DrawTextM(200, num * 6, L" %.2f\t %.2f\t %.2f\t %.2f", viewmat.d1, viewmat.d2, viewmat.d3, viewmat.d4);
	DrawTextM(200, num * 7, L"%.2f", viewmat.GetDet());

	int xp = 0;
	int yp = 0;
	
	input->GetMousePosition(xp, yp);

	DrawTextM(500, num * 8, L"%d", yp);
	DrawTextM(500, num * 9, L"%d", xp);
}

void GDIRenderer::beginRender()
{
	PatBlt(memdc, 0, 0, rect.right, rect.bottom, BLACKNESS);
}

void GDIRenderer::EndRender()
{
	BitBlt(GetDC(*phwnd), 0, 0, rect.right, rect.bottom, memdc, 0, 0, SRCCOPY);

}

void GDIRenderer::Finalize()
{
	DeleteObject(backgroundBrush);

	SelectObject(memdc, oldBitmap);
	DeleteObject(memBitmap);

	ReleaseDC(*phwnd, memdc);
}

void GDIRenderer::DrawLine(float sposx, float sposy, float eposx, float eposy, _In_ COLORREF color)
{
	hMyPen = CreatePen(PS_SOLID, 2, color);
	hOldPen = (HPEN)SelectObject(memdc, hMyPen);

	MoveToEx(memdc, sposx, sposy, NULL);
	LineTo(memdc, eposx, eposy);

	SelectObject(memdc, hOldPen);
	DeleteObject(hMyPen);
}

void GDIRenderer::DrawLine(Point spos, Point epos, _In_ COLORREF color)
{
	hMyPen = CreatePen(PS_SOLID, 2, color);
	hOldPen = (HPEN)SelectObject(memdc, hMyPen);

	MoveToEx(memdc, spos.x, spos.y, NULL);
	LineTo(memdc, epos.x, epos.y);

	SelectObject(memdc, hOldPen);
	DeleteObject(hMyPen);
}

void GDIRenderer::DrawDot(float posx, float posy, _In_ COLORREF color)
{
	hMyPen = CreatePen(PS_SOLID, 2, color);
	hOldPen = (HPEN)SelectObject(memdc, hMyPen);

	MoveToEx(memdc, posx, posy, NULL);
	LineTo(memdc, posx, posy);

	SelectObject(memdc, hOldPen);
	DeleteObject(hMyPen);
}

void GDIRenderer::DrawTextM(float xpos, float ypos, const wchar_t* format, ...)
{
	// 배경 모드를 TRANSPARENT로 설정
	SetBkMode(memdc, TRANSPARENT);

	// 배경 브러시를 선택
	HBRUSH oldBrush = (HBRUSH)SelectObject(memdc, backgroundBrush);
	SetTextColor(memdc, RGB(255, 255, 255));

	//////가변인자를 적용하여 문자열을 구성하는 부분//////
	wchar_t buffer[1024]; // 문자열을 저장할 버퍼
	va_list args;
	va_start(args, format);

	// 서식 문자열과 가변 인자를 사용하여 문자열 생성
	vswprintf(buffer, sizeof(buffer) / sizeof(buffer[0]), format, args);

	va_end(args);
	///////////////////////////////////////////////////

	// TextOut 함수를 사용하여 문자열을 화면에 출력
	TextOut(memdc, xpos, ypos, buffer, lstrlen(buffer));

	// 이전 브러시로 선택
	SelectObject(memdc, oldBrush);

	// 배경 모드를 다시 OPAQUE로 설정 (기본값)
	SetBkMode(memdc, OPAQUE);
}
