#include "StdAfx.h"
#include "CObj__RF_STD.h"

#include "CObj__RF_STD__ALID.h"
#include "CObj__RF_STD__DEF.h"


// ...
int CObj__RF_STD::
Mon__IO_TYPE_ALARM_CHECK(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm) // KMS
{
	CString Alarm_info = "";
	CCommon_Utility m_fnc;
	if(bActive__RF_IO_OBJ) return 1; // IF OBJ TYPE EXIT
	while(1)
	{
		if(dEXT_CH__RF_ALARM->Check__VARIABLE_NAME(STR__ON) > 0)
		{	
			Alarm_info = sEXT_CH__INFO_RF_ALARM->Get__STRING();
			int alarm_no = m_fnc.Get__Hexa_From_String(Alarm_info);
			if(alarm_no == 20) Alarm_info = "INTERLOCK LOST";
			else if(alarm_no == 21)	Alarm_info = "COOLING AIR";
			else if(alarm_no == 22) Alarm_info = "COOLING WAFER";
			else if(alarm_no == 23) Alarm_info = "DEW CONDENSATION";
			else if(alarm_no == 24) Alarm_info = "POWER EXCESS";
			else if(alarm_no == 25) Alarm_info = "REF LIMIT";
			else if(alarm_no == 27) Alarm_info = "POWER FALL";
			else if(alarm_no == 28) Alarm_info = "COMM ERROR";
			else if(alarm_no == 31) Alarm_info = "FAN FAILURE";
			else if(alarm_no == 32) Alarm_info = "PS FAILURE";
			else if(alarm_no == 33) Alarm_info = "AC DROPOUT";
			else if(alarm_no == 34) Alarm_info = "ARC COUNT LIMIT";
			else if(alarm_no == 35) Alarm_info = "INTERNAL COMM ERROR";
			else if(alarm_no == 36) Alarm_info = "RF-ON TIME LIMIT";
			else if(alarm_no == 37) Alarm_info = "WATER VALVE";
			else if(alarm_no == 38) Alarm_info = "WAFER LEAK";
			else if(alarm_no == 39) Alarm_info = "NO OSC SIGNAL";
			else
			{
				alarm_no = 0;
				Alarm_info = "";
			}
			
			if(alarm_no > 0)
			{
				int alarm_id = ALID__RF_DEVICE_WARNING_EXIST;
				CString r_act;

				p_alarm->Check__ALARM(alarm_id,r_act);
				p_alarm->Post__ALARM_With_MESSAGE(alarm_id, Alarm_info);
			}			
			Sleep(50);
		}

	}
	return 1;
}