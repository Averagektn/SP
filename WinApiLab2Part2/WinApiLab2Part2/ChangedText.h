#pragma once
#include <Windows.h>

#define PI 3.1416

class ChangedText
{
public:
	static void  DrawRotatedText(HWND hWnd, std::string text, int ElipsWidth, int ElipsHeight, LOGFONT font)
	{
		HDC hdc = GetDC(hWnd);
		HFONT hFont = CreateFontIndirect(&font);
		XFORM tempXFORM;
		GetWorldTransform(hdc, &tempXFORM);
		SelectObject(hdc, hFont);
		SetGraphicsMode(hdc, GM_ADVANCED);
		int centerX = 500;
		int centerY = 300;
		Ellipse(hdc, centerX - ElipsWidth, centerY - ElipsHeight, centerX + ElipsWidth, centerY + ElipsHeight);

		int currentTextLength = text.length();
		double startAngle = -PI / 2;
		double angle = 0;
		double deltaDegree;
		int arcSize = 2 * PI * sqrt((ElipsWidth * ElipsWidth + ElipsHeight * ElipsHeight) / 8);
		int pieceOfArc = arcSize / (2 * font.lfWidth);

		int numberOfSymbols;
		int count = 0;
		bool neccessaryToJump = CalculateJump(ElipsWidth, ElipsHeight, text.length(), &numberOfSymbols, font);
		deltaDegree = 2 * PI / numberOfSymbols;
		int size = MultiByteToWideChar(CP_UTF8, 0, text.c_str(), -1, NULL, 0);
		wchar_t* buffer = new wchar_t[size];
		MultiByteToWideChar(CP_UTF8, 0, text.c_str(), -1, buffer, size);
		for (int i = 0; i < text.length(); i++)
		{
			double angle = startAngle + count * deltaDegree;
			int x = static_cast<int>(centerX + ElipsWidth * cos(angle));
			int y = static_cast<int>(centerY + ElipsHeight * sin(angle));

			XFORM xForm;
			xForm.eM11 = static_cast<FLOAT>(cos(angle - startAngle));
			xForm.eM12 = static_cast<FLOAT>(sin(angle - startAngle));
			xForm.eM21 = static_cast<FLOAT>(-sin(angle - startAngle));
			xForm.eM22 = static_cast<FLOAT>(cos(angle - startAngle));
			xForm.eDx = x;
			xForm.eDy = y;

			SetWorldTransform(hdc, &xForm);
			TextOut(hdc, 0, 0, &buffer[i], 1);
			angle += deltaDegree;
			count++;
			if (count == numberOfSymbols && neccessaryToJump)
			{
				ElipsHeight *= 0.7;
				ElipsWidth *= 0.7;
				neccessaryToJump = CalculateJump(ElipsWidth, ElipsHeight, currentTextLength - count, &numberOfSymbols, font);
				deltaDegree = 2 * PI / numberOfSymbols;
				currentTextLength -= count;
				SetWorldTransform(hdc, &tempXFORM);

				Ellipse(hdc, centerX - ElipsWidth, centerY - ElipsHeight, centerX + ElipsWidth, centerY + ElipsHeight);


				count = 0;

			}
		}

	}

	static bool CalculateJump(int ElipsHeight, int ElipsWidth, int WordsNumber, int* numberOfSymbols, LOGFONT font)
	{
		int arcSize = 2 * PI * sqrt((ElipsWidth * ElipsWidth + ElipsHeight * ElipsHeight) / 8);
		int pieceOfArc = arcSize / (2 * font.lfWidth);

		int count = 0;
		bool neccessaryToJump;
		if (WordsNumber > pieceOfArc)
		{
			*numberOfSymbols = pieceOfArc;

			return true;
		}
		else
		{
			if (2 * WordsNumber < pieceOfArc)
			{
				*numberOfSymbols = WordsNumber * 2;
			}
			else
				*numberOfSymbols = WordsNumber;

			neccessaryToJump = false;
			return false;
		}
	}
};
