#include "StdAfx.h"
#include "CObj__PARTICLE_TABLE.h"
#include "CObj__PARTICLE_TABLE__DEF.h"


//-------------------------------------------------------------------------------------
CObj__PARTICLE_TABLE::CObj__PARTICLE_TABLE()
{
	pPage_Ctrl = NULL;
	bActive_Show = false;
}
CObj__PARTICLE_TABLE::~CObj__PARTICLE_TABLE()
{

}

//-------------------------------------------------------------------------------------
void CObj__PARTICLE_TABLE
::Get_Parameter(GObj__Parameter_Def* p_obj_para_def)
{
	CString key_name;
	int i;
	int k;

	// STATE COLOR ...
	{
		key_name = pKEY__DATA_T_COLOR_IDLE;
		p_obj_para_def->Register_Command(key_name, "Color", "", "RGB(0,0,0)");

		key_name = pKEY__DATA_B_COLOR_IDLE;
		p_obj_para_def->Register_Command(key_name, "Color", "", "RGB(255,255,255)");

		//
		key_name = pKEY__DATA_T_COLOR_DISABLE;
		p_obj_para_def->Register_Command(key_name, "Color", "", "RGB(50,50,50)");

		key_name = pKEY__DATA_B_COLOR_DISABLE;
		p_obj_para_def->Register_Command(key_name, "Color", "", "RGB(155,155,155)");

		//
		key_name = pKEY__DATA_T_COLOR_RESERVE;
		p_obj_para_def->Register_Command(key_name, "Color", "", "RGB(0,0,0)");

		key_name = pKEY__DATA_B_COLOR_RESERVE;
		p_obj_para_def->Register_Command(key_name, "Color", "", "RGB(0,255,255)");

		//
		key_name = pKEY__DATA_T_COLOR_RUN;
		p_obj_para_def->Register_Command(key_name, "Color", "", "RGB(255,255,255)");

		key_name = pKEY__DATA_B_COLOR_RUN;
		p_obj_para_def->Register_Command(key_name, "Color", "", "RGB(0,0,255)");

		//
		key_name = pKEY__DATA_T_COLOR_END;
		p_obj_para_def->Register_Command(key_name, "Color", "", "RGB(0,0,0)");

		key_name = pKEY__DATA_B_COLOR_END;
		p_obj_para_def->Register_Command(key_name, "Color", "", "RGB(188,106,235)");

		//
		key_name = pKEY__DATA_T_COLOR_ABORT;
		p_obj_para_def->Register_Command(key_name, "Color", "", "RGB(255,255,255)");

		key_name = pKEY__DATA_B_COLOR_ABORT;
		p_obj_para_def->Register_Command(key_name, "Color", "", "RGB(155,0,0)");
	}

	// CFG : LLx & STx ...
	{
		key_name = pKEY__DATA_LLx_SLOT_SIZE;
		p_obj_para_def->Register_Command(key_name, "ListBox", "1 2", "2");

		key_name = pKEY__DATA_LLx_PIN_USE;
		p_obj_para_def->Register_Command(key_name, "ListBox", "NO YES", "NO");

		//
		key_name = pKEY__DATA_STx_SIZE;
		p_obj_para_def->Register_Command(key_name, "ListBox", "1 2", "1");

		//
		key_name = pKEY__DATA_PMx_SIZE;
		p_obj_para_def->Register_Command(key_name, "ListBox", "1 2 3 4 5 6", "4");
	}

	// TRANSFER.PART ...
	{
		CString act_name;

		int i_limit = _ACT__TRANSFER_SIZE;
		for(int i=0; i<i_limit; i++)
		{
				 if(i == _ACT_ID__MOVE_TO_LPx)				act_name = _ACT_MOVE__MOVE_TO_LPx;
			else if(i == _ACT_ID__MOVE_TO_LLx_IN_ATM)		act_name = _ACT_MOVE__MOVE_TO_LLx_IN_ATM;
			else if(i == _ACT_ID__LLx_DOOR_VLV_OP_CL)		act_name = _ACT_MOVE__LLx_DOOR_VLV_OP_CL;
			else if(i == _ACT_ID__LLx_PUMP_VENT)			act_name = _ACT_MOVE__LLx_PUMP_VENT;
			else if(i == _ACT_ID__LLx_COOLING)				act_name = _ACT_MOVE__LLx_COOLING;
			else if(i == _ACT_ID__LLx_SLOT_VLV_OP_CL)		act_name = _ACT_MOVE__LLx_SLOT_VLV_OP_CL;
			else if(i == _ACT_ID__MOVE_TO_LLx_IN_VAC)		act_name = _ACT_MOVE__MOVE_TO_LLx_IN_VAC;
			else if(i == _ACT_ID__MOVE_TO_AL1)				act_name = _ACT_MOVE__MOVE_TO_AL1;
			else if(i == _ACT_ID__MOVE_TO_ST1)				act_name = _ACT_MOVE__MOVE_TO_ST1;
			else if(i == _ACT_ID__MOVE_TO_ST2)				act_name = _ACT_MOVE__MOVE_TO_ST2;
			else											continue;

			//
			key_name.Format("%s%s", pKEY__CH_MOVE_CTRL_STATE_X, act_name);
			p_obj_para_def->Register_Channel(key_name);

			//
			key_name.Format("%s%s", pKEY__CH_MOVE_STN_SRC_X, act_name);
			p_obj_para_def->Register_Channel(key_name);

			key_name.Format("%s%s", pKEY__CH_MOVE_STN_TRG_X, act_name);
			p_obj_para_def->Register_Channel(key_name);

			key_name.Format("%s%s", pKEY__CH_MOVE_CFG_COUNT_X, act_name);
			p_obj_para_def->Register_Channel(key_name);

			key_name.Format("%s%s", pKEY__CH_MOVE_CUR_COUNT_X, act_name);
			p_obj_para_def->Register_Channel(key_name);

			//
			key_name.Format("%s%s", pKEY__CH_MOVE_ACT_CHECK_X, act_name);
			p_obj_para_def->Register_Channel(key_name);
		}
	}

	// PROCESS.PART ...
	{
		CString str_id;

		int i_limit = 6;
		for(int i=0; i<i_limit; i++)
		{
			int t_limit = _ACT__PROCESS_SIZE;
			for(int t=0; t<t_limit; t++)
			{
				str_id.Format("%1d", i+1);
				
				// ...
				CString act_name;

					 if(t == _ACT_ID__MOVE_TO_PMx)				act_name = _ACT_PROC__MOVE_TO_PMx;
				else if(t == _ACT_ID__PMx_SLOT_VLV_OP_CL)		act_name = _ACT_PROC__PMx_SLOT_VLV_OP_CL;
				else if(t == _ACT_ID__PMx_PIN_UP_TO_DOWN)		act_name = _ACT_PROC__PMx_PIN_UP_TO_DOWN;
				else if(t == _ACT_ID__PMx_PROCESS)				act_name = _ACT_PROC__PMx_PROCESS;
				else											continue;

				//
				key_name.Format("%s%s%s", pKEY__CH_PROC_CTRL_STATE_X, act_name,str_id);
				p_obj_para_def->Register_Channel(key_name);

				//
				key_name.Format("%s%s%s", pKEY__CH_PROC_STN_SRC_X, act_name,str_id);
				p_obj_para_def->Register_Channel(key_name);

				key_name.Format("%s%s%s", pKEY__CH_PROC_STN_TRG_X, act_name,str_id);
				p_obj_para_def->Register_Channel(key_name);

				key_name.Format("%s%s%s", pKEY__CH_PROC_CFG_COUNT_X, act_name,str_id);
				p_obj_para_def->Register_Channel(key_name);

				key_name.Format("%s%s%s", pKEY__CH_PROC_CUR_COUNT_X, act_name,str_id);
				p_obj_para_def->Register_Channel(key_name);

				//
				key_name.Format("%s%s%s", pKEY__CH_PROC_ACT_CHECK_X, act_name,str_id);
				p_obj_para_def->Register_Channel(key_name);

				if(t == _ACT_ID__PMx_PROCESS)
				{
					key_name.Format("%s%s", pKEY__CH_PROC_RECIPE_NAME_X, str_id);
					p_obj_para_def->Register_Channel(key_name);
				}
			}
		}
	}

	// ...
}
void CObj__PARTICLE_TABLE
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
		pPage_Ctrl = new CDlg__PARTICLE_TABLE;
	}
	if(pPage_Ctrl != NULL)
	{
		pPage_Ctrl->pGObj_Res  = pGObj_Res;
		pPage_Ctrl->iREAL_MODE = iREAL_MODE;

		pPage_Ctrl->Set_Parameter(module_id);

		if(!bActive_Show)
		{
			bActive_Show = true;

			pPage_Ctrl->Create(IDD_DLG__PARTICLE_TABLE, CWnd::FromHandle(hwnd));	
		}
	}	

	iTimer_Delay_Count = 1;
}

void CObj__PARTICLE_TABLE
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
void CObj__PARTICLE_TABLE
::Hide_GObj()
{
	if(pPage_Ctrl != NULL)
	{
		pPage_Ctrl->ShowWindow(SW_HIDE);
	}
}

//-------------------------------------------------------------------------------------	
void CObj__PARTICLE_TABLE
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
void CObj__PARTICLE_TABLE::
WM_Timer(const HWND& hwnd)
{
	if(pPage_Ctrl != NULL)
	{
		if(iREAL_MODE > 0)
		{
			if(iTimer_Delay_Count < 1)
			{
				pPage_Ctrl->WM_Timer(hwnd);
			}
			else
			{
				iTimer_Delay_Count--;

				/*
				printf(" * CObj__PARTICLE_TABLE::WM_Timer() \n");
				printf("  * Timer_Delay_Count <- [%1d] \n", iTimer_Delay_Count);
				*/
			}
		}
		else
		{
			pPage_Ctrl->WM_Timer(hwnd);
		}
	}
}

void CObj__PARTICLE_TABLE::
WM_LButtonDown(const POINT& mouse_pt,const HWND& hwnd)
{

}
void CObj__PARTICLE_TABLE::
WM_LButtonUp(const HWND& hwnd)
{

}

void CObj__PARTICLE_TABLE::
WM_RButtonDown(const POINT& mouse_pt,const HWND& hwnd)
{

}
void CObj__PARTICLE_TABLE::
WM_RButtonUp(const HWND& hwnd)
{

}

void CObj__PARTICLE_TABLE::
WM_Notify(UINT message,WPARAM wparam,LPARAM lparam)
{

}

//-------------------------------------------------------------------------------------	
void CObj__PARTICLE_TABLE
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
