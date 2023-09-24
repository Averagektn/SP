#pragma once

namespace TextFormatter 
{
	const wchar_t* ELLIPTICAL_TEXT = L"Тут могла бы быть ваша реклама";
	const int COORD_X = 400;
	const int COORD_Y = 350;
	const int RADIUS_V = 200;
	const int RADIUS_H = 250;
	const double PI = 3.14;

	void drawEllipticalText(HDC hdc, const wchar_t* text, int centerX, int centerY, int vRadius, int hRadius)
	{
		XFORM xForm;
		int textLength = wcslen(text);
		double angleStep = 2 * PI / textLength;

		SetGraphicsMode(hdc, GM_ADVANCED);

		for (int i = 0; i < textLength; i++)
		{
			int x = static_cast<int>(centerX + hRadius * cos(i * angleStep - PI / 2));
			int y = static_cast<int>(centerY + vRadius * sin(i * angleStep - PI / 2));
			double rotationAngle = -(i * angleStep);

			xForm.eM11 = cos(rotationAngle);
			xForm.eM12 = -sin(rotationAngle);
			xForm.eM21 = sin(rotationAngle);
			xForm.eM22 = cos(rotationAngle);
			xForm.eDx = x;
			xForm.eDy = y;

			SetWorldTransform(hdc, &xForm);

			TextOut(hdc, 0, 0, &text[i], 1);

			ModifyWorldTransform(hdc, NULL, MWT_IDENTITY);
		}
	}
}
