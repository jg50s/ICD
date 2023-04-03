#include "StdAfx.h"
#include "CObj_Phy__ROBOT_ATM.h"

#include "Macro_Function.h"


// ...
void CObj_Phy__ROBOT_ATM
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


void CObj_Phy__ROBOT_ATM
::Update__MATERIAL_INFO()
{
	CString ch_data;

	CString arm_type;
	int i;

	for(i=0; i<CFG_ROBOT__ARM_SIZE; i++)
	{
		if(xCH__SLOT_STATUS[i]->Check__DATA(STR__NONE) > 0)
		{
			continue;
		}

			 if(i == 0)		arm_type = "A";
		else if(i == 1)		arm_type = "B";
		else				continue;

		// ...
		IDS__SCH_MATERIAL_INFO db_info;

		if(xI_SCH_MATERIAL_CTRL->Get__MATERIAL_INFO(arm_type,db_info) > 0)
		{
			xCH__SLOT_LOTID[i]->Set__DATA(db_info.sLOT_ID);
			xCH__SLOT_MATERIALID[i]->Set__DATA(db_info.sMATERIAL_ID);

			ch_data.Format("%1d", db_info.iSRC__PTN);
			xCH__SLOT_LPx_PTN[i]->Set__DATA(ch_data);

			ch_data.Format("%1d", db_info.iSRC__STN);
			xCH__SLOT_LPx_STN[i]->Set__DATA(ch_data);

			xCH__SLOT_PPID[i]->Set__DATA(db_info.sPPID);
		}
		else
		{
			xCH__SLOT_LOTID[i]->Set__DATA("");
			xCH__SLOT_MATERIALID[i]->Set__DATA("");

			xCH__SLOT_LPx_PTN[i]->Set__DATA("");
			xCH__SLOT_LPx_STN[i]->Set__DATA("");
			xCH__SLOT_PPID[i]->Set__DATA("");
		}

		// ...
		{
			CString log_msg;
			CString log_bff;

			log_msg = "\n";
			log_bff.Format("Material Info - Arm(%s) ... \n", arm_type);
			log_msg += log_bff;

			log_bff.Format(" * %s <- %s \n",
							xCH__SLOT_LOTID[i]->Get__CHANNEL_NAME(),
							xCH__SLOT_LOTID[i]->Get__STRING());
			log_msg += log_bff;

			log_bff.Format(" * %s <- %s \n",
							xCH__SLOT_MATERIALID[i]->Get__CHANNEL_NAME(),
							xCH__SLOT_MATERIALID[i]->Get__STRING());
			log_msg += log_bff;

			log_bff.Format(" * %s <- %s \n",
							xCH__SLOT_LPx_PTN[i]->Get__CHANNEL_NAME(),
							xCH__SLOT_LPx_PTN[i]->Get__STRING());
			log_msg += log_bff;

			log_bff.Format(" * %s <- %s \n",
							xCH__SLOT_LPx_STN[i]->Get__CHANNEL_NAME(),
							xCH__SLOT_LPx_STN[i]->Get__STRING());
			log_msg += log_bff;

			log_bff.Format(" * %s <- %s \n",
							xCH__SLOT_PPID[i]->Get__CHANNEL_NAME(),
							xCH__SLOT_PPID[i]->Get__STRING());
			log_msg += log_bff;

			xI_LOG_CTRL->WRITE__LOG(log_msg);
		}
	}
}

void CObj_Phy__ROBOT_ATM
::Report__MATERIAL_INFO(const CString& mode)
{
	CString para_arm  = dCH__PARA_ARM_TYPE->Get__STRING();

	if(para_arm.CompareNoCase(_ARM__AB) == 0)
	{
		_Report__MATERIAL_INFO(mode, _ARM__A);
		_Report__MATERIAL_INFO(mode, _ARM__B);
	}
	else
	{
		_Report__MATERIAL_INFO(mode, para_arm);
	}
}
void CObj_Phy__ROBOT_ATM
::_Report__MATERIAL_INFO(const CString& mode, const CString& para_arm)
{
	CString para_module = dCH__PARA_MODULE->Get__STRING();
	CString para_slot   = dCH__PARA_SLOT->Get__STRING();

	// ...
	int arm_i = -1;

		 if(para_arm.CompareNoCase(_ARM__A) == 0)		arm_i = 0;
	else if(para_arm.CompareNoCase(_ARM__B) == 0)		arm_i = 1;
	else												return;

	// ...
	bool active_wfr = false;

	int lp_id;
	int lp_slot;

	if(xCH__SLOT_STATUS[arm_i]->Check__DATA(STR__NONE) < 0)
	{
		CString wfr_title = xCH__SLOT_TITLE[arm_i]->Get__STRING();
		active_wfr = true;

		if(Macro__Get_Wafer_Info(wfr_title, lp_id,lp_slot) < 0)
		{
			return;
		}
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
	}

	// LPx ...
	{
		int xx_id = Macro__LPx_ID(para_module);
		int xx_slot = atoi(para_slot);

		if(xx_id == lp_id)
		{
			_Report__LPx_MATERIAL_INFO(mode, para_arm,lp_id,lp_slot, active_wfr);
			return;
		}
	}

	// ALx ...
	{
		int al_id = Macro__ALx_ID(para_module);
		int al_slot = atoi(para_slot);

		if(al_id > 0)
		{
			_Report__ALx_MATERIAL_INFO(mode, para_arm,al_id,al_slot, lp_id,lp_slot);
			return;
		}
	}

	// LLx & STx ...
	{
		_Report__MDx_MATERIAL_INFO(mode, para_arm, para_module,para_slot, lp_id,lp_slot);
	}
}
void CObj_Phy__ROBOT_ATM
::_Report__LPx_MATERIAL_INFO(const CString& mode, 
							 const CString& arm_type, 
							 const int lp_id,
							 const int lp_slot,
							 const bool active_wfr)
{
	IDS__SCH_MATERIAL_INFO ds_info;

	if(xI_SCH_MATERIAL_CTRL->Get__MATERIAL_INFO(lp_id,lp_slot, ds_info) < 0)
	{
		return;
	}

	CString wfr_lotid = ds_info.sLOT_ID;

	// ...
	CString step_log = "";
	CString step_bff;

	// Main Process ...
	if(active_wfr)
	{
		CStringArray l_pre_pmx;
		CStringArray l_pre_crp;
		CStringArray l_main_pmx;
		CStringArray l_main_rcp;
		CStringArray l_post_pmx;
		CStringArray l_post_rcp;

		int i_limit = xI_SCH_MATERIAL_CTRL->Get__STEP_SIZE_OF_MATERIAL(lp_id,lp_slot);
		int i;

		step_bff.Format("#STEP_SIZE=%1d\n", i_limit);
		step_log += step_bff;

		for(i=0; i<i_limit; i++)
		{
			step_bff.Format("#STEP_%02d=", i+1);
			step_log += step_bff;

			xI_SCH_MATERIAL_CTRL->Get__STEPx_PROCESS_INFO_OF_MATERIAL(lp_id,lp_slot, i, l_pre_pmx,l_pre_crp, l_main_pmx,l_main_rcp, l_post_pmx,l_post_rcp);

			int k_limit = l_main_pmx.GetSize();
			int k;

			for(k=0; k<k_limit; k++)
			{
				CString main_pmx = l_main_pmx[k];
				CString main_rcp = l_main_rcp[k];

				step_bff.Format("%s/%s,",  main_pmx,main_rcp);
				step_log += step_bff;
			}
			
			step_log += "\n";
		}
	}
	// Process Loop ...
	if(active_wfr)
	{
		CString loop_id = "";
		int loop_count = -1;

		xI_SCH_MATERIAL_CTRL->Get__PROC_LOOPx_OF_EDIT_TYPE(lp_id,lp_slot, loop_id,loop_count);

		step_bff.Format("#LOOP=%s,%1d\n", loop_id,loop_count);
		step_log += step_bff;
	}

	// ...
	CString log_msg = "";

	if(active_wfr)
	{
		CString log_bff;

		log_msg  = "\n";
		log_msg += "#WAFER.START!";
		log_msg += "\n";

		log_bff.Format("#PORTID=%1d\n", lp_id);
		log_msg += log_bff;

		log_bff.Format("#SLOTID=%1d\n", lp_slot);
		log_msg += log_bff;

		log_bff.Format("#LOTID=%s\n", wfr_lotid);
		log_msg += log_bff;

		log_bff.Format("#PPID=%s\n", ds_info.sPPID);
		log_msg += log_bff;

		log_bff.Format("#MATERIALID=%s\n", ds_info.sMATERIAL_ID);
		log_msg += log_bff;

		log_msg += step_log;

		log_msg += "#WAFER.END!";
		log_msg += "\n";
	}

	// ...
	{
		CString md_name;
		md_name.Format("LP%1d-%02d", lp_id,lp_slot);

		log_msg += _Get__MDx_ACTION_INFO(mode, arm_type,md_name, "");
	}

	_Save__MATERIAL_INFO(lp_id,lp_slot, log_msg);
}
void CObj_Phy__ROBOT_ATM
::_Report__ALx_MATERIAL_INFO(const CString& mode, 
							 const CString& arm_type, 
							 const int al_id,
							 const int al_slot,
							 const int lp_id,
							 const int lp_slot)
{
	IDS__SCH_MATERIAL_INFO ds_info;

	if(xI_SCH_MATERIAL_CTRL->Get__MATERIAL_INFO(lp_id,lp_slot, ds_info) < 0)
	{
		return;
	}

	CString wfr_lotid = ds_info.sLOT_ID;

	// ...
	CString log_msg;
	CString act_log;

	// ...
	{
		CString log_bff;

		log_bff.Format("#ALIGN.LLx_NAME=%s\n",  sCH__TARGET_LLx_NAME_GET->Get__STRING());
		act_log += log_bff;

		log_bff.Format("#ALIGN.LLx_SLOT=%s\n",  sCH__TARGET_LLx_SLOT_GET->Get__STRING());
		act_log += log_bff;

		log_bff.Format("#ALIGN.LLx_ANGLE=%s\n", sCH__TARGET_LLx_ANGLE_GET->Get__STRING());
		act_log += log_bff;
	}

	// ...
	{
		CString md_name;
		md_name.Format("AL%1d-%1d", al_id,al_slot);

		log_msg += _Get__MDx_ACTION_INFO(mode, arm_type,md_name, act_log);
	}

	_Save__MATERIAL_INFO(lp_id,lp_slot, log_msg);
}
void CObj_Phy__ROBOT_ATM
::_Report__MDx_MATERIAL_INFO(const CString& mode, 
							 const CString& arm_type, 
							 const CString& md_id,
							 const CString& md_slot,
							 const int lp_id,
							 const int lp_slot)
{
	IDS__SCH_MATERIAL_INFO ds_info;

	if(xI_SCH_MATERIAL_CTRL->Get__MATERIAL_INFO(lp_id,lp_slot, ds_info) < 0)
	{
		return;
	}

	CString wfr_lotid = ds_info.sLOT_ID;
	
	// ...
	CString log_msg;

	// ...
	{
		CString md_name;
		md_name.Format("%s-%s\n", md_id,md_slot);

		int ll_id = Macro__LLx_ID(md_id);
	    if(ll_id > 0)		md_name.Format("LL%1d-%s", ll_id,md_slot);

		int st_id = Macro__STx_ID(md_id);
		if(st_id > 0)		md_name.Format("ST%1d-%s", st_id,md_slot);

		log_msg += _Get__MDx_ACTION_INFO(mode, arm_type,md_name, "");
	}

	_Save__MATERIAL_INFO(lp_id,lp_slot, log_msg);
}

CString CObj_Phy__ROBOT_ATM
::_Get__MDx_ACTION_INFO(const CString& act_mode, 
						const CString& arm_type,
						const CString& md_name, 
						const CString& act_log)
{
	CString log_msg;
	CString log_bff;

	log_msg += "\n";
	log_msg += "#ACT.START!";
	log_msg += "\n";

	log_bff.Format("#ACT=%s\n", act_mode);
	log_msg += log_bff;

	log_bff.Format("#ROBOT=%s\n", sSCH_NAME);
	log_msg += log_bff;

	log_bff.Format("#ARM=%s\n", arm_type);
	log_msg += log_bff;

	log_bff.Format("#MD=%s\n", md_name);
	log_msg += log_bff;

	log_bff.Format("#TIME.ACT=%s\n", sCH__TIME_ACT_TACK->Get__STRING());
	log_msg += log_bff;

	log_bff.Format("#TIME.START=%s\n", sCH__TIME_ACT_START->Get__STRING());
	log_msg += log_bff;

	log_bff.Format("#TIME.END=%s\n", sCH__TIME_ACT_END->Get__STRING());
	log_msg += log_bff;

	log_bff.Format("#RESULT=%s\n", sCH__TIME_ACT_RESULT->Get__STRING());
	log_msg += log_bff;

	log_msg += act_log;

	log_msg += "#ACT.END!";
	log_msg += "\n";

	return log_msg;
}
void CObj_Phy__ROBOT_ATM
::_Save__MATERIAL_INFO(const int lp_id,
					   const int lp_slot, 
					   const CString& wfr_info)
{
	SCX__FILE_CTRL x_file_ctrl;
	x_file_ctrl->DISABLE__TIME_LOG();

	// ...
	CString ref_root;
	CString dir_date_lot;

	// ...
	{
		int check_count = 0;
	
		while(1)
		{
			xI_SCH_MATERIAL_CTRL->Get__DIR_JOB_LOG(lp_id, dir_date_lot);
			if(dir_date_lot.GetLength() > 0)		break;

			check_count++;
			if(check_count > 10)		break;

			Sleep(100);
		}
	}

	ref_root  = sDir_WFR_DATA;
	ref_root += dir_date_lot;
	x_file_ctrl->Create__LOG_DIR(ref_root);

	//
	CString file_path;

	file_path.Format("%s\\P%1d_%1d.wfr", ref_root,lp_id,lp_slot);		
	x_file_ctrl->Write__LOG_MSG(file_path, wfr_info);
}
