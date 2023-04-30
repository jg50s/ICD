#include "stdafx.h"
#include "JGLEE__LOG_ANALYSIS.h"

#include "Dlg__PMx_Table.h"

#include "CObj__PMx_Table__KEY_DEF.h"


// ...
int CDlg__PMx_Table
::Set_Parameter(const int module_id)
{
	GObj__Parameter_Ctrl *p_para_ctrl = pGObj_Res->pGOBJ_PARA_CTRL;

	CString path_inf;
	CString dir_root;
	CString inf_file;

	// ...
	{
		CGX__SYSTEM_CTRL x_sys_ctrl;
		CString para_data;

		x_sys_ctrl->Get__GUI_DIR_EXE(dir_root);
		dir_root += "\\INCLUDE_FILE";
		dir_root += "\\";

		p_para_ctrl->Get_Constant_Data(pKEY__DATA_INF_DIR,  para_data);
		dir_root += para_data;

		p_para_ctrl->Get_Constant_Data(pKEY__DATA_INF_FILE, inf_file);
	}

	// ...
	{
		CString para_data;
		
		p_para_ctrl->Get_Constant_Data(pKEY__DATA_COL_WITH_NO, para_data);
		iData__Col_Width__NO = atoi(para_data);

		p_para_ctrl->Get_Constant_Data(pKEY__DATA_COL_WITH_NAME, para_data);
		iData__Col_Width__NAME = atoi(para_data);

		p_para_ctrl->Get_Constant_Data(pKEY__DATA_COL_WITH_DATA, para_data);
		iData__Col_Width__DATA = atoi(para_data);
		
		p_para_ctrl->Get_Constant_Data(pKEY__DATA_COL_WITH_CHANNEL, para_data);
		iData__Col_Width__CHANNEL = atoi(para_data);
	}

	// ...
	{
		CString key_name;
		CString str_data;

		for(int i=0; i<6; i++)
		{
			key_name.Format("DATA.PM%1d_USE", i+1);
			p_para_ctrl->Get_Constant_Data(key_name, str_data);

			if(str_data.CompareNoCase("YES") == 0)			bActive_PMx[i] = true;
			else											bActive_PMx[i] = false;

			//
			key_name.Format("DATA.PM%1d_NAME", i+1);
			p_para_ctrl->Get_Constant_Data(key_name, str_data);

			if(str_data.GetLength() > 0)		sPMx_NAME[i] = str_data;
			else								sPMx_NAME[i].Format("PM%1d", i+1);
		}
	}

	sFile_Info = inf_file;
	sDir_Info  = dir_root;

	// ...
	{
		mCls_Def.Clear();
		mCtrl_PMx.Clear();

		_Update__File_Info(sDir_Info,sFile_Info);
	}

	// ...
	{
		CStringArray l_channel;
		mCtrl_PMx.Get__ALL_CHANNEL_INFO(l_channel);

		p_para_ctrl->Make_Exe_Channel_List(l_channel);
	}

	if(bActive_Init)
	{
		CListCtrl* p_table = &mCtrl__PMx_Table;
		
		_Make__PMx_Table(p_table);
	}
	return 1;
}

int CDlg__PMx_Table
::Set_MoveWindow(const POINT& p_st, const POINT& p_et)
{
	if(!bActive_Init)
	{
		bActive_Init = true;

		// ...
		mReSize.Link_Dlg(this);

		mReSize.Link_ResID(IDC_LIST__PMx_TABLE);
		mReSize.Link_ResID(IDC_BTN__PM1);
		mReSize.Link_ResID(IDC_BTN__PM2);
		mReSize.Link_ResID(IDC_BTN__PM3);
		mReSize.Link_ResID(IDC_BTN__PM4);
		mReSize.Link_ResID(IDC_BTN__PM5);
		mReSize.Link_ResID(IDC_BTN__PM6);
		mReSize.Link_ResID(IDC_BTN__PMx);
		mReSize.Link_ResID(IDC_BTN__GOTO_MAINT);

		mReSize.Init_Position();
	}
	mReSize.Move_Position(p_st,p_et);

	// ...
	{
		mBtn__PM1.EnableWindow(FALSE);
		mBtn__PM2.EnableWindow(FALSE);
		mBtn__PM3.EnableWindow(FALSE);
		mBtn__PM4.EnableWindow(FALSE);
		mBtn__PM5.EnableWindow(FALSE);
		mBtn__PM6.EnableWindow(FALSE);
		mBtn__PMx.EnableWindow(TRUE);

		//
		int active__pm_id = -1;

		CUIntArray l_pm;
		mCtrl_PMx.Get__PMx_LIST(l_pm);

		int i_limit = l_pm.GetSize();
		int i;
	
		for(i=0; i<i_limit; i++)
		{
			int pm_i = l_pm[i];

			if(pm_i < 1)				continue;
			if(pm_i > 6)				continue;

				 if(pm_i == 1)			mBtn__PM1.SetWindowText(sPMx_NAME[i]);
			else if(pm_i == 2)			mBtn__PM2.SetWindowText(sPMx_NAME[i]);
			else if(pm_i == 3)			mBtn__PM3.SetWindowText(sPMx_NAME[i]);
			else if(pm_i == 4)			mBtn__PM4.SetWindowText(sPMx_NAME[i]);
			else if(pm_i == 5)			mBtn__PM5.SetWindowText(sPMx_NAME[i]);
			else if(pm_i == 6)			mBtn__PM6.SetWindowText(sPMx_NAME[i]);

			if(!bActive_PMx[pm_i-1])	continue;;

				 if(pm_i == 1)			mBtn__PM1.EnableWindow(TRUE);
			else if(pm_i == 2)			mBtn__PM2.EnableWindow(TRUE);
			else if(pm_i == 3)			mBtn__PM3.EnableWindow(TRUE);
			else if(pm_i == 4)			mBtn__PM4.EnableWindow(TRUE);
			else if(pm_i == 5)			mBtn__PM5.EnableWindow(TRUE);
			else if(pm_i == 6)			mBtn__PM6.EnableWindow(TRUE);

			if(active__pm_id < 0)		active__pm_id = pm_i;
		}

		if(iPMx_ID == 0)
		{
			if(active__pm_id > 0)
			{
				iPMx_ID = active__pm_id;

				_Change__PMx(iPMx_ID);
			}
		}
	}

	// ...
	{
		CFont font;
		font.CreateFont(21, 11, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, HANGUL_CHARSET, 0, 0, 0, VARIABLE_PITCH, "fixedsys");

		mBtn__PMx.SetFont(&font);
	}

	// ...
	{
		int sx = p_st.x;
		int sy = p_st.y;
		int wx = p_et.x - p_st.x;
		int wy = p_et.y - p_st.y;

		MoveWindow(sx,sy,wx,wy,true);
		ShowWindow(SW_SHOW);
	}
	return 1;
}
int CDlg__PMx_Table
::Redraw_Page()
{
	Invalidate(TRUE);
	return 1;
}


// ...
void CDlg__PMx_Table
::_Request__GOTO_MAINT_Of_PMx(const int pm_id)
{
	CString key_name;

		 if(pm_id == 1)			key_name = pKEY__CH_PM1_GOTO_MAINT;
	else if(pm_id == 2)			key_name = pKEY__CH_PM2_GOTO_MAINT;
	else if(pm_id == 3)			key_name = pKEY__CH_PM3_GOTO_MAINT;
	else if(pm_id == 4)			key_name = pKEY__CH_PM4_GOTO_MAINT;
	else if(pm_id == 5)			key_name = pKEY__CH_PM5_GOTO_MAINT;
	else if(pm_id == 6)			key_name = pKEY__CH_PM6_GOTO_MAINT;
	else						return;

	// ...
	GObj__Parameter_Ctrl *p_para_ctrl = pGObj_Res->pGOBJ_PARA_CTRL;

	p_para_ctrl->Set_Suffix_Feedback(key_name, "YES");
}
