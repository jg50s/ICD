#pragma once

#include "Interface_Code.h"
#include "Dlg__PARTICLE_TABLE.h"


class CObj__PARTICLE_TABLE : public GObj__Interface_Ctrl
{
private:
	CRITICAL_SECTION mCS_LOCK;

	//-------------------------------------------------------------------------------------
	int iMODULE_ID;
	POINT pSt;
	POINT pEt;

	int iREAL_MODE;
	GObj__Resource_Info *pGObj_Res;

	//-------------------------------------------------------------------------------------
	CDlg__PARTICLE_TABLE *pPage_Ctrl;
	bool bActive_Show;

	int iTimer_Delay_Count;

	//-------------------------------------------------------------------------------------
	void Draw__Area();
	//

public:
	//-------------------------------------------------------------------------------------
	CObj__PARTICLE_TABLE();
	~CObj__PARTICLE_TABLE();

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
