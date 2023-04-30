#include "stdafx.h"
#include "JGLEE__LOG_ANALYSIS.h"

#include "Interface_Header.h"

#include "Dlg__Wafer_MDx_Sel.h"
#include "Macro_Function.h"

#include "CLS__Proc_Log.h"
#include "Dlg__File_Save.h"


// ...
void CDlg__Wafer_MDx_Sel::
_Upload__Log_Text(const CString& md_name, const CString& log_path)
{
	int eqp_id = -1;

	CString dir_md;
	CString temp_name;

	// ...
	int pm_id = MACRO__Get_PMx_ID(md_name);
	if(pm_id > 0)
	{
		eqp_id = pm_id + 1;
		dir_md.Format("PM%1d", pm_id);

		temp_name = _Get__Template_Name_Of_PMx(pm_id);
	}

	int ll_id = MACRO__Get_LLx_ID(md_name);
	if(ll_id > 0)
	{
		eqp_id = 1;
		dir_md.Format("LL%1d", ll_id);

		temp_name = _Get__Template_Name_Of_LLx(ll_id);
	}

	if(eqp_id > 0)
	{
		CGX__SYSTEM_CTRL x_sys_ctrl;
		CString dir_log;

		x_sys_ctrl->Get__SEQ_DIR_ROOT(eqp_id, dir_log);
		dir_log += "\\EQP_LOG\\Datalog";

		// ...
		CString file_name = MACRO__Get_File_Name(log_path);

		CString prc_path;
		if(ll_id > 0)		prc_path.Format("%s\\%s.d%1d", dir_log,log_path,ll_id);
		else				prc_path.Format("%s\\%s.d",    dir_log,log_path);

		/*
		CString inf_path;
		CString rcp_path;

		inf_path.Format("%s\\%s.rcp_inf", dir_log,log_path);
		rcp_path.Format("%s\\%s.rcp_log", dir_log,log_path);
		*/

		// ...
		/*
		CString bck_prc__path;
		CString bck_inf__path;
		CString bck_rcp__path;

		CString dir_path;

		// Backup ...
		{
			dir_path.Format("%s\\%s\\%s", sDir_Root,sDir_Lot,dir_md);
			CreateDirectory(dir_path, NULL);
		}

		// Process Log ...
		{
			bck_prc__path.Format("%s\\%s.d", dir_path,file_name);
		
			CopyFile(prc_path, bck_prc__path, TRUE);
		}
		// Recipe Inf ...
		{
			bck_inf__path.Format("%s\\%s.rcp_inf", dir_path,file_name);

			CopyFile(rcp_path, bck_inf__path, TRUE);
		}
		// Recipe Log ...
		{
			bck_rcp__path.Format("%s\\%s.rcp_log", dir_path,file_name);

			CopyFile(rcp_path, bck_rcp__path, TRUE);
		}
		*/

		// ...
		{
			CString dir_exe;
			x_sys_ctrl->Get__GUI_DIR_EXE(dir_exe);

			//
			CLS__Proc_Log x_log;
			x_log.Set__Dir_Root(dir_exe);
			
			x_log.bActive__CH_MIN = mCheck__STEP_MIN.GetCheck();
			x_log.bActive__CH_MAX = mCheck__STEP_MAX.GetCheck();
			x_log.bActive__CH_AVG = mCheck__STEP_AVG.GetCheck();

			CString temp_path;
			temp_path.Format("%s\\%s", dir_log,temp_name);
			if(x_log.Update__Template_File(m_hWnd, temp_path) < 0)							return;

			if(x_log.Make__Log_Txt_File(m_hWnd, prc_path, file_name,temp_name) < 0)			return;

			//			
			CX_PROGRAM_CONTROL x_program;
			x_program->Start_Program(dir_exe, "JGLEE__Process_Log_View");
		}
	}
}

void CDlg__Wafer_MDx_Sel::
_Upload__Log_CSV(const CString& md_name, const CString& log_path)
{
	int eqp_id = -1;

	CString dir_md;
	CString temp_name;

	// ...
	int pm_id = MACRO__Get_PMx_ID(md_name);
	if(pm_id > 0)
	{
		eqp_id = pm_id + 1;
		dir_md.Format("PM%1d", pm_id);

		temp_name = _Get__Template_Name_Of_PMx(pm_id);
	}

	int ll_id = MACRO__Get_LLx_ID(md_name);
	if(ll_id > 0)
	{
		eqp_id = 1;
		dir_md.Format("LL%1d", ll_id);

		temp_name = _Get__Template_Name_Of_LLx(ll_id);
	}

	if(eqp_id > 0)
	{
		CDlg__File_Save dlg_save;

		if(dlg_save.DoModal() != IDOK)
		{
			return;
		}

		CString dir_output = dlg_save.sPara__SEL_DIR;
		bool active__left_align = true;
		
		if((dlg_save.bActive__ALIGN_LEFT) 
		&& (!dlg_save.bActive__ALIGN_RIGHT))
		{
			active__left_align = true;
		}

		// ...
		CGX__SYSTEM_CTRL x_sys_ctrl;
		CString dir_log;

		x_sys_ctrl->Get__SEQ_DIR_ROOT(eqp_id, dir_log);
		dir_log += "\\EQP_LOG\\Datalog";

		// ...
		CString prc_path;

		if(ll_id > 0)		prc_path.Format("%s\\%s.d%1d", dir_log,log_path,ll_id);
		else				prc_path.Format("%s\\%s.d",    dir_log,log_path);

		// ...
		CString path_output;
		CString file_name = MACRO__Get_File_Name(log_path);

		// Process Log ...
		{
			path_output.Format("%s\\%s.csv", dir_output,file_name);
		}

		// ...
		{
			CLS__Proc_Log x_log;

			x_log.bActive__CH_MIN = mCheck__STEP_MIN.GetCheck();
			x_log.bActive__CH_MAX = mCheck__STEP_MAX.GetCheck();
			x_log.bActive__CH_AVG = mCheck__STEP_AVG.GetCheck();

			CString temp_path;
			temp_path.Format("%s\\%s", dir_log,temp_name);
			if(x_log.Update__Template_File(m_hWnd, temp_path) < 0)			return;

			if(x_log.Make__Log_Csv_File(m_hWnd, prc_path,file_name,temp_name, path_output,active__left_align) < 0)
			{
				return;
			}
		}
	}
}

CString CDlg__Wafer_MDx_Sel::
_Get__Template_Name_Of_PMx(const int pm_id)
{
	CString temp_name;

	if(pm_id == 1)		mBtn__Template_Name_PM1.GetWindowText(temp_name);
	if(pm_id == 2)		mBtn__Template_Name_PM2.GetWindowText(temp_name);
	if(pm_id == 3)		mBtn__Template_Name_PM3.GetWindowText(temp_name);
	if(pm_id == 4)		mBtn__Template_Name_PM4.GetWindowText(temp_name);
	if(pm_id == 5)		mBtn__Template_Name_PM5.GetWindowText(temp_name);
	if(pm_id == 6)		mBtn__Template_Name_PM6.GetWindowText(temp_name);

	return temp_name;
}
CString CDlg__Wafer_MDx_Sel::
_Get__Template_Name_Of_LLx(const int ll_id)
{
	CString temp_name;

	if(ll_id == 1)		mBtn__Template_Name_LL1.GetWindowText(temp_name);
	if(ll_id == 2)		mBtn__Template_Name_LL2.GetWindowText(temp_name);

	return temp_name;
}
