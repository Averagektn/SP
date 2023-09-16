#pragma once

#include "Constants.h"
#include "Variables.h"

namespace ProjFuncs {
	wchar_t* GetCurrPicName() {
		ProjVars::currPic = (ProjVars::currPic + 1) % ProjConst::TOTAL_PICTURES;
		return (wchar_t*)ProjConst::PIC_NAMES[ProjVars::currPic];
	}

	bool isRusLayout(HKL hkl) {
		return (int)hkl == ProjConst::RUS_LAYOUT;
	}
}

namespace DrawFuncs {
	void DrawImage(HDC hdc, int x, int y) {
		Gdiplus::Graphics graphics(hdc);
		Gdiplus::Bitmap bmp(ProjFuncs::GetCurrPicName());

		graphics.DrawImage(&bmp, x, y, ProjConst::PIC_WIDTH, ProjConst::PIC_HEIGHT);
	}
}