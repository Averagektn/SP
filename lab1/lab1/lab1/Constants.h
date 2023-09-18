#pragma once

namespace ProjConst {
	// NAMES
	const wchar_t* PROJ_NAME = L"Tracker";
	const wchar_t* WND_CAPTION = L"THIS SPRITE IS MOVING OMG!!!!!!!";
	const wchar_t* PIC_NAMES[] = { L"sprite_500ml.png", L"coca-cola.png", L"fanta.png", L"beer-bottle.png"};
	
	// DRAWING
	const int SPEED = 5;

	// SIZES
	const int WND_DEF_HEIGHT = 800;
	const int WND_DEF_WIDTH = 600;
	
	const int TOTAL_PICTURES = 4;
	const int PIC_WIDTH = 120;
	const int PIC_HEIGHT = 150;
	const int PIC_INITIAL_X = 50;
	const int PIC_INITIAL_Y = 50;

	const int BORDER_BOTTOM = WND_DEF_HEIGHT - PIC_HEIGHT - 40;
	const int BORDER_TOP = 0;
	const int BORDER_RIGHT = WND_DEF_WIDTH - PIC_WIDTH + 20;
	const int BORDER_LEFT = -35;
	
	// CODES
	const int RUS_LAYOUT = 68748313;
	const int ENG_LAYOUT = 67699721;
	
	const int VK_CAP_RUS_W = 1062;
	const int VK_RUS_W = 1094;

	const int VK_CAP_RUS_S = 1067;
	const int VK_RUS_S = 1099;

	const int VK_CAP_RUS_A = 1060;
	const int VK_RUS_A = 1092;

	const int VK_CAP_RUS_D = 1042;
	const int VK_RUS_D = 1074;
}
