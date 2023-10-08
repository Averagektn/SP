// CircleText_Static.cpp : Defines the functions for the static library.
//

#include "pch.h"
#include "framework.h"

// TODO: This is an example of a library function
BOOL WINAPI Message(HWND hWnd)
{
	MessageBox(hWnd, L"Test", L"Text", MB_OK);
	return true;
}
