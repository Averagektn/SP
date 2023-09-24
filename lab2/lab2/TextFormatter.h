#pragma once

namespace TextFormatter 
{
	const wchar_t* ELLIPTICAL_TEXT = L"Тут могла бы быть ваша реклама";
	const int COORD_X = 400;
	const int COORD_Y = 350;
	const int RADIUS_V = 200;
	const int RADIUS_H = 250;
	const double PI = 3.14;

	// Draws formatted text. Elliptic text
	// hdc - device context
	// text - drawn text
	// centerX, centerY - central point of ellipse
	// vRadius, hRadius - reiuses of ellipse
	void drawEllipticalText(HDC hdc, const wchar_t* text, int centerX, int centerY, int vRadius, int hRadius)
	{
		XFORM xForm;
		size_t textLength = wcslen(text);
		double angleStep = 2 * PI / textLength;

		SetGraphicsMode(hdc, GM_ADVANCED);

		for (int i = 0; i < textLength; i++)
		{
			int x = static_cast<int>(centerX + hRadius * cos(i * angleStep - PI / 2));
			int y = static_cast<int>(centerY + vRadius * sin(i * angleStep - PI / 2));
			double rotationAngle = -(i * angleStep);

			xForm.eM11 = (FLOAT)cos(rotationAngle);
			xForm.eM12 = (FLOAT) - sin(rotationAngle);
			xForm.eM21 = (FLOAT)sin(rotationAngle);
			xForm.eM22 = (FLOAT)cos(rotationAngle);
			xForm.eDx = (FLOAT)x;
			xForm.eDy = (FLOAT)y;

			SetWorldTransform(hdc, &xForm);

			TextOut(hdc, 0, 0, &text[i], 1);

			ModifyWorldTransform(hdc, NULL, MWT_IDENTITY);
		}
	}
}
