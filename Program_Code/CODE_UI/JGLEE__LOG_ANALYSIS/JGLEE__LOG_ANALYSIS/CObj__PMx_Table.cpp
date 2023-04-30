#include "StdAfx.h"
#include "CObj__PMx_Table.h"

#include "CObj__PMx_Table__KEY_DEF.h"


//-------------------------------------------------------------------------------------
CObj__PMx_Table::CObj__PMx_Table()
{
	pPage_Ctrl = NULL;
	bActive_Show = false;
}
CObj__PMx_Table::~CObj__PMx_Table()
{

}

//-------------------------------------------------------------------------------------
void CObj__PMx_Table
::Get_Parameter(GObj__Parameter_Def* p_obj_para_def)
{
	p_obj_para_def->Register_Command(pKEY__DATA_INF_DIR);
	p_obj_para_def->Register_Command(pKEY__DATA_INF_FILE);

	p_obj_para_def->Register_Command(pKEY__DATA_COL_WITH_NO,      "", "",  "60");
	p_obj_para_def->Register_Command(pKEY__DATA_COL_WITH_NAME,    "", "", "250");
	p_obj_para_def->Register_Command(pKEY__DATA_COL_WITH_DATA,    "", "", "200");
	p_obj_para_def->Register_Command(pKEY__DATA_COL_WITH_CHANNEL, "", "", "250");

	p_obj_para_def->Register_Command(pKEY__DATA_PM1_USE, "ListBox", "YES NO", "YES");
	p_obj_para_def->Register_Command(pKEY__DATA_PM2_USE, "ListBox", "YES NO", "YES");
	p_obj_para_def->Register_Command(pKEY__DATA_PM3_USE, "ListBox", "YES NO", "YES");
	p_obj_para_def->Register_Command(pKEY__DATA_PM4_USE, "ListBox", "YES NO", "YES");
	p_obj_para_def->Register_Command(pKEY__DATA_PM5_USE, "ListBox", "YES NO", "YES");
	p_obj_para_def->Register_Command(pKEY__DATA_PM6_USE, "ListBox", "YES NO", "YES");

	p_obj_para_def->Register_Command(pKEY__DATA_PM1_NAME);
	p_obj_para_def->Register_Command(pKEY__DATA_PM2_NAME);
	p_obj_para_def->Register_Command(pKEY__DATA_PM3_NAME);
	p_obj_para_def->Register_Command(pKEY__DATA_PM4_NAME);
	p_obj_para_def->Register_Command(pKEY__DATA_PM5_NAME);
	p_obj_para_def->Register_Command(pKEY__DATA_PM6_NAME);

	p_obj_para_def->Register_Channel(pKEY__CH_PM1_GOTO_MAINT);
	p_obj_para_def->Register_Channel(pKEY__CH_PM2_GOTO_MAINT);
	p_obj_para_def->Register_Channel(pKEY__CH_PM3_GOTO_MAINT);
	p_obj_para_def->Register_Channel(pKEY__CH_PM4_GOTO_MAINT);
	p_obj_para_def->Register_Channel(pKEY__CH_PM5_GOTO_MAINT);
	p_obj_para_def->Register_Channel(pKEY__CH_PM6_GOTO_MAINT);
}

void CObj__PMx_Table
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
		pPage_Ctrl = new CDlg__PMx_Table;
	}
	if(pPage_Ctrl != NULL)
	{
		pPage_Ctrl->pGObj_Res  = pGObj_Res;
		pPage_Ctrl->iREAL_MODE = iREAL_MODE;

		pPage_Ctrl->Set_Parameter(module_id);

		if(!bActive_Show)
		{
			bActive_Show = true;

			pPage_Ctrl->Create(IDD_DLG__PMx_TABLE, CWnd::FromHandle(hwnd));	
		}
	}
}

void CObj__PMx_Table
::Show_GObj(const HWND& hwnd)
{
	if(pPage_Ctrl != NULL)
	{
		pPage_Ctrl->Set_MoveWindow(pSt, pEt);
	}

	Draw__Area();
}
void CObj__PMx_Table
::Hide_GObj()
{
	if(pPage_Ctrl != NULL)
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());

		pPage_Ctrl->ShowWindow(SW_HIDE);
	}
}

//-------------------------------------------------------------------------------------	
void CObj__PMx_Table
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
void CObj__PMx_Table::
WM_Timer(const HWND& hwnd)
{

}

void CObj__PMx_Table::
WM_LButtonDown(const POINT& mouse_pt,const HWND& hwnd)
{

}
void CObj__PMx_Table::
WM_LButtonUp(const HWND& hwnd)
{

}

void CObj__PMx_Table::
WM_RButtonDown(const POINT& mouse_pt,const HWND& hwnd)
{

}
void CObj__PMx_Table::
WM_RButtonUp(const HWND& hwnd)
{

}

void CObj__PMx_Table::
WM_Notify(UINT message,WPARAM wparam,LPARAM lparam)
{

}

//-------------------------------------------------------------------------------------	
void CObj__PMx_Table
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
