#include "StdAfx.h"
#include "CObj_Phy__CHM_STD.h"
#include "CObj_Phy__CHM_STD__DEF.h"


// ...
int CObj_Phy__CHM_STD
::Call__INIT(CII_OBJECT__VARIABLE* p_variable,
			 CII_OBJECT__ALARM *p_alarm)
{
	int r_flag = Fnc__MODULE_OBJ(p_variable, _CMMD__INIT);

	if(r_flag > 0)
	{
		if(iActive__SIM_MODE > 0)
		{
			if(dEXT_CH_CFG__TRANSFER_MODE->Check__DATA(STR__VAC) > 0)
			{
				Call__PUMP(p_variable, p_alarm);
			}
			else
			{
				Call__VENT(p_variable, p_alarm);
			}
		}
	}
	return r_flag;
}
int CObj_Phy__CHM_STD
::Call__MAINT(CII_OBJECT__VARIABLE* p_variable,
			  CII_OBJECT__ALARM *p_alarm)
{
	return Fnc__MODULE_OBJ(p_variable, _CMMD__MAINT);
}

int CObj_Phy__CHM_STD
::Call__PUMP(CII_OBJECT__VARIABLE* p_variable,
			 CII_OBJECT__ALARM *p_alarm)
{
	int loop = -1;
	int flag;

	do
	{
		loop = -1;
		flag = Fnc__MODULE_OBJ(p_variable, _CMMD__PUMP);

		if(flag > 0)
		{
			CString var_data;
			double ref_press;
			double cur_press;

			aEXT_CH_CFG__REF_VAC_PRESSURE->Get__DATA(var_data);
			ref_press = atof(var_data);

			if(iActive__SIM_MODE > 0)
			{
				cur_press = ref_press * 0.9;

				var_data.Format("%.3f", cur_press);
				xCH__PRESSURE_VALUE->Set__DATA(var_data);
			}
			else
			{
				xCH__PRESSURE_VALUE->Get__DATA(var_data);
				cur_press = atof(var_data);
			}

			if(cur_press > ref_press)
			{
				CString alarm_msg;
				CString r_act;

				alarm_msg.Format("TMC's pressure (%.3f torr) must be less than %.3f torr.",
					cur_press,ref_press);

				p_alarm->Popup__ALARM_With_MESSAGE(ALID__PUMP_ERROR,alarm_msg,r_act);

				if(r_act.CompareNoCase("RETRY") == 0)
				{
					loop = 1;
				}
				else
				{
					flag = -1;
				}
			}	
		}
	}
	while(loop > 0);

	return flag;
}
int CObj_Phy__CHM_STD::Call__VENT(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM *p_alarm)
{
	int loop = -1;
	int flag;

	do
	{
		loop = -1;
		flag = Fnc__MODULE_OBJ(p_variable, _CMMD__VENT);

		if(flag > 0)
		{
			CString var_data;
			double ref_press;
			double cur_press;

			aEXT_CH_CFG__REF_ATM_PRESSURE->Get__DATA(var_data);
			ref_press = atof(var_data);

			if(iActive__SIM_MODE > 0)
			{
				cur_press = ref_press * 1.01;

				var_data.Format("%.1f", cur_press);
				xCH__PRESSURE_VALUE->Set__DATA(var_data);
			}
			else
			{
				xCH__PRESSURE_VALUE->Get__DATA(var_data);
				cur_press = atof(var_data);
			}

			if(cur_press < ref_press)
			{
				CString alarm_msg;
				CString r_act;

				alarm_msg.Format("TMC's pressure (%.3f torr) must be more than %.3f torr.",	cur_press,ref_press);

				p_alarm->Popup__ALARM_With_MESSAGE(ALID__VENT_ERROR,alarm_msg,r_act);

				if(r_act.CompareNoCase("RETRY") == 0)
				{
					loop = 1;
				}
				else
				{
					flag = -1;
				}
			}	
		}
	}
	while(loop > 0);

	return flag;
}
int CObj_Phy__CHM_STD::Call__ISOLATE(CII_OBJECT__VARIABLE* p_variable)
{
	return Fnc__MODULE_OBJ(p_variable, _CMMD__ISOLATE);
}
int CObj_Phy__CHM_STD::Call__PURGE(CII_OBJECT__VARIABLE* p_variable)
{
	return Fnc__MODULE_OBJ(p_variable, _CMMD__PURGE);
}


// ...
int CObj_Phy__CHM_STD::Call__PMx_SV_OPEN(CII_OBJECT__VARIABLE* p_variable)
{
	CString ch_data = dCH__PARA_PMx_ID->Get__STRING();
	xCH__TMC_CHM_PARA_PMx_ID->Set__DATA(ch_data);

	return Fnc__MODULE_OBJ(p_variable, _CMMD__PMx_SV_OPEN);
}
int CObj_Phy__CHM_STD::Call__PMx_SV_CLOSE(CII_OBJECT__VARIABLE* p_variable)
{
	CString ch_data = dCH__PARA_PMx_ID->Get__STRING();
	xCH__TMC_CHM_PARA_PMx_ID->Set__DATA(ch_data);

	return Fnc__MODULE_OBJ(p_variable, _CMMD__PMx_SV_CLOSE);
}
