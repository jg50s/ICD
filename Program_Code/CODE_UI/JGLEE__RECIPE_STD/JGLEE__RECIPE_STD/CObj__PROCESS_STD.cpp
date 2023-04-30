#include "StdAfx.h"
#include "CObj__PROCESS_STD.h"

#include "CObj__PROCESS_STD__KEY_DEF.h"


//-------------------------------------------------------------------------------------
CObj__PROCESS_STD::CObj__PROCESS_STD()
{
	pPage_Ctrl = NULL;
	bActive_Show = false;
}
CObj__PROCESS_STD::~CObj__PROCESS_STD()
{

}

//-------------------------------------------------------------------------------------
void CObj__PROCESS_STD
::Get_Parameter(GObj__Parameter_Def* p_obj_para_def)
{
	CString key_name;
	int i;

	//
	p_obj_para_def->Register_Channel(pKEY__CH_FILE_LOCK_FLAG);

	//
	p_obj_para_def->Register_Command(pKEY__ITEM_HEADER_USE, "ListBox", "NO  NO_SHOW  YES", "YES");
	p_obj_para_def->Register_Command(pKEY__ITEM_HEADER_FILE);
	p_obj_para_def->Register_Command(pKEY__ITEM_HEADER_WIDTH);

	p_obj_para_def->Register_Command(pKEY__ITEM_STEP_USE, "ListBox", "NO  NO_SHOW  YES", "YES");
	p_obj_para_def->Register_Command(pKEY__ITEM_STEP_FILE);
	p_obj_para_def->Register_Command(pKEY__ITEM_STEP_WIDTH);

	p_obj_para_def->Register_Command(pKEY__ITEM_TOLERANCE_USE, "ListBox", "NO  NO_SHOW  YES", "YES");
	p_obj_para_def->Register_Command(pKEY__ITEM_TOLERANCE_FILE);
	p_obj_para_def->Register_Command(pKEY__ITEM_TOLERANCE_WIDTH);

	//
	p_obj_para_def->Register_Command(pKEY__RCP_PRE_USE,  "ListBox", "NO  YES", "YES");
	p_obj_para_def->Register_Command(pKEY__RCP_PRE_FOLDER);

	p_obj_para_def->Register_Command(pKEY__RCP_MAIN_USE, "ListBox", "NO  YES", "YES");
	p_obj_para_def->Register_Command(pKEY__RCP_MAIN_FOLDER);

	p_obj_para_def->Register_Command(pKEY__RCP_POST_USE, "ListBox", "NO  YES", "YES");
	p_obj_para_def->Register_Command(pKEY__RCP_POST_FOLDER);

	//
	p_obj_para_def->Register_Command(pKEY__PM1_LINK_USE, "ListBox", "NO  YES", "YES");
	p_obj_para_def->Register_Command(pKEY__PM2_LINK_USE, "ListBox", "NO  YES", "YES");
	p_obj_para_def->Register_Command(pKEY__PM3_LINK_USE, "ListBox", "NO  YES", "YES");
	p_obj_para_def->Register_Command(pKEY__PM4_LINK_USE, "ListBox", "NO  YES", "YES");
	p_obj_para_def->Register_Command(pKEY__PM5_LINK_USE, "ListBox", "NO  YES", "YES");
	p_obj_para_def->Register_Command(pKEY__PM6_LINK_USE, "ListBox", "NO  YES", "YES");

	//
	p_obj_para_def->Register_Command(pKEY__SUMMARY_MODE, "ListBox", "DISABLE ENABLE USER", "DISABLE");

	for(i = 0; i < _CFG__SUMMARY_ITEM_MAX; i++)
	{
		key_name.Format(pKEY__SUMMARY_ITEM_ID_X, i+1);
		p_obj_para_def->Register_Command(key_name);
	}

	//
	p_obj_para_def->Register_Command(pKEY__RCP_TYPE_LINE_ID, "ListBox", "0 1 2 3 4 5 6 7 8 9", "0");
	p_obj_para_def->Register_Command(pKEY__RCP_TYPE_CHECK_DATA, "");

	//
	p_obj_para_def->Register_Command(pKEY__RCP_INTERLOCK_SAVE_CHECK, "ListBox", "NO YES", "NO");

	//
	p_obj_para_def->Register_Command(pKEY__RCP_INTERLOCK_DLL_NAME, "RCP_INTERLOCK.DLL_NAME");

	//
	p_obj_para_def->Register_Command(pKEY__TEST_MODULE_ID, "ListBox", "0 1 2 3 4 5 6 7", "2");

}
void CObj__PROCESS_STD
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
		pPage_Ctrl = new CDlg__PROCESS_STD;
	}
	if(pPage_Ctrl != NULL)
	{
		pPage_Ctrl->pGObj_Res  = pGObj_Res;
		pPage_Ctrl->iREAL_MODE = iREAL_MODE;

		pPage_Ctrl->Set_Parameter(module_id);

		if(!bActive_Show)
		{
			bActive_Show = true;

			pPage_Ctrl->Create(IDD_DLG__PROCESS_STD, CWnd::FromHandle(hwnd));	
		}

		// ...
		{
			CStringArray l__link_ch;
			pPage_Ctrl->Get_Link_Channel_List(l__link_ch);

			/*
			// ...
			{
				CString log_msg;
				CString log_bff;

				log_msg = " * pPage_Ctrl->Get_Link_Channel_List() ... \n";

				int i_limit = l__link_ch.GetSize();
				int i;

				for(i=0; i<i_limit; i++)
				{
					log_bff.Format(" * %02d) [%s] \n", i+1,l__link_ch[i]); 
					log_msg += log_bff;
				}
				log_msg += "\n";

				printf(log_msg);
			}
			*/

			p_obj_res->pGOBJ_PARA_CTRL->Make_Exe_Channel_List(l__link_ch);
		}
	}
}

void CObj__PROCESS_STD
::Show_GObj(const HWND& hwnd)
{
	if(pPage_Ctrl != NULL)
	{
		pPage_Ctrl->Set_MoveWindow(pSt, pEt);
	}

	Draw__Area();
}
void CObj__PROCESS_STD
::Hide_GObj()
{
	if(pPage_Ctrl != NULL)
	{
		pPage_Ctrl->ShowWindow(SW_HIDE);
	}
}

//-------------------------------------------------------------------------------------	
void CObj__PROCESS_STD
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
void CObj__PROCESS_STD::
WM_Timer(const HWND& hwnd)
{

}

void CObj__PROCESS_STD::
WM_LButtonDown(const POINT& mouse_pt,const HWND& hwnd)
{

}
void CObj__PROCESS_STD::
WM_LButtonUp(const HWND& hwnd)
{

}

void CObj__PROCESS_STD::
WM_RButtonDown(const POINT& mouse_pt,const HWND& hwnd)
{

}
void CObj__PROCESS_STD::
WM_RButtonUp(const HWND& hwnd)
{

}

void CObj__PROCESS_STD::
WM_Notify(UINT message,WPARAM wparam,LPARAM lparam)
{

}

//-------------------------------------------------------------------------------------	
void CObj__PROCESS_STD
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
