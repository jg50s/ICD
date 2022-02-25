#include "StdAfx.h"
#include "CObj_Phy__CHM_STD.h"
#include "CObj_Phy__CHM_STD__DEF.h"

#include "CCommon_System.h"


// ...
int CObj_Phy__CHM_STD
::Fnc__MODULE_OBJ(CII_OBJECT__VARIABLE* p_variable,
				  const CString obj_mode)
{
	int flag = -1;

	if(dEXT_CH__SCH_TEST_CFG_TMC_DUMMY_BY_CTC->Check__DATA(STR__YES) > 0)
	{
		flag = Sim__MODULE_OBJ(p_variable, obj_mode);
	}
	else
	{
		flag = xI_Module_Obj->Connect__Module_Obj(obj_mode);
	}

	return flag;
}
int CObj_Phy__CHM_STD
::Sim__MODULE_OBJ(CII_OBJECT__VARIABLE* p_variable,
				  const CString obj_mode)
{
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
	else if(obj_mode.CompareNoCase(_CMMD__PUMP) == 0)
	{
		pch_analog_cfg = aCH__SCH_TEST_CFG_PUMP_SEC.Get__PTR();
	}
	else if(obj_mode.CompareNoCase(_CMMD__VENT) == 0)
	{
		pch_analog_cfg = aCH__SCH_TEST_CFG_VENT_SEC.Get__PTR();
	}
	else if(obj_mode.CompareNoCase(_CMMD__ISOLATE) == 0)
	{
		pch_analog_cfg = aCH__SCH_TEST_CFG_ISOLATE_SEC.Get__PTR();
	}
	else if(obj_mode.CompareNoCase(_CMMD__PURGE) == 0)
	{
		pch_analog_cfg = aCH__SCH_TEST_CFG_PURGE_SEC.Get__PTR();
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

		xCH__OBJ_STATUS->Set__DATA(STR__STANDBY);
	}
	else if(obj_mode.CompareNoCase(_CMMD__MAINT) == 0)
	{
		xCH__OBJ_STATUS->Set__DATA(STR__MAINTMODE);
	}
	else if(obj_mode.CompareNoCase(_CMMD__PUMP) == 0)
	{

	}
	else if(obj_mode.CompareNoCase(_CMMD__VENT) == 0)
	{

	}
	else if(obj_mode.CompareNoCase(_CMMD__ISOLATE) == 0)
	{

	}
	else if(obj_mode.CompareNoCase(_CMMD__PURGE) == 0)
	{

	}

	// ...
	{
		log_msg.Format("Sim__MODULE_OBJ() : Completetd ... \n");

		xI_LOG_CTRL->WRITE__LOG(log_msg);
	}
	return 1;
}

int CObj_Phy__CHM_STD
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
