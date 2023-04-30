#include "stdafx.h"
#include "Dlg__PARTICLE_TABLE.h"

#include "CObj__PARTICLE_TABLE__DEF.h"
#include "PARTICLE_TABLE__COMMON_DEF.h"

#include "PARTICLE_TABLE__COMMON_RES.h"
extern CPARTICLE_TABLE__COMMON_RES mRes_Common;


// ...
int CDlg__PARTICLE_TABLE
::Set_Parameter(const int module_id)
{
	GObj__Parameter_Ctrl* p_obj_para_ctrl = pGObj_Res->pGOBJ_PARA_CTRL;

	CString key_name;
	CString key_data;


	// COLOR.IDLE ...
	{
		key_name = pKEY__DATA_T_COLOR_IDLE;
		p_obj_para_ctrl->Get_Constant_Data(key_name, key_data);
		mRes_Common.sDATA__T_Color__IDLE = key_data;

		key_name = pKEY__DATA_B_COLOR_IDLE;
		p_obj_para_ctrl->Get_Constant_Data(key_name, key_data);
		mRes_Common.sDATA__B_Color__IDLE = key_data;
	}
	// COLOR.DISABLE ...
	{
		key_name = pKEY__DATA_T_COLOR_DISABLE;
		p_obj_para_ctrl->Get_Constant_Data(key_name, key_data);
		mRes_Common.sDATA__T_Color__DISABLE = key_data;

		key_name = pKEY__DATA_B_COLOR_DISABLE;
		p_obj_para_ctrl->Get_Constant_Data(key_name, key_data);
		mRes_Common.sDATA__B_Color__DISABLE = key_data;
	}
	// COLOR.RESERVE ...
	{
		key_name = pKEY__DATA_T_COLOR_RESERVE;
		p_obj_para_ctrl->Get_Constant_Data(key_name, key_data);
		mRes_Common.sDATA__T_Color__RESERVE = key_data;

		key_name = pKEY__DATA_B_COLOR_RESERVE;
		p_obj_para_ctrl->Get_Constant_Data(key_name, key_data);
		mRes_Common.sDATA__B_Color__RESERVE = key_data;
	}
	// COLOR.RUN ...
	{
		key_name = pKEY__DATA_T_COLOR_RUN;
		p_obj_para_ctrl->Get_Constant_Data(key_name, key_data);
		mRes_Common.sDATA__T_Color__RUN = key_data;

		key_name = pKEY__DATA_B_COLOR_RUN;
		p_obj_para_ctrl->Get_Constant_Data(key_name, key_data);
		mRes_Common.sDATA__B_Color__RUN = key_data;
	}
	// COLOR.END ...
	{
		key_name = pKEY__DATA_T_COLOR_END;
		p_obj_para_ctrl->Get_Constant_Data(key_name, key_data);
		mRes_Common.sDATA__T_Color__END = key_data;

		key_name = pKEY__DATA_B_COLOR_END;
		p_obj_para_ctrl->Get_Constant_Data(key_name, key_data);
		mRes_Common.sDATA__B_Color__END = key_data;
	}
	// COLOR.ABORT ...
	{
		key_name = pKEY__DATA_T_COLOR_ABORT;
		p_obj_para_ctrl->Get_Constant_Data(key_name, key_data);
		mRes_Common.sDATA__T_Color__ABORT = key_data;

		key_name = pKEY__DATA_B_COLOR_ABORT;
		p_obj_para_ctrl->Get_Constant_Data(key_name, key_data);
		mRes_Common.sDATA__B_Color__ABORT = key_data;
	}

	// CFG : LLx ...
	{
		key_name = pKEY__DATA_LLx_SLOT_SIZE;
		p_obj_para_ctrl->Get_Constant_Data(key_name, key_data);
		iLLx__SLOT_SIZE = atoi(key_data);

		//
		key_name = pKEY__DATA_LLx_PIN_USE;
		p_obj_para_ctrl->Get_Constant_Data(key_name, key_data);

		if(key_data.CompareNoCase("YES") == 0)		bLLx__PIN_USE = TRUE;
		else										bLLx__PIN_USE = FALSE;
	}
	// CFG : PMx ...
	{
		key_name = pKEY__DATA_PMx_SIZE;
		p_obj_para_ctrl->Get_Constant_Data(key_name, key_data);
		iPMx__MD_SIZE = atoi(key_data);
	}
	// CFG : STx ...
	{
		key_name = pKEY__DATA_STx_SIZE;
		p_obj_para_ctrl->Get_Constant_Data(key_name, key_data);
		iSTx__MD_SIZE = atoi(key_data);
	}
	
	return 1;
}

int CDlg__PARTICLE_TABLE
::Set_MoveWindow(const POINT& p_st, const POINT& p_et)
{
	bool active__update_page = true;

	if(iREAL_MODE > 0)
	{
		if(!bActive__Init_Page)
		{
			bActive__Init_Page = true;
		}
		else
		{
			active__update_page = false;
		}
	}

	// ...
	int sx = p_st.x;
	int sy = p_st.y;
	int width  = p_et.x - p_st.x;
	int height = p_et.y - p_st.y;

	if(active__update_page)
	{
		m_mainTab.MoveWindow( 5, 5, width - 10, height - 10 );

		CRect rect_main;
		m_mainTab.GetClientRect(&rect_main);

		int y_offset = 25;

		// CDlg__PARTICLE_TABLE__TRANSFER_PART ...
		if(pDlg_subTab__Transfer_Part != NULL)
		{
			CDlg__PARTICLE_TABLE__TRANSFER_PART *p_dlg = pDlg_subTab__Transfer_Part;

			p_dlg->MoveWindow( 5, 25, rect_main.Width() - 10, rect_main.Height() - y_offset);

			CRect rect_table;
			p_dlg->GetClientRect(&rect_table);

			p_dlg->mTable_Transfer.MoveWindow( 0, 10, rect_table.Width() - 6, rect_table.Height() - 15);
		}

		// CDlg__PARTICLE_TABLE__PROCESS_PART ...
		if(pDlg_subTab__Process_Part != NULL)
		{
			CDlg__PARTICLE_TABLE__PROCESS_PART *p_dlg = pDlg_subTab__Process_Part;

			p_dlg->MoveWindow( 5, 25, rect_main.Width() - 10, rect_main.Height() - y_offset);

			CRect rect_table;
			p_dlg->GetClientRect(&rect_table);

			p_dlg->mTable_Process.MoveWindow( 0, 10, rect_table.Width() - 6, rect_table.Height() - 15);
		}
	}

	MoveWindow(sx,sy, width,height, true);
	ShowWindow(SW_SHOW);
	return 1;
}

int CDlg__PARTICLE_TABLE
::Redraw_Page()
{
	Invalidate(TRUE);
	return 1;
}


// ...
void CDlg__PARTICLE_TABLE::WM_Timer(const HWND& hwnd)
{
	if(m_pwndShow != NULL)
	{
		switch(iMainTAB_ID)
		{
			case _MainTAB_ID__TRANSFER_PART:	
				pDlg_subTab__Transfer_Part->WM_Timer(hwnd);
				break;

			case _MainTAB_ID__PROCESS_PART:	
				pDlg_subTab__Process_Part->WM_Timer(hwnd);
				break;
		}
	}
}

