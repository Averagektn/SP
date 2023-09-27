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
	const int COLUMNS = 3;

	const LPCWSTR TEXT[]
	{
		L"TEst",
		L"Phrase",
		L"For",
		L"Changing",
		L"Font",
		L"Paramterers",
		L"Type",
		L"Height",
		L"Width"
	};
}
