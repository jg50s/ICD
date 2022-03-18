#include "StdAfx.h"
#include "CObj__PROC_STD.h"


// ...
int CObj__PROC_STD
::Sub__PROC_READY(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm, const bool active_dechuck)
{
	CString obj_msg;

	obj_msg = "Process Ready - Start ...";
	sCH__OBJ_MSG->Set__DATA(obj_msg);

	// ...
	{
		sCH__PRC_TOTAL_TIME->Set__DATA("");
		sCH__PRC_CUR_TIME->Set__DATA("");

		aCH__STEP_TOTAL_NUM->Set__DATA("");
		aCH__STEP_CUR_NUM->Set__DATA("");

		//
		aCH__RCP_LOOP_START->Set__VALUE(0.0);
		aCH__RCP_LOOP_REPEAT->Set__VALUE(0.0);
	}

	// ...
	{
		int r_flag = _Fnc__RCP_UPLOAD(p_variable, p_alarm, active_dechuck);
		if(r_flag < 0)			return r_flag;
	}

	// Total Step Time Check .....
	{
		CString ch_data;

		double total_time = 0.0;
		int step_count = 0;

		while(1)
		{
			int r_flag = xRCP__FILE_CTRL->Read__MEM();
			if(r_flag < 0)		break;

			if(r_flag > 0)
			{
				step_count++;

				double step_time = aEXT_CH__RCP_STEP_TIME->Get__VALUE();
				total_time += step_time;
			}

			if(p_variable->Check__CTRL_ABORT() > 0)
			{
				return -21;
			}
		}

		ch_data.Format("%.0f", total_time);
		sCH__PRC_TOTAL_TIME->Set__DATA(ch_data);
		sCH__PRC_TOTAL_TIME_TO_CTC->Set__DATA(ch_data);
		sEXT_CH__PRC_TOTAL_TIME_TO_CTC->Set__DATA(ch_data);

		aCH__STEP_TOTAL_NUM->Set__VALUE(step_count);

		xRCP__FILE_CTRL->Jump__STEP_NO(1);
	}

	return pOBJ_CTRL__STEP->Call__OBJECT(_STEP_CMD__READY);
}


int CObj__PROC_STD
::_Fnc__RCP_UPLOAD(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm, const bool active_dechuck)
{
	CString rcp_path;
	CString rcp_name;

LOOP_START:

	if(active_dechuck)
	{
		sEXT_CH__CFG_DECHUCK_RECIPE_ABORT->Get__DATA(rcp_name);

		rcp_path.Format("%s%s.rcp", sDir_PROC,rcp_name);
		sCH__CUR_RCP_FILE_PATH->Set__DATA(rcp_path);
	}
	else
	{
		sEXT_CH__RCP_NAME->Get__DATA(rcp_name);

		rcp_path.Format("%s%s.rcp", sDir_PROC,rcp_name);
		sCH__CUR_RCP_FILE_PATH->Set__DATA(rcp_path);
	}

	// ...
	{
		CString log_msg;

		log_msg.Format("RCP Name: %s\n", rcp_name);
		xI_LOG_CTRL->WRITE__LOG(log_msg);
	}

	// Recipe Check ...
	{
		xRCP__FILE_CTRL->Clear__APC_INFO();
		xRCP__FILE_CTRL->Free__MEM();

		if(xRCP__FILE_CTRL->Upload__FILE(rcp_path) < 0)
		{
			int alarm_id = ALID__PROCESS_RECIPE_NOT_EXIST;

			CString log_msg;
			CString r_act;

			log_msg.Format("The \"%s\" recipe file does not exist.\n", rcp_path);
			xI_LOG_CTRL->WRITE__LOG(log_msg);

			p_alarm->Popup__ALARM_With_MESSAGE(alarm_id,log_msg,r_act);

			log_msg.Format("Alarm Recovery : [%s]",r_act);
			xI_LOG_CTRL->WRITE__LOG(log_msg);

			if(r_act.CompareNoCase(ACT__RETRY) == 0)
			{
				goto LOOP_START;
			}
			return -11;
		}

		// ...
		int ref_item_num;
		int err_step;
		int err_item_num;
		CUIntArray l_step_item;

		if(xRCP__FILE_CTRL->Check__STEP_ITEM_CHECK(ref_item_num, err_step,err_item_num,l_step_item) < 0)
		{
			int alarm_id = ALID__RECIPE_STEP_SIZE_ERROR;

			CString log_msg;
			CString log_bff;
			CString r_act;

			// ...
			{
				log_bff.Format("Reference item number is %1d. \n", ref_item_num);
				log_msg += log_bff;

				log_bff.Format("Error step ID : %1d. \n", err_step);
				log_msg += log_bff;

				log_bff.Format("Error item number : %1d \n", err_item_num);
				log_msg += log_bff;

				// ...
				int i_limit = l_step_item.GetSize();
				int i;

				for(i=0; i<i_limit; i++)
				{
					log_bff.Format("Step%1d [%1d], ", i+1,l_step_item[i]);
					log_msg += log_bff;

					if((i % 10) == 9)
					{
						log_msg += "\n";
					}
				}
			}

			p_alarm->Popup__ALARM_With_MESSAGE(alarm_id,log_msg,r_act);

			if(r_act.CompareNoCase(ACT__RETRY) == 0)
			{
				goto LOOP_START;
			}
			return -12;
		}
	}

	return 1;
}

