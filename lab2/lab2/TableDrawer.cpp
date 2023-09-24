#include "TableDrawer.h"

TableDrawer::TableDrawer(int rows, int columns, int width, int height, const LPCWSTR text[])
{
	this->rows = rows;
	this->columns = columns;
	wndWidth = width;
	wndHeight = height;
	hdc = NULL;
	for (int i = 0; i < rows * columns; i++)
	{
		this->text.push_back(text[i]);
	}
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
	DrawText(hdc, text[ind], -1, &cell[ind], TEXT_FORMAT_DRAW);
}

void TableDrawer::drawBorders()
{
	Gdiplus::Graphics graphics(hdc);
	Gdiplus::Pen pen(RGB(255, 0, 0));
	graphics.DrawLine(&pen, 0, 0, 200, 200);
	//for (int column = 0; column < columns - 1; column++)
	//{
	//	graphics.DrawLine(&pen, cell[column].right, 0, cell[column].right, wndHeight);
	//}

	//for (int row = 0; row < rows; row++)
	//{
	//	graphics.DrawLine(&pen, 0, cell[row].bottom, wndWidth, cell[row].bottom);
	//}
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
