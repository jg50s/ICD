#include "stdafx.h"
#include "JGLEE__LOG_ANALYSIS.h"

#include "Interface_Header.h"

#include "Dlg__Wafer_MDx_Sel.h"
#include "Macro_Function.h"

#include "CLS__Proc_Log.h"
#include "Dlg__Wafer_Proc_Chart.h"


// ...
void CDlg__Wafer_MDx_Sel::
_Upload__Log_Graph(const CString& md_name, const CString& log_path)
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

		if(pm_id == 1)		mBtn__Template_Name_PM1.GetWindowText(temp_name);
		if(pm_id == 2)		mBtn__Template_Name_PM2.GetWindowText(temp_name);
		if(pm_id == 3)		mBtn__Template_Name_PM3.GetWindowText(temp_name);
		if(pm_id == 4)		mBtn__Template_Name_PM4.GetWindowText(temp_name);
		if(pm_id == 5)		mBtn__Template_Name_PM5.GetWindowText(temp_name);
		if(pm_id == 6)		mBtn__Template_Name_PM6.GetWindowText(temp_name);
	}

	int ll_id = MACRO__Get_LLx_ID(md_name);
	if(ll_id > 0)
	{
		eqp_id = 1;
		dir_md.Format("LL%1d", ll_id);

		if(ll_id == 1)		mBtn__Template_Name_LL1.GetWindowText(temp_name);
		if(ll_id == 2)		mBtn__Template_Name_LL2.GetWindowText(temp_name);
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
		else				prc_path.Format("%s\\%s.d", dir_log,log_path);

		CString inf_path;
		CString rcp_path;

		inf_path.Format("%s\\%s.rcp_inf", dir_log,log_path);
		rcp_path.Format("%s\\%s.rcp_log", dir_log,log_path);

		printf("prc_path <- [%s] \n", prc_path);
		printf("inf_path <- [%s] \n", inf_path);
		printf("rcp_path <- [%s] \n", rcp_path);

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

			printf(" * process_path \n");
			printf("  <- [%s] \n", bck_prc__path);

			CopyFile(prc_path, bck_prc__path, TRUE);
		}

		// Recipe Inf ...
		{
			bck_inf__path.Format("%s\\%s.rcp_inf", dir_path,file_name);

			printf(" * rcp_inf_path \n");
			printf("  <- [%s] \n", bck_inf__path);

			CopyFile(rcp_path, bck_inf__path, TRUE);
		}
		// Recipe Log ...
		{
			bck_rcp__path.Format("%s\\%s.rcp_log", dir_path,file_name);

			printf(" * rcp_log_path \n");
			printf("  <- [%s] \n", bck_rcp__path);

			CopyFile(rcp_path, bck_rcp__path, TRUE);
		}
		*/

		// ...
		{
			CString dir_exe;
			x_sys_ctrl->Get__GUI_DIR_EXE(dir_exe);

			//
			CLS__Proc_Log x_log;
			CString temp_path;

			x_log.Set__Dir_Root(dir_exe);
			x_log.Set_Template___Only_Analog();

			//
			temp_path.Format("%s\\%s", dir_log,temp_name);
			if(x_log.Update__Template_File(m_hWnd, temp_path) < 0)				return;

			if(x_log.Upload__Proc_Data_Of_Log_File(m_hWnd, prc_path) < 0)		return;

			//
			CDlg__Wafer_Proc_Chart dlg;

			dlg.pLog_Proc = &x_log;

			dlg.DoModal();
		}
	}
}
