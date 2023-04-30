#include "StdAfx.h"
#include "CObj_Phy__ROBOT_VAC.h"
#include "CObj_Phy__ROBOT_VAC__DEF.h"

#include "Macro_Function.h"


// SCH_TEST : CONFIG ...
int CObj_Phy__ROBOT_VAC
::Call__SCH_TEST_CFG(CII_OBJECT__VARIABLE* p_variable)
{
	CString sec_pick  = "3.0";
	CString sec_place = "3.0";

	// CFG : PICK ...
	{
		aCH__SCH_TEST_CFG_PICK_LLx_SEC->Set__DATA(sec_pick);
		aCH__SCH_TEST_CFG_PICK_PMx_SEC->Set__DATA(sec_pick);
	}
	// CFG : PLACE ...
	{
		aCH__SCH_TEST_CFG_PLACE_LLx_SEC->Set__DATA(sec_place);
		aCH__SCH_TEST_CFG_PLACE_PMx_SEC->Set__DATA(sec_place);
	}

	// CFG ...
	{
		aCH__SCH_TEST_CFG_INIT_SEC->Set__DATA("5.0");
		aCH__SCH_TEST_CFG_HOME_SEC->Set__DATA("5.0");
	}
	return 1;
}


// ...
int CObj_Phy__ROBOT_VAC
::Fnc__MODULE_OBJ(CII_OBJECT__VARIABLE* p_variable, const CString obj_mode)
{
	int ll_i = Macro__Get_LLx_INDEX(sPara1__Module);
	int pm_i = Macro__Get_PMx_INDEX(sPara1__Module);

	if((obj_mode.CompareNoCase(_CMMD__INIT) == 0)
	|| (obj_mode.CompareNoCase(_CMMD__HOME) == 0))
	{

	}
	else
	{
		if(ll_i >= 0)
		{
			_Set__LLx_INFO(ll_i, obj_mode, STR__YES);		
		}
		else if(pm_i >= 0)
		{		
			_Set__PMx_INFO(pm_i, obj_mode, STR__YES);

			if(sPara0__Arm_Type.CompareNoCase(_ARM__AB) == 0)
			{
				int next_pm_i = pm_i + 1;
				_Set__PMx_INFO(next_pm_i, obj_mode, STR__YES);
			}
		}
	}
	
	int r_flag = _Fnc__MODULE_OBJ(p_variable, obj_mode);
	if(r_flag < 0)		return r_flag;

	if((obj_mode.CompareNoCase(_CMMD__INIT) == 0)
	|| (obj_mode.CompareNoCase(_CMMD__HOME) == 0))
	{
		_Init__LLx_INFO(STR__NO);
		_Init__PMx_INFO(STR__NO);
	}
	else
	{
		if(ll_i >= 0)
		{
			_Set__LLx_INFO(ll_i, obj_mode, STR__NO);		
		}
		else if(pm_i >= 0)
		{
			_Set__PMx_INFO(pm_i, obj_mode, STR__NO);

			if(sPara0__Arm_Type.CompareNoCase(_ARM__AB) == 0)
			{	
				int next_pm_i = pm_i + 1;
				_Set__PMx_INFO(next_pm_i, obj_mode, STR__NO);
			}
		}
	}

	return r_flag;
}

int CObj_Phy__ROBOT_VAC
::_Init__LLx_INFO(const CString& set_data)
{
	for(int i=0; i<iLLx_SIZE; i++)
	{		
		dEXT_CH__LLx_MOVE_FLAG[i]->Set__DATA(set_data);
	}
	return 1;
}
int CObj_Phy__ROBOT_VAC
::_Init__PMx_INFO(const CString& set_data)
{
	for(int i=0; i<iPM_SIZE; i++)
	{		
		dEXT_CH__PMx_MOVE_FLAG[i]->Set__DATA(set_data);

		sEXT_CH__PMx_X_PICK_FLAG[i]->Set__DATA(set_data);
		sEXT_CH__PMx_X_PLACE_FLAG[i]->Set__DATA(set_data);
	}
	return 1;
}

int CObj_Phy__ROBOT_VAC
::_Set__LLx_INFO(const int ll_index, const CString& obj_mode, const CString& set_data)
{
	if((ll_index >= 0) && (ll_index < iLLx_SIZE))
	{		
		dEXT_CH__LLx_MOVE_FLAG[ll_index]->Set__DATA(set_data);
	}
	return 1;
}
int CObj_Phy__ROBOT_VAC
::_Set__PMx_INFO(const int pm_index, const CString& obj_mode, const CString& set_data)
{
	if((pm_index >= 0) && (pm_index < iPM_SIZE))
	{		
		dEXT_CH__PMx_MOVE_FLAG[pm_index]->Set__DATA(set_data);

			 if(obj_mode.CompareNoCase(_CMMD__X_PICK)  == 0)		sEXT_CH__PMx_X_PICK_FLAG[pm_index]->Set__DATA(set_data);
		else if(obj_mode.CompareNoCase(_CMMD__X_PLACE) == 0)		sEXT_CH__PMx_X_PLACE_FLAG[pm_index]->Set__DATA(set_data);
	}
	return 1;
}

int CObj_Phy__ROBOT_VAC
::_Fnc__MODULE_OBJ(CII_OBJECT__VARIABLE* p_variable, const CString obj_mode)
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
int CObj_Phy__ROBOT_VAC
::Sim__MODULE_OBJ(CII_OBJECT__VARIABLE* p_variable,
				  const CString obj_mode)
{
	CII__VAR_ANALOG_CTRL* pch_analog_cfg = NULL;
	bool active_check = true;

	if(obj_mode.CompareNoCase(_CMMD__INIT) == 0)
	{
		pch_analog_cfg = aCH__SCH_TEST_CFG_INIT_SEC.Get__PTR();
	}
	else if(obj_mode.CompareNoCase(_CMMD__HOME) == 0)
	{
		active_check = false;
	}
	else if(obj_mode.CompareNoCase(_CMMD__ROTATE) == 0)
	{
		active_check = false;
	}
	else if(obj_mode.CompareNoCase(_CMMD__MAINT) == 0)
	{
		pch_analog_cfg = aCH__SCH_TEST_CFG_INIT_SEC.Get__PTR();
	}
	else if((obj_mode.CompareNoCase(_CMMD__PICK)   == 0)
		 || (obj_mode.CompareNoCase(_CMMD__X_PICK) == 0))
	{
		CString str_module = sPara1__Module;

		if(pch_analog_cfg == NULL)
		{
			if(Get__LLx_INDEX(str_module) >= 0)
				pch_analog_cfg = aCH__SCH_TEST_CFG_PICK_LLx_SEC.Get__PTR();
		}
		if(pch_analog_cfg == NULL)
		{
			if(Get__PMx_INDEX(str_module) >= 0)
				pch_analog_cfg = aCH__SCH_TEST_CFG_PICK_PMx_SEC.Get__PTR();
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
			if(Get__LLx_INDEX(str_module) >= 0)
				pch_analog_cfg = aCH__SCH_TEST_CFG_PLACE_LLx_SEC.Get__PTR();
		}
		if(pch_analog_cfg == NULL)
		{
			if(Get__PMx_INDEX(str_module) >= 0)
				pch_analog_cfg = aCH__SCH_TEST_CFG_PLACE_PMx_SEC.Get__PTR();
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
	else if(obj_mode.CompareNoCase(_CMMD__HOME) == 0)
	{

	}
	else if(obj_mode.CompareNoCase(_CMMD__ROTATE) == 0)
	{

	}
	else if(obj_mode.CompareNoCase(_CMMD__MAINT) == 0)
	{
		xCH__OBJ_STATUS->Set__DATA(STR__MAINTMODE);
		xCH__UPPER_OBJ__STATUS->Set__DATA(STR__MAINTMODE);
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
		else if(obj_mode.CompareNoCase(_CMMD__ROTATE) == 0)
		{
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

int CObj_Phy__ROBOT_VAC
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

// ...
int CObj_Phy__ROBOT_VAC
::_Set__ARM_ANI(const bool act_start, const CString& arm_type,const CString& stn_name,const CString& stn_slot)
{
	bool active__arm_a = false;
	bool active__arm_b = false;
	
		 if(arm_type.CompareNoCase(_ARM__A)  == 0)			active__arm_a = true;
	else if(arm_type.CompareNoCase(_ARM__B)  == 0)			active__arm_b = true;
	else if(arm_type.CompareNoCase(_ARM__AB) == 0)
	{
		active__arm_a = true;
		active__arm_b = true;
	}

	// ...
	int ll_i = Get__LLx_INDEX(stn_name);
	int pm_i = Get__PMx_INDEX(stn_name);

	if((bActive__LLx_MULTI_SLOT_VALVE)
	&& (ll_i >= 0))
	{
		CString ani_module;

		if(active__arm_a && active__arm_b)
			ani_module.Format("%s-%s", stn_name,"12");
		else
			ani_module.Format("%s-%s", stn_name,stn_slot);

		dCH__ANI_TRG_MOVE->Set__DATA(ani_module);
		dCH__ANI_TRG_ROTE->Set__DATA(ani_module);
	}
	else if(pm_i >= 0)
	{
		CString ani_module;

		if(active__arm_a && active__arm_b)
		{
			int id_left  = ((pm_i / 2) * 2) + 1;
			int id_irght = id_left + 1;

			ani_module.Format("PM%1d%1d", id_left,id_irght);
		}
		else
			ani_module = stn_name;

		dCH__ANI_TRG_MOVE->Set__DATA(ani_module);
		dCH__ANI_TRG_ROTE->Set__DATA(ani_module);
	}
	else
	{
		dCH__ANI_TRG_MOVE->Set__DATA(stn_name);
		dCH__ANI_TRG_ROTE->Set__DATA(stn_name);
	}

	dCH__ANI_ROTE_ARM->Set__DATA(arm_type);

	if(active__arm_a)
	{
		if(act_start)			dCH__ANI_ARM_A_ACT->Set__DATA("EXTEND");
		else					dCH__ANI_ARM_A_ACT->Set__DATA("RETRACT");
	}
	if(active__arm_b)
	{
		if(act_start)			dCH__ANI_ARM_B_ACT->Set__DATA("EXTEND");
		else					dCH__ANI_ARM_B_ACT->Set__DATA("RETRACT");
	}

	return 1;
}

int CObj_Phy__ROBOT_VAC
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
	CString arm_type = sPara0__Arm_Type;
	CString stn_name = sPara1__Module;
	CString stn_slot = sPara2__Slot;

	CStringArray l__arm_type;
	CStringArray l__stn_name;
	CStringArray l__stn_slot;

	_Get__ARM_INFO(arm_type,stn_name,stn_slot, l__arm_type,l__stn_name,l__stn_slot);

	// ...
	int k_limit = l__arm_type.GetSize();

	for(int k=0; k<k_limit; k++) 
	{
		CString cur__arm_type = l__arm_type[k];
		CString cur__stn_name = l__stn_name[k];
		CString cur__stn_slot = l__stn_slot[k];

		int r_flag = _Sim__PICK_MATERIAL(act_start,ex_mode, cur__arm_type,cur__stn_name,cur__stn_slot);
		if(r_flag < 0)		return r_flag;
	}

	_Set__ARM_ANI(act_start, arm_type,stn_name,stn_slot);
	return 1;
}
int CObj_Phy__ROBOT_VAC
::_Sim__PICK_MATERIAL(const bool act_start,const bool ex_mode, const CString& arm_type,const CString& stn_name,const CString& stn_slot)
{
	CString log_msg;
	CString log_bff;

	// ...
	int arm_index = -1;

		 if(arm_type.CompareNoCase(_ARM__A) == 0)			arm_index = 0;
	else if(arm_type.CompareNoCase(_ARM__B) == 0)			arm_index = 1;
	else													return -11;
	
	// ...
	CII__VAR_DIGITAL_CTRL *pch__arm_status = xCH__SLOT_STATUS[arm_index].Get__PTR();
	CII__VAR_STRING_CTRL  *pch__arm_title  = xCH__SLOT_TITLE[arm_index].Get__PTR();

	if(pch__arm_status->Check__DATA(STR__NONE) < 0)			return -12;

	// ...
	CII__VAR_DIGITAL_CTRL *pch__door_status = NULL;
	CII__VAR_DIGITAL_CTRL *pch__slot_status = NULL;
	CII__VAR_STRING_CTRL  *pch__slot_title  = NULL;

	// CHECK : LLx ...
	int ll_i = Get__LLx_INDEX(stn_name);
	if(ll_i >= 0)
	{
		if(ll_i >= iLLx_SIZE)					return -21;

		int s_index = atoi(stn_slot) - 1;

		if(s_index <  0)						return -22;
		if(s_index >= CFG_LLx__SLOT_MAX)		return -23;

		if(bActive__LLx_MULTI_SLOT_VALVE)
		{
			pch__door_status = dEXT_CH__LLx_DOOR_STATUS_X[ll_i][s_index].Get__PTR();
		}
		else
		{
			pch__door_status = dEXT_CH__LLx_DOOR_STATUS[ll_i].Get__PTR();
		}

		pch__slot_status = dEXT_CH__LLx_SLOTx_STATUS[ll_i][s_index].Get__PTR();
		pch__slot_title  = sEXT_CH__LLx_SLOTx_TITLE[ll_i][s_index].Get__PTR();
	}

	// CHECK : PMx ...
	int pm_i = Get__PMx_INDEX(stn_name);
	if(pm_i >= 0)
	{
		if(pm_i >= iPM_SIZE)					return -31;

		int s_index = atoi(stn_slot) - 1;
		if(s_index != 0)						return -32;

		pch__door_status = dEXT_CH__PMx_DOOR_STATUS[pm_i].Get__PTR();

		pch__slot_status = dEXT_CH__PMx_SLOT_STATUS[pm_i].Get__PTR();
		pch__slot_title  = sEXT_CH__PMx_SLOT_TITLE[pm_i].Get__PTR();
	}

	if(pch__door_status == NULL)
	{
		return -101;
	}

	if(act_start)
	{
		pch__door_status->Set__DATA(STR__OPEN);

		if(pch__door_status->Check__DATA(STR__OPEN) < 0)
		{
			return -102;
		}
		if(pch__slot_status->Check__DATA(STR__NONE) > 0)
		{
			return -103;
		}
	}
	else
	{
		// ...
		{
			CString slot_status = pch__slot_status->Get__STRING();
			CString slot_title  = pch__slot_title->Get__STRING();

			pch__arm_status->Set__DATA(slot_status);
			pch__arm_title->Set__DATA(slot_title);

			pch__slot_status->Set__DATA(STR__NONE);
			pch__slot_title->Set__DATA("");
		}

		//==============================================================
		if(act_start)
		{

		}
		else
		{
			if(ll_i >= 0)
			{
				CString skip_data = sEXT_CH__OBJ_MAINT__PARA_MANUAL_MOVE_LLx_SLOT_CLOSE_SKIP->Get__STRING();
				int skip_index = skip_data.Find(STR__YES);
				if(skip_index >= 0)			return 11;
			}
			
			if(pm_i >= 0)
			{
				CString skip_data = sEXT_CH__OBJ_MAINT__PARA_MANUAL_MOVE_PMx_SLOT_CLOSE_SKIP->Get__STRING();
				int skip_index = skip_data.Find(STR__YES);
				if(skip_index >= 0)			return 12;
			}
		}
		//==============================================================

		pch__door_status->Set__DATA(STR__CLOSE);
	}

	return 1;
}

int CObj_Phy__ROBOT_VAC
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
	CString arm_type = sPara0__Arm_Type;
	CString stn_name = sPara1__Module;
	CString stn_slot = sPara2__Slot;

	CStringArray l__arm_type;
	CStringArray l__stn_name;
	CStringArray l__stn_slot;

	_Get__ARM_INFO(arm_type,stn_name,stn_slot, l__arm_type,l__stn_name,l__stn_slot);

	// ...
	int k_limit = l__arm_type.GetSize();

	for(int k=0; k<k_limit; k++) 
	{
		CString cur__arm_type = l__arm_type[k];
		CString cur__stn_name = l__stn_name[k];
		CString cur__stn_slot = l__stn_slot[k];

		int r_flag = _Sim__PLACE_MATERIAL(act_start,ex_mode, cur__arm_type,cur__stn_name,cur__stn_slot);
		if(r_flag < 0)		return r_flag;
	}

	_Set__ARM_ANI(act_start, arm_type,stn_name,stn_slot);
	return 1;
}
int CObj_Phy__ROBOT_VAC
::_Sim__PLACE_MATERIAL(const bool act_start,const bool ex_mode, const CString& arm_type,const CString& stn_name,const CString& stn_slot)
{
	CString log_msg;
	CString log_bff;

	// ...
	int arm_index = -1;

		 if(arm_type.CompareNoCase(_ARM__A) == 0)			arm_index = 0;
	else if(arm_type.CompareNoCase(_ARM__B) == 0)			arm_index = 1;
	else													return -11;

	// ...
	CII__VAR_DIGITAL_CTRL *pch__arm_status = xCH__SLOT_STATUS[arm_index].Get__PTR();
	CII__VAR_STRING_CTRL  *pch__arm_title  = xCH__SLOT_TITLE[arm_index].Get__PTR();

	if(pch__arm_status->Check__DATA(STR__NONE) > 0)			return -12;

	// ...
	CII__VAR_DIGITAL_CTRL *pch__door_status = NULL;
	CII__VAR_DIGITAL_CTRL *pch__slot_status = NULL;
	CII__VAR_STRING_CTRL  *pch__slot_title  = NULL;

	// CHECK : LLx ...
	int ll_i = Get__LLx_INDEX(stn_name);
	if(ll_i >= 0)
	{
		if(ll_i >= iLLx_SIZE)					return -21;

		int s_index = atoi(stn_slot) - 1;

		if(s_index <  0)						return -22;
		if(s_index >= CFG_LLx__SLOT_MAX)		return -23;

		if(bActive__LLx_MULTI_SLOT_VALVE)
		{
			pch__door_status = dEXT_CH__LLx_DOOR_STATUS_X[ll_i][s_index].Get__PTR();
		}
		else
		{
			pch__door_status = dEXT_CH__LLx_DOOR_STATUS[ll_i].Get__PTR();
		}

		pch__slot_status = dEXT_CH__LLx_SLOTx_STATUS[ll_i][s_index].Get__PTR();
		pch__slot_title  = sEXT_CH__LLx_SLOTx_TITLE[ll_i][s_index].Get__PTR();
	}

	// CHECK : PMx ...
	int pm_i = Get__PMx_INDEX(stn_name);
	if(pm_i >= 0)
	{
		if(pm_i >= iPM_SIZE)					return -31;

		int s_index = atoi(stn_slot) - 1;
		if(s_index != 0)						return -32;

		pch__door_status = dEXT_CH__PMx_DOOR_STATUS[pm_i].Get__PTR();
	
		pch__slot_status = dEXT_CH__PMx_SLOT_STATUS[pm_i].Get__PTR();
		pch__slot_title  = sEXT_CH__PMx_SLOT_TITLE[pm_i].Get__PTR();
	}

	if(pch__door_status == NULL)
	{
		return -101;
	}

	if(act_start)
	{
		pch__door_status->Set__DATA(STR__OPEN);

		if(pch__door_status->Check__DATA(STR__OPEN) < 0)
		{
			return -102;
		}
		if(pch__slot_status->Check__DATA(STR__NONE) < 0)
		{
			return -103;
		}
	}
	else
	{
		// ...
		{
			CString arm_status = pch__arm_status->Get__STRING();
			CString arm_title  = pch__arm_title->Get__STRING();

			pch__slot_status->Set__DATA(arm_status);
			pch__slot_title->Set__DATA(arm_title);

			pch__arm_status->Set__DATA(STR__NONE);
			pch__arm_title->Set__DATA("");
		}

		//==============================================================
		if(act_start)
		{

		}
		else
		{
			if(ll_i >= 0)
			{
				CString skip_data = sEXT_CH__OBJ_MAINT__PARA_MANUAL_MOVE_LLx_SLOT_CLOSE_SKIP->Get__STRING();
				int skip_index = skip_data.Find(STR__YES);
				if(skip_index >= 0)			return 11;
			}

			if(pm_i >= 0)
			{
				CString skip_data = sEXT_CH__OBJ_MAINT__PARA_MANUAL_MOVE_PMx_SLOT_CLOSE_SKIP->Get__STRING();
				int skip_index = skip_data.Find(STR__YES);
				if(skip_index >= 0)			return 12;
			}
		}
		//==============================================================

		pch__door_status->Set__DATA(STR__CLOSE);
	}

	return 1;
}


// ...
int CObj_Phy__ROBOT_VAC
::Get__ARMx_INDEX(const CString& str_arm)
{
	if(str_arm.CompareNoCase("A") == 0)				return 0;
	if(str_arm.CompareNoCase("B") == 0)				return 1;

	return -1;
}
int CObj_Phy__ROBOT_VAC
::Get__ARMx_INDEX_LIST(const CString& str_arm, CUIntArray& l_arm_index)
{
	l_arm_index.RemoveAll();

	if(str_arm.CompareNoCase("A") == 0) 
	{
		l_arm_index.Add(0);
		return 11;
	}
	if(str_arm.CompareNoCase("B") == 0)	 
	{
		l_arm_index.Add(1);
		return 12;
	}
	if(str_arm.CompareNoCase("AB") == 0)	 
	{
		l_arm_index.Add(0);
		l_arm_index.Add(1);
		return 13;
	}

	return -1;
}

int CObj_Phy__ROBOT_VAC
::Get__LLx_INDEX(const CString& str_module)
{
	if(str_module.CompareNoCase(MODULE__LBA) == 0)		return _LLx_INDEX__LBA;
	if(str_module.CompareNoCase(MODULE__LBB) == 0)		return _LLx_INDEX__LBB;
	if(str_module.CompareNoCase(MODULE__LBC) == 0)		return _LLx_INDEX__LBC;
	if(str_module.CompareNoCase(MODULE__LBD) == 0)		return _LLx_INDEX__LBD;

	return -1;
}
int CObj_Phy__ROBOT_VAC
::Get__PMx_INDEX(const CString& str_module)
{
	CString cmp_module;

	int i_limit = iPM_SIZE;
	int i;

	for(i=0; i<i_limit; i++)
	{
		int id = i + 1;

		cmp_module.Format("PM%1d", id);
		if(str_module.CompareNoCase(cmp_module) != 0)
		{
			continue;
		}

		return i;
	}

	return -1;
}

void CObj_Phy__ROBOT_VAC
::_Get__ARM_INFO(const CString& arm_type,
				 const CString& stn_name,
				 const CString& stn_slot,
				 CStringArray& l__arm_type,
				 CStringArray& l__stn_name,
				 CStringArray& l__stn_slot)
{
	// ...
	{
		l__arm_type.RemoveAll();
		l__stn_name.RemoveAll();
		l__stn_slot.RemoveAll();
	}

	if(arm_type.CompareNoCase(_ARM__AB) == 0)
	{
		CString ch_data;

		int ll_i = Get__LLx_INDEX(stn_name);
		int pm_i = Get__PMx_INDEX(stn_name);

		if(ll_i >= 0)
		{
			l__arm_type.Add(_ARM__A);
			l__stn_name.Add(stn_name);
			l__stn_slot.Add("1");

			l__arm_type.Add(_ARM__B);
			l__stn_name.Add(stn_name);
			l__stn_slot.Add("2");
		}
		else if(pm_i >= 0)
		{
			int pm_id = ((pm_i / 2) * 2) + 1;
			int id_left  = pm_id;
			int id_right = pm_id + 1;

			l__arm_type.Add(_ARM__A);
			ch_data.Format("PM%1d", id_left);
			l__stn_name.Add(ch_data);
			l__stn_slot.Add("1");

			l__arm_type.Add(_ARM__B);
			ch_data.Format("PM%1d", id_right);
			l__stn_name.Add(ch_data);
			l__stn_slot.Add("1");
		}
		else
		{
			l__arm_type.Add(arm_type);
			l__stn_name.Add(stn_name);
			l__stn_slot.Add(stn_slot);
		}
	}
	else
	{
		l__arm_type.Add(arm_type);
		l__stn_name.Add(stn_name);
		l__stn_slot.Add(stn_slot);
	}
}
