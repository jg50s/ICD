#include "StdAfx.h"
#include "CObj_Phy__SYS_STD.h"
#include "CObj_Phy__SYS_STD__DEF.h"

#include "CCommon_System.h"


// ...
int CObj_Phy__SYS_STD
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
int CObj_Phy__SYS_STD
::Sim__MODULE_OBJ(CII_OBJECT__VARIABLE* p_variable,
				  const CString obj_mode)
{
	CII__VAR_ANALOG_CTRL* pch_analog_cfg = NULL;

	if((obj_mode.CompareNoCase(_CMMD__TIME_INIT)    == 0)
	|| (obj_mode.CompareNoCase(_CMMD__SYSTEM_INIT)  == 0)
	|| (obj_mode.CompareNoCase(_CMMD__AUTO_INIT)    == 0)
	|| (obj_mode.CompareNoCase(_CMMD__SYSTEM_MAINT) == 0))
	{
		pch_analog_cfg = aCH__SCH_TEST_CFG_INIT_SEC.Get__PTR();
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
	else if(obj_mode.CompareNoCase(_CMMD__SYSTEM_MAINT) == 0)
	{
		// OBJ : EFEM_ROBOT ...
		{
			pOBJ_CTRL__EFEM_ROBOT->Call__OBJECT(_CMMD__MAINT);
		}
		// OBJ : VAC_ROBOT ...
		{
			pOBJ_CTRL__VAC_ROBOT->Call__OBJECT(_CMMD__MAINT);
		}

		// OBJ : LLx ...
		for(int i=0; i<iLLx_SIZE; i++)
		{
			pOBJ_CTRL__LLx[i]->Call__OBJECT(_CMMD__MAINT);
		}

		// OBJ : TMC_CHM ...
		{
			pOBJ_CTRL__TMC_CHM->Call__OBJECT(_CMMD__MAINT);
		}
	}
	else
	{
		int i;

		// OBJ_EFEM_ROBOT ...
		{
			pOBJ_CTRL__EFEM_ROBOT->Call__OBJECT(_CMMD__INIT);
		}
		// OBJ_VAC_ROBOT ...
		{
			pOBJ_CTRL__VAC_ROBOT->Call__OBJECT(_CMMD__INIT);
		}

		// OBJ_LPx ...
		for(i=0; i<iLP_SIZE; i++)
		{
			pOBJ_CTRL__LPx[i]->Call__OBJECT(_CMMD__INIT);
		}

		// OBJ_ALx ...
		{
			pOBJ_CTRL__AL1->Call__OBJECT(_CMMD__INIT);
		}

		// OBJ_LLx ...
		for(i=0; i<iLLx_SIZE; i++)
		{
			pOBJ_CTRL__LLx[i]->Call__OBJECT(_CMMD__INIT);
		}

		// OBJ_TMC_CHM ...
		{
			pOBJ_CTRL__TMC_CHM->Call__OBJECT(_CMMD__INIT);
		}

		// OBJ_PMX ...
		for(i=0; i<iPM_SIZE; i++)
		{
			pEXT_CH__PMx_SLIT_VLV[i]->Set__DATA(STR__CLOSE);
		}

		// ...
		{
			log_bff.Format(" * %s <- %.1f sec \n", 
							pch_analog_cfg->Get__CHANNEL_NAME(),
							pch_analog_cfg->Get__VALUE());
			log_msg += log_bff;

			xI_LOG_CTRL->WRITE__LOG(log_msg);
		}
	}

	if(Fnc__WAIT_SEC(p_variable, pch_analog_cfg) < 0)
	{
		return -2;
	}

	if((obj_mode.CompareNoCase(_CMMD__TIME_INIT)   == 0)
	|| (obj_mode.CompareNoCase(_CMMD__SYSTEM_INIT) == 0)
	|| (obj_mode.CompareNoCase(_CMMD__AUTO_INIT)   == 0))
	{
		xCH__OBJ_STATUS->Set__DATA(STR__STANDBY);
	}
	else if(obj_mode.CompareNoCase(_CMMD__SYSTEM_MAINT) == 0)
	{
		xCH__OBJ_STATUS->Set__DATA(STR__MAINTMODE);
	}

	// ...
	{
		log_msg.Format("Sim__MODULE_OBJ() : Completetd ... \n");

		xI_LOG_CTRL->WRITE__LOG(log_msg);
	}
	return 1;
}

int CObj_Phy__SYS_STD
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
