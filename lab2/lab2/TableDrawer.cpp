#include "TableDrawer.h"

// rows - number of rows
// columns - number of columns
// width - table width
// text - sentences to be written
TableDrawer::TableDrawer(int rows, int columns, int width, const LPCWSTR text[])
{
	this->rows = rows;
	this->columns = columns;
	wndWidth = width - LETTER_SIZE;
	hdc = NULL;
	for (int i = 0; i < rows * columns; i++)
	{
		this->text.push_back(text[i]);
	}
	tableHeight = 0;
}

// Draws table
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

// Draws table with given font
void TableDrawer::draw(HFONT hFont)
{
	createCells();

	SelectObject(hdc, hFont);

	for (int row = 0; row < rows; row++)
	{
		int height = getRowHeight(row);
		drawRow(row, height);
	}

	drawBorders();
}

// Draws table with given font
void TableDrawer::draw(LOGFONT font)
{
	createCells();

	HFONT hFont = CreateFontIndirect(&font);
	SelectObject(hdc, hFont);

	for (int row = 0; row < rows; row++) 
	{
		int height = getRowHeight(row);
		drawRow(row, height);
	}

	drawBorders();
}

// Fills cells with coordinates
void TableDrawer::createCells()
{
	for (int i = 0; i < rows * columns; i++)
	{
		int width = getColWidth();
		RECT rect{ (i % columns) * width, 0,  (i % columns) * width + width, 0 };
		cell.push_back(rect);
	}
}

// Draws one row of the table
// row - row number to draw
// rowHeight - maximum height of cell of the row
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

// Draws selected cell
// row - selected row
// column - selected column
void TableDrawer::drawCell(int row, int column)
{
	int ind = getCellInd(row, column);
	cell[ind].left += LEFT_OFFSET;
	cell[ind].right += LEFT_OFFSET;
	DrawText(hdc, text[ind], -1, &cell[ind], TEXT_FORMAT_DRAW);
}

// Draws border of the table
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

// Sets the height of all cells in the row
void TableDrawer::setRowHeight(int row, int rowHeight)
{
	for (int column = 0; column < columns; column++)
	{
		int ind = getCellInd(row, column);
		cell[ind].bottom += rowHeight;
	}
}

// Returns column width
int TableDrawer::getColWidth()
{
	return wndWidth / columns;
}

// Returns row height
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

// Returns cell as array index
int TableDrawer::getCellInd(int row, int column)
{
	return row * columns + column;
}

// Provides device context handle to draw
void TableDrawer::setHDC(HDC hdc)
{
	this->hdc = hdc;
}
