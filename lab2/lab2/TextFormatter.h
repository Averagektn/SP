#pragma once

namespace TextFormatter 
{
	const wchar_t* ELLIPTICAL_TEXT = L"Dima ne sosat'";
	const int COORD_X = 800;
	const int COORD_Y = 800;
	const int RADIUS_V = 200;
	const int RADIUS_H = 300;
	const double PI = 3.14;

	// Counts max length of text that can be written in given perimeter
	int getTextMaxLength(HDC hdc, int perimeter, const wchar_t* text, size_t textLength, int ind)
	{
		SIZE letterSize;
		int i;

		for (i = ind; perimeter > 0 && i < textLength; i++)
		{
			GetTextExtentPoint(hdc, &text[i], 1, &letterSize);
			perimeter -= letterSize.cx;
		}

		return i - ind;
	}

	// Counts ellipse perimeter as S = 2 * PI sqrt((a^2 + b^2) / 8)
	int getEllipsePerimeter(int a, int b)
	{
		return 2 * PI * sqrt((a * a + b * b) / 8);
	}

	// Draws formatted text. Elliptic text
	// hdc - device context
	// text - drawn text
	// centerX, centerY - central point of ellipse
	// vRadius, hRadius - reiuses of ellipse
	void drawEllipticalText(HDC hdc, const wchar_t* text, POINT center, int vDiameter, int hDiameter, int letterHeight, int ind = 0)
	{
		XFORM xForm;
		size_t textLength = wcslen(text);
		int perimeter = getEllipsePerimeter(vDiameter, hDiameter);
		int maxLetters = getTextMaxLength(hdc, perimeter, text, textLength, ind);
		double angleStep = 2 * PI / (maxLetters);

		SetGraphicsMode(hdc, GM_ADVANCED);

		for (int i = ind; i < maxLetters + ind && i < textLength; i++)
		{
			int x = static_cast<int>(center.x + hDiameter * cos(i * angleStep - PI / 2));
			int y = static_cast<int>(center.y + vDiameter * sin(i * angleStep - PI / 2));
			double rotationAngle = -(i * angleStep);

			xForm.eM11 = (FLOAT)cos(rotationAngle);
			xForm.eM12 = (FLOAT) -sin(rotationAngle);
			xForm.eM21 = (FLOAT)sin(rotationAngle);
			xForm.eM22 = (FLOAT)cos(rotationAngle);
			xForm.eDx = (FLOAT)x;
			xForm.eDy = (FLOAT)y;

			SetWorldTransform(hdc, &xForm);

			TextOut(hdc, 0, 0, &text[i], 1);

			ModifyWorldTransform(hdc, NULL, MWT_IDENTITY);
		}

		if (ind < textLength) 
		{
			drawEllipticalText(hdc, text, center, vDiameter - letterHeight, hDiameter - letterHeight, letterHeight, ind + maxLetters);
		}
	}
}
