#include "StdAfx.h"
#include "CObj__Report_Table.h"

#include "CObj__Report_Table__KEY_DEF.h"


//-------------------------------------------------------------------------------------
CObj__Report_Table::CObj__Report_Table()
{
	pPage_Ctrl = NULL;
	bActive_Show = false;
}
CObj__Report_Table::~CObj__Report_Table()
{

}

//-------------------------------------------------------------------------------------
void CObj__Report_Table
::Get_Parameter(GObj__Parameter_Def* p_obj_para_def)
{
	p_obj_para_def->Register_Command(pKEY__DATA_TABLE_ROW_MAX);
	p_obj_para_def->Register_Command(pKEY__DATA_COL_WIDTH_INDEX);
	p_obj_para_def->Register_Command(pKEY__DATA_COL_WIDTH_MSG);

	// ...
	CString ch_name;

	int i_limit = _CFG__MSG_SIZE;
	int i;

	for(i=0; i<i_limit; i++)
	{
		ch_name.Format("%s%02d", pKEY__CH_MSG_X,i+1);
		p_obj_para_def->Register_Channel(ch_name);
	}
}
void CObj__Report_Table
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
		pPage_Ctrl = new CDlg__Report_Table;
	}
	if(pPage_Ctrl != NULL)
	{
		pPage_Ctrl->pGObj_Res  = pGObj_Res;
		pPage_Ctrl->iREAL_MODE = iREAL_MODE;

		pPage_Ctrl->Set_Parameter(module_id);

		if(!bActive_Show)
		{
			bActive_Show = true;

			pPage_Ctrl->Create(IDD_DLG__REPORT_TABLE, CWnd::FromHandle(hwnd));	
		}
	}
}

void CObj__Report_Table
::Show_GObj(const HWND& hwnd)
{
	if(pPage_Ctrl != NULL)
	{
		pPage_Ctrl->Set_MoveWindow(pSt, pEt);
	}

	if(iREAL_MODE < 0)
	{
		Draw__Area();
	}
}
void CObj__Report_Table
::Hide_GObj()
{
	if(pPage_Ctrl != NULL)
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());

		pPage_Ctrl->ShowWindow(SW_HIDE);
	}
}

//-------------------------------------------------------------------------------------	
void CObj__Report_Table
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
void CObj__Report_Table::
WM_Timer(const HWND& hwnd)
{

}

void CObj__Report_Table::
WM_LButtonDown(const POINT& mouse_pt,const HWND& hwnd)
{

}
void CObj__Report_Table::
WM_LButtonUp(const HWND& hwnd)
{

}

void CObj__Report_Table::
WM_RButtonDown(const POINT& mouse_pt,const HWND& hwnd)
{

}
void CObj__Report_Table::
WM_RButtonUp(const HWND& hwnd)
{

}

void CObj__Report_Table::
WM_Notify(UINT message,WPARAM wparam,LPARAM lparam)
{

}

//-------------------------------------------------------------------------------------	
void CObj__Report_Table
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
