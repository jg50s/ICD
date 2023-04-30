#include "StdAfx.h"
#include "CObj__PMx_Recipe_Select.h"



//-------------------------------------------------------------------------------------
CObj__PMx_Recipe_Select::CObj__PMx_Recipe_Select()
{
	pPage_Ctrl = NULL;
	bActive_Show = false;
}
CObj__PMx_Recipe_Select::~CObj__PMx_Recipe_Select()
{

}


//-------------------------------------------------------------------------------------
#include "CObj__PMx_Recipe_Select__KEY_DEF.h"


void CObj__PMx_Recipe_Select
::Get_Parameter(GObj__Parameter_Def* p_obj_para_def)
{
	// ...
	{
		CString ch_name;

		int i_limit;
		int i;

		//
		p_obj_para_def->Register_Command(pKEY__DATA_PART_NAME);

		p_obj_para_def->Register_Command(pKEY__DATA_PM_SIZE, "ListBox", "1 2 3 4 5 6", "4");
		p_obj_para_def->Register_Command(pKEY__DATA_LL_SIZE, "ListBox", "0 1 2 3 4", "0");
		
		//
		p_obj_para_def->Register_Command(pKEY__DATA_PRE_USE,  "ListBox", "NO YES", "NO");
		p_obj_para_def->Register_Command(pKEY__DATA_POST_USE, "ListBox", "NO YES", "NO");

		p_obj_para_def->Register_Command(pKEY__DATA_PRE_SUB_DIR);
		p_obj_para_def->Register_Command(pKEY__DATA_MAIN_SUB_DIR);
		p_obj_para_def->Register_Command(pKEY__DATA_POST_SUB_DIR);

		//
		p_obj_para_def->Register_Channel(pKEY__CH_CURRENT_PM_ID);

		// 
		i_limit = _DEF_PMx__MAX;
		for(i=0; i<i_limit; i++)
		{
			int id = i + 1;

			ch_name.Format(	pKEY__CH_RECIPE_PRE_PM_X, id);
			p_obj_para_def->Register_Channel(ch_name);

			ch_name.Format(pKEY__CH_RECIPE_MAIN_PM_X, id);
			p_obj_para_def->Register_Channel(ch_name);

			ch_name.Format(pKEY__CH_RECIPE_POST_PM_X, id);
			p_obj_para_def->Register_Channel(ch_name);
		}

		// 
		i_limit = _DEF_LLx__MAX;
		for(i=0; i<i_limit; i++)
		{
			int id = i + 1;

			ch_name.Format(	pKEY__CH_RECIPE_PRE_LL_X, id);
			p_obj_para_def->Register_Channel(ch_name);

			ch_name.Format(pKEY__CH_RECIPE_MAIN_LL_X, id);
			p_obj_para_def->Register_Channel(ch_name);

			ch_name.Format(pKEY__CH_RECIPE_POST_LL_X, id);
			p_obj_para_def->Register_Channel(ch_name);
		}
	}
}
void CObj__PMx_Recipe_Select
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
		pPage_Ctrl = new CDlg__PMx_Recipe_Select;
	}
	if(pPage_Ctrl != NULL)
	{
		pPage_Ctrl->pGObj_Res  = pGObj_Res;
		pPage_Ctrl->iREAL_MODE = iREAL_MODE;

		pPage_Ctrl->Set_Parameter(module_id);

		if(!bActive_Show)
		{
			bActive_Show = true;

			pPage_Ctrl->Create(IDD_DLG__PMx_RECIPE_SELECT, CWnd::FromHandle(hwnd));	
		}
	}	
}

void CObj__PMx_Recipe_Select
::Show_GObj(const HWND& hwnd)
{
	if(pPage_Ctrl != NULL)
	{
		pPage_Ctrl->Set_MoveWindow(pSt, pEt);
	}	

	Draw__Area();
}
void CObj__PMx_Recipe_Select
::Hide_GObj()
{
	if(pPage_Ctrl != NULL)
	{
		pPage_Ctrl->ShowWindow(SW_HIDE);
	}
}

//-------------------------------------------------------------------------------------	
void CObj__PMx_Recipe_Select
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
void CObj__PMx_Recipe_Select::
WM_Timer(const HWND& hwnd)
{

}

void CObj__PMx_Recipe_Select::
WM_LButtonDown(const POINT& mouse_pt,const HWND& hwnd)
{

	printf("CObj__PMx_Recipe_Select::WM_LButtonDown() \n");
}
void CObj__PMx_Recipe_Select::
WM_LButtonUp(const HWND& hwnd)
{

	printf("CObj__PMx_Recipe_Select::WM_LButtonUp() \n");
}

void CObj__PMx_Recipe_Select::
WM_RButtonDown(const POINT& mouse_pt,const HWND& hwnd)
{

	printf("CObj__PMx_Recipe_Select::WM_RButtonDown() \n");
}
void CObj__PMx_Recipe_Select::
WM_RButtonUp(const HWND& hwnd)
{

	printf("CObj__PMx_Recipe_Select::WM_RButtonUp() \n");
}

void CObj__PMx_Recipe_Select::
WM_Notify(UINT message,WPARAM wparam,LPARAM lparam)
{

	printf("CObj__PMx_Recipe_Select::WM_Notify() \n");
}

//-------------------------------------------------------------------------------------	
void CObj__PMx_Recipe_Select
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
