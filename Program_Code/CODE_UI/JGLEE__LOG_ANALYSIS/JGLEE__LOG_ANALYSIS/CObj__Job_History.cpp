#include "StdAfx.h"
#include "CObj__Job_History.h"

#include "CObj__Job_History__KEY_DEF.h"


//-------------------------------------------------------------------------------------
CObj__Job_History::CObj__Job_History()
{
	pPage_Ctrl = NULL;
	bActive_Show = false;
}
CObj__Job_History::~CObj__Job_History()
{

}

//-------------------------------------------------------------------------------------
void CObj__Job_History
::Get_Parameter(GObj__Parameter_Def* p_obj_para_def)
{
	CString ch_name;

	int lp_size = 5;
	int i;

	// ...
	p_obj_para_def->Register_Command(pKEY__DATA_AXIS_MAX);
	p_obj_para_def->Register_Command(pKEY__DATA_ERR_RANGE);

	p_obj_para_def->Register_Command(pKEY__DATA_LPx_MAX, "ListBox", "1, 2, 3, 4 ,5", "3");

	//
	p_obj_para_def->Register_Command(pKEY__DATA_RCP_PARA_PM1);
	p_obj_para_def->Register_Command(pKEY__DATA_RCP_PARA_PM2);
	p_obj_para_def->Register_Command(pKEY__DATA_RCP_PARA_PM3);
	p_obj_para_def->Register_Command(pKEY__DATA_RCP_PARA_PM4);
	p_obj_para_def->Register_Command(pKEY__DATA_RCP_PARA_PM5);
	p_obj_para_def->Register_Command(pKEY__DATA_RCP_PARA_PM6);

	p_obj_para_def->Register_Command(pKEY__DATA_RCP_PARA_LL1);
	p_obj_para_def->Register_Command(pKEY__DATA_RCP_PARA_LL2);

	//
	p_obj_para_def->Register_Channel(pKEY__CH_TEMPLATE_FILE_PM1);
	p_obj_para_def->Register_Channel(pKEY__CH_TEMPLATE_FILE_PM2);
	p_obj_para_def->Register_Channel(pKEY__CH_TEMPLATE_FILE_PM3);
	p_obj_para_def->Register_Channel(pKEY__CH_TEMPLATE_FILE_PM4);
	p_obj_para_def->Register_Channel(pKEY__CH_TEMPLATE_FILE_PM5);
	p_obj_para_def->Register_Channel(pKEY__CH_TEMPLATE_FILE_PM6);

	p_obj_para_def->Register_Channel(pKEY__CH_TEMPLATE_FILE_LL1);
	p_obj_para_def->Register_Channel(pKEY__CH_TEMPLATE_FILE_LL2);
}
void CObj__Job_History
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
		pPage_Ctrl = new CDlg__Job_History;
	}
	if(pPage_Ctrl != NULL)
	{
		pPage_Ctrl->pGObj_Res  = pGObj_Res;
		pPage_Ctrl->iREAL_MODE = iREAL_MODE;

		pPage_Ctrl->Set_Parameter(module_id);

		if(!bActive_Show)
		{
			bActive_Show = true;

			pPage_Ctrl->Create(IDD_DLG__JOB_HISTORY, CWnd::FromHandle(hwnd));	
		}
	}
}

void CObj__Job_History
::Show_GObj(const HWND& hwnd)
{
	if(pPage_Ctrl != NULL)
	{
		pPage_Ctrl->Set_MoveWindow(pSt, pEt);
	}

	Draw__Area();
}
void CObj__Job_History
::Hide_GObj()
{
	if(pPage_Ctrl != NULL)
	{
		pPage_Ctrl->ShowWindow(SW_HIDE);
	}
}

//-------------------------------------------------------------------------------------	
void CObj__Job_History
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
void CObj__Job_History::
WM_Timer(const HWND& hwnd)
{

}

void CObj__Job_History::
WM_LButtonDown(const POINT& mouse_pt,const HWND& hwnd)
{

}
void CObj__Job_History::
WM_LButtonUp(const HWND& hwnd)
{

}

void CObj__Job_History::
WM_RButtonDown(const POINT& mouse_pt,const HWND& hwnd)
{

}
void CObj__Job_History::
WM_RButtonUp(const HWND& hwnd)
{

}

void CObj__Job_History::
WM_Notify(UINT message,WPARAM wparam,LPARAM lparam)
{

}

//-------------------------------------------------------------------------------------	
void CObj__Job_History
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

	SetPixel(hdc_back,st.x,st.y, tcolor);

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
