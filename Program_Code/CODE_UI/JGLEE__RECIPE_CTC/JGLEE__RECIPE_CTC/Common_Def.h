#pragma once


// ...
#define  iSTEP__SIZE					2
#define  iSTEP__SIZE_CMP				4


#define  RCP_ITEM_MAXLINE_II			200 
#define  RCP_ITEM_SCR_MAXH				26
#define  RCP_ITEM_SCR_MAXW				5


// ...
#define  COLOR____BLACK					RGB(0, 0, 0)
#define  COLOR____WHITE					RGB(255, 255, 255)

#define  COLOR____CIAN					RGB(24, 218, 245)
#define  COLOR____LIGHT_GRAY			RGB(234, 239, 242) 
#define  COLOR____DARK_GRAY_BLUE		RGB(117, 129, 138)
#define  COLOR____MID_GRAY				RGB(223, 225, 225)

#define  COLOR____DARK_BLUE				RGB(0, 66, 123)
#define  COLOR____NAVY_BLUE				RGB(40, 108, 149)
#define  COLOR____LIGHT_NAVY_BLUE		RGB(95, 164, 226)

#define  COLOR____GOLD					RGB(255, 201, 14)
#define  COLOR____ORANGE				RGB(255, 172, 40)


// ...
#define  MARGIN_LEFT					50
#define  MARGIN_TOP						10
#define  MARGIN_RIGHT					20
#define  MARGIN_BOTTOM					30


#define  STATIC_CLASS _T("Static") 
#define  BUTTON_CLASS _T("Button") 


#define  BACK_COLOR						Gdiplus::Color.Honeydew		// Gdiplus::Color.Honeydew // RGB(70, 95, 108)
#define  TXT_COLOR						RGB(0,0,0)					// (255, 255, 255)
#define  BACK_POP_COLOR					Gdiplus::Color.LightBlue	// Gdiplus::Color.Honeydew // RGB(70, 95, 108)

#define  GRID_COUNT_HALF				5
#define  GRID_RULER_HALF				3
#define  POINT_RADIUS_HALF				6
#define  POINT_TXT_WIDTH_HALF			20


// ...
static COLORREF Get_RGBColor(Gdiplus::Color color)
{
	return RGB(color.GetR(), color.GetG(), color.GetB());
}


enum
{
	ERR_NO_FILE_NAME = -4,
	ERR_NO_FILE = -3,
	ERR_IN_FILE_NO_DATA = -2,
	ERR_CANNOT_OPEN_FILE = -1,
	ERR_NO_MSG = 0,

	FILE_OK	
};

enum
{
	INPUT__FILE_MODE = 0,
	INPUT__DIGIT_MODE
};

enum
{
	INDEX_EQATION__EQUAL,
	INDEX_EQATION__DIFFERENT,
	INDEX_EQATION__CHANGE
};
