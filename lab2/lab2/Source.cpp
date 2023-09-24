#include <windows.h>
#include "Constant.h"
#include "TableDrawer.h"
#include "TextFormatter.h"

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) 
{
	WNDCLASSEX wcex;
	HWND hWnd;
	MSG msg;

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_DBLCLKS;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = HBRUSH(CreateSolidBrush(ProjConst::WND_MAIN_INI_COLOR));
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = ProjConst::WND_MAIN_CLASS_NAME;
	wcex.hIconSm = wcex.hIcon;

	RegisterClassEx(&wcex);

	hWnd = CreateWindow(ProjConst::WND_MAIN_CLASS_NAME, ProjConst::WND_MAIN_CAPTION, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, ProjConst::WND_INI_WIDTH, ProjConst::WND_INI_HEIGHT,
		NULL, NULL, hInstance, NULL);

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) 
{
	HDC hdc;
	PAINTSTRUCT ps;
	RECT wndRect;

	GetWindowRect(hWnd, &wndRect);
	int width = wndRect.right - wndRect.left;
	TableDrawer table(ProjConst::ROWS, ProjConst::COLUMNS, width, ProjConst::TEXT);
	
	switch (message) 
	{
	case WM_SIZE:
		InvalidateRect(hWnd, NULL, true);
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);

		table.setHDC(hdc);
		table.draw();

		TextFormatter::drawEllipticalText(hdc, TextFormatter::ELLIPTICAL_TEXT, TextFormatter::COORD_X, 
			TextFormatter::COORD_Y, TextFormatter::RADIUS_V, TextFormatter::RADIUS_H);

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
