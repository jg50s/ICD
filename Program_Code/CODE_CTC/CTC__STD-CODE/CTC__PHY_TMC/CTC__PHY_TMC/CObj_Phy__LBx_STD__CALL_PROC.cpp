#include "StdAfx.h"
#include "CObj_Phy__LBx_STD.h"
#include "CObj_Phy__LBx_STD__DEF.h"

#include "Macro_Function.h"


// ...
int  CObj_Phy__LBx_STD
::Call__PROC_MAIN(CII_OBJECT__VARIABLE* p_variable,
				   CII_OBJECT__ALARM* p_alarm)
{
	_Start__Wafer_Log();

	int flag = _Fnc__PROC_MAIN(p_variable,p_alarm);

	_Process_Report__Wafer_Info();
	return flag;
}
int  CObj_Phy__LBx_STD
::_Fnc__PROC_MAIN(CII_OBJECT__VARIABLE* p_variable,
				  CII_OBJECT__ALARM* p_alarm)
{
	// PRCO_READY ...
	{
		CString cmmd_proc = _CMMD__PROC_READY;

		int r_flag = Fnc__MODULE_OBJ(p_variable,p_alarm, cmmd_proc);
		if(r_flag < 0)		return r_flag;
	}
	// PROC_START ...
	{
		CString cmmd_proc = _CMMD__PROC_START;

		int r_flag = Fnc__MODULE_OBJ(p_variable,p_alarm, cmmd_proc);
		if(r_flag < 0)		return r_flag;
	}

	return 1;
}

void CObj_Phy__LBx_STD
::_Start__Wafer_Log()
{
	IDS__SCH_MATERIAL_INFO db_info;			

	// ...
	{
		CString sch_name = sCH__PARA_PROC_SCH_NAME->Get__STRING();

		if(xI_SCH_MATERIAL_CTRL->Get__MATERIAL_INFO(sch_name, db_info) < 0)
		{
			return;
		}
	}

	// ...
	CString dir_sub;
	CString log_file;

	// ...
	{
		CString str_date;
		CString str_time;

		Macro__Get_DateTime(str_date, str_time);

		dir_sub.Format("%s\\%s\\", str_date,db_info.sLOT_ID);
		log_file.Format("%s_%1d_%s", db_info.sLOT_ID, db_info.iSRC__STN, str_time);
	}

	// ...
	{
		xCH__LOG_SUB_DIRECTORY->Set__DATA(dir_sub);
		xCH__LOG_FILE_NAME->Set__DATA(log_file);

		CString wfr_log;
		wfr_log.Format("%s%s", dir_sub,log_file);
		xCH__WFR_LOG_INFO->Set__DATA(wfr_log);
	}
}

void CObj_Phy__LBx_STD
::_Process_Report__Wafer_Info()
{
	CString file_date;

	// ...
	{
		SYSTEMTIME file__sys_time;
		GetLocalTime(&file__sys_time);

		file_date.Format("%04d_%02d_%02d",		
						 file__sys_time.wYear,
						 file__sys_time.wMonth,
						 file__sys_time.wDay);
	}

	int ll_id = Macro__LLx_ID(sSCH_NAME);

	for(int i=0; i<CFG_LBx__SLOT_MAX; i++)
	{
		int ll_slot = i + 1;

		if(xCH__SLOT_STATUS[i]->Check__DATA(STR__NONE) > 0)
		{
			continue;
		}

		// ...
		IDS__SCH_MATERIAL_INFO ds_info;

		CString sch_name;
		sch_name.Format("%s-%1d", sSCH_NAME,ll_slot);

		if(xI_SCH_MATERIAL_CTRL->Get__MATERIAL_INFO(sch_name, ds_info) < 0)
		{
			continue;
		}

		// ...
		int lp_id   = ds_info.iSRC__PTN;
		int lp_slot = ds_info.iSRC__STN;

		// ...
		CString log_msg;

		// ...
		{
			CString log_bff;

			log_msg  = "\n";
			log_msg += "#ACT.START!";
			log_msg += "\n";

			log_bff.Format("#ACT=%s\n", "PROCESS");
			log_msg += log_bff;

			log_bff.Format("#MD=LL%1d-%1d\n",  ll_id,ll_slot);
			log_msg += log_bff;

			log_bff.Format("#RT_OFFSET=%s\n", sCH__FDC_DA_RT_OFFSET->Get__STRING());
			log_msg += log_bff;

			log_bff.Format("#RECIPE=%s\n", ds_info.sCUR_RECIPE);
			log_msg += log_bff;

			log_bff.Format("#LOG=%s\n", xCH__WFR_LOG_INFO->Get__STRING());
			log_msg += log_bff;

			log_bff.Format("#TIME.ACT=%s\n", sCH__TIME_ACT_TACK->Get__STRING());
			log_msg += log_bff;

			log_bff.Format("#TIME.START=%s\n", sCH__TIME_ACT_START->Get__STRING());
			log_msg += log_bff;

			log_bff.Format("#TIME.END=%s\n", sCH__TIME_ACT_END->Get__STRING());
			log_msg += log_bff;

			log_bff.Format("#RESULT=%s\n", sCH__TIME_ACT_RESULT->Get__STRING());
			log_msg += log_bff;

			log_msg += "#ACT.END!";
			log_msg += "\n";
		}

		// ...
		{
			SCX__FILE_CTRL x_file_ctrl;
			x_file_ctrl->DISABLE__TIME_LOG();

			//
			CString ref_root;

			ref_root  = sDir_ROOT;
			ref_root += "\\EQP_LOG";
			x_file_ctrl->Create__LOG_DIR(ref_root);

			ref_root += "\\Wafer_Data";
			x_file_ctrl->Create__LOG_DIR(ref_root);

			//
			CString dir_date_lot;
			xI_SCH_MATERIAL_CTRL->Get__DIR_JOB_LOG(lp_id, dir_date_lot);

			ref_root += dir_date_lot;

			//
			CString file_path;
			file_path.Format("%s\\P%1d_%1d.wfr", ref_root,lp_id,lp_slot);		

			x_file_ctrl->Write__LOG_MSG(file_path, log_msg);
		}
	}
}

int  CObj_Phy__LBx_STD
::Call__PROC_PRE(CII_OBJECT__VARIABLE* p_variable,
				 CII_OBJECT__ALARM* p_alarm)
{
	// PRE_READY ...
	{
		CString cmmd_proc = _CMMD__PRE_READY;

		int r_flag = Fnc__MODULE_OBJ(p_variable,p_alarm, cmmd_proc);
		if(r_flag < 0)		return r_flag;
	}
	// PRE_START ...
	{
		CString cmmd_proc = _CMMD__PRE_START;

		int r_flag = Fnc__MODULE_OBJ(p_variable,p_alarm, cmmd_proc);
		if(r_flag < 0)		return r_flag;
	}

	return 1;
}

int  CObj_Phy__LBx_STD
::Call__PROC_POST(CII_OBJECT__VARIABLE* p_variable,
				  CII_OBJECT__ALARM* p_alarm)
{
	// POST_READY ...
	{
		CString cmmd_proc = _CMMD__CLN_READY;

		int r_flag = Fnc__MODULE_OBJ(p_variable,p_alarm, cmmd_proc);
		if(r_flag < 0)		return r_flag;
	}
	// POST_START ...
	{
		CString cmmd_proc = _CMMD__CLN_START;

		int r_flag = Fnc__MODULE_OBJ(p_variable,p_alarm, cmmd_proc);
		if(r_flag < 0)		return r_flag;
	}

	return 1;
}

int  CObj_Phy__LBx_STD
::Call__PROC_MAINT(CII_OBJECT__VARIABLE* p_variable,
				  CII_OBJECT__ALARM* p_alarm)
{
	if(Call__PUMP(p_variable, p_alarm) < 0)
	{
		return -11;
	}

	// MAINT_READY ...
	{
		CString cmmd_proc = _CMMD__MNT_READY;

		int r_flag = Fnc__MODULE_OBJ(p_variable,p_alarm, cmmd_proc);
		if(r_flag < 0)		return r_flag;
	}
	// MAINT_START ...
	{
		CString cmmd_proc = _CMMD__MNT_START;

		return Fnc__MODULE_OBJ(p_variable,p_alarm, cmmd_proc);
	}

	return 1;
}
