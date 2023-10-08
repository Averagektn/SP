#pragma once

#include <windows.h>
#include <vector>

// Used to draw text in a table
class TableDrawer
{
public:
	TableDrawer(int rows, int columns, int width, const LPCWSTR text[]);

	void draw();
	void draw(HFONT hFont);
	void draw(LOGFONT font);
	void setHDC(HDC hdc);

private:
	const int TEXT_FORMAT_DRAW = DT_LEFT | DT_WORDBREAK | DT_WORD_ELLIPSIS;
	const int TEXT_FORMAT_COUNT = DT_LEFT | DT_WORDBREAK | DT_CALCRECT | DT_WORD_ELLIPSIS;
	const int LEFT_OFFSET = 3;
	const int LETTER_SIZE = 20 + LEFT_OFFSET;

	HDC hdc;
	std::vector<RECT> cell;
	std::vector<LPCWSTR> text;
	int rows;
	int columns;
	int wndWidth;
	int tableHeight;

	int getCellInd(int row, int column);
	int getColWidth();
	int getRowHeight(int row);
	void setRowHeight(int row, int rowHeight);
	void drawCell(int row, int column);
	void drawRow(int row, int rowHeight);
	void drawBorders();
	void createCells();
};
