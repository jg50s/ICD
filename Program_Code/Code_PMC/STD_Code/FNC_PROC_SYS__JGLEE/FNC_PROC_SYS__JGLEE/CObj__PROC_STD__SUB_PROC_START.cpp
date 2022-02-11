#include "StdAfx.h"
#include "CObj__PROC_STD.h"

#include "Macro_Function.h"


// ...
int CObj__PROC_STD::
Sub__PROC_START(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm)
{
	int restart_count = 0;

LOOP_RESTART:

	// ...
	{
		_Make__PROC_LOG(restart_count);

		sCH__ACT_RECOVERY_RESTART_FLAG->Set__DATA("");
	}

	int r_flag = pOBJ_CTRL__STEP->Call__OBJECT(_STEP_CMD__START);

	if(sCH__ACT_RECOVERY_RESTART_FLAG->Check__DATA(STR__YES) > 0)
	{		
		xI_LOG_CTRL->WRITE__LOG("Recovery Restart - PROC_READY() Starting !!!");

		if(Fnc__PROC_READY(p_variable, p_alarm) < 0)
		{
			xI_LOG_CTRL->WRITE__LOG("Recovery Restart - PROC_READY() Aborted !!!");

			sCH__ACT_RECOVERY_RESTART_FLAG->Set__DATA("");
			return -1;
		}

		xI_LOG_CTRL->WRITE__LOG("Recovery Restart - PROC_READY() Completed !!!");

		restart_count++;
		goto LOOP_RESTART;
	}

	return r_flag;
}

int CObj__PROC_STD::
_Make__PROC_LOG(const int restart_count)
{
	CString str__lotid  = sEXT_CH__SLOT01_LOTID->Get__STRING();
	CString str__slotid = sEXT_CH__SLOT01_SLOTID->Get__STRING();

	printf(" * _Make__PROC_LOG() ... \n");
	printf(" -> restart_count <- %1d \n", restart_count);
	printf(" -> str__lotid  <- %s \n", str__lotid);
	printf(" -> str__slotid <- %s \n", str__slotid);
	printf("\n");

	if(restart_count > 0)
	{
		if(str__lotid.GetLength() > 0)
		{
			CString sub_dir;
			CString file;
			CString date;
			CString time;

			Macro__Get_DateTime(date,time);

			// ...
			{
				sub_dir  = date;
				sub_dir += "\\";
				sub_dir += str__lotid;
				sub_dir += "\\";

				sEXT_CH__PROC_LOG__SUB_DIR->Set__DATA(sub_dir);
			}

			// ...
			{
				file.Format("RESTART%1d-", restart_count);
				file += str__lotid;
				file += "_";	
				file += str__slotid;
				file += "-";
				file += time;

				sEXT_CH__PROC_LOG__FILE_NAME->Set__DATA(file);
			}
		}
		return 1;
	}

	if(dCH__CUR_PROCESS_TYPE->Check__DATA(STR__MANUAL) < 0)
	{
		return 1;
	}

	if(str__lotid.GetLength() > 0)
	{
		CString sub_dir;
		CString file;
		CString date;
		CString time;
				
		Macro__Get_DateTime(date, time);
				
		// ...
		{
			sub_dir  = date;
			sub_dir += "\\";
			sub_dir += str__lotid;
			sub_dir += "\\";
					
			sEXT_CH__PROC_LOG__SUB_DIR->Set__DATA(sub_dir);
		}
				
		// ...
		{
			file  = "RETRY-";
			file += str__lotid;
			file += "_";	
			file += str__slotid;
			file += "-";
			file += time;
					
			sEXT_CH__PROC_LOG__FILE_NAME->Set__DATA(file);
		}

		return 1;
	}

	// ...
	{
		CString sub_dir;
		CString file;
		CString date;
		CString time;

		Macro__Get_DateTime(date,time);

		// ...
		{
			sub_dir  = date;
			sub_dir += "\\";
			sub_dir += "MNT";
			sub_dir += "\\";

			sEXT_CH__PROC_LOG__SUB_DIR->Set__DATA(sub_dir);
		}

		printf(" -> sub_dir <- %s \n", sub_dir);

		// ...
		{
			file  = "MANUAL-";
			file += str__slotid;
			file += "-";
			file += time;

			sEXT_CH__PROC_LOG__FILE_NAME->Set__DATA(file);
		}

		printf(" -> file <- %s \n", file);
	}

	printf("\n");
	return 1;
}
