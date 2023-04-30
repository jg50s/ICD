#include "StdAfx.h"
#include "CObj__Route_EDIT.h"



//-------------------------------------------------------------------------------------
CObj__Route_EDIT::CObj__Route_EDIT()
{
	pPage_Ctrl = NULL;
	bActive_Show = false;
}
CObj__Route_EDIT::~CObj__Route_EDIT()
{

}


//-------------------------------------------------------------------------------------
#include "CObj__Route_EDIT__KEY_DEF.h"


void CObj__Route_EDIT
::Get_Parameter(GObj__Parameter_Def* p_obj_para_def)
{
	CString key_name;

	//
	p_obj_para_def->Register_Command(pKEY__DATA_PART_NAME);
	
	//
	p_obj_para_def->Register_Command(pKEY__DATA_PM_SIZE, "ListBox", "1 2 3 4 5 6", "4");

	for(int i=0; i<DEF_PMx__SIZE; i++)
	{
		key_name.Format(pKEY__CH_CFG_NAME_PM_X, i+1);
		p_obj_para_def->Register_Channel(key_name);
	}

	// ...
	{
		p_obj_para_def->Register_Command(pKEY__DATA_ST_SIZE, "ListBox", "1 2 3", "2");
	
		p_obj_para_def->Register_Command(pKEY__DATA_PRE_SUB_DIR);
		p_obj_para_def->Register_Command(pKEY__DATA_MAIN_SUB_DIR);
		p_obj_para_def->Register_Command(pKEY__DATA_POST_SUB_DIR);
	}

	// LLx_COMMON ...
	{
		p_obj_para_def->Register_Command(pKEY__DATA_LLx_MODE, "ListBox", "ALL  ONLY_MODE", "ALL");
	}
	// LLx_IN ...
	{
		p_obj_para_def->Register_Command(pKEY__DATA_LLx_IN_SIZE, "ListBox", "2 4", "2");

		for(int i=0; i<_LLx__MAX; i++)
		{
			key_name.Format(pKEY__DATA_LLx_IN_ACTIVE_X, i+1);
			p_obj_para_def->Register_Command(key_name, "ListBox", "NO YES", "YES");
		}
	}

	// LLx_OUT ...
	{
		p_obj_para_def->Register_Command(pKEY__DATA_LLx_OUT_SIZE, "ListBox", "2 4", "2");
	
		for(int i=0; i<_LLx__MAX; i++)
		{
			key_name.Format(pKEY__DATA_LLx_OUT_ACTIVE_X, i+1);
			p_obj_para_def->Register_Command(key_name, "ListBox", "NO YES", "YES");
		}
	}

	// LLx_PROC ...
	{
		p_obj_para_def->Register_Command(pKEY__DATA_LOOPx_PROC_ACTIVE, "ListBox", "NO YES", "NO");

		p_obj_para_def->Register_Command(pKEY__DATA_LLx_PROC_ACTIVE, "ListBox", "NO YES", "NO");
		p_obj_para_def->Register_Command(pKEY__DATA_LLx_PROC_SIZE,   "ListBox", "2 4", "2");
		p_obj_para_def->Register_Command(pKEY__DATA_LL1_PROC_ACTIVE, "ListBox", "NO YES", "YES");
		p_obj_para_def->Register_Command(pKEY__DATA_LL2_PROC_ACTIVE, "ListBox", "NO YES", "YES");
		p_obj_para_def->Register_Command(pKEY__DATA_LL3_PROC_ACTIVE, "ListBox", "NO YES", "YES");
		p_obj_para_def->Register_Command(pKEY__DATA_LL4_PROC_ACTIVE, "ListBox", "NO YES", "YES");
	}

	// ALx_SLOT ...
	{
		p_obj_para_def->Register_Command(pKEY__DATA_DEFAULT_AL1_CONTROL_TYPE, "ListBox", "CONFIG ROUTE", "CONFIG");
		p_obj_para_def->Register_Command(pKEY__DATA_DEFAULT_AL1_SLOT_TYPE, "ListBox", "FIXED", "FIXED");

		p_obj_para_def->Register_Command(pKEY__DATA_DEFAULT_AL1_SLOT01_ACTIVE, "ListBox", "YES NO", "YES");
		p_obj_para_def->Register_Command(pKEY__DATA_DEFAULT_AL1_SLOT02_ACTIVE, "ListBox", "YES NO", "YES");
	}

	// LLx_SLOT ...
	{
		p_obj_para_def->Register_Command(pKEY__DATA_DEFAULT_LLx_SLOT_TYPE, "ListBox", "FIXED", "FIXED");

		int i_limit = 4;
		for(int i=0; i<i_limit; i++)
		{
			key_name.Format(pKEY__DATA_DEFAULT_LLX_SLOT01_ACTIVE, i+1);
			p_obj_para_def->Register_Command(key_name, "ListBox", "YES NO", "YES");

			key_name.Format(pKEY__DATA_DEFAULT_LLX_SLOT02_ACTIVE, i+1);
			p_obj_para_def->Register_Command(key_name, "ListBox", "YES NO", "YES");
		}
	}

	// LLx_OUT ...
	{
		p_obj_para_def->Register_Command(pKEY__DATA_LLx_OUT_COOLING_ACTIVE, "ListBox", "NO YES", "NO");
	}

	// STx PARA ...
	{
		p_obj_para_def->Register_Command(pKEY__DATA_STx_N2_PURGE_ACTIVE, "ListBox", "NO YES", "NO");
	}
}
void CObj__Route_EDIT
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
		pPage_Ctrl = new CDlg__Route_EDIT;
	}
	if(pPage_Ctrl != NULL)
	{
		pPage_Ctrl->pGObj_Res  = pGObj_Res;
		pPage_Ctrl->iREAL_MODE = iREAL_MODE;

		pPage_Ctrl->Set_Parameter(module_id);

		if(!bActive_Show)
		{
			bActive_Show = true;

			pPage_Ctrl->Create(IDD_DLG__ROUTE_EDIT, CWnd::FromHandle(hwnd));	
		}
	}
}

void CObj__Route_EDIT
::Show_GObj(const HWND& hwnd)
{
	if(pPage_Ctrl != NULL)
	{
		pPage_Ctrl->Set_MoveWindow(pSt, pEt);
	}

	Draw__Area();
}
void CObj__Route_EDIT
::Hide_GObj()
{
	if(pPage_Ctrl != NULL)
	{
		pPage_Ctrl->ShowWindow(SW_HIDE);
	}
}

//-------------------------------------------------------------------------------------	
void CObj__Route_EDIT
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
void CObj__Route_EDIT::
WM_Timer(const HWND& hwnd)
{

}

void CObj__Route_EDIT::
WM_LButtonDown(const POINT& mouse_pt,const HWND& hwnd)
{

}
void CObj__Route_EDIT::
WM_LButtonUp(const HWND& hwnd)
{

}

void CObj__Route_EDIT::
WM_RButtonDown(const POINT& mouse_pt,const HWND& hwnd)
{

}
void CObj__Route_EDIT::
WM_RButtonUp(const HWND& hwnd)
{

}

void CObj__Route_EDIT::
WM_Notify(UINT message,WPARAM wparam,LPARAM lparam)
{

}

//-------------------------------------------------------------------------------------	
void CObj__Route_EDIT
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
