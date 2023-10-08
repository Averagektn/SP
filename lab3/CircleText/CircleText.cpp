#include "pch.h"

BOOL WINAPI Message(HWND hWnd) {
	MessageBox(hWnd, L"Hello, World!", L"Message", MB_OK);
	return true;
}