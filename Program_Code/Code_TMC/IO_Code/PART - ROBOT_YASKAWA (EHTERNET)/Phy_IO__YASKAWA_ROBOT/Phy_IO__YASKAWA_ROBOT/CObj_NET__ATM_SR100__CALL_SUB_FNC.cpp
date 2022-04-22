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
	int slot_id = atoi(stn_slot);

	/*
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
	*/
	// ...
	CString drv__stn_name = "XXX";

	if(stn_name.CompareNoCase(STR__AL1) == 0)
	{
		// drv__stn_name = "P01";
		drv__stn_name = dCH__CFG_AL1_STN_NUM->Get__STRING();
	}
	else if(lp_i >= 0)				
	{
		// drv__stn_name.Format("C%02d", lp_i+1);
		drv__stn_name = dCH__CFG_LPx_STN_NUM[lp_i]->Get__STRING();
	}
	else if(ll_i >= 0)
	{
		// drv__stn_name.Format("C%02d", ll_i + 4);
		if(bActive__LLx_MULTI_DOOR_VALVE)
		{
			if(slot_id == 1)		
				drv__stn_name = dCH__CFG_LLx_1_STN_NUM[ll_i]->Get__STRING();
			else if(slot_id == 2)
				drv__stn_name = dCH__CFG_LLx_2_STN_NUM[ll_i]->Get__STRING();
		}
		else
		{
			drv__stn_name = dCH__CFG_LLx_STN_NUM[ll_i]->Get__STRING();
		}
	}
	else if(stn_name.CompareNoCase(STR__BUFF1) == 0)
	{
		// drv__stn_name.Format("C%02d", 8);
		drv__stn_name = dCH__CFG_ST1_STN_NUM->Get__STRING();
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

	int r_act = doCH__COMMAND->Set__DATA(_CMMD__Pick);

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

	if(r_act < 0)
	{
		CString ch_data = diCH__RB_STS_MANUAL->Get__STRING();
		if(ch_data.CompareNoCase(STR__Error) == 0)			return r_act;
	}

	// Wafer Check ...
	{
		double cfg_sec = 2.0;

		if(iSim_Flag > 0)
		{
			sCH__MON_SYS_STS__UNIT_STATUS->Set__DATA(STR__READY);
			sCH__MON_SYS_STS__ERROR_STATUS->Set__DATA(STR__OFF);
		}

		int r_state = sCH__MON_SYS_STS__UNIT_STATUS->When__DATA(STR__READY, cfg_sec);
		if(r_state <= 0)
		{
			r_act = -101;
		}

		if(sCH__MON_SYS_STS__ERROR_STATUS->Check__DATA(STR__OFF) < 0)
		{
			r_act = -201;
		}

		if(arm_type.CompareNoCase(ARM_A) == 0)
		{
			if(iSim_Flag > 0)
			{
				sCH__MON_SYS_STS__WAFER_PRESENCE_STS1->Set__DATA(STR__ON);
			}

			if(sCH__MON_SYS_STS__WAFER_PRESENCE_STS1->Check__DATA(STR__ON) > 0)
			{
				dCH__MON__ARM_A_MATERIAL_STATUS->Set__DATA(STR__EXIST);
			}
			else if(sCH__MON_SYS_STS__WAFER_PRESENCE_STS1->Check__DATA(STR__OFF) > 0)
			{
				dCH__MON__ARM_A_MATERIAL_STATUS->Set__DATA(STR__NONE);
			}
		}
		else if(arm_type.CompareNoCase(ARM_B) == 0)
		{
			if(iSim_Flag > 0)
			{
				sCH__MON_SYS_STS__WAFER_PRESENCE_STS2->Set__DATA(STR__ON);
			}

			if(sCH__MON_SYS_STS__WAFER_PRESENCE_STS2->Check__DATA(STR__ON) > 0)
			{
				dCH__MON__ARM_B_MATERIAL_STATUS->Set__DATA(STR__EXIST);
			}
			else if(sCH__MON_SYS_STS__WAFER_PRESENCE_STS2->Check__DATA(STR__OFF) > 0)
			{
				dCH__MON__ARM_B_MATERIAL_STATUS->Set__DATA(STR__NONE);
			}
		}
	}

	return r_act;
}
int  CObj_NET__ATM_SR100
::Seq__ROBOT_PLACE(CII_OBJECT__VARIABLE* p_variable,
				   CII_OBJECT__ALARM* p_alarm,
				   const CString& arm_type,
				   const CString& stn_name,
				   const CString& stn_slot)
{
LOOP_RETRY:

	int r_act = doCH__COMMAND->Set__DATA(_CMMD__Place);

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

	if(r_act < 0)
	{
		CString ch_data = diCH__RB_STS_MANUAL->Get__STRING();
		if(ch_data.CompareNoCase(STR__Error) == 0)			return r_act;
	}

	// Wafer Check ...
	{
		double cfg_sec = 2.0;

		if(iSim_Flag > 0)
		{
			sCH__MON_SYS_STS__UNIT_STATUS->Set__DATA(STR__READY);
			sCH__MON_SYS_STS__ERROR_STATUS->Set__DATA(STR__OFF);
		}

		int r_state = sCH__MON_SYS_STS__UNIT_STATUS->When__DATA(STR__READY, cfg_sec);
		if(r_state <= 0)
		{
			r_act = -101;
		}

		if(sCH__MON_SYS_STS__ERROR_STATUS->Check__DATA(STR__OFF) < 0)
		{
			r_act = -201;
		}

		if(arm_type.CompareNoCase(ARM_A) == 0)
		{
			if(iSim_Flag > 0)
			{
				sCH__MON_SYS_STS__WAFER_PRESENCE_STS1->Set__DATA(STR__OFF);
			}

			if(sCH__MON_SYS_STS__WAFER_PRESENCE_STS1->Check__DATA(STR__ON) > 0)
			{
				dCH__MON__ARM_A_MATERIAL_STATUS->Set__DATA(STR__EXIST);
			}
			else if(sCH__MON_SYS_STS__WAFER_PRESENCE_STS1->Check__DATA(STR__OFF) > 0)
			{
				dCH__MON__ARM_A_MATERIAL_STATUS->Set__DATA(STR__NONE);
			}
		}
		else if(arm_type.CompareNoCase(ARM_B) == 0)
		{
			if(iSim_Flag > 0)
			{
				sCH__MON_SYS_STS__WAFER_PRESENCE_STS2->Set__DATA(STR__OFF);
			}

			if(sCH__MON_SYS_STS__WAFER_PRESENCE_STS2->Check__DATA(STR__ON) > 0)
			{
				dCH__MON__ARM_B_MATERIAL_STATUS->Set__DATA(STR__EXIST);
			}
			else if(sCH__MON_SYS_STS__WAFER_PRESENCE_STS2->Check__DATA(STR__OFF) > 0)
			{
				dCH__MON__ARM_B_MATERIAL_STATUS->Set__DATA(STR__NONE);
			}
		}
	}

	return r_act;
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
