#include "TableDrawer.h"

// после рисования строки обновить y координату всех прямоугольников в последующих строках
TableDrawer::TableDrawer(int rows, int columns, int width, const LPCWSTR text[])
{
	this->rows = rows;
	this->columns = columns;
	wndWidth = width;
	hdc = NULL;
	for (int i = 0; i < rows * columns; i++)
	{
		this->text.push_back(text[i]);
	}
}

void TableDrawer::draw()
{
	createCells();
	//for (int row = 0; row < rows; row++) 
	//{
	//	int height = TableDrawer::getRowHeight(row);
	//	TableDrawer::drawRow(row, height);
	//}
	int height = TableDrawer::getRowHeight(0);
	TableDrawer::drawRow(0, height);
}

void TableDrawer::drawRow(int row, int rowHeight)
{
	setRowHeight(row, rowHeight);

	for (int column = 0; column < columns; column++) 
	{
		TableDrawer::drawCell(row, column);
	}
}

void TableDrawer::drawCell(int row, int column)
{
	int ind = getCellInd(row, column);
	DrawText(hdc, text[ind], -1, &cell[ind], TEXT_FORMAT_DRAW);
}

void TableDrawer::createCells()
{
	for (int i = 0; i < rows * columns; i++)
	{
		int width = getColWidth();
		RECT rect { i % rows * width, 0,  i % rows * width + width, 0 };
		cell.push_back(rect);
	}
}

void TableDrawer::setRowHeight(int row, int rowHeight)
{
	for (int column = 0; column < columns; column++)
	{
		int ind = getCellInd(row, column);
		cell[ind].bottom = rowHeight;
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

void TableDrawer::setWidth(int width)
{
	wndWidth = width;
}
