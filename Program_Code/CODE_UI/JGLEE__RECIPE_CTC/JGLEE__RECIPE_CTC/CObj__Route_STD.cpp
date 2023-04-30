#include "StdAfx.h"
#include "CObj__Route_STD.h"


//-------------------------------------------------------------------------------------
CObj__Route_STD::CObj__Route_STD()
{
	pPage_Ctrl = NULL;
	bActive_Show = false;
}
CObj__Route_STD::~CObj__Route_STD()
{

}

//-------------------------------------------------------------------------------------
#include "CObj__Route_STD__KEY_DEF.h"


void CObj__Route_STD
::Get_Parameter(GObj__Parameter_Def* p_obj_para_def)
{
	p_obj_para_def->Register_Command(pKEY__DATA_PART_NAME);

	p_obj_para_def->Register_Command(pKEY__DATA_DIR_PRE);
	p_obj_para_def->Register_Command(pKEY__DATA_DIR_MAIN);
	p_obj_para_def->Register_Command(pKEY__DATA_DIR_POST);

	// 
	p_obj_para_def->Register_Command(pKEY__DATA_PMx_SIZE, "ListBox", "1 2 3 4 5 6", "4");

	for(int i=0; i<DEF_PMx__SIZE; i++)
	{
		CString key_name;

		key_name.Format(pKEY__CH_CFG_NAME_PM_X, i+1);
		p_obj_para_def->Register_Channel(key_name);
	}
}
void CObj__Route_STD
::Set_Parameter(const int& module_id,
			    const POINT& st,
			    const POINT& et,
			    const HWND& hwnd,
			    GObj__Resource_Info *p_obj_res)
{
	// ...
	{
		iMODULE_ID = module_id;

		pSt = st;
		pEt = et;

		iREAL_MODE = p_obj_res->pGOBJ_PARA_CTRL->Check__RealMode();
		pGObj_Res  = p_obj_res;
	}

	// ...
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	if(pPage_Ctrl == NULL)
	{
		pPage_Ctrl = new CDlg__Route_STD;
	}
	if(pPage_Ctrl != NULL)
	{
		pPage_Ctrl->pGObj_Res  = pGObj_Res;
		pPage_Ctrl->iREAL_MODE = iREAL_MODE;

		pPage_Ctrl->Set_Parameter(module_id);

		if(!bActive_Show)
		{
			bActive_Show = true;

			pPage_Ctrl->Create(IDD_DLG__ROUTE_STD, CWnd::FromHandle(hwnd));	
		}
	}	
}

void CObj__Route_STD
::Show_GObj(const HWND& hwnd)
{
	if(pPage_Ctrl != NULL)
	{
		pPage_Ctrl->Set_MoveWindow(pSt, pEt);
	}	

	Draw__Area();
}
void CObj__Route_STD
::Hide_GObj()
{
	if(pPage_Ctrl != NULL)
	{
		pPage_Ctrl->ShowWindow(SW_HIDE);
	}
}

//-------------------------------------------------------------------------------------	
void CObj__Route_STD
::WM_Paint(const HWND& hwnd)
{
	if(iREAL_MODE < 0)
	{
		if(pPage_Ctrl != NULL)
		{
			AFX_MANAGE_STATE(AfxGetStaticModuleState());

			pPage_Ctrl->Redraw_Page();
		}

		Draw__Area();
	}
}
void CObj__Route_STD::
WM_Timer(const HWND& hwnd)
{

}

void CObj__Route_STD::
WM_LButtonDown(const POINT& mouse_pt,const HWND& hwnd)
{

}
void CObj__Route_STD::
WM_LButtonUp(const HWND& hwnd)
{

}

void CObj__Route_STD::
WM_RButtonDown(const POINT& mouse_pt,const HWND& hwnd)
{

}
void CObj__Route_STD::
WM_RButtonUp(const HWND& hwnd)
{

}

void CObj__Route_STD::
WM_Notify(UINT message,WPARAM wparam,LPARAM lparam)
{

}

//-------------------------------------------------------------------------------------	
void CObj__Route_STD
::Draw__Area()
{
	HDC hdc      = pGObj_Res->hDC;
	HDC hdc_back = pGObj_Res->hDC_BACK;

	COLORREF tcolor = RGB(0,0,0);

	POINT st = pSt;
	POINT et = pEt;
	POINT size;

	size.x = pEt.x - pSt.x;
	size.y = pEt.y - pSt.y;

	SetPixel(hdc_back,st.x,st.y,tcolor);

	StretchBlt(hdc_back,
				st.x,st.y,size.x,1,
				hdc_back, 
				st.x,st.y,1,1,
				SRCCOPY);	

	StretchBlt(hdc_back,
				st.x,st.y,1,size.y,
				hdc_back, 
				st.x,st.y,1,1,
				SRCCOPY);	

	StretchBlt(hdc_back,
				st.x,et.y-1,size.x,1,
				hdc_back, 
				st.x,st.y,1,1,
				SRCCOPY);	

	StretchBlt(hdc_back,
				et.x-1,st.y,1,size.y,
				hdc_back, 
				st.x,st.y,1,1,
				SRCCOPY);	

	StretchBlt(hdc,
				st.x,st.y, 
				size.x,size.y,
				hdc_back, 
				st.x,st.y, 
				size.x,size.y,
				SRCCOPY);	
}
