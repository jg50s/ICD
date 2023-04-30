#include "stdafx.h"
#include "Part_Config.h"


// ...
#define CFG_STATE__DISABLE             1
#define CFG_STATE__BLINK               2


CPart__Cfg_Common::CPart__Cfg_Common()
{
	sDir_IMG = "C:\\Module_Linker\\SUI_Link_Res\\RES_UI\\IMG_RES\\Config_Button\\";

	iState = CFG_STATE__DISABLE;
	bBlink_High = FALSE;
}
CPart__Cfg_Common::~CPart__Cfg_Common()
{

}

void CPart__Cfg_Common::Init_Common(CWnd* p_parent_wnd, CDC* p_dc_back)
{
	Set__Owner_Draw();

	Link_Resource(p_parent_wnd, p_dc_back);
}

void CPart__Cfg_Common::Set_Blink()
{
	iState = CFG_STATE__BLINK;
	bBlink_High = FALSE;
}
void CPart__Cfg_Common::Set_Disable()
{
	iState = CFG_STATE__DISABLE;
}

int  CPart__Cfg_Common::Is_Disable()
{
	if(iState == CFG_STATE__DISABLE)		return 1;

	return -1;
}

void CPart__Cfg_Common::Draw_State()
{
	if(iState == CFG_STATE__DISABLE)
	{
		Draw__Disable_State();
		return;
	}

	// Blink ...
	{
		if(bBlink_High)			Draw__Up_State();
		else					Draw__Active_State();

		bBlink_High = !bBlink_High;
	}
	return;
}


// ...
CPart__Cfg_Refresh::CPart__Cfg_Refresh()
{

}
CPart__Cfg_Refresh::~CPart__Cfg_Refresh()
{

}

void CPart__Cfg_Refresh::Init_Resource(CWnd* p_parent_wnd, CDC* p_dc_back)
{
	Init_Common(p_parent_wnd, p_dc_back);

	// ...
	CString path_bmp;			

	path_bmp.Format("%s%s", sDir_IMG,"REFRESH-SEL.bmp");
	Link_Bitmap__Active_State(path_bmp);

	path_bmp.Format("%s%s", sDir_IMG,"REFRESH-IDLE.bmp");
	Link_Bitmap__Up_State(path_bmp);
}

// ...
CPart__Cfg_Search::CPart__Cfg_Search()
{

}
CPart__Cfg_Search::~CPart__Cfg_Search()
{

}

void CPart__Cfg_Search::Init_Resource(CWnd* p_parent_wnd, CDC* p_dc_back)
{
	Init_Common(p_parent_wnd, p_dc_back);

	// ...
	CString path_bmp;			

	path_bmp.Format("%s%s", sDir_IMG,"BUTTON-CFG_SEARCH-UP.bmp");
	Link_Bitmap__Up_State(path_bmp);

	path_bmp.Format("%s%s", sDir_IMG,"BUTTON-CFG_SEARCH-DOWN.bmp");
	Link_Bitmap__Down_State(path_bmp);

	path_bmp.Format("%s%s", sDir_IMG,"BUTTON-CFG_SEARCH-ACTIVE.bmp");
	Link_Bitmap__Active_State(path_bmp);

	path_bmp.Format("%s%s", sDir_IMG,"BUTTON-CFG_SEARCH-DISABLE.bmp");
	Link_Bitmap__Disable_State(path_bmp);
}

// ...
CPart__Cfg_Undo::CPart__Cfg_Undo()
{

}
CPart__Cfg_Undo::~CPart__Cfg_Undo()
{

}

void CPart__Cfg_Undo::Init_Resource(CWnd* p_parent_wnd, CDC* p_dc_back)
{
	Init_Common(p_parent_wnd, p_dc_back);

	// ...
	CString path_bmp;			

	path_bmp.Format("%s%s", sDir_IMG,"BUTTON-CFG_UNDO-UP.bmp");
	Link_Bitmap__Up_State(path_bmp);

	path_bmp.Format("%s%s", sDir_IMG,"BUTTON-CFG_UNDO-DOWN.bmp");
	Link_Bitmap__Down_State(path_bmp);

	path_bmp.Format("%s%s", sDir_IMG,"BUTTON-CFG_UNDO-ACTIVE.bmp");
	Link_Bitmap__Active_State(path_bmp);

	path_bmp.Format("%s%s", sDir_IMG,"BUTTON-CFG_UNDO-DISABLE.bmp");
	Link_Bitmap__Disable_State(path_bmp);
}

// ...
CPart__Cfg_Save::CPart__Cfg_Save()
{

}
CPart__Cfg_Save::~CPart__Cfg_Save()
{

}

void CPart__Cfg_Save::Init_Resource(CWnd* p_parent_wnd, CDC* p_dc_back)
{
	Init_Common(p_parent_wnd, p_dc_back);

	// ...
	CString path_bmp;			

	path_bmp.Format("%s%s", sDir_IMG,"BUTTON-CFG_SAVE-UP.bmp");
	Link_Bitmap__Up_State(path_bmp);

	path_bmp.Format("%s%s", sDir_IMG,"BUTTON-CFG_SAVE-DOWN.bmp");
	Link_Bitmap__Down_State(path_bmp);

	path_bmp.Format("%s%s", sDir_IMG,"BUTTON-CFG_SAVE-ACTIVE.bmp");
	Link_Bitmap__Active_State(path_bmp);

	path_bmp.Format("%s%s", sDir_IMG,"BUTTON-CFG_SAVE-DISABLE.bmp");
	Link_Bitmap__Disable_State(path_bmp);
}
