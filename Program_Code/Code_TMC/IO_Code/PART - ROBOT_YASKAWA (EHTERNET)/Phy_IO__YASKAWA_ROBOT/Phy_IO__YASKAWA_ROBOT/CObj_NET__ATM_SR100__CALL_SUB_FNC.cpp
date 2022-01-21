#include "StdAfx.h"
#include "CObj_NET__ATM_SR100.h"
#include "CObj_NET__ATM_SR100__DEF.h"
#include "CObj_NET__ATM_SR100__ALID.h"

#include "math.h"
#include "CCommon_DEF.h"
#include "Macro_Function.h"


//------------------------------------------------------------------------------------
int  CObj_NET__ATM_SR100
::Is__LOCAL(CII_OBJECT__ALARM* p_alarm)
{

	return 1;
}
int  CObj_NET__ATM_SR100
::Is__OFFLINE(CII_OBJECT__ALARM* p_alarm)
{
LOOP_RETRY:

	if(m_nCommState == OFFLINE)
	{
		int alarm_id = ALID__OFFLINE_ALARM;
		CString r_act;

		p_alarm->Popup__ALARM(alarm_id,r_act);

		if(r_act.CompareNoCase("RETRY") == 0)
		{
			goto LOOP_RETRY;
		}
		return -1;
	}

	return 1;
}

CString CObj_NET__ATM_SR100
::_Get__TRG_STN()
{
	CString stn_name = dCH__OTR_IN_PARA__STN_NAME->Get__STRING();
	CString stn_slot = dCH__OTR_IN_PARA__STN_SLOT->Get__STRING();

	return _Get__TRG_STN(stn_name, stn_slot);
}
CString CObj_NET__ATM_SR100
::_Get__TRG_STN(const CString& stn_name, const CString& stn_slot)
{
	int ll_i = Macro__CHECK_LLx_INDEX(stn_name);
	int lp_i = Macro__CHECK_LPx_INDEX(stn_name);

	// ...
	CString drv__stn_name = "XXX";

	if(stn_name.CompareNoCase(STR__AL1) == 0)
	{
		drv__stn_name = "P01";
	}
	else if(lp_i >= 0)				
	{
		drv__stn_name.Format("C%02d", lp_i+1);
	}
	else if(ll_i >= 0)
	{
		if(bActive__LLx_MULTI_DOOR_VALVE)
		{
			int id = atoi(stn_slot);

			drv__stn_name.Format("C%02d", (ll_i * 2) + id + 4);			
		}
		else
		{
			drv__stn_name.Format("C%02d", ll_i + 5);
		}
	}
	else if(stn_name.CompareNoCase(STR__BUFF1) == 0)
	{
		drv__stn_name.Format("C%02d", 4);
	}

	return drv__stn_name;
}
CString CObj_NET__ATM_SR100
::_Get__TRG_SLOT()
{
	CString para__stn_slot;
	dCH__OTR_IN_PARA__STN_SLOT->Get__DATA(para__stn_slot);

	int i_slot = atoi(para__stn_slot);
	para__stn_slot.Format("%02d", i_slot);
	return para__stn_slot;
}
CString CObj_NET__ATM_SR100
::_Get__ARM_ID()
{
	CString para__arm_type;
	dCH__OTR_IN_PARA__ARM_TYPE->Get__DATA(para__arm_type);

	if(para__arm_type.CompareNoCase("A") == 0)		return "1";
	if(para__arm_type.CompareNoCase("B") == 0)		return "2";

	return "?";
}
int CObj_NET__ATM_SR100
::_Check__ARM_WAFER()
{
	CString para__arm_type;
	dCH__OTR_IN_PARA__ARM_TYPE->Get__DATA(para__arm_type);

	if(para__arm_type.CompareNoCase("A") == 0)
	{
		if(dCH__MON__ARM_A_MATERIAL_STATUS->Check__DATA(STR__NONE) < 0)
			return 1;
	}
	if(para__arm_type.CompareNoCase("B") == 0)
	{
		if(dCH__MON__ARM_B_MATERIAL_STATUS->Check__DATA(STR__NONE) < 0)
			return 1;
	}

	return -1;
}
CString CObj_NET__ATM_SR100
::_Get__ARM_MODE()
{
	return "A";

	// return "L";
	// return "R";
}


//------------------------------------------------------------------------------------
int  CObj_NET__ATM_SR100
::Seq__ROBOT_PICK(CII_OBJECT__VARIABLE* p_variable,
				  CII_OBJECT__ALARM* p_alarm,
				  const CString& arm_type,
				  const CString& stn_name,
				  const CString& stn_slot)
{
LOOP_RETRY:

	doCH__COMMAND->Set__DATA(_CMMD__Pick);

	// ...
	{
		int r_flag = Fnc__ONLINE_CHECK(p_alarm,1);
			 
			 if(r_flag == 0)		goto LOOP_RETRY;
		else if(r_flag <  0)		return -1;			

		if(p_variable->Check__CTRL_ABORT() > 0)
		{
			return -1;
		}
	}

	/*
	int ll_i = Macro__CHECK_LLx_INDEX(stn_name);
	if(ll_i >= 0)
	{
		CString log_msg;

		log_msg.Format("%s - RNE Sensor Check ...", stn_name);
		Fnc__APP_LOG(log_msg);
		
		int r_flag = dEXT_IO_CH__ARM_LLx_RNE_SNS[ll_i]->When__DATA("None", 3.0);
		if(r_flag <= 0)
		{
			log_msg.Format("RNE Sensor Result : :%d", r_flag);
			Fnc__APP_LOG(log_msg);
			return -1;
		}
	}
	*/

	return 1;
}
int  CObj_NET__ATM_SR100
::Seq__ROBOT_PLACE(CII_OBJECT__VARIABLE* p_variable,
				   CII_OBJECT__ALARM* p_alarm,
				   const CString& arm_type,
				   const CString& stn_name,
				   const CString& stn_slot)
{
LOOP_RETRY:

	doCH__COMMAND->Set__DATA(_CMMD__Place);

	// ...
	{
		int r_flag = Fnc__ONLINE_CHECK(p_alarm,1);

			 if(r_flag == 0)		goto LOOP_RETRY;
		else if(r_flag  < 0)		return -1;				// abort

		if(p_variable->Check__CTRL_ABORT() > 0)
		{
			return -1;
		}
	}

	return 1;
}
int  CObj_NET__ATM_SR100
::Seq__ROBOT_ROTATE(CII_OBJECT__VARIABLE* p_variable,
				    CII_OBJECT__ALARM* p_alarm,
				    const CString& arm_type,
				    const CString& stn_name,
				    const CString& stn_slot)
{
LOOP_RETRY:

	// ...
	{
		int r_flag = Fnc__ONLINE_CHECK(p_alarm,0);

			 if(r_flag == 0)		goto LOOP_RETRY;
		else if(r_flag  < 0)		return -1;				// abort

		if(p_variable->Check__CTRL_ABORT() > 0)
		{
			return -1;
		}
	}

	doCH__COMMAND->Set__DATA(_CMMD__Goto);
	Sleep(1000);  // Test !!!

	// ...
	{
		int status = Fnc__ONLINE_CHECK(p_alarm,1);

			 if(status == 0)		goto LOOP_RETRY;
		else if(status <  0)		return -1;				// abort

		if(p_variable->Check__CTRL_ABORT() > 0)
		{
			return -1;
		}
	}

	return 1;
}


//------------------------------------------------------------------------------------
int  CObj_NET__ATM_SR100
::Fnc__IS_COMM_ONLINE()
{
	if(m_nCommState == ONLINE)
	{
		return 1;
	}
	return -1;
}
int  CObj_NET__ATM_SR100
::Fnc__ONLINE_CHECK(CII_OBJECT__ALARM* p_alarm,
				    const int alarm_check)
{
	SCX__TIMER_CTRL x_timer_ctrl;
	x_timer_ctrl->REGISTER__ABORT_OBJECT(sObject_Name);

	if(iSim_Flag > 0)     
	{
		m_nCommState = ONLINE;
		
		sCH__INR__ERROR_ID->Set__DATA("0");
	}

	if(Fnc__IS_COMM_ONLINE() > 0)
	{
		return 1;
	} 

	// Offline ...
	{
		int alarm_id = ALID__OFFLINE_ALARM;

		CString err_msg;
		CString r_act;

		err_msg  = "1. Check the Serial cable\n";
		err_msg += "2. Check the Robot power";

		p_alarm->Popup__ALARM_With_MESSAGE(alarm_id,err_msg,r_act);

			 if(r_act.CompareNoCase("ABORT") == 0)		return -1;
		else if(r_act.CompareNoCase("RETRY") == 0)		return 0;
	}
    return -1;
}
