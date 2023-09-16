#pragma once

namespace ProjFuncs {
	// Defines which picture to paint
	wchar_t* GetCurrPicName() {
		ProjVars::currPic %= ProjConst::TOTAL_PICTURES;
		if (ProjVars::currPic < 0) {
			ProjVars::currPic += ProjConst::TOTAL_PICTURES;
		}
		return (wchar_t*)ProjConst::PIC_NAMES[ProjVars::currPic];
	}

	// Keyboard layout info
	bool isRusLayout(HKL hkl) {
		return (int)hkl == ProjConst::RUS_LAYOUT;
	}

	// New rect to be redrawn
	RECT GetRect() {
		return  { ProjVars::x - ProjConst::SPEED - 1, ProjVars::y - ProjConst::SPEED - 1,
			ProjVars::x + ProjConst::PIC_WIDTH + ProjConst::SPEED + 1,
			ProjVars::y + ProjConst::PIC_HEIGHT + ProjConst::SPEED + 1 };
	}

	// Mouse X coordinate
	int GetXParam(LPARAM lParam) {
		int res = lParam & 0xFFFF;
		res -= ProjConst::PIC_WIDTH / 2;
		return res;
	}

	// Mouse Y coordinate
	int GetYParam(LPARAM lParam) {
		int res = lParam >> 16;
		res -= ProjConst::PIC_HEIGHT / 2;
		return res;
	}
}

namespace DrawFuncs {
	void DrawImage(HDC hdc, int x, int y) {
		Gdiplus::Graphics graphics(hdc);
		Gdiplus::Bitmap bmp(ProjFuncs::GetCurrPicName());

		graphics.DrawImage(&bmp, x, y, ProjConst::PIC_WIDTH, ProjConst::PIC_HEIGHT);
	}

	void DoubleBufferedPaint(HWND hWnd, HDC hdc) {
		HDC memDC;
		HBITMAP memBMP;
		HGDIOBJ hOld;
		memDC = CreateCompatibleDC(hdc);
		memBMP = CreateCompatibleBitmap(hdc, ProjConst::WND_DEF_WIDTH, ProjConst::WND_DEF_HEIGHT);

		hOld = SelectObject(memDC, memBMP);
		DrawImage(memDC, ProjVars::x, ProjVars::y);
		BitBlt(hdc, 0, 0, ProjConst::WND_DEF_WIDTH, ProjConst::WND_DEF_HEIGHT, memDC, 0, 0, SRCCOPY);
		SelectObject(memDC, hOld);

		DeleteObject(memBMP);
		DeleteDC(memDC);
		ReleaseDC(hWnd, hdc);
	}

	void ProcessRusLayout(WPARAM wParam) {
		//W
		if (wParam == ProjConst::VK_CAP_RUS_W || wParam == ProjConst::VK_RUS_W) {
			//
			if (ProjVars::y < ProjConst::BORDER_BOTTOM) {
				ProjVars::y += ProjConst::SPEED;
			}
		}
		//D
		else if (wParam == ProjConst::VK_CAP_RUS_D || wParam == ProjConst::VK_RUS_D) {
			//
			if (ProjVars::x > ProjConst::BORDER_LEFT) {
				ProjVars::x -= ProjConst::SPEED;
			}
		}
		//A
		else if (wParam == ProjConst::VK_CAP_RUS_A || wParam == ProjConst::VK_RUS_A) {
			//
			if (ProjVars::x < ProjConst::BORDER_RIGHT) {
				ProjVars::x += ProjConst::SPEED;
			}
		}
		//S
		else if (wParam == ProjConst::VK_CAP_RUS_S || wParam == ProjConst::VK_RUS_S) {
			//
			if (ProjVars::y > ProjConst::BORDER_TOP) {
				ProjVars::y -= ProjConst::SPEED;
			}
		}
	}

	void ProcessEngLayout(WPARAM wParam) {
		switch (wParam) {
		case 'w':
		case 'W':
			if (ProjVars::y > ProjConst::BORDER_TOP) {
				ProjVars::y -= ProjConst::SPEED;
			}
			break;
		case 's':
		case 'S':
			if (ProjVars::y < ProjConst::BORDER_BOTTOM) {
				ProjVars::y += ProjConst::SPEED;
			}
			break;
		case 'a':
		case 'A':
			if (ProjVars::x > ProjConst::BORDER_LEFT) {
				ProjVars::x -= ProjConst::SPEED;
			}
			break;
		case 'd':
		case 'D':
			if (ProjVars::x < ProjConst::BORDER_RIGHT) {
				ProjVars::x += ProjConst::SPEED;
			}
			break;
		default:
			break;
		}
	}

	void ProcessHorisontalMouseScroll(WPARAM wParam) {
		if (GET_WHEEL_DELTA_WPARAM(wParam) > 0) {
			if (ProjVars::x > ProjConst::BORDER_LEFT) {
				ProjVars::x -= ProjConst::SPEED;
			}
		}
		else {
			if (ProjVars::x < ProjConst::BORDER_RIGHT) {
				ProjVars::x += ProjConst::SPEED;
			}
		}
	}

	void ProcessVerticalMouseScroll(WPARAM wParam) {
		if (GET_WHEEL_DELTA_WPARAM(wParam) > 0) {
			if (ProjVars::y > ProjConst::BORDER_TOP) {
				ProjVars::y -= ProjConst::SPEED;
			}
		}
		else {
			if (ProjVars::y < ProjConst::BORDER_BOTTOM) {
				ProjVars::y += ProjConst::SPEED;
			}
		}
	}
}
