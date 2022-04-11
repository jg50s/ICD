#include "StdAfx.h"
#include "CObj__ESC_IO.h"

#include "CCommon_Utility.h"


//-------------------------------------------------------------------------
CObj__ESC_IO::CObj__ESC_IO()
{

}
CObj__ESC_IO::~CObj__ESC_IO()
{

}

//-------------------------------------------------------------------------
int CObj__ESC_IO::__DEFINE__CONTROL_MODE(obj,l_mode)
{
	sObject_Name = obj;

	// ...
	{
		ADD__CTRL_VAR(sMODE__INIT,           "INIT");

		ADD__CTRL_VAR(sMODE__TO_DECHUCKED,   "TO.DECHUCKED");
		ADD__CTRL_VAR(sMODE__HE_CLOSE,       "HE.CLOSE");
		ADD__CTRL_VAR(sMODE__HW_CHECK,       "HW.CHECK");
		ADD__CTRL_VAR(sMODE__DECHUCK_VERIFY, "DECHUCK.VERIFY");

		ADD__CTRL_VAR(sMODE__VENT_READY,     "VENT.READY");
		ADD__CTRL_VAR(sMODE__PUMP_READY,     "PUMP.READY");

		ADD__CTRL_VAR(sMODE__CHUCK_CFG,	     "CHUCK.CFG");
		ADD__CTRL_VAR(sMODE__CHUCK1_CFG,     "CHUCK1.CFG");
		ADD__CTRL_VAR(sMODE__CHUCK2_CFG,     "CHUCK2.CFG");

		ADD__CTRL_VAR(sMODE__CHUCK_TEST,     "CHUCK.TEST");
		ADD__CTRL_VAR(sMODE__CHUCK_PROC,     "CHUCK.PROC");
		ADD__CTRL_VAR(sMODE__CHUCK1_PROC,    "CHUCK1.PROC");
		ADD__CTRL_VAR(sMODE__CHUCK2_PROC,    "CHUCK2.PROC");
		ADD__CTRL_VAR(sMODE__HE_SET_PROC,    "HE_SET.PROC");

		ADD__CTRL_VAR(sMODE__DECHUCK_END,    "DECHUCK.END");
		ADD__CTRL_VAR(sMODE__DECHUCK,        "DECHUCK");
		ADD__CTRL_VAR(sMODE__DECHUCK1,       "DECHUCK1");
		ADD__CTRL_VAR(sMODE__DECHUCK2,       "DECHUCK2");
	}
	return 1;
}
int CObj__ESC_IO::__DEFINE__VERSION_HISTORY(version)
{

	return 1;
}


// ...
#define MON_ID__REQ_CTRL						1
#define MON_ID__SYS_INFO						2
#define MON_ID__ESC_STABLE_CHECK				3
#define MON_ID__HELIUM_STABLE_CHECK				4

// ...
#define APP_DSP__ENABLE_DISABLE                 \
"ENABLE DISABLE"

#define APP_DSP__DISABLE_ENABLE                 \
"DISABLE ENABLE"

#define APP_DSP__ESC_VOLT_CTRL_TYPE             \
"AUTO STEP"


int CObj__ESC_IO::__DEFINE__VARIABLE_STD(p_variable)
{
	DECLARE__STD_VARIABLE;

	// ...
	CCommon_Error__DEF_VARIABLE m_err_def_variable;
	p_variable->Link__DEF_VARIABLE__ERROR_FEEDBACK(&m_err_def_variable);

	// ...
	CString var_name;
	CString str_item_list;
	int i;

	// ...
	{
		var_name = "APP.OBJ.MSG";
		STD__ADD_STRING(var_name);
		LINK__VAR_STRING_CTRL(sCH__APP_LOG_MSG, var_name);

		var_name = "APP.OBJ.SUB.MSG";
		STD__ADD_STRING(var_name);
		LINK__VAR_STRING_CTRL(sCH__APP_LOG_SUB_MSG, var_name);

		var_name = "APP.TIMER.COUNT";
		STD__ADD_STRING(var_name);
		LINK__VAR_STRING_CTRL(sCH__APP_TIMER_COUNT, var_name);
	}

	// 3WAY_VLV.CENTER ...
	{
		var_name = "REQ.HE.FINAL.CENTER.3WAY.VLV";
		STD__ADD_STRING(var_name);
		LINK__VAR_STRING_CTRL(sCH__REQ_HE_FINAL_CENTER__3WAY_VLV, var_name);

		var_name = "MON.HE.FINAL.CENTER.3WAY.VLV";
		STD__ADD_STRING(var_name);
		LINK__VAR_STRING_CTRL(sCH__MON_HE_FINAL_CENTER__3WAY_VLV, var_name);
	}
	// 3WAY_VLV.EDGE ...
	{
		var_name = "REQ.HE.FINAL.EDGE.3WAY.VLV";
		STD__ADD_STRING(var_name);
		LINK__VAR_STRING_CTRL(sCH__REQ_HE_FINAL_EDGE__3WAY_VLV, var_name);

		var_name = "MON.HE.FINAL.EDGE.3WAY.VLV";
		STD__ADD_STRING(var_name);
		LINK__VAR_STRING_CTRL(sCH__MON_HE_FINAL_EDGE__3WAY_VLV, var_name);
	}

	// ...
	{
		var_name = "MON.ESC.OBJ_STATUS";
		STD__ADD_STRING(var_name);
		LINK__VAR_STRING_CTRL(sCH__MON_ESC_OBJ_STATUS, var_name);

		var_name = "MON.He.OBJ_STATUS";
		STD__ADD_STRING(var_name);
		LINK__VAR_STRING_CTRL(sCH__MON_He_OBJ_STATUS, var_name);
	}

	// MON.HE ...
	{
		// ...
		{
			var_name = "MON.CHUCK_STATUS";
			str_item_list = "UNKNOWN CHUCKING CHUCKED DECHUCKING DECHUCKED";
			STD__ADD_DIGITAL(var_name, str_item_list);
			LINK__VAR_DIGITAL_CTRL(dCH__MON_CHUCK_STATUS, var_name);

			var_name = "MON.He_FLOW_STATUS";
			STD__ADD_STRING(var_name);
			LINK__VAR_STRING_CTRL(sCH__MON_He_FLOW_STATUS, var_name);
		}

		// Center ...
		{
			var_name = "MON.He_LEAK_SCCM.CENTER";
			STD__ADD_STRING(var_name);
			LINK__VAR_STRING_CTRL(sCH__MON_He_LEAK_SCCM_CENTER, var_name);

			var_name = "MON.He_Pressure.CENTER";
			STD__ADD_STRING(var_name);
			LINK__VAR_STRING_CTRL(sCH__MON_He_Pressure_CENTER, var_name);

			var_name = "MON.He_Flow.CENTER";
			STD__ADD_STRING(var_name);
			LINK__VAR_STRING_CTRL(sCH__MON_He_Flow_CENTER, var_name);
		}
		// Edge ...
		{
			var_name = "MON.He_LEAK_SCCM.EDGE";
			STD__ADD_STRING(var_name);
			LINK__VAR_STRING_CTRL(sCH__MON_He_LEAK_SCCM_EDGE, var_name);

			var_name = "MON.He_Pressure.EDGE";
			STD__ADD_STRING(var_name);
			LINK__VAR_STRING_CTRL(sCH__MON_He_Pressure_EDGE, var_name);

			var_name = "MON.He_Flow.EDGE";
			STD__ADD_STRING(var_name);
			LINK__VAR_STRING_CTRL(sCH__MON_He_Flow_EDGE, var_name);
		}
	}

	// MON.ESC_ON ...
	{
		var_name = "MON.ESC_ON.TIME.START_DATE";
		STD__ADD_STRING(var_name);
		LINK__VAR_STRING_CTRL(sCH__MON_ESC_ON_TIME_START_DATE, var_name);

		var_name = "MON.ESC_ON.TIME.TOTAL_HOUR";
		STD__ADD_ANALOG_WITH_X_OPTION(var_name, "hour", 0, 0, 9999999, "");
		LINK__VAR_ANALOG_CTRL(aCH__MON_ESC_ON_TIME_TOTAL_HOUR, var_name);

		var_name = "MON.ESC_ON.TIME.TOTAL_SEC";
		STD__ADD_ANALOG_WITH_X_OPTION(var_name, "sec", 0, 0, 9999999, "");
		LINK__VAR_ANALOG_CTRL(aCH__MON_ESC_ON_TIME_TOTAL_SEC, var_name);

		var_name = "MON.ESC_ON.TIME.RESET";
		STD__ADD_DIGITAL(var_name, "RETURN  RESET");
		LINK__VAR_DIGITAL_CTRL(dCH__MON_ESC_ON_TIME_RESET, var_name);
	}

	// ZERO CAL - HE_PRESSURE ...
	{
		// Center ...
		{
			var_name = "ZERO_CAL.REQ.HE_PRESSURE.CENTER";
			STD__ADD_STRING(var_name);
			LINK__VAR_STRING_CTRL(sCH__ZERO_CAL_REQ_HE_PRESSURE_CENTER, var_name);

			var_name = "ZERO_CAL.RESET.HE_PRESSURE.CENTER";
			STD__ADD_STRING(var_name);
			LINK__VAR_STRING_CTRL(sCH__ZERO_CAL_RESET_HE_PRESSURE_CENTER, var_name);
		}
		// Edge ...
		{
			var_name = "ZERO_CAL.REQ.HE_PRESSURE.EDGE";
			STD__ADD_STRING(var_name);
			LINK__VAR_STRING_CTRL(sCH__ZERO_CAL_REQ_HE_PRESSURE_EDGE, var_name);

			var_name = "ZERO_CAL.RESET.HE_PRESSURE.EDGE";
			STD__ADD_STRING(var_name);
			LINK__VAR_STRING_CTRL(sCH__ZERO_CAL_RESET_HE_PRESSURE_EDGE, var_name);
		}

		// Center ...
		{
			var_name = "ZERO_CAL.He_Pressure.CENTER";
			STD__ADD_STRING_WITH_X_OPTION(var_name, "");
			LINK__VAR_STRING_CTRL(sCH__ZERO_CAL_He_Pressure_CENTER, var_name);
		}
		// Edge ...
		{
			var_name = "ZERO_CAL.He_Pressure.EDGE";
			STD__ADD_STRING_WITH_X_OPTION(var_name, "");
			LINK__VAR_STRING_CTRL(sCH__ZERO_CAL_He_Pressure_EDGE, var_name);
		}
	}

	// ZERO CAL - HE_FLOW...
	{
		// Center ...
		{
			var_name = "ZERO_CAL.REQ.HE_FLOW.CENTER";
			STD__ADD_STRING(var_name);
			LINK__VAR_STRING_CTRL(sCH__ZERO_CAL_REQ_HE_FLOW_CENTER, var_name);

			var_name = "ZERO_CAL.RESET.HE_FLOW.CENTER";
			STD__ADD_STRING(var_name);
			LINK__VAR_STRING_CTRL(sCH__ZERO_CAL_RESET_HE_FLOW_CENTER, var_name);
		}
		// Edge ...
		{
			var_name = "ZERO_CAL.REQ.HE_FLOW.EDGE";
			STD__ADD_STRING(var_name);
			LINK__VAR_STRING_CTRL(sCH__ZERO_CAL_REQ_HE_FLOW_EDGE, var_name);

			var_name = "ZERO_CAL.RESET.HE_FLOW.EDGE";
			STD__ADD_STRING(var_name);
			LINK__VAR_STRING_CTRL(sCH__ZERO_CAL_RESET_HE_FLOW_EDGE, var_name);
		}

		// Center ...
		{
			var_name = "ZERO_CAL.He_Flow.CENTER";
			STD__ADD_STRING_WITH_X_OPTION(var_name, "");
			LINK__VAR_STRING_CTRL(sCH__ZERO_CAL_He_Flow_CENTER, var_name);
		}
		// Edge ...
		{
			var_name = "ZERO_CAL.He_Flow.EDGE";
			STD__ADD_STRING_WITH_X_OPTION(var_name, "");
			LINK__VAR_STRING_CTRL(sCH__ZERO_CAL_He_Flow_EDGE, var_name);
		}
	}

	// ...
	{
		var_name = "MON.MSG.STABLE_CHECK";
		STD__ADD_STRING(var_name);
		LINK__VAR_STRING_CTRL(sCH__MON_MSG_STABLE_CHECK, var_name);

		// System ...
		{
			var_name = "MON.STABLE.FLAG";
			STD__ADD_STRING(var_name);
			LINK__VAR_STRING_CTRL(sCH__MON_STABLE_FLAG, var_name);

			var_name = "MON.FAULT.FLAG";
			STD__ADD_STRING(var_name);
			LINK__VAR_STRING_CTRL(sCH__MON_FAULT_FLAG, var_name);

			//
			var_name = "MON.ESC.VOLTAGE.STATE";
			STD__ADD_DIGITAL(var_name, "OFF ON");
			LINK__VAR_DIGITAL_CTRL(dCH__MON_ESC_VOLTAGE_STATE, var_name);
		}

		// ESC Center ...
		{
			var_name = "MON.CENTER.CHANGE.ESC.STATE";
			STD__ADD_STRING(var_name);
			LINK__VAR_STRING_CTRL(sCH__MON_CENTER_CHANGE_ESC_STATE, var_name);

			var_name = "MON.CENTER.CHANGE.ESC.TIME";
			STD__ADD_STRING(var_name);
			LINK__VAR_STRING_CTRL(sCH__MON_CENTER_CHANGE_ESC_TIME, var_name);

			//
			var_name = "MON.CENTER.STABLE.ESC.STATE";
			STD__ADD_STRING(var_name);
			LINK__VAR_STRING_CTRL(sCH__MON_CENTER_STABLE_ESC_STATE, var_name);

			var_name = "MON.CENTER.STABLE.ESC.TIME";
			STD__ADD_STRING(var_name);
			LINK__VAR_STRING_CTRL(sCH__MON_CENTER_STABLE_ESC_TIME, var_name);

			//
			var_name = "MON.CENTER.FAULT.ESC.STATE";
			STD__ADD_STRING(var_name);
			LINK__VAR_STRING_CTRL(sCH__MON_CENTER_FAULT_ESC_STATE, var_name);

			var_name = "MON.CENTER.FAULT.ESC.TIME";
			STD__ADD_STRING(var_name);
			LINK__VAR_STRING_CTRL(sCH__MON_CENTER_FAULT_ESC_TIME, var_name);

			//
			var_name = "MON.CENTER.ESC.VOLTAGE.STATE";
			STD__ADD_DIGITAL(var_name, "OFF ON");
			LINK__VAR_DIGITAL_CTRL(dCH__MON_CENTER_ESC_VOLTAGE_STATE, var_name);
		}
		// ESC Edge ...
		{
			var_name = "MON.EDGE.CHANGE.ESC.STATE";
			STD__ADD_STRING(var_name);
			LINK__VAR_STRING_CTRL(sCH__MON_EDGE_CHANGE_ESC_STATE, var_name);

			var_name = "MON.EDGE.CHANGE.ESC.TIME";
			STD__ADD_STRING(var_name);
			LINK__VAR_STRING_CTRL(sCH__MON_EDGE_CHANGE_ESC_TIME, var_name);

			//
			var_name = "MON.EDGE.STABLE.ESC.STATE";
			STD__ADD_STRING(var_name);
			LINK__VAR_STRING_CTRL(sCH__MON_EDGE_STABLE_ESC_STATE, var_name);

			var_name = "MON.EDGE.STABLE.ESC.TIME";
			STD__ADD_STRING(var_name);
			LINK__VAR_STRING_CTRL(sCH__MON_EDGE_STABLE_ESC_TIME, var_name);

			//
			var_name = "MON.EDGE.FAULT.ESC.STATE";
			STD__ADD_STRING(var_name);
			LINK__VAR_STRING_CTRL(sCH__MON_EDGE_FAULT_ESC_STATE, var_name);

			var_name = "MON.EDGE.FAULT.ESC.TIME";
			STD__ADD_STRING(var_name);
			LINK__VAR_STRING_CTRL(sCH__MON_EDGE_FAULT_ESC_TIME, var_name);

			//
			var_name = "MON.EDGE.ESC.VOLTAGE.STATE";
			STD__ADD_DIGITAL(var_name, "OFF ON");
			LINK__VAR_DIGITAL_CTRL(dCH__MON_EDGE_ESC_VOLTAGE_STATE, var_name);
		}

		// He Center ...
		{
			var_name = "MON.CHANGE.HE.CENTER.STATE";
			STD__ADD_STRING(var_name);
			LINK__VAR_STRING_CTRL(sCH__MON_CHANGE_HE_CENTER_STATE, var_name);

			var_name = "MON.CHANGE.HE.CENTER.TIME";
			STD__ADD_STRING(var_name);
			LINK__VAR_STRING_CTRL(sCH__MON_CHANGE_HE_CENTER_TIME, var_name);

			//
			var_name = "MON.STABLE.HE.CENTER.STATE";
			STD__ADD_STRING(var_name);
			LINK__VAR_STRING_CTRL(sCH__MON_STABLE_HE_CENTER_STATE, var_name);

			var_name = "MON.STABLE.HE.CENTER.TIME";
			STD__ADD_STRING(var_name);
			LINK__VAR_STRING_CTRL(sCH__MON_STABLE_HE_CENTER_TIME, var_name);

			//
			var_name = "MON.FAULT.HE.CENTER.STATE";
			STD__ADD_STRING(var_name);
			LINK__VAR_STRING_CTRL(sCH__MON_FAULT_HE_CENTER_STATE, var_name);

			var_name = "MON.FAULT.HE.CENTER.TIME";
			STD__ADD_STRING(var_name);
			LINK__VAR_STRING_CTRL(sCH__MON_FAULT_HE_CENTER_TIME, var_name);
		}
		// He Edge ...
		{
			var_name = "MON.CHANGE.HE.EDGE.STATE";
			STD__ADD_STRING(var_name);
			LINK__VAR_STRING_CTRL(sCH__MON_CHANGE_HE_EDGE_STATE, var_name);

			var_name = "MON.CHANGE.HE.EDGE.TIME";
			STD__ADD_STRING(var_name);
			LINK__VAR_STRING_CTRL(sCH__MON_CHANGE_HE_EDGE_TIME, var_name);

			//
			var_name = "MON.STABLE.HE.EDGE.STATE";
			STD__ADD_STRING(var_name);
			LINK__VAR_STRING_CTRL(sCH__MON_STABLE_HE_EDGE_STATE, var_name);

			var_name = "MON.STABLE.HE.EDGE.TIME";
			STD__ADD_STRING(var_name);
			LINK__VAR_STRING_CTRL(sCH__MON_STABLE_HE_EDGE_TIME, var_name);

			//
			var_name = "MON.FAULT.HE.EDGE.STATE";
			STD__ADD_STRING(var_name);
			LINK__VAR_STRING_CTRL(sCH__MON_FAULT_HE_EDGE_STATE, var_name);

			var_name = "MON.FAULT.HE.EDGE.TIME";
			STD__ADD_STRING(var_name);
			LINK__VAR_STRING_CTRL(sCH__MON_FAULT_HE_EDGE_TIME, var_name);
		}
	}

	// Parameter ...
	{
		// PARA.CENTER ...
		{
			var_name = "TEST.PARA.He.SET_PRESSURE.CENTER";
			STD__ADD_ANALOG_WITH_X_OPTION(var_name, "torr", 1, 0.0, 1000.0, "");
			LINK__VAR_ANALOG_CTRL(aCH__TEST_PARA_He_SET_PRESSURE_CENTER, var_name);

			var_name = "PARA.ESC.CENTER.SET_VOLTAGE";
			STD__ADD_STRING(var_name);
			LINK__VAR_STRING_CTRL(sCH__PARA_ESC_CENTER_SET_VOLTAGE, var_name);

			var_name = "PARA.ESC.CENTER.CURRENT_LIMIT";
			STD__ADD_STRING(var_name);
			LINK__VAR_STRING_CTRL(sCH__PARA_ESC_CENTER_CURRENT_LIMIT, var_name);

			//
			var_name = "PARA.He.SET_PRESSURE.CENTER";
			STD__ADD_STRING(var_name);
			LINK__VAR_STRING_CTRL(sCH__PARA_He_SET_PRESSURE_CENTER, var_name);
		}
		// PARA.EDGE ...
		{
			var_name = "TEST.PARA.He.SET_PRESSURE.EDGE";
			STD__ADD_ANALOG_WITH_X_OPTION(var_name, "torr", 1, 0.0, 1000.0, "");
			LINK__VAR_ANALOG_CTRL(aCH__TEST_PARA_He_SET_PRESSURE_EDGE, var_name);

			var_name = "PARA.ESC.EDGE.SET_VOLTAGE";
			STD__ADD_STRING(var_name);
			LINK__VAR_STRING_CTRL(sCH__PARA_ESC_EDGE_SET_VOLTAGE, var_name);

			var_name = "PARA.ESC.EDGE.CURRENT_LIMIT";
			STD__ADD_STRING(var_name);
			LINK__VAR_STRING_CTRL(sCH__PARA_ESC_EDGE_CURRENT_LIMIT, var_name);

			//
			var_name = "PARA.He.SET_PRESSURE.EDGE";
			STD__ADD_STRING(var_name);
			LINK__VAR_STRING_CTRL(sCH__PARA_He_SET_PRESSURE_EDGE, var_name);
		}

		// ...
		{
			var_name = "PARA.STABLE.CHECK_REQ";
			STD__ADD_STRING(var_name);
			LINK__VAR_STRING_CTRL(sCH__PARA_STABLE_CHECK_REQ, var_name);

			var_name = "PARA.STABLE.CHECK_MODE";
			STD__ADD_STRING(var_name);
			LINK__VAR_STRING_CTRL(sCH__PARA_STABLE_CHECK_MODE, var_name);
		}
	}

	// ESC Parameter ...
	{
		// ...
		{
			var_name = "CFG.ELECTROSTATIC_CHUCK_TYPE";
			STD__ADD_DIGITAL_WITH_X_OPTION(var_name, "UNIPOLAR BIPOLAR", "");
			LINK__VAR_DIGITAL_CTRL(dCH__CFG_ELECTROSTATIC_CHUCK_TYPE, var_name);

			var_name = "CFG.ESC.VOLTAGE.FULL.SCALE";
			STD__ADD_ANALOG_WITH_X_OPTION(var_name, "V", 1, 0.0, 10000.0, "");
			LINK__VAR_ANALOG_CTRL(aCH__CFG_ESC_VOLTAGE_FULL_SCALE, var_name);

			//
			var_name = "CFG.STABLE_TIME.FOR.ESC_HELIUM_SETPOINT_CHANGE";
			STD__ADD_ANALOG_WITH_X_OPTION(var_name, "sec", 1, 1.0, 10.0, "");
			LINK__VAR_ANALOG_CTRL(aCH__CFG_STABLE_TIME_FOR_ESC_HELIUM_SETPOINT_CHANGE, var_name);

			var_name = "CFG.ERROR_TIMEOUT.FOR.ESC_HELIUM_STATE";
			STD__ADD_ANALOG_WITH_X_OPTION(var_name, "sec", 1, 1.0, 10.0, "");
			LINK__VAR_ANALOG_CTRL(aCH__CFG_ERROR_TIMEOUT_FOR_ESC_HELIUM_STATE, var_name);

			var_name = "CFG.CHECKING_TIME.FOR.ESC_HELIUM_STABLE";
			STD__ADD_ANALOG_WITH_X_OPTION(var_name, "sec", 1, 1.0, 10.0, "");
			LINK__VAR_ANALOG_CTRL(aCH__CFG_CHECKING_TIME_FOR_ESC_HELIUM_STABLE, var_name);
		}

		// Center ...
		{
			var_name = "CFG.ESC.CENTER.VOLTAGE.MAX.SETPOINT.FOR.CHUCKING";
			STD__ADD_ANALOG_WITH_X_OPTION(var_name, "V", 1, -10000.0, 10000.0, "");
			LINK__VAR_ANALOG_CTRL(aCH__CFG_ESC_CENTER_VOLTAGE_MAX_SETPOINT_FOR_CHUCKING, var_name);

			var_name = "CFG.ESC.CENTER.VOLTAGE.MIN.SETPOINT.FOR.CHUCKING";
			STD__ADD_ANALOG_WITH_X_OPTION(var_name, "V", 1, -10000.0, 10000.0, "");
			LINK__VAR_ANALOG_CTRL(aCH__CFG_ESC_CENTER_VOLTAGE_MIN_SETPOINT_FOR_CHUCKING, var_name);

			var_name = "CFG.ESC.CENTER.VOLTAGE_THRESHOLD";
			STD__ADD_ANALOG_WITH_X_OPTION(var_name, "V", 1, -10000.0, 10000.0, "");
			LINK__VAR_ANALOG_CTRL(aCH__CFG_ESC_CENTER_VOLTAGE_THRESHOLD, var_name);

			var_name = "CFG.ESC.CENTER.CURRENT_LIMIT";
			STD__ADD_ANALOG_WITH_X_OPTION(var_name, "mA", 1, 0.3, 1.0, "");
			LINK__VAR_ANALOG_CTRL(aCH__CFG_ESC_CENTER_CURRENT_LIMIT, var_name);

			var_name = "CFG.ESC.CENTER.VOLTAGE.MAX.SETPOINT.FOR.DECHUCKING";
			STD__ADD_ANALOG_WITH_X_OPTION(var_name, "V", 1, -10000.0, 10000.0, "");
			LINK__VAR_ANALOG_CTRL(aCH__CFG_ESC_CENTER_VOLTAGE_MAX_SETPOINT_FOR_DECHUCKING, var_name);
		}
		// Edge ...
		{
			var_name = "CFG.ESC.EDGE.VOLTAGE.MAX.SETPOINT.FOR.CHUCKING";
			STD__ADD_ANALOG_WITH_X_OPTION(var_name, "V", 1, -10000.0, 10000.0, "");
			LINK__VAR_ANALOG_CTRL(aCH__CFG_ESC_EDGE_VOLTAGE_MAX_SETPOINT_FOR_CHUCKING, var_name);

			var_name = "CFG.ESC.EDGE.VOLTAGE.MIN.SETPOINT.FOR.CHUCKING";
			STD__ADD_ANALOG_WITH_X_OPTION(var_name, "V", 1, -10000.0, 10000.0, "");
			LINK__VAR_ANALOG_CTRL(aCH__CFG_ESC_EDGE_VOLTAGE_MIN_SETPOINT_FOR_CHUCKING, var_name);

			var_name = "CFG.ESC.EDGE.VOLTAGE_THRESHOLD";
			STD__ADD_ANALOG_WITH_X_OPTION(var_name, "V", 1, -10000.0, 10000.0, "");
			LINK__VAR_ANALOG_CTRL(aCH__CFG_ESC_EDGE_VOLTAGE_THRESHOLD, var_name);

			var_name = "CFG.ESC.EDGE.CURRENT_LIMIT";
			STD__ADD_ANALOG_WITH_X_OPTION(var_name, "mA", 1, 0.3, 1.0, "");
			LINK__VAR_ANALOG_CTRL(aCH__CFG_ESC_EDGE_CURRENT_LIMIT, var_name);

			var_name = "CFG.ESC.EDGE.VOLTAGE.MAX.SETPOINT.FOR.DECHUCKING";
			STD__ADD_ANALOG_WITH_X_OPTION(var_name, "V", 1, -10000.0, 10000.0, "");
			LINK__VAR_ANALOG_CTRL(aCH__CFG_ESC_EDGE_VOLTAGE_MAX_SETPOINT_FOR_DECHUCKING, var_name);
		}
	}

	// Helium Parameter ...
	{
		var_name = "CFG.He_PRESSURE.FULL.SCALE";
		STD__ADD_ANALOG_WITH_X_OPTION(var_name, "torr", 1, 0.0, 100.0, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_He_PRESSURE_FULL_SCALE, var_name);

		var_name = "CFG.He_FLOW.FULL.SCALE";
		STD__ADD_ANALOG_WITH_X_OPTION(var_name, "sccm", 1, 0.0, 1000.0, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_He_FLOW_FULL_SCALE, var_name);

		var_name = "CFG.He_PRESSURE.MAX.SETPOINT";
		STD__ADD_ANALOG_WITH_X_OPTION(var_name, "torr", 1, 0.0, 100.0, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_He_PRESSURE_MAX_SETPOINT, var_name);

		//
		var_name = "CFG.He_CENTER.PRESSURE_THRESHOLD.MIN.WARNING";
		STD__ADD_ANALOG_WITH_X_OPTION(var_name, "%", 1, 0.0, 100.0, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_He_CENTER_PRESSURE_THRESHOLD_MIN_WARNING, var_name);

		var_name = "CFG.He_CENTER.PRESSURE_THRESHOLD.MAX.WARNING";
		STD__ADD_ANALOG_WITH_X_OPTION(var_name, "%", 1, 0.0, 100.0, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_He_CENTER_PRESSURE_THRESHOLD_MAX_WARNING, var_name);

		var_name = "CFG.He_CENTER.PRESSURE_THRESHOLD.MIN.FAULT";
		STD__ADD_ANALOG_WITH_X_OPTION(var_name, "%", 1, 0.0, 100.0, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_He_CENTER_PRESSURE_THRESHOLD_MIN_FAULT, var_name);

		var_name = "CFG.He_CENTER.PRESSURE_THRESHOLD.MAX.FAULT";
		STD__ADD_ANALOG_WITH_X_OPTION(var_name, "%", 1, 0.0, 100.0, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_He_CENTER_PRESSURE_THRESHOLD_MAX_FAULT, var_name);
	}

	// Chuck Step - Parameter ...
	{
		// ESC Voltage.Center ...
		{
			var_name = "CFG.ESC.CENTER.CHUCKING.VOLTAGE.SETPOINT";
			STD__ADD_ANALOG_WITH_X_OPTION(var_name, "V", 1, -10000.0, 10000.0, "");
			LINK__VAR_ANALOG_CTRL(aCH__CFG_ESC_CENTER_CHUCKING_VOLTAGE_SETPOINT, var_name);

			var_name = "CFG.ESC.CENTER.CHUCKING.VOLTAGE.WARNING";
			STD__ADD_ANALOG_WITH_X_OPTION(var_name, "%", 1, 0.0, 100.0, "");
			LINK__VAR_ANALOG_CTRL(aCH__CFG_ESC_CENTER_CHUCKING_VOLTAGE_WARNING, var_name);

			var_name = "CFG.ESC.CENTER.CHUCKING.VOLTAGE.FAULT";
			STD__ADD_ANALOG_WITH_X_OPTION(var_name, "%", 1, 0.0, 100.0, "");
			LINK__VAR_ANALOG_CTRL(aCH__CFG_ESC_CENTER_CHUCKING_VOLTAGE_FAULT, var_name);
		}
		// ESC Voltage.Edge ...
		{
			var_name = "CFG.ESC.EDGE.CHUCKING.VOLTAGE.SETPOINT";
			STD__ADD_ANALOG_WITH_X_OPTION(var_name, "V", 1, -10000.0, 10000.0, "");
			LINK__VAR_ANALOG_CTRL(aCH__CFG_ESC_EDGE_CHUCKING_VOLTAGE_SETPOINT, var_name);

			var_name = "CFG.ESC.EDGE.CHUCKING.VOLTAGE.WARNING";
			STD__ADD_ANALOG_WITH_X_OPTION(var_name, "%", 1, 0.0, 100.0, "");
			LINK__VAR_ANALOG_CTRL(aCH__CFG_ESC_EDGE_CHUCKING_VOLTAGE_WARNING, var_name);

			var_name = "CFG.ESC.EDGE.CHUCKING.VOLTAGE.FAULT";
			STD__ADD_ANALOG_WITH_X_OPTION(var_name, "%", 1, 0.0, 100.0, "");
			LINK__VAR_ANALOG_CTRL(aCH__CFG_ESC_EDGE_CHUCKING_VOLTAGE_FAULT, var_name);
		}

		// HE Center ...
		{
			var_name = "CFG.HE_CENTER.PRESSURE.SETPOINT";
			STD__ADD_ANALOG_WITH_X_OPTION(var_name, "sccm", 1, 0.0, 1000.0, "");
			LINK__VAR_ANALOG_CTRL(aCH__CFG_HE_CENTER_PRESSURE_SETPOINT, var_name);

			var_name = "CFG.HE_CENTER.PRESSURE.WARNING";
			STD__ADD_ANALOG_WITH_X_OPTION(var_name, "%", 1, 0.0, 100.0, "");
			LINK__VAR_ANALOG_CTRL(aCH__CFG_HE_CENTER_PRESSURE_WARNING, var_name);

			var_name = "CFG.HE_CENTER.PRESSURE.FAULT";
			STD__ADD_ANALOG_WITH_X_OPTION(var_name, "%", 1, 0.0, 100.0, "");
			LINK__VAR_ANALOG_CTRL(aCH__CFG_HE_CENTER_PRESSURE_FAULT, var_name);

			//
			var_name = "CFG.HE_CENTER.FLOW.MIN.THRESHOLD";
			STD__ADD_ANALOG_WITH_X_OPTION(var_name, "sccm", 1, 0.0, 1000.0, "");
			LINK__VAR_ANALOG_CTRL(aCH__CFG_HE_CENTER_FLOW_MIN_THRESHOLD, var_name);

			var_name = "CFG.HE_CENTER.FLOW.MAX.THRESHOLD";
			STD__ADD_ANALOG_WITH_X_OPTION(var_name, "sccm", 1, 0.0, 1000.0, "");
			LINK__VAR_ANALOG_CTRL(aCH__CFG_HE_CENTER_FLOW_MAX_THRESHOLD, var_name);

			//
			var_name = "MON.HE_CENTER.FLOW.MIN.THRESHOLD";
			STD__ADD_ANALOG_WITH_X_OPTION(var_name, "sccm", 1, 0.0, 1000.0, "");
			LINK__VAR_ANALOG_CTRL(aCH__MON_HE_CENTER_FLOW_MIN_THRESHOLD, var_name);

			var_name = "MON.HE_CENTER.FLOW.MAX.THRESHOLD";
			STD__ADD_ANALOG_WITH_X_OPTION(var_name, "sccm", 1, 0.0, 1000.0, "");
			LINK__VAR_ANALOG_CTRL(aCH__MON_HE_CENTER_FLOW_MAX_THRESHOLD, var_name);

			//
			var_name = "CFG.HE_CENTER.WAFER_MAX_LEAK";
			STD__ADD_ANALOG_WITH_X_OPTION(var_name, "sccm", 1, 0.0, 20.0, "");
			LINK__VAR_ANALOG_CTRL(aCH__CFG_HE_CENTER_WAFER_MAX_LEAK, var_name);
		}
		// HE Edge ...
		{
			var_name = "CFG.HE_EDGE.PRESSURE.SETPOINT";
			STD__ADD_ANALOG_WITH_X_OPTION(var_name, "sccm", 1, 0.0, 1000.0, "");
			LINK__VAR_ANALOG_CTRL(aCH__CFG_HE_EDGE_PRESSURE_SETPOINT, var_name);

			var_name = "CFG.HE_EDGE.PRESSURE.WARNING";
			STD__ADD_ANALOG_WITH_X_OPTION(var_name, "%", 1, 0.0, 100.0, "");
			LINK__VAR_ANALOG_CTRL(aCH__CFG_HE_EDGE_PRESSURE_WARNING, var_name);

			var_name = "CFG.HE_EDGE.PRESSURE.FAULT";
			STD__ADD_ANALOG_WITH_X_OPTION(var_name, "%", 1, 0.0, 100.0, "");
			LINK__VAR_ANALOG_CTRL(aCH__CFG_HE_EDGE_PRESSURE_FAULT, var_name);

			//
			var_name = "CFG.HE_EDGE.FLOW.MIN.THRESHOLD";
			STD__ADD_ANALOG_WITH_X_OPTION(var_name, "sccm", 1, 0.0, 1000.0, "");
			LINK__VAR_ANALOG_CTRL(aCH__CFG_HE_EDGE_FLOW_MIN_THRESHOLD, var_name);

			var_name = "CFG.HE_EDGE.FLOW.MAX.THRESHOLD";
			STD__ADD_ANALOG_WITH_X_OPTION(var_name, "sccm", 1, 0.0, 1000.0, "");
			LINK__VAR_ANALOG_CTRL(aCH__CFG_HE_EDGE_FLOW_MAX_THRESHOLD, var_name);

			//
			var_name = "MON.HE_EDGE.FLOW.MIN.THRESHOLD";
			STD__ADD_ANALOG_WITH_X_OPTION(var_name, "sccm", 1, 0.0, 1000.0, "");
			LINK__VAR_ANALOG_CTRL(aCH__MON_HE_EDGE_FLOW_MIN_THRESHOLD, var_name);

			var_name = "MON.HE_EDGE.FLOW.MAX.THRESHOLD";
			STD__ADD_ANALOG_WITH_X_OPTION(var_name, "sccm", 1, 0.0, 1000.0, "");
			LINK__VAR_ANALOG_CTRL(aCH__MON_HE_EDGE_FLOW_MAX_THRESHOLD, var_name);

			//
			var_name = "CFG.HE_EDGE.WAFER_MAX_LEAK";
			STD__ADD_ANALOG_WITH_X_OPTION(var_name, "sccm", 1, 0.0, 20.0, "");
			LINK__VAR_ANALOG_CTRL(aCH__CFG_HE_EDGE_WAFER_MAX_LEAK, var_name);
		}

		// ...
		{
			var_name = "CFG.CHUCK.SEL";
			STD__ADD_STRING(var_name);
			LINK__VAR_STRING_CTRL(sCH__CFG_CHUCK_SEL, var_name);

			var_name = "CUR.CHUCK.SEL";
			STD__ADD_STRING(var_name);
			LINK__VAR_STRING_CTRL(sCH__CUR_CHUCK_SEL, var_name);
		}

		for(i=0; i<DEF__CHUCK_MODE_SIZE; i++)
		{
			var_name.Format("CFG.HV_OFF.TIME.CHUCK%1d", i);
			STD__ADD_ANALOG_WITH_X_OPTION(var_name, "sec", 1, 0.0, 10.0, "");
			LINK__VAR_ANALOG_CTRL(aCH__CFG_HV_OFF_TIME_CHUCK_X[i], var_name);

			var_name.Format("CFG.HV_ON.TIME.CHUCK%1d", i);
			STD__ADD_ANALOG_WITH_X_OPTION(var_name, "sec", 1, 0.0, 100.0, "");
			LINK__VAR_ANALOG_CTRL(aCH__CFG_HV_ON_TIME_CHUCK_X[i], var_name);

			var_name.Format("CFG.HV_STABLE.TIME.CHUCK%1d", i);
			STD__ADD_ANALOG_WITH_X_OPTION(var_name, "sec", 1, 0.0, 100.0, "");
			LINK__VAR_ANALOG_CTRL(aCH__CFG_HV_STABLE_TIME_CHUCK_X[i], var_name);

			var_name.Format("CFG.HV_HOLDING.TIME.CHUCK%1d", i);
			STD__ADD_ANALOG_WITH_X_OPTION(var_name, "sec", 1, 0.0, 100.0, "");
			LINK__VAR_ANALOG_CTRL(aCH__CFG_HV_HOLDING_TIME_CHUCK_X[i], var_name);

			var_name.Format("CFG.RF_ON.TIME.CHUCK%1d", i);
			STD__ADD_ANALOG_WITH_X_OPTION(var_name, "sec", 1, 0.0, 100.0, "");
			LINK__VAR_ANALOG_CTRL(aCH__CFG_RF_ON_TIME_CHUCK_X[i], var_name);

			var_name.Format("CFG.FINAL_FLOW_STABLE.TIME.CHUCK%1d", i);
			STD__ADD_ANALOG_WITH_X_OPTION(var_name, "sec", 1, 0.0, 100.0, "");
			LINK__VAR_ANALOG_CTRL(aCH__CFG_FINAL_FLOW_STABLE_TIME_CHUCK_X[i], var_name);
		}

		//
		for(i=0; i<DEF__CHUCK_CHART_SIZE; i++)
		{
			var_name.Format("CFG.CHUCK_CHART.TIME%1d", i);
			STD__ADD_STRING(var_name);
			LINK__VAR_STRING_CTRL(sCH__CFG_CHUCK_CHART_TIME[i], var_name);
		}

		// ...
		{
			var_name = "CFG.CHUCK_CHART.TIME_TOTAL";
			STD__ADD_STRING(var_name);
			LINK__VAR_STRING_CTRL(sCH__CFG_CHUCK_CHART_TIME_TOTAL, var_name);

			var_name = "CFG.CHUCK_CHART.TIME_CHUCK";
			STD__ADD_STRING(var_name);
			LINK__VAR_STRING_CTRL(sCH__CFG_CHUCK_CHART_TIME_CHUCK, var_name);

			var_name = "CFG.CHUCK_CHART.TIME_CHUCK1";
			STD__ADD_STRING(var_name);
			LINK__VAR_STRING_CTRL(sCH__CFG_CHUCK_CHART_TIME_CHUCK1, var_name);

			var_name = "CFG.CHUCK_CHART.TIME_CHUCK2";
			STD__ADD_STRING(var_name);
			LINK__VAR_STRING_CTRL(sCH__CFG_CHUCK_CHART_TIME_CHUCK2, var_name);
		}
	}

	// TEST & RESULT ...
	{
		// TEST START ...
		{
			var_name = "TEST.CH1.ESC.CHUCKING.VOLTAGE.SETPOINT.START";
			STD__ADD_STRING(var_name);
			LINK__VAR_STRING_CTRL(sCH__TEST_CH1_ESC_CHUCKING_VOLTAGE_SETPOINT_START, var_name);

			var_name = "TEST.CH2.ESC.CHUCKING.VOLTAGE.SETPOINT.START";
			STD__ADD_STRING(var_name);
			LINK__VAR_STRING_CTRL(sCH__TEST_CH2_ESC_CHUCKING_VOLTAGE_SETPOINT_START, var_name);

			//
			var_name = "TEST.HE_CENTER.PRESSURE.SETPOINT.START";
			STD__ADD_STRING(var_name);
			LINK__VAR_STRING_CTRL(sCH__TEST_HE_CENTER_PRESSURE_SETPOINT_START, var_name);
		}

		// RESULT POINT1 ...
		{
			var_name = "RESULT.CH1.ESC.CHUCKING.VOLTAGE.READING.POINT1";
			STD__ADD_STRING(var_name);
			LINK__VAR_STRING_CTRL(sCH__RESULT_CH1_ESC_CHUCKING_VOLTAGE_READING_POINT1, var_name);

			var_name = "RESULT.CH1.ESC.CHUCKING.CURRENT.READING.POINT1";
			STD__ADD_STRING(var_name);
			LINK__VAR_STRING_CTRL(sCH__RESULT_CH1_ESC_CHUCKING_CURRENT_READING_POINT1, var_name);

			//
			var_name = "RESULT.CH2.ESC.CHUCKING.VOLTAGE.READING.POINT1";
			STD__ADD_STRING(var_name);
			LINK__VAR_STRING_CTRL(sCH__RESULT_CH2_ESC_CHUCKING_VOLTAGE_READING_POINT1, var_name);

			var_name = "RESULT.CH2.ESC.CHUCKING.CURRENT.READING.POINT1";
			STD__ADD_STRING(var_name);
			LINK__VAR_STRING_CTRL(sCH__RESULT_CH2_ESC_CHUCKING_CURRENT_READING_POINT1, var_name);

			//
			var_name = "RESULT.HE_CENTER.PRESSURE.READING.POINT1";
			STD__ADD_STRING(var_name);
			LINK__VAR_STRING_CTRL(sCH__RESULT_HE_CENTER_PRESSURE_READING_POINT1, var_name);

			var_name = "RESULT.HE_CENTER.FLOW.READING.POINT1";
			STD__ADD_STRING(var_name);
			LINK__VAR_STRING_CTRL(sCH__RESULT_HE_CENTER_FLOW_READING_POINT1, var_name);

			//
			var_name = "RESULT.HE_EDGE.PRESSURE.READING.POINT1";
			STD__ADD_STRING(var_name);
			LINK__VAR_STRING_CTRL(sCH__RESULT_HE_EDGE_PRESSURE_READING_POINT1, var_name);

			var_name = "RESULT.HE_EDGE.FLOW.READING.POINT1";
			STD__ADD_STRING(var_name);
			LINK__VAR_STRING_CTRL(sCH__RESULT_HE_EDGE_FLOW_READING_POINT1, var_name);
		}

		// RESULT POINT2 ...
		{
			var_name = "RESULT.CH1.ESC.CHUCKING.VOLTAGE.READING.POINT2";
			STD__ADD_STRING(var_name);
			LINK__VAR_STRING_CTRL(sCH__RESULT_CH1_ESC_CHUCKING_VOLTAGE_READING_POINT2, var_name);

			var_name = "RESULT.CH1.ESC.CHUCKING.CURRENT.READING.POINT2";
			STD__ADD_STRING(var_name);
			LINK__VAR_STRING_CTRL(sCH__RESULT_CH1_ESC_CHUCKING_CURRENT_READING_POINT2, var_name);

			//
			var_name = "RESULT.CH2.ESC.CHUCKING.VOLTAGE.READING.POINT2";
			STD__ADD_STRING(var_name);
			LINK__VAR_STRING_CTRL(sCH__RESULT_CH2_ESC_CHUCKING_VOLTAGE_READING_POINT2, var_name);

			var_name = "RESULT.CH2.ESC.CHUCKING.CURRENT.READING.POINT2";
			STD__ADD_STRING(var_name);
			LINK__VAR_STRING_CTRL(sCH__RESULT_CH2_ESC_CHUCKING_CURRENT_READING_POINT2, var_name);

			//
			var_name = "RESULT.HE_CENTER.PRESSURE.READING.POINT2";
			STD__ADD_STRING(var_name);
			LINK__VAR_STRING_CTRL(sCH__RESULT_HE_CENTER_PRESSURE_READING_POINT2, var_name);

			var_name = "RESULT.HE_CENTER.FLOW.READING.POINT2";
			STD__ADD_STRING(var_name);
			LINK__VAR_STRING_CTRL(sCH__RESULT_HE_CENTER_FLOW_READING_POINT2, var_name);

			//
			var_name = "RESULT.HE_EDGE.PRESSURE.READING.POINT2";
			STD__ADD_STRING(var_name);
			LINK__VAR_STRING_CTRL(sCH__RESULT_HE_EDGE_PRESSURE_READING_POINT2, var_name);

			var_name = "RESULT.HE_EDGE.FLOW.READING.POINT2";
			STD__ADD_STRING(var_name);
			LINK__VAR_STRING_CTRL(sCH__RESULT_HE_EDGE_FLOW_READING_POINT2, var_name);
		}

		//
		for(i=0; i<DEF__CHUCK_CHART_SIZE; i++)
		{
			var_name.Format("TEST.CHUCK_CHART.TIME%1d", i);
			STD__ADD_STRING(var_name);
			LINK__VAR_STRING_CTRL(sCH__TEST_CHUCK_CHART_TIME[i], var_name);
		}

		var_name = "TEST.CHUCK_CHART.TIME_TOTAL";
		STD__ADD_STRING(var_name);
		LINK__VAR_STRING_CTRL(sCH__TEST_CHUCK_CHART_TIME_TOTAL, var_name);

		var_name = "TEST.CHUCK_CHART.TIME_CHUCK1";
		STD__ADD_STRING(var_name);
		LINK__VAR_STRING_CTRL(sCH__TEST_CHUCK_CHART_TIME_CHUCK1, var_name);

		var_name = "TEST.CHUCK_CHART.TIME_CHUCK2";
		STD__ADD_STRING(var_name);
		LINK__VAR_STRING_CTRL(sCH__TEST_CHUCK_CHART_TIME_CHUCK2, var_name);

		var_name = "TEST.CHUCK_CHART.TIME_CHUCK";
		STD__ADD_STRING(var_name);
		LINK__VAR_STRING_CTRL(sCH__TEST_CHUCK_CHART_TIME_CHUCK, var_name);

		//
		for(i=0; i<DEF__CHUCK_CHART_SIZE; i++)
		{
			var_name.Format("RESULT.CHUCK_CHART.TIME%1d", i);
			STD__ADD_STRING(var_name);
			LINK__VAR_STRING_CTRL(sCH__RESULT_CHUCK_CHART_TIME[i], var_name);
		}

		var_name = "RESULT.CHUCK_CHART.TIME_TOTAL";
		STD__ADD_STRING(var_name);
		LINK__VAR_STRING_CTRL(sCH__RESULT_CHUCK_CHART_TIME_TOTAL, var_name);

		var_name = "RESULT.CHUCK_CHART.TIME_CHUCK1";
		STD__ADD_STRING(var_name);
		LINK__VAR_STRING_CTRL(sCH__RESULT_CHUCK_CHART_TIME_CHUCK1, var_name);

		var_name = "RESULT.CHUCK_CHART.TIME_CHUCK2";
		STD__ADD_STRING(var_name);
		LINK__VAR_STRING_CTRL(sCH__RESULT_CHUCK_CHART_TIME_CHUCK2, var_name);

		var_name = "RESULT.CHUCK_CHART.TIME_CHUCK";
		STD__ADD_STRING(var_name);
		LINK__VAR_STRING_CTRL(sCH__RESULT_CHUCK_CHART_TIME_CHUCK, var_name);

		//
		var_name = "RESULT.CHUCK_CHART.TEST_DATE";
		STD__ADD_STRING(var_name);
		LINK__VAR_STRING_CTRL(sCH__RESULT_CHUCK_CHART_TEST_DATE, var_name);

		var_name = "RESULT.CHUCK_CHART.TEST_MODE";
		STD__ADD_STRING(var_name);
		LINK__VAR_STRING_CTRL(sCH__RESULT_CHUCK_CHART_TEST_MODE, var_name);

		var_name = "RESULT.CHUCK_CHART.TEST_RESULT";
		STD__ADD_STRING(var_name);
		LINK__VAR_STRING_CTRL(sCH__RESULT_CHUCK_CHART_TEST_RESULT, var_name);

		var_name = "RESULT.CHUCK_CHART.MAIN_MSG";
		STD__ADD_STRING(var_name);
		LINK__VAR_STRING_CTRL(sCH__RESULT_CHUCK_CHART_MAIN_MSG, var_name);

		var_name = "RESULT.CHUCK_CHART.SUB_MSG";
		STD__ADD_STRING(var_name);
		LINK__VAR_STRING_CTRL(sCH__RESULT_CHUCK_CHART_SUB_MSG, var_name);

		//
		var_name = "RESULT.HE_CENTER.WAFER_LEAK_CHECK.RESULT";
		STD__ADD_STRING(var_name);
		LINK__VAR_STRING_CTRL(sCH__RESULT_HE_CENTER_WAFER_LEAK_CHECK_RESULT, var_name);

		var_name = "TEST.HE_CENTER.WAFER_LEAK_CHECK.REF";
		STD__ADD_STRING(var_name);
		LINK__VAR_STRING_CTRL(sCH__TEST_HE_CENTER_WAFER_LEAK_CHECK_REF, var_name);
	}

	// Config ...
	{				
		var_name = "CFG.He_DUMP_TIME.BEFORE_DECHUCK";
		STD__ADD_ANALOG_WITH_X_OPTION(var_name, "sec", 1, 0.0, 60.0, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_He_DUMP_TIME_BEFORE_DECHUCK, var_name);

		var_name = "CFG.ESC.POWER.ZERO.VOLTAGE.READING.NOISE.RANGE";
		STD__ADD_ANALOG_WITH_X_OPTION(var_name, "V", 1, 0.0, 100.0, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_ESC_POWER_ZERO_VOLTAGE_READING_NOISE_RANGE, var_name);

		var_name = "CFG.ESC.POWER.ZERO.CURRENT.READING.NOISE.RANGE";
		STD__ADD_ANALOG_WITH_X_OPTION(var_name, "mA", 1, 0.0, 100.0, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_ESC_POWER_ZERO_CURRENT_READING_NOISE_RANGE, var_name);

		// During HW Checking ...
		{
			var_name = "CFG.HW_CHECK.USE.DURING_INITIAL";
			STD__ADD_DIGITAL_WITH_X_OPTION(var_name, APP_DSP__ENABLE_DISABLE, "");
			LINK__VAR_DIGITAL_CTRL(dCH__CFG_HW_CHECK_USE_DURING_INITIAL, var_name);

			// Center ...
			{
				var_name = "CFG.HE_CENTER.PRESSURE.FOR.HW_CHECK";
				STD__ADD_ANALOG_WITH_X_OPTION(var_name, "torr", 1, 0, 100, "");
				LINK__VAR_ANALOG_CTRL(aCH__CFG_HE_CENTER_PRESSURE_FOR_HW_CHECK, var_name);

				var_name = "CFG.HE_CENTER.BYPASS_FLOW.FOR.HW_CHECK";
				STD__ADD_ANALOG_WITH_X_OPTION(var_name, "sccm", 1, 0, 100, "");
				LINK__VAR_ANALOG_CTRL(aCH__CFG_HE_CENTER_BYPASS_FLOW_FOR_HW_CHECK, var_name);
			}
			// Edge ...
			{
				var_name = "CFG.HE_EDGE.PRESSURE.FOR.HW_CHECK";
				STD__ADD_ANALOG_WITH_X_OPTION(var_name, "torr", 1, 0, 100, "");
				LINK__VAR_ANALOG_CTRL(aCH__CFG_HE_EDGE_PRESSURE_FOR_HW_CHECK, var_name);

				var_name = "CFG.HE_EDGE.BYPASS_FLOW.FOR.HW_CHECK";
				STD__ADD_ANALOG_WITH_X_OPTION(var_name, "sccm", 1, 0, 100, "");
				LINK__VAR_ANALOG_CTRL(aCH__CFG_HE_EDGE_BYPASS_FLOW_FOR_HW_CHECK, var_name);
			}

			var_name = "CFG.HE.FLOW.ERROR.RANGE.FOR.HW_CHECK";
			STD__ADD_ANALOG_WITH_X_OPTION(var_name, "sccm", 1, 0.1, 5.0, "");
			LINK__VAR_ANALOG_CTRL(aCH__CFG_HE_FLOW_ERROR_RANGE_FOR_HW_CHECK, var_name);

			var_name = "CFG.HE.STABLE.TIME.FOR.HW_CHECK";
			STD__ADD_ANALOG_WITH_X_OPTION(var_name, "sec", 0, 0, 10, "");
			LINK__VAR_ANALOG_CTRL(aCH__CFG_HE_STABLE_TIME_FOR_HW_CHECK, var_name);
		}

		// Dechuck Verify ...
		{
			var_name = "CFG.He.DECHUCK.CHECK.APPLY";
			STD__ADD_DIGITAL_WITH_X_OPTION(var_name, APP_DSP__DISABLE_ENABLE, "");
			LINK__VAR_DIGITAL_CTRL(dCH__CFG_He_DECHUCK_CHECK_APPLY, var_name);

			var_name = "CFG.HE.MINIMUM_LEAK.FOR.DECHUCK_VERIFY";
			STD__ADD_ANALOG_WITH_X_OPTION(var_name, "sccm", 1, 0.0, 100.0, "");
			LINK__VAR_ANALOG_CTRL(aCH__CFG_HE_MINIMUM_LEAK_FOR_DECHUCK_VERIFY, var_name);

			//
			var_name = "CFG.HE_CENTER.PRESSURE.DURING_DECHUCK_VERIFY";
			STD__ADD_ANALOG_WITH_X_OPTION(var_name, "torr", 1, 0.0, 1000.0, "");
			LINK__VAR_ANALOG_CTRL(aCH__CFG_HE_CENTER_PRESSURE_DURING_DECHUCK_VERIFY, var_name);

			var_name = "CFG.HE_EDGE.PRESSURE.DURING_DECHUCK_VERIFY";
			STD__ADD_ANALOG_WITH_X_OPTION(var_name, "torr", 1, 0.0, 1000.0, "");
			LINK__VAR_ANALOG_CTRL(aCH__CFG_HE_EDGE_PRESSURE_DURING_DECHUCK_VERIFY, var_name);

			//
			var_name = "CUR.HE_CENTER.BYPASS_FLOW.FOR.DECHUCK_VERIFY";
			STD__ADD_STRING(var_name);
			LINK__VAR_STRING_CTRL(sCH__CUR_HE_CENTER_BYPASS_FLOW_FOR_DECHUCK_VERIFY, var_name);

			var_name = "CUR.HE_EDGE.BYPASS_FLOW.FOR.DECHUCK_VERIFY";
			STD__ADD_STRING(var_name);
			LINK__VAR_STRING_CTRL(sCH__CUR_HE_EDGE_BYPASS_FLOW_FOR_DECHUCK_VERIFY, var_name);

			//
			var_name = "CFG.HE.BYPASS_FLOW.STABLE.TIME.FOR.DECHUCK_VERIFY";
			STD__ADD_ANALOG_WITH_X_OPTION(var_name, "sec", 1, 0.0, 60.0, "");
			LINK__VAR_ANALOG_CTRL(aCH__CFG_HE_BYPASS_FLOW_STABLE_TIME_FOR_DECHUCK_VERIFY, var_name);

			var_name = "CFG.HE.FINAL_FLOW.STABLE.TIME.FOR.DECHUCK_VERIFY";
			STD__ADD_ANALOG_WITH_X_OPTION(var_name, "sec", 1, 0.0, 60.0, "");
			LINK__VAR_ANALOG_CTRL(aCH__CFG_HE_FINAL_FLOW_STABLE_TIME_FOR_DECHUCK_VERIFY, var_name);
		}

		// ...
		{
			int k;

			for(k=0; k<DEF__DECHUCK_MODE_SIZE; k++)
			{
				for(i=0; i<DEF_DECHUCK__STEP_SIZE; i++)
				{
					var_name.Format("CFG.CENTER.DECHUCK%1d.STEP%1d.VOLT", k,i+1);
					STD__ADD_ANALOG_WITH_X_OPTION(var_name, "V", 0, -1000, 1000, "");
					LINK__VAR_ANALOG_CTRL(aCH__CFG_CENTER_DECHUCK_X__STEPx_VOLT[k][i], var_name);

					var_name.Format("CFG.EDGE.DECHUCK%1d.STEP%1d.VOLT", k,i+1);
					STD__ADD_ANALOG_WITH_X_OPTION(var_name, "V", 0, -1000, 1000, "");
					LINK__VAR_ANALOG_CTRL(aCH__CFG_EDGE_DECHUCK_X__STEPx_VOLT[k][i], var_name);

					var_name.Format("CFG.DECHUCK%1d.STEP%1d.TIME", k,i+1);
					STD__ADD_ANALOG_WITH_X_OPTION(var_name, "sec", 1, 0.0, 10, "");
					LINK__VAR_ANALOG_CTRL(aCH__CFG_DECHUCK_X__STEPx_TIME[k][i], var_name);
				}

				// ...
				{
					var_name.Format("CFG.CENTER.DECHUCK%1d.LAST.VOLT", k);
					STD__ADD_ANALOG_WITH_X_OPTION(var_name, "V", 0, -100.0, 100.0, "");
					LINK__VAR_ANALOG_CTRL(aCH__CFG_CENTER_DECHUCK_X__LAST_VOLT[k], var_name);

					var_name.Format("CFG.EDGE.DECHUCK%1d.LAST.VOLT", k);
					STD__ADD_ANALOG_WITH_X_OPTION(var_name, "V", 0, -100.0, 100.0, "");
					LINK__VAR_ANALOG_CTRL(aCH__CFG_EDGE_DECHUCK_X__LAST_VOLT[k], var_name);

					var_name.Format("CFG.DECHUCK%1d.LAST.TIME", k);
					STD__ADD_ANALOG_WITH_X_OPTION(var_name, "sec", 1, 0.0, 100.0, "");
					LINK__VAR_ANALOG_CTRL(aCH__CFG_DECHUCK_X__LAST_TIME[k], var_name);
				}
			}
		}

		// ...
	}

	// Recipe Parameter ...
	{
		var_name = "RCP.STABLE.CHECK_COUNT";
		STD__ADD_STRING(var_name);
		LINK__VAR_STRING_CTRL(sCH__RCP_STABLE_CHECK_COUNT, var_name);

		//
		var_name = "RCP.He_CENTER.PRESSURE_SETPOINT.TORR";
		STD__ADD_STRING(var_name);
		LINK__VAR_STRING_CTRL(sCH__RCP_He_CENTER_PRESSURE_SETPOINT_TORR, var_name);

		var_name = "RCP.He_EDGE.PRESSURE_SETPOINT.TORR";
		STD__ADD_STRING(var_name);
		LINK__VAR_STRING_CTRL(sCH__RCP_He_EDGE_PRESSURE_SETPOINT_TORR, var_name);

		//
		var_name = "RCP.He_CENTER.ZONE.FLOW.MAX.THRESHOLD";
		STD__ADD_STRING(var_name);
		LINK__VAR_STRING_CTRL(sCH__RCP_He_CENTER_FLOW_MAX_THRESHOLD, var_name);

		var_name = "RCP.He_CENTER.ZONE.FLOW.MIN.THRESHOLD";
		STD__ADD_STRING(var_name);
		LINK__VAR_STRING_CTRL(sCH__RCP_He_CENTER_FLOW_MIN_THRESHOLD, var_name);

		//
		var_name = "RCP.He_EDGE.ZONE.FLOW.MAX.THRESHOLD";
		STD__ADD_STRING(var_name);
		LINK__VAR_STRING_CTRL(sCH__RCP_He_EDGE_FLOW_MAX_THRESHOLD, var_name);

		var_name = "RCP.He_EDGE.ZONE.FLOW.MIN.THRESHOLD";
		STD__ADD_STRING(var_name);
		LINK__VAR_STRING_CTRL(sCH__RCP_He_EDGE_FLOW_MIN_THRESHOLD, var_name);
	}

	// ...
	{
		p_variable->Add__MONITORING_PROC(1.0, MON_ID__REQ_CTRL);
		p_variable->Add__MONITORING_PROC(1.0, MON_ID__SYS_INFO);
		
		p_variable->Add__MONITORING_PROC(1.0, MON_ID__ESC_STABLE_CHECK);
		p_variable->Add__MONITORING_PROC(1.0, MON_ID__HELIUM_STABLE_CHECK);
	}
	return 1;
}


// ...
#define  ACT__CLEAR								\
l_act.RemoveAll();								\
l_act.Add(STR__CLEAR);

#define  ACT__RETRY_ABORT						\
l_act.RemoveAll();								\
l_act.Add(STR__RETRY);							\
l_act.Add(STR__ABORT);


int CObj__ESC_IO::__DEFINE__ALARM(p_alarm)
{
	DECLARE__ALARM;

	// ...
	CString title;
	title.Format("%s - ",sObject_Name);

	CString alarm_title;
	CString alarm_msg;
	CStringArray l_act;
	int alarm_id;

	// ...
	{
		alarm_id = ALID__ESC_CHUCK_STATUS__UNKNOWN;

		alarm_title  = title;
		alarm_title += "ESC Chuck Status is Unknown !";

		alarm_msg  = "";
		alarm_msg += "Please, check current chuck-status ! \n";

		ACT__RETRY_ABORT;

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	// ...
	{
		alarm_id = ALID__ESC_CHUCK_ERROR__PRESSURE_NOT_VAC;

		alarm_title  = title;
		alarm_title += "ESC Chuck Error : Chamber pressure is not vacuum !";

		alarm_msg  = "";
		alarm_msg += "Please, check pressure in chamber ! \n";

		ACT__CLEAR;

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}
	// ...
	{
		alarm_id = ALID__ESC_CHUCK_ERROR__WAFER_NOT_EXIST;

		alarm_title  = title;
		alarm_title += "ESC Chuck Error : There is no wafer !";

		alarm_msg  = "";
		alarm_msg += "Please, check wafer in chamber ! \n";

		ACT__CLEAR;

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	// ESC Center ...
	{
		// ...
		{
			alarm_id = ALID__ESC_CENTER_CHUCK_VOLTAGE__MIN_ERROR;

			alarm_title  = title;
			alarm_title += "ESC Chuck Center Voltage : MIN. Error !";

			alarm_msg  = "";
			alarm_msg += "Please, check esc center config ! \n";

			ACT__CLEAR;

			ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
		}
		// ...
		{
			alarm_id = ALID__ESC_CENTER_CHUCK_VOLTAGE__MAX_ERROR;

			alarm_title  = title;
			alarm_title += "ESC Chuck Center Voltage : MAX. Error !";

			alarm_msg  = "";
			alarm_msg += "Please, check esc center config ! \n";

			ACT__CLEAR;

			ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
		}

		// ...
		{
			alarm_id = ALID__ESC_CENTER_VOLTAGE__WARNING_RANGE;

			alarm_title  = title;
			alarm_title += "ESC_Center voltage is in warning range !";

			alarm_msg  = "";
			alarm_msg += "Please, check ESC_Center voltage ! \n";

			ACT__CLEAR;

			ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
		}
		// ...
		{	
			alarm_id = ALID__ESC_CENTER_VOLTAGE__FAULT_RANGE;

			alarm_title  = title;
			alarm_title += "ESC_Center voltage is in fault range !";

			alarm_msg  = "";
			alarm_msg += "Please, check ESC_Center voltage ! \n";

			ACT__CLEAR;

			ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
		}

		// ...
		{
			alarm_id = ALID__ESC_CENTER_VOLTAGE__HIGH_LIMIT;

			alarm_title  = title;
			alarm_title += "ESC_Center voltage high limit !";

			alarm_msg  = "";
			alarm_msg += "Please, check ESC_Center voltage ! \n";

			ACT__CLEAR;

			ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
		}
		// ...
		{
			alarm_id = ALID__ESC_CENTER_CURRENT__HIGH_LIMIT;

			alarm_title  = title;
			alarm_title += "ESC_Center current high limit !";

			alarm_msg  = "";
			alarm_msg += "Please, check ESC_Center current ! \n";

			ACT__CLEAR;

			ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
		}
	}
	// ESC Edge ...
	{
		// ...
		{
			alarm_id = ALID__ESC_EDGE_CHUCK_VOLTAGE__MIN_ERROR;

			alarm_title  = title;
			alarm_title += "ESC Chuck Edge Voltage : MIN. Error !";

			alarm_msg  = "";
			alarm_msg += "Please, check esc edge config ! \n";

			ACT__CLEAR;

			ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
		}
		// ...
		{
			alarm_id = ALID__ESC_EDGE_CHUCK_VOLTAGE__MAX_ERROR;

			alarm_title  = title;
			alarm_title += "ESC Chuck Edge Voltage : MAX. Error !";

			alarm_msg  = "";
			alarm_msg += "Please, check esc edge config ! \n";

			ACT__CLEAR;

			ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
		}

		// ...
		{
			alarm_id = ALID__ESC_EDGE_VOLTAGE__WARNING_RANGE;

			alarm_title  = title;
			alarm_title += "ESC_Edge voltage is in warning range !";

			alarm_msg  = "";
			alarm_msg += "Please, check ESC_Edge voltage ! \n";

			ACT__CLEAR;

			ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
		}
		// ...
		{	
			alarm_id = ALID__ESC_EDGE_VOLTAGE__FAULT_RANGE;

			alarm_title  = title;
			alarm_title += "ESC_Edge voltage is in fault range !";

			alarm_msg  = "";
			alarm_msg += "Please, check ESC_Edge voltage ! \n";

			ACT__CLEAR;

			ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
		}

		// ...
		{
			alarm_id = ALID__ESC_EDGE_VOLTAGE__HIGH_LIMIT;

			alarm_title  = title;
			alarm_title += "ESC_Edge voltage high limit !";

			alarm_msg  = "";
			alarm_msg += "Please, check ESC_Edge voltage ! \n";

			ACT__CLEAR;

			ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
		}
		// ...
		{
			alarm_id = ALID__ESC_EDGE_CURRENT__HIGH_LIMIT;

			alarm_title  = title;
			alarm_title += "ESC_Edge current high limit !";

			alarm_msg  = "";
			alarm_msg += "Please, check ESC_Edge current ! \n";

			ACT__CLEAR;

			ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
		}
	}

	// He Pressure.Center ...
	{

		// ...
		{
			alarm_id = ALID__HE_CENTER_PRESSURE_WARNING;

			alarm_title  = title;
			alarm_title += "He Center Pressure Warning !";

			alarm_msg  = "";
			alarm_msg += "Please, check he center pressure ! \n";

			ACT__CLEAR;

			ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
		}	

		// ...
		{
			alarm_id = ALID__HE_CENTER_PRESSURE_FAULT;

			alarm_title  = title;
			alarm_title += "He Center Pressure Fault !";

			alarm_msg  = "";
			alarm_msg += "Please, check he center pressure ! \n";

			ACT__CLEAR;

			ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
		}	
	}
	// He Pressure.Edge ...
	{

		// ...
		{
			alarm_id = ALID__HE_EDGE_PRESSURE_WARNING;

			alarm_title  = title;
			alarm_title += "He Edge Pressure Warning !";

			alarm_msg  = "";
			alarm_msg += "Please, check he edge pressure ! \n";

			ACT__CLEAR;

			ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
		}	

		// ...
		{
			alarm_id = ALID__HE_EDGE_PRESSURE_FAULT;

			alarm_title  = title;
			alarm_title += "He Edge Pressure Fault !";

			alarm_msg  = "";
			alarm_msg += "Please, check he edge pressure ! \n";

			ACT__CLEAR;

			ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
		}	
	}

	// He Flow.Center ...
	{
		// ...
		{
			alarm_id = ALID__HE_CENTER_FLOW_MIN_THRESHOLD;

			alarm_title  = title;
			alarm_title += "He Center Flow Min. Threshold Error !";

			alarm_msg  = "";
			alarm_msg += "Please, check he center flow ! \n";

			ACT__CLEAR;

			ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
		}	
		// ...
		{
			alarm_id = ALID__HE_CENTER_FLOW_MAX_THREASHOLD;

			alarm_title  = title;
			alarm_title += "He Center Flow Max. Threshold Error !";

			alarm_msg  = "";
			alarm_msg += "Please, check he center flow ! \n";

			ACT__CLEAR;

			ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
		}	
	}
	// He Flow.Edge ...
	{
		// ...
		{
			alarm_id = ALID__HE_EDGE_FLOW_MIN_THRESHOLD;

			alarm_title  = title;
			alarm_title += "He Edge Flow Min. Threshold Error !";

			alarm_msg  = "";
			alarm_msg += "Please, check he edge flow ! \n";

			ACT__CLEAR;

			ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
		}	
		// ...
		{
			alarm_id = ALID__HE_EDGE_FLOW_MAX_THREASHOLD;

			alarm_title  = title;
			alarm_title += "He Edge Flow Max. Threshold Error !";

			alarm_msg  = "";
			alarm_msg += "Please, check he edger flow ! \n";

			ACT__CLEAR;

			ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
		}	
	}

	// ...
	{
		alarm_id = ALID__HE_WAFER_MINIMUM_LEAK_SCCM;

		alarm_title  = title;
		alarm_title += "Wafer가 Dechuck된 상태가 아닙니다 !";

		alarm_msg  = "";
		alarm_msg += "Wafer Minimum Leak Error ! \n";
		alarm_msg += "Please, check He flow! \n";

		ACT__CLEAR;

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}	
	// ...
	{
		alarm_id = ALID__HE_WAFER_MAXIMUM_LEAK_SCCM;

		alarm_title  = title;
		alarm_title += "Wafer Maximum Leak Error !";

		alarm_msg  = "";
		alarm_msg += "Please, check He flow ! \n";

		ACT__CLEAR;

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}	

	// ...
	{
		alarm_id = ALID__SHUTTER_NOT_CLOSE;

		alarm_title  = title;
		alarm_title += "Shutter not close !";

		alarm_msg  = "";
		alarm_msg += "Shutter가 닫힌 상태인지? 확인 바랍니다 ! \n";

		ACT__CLEAR;

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}
	// ...
	{
		alarm_id = ALID__SLOT_VALVE_NOT_CLOSE;

		alarm_title  = title;
		alarm_title += "Slot-Valve not close !";

		alarm_msg  = "";
		alarm_msg += "Slot-Valve가 닫힌 상태인지? 확인 바랍니다 ! \n";

		ACT__CLEAR;

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	// ...
	{
		alarm_id = ALID__HE_PRESSURE__MAX_ERROR;

		alarm_title  = title;
		alarm_title += "He pressure Max. error !";

		alarm_msg  = "";
		alarm_msg += "Please, check he pressure ! \n";

		ACT__CLEAR;

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	// ...
	{
		alarm_id = ALID__HE_CENTER_CONFIG_RANGE_ERROR;

		alarm_title  = title;
		alarm_title += "Helium center config range error !";

		alarm_msg  = "";
		alarm_msg += "Please, check helium center flow ! \n";

		alarm_msg += "Helium center flow config condition is as followings : \n";
		alarm_msg += "   1. Helium center pressure is set to 4.0 torr. \n";
		alarm_msg += "   2. Get the flow of helium center bypass. \n";
		alarm_msg += "   3. The flow of helium center bypass must be in (3.1 ~ 3.6) sccm range. \n";

		ACT__CLEAR;

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	// ...
	{
		alarm_id = ALID__HE_SET__ERROR;

		alarm_title  = title;
		alarm_title += "Helium setting error !";

		alarm_msg  = "Process 중에 Helium 설정 값을 변경하는 작업을 할 수 없습니다. \n";
		alarm_msg += "ESC 상태가 \"Chucked\"인 상태에서만 가능합니다. \n";

		ACT__CLEAR;

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	return 1;
}


//-------------------------------------------------------------------------
int CObj__ESC_IO::__INITIALIZE__OBJECT(p_variable,p_ext_obj_create)
{
	CString def_name;
	CString def_data;

	CString ch_name;
	CString obj_name;
	CString var_name;

	// ...
	CCommon_Utility x_utility;
	bool def_check;


	// DB OBJ ...
	{	
		def_name = "OBJ__DB";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, obj_name);

		// ...
		{
			var_name = "CHM.PRESSURE.STATUS";
			LINK__EXT_VAR_STRING_CTRL(sEXT_CH__CHM_PRESSURE_STATUS, obj_name,var_name);

			var_name = "SLOT01.STATUS";
			LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__WAFER_STATUS, obj_name,var_name);

			var_name = "CFG.DECHUCK.CTRL.MODE";
			LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__CFG_DECHUCK_CTRL_MODE, obj_name,var_name);
		}
	}

	// LInk.Shutter_State ...
	{
		def_name = "CH__SHUTTER_STATE";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);

		def_check = x_utility.Check__Link(ch_name);
		bActive__SHUTTER_STATUS = def_check;

		if(def_check)
		{
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
			p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
			LINK__EXT_VAR_STRING_CTRL(sEXT_CH__SHUTTER_STATUS, obj_name,var_name);
		}
	}
	// Link.Slot_Valve_State ...
	{
		def_name = "CH__SLOT_VALVE_STATE";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);

		def_check = x_utility.Check__Link(ch_name);
		bActive__SLOT_VALVE_STATE = def_check;

		if(def_check)
		{
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
			p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
			LINK__EXT_VAR_STRING_CTRL(sEXT_CH__SLOT_VALVE_STATE, obj_name,var_name);
		}
	}

	// LINK Channel ...
	{
		// Config Save ...
		{
			def_name = "CH__CONFIG_SAVE";
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
			p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
			LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__CONFIG_SAVE, obj_name,var_name);
		}

		// CENTER.USE ...
		{
			def_name = "DATA__CENTER_USE";
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name, def_data);
			
			def_check = x_utility.Check__Link(def_data);
			bActive__CENTER_USE      = def_check;
			bActive__CENTER_3WAY_VLV = def_check; 

			if(bActive__CENTER_USE)
			{
				def_name = "DATA__CENTER_3WAY_VALVE";
				p_ext_obj_create->Get__DEF_CONST_DATA(def_name, def_data);
			
				def_check = x_utility.Check__Link(def_data);
				bActive__CENTER_3WAY_VLV = def_check;
			}
		}
		// EDGE.USE ...
		{
			def_name = "DATA__EDGE_USE";
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name, def_data);

			def_check = x_utility.Check__Link(def_data);
			bActive__EDGE_USE      = def_check;
			bActive__EDGE_3WAY_VLV = def_check; 

			if(bActive__EDGE_USE)
			{
				def_name = "DATA__EDGE_3WAY_VALVE";
				p_ext_obj_create->Get__DEF_CONST_DATA(def_name, def_data);

				def_check = x_utility.Check__Link(def_data);
				bActive__EDGE_3WAY_VLV = def_check;
			}
		}

		// ESC IO ...
		{
			// All ...
			{
				def_name = "CH__DO_ESC_ALL_VOLTAGE_POWER";
				p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
				p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
				LINK__EXT_VAR_DIGITAL_CTRL(doEXT_CH__ESC_All_Voltage, obj_name,var_name);
			}

			// Center ...
			if(bActive__CENTER_USE)
			{
				def_name = "CH__AO_ESC_VOLTAGE.CENTER";
				p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
				p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
				LINK__EXT_VAR_ANALOG_CTRL(aoEXT_CH__ESC_Voltage_CENTER, obj_name,var_name);

				def_name = "CH__AI_ESC_VOLTAGE.CENTER";
				p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
				p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
				LINK__EXT_VAR_ANALOG_CTRL(aiEXT_CH__ESC_Voltage_CENTER, obj_name,var_name);

				//
				def_name = "CH__AI_ESC_CURRENT.CENTER";
				p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
				p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
				LINK__EXT_VAR_ANALOG_CTRL(aiEXT_CH__ESC_Current_CENTER, obj_name,var_name);
			}
			// Edge ...
			if(bActive__EDGE_USE)
			{
				def_name = "CH__AO_ESC_VOLTAGE.EDGE";
				p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
				p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
				LINK__EXT_VAR_ANALOG_CTRL(aoEXT_CH__ESC_Voltage_EDGE, obj_name,var_name);

				def_name = "CH__AI_ESC_VOLTAGE.EDGE";
				p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
				p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
				LINK__EXT_VAR_ANALOG_CTRL(aiEXT_CH__ESC_Voltage_EDGE, obj_name,var_name);

				//
				def_name = "CH__AI_ESC_CURRENT.EDGE";
				p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
				p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
				LINK__EXT_VAR_ANALOG_CTRL(aiEXT_CH__ESC_Current_EDGE, obj_name,var_name);
			}
		}

		// He Valve ...
		{
			def_name = "DATA.HE_LINE.TYPE";
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name, def_data);
			
				 if(def_data.CompareNoCase("ICD")  == 0)			iDATA__HE_LINE_TYPE = _HE_LINE_TYPE__ICD;
			else if(def_data.CompareNoCase("FLEX") == 0)			iDATA__HE_LINE_TYPE = _HE_LINE_TYPE__FLEX;
			else													iDATA__HE_LINE_TYPE = _HE_LINE_TYPE__STD;
				
			// Common ...
			{
				def_name = "CH__DO_HE_SIDE_SUPPLY_VLV";
				p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
				p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
				LINK__EXT_VAR_DIGITAL_CTRL(doEXT_CH__He_Side_Supply_Vlv, obj_name,var_name);

				def_name = "CH__DO_HE_EXHAUST_VLV";
				p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
				p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
				LINK__EXT_VAR_DIGITAL_CTRL(doEXT_CH__He_Exhaust_Vlv, obj_name,var_name);			
			}

			// Center ...
			if(bActive__CENTER_USE)
			{
				def_name = "CH__DO_HE_FINAL_OUT_VLV.CENTER";
				p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
				p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
				LINK__EXT_VAR_DIGITAL_CTRL(doEXT_CH__He_Final_Out_Vlv_CENTER, obj_name,var_name);			

				def_name = "CH__DO_HE_FINAL_DUMP_VLV.CENTER";
				p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
				p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
				LINK__EXT_VAR_DIGITAL_CTRL(doEXT_CH__He_Final_Dump_Vlv_CENTER, obj_name,var_name);			

				def_name = "CH__DO_HE_SIDE_DUMP_VLV.CENTER";
				p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
				p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
				LINK__EXT_VAR_DIGITAL_CTRL(doEXT_CH__He_Side_Dump_Vlv_CENTER, obj_name,var_name);

				//
				def_name = "CH__DO_HE_SIDE_EXHAUST_VLV.CENTER";
				p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);

				def_check = x_utility.Check__Link(ch_name);
				bActive__He_Side_Exhaust_Vlv_CENTER = def_check;

				if(def_check)
				{
					p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
					LINK__EXT_VAR_DIGITAL_CTRL(doEXT_CH__He_Side_Exhaust_Vlv_CENTER, obj_name,var_name);
				}
			}
			// Edge ...
			if(bActive__EDGE_USE)
			{
				def_name = "CH__DO_HE_FINAL_OUT_VLV.EDGE";
				p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
				p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
				LINK__EXT_VAR_DIGITAL_CTRL(doEXT_CH__He_Final_Out_Vlv_EDGE, obj_name,var_name);			

				def_name = "CH__DO_HE_FINAL_DUMP_VLV.EDGE";
				p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
				p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
				LINK__EXT_VAR_DIGITAL_CTRL(doEXT_CH__He_Final_Dump_Vlv_EDGE, obj_name,var_name);			

				def_name = "CH__DO_HE_SIDE_DUMP_VLV.EDGE";
				p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
				p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
				LINK__EXT_VAR_DIGITAL_CTRL(doEXT_CH__He_Side_Dump_Vlv_EDGE, obj_name,var_name);

				//
				def_name = "CH__DO_HE_SIDE_EXHAUST_VLV.EDGE";
				p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);

				def_check = x_utility.Check__Link(ch_name);
				bActive__He_Side_Exhaust_Vlv_EDGE = def_check;

				if(def_check)
				{
					p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
					LINK__EXT_VAR_DIGITAL_CTRL(doEXT_CH__He_Side_Exhaust_Vlv_EDGE, obj_name,var_name);
				}
			}
		}

		// He Pressure & Flow ...
		{
			// Center ...
			if(bActive__CENTER_USE)
			{
				def_name = "CH__AO_HE_PRESSURE.CENTER";
				p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
				p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
				LINK__EXT_VAR_ANALOG_CTRL(aoEXT_CH__He_Pressure_CENTER, obj_name,var_name);

				def_name = "CH__AI_HE_PRESSURE.CENTER";
				p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
				p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
				LINK__EXT_VAR_ANALOG_CTRL(aiEXT_CH__He_Pressure_CENTER_IO, obj_name,var_name);

				def_name = "CH__AI_HE_FLOW.CENTER";
				p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
				p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
				LINK__EXT_VAR_ANALOG_CTRL(aiEXT_CH__He_Flow_CENTER_IO, obj_name,var_name);
			}
			// Edge ...
			if(bActive__EDGE_USE)
			{
				def_name = "CH__AO_HE_PRESSURE.EDGE";
				p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
				p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
				LINK__EXT_VAR_ANALOG_CTRL(aoEXT_CH__He_Pressure_EDGE, obj_name,var_name);

				def_name = "CH__AI_HE_PRESSURE.EDGE";
				p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
				p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
				LINK__EXT_VAR_ANALOG_CTRL(aiEXT_CH__He_Pressure_EDGE_IO, obj_name,var_name);

				def_name = "CH__AI_HE_FLOW.EDGE";
				p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
				p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
				LINK__EXT_VAR_ANALOG_CTRL(aiEXT_CH__He_Flow_EDGE_IO, obj_name,var_name);
			}
		}

		// ESC OBJ_IO ...
		{
			def_name = "OBJ__ESC_IO";
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name, obj_name);

			pOBJ_CTRL__ESC_IO = p_ext_obj_create->Create__OBJECT_CTRL(obj_name);

			if(bActive__CENTER_USE)
			{
				def_name = "VAR__CFG_LEAK_CURRENT_LIMIT.CENTER";
				p_ext_obj_create->Get__DEF_CONST_DATA(def_name, var_name);
				LINK__EXT_VAR_ANALOG_CTRL(eaoEXT_CH__ESC_IO__CUR_LIMIT_SETPOINT_CENTER, obj_name,var_name);
			}
			if(bActive__EDGE_USE)
			{
				def_name = "VAR__CFG_LEAK_CURRENT_LIMIT.EDGE";
				p_ext_obj_create->Get__DEF_CONST_DATA(def_name, var_name);
				LINK__EXT_VAR_ANALOG_CTRL(eaoEXT_CH__ESC_IO__CUR_LIMIT_SETPOINT_EDGE, obj_name,var_name);
			}
		}
	}

	// ...
	{
		CString file_name;
		CString log_msg;

		file_name.Format("%s-App.log", sObject_Name);

		log_msg  = "\n\n";
		log_msg += "//------------------------------------------------------------------------";

		xLOG_CTRL->CREATE__SUB_DIRECTORY(sObject_Name);
		xLOG_CTRL->SET__PROPERTY(file_name,24*5,60);

		xLOG_CTRL->DISABLE__TIME_LOG();
		xLOG_CTRL->WRITE__LOG(log_msg);

		xLOG_CTRL->ENABLE__TIME_LOG();
		xLOG_CTRL->WRITE__LOG("   START   \n");
	}

	// ...
	{
		sCH__CFG_CHUCK_SEL->Set__DATA("CHUCK");

		iACTIVE_FLAG = -1;
		iACTIVE__WAFER_LEAK_CHECK = -1;
	}

	// ...
	{
		SCX__SEQ_INFO x_seq_info;

		iActive__SIM_MODE = x_seq_info->Is__SIMULATION_MODE();
	}

	if(iActive__SIM_MODE > 0)
	{
		dCH__MON_CHUCK_STATUS->Set__DATA(STR__DECHUCKED);
	}
	return 1;
}



//-------------------------------------------------------------------------
int CObj__ESC_IO::__CALL__CONTROL_MODE(mode,p_debug,p_variable,p_alarm)
{
	CString log_msg;
	int flag = -1;

	iACTIVE_FLAG = 1;
	iACTIVE__WAFER_LEAK_CHECK = -1;

	// ...
	{
		log_msg.Format("Start ... : [%s]", mode);

		xLOG_CTRL->WRITE__LOG(log_msg);
		sCH__APP_LOG_MSG->Set__DATA(log_msg);

		sCH__APP_LOG_SUB_MSG->Set__DATA("");
	}

	// ...
	{
		     IF__CTRL_MODE(sMODE__INIT)			    flag = Call__INIT(p_variable,p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__TO_DECHUCKED)		flag = Call__TO_DECHUCKED(p_variable,p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__HE_CLOSE)			flag = Call__HE_CLOSE(p_variable,p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__HW_CHECK)			flag = Call__HW_CHECK(p_variable,p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__DECHUCK_VERIFY)   flag = Call__DECHUCK_VERIFY(p_variable,p_alarm);

		ELSE_IF__CTRL_MODE(sMODE__VENT_READY)		flag = Call__VENT_READY(p_variable,p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__PUMP_READY)		flag = Call__PUMP_READY(p_variable,p_alarm);

		ELSE_IF__CTRL_MODE(sMODE__CHUCK_CFG)		flag = Call__CHUCK_OF_CONFIG(p_variable,p_alarm, 0);	
		ELSE_IF__CTRL_MODE(sMODE__CHUCK1_CFG)		flag = Call__CHUCK_OF_CONFIG(p_variable,p_alarm, 1);	
		ELSE_IF__CTRL_MODE(sMODE__CHUCK2_CFG)		flag = Call__CHUCK_OF_CONFIG(p_variable,p_alarm, 2);	

		ELSE_IF__CTRL_MODE(sMODE__CHUCK_TEST)	    flag = Call__CHUCK_OF_PROCESS(p_variable,p_alarm, -1);	
		ELSE_IF__CTRL_MODE(sMODE__CHUCK_PROC)	    flag = Call__CHUCK_OF_PROCESS(p_variable,p_alarm,  0);	
		ELSE_IF__CTRL_MODE(sMODE__CHUCK1_PROC)	    flag = Call__CHUCK_OF_PROCESS(p_variable,p_alarm,  1);	
		ELSE_IF__CTRL_MODE(sMODE__CHUCK2_PROC)	    flag = Call__CHUCK_OF_PROCESS(p_variable,p_alarm,  2);	
		ELSE_IF__CTRL_MODE(sMODE__HE_SET_PROC)	    flag = Call__HE_SET_OF_PROC(p_variable,p_alarm);	

		ELSE_IF__CTRL_MODE(sMODE__DECHUCK_END)
		{
			if(dCH__MON_CHUCK_STATUS->Check__DATA(STR__DECHUCKED) > 0)
			{
				flag = Call__HE_CLOSE(p_variable,p_alarm);
			}
			else
			{
				flag = Call__DECHUCK(p_variable,p_alarm, 0);	
			}
		}
		ELSE_IF__CTRL_MODE(sMODE__DECHUCK)		    flag = Call__DECHUCK(p_variable,p_alarm, 0);	
		ELSE_IF__CTRL_MODE(sMODE__DECHUCK1)		    flag = Call__DECHUCK(p_variable,p_alarm, 1);	
		ELSE_IF__CTRL_MODE(sMODE__DECHUCK2)		    flag = Call__DECHUCK(p_variable,p_alarm, 2);	
	}

	if((flag < 0)||(p_variable->Check__CTRL_ABORT() > 0))
	{
		// ...
		{
			CString err_msg;
			err_msg.Format("Flag(%1d)", flag);

			Fnc__ESC_ABORT(p_variable,p_alarm, err_msg);
		}

		// ...
		{
			log_msg.Format("Aborted ... : [%s]", mode);

			xLOG_CTRL->WRITE__LOG(log_msg);
			sCH__APP_LOG_MSG->Set__DATA(log_msg);
		}
	}
	else
	{
		// ...
		{
			log_msg.Format("Completed ... : [%s]", mode);

			xLOG_CTRL->WRITE__LOG(log_msg);
			sCH__APP_LOG_MSG->Set__DATA(log_msg);
			sCH__APP_LOG_SUB_MSG->Set__DATA("");
		}
	}

	iACTIVE_FLAG = -1;
	return flag;
}

int CObj__ESC_IO::__CALL__MONITORING(id,p_variable,p_alarm)
{
	switch(id)
	{
		case MON_ID__REQ_CTRL:					Mon__REQ_CTRL(p_variable,p_alarm);				break;
		case MON_ID__SYS_INFO:					Mon__SYS_INFO(p_variable,p_alarm);				break;

		case MON_ID__ESC_STABLE_CHECK:			Mon__ESC_STABLE_CHECK(p_variable,p_alarm);		break;
		case MON_ID__HELIUM_STABLE_CHECK:		Mon__HELIUM_STABLE_CHECK(p_variable,p_alarm);	break;
	}

	return 1;
}
