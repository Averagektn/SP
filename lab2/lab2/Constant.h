#pragma once

namespace ProjConst 
{
	const int WND_INI_WIDTH = 800;
	const int WND_INI_HEIGHT = 600;
	const FLOAT FONT_DEFAULT_SIZE = 16;
	
	const wchar_t* WND_MAIN_CLASS_NAME = L"MainWnd";
	const wchar_t* WND_MAIN_CAPTION = L"Tables";
	const wchar_t* FONT_TYPE_FIXED = L"Fixed";
	const wchar_t* FONT_TYPE_FIXEDSYS = L"Fixedsys";
	const wchar_t* FONT_TYPE_GNU_UNIFONT = L"GNU unifont";
	const wchar_t* FONT_TYPE_PC_SCREEN_FONT = L"PC Screen Font";
	const wchar_t* FONT_TYPE_PROGGY_PROGRAMMING_FONTS = L"Proggy programming fonts";
	const wchar_t* FONT_TYPE_TERMINAL = L"TERMINAL";

	const COLORREF WND_MAIN_INI_COLOR = RGB(255, 255, 255);

	const int TEXT_FORMAT_DRAW = DT_LEFT | DT_WORDBREAK | DT_WORD_ELLIPSIS;
	const int TEXT_FORMAT_COUNT = DT_LEFT | DT_WORDBREAK | DT_CALCRECT | DT_WORD_ELLIPSIS;

	const int ROWS = 3;
	const int COLUMNS = 4;

	const LPCWSTR TEXT[]
	{
		L"Testing multiline text. It shold jump to the next line soon. Just wait for it.",
		L"Test",
		L"Phrase",
		L"Font",
		L"Changing",
		L"See, it changes, multiple lines appear",
		L"Empty cell in this line",
		L"Height and width are changing!",
		L"A",
		L"B",
		L"C",
		L"D"
	};
}
