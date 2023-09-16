#include <windows.h>
#include <gdiplus.h>
#include "Constants.h"
#include "Functions.h"
#include "Variables.h"


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	Gdiplus::GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR gdiplusToken;
	Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, nullptr);

	WNDCLASSEX wcex; HWND hWnd; MSG msg;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_DBLCLKS;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = HBRUSH(CreateSolidBrush(RGB(255, 255, 255)));
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = ProjConst::PROJ_NAME;
	wcex.hIconSm = wcex.hIcon;

	RegisterClassEx(&wcex);

	hWnd = CreateWindow(ProjConst::PROJ_NAME, ProjConst::WND_CAPTION, WS_OVERLAPPEDWINDOW, 
		CW_USEDEFAULT, CW_USEDEFAULT, ProjConst::WND_DEF_WIDTH, ProjConst::WND_DEF_HEIGHT, 
		NULL, NULL, hInstance, NULL);

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	Gdiplus::GdiplusShutdown(gdiplusToken);

	return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) { 
	HDC hdc;
	PAINTSTRUCT ps;
	HKL hkl;
	switch (message)
	{
	case WM_CHAR:
		hkl = GetKeyboardLayout(NULL);
		if (ProjFuncs::isRusLayout(hkl)) {
			MessageBox(hWnd, L"ﬂ–”— »…", L"CAPTION", MB_OK);
		}
		else {
			MessageBox(hWnd, L"ﬂENGLISH", L"CAPTION", MB_OK);
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		DrawFuncs::DrawImage(hdc, ProjConst::PIC_INITIAL_X, ProjConst::PIC_INITIAL_Y);
		EndPaint(hWnd, &ps);
		break;
	case WM_LBUTTONDOWN:
		MessageBox(hWnd, L"Hello WINAPI", L"CAPTION", MB_OK);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
