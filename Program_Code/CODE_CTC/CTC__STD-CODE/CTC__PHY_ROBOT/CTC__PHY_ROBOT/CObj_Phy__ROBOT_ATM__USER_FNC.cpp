#include "StdAfx.h"
#include "CObj_Phy__ROBOT_ATM.h"
#include "CObj_Phy__ROBOT_ATM__DEF.h"

#include "Macro_Function.h"


// SCH_TEST : CONFIG ...
int CObj_Phy__ROBOT_ATM
::Call__SCH_TEST_CFG(CII_OBJECT__VARIABLE* p_variable)
{
	CString sec_pick  = "3.0";
	CString sec_place = "3.0";

	// CFG : PICK ...
	{
		aCH__SCH_TEST_CFG_PICK_LPx_SEC->Set__DATA(sec_pick);
		aCH__SCH_TEST_CFG_PICK_ALx_SEC->Set__DATA(sec_pick);
		aCH__SCH_TEST_CFG_PICK_LLx_SEC->Set__DATA(sec_pick);
		aCH__SCH_TEST_CFG_PICK_STx_SEC->Set__DATA(sec_pick);
	}
	// CFG : PLACE ...
	{
		aCH__SCH_TEST_CFG_PLACE_LPx_SEC->Set__DATA(sec_place);
		aCH__SCH_TEST_CFG_PLACE_ALx_SEC->Set__DATA(sec_place);
		aCH__SCH_TEST_CFG_PLACE_LLx_SEC->Set__DATA(sec_place);
		aCH__SCH_TEST_CFG_PLACE_STx_SEC->Set__DATA(sec_place);
	}

	// CFG ...
	{
		aCH__SCH_TEST_CFG_INIT_SEC->Set__DATA("5.0");
		aCH__SCH_TEST_CFG_HOME_SEC->Set__DATA("5.0");
		aCH__SCH_TEST_CFG_LP_MAP_SEC->Set__DATA("5.0");
	}
	return 1;
}

// ...
int CObj_Phy__ROBOT_ATM
::Fnc__MODULE_OBJ(CII_OBJECT__VARIABLE* p_variable,
				  const CString obj_mode)
{
	SCX__ASYNC_TIMER_CTRL x_timer_ctrl;
	x_timer_ctrl->START__COUNT_UP(9999);

	// ...
	{
		CString ch_data = Macro__Get_Current_Time();
		sCH__TIME_ACT_START->Set__DATA(ch_data);
	}

	// ...
	int flag = -1;

	if(dEXT_CH__SCH_TEST_CFG_TMC_DUMMY_BY_CTC->Check__DATA(STR__YES) > 0)
	{
		flag = Sim__MODULE_OBJ(p_variable, obj_mode);

		if(iACTIVE__SIM_MODE > 0)
		{
			CString cur_md = dCH__PARA_MODULE->Get__STRING();

			if(cur_md.Find("AL1") == 0)
			{
				CString ch_data;

				ch_data = sCH__TARGET_LLx_NAME_SET_AL->Get__STRING();
				sCH__TARGET_LLx_NAME_GET->Set__DATA(ch_data);

				ch_data = sCH__TARGET_LLx_SLOT_SET_AL->Get__STRING();
				sCH__TARGET_LLx_SLOT_GET->Set__DATA(ch_data);
			}
		}
	}
	else
	{
		flag = xI_Module_Obj->Connect__Module_Obj(obj_mode);
	}

	// ...
	{
		CString ch_data;

		ch_data.Format("%.3f", x_timer_ctrl->Get__CURRENT_TIME());
		sCH__TIME_ACT_TACK->Set__DATA(ch_data);

		ch_data = Macro__Get_Current_Time();
		sCH__TIME_ACT_END->Set__DATA(ch_data);
	}

	if(flag > 0)		sCH__TIME_ACT_RESULT->Set__DATA("OK");
	else				sCH__TIME_ACT_RESULT->Set__DATA("ERROR");

	return flag;
}
int CObj_Phy__ROBOT_ATM
::Sim__MODULE_OBJ(CII_OBJECT__VARIABLE* p_variable,
				  const CString obj_mode)
{
	CII__VAR_ANALOG_CTRL* pch_analog_cfg = NULL;
	bool active_check = true;

	if((obj_mode.CompareNoCase(_CMMD__INIT)  == 0)
	|| (obj_mode.CompareNoCase(_CMMD__MAINT) == 0))
	{
		pch_analog_cfg = aCH__SCH_TEST_CFG_INIT_SEC.Get__PTR();
	}
	else if(obj_mode.CompareNoCase(_CMMD__HOME) == 0)
	{
		active_check = false;
	}
	else if(obj_mode.CompareNoCase(_CMMD__LP_MAP) == 0)
	{
		pch_analog_cfg = aCH__SCH_TEST_CFG_LP_MAP_SEC.Get__PTR();
	}
	else if(obj_mode.CompareNoCase(_CMMD__ROTATE) == 0)
	{
		active_check = false;
	}
	else if((obj_mode.CompareNoCase(_CMMD__PICK)   == 0)
		 || (obj_mode.CompareNoCase(_CMMD__X_PICK) == 0))
	{
		CString str_module = sPara1__Module;

		if(pch_analog_cfg == NULL)
		{
			if(Get__ALx_INDEX(str_module) >= 0)
				pch_analog_cfg = aCH__SCH_TEST_CFG_PICK_ALx_SEC.Get__PTR();
		}
		if(pch_analog_cfg == NULL)
		{
			if(Get__LLx_INDEX(str_module) >= 0)
				pch_analog_cfg = aCH__SCH_TEST_CFG_PICK_LLx_SEC.Get__PTR();
		}
		if(pch_analog_cfg == NULL)
		{
			if(Get__STx_INDEX(str_module) >= 0)
				pch_analog_cfg = aCH__SCH_TEST_CFG_PICK_STx_SEC.Get__PTR();
		}
		if(pch_analog_cfg == NULL)
		{
			if(Get__LPx_INDEX(str_module) >= 0)
				pch_analog_cfg = aCH__SCH_TEST_CFG_PICK_LPx_SEC.Get__PTR();
		}

		// ...
		int r_flag = -1;

		if(obj_mode.CompareNoCase(_CMMD__PICK) == 0)
		{
			r_flag = Sim__PICK_MATERIAL(true, false);
		}
		else if(obj_mode.CompareNoCase(_CMMD__X_PICK) == 0)
		{
			r_flag = Sim__PICK_MATERIAL(true, true);
		}
		
		if(r_flag < 0)
		{
			return r_flag;
		}
	}
	else if((obj_mode.CompareNoCase(_CMMD__PLACE)   == 0)
		 || (obj_mode.CompareNoCase(_CMMD__X_PLACE) == 0))
	{
		CString str_module = sPara1__Module;

		if(pch_analog_cfg == NULL)
		{
			if(Get__ALx_INDEX(str_module) >= 0)
				pch_analog_cfg = aCH__SCH_TEST_CFG_PLACE_ALx_SEC.Get__PTR();
		}
		if(pch_analog_cfg == NULL)
		{
			if(Get__LLx_INDEX(str_module) >= 0)
				pch_analog_cfg = aCH__SCH_TEST_CFG_PLACE_LLx_SEC.Get__PTR();
		}
		if(pch_analog_cfg == NULL)
		{
			if(Get__STx_INDEX(str_module) >= 0)
				pch_analog_cfg = aCH__SCH_TEST_CFG_PLACE_STx_SEC.Get__PTR();
		}
		if(pch_analog_cfg == NULL)
		{
			if(Get__LPx_INDEX(str_module) >= 0)
				pch_analog_cfg = aCH__SCH_TEST_CFG_PLACE_LPx_SEC.Get__PTR();
		}

		// ...
		int r_flag = -1;

		if(obj_mode.CompareNoCase(_CMMD__PLACE) == 0)
		{
			r_flag = Sim__PLACE_MATERIAL(true, false);
		}
		else if(obj_mode.CompareNoCase(_CMMD__X_PLACE) == 0)
		{
			r_flag = Sim__PLACE_MATERIAL(true, true);
		}

		if(r_flag < 0)
		{
			return r_flag;
		}
	}

	// ...
	CString log_msg;
	CString log_bff;

	log_msg.Format("Sim__MODULE_OBJ() : Started ... \n");
	log_bff.Format(" * Obj_Mode <- %s \n", obj_mode);
	log_msg += log_bff;

	if(pch_analog_cfg == NULL)
	{
		if(active_check)
		{
			log_msg += " * pch_analog_cfg - Error ! \n";

			xI_LOG_CTRL->WRITE__LOG(log_msg);
			return -1;
		}
	}
	else
	{
		log_bff.Format(" * %s <- %.1f sec \n", 
						pch_analog_cfg->Get__CHANNEL_NAME(),
						pch_analog_cfg->Get__VALUE());
		log_msg += log_bff;

		xI_LOG_CTRL->WRITE__LOG(log_msg);
	}

	if(active_check)
	{
		if(Fnc__WAIT_SEC(p_variable, pch_analog_cfg) < 0)
		{
			return -2;
		}
	}

	if(obj_mode.CompareNoCase(_CMMD__INIT) == 0)
	{
		xCH__OBJ_STATUS->Set__DATA(STR__STANDBY);
		xCH__UPPER_OBJ__STATUS->Set__DATA(STR__STANDBY);
	}
	else if(obj_mode.CompareNoCase(_CMMD__MAINT) == 0)
	{
		xCH__OBJ_STATUS->Set__DATA(STR__MAINTMODE);
		xCH__UPPER_OBJ__STATUS->Set__DATA(STR__MAINTMODE);
	}
	else if(obj_mode.CompareNoCase(_CMMD__HOME) == 0)
	{

	}
	else if(obj_mode.CompareNoCase(_CMMD__ROTATE) == 0)
	{
		Sleep(1000);

		if((bActive__LLx_MULTI_SLOT_VALVE)
		&& (Get__LLx_INDEX(sPara1__Module) >= 0))
		{
			CString ani_module;
			ani_module.Format("%s-%s", sPara1__Module,sPara2__Slot);

			dCH__ANI_TRG_MOVE->Set__DATA(ani_module);
			dCH__ANI_TRG_ROTE->Set__DATA(ani_module);
		}
		else
		{
			dCH__ANI_TRG_MOVE->Set__DATA(sPara1__Module);
			dCH__ANI_TRG_ROTE->Set__DATA(sPara1__Module);
		}
	}
	else if(obj_mode.CompareNoCase(_CMMD__LP_MAP) == 0)
	{
		int lp_index = -1;

		// ...
		{
			for(int i=0; i<iLPx_SIZE; i++)
			{
				CString name_lp;
				name_lp.Format("LP%1d", i+1);

				if(name_lp.CompareNoCase(sPara1__Module) != 0)
					continue;

				lp_index = i;
				break;
			}
		}

		if(lp_index >= 0)
		{
			for(int i=0; i<CFG_LP__SLOT_MAX; i++)
			{
				dEXT_CH__LPx_SLOTx_STATUS[lp_index][i]->Set__DATA(STR__EXIST);
			}
		}
	}
	else if(obj_mode.CompareNoCase(_CMMD__PICK) == 0)
	{
		Sim__PICK_MATERIAL(false, false);
	}
	else if(obj_mode.CompareNoCase(_CMMD__X_PICK) == 0)
	{
		Sim__PICK_MATERIAL(false, true);
	}
	else if(obj_mode.CompareNoCase(_CMMD__PLACE) == 0)
	{
		Sim__PLACE_MATERIAL(false, false);
	}
	else if(obj_mode.CompareNoCase(_CMMD__X_PLACE) == 0)
	{
		Sim__PLACE_MATERIAL(false, true);
	}

	// AnimAtion ...
	{
		if((obj_mode.CompareNoCase(_CMMD__INIT) == 0)
		|| (obj_mode.CompareNoCase(_CMMD__HOME) == 0))
		{
			CString str_home = "HOME";

			dCH__ANI_TRG_MOVE->Set__DATA(str_home);
			dCH__ANI_TRG_ROTE->Set__DATA(str_home);

			dCH__ANI_ARM_A_ACT->Set__DATA("RETRACT");
			dCH__ANI_ARM_B_ACT->Set__DATA("RETRACT");
		}
	}

	// ...
	{
		log_msg.Format("Sim__MODULE_OBJ() : Completetd ... \n");

		xI_LOG_CTRL->WRITE__LOG(log_msg);
	}
	return 1;
}

int CObj_Phy__ROBOT_ATM
::Fnc__WAIT_SEC(CII_OBJECT__VARIABLE* p_variable,
				CII__VAR_ANALOG_CTRL* pch_analog_cfg)
{
	double cfg_sec = pch_analog_cfg->Get__VALUE();

	SCX__ASYNC_TIMER_CTRL x_timer_ctrl;
	x_timer_ctrl->START__COUNT_UP(cfg_sec + 1.0);

	while(1)
	{
		Sleep(1);

		if(x_timer_ctrl->Get__CURRENT_TIME() >= cfg_sec)
		{
			return 1;
		}

		if(p_variable->Check__CTRL_ABORT() > 0)
		{
			break;
		}
	}

	return -1;
}

int CObj_Phy__ROBOT_ATM
::Sim__PICK_MATERIAL(const bool act_start, const bool ex_mode)
{
	CString log_msg;
	CString log_bff;

	if(act_start)
	{
		log_msg = "\n";
		log_bff.Format(" # Sim__PICK_MATERIAL(%1d) - Start ...\n", ex_mode);
		log_msg += log_bff;
		
		log_bff.Format("  * Arm_Type <- %s \n", sPara0__Arm_Type);
		log_msg += log_bff;
		log_bff.Format("  * Module   <- %s \n", sPara1__Module);
		log_msg += log_bff;
		log_bff.Format("  * Slot     <- %s \n", sPara2__Slot);
		log_msg += log_bff;
		log_bff.Format("  * Position <- %s \n", sPara3__Pos);
		log_msg += log_bff;
		
		xI_LOG_CTRL->WRITE__LOG(log_msg);
	}
	else
	{
		log_msg = "\n";
		log_bff.Format(" # Sim__PICK_MATERIAL(%1d) - End ...\n", ex_mode);
		log_msg += log_bff;

		xI_LOG_CTRL->WRITE__LOG(log_msg);
	}

	// ...
	CUIntArray l__arm_index;

	Get__ARMx_INDEX_LIST(sPara0__Arm_Type, l__arm_index);

	int k_limit = l__arm_index.GetSize();
	int k;

	for(k=0; k<k_limit; k++)
	{
		int arm_index = l__arm_index[k];
		if(arm_index < 0)
		{
			return -11;
		}

		// ...
		CII__VAR_DIGITAL_CTRL *pch__arm_status = xCH__SLOT_STATUS[arm_index].Get__PTR();
		CII__VAR_STRING_CTRL  *pch__arm_title  = xCH__SLOT_TITLE[arm_index].Get__PTR();

		if(pch__arm_status->Check__DATA(STR__NONE) < 0)
		{
			return -21;
		}

		// ...
		CII__VAR_DIGITAL_CTRL *pch__door_status = NULL;
		CII__VAR_DIGITAL_CTRL *pch__slot_status = NULL;
		CII__VAR_STRING_CTRL  *pch__slot_title  = NULL;

		CString slot_title = "";

		int md_index   = -1;
		int active_lp  = -1;

		int slot_index = atoi(sPara2__Slot) - 1;
		if(sPara0__Arm_Type.CompareNoCase(_ARM__AB) == 0)			slot_index += k;

		if(md_index < 0)
		{
			md_index = Get__ALx_INDEX(sPara1__Module);

			if(md_index >= 0)
			{
				if(slot_index <  0)						return -31;
				if(slot_index >= CFG_AL__SLOT_MAX)		return -32;

				pch__slot_status = dEXT_CH__AL1_SLOTx_STATUS[slot_index].Get__PTR();
				pch__slot_title  = sEXT_CH__AL1_SLOTx_TITLE[slot_index].Get__PTR();
			}
		}
		if(md_index < 0)
		{
			md_index = Get__LLx_INDEX(sPara1__Module);

			if(md_index >= iLLx_SIZE)
			{
				return -10002;
			}
			if(md_index >= 0)
			{
				if(slot_index <  0)						return -41;
				if(slot_index >= CFG_LLx__SLOT_MAX)		return -42;

				if(bActive__LLx_MULTI_SLOT_VALVE)
				{
					pch__door_status = dEXT_CH__LLx_DOOR_STATUS_X[md_index][slot_index].Get__PTR();
				}
				else
				{
					pch__door_status = dEXT_CH__LLx_DOOR_STATUS[md_index].Get__PTR();
				}

				pch__slot_status = dEXT_CH__LLx_SLOTx_STATUS[md_index][slot_index].Get__PTR();
				pch__slot_title  = sEXT_CH__LLx_SLOTx_TITLE[md_index][slot_index].Get__PTR();
			}
		}
		if(md_index < 0)
		{
			md_index = Get__STx_INDEX(sPara1__Module);

			if(md_index == 0)
			{
				if(slot_index <  0)						return -51;
				if(slot_index >= CFG_LP__SLOT_MAX)		return -52;

				pch__slot_status = dEXT_CH__ST1_SLOTx_STATUS[slot_index].Get__PTR();
				pch__slot_title  = sEXT_CH__ST1_SLOTx_TITLE[slot_index].Get__PTR();
			}
			else if(md_index == 1)
			{
				if(slot_index <  0)						return -53;
				if(slot_index >= CFG_LP__SLOT_MAX)		return -54;

				pch__slot_status = dEXT_CH__ST2_SLOTx_STATUS[slot_index].Get__PTR();
				pch__slot_title  = sEXT_CH__ST2_SLOTx_TITLE[slot_index].Get__PTR();
			}
		}
		if(md_index < 0)
		{
			md_index = Get__LPx_INDEX(sPara1__Module);

			if(md_index >= 0)
			{
				if(slot_index <  0)						return -61;
				if(slot_index >= CFG_LP__SLOT_MAX)		return -62;

				pch__door_status = dEXT_CH__LPx_DOOR_STATUS[md_index].Get__PTR();

				pch__slot_status = dEXT_CH__LPx_SLOTx_STATUS[md_index][slot_index].Get__PTR();
				pch__slot_title  = NULL;
				slot_title.Format("P%1d:%02d", md_index+1,slot_index+1);

				active_lp = 1;
			}
		}

		if(md_index < 0)
		{
			return -101;
		}
		if(pch__slot_status->Check__DATA(STR__NONE) > 0)
		{
			return -102;
		}

		if(act_start)
		{
			if(pch__door_status != NULL)
			{
				pch__door_status->Set__DATA("OPEN");

				// ...
				{
					CString ch_name = pch__door_status->Get__CHANNEL_NAME();
					CString ch_data = pch__door_status->Get__STRING();

					log_msg = "\n";
					log_bff.Format(" * Set : %s <- %s.\n", ch_name,ch_data);
					log_msg += log_bff;

					xI_LOG_CTRL->WRITE__LOG(log_msg);
				}
			}

			if((bActive__LLx_MULTI_SLOT_VALVE)
			&& (Get__LLx_INDEX(sPara1__Module) >= 0))
			{
				CString ani_module;
				ani_module.Format("%s-%s", sPara1__Module,sPara2__Slot);

				dCH__ANI_TRG_MOVE->Set__DATA(ani_module);
				dCH__ANI_TRG_ROTE->Set__DATA(ani_module);
			}
			else
			{
				dCH__ANI_TRG_MOVE->Set__DATA(sPara1__Module);
				dCH__ANI_TRG_ROTE->Set__DATA(sPara1__Module);
			}
			
			dCH__ANI_ROTE_ARM->Set__DATA(sPara0__Arm_Type);

				 if(arm_index == 0)		dCH__ANI_ARM_A_ACT->Set__DATA("EXTEND");
			else if(arm_index == 1)		dCH__ANI_ARM_B_ACT->Set__DATA("EXTEND");
		}
		else
		{
			if((bActive__LLx_MULTI_SLOT_VALVE)
			&& (Get__LLx_INDEX(sPara1__Module) >= 0))
			{
				CString ani_module;
				ani_module.Format("%s-%s", sPara1__Module,sPara2__Slot);

				dCH__ANI_TRG_MOVE->Set__DATA(ani_module);
				dCH__ANI_TRG_ROTE->Set__DATA(ani_module);
			}
			else
			{
				dCH__ANI_TRG_MOVE->Set__DATA(sPara1__Module);
				dCH__ANI_TRG_ROTE->Set__DATA(sPara1__Module);
			}
			
			dCH__ANI_ROTE_ARM->Set__DATA(sPara0__Arm_Type);

				 if(arm_index == 0)		dCH__ANI_ARM_A_ACT->Set__DATA("RETRACT");
			else if(arm_index == 1)		dCH__ANI_ARM_B_ACT->Set__DATA("RETRACT");

			// ...
			CString slot_status = pch__slot_status->Get__STRING();

			if(pch__slot_title != NULL)		
				slot_title = pch__slot_title->Get__STRING();

			pch__arm_status->Set__DATA(slot_status);
			pch__arm_title->Set__DATA(slot_title);

			pch__slot_status->Set__DATA(STR__NONE);
			if(pch__slot_title != NULL)		pch__slot_title->Set__DATA("");

			if(!ex_mode)
			{
				if((pch__door_status != NULL)
				&& (active_lp < 0))
				{
					pch__door_status->Set__DATA("CLOSE");

					// ...
					{
						CString ch_name = pch__door_status->Get__CHANNEL_NAME();
						CString ch_data = pch__door_status->Get__STRING();

						log_msg = "\n";
						log_bff.Format(" * Set : %s <- %s.\n", ch_name,ch_data);
						log_msg += log_bff;

						xI_LOG_CTRL->WRITE__LOG(log_msg);
					}
				}
			}
			else if(bActive__LLx_MULTI_SLOT_VALVE)
			{
				if((pch__door_status != NULL)
				&& (Get__LLx_INDEX(sPara1__Module) >= 0))
				{
					pch__door_status->Set__DATA("CLOSE");

					// ...
					{
						CString ch_name = pch__door_status->Get__CHANNEL_NAME();
						CString ch_data = pch__door_status->Get__STRING();

						log_msg = "\n";
						log_bff.Format(" ** Set : %s <- %s.\n", ch_name,ch_data);
						log_msg += log_bff;

						xI_LOG_CTRL->WRITE__LOG(log_msg);
					}
				}
			}

			// ...
		}
	}

	return 1;
}
int CObj_Phy__ROBOT_ATM
::Sim__PLACE_MATERIAL(const bool act_start, const bool ex_mode)
{
	CString log_msg;
	CString log_bff;

	if(act_start)
	{
		log_msg = "\n";
		log_bff.Format(" # Sim__PLACE_MATERIAL(%1d) - Start ...\n", ex_mode);
		log_msg += log_bff;

		log_bff.Format("  * Arm_Type <- %s \n", sPara0__Arm_Type);
		log_msg += log_bff;
		log_bff.Format("  * Module   <- %s \n", sPara1__Module);
		log_msg += log_bff;
		log_bff.Format("  * Slot     <- %s \n", sPara2__Slot);
		log_msg += log_bff;
		log_bff.Format("  * Position <- %s \n", sPara3__Pos);
		log_msg += log_bff;

		xI_LOG_CTRL->WRITE__LOG(log_msg);
	}
	else
	{
		log_msg = "\n";
		log_bff.Format(" # Sim__PLACE_MATERIAL(%1d) - End ...\n", ex_mode);
		log_msg += log_bff;

		xI_LOG_CTRL->WRITE__LOG(log_msg);
	}

	// ...
	CUIntArray l__arm_index;

	Get__ARMx_INDEX_LIST(sPara0__Arm_Type, l__arm_index);

	int k_limit = l__arm_index.GetSize();
	int k;

	for(k=0; k<k_limit; k++)
	{
		int arm_index = l__arm_index[k];
		if(arm_index < 0)
		{
			return -11;
		}

		// ...
		CII__VAR_DIGITAL_CTRL *pch__arm_status = xCH__SLOT_STATUS[arm_index].Get__PTR();
		CII__VAR_STRING_CTRL  *pch__arm_title  = xCH__SLOT_TITLE[arm_index].Get__PTR();

		if(pch__arm_status->Check__DATA(STR__NONE) > 0)
		{
			return -21;
		}

		// ...
		CII__VAR_DIGITAL_CTRL *pch__door_status = NULL;
		CII__VAR_DIGITAL_CTRL *pch__slot_status = NULL;
		CII__VAR_STRING_CTRL  *pch__slot_title  = NULL;

		int active_lp  = -1;
		int md_index   = -1;
		
		int slot_index = atoi(sPara2__Slot) - 1;	
		if(sPara0__Arm_Type.CompareNoCase(_ARM__AB) == 0)			slot_index += k;

		if(md_index < 0)
		{
			md_index = Get__ALx_INDEX(sPara1__Module);

			if(md_index >= 0)
			{
				if(slot_index <  0)						return -31;
				if(slot_index >= CFG_AL__SLOT_MAX)		return -32;

				pch__slot_status = dEXT_CH__AL1_SLOTx_STATUS[slot_index].Get__PTR();
				pch__slot_title  = sEXT_CH__AL1_SLOTx_TITLE[slot_index].Get__PTR();
			}
		}
		if(md_index < 0)
		{
			md_index = Get__LLx_INDEX(sPara1__Module);

			if(md_index >= iLLx_SIZE)
			{
				return -10003;
			}
			if(md_index >= 0)
			{
				if(slot_index <  0)						return -41;
				if(slot_index >= CFG_LLx__SLOT_MAX)		return -42;

				if(bActive__LLx_MULTI_SLOT_VALVE)
				{
					pch__door_status = dEXT_CH__LLx_DOOR_STATUS_X[md_index][slot_index].Get__PTR();
				}
				else
				{
					pch__door_status = dEXT_CH__LLx_DOOR_STATUS[md_index].Get__PTR();
				}

				pch__slot_status = dEXT_CH__LLx_SLOTx_STATUS[md_index][slot_index].Get__PTR();
				pch__slot_title  = sEXT_CH__LLx_SLOTx_TITLE[md_index][slot_index].Get__PTR();
			}
		}
		if(md_index < 0)
		{
			md_index = Get__STx_INDEX(sPara1__Module);

			if(md_index == 0)
			{
				if(slot_index <  0)						return -51;
				if(slot_index >= CFG_LP__SLOT_MAX)		return -52;

				pch__slot_status = dEXT_CH__ST1_SLOTx_STATUS[slot_index].Get__PTR();
				pch__slot_title  = sEXT_CH__ST1_SLOTx_TITLE[slot_index].Get__PTR();
			}
			else if(md_index == 1)
			{
				if(slot_index <  0)						return -53;
				if(slot_index >= CFG_LP__SLOT_MAX)		return -54;

				pch__slot_status = dEXT_CH__ST2_SLOTx_STATUS[slot_index].Get__PTR();
				pch__slot_title  = sEXT_CH__ST2_SLOTx_TITLE[slot_index].Get__PTR();
			}
		}
		if(md_index < 0)
		{
			md_index = Get__LPx_INDEX(sPara1__Module);

			if(md_index >= 0)
			{
				if(slot_index <  0)						return -61;
				if(slot_index >= CFG_LP__SLOT_MAX)		return -62;

				pch__door_status = dEXT_CH__LPx_DOOR_STATUS[md_index].Get__PTR();

				pch__slot_status = dEXT_CH__LPx_SLOTx_STATUS[md_index][slot_index].Get__PTR();
				pch__slot_title  = NULL;

				active_lp = 1;
			}
		}

		if(md_index < 0)
		{
			return -101;
		}
		if(pch__slot_status->Check__DATA(STR__NONE) < 0)
		{
			return -102;
		}

		if(act_start)
		{
			if(pch__door_status != NULL)
			{
				pch__door_status->Set__DATA("OPEN");

				// ...
				{
					CString ch_name = pch__door_status->Get__CHANNEL_NAME();
					CString ch_data = pch__door_status->Get__STRING();

					log_msg = "\n";
					log_bff.Format(" * Set : %s <- %s.\n", ch_name,ch_data);
					log_msg += log_bff;

					xI_LOG_CTRL->WRITE__LOG(log_msg);
				}
			}

			if((bActive__LLx_MULTI_SLOT_VALVE)
			&& (Get__LLx_INDEX(sPara1__Module) >= 0))
			{
				CString ani_module;
				ani_module.Format("%s-%s", sPara1__Module,sPara2__Slot);

				dCH__ANI_TRG_MOVE->Set__DATA(ani_module);
				dCH__ANI_TRG_ROTE->Set__DATA(ani_module);
			}
			else
			{
				dCH__ANI_TRG_MOVE->Set__DATA(sPara1__Module);
				dCH__ANI_TRG_ROTE->Set__DATA(sPara1__Module);
			}
			
			dCH__ANI_ROTE_ARM->Set__DATA(sPara0__Arm_Type);

				 if(arm_index == 0)		dCH__ANI_ARM_A_ACT->Set__DATA("EXTEND");
			else if(arm_index == 1)		dCH__ANI_ARM_B_ACT->Set__DATA("EXTEND");
		}
		else
		{
			if((bActive__LLx_MULTI_SLOT_VALVE)
			&& (Get__LLx_INDEX(sPara1__Module) >= 0))
			{
				CString ani_module;
				ani_module.Format("%s-%s", sPara1__Module,sPara2__Slot);

				dCH__ANI_TRG_MOVE->Set__DATA(ani_module);
				dCH__ANI_TRG_ROTE->Set__DATA(ani_module);
			}
			else
			{
				dCH__ANI_TRG_MOVE->Set__DATA(sPara1__Module);
				dCH__ANI_TRG_ROTE->Set__DATA(sPara1__Module);
			}
			
			dCH__ANI_ROTE_ARM->Set__DATA(sPara0__Arm_Type);

				 if(arm_index == 0)		dCH__ANI_ARM_A_ACT->Set__DATA("RETRACT");
			else if(arm_index == 1)		dCH__ANI_ARM_B_ACT->Set__DATA("RETRACT");

			// ...
			CString arm_status = pch__arm_status->Get__STRING();
			CString arm_title  = pch__arm_title->Get__STRING();

			pch__slot_status->Set__DATA(arm_status);
			if(pch__slot_title  != NULL)		pch__slot_title->Set__DATA(arm_title);

			pch__arm_status->Set__DATA(STR__NONE);
			pch__arm_title->Set__DATA("");

			if(!ex_mode)
			{
				if((pch__door_status != NULL)
				&& (active_lp < 0))
				{
					pch__door_status->Set__DATA("CLOSE");

					// ...
					{
						CString ch_name = pch__door_status->Get__CHANNEL_NAME();
						CString ch_data = pch__door_status->Get__STRING();

						log_msg = "\n";
						log_bff.Format(" * Set : %s <- %s.\n", ch_name,ch_data);
						log_msg += log_bff;

						xI_LOG_CTRL->WRITE__LOG(log_msg);
					}
				}
			}
			else if(bActive__LLx_MULTI_SLOT_VALVE)
			{
				if((pch__door_status != NULL)
				&& (Get__LLx_INDEX(sPara1__Module) >= 0))
				{
					pch__door_status->Set__DATA("CLOSE");

					// ...
					{
						CString ch_name = pch__door_status->Get__CHANNEL_NAME();
						CString ch_data = pch__door_status->Get__STRING();

						log_msg = "\n";
						log_bff.Format(" ** Set : %s <- %s.\n", ch_name,ch_data);
						log_msg += log_bff;

						xI_LOG_CTRL->WRITE__LOG(log_msg);
					}
				}
			}

			// ...
		}
	}

	return 1;
}


// ...
int CObj_Phy__ROBOT_ATM
::Get__ARMx_INDEX(const CString& str_arm)
{
	if(str_arm.CompareNoCase(_ARM__A) == 0)			return 0;
	if(str_arm.CompareNoCase(_ARM__B) == 0)			return 1;

	return -1;
}
int CObj_Phy__ROBOT_ATM
::Get__ARMx_INDEX_LIST(const CString& str_arm, CUIntArray& l_arm_index)
{
	l_arm_index.RemoveAll();

	if(str_arm.CompareNoCase(_ARM__A)  == 0) 
	{
		l_arm_index.Add(0);
		return 11;
	}
	if(str_arm.CompareNoCase(_ARM__B)  == 0) 
	{
		l_arm_index.Add(1);
		return 12;
	}
	if(str_arm.CompareNoCase(_ARM__AB) == 0) 
	{
		l_arm_index.Add(0);
		l_arm_index.Add(1);
		return 13;
	}

	return -1;
}

int CObj_Phy__ROBOT_ATM
::Get__ALx_INDEX(const CString& str_module)
{
	if(str_module.CompareNoCase("AL1") == 0)		return 0;

	return -1;
}
int CObj_Phy__ROBOT_ATM
::Get__LLx_INDEX(const CString& str_module)
{
	if(str_module.CompareNoCase(MODULE__LBA) == 0)		return _LLx_INDEX__LBA;
	if(str_module.CompareNoCase(MODULE__LBB) == 0)		return _LLx_INDEX__LBB;
	if(str_module.CompareNoCase(MODULE__LBC) == 0)		return _LLx_INDEX__LBC;
	if(str_module.CompareNoCase(MODULE__LBD) == 0)		return _LLx_INDEX__LBD;

	return -1;
}
int CObj_Phy__ROBOT_ATM
::Get__STx_INDEX(const CString& str_module)
{
	if((str_module.CompareNoCase("BUFF1") == 0)
	|| (str_module.CompareNoCase("BUF1")  == 0)
	|| (str_module.CompareNoCase("STG1")  == 0))
	{
		return 0;
	}
	if((str_module.CompareNoCase("BUFF2") == 0)
	|| (str_module.CompareNoCase("BUF2")  == 0)
	|| (str_module.CompareNoCase("STG2")  == 0))
	{
		return 1;
	}

	return -1;
}
int CObj_Phy__ROBOT_ATM
::Get__LPx_INDEX(const CString& str_module)
{
	CString cmp_module;

	int i_limit = iLPx_SIZE;
	int i;

	for(i=0; i<i_limit; i++)
	{
		int id = i + 1;

		cmp_module.Format("LP%1d", id);
		if(str_module.CompareNoCase(cmp_module) != 0)
		{
			continue;
		}

		return i;
	}

	return -1;
}
