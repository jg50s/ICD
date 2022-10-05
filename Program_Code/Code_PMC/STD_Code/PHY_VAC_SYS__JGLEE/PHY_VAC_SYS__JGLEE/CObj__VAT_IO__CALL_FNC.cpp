#include "StdAfx.h"
#include "CObj__VAT_IO.h"
#include "CObj__VAT_IO__DEF.h"

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
		int r_flag = pOBJ_CTRL__VAT->Call__OBJECT(sVAT_CMMD__CLOSE);
		if(r_flag < 0)			return r_flag;
	}
	else if(iDATA__VAT_CTRL_TYPE == _VAT_CTRL_TYPE__HEXA)
	{
		sEXT_CH__SO_APC_CTRL_MODE->Set__DATA("01");

		if(iActive__SIM_MODE > 0)
		{
			sEXT_CH__SI_APC_POSITION->Set__DATA("00 00");
		}
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

	while(1)
	{
		if(p_variable->Check__CTRL_ABORT() > 0)
		{
			return -101;
		}

		CString ch_data = sCH__MON_POSITION->Get__STRING();
		double cur_pos = atof(ch_data);
		if(cur_pos < 0.1)		break;

		Sleep(10);
	}
	return 1;
}
int CObj__VAT_IO
::Call__OPEN(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm)
{
	if(iDATA__VAT_CTRL_TYPE == _VAT_CTRL_TYPE__OBJ)
	{
		int r_flag = pOBJ_CTRL__VAT->Call__OBJECT(sVAT_CMMD__OPEN);
		if(r_flag < 0)			return r_flag;
	}
	else if(iDATA__VAT_CTRL_TYPE == _VAT_CTRL_TYPE__HEXA)
	{
		sEXT_CH__SO_APC_CTRL_MODE->Set__DATA("02");

		if(iActive__SIM_MODE > 0)
		{
			UNION_2_BYTE__UINT m_pos;
			m_pos.uiDATA = (unsigned short int) iLINK_HEXA__MAX_VALUE;
	
			CString str_hexa;
			str_hexa.Format("%02X %02X", 0x0ff & m_pos.cBYTE[0], 0x0ff & m_pos.cBYTE[1]);

			sEXT_CH__SI_APC_POSITION->Set__DATA(str_hexa);
		}
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

	while(1)
	{
		if(p_variable->Check__CTRL_ABORT() > 0)
		{
			return -101;
		}

		CString ch_data = sCH__MON_POSITION->Get__STRING();
		double cur_pos = atof(ch_data);
		if(cur_pos > 99.0)		break;

		Sleep(10);
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
	else if(iDATA__VAT_CTRL_TYPE == _VAT_CTRL_TYPE__HEXA)
	{
		int set_hexa = (int) (set_pos * iLINK_HEXA__MAX_VALUE / 100.0);
	
		UNION_2_BYTE__UINT x_data;
		x_data.uiDATA = 0x0ffff & set_hexa;

		CString str_hexa;
		str_hexa.Format("%02X %02X", 0x0ff & x_data.cBYTE[0], 0x0ff & x_data.cBYTE[1]);

		sCH__MON_SET_POSITION->Set__DATA(ch_pos);
		sEXT_CH__SO_APC_SETPOINT_DATA->Set__DATA(str_hexa);

		sEXT_CH__SO_APC_SETPOINT_TYPE->Set__DATA("01");
		sEXT_CH__SO_APC_CTRL_MODE->Set__DATA("00");

		if(iActive__SIM_MODE > 0)
		{
			sEXT_CH__SI_APC_POSITION->Set__DATA(str_hexa);
		}
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
::Call__PRESSURE_mTORR(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm)
{
	double set_pressure = aCH__PARA_PRESSURE_mTORR->Get__VALUE() * 0.001;

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
		else if(iDATA__VAT_CTRL_TYPE == _VAT_CTRL_TYPE__HEXA)
		{
			CString ch_pos;

			ch_pos.Format("%.1f", para__hold_pos);
			int set_hexa = (int) ((para__hold_pos / 100.0) * iLINK_HEXA__MAX_VALUE);

			UNION_2_BYTE__UINT x_data;
			x_data.uiDATA = 0x0ffff & set_hexa;

			CString str_hexa;
			str_hexa.Format("%02X %02X", 0x0ff & x_data.cBYTE[0], 0x0ff & x_data.cBYTE[1]);

			sCH__MON_SET_POSITION->Set__DATA(ch_pos);
			sEXT_CH__SO_APC_SETPOINT_DATA->Set__DATA(str_hexa);

			sEXT_CH__SO_APC_SETPOINT_TYPE->Set__DATA("01");
			sEXT_CH__SO_APC_CTRL_MODE->Set__DATA("00");

			if(iActive__SIM_MODE > 0)
			{
				sEXT_CH__SI_APC_POSITION->Set__DATA(str_hexa);
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

	// ...
	CString ch__pressure_torr;
	CString ch__pressure_mtorr;

	ch__pressure_torr.Format("%.3f", set_pressure);
	ch__pressure_mtorr.Format("%.1f", set_pressure * 1000.0);

	sCH__MON_SET_PRESSURE_TORR->Set__DATA(ch__pressure_torr);
	sCH__MON_SET_PRESSURE_mTORR->Set__DATA(ch__pressure_mtorr);

	if(iDATA__VAT_CTRL_TYPE == _VAT_CTRL_TYPE__OBJ)
	{
		if(iPARA__PRESSURE_UNIT == _PRESSURE_UNIT__mTORR)
		{
			aEXT_CH__VAT__PARA_PRESSURE_VALUE->Set__DATA(ch__pressure_mtorr);
		}
		else
		{
			aEXT_CH__VAT__PARA_PRESSURE_VALUE->Set__DATA(ch__pressure_torr);
		}

		if(iActive__SIM_MODE > 0)
		{
			sEXT_CH__SIM_PRESSURE_TORR->Set__DATA(ch__pressure_torr);

			if(iPARA__PRESSURE_UNIT == _PRESSURE_UNIT__mTORR)
			{
				aEXT_CH__VAT__CUR_PRESSURE_VALUE->Set__DATA(ch__pressure_mtorr);
			}		
			else
			{
				aEXT_CH__VAT__CUR_PRESSURE_VALUE->Set__DATA(ch__pressure_torr);
			}
		}

		return pOBJ_CTRL__VAT->Call__OBJECT(sVAT_CMMD__PRESSURE);
	}
	else if(iDATA__VAT_CTRL_TYPE == _VAT_CTRL_TYPE__HEXA)
	{
		double cfg_max = aCH__CFG_PRESSURE_MAX_VALUE->Get__VALUE();
		int set_hexa = (int) ((set_pressure / cfg_max) * iLINK_HEXA__MAX_VALUE);

		UNION_2_BYTE__UINT x_data;
		x_data.uiDATA = 0x0ffff & set_hexa;

		CString str_hexa;
		str_hexa.Format("%02X %02X", 0x0ff & x_data.cBYTE[0], 0x0ff & x_data.cBYTE[1]);

		sEXT_CH__SO_APC_SETPOINT_DATA->Set__DATA(str_hexa);

		sEXT_CH__SO_APC_SETPOINT_TYPE->Set__DATA("00");
		sEXT_CH__SO_APC_CTRL_MODE->Set__DATA("00");

		if(iActive__SIM_MODE > 0)
		{
			sEXT_CH__SIM_PRESSURE_TORR->Set__DATA(ch__pressure_torr);
			sEXT_CH__SI_APC_PRESSURE->Set__DATA(str_hexa);
		}
	}
	else
	{
		double cfg__press_max = aCH__CFG_PRESSURE_MAX_VALUE->Get__VALUE();
		double set__press_per = (set_pressure / cfg__press_max) * 100.0;
		if(set__press_per > 100.0)			set__press_per = 100.0;

		aEXT_CH__AO_APC_SETPOINT_DATA->Set__VALUE(set__press_per);

		dEXT_CH__DO_APC_SETPOINT_TYPE->Set__DATA(STR__PRESSURE);
		dEXT_CH__DO_APC_CTRL_MODE->Set__DATA(STR__CONTROL);

		if(iActive__SIM_MODE > 0)
		{
			sEXT_CH__SIM_PRESSURE_TORR->Set__DATA(ch__pressure_torr);

			if(iPARA__PRESSURE_UNIT == _PRESSURE_UNIT__mTORR)
			{
				aEXT_CH__AI_APC_PRESSURE->Set__DATA(ch__pressure_mtorr);
			}		
			else
			{
				aEXT_CH__AI_APC_PRESSURE->Set__DATA(ch__pressure_torr);
			}

			if(bActive__DI_APC_VLV_CLOSE)		dEXT_CH__DI_APC_VLV_CLOSE->Set__DATA(STR__OFF);
			if(bActive__DI_APC_VLV_OPEN)		dEXT_CH__DI_APC_VLV_OPEN->Set__DATA(STR__OFF);
		}
	}

	return 1;
}
