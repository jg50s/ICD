#include "StdAfx.h"
#include "CObj_NET__VAC_PERSIMMON.h"
#include "CObj_NET__VAC_PERSIMMON__DEF.h"
#include "CObj_NET__VAC_PERSIMMON__ALID.h"

#include "Macro_Function.h"
#include "CCommon_DEF.h"


//-------------------------------------------------------------------------	
int  CObj_NET__VAC_PERSIMMON
::Call__INIT(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm)
{
	if(iSim_Flag > 0)
	{
		Sleep(1500);

		m_nCommState = ONLINE;
	}

	return Fnc__INIT(p_variable,p_alarm);
}
int  CObj_NET__VAC_PERSIMMON
::Fnc__INIT(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm)
{
	// Info ...
	{
		CString ch_data;

		siCH__VERSION->Get__DATA(ch_data);
		sCH__VERSION->Set__DATA(ch_data);
	}

	if(_Call__ROBOT_ACTION(p_variable, _Cmmd__HomeAll, "") < 0)
	{
		return -11;
	}

	if(Fnc__HOME(p_variable, p_alarm) < 0)
	{
		return -12;
	}
	return 1;
}

int  CObj_NET__VAC_PERSIMMON
::Call__PICK(CII_OBJECT__VARIABLE* p_variable,
		     CII_OBJECT__ALARM* p_alarm,
		     const CString& stn_name,
		     const CString& arm_type,
		     const CString& stn_slot)
{
	// ...
	{
		CString ch_data = "???";

		sCH__DA_RESULT_R_OFFSET_DEG->Set__DATA(ch_data);
		sCH__DA_RESULT_T_OFFSET_MM->Set__DATA(ch_data);
	}

	return Fnc__PICK(p_variable,p_alarm, stn_name,arm_type,stn_slot);
}
int  CObj_NET__VAC_PERSIMMON
::Fnc__PICK(CII_OBJECT__VARIABLE* p_variable,
		    CII_OBJECT__ALARM* p_alarm,
		    const CString& stn_name,
		    const CString& arm_type,
		    const CString& stn_slot)
{
	// ...
	{
			 if(arm_type.CompareNoCase(ARM_A) == 0)		doCH__COMMAND->Set__DATA(_Cmmd__UnloadA);
		else if(arm_type.CompareNoCase(ARM_B) == 0)		doCH__COMMAND->Set__DATA(_Cmmd__UnloadB);
	}

	int r_flag = _Fnc__PICK(p_variable,p_alarm, stn_name,arm_type,stn_slot);

	if(r_flag > 0)
	{
			 if(arm_type.CompareNoCase(ARM_A) == 0)		doCH__COMMAND->Set__DATA(_Cmmd__LoadA);
		else if(arm_type.CompareNoCase(ARM_B) == 0)		doCH__COMMAND->Set__DATA(_Cmmd__LoadB);
	}

	if(r_flag > 0)
	{
		_Update__WFR_CEN_DATA(p_variable);
	}
	return r_flag;
}
int  CObj_NET__VAC_PERSIMMON
::_Fnc__PICK(CII_OBJECT__VARIABLE* p_variable,
			 CII_OBJECT__ALARM* p_alarm,
			 const CString& stn_name,
			 const CString& arm_type,
			 const CString& stn_slot)
{
	Fnc__ACT_MSG("_Fnc_Pick : Start...");

	// ...
	CString str__trg_stn_num;

	// Set Station
	{
		str__trg_stn_num = Get__CFG_STN_NUM(stn_name);

			 if(arm_type.CompareNoCase(ARM_A) == 0)		doCH__STN_A->Set__DATA(str__trg_stn_num);
		else if(arm_type.CompareNoCase(ARM_B) == 0)		doCH__STN_B->Set__DATA(str__trg_stn_num);

		doCH__SLOT->Set__DATA(stn_slot);
	}

	// Action : [Pick] ...
	{
		CString cmmd__arm_pick = "???";

			 if(arm_type.CompareNoCase(ARM_A) == 0)		cmmd__arm_pick = _Cmmd__APick_Act;
		else if(arm_type.CompareNoCase(ARM_B) == 0)		cmmd__arm_pick = _Cmmd__BPick_Act;

		if(_Call__ROBOT_ACTION(p_variable, cmmd__arm_pick, stn_name) < 0)
		{
			return -11;
		}
	}

	if(Is__OFFLINE(p_alarm) < 0)
	{
		return -12;
	}
	return 1;
}

int  CObj_NET__VAC_PERSIMMON
::Call__PLACE(CII_OBJECT__VARIABLE* p_variable,
			  CII_OBJECT__ALARM* p_alarm,
			  const CString& stn_name,
			  const CString& arm_type,
			  const CString& stn_slot)
{
	// ...
	{
		CString ch_data = "???";

		sCH__DA_RESULT_R_OFFSET_DEG->Set__DATA(ch_data);
		sCH__DA_RESULT_T_OFFSET_MM->Set__DATA(ch_data);
	}

	return Fnc__PLACE(p_variable,p_alarm, stn_name,arm_type,stn_slot);
}
int  CObj_NET__VAC_PERSIMMON
::Fnc__PLACE(CII_OBJECT__VARIABLE* p_variable,
		     CII_OBJECT__ALARM* p_alarm,
		     const CString& stn_name,
		     const CString& arm_type,
		     const CString& stn_slot)
{
	Fnc__ACT_MSG("Place Start...");

	if(Is__OFFLINE(p_alarm) < 0)
	{
		return -1;
	}

	// ...
	{
			 if(arm_type.CompareNoCase(ARM_A) == 0)		doCH__COMMAND->Set__DATA(_Cmmd__LoadA);
		else if(arm_type.CompareNoCase(ARM_B) == 0)		doCH__COMMAND->Set__DATA(_Cmmd__LoadB);
	}

	int r_flag = _Fnc__PLACE(p_variable,p_alarm, stn_name,arm_type,stn_slot);

	if(r_flag > 0)
	{
			 if(arm_type.CompareNoCase(ARM_A) == 0)		doCH__COMMAND->Set__DATA(_Cmmd__UnloadA);
		else if(arm_type.CompareNoCase(ARM_B) == 0)		doCH__COMMAND->Set__DATA(_Cmmd__UnloadB);
	}

	if(r_flag > 0)
	{
		_Update__WFR_CEN_DATA(p_variable);
	}
	return r_flag;
}
int  CObj_NET__VAC_PERSIMMON
::_Fnc__PLACE(CII_OBJECT__VARIABLE* p_variable,
			  CII_OBJECT__ALARM* p_alarm,
			  const CString& stn_name,
			  const CString& arm_type,
			  const CString& stn_slot)
{
	Fnc__ACT_MSG("Place Start...");

	if(Is__OFFLINE(p_alarm) < 0)
	{
		return -1;
	}

	// Set Station ...
	{
		CString str__trg_stn_num = Get__CFG_STN_NUM(stn_name);

			 if(arm_type.CompareNoCase(ARM_A) == 0)		doCH__STN_A->Set__DATA(str__trg_stn_num);
		else if(arm_type.CompareNoCase(ARM_B) == 0)		doCH__STN_B->Set__DATA(str__trg_stn_num);

		doCH__SLOT->Set__DATA(stn_slot);
	}

	// Place ...
	{
		CString cmmd__arm_act = "???";

			 if(arm_type.CompareNoCase(ARM_A) == 0)		cmmd__arm_act = _Cmmd__APlace_Act;
		else if(arm_type.CompareNoCase(ARM_B) == 0)		cmmd__arm_act = _Cmmd__BPlace_Act;

		if(_Call__ROBOT_ACTION(p_variable, cmmd__arm_act, stn_name) < 0)
		{
			return -11;
		}
	}

	// ...
	{
		CString log_msg;

		log_msg.Format("PLACE : End ...");
		Fnc__APP_LOG(log_msg);
	}
	return 1;
}

// ...
int  CObj_NET__VAC_PERSIMMON
::Call__EXTEND(CII_OBJECT__VARIABLE* p_variable,
			   CII_OBJECT__ALARM* p_alarm,
			   const CString& act_cmmd,
			   const CString& stn_name, 
			   const CString& arm_type,
			   const CString& stn_slot)
{
	bool active_pick = false;

	if(arm_type.CompareNoCase(ARM_A) == 0)
	{
		if(dCH__OTR_OUT_MON__ARM_A_MATERIAL_STATUS->Check__DATA("NONE") > 0)		active_pick = true;
	}
	else if(arm_type.CompareNoCase(ARM_B) == 0)
	{
		if(dCH__OTR_OUT_MON__ARM_B_MATERIAL_STATUS->Check__DATA("NONE") > 0)		active_pick = true;
	}
	else
	{
		return -11;
	}

	return Fnc__EXTEND_ACT(p_variable,p_alarm, active_pick, stn_name,arm_type,stn_slot);
}
int  CObj_NET__VAC_PERSIMMON
::Fnc__EXTEND_ACT(CII_OBJECT__VARIABLE* p_variable,
				  CII_OBJECT__ALARM* p_alarm,
				  const bool act_pick,
				  const CString& stn_name, 
				  const CString& arm_type,
				  const CString& stn_slot)
{
	if(act_pick)		Fnc__ACT_MSG("Extend.Pick Start...");
	else				Fnc__ACT_MSG("Extend.Place Start...");

	// ...
	{
		CString ch_data = "???";

		sCH__DA_RESULT_R_OFFSET_DEG->Set__DATA(ch_data);
		sCH__DA_RESULT_T_OFFSET_MM->Set__DATA(ch_data);
	}

	if(act_pick)
	{
			 if(arm_type.CompareNoCase(ARM_A) == 0)		doCH__COMMAND->Set__DATA(_Cmmd__UnloadA);
		else if(arm_type.CompareNoCase(ARM_B) == 0)		doCH__COMMAND->Set__DATA(_Cmmd__UnloadB);
	}
	else
	{
			 if(arm_type.CompareNoCase(ARM_A) == 0)		doCH__COMMAND->Set__DATA(_Cmmd__LoadA);
		else if(arm_type.CompareNoCase(ARM_B) == 0)		doCH__COMMAND->Set__DATA(_Cmmd__LoadB);
	}

	int r_flag = _Fnc__EXTEND_ACT(p_variable,p_alarm, act_pick, stn_name,arm_type,stn_slot);

	// ...
	{
		CString log_msg;

		if(act_pick)		log_msg.Format("Extend.Pick : End (%1d) ...", r_flag);
		else				log_msg.Format("Extend.Place : End (%1d) ...", r_flag);

		Fnc__APP_LOG(log_msg);
	}
	return r_flag;
}
int  CObj_NET__VAC_PERSIMMON
::_Fnc__EXTEND_ACT(CII_OBJECT__VARIABLE* p_variable,
				   CII_OBJECT__ALARM* p_alarm,
				   const bool act_pick,
				   const CString& stn_name, 
				   const CString& arm_type,
				   const CString& stn_slot)
{
	if(Is__OFFLINE(p_alarm) < 0)
	{
		return -11;
	}

	// Set Station ...
	{
		CString str__trg_stn_num = Get__CFG_STN_NUM(stn_name);

			 if(arm_type.CompareNoCase(ARM_A) == 0)			doCH__STN_A->Set__DATA(str__trg_stn_num);
		else if(arm_type.CompareNoCase(ARM_B) == 0)			doCH__STN_B->Set__DATA(str__trg_stn_num);

		doCH__SLOT->Set__DATA(stn_slot);
	}

	// Extend ...
	{
		CString cmmd__arm_act = "???";

		if(arm_type.CompareNoCase(ARM_A) == 0)
		{
			if(act_pick)			cmmd__arm_act = _Cmmd__APick_Extend;
			else					cmmd__arm_act = _Cmmd__APlace_Extend;
		}
		else if(arm_type.CompareNoCase(ARM_B) == 0)
		{
			if(act_pick)			cmmd__arm_act = _Cmmd__BPick_Extend;
			else					cmmd__arm_act = _Cmmd__BPlace_Extend;
		}

		if(_Call__ROBOT_ACTION(p_variable, cmmd__arm_act, stn_name) < 0)
		{
			return -12;
		}
	}
	return 1;
}

int  CObj_NET__VAC_PERSIMMON
::Call__RETRACT(CII_OBJECT__VARIABLE* p_variable,
				CII_OBJECT__ALARM* p_alarm,
				const CString& act_cmmd,
				const CString& stn_name, 
				const CString& arm_type,
				const CString& stn_slot)
{
	bool active_pick = false;

	if(arm_type.CompareNoCase(ARM_A) == 0)
	{
		if(dCH__OTR_OUT_MON__ARM_A_MATERIAL_STATUS->Check__DATA("NONE") < 0)		active_pick = true;
	}
	else if(arm_type.CompareNoCase(ARM_B) == 0)
	{
		if(dCH__OTR_OUT_MON__ARM_B_MATERIAL_STATUS->Check__DATA("NONE") < 0)		active_pick = true;
	}
	else
	{
		return -11;
	}

	Fnc__RETRACT_ACT(p_variable,p_alarm, active_pick, stn_name,arm_type,stn_slot);
}
int  CObj_NET__VAC_PERSIMMON
::Fnc__RETRACT_ACT(CII_OBJECT__VARIABLE* p_variable,
				    CII_OBJECT__ALARM* p_alarm,
				    const bool act_pick,
				    const CString& stn_name, 
				    const CString& arm_type,
				    const CString& stn_slot)
{
	if(act_pick)		Fnc__ACT_MSG("Retract.Pick Start...");
	else				Fnc__ACT_MSG("Retract.Place Start...");

	int r_flag = _Fnc__RETRACT_ACT(p_variable,p_alarm, act_pick, stn_name,arm_type,stn_slot);

	if(r_flag > 0)
	{
		if(act_pick)
		{
				 if(arm_type.CompareNoCase(ARM_A) == 0)		doCH__COMMAND->Set__DATA(_Cmmd__LoadA);
			else if(arm_type.CompareNoCase(ARM_B) == 0)		doCH__COMMAND->Set__DATA(_Cmmd__LoadB);
		}
		else
		{
				 if(arm_type.CompareNoCase(ARM_A) == 0)		doCH__COMMAND->Set__DATA(_Cmmd__UnloadA);
			else if(arm_type.CompareNoCase(ARM_B) == 0)		doCH__COMMAND->Set__DATA(_Cmmd__UnloadB);
		}

		_Update__WFR_CEN_DATA(p_variable);
	}

	// ...
	{
		CString log_msg;

		if(act_pick)		log_msg.Format("Retract.Pick : End (%1d) ...", r_flag);
		else				log_msg.Format("Retract.Place : End (%1d) ...", r_flag);

		Fnc__APP_LOG(log_msg);
	}
	return r_flag;
}
int  CObj_NET__VAC_PERSIMMON
::_Fnc__RETRACT_ACT(CII_OBJECT__VARIABLE* p_variable,
					CII_OBJECT__ALARM* p_alarm,
					const bool act_pick,
					const CString& stn_name, 
					const CString& arm_type,
					const CString& stn_slot)
{
	if(Is__OFFLINE(p_alarm) < 0)
	{
		return -11;
	}

	// Set Station ...
	{
		CString str__trg_stn_num = Get__CFG_STN_NUM(stn_name);

			 if(arm_type.CompareNoCase(ARM_A) == 0)			doCH__STN_A->Set__DATA(str__trg_stn_num);
		else if(arm_type.CompareNoCase(ARM_B) == 0)			doCH__STN_B->Set__DATA(str__trg_stn_num);

		doCH__SLOT->Set__DATA(stn_slot);
	}

	// Retract ...
	{
		CString cmmd__arm_act = "???";

		if(arm_type.CompareNoCase(ARM_A) == 0)
		{
			if(act_pick)			cmmd__arm_act = _Cmmd__APick_Retract;
			else					cmmd__arm_act = _Cmmd__APlace_Retract;
		}
		else if(arm_type.CompareNoCase(ARM_B) == 0)
		{
			if(arm_type)			cmmd__arm_act = _Cmmd__BPick_Retract;
			else					cmmd__arm_act = _Cmmd__BPlace_Retract;
		}

		if(_Call__ROBOT_ACTION(p_variable, cmmd__arm_act, stn_name) < 0)
		{
			return -12;
		}
	}
	return 1;
}

// Rotate -----
int  CObj_NET__VAC_PERSIMMON
::Call__ROTATE(CII_OBJECT__VARIABLE* p_variable,
			   CII_OBJECT__ALARM* p_alarm,
			   const CString& para__stn_name, 
			   const CString& para__arm_type,
			   const CString& para__stn_slot)
{

	return Fnc__ROTATE(p_variable,p_alarm, para__stn_name,para__arm_type,para__stn_slot);
}
int  CObj_NET__VAC_PERSIMMON
::Fnc__ROTATE(CII_OBJECT__VARIABLE* p_variable,
			  CII_OBJECT__ALARM* p_alarm,
			  const CString& stn_name, 
			  const CString& arm_type,
			  const CString& stn_slot)
{
	Fnc__ACT_MSG("Rotate Start...");

	if(Is__OFFLINE(p_alarm) < 0)
	{
		return -1;
	}

	// ...
	{
		CString str__trg_stn_num = Get__CFG_STN_NUM(stn_name);

			 if(arm_type.CompareNoCase(ARM_A) == 0)		doCH__STN_A->Set__DATA(str__trg_stn_num);
		else if(arm_type.CompareNoCase(ARM_B) == 0)		doCH__STN_B->Set__DATA(str__trg_stn_num);

		doCH__SLOT->Set__DATA(stn_slot);
	}

	// ...
	{
		CString str__zpos = "Down";

		if(arm_type.CompareNoCase(ARM_A) == 0)
		{
			if(dCH__OTR_OUT_MON__ARM_A_MATERIAL_STATUS->Check__DATA("NONE") > 0)		str__zpos = "Down";
			else																		str__zpos = "Up";
		}
		else if(arm_type.CompareNoCase(ARM_B) == 0)
		{
			if(dCH__OTR_OUT_MON__ARM_B_MATERIAL_STATUS->Check__DATA("NONE") > 0)		str__zpos = "Down";
			else																		str__zpos = "Up";
		}

		doCH__ZPOS->Set__DATA(str__zpos);
		doCH__RPOS->Set__DATA("Retract");
	}

	// ...
	{
		CString cmmd__arm_act = "???";

			 if(arm_type.CompareNoCase(ARM_A) == 0)		cmmd__arm_act = _Cmmd__AGoto;
		else if(arm_type.CompareNoCase(ARM_B) == 0)		cmmd__arm_act = _Cmmd__BGoto;

		if(_Call__ROBOT_ACTION(p_variable, cmmd__arm_act, stn_name) < 0)
		{
			return -11;
		}
	}
	return 1;
}

int  CObj_NET__VAC_PERSIMMON
::Call__HOME(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm)
{

	return Fnc__HOME(p_variable,p_alarm);
}
int  CObj_NET__VAC_PERSIMMON
::Fnc__HOME(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm)
{
	if(Is__OFFLINE(p_alarm) < 0)
	{
		return -1;
	}

	// ...
	{
		CString cmmd__arm_act = _Cmmd__HomeAll;

		if(_Call__ROBOT_ACTION(p_variable, cmmd__arm_act, "") < 0)
		{
			return -11;
		}
	}
	return 1;
}

int  CObj_NET__VAC_PERSIMMON
::Call__RQ_WFR_CEN_DATA(CII_OBJECT__VARIABLE* p_variable,
					    CII_OBJECT__ALARM* p_alarm)
{
	_Update__WFR_CEN_DATA(p_variable);
	return 1;
}

int  CObj_NET__VAC_PERSIMMON
::Call__CHECK_ERROR_CODE(CII_OBJECT__VARIABLE* p_variable,
						 CII_OBJECT__ALARM* p_alarm)
{
LOOP_RETRY:

	mMNG__ERR_CODE.Clear__Error_Code();

	CString err_code = sCH__ERROR_TEST__ERROR_CODE->Get__STRING();
	_Check__ERROR_CODE(err_code);

	// ...
	CString err_msg;

	while(mMNG__ERR_CODE.Get__Error_Code(err_code,err_msg) > 0)
	{
		int i_error = atoi(err_code);
		if(i_error == 0)		continue;

		// ...
		int alm_id = ALID__ERROR_CODE;
		CString alm_msg;
		CString alm_bff;
		CString r_act;

		alm_msg.Format("Control_Mode : %s \n", "Call__CHECK_ERROR_CODE()");

		alm_bff.Format("Error_Code : %s \n", err_code);
		alm_msg += alm_bff;
		alm_bff.Format("Error_Message \n");
		alm_msg += alm_bff;
		alm_msg += "  * ";
		alm_msg += err_msg;

		// ...
		{
			CString log_msg;

			log_msg.Format("Alarm Post : %1d \n", alm_id);
			log_msg += alm_msg;

			Fnc__APP_LOG(log_msg);
		}

		p_alarm->Popup__ALARM_With_MESSAGE(alm_id,alm_msg,r_act);			

		if(r_act.CompareNoCase(ACT__RETRY) == 0)
		{
			CString log_msg = "Alarm Selection <- Retry";
			Fnc__APP_LOG(log_msg);

			goto LOOP_RETRY;
		}
		if(r_act.CompareNoCase(ACT__ABORT) == 0)
		{
			return -1;
		}

		if(r_act.CompareNoCase(ACT__IGNORE) == 0)
		{
			// ...
		}
	}

	return 1;
}
