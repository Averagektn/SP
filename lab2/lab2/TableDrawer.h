#pragma once

#include <windows.h>
#include <vector>
#include <gdiplus.h>

class TableDrawer
{
public:
	TableDrawer(int rows, int columns, int width, int height, const LPCWSTR text[]);

	void draw();
	void setHDC(HDC hdc);

private:
	const int TEXT_FORMAT_DRAW = DT_LEFT | DT_WORDBREAK | DT_WORD_ELLIPSIS;
	const int TEXT_FORMAT_COUNT = DT_LEFT | DT_WORDBREAK | DT_CALCRECT | DT_WORD_ELLIPSIS;

	HDC hdc;
	std::vector<RECT> cell;
	std::vector<LPCWSTR> text;
	int rows;
	int columns;
	int wndWidth;
	int wndHeight;

	int getCellInd(int row, int column);
	int getColWidth();
	int getRowHeight(int row);
	void setRowHeight(int row, int rowHeight);
	void drawCell(int row, int column);
	void drawRow(int row, int rowHeight);
	void drawBorders();
	void createCells();
};
