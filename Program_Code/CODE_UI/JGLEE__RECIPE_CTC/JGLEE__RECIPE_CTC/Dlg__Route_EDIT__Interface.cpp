#include "stdafx.h"
#include "Dlg__Route_EDIT.h"
#include "Dlg__Route_EDIT__Def.h"

#include "CObj__Route_EDIT__KEY_DEF.h"


// ...
int CDlg__Route_EDIT
::Set_Parameter(const int module_id)
{
	GObj__Parameter_Ctrl *p_para_ctrl = pGObj_Res->pGOBJ_PARA_CTRL;

	CString key_name;
	CString str_data;
	int i;

	// ...
	{
		// PMx ...
		{
			p_para_ctrl->Get_Constant_Data(pKEY__DATA_PM_SIZE, str_data);
			iPMx_SIZE = atoi(str_data);
			if(iPMx_SIZE > _DEF_PMx__MAX)			iPMx_SIZE = _DEF_PMx__MAX;
		}

		// STx ...
		{
			p_para_ctrl->Get_Constant_Data(pKEY__DATA_ST_SIZE, str_data);
			iSTx_SIZE = atoi(str_data);
			if(iSTx_SIZE > _DEF_STx__MAX)			iSTx_SIZE = _DEF_STx__MAX;
		}

		// RCP ...
		{
			p_para_ctrl->Get_Constant_Data(pKEY__DATA_PRE_SUB_DIR,  str_data);
			sData__RCP_PRE = str_data;

			p_para_ctrl->Get_Constant_Data(pKEY__DATA_MAIN_SUB_DIR, str_data);
			sData__RCP_MAIN = str_data;

			p_para_ctrl->Get_Constant_Data(pKEY__DATA_POST_SUB_DIR, str_data);
			sData__RCP_POST = str_data;
		}

		// LOOPx_PROC ...
		{
			p_para_ctrl->Get_Constant_Data(pKEY__DATA_LOOPx_PROC_ACTIVE, str_data);
			if(str_data.CompareNoCase(STR__YES) == 0)			bActive__LOOPx_PROC = true;
			else												bActive__LOOPx_PROC = false;
		}

		// LLx_COMMON ...
		{
			p_para_ctrl->Get_Constant_Data(pKEY__DATA_LLx_MODE, str_data);

			if(str_data.CompareNoCase(STR__ONLY_MODE) == 0)			iLLx_MODE = _LLx_MODE__ONLY;
			else													iLLx_MODE = _LLx_MODE__ALL;
		}
		// LLx_IN ...
		{
			p_para_ctrl->Get_Constant_Data(pKEY__DATA_LLx_IN_SIZE, str_data);
			iSIZE__LLx_IN = atoi(str_data);
			if(iSIZE__LLx_IN > _LLx__MAX)		iSIZE__LLx_IN = _LLx__MAX;

			for(i=0; i<_LLx__MAX; i++)
			{
				bACTIVE__LLx_IN[i] = false;
			}
			for(i=0; i<iSIZE__LLx_IN; i++)
			{
				key_name.Format(pKEY__DATA_LLx_IN_ACTIVE_X, i+1);
				p_para_ctrl->Get_Constant_Data(key_name, str_data);

				if(str_data.CompareNoCase(STR__YES) == 0)			bACTIVE__LLx_IN[i] = true;
			}
		}
		// LLx_OUT ...
		{
			p_para_ctrl->Get_Constant_Data(pKEY__DATA_LLx_OUT_SIZE, str_data);
			iSIZE__LLx_OUT = atoi(str_data);
			if(iSIZE__LLx_OUT > _LLx__MAX)		iSIZE__LLx_OUT = _LLx__MAX;

			for(i=0; i<_LLx__MAX; i++)
			{
				bACTIVE__LLx_OUT[i] = false;
			}
			for(i=0; i<iSIZE__LLx_OUT; i++)
			{
				key_name.Format(pKEY__DATA_LLx_OUT_ACTIVE_X, i+1);
				p_para_ctrl->Get_Constant_Data(key_name, str_data);

				if(str_data.CompareNoCase(STR__YES) == 0)			bACTIVE__LLx_OUT[i] = true;
			}
		}

		// LLx_PROC ...
		{
			p_para_ctrl->Get_Constant_Data(pKEY__DATA_LLx_PROC_ACTIVE, str_data);
			if(str_data.CompareNoCase(STR__YES) == 0)			bActive__LLx_PROC = true;
			else												bActive__LLx_PROC = false;

			p_para_ctrl->Get_Constant_Data(pKEY__DATA_LLx_PROC_SIZE, str_data);
			iSIZE__ACTIVE_LLx_PROC = atoi(str_data);
			if(iSIZE__ACTIVE_LLx_PROC > _LLx__MAX)		iSIZE__ACTIVE_LLx_PROC = _LLx__MAX;

			for(i=0; i<_LLx__MAX; i++)
			{
				bACTIVE__ACTIVE_LLx_PROC[i] = false;
			}
			for(i=0; i<iSIZE__ACTIVE_LLx_PROC; i++)
			{
				key_name.Format(pKEY__DATA_LLx_PROC_ACTIVE_X, i+1);
				p_para_ctrl->Get_Constant_Data(key_name, str_data);

				if(str_data.CompareNoCase(STR__YES) == 0)			bACTIVE__ACTIVE_LLx_PROC[i] = true;
			}
		}
	}

	// ...
	{
		key_name = pKEY__DATA_DEFAULT_AL1_CONTROL_TYPE;
		p_para_ctrl->Get_Constant_Data(key_name, str_data);
		if(str_data.CompareNoCase(STR__CONFIG) == 0)		bACTIVE_DEFAULT__AL1_CTRL_CFG = true;
		else												bACTIVE_DEFAULT__AL1_CTRL_CFG = false;

		key_name = pKEY__DATA_DEFAULT_AL1_SLOT_TYPE;
		p_para_ctrl->Get_Constant_Data(key_name, str_data);
		if(str_data.CompareNoCase(STR__FIXED) == 0)			bACTIVE_DEFAULT__AL1_SLOT_FIXED = true;
		else												bACTIVE_DEFAULT__AL1_SLOT_FIXED = false;

		//
		key_name = pKEY__DATA_DEFAULT_AL1_SLOT01_ACTIVE;
		p_para_ctrl->Get_Constant_Data(key_name, str_data);
		if(str_data.CompareNoCase(STR__YES) == 0)			bACTIVE_DEFAULT__AL1_SLOT01 = true;
		else												bACTIVE_DEFAULT__AL1_SLOT01 = false;

		key_name = pKEY__DATA_DEFAULT_AL1_SLOT02_ACTIVE;
		p_para_ctrl->Get_Constant_Data(key_name, str_data);
		if(str_data.CompareNoCase(STR__YES) == 0)			bACTIVE_DEFAULT__AL1_SLOT02 = true;
		else												bACTIVE_DEFAULT__AL1_SLOT02 = false;
	}
	// ...
	{
		key_name = pKEY__DATA_DEFAULT_LLx_SLOT_TYPE;
		p_para_ctrl->Get_Constant_Data(key_name, str_data);
		if(str_data.CompareNoCase(STR__FIXED) == 0)			bACTIVE_DEFAULT__LLx_SLOT_FIXED = true;
		else												bACTIVE_DEFAULT__LLx_SLOT_FIXED = false;

		//
		int i_limit = _LLx__MAX;
		for(i=0; i<i_limit; i++)
		{
			key_name.Format(pKEY__DATA_DEFAULT_LLX_SLOT01_ACTIVE, i+1);
			p_para_ctrl->Get_Constant_Data(key_name, str_data);
			if(str_data.CompareNoCase(STR__YES) == 0)			bACTIVE_DEFAULT__LLx_SLOT01[i] = true;
			else												bACTIVE_DEFAULT__LLx_SLOT01[i] = false;

			key_name.Format(pKEY__DATA_DEFAULT_LLX_SLOT02_ACTIVE, i+1);
			p_para_ctrl->Get_Constant_Data(key_name, str_data);
			if(str_data.CompareNoCase(STR__YES) == 0)			bACTIVE_DEFAULT__LLx_SLOT02[i] = true;
			else												bACTIVE_DEFAULT__LLx_SLOT02[i] = false;
		}
	}

	// LLx_OUT : INFO ...
	{
		key_name = pKEY__DATA_LLx_OUT_COOLING_ACTIVE;
		p_para_ctrl->Get_Constant_Data(key_name, str_data);

		if(str_data.CompareNoCase(STR__YES) == 0)			bACTIVE__LLx_OUT_COOLING = true;
		else												bACTIVE__LLx_OUT_COOLING = false;
	}

	// STx PARA ...
	{
		key_name = pKEY__DATA_STx_N2_PURGE_ACTIVE;
		p_para_ctrl->Get_Constant_Data(key_name, str_data);

		if(str_data.CompareNoCase(STR__YES) == 0)			bACTIVE__STx_N2_PURGE = true;
		else												bACTIVE__STx_N2_PURGE = false;
	}

	return 1;
}

int CDlg__Route_EDIT
::Set_MoveWindow(const POINT& p_st, const POINT& p_et)
{
	int sx = p_st.x;
	int sy = p_st.y;
	int wx = p_et.x - p_st.x;
	int wy = p_et.y - p_st.y;

	// ...
	{
		mBtn__Route_New.Set_Position(&wndTop, SWP_SHOWWINDOW);
		mBtn__Route_Undo.Set_Position(&wndTop, SWP_SHOWWINDOW);

		mBtn__Route_Save.Set_Position(&wndTop, SWP_SHOWWINDOW);
		mBtn__Route_SaveAs.Set_Position(&wndTop, SWP_SHOWWINDOW);
		mBtn__Route_Delete.Set_Position(&wndTop, SWP_SHOWWINDOW);
	}

	if(iREAL_MODE < 0)
	{
		mBtn__Route_New.Draw__Active_State();
		mBtn__Route_Undo.Draw__Active_State();
		
		mBtn__Route_Save.Draw__Active_State();
		mBtn__Route_SaveAs.Draw__Active_State();
		mBtn__Route_Delete.Draw__Active_State();
	}
	else
	{
		mBtn__Route_New.Draw__Buttn_State();
		mBtn__Route_Undo.Draw__Buttn_State();
		
		mBtn__Route_Save.Draw__Buttn_State();
		mBtn__Route_SaveAs.Draw__Buttn_State();
		mBtn__Route_Delete.Draw__Buttn_State();
	}

	// ...
	{
		bool active_check = true;

		while((iShow_Count < 2) || (active_check))
		{
			iShow_Count++;
			active_check = false;

			//
			CString key_name;
			CString str_data;

			for(int i=0; i<iPMx_SIZE; i++)
			{
				int pm_id = i + 1;
				key_name.Format(pKEY__CH_CFG_NAME_PM_X, pm_id);
				pGObj_Res->pGOBJ_PARA_CTRL->Get_Channel_Data(key_name, str_data);
	
				CString pm_name = "";
				if(str_data.GetLength() > 0)		pm_name = str_data;

				sPMx_NAME[i] = pm_name;
				mDB__PMx_TREE_CTRL.Change_NAME(pm_id, pm_name);
			}
		}

		CDragDropTreeCtrl *p_tree = &mTree__Module_List;
		mDB__PMx_TREE_CTRL.Update_INFO(p_tree);
	}

	MoveWindow(sx,sy,wx,wy,true);
	ShowWindow(SW_SHOW);
	return 1;
}
int CDlg__Route_EDIT
::Redraw_Page()
{
	Invalidate(TRUE);
	return 1;
}

