#include "StdAfx.h"
#include "CObj_Fnc__SINGLE_ARM_STD.h"



// ...
int  CObj_Fnc__SINGLE_ARM_STD::
SCH__FRONT_MODULE(CII_OBJECT__VARIABLE *p_variable,
				  const CString& str_module,const CString& str_slot)
{
	if((xCH__ATM_RB__ANI_TRG_ROTE->Check__DATA(str_module) > 0)
	|| (xCH__ATM_RB__ANI_TRG_MOVE->Check__DATA(str_module) > 0))
	{
		return -1;
	}

	DECLARE__EXT_CTRL(p_variable);

	//.....
	{
		CStringArray l_para;

		l_para.RemoveAll();
		l_para.Add("A");
		l_para.Add(str_module);
		l_para.Add(str_slot);

		pATM_RB__OBJ_CTRL->Call__OBJ_MODE(ATM_CMMD__ROTATE,l_para);
	}
	return 1;
}

int  CObj_Fnc__SINGLE_ARM_STD::
SCH__PICK_MODULE(CII_OBJECT__VARIABLE *p_variable,
				 CII_OBJECT__ALARM *p_alarm,
				 const CString& log_id,
				 const bool ex_flag,
				 const CString& arm_type,const CString& para_module,const CString& para_slot,
				 const CString& from_sch_module,
				 const int maint_flag)
{
	CString fnc_id = "SCH__PICK_MODULE()";

	// ...
	{
		CString log_msg;
		CString log_bff;

		log_msg = "SCH__PICK_MODULE() : Started ! \n";
		log_bff.Format(" * arm_type <- %s \n", arm_type);
		log_msg += log_bff;
		log_bff.Format(" * para_module <- %s \n", para_module);
		log_msg += log_bff;
		log_bff.Format(" * para_slot <- %s \n", para_slot);
		log_msg += log_bff;
		log_bff.Format(" * from_sch_module <- %s \n", from_sch_module);
		log_msg += log_bff;

		xAPP_LOG_CTRL->WRITE__LOG(log_msg);
	}

	// ...
	if(SCH__CHECK_PICK_MODULE__READY(p_variable,ex_flag,para_module,para_slot,maint_flag) < 0)
	{
		return -1;
	}

	if(maint_flag < 0)
	{
		Datalog__Picking_Material(arm_type,para_module,para_slot,ex_flag);

		xSCH_MATERIAL_CTRL->Transfer_Start__To_MODULE(from_sch_module,arm_type);
	}

	iLBx_FRONT_FLAG = -1;

	if(SCH__PICK_FROM(p_variable,p_alarm,ex_flag,arm_type,para_module,para_slot) < 0)
	{
		return -1;
	}

	// ...
	{
		CString para_info;
		para_info.Format("%s <- %s(%s) : ex_flag(%1d)", arm_type,para_module,para_slot,ex_flag);

		Fnc__LOG_INFO(fnc_id, log_id, para_info);
	}

	if(maint_flag < 0)
	{
		Datalog__Picked_Material(arm_type,para_module,para_slot,ex_flag);

		xSCH_MATERIAL_CTRL->Transfer_End__To_MODULE(from_sch_module,arm_type);
	}

	if(SCH__CHECK_PICK_MODULE__COMPLETE(p_variable,ex_flag,para_module,para_slot,maint_flag) < 0)
	{
	
	}

	// ...
	{
		if((para_module.CompareNoCase(MODULE__BUFFER1) == 0)
		|| (para_module.CompareNoCase(MODULE__BUFFER2) == 0))
		{
			if(para_module.CompareNoCase(MODULE__BUFFER1) == 0)
			{
				if(Buffer1__Check_Empty__All_Slot() > 0)
				{
					xEXT_CH__BUFFER1__APP_CUR_LOTID->Set__DATA("");
				}
			}
			else
			{
				if(Buffer2__Check_Empty__All_Slot() > 0)
				{
					xEXT_CH__BUFFER2__APP_CUR_LOTID->Set__DATA("");
				}
			}
		}
	}

	return 1;
}
int  CObj_Fnc__SINGLE_ARM_STD::
SCH__PLACE_MODULE(CII_OBJECT__VARIABLE *p_variable,
				  CII_OBJECT__ALARM *p_alarm,
				  const CString& log_xx,
				  const bool ex_flag,
				  const CString& arm_type,
				  const CString& para_module,
				  const CString& para_slot,
				  const CString& to_sch_module,
				  const int maint_flag)
{
	CString log_id = log_xx;
	log_id += " -> ";
	log_id += "SCH__PLACE_MODULE()";

	// ...
	int ll_i = Get__LLx_INDEX(para_module);
	if(ll_i >= 0)
	{
		xCH__ATM_RB__SCH_STS_TO_LLx[ll_i]->Set__DATA("YES");
	}

	int r_flag = _SCH__PLACE_MODULE(p_variable,p_alarm, log_id, ex_flag, arm_type,para_module,para_slot,to_sch_module, maint_flag);

	if(ll_i >= 0)
	{
		xCH__ATM_RB__SCH_STS_TO_LLx[ll_i]->Set__DATA("");
	}
	return r_flag;
}
int  CObj_Fnc__SINGLE_ARM_STD::
_SCH__PLACE_MODULE(CII_OBJECT__VARIABLE *p_variable,
				  CII_OBJECT__ALARM *p_alarm,
				  const CString& log_id,
				  const bool ex_flag,
				  const CString& arm_type,
				  const CString& para_module,
				  const CString& para_slot,
				  const CString& to_sch_module,
				  const int maint_flag)
{
	CString fnc_id = "_SCH__PLACE_MODULE()";

	// ...
	{
		CString log_msg;
		CString log_bff;

		log_msg = "_SCH__PLACE_MODULE() : Started ! \n";
		log_bff.Format(" * arm_type <- %s \n", arm_type);
		log_msg += log_bff;
		log_bff.Format(" * para_module <- %s \n", para_module);
		log_msg += log_bff;
		log_bff.Format(" * para_slot <- %s \n", para_slot);
		log_msg += log_bff;
		log_bff.Format(" * to_sch_module <- %s \n", to_sch_module);
		log_msg += log_bff;

		xAPP_LOG_CTRL->WRITE__LOG(log_msg);
	}

	if(Get__LLx_INDEX(para_module) >= 0)
	{
		bool active__ll_align = false;

		if(xCH__ATM_RB__TARGET_LLx_MODE->Check__DATA(STR__ENABLE) > 0)
		{
			if((xCH__ATM_RB__TARGET_LLx_NAME_SET->Check__DATA(para_module) < 0)
			|| (xCH__ATM_RB__TARGET_LLx_SLOT_SET->Check__DATA(para_slot)   < 0))
			{
				active__ll_align = true;
			}
		}

		if(active__ll_align)
		{
			if(AL1__Is_Available() < 0)
			{
				return -1;
			}
			if(AL1__Check_Empty__All_Slot() < 0)
			{
				return -1;
			}

			// ...
			CString sch_module;
			CString al_name = "AL1";
			CString al_slot = "1";

			sch_module.Format("%s-%s", al_name,al_slot);

			// Place ...
			{
				if(SCH__PLACE_TO(p_variable,
								 p_alarm, 
								 false, 
								 arm_type, 
								 al_name, 
								 al_slot) < 0)
				{
					return -1;
				}

				xSCH_MATERIAL_CTRL->Place__To_MODULE(arm_type,sch_module);
				xSCH_MATERIAL_CTRL->Set__MATERIAL_STATUS(sch_module, "ALIGNED");
			}

			xCH__ATM_RB__TARGET_LLx_NAME_SET->Set__DATA(para_module);
			xCH__ATM_RB__TARGET_LLx_SLOT_SET->Set__DATA(para_slot);

			// Pick ...
			{
				if(SCH__PICK_FROM(p_variable, 
								  p_alarm, 
								  false, 
								  arm_type, 
								  al_name, 
								  al_slot) < 0)
				{
					return -1;
				}

				xSCH_MATERIAL_CTRL->Pick__From_MODULE(sch_module,arm_type);
			}		
		}
	}

	if(SCH__CHECK_PLACE_MODULE__READY(p_variable,
										ex_flag,
										para_module,
										para_slot,
										maint_flag) < 0)
	{
		return -1;
	}

	if(maint_flag < 0)
	{
		if((para_module.CompareNoCase(MODULE__BUFFER1) == 0)
		|| (para_module.CompareNoCase(MODULE__BUFFER2) == 0))
		{
			IDS__SCH_MATERIAL_INFO ds_info;
			xSCH_MATERIAL_CTRL->Get__MATERIAL_INFO(arm_type,ds_info);

			CString str__lotid = ds_info.sLOT_ID;

			if(para_module.CompareNoCase(MODULE__BUFFER1) == 0)
			{
				xEXT_CH__BUFFER1__APP_CUR_LOTID->Set__DATA(str__lotid);
			}
			else
			{
				xEXT_CH__BUFFER2__APP_CUR_LOTID->Set__DATA(str__lotid);
			}
		}
	}

	if(maint_flag < 0)
	{
		Datalog__Placing_Material(arm_type,
									para_module,
									para_slot,
									ex_flag);

		xSCH_MATERIAL_CTRL->Transfer_Start__To_MODULE(arm_type,to_sch_module);	
	}

	iLBx_FRONT_FLAG = -1;

	if(SCH__PLACE_TO(p_variable,
						p_alarm,
						ex_flag,
						arm_type,
						para_module,
						para_slot) < 0)
	{
		return -1;
	}

	// ...
	{
		CString para_info;
		para_info.Format("%s -> %s(%s) : ex_flag(%1d)", arm_type,para_module,para_slot,ex_flag);

		Fnc__LOG_INFO(fnc_id, log_id, para_info);
	}

	if(maint_flag < 0)
	{
		Datalog__Placed_Material(arm_type,
									para_module,
									para_slot,
									ex_flag);

		xSCH_MATERIAL_CTRL->Transfer_End__To_MODULE(arm_type,to_sch_module);
	}

	if(SCH__CHECK_PLACE_MODULE__COMPLETE(p_variable,
										 ex_flag,
										 arm_type,
										 para_module,
										 para_slot,
										 maint_flag) < 0)
	{

	}

	return 1;
}


//------------------------------------------------------------------------------------------------
int  CObj_Fnc__SINGLE_ARM_STD::
SEQ__MAP_BY_ATM_RB(CII_OBJECT__VARIABLE *p_variable,const CString& str_module)
{
	DECLARE__EXT_CTRL(p_variable);

	if(ATM_RB__Is_Available() < 0)
	{
		return -1;
	}

	// ...
	CStringArray l_para;

	l_para.RemoveAll();
	l_para.Add(str_module);

	return pATM_RB__OBJ_CTRL->Call__OBJ_MODE(ATM_CMMD__LP_MAP,l_para);
}
int  CObj_Fnc__SINGLE_ARM_STD::
SEQ__ATM_RB__HOME(const int run_call)
{
	if(ATM_RB__Is_Available() < 0)
	{
		return -1;
	}

	if(run_call > 0)
	{
		return pATM_RB__OBJ_CTRL->Run__OBJECT(ATM_CMMD__HOME);
	}
	return pATM_RB__OBJ_CTRL->Call__OBJECT(ATM_CMMD__HOME);
}


//------------------------------------------------------------------------------------------------
int  CObj_Fnc__SINGLE_ARM_STD::
SCH__Get_LPx_INDEX(const CString& str_module)
{
	CString lp_name;
	int i;

	for(i=0;i<CFG_LP_LIMIT;i++)
	{
		lp_name.Format("LP%1d",i+1);

		if(str_module.CompareNoCase(lp_name) == 0)
		{
			return i;
		}
	}
	return -1;
}

int  CObj_Fnc__SINGLE_ARM_STD::
SCH__PICK_FROM(CII_OBJECT__VARIABLE *p_variable,
			   CII_OBJECT__ALARM *p_alarm,
			   const bool ex_flag,
			   const CString& arm_type,
			   const CString& str_module,
			   const CString& str_slot)
{
	DECLARE__EXT_CTRL(p_variable);

	//.....
	if(ATM_RB__Is_Available() < 0)
	{
		return -1;
	}

	// ...
	{
		CString str_lp_name;
		CString var_data;

		int lp_i = -1;
		int i;

		for(i=0;i<iLPx_SIZE;i++)
		{
			str_lp_name.Format("LP%1d",i+1);
			if(str_lp_name.CompareNoCase(str_module) != 0)
			{
				continue;
			}

			lp_i = i;
			break;
		}

		if(lp_i >= 0)
		{
			xCH__LPx__LAST_PICK_SLOT[lp_i]->Set__DATA(str_slot);
		}
	}

	//.....
	CStringArray l_para;

	// ...
	{
		l_para.RemoveAll();
		l_para.Add(arm_type);
		l_para.Add(str_module);
		l_para.Add(str_slot);
	}

	// ...
	int flag;

	if(ex_flag == false)
	{
		flag = pATM_RB__OBJ_CTRL->Call__OBJ_MODE("PICK", l_para);
	}
	else
	{
		flag = pATM_RB__OBJ_CTRL->Call__OBJ_MODE("XPICK", l_para);
	}

	if(flag < 0)
	{
		// ...
		{
			int alarm_id;
			CString str_msg;
			CString str_bff;
			CString r_act;

			alarm_id = ALID__MOVE_ERROR__WAFER_CONFIRM;

			str_bff.Format("Wafer가 %s[%s]에서 Arm[%s]으로 이동 되었나요?\n",
				str_module,
				str_slot,
				arm_type);
			str_msg += str_bff;

			str_bff.Format("GUI상의 Wafer 정보와 실제 Wafer가 일치하는지 확인하십시요.\n");
			str_msg += str_bff;

			str_msg += "만약, 일치하지 않는다면 아래의 [YES]나 [NO]를 선택해 주십시요. \n";
			str_msg += "일치한다면, 아래의 [IGNORE]를 선택해야 합니다. \n";

			str_bff.Format("1. 실제로 Wafer가 Robot Arm[%s]으로 이동 되어 있으면,", arm_type);
			str_msg += str_bff;
			str_msg += "       [YES]를 선택하십시요. \n";
			str_bff.Format("2. 실제로 Wafer가 Robot Arm[%s]으로 이동 되지 않았다면,", arm_type);
			str_msg += str_bff;
			str_msg += "       [NO]를 선택하십시요. \n";			
			str_bff.Format("3. 현재 상태가 맞다면, [IGNORE]를 선택하십시요. \n");
			str_msg += str_bff;

			p_alarm->Popup__ALARM_With_MESSAGE(alarm_id,str_msg,r_act);

			if(r_act.CompareNoCase(STR__YES) == 0)
			{
				// Module -> Arm

				// ....
				CString slot_status;
				CString slot_title;
				int check_flag = -1;

				int ll_i = Get__LLx_INDEX(str_module);
				int slot_index = atoi(str_slot) - 1;

				if(str_module.CompareNoCase(MODULE__AL1) == 0)
				{
					check_flag = 1;

					//
					xCH__AL1__SLOT01_STATUS->Get__DATA(slot_status);
					xCH__AL1__SLOT01_TITLE->Get__DATA(slot_title);

					xCH__AL1__SLOT01_STATUS->Set__DATA(STR__NONE);
					xCH__AL1__SLOT01_TITLE->Set__DATA("");
				}
				else if(ll_i >= 0)
				{
					int slot_size = iLLx_SLOT_MAX[ll_i];

					if((slot_index >= 0)
					&& (slot_index <  slot_size))	
					{
						check_flag = 1;
						
						xEXT_CH__LLx__SLOT_STATUS[ll_i][slot_index]->Get__DATA(slot_status);
						xEXT_CH__LLx__SLOT_TITLE[ll_i][slot_index]->Get__DATA(slot_title);

						xEXT_CH__LLx__SLOT_STATUS[ll_i][slot_index]->Set__DATA(STR__NONE);
						xEXT_CH__LLx__SLOT_TITLE[ll_i][slot_index]->Set__DATA("");
					}
				}
				else if(str_module.CompareNoCase(MODULE__BUFFER1) == 0)
				{
					if((slot_index >= 0)
					&& (slot_index <  CFG_LP__SLOT_MAX))
					{
						check_flag = 1;

						//
						xEXT_CH__BUFFER1__SLOT_STATUS[slot_index]->Get__DATA(slot_status);
						xEXT_CH__BUFFER1__SLOT_TITLE[slot_index]->Get__DATA(slot_title);

						xEXT_CH__BUFFER1__SLOT_STATUS[slot_index]->Set__DATA(STR__NONE);
						xEXT_CH__BUFFER1__SLOT_TITLE[slot_index]->Set__DATA("");
					}
				}
				else if(str_module.CompareNoCase(MODULE__BUFFER2) == 0)
				{
					if((slot_index >= 0)
					&& (slot_index <  CFG_LP__SLOT_MAX))
					{
						check_flag = 1;

						//
						xEXT_CH__BUFFER2__SLOT_STATUS[slot_index]->Get__DATA(slot_status);
						xEXT_CH__BUFFER2__SLOT_TITLE[slot_index]->Get__DATA(slot_title);

						xEXT_CH__BUFFER2__SLOT_STATUS[slot_index]->Set__DATA(STR__NONE);
						xEXT_CH__BUFFER2__SLOT_TITLE[slot_index]->Set__DATA("");
					}
				}
				else
				{
					int lp_index = SCH__Get_LPx_INDEX(str_module);

					if(lp_index >= 0)
					{
						if((slot_index >= 0)
						&& (slot_index <  CFG_LP__SLOT_MAX))
						{
							check_flag = 1;

							//
							xCH__LPx__SLOT_STATUS[lp_index][slot_index]->Get__DATA(slot_status);

							xCH__LPx__SLOT_STATUS[lp_index][slot_index]->Set__DATA(STR__NONE);
						}
					}
				}

				if(check_flag > 0)
				{
					if(arm_type.CompareNoCase(STR__A) == 0)
					{
						xCH__ATM_RB__SLOT01_STATUS->Set__DATA(slot_status);	
						xCH__ATM_RB__SLOT01_TITLE->Set__DATA(slot_title);
					}	
					else if(arm_type.CompareNoCase(STR__B) == 0)
					{
						xCH__ATM_RB__SLOT02_STATUS->Set__DATA(slot_status);	
						xCH__ATM_RB__SLOT02_TITLE->Set__DATA(slot_title);
					}	
				}
			}
			else if(r_act.CompareNoCase(STR__NO) == 0)
			{
				// Arm -> Module

				// ....
				CString slot_status;
				CString slot_title;
				int check_flag = -1;

				int ll_i = Get__LLx_INDEX(str_module);
				int slot_index = atoi(str_slot) - 1;

				if(arm_type.CompareNoCase(STR__A) == 0)
				{
					check_flag = 1;

					//
					xCH__ATM_RB__SLOT01_STATUS->Get__DATA(slot_status);	
					xCH__ATM_RB__SLOT01_TITLE->Get__DATA(slot_title);

					xCH__ATM_RB__SLOT01_STATUS->Set__DATA(STR__NONE);	
					xCH__ATM_RB__SLOT01_TITLE->Set__DATA("");
				}
				else if(arm_type.CompareNoCase(STR__B) == 0)
				{
					check_flag = 1;

					//
					xCH__ATM_RB__SLOT02_STATUS->Get__DATA(slot_status);	
					xCH__ATM_RB__SLOT02_TITLE->Get__DATA(slot_title);

					xCH__ATM_RB__SLOT02_STATUS->Set__DATA(STR__NONE);	
					xCH__ATM_RB__SLOT02_TITLE->Set__DATA("");
				}

				if(check_flag > 0)
				{
					if(str_module.CompareNoCase(MODULE__AL1) == 0)
					{
						xCH__AL1__SLOT01_STATUS->Set__DATA(slot_status);
						xCH__AL1__SLOT01_TITLE->Set__DATA(slot_title);
					}
					else if(ll_i >= 0)
					{
						int slot_max = iLLx_SLOT_MAX[ll_i];

						if((slot_index >= 0)
						&& (slot_index <  slot_max))	
						{
							xEXT_CH__LLx__SLOT_STATUS[ll_i][slot_index]->Set__DATA(slot_status);
							xEXT_CH__LLx__SLOT_TITLE[ll_i][slot_index]->Set__DATA(slot_title);
						}
					}
					else if(str_module.CompareNoCase(MODULE__BUFFER1) == 0)
					{
						if((slot_index >= 0)
						&& (slot_index <  CFG_LP__SLOT_MAX))
						{
							xEXT_CH__BUFFER1__SLOT_STATUS[slot_index]->Set__DATA(slot_status);
							xEXT_CH__BUFFER1__SLOT_TITLE[slot_index]->Set__DATA(slot_title);
						}
					}
					else if(str_module.CompareNoCase(MODULE__BUFFER2) == 0)
					{
						if((slot_index >= 0)
						&& (slot_index <  CFG_LP__SLOT_MAX))
						{
							xEXT_CH__BUFFER2__SLOT_STATUS[slot_index]->Set__DATA(slot_status);
							xEXT_CH__BUFFER2__SLOT_TITLE[slot_index]->Set__DATA(slot_title);
						}
					}
					else
					{
						int lp_index = SCH__Get_LPx_INDEX(str_module);

						if(lp_index >= 0)
						{
							if((slot_index >= 0)
							&& (slot_index <  CFG_LP__SLOT_MAX))
							{
								xCH__LPx__SLOT_STATUS[lp_index][slot_index]->Set__DATA(slot_status);
							}
						}
					}
				}
			}
		}

		// ...
		{
			int alarm_id;
			CString str_msg;
			CString str_bff;
			CString r_act;

			alarm_id = ALID__USER_CHECK__WAFER_CONFIRM;

			str_bff.Format("GUI상의 Wafer 정보와 실제 Wafer 정보가 일치하는지 확인하십시요.\n");
			str_msg += str_bff;

			str_msg += "만약, 일치하지 않는다면 아래와 같이 처리해 주십시요.\n";

			str_msg += "   1. 현재 실행 중인 Job을 Abort시킨다. \n";
			str_msg += "   2. CTC Resync-Page에서 Wafer 정보를 실제와 일치시킨다. \n";
			str_msg += "   3. Tool-Clear를 실행시킨다. \n";

			p_alarm->Popup__ALARM_With_MESSAGE(alarm_id,str_msg,r_act);
		}
	}
	else if(flag > 0)
	{
LOOP__RETRY_CHECK:

		// Material Pick : Check ...
		CString slot_status;
		CString slot_title;
		int check_flag = -1;

		int ll_i = Get__LLx_INDEX(str_module);
		int slot_index = atoi(str_slot) - 1;

		if(str_module.CompareNoCase(MODULE__AL1) == 0)
		{
			check_flag = 1;

			if(slot_index == 0)
			{
				xCH__AL1__SLOT01_STATUS->Get__DATA(slot_status);
				xCH__AL1__SLOT01_TITLE->Get__DATA(slot_title);
			}
			else if(slot_index == 1)
			{
				xCH__AL1__SLOT02_STATUS->Get__DATA(slot_status);
				xCH__AL1__SLOT02_TITLE->Get__DATA(slot_title);
			}
			else 
			{
				slot_status = "UNKNOWN";
				slot_title  = "??";
			}
		}
		else if(ll_i >= 0)
		{
			int slot_max = iLLx_SLOT_MAX[ll_i];

			if((slot_index >= 0)
			&& (slot_index <  slot_max))	
			{
				check_flag = 1;
				
				xEXT_CH__LLx__SLOT_STATUS[ll_i][slot_index]->Get__DATA(slot_status);
				xEXT_CH__LLx__SLOT_TITLE[ll_i][slot_index]->Get__DATA(slot_title);
			}
		}
		else if(str_module.CompareNoCase(MODULE__BUFFER1) == 0)
		{
			if((slot_index >= 0)
			&& (slot_index <  CFG_LP__SLOT_MAX))
			{
				check_flag = 1;

				//
				xEXT_CH__BUFFER1__SLOT_STATUS[slot_index]->Get__DATA(slot_status);
				xEXT_CH__BUFFER1__SLOT_TITLE[slot_index]->Get__DATA(slot_title);
			}
		}
		else if(str_module.CompareNoCase(MODULE__BUFFER2) == 0)
		{
			if((slot_index >= 0)
			&& (slot_index <  CFG_LP__SLOT_MAX))
			{
				check_flag = 1;

				//
				xEXT_CH__BUFFER2__SLOT_STATUS[slot_index]->Get__DATA(slot_status);
				xEXT_CH__BUFFER2__SLOT_TITLE[slot_index]->Get__DATA(slot_title);
			}
		}
		else
		{
			int lp_index = SCH__Get_LPx_INDEX(str_module);

			if(lp_index >= 0)
			{
				if((slot_index >= 0)
				&& (slot_index <  CFG_LP__SLOT_MAX))
				{
					check_flag = 1;

					//
					xCH__LPx__SLOT_STATUS[lp_index][slot_index]->Get__DATA(slot_status);
					slot_title.Format("%1d", slot_index+1);
				}
			}
		}

		if(check_flag > 0)
		{
			CString arm_status;
			CString arm_title;

			if(arm_type.CompareNoCase(STR__A) == 0)
			{
				xCH__ATM_RB__SLOT01_STATUS->Get__DATA(arm_status);	
				xCH__ATM_RB__SLOT01_TITLE->Get__DATA(arm_title);
			}	
			else if(arm_type.CompareNoCase(STR__B) == 0)
			{
				xCH__ATM_RB__SLOT02_STATUS->Get__DATA(arm_status);	
				xCH__ATM_RB__SLOT02_TITLE->Get__DATA(arm_title);
			}	

			if((arm_status.CompareNoCase(STR__NONE)  == 0)
			|| (slot_status.CompareNoCase(STR__NONE) != 0))	
			{
				int alarm_id;
				CString str_msg;
				CString str_bff;
				CString r_act;

				alarm_id = ALID__PICK_ERROR__WAFER_MITMATCH;

				str_bff.Format("아래와 같이 PICK 명령을 처리 후 Wafer 정보에 문제가 발생 했습니다. \n");
				str_msg += str_bff;

				str_bff.Format("   PICK 명령은 %s(%s) -> Arm(%s) 입니다. \n", 
					str_module,str_slot, arm_type);
				str_msg += str_bff;

				str_bff.Format("   현재, GUI Wafer 상태는 Robot(%s) <- %s(%s)이고 %s(%s) <- %s(%s)입니다. \n",
					arm_type, arm_status,arm_title,
					str_module,str_slot, slot_status,slot_title);
				str_msg += str_bff;

				str_msg += "GUI 정보와 실제 Wafer가 일치하는지 확인 부탁합니다.\n";
				str_msg += "   1. 만약, PICK 명령이 제대로 수행되지 않았다면 \n";
				str_msg += "      ABORT를 선택하시고 JOB를 Abort해 주십시요. \n";
				str_msg += "      Robot은 Pause 됩니다. \n";
				str_msg += "   2. 실제 Wafer가 PICK 명령처럼 정상처리 되었다면, RETRY 선택하십시요. \n";
				str_msg += "      GUI 정보가 모두 정상이면 정상적으로 JOB을 진행할 것입니다. \n";

				p_alarm->Popup__ALARM_With_MESSAGE(alarm_id,str_msg,r_act);

				if(r_act.CompareNoCase(STR__RETRY) == 0)
				{
					goto LOOP__RETRY_CHECK;
				}

				xCH__ATM_RB_PAUSE_FLAG->Set__DATA(STR__YES);
				return -1;
			}
		}
	}

	return flag;
}
int  CObj_Fnc__SINGLE_ARM_STD::
SCH__PLACE_TO(CII_OBJECT__VARIABLE *p_variable,
			  CII_OBJECT__ALARM *p_alarm,
			  const bool ex_flag,
			  const CString& arm_type,const CString& str_module,const CString& str_slot)
{
	DECLARE__EXT_CTRL(p_variable);

	if(ATM_RB__Is_Available() < 0)
	{
		return -1;
	}

	if((str_module.CompareNoCase(MODULE__LBA) == 0)
	|| (str_module.CompareNoCase(MODULE__LBB) == 0))
	{
		bool active__ll_align = false;

		if(xCH__ATM_RB__TARGET_LLx_MODE->Check__DATA(STR__ENABLE) > 0)
		{
			if((xCH__ATM_RB__TARGET_LLx_NAME_SET->Check__DATA(str_module) < 0)
			|| (xCH__ATM_RB__TARGET_LLx_SLOT_SET->Check__DATA(str_slot)   < 0))
			{
				active__ll_align = true;
			}
		}

		if(active__ll_align)
		{
			CString cur__trg_name;
			CString cur__trg_slot;

			xCH__ATM_RB__TARGET_LLx_NAME_SET->Get__DATA(cur__trg_name);
			xCH__ATM_RB__TARGET_LLx_SLOT_SET->Get__DATA(cur__trg_slot);

			xCH__ATM_RB__TARGET_LLx_NAME_SET->Set__DATA("");
			xCH__ATM_RB__TARGET_LLx_SLOT_SET->Set__DATA("");

			//
			int alarm_id = ALID__ALx_LLx_TARGET_NAME_ERROR;
			CString alm_msg;
			CString alm_bff;
			CString r_act;

			alm_bff.Format("AL's \"L/L target name\" is \"%s(%s)\". \n", cur__trg_name,cur__trg_slot);
			alm_msg += alm_bff;

			alm_bff.Format("L/L name to place is \"%s\". \n", str_module);
			alm_msg += alm_bff;

			//
			p_alarm->Check__ALARM(alarm_id,r_act);
			p_alarm->Post__ALARM_With_MESSAGE(alarm_id,alm_msg);
		}
	}

	// ...
	CStringArray l_para;

	// ...
	{
		l_para.RemoveAll();
		l_para.Add(arm_type);
		l_para.Add(str_module);
		l_para.Add(str_slot);
	}

	// ...
	int flag;

	if(ex_flag == false)
	{
		flag = pATM_RB__OBJ_CTRL->Call__OBJ_MODE(ATM_CMMD__PLACE,l_para);
	}
	else
	{
		flag = pATM_RB__OBJ_CTRL->Call__OBJ_MODE(ATM_CMMD__XPLACE,l_para);	
	}

	if(flag < 0)
	{
		// ...
		{
			int alarm_id;
			CString str_msg;
			CString str_bff;
			CString r_act;

			alarm_id = ALID__MOVE_ERROR__WAFER_CONFIRM;

			str_bff.Format("Wafer가 Arm[%s]에서 %s[%s]으로 이동 되었나요?\n",
				arm_type,
				str_module,
				str_slot);
			str_msg += str_bff;

			str_bff.Format("GUI상의 Wafer 정보와 실제 Wafer가 일치하는지 확인하십시요.\n");
			str_msg += str_bff;

			str_msg += "만약, 일치하지 않는다면 아래의 [YES]나 [NO]를 선택해 주십시요. \n";
			str_msg += "일치한다면, 아래의 [IGNORE]를 선택해야 합니다. \n";

			str_bff.Format("1. 실제로 Wafer가 Module[%s]로 이동 되어 있으면,", str_module);
			str_msg += str_bff;
			str_msg += "       [YES]를 선택하십시요. \n";
			str_bff.Format("2. 실제로 Wafer가 Module[%s]로 이동 되지 않았다면,", str_module);
			str_msg += str_bff;
			str_msg += "       [NO]를 선택하십시요. \n";			
			str_bff.Format("3. 현재 상태가 맞다면, [IGNORE]를 선택하십시요. \n");
			str_msg += str_bff;

			p_alarm->Popup__ALARM_With_MESSAGE(alarm_id,str_msg,r_act);

			if(r_act.CompareNoCase(STR__YES) == 0)
			{
				// Arm -> Module

				// ....
				CString slot_status;
				CString slot_title;
				int check_flag = -1;

				int slot_index = atoi(str_slot) - 1;

				if(arm_type.CompareNoCase(STR__A) == 0)
				{
					check_flag = 1;

					//
					xCH__ATM_RB__SLOT01_STATUS->Get__DATA(slot_status);	
					xCH__ATM_RB__SLOT01_TITLE->Get__DATA(slot_title);

					xCH__ATM_RB__SLOT01_STATUS->Set__DATA(STR__NONE);	
					xCH__ATM_RB__SLOT01_TITLE->Set__DATA("");
				}	
				else if(arm_type.CompareNoCase(STR__B) == 0)
				{
					check_flag = 1;

					//
					xCH__ATM_RB__SLOT02_STATUS->Get__DATA(slot_status);	
					xCH__ATM_RB__SLOT02_TITLE->Get__DATA(slot_title);

					xCH__ATM_RB__SLOT02_STATUS->Set__DATA(STR__NONE);	
					xCH__ATM_RB__SLOT02_TITLE->Set__DATA("");
				}	

				if(check_flag > 0)
				{
					if(str_module.CompareNoCase(MODULE__AL1) == 0)
					{
						xCH__AL1__SLOT01_STATUS->Set__DATA(slot_status);
						xCH__AL1__SLOT01_TITLE->Set__DATA(slot_title);
					}
					else if(str_module.CompareNoCase(MODULE__LBA) == 0)
					{
						int ll_i = _LLx_INDEX__LBA;
						int slot_max = iLLx_SLOT_MAX[ll_i];

						if((slot_index >= 0)
						&& (slot_index <  slot_max))	
						{
							xEXT_CH__LLx__SLOT_STATUS[ll_i][slot_index]->Set__DATA(slot_status);
							xEXT_CH__LLx__SLOT_TITLE[ll_i][slot_index]->Set__DATA(slot_title);
						}
					}
					else if(str_module.CompareNoCase(MODULE__LBB) == 0)
					{
						int ll_i = _LLx_INDEX__LBB;
						int slot_max = iLLx_SLOT_MAX[ll_i];

						if((slot_index >= 0)
						&& (slot_index <  slot_max))	
						{
							xEXT_CH__LLx__SLOT_STATUS[ll_i][slot_index]->Set__DATA(slot_status);
							xEXT_CH__LLx__SLOT_TITLE[ll_i][slot_index]->Set__DATA(slot_title);
						}
					}
					else if(str_module.CompareNoCase(MODULE__BUFFER1) == 0)
					{
						if((slot_index >= 0)
						&& (slot_index <  CFG_LP__SLOT_MAX))
						{
							xEXT_CH__BUFFER1__SLOT_STATUS[slot_index]->Set__DATA(slot_status);
							xEXT_CH__BUFFER1__SLOT_TITLE[slot_index]->Set__DATA(slot_title);
						}
					}
					else if(str_module.CompareNoCase(MODULE__BUFFER2) == 0)
					{
						if((slot_index >= 0)
						&& (slot_index <  CFG_LP__SLOT_MAX))
						{
							xEXT_CH__BUFFER2__SLOT_STATUS[slot_index]->Set__DATA(slot_status);
							xEXT_CH__BUFFER2__SLOT_TITLE[slot_index]->Set__DATA(slot_title);
						}
					}
					else
					{
						int lp_index = SCH__Get_LPx_INDEX(str_module);

						if(lp_index >= 0)
						{
							if((slot_index >= 0)
							&& (slot_index <  CFG_LP__SLOT_MAX))
							{
								xCH__LPx__SLOT_STATUS[lp_index][slot_index]->Set__DATA(slot_status);
							}
						}
					}
				}
			}
			else if(r_act.CompareNoCase(STR__NO) == 0)
			{
				// Module -> Arm

				// ....
				CString slot_status;
				CString slot_title;
				int check_flag = -1;

				int slot_index = atoi(str_slot) - 1;

				if(str_module.CompareNoCase(MODULE__AL1) == 0)
				{
					check_flag = 1;

					//
					xCH__AL1__SLOT01_STATUS->Get__DATA(slot_status);
					xCH__AL1__SLOT01_TITLE->Get__DATA(slot_title);

					xCH__AL1__SLOT01_STATUS->Set__DATA(STR__NONE);
					xCH__AL1__SLOT01_TITLE->Set__DATA("");
				}
				else if(str_module.CompareNoCase(MODULE__LBA) == 0)
				{
					int ll_i = _LLx_INDEX__LBA;
					int slot_max = iLLx_SLOT_MAX[ll_i];

					if((slot_index >= 0)
					&& (slot_index <  slot_max))	
					{
						check_flag = 1;
						
						xEXT_CH__LLx__SLOT_STATUS[ll_i][slot_index]->Get__DATA(slot_status);
						xEXT_CH__LLx__SLOT_TITLE[ll_i][slot_index]->Get__DATA(slot_title);

						xEXT_CH__LLx__SLOT_STATUS[ll_i][slot_index]->Set__DATA(STR__NONE);
						xEXT_CH__LLx__SLOT_TITLE[ll_i][slot_index]->Set__DATA("");
					}
				}
				else if(str_module.CompareNoCase(MODULE__LBB) == 0)
				{
					int ll_i = _LLx_INDEX__LBB;
					int slot_max = iLLx_SLOT_MAX[ll_i];

					if((slot_index >= 0)
					&& (slot_index <  slot_max))	
					{
						check_flag = 1;

						xEXT_CH__LLx__SLOT_STATUS[ll_i][slot_index]->Get__DATA(slot_status);
						xEXT_CH__LLx__SLOT_TITLE[ll_i][slot_index]->Get__DATA(slot_title);

						xEXT_CH__LLx__SLOT_STATUS[ll_i][slot_index]->Set__DATA(STR__NONE);
						xEXT_CH__LLx__SLOT_TITLE[ll_i][slot_index]->Set__DATA("");
					}
				}
				else if(str_module.CompareNoCase(MODULE__BUFFER1) == 0)
				{
					if((slot_index >= 0)
					&& (slot_index <  CFG_LP__SLOT_MAX))
					{
						check_flag = 1;

						//
						xEXT_CH__BUFFER1__SLOT_STATUS[slot_index]->Get__DATA(slot_status);
						xEXT_CH__BUFFER1__SLOT_TITLE[slot_index]->Get__DATA(slot_title);

						xEXT_CH__BUFFER1__SLOT_STATUS[slot_index]->Set__DATA(STR__NONE);
						xEXT_CH__BUFFER1__SLOT_TITLE[slot_index]->Set__DATA("");
					}
				}
				else if(str_module.CompareNoCase(MODULE__BUFFER2) == 0)
				{
					if((slot_index >= 0)
					&& (slot_index <  CFG_LP__SLOT_MAX))
					{
						check_flag = 1;

						//
						xEXT_CH__BUFFER2__SLOT_STATUS[slot_index]->Get__DATA(slot_status);
						xEXT_CH__BUFFER2__SLOT_TITLE[slot_index]->Get__DATA(slot_title);

						xEXT_CH__BUFFER2__SLOT_STATUS[slot_index]->Set__DATA(STR__NONE);
						xEXT_CH__BUFFER2__SLOT_TITLE[slot_index]->Set__DATA("");
					}
				}
				else
				{
					int lp_index = SCH__Get_LPx_INDEX(str_module);

					if(lp_index >= 0)
					{
						if((slot_index >= 0)
						&& (slot_index <  CFG_LP__SLOT_MAX))
						{
							check_flag = 1;

							//
							xCH__LPx__SLOT_STATUS[lp_index][slot_index]->Get__DATA(slot_status);

							xCH__LPx__SLOT_STATUS[lp_index][slot_index]->Set__DATA(STR__NONE);
						}
					}
				}

				if(check_flag > 0)
				{
					if(arm_type.CompareNoCase(STR__A) == 0)
					{
						xCH__ATM_RB__SLOT01_STATUS->Set__DATA(slot_status);	
						xCH__ATM_RB__SLOT01_TITLE->Set__DATA(slot_title);
					}	
					else if(arm_type.CompareNoCase(STR__B) == 0)
					{
						xCH__ATM_RB__SLOT02_STATUS->Set__DATA(slot_status);	
						xCH__ATM_RB__SLOT02_TITLE->Set__DATA(slot_title);
					}	
				}
			}
		}

		// ...
		{
			int alarm_id;
			CString str_msg;
			CString str_bff;
			CString r_act;

			alarm_id = ALID__USER_CHECK__WAFER_CONFIRM;

			str_bff.Format("GUI상의 Wafer 정보와 실제 Wafer 정보가 일치하는지 확인하십시요.\n");
			str_msg += str_bff;

			str_msg += "만약, 일치하지 않는다면 아래와 같이 처리해 주십시요.\n";

			str_msg += "   1. 현재 실행 중인 Job을 Abort시킨다. \n";
			str_msg += "   2. CTC Resync-Page에서 Wafer 정보를 실제와 일치시킨다. \n";
			str_msg += "   3. Tool-Clear를 실행시킨다. \n";

			p_alarm->Popup__ALARM_With_MESSAGE(alarm_id,str_msg,r_act);
		}
	}
	else if(flag > 0)
	{
LOOP__RETRY_CHECK:

		// Material Place : Check ...
		CString slot_status;
		CString slot_title;
		int check_flag = -1;

		int slot_index = atoi(str_slot) - 1;

		if(str_module.CompareNoCase(MODULE__AL1) == 0)
		{
			check_flag = 1;

			if(slot_index == 0)
			{
				xCH__AL1__SLOT01_STATUS->Get__DATA(slot_status);
				xCH__AL1__SLOT01_TITLE->Get__DATA(slot_title);
			}
			else if(slot_index == 1)
			{
				xCH__AL1__SLOT02_STATUS->Get__DATA(slot_status);
				xCH__AL1__SLOT02_TITLE->Get__DATA(slot_title);
			}
			else
			{
				slot_status = "UNKNOWN";
				slot_title  = "??";
			}
		}
		else if(str_module.CompareNoCase(MODULE__LBA) == 0)
		{
			int ll_i = _LLx_INDEX__LBA;
			int slot_max = iLLx_SLOT_MAX[ll_i];

			if((slot_index >= 0)
			&& (slot_index <  slot_max))	
			{
				check_flag = 1;

				xEXT_CH__LLx__SLOT_STATUS[ll_i][slot_index]->Get__DATA(slot_status);
				xEXT_CH__LLx__SLOT_TITLE[ll_i][slot_index]->Get__DATA(slot_title);
			}
		}
		else if(str_module.CompareNoCase(MODULE__LBB) == 0)
		{
			int ll_i = _LLx_INDEX__LBB;
			int slot_max = iLLx_SLOT_MAX[ll_i];

			if((slot_index >= 0)
			&& (slot_index <  slot_max))	
			{
				check_flag = 1;

				xEXT_CH__LLx__SLOT_STATUS[ll_i][slot_index]->Get__DATA(slot_status);
				xEXT_CH__LLx__SLOT_TITLE[ll_i][slot_index]->Get__DATA(slot_title);
			}
		}
		else if(str_module.CompareNoCase(MODULE__BUFFER1) == 0)
		{
			if((slot_index >= 0)
			&& (slot_index <  CFG_LP__SLOT_MAX))
			{
				check_flag = 1;

				//
				xEXT_CH__BUFFER1__SLOT_STATUS[slot_index]->Get__DATA(slot_status);
				xEXT_CH__BUFFER1__SLOT_TITLE[slot_index]->Get__DATA(slot_title);
			}
		}
		else if(str_module.CompareNoCase(MODULE__BUFFER2) == 0)
		{
			if((slot_index >= 0)
			&& (slot_index <  CFG_LP__SLOT_MAX))
			{
				check_flag = 1;

				//
				xEXT_CH__BUFFER2__SLOT_STATUS[slot_index]->Get__DATA(slot_status);
				xEXT_CH__BUFFER2__SLOT_TITLE[slot_index]->Get__DATA(slot_title);
			}
		}
		else
		{
			int lp_index = SCH__Get_LPx_INDEX(str_module);

			if(lp_index >= 0)
			{
				if((slot_index >= 0)
					&& (slot_index <  CFG_LP__SLOT_MAX))
				{
					check_flag = 1;

					//
					xCH__LPx__SLOT_STATUS[lp_index][slot_index]->Get__DATA(slot_status);
					slot_title.Format("%1d", slot_index+1);
				}
			}
		}

		if(check_flag > 0)
		{
			CString arm_status;
			CString arm_title;

			if(arm_type.CompareNoCase(STR__A) == 0)
			{
				xCH__ATM_RB__SLOT01_STATUS->Get__DATA(arm_status);	
				xCH__ATM_RB__SLOT01_TITLE->Get__DATA(arm_title);
			}	
			else if(arm_type.CompareNoCase(STR__B) == 0)
			{
				xCH__ATM_RB__SLOT02_STATUS->Get__DATA(arm_status);	
				xCH__ATM_RB__SLOT02_TITLE->Get__DATA(arm_title);
			}	

			if((arm_status.CompareNoCase(STR__NONE)  != 0)
			|| (slot_status.CompareNoCase(STR__NONE) == 0))	
			{
				// ...
				int alarm_id;
				CString str_msg;
				CString str_bff;
				CString r_act;

				alarm_id = ALID__PLACE_ERROR__WAFER_MITMATCH;

				str_bff.Format("아래와 같이 PLACE 명령을 처리 후 Wafer 정보에 문제가 발생 했습니다. \n");
				str_msg += str_bff;

				str_bff.Format("   PLACE 명령은 Arm(%s) -> %s(%s) 입니다. \n", 
					arm_type, str_module,str_slot);
				str_msg += str_bff;

				str_bff.Format("   현재, GUI Wafer 상태는 Robot(%s) <- %s(%s)이고 %s(%s) <- %s(%s)입니다. \n",
					arm_type, arm_status,arm_title,
					str_module,str_slot, slot_status,slot_title);
				str_msg += str_bff;

				str_msg += "GUI 정보와 실제 Wafer가 일치하는지 확인 부탁합니다.\n";
				str_msg += "   1. 만약, PLACE 명령이 제대로 수행되지 않았다면 \n";
				str_msg += "      ABORT를 선택하시고 JOB를 Abort해 주십시요. \n";
				str_msg += "      Robot은 Pause 됩니다. \n";
				str_msg += "   2. 실제 Wafer가 PICK 명령처럼 정상처리 되었다면, RETRY 선택하십시요. \n";
				str_msg += "      GUI 정보가 모두 정상이면 정상적으로 JOB을 진행할 것입니다. \n";

				p_alarm->Popup__ALARM_With_MESSAGE(alarm_id,str_msg,r_act);

				if(r_act.CompareNoCase(STR__RETRY) == 0)
				{
					goto LOOP__RETRY_CHECK;
				}

				// ...
				{
					xCH__ATM_RB_PAUSE_FLAG->Set__DATA(STR__YES);
				}
				return -1;
			}
		}
	}

	return flag;
}


//------------------------------------------------------------------------------------------------
int  CObj_Fnc__SINGLE_ARM_STD::
SCH__CHECK_PICK_MODULE__READY(CII_OBJECT__VARIABLE* p_variable,
							  const bool ex_flag,
							  const CString& para_module,const CString& para_slot,
							  const int maint_flag)
{
	DECLARE__EXT_CTRL(p_variable);

	CString log_id = "SCH__CHECK_PICK_MODULE__READY()";

	// ...
	int ll_i = Get__LLx_INDEX(para_module);

	if(para_module.CompareNoCase("AL1") == 0)
	{
		if(AL1__Is_Available() < 0)
		{
			return -1;
		}
	}
	else if(ll_i >= 0)
	{
		if(LLx__Is_Available(ll_i) < 0)
		{
			return -1;
		}

		if(LLx__Is_ATM(ll_i) < 0)
		{
			if(SCH_CALL__LLx_VENT(ll_i, p_variable, log_id, "1") < 0)
			{
				return -1;
			}
		}

		if(SCH__LLx_PREPMATER(ll_i, para_slot) < 0)
		{
			return -1;
		}
	}
	else
	{
		CString lp_name;
		int i;

		for(i=0; i<CFG_LP_LIMIT; i++)
		{
			lp_name.Format("LP%1d",i+1);
			if(lp_name != para_module)
			{
				continue;
			}

			if(LPx__Is_Available(i) < 0)
			{
				return -1;
			}
			break;
		}
	}

	return 1;
}
int  CObj_Fnc__SINGLE_ARM_STD::
SCH__CHECK_PICK_MODULE__COMPLETE(CII_OBJECT__VARIABLE* p_variable,
								 const bool ex_flag,
								 const CString& para_module,const CString& para_slot,
								 const int maint_flag)
{
	DECLARE__EXT_CTRL(p_variable);

	int ll_i = Get__LLx_INDEX(para_module);

	if(para_module.CompareNoCase("AL1") == 0)
	{

	}
	else if(ll_i >= 0)
	{
		if(ex_flag == FALSE)
		{
			if(SCH__LLx_COMPMATER(ll_i, para_slot) < 0)
			{
				return -1;
			}
		}
	}
	else
	{
		CString lp_name;
		int i;

		for(i=0;i<CFG_LP_LIMIT;i++)
		{
			lp_name.Format("LP%1d",i+1);
			if(lp_name != para_module)
			{
				continue;
			}

			break;
		}
	}

	return 1;
}


//
int  CObj_Fnc__SINGLE_ARM_STD:: 
SCH__CHECK_PLACE_MODULE__READY(CII_OBJECT__VARIABLE* p_variable,
							   const bool ex_flag,
							   const CString& para_module,
							   const CString& para_slot,
							   const int maint_flag)
{
	DECLARE__EXT_CTRL(p_variable);

	CString log_id = "SCH__CHECK_PLACE_MODULE__READY()";

	// ...
	int ll_i = Get__LLx_INDEX(para_module);

	if(para_module.CompareNoCase("AL1") == 0)
	{
		if(AL1__Is_Available() < 0)
		{
			return -1;
		}
	}
	else if(ll_i >= 0)
	{
		if(LLx__Is_Available(ll_i) < 0)
		{
			return -1;
		}

		if(LLx__Is_ATM(ll_i) < 0)
		{
			if(SCH_CALL__LLx_VENT(ll_i, p_variable, log_id, "1") < 0)
			{
				return -1;
			}
		}

		if(SCH__LLx_PREPMATER(ll_i, para_slot) < 0)
		{
			return -1;
		}
	}
	else
	{
		CString lp_name;
		int i;

		for(i=0;i<CFG_LP_LIMIT;i++)
		{
			lp_name.Format("LP%1d",i+1);
			if(lp_name != para_module)
			{
				continue;
			}

			if(LPx__Is_Available(i) < 0)
			{
				return -1;
			}
			break;
		}
	}

	return 1;
}
int  CObj_Fnc__SINGLE_ARM_STD:: 
SCH__CHECK_PLACE_MODULE__COMPLETE(CII_OBJECT__VARIABLE* p_variable,
								  const bool ex_flag,
								  const CString& arm_type,
								  const CString& para_module,const CString& para_slot,
								  const int maint_flag)
{
	DECLARE__EXT_CTRL(p_variable);

	// ...
	int ll_i = Get__LLx_INDEX(para_module);

	if(para_module.CompareNoCase("AL1") == 0)
	{
		if(xEXT_CH__SCH_ALIGN_DEVICE->Check__DATA(STR__ATM_RB) < 0)
		{
			if(ex_flag == false)
			{
				CStringArray l_para;
				l_para.Add(para_slot);

				if(maint_flag < 0)
				{
					if(pAL1__OBJ_CTRL->Run__OBJ_MODE(AL_CMMD__ALIGN,l_para) < 0)
					{
						return -1;
					}
				}
				else
				{
					if(pAL1__OBJ_CTRL->Call__OBJ_MODE(AL_CMMD__ALIGN,l_para) < 0)
					{
						return -1;
					}
				}
			}
		}
	}
	else if(ll_i >= 0)
	{
		xCH__ATM_RB__SCH_STS_TO_LLx[ll_i]->Set__DATA("");

		int r_flag = SCH__LLx_COMPMATER(ll_i, para_slot);
		if(r_flag < 0)		return -1;
	}
	else if((para_module.CompareNoCase(MODULE__BUFFER1) == 0)
		 || (para_module.CompareNoCase(MODULE__BUFFER2) == 0))
	{
		if(maint_flag > 0)
		{
			int slot_index = atoi(para_slot) - 1;

			if((slot_index >= 0) && (slot_index < CFG_LP__SLOT_MAX))
			{
				CString var_data;				
				xCH__CFG_DB_BUFFER_WAFER_CLEAN_TIME->Get__DATA(var_data);

				if(para_module.CompareNoCase(MODULE__BUFFER1) == 0)
				{
					xEXT_CH__BUFFER1__SLOT_WAIT_SEC[slot_index]->Set__DATA(var_data);
				}
				else if(para_module.CompareNoCase(MODULE__BUFFER2) == 0)
				{
					xEXT_CH__BUFFER2__SLOT_WAIT_SEC[slot_index]->Set__DATA(var_data);
				}
			}
		}
	}
	else
	{
		CString lp_name;
		int i;

		for(i=0;i<CFG_LP_LIMIT;i++)
		{
			lp_name.Format("LP%1d",i+1);
			if(lp_name != para_module)
			{
				continue;
			}

			break;
		}
	}

	return 1;
}


//------------------------------------------------------------------------------------------------
int  CObj_Fnc__SINGLE_ARM_STD::
SCH__LPx_TO_LLx_OF_ROUTE_TYPE(CII_OBJECT__VARIABLE *p_variable,
							  const int port_id,
							  const int slot_id)
{
	if(sEXT_CH__SCH_MODE_LLx_IN->Check__DATA(_SCH_MODE__ROUTE) < 0)
	{
		return 0;
	}

	// ...
	CUIntArray l__sch_ll;

	// ...
	{
		CStringArray l_ll_id;
		CStringArray l_ll_mode;
		CStringArray l_ll_slot;

		xSCH_MATERIAL_CTRL->Get__LLx_IN_OF_EDIT_TYPE(port_id,slot_id, l_ll_id,l_ll_mode,l_ll_slot);

		int i_limit = l_ll_id.GetSize();
		int i;

		for(i=0; i<i_limit; i++)
		{
			int ll_id = atoi(l_ll_id[i]);

			CString str_mode = l_ll_mode[i];
			CString str_slot = l_ll_slot[i];

			if((str_mode.CompareNoCase("ALL") == 0)
			|| (str_mode.CompareNoCase("ONLY_INPUT") == 0))
			{
				if((str_slot.CompareNoCase("11") == 0)
				|| (str_slot.CompareNoCase("10") == 0)
				|| (str_slot.CompareNoCase("01") == 0))
				{
					l__sch_ll.Add(ll_id);
				}
			}
		}
	}

	// ...
	CUIntArray l_job_lp;
	xSCH_MATERIAL_CTRL->Get__JOB_PORT_LIST(l_job_lp);

	int job_cnt = l_job_lp.GetSize();

	// ...
	CString log_id = "";
	log_id.Format("SCH__LPx_TO_LLx_OF_ROUTE_TYPE() <- LP%1d(%1d) \n", port_id,slot_id);

	int i_limit = l__sch_ll.GetSize();
	int i;

	for(i=0; i<i_limit; i++)
	{
		int cur__pick_count = 0;

		int db_index = port_id - 1;
		if(db_index <  0)				continue;
		if(db_index >= iLPx_SIZE)		continue;

		CString ch_data = xCH__LPx__PICK_COUNT[db_index]->Get__STRING();
		cur__pick_count = atoi(ch_data);

		// LLx Check ...
		int ll_i = l__sch_ll[i] - 1;

		if((ll_i >= 0) && (ll_i < iLLx_SIZE))
		{
			if(xEXT_CH__SCH_DB_LLx_USE_FLAG[ll_i]->Check__DATA(STR__ENABLE) < 0)
			{
				continue;
			}

			if((xEXT_CH__SCH_DB_LLx_MODE_TYPE[ll_i]->Check__DATA(LBx_MODE__ALL) > 0)
			|| (xEXT_CH__SCH_DB_LLx_MODE_TYPE[ll_i]->Check__DATA(LBx_MODE__ONLY_INPUT) > 0))
			{
				if(job_cnt == 1)
				{
					if((LLx__Check_Empty__InSlot(ll_i) > 0)
					&& (LLx__Check_CtcInUse_Or_Standby(ll_i) > 0))
					{
						if(xEXT_CH__LLx__IN_OUT_FLAG[ll_i]->Check__DATA("IN") > 0)
						{
							return (ll_i + 1);
						}
					}
				}
				else
				{
					if((LLx__Check_Empty__InSlot(ll_i) > 0)
					&& (LLx__Is_Available(ll_i) > 0))
					{
						if(xEXT_CH__LLx__IN_OUT_FLAG[ll_i]->Check__DATA("IN") > 0)
						{
							return (ll_i + 1);
						}
					
						if(cur__pick_count < 1)
						{
							if(LLx__Is_ATM(ll_i) < 0)
							{
								if(SCH_RUN__LLx_VENT(ll_i, p_variable, log_id, "1") > 0)
								{
									xEXT_CH__LLx__IN_OUT_FLAG[ll_i]->Set__DATA("IN");
									return (ll_i + 1);
								}
							}
						}
					}
				}
			}

			// ...
		}
	}

	return -1;
}


int  CObj_Fnc__SINGLE_ARM_STD::
SCH__LBx_PUMP(CII_OBJECT__VARIABLE *p_variable,const CString& lbx_name, const CString& log_xxx)
{
	DECLARE__EXT_CTRL(p_variable);

	CString log_id = log_xxx;
	log_id = " -> ";
	log_id = "SCH__LBx_PUMP()";

	// ...
	int ll_i = Get__LLx_INDEX(lbx_name);

	if(ll_i >= 0)
	{
		if(LLx__Is_Available(ll_i) < 0)
		{
			return -1;
		}

		if(xEXT_CH__SCH_DB_LLx_MODE_TYPE[ll_i]->Check__DATA(LBx_MODE__ONLY_OUTPUT) > 0)
		{
			if(LLx__Check_All_Empty(ll_i) < 0)
			{
				return -1;
			}
		}
		else 
		{
			if(LLx__Get_Occupied__Total_OutSlot(ll_i) > 0)
			{
				return -1;
			}
		}

		SCH_RUN__LLx_PUMP(ll_i, p_variable, log_id, "1");
		return 1;
	}

	return -1;
}

int  CObj_Fnc__SINGLE_ARM_STD::
SCH__CHECK_LBi_ATM_PRESSURE(CII_OBJECT__VARIABLE *p_variable,
							CII_OBJECT__ALARM* p_alarm)
{
	int ll_limit = iLLx_SIZE;
	int ll_i;

	for(ll_i=0; ll_i<ll_limit; ll_i++)
	{
		int active_ll = xEXT_CH__SCH_DB_LLx_USE_FLAG[1]->Check__DATA(STR__ENABLE);
		if(active_ll < 0)		continue;

		// ...
		int lb_slot;

		if(xEXT_CH__SCH_DB_LLx_MODE_TYPE[ll_i]->Check__DATA(LBx_MODE__ONLY_INPUT) > 0)
		{
			if(xEXT_CH__LLx__IN_OUT_FLAG[ll_i]->Check__DATA("IN") < 0)
			{
				return -1;
			}

			if(LLx__Get_Empty__InSlot(ll_i, lb_slot) < 0)		return -1;
			if(LLx__Is_Available(ll_i) < 0)						return -1;

			if(LLx__Is_ATM(ll_i) < 0)
			{
				if(SCH__LLx_PRESSURE_ERROR(ll_i, p_variable,p_alarm) < 0)
				{
					return -1;
				}
			}		
			return 1;
		}

		if(xEXT_CH__SCH_DB_LLx_MODE_TYPE[ll_i]->Check__DATA(LBx_MODE__ALL) > 0)
		{
			if(xEXT_CH__LLx__IN_OUT_FLAG[ll_i]->Check__DATA("IN") > 0)
			{
				if((LLx__Get_Empty__InSlot(ll_i, lb_slot) > 0)
				&& (LLx__Is_Available(ll_i) > 0))
				{
					if(LLx__Is_ATM(ll_i) > 0)			
					{
						return 1;
					}
					else
					{
						if(SCH__LLx_PRESSURE_ERROR(ll_i, p_variable,p_alarm) > 0)
						{
							return 1;
						}
					}
				}
			}
		}

		// ...
	}

	return -1;
}

int  CObj_Fnc__SINGLE_ARM_STD::
SCH__CHECK_DUMMY_PORT(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM* p_alarm)
{
	int dummy_lp = Fnc__GET_DUMMY_PORT();
	if(dummy_lp < 0)		return -1;

	if(xSCH_MATERIAL_CTRL->Check__MATERIAL_TO_PROCESS_IN_LPx(dummy_lp) > 0)
	{
		return -2;
	}

	// ...
	{
		CUIntArray l_ptn;
		xSCH_MATERIAL_CTRL->Get__JOB_PORT_LIST(l_ptn);

		int i_limit = l_ptn.GetSize();
		int i;

		for(i=0; i<i_limit; i++)
		{
			int lp_id = l_ptn[i];

			if(lp_id <  1)				continue;
			if(lp_id >  iLPx_SIZE)		continue;
			if(lp_id == dummy_lp)		continue;

			if(xCH__LPx__PORT_STATUS[lp_id - 1]->Check__DATA(STR__BUSY) < 0)
			{
				continue;
			}
			if(xSCH_MATERIAL_CTRL->Check__Pause_PORT_ID(lp_id) < 0)
			{
				continue;
			}

			xSCH_MATERIAL_CTRL->Resume__PORT_ID(lp_id);

			printf("===================================================\n");
			printf(" * CObj_Fnc__SINGLE_ARM_STD::SCH__CHECK_DUMMY_PORT() .. \n");
			printf(" ** lp_id [%1d] - Resume !!! \n\n", lp_id);
			printf("===================================================\n\n");
		}
	}
	return 1;
}

int  CObj_Fnc__SINGLE_ARM_STD::
SCH__CAN_PLACE_LBi(const int vent_check)
{
	int ll_limit = iLLx_SIZE;
	int ll_i;

	for(ll_i=0; ll_i<ll_limit; ll_i++)
	{
		int active_ll = xEXT_CH__SCH_DB_LLx_USE_FLAG[ll_i]->Check__DATA(STR__ENABLE);
		if(active_ll < 0)		continue;

		// ...
		int lb_slot;

		if(xEXT_CH__SCH_DB_LLx_MODE_TYPE[ll_i]->Check__DATA(LBx_MODE__ONLY_INPUT) > 0)
		{
			if(xEXT_CH__LLx__IN_OUT_FLAG[ll_i]->Check__DATA("IN") < 0)
			{
				continue;
			}

			if(vent_check > 0)
			{
				if(xEXT_CH__LLx__VENTING_FLAG[ll_i]->Check__DATA(STR__YES) > 0)
				{
					if(LLx__Check_CtcInUse_Or_Standby(ll_i) > 0)
					{
						return 1;
					}
				}
			}

			if(LLx__Get_Empty__InSlot(ll_i, lb_slot) < 0)		continue;
			if(LLx__Is_Available(ll_i)  < 0)					continue;;
			if(LLx__Is_ATM(ll_i) < 0)							continue;

			return 1;
		}

		if(xEXT_CH__SCH_DB_LLx_MODE_TYPE[ll_i]->Check__DATA(LBx_MODE__ALL) > 0)
		{
			if(xEXT_CH__LLx__IN_OUT_FLAG[ll_i]->Check__DATA("IN") > 0)
			{
				if(vent_check > 0)
				{
					if(xEXT_CH__LLx__VENTING_FLAG[ll_i]->Check__DATA(STR__YES) > 0)
					{
						if(LLx__Check_CtcInUse_Or_Standby(ll_i) > 0)
						{
							return 1;
						}
					}
				}

				if((LLx__Get_Empty__InSlot(ll_i, lb_slot) > 0)
				&& (LLx__Is_Available(ll_i) > 0))
				{
					if(LLx__Is_ATM(ll_i) > 0)			
					{
						return 1;
					}
				}
			}
		}
	}

	return -1;
}
int  CObj_Fnc__SINGLE_ARM_STD::
SCH__CAN_PICK_LBo()
{
	int ll_limit = iLLx_SIZE;
	int ll_i;

	for(ll_i=0; ll_i<ll_limit; ll_i++)
	{
		int active_ll = xEXT_CH__SCH_DB_LLx_USE_FLAG[ll_i]->Check__DATA(STR__ENABLE);
		if(active_ll < 0)			continue;

		// ...
		int lb_slot;

		if(xEXT_CH__SCH_DB_LLx_MODE_TYPE[ll_i]->Check__DATA(LBx_MODE__ONLY_OUTPUT) > 0)
		{
			if(xEXT_CH__LLx__IN_OUT_FLAG[ll_i]->Check__DATA("OUT") < 0)
			{
				return -1;
			}

			if(LLx__Get_Occupied__OutSlot(ll_i, lb_slot) < 0)		return -1;
			if(LLx__Is_Available(ll_i) < 0)							return -1;
			if(LLx__Is_ATM(ll_i) < 0)								return -1;

			return 1;
		}

		if(xEXT_CH__SCH_DB_LLx_MODE_TYPE[ll_i]->Check__DATA(LBx_MODE__ALL) > 0)
		{
			if(xEXT_CH__LLx__IN_OUT_FLAG[ll_i]->Check__DATA("OUT") > 0)
			{
				if((LLx__Get_Occupied__OutSlot(ll_i, lb_slot) > 0)
				&& (LLx__Is_Available(ll_i) > 0))
				{
					if(LLx__Is_ATM(ll_i) > 0)			
					{
						return 1;
					}
				}
			}
		}
	}
	
	return -1;
}

int  CObj_Fnc__SINGLE_ARM_STD::SCH__CHECK_LBo_OCCUPIED()
{
	int ll_limit = iLLx_SIZE;
	int ll_i;

	for(ll_i=0; ll_i<ll_limit; ll_i++)
	{
		if(xEXT_CH__SCH_DB_LLx_MODE_TYPE[ll_i]->Check__DATA(LBx_MODE__ONLY_OUTPUT) > 0)
		{
			return LLx__Get_Occupied__Total_OutSlot(ll_i);
		}
	}
	return -1;
}
int  CObj_Fnc__SINGLE_ARM_STD::SCH__CHECK_LBi_EMPTY()
{
	int ll_limit = iLLx_SIZE;
	int ll_i;

	for(ll_i=0; ll_i<ll_limit; ll_i++)
	{
		if(xEXT_CH__SCH_DB_LLx_MODE_TYPE[ll_i]->Check__DATA(LBx_MODE__ONLY_INPUT) > 0)
		{
			return LLx__Get_Empty__Total_InSlot(ll_i);
		}
	}
	return -1;
}

int  CObj_Fnc__SINGLE_ARM_STD::SCH__LBx__CHECK_ONLY_INPUNT()
{
	int ll_limit = iLLx_SIZE;
	int ll_i;

	for(ll_i=0; ll_i<ll_limit; ll_i++)
	{
		if(xEXT_CH__SCH_DB_LLx_MODE_TYPE[ll_i]->Check__DATA(LBx_MODE__ONLY_INPUT) > 0)
		{
			return 1;
		}
	}
	return -1;
}
int  CObj_Fnc__SINGLE_ARM_STD::SCH__LBx__CHECK_ONLY_OUTPUT()
{
	int ll_limit = iLLx_SIZE;
	int ll_i;

	for(ll_i=0; ll_i<ll_limit; ll_i++)
	{
		if(xEXT_CH__SCH_DB_LLx_MODE_TYPE[ll_i]->Check__DATA(LBx_MODE__ONLY_OUTPUT) > 0)
		{
			return 1;
		}
	}
	return -1;
}

CString CObj_Fnc__SINGLE_ARM_STD::SCH__Get_LBx_To_PLACE(CString& ll_slot)
{
	int ll_limit = iLLx_SIZE;
	int ll_i;

	for(ll_i=0; ll_i<ll_limit; ll_i++)
	{
		CString ll_name = Get__LLx_NAME(ll_i);

		if(xEXT_CH__SCH_DB_LLx_MODE_TYPE[ll_i]->Check__DATA(LBx_MODE__ONLY_OUTPUT) > 0)
		{
			continue;
		}

		if((LLx__Is_ATM(ll_i) > 0)
		&& (LLx__Is_Available(ll_i) > 0))
		{
			int slot_id = LLx__Check_Empty__InSlot(ll_i);
			if(slot_id > 0)
			{
				ll_slot.Format("%1d", slot_id);
				return ll_name;
			}
		}	

		/*
		if((LLx__Check_CtcInUse_Or_Standby(ll_i) > 0)
		&& (xEXT_CH__LLx__VENTING_COMP_FLAG[ll_i]->Check__DATA(STR__YES) > 0))	
		{
			if(LLx__Check_Empty__InSlot(ll_i) > 0)
			{
				return ll_name;
			}
		}
		*/
	}

	return "";
}


//------------------------------------------------------------------------------------------------
int  CObj_Fnc__SINGLE_ARM_STD::
SCH__LLx_PREPMATER(const int ll_index,const CString& str_slot)
{
	if(xCH_CFG__SCH_LLx_PREPMATER_USE->Check__DATA(STR__ENABLE) < 0)
	{
		return 1;
	}
	if(xEXT_CH__LLx__CFG_PREPMATER_USE[ll_index]->Check__DATA(STR__ENABLE) < 0)
	{
		return 1;
	}

	if(pLLx__OBJ_CTRL[ll_index] == NULL)
	{
		return -1;
	}

	// ...
	CStringArray l_para;

	l_para.RemoveAll();
	l_para.Add(str_slot);

	return pLLx__OBJ_CTRL[ll_index]->Call__OBJ_MODE("PREPMATER",l_para);
}

int  CObj_Fnc__SINGLE_ARM_STD::
SCH__LLx_COMPMATER(const int ll_index,const CString& str_slot)
{
	if(xCH_CFG__SCH_LLx_COMPMATER_USE->Check__DATA(STR__ENABLE) < 0)
	{
		return 1;
	}
	if(xEXT_CH__LLx__CFG_COMPMATER_USE[ll_index]->Check__DATA(STR__ENABLE) < 0)
	{
		return 1;
	}

	if(pLLx__OBJ_CTRL[ll_index] == NULL)
	{
		return -1;
	}

	// ...
	CStringArray l_para;

	l_para.RemoveAll();
	l_para.Add(str_slot);

	return pLLx__OBJ_CTRL[ll_index]->Call__OBJ_MODE("COMPMATER",l_para);
}

int  CObj_Fnc__SINGLE_ARM_STD
::SCH_CHECK__LLx_PUMP(const int ll_i)
{
	if(xEXT_CH__CFG__TRANSFER_MODE->Check__DATA("VAC") > 0)
	{
		if(LLx__Is_VAC(ll_i) < 0)		
		{
			return 1;
		}
	}
	else
	{
		if(LLx__Is_ATM(ll_i) < 0)
		{
			return 1;
		}
	}
	return -1;
}
int  CObj_Fnc__SINGLE_ARM_STD
::SCH_RUN__LLx_PUMP(const int ll_i,
					CII_OBJECT__VARIABLE *p_variable, 
					const CString& log_id,
					const CString& sub_id)
{
	if(xEXT_CH__LLx__MOVE_FLAG[ll_i]->Check__DATA("YES") > 0)
	{
		return -1;
	}

	DECLARE__EXT_CTRL(p_variable);

	// ...
	{
		CString log_msg;
		CString log_bff;

		CString ll_name = Get__LLx_NAME(ll_i);

		log_msg.Format("SCH_RUN__LLx_PUMP(%s) ... \n", ll_name);
		log_bff.Format(" * log_id <- [%s] \n", log_id);
		log_msg += log_bff;
		log_bff.Format(" * sub_id <- [%s] \n", sub_id);
		log_msg += log_bff;

		xAPP_LOG_CTRL->WRITE__LOG(log_msg);
	}

	if(xEXT_CH__CFG__TRANSFER_MODE->Check__DATA("VAC") > 0)
	{
		if(LLx__Is_VAC(ll_i) < 0)
		{
			sEXT_CH__LLx__UPPER_OBJ_MSG[ll_i]->Set__DATA(log_id);

			pLLx__OBJ_CTRL[ll_i]->Run__OBJECT(LL_CMMD__PUMP);
		}
	}
	else
	{
		if(LLx__Is_ATM(ll_i) < 0)
		{
			sEXT_CH__LLx__UPPER_OBJ_MSG[ll_i]->Set__DATA(log_id);

			pLLx__OBJ_CTRL[ll_i]->Run__OBJECT(LL_CMMD__VENT);
		}
	}
	return 1;
}

int  CObj_Fnc__SINGLE_ARM_STD
::SCH_RUN__LLx_VENT(const int ll_i,
					CII_OBJECT__VARIABLE *p_variable,
					const CString& log_id, 
					const CString& sub_id)
{
	DECLARE__EXT_CTRL(p_variable);

	if(xEXT_CH__LLx__MOVE_FLAG[ll_i]->Check__DATA("YES") > 0)
	{
		return -1;
	}

	// ...
	{
		CString log_msg;
		CString log_bff;

		CString ll_name = Get__LLx_NAME(ll_i);

		log_msg.Format("SCH_RUN__LLx_VENT(%s) ... \n", ll_name);
		log_bff.Format(" * log_id <- [%s] \n", log_id);
		log_msg += log_bff;
		log_bff.Format(" * sub_id <- [%s] \n", sub_id);
		log_msg += log_bff;

		xAPP_LOG_CTRL->WRITE__LOG(log_msg);
	}

	if(LLx__Is_ATM(ll_i) < 0)
	{
		pLLx__OBJ_CTRL[ll_i]->Run__OBJECT(LL_CMMD__VENT);
	}
	return 1;
}
int  CObj_Fnc__SINGLE_ARM_STD
::SCH_CALL__LLx_VENT(const int ll_i,
					 CII_OBJECT__VARIABLE *p_variable,
					 const CString& log_id, 
					 const CString& sub_id)
{
	if(xEXT_CH__LLx__MOVE_FLAG[ll_i]->Check__DATA("YES") > 0)
	{
		return -1;
	}

	DECLARE__EXT_CTRL(p_variable);

	// ...
	{
		CString log_msg;
		CString log_bff;

		CString ll_name = Get__LLx_NAME(ll_i);

		log_msg.Format("SCH_CALL__LLx_VENT(%s) ... \n", ll_name);
		log_bff.Format(" * log_id <- [%s] \n", log_id);
		log_msg += log_bff;
		log_bff.Format(" * sub_id <- [%s] \n", sub_id);
		log_msg += log_bff;

		xAPP_LOG_CTRL->WRITE__LOG(log_msg);
	}

	if(LLx__Is_ATM(ll_i) < 0)
	{
		return pLLx__OBJ_CTRL[ll_i]->Call__OBJECT(LL_CMMD__VENT);
	}
	return 1;
}

int  CObj_Fnc__SINGLE_ARM_STD::
SCH__LLx_PRESSURE_ERROR(const int ll_i,
						CII_OBJECT__VARIABLE *p_variable,
						CII_OBJECT__ALARM *p_alarm)
{
	CString log_id = "CObj_Fnc__SINGLE_ARM_STD::SCH__LBA_PRESSURE_ERROR()";

	// ...
	LLx__Update_PRESSURE(ll_i);

	if(LLx__Is_ATM(ll_i) > 0)
	{
		return 1;
	}

	// ...
	CString cfg_mode;
	xEXT_CH__CFG__PRESSURE_CHECK_MODE->Get__DATA(cfg_mode);

	if((cfg_mode.CompareNoCase(STR__ALARM)    == 0)
	|| (cfg_mode.CompareNoCase(STR__RECOVERY) == 0)
	|| (cfg_mode.CompareNoCase(STR__ONLY_RECOVERY) == 0))
	{
		if(cfg_mode.CompareNoCase(STR__ONLY_RECOVERY) != 0)
		{
			int alm_id = ALID__JOB_ERROR__LBA__CHECK_ATM_PRESSURE + ll_i;
			CString r_act;			

			p_alarm->Check__ALARM(alm_id, r_act);
			p_alarm->Post__ALARM(alm_id);
		}

		if((cfg_mode.CompareNoCase(STR__RECOVERY) == 0)
		|| (cfg_mode.CompareNoCase(STR__ONLY_RECOVERY) == 0))
		{
			SCH_RUN__LLx_VENT(ll_i, p_variable, log_id, "1");
		}
	}
	return -1;
}

//.....
int  CObj_Fnc__SINGLE_ARM_STD:: 
SCH__ALIGN(CII_OBJECT__VARIABLE *p_variable,const CString& str_slot)
{
	DECLARE__EXT_CTRL(p_variable);

	if(xEXT_CH__SCH_ALIGN_DEVICE->Check__DATA(STR__ATM_RB) > 0)
	{
		return 1;
	}

	//.....
	CStringArray l_para;
	l_para.Add(str_slot);

	return pAL1__OBJ_CTRL->Run__OBJ_MODE(AL_CMMD__ALIGN, l_para);
}

