#include "StdAfx.h"
#include "CObj_Phy__ALx_STD.h"
#include "CObj_Phy__ALx_STD__DEF.h"

#include "CCommon_System.h"


// ...
int CObj_Phy__ALx_STD
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
int CObj_Phy__ALx_STD
::Sim__MODULE_OBJ(CII_OBJECT__VARIABLE* p_variable,
				  const CString obj_mode)
{
	CII__VAR_ANALOG_CTRL* pch_analog_cfg = NULL;

	if(obj_mode.CompareNoCase(_CMMD__INIT) == 0)
	{
		pch_analog_cfg = aCH__SCH_TEST_CFG_INIT_SEC.Get__PTR();
	}
	else if(obj_mode.CompareNoCase("ALIGN") == 0)
	{
		pch_analog_cfg = aCH__SCH_TEST_CFG_ALIGN_SEC.Get__PTR();
	}
	else if(obj_mode.CompareNoCase("PICK_READY") == 0)
	{
		pch_analog_cfg = aCH__SCH_TEST_CFG_PICK_READY_SEC.Get__PTR();
	}
	else if(obj_mode.CompareNoCase("PICK_COMPLETE") == 0)
	{
		pch_analog_cfg = aCH__SCH_TEST_CFG_PICK_COMPLETE_SEC.Get__PTR();
	}
	else if(obj_mode.CompareNoCase("PLACE_READY") == 0)
	{
		pch_analog_cfg = aCH__SCH_TEST_CFG_PLACE_READY_SEC.Get__PTR();
	}
	else if(obj_mode.CompareNoCase("PLACE_COMPLETE") == 0)
	{
		pch_analog_cfg = aCH__SCH_TEST_CFG_PLACE_COMPLETE_SEC.Get__PTR();
	}

	// ...
	CString log_msg;
	CString log_bff;

	log_msg.Format("Sim__MODULE_OBJ() : Started ... \n");
	log_bff.Format(" * Obj_Mode <- %s \n", obj_mode);
	log_msg += log_bff;

	if(pch_analog_cfg == NULL)
	{
		log_msg += " * pch_analog_cfg - Error ! \n";

		xI_LOG_CTRL->WRITE__LOG(log_msg);
		return -1;
	}
	else
	{
		log_bff.Format(" * %s <- %.1f sec \n", 
						pch_analog_cfg->Get__CHANNEL_NAME(),
						pch_analog_cfg->Get__VALUE());
		log_msg += log_bff;

		xI_LOG_CTRL->WRITE__LOG(log_msg);
	}

	if(Fnc__WAIT_SEC(p_variable, pch_analog_cfg) < 0)
	{
		return -2;
	}

	if(obj_mode.CompareNoCase(_CMMD__INIT) == 0)
	{
		xCH__OBJ_STATUS->Set__DATA(STR__STANDBY);
	}

	// ...
	{
		log_msg.Format("Sim__MODULE_OBJ() : Completetd ... \n");

		xI_LOG_CTRL->WRITE__LOG(log_msg);
	}
	return 1;
}

int CObj_Phy__ALx_STD
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
