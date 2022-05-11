#include "StdAfx.h"
#include "CObj__ESC_IO.h"


// ...
int  CObj__ESC_IO
::Call__INIT(CII_OBJECT__VARIABLE* p_variable,
			 CII_OBJECT__ALARM* p_alarm)
{
	return Fnc__INIT(p_variable, p_alarm);
}

int  CObj__ESC_IO
::Call__TO_DECHUCKED(CII_OBJECT__VARIABLE* p_variable,
					 CII_OBJECT__ALARM* p_alarm)
{
	dCH__MON_CHUCK_STATUS->Set__DATA(STR__DECHUCKED);
	return 1;
}

int  CObj__ESC_IO
::Call__HE_CLOSE(CII_OBJECT__VARIABLE* p_variable,
				 CII_OBJECT__ALARM* p_alarm)
{
	return Fnc__HE_CLOSE(p_variable,p_alarm);
}

int  CObj__ESC_IO
::Call__HW_CHECK(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm)
{
	return Fnc__HW_CHECK(p_variable, p_alarm);
}
int  CObj__ESC_IO
::Call__DECHUCK_VERIFY(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm)
{
	return Fnc__DECHUCK_VERIFY(p_variable, p_alarm);
}

int  CObj__ESC_IO
::Call__VENT_READY(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm)
{
	return Fnc__VENT_READY(p_variable, p_alarm);
}
int  CObj__ESC_IO
::Call__PUMP_READY(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm)
{
	return Fnc__PUMP_READY(p_variable, p_alarm);
}

int  CObj__ESC_IO
::Call__CHUCK_OF_CONFIG(CII_OBJECT__VARIABLE* p_variable,
						CII_OBJECT__ALARM* p_alarm,
						const int chuck_mode)
{
	CString var_data;

	// Setting ...
	{
		// Center.Cfg ...
		{
			aCH__CFG_ESC_CENTER_CHUCKING_VOLTAGE_SETPOINT->Get__DATA(var_data);
			sCH__PARA_ESC_CENTER_SET_VOLTAGE->Set__DATA(var_data);

			aCH__CFG_HE_CENTER_PRESSURE_SETPOINT->Get__DATA(var_data);
			sCH__PARA_He_SET_PRESSURE_CENTER->Set__DATA(var_data);
		}
		// Edge.Cfg ...
		{
			aCH__CFG_ESC_EDGE_CHUCKING_VOLTAGE_SETPOINT->Get__DATA(var_data);
			sCH__PARA_ESC_EDGE_SET_VOLTAGE->Set__DATA(var_data);

			aCH__CFG_HE_EDGE_PRESSURE_SETPOINT->Get__DATA(var_data);
			sCH__PARA_He_SET_PRESSURE_EDGE->Set__DATA(var_data);
		}
	}

	// Monitoring ...
	{
		// Center.Flow ...
		{
			aCH__CFG_HE_CENTER_FLOW_MIN_THRESHOLD->Get__DATA(var_data);
			aCH__MON_HE_CENTER_FLOW_MIN_THRESHOLD->Set__DATA(var_data);

			aCH__CFG_HE_CENTER_FLOW_MAX_THRESHOLD->Get__DATA(var_data);
			aCH__MON_HE_CENTER_FLOW_MAX_THRESHOLD->Set__DATA(var_data);
		}
		// Edge.Flow ...
		{
			aCH__CFG_HE_EDGE_FLOW_MIN_THRESHOLD->Get__DATA(var_data);
			aCH__MON_HE_EDGE_FLOW_MIN_THRESHOLD->Set__DATA(var_data);

			aCH__CFG_HE_EDGE_FLOW_MAX_THRESHOLD->Get__DATA(var_data);
			aCH__MON_HE_EDGE_FLOW_MAX_THRESHOLD->Set__DATA(var_data);
		}
	}

	return Fnc__CHUCK(p_variable, p_alarm, chuck_mode);
}
int  CObj__ESC_IO
::Call__CHUCK_OF_PROCESS(CII_OBJECT__VARIABLE* p_variable,
						 CII_OBJECT__ALARM* p_alarm,
						 const int proc_mode)
{
	int chuck_mode = -1;
	CString var_data;

	if(proc_mode >= 0)
	{
		chuck_mode = proc_mode;

		// Setting ...
		{
			// Center.CFG ...
			{
				aCH__CFG_ESC_CENTER_CHUCKING_VOLTAGE_SETPOINT->Get__DATA(var_data);
				sCH__PARA_ESC_CENTER_SET_VOLTAGE->Set__DATA(var_data);

				var_data = sCH__RCP_He_CENTER_PRESSURE_SETPOINT_TORR->Get__STRING();
				sCH__PARA_He_SET_PRESSURE_CENTER->Set__DATA(var_data);
			}
			// Edge.CFG ...
			{
				aCH__CFG_ESC_EDGE_CHUCKING_VOLTAGE_SETPOINT->Get__DATA(var_data);
				sCH__PARA_ESC_EDGE_SET_VOLTAGE->Set__DATA(var_data);

				var_data = sCH__RCP_He_EDGE_PRESSURE_SETPOINT_TORR->Get__STRING();
				sCH__PARA_He_SET_PRESSURE_EDGE->Set__DATA(var_data);
			}
		}

		// Monitoring ...
		{
			// Center.Flow ...
			{
				var_data = sCH__RCP_He_CENTER_FLOW_MIN_THRESHOLD->Get__STRING();
				double rcp_min = atof(var_data);

				if(rcp_min < 0.001)		aCH__CFG_HE_CENTER_FLOW_MIN_THRESHOLD->Get__DATA(var_data);
				aCH__MON_HE_CENTER_FLOW_MIN_THRESHOLD->Set__DATA(var_data);

				//
				var_data = sCH__RCP_He_CENTER_FLOW_MAX_THRESHOLD->Get__STRING();
				double rcp_max = atof(var_data);

				if(rcp_max < 0.001)		aCH__CFG_HE_CENTER_FLOW_MAX_THRESHOLD->Get__DATA(var_data);
				aCH__MON_HE_CENTER_FLOW_MAX_THRESHOLD->Set__DATA(var_data);
			}
			// Edge.Flow ...
			{
				var_data = sCH__RCP_He_EDGE_FLOW_MIN_THRESHOLD->Get__STRING();
				double rcp_min = atof(var_data);

				if(rcp_min < 0.001)		aCH__CFG_HE_EDGE_FLOW_MIN_THRESHOLD->Get__DATA(var_data);
				aCH__MON_HE_EDGE_FLOW_MIN_THRESHOLD->Set__DATA(var_data);

				//
				var_data = sCH__RCP_He_EDGE_FLOW_MAX_THRESHOLD->Get__STRING();
				double rcp_max = atof(var_data);

				if(rcp_max < 0.001)		aCH__CFG_HE_EDGE_FLOW_MAX_THRESHOLD->Get__DATA(var_data);
				aCH__MON_HE_EDGE_FLOW_MAX_THRESHOLD->Set__DATA(var_data);
			}
		}
	}
	else
	{
		chuck_mode = 0;

		// Setting ...
		{
			// Center.Cfg ...
			{
				aCH__CFG_ESC_CENTER_CHUCKING_VOLTAGE_SETPOINT->Get__DATA(var_data);
				sCH__PARA_ESC_CENTER_SET_VOLTAGE->Set__DATA(var_data);

				aCH__TEST_PARA_He_SET_PRESSURE_CENTER->Get__DATA(var_data);
				sCH__PARA_He_SET_PRESSURE_CENTER->Set__DATA(var_data);
			}
			// Edge.Cfg ...
			{
				aCH__CFG_ESC_EDGE_CHUCKING_VOLTAGE_SETPOINT->Get__DATA(var_data);
				sCH__PARA_ESC_EDGE_SET_VOLTAGE->Set__DATA(var_data);

				aCH__TEST_PARA_He_SET_PRESSURE_EDGE->Get__DATA(var_data);
				sCH__PARA_He_SET_PRESSURE_EDGE->Set__DATA(var_data);
			}
		}

		// Monitoring ...
		{
			// Center.Flow ...
			{
				aCH__CFG_HE_CENTER_FLOW_MIN_THRESHOLD->Get__DATA(var_data);
				aCH__MON_HE_CENTER_FLOW_MIN_THRESHOLD->Set__DATA(var_data);

				aCH__CFG_HE_CENTER_FLOW_MAX_THRESHOLD->Get__DATA(var_data);
				aCH__MON_HE_CENTER_FLOW_MAX_THRESHOLD->Set__DATA(var_data);
			}
			// Edge.Flow ...
			{
				aCH__CFG_HE_EDGE_FLOW_MIN_THRESHOLD->Get__DATA(var_data);
				aCH__MON_HE_EDGE_FLOW_MIN_THRESHOLD->Set__DATA(var_data);

				aCH__CFG_HE_EDGE_FLOW_MAX_THRESHOLD->Get__DATA(var_data);
				aCH__MON_HE_EDGE_FLOW_MAX_THRESHOLD->Set__DATA(var_data);
			}
		}
	}

	return Fnc__CHUCK(p_variable, p_alarm, chuck_mode);
}
int  CObj__ESC_IO
::Call__HE_SET_OF_PROC(CII_OBJECT__VARIABLE* p_variable,
					   CII_OBJECT__ALARM* p_alarm)
{
	CString var_data;

	// Setting ...
	{
		// Center.RCP ...
		{
			var_data = sCH__RCP_He_CENTER_PRESSURE_SETPOINT_TORR->Get__STRING();
			sCH__PARA_He_SET_PRESSURE_CENTER->Set__DATA(var_data);
		}
		// Edge.RCP ...
		{
			var_data = sCH__RCP_He_EDGE_PRESSURE_SETPOINT_TORR->Get__STRING();
			sCH__PARA_He_SET_PRESSURE_EDGE->Set__DATA(var_data);
		}
	}

	int r_flag = Fnc__HE_SET_OF_PROC(p_variable, p_alarm);

	// Monitoring ...
	if(r_flag > 0)
	{
		// Center.Flow ...
		{
			var_data = sCH__RCP_He_CENTER_FLOW_MIN_THRESHOLD->Get__STRING();
			double rcp_min = atof(var_data);

			if(rcp_min < 0.001)		aCH__CFG_HE_CENTER_FLOW_MIN_THRESHOLD->Get__DATA(var_data);
			aCH__MON_HE_CENTER_FLOW_MIN_THRESHOLD->Set__DATA(var_data);

			//
			var_data = sCH__RCP_He_CENTER_FLOW_MAX_THRESHOLD->Get__STRING();
			double rcp_max = atof(var_data);

			if(rcp_max < 0.001)		aCH__CFG_HE_CENTER_FLOW_MAX_THRESHOLD->Get__DATA(var_data);
			aCH__MON_HE_CENTER_FLOW_MAX_THRESHOLD->Set__DATA(var_data);
		}
		// Edge.Flow ...
		{
			var_data = sCH__RCP_He_EDGE_FLOW_MIN_THRESHOLD->Get__STRING();
			double rcp_min = atof(var_data);

			if(rcp_min < 0.001)		aCH__CFG_HE_EDGE_FLOW_MIN_THRESHOLD->Get__DATA(var_data);
			aCH__MON_HE_EDGE_FLOW_MIN_THRESHOLD->Set__DATA(var_data);

			//
			var_data = sCH__RCP_He_EDGE_FLOW_MAX_THRESHOLD->Get__STRING();
			double rcp_max = atof(var_data);

			if(rcp_max < 0.001)		aCH__CFG_HE_EDGE_FLOW_MAX_THRESHOLD->Get__DATA(var_data);
			aCH__MON_HE_EDGE_FLOW_MAX_THRESHOLD->Set__DATA(var_data);
		}
	}

	return r_flag;
}

int  CObj__ESC_IO
::Call__DECHUCK(CII_OBJECT__VARIABLE* p_variable,
				CII_OBJECT__ALARM* p_alarm,
				const int dechuck_mode)
{
	int r_flag = Fnc__DECHUCK(p_variable, p_alarm, dechuck_mode);

	doEXT_CH__ESC_All_Voltage->Set__DATA(STR__Off);
	return r_flag;
}
