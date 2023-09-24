#pragma once

namespace ProjConst 
{
	const int WND_INI_WIDTH = 800;
	const int WND_INI_HEIGHT = 600;
	
	const wchar_t* WND_MAIN_CLASS_NAME = L"MainWnd";
	const wchar_t* WND_MAIN_CAPTION = L"Tables";

	const COLORREF WND_MAIN_INI_COLOR = RGB(255, 255, 255);

	const int TEXT_FORMAT_DRAW = DT_LEFT | DT_WORDBREAK | DT_WORD_ELLIPSIS;
	const int TEXT_FORMAT_COUNT = DT_LEFT | DT_WORDBREAK | DT_CALCRECT | DT_WORD_ELLIPSIS;

	const int ROWS = 3;
	const int COLUMNS = 3;

	const LPCWSTR TEXT[]
	{
		L"Dude, did you think something was gonna happen here? Ohhhh, no, you stink of **** even from here.", L" Close  ", L"it",
		L", close ", L"the video,", L" **** you. ,",
		L"Friend of a cool friend, ", L"you ****** up *****", L"aaaaaaah ****, aaaaah.",
	};
}
