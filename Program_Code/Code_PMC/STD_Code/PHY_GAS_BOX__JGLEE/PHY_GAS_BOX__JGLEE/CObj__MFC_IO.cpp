#include "StdAfx.h"
#include "CObj__MFC_IO.h"

#include "CCommon_Utility.h"


//-------------------------------------------------------------------------
CObj__MFC_IO::CObj__MFC_IO()
{

}
CObj__MFC_IO::~CObj__MFC_IO()
{

}

//-------------------------------------------------------------------------
int CObj__MFC_IO::__DEFINE__CONTROL_MODE(obj,l_mode)
{
	sObject_Name = obj;

	// ...
	{
		ADD__CTRL_VAR(sMODE__INIT,  "INIT");

		ADD__CTRL_VAR(sMODE__OPEN,	"OPEN");
		ADD__CTRL_VAR(sMODE__CLOSE,	"CLOSE");

		//
		ADD__CTRL_VAR(sMODE__CONTROL,   "CONTROL");
		ADD__CTRL_VAR(sMODE__RAMP_CTRL, "RAMP.CTRL");

		ADD__CTRL_VAR(sMODE__SET_FLOW, "SET.FLOW");

		//
		ADD__CTRL_VAR(sMODE__PURGE, "PURGE");

		ADD__CTRL_VAR(sMODE__GAS_LINE_PURGE, "GAS_LINE_PURGE");
		ADD__CTRL_VAR(sMODE__CHM_LINE_PURGE, "CHM_LINE_PURGE");
	}
	return 1;
}
int CObj__MFC_IO::__DEFINE__VERSION_HISTORY(version)
{
	// ...
	{

	}
	return 1;
}


// ...
#define  MON_ID__STATE_CHECK			1
#define  MON_ID__ERROR_CHECK            2


#define  APP_DSP__VALVE_CTRL			"NONE CONTROL CLOSE OPEN OFF"


int CObj__MFC_IO::__DEFINE__VARIABLE_STD(p_variable)
{
	DECLARE__STD_VARIABLE;

	CCommon_Error__DEF_VARIABLE m_err_def_variable;
	p_variable->Link__DEF_VARIABLE__ERROR_FEEDBACK(&m_err_def_variable);

	// ...
	CString str_name;

	// ...
	{
		str_name = "OBJ.MSG";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__OBJ_MSG, str_name);
	}

	// PARA ...
	{
		str_name = "PARA.SET.FLOW";
		STD__ADD_ANALOG_WITH_OPTION(str_name, "slm", 3, 0.0, 10000, -1, "L", "");
		LINK__VAR_ANALOG_CTRL(aCH__PARA_SET_VALUE, str_name);

		str_name = "PARA.RAMP.SEC";
		STD__ADD_ANALOG_WITH_OPTION(str_name, "sec", 1, 0.0, 5, -1, "L", "");
		LINK__VAR_ANALOG_CTRL(aCH__PARA_RAMP_SEC, str_name);
	}

	// INFO ...
	{
		str_name = "INFO.LINK_DATA.TYPE";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__INFO_LINK_DATA__TYPE, str_name);

		str_name = "INFO.LINK_DATA.MAX_FLOW";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__INFO_LINK_DATA__MAX_FLOW, str_name);

		str_name = "INFO.LINK_DATA.MAX_DEFAULT";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__INFO_LINK_DATA__MAX_DEFAULT, str_name);
	}

	// MON.MFC ...
	{
		str_name = "MON.MFC.STATE";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_MFC_STATE, str_name);

		//
		str_name = "MON.MFC.SET.FLOW";		
		STD__ADD_ANALOG_WITH_OPTION(str_name, "sccm", 1, 0, 10000, -1, "L", "");
		LINK__VAR_ANALOG_CTRL(aCH__MON_MFC_SET_FLOW, str_name);

		str_name = "MON.MFC.SET.PERCENT";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_MFC_SET_PERCENT, str_name);

		//
		str_name = "MON.MFC.READ.FLOW";		
		STD__ADD_ANALOG_WITH_OPTION(str_name, "sccm", 1, 0, 10000, -1, "L", "");
		LINK__VAR_ANALOG_CTRL(aCH__MON_MFC_READ_FLOW, str_name);

		str_name = "MON.MFC.FLOW.PERCENT";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_MFC_FLOW_PERCENT, str_name);

		//
		str_name = "MON.MFC.EXCEPTION_STATE";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_MFC_EXCEPTION_STATE, str_name);

		str_name = "MON.MFC.EXCEPTION_INFO";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_MFC_EXCEPTION_INFO, str_name);

		//
		str_name = "MON.MFC.READ.VALVE_VOLTAGE";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_MFC_READ_VALVE_VOLTAGE, str_name);

		str_name = "MON.MFC.VALVE_VOLTAGE.PERCENT";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_MFC_VALVE_VOLTAGE_PERCENT, str_name);

		//
		str_name = "MON.MFC.READ.INLET_PRESSURE";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_MFC_READ_INLET_PRESSURE, str_name);

		str_name = "MON.MFC.INLET_PRESSURE.PERCENT";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_MFC_INLET_PRESSURE_PERCENT, str_name);

		//
		str_name = "MON.MFC.READ.TEMPERATURE";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_MFC_READ_TEMPERATURE, str_name);

		str_name = "MON.MFC.TEMPERATURE.PERCENT";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_MFC_TEMPERATURE_PERCENT, str_name);
	}

	// MON.STABLE ...
	{
		str_name = "MON.MFC.ABORT.ACTIVE";
		STD__ADD_DIGITAL(str_name, "OFF ON");
		LINK__VAR_DIGITAL_CTRL(dCH__MON_MFC_ABORT_ACTIVE, str_name);

		str_name = "MON.MFC.STABLE.ACTIVE";
		STD__ADD_DIGITAL(str_name, "OFF ON");
		LINK__VAR_DIGITAL_CTRL(dCH__MON_MFC_STABLE_ACTIVE, str_name);

		str_name = "MON.ERROR.CHECK.ACTIVE";
		STD__ADD_DIGITAL(str_name, "OFF ON READY");
		LINK__VAR_DIGITAL_CTRL(dCH__MON_ERROR_CHECK_ACTIVE, str_name);

		//
		str_name = "MON.MFC.STABLE.MIN";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_MFC_STABLE_MIN, str_name);

		str_name = "MON.MFC.STABLE.MAX";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_MFC_STABLE_MAX, str_name);

		str_name = "MON.MFC.STABLE.DELAY.TIME";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_MFC_STABLE_DELAY_TIME, str_name);

		str_name = "MON.MFC.STABLE.CHECK.TIME";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_MFC_STABLE_CHECK_TIME, str_name);

		str_name = "MON.MFC.WARNING.CHECK.TIME";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_MFC_WARNING_CHECK_TIME, str_name);

		str_name = "MON.MFC.ABORT.MIN";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_MFC_ABORT_MIN, str_name);

		str_name = "MON.MFC.ABORT.MAX";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_MFC_ABORT_MAX, str_name);

		str_name = "MON.MFC.ABORT.CHECK.TIME";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_MFC_ABORT_CHECK_TIME, str_name);
	}

	// MON.PT ...
	{
		str_name = "MON.ERROR.CHECK.ACTIVE.PT";
		STD__ADD_DIGITAL(str_name, "OFF ON READY");
		LINK__VAR_DIGITAL_CTRL(dCH__MON_ERROR_CHECK_ACTIVE_PT, str_name);

		str_name = "MON.ABORT.ACTIVE.PT";
		STD__ADD_DIGITAL(str_name, "OFF ON");
		LINK__VAR_DIGITAL_CTRL(dCH__MON_ABORT_ACTIVE_PT, str_name);

		str_name = "MON.STABLE.ACTIVE.PT";
		STD__ADD_DIGITAL(str_name, "OFF ON");
		LINK__VAR_DIGITAL_CTRL(dCH__MON_STABLE_ACTIVE_PT, str_name);

		//
		str_name = "MON.STABLE.CHECK.TIME.PT";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_STABLE_CHECK_TIME_PT, str_name);

		str_name = "MON.WARNING.MIN.PT";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_WARNING_MIN_PT, str_name);

		str_name = "MON.WARNING.MAX.PT";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_WARNING_MAX_PT, str_name);

		str_name = "MON.WARNING.CHECK.TIME.PT";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_WARNING_CHECK_TIME_PT, str_name);

		str_name = "MON.ABORT.MIN.PT";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_ABORT_MIN_PT, str_name);

		str_name = "MON.ABORT.MAX.PT";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_ABORT_MAX_PT, str_name);

		str_name = "MON.ABORT.CHECK.TIME.PT";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_ABORT_CHECK_TIME_PT, str_name);
	}

	// CFG ...
	{
		str_name = "CFG.GAS.NAME";
		STD__ADD_STRING_WITH_X_OPTION(str_name, "");
		LINK__VAR_STRING_CTRL(sCH__CFG_GAS_NAME, str_name);

		str_name = "CFG.MFC.USE";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name, "YES NO", "");
		LINK__VAR_DIGITAL_CTRL(dCH__CFG_MFC_USE, str_name);

		str_name = "CFG.MFC.MIN.VALUE";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "slm", 0, 0, 999999, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_MFC_MIN_VALUE, str_name);

		str_name = "CFG.MFC.MAX.VALUE";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "slm", 0, 0, 999999, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_MFC_MAX_VALUE, str_name);

		str_name = "CFG.MFC.DEC.VALUE";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "dec", 0, 0, 5, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_MFC_DEC_VALUE, str_name);

		//
		str_name = "CFG.STABLE.DELAY.TIME";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "sec", 0, 0, 3600, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_STABLE_DELAY_TIME, str_name);

		str_name = "CFG.STABLE.CHECK.TIME";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "sec", 1, 0, 10, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_STABLE_CHECK_TIME, str_name);

		//
		str_name = "CFG.TOL.WARN.TIMEOUT";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "sec", 0, 0, 3600, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_TOL_WARN_TIMEOUT,str_name);

		str_name = "CFG.TOL.ABORT.TIMEOUT";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "sec", 0, 0, 3600, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_TOL_ABORT_TIMEOUT,str_name);

		str_name = "CFG.WARN.BAND";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "%", 0, 0, 100, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_WARN_BAND,str_name);

		str_name = "CFG.ABORT.BAND";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "%", 0, 0, 100, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_ABORT_BAND,str_name);

		str_name = "CFG.IDLE.WARN.BAND";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "%", 0, 0, 100, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_IDLE_WARN_BAND,str_name);

		str_name = "CFG.IDLE.ABORT.BAND";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "%", 0, 0, 100, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_IDLE_ABORT_BAND,str_name);

		str_name = "CFG.MFC.Zero.Setpoint.Tolerance.Compensation";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name,"%", 1, 2, 100, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_MFC_Zero_Setpoint_Tolerance_Compensation, str_name);

		//
		str_name = "CFG.ABORT.TOLERANCE.VALVE.CLOSE";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name, "NO YES", "");
		LINK__VAR_DIGITAL_CTRL(dCH__CFG_ABORT_TOLE_VALVE_CLOSE, str_name);

		//
		str_name = "CFG.FLOW.MODE";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name, "ALL CENTER EDGE", "");
		LINK__VAR_DIGITAL_CTRL(dCH__CFG_FLOW_MODE, str_name);
	}

	// CFG - RANGE ...
	{
		str_name = "CFG.RANGE.MFC.UNIT";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name, "sccm  slm", "");	
		LINK__VAR_DIGITAL_CTRL(dCH__CFG_RANGE_MFC_UNIT, str_name);

		// Pressure
		str_name = "CFG.RANGE.MAX.PRESSURE";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "psi", 0, 0, 999999, "");	
		LINK__VAR_ANALOG_CTRL(aCH__CFG_RANGE_MAX_PRESSURE, str_name);

		str_name = "CFG.RANGE.DEC.PRESSURE";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "dec", 0, 0, 5, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_RANGE_DEC_PRESSURE, str_name);

		// Temperature
		str_name = "CFG.RANGE.MAX.TEMPERATURE";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "C", 0, 0, 999999, "");	
		LINK__VAR_ANALOG_CTRL(aCH__CFG_RANGE_MAX_TEMPERATURE, str_name);

		str_name = "CFG.RANGE.DEC.TEMPERATURE";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "dec", 0, 0, 5, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_RANGE_DEC_TEMPERATURE, str_name);
	}

	// ...
	{
		p_variable->Add__MONITORING_PROC(1.0, MON_ID__STATE_CHECK);
		p_variable->Add__MONITORING_PROC(1.0, MON_ID__ERROR_CHECK);
	}
	return 1;
}


// ...
#define  ACT__RETRY_ABORT						\
l_act.RemoveAll();								\
l_act.Add("RETRY");								\
l_act.Add("ABORT");


int CObj__MFC_IO::__DEFINE__ALARM(p_alarm)
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
		alarm_id = ALID__MFC_NOT_USE;

		alarm_title  = title;
		alarm_title += "In MFC config page, MFC's use is selected to \"YES\".";

		alarm_msg = "Please, check MFC's Use Option in the config page. \n";

		l_act.RemoveAll();
		l_act.Add(ACT__CHECK);

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	// ...
	{
		alarm_id = ALID__MFC_FLOW__CONTROL_ABORTED;

		alarm_title  = title;
		alarm_title += "MFC Flow Control Aborted !.";

		alarm_msg  = "MFC Control Error !.\n";
		alarm_msg += "Please, check H/W MFC controller.";

		l_act.RemoveAll();
		l_act.Add(ACT__CLEAR);

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	// ...
	{
		alarm_id = ALID__MFC_FLOW__CONTROL_WARNING_RANGE;

		alarm_title  = title;
		alarm_title += "MFC Flow Control Warning Range Alarm.";

		alarm_msg.Format("MFC Flow Control was over the Warning Range..\n");

		l_act.RemoveAll();
		l_act.Add(ACT__CLEAR);

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}
	// ...
	{
		alarm_id = ALID__MFC_FLOW__CONTROL_ABORT_RANGE;

		alarm_title  = title;
		alarm_title += "MFC Flow Control Abort Range Alarm.";

		alarm_msg = "Flow Control was over the Abort Range..\n";
		alarm_msg += "For Safety, MFC Flow Will be Stopped !!\n";

		l_act.RemoveAll();
		l_act.Add(ACT__CLEAR);

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	// ...
	{
		alarm_id = ALID__MFC_FLOW__CONTROL_IDLE_WARNING_RANGE;

		alarm_title  = title;
		alarm_title += "During Idle, MFC Flow Control Warning Range Alarm.";

		alarm_msg = "Flow Control was over the Warning Range..\n";

		l_act.RemoveAll();
		l_act.Add(ACT__CLEAR);

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}
	// ...
	{
		alarm_id = ALID__MFC_FLOW__CONTROL_IDLE_ABORT_RANGE;

		alarm_title  = title;
		alarm_title += "During Idle, MFC Flow Control Abort Range Alarm.";

		alarm_msg = "Flow Control was over the Abort Range..\n";
		alarm_msg += "For Safety, MFC Flow Will be Stopped !!\n";

		l_act.RemoveAll();
		l_act.Add(ACT__CLEAR);

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	return 1;
}

int CObj__MFC_IO::__Define__USER_FUNCTION(CII_DEFINE__FUNCTION *p_fnc_ctrl)
{
	p_fnc_ctrl->Link__ERROR_FEEDBACK(&mERROR__USER_FNC);

	//
	return 1;
}

//-------------------------------------------------------------------------
int CObj__MFC_IO::__INITIALIZE__OBJECT(p_variable,p_ext_obj_create)
{
	// ...
	{
		CString file_name;
		CString log_msg;

		file_name.Format("%s.log", sObject_Name);

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
	CString def_name;
	CString def_data;
	CString ch_name;
	CString obj_name;
	CString var_name;
	CString ch_data;
	int i;

	// ...
	CCommon_Utility m_fnc;	
	bool def_check;

	// DB_SYS ...
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

		//
		var_name = "MON.INTERLOCK.HEAVY.ACTIVE.GAS_BOX";
		LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__MON_INTERLOCK_HEAVY_ACTIVE_GAS_BOX, obj_name,var_name);

		var_name = "MON.INTERLOCK.LIGHT.ACTIVE.GAS_BOX";
		LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__MON_INTERLOCK_LIGHT_ACTIVE_GAS_BOX, obj_name,var_name);
	}

	// LINK.DATA ...
	{
		// TYPE ...
		{
			def_name = "LINK_DATA__TYPE";	
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name, def_data);

			if(def_data.CompareNoCase("HEXA") == 0)	
			{
				iLINK_DATA__TYPE = _DATA_TYPE__HEXA;
				ch_data = "HEXA";
			}
			else
			{
				iLINK_DATA__TYPE = _DATA_TYPE__DEC;
				ch_data = "DEC";
			}

			sCH__INFO_LINK_DATA__TYPE->Set__DATA(ch_data);
		}
		
		// MAX.FLOW ...
		if(iLINK_DATA__TYPE == _DATA_TYPE__HEXA)
		{
			def_name = "LINK_DATA__MAX_FLOW";
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name, def_data);

			if(m_fnc.Check__Hexa_Type(def_data) > 0)
			{
				iLINK_DATA__MAX_FLOW = m_fnc.Get__Hexa_From_String(def_data);
			}
			else
			{
				iLINK_DATA__MAX_FLOW = atoi(def_data);
			}

			if(iLINK_DATA__MAX_FLOW < 1)			iLINK_DATA__MAX_FLOW = 0x6000;

			ch_data.Format("%02X", iLINK_DATA__MAX_FLOW);
			sCH__INFO_LINK_DATA__MAX_FLOW->Set__DATA(ch_data);
		}
		// MAX.DEFAULT ...
		if(iLINK_DATA__TYPE == _DATA_TYPE__HEXA)
		{
			def_name = "LINK_DATA__MAX_DEFAULT";	
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name, def_data);

			if(m_fnc.Check__Hexa_Type(def_data) > 0)		iLINK_DATA__MAX_DEFAULT = m_fnc.Get__Hexa_From_String(def_data);
			else											iLINK_DATA__MAX_DEFAULT = atoi(def_data);

			if(iLINK_DATA__MAX_DEFAULT < 1)			iLINK_DATA__MAX_DEFAULT = 0x6000;
		
			ch_data.Format("%02X", iLINK_DATA__MAX_DEFAULT);
			sCH__INFO_LINK_DATA__MAX_DEFAULT->Set__DATA(ch_data);
		}
	}

	// LINK : IO ...
	{
		// MFC ...
		{
			// SET & READ ...
			{
				def_name = "CH__IO_MFC_SET";
				p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
				p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
				LINK__EXT_VAR_STRING_CTRL(sEXT_CH__IO_MFC_SET, obj_name,var_name);

				def_name = "CH__IO_MFC_READ";
				p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
				p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
				LINK__EXT_VAR_STRING_CTRL(sEXT_CH__IO_MFC_READ, obj_name,var_name);
			}

			// IO.STATE ...
			{
				def_name = "CH__IO_MFC_STATE";
				p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);

				def_check = m_fnc.Check__Link(ch_name);
				bActive__MFC_STATE = def_check;

				if(def_check)
				{
					p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
					LINK__EXT_VAR_STRING_CTRL(sEXT_CH__IO_MFC_STATE, obj_name,var_name);
				}
			}

			// IO.VOLTAGE ...
			{
				def_name = "CH__IO_MFC_VALVE_VOLTAGE";
				p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);

				def_check = m_fnc.Check__Link(ch_name);
				bActive__MFC_VALVE_VOLTAGE = def_check;

				if(def_check)
				{
					p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
					LINK__EXT_VAR_STRING_CTRL(sEXT_CH__IO_MFC_VALVE_VOLTAGE, obj_name,var_name);
				}
			}

			// IO.PRESSYRE ...
			{
				def_name = "CH__IO_MFC_PRESSURE";
				p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);

				def_check = m_fnc.Check__Link(ch_name);
				bActive__MFC_PRESSURE = def_check;

				if(def_check)
				{
					p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
					LINK__EXT_VAR_STRING_CTRL(sEXT_CH__IO_MFC_PRESSURE, obj_name,var_name);
				}
			}

			// IO.TEMPERATURE ...
			{
				def_name = "CH__IO_MFC_TEMPERATURE";
				p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);

				def_check = m_fnc.Check__Link(ch_name);
				bActive__MFC_TEMPERATURE = def_check;

				if(def_check)
				{
					p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
					LINK__EXT_VAR_STRING_CTRL(sEXT_CH__IO_MFC_TEMPERATURE, obj_name,var_name);
				}
			}
		}

		// VLV.PURGE_IN ...
		{
			def_name = "DATA.VLV_PURGE_IN";
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name, def_data);

			iSIZE__VLV_PURGE_IN = atoi(def_data);
			if(iSIZE__VLV_PURGE_IN > _CFG_MFC_VLV__SIZE)			iSIZE__VLV_PURGE_IN = _CFG_MFC_VLV__SIZE;

			for(i=0; i<iSIZE__VLV_PURGE_IN; i++)
			{
				def_name.Format("CH__IO_VLV_PURGE_IN.%1d", i+1);
				p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
				p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);

				LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__IO_VLV_PURGE_IN_X[i], obj_name,var_name);
			}
		}
		// VLV.IN ...
		{
			def_name = "DATA.VLV_IN";
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name, def_data);

			iSIZE__VLV_IN = atoi(def_data);
			if(iSIZE__VLV_IN > _CFG_MFC_VLV__SIZE)			iSIZE__VLV_IN = _CFG_MFC_VLV__SIZE;

			for(i=0; i<iSIZE__VLV_IN; i++)
			{
				def_name.Format("CH__IO_VLV_IN.%1d", i+1);
				p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
				p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);

				LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__IO_VLV_IN_X[i], obj_name,var_name);
			}
		}
		// VLV.OUT_ALL ...
		{
			def_name = "DATA.VLV_OUT_ALL";
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name, def_data);

			iSIZE__VLV_OUT_ALL = atoi(def_data);
			if(iSIZE__VLV_OUT_ALL > _CFG_MFC_VLV__SIZE)			iSIZE__VLV_OUT_ALL = _CFG_MFC_VLV__SIZE;

			for(i=0; i<iSIZE__VLV_OUT_ALL; i++)
			{
				def_name.Format("CH__IO_VLV_OUT_ALL.%1d", i+1);
				p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
				p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);

				LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__IO_VLV_OUT_ALL_X[i], obj_name,var_name);
			}
		}
		// VLV.OUT_CENTER ...
		{
			def_name = "DATA.VLV_OUT_CENTER";
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name, def_data);

			iSIZE__VLV_OUT_CENTER = atoi(def_data);
			if(iSIZE__VLV_OUT_CENTER > _CFG_MFC_VLV__SIZE)		iSIZE__VLV_OUT_CENTER = _CFG_MFC_VLV__SIZE;

			for(i=0; i<iSIZE__VLV_OUT_CENTER; i++)
			{
				def_name.Format("CH__IO_VLV_OUT_CENTER.%1d", i+1);
				p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
				p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);

				LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__IO_VLV_OUT_CENTER_X[i], obj_name,var_name);
			}
		}
		// VLV.OUT_EDGE ...
		{
			def_name = "DATA.VLV_OUT_EDGE";
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name, def_data);

			iSIZE__VLV_OUT_EDGE = atoi(def_data);
			if(iSIZE__VLV_OUT_EDGE > _CFG_MFC_VLV__SIZE)		iSIZE__VLV_OUT_EDGE = _CFG_MFC_VLV__SIZE;

			for(i=0; i<iSIZE__VLV_OUT_EDGE; i++)
			{
				def_name.Format("CH__IO_VLV_OUT_EDGE.%1d", i+1);
				p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
				p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);

				LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__IO_VLV_OUT_EDGE_X[i], obj_name,var_name);
			}
		}
		// VLV.PURGE_OUT ...
		{
			def_name = "DATA.VLV_PURGE_OUT";
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name, def_data);

			iSIZE__VLV_PURGE_OUT = atoi(def_data);
			if(iSIZE__VLV_PURGE_OUT > _CFG_MFC_VLV__SIZE)			iSIZE__VLV_PURGE_OUT = _CFG_MFC_VLV__SIZE;

			for(i=0; i<iSIZE__VLV_PURGE_OUT; i++)
			{
				def_name.Format("CH__IO_VLV_PURGE_OUT.%1d", i+1);
				p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
				p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);

				LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__IO_VLV_PURGE_OUT_X[i], obj_name,var_name);
			}
		}
	}

	// ...
	{
		sCH__MON_MFC_STATE->Set__DATA(STR__CLOSE);

		aCH__MON_MFC_SET_FLOW->Set__DATA("0");
	}

	// ...
	{
		SCX__SEQ_INFO x_seq;

		iActive__SIM_MODE = x_seq->Is__SIMULATION_MODE();
	}
	return 1;
}

//-------------------------------------------------------------------------
int CObj__MFC_IO::__CALL__CONTROL_MODE(mode,p_debug,p_variable,p_alarm)
{
	int flag = 1;
	CString log_msg;

	// ...	
	CString var_gas_name = sCH__CFG_GAS_NAME->Get__STRING();

	// ...
	{
		log_msg.Format("Start ... :  [%s], Gas_Name:[%s]",mode,var_gas_name);

		xLOG_CTRL->WRITE__LOG(log_msg);
		sCH__OBJ_MSG->Set__DATA(log_msg);

	}

	if(dCH__CFG_MFC_USE->Check__DATA(STR__YES) < 0)
	{
		if((mode.CompareNoCase(sMODE__INIT)  != 0)
		&& (mode.CompareNoCase(sMODE__CLOSE) != 0))
		{
			flag = -1;

			// ...
			{
				int alarm_id = ALID__MFC_NOT_USE;
				CString r_act;

				p_alarm->Check__ALARM(alarm_id,r_act);
				p_alarm->Post__ALARM(alarm_id);
			}
		}
	}
	else
	{
		bool active__interlock_system  = false;
		bool active__interlock_chamber = false;
		bool active__interlock_gas_box = false;

		if(dEXT_CH__MON_INTERLOCK_HEAVY_ACTIVE_SYSTEM->Check__DATA(STR__ON)  > 0)		active__interlock_system  = true;
		if(dEXT_CH__MON_INTERLOCK_HEAVY_ACTIVE_CHAMBER->Check__DATA(STR__ON) > 0)		active__interlock_chamber = true;
		if(dEXT_CH__MON_INTERLOCK_HEAVY_ACTIVE_GAS_BOX->Check__DATA(STR__ON) > 0)		active__interlock_gas_box = true;

		if((mode.CompareNoCase(sMODE__OPEN)      == 0)
		|| (mode.CompareNoCase(sMODE__CONTROL)   == 0)
		|| (mode.CompareNoCase(sMODE__RAMP_CTRL) == 0)
		|| (mode.CompareNoCase(sMODE__SET_FLOW)  == 0))
		{
			flag = -1;

			if(active__interlock_system)
			{
				int alm_id = ALID__INTERLOCK_SENSOR__SYSTEM;
				CString alm_msg;
				CString alm_bff;
				CString r_act;

				alm_bff.Format(" * %s <- %s \n", 
								dEXT_CH__MON_INTERLOCK_HEAVY_ACTIVE_SYSTEM->Get__CHANNEL_NAME(),
								dEXT_CH__MON_INTERLOCK_HEAVY_ACTIVE_SYSTEM->Get__STRING());
				alm_msg += alm_bff;

				p_alarm->Check__ALARM(alm_id, r_act);
				p_alarm->Post__ALARM_With_MESSAGE(alm_id, alm_msg);
			}
			else if(active__interlock_system)
			{
				int alm_id = ALID__INTERLOCK_SENSOR__CHMABER;
				CString alm_msg;
				CString alm_bff;
				CString r_act;

				alm_bff.Format(" * %s <- %s \n", 
								dEXT_CH__MON_INTERLOCK_HEAVY_ACTIVE_CHAMBER->Get__CHANNEL_NAME(),
								dEXT_CH__MON_INTERLOCK_HEAVY_ACTIVE_CHAMBER->Get__STRING());
				alm_msg += alm_bff;

				p_alarm->Check__ALARM(alm_id, r_act);
				p_alarm->Post__ALARM_With_MESSAGE(alm_id, alm_msg);
			}
			else if(active__interlock_gas_box)
			{
				int alm_id = ALID__INTERLOCK_SENSOR__GAS_BOX;
				CString alm_msg;
				CString alm_bff;
				CString r_act;

				alm_bff.Format(" * %s <- %s \n", 
								dEXT_CH__MON_INTERLOCK_HEAVY_ACTIVE_GAS_BOX->Get__CHANNEL_NAME(),
								dEXT_CH__MON_INTERLOCK_HEAVY_ACTIVE_GAS_BOX->Get__STRING());
				alm_msg += alm_bff;

				p_alarm->Check__ALARM(alm_id, r_act);
				p_alarm->Post__ALARM_With_MESSAGE(alm_id, alm_msg);
			}
			else
			{
				flag = 1;
			}
		}
	}

	if(flag > 0)
	{
		dCH__MON_ERROR_CHECK_ACTIVE->Set__DATA(STR__OFF);
		dCH__MON_MFC_ABORT_ACTIVE->Set__DATA(STR__OFF);
		dCH__MON_MFC_STABLE_ACTIVE->Set__DATA(STR__OFF);

		IF__CTRL_MODE(sMODE__INIT)
		{
			flag = Call__INIT(p_variable,p_alarm);

			sCH__MON_MFC_STATE->Set__DATA(STR__CLOSE);
		}
		ELSE_IF__CTRL_MODE(sMODE__CLOSE)
		{
			flag = Call__CLOSE(p_variable,p_alarm);

			sCH__MON_MFC_STATE->Set__DATA(STR__CLOSE);
		}
		ELSE_IF__CTRL_MODE(sMODE__OPEN)
		{
			flag = Call__OPEN(p_variable,p_alarm);

			sCH__MON_MFC_STATE->Set__DATA(STR__OPEN);
		}
		ELSE_IF__CTRL_MODE(sMODE__CONTROL)
		{
			flag = Call__CONTROL(p_variable,p_alarm);

			sCH__MON_MFC_STATE->Set__DATA(STR__CONTROL);
			dCH__MON_ERROR_CHECK_ACTIVE->Set__DATA(STR__READY);
		}
		ELSE_IF__CTRL_MODE(sMODE__RAMP_CTRL)
		{
			flag = Call__RAMP_CTRL(p_variable,p_alarm);

			sCH__MON_MFC_STATE->Set__DATA(STR__CONTROL);
			dCH__MON_ERROR_CHECK_ACTIVE->Set__DATA(STR__READY);
		}
		ELSE_IF__CTRL_MODE(sMODE__SET_FLOW)
		{
			flag = Call__SET_FLOW(p_variable,p_alarm);

			sCH__MON_MFC_STATE->Set__DATA(STR__CONTROL);
			dCH__MON_ERROR_CHECK_ACTIVE->Set__DATA(STR__READY);
		}
		ELSE_IF__CTRL_MODE(sMODE__PURGE)
		{
			flag = Call__PURGE(p_variable,p_alarm);

			sCH__MON_MFC_STATE->Set__DATA(STR__OPEN);
		}
		ELSE_IF__CTRL_MODE(sMODE__GAS_LINE_PURGE)
		{
			flag = Call__GAS_LINE_PURGE(p_variable,p_alarm);

			sCH__MON_MFC_STATE->Set__DATA(STR__OPEN);
		}
		ELSE_IF__CTRL_MODE(sMODE__CHM_LINE_PURGE)
		{
			flag = Call__CHM_LINE_PURGE(p_variable,p_alarm);

			sCH__MON_MFC_STATE->Set__DATA(STR__CLOSE);
		}
	}

	if((flag < 0)||(p_variable->Check__CTRL_ABORT() > 0))
	{
		// ...
		{
			int alarm_id = ALID__MFC_FLOW__CONTROL_ABORTED;
			CString alm_msg;
			CString r_act;

			alm_msg.Format("MFC [%s] command is aborted !.\n", mode);

			p_alarm->Check__ALARM(alarm_id,r_act);
			p_alarm->Post__ALARM_With_MESSAGE(alarm_id,alm_msg);
		}

		// ...
		{
			log_msg.Format("Aborted ... :  [%s], Gas_Name:[%s]",mode,var_gas_name);

			xLOG_CTRL->WRITE__LOG(log_msg);
			sCH__OBJ_MSG->Set__DATA(log_msg);
		}
	}
	else
	{
		// ...
		{
			log_msg.Format("Completed ... :  [%s], Gas_Name:[%s]",mode,var_gas_name);

			xLOG_CTRL->WRITE__LOG(log_msg);
			sCH__OBJ_MSG->Set__DATA(log_msg);
		}
	}

	return flag;
}
int CObj__MFC_IO::__CALL__MONITORING(id, p_variable, p_alarm)
{
	if(id == MON_ID__STATE_CHECK)		Mon__STATE_CHECK(p_variable,p_alarm);
	if(id == MON_ID__ERROR_CHECK)		Mon__ERROR_CHECK(p_variable,p_alarm);

	return 1;
}
