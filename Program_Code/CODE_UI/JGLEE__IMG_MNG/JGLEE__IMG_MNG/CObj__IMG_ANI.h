#pragma once

#include "interface_Header.h"
#include "CRes__IMG_CTRL.h"


class CObj__IMG_ANI : public GObj__Interface_Ctrl
{
private:
	//---------------------------------------------------------
	int iMODULE_ID;
	POINT pSt;
	POINT pEt;

	GObj__Resource_Info *pGObj_Res;
	int iREAL_MODE;

	CRes__IMG_CTRL mRes__IMG_CTRL;
	int iIMG_ID;
	int iIMG_SIZE;

	bool bActive_Display_Mode;
	bool bActive_Timer;
	int iTimer_Count;
	int iTimer_Ref_Tick;

	// ...
	void Draw__Area_Line();
	void Draw__Img(const bool draw_mode = false);
	//

public:
	CObj__IMG_ANI();
	~CObj__IMG_ANI();

	//---------------------------------------------------------
	void Get_Parameter(GObj__Parameter_Def* p_obj_para_def);
	void Set_Parameter(const int& module_id,
						const POINT& st,
						const POINT& et,
						const HWND& hwnd,
						GObj__Resource_Info *p_obj_res);

	void Show_GObj(const HWND& hwnd);
	void Hide_GObj();

	//---------------------------------------------------------
	void WM_Paint(const HWND& hwnd);
	void WM_Timer(const HWND& hwnd);

	void WM_LButtonDown(const POINT& mouse_pt,const HWND& hwnd);
	void WM_LButtonUp(const HWND& hwnd);

	void WM_RButtonDown(const POINT& mouse_pt,const HWND& hwnd);
	void WM_RButtonUp(const HWND& hwnd);

	void WM_Notify(UINT message,const WPARAM wparam,LPARAM lparam);
};
