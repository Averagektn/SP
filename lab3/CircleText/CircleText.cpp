#include "pch.h"

__declspec(dllexport) BOOL WINAPI MessageCircle(HWND hWnd) 
{
	MessageBox(hWnd, L"Hello, World!", L"Message", MB_OK);
	return true;
}