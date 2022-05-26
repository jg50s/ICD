#include "StdAfx.h"
#include "CObj__PMC_OPR.h"

#include "CObj__PMC_OPR__ALID.h"
#include "CObj__PMC_OPR__DEF.h"


// ...
int CObj__PMC_OPR
::Call__INIT(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM* p_alarm)
{
	DECLARE__EXT_CTRL(p_variable);

	if(sEXT_CH__SYSTEM_SETUP_REQ->Check__DATA(STR__YES) > 0)
	{
		CString box_title;
		CString box_msg;
		CStringArray l_act;
		CString r_act;

		box_title = "SETUP 모드에서 INIT 모드로 전환합니다 !";

		box_msg  = "현재 SETUP 모드에서 INIT로 전환하는 것이 맞나요? \n";
		box_msg += "INIT 전환되면 I/O 설정들이 자동으로 변경됩니다. \n";
		box_msg += "INIT로 전환되어도 문제 없는지? \n";
		box_msg += "모든 I/O의 현재 설정을 확인 바랍니다.";

		l_act.RemoveAll();
		l_act.Add("ABORT");
		l_act.Add("GOTO_INIT");

		p_alarm->Popup__MESSAGE_BOX(box_title,box_msg,l_act,r_act);

		if(r_act.CompareNoCase("ABORT") == 0)
		{
			return -1;
		}
	}

	if(iSIM_FLAG > 0)
	{
		if(dEXT_CH__CFG_TRANSFER_MODE->Check__DATA("ATM") > 0)
		{
			sEXT_CH__CHM_ATM_SNS->Set__DATA("ON");
			sEXT_CH__CHM_VAC_SNS->Set__DATA("OFF");
			sEXT_CH__CHM_PRESSURE_VALUE->Set__DATA("790");
		}
		else
		{
			sEXT_CH__CHM_ATM_SNS->Set__DATA("OFF");
			sEXT_CH__CHM_VAC_SNS->Set__DATA("ON");
			sEXT_CH__CHM_PRESSURE_VALUE->Set__DATA("0.001");
		}
	}

	// ...
	int r_flag = p_ext_mode_ctrl->Call__FNC_MODE(sEXT_MODE__INIT);
	if(r_flag < 0)
	{
		return -11;
	}

	if(dEXT_CH__CFG_TRANSFER_MODE->Check__DATA("ATM") > 0)
	{
		if(p_ext_mode_ctrl->Call__FNC_MODE(sEXT_MODE__VENT) < 0)
		{
			return -21;
		}
	}
	else
	{
		if(p_ext_mode_ctrl->Call__FNC_MODE(sEXT_MODE__PUMP) < 0)
		{
			return -21;
		}
	}

	// ...
	{
		sEXT_CH__SYSTEM_SETUP_REQ->Set__DATA("");
		xCH__OBJ_STATUS->Set__DATA(STR__STANDBY);
	}
	return 1;	
}
int CObj__PMC_OPR
::Call__TRANSFER_INIT(CII_OBJECT__VARIABLE *p_variable)
{
	return -1;	
}

int CObj__PMC_OPR
::Call__MAINT(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM* p_alarm)
{
	DECLARE__EXT_CTRL(p_variable);

	if(sEXT_CH__SYSTEM_SETUP_REQ->Check__DATA(STR__YES) > 0)
	{
		CString box_title;
		CString box_msg;
		CStringArray l_act;
		CString r_act;

		box_title = "SETUP 모드에서 MAINT 모드로 전환합니다 !";

		box_msg  = "현재 SETUP 모드에서 MAINT로 전환하는 것이 맞나요? \n";
		box_msg += "MAINT 전환되면 I/O 설정들이 자동으로 변경됩니다. \n";
		box_msg += "MAINT로 전환되어도 문제 없는지? \n";
		box_msg += "모든 I/O의 현재 설정을 확인 바랍니다.";

		l_act.RemoveAll();
		l_act.Add("ABORT");
		l_act.Add("GOTO_MAINT");

		p_alarm->Popup__MESSAGE_BOX(box_title,box_msg,l_act,r_act);
	
		if(r_act.CompareNoCase("ABORT") == 0)
		{
			return -1;
		}
	}

	int r_flag = p_ext_mode_ctrl->Call__FNC_MODE(sEXT_MODE__MAINT);

	if(r_flag > 0)
	{
		sEXT_CH__SYSTEM_SETUP_REQ->Set__DATA("");
		xCH__OBJ_STATUS->Set__DATA(STR__MAINTMODE);
	}
	return r_flag;	
}
int CObj__PMC_OPR
::Call__SETUP(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM* p_alarm)
{
	DECLARE__EXT_CTRL(p_variable);

	// ...
	{	
		sEXT_CH__SYSTEM_SETUP_REQ->Set__DATA(STR__YES);
		xCH__OBJ_STATUS->Set__DATA(STR__MAINTMODE);
	}
	return 1;	
}

// ...
int CObj__PMC_OPR
::Call__PUMP(CII_OBJECT__VARIABLE *p_variable)
{
	DECLARE__EXT_CTRL(p_variable);

	return p_ext_mode_ctrl->Call__FNC_MODE(sEXT_MODE__PUMP);
}
int CObj__PMC_OPR
::Call__VENT(CII_OBJECT__VARIABLE *p_variable)
{
	DECLARE__EXT_CTRL(p_variable);

	return p_ext_mode_ctrl->Call__FNC_MODE(sEXT_MODE__VENT);
}

int CObj__PMC_OPR
::Call__LEAK_CHECK(CII_OBJECT__VARIABLE *p_variable)
{
	DECLARE__EXT_CTRL(p_variable);

	return p_ext_mode_ctrl->Call__FNC_MODE(sEXT_MODE__LEAK_CHECK);
}
int CObj__PMC_OPR
::Call__AUTO_PM(CII_OBJECT__VARIABLE *p_variable)
{
	if(bActive__OBJ_CTRL__AUTO_PM)
	{
		return pOBJ_CTRL__AUTO_PM->Call__OBJECT(sLINK_MODE__AUTO_PM);
	}
	return -1;
}
int CObj__PMC_OPR
::Call__PURGE(CII_OBJECT__VARIABLE *p_variable)
{
	DECLARE__EXT_CTRL(p_variable);

	return p_ext_mode_ctrl->Call__FNC_MODE(sEXT_MODE__PURGE);
}


// ...
int CObj__PMC_OPR
::Call__PRO_READY(CII_OBJECT__VARIABLE *p_variable)
{
	DECLARE__EXT_CTRL(p_variable);

	if(bActive__OBJ_CTRL__SHUTTER)
	{
		pOBJ_CTRL__SHUTTER->Run__OBJECT(sLINK_MODE__SHUTTER__CLOSE);
	}
	if(bActive__OBJ_CTRL__LIFT_PIN)
	{
		pOBJ_CTRL__LIFT_PIN->Run__OBJECT(sLINK_MODE__LIFT_PIN__PROCESS_READY);
	}

	if(bActive__OBJ_CTRL__SHUTTER)
	{
		if(pOBJ_CTRL__SHUTTER->When__OBJECT() < 0)			return -11;
	}
	if(bActive__OBJ_CTRL__LIFT_PIN)
	{
		if(pOBJ_CTRL__LIFT_PIN->When__OBJECT() < 0)			return -21;
	}

	return p_ext_mode_ctrl->Call__FNC_MODE(sEXT_MODE__PRO_READY);
}

int CObj__PMC_OPR
::Call__PRO_START(CII_OBJECT__VARIABLE *p_variable)
{
	DECLARE__EXT_CTRL(p_variable);

	// ...
	{
		dEXT_CH__CHM_PRC_STS->Set__DATA("PROCESSING");
	}

	/*
	// ...
	{
		CString ch_data;

		sCH__PARA_PROCESS_TIME_SEC->Get__DATA(ch_data);
		sEXT_CH__CHM_PRC_TOTAL_TIME_TO_CTC->Set__DATA(ch_data);
		double cfg_sec = atoi(ch_data);

		sEXT_CH__CHM_PRC_CHANGE_TIME_TO_CTC->Set__DATA("");

		SCX__TIMER_CTRL x_timer;
		x_timer->REGISTER__ABORT_OBJECT(sObject_Name);
		x_timer->REGISTER__COUNT_CHANNEL(sCH__APP_PROCESS_TIME_COUNT->Get__CHANNEL_NAME());

		x_timer->WAIT(cfg_sec);
	}
	*/

	int r_flag = p_ext_mode_ctrl->Call__FNC_MODE(sEXT_MODE__PRO_START);

	// ...
	{
		sEXT_CH__CHM_PRC_TOTAL_TIME_TO_CTC->Set__DATA("");
		sEXT_CH__CHM_PRC_CHANGE_TIME_TO_CTC->Set__DATA("");

		dEXT_CH__CHM_PRC_STS->Set__DATA("IDLE");
	}

	return r_flag;
}

int CObj__PMC_OPR
::Call__CLN_READY(CII_OBJECT__VARIABLE *p_variable)
{
	if(bActive__OBJ_CTRL__SHUTTER)
	{
		pOBJ_CTRL__SHUTTER->Run__OBJECT(sLINK_MODE__SHUTTER__CLOSE);
	}
	if(bActive__OBJ_CTRL__LIFT_PIN)
	{
		pOBJ_CTRL__LIFT_PIN->Run__OBJECT(sLINK_MODE__LIFT_PIN__PROCESS_READY);
	}

	if(bActive__OBJ_CTRL__SHUTTER)
	{
		if(pOBJ_CTRL__SHUTTER->When__OBJECT() < 0)			return -11;
	}
	if(bActive__OBJ_CTRL__LIFT_PIN)
	{
		if(pOBJ_CTRL__LIFT_PIN->When__OBJECT() < 0)			return -21;
	}

	return 1;
}

int CObj__PMC_OPR
::Call__CLN_START(CII_OBJECT__VARIABLE *p_variable)
{
	CString ch_data;
	double cfg_sec = 0.0;

	// ...
	{
		dEXT_CH__CHM_PRC_STS->Set__DATA("PROCESSING");

		sCH__PARA_PROCESS_TIME_SEC->Get__DATA(ch_data);
		sEXT_CH__CHM_PRC_TOTAL_TIME_TO_CTC->Set__DATA(ch_data);
		cfg_sec = atoi(ch_data);

		sEXT_CH__CHM_PRC_CHANGE_TIME_TO_CTC->Set__DATA("");
	}

	// ...
	{
		SCX__TIMER_CTRL x_timer;
		x_timer->REGISTER__ABORT_OBJECT(sObject_Name);
		x_timer->REGISTER__COUNT_CHANNEL(sCH__APP_PROCESS_TIME_COUNT->Get__CHANNEL_NAME());

		x_timer->WAIT(cfg_sec);
	}

	// ...
	{
		sEXT_CH__CHM_PRC_TOTAL_TIME_TO_CTC->Set__DATA("");
		sEXT_CH__CHM_PRC_CHANGE_TIME_TO_CTC->Set__DATA("");

		dEXT_CH__CHM_PRC_STS->Set__DATA("IDLE");
	}
	return 1;
}

int CObj__PMC_OPR
::Call__MNT_READY(CII_OBJECT__VARIABLE *p_variable)
{
	return 1;
}

int CObj__PMC_OPR
::Call__MNT_START(CII_OBJECT__VARIABLE *p_variable)
{
	return 1;
}

int CObj__PMC_OPR
::Call__JOB_START_READY(CII_OBJECT__VARIABLE *p_variable)
{
	return 1;
}

int CObj__PMC_OPR
::Call__JOB_END_READY(CII_OBJECT__VARIABLE *p_variable)
{
	return 1;
}

