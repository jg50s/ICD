#include "StdAfx.h"
#include "CObj_NET__VAC_PERSIMMON.h"
#include "CObj_NET__VAC_PERSIMMON__DEF.h"
#include "CObj_NET__VAC_PERSIMMON__ALID.h"

#include "math.h"
#include "Macro_Function.h"
#include "CCommon_DEF.h"


//------------------------------------------------------------------------------------
int  CObj_NET__VAC_PERSIMMON
::Is__OFFLINE(CII_OBJECT__ALARM* p_alarm)
{
LOOP_RETRY:

	if(m_nCommState == OFFLINE)
	{
		int alarm_id = ALID__OFFLINE_ALARM;
		CString r_act;

		p_alarm->Popup__ALARM(alarm_id,r_act);

		if(r_act.CompareNoCase("RETRY") == 0)		goto LOOP_RETRY;
		else										return -1;
	}

	return 1;
}

int CObj_NET__VAC_PERSIMMON
::_Call__ROBOT_ACTION(CII_OBJECT__VARIABLE* p_variable,
					  const CString& cmmd_action,
					  const CString& stn_name)
{
	int r_act = doCH__COMMAND->Set__DATA(cmmd_action);
	if(r_act < 0)		return -1;

	// ...
	{
		int cmmd__act_check = -1;

		if(cmmd_action.CompareNoCase(_Cmmd__AGoto) == 0)				cmmd__act_check = 1;
		if(cmmd_action.CompareNoCase(_Cmmd__AGoto_Offset)  == 0)		cmmd__act_check = 1;
		if(cmmd_action.CompareNoCase(_Cmmd__BGoto) == 0)				cmmd__act_check = 1;
		if(cmmd_action.CompareNoCase(_Cmmd__BGoto_Offset) == 0)			cmmd__act_check = 1;

		if(cmmd_action.CompareNoCase(_Cmmd__APick_Act) == 0)			cmmd__act_check = 1;
		if(cmmd_action.CompareNoCase(_Cmmd__APick_Extend) == 0)			cmmd__act_check = 1;
		if(cmmd_action.CompareNoCase(_Cmmd__APick_Retract) == 0)		cmmd__act_check = 1;

		if(cmmd_action.CompareNoCase(_Cmmd__BPick_Act) == 0)			cmmd__act_check = 1;
		if(cmmd_action.CompareNoCase(_Cmmd__BPick_Extend) == 0)			cmmd__act_check = 1;
		if(cmmd_action.CompareNoCase(_Cmmd__BPick_Retract) == 0)		cmmd__act_check = 1;

		if(cmmd_action.CompareNoCase(_Cmmd__APlace_Act) == 0)			cmmd__act_check = 1;
		if(cmmd_action.CompareNoCase(_Cmmd__APlace_Extend) == 0)		cmmd__act_check = 1;
		if(cmmd_action.CompareNoCase(_Cmmd__APlace_Retract) == 0)		cmmd__act_check = 1;

		if(cmmd_action.CompareNoCase(_Cmmd__BPlace_Act) == 0)			cmmd__act_check = 1;
		if(cmmd_action.CompareNoCase(_Cmmd__BPlace_Extend) == 0)		cmmd__act_check = 1;
		if(cmmd_action.CompareNoCase(_Cmmd__BPlace_Retract) == 0)		cmmd__act_check = 1;

		if(cmmd_action.CompareNoCase(_Cmmd__APlace_Offset) == 0)		cmmd__act_check = 1;
		if(cmmd_action.CompareNoCase(_Cmmd__BPlace_Offset) == 0)		cmmd__act_check = 1;
		if(cmmd_action.CompareNoCase(_Cmmd__HomeAll) == 0)				cmmd__act_check = 1;
		if(cmmd_action.CompareNoCase(_Cmmd__HomeR) == 0)				cmmd__act_check = 1;

		if(cmmd__act_check < 0)		return 1;
	}

	return _Wait__ROBOT_ACTION(p_variable,stn_name);
}
int CObj_NET__VAC_PERSIMMON
::_Wait__ROBOT_ACTION(CII_OBJECT__VARIABLE* p_variable,
					  const CString& stn_name)
{
	if(iSim_Flag > 0)
	{
		return _Wait__SIM_SEC(p_variable,stn_name);
	}

	// ...
	CString cur_sts = diCH__RB_STS_READ->Get__STRING();
	if(cur_sts.CompareNoCase(STR__Busy) != 0)
	{
		return -11;
	}

	while(1)
	{
		Sleep(100);

		if(p_variable->Check__CTRL_ABORT() > 0)
		{
			return -12;
		}

		cur_sts = diCH__RB_STS_READ->Get__STRING();
		if(cur_sts.CompareNoCase(STR__Idle) == 0)
		{
			CString e_data = sCH__DRV_RB_STS->Get__STRING();
			int e_value = atoi(e_data);

			if(e_value > 0)
			{
				CString log_msg;
				CString log_bff;

				log_msg  = "\n";
				log_msg += "_Wait__ROBOT_ACTION() ... \n";
				
				log_bff.Format(" * %s <- [%s][%1d] \n",
								sCH__DRV_RB_STS->Get__CHANNEL_NAME(),
								e_data,
								e_value);
				log_msg += log_bff;

				Fnc__DRV_LOG(log_msg);			
				return -13;
			}

			return 1;
		}
	}

	return -1;
}
int  CObj_NET__VAC_PERSIMMON
::_Wait__SIM_SEC(CII_OBJECT__VARIABLE* p_variable,
				 const CString& stn_name)
{
	SCX__TIMER_CTRL x_timer_ctrl;
	x_timer_ctrl->REGISTER__ABORT_OBJECT(sObject_Name);

	double cfg_sec = 1.0;

	if(Macro__CHECK_LLx_INDEX(stn_name) > 0)
	{
		cfg_sec = aCH__SIM_CFG__LLx_MOVE_TIME->Get__VALUE();
	}
	else if(Macro__CHECK_PMx_INDEX(stn_name) >= 0)
	{
		cfg_sec = aCH__SIM_CFG__PMx_MOVE_TIME->Get__VALUE();
	}

	if(x_timer_ctrl->WAIT(cfg_sec) < 0)
	{
		return -1;
	}
	return 1;
}

CString  CObj_NET__VAC_PERSIMMON
::Get__CFG_STN_NUM(const CString& stn_name)
{
	CString cfg_stn_num = "";

	int ll_i = Macro__CHECK_LLx_INDEX(stn_name);
	int pm_i = Macro__CHECK_PMx_INDEX(stn_name);

	if(ll_i >= 0)
	{
		aCH__OTR_IN_CFG__LLx_STN_NUM[ll_i]->Get__DATA(cfg_stn_num);
	}

	if((pm_i >= 0)
	&& (pm_i <  m_nPM_LIMIT))
	{
		aCH__OTR_IN_CFG__PMx_STN_NUM[pm_i]->Get__DATA(cfg_stn_num);
	}

	return cfg_stn_num;
}

CString  CObj_NET__VAC_PERSIMMON
::Get__CFG_STN_CPTR_NUM(const CString& stn_name)
{
	CString cfg_val;

	// LLx ...
	{
		int ll_i = Macro__CHECK_LLx_INDEX(stn_name);

		if(ll_i >= 0)
		{
			aCH__OTR_IN_CFG_LLx_CPTR_SNS_NUM[ll_i]->Get__DATA(cfg_val);
		}
	}
	// PMx ...
	{
		int pm_i = Macro__CHECK_PMx_INDEX(stn_name);

		if((pm_i >= 0)
		&& (pm_i <  m_nPM_LIMIT))
		{
			aCH__OTR_IN_CFG_PMx_CPTR_SNS_NUM[pm_i]->Get__DATA(cfg_val);
		}
	}

	return cfg_val;
}
