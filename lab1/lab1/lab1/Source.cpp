#include <windows.h>
#include <gdiplus.h>
#include "Constants.h"
#include "Variables.h"
#include "Functions.h"
#include "resource.h"

// all buttons generate redraw
// double buffer doesn't work, work worse than single buffer

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	WNDCLASSEX wcex;
	HWND hWnd;
	MSG msg;
	HACCEL hAccel;
	Gdiplus::GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR gdiplusToken;

	Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_DBLCLKS;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = HBRUSH(CreateSolidBrush(RGB(0, 0, 0)));
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = ProjConst::PROJ_NAME;
	wcex.hIconSm = wcex.hIcon;

	RegisterClassEx(&wcex);

	hWnd = CreateWindow(ProjConst::PROJ_NAME, ProjConst::WND_CAPTION, WS_OVERLAPPEDWINDOW, 
		CW_USEDEFAULT, CW_USEDEFAULT, ProjConst::WND_DEF_WIDTH, ProjConst::WND_DEF_HEIGHT, 
		NULL, NULL, hInstance, NULL);

	hAccel = LoadAccelerators(hInstance, (LPCTSTR)IDR_ACCELERATOR1);
	if (hAccel == NULL) {
		MessageBox(hWnd, L"Table of acceleration is null", L"Error Message", NULL);
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(hWnd, hAccel, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	Gdiplus::GdiplusShutdown(gdiplusToken);

	return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) { 
	HDC hdc;// , memDC;
	PAINTSTRUCT ps;
	RECT rect = {ProjConst::PIC_INITIAL_X, ProjConst::PIC_INITIAL_Y, 
		ProjVars::x + ProjConst::PIC_WIDTH, ProjVars::y + ProjConst::PIC_HEIGHT};
	HKL hkl;
	//HBITMAP memBMP;
	//HGDIOBJ hOld;

	switch (message) {
	case WM_CHAR:
		hkl = GetKeyboardLayout(NULL);
		if (ProjFuncs::isRusLayout(hkl)) {
			DrawFuncs::ProcessRusLayout(wParam);
		}
		else {
			DrawFuncs::ProcessEngLayout(wParam);
		}
		rect = ProjFuncs::GetRect();
		InvalidateRect(hWnd, &rect, RDW_UPDATENOW | RDW_INVALIDATE);
		//InvalidateRect(hWnd, &rect, true);
		break;
	case WM_MOUSEWHEEL:
		if (GetAsyncKeyState(VK_LSHIFT)) {
			DrawFuncs::ProcessHorisontalMouseScroll(wParam);
		}
		else {
			DrawFuncs::ProcessVerticalMouseScroll(wParam);
		}
		rect = ProjFuncs::GetRect();
		InvalidateRect(hWnd, &rect, true);
		break;
	case WM_LBUTTONDOWN: 
		ProjVars::x = ProjFuncs::GetXParam(lParam);
		ProjVars::y = ProjFuncs::GetYParam(lParam);
		rect = {0, 0, ProjConst::WND_DEF_WIDTH, ProjConst::WND_DEF_HEIGHT};
		InvalidateRect(hWnd, &rect, true);
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case NEXT_SPRITE:
			ProjVars::currPic++;
			InvalidateRect(hWnd, &rect, true);
			break;
		case PREV_SPRITE:
			ProjVars::currPic--;
			InvalidateRect(hWnd, &rect, true);
			break;
		default:
			break;
		}
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		DrawFuncs::DoubleBufferedPaint(hWnd, hdc);
		//DrawFuncs::DrawImage(hdc, ProjVars::x, ProjVars::y);
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
