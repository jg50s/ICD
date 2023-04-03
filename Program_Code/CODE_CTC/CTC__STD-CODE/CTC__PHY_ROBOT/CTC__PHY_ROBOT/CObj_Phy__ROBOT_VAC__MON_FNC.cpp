#include "StdAfx.h"
#include "CObj_Phy__ROBOT_VAC.h"

#include "Macro_Function.h"


// ...
void CObj_Phy__ROBOT_VAC
::Mon__MODULE_STATUS(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm)
{
	CString obj_ctrl;
	int r_count = 0;

	while(1)
	{
		p_variable->Wait__SINGLE_OBJECT(0.5);

		if(iPRC_STS < 0)
		{
			xCH__UPPER_OBJ__CTRL->Get__DATA(obj_ctrl);

			if(dEXT_CH__SCH_TEST_CFG_TMC_DUMMY_BY_CTC->Check__DATA(STR__YES) > 0)
			{
				if((obj_ctrl.CompareNoCase(STR__AVAILABLE) == 0)
				|| (obj_ctrl.CompareNoCase(STR__ABORTED)   == 0))
				{
					if(xCH__UPPER_OBJ__STATUS->Check__DATA(STR__CTCINUSE) > 0)
					{
						xCH__UPPER_OBJ__STATUS->Set__DATA(STR__STANDBY);
					}
				}
			}
			else
			{
				if((obj_ctrl.CompareNoCase(STR__AVAILABLE) == 0)
				|| (obj_ctrl.CompareNoCase(STR__ABORTED)   == 0))
				{
					if(xCH__UPPER_OBJ__STATUS->Check__DATA(STR__CTCINUSE) > 0)
					{
						r_count++;

						if(r_count > 3)
						{
							r_count = 0;

							xI_Sync_Ctrl.Thread__LOCK();

							if(iPRC_STS < 0)
							{
								xCH__UPPER_OBJ__STATUS->Set__DATA(STR__STANDBY);
							}

							xI_Sync_Ctrl.Thread__UNLOCK();
						}
					}
					else
					{
						r_count = 0;
					}
				}
				else
				{
					r_count = 0;
				}
			}
		}

		if(iPRC_STS < 0)
		{
			xCH__OBJ_CTRL->Get__DATA(obj_ctrl);

			if(dEXT_CH__SCH_TEST_CFG_TMC_DUMMY_BY_CTC->Check__DATA(STR__YES) > 0)
			{
				if((obj_ctrl.CompareNoCase(STR__AVAILABLE) == 0)
				|| (obj_ctrl.CompareNoCase(STR__ABORTED)   == 0))
				{
					if(xCH__OBJ_STATUS->Check__DATA(STR__CTCINUSE) > 0)
					{
						xCH__OBJ_STATUS->Set__DATA(STR__STANDBY);
					}
				}
			}
			else
			{
				if((obj_ctrl.CompareNoCase(STR__AVAILABLE) == 0)
				|| (obj_ctrl.CompareNoCase(STR__ABORTED)   == 0))
				{
					if(xCH__OBJ_STATUS->Check__DATA(STR__CTCINUSE) > 0)
					{
						xI_Sync_Ctrl.Thread__LOCK();

						if(iPRC_STS < 0)
						{
							xCH__OBJ_STATUS->Set__DATA(STR__STANDBY);
						}
	
						xI_Sync_Ctrl.Thread__UNLOCK();
					}
				}
			}
		}

		// ...
	}
}

void CObj_Phy__ROBOT_VAC
::Update__MATERIAL_INFO_TO_MODULE_LINK(const bool active__place_act,
									   const bool active__data_reset)
{
	CString arm_type = sPara0__Arm_Type;
	int arm_index = -1;

		 if(arm_type.CompareNoCase(_ARM__A) == 0)			arm_index = 0;
	else if(arm_type.CompareNoCase(_ARM__B) == 0)			arm_index = 1;
	else													return;

	// ...
	{
		CString sch_name;

		if(active__place_act)
		{
			sch_name = arm_type;
		}
		else
		{
			sch_name.Format("%s-%s", sPara1__Module, sPara2__Slot);
		}

		// ...
		bool active__data_clear = false;

		if(active__data_reset)
		{
			active__data_clear = true;
		}
		else
		{
			IDS__SCH_MATERIAL_INFO db_info;
			CString ch_data;

			if(xI_SCH_MATERIAL_CTRL->Get__MATERIAL_INFO(sch_name, db_info) > 0)
			{
				xCH__SLOT_LOTID[arm_index]->Set__DATA(db_info.sLOT_ID);
				xCH__SLOT_MATERIALID[arm_index]->Set__DATA(db_info.sMATERIAL_ID);

				ch_data.Format("%1d", db_info.iSRC__PTN);
				xCH__SLOT_LPx_PTN[arm_index]->Set__DATA(ch_data);
	
				ch_data.Format("%1d", db_info.iSRC__STN);
				xCH__SLOT_LPx_STN[arm_index]->Set__DATA(ch_data);

				xCH__SLOT_PPID[arm_index]->Set__DATA(db_info.sPPID);
			}
			else
			{
				active__data_clear = true;
			}
		}

		if(active__data_clear)
		{
			xCH__SLOT_LOTID[arm_index]->Set__DATA("");
			xCH__SLOT_MATERIALID[arm_index]->Set__DATA("");

			xCH__SLOT_LPx_PTN[arm_index]->Set__DATA("");
			xCH__SLOT_LPx_STN[arm_index]->Set__DATA("");
			xCH__SLOT_PPID[arm_index]->Set__DATA("");
		}

		// ...
		{
			CString log_msg;
			CString log_bff;
			
			log_msg = "\n";

			log_bff.Format("Material Info - Arm(%s) ... \n", arm_type);
			log_msg += log_bff;

			if(active__data_clear)
			{
				log_msg += " * DATA.CLEAR \n";
			}
			else
			{
				if(active__place_act)		log_msg += " * PLACE.ACTION \n";
				else						log_msg += " * PICK.ACTION \n";
			}

			log_bff.Format(" * %s <- %s \n",
						   xCH__SLOT_LOTID[arm_index]->Get__CHANNEL_NAME(),
						   xCH__SLOT_LOTID[arm_index]->Get__STRING());
			log_msg += log_bff;

			log_bff.Format(" * %s <- %s \n",
						   xCH__SLOT_MATERIALID[arm_index]->Get__CHANNEL_NAME(),
						   xCH__SLOT_MATERIALID[arm_index]->Get__STRING());
			log_msg += log_bff;

			log_bff.Format(" * %s <- %s \n",
						   xCH__SLOT_LPx_PTN[arm_index]->Get__CHANNEL_NAME(),
						   xCH__SLOT_LPx_PTN[arm_index]->Get__STRING());
			log_msg += log_bff;

			log_bff.Format(" * %s <- %s \n",
						   xCH__SLOT_LPx_STN[arm_index]->Get__CHANNEL_NAME(),
						   xCH__SLOT_LPx_STN[arm_index]->Get__STRING());
			log_msg += log_bff;

			log_bff.Format(" * %s <- %s \n",
						   xCH__SLOT_PPID[arm_index]->Get__CHANNEL_NAME(),
						   xCH__SLOT_PPID[arm_index]->Get__STRING());
			log_msg += log_bff;

			xI_LOG_CTRL->WRITE__LOG(log_msg);
		}
	}
}

void CObj_Phy__ROBOT_VAC
::Report__MATERIAL_INFO(const CString& mode)
{
	CString para_arm    = dCH__PARA_ARM_TYPE->Get__STRING();
	CString para_module = dCH__PARA_MODULE->Get__STRING();
	CString para_slot   = dCH__PARA_SLOT->Get__STRING();

	// ...
	int arm_i = -1;

		 if(para_arm.CompareNoCase(_ARM__A) == 0)		arm_i = 0;
	else if(para_arm.CompareNoCase(_ARM__B) == 0)		arm_i = 1;
	else												return;

	// ...
	int lp_id;
	int lp_slot;

	CString wfr_lotid;

	if(xCH__SLOT_STATUS[arm_i]->Check__DATA(STR__NONE) < 0)
	{
		CString wfr_ttile = xCH__SLOT_TITLE[arm_i]->Get__STRING();

		if(Macro__Get_Wafer_Info(wfr_ttile, lp_id,lp_slot) < 0)			
		{
			return;
		}

		// ...
		IDS__SCH_MATERIAL_INFO ds_info;

		if(xI_SCH_MATERIAL_CTRL->Get__MATERIAL_INFO(lp_id,lp_slot, ds_info) < 0)			
		{
			return;
		}

		wfr_lotid = ds_info.sLOT_ID;
	}
	else
	{
		IDS__SCH_MATERIAL_INFO ds_info;

		if(xI_SCH_MATERIAL_CTRL->Get__MATERIAL_INFO(para_arm, ds_info) < 0)			
		{
			return;
		}
		
		lp_id   = ds_info.iSRC__PTN;
		lp_slot = ds_info.iSRC__STN;

		wfr_lotid = ds_info.sLOT_ID;
	}

	// ...
	IDS__JOB_INFO job_info;
	xI_SCH_MATERIAL_CTRL->Get__JOB_INFO(lp_id,lp_slot, job_info);

	CString wfr_jobid = job_info.sJOB_ID;

	CString wfr_cstid;
	xI_SCH_MATERIAL_CTRL->Get__LPx_CID(lp_id, wfr_cstid);

	// ...
	CString file_date;
	CString file_time;

	// ...
	{
		SYSTEMTIME file__sys_time;
		GetLocalTime(&file__sys_time);

		file_date.Format("%04d_%02d_%02d",		
						file__sys_time.wYear,
						file__sys_time.wMonth,
						file__sys_time.wDay);

		file_time.Format("%02d:%02d:%02d",		
						file__sys_time.wHour,
						file__sys_time.wMinute,
						file__sys_time.wSecond);
	}

	// ...
	CString log_msg;

	// ...
	{
		CString log_bff;

		log_msg  = "\n";
		log_msg += "#ACT.START!";
		log_msg += "\n";

		log_bff.Format("#ACT=%s\n", mode);
		log_msg += log_bff;

		log_bff.Format("#ROBOT=%s\n", sSCH_NAME);
		log_msg += log_bff;

		log_bff.Format("#ARM=%s\n", para_arm);
		log_msg += log_bff;

		int ll_id = Macro__LLx_ID(para_module);
		if(ll_id > 0)	log_bff.Format("#MD=LL%1d-%s\n", ll_id,para_slot);
		else			log_bff.Format("#MD=%s-%s\n", para_module,para_slot);
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

		// ...
		CString ref_root;
		CString dir_date_lot;

		xI_SCH_MATERIAL_CTRL->Get__DIR_JOB_LOG(lp_id, dir_date_lot);

		ref_root  = sDir_WFR_DATA;
		ref_root += dir_date_lot;
		x_file_ctrl->Create__LOG_DIR(ref_root);

		//
		CString file_path;

		file_path.Format("%s\\P%1d_%1d.wfr", ref_root,lp_id,lp_slot);		
		x_file_ctrl->Write__LOG_MSG(file_path, log_msg);
	}
}
