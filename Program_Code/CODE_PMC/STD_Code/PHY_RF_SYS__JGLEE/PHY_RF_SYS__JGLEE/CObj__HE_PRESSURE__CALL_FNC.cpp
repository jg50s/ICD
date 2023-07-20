#include "StdAfx.h"
#include "CObj__HE_PRESSURE.h"
#include "CCommon_Utility.h"

#include "Macro__Function.h"


// ...
int CObj__HE_PRESSURE
::Call__INIT(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm)
{

	return 1;
}

// ...
int CObj__HE_PRESSURE
::Call__CLOSE(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm)
{
	for(int i=0; i<iZONE_SIZE; i++)
	{
		Fnc__PRESSURE_SET(i, 0.0);
	}
	return 1;
}

int CObj__HE_PRESSURE
::Call__PRESSURE_SET(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm)
{
	for(int i=0; i<iZONE_SIZE; i++)
	{
		double set_pressure = aCH__PARA_PRESSURE_SET_X[i]->Get__VALUE();

		Fnc__PRESSURE_SET(i, set_pressure);
	}
	return 1;
}

// ...
int CObj__HE_PRESSURE
::Fnc__PRESSURE_SET(const int zone_index,const double set_pressure)
{
	double cfg_min, cfg_max;
	int cfg_dec;

	aCH__USER_IO_PRESSURE_SET_X[zone_index]->Get__MIN_MAX_DEC(cfg_min,cfg_max, cfg_dec);

	//
	double cur_pressure = set_pressure;
	if(cur_pressure > cfg_max)		cur_pressure = cfg_max;

	aCH__USER_IO_PRESSURE_SET_X[zone_index]->Set__VALUE(cur_pressure);
	aCH__MON_IO_PRESSURE_SET_X[zone_index]->Set__VALUE(cur_pressure);

	// Output.HEXA ...
	{
		unsigned short int set_hexa = (unsigned short int) (0x7FFF * (cur_pressure / cfg_max));

		//
		byte uch_data[11];
		memset(uch_data, 0, 11);

		UNION_2_BYTE__UINT m_data;
		m_data.uiDATA = set_hexa;

		uch_data[0] = 0x0ff & m_data.cBYTE[0];		// Low
		uch_data[1] = 0x0ff & m_data.cBYTE[1];		// High

		//
		CString ch_data;
		CString ch_hexa;

		int i_limit = 2;
		for(int i=0; i<i_limit; i++)
		{
			ch_hexa.Format("%02X ", 0x0ff & uch_data[i]);
			ch_data += ch_hexa;
		}

		soEXT_CH__PRESSURE_HEXA_X[zone_index]->Set__DATA(ch_data);

		//
		if(iActive__SIM_MODE > 0)
		{
			siEXT_CH__PRESSURE_HEXA_X[zone_index]->Set__DATA(ch_data);

			// ...
			aCH__MON_IO_FLOW_X[zone_index]->Get__MIN_MAX_DEC(cfg_min,cfg_max,cfg_dec);

			double cur_flow = cur_pressure * 0.5;
			set_hexa = (unsigned short int) (0x7FFF * (cur_flow / cfg_max));

			UNION_2_BYTE__UINT m_data;
			m_data.uiDATA = set_hexa;

			uch_data[0] = 0x0ff & m_data.cBYTE[0];
			uch_data[1] = 0x0ff & m_data.cBYTE[1];

			//
			ch_data = "";

			int i_limit = 2;
			for(int i=0; i<i_limit; i++)
			{
				ch_hexa.Format("%02X ", 0x0ff & uch_data[i]);
				ch_data += ch_hexa;
			}

			siEXT_CH__FLOW_HEXA_X[zone_index]->Set__DATA(ch_data);
		}
	}

	// ...
	{
		CString log_msg;
		CString log_bff;

		log_msg  = "\n";
		log_bff.Format("SZone(%1d) Setting Info ... \n", zone_index+1);
		log_msg += log_bff;

		log_bff.Format("  * Set_Pressure <- %.3f \n", set_pressure);
		log_msg += log_bff;

		log_bff.Format("  * Cfg_Max <- %.3f \n", cfg_max);
		log_msg += log_bff;

		log_bff.Format("  * %s <- %s \n",
						soEXT_CH__PRESSURE_HEXA_X[zone_index]->Get__CHANNEL_NAME(),
						soEXT_CH__PRESSURE_HEXA_X[zone_index]->Get__STRING());
		log_msg += log_bff;

		xI_LOG_CTRL->WRITE__LOG(log_msg);		
	}

	return 1;
}
