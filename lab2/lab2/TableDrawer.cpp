#include "TableDrawer.h"

TableDrawer::TableDrawer(int rows, int columns, int width, int height, const LPCWSTR text[])
{
	this->rows = rows;
	this->columns = columns;
	wndWidth = width - LETTER_SIZE;
	wndHeight = height;
	hdc = NULL;
	for (int i = 0; i < rows * columns; i++)
	{
		this->text.push_back(text[i]);
	}
	tableHeight = 0;
}

void TableDrawer::draw()
{
	createCells();

	for (int row = 0; row < rows; row++) 
	{
		int height = getRowHeight(row);
		drawRow(row, height);
	}

	drawBorders();
}

void TableDrawer::createCells()
{
	for (int i = 0; i < rows * columns; i++)
	{
		int width = getColWidth();
		RECT rect{ i % rows * width, 0,  i % rows * width + width, 0 };
		cell.push_back(rect);
	}
}

void TableDrawer::drawRow(int row, int rowHeight)
{
	setRowHeight(row, rowHeight);

	for (int column = 0; column < columns; column++) 
	{
		drawCell(row, column);
	}

	for (int currCell = (row + 1) * columns; currCell < rows * columns; currCell++)
	{
		cell[currCell].top += rowHeight;
	}
}

void TableDrawer::drawCell(int row, int column)
{
	int ind = getCellInd(row, column);
	cell[ind].left += LEFT_OFFSET;
	cell[ind].right += LEFT_OFFSET;
	DrawText(hdc, text[ind], -1, &cell[ind], TEXT_FORMAT_DRAW);
}

void TableDrawer::drawBorders()
{
	HPEN pen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
	int currRow = 0;

	for (int column = 1; column < columns; column++)
	{
		MoveToEx(hdc, column * getColWidth(), 0, NULL);
		LineTo(hdc, column * getColWidth(), tableHeight);
	}

	tableHeight = 0;

	for (int row = 0; row < rows; row++)
	{
		currRow += getRowHeight(row);
		MoveToEx(hdc, 0, currRow, NULL);
		LineTo(hdc, wndWidth + LETTER_SIZE, currRow);
	}
}

void TableDrawer::setRowHeight(int row, int rowHeight)
{
	for (int column = 0; column < columns; column++)
	{
		int ind = getCellInd(row, column);
		cell[ind].bottom += rowHeight;
	}
}

int TableDrawer::getColWidth()
{
	return wndWidth / columns;
}


int TableDrawer::getRowHeight(int row)
{
	int rowHeight = 0;
	int currCellHeight = 0;

	for (int column = 0; column < columns; column++)
	{
		int ind = getCellInd(row, column);
		
		currCellHeight = DrawText(hdc, text[ind], -1, &cell[ind], TEXT_FORMAT_COUNT);

		if (currCellHeight > rowHeight)
		{
			rowHeight = currCellHeight;
		}
	}

	tableHeight += rowHeight;

	return rowHeight;
}

int TableDrawer::getCellInd(int row, int column)
{
	return row * columns + column;
}

void TableDrawer::setHDC(HDC hdc)
{
	this->hdc = hdc;
}
