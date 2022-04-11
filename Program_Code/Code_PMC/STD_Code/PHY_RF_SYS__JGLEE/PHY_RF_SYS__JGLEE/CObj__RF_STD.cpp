#include "StdAfx.h"
#include "CObj__RF_STD.h"

#include "CCommon_Utility.h"


//-------------------------------------------------------------------------
CObj__RF_STD::CObj__RF_STD()
{

}
CObj__RF_STD::~CObj__RF_STD()
{

}

//-------------------------------------------------------------------------
int CObj__RF_STD::__DEFINE__CONTROL_MODE(obj,l_mode)
{
	sObject_Name = obj;

	// ...
	{
		ADD__CTRL_VAR(sMODE__INIT,		"INIT");

		ADD__CTRL_VAR(sMODE__OFF,	    "OFF");
		ADD__CTRL_VAR(sMODE__QUICK_OFF, "QUICK_OFF");

		ADD__CTRL_VAR(sMODE__SET_POWER,	"SET_POWER");

		ADD__CTRL_VAR(sMODE__REMOTE,	"REMOTE");
		ADD__CTRL_VAR(sMODE__LOCAL,		"LOCAL");
	}
	return 1;
}
int CObj__RF_STD::__DEFINE__VERSION_HISTORY(version)
{

	return 1;
}


// ...
#define MON_ID__STATE_CHECK						1
#define MON_ID__INTERLOCK_CHECK					2
#define MON_ID__ERROR_CHECK						3


int CObj__RF_STD::__DEFINE__VARIABLE_STD(p_variable)
{
	DECLARE__STD_VARIABLE;

	// ...
	CCommon_Error__DEF_VARIABLE m_err_def_variable;
	p_variable->Link__DEF_VARIABLE__ERROR_FEEDBACK(&m_err_def_variable);

	// ...
	CString str_name;
	CString item_list;
	int i;

	// OBJ ...
	{
		str_name = "OBJ.MSG";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__OBJ_MSG, str_name);
	}

	// PARA : COMMON ...
	{
		str_name = "PARA.SET.POWER";
		STD__ADD_ANALOG(str_name, "W", 0, 0, 2500);
		LINK__VAR_ANALOG_CTRL(aCH__PARA_SET_POWER, str_name);

		str_name = "PARA.HOLD.TIME";
		STD__ADD_ANALOG(str_name, "sec", 0, 0, 10000);
		LINK__VAR_ANALOG_CTRL(aCH__PARA_HOLD_TIME, str_name);

		//
		str_name = "PARA.RAMP.UP.TIME";
		STD__ADD_ANALOG(str_name, "msec", 0, 0, 30000);
		LINK__VAR_ANALOG_CTRL(aCH__PARA_RAMP_UP_TIME, str_name);

		str_name = "PARA.RAMP.DOWN.TIME";
		STD__ADD_ANALOG(str_name, "msec", 0, 0, 30000);
		LINK__VAR_ANALOG_CTRL(aCH__PARA_RAMP_DOWN_TIME, str_name);

		//
		str_name = "PARA.STEP_TIME";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__PARA_STEP_TIME, str_name);

		str_name = "PARA.RF.OFFSET.POWER";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__PARA_RF_OFFSET_POWER, str_name);
	}
	// PARA : FREQ ...
	{
		str_name = "PARA.FREQ.TUNE.USE";
		item_list.Format("Off On");
		STD__ADD_DIGITAL(str_name, item_list);
		LINK__VAR_DIGITAL_CTRL(dCH__PARA_FREQ_TUNE_USE, str_name);

		str_name = "PARA.FREQ.TUNE.DELAY";
		STD__ADD_ANALOG(str_name, "msec", 0, 0, 10000);
		LINK__VAR_ANALOG_CTRL(aCH__PARA_FREQ_TUNE_DELAY, str_name);

		str_name = "PARA.FREQ.PRESET";
		STD__ADD_ANALOG(str_name, "KHz", 0, 0, 28476);
		LINK__VAR_ANALOG_CTRL(aCH__PARA_FREQ_PRESET, str_name);

		str_name = "PARA.FREQ.OUTPUT";
		STD__ADD_ANALOG(str_name, "KHz", 0, 0, 28476);
		LINK__VAR_ANALOG_CTRL(aCH__PARA_FREQ_OUTPUT, str_name);

		str_name = "PARA.FREQ.LEARNED.VALUE";
		STD__ADD_ANALOG(str_name, "KHz", 0, 0, 28476);
		LINK__VAR_ANALOG_CTRL(aCH__PARA_FREQ_LEARNED, str_name);
	}
	// PARA : RCP ...
	{
		str_name = "PARA.RCP.CTRL.ACTIVE";
		STD__ADD_DIGITAL(str_name, "OFF ON", "");
		LINK__VAR_DIGITAL_CTRL(dCH__PARA_RCP_CTRL_ACTIVE, str_name);
	}

	// MON : IO ...
	{
		str_name = "MON.IO.SET.POWER";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_IO_SET_POWER, str_name);

		str_name = "MON.IO.FORWARD.POWER";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_IO_FORWARD_POWER, str_name);

		str_name = "MON.IO.REFLECT.POWER"; 
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_IO_REFLECT_POWER, str_name);

		//
		str_name = "MON.IO.POWER.STATE";
		STD__ADD_DIGITAL(str_name, "OFF ON", "");
		LINK__VAR_DIGITAL_CTRL(dCH__MON_IO_POWER_STATE, str_name);
	}
	// MON : RF_ON ...
	{
		str_name = "MON.RF_ON.TIME.START_DATE";
		STD__ADD_STRING_WITH_X_OPTION(str_name, "");
		LINK__VAR_STRING_CTRL(sCH__MON_RF_ON_TIME_START_DATE, str_name);

		str_name = "MON.RF_ON.TIME.TOTAL_HOUR";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "hour", 0, 0, 9999999, "");
		LINK__VAR_ANALOG_CTRL(aCH__MON_RF_ON_TIME_TOTAL_HOUR, str_name);

		str_name = "MON.RF_ON.TIME.TOTAL_SEC";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "sec", 0, 0, 9999999, "");
		LINK__VAR_ANALOG_CTRL(aCH__MON_RF_ON_TIME_TOTAL_SEC, str_name);

		str_name = "MON.RF_ON.TIME.RESET";
		STD__ADD_DIGITAL(str_name, "RETURN  RESET");
		LINK__VAR_DIGITAL_CTRL(dCH__MON_RF_ON_TIME_RESET, str_name);
	}

	// MON : STABLE  ...
	{
		str_name = "MON.ERROR.CHECK.ACTIVE";
		STD__ADD_DIGITAL(str_name, "OFF ON READY");
		LINK__VAR_DIGITAL_CTRL(dCH__MON_POWER_CHECK_ACTIVE, str_name);

		str_name = "MON.POWER.ABORT.ACTIVE";
		STD__ADD_DIGITAL(str_name, "OFF ON");
		LINK__VAR_DIGITAL_CTRL(dCH__MON_POWER_ABORT_ACTIVE, str_name);

		str_name = "MON.POWER.STABLE.ACTIVE";
		STD__ADD_DIGITAL(str_name, "OFF ON");
		LINK__VAR_DIGITAL_CTRL(dCH__MON_POWER_STABLE_ACTIVE, str_name);

		//
		str_name = "MON.POWER.STABLE.MIN";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_POWER_STABLE_MIN, str_name);

		str_name = "MON.POWER.STABLE.MAX";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_POWER_STABLE_MAX, str_name);

		str_name = "MON.POWER.STABLE.DELAY.TIME";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_POWER_STABLE_DELAY_TIME, str_name);

		str_name = "MON.POWER.STABLE.CHECK.TIME";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_POWER_STABLE_CHECK_TIME, str_name);

		str_name = "MON.POWER.WARNING.CHECK.TIME";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_POWER_WARNING_CHECK_TIME, str_name);

		str_name = "MON.POWER.ABORT.MIN";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_POWER_ABORT_MIN, str_name);

		str_name = "MON.POWER.ABORT.MAX";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_POWER_ABORT_MAX, str_name);

		str_name = "MON.POWER.ABORT.CHECK.TIME";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_POWER_ABORT_CHECK_TIME, str_name);

		//
		str_name = "MON.REFLECT.HIGH_LIMIT.CHECK.TIME";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_REFLECT_HIGH_LIMIT_CHECK_TIME, str_name);

		str_name = "MON.REFLECT.MAX_COEFFICIENT.CHECK.TIME";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_REFLECT_MAX_COEFFICIENT_CHECK_TIME, str_name);

		//
		str_name = "MON.REFLECT.HIGH_LIMIT.ACTIVE";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_REFLECT_HIGH_LIMIT_ACTIVE, str_name);

		str_name = "MON.REFLECT.MAX_COEFFICIENT.ACTIVE";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_REFLECT_MAX_COEFFICIENT_ACTIVE, str_name);
	}

	// CFG : STABLE ...
	{
		str_name = "CFG.USE.PART";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name, "YES NO", "");
		LINK__VAR_DIGITAL_CTRL(dCH__CFG_USE_PART, str_name);

		//
		str_name = "CFG.POWER.MIN.VALUE";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "W", 0, 0, 9999, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_POWER_MIN_VALUE, str_name);

		str_name = "CFG.POWER.MAX.VALUE";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "W", 0, 1, 9999, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_POWER_MAX_VALUE, str_name);

		str_name = "CFG.POWER.DEC.VALUE";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "dec", 0, 0, 5, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_POWER_DEC_VALUE, str_name);

		//
		str_name = "CFG.POWER.STABLE.DELAY.TIME";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "sec", 0, 0, 3600, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_POWER_STABLE_DELAY_TIME, str_name);

		str_name = "CFG.POWER.STABLE.CHECK.TIME";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "sec", 1, 0, 10, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_POWER_STABLE_CHECK_TIME, str_name);

		//
		str_name = "CFG.POWER.WARNING.TIMEOUT";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "sec", 0, 0, 3600, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_POWER_WARNING_TIMEOUT, str_name);

		str_name = "CFG.POWER.ABORT.TIMEOUT";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "sec", 0, 0, 3600, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_POWER_ABORT_TIMEOUT, str_name);

		//
		str_name = "CFG.POWER.WARNING.BAND";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "%", 0, 0, 100, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_POWER_WARNING_BAND, str_name);

		str_name = "CFG.POWER.ABORT.BAND";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "%", 0, 0, 100, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_POWER_ABORT_BAND, str_name);

		str_name = "CFG.IDLE.POWER.WARNING.BAND";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "%", 0, 0, 100, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_IDLE_POWER_WARNING_BAND, str_name);

		str_name = "CFG.IDLE.POWER.ABORT.BAND";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "%", 0, 0, 100, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_IDLE_POWER_ABORT_BAND, str_name);

		str_name = "CFG.Zero.Setpoint.Tolerance.Compensation";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "%", 1, 0, 10, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_Zero_Setpoint_Tolerance_Compensation, str_name);

		//
		str_name = "CFG.ERROR.CHECK.TIMEOUT";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "sec", 0, 0, 3600, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_ERROR_CHECK_TIMEOUT, str_name);

		str_name = "CFG.REFLECT.HIGH_LIMIT";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "W", 1, 0, 1000, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_REFLECT_HIGH_LIMIT, str_name);
		
		str_name = "CFG.REFLECT.MAX_COEFFICIENT";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "W", 3, 0, 1, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_REFLECT_MAX_COEFFICIENT, str_name);
	}

	// CAL ITEM ...
	{
		for(i=0;i<CFG__ITEM_CHECK;i++)
		{
			str_name.Format("RF_CAL.CFG.SET_POWER.%1d", i+1);
			STD__ADD_ANALOG_WITH_X_OPTION(str_name,"watt",0,0,10000,"");
			LINK__VAR_ANALOG_CTRL(aCH__RF_CAL__CFG_SET_POWER[i],str_name);

			//
			str_name.Format("RF_CAL.CFG.NEW_POWER.%1d", i+1);
			STD__ADD_STRING_WITH_X_OPTION(str_name,"");
			LINK__VAR_STRING_CTRL(sCH__RF_CAL__CFG_NEW_POWER[i],str_name);

			str_name.Format("RF_CAL.CFG.NEW_METER.%1d", i+1);
			STD__ADD_STRING_WITH_X_OPTION(str_name,"");
			LINK__VAR_STRING_CTRL(sCH__RF_CAL__CFG_NEW_METER[i],str_name);

			str_name.Format("RF_CAL.CFG.NEW_OFFSET.%1d", i+1);
			STD__ADD_STRING_WITH_X_OPTION(str_name,"");
			LINK__VAR_STRING_CTRL(sCH__RF_CAL__CFG_NEW_OFFSET[i],str_name);

			//
			str_name.Format("RF_CAL.CFG.NOW_POWER.%1d", i+1);
			STD__ADD_STRING_WITH_X_OPTION(str_name,"");
			LINK__VAR_STRING_CTRL(sCH__RF_CAL__CFG_NOW_POWER[i],str_name);

			str_name.Format("RF_CAL.CFG.NOW_METER.%1d", i+1);
			STD__ADD_STRING_WITH_X_OPTION(str_name,"");
			LINK__VAR_STRING_CTRL(sCH__RF_CAL__CFG_NOW_METER[i],str_name);

			str_name.Format("RF_CAL.CFG.NOW_OFFSET.%1d", i+1);
			STD__ADD_STRING_WITH_X_OPTION(str_name,"");
			LINK__VAR_STRING_CTRL(sCH__RF_CAL__CFG_NOW_OFFSET[i],str_name);
		}

		//
		str_name = "RF_CAL.CFG.NEW.AVG_OFFSET";
		STD__ADD_STRING_WITH_X_OPTION(str_name,"");
		LINK__VAR_STRING_CTRL(sCH__RF_CAL__CFG_NEW_AVG_OFFSET,str_name);

		str_name = "RF_CAL.CFG.NOW.AVG_OFFSET";
		STD__ADD_STRING_WITH_X_OPTION(str_name,"");
		LINK__VAR_STRING_CTRL(sCH__RF_CAL__CFG_NOW_AVG_OFFSET,str_name);

		//
		str_name = "RF_CAL.OFFSET.APPLY";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name,"NO AVERAGE LOOKUP","");
		LINK__VAR_DIGITAL_CTRL(dCH__RF_CAL__OFFSET_APPLY, str_name);

		str_name = "RF_CAL.OFFSET.SAVE.DATE";
		STD__ADD_STRING_WITH_X_OPTION(str_name,"");
		LINK__VAR_STRING_CTRL(sCH__RF_CAL__OFFSET_SAVE_DATE,str_name);

		str_name = "RF_CAL.TEST.FLAG";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__RF_CAL__TEST_FLAG,str_name);
	}

	// ...
	{
		str_name = "RF.ABORT.FLAG";		
		STD__ADD_DIGITAL(str_name, "OFF ON");
		LINK__VAR_DIGITAL_CTRL(dCH__RF_ABORT_FLAG, str_name);

		str_name = "RF.STABLE.FLAG";
		STD__ADD_DIGITAL(str_name, "OFF ON");
		LINK__VAR_DIGITAL_CTRL(dCH__RF_STABLE_FLAG, str_name);
	}

	// User Config Item ...
	{
		str_name.Format("CFG.MAX.ALLOWED.POWER");
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "watt", 0, 0, 999999, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_MAX_ALLOWED_POWER, str_name);

		//
		str_name.Format("CFG.POWER.INTERLOCK.WITHOUT.WAFER");
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name, "YES NO", "");
		LINK__VAR_DIGITAL_CTRL(dCH__CFG_POWER_INTERLOCK_WITHOUT_WAFER, str_name);

		str_name.Format("CFG.MAX.POWER.WITHOUT.WAFER");
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "watt", 0, 0, 1500, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_MAX_POWER_WITHOUT_WAFER, str_name);

		//
		str_name = "CFG.FREQUENCY.USE";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name, "NO YES", "");
		LINK__VAR_DIGITAL_CTRL(dCH__CFG_FREQUENCY_USE, str_name);

		str_name.Format("CFG.MIN.FREQUENCY");
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "kHz", 0, 0, 999999, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_MIN_FREQUENCY, str_name);

		str_name.Format("CFG.MAX.FREQUENCY");
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "kHz", 0, 0, 999999, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_MAX_FREQUENCY, str_name);

		str_name.Format("CFG.DEFAULT.FREQUENCY");
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "kHz", 0, 0, 999999, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_DEFAULT_FREQUENCY, str_name);

		str_name.Format("CFG.DEFAULT.RAMP.TIME");
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "msec", 0, 0, 30000, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_DEFAULT_RAMP_TIME, str_name);

		str_name.Format("CFG.DEFAULT.TUNE.DELAY");
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "msec", 0, 100, 10000, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_DEFAULT_TUNE_DELAY, str_name);
	}

	// RF Conductance Interlock Skip ...
	{
		str_name.Format("RF.CONDUCTANCE.INTLK.SKIP");
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__RF_CONDUCTANCE_INTLK_SKIP, str_name);
	}

	// ...
	{
		p_variable->Add__MONITORING_PROC(1.0, MON_ID__STATE_CHECK);
		p_variable->Add__MONITORING_PROC(1.0, MON_ID__INTERLOCK_CHECK);
		p_variable->Add__MONITORING_PROC(1.0, MON_ID__ERROR_CHECK);
	}
	return 1;
}
int CObj__RF_STD::__DEFINE__ALARM(p_alarm)
{
	DECLARE__ALARM;

	// ...
	CString title;
	title.Format("%s : ",sObject_Name);

	CString alarm_title;
	CString alarm_msg;
	CStringArray l_act;
	int alarm_id;


	// ...
	{
		alarm_id = ALID__PART_NOT_USE;

		alarm_title  = title;
		alarm_title += "RF Generator Not Use !";

		alarm_msg = "RF Generator use option is not \"YES\". \n";
		alarm_msg += "Please, Check the config option of RF Generator !!\n";

		l_act.RemoveAll();
		l_act.Add(ACT__CHECK);

		ADD__ALARM_EX(alarm_id, alarm_title, alarm_msg, l_act);
	}
	// ...
	{
		alarm_id = ALID__PART_CTRL_ABORTED;

		alarm_title  = title;
		alarm_title += " RF SYSTEM - Control Aborted.";

		alarm_msg = "Please, check RF Status.";

		l_act.RemoveAll();
		l_act.Add(ACT__CHECK);

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	// ...
	{
		alarm_id = ALID__FORWARD_POWER__PROCESS_WARNING_RANGE;

		alarm_title  = title;
		alarm_title += " RF SYSTEM - FORWARD.POWER PROCESS WARNING.RANGE.";

		alarm_msg = "Forward power is process warning tolerance.";

		l_act.RemoveAll();
		l_act.Add(ACT__CHECK);

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}
	// ...
	{
		alarm_id = ALID__FORWARD_POWER__PROCESS_ABORT_RANGE;

		alarm_title  = title;
		alarm_title += " RF SYSTEM - FORWARD.POWER PROCESS ABORT.RANGE.";

		alarm_msg = "Forward power is process abort tolerance.";

		l_act.RemoveAll();
		l_act.Add(ACT__CHECK);

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	// ...
	{
		alarm_id = ALID__FORWARD_POWER__IDLE_WARNING_RANGE;

		alarm_title  = title;
		alarm_title += " RF SYSTEM - FORWARD.POWER IDLE WARNING.RANGE.";

		alarm_msg = "Forward power is idle warning tolerance.";

		l_act.RemoveAll();
		l_act.Add(ACT__CHECK);

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}
	// ...
	{
		alarm_id = ALID__FORWARD_POWER__IDLE_ABORT_RANGE;

		alarm_title  = title;
		alarm_title += " RF SYSTEM - FORWARD.POWER IDLE ABORT.RANGE.";

		alarm_msg = "Forward power is idle abort tolerance.";

		l_act.RemoveAll();
		l_act.Add(ACT__CHECK);

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	// ...
	{
		alarm_id = ALID__VACUUM_SWITCH_ALARM;

		alarm_title  = title;
		alarm_title += "RF Power Control Alarm.";

		alarm_msg = "Chamber Vacuum Switch is not On.\n";
		alarm_msg += "Please, Check Vacuum Switch Status !!\n";

		l_act.RemoveAll();
		l_act.Add(ACT__CHECK);

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}
	// ...
	{
		alarm_id = ALID__ATM_SWITCH_ALARM;

		alarm_title  = title;
		alarm_title += "RF Power Control Alarm.";

		alarm_msg = "Chamber ATM Switch is not Off.\n";
		alarm_msg += "Please, Check ATM Switch Status !!\n";

		l_act.RemoveAll();
		l_act.Add(ACT__CHECK);

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	// ...
	{
		alarm_id = ALID__CHAMBER_LID_INTLK_ALARM;

		alarm_title  = title;
		alarm_title += "RF Power Control Alarm.";

		alarm_msg = "The lid of chamber is not close.\n";
		alarm_msg += "Please, check the lid close sensor of chamber !\n";

		l_act.RemoveAll();
		l_act.Add(ACT__CHECK);

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}
	// ...
	{
		alarm_id = ALID__CHAMBER_SHUTTER_NOT_CLOSE;

		alarm_title  = title;
		alarm_title += "RF Power Control Alarm.";

		alarm_msg = "The shutter of chamber is not close.\n";
		alarm_msg += "Please, Check PM's shutter status !!\n";

		l_act.RemoveAll();
		l_act.Add(ACT__CHECK);

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	// ...
	{
		alarm_id = ALID__INTERLOCK_SENSOR_ALARM;

		alarm_title  = title;
		alarm_title += "RF Power Control Alarm.";

		alarm_msg = "System Interlock Sensor가 감지 되었습니다.\n";
		alarm_msg += "Interlock Sensor를 확인 바랍니다.\n";

		l_act.RemoveAll();
		l_act.Add(ACT__CHECK);

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	// ...
	{
		alarm_id = ALID__REFLECTED_POWER_OVER;

		alarm_title  = title;
		alarm_title += " RF SYSTEM - REFLECTED POWER OVER.";

		alarm_msg = "Reflected Power Limit Over.";

		l_act.RemoveAll();
		l_act.Add(ACT__CHECK);

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}
	// ...
	{
		alarm_id = 	ALID__REFLECTED_COEFF_OVER;

		alarm_title  = title;
		alarm_title += " RF SYSTEM - REFLECTED Coefficient OVER.";

		alarm_msg = "Reflected Coefficient Limit Over.";

		l_act.RemoveAll();
		l_act.Add(ACT__CHECK);

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	// ...
	{
		alarm_id = ALID__REFLECTED_POWER_WARNING;

		alarm_title  = title;
		alarm_title += " RF SYSTEM - REFLECTED POWER WARNING.";

		alarm_msg = "Reflected Power is Soft Tolerance Over.";

		l_act.RemoveAll();
		l_act.Add(ACT__CHECK);

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}
	// ...
	{
		alarm_id = ALID__REFLECTED_POWER_ALARM;

		alarm_title  = title;
		alarm_title += " RF SYSTEM - REFLECTED POWER ALARM.";

		alarm_msg = "Reflected Power is Hard Tolerance Over.";

		l_act.RemoveAll();
		l_act.Add(ACT__CHECK);

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	// ...
	{
		alarm_id = ALID__RF_MAX_POWER_OVER_WHITOUT_WAFER;

		alarm_title  = title;
		alarm_title += " RF SYSTEM - MAX POWER OVER WITHOUT WAFER.";

		alarm_msg = "Wafer is Absent, RF Power Limit Over.";

		l_act.RemoveAll();
		l_act.Add(ACT__CHECK);

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	// ...
	{
		alarm_id = ALID__RF_MAX_ALLOWED_POWER_OVER;

		alarm_title  = title;
		alarm_title += " RF SYSTEM - PLASMA ALLOWED POWER OVER ALARM.";

		alarm_msg = "Set Power is not allowed.";

		l_act.RemoveAll();
		l_act.Add(ACT__CHECK);

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	return 1;
}


//-------------------------------------------------------------------------
int CObj__RF_STD::__INITIALIZE__OBJECT(p_variable,p_ext_obj_create)
{	
	CString def_name;
	CString def_data;

	CString ch_name;
	CString obj_name;
	CString var_name;

	// ...
	{
		CString file_name;
		CString log_msg;

		file_name.Format("%s_App.log", sObject_Name);

		log_msg  = "\n\n";
		log_msg += "//------------------------------------------------------------------------";

		xLOG_CTRL->CREATE__SUB_DIRECTORY(sObject_Name);
		xLOG_CTRL->SET__PROPERTY(file_name,12*1,60);

		xLOG_CTRL->DISABLE__TIME_LOG();
		xLOG_CTRL->WRITE__LOG(log_msg);

		xLOG_CTRL->ENABLE__TIME_LOG();
		xLOG_CTRL->WRITE__LOG("   START   \n");
	}

	// ...
	CCommon_Utility x_utility;
	bool def_check;

	// OBJ : DB_SYS 
	{
		def_name = "OBJ__DB_SYS";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, obj_name);

		//
		var_name = "MON.SYSTEM.PROCESS.ACTIVE";
		LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__MON_SYSTEM_PROCESS_ACTIVE, obj_name,var_name);

		//
		var_name = "MON.INTERLOCK.HEAVY.ACTIVE.SYSTEM";
		LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__MON_INTERLOCK_HEAVY_ACTIVE_SYSTEM, obj_name,var_name);

		var_name = "MON.INTERLOCK.LIGHT.ACTIVE.SYSTEM";
		LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__MON_INTERLOCK_LIGHT_ACTIVE_SYSTEM, obj_name,var_name);

		//
		var_name = "MON.INTERLOCK.HEAVY.ACTIVE.CHAMBER";
		LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__MON_INTERLOCK_HEAVY_ACTIVE_CHAMBER, obj_name,var_name);

		var_name = "MON.INTERLOCK.LIGHT.ACTIVE.CHAMBER";
		LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__MON_INTERLOCK_LIGHT_ACTIVE_CHAMBER, obj_name,var_name);
	}

	// Object Link ...
	{
		def_name = "DATA.RF_FREQUENCY.ACTIVE";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, def_data);

		if(def_data.CompareNoCase("YES") == 0)		bActive__RF_FREQ_MODE = true;
		else										bActive__RF_FREQ_MODE = false;

		def_name = "OBJ__IO_RF";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, obj_name);

		def_check = x_utility.Check__Link(obj_name);		
		bActive__RF_IO_OBJ = def_check;

		if(def_check)
		{
			pOBJ_CTRL__IO_RF = p_ext_obj_create->Create__OBJECT_CTRL(obj_name);

			// Parameter ...
			{
				var_name = "PARA.SET.POWER";
				LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__RF_PARA_SET_POWER, obj_name,var_name);

				if(bActive__RF_FREQ_MODE)
				{
					var_name = "PARA.TUNE.USE";
					LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__RF_PARA_TUNE_USE, obj_name,var_name);

					var_name = "PARA.TUNE.DELAY";
					LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__RF_PARA_TUNE_DELAY, obj_name,var_name);

					//
					var_name = "PARA.START.FREQUENCY";
					LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__RF_PARA_START_FREQUENCY, obj_name,var_name);

					var_name = "PARA.OUTPUT.FREQUENCY";
					LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__RF_PARA_OUTPUT_FREQUENCY, obj_name,var_name);

					//
					var_name = "PARA.RAMP.UP.TIME";
					LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__RF_PARA_RAMP_UP_TIME, obj_name,var_name);

					var_name = "PARA.RAMP.DOWN.TIME";
					LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__RF_PARA_RAMP_DOWN_TIME, obj_name,var_name);
				}
			}

			// LINK_MODE ...
			{
				def_name = "LINK_MODE__INIT";
				p_ext_obj_create->Get__DEF_CONST_DATA(def_name, def_data);
				sLINK__RF_MODE__INIT = def_data;

				def_name = "LINK_MODE__LOCAL";
				p_ext_obj_create->Get__DEF_CONST_DATA(def_name, def_data);
				sLINK__RF_MODE__LOCAL = def_data;

				def_name = "LINK_MODE__REMOTE";
				p_ext_obj_create->Get__DEF_CONST_DATA(def_name, def_data);
				sLINK__RF_MODE__REMOTE = def_data;

				def_name = "LINK_MODE__SET_POWER";
				p_ext_obj_create->Get__DEF_CONST_DATA(def_name, def_data);
				sLINK__RF_MODE__SET_POWER = def_data;

				def_name = "LINK_MODE__OFF";
				p_ext_obj_create->Get__DEF_CONST_DATA(def_name, def_data);
				sLINK__RF_MODE__OFF = def_data;
			}
			// LINK_VAR ...
			{
				// DO,POWER_CTRL ...
				{
					def_name = "VAR__RF_DO_POWER_CTRL";
					p_ext_obj_create->Get__DEF_CONST_DATA(def_name, var_name);

					bool def_check = x_utility.Check__Link(var_name);
					bActive__RF_DO_POWER_CTRL = def_check;

					if(bActive__RF_DO_POWER_CTRL)
					{
						LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__RF_DO_POWER_CTRL, obj_name,var_name);
					}
				}

				// AO.SET_POWER ...
				{
					def_name = "VAR__RF_AO_SET_POWER";
					p_ext_obj_create->Get__DEF_CONST_DATA(def_name, var_name);
					LINK__EXT_VAR_STRING_CTRL(sEXT_CH__RF_AO_SET_POWER, obj_name,var_name);
				}

				// AI.FORWARD_POWER ...
				{
					def_name = "VAR__RF_AI_FORWARD_POWER";
					p_ext_obj_create->Get__DEF_CONST_DATA(def_name, var_name);
					LINK__EXT_VAR_STRING_CTRL(sEXT_CH__RF_AI_FORWARD_POWER, obj_name,var_name);
				}
				// AI.REFLECT_POWER ...
				{
					def_name = "VAR__RF_AI_REFLECT_POWER";
					p_ext_obj_create->Get__DEF_CONST_DATA(def_name, var_name);
					LINK__EXT_VAR_STRING_CTRL(sEXT_CH__RF_AI_REFLECT_POWER, obj_name,var_name);
				}
			}
		}
		else  
		{
			// DO,POWER_CTRL ...
			{
				def_name = "CH__RF_DO_POWER_CTRL";
				p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);

				bool def_check = x_utility.Check__Link(ch_name);
				bActive__RF_DO_POWER_CTRL = def_check;

				if(bActive__RF_DO_POWER_CTRL)
				{
					p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
					LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__RF_DO_POWER_CTRL, obj_name,var_name);
				}
			}

			// AO.SET_POWER ...
			{
				def_name = "CH__RF_AO_SET_POWER";
				p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
				p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
				LINK__EXT_VAR_STRING_CTRL(sEXT_CH__RF_AO_SET_POWER, obj_name,var_name);
			}

			// AI.FORWARD_POWER ...
			{
				def_name = "CH__RF_AI_FORWARD_POWER";
				p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
				p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
				LINK__EXT_VAR_STRING_CTRL(sEXT_CH__RF_AI_FORWARD_POWER, obj_name,var_name);
			}
			// AI.REFLECT_POWER ...
			{
				def_name = "CH__RF_AI_REFLECT_POWER";
				p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
				p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
				LINK__EXT_VAR_STRING_CTRL(sEXT_CH__RF_AI_REFLECT_POWER, obj_name,var_name);
			}			
		}
	}

	// IO Link ...
	{
		def_name = "CH__DI_VAC_SENSOR";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
		p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
		LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__DI_VAC_SNS, obj_name,var_name);

		def_name = "CH__DI_ATM_SENSOR";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
		p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
		LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__DI_ATM_SNS, obj_name,var_name);

		//
		def_name = "CH__DI_CHM_LID_CLOSE_SENSOR";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
		
		def_check = x_utility.Check__Link(ch_name);
		bActive__DI_CHM_LID_CLOSE_SNS = def_check;

		if(def_check)
		{
			p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
			LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__DI_CHM_LID_CLOSE_SNS, obj_name,var_name);
		}

		//
		def_name = "CH__DI_CHM_LID_OPEN_SENSOR";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);

		def_check = x_utility.Check__Link(ch_name);
		bActive__DI_CHM_LID_OPEN_SNS = def_check;

		if(def_check)
		{
			p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
			LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__DI_CHM_LID_OPEN_SNS, obj_name,var_name);
		}

		//
		def_name = "CH__CHM_SHUTTER_STATE";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
		p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
		LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__CHM_SHUTTER_STATE, obj_name,var_name);

		def_name = "CH__WAFER_STATE";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
		p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
		LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__SLOT01_STATUS, obj_name,var_name);

		//
		def_name = "CH__INTERLOCK_ACTIVE";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
		p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
		LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__INTERLOCK_ACTIVE, obj_name,var_name);
		
		def_name = "CH__INTERLOCK_MSG";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
		p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
		LINK__EXT_VAR_STRING_CTRL(sEXT_CH__INTERLOCK_MSG, obj_name,var_name);
	}

	// ...
	{
		SCX__SEQ_INFO x_seq_info;

		iActive__SIM_MODE = x_seq_info->Is__SIMULATION_MODE();
	}
	return 1;
}


//-------------------------------------------------------------------------
int CObj__RF_STD::__CALL__CONTROL_MODE(mode,p_debug,p_variable,p_alarm)
{
	int flag = -1;

	// ...
	{
		CString log_msg;
		log_msg.Format("Start ... :  [%s]",mode);

		sCH__OBJ_MSG->Set__DATA(log_msg);
		xLOG_CTRL->WRITE__LOG(log_msg);
	}

	// ...
	{
		dCH__MON_POWER_CHECK_ACTIVE->Set__DATA(STR__OFF);
		dCH__MON_POWER_STABLE_ACTIVE->Set__DATA(STR__OFF);	
		dCH__MON_POWER_ABORT_ACTIVE->Set__DATA(STR__OFF);	
	}

	if(dCH__CFG_USE_PART->Check__DATA(STR__YES) < 0)
	{
		int alarm_id = ALID__PART_NOT_USE;
		CString alm_msg;
		CString r_act;

		alm_msg.Format("RF.GEN [%s] command is aborted !.\n", mode);

		p_alarm->Check__ALARM(alarm_id, r_act);
		p_alarm->Post__ALARM_With_MESSAGE(alarm_id, alm_msg);
	}
	else
	{
		flag = 1;
	}

	if(flag > 0)
	{
		IF__CTRL_MODE(sMODE__INIT)
		{
			flag = Call__INIT(p_variable, p_alarm);
		}
		ELSE_IF__CTRL_MODE(sMODE__OFF)
		{
			flag = Call__OFF(p_variable, p_alarm);
		}
		ELSE_IF__CTRL_MODE(sMODE__QUICK_OFF)
		{
			flag = Call__QUICK_OFF(p_variable, p_alarm);
		}
		ELSE_IF__CTRL_MODE(sMODE__SET_POWER)
		{
			flag = Call__SET_POWER(p_variable, p_alarm);

			if(flag > 0)		dCH__MON_POWER_CHECK_ACTIVE->Set__DATA(STR__READY);
		}
		ELSE_IF__CTRL_MODE(sMODE__REMOTE)
		{
			flag = Call__REMOTE(p_variable, p_alarm);
		}
		ELSE_IF__CTRL_MODE(sMODE__LOCAL)
		{
			flag = Call__LOCAL(p_variable, p_alarm);
		}
	}

	sCH__PARA_STEP_TIME->Set__DATA("");
	dCH__PARA_RCP_CTRL_ACTIVE->Set__DATA(STR__OFF);

	if((flag < 0)||(p_variable->Check__CTRL_ABORT() > 0))
	{
		CString log_msg;
		log_msg.Format("Aborted ... :  [%s]",mode);

		sCH__OBJ_MSG->Set__DATA(log_msg);
		xLOG_CTRL->WRITE__LOG(log_msg);

		// ...
		{
			int alarm_id = ALID__PART_CTRL_ABORTED;
			CString alm_msg;
			CString r_act;

			if(p_variable->Check__CTRL_ABORT() > 0)
			{
				alm_msg.Format("RF Mode (%s) is aborted by upper object.", mode);
			}
			else
			{
				alm_msg.Format("RF Mode (%s) is aborted by physical object.", mode);
			}

			p_alarm->Check__ALARM(alarm_id,r_act);
			p_alarm->Post__ALARM_With_MESSAGE(alarm_id,alm_msg);
		}
	}
	else
	{
		CString log_msg;
		log_msg.Format("Completed ... :  [%s]",mode);

		sCH__OBJ_MSG->Set__DATA(log_msg);
		xLOG_CTRL->WRITE__LOG(log_msg);
	}

	return flag;
}

int CObj__RF_STD::__CALL__MONITORING(id,p_variable,p_alarm)
{
	if(id == MON_ID__STATE_CHECK)			Mon__STATE_CHECK(p_variable, p_alarm);
	if(id == MON_ID__INTERLOCK_CHECK)		Mon__INTERLOCK_CHECK(p_variable, p_alarm);
	if(id == MON_ID__ERROR_CHECK)			Mon__ERROR_CHECK(p_variable, p_alarm);

	return 1;
}
