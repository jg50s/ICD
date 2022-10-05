#include "StdAfx.h"
#include "CObj__PT_IO.h"


//-------------------------------------------------------------------------
CObj__PT_IO::CObj__PT_IO()
{

}
CObj__PT_IO::~CObj__PT_IO()
{

}

//-------------------------------------------------------------------------
int CObj__PT_IO::__DEFINE__CONTROL_MODE(obj,l_mode)
{
	sObject_Name = obj;

	// ...
	{
		ADD__CTRL_VAR(sMODE__INIT, "INIT");
	}
	return 1;
}
int CObj__PT_IO::__DEFINE__VERSION_HISTORY(version)
{
	// ...
	{

	}
	return 1;
}


// ...
#define  MON_ID__STATE_CHECK			1
#define  MON_ID__PT_CHECK				2


int CObj__PT_IO::__DEFINE__VARIABLE_STD(p_variable)
{
	DECLARE__STD_VARIABLE;

	CCommon_Error__DEF_VARIABLE m_err_def_variable;
	p_variable->Link__DEF_VARIABLE__ERROR_FEEDBACK(&m_err_def_variable);

	// ...
	CString str_name;
	int i;

	// OBJ ...
	{
		str_name = "OBJ.MSG";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__OBJ_MSG, str_name);
	}

	// PT.SIZE ...
	{
		CString def_name;
		CString def_data;

		def_name = "DATA__PT_SIZE";
		p_variable->Get__DEF_CONST_DATA(def_name, def_data);

		iPT_SIZE = atoi(def_data);
		if(iPT_SIZE > _CFG__PT_MAX)			iPT_SIZE = _CFG__PT_MAX;
	}

	// MON.INFO ...
	for(i=0; i<iPT_SIZE; i++)
	{
		int id = i + 1;

		str_name.Format("MON.PRESSURE.PT.%02d", id);
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "__", 0, 0, 999999, "");
		LINK__VAR_ANALOG_CTRL(aCH__MON_PRESSURE__PT_X[i], str_name);
	}

	// CFG ...
	for(i=0; i<iPT_SIZE; i++)
	{
		int id = i + 1;

		str_name.Format("CFG.NAME.PT.%02d", id);
		STD__ADD_STRING_WITH_X_OPTION(str_name, "");
		LINK__VAR_STRING_CTRL(sCH__CFG_NAME__PT_X[i], str_name);

		str_name.Format("CFG.USE.PT.%02d", id);
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name, "NO YES", "");
		LINK__VAR_DIGITAL_CTRL(dCH__CFG_USE__PT_X[i], str_name);

		//
		str_name.Format("CFG.MIN.VALUE.PT.%02d", id);
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "__", 0, 0, 999999, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_MIN_VALUE__PT_X[i], str_name);
		
		str_name.Format("CFG.MAX.VALUE.PT.%02d", id);
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "__", 0, 0, 999999, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_MAX_VALUE__PT_X[i], str_name);
		
		str_name.Format("CFG.DEC.VALUE.PT.%02d", id);
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "__", 0, 0, 6, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_DEC_VALUE__PT_X[i], str_name);
		
		str_name.Format("CFG.UNIT.PT.%02d", id);
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name, "torr psi", "");
		LINK__VAR_DIGITAL_CTRL(dCH__CFG_UNIT__PT_X[i], str_name);

		//
		str_name.Format("CFG.SETPOINT.PT.%02d", id);
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "psi", 3, 0, 100, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_SETPOINT__PT_X[i], str_name);

		//
		str_name.Format("CFG.STABLE.CHECK.TIMEOUT.PT.%02d", id);
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "sec", 0, 1, 1800, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_STABLE_CHECK_TIMEOUT__PT_X[i], str_name);

		str_name.Format("CFG.HARD.TOLERANCE.TIMEOUT.PT.%02d", id);
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "sec", 0, 0, 20, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_HARD_TOLERANCE_TIMEOUT__PT_X[i], str_name);

		str_name.Format("CFG.SOFT.TOLERANCE.TIMEOUT.PT.%02d", id);
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "sec", 0, 0, 20, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_SOFT_TOLERANCE_TIMEOUT__PT_X[i], str_name);

		//
		str_name.Format("CFG.HARD.TOLERANCE.THRESHOLD.PT.%02d", id);
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "psi", 3, 0, 100, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_HARD_TOLERANCE_THRESHOLD__PT_X[i], str_name);

		str_name.Format("CFG.SOFT.TOLERANCE.THRESHOLD.PT.%02d", id);
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "psi", 3, 0, 100, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_SOFT_TOLERANCE_THRESHOLD__PT_X[i], str_name);
	}

	// CFG : ZERO-CAL ...
	for(i=0; i<iPT_SIZE; i++)
	{
		int id = i + 1;

		str_name.Format("ZERO_CAL.OFFSET.PT.%02d", id);
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "torr", 3, -100, 100, "");
		LINK__VAR_ANALOG_CTRL(aCH__ZERO_CAL_OFFSET__PT_X[i], str_name);

		str_name.Format("ZERO_CAL.REQ.PRESSURE.PT.%02d", id);
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__ZERO_CAL_REQ_PRESSURE__PT_X[i], str_name);

		str_name.Format("ZERO_CAL.RESET.PRESSURE.PT.%02d", id);
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__ZERO_CAL_RESET_PRESSURE__PT_X[i], str_name);
	}

	// MON.PT ...
	for(i=0; i<iPT_SIZE; i++)
	{
		int id = i + 1;

		str_name.Format("MON.ERROR.CHECK.ACTIVE.PT.%02d", id);
		STD__ADD_DIGITAL(str_name, "OFF ON READY");
		LINK__VAR_DIGITAL_CTRL(dCH__MON_ERROR_CHECK_ACTIVE__PT_X[i], str_name);

		str_name.Format("MON.ABORT.ACTIVE.PT.%02d", id);
		STD__ADD_DIGITAL(str_name, "OFF ON");
		LINK__VAR_DIGITAL_CTRL(dCH__MON_ABORT_ACTIVE__PT_X[i], str_name);

		str_name.Format("MON.STABLE.ACTIVE.PT.%02d", id);
		STD__ADD_DIGITAL(str_name, "OFF ON");
		LINK__VAR_DIGITAL_CTRL(dCH__MON_STABLE_ACTIVE__PT_X[i], str_name);

		//
		str_name.Format("MON.STABLE.CHECK.TIME.PT.%02d", id);
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_STABLE_CHECK_TIME__PT_X[i], str_name);

		str_name.Format("MON.WARNING.MIN.PT.%02d", id);
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_WARNING_MIN__PT_X[i], str_name);

		str_name.Format("MON.WARNING.MAX.PT.%02d", id);
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_WARNING_MAX__PT_X[i], str_name);

		str_name.Format("MON.WARNING.CHECK.TIME.PT.%02d", id);
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_WARNING_CHECK_TIME__PT_X[i], str_name);

		str_name.Format("MON.ABORT.MIN.PT.%02d", id);
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_ABORT_MIN__PT_X[i], str_name);

		str_name.Format("MON.ABORT.MAX.PT.%02d", id);
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_ABORT_MAX__PT_X[i], str_name);

		str_name.Format("MON.ABORT.CHECK.TIME.PT.%02d", id);
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_ABORT_CHECK_TIME__PT_X[i], str_name);
	}

	// ...
	{
		p_variable->Add__MONITORING_PROC(1.0, MON_ID__STATE_CHECK);
		p_variable->Add__MONITORING_PROC(1.0, MON_ID__PT_CHECK);
	}
	return 1;
}

int CObj__PT_IO::__DEFINE__ALARM(p_alarm)
{
	DECLARE__ALARM;

	// ...
	CString title;
	title.Format("%s - ",sObject_Name);

	// ...
	int alm_id;
	CString alm_title;
	CString alm_msg;
	CString alm_bff;
	CStringArray l_act;

	for(int i=0; i<_CFG__PT_MAX; i++)
	{
		// PT.Warning ...
		{
			alm_id = ALID__PRESSURE_TRANSMITTER__THRESHOLD_WARNING + i;

			alm_title  = title;
			alm_bff.Format("PT%1d Threshold Warning.", i+1);
			alm_title += alm_bff;

			alm_msg = "PT was over threshold warning range. \n";

			l_act.RemoveAll();
			l_act.Add(ACT__CLEAR);

			ADD__ALARM_EX(alm_id, alm_title, alm_msg, l_act);
		}

		// PT.Abort ...
		{
			alm_id = ALID__PRESSURE_TRANSMITTER__THRESHOLD_ABORT + i;

			alm_title  = title;
			alm_bff.Format("PT%1d Threshold Abort.", i+1);
			alm_title += alm_bff;

			alm_msg = "PT was over threshold abort range. \n";

			l_act.RemoveAll();
			l_act.Add(ACT__CLEAR);

			ADD__ALARM_EX(alm_id, alm_title, alm_msg, l_act);
		}
	}

	return 1;
}

int CObj__PT_IO::__Define__USER_FUNCTION(CII_DEFINE__FUNCTION *p_fnc_ctrl)
{
	p_fnc_ctrl->Link__ERROR_FEEDBACK(&mERROR__USER_FNC);

	//
	return 1;
}

//-------------------------------------------------------------------------
int CObj__PT_IO::__INITIALIZE__OBJECT(p_variable,p_ext_obj_create)
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

	// DB_SYS ...
	{
		def_name = "OBJ__DB_SYS";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, obj_name);

		// ...
		{
			var_name = "CFG.PMC.ATM_MAINT.ACTIVE";
			LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__CFG_PMC_ATM_MAINT_ACTIVE, obj_name,var_name);

			//
			var_name = "MON.SYSTEM.PROCESS.ACTIVE";
			LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__MON_SYSTEM_PROCESS_ACTIVE, obj_name,var_name);
		}
	}

	// PT ...
	{
		def_name = "DATA__PT_SIZE";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, def_data);

		iPT_SIZE = atoi(def_data);
		if(iPT_SIZE > _CFG__PT_MAX)			iPT_SIZE = _CFG__PT_MAX;

		for(int i=0; i<iPT_SIZE; i++)
		{
			int id = i + 1;

			def_name.Format("CH__IO_PT.%1d", id);
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
			p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
			LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__AI_PT_PRESSURE_X[i], obj_name,var_name);
		}
	}

	// ...
	{
		SCX__SEQ_INFO x_seq;

		iActive__SIM_MODE = x_seq->Is__SIMULATION_MODE();
	}
	return 1;
}

//-------------------------------------------------------------------------
int CObj__PT_IO::__CALL__CONTROL_MODE(mode,p_debug,p_variable,p_alarm)
{
	DECLARE__EXT_CTRL(p_variable);

	int flag = -1;

	CString log_msg;
	CString log_bff;

	// ...
	{
		log_msg.Format("Start [%s] ... By %s", mode, p_ext_mode_ctrl->Get__UPPER_OBJECT_NAME());

		sCH__OBJ_MSG->Set__DATA(log_msg);
		xLOG_CTRL->WRITE__LOG(log_msg);
	}

	// ...
	{
		IF__CTRL_MODE(sMODE__INIT)
		{
			flag = Call__INIT(p_variable,p_alarm);
		}
	}

	if((flag < 0)||(p_variable->Check__CTRL_ABORT() > 0))
	{
		// ...
		{
			log_msg.Format("Aborted ... :  [%s]", mode);

			xLOG_CTRL->WRITE__LOG(log_msg);
			sCH__OBJ_MSG->Set__DATA(log_msg);
		}
	}
	else
	{
		// ...
		{
			log_msg.Format("Completed ... :  [%s]", mode);

			xLOG_CTRL->WRITE__LOG(log_msg);
			sCH__OBJ_MSG->Set__DATA(log_msg);
		}
	}

	return flag;
}
int CObj__PT_IO::__CALL__MONITORING(id, p_variable, p_alarm)
{
	if(id == MON_ID__STATE_CHECK)		Mon__STATE_CHECK(p_variable,p_alarm);
	if(id == MON_ID__PT_CHECK)			Mon__PT_CHECK(p_variable,p_alarm);

	return 1;
}
