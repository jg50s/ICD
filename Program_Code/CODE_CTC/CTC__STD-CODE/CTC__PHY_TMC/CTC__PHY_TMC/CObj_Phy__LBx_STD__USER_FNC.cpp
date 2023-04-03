#include "StdAfx.h"
#include "CObj_Phy__LBx_STD.h"
#include "CObj_Phy__LBx_STD__DEF.h"

#include "CCommon_System.h"
#include "Macro_Function.h"


// SCH_TEST : CONFIG ...
int CObj_Phy__LBx_STD
::Call__SCH_TEST_CFG(CII_OBJECT__VARIABLE* p_variable,
					 CII_OBJECT__ALARM* p_alarm)
{

	aCH__SCH_TEST_CFG_INIT_SEC->Set__VALUE(5.0);

	aCH__SCH_TEST_CFG_PUMP_SEC->Set__VALUE(5.0);
	aCH__SCH_TEST_CFG_VENT_SEC->Set__VALUE(5.0);

	aCH__SCH_TEST_CFG_DOOR_SEC->Set__VALUE(1.0);
	aCH__SCH_TEST_CFG_SLOT_SEC->Set__VALUE(1.0);

	aCH__SCH_TEST_CFG_PREPMATER_SEC->Set__VALUE(1.0);
	aCH__SCH_TEST_CFG_MAP_SEC->Set__VALUE(1.0);
	
	aCH__SCH_TEST_CFG_COMPMATER_SEC->Set__VALUE(5.0);
	aCH__SCH_TEST_CFG_COMPMATER_EX_SEC->Set__VALUE(5.0);

	aCH__SCH_TEST_CFG_ISOLATE_SEC->Set__VALUE(5.0);
	aCH__SCH_TEST_CFG_LOAD_SEC->Set__VALUE(5.0);
	aCH__SCH_TEST_CFG_UNLOAD_SEC->Set__VALUE(5.0);

	return 1;
}


// ...
int CObj_Phy__LBx_STD
::Fnc__MODULE_OBJ(CII_OBJECT__VARIABLE* p_variable,
				  CII_OBJECT__ALARM* p_alarm,
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

	if((obj_mode.CompareNoCase(_CMMD__PROC_START) == 0)
	|| (obj_mode.CompareNoCase(_CMMD__PRE_START)  == 0)
	|| (obj_mode.CompareNoCase(_CMMD__CLN_START)  == 0)
	|| (obj_mode.CompareNoCase(_CMMD__MNT_START)  == 0))
	{
		sCH__PROC_INFO_CUR_PROC_TIME->Set__DATA("");

		iActive__PROC_STS = 1;
	}

	if(dEXT_CH__SCH_TEST_CFG_TMC_DUMMY_BY_CTC->Check__DATA(STR__YES) > 0)
	{
		flag = Sim__MODULE_OBJ(p_variable,p_alarm, obj_mode);
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
int CObj_Phy__LBx_STD
::Sim__MODULE_OBJ(CII_OBJECT__VARIABLE* p_variable,
				  CII_OBJECT__ALARM* p_alarm,
				  const CString obj_mode)
{
LOOP_RETRY:

	CII__VAR_ANALOG_CTRL* pch_analog_cfg = NULL;
	bool active_check = true;

	if(obj_mode.CompareNoCase(_CMMD__INIT) == 0)
	{
		pch_analog_cfg = aCH__SCH_TEST_CFG_INIT_SEC.Get__PTR();
	}
	else if(obj_mode.CompareNoCase(_CMMD__MAINT) == 0)
	{
		active_check = false;
	}
	else if(obj_mode.CompareNoCase(_CMMD__VENT) == 0)
	{
		pch_analog_cfg = aCH__SCH_TEST_CFG_VENT_SEC.Get__PTR();
	}
	else if(obj_mode.CompareNoCase(_CMMD__PUMP) == 0)
	{
		pch_analog_cfg = aCH__SCH_TEST_CFG_PUMP_SEC.Get__PTR();
	}
	else if((obj_mode.CompareNoCase(_CMMD__DOOR_OPEN)  == 0)
		 || (obj_mode.CompareNoCase(_CMMD__DOOR_CLOSE) == 0))
	{
		// Interlock Check ...
		if(obj_mode.CompareNoCase(_CMMD__DOOR_OPEN) == 0)
		{
			bool active__err_check = false;

			double cur__pressure_torr = xCH__PRESSURE_VALUE->Get__VALUE();
			double cfg__pressure_torr = 0.0;

			if(xEXT_CH_CFG__TRANSFER_MODE->Check__DATA(STR__ATM) > 0)
			{
				cfg__pressure_torr = aEXT_CH_CFG__REF_ATM_PRESSURE->Get__VALUE();

				if(cur__pressure_torr < cfg__pressure_torr)
				{
					active__err_check = true;
				}
			}
			else
			{
				cfg__pressure_torr = aEXT_CH_CFG__REF_VAC_PRESSURE->Get__VALUE();

				if(cur__pressure_torr > cfg__pressure_torr)
				{
					active__err_check = true;
				}
			}

			if(active__err_check)
			{
				int alm_id = ALID__DOOR_VALVE_OPEN_ERROR;
				CString alm_msg;
				CString alm_bff;
				CString r_act;

				// ...
				{
					alm_bff.Format("Current pressure is %.3f torr \n", cur__pressure_torr);
					alm_msg += alm_bff;

					alm_bff.Format("Config pressure is %.3f torr \n", cfg__pressure_torr);
					alm_msg += alm_bff;
				}

				p_alarm->Popup__ALARM_With_MESSAGE(alm_id, alm_msg, r_act);
	
				if(r_act.CompareNoCase(_ACT__RETRY) == 0)
				{
					goto LOOP_RETRY;
				}
				return -101;
			}
		}

		pch_analog_cfg = aCH__SCH_TEST_CFG_DOOR_SEC.Get__PTR();
	}
	else if((obj_mode.CompareNoCase(_CMMD__SLOT_OPEN)  == 0)
		 || (obj_mode.CompareNoCase(_CMMD__SLOT_CLOSE) == 0))
	{
		// Interlock Check ...
		if(obj_mode.CompareNoCase(_CMMD__SLOT_OPEN) == 0)
		{
			bool active__err_check = false;

			double cur__pressure_torr = xCH__PRESSURE_VALUE->Get__VALUE();
			double cfg__pressure_torr = 0.0;

			if(xEXT_CH_CFG__TRANSFER_MODE->Check__DATA(STR__ATM) > 0)
			{
				double cfg__pressure_torr = aEXT_CH_CFG__REF_ATM_PRESSURE->Get__VALUE();

				if(cur__pressure_torr < cfg__pressure_torr)
				{
					active__err_check = true;
				}
			}
			else
			{
				double cfg__pressure_torr = aEXT_CH_CFG__REF_VAC_PRESSURE->Get__VALUE();

				if(cur__pressure_torr > cfg__pressure_torr)
				{
					active__err_check = true;
				}
			}

			if(active__err_check)
			{
				int alm_id = ALID__SLOT_VALVE_OPEN_ERROR;
				CString alm_msg;
				CString alm_bff;
				CString r_act;

				// ...
				{
					alm_bff.Format("Current pressure is %.3f torr \n", cur__pressure_torr);
					alm_msg += alm_bff;

					alm_bff.Format("Config pressure is %.3f torr \n", cfg__pressure_torr);
					alm_msg += alm_bff;
				}

				p_alarm->Popup__ALARM_With_MESSAGE(alm_id, alm_msg, r_act);

				if(r_act.CompareNoCase(_ACT__RETRY) == 0)
				{
					goto LOOP_RETRY;
				}
				return -201;
			}
		}

		pch_analog_cfg = aCH__SCH_TEST_CFG_SLOT_SEC.Get__PTR();
	}
	else if(obj_mode.CompareNoCase(_CMMD__PREPMATER) == 0)
	{
		pch_analog_cfg = aCH__SCH_TEST_CFG_PREPMATER_SEC.Get__PTR();
	}
	else if(obj_mode.CompareNoCase(_CMMD__COMPMATER) == 0)
	{
		pch_analog_cfg = aCH__SCH_TEST_CFG_COMPMATER_SEC.Get__PTR();
	}
	else if(obj_mode.CompareNoCase(_CMMD__COMPMATER_EX) == 0)
	{
		pch_analog_cfg = aCH__SCH_TEST_CFG_COMPMATER_EX_SEC.Get__PTR();

		// ...
		{
			SCX__ASYNC_TIMER_CTRL x_timer_ctrl;
			CString ch_data;
		
			pch_analog_cfg->Get__DATA(ch_data);
			xCH__CFG_HEATING_TIME->Set__DATA(ch_data);
			double cfg_sec = atof(ch_data);

			x_timer_ctrl->REGISTER__COUNT_CHANNEL_NAME(xCH__APP_HEATING_TIME_COUNT->Get__CHANNEL_NAME());
			x_timer_ctrl->START__COUNT_DOWN(cfg_sec);
		}
	}
	else if((obj_mode.CompareNoCase(_CMMD__PROC_READY) == 0)
		 || (obj_mode.CompareNoCase(_CMMD__PRE_READY)  == 0)
		 || (obj_mode.CompareNoCase(_CMMD__CLN_READY)  == 0)
		 || (obj_mode.CompareNoCase(_CMMD__MNT_READY)  == 0))
	{
		pch_analog_cfg = aCH__SCH_TEST_CFG_PROC_READY_SEC.Get__PTR();
	}
	else if((obj_mode.CompareNoCase(_CMMD__PROC_START) == 0)
		 || (obj_mode.CompareNoCase(_CMMD__PRE_START)  == 0)
		 || (obj_mode.CompareNoCase(_CMMD__CLN_START)  == 0)
		 || (obj_mode.CompareNoCase(_CMMD__MNT_START)  == 0))
	{
		pch_analog_cfg = aCH__SCH_TEST_CFG_PROC_START_SEC.Get__PTR();
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
		xCH__PRESSURE_STATUS->Set__DATA("VAC");
		xCH__PRESSURE_VALUE->Set__DATA("0.000");
		xCH__PRESSURE_mTORR->Set__DATA("0.0");
		xCH__VAC_SNS->Set__DATA("ON");

		// ...
		{
			dCH__SLIT_VLV_STS_X->Set__DATA(STR__CLOSE);
		
			for(int i=0; i<CFG_LBx__SLOT_MAX; i++)
				dCH__SLIT_VLV_STS_SLOT[i]->Set__DATA(STR__CLOSE);
		}
		// ...
		{
			dCH__DOOR_STS_X->Set__DATA(STR__CLOSE);

			for(int i=0; i<CFG_LBx__SLOT_MAX; i++)
				dCH__DOOR_STS_SLOT[i]->Set__DATA(STR__CLOSE);
		}

		xCH__OBJ_STATUS->Set__DATA(STR__STANDBY);
	}
	else if(obj_mode.CompareNoCase(_CMMD__MAINT) == 0)
	{
		xCH__OBJ_STATUS->Set__DATA(STR__MAINTMODE);
	}
	else if(obj_mode.CompareNoCase(_CMMD__VENT) == 0)
	{
		xCH__PRESSURE_STATUS->Set__DATA("ATM");
		xCH__PRESSURE_VALUE->Set__DATA("770.0");
		xCH__PRESSURE_mTORR->Set__DATA("770000");
		xCH__VAC_SNS->Set__DATA("OFF");
	}
	else if(obj_mode.CompareNoCase(_CMMD__PUMP) == 0)
	{
		xCH__PRESSURE_STATUS->Set__DATA("VAC");
		xCH__PRESSURE_VALUE->Set__DATA("0.000");
		xCH__PRESSURE_mTORR->Set__DATA("0.0");
		xCH__VAC_SNS->Set__DATA("ON");
	}
	else if(obj_mode.CompareNoCase(_CMMD__DOOR_OPEN) == 0)
	{
		CString ch_data = dCH__PARA_SLOT_ID->Get__STRING();
		int slot_index = atoi(ch_data) - 1;

		dCH__DOOR_STS_X->Set__DATA(STR__OPEN);
		dCH__DOOR_STS_SLOT[slot_index]->Set__DATA(STR__OPEN);
	}
	else if(obj_mode.CompareNoCase(_CMMD__DOOR_CLOSE) == 0)
	{
		CString ch_data = dCH__PARA_SLOT_ID->Get__STRING();
		int slot_index = atoi(ch_data) - 1;

		dCH__DOOR_STS_X->Set__DATA(STR__CLOSE);
		dCH__DOOR_STS_SLOT[slot_index]->Set__DATA(STR__CLOSE);
	}
	else if(obj_mode.CompareNoCase(_CMMD__SLOT_OPEN) == 0)
	{
		CString ch_data = dCH__PARA_SLOT_ID->Get__STRING();
		int slot_index = atoi(ch_data) - 1;

		dCH__SLIT_VLV_STS_X->Set__DATA(STR__OPEN);
		dCH__SLIT_VLV_STS_SLOT[slot_index]->Set__DATA(STR__OPEN);
	}
	else if(obj_mode.CompareNoCase(_CMMD__SLOT_CLOSE) == 0)
	{
		CString ch_data = dCH__PARA_SLOT_ID->Get__STRING();
		int slot_index = atoi(ch_data) - 1;

		dCH__SLIT_VLV_STS_X->Set__DATA(STR__CLOSE);
		dCH__SLIT_VLV_STS_SLOT[slot_index]->Set__DATA(STR__CLOSE);
	}
	else if(obj_mode.CompareNoCase(_CMMD__PREPMATER) == 0)
	{

	}
	else if(obj_mode.CompareNoCase(_CMMD__COMPMATER) == 0)
	{

	}
	else if(obj_mode.CompareNoCase(_CMMD__COMPMATER_EX) == 0)
	{

	}

	// ...
	{
		log_msg.Format("Sim__MODULE_OBJ() : Completetd ... \n");

		xI_LOG_CTRL->WRITE__LOG(log_msg);
	}
	return 1;
}

int CObj_Phy__LBx_STD
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
