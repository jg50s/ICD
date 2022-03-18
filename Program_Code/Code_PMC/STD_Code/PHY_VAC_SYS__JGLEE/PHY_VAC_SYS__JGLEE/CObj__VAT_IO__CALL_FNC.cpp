#include "StdAfx.h"
#include "CObj__VAT_IO.h"

#include "CCommon_Utility.h"


#define CTRL_MODE__NORMAL			0
#define CTRL_MODE__CLOSE			1
#define CTRL_MODE__OPEN				2
#define CTRL_MODE__HOLD				3
#define CTRL_MODE__RESET			4


// ...
int CObj__VAT_IO
::Call__INIT(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm)
{
	sCH__OBJ_STATUS->Set__DATA("STANDBY");

	return OBJ_AVAILABLE;
}

int CObj__VAT_IO
::Call__CLOSE(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm)
{
	if(iDATA__VAT_CTRL_TYPE == _VAT_CTRL_TYPE__OBJ)
	{
		return pOBJ_CTRL__VAT->Call__OBJECT(sVAT_CMMD__CLOSE);
	}
	else
	{
		dEXT_CH__DO_APC_CTRL_MODE->Set__DATA(STR__CLOSE);

		if(iActive__SIM_MODE > 0)
		{
			aEXT_CH__AI_APC_POSITION->Set__DATA("0.0");

			if(bActive__DI_APC_VLV_CLOSE)		dEXT_CH__DI_APC_VLV_CLOSE->Set__DATA(STR__ON);
			if(bActive__DI_APC_VLV_OPEN)		dEXT_CH__DI_APC_VLV_OPEN->Set__DATA(STR__OFF);
			if(bActive__DI_APC_VLV_STATE)		dEXT_CH__DI_APC_VLV_STATE->Set__DATA(STR__CLOSE);
		}
	}

	return 1;
}
int CObj__VAT_IO
::Call__OPEN(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm)
{
	if(iDATA__VAT_CTRL_TYPE == _VAT_CTRL_TYPE__OBJ)
	{
		return pOBJ_CTRL__VAT->Call__OBJECT(sVAT_CMMD__OPEN);
	}
	else
	{
		dEXT_CH__DO_APC_CTRL_MODE->Set__DATA(STR__OPEN);

		if(iActive__SIM_MODE > 0)
		{
			aEXT_CH__AI_APC_POSITION->Set__DATA("100.0");

			if(bActive__DI_APC_VLV_CLOSE)		dEXT_CH__DI_APC_VLV_CLOSE->Set__DATA(STR__OFF);
			if(bActive__DI_APC_VLV_OPEN)		dEXT_CH__DI_APC_VLV_OPEN->Set__DATA(STR__ON);
			if(bActive__DI_APC_VLV_STATE)		dEXT_CH__DI_APC_VLV_STATE->Set__DATA(STR__OPEN);
		}
	}

	return 1;
}

int CObj__VAT_IO
::Call__POSITION(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm)
{
	double set_pos = aCH__PARA_POSITION->Get__VALUE();

	return Fnc__POSITION(p_alarm, set_pos);
}
int CObj__VAT_IO
::Fnc__POSITION(CII_OBJECT__ALARM *p_alarm, const double set_pos)
{
	CString ch_pos;
	ch_pos.Format("%.1f", set_pos);

	if(iDATA__VAT_CTRL_TYPE == _VAT_CTRL_TYPE__OBJ)
	{
		sCH__MON_SET_POSITION->Set__DATA(ch_pos);
		aEXT_CH__VAT__PARA_POSITION_PER->Set__DATA(ch_pos);

		if(iActive__SIM_MODE > 0)
		{
			aEXT_CH__VAT__CUR_POSITION_PER->Set__DATA(ch_pos);
		}

		return pOBJ_CTRL__VAT->Call__OBJECT(sVAT_CMMD__POSITION);
	}
	else
	{
		sCH__MON_SET_POSITION->Set__DATA(ch_pos);
		aEXT_CH__AO_APC_SETPOINT_DATA->Set__DATA(ch_pos);

		dEXT_CH__DO_APC_SETPOINT_TYPE->Set__DATA(STR__POSITION);
		dEXT_CH__DO_APC_CTRL_MODE->Set__DATA(STR__CONTROL);

		if(iActive__SIM_MODE > 0)
		{
			aEXT_CH__AI_APC_POSITION->Set__DATA(ch_pos);

			if(bActive__DI_APC_VLV_CLOSE)		dEXT_CH__DI_APC_VLV_CLOSE->Set__DATA(STR__OFF);
			if(bActive__DI_APC_VLV_OPEN)		dEXT_CH__DI_APC_VLV_OPEN->Set__DATA(STR__OFF);
		}
	}

	return 1;
}

int CObj__VAT_IO
::Call__PRESSURE(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm)
{
	double set_pressure = aCH__PARA_PRESSURE->Get__VALUE();

	return Fnc__PRESSURE(p_variable,p_alarm, set_pressure);
}
int CObj__VAT_IO
::Fnc__PRESSURE(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm, const double set_pressure)
{
	double para__hold_sec = aCH__PARA_HOLD_SEC->Get__VALUE();

	CString ch__hold_sec;
	ch__hold_sec.Format("%.1f", para__hold_sec);
	sCH__MON_SET_HOLD_SEC->Set__DATA(ch__hold_sec);

	if(para__hold_sec > 0.1)
	{
		SCX__ASYNC_TIMER_CTRL x_timer_ctrl;
		x_timer_ctrl->START__COUNT_UP(9999);

		double para__hold_pos = aCH__PARA_POSITION->Get__VALUE();

		if(iDATA__VAT_CTRL_TYPE == _VAT_CTRL_TYPE__OBJ)
		{
			CString ch_pos;

			ch_pos.Format("%.1f", para__hold_pos);
			sCH__MON_SET_POSITION->Set__DATA(ch_pos);
			aEXT_CH__VAT__PARA_POSITION_PER->Set__DATA(ch_pos);

			pOBJ_CTRL__VAT->Run__OBJECT(sVAT_CMMD__POSITION);
	
			if(iActive__SIM_MODE > 0)
			{
				aEXT_CH__VAT__CUR_POSITION_PER->Set__DATA(ch_pos);
			}
		}
		else
		{
			CString ch_pos;

			ch_pos.Format("%.1f", para__hold_pos);
			aEXT_CH__AO_APC_SETPOINT_DATA->Set__DATA(ch_pos);

			dEXT_CH__DO_APC_SETPOINT_TYPE->Set__DATA(STR__POSITION);
			dEXT_CH__DO_APC_CTRL_MODE->Set__DATA(STR__CONTROL);

			if(iActive__SIM_MODE > 0)
			{
				aEXT_CH__AI_APC_POSITION->Set__DATA(ch_pos);
			}
		}

		while(1)
		{
			Sleep(1);

			if(p_variable->Check__CTRL_ABORT() > 0)							return -11;
			if(x_timer_ctrl->Get__CURRENT_TIME() >= para__hold_sec)			break;
		}
	}

	//
	CString ch_pressure;
	ch_pressure.Format("%.3f", set_pressure);

	if(iDATA__VAT_CTRL_TYPE == _VAT_CTRL_TYPE__OBJ)
	{
		sCH__MON_SET_PRESSURE->Set__DATA(ch_pressure);
		aEXT_CH__VAT__PARA_PRESSURE_TORR->Set__DATA(ch_pressure);

		if(iActive__SIM_MODE > 0)
		{
			sEXT_CH__SIM_PRESSURE_TORR->Set__DATA(ch_pressure);
			aEXT_CH__VAT__CUR_PRESSURE_TORR->Set__DATA(ch_pressure);
		}

		return pOBJ_CTRL__VAT->Call__OBJECT(sVAT_CMMD__PRESSURE);
	}
	else
	{
		sCH__MON_SET_PRESSURE->Set__DATA(ch_pressure);
		aEXT_CH__AO_APC_SETPOINT_DATA->Set__DATA(ch_pressure);

		dEXT_CH__DO_APC_SETPOINT_TYPE->Set__DATA(STR__PRESSURE);
		dEXT_CH__DO_APC_CTRL_MODE->Set__DATA(STR__CONTROL);

		if(iActive__SIM_MODE > 0)
		{
			sEXT_CH__SIM_PRESSURE_TORR->Set__DATA(ch_pressure);
			aEXT_CH__AI_APC_PRESSURE->Set__DATA(ch_pressure);

			if(bActive__DI_APC_VLV_CLOSE)		dEXT_CH__DI_APC_VLV_CLOSE->Set__DATA(STR__OFF);
			if(bActive__DI_APC_VLV_OPEN)		dEXT_CH__DI_APC_VLV_OPEN->Set__DATA(STR__OFF);
		}
	}

	return 1;
}
