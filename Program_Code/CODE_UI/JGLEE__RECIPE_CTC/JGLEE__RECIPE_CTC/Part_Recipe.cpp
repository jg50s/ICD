#include "stdafx.h"
#include "Part_Recipe.h"


// ...
#define RCP_STATE__DISABLE             1
#define RCP_STATE__BLINK               2


CPart__Rcp_Common::CPart__Rcp_Common()
{
	sDir_IMG = "C:\\Module_Linker\\SUI_Link_Res\\RES_UI\\IMG_RES\\Recipe_Button\\";

	iState = RCP_STATE__DISABLE;
	bBlink_High = FALSE;
}
CPart__Rcp_Common::~CPart__Rcp_Common()
{

}

void CPart__Rcp_Common::Init_Common(CWnd* p_parent_wnd, CDC* p_dc_back)
{
	Set__Owner_Draw();

	Link_Resource(p_parent_wnd, p_dc_back);
}

void CPart__Rcp_Common::Set_Blink()
{
	iState = RCP_STATE__BLINK;
	bBlink_High = FALSE;
}
void CPart__Rcp_Common::Set_Disable()
{
	iState = RCP_STATE__DISABLE;
}

int  CPart__Rcp_Common::Is_Disable()
{
	if(iState == RCP_STATE__DISABLE)		return 1;

	return -1;
}

void CPart__Rcp_Common::Draw_State()
{
	if(iState == RCP_STATE__DISABLE)
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
CPart__Rcp_New::CPart__Rcp_New()
{

}
CPart__Rcp_New::~CPart__Rcp_New()
{

}

void CPart__Rcp_New::Init_Resource(CWnd* p_parent_wnd, CDC* p_dc_back)
{
	Init_Common(p_parent_wnd, p_dc_back);

	// ...
	CString path_bmp;			

	path_bmp.Format("%s%s", sDir_IMG,"BUTTON-RCP_NEW-UP.bmp");
	Link_Bitmap__Up_State(path_bmp);

	path_bmp.Format("%s%s", sDir_IMG,"BUTTON-RCP_NEW-DOWN.bmp");
	Link_Bitmap__Down_State(path_bmp);

	path_bmp.Format("%s%s", sDir_IMG,"BUTTON-RCP_NEW-ACTIVE.bmp");
	Link_Bitmap__Active_State(path_bmp);

	path_bmp.Format("%s%s", sDir_IMG,"BUTTON-RCP_NEW-DISABLE.bmp");
	Link_Bitmap__Disable_State(path_bmp);
}

// ...
CPart__Rcp_Undo::CPart__Rcp_Undo()
{

}
CPart__Rcp_Undo::~CPart__Rcp_Undo()
{

}

void CPart__Rcp_Undo::Init_Resource(CWnd* p_parent_wnd, CDC* p_dc_back)
{
	Init_Common(p_parent_wnd, p_dc_back);

	// ...
	CString path_bmp;			

	path_bmp.Format("%s%s", sDir_IMG,"BUTTON-RCP_UNDO-UP.bmp");
	Link_Bitmap__Up_State(path_bmp);

	path_bmp.Format("%s%s", sDir_IMG,"BUTTON-RCP_UNDO-DOWN.bmp");
	Link_Bitmap__Down_State(path_bmp);

	path_bmp.Format("%s%s", sDir_IMG,"BUTTON-RCP_UNDO-ACTIVE.bmp");
	Link_Bitmap__Active_State(path_bmp);

	path_bmp.Format("%s%s", sDir_IMG,"BUTTON-RCP_UNDO-DISABLE.bmp");
	Link_Bitmap__Disable_State(path_bmp);
}

// ...
CPart__Rcp_Save::CPart__Rcp_Save()
{

}
CPart__Rcp_Save::~CPart__Rcp_Save()
{

}

void CPart__Rcp_Save::Init_Resource(CWnd* p_parent_wnd, CDC* p_dc_back)
{
	Init_Common(p_parent_wnd, p_dc_back);

	// ...
	CString path_bmp;			

	path_bmp.Format("%s%s", sDir_IMG,"BUTTON-RCP_SAVE-UP.bmp");
	Link_Bitmap__Up_State(path_bmp);

	path_bmp.Format("%s%s", sDir_IMG,"BUTTON-RCP_SAVE-DOWN.bmp");
	Link_Bitmap__Down_State(path_bmp);

	path_bmp.Format("%s%s", sDir_IMG,"BUTTON-RCP_SAVE-ACTIVE.bmp");
	Link_Bitmap__Active_State(path_bmp);

	path_bmp.Format("%s%s", sDir_IMG,"BUTTON-RCP_SAVE-DISABLE.bmp");
	Link_Bitmap__Disable_State(path_bmp);
}

// ...
CPart__Rcp_SaveAs::CPart__Rcp_SaveAs()
{

}
CPart__Rcp_SaveAs::~CPart__Rcp_SaveAs()
{

}

void CPart__Rcp_SaveAs::Init_Resource(CWnd* p_parent_wnd, CDC* p_dc_back)
{
	Init_Common(p_parent_wnd, p_dc_back);

	// ...
	CString path_bmp;			

	path_bmp.Format("%s%s", sDir_IMG,"BUTTON-RCP_SaveAs-UP.bmp");
	Link_Bitmap__Up_State(path_bmp);

	path_bmp.Format("%s%s", sDir_IMG,"BUTTON-RCP_SaveAs-DOWN.bmp");
	Link_Bitmap__Down_State(path_bmp);

	path_bmp.Format("%s%s", sDir_IMG,"BUTTON-RCP_SaveAs-ACTIVE.bmp");
	Link_Bitmap__Active_State(path_bmp);

	path_bmp.Format("%s%s", sDir_IMG,"BUTTON-RCP_SaveAs-DISABLE.bmp");
	Link_Bitmap__Disable_State(path_bmp);
}

// ...
CPart__Rcp_Delete::CPart__Rcp_Delete()
{

}
CPart__Rcp_Delete::~CPart__Rcp_Delete()
{

}

void CPart__Rcp_Delete::Init_Resource(CWnd* p_parent_wnd, CDC* p_dc_back)
{
	Init_Common(p_parent_wnd, p_dc_back);

	// ...
	CString path_bmp;			

	path_bmp.Format("%s%s", sDir_IMG,"BUTTON-RCP_DELETE-UP.bmp");
	Link_Bitmap__Up_State(path_bmp);

	path_bmp.Format("%s%s", sDir_IMG,"BUTTON-RCP_DELETE-DOWN.bmp");
	Link_Bitmap__Down_State(path_bmp);

	path_bmp.Format("%s%s", sDir_IMG,"BUTTON-RCP_DELETE-ACTIVE.bmp");
	Link_Bitmap__Active_State(path_bmp);

	path_bmp.Format("%s%s", sDir_IMG,"BUTTON-RCP_DELETE-DISABLE.bmp");
	Link_Bitmap__Disable_State(path_bmp);
}
