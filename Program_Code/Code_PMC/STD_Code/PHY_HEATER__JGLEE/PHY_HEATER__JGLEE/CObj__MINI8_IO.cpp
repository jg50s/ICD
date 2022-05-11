#include "StdAfx.h"
#include "CObj__MINI8_IO.h"
#include "CObj__MINI8_IO__ALID.h"

#include "CCommon_Utility.h"


//-------------------------------------------------------------------------
CObj__MINI8_IO::CObj__MINI8_IO()
{

}
CObj__MINI8_IO::~CObj__MINI8_IO()
{

}

//-------------------------------------------------------------------------
int CObj__MINI8_IO::__DEFINE__CONTROL_MODE(obj,l_mode)
{
	sObject_Name = obj;

	// ...
	{
		ADD__CTRL_VAR(sMODE__INIT,	       "INIT");
		ADD__CTRL_VAR(sMODE__ALARM_RESET,  "ALARM.RESET");

		ADD__CTRL_VAR(sMODE__HEATING_IDLE, "HEATING.IDLE");
		ADD__CTRL_VAR(sMODE__HEATING_PROC, "HEATING.PROC");

		ADD__CTRL_VAR(sMODE__POWER_OFF,    "POWER.OFF");
		
		ADD__CTRL_VAR(sMODE__STABLE_CHECK, "STABLE.CHECK");
	}
	return 1;
}
int CObj__MINI8_IO::__DEFINE__VERSION_HISTORY(version)
{

	return 1;
}


// ...
#define MON_ID__STATE_CHECK						1
#define MON_ID__IDLE_ERROR_CHECK				2
#define MON_ID__PROC_ERROR_CHECK				3


int CObj__MINI8_IO::__DEFINE__VARIABLE_STD(p_variable)
{
	DECLARE__STD_VARIABLE;

	CCommon_Error__DEF_VARIABLE m_err_def_variable;
	p_variable->Link__DEF_VARIABLE__ERROR_FEEDBACK(&m_err_def_variable);

	// ...
	CString str_name;
	CString item_list;
	int i;

	// LINK : IO_Chammel
	{
		CString def_name;
		CString def_data;

		def_name = "DATA.LOOP_SIZE";
		p_variable->Get__DEF_CONST_DATA(def_name, def_data);

		iLOOP_SIZE = atoi(def_data);
		if(iLOOP_SIZE > CFG__LOOP_SIZE)		iLOOP_SIZE = CFG__LOOP_SIZE;
	}

	// ...
	{
		str_name = "OBJ.MSG";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__OBJ_MSG, str_name);

		str_name = "OBJ.STATUS";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__OBJ_STATUS, str_name);

		str_name = "OBJ.TIMER";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__OBJ_TIMER, str_name);
	}

	// Parameter ...
	{
		// PARA ...
		{
			str_name = "PARA.LOOP.ID";
			STD__ADD_DIGITAL_WITH_X_OPTION(str_name, "1 2 3 4 5 6 7 8", "");
			LINK__VAR_DIGITAL_CTRL(dCH__PARA_LOOP_ID, str_name);

			str_name = "PARA.TARGET.SP";
			STD__ADD_ANALOG_WITH_X_OPTION(str_name, "C", 0, 0, 100, "");
			LINK__VAR_ANALOG_CTRL(aCH__PARA_TARGET_SP, str_name);
		}

		// HEATING ...
		for(i=0; i<iLOOP_SIZE; i++)
		{
			int id = i + 1;

			//
			str_name.Format("PARA.PROC.REF.SP.%02d", id);
			STD__ADD_STRING(str_name);
			LINK__VAR_STRING_CTRL(sCH__PARA_PROC_REF_SP__LOOP_X[i], str_name);

			str_name.Format("PARA.TARGET.SP.%02d", id);
			STD__ADD_ANALOG(str_name, "C", 0, 0, 100);
			LINK__VAR_ANALOG_CTRL(aCH__PARA_TARGET_SP__LOOP_X[i], str_name);

			//
			str_name.Format("CFG.TARGET.SP.%02d", id);
			STD__ADD_ANALOG_WITH_X_OPTION(str_name, "C", 0, 0, 100, "");
			LINK__VAR_ANALOG_CTRL(aCH__CFG_TARGET_SP__LOOP_X[i], str_name);
		}
	}

	// CFG : ERROR CHECK ...
	for(i=0; i<iLOOP_SIZE; i++)
	{
		int id = i + 1;

		// COMMON ...
		{
			str_name.Format("CFG.NAME.LOOP.%02d", id);
			STD__ADD_STRING_WITH_X_OPTION(str_name, "");
			LINK__VAR_STRING_CTRL(sCH__CFG_NAME__LOOP_X[i], str_name);

			str_name.Format("CFG.USE.LOOP.%02d", id);
			STD__ADD_DIGITAL_WITH_X_OPTION(str_name, "NO YES", "");
			LINK__VAR_DIGITAL_CTRL(dCH__CFG_USE__LOOP_X[i], str_name);

			//
			str_name.Format("CFG.MIN.VALUE.LOOP.%02d", id);
			STD__ADD_ANALOG_WITH_X_OPTION(str_name, "__", 0, 0, 999999, "");
			LINK__VAR_ANALOG_CTRL(aCH__CFG_MIN_VALUE__LOOP_X[i], str_name);

			str_name.Format("CFG.MAX.VALUE.LOOP.%02d", id);
			STD__ADD_ANALOG_WITH_X_OPTION(str_name, "__", 0, 0, 999999, "");
			LINK__VAR_ANALOG_CTRL(aCH__CFG_MAX_VALUE__LOOP_X[i], str_name);

			str_name.Format("CFG.DEC.VALUE.LOOP.%02d", id);
			STD__ADD_ANALOG_WITH_X_OPTION(str_name, "__", 0, 0, 6, "");
			LINK__VAR_ANALOG_CTRL(aCH__CFG_DEC_VALUE__LOOP_X[i], str_name);

			str_name.Format("CFG.UNIT.LOOP.%02d", id);
			STD__ADD_DIGITAL_WITH_X_OPTION(str_name, "C  F", "");
			LINK__VAR_DIGITAL_CTRL(dCH__CFG_UNIT__LOOP_X[i], str_name);

			str_name.Format("CFG.PV_OFFSET.LOOP.%02d", id);
			STD__ADD_ANALOG_WITH_X_OPTION(str_name, "__", 3, 0, 10, "");
			LINK__VAR_ANALOG_CTRL(aCH__CFG_PV_OFFSET__LOOP_X[i], str_name);

			//
			str_name.Format("CFG.STABLE.CHECK.TIMEOUT.LOOP.%02d", id);
			STD__ADD_ANALOG_WITH_X_OPTION(str_name, "sec", 0, 1, 1800, "");
			LINK__VAR_ANALOG_CTRL(aCH__CFG_STABLE_CHECK_TIMEOUT__LOOP_X[i], str_name);

			str_name.Format("CFG.DELAY.CHECK.TIMEOUT.LOOP.%02d", id);
			STD__ADD_ANALOG_WITH_X_OPTION(str_name, "sec", 0, 1, 1800, "");
			LINK__VAR_ANALOG_CTRL(aCH__CFG_DELAY_CHECK_TIMEOUT__LOOP_X[i], str_name);

			str_name.Format("CFG.HARD.TOLERANCE.TIMEOUT.LOOP.%02d", id);
			STD__ADD_ANALOG_WITH_X_OPTION(str_name, "sec", 0, 0, 20, "");
			LINK__VAR_ANALOG_CTRL(aCH__CFG_HARD_TOLERANCE_TIMEOUT__LOOP_X[i], str_name);

			str_name.Format("CFG.SOFT.TOLERANCE.TIMEOUT.LOOP.%02d", id);
			STD__ADD_ANALOG_WITH_X_OPTION(str_name, "sec", 0, 0, 20, "");
			LINK__VAR_ANALOG_CTRL(aCH__CFG_SOFT_TOLERANCE_TIMEOUT__LOOP_X[i], str_name);

			//
			str_name.Format("CFG.ERROR.CHECK.TIMEOUT.LOOP.%02d", id);
			STD__ADD_ANALOG_WITH_X_OPTION(str_name, "sec", 0, 1, 1800, "");
			LINK__VAR_ANALOG_CTRL(aCH__CFG_ERROR_CHECK_TIMEOUT__LOOP_X[i], str_name);

			str_name.Format("CFG.TEMP.HIGH_LIMIT.LOOP.%02d", id);
			STD__ADD_ANALOG_WITH_X_OPTION(str_name, "C", 1, 0.0, 1000.0, "");
			LINK__VAR_ANALOG_CTRL(aCH__CFG_TEMP_HIGH_LIMIT__LOOP_X[i], str_name);

			str_name.Format("CFG.OP.HIGH_LIMIT.LOOP.%02d", id);
			STD__ADD_ANALOG_WITH_X_OPTION(str_name, "%", 1, 0.0, 100.0, "");
			LINK__VAR_ANALOG_CTRL(aCH__CFG_OP_HIGH_LIMIT__LOOP_X[i], str_name);

			str_name.Format("CFG.MAX_DEVIATION.LOOP.%02d", id);
			STD__ADD_ANALOG_WITH_X_OPTION(str_name, "C", 0, 0.0, 100.0, "");
			LINK__VAR_ANALOG_CTRL(aCH__CFG_MAX_DEVIATION__LOOP_X[i], str_name);

			str_name.Format("CFG.DI.OVER_TEMP.LOOP.%02d", id);
			STD__ADD_DIGITAL_WITH_X_OPTION(str_name, "NO  YES", "");
			LINK__VAR_DIGITAL_CTRL(dCH__CFG_DI_OVER_TEMP__LOOP_X[i], str_name);

			str_name.Format("CFG.DI.HIGH_LIMIT.LOOP.%02d", id);
			STD__ADD_DIGITAL_WITH_X_OPTION(str_name, "NO  YES", "");
			LINK__VAR_DIGITAL_CTRL(dCH__CFG_DI_HIGH_LIMIT__LOOP_X[i], str_name);
		}

		// IDLE.CONDITION ...
		{
			str_name.Format("CFG.HARD.TOLERANCE.THRESHOLD.LOOP.%02d", id);
			STD__ADD_ANALOG_WITH_X_OPTION(str_name, "C", 1, 0, 100, "");
			LINK__VAR_ANALOG_CTRL(aCH__CFG_IDLE_HARD_TOLERANCE_THRESHOLD__LOOP_X[i], str_name);

			str_name.Format("CFG.SOFT.TOLERANCE.THRESHOLD.LOOP.%02d", id);
			STD__ADD_ANALOG_WITH_X_OPTION(str_name, "C", 1, 0, 100, "");
			LINK__VAR_ANALOG_CTRL(aCH__CFG_IDLE_SOFT_TOLERANCE_THRESHOLD__LOOP_X[i], str_name);
		}
		// PROC.CONDITION ...
		{
			str_name.Format("CFG.PROC.HARD.TOLERANCE.THRESHOLD.LOOP.%02d", id);
			STD__ADD_ANALOG_WITH_X_OPTION(str_name, "C", 1, 0, 100, "");
			LINK__VAR_ANALOG_CTRL(aCH__CFG_PROC_HARD_TOLERANCE_THRESHOLD__LOOP_X[i], str_name);

			str_name.Format("CFG.PROC.SOFT.TOLERANCE.THRESHOLD.LOOP.%02d", id);
			STD__ADD_ANALOG_WITH_X_OPTION(str_name, "C", 1, 0, 100, "");
			LINK__VAR_ANALOG_CTRL(aCH__CFG_PROC_SOFT_TOLERANCE_THRESHOLD__LOOP_X[i], str_name);
		}
	}

	// Interlock Config ...
	{
		str_name = "CFG.RAMPING.RATE";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "C/sec", 1, 0.1, 1.0, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_RAMPING_RATE, str_name);

		str_name = "CFG.RAMPING.RANGE";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "C", 0, 1, 40.0, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_RAMPING_RANGE, str_name);

		str_name = "CFG.RAMPING.STABLE.TIME";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "sec", 0, 0, 600, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_RAMPING_STABLE_TIME, str_name);

		//
		str_name = "CUR.RAMPING.RATE";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__CUR_RAMPING_RATE, str_name);

		str_name = "CUR.RAMPING.RANGE";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__CUR_RAMPING_RANGE, str_name);

		str_name = "CUR.RAMPING.STABLE.TIME.COUNT";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__CUR_RAMPING_STABLE_TIME_COUNT, str_name);

		//
		str_name = "CFG.HEATING.TIMEOUT";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "sec", 0, 1, 9999, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_HEATING_TIMEOUT, str_name);

		str_name = "CUR.HEATING.TIMEOUT";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__CUR_HEATING_TIMEOUT, str_name);
		
		//
		str_name = "CFG.TEMPERATURE.DIFF.MAX";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "C", 0, 1, 50, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_TEMPERATURE_DIFF_MAX, str_name);

		//
		str_name = "CFG.SP.RANGE.INTERLOCK.USE";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name, "NO YES", "");
		LINK__VAR_DIGITAL_CTRL(dCH__CFG_SP_RANGE_INTERLOCK_USE, str_name);

		str_name = "CFG.SP.RANGE.INTERLOCK.VALUE";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "C", 0, 10, 50, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_SP_RANGE_INTERLOCK_VALUE, str_name);

		//
		str_name = "CFG.ALARM.RESET.ON.TIME";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "sec", 0, 1, 60, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_ALARM_RESET_ON_TIME, str_name);

		str_name = "CUR.ALARM.RESET.ON.TIME_COUNT";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__CUR_ALARM_RESET_ON_TIME_COUNT, str_name);

		//
		str_name = "CFG.AI_ALARM.MC_OFF.LOOP.ALL";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name, "YES NO", "");
		LINK__VAR_DIGITAL_CTRL(dCH__CFG_AI_ALARM_MC_OFF__LOOP_ALL, str_name);

		str_name = "CFG.DI_ALARM.MC_OFF.LOOP.ALL";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name, "YES NO", "");
		LINK__VAR_DIGITAL_CTRL(dCH__CFG_DI_ALARM_MC_OFF__LOOP_ALL, str_name);
	}

	// IO - Output ...
	{
		for(i=0; i<iLOOP_SIZE; i++)
		{
			int id = i + 1;

			str_name.Format("MON.IO.SET.SP.LOOP.%02d", id);
			STD__ADD_ANALOG_WITH_OPTION(str_name, "C", 1, 0, 100, -1, "L", "");
			LINK__VAR_ANALOG_CTRL(aCH__MON_IO_SET_SP__LOOP_X[i], str_name);		
		}
	}
	// IO - Input ...
	{
		for(i=0; i<iLOOP_SIZE; i++)
		{
			int id = i + 1;

			str_name.Format("MON.IO.GET.PV.LOOP.%02d", id);
			STD__ADD_STRING_WITH_OPTION(str_name, -1, "L", "");
			LINK__VAR_STRING_CTRL(sCH__MON_IO_GET_PV__LOOP_X[i], str_name);

			str_name.Format("MON.IO.GET.WORKING_SP.LOOP.%02d", id);
			STD__ADD_STRING_WITH_OPTION(str_name, -1, "L", "");
			LINK__VAR_STRING_CTRL(sCH__MON_IO_GET_WORKING_SP__LOOP_X[i], str_name);

			str_name.Format("MON.IO.GET.WORKING_OP.LOOP.%02d", id);
			STD__ADD_STRING_WITH_OPTION(str_name, -1, "L", "");
			LINK__VAR_STRING_CTRL(sCH__MON_IO_GET_WORKING_OP__LOOP_X[i], str_name);

			str_name.Format("MON.IO.GET.PV_OFFSET.LOOP.%02d", id);
			STD__ADD_STRING_WITH_OPTION(str_name, -1, "L", "");
			LINK__VAR_STRING_CTRL(sCH__MON_IO_GET_PV_OFFSET__LOOP_X[i], str_name);
		
			str_name.Format("MON.IO.GET.OP_HIGH_LIMIT.LOOP.%02d", id);
			STD__ADD_STRING_WITH_OPTION(str_name, -1, "L", "");
			LINK__VAR_STRING_CTRL(sCH__MON_IO_GET_OP_HIGH_LIMIT__LOOP_X[i], str_name);
			
			str_name.Format("MON.IO.GET.FORWARD_OP.LOOP.%02d", id);
			STD__ADD_STRING_WITH_OPTION(str_name, -1, "L", "");
			LINK__VAR_STRING_CTRL(sCH__MON_IO_GET_FORWARD_OP__LOOP_X[i], str_name);
		}

		for(i=0; i<CFG__ALARM_BIT_SIZE; i++)
		{
			str_name.Format("MON.IO.GET.ALARM_STATUS.BIT.%1d", i);
			STD__ADD_STRING(str_name);
			LINK__VAR_STRING_CTRL(sCH__MON_IO_GET_ALARM_STATUS_BIT_X[i], str_name);

			str_name.Format("MON.IO.GET.ALARM_MESSAGE.BIT.%1d", i);
			STD__ADD_STRING(str_name);
			LINK__VAR_STRING_CTRL(sCH__MON_IO_GET_ALARM_MESSAGE_BIT_X[i], str_name);
		}

		str_name = "MON.IO.GET.ALARM_STATUS.ACTIVE";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_IO_GET_ALARM_STATUS_ACTIVE, str_name);
	}

	// CFG : INITIAL ...
	{
		// ...
		{
			str_name = "CFG.INITIAL.MODE";
			STD__ADD_DIGITAL_WITH_X_OPTION(str_name, "DISABLE  HEATING", "");
			LINK__VAR_DIGITAL_CTRL(dCH__CFG_INITIAL_MODE, str_name);

			//
			str_name = "CFG.INITIAL.HEATING.TIMEOUT";
			STD__ADD_ANALOG_WITH_X_OPTION(str_name, "sec", 0, 0.0, 600.0, "");
			LINK__VAR_ANALOG_CTRL(aCH__CFG_INITIAL_HEATING_TIMEOUT, str_name);
		}

		for(i=0; i<iLOOP_SIZE; i++)
		{
			int id = i + 1;

			str_name.Format("CFG.INITIAL.TARGET.TEMP.LOOP.%02d", id);
			STD__ADD_ANALOG_WITH_X_OPTION(str_name, "C", 1, 0.0, 100.0, "");
			LINK__VAR_ANALOG_CTRL(aCH__CFG_INITIAL_TARTGET_TEMP__LOOP_X[i], str_name);
		}
	}

	// CFG : MC.OFF ...
	{
		for(i=0; i<iLOOP_SIZE; i++)
		{
			int id = i + 1;

			str_name.Format("CFG.AI_ALARM.MC_OFF.LOOP.%02d", id);
			STD__ADD_DIGITAL_WITH_X_OPTION(str_name, "YES NO", "");
			LINK__VAR_DIGITAL_CTRL(dCH__CFG_AI_ALARM_MC_OFF__LOOP_X[i], str_name);

			str_name.Format("CFG.DI_ALARM.MC_OFF.LOOP.%02d", id);
			STD__ADD_DIGITAL_WITH_X_OPTION(str_name, "YES NO", "");
			LINK__VAR_DIGITAL_CTRL(dCH__CFG_DI_ALARM_MC_OFF__LOOP_X[i], str_name);
		}
	}

	// MON.ACTIVE ...
	{
		str_name = "MON.HEATING.ACTIVE";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_HEATING_ACTIVE, str_name);
	}

	// MON.STABLE_IDLE ...
	{
		for(i=0; i<iLOOP_SIZE; i++)
		{
			int id = i + 1;

			str_name.Format("MON.IDLE.ERROR.CHECK.ACTIVE.LOOP.%02d", id);
			STD__ADD_DIGITAL(str_name, "OFF ON READY");
			LINK__VAR_DIGITAL_CTRL(dCH__MON_IDLE_ERROR_CHECK_ACTIVE__LOOP_X[i], str_name);

			str_name.Format("MON.IDLE.ABORT.ACTIVE.LOOP.%02d", id);
			STD__ADD_DIGITAL(str_name, "OFF ON");
			LINK__VAR_DIGITAL_CTRL(dCH__MON_IDLE_ABORT_ACTIVE__LOOP_X[i], str_name);

			str_name.Format("MON.IDLE.STABLE.ACTIVE.LOOP.%02d", id);
			STD__ADD_DIGITAL(str_name, "OFF ON");
			LINK__VAR_DIGITAL_CTRL(dCH__MON_IDLE_STABLE_ACTIVE__LOOP_X[i], str_name);

			//
			str_name.Format("MON.IDLE.STABLE.CHECK.TIME.LOOP.%02d", id);
			STD__ADD_STRING(str_name);
			LINK__VAR_STRING_CTRL(sCH__MON_IDLE_STABLE_CHECK_TIME__LOOP_X[i], str_name);

			str_name.Format("MON.IDLE.DELAY.CHECK.TIME.LOOP.%02d", id);
			STD__ADD_STRING(str_name);
			LINK__VAR_STRING_CTRL(sCH__MON_IDLE_DELAY_CHECK_TIME__LOOP_X[i], str_name);

			str_name.Format("MON.IDLE.WARNING.MIN.LOOP.%02d", id);
			STD__ADD_STRING(str_name);
			LINK__VAR_STRING_CTRL(sCH__MON_IDLE_WARNING_MIN__LOOP_X[i], str_name);

			str_name.Format("MON.IDLE.WARNING.MAX.LOOP.%02d", id);
			STD__ADD_STRING(str_name);
			LINK__VAR_STRING_CTRL(sCH__MON_IDLE_WARNING_MAX__LOOP_X[i], str_name);

			str_name.Format("MON.IDLE.WARNING.CHECK.TIME.LOOP.%02d", id);
			STD__ADD_STRING(str_name);
			LINK__VAR_STRING_CTRL(sCH__MON_IDLE_WARNING_CHECK_TIME__LOOP_X[i], str_name);

			str_name.Format("MON.IDLE.ABORT.MIN.LOOP.%02d", id);
			STD__ADD_STRING(str_name);
			LINK__VAR_STRING_CTRL(sCH__MON_IDLE_ABORT_MIN__LOOP_X[i], str_name);

			str_name.Format("MON.IDLE.ABORT.MAX.LOOP.%02d", id);
			STD__ADD_STRING(str_name);
			LINK__VAR_STRING_CTRL(sCH__MON_IDLE_ABORT_MAX__LOOP_X[i], str_name);

			str_name.Format("MON.IDLE.ABORT.CHECK.TIME.LOOP.%02d", id);
			STD__ADD_STRING(str_name);
			LINK__VAR_STRING_CTRL(sCH__MON_IDLE_ABORT_CHECK_TIME__LOOP_X[i], str_name);
		}
	}
	// MON.STABLE_PROC ...
	{
		for(i=0; i<iLOOP_SIZE; i++)
		{
			int id = i + 1;

			str_name.Format("MON.PROC.ERROR.CHECK.ACTIVE.LOOP.%02d", id);
			STD__ADD_DIGITAL(str_name, "OFF ON READY");
			LINK__VAR_DIGITAL_CTRL(dCH__MON_PROC_ERROR_CHECK_ACTIVE__LOOP_X[i], str_name);

			str_name.Format("MON.PROC.ABORT.ACTIVE.LOOP.%02d", id);
			STD__ADD_DIGITAL(str_name, "OFF ON");
			LINK__VAR_DIGITAL_CTRL(dCH__MON_PROC_ABORT_ACTIVE__LOOP_X[i], str_name);

			str_name.Format("MON.PROC.STABLE.ACTIVE.LOOP.%02d", id);
			STD__ADD_DIGITAL(str_name, "OFF ON");
			LINK__VAR_DIGITAL_CTRL(dCH__MON_PROC_STABLE_ACTIVE__LOOP_X[i], str_name);

			//
			str_name.Format("MON.PROC.STABLE.CHECK.TIME.LOOP.%02d", id);
			STD__ADD_STRING(str_name);
			LINK__VAR_STRING_CTRL(sCH__MON_PROC_STABLE_CHECK_TIME__LOOP_X[i], str_name);

			str_name.Format("MON.PROC.DELAY.CHECK.TIME.LOOP.%02d", id);
			STD__ADD_STRING(str_name);
			LINK__VAR_STRING_CTRL(sCH__MON_PROC_DELAY_CHECK_TIME__LOOP_X[i], str_name);

			str_name.Format("MON.PROC.WARNING.MIN.LOOP.%02d", id);
			STD__ADD_STRING(str_name);
			LINK__VAR_STRING_CTRL(sCH__MON_PROC_WARNING_MIN__LOOP_X[i], str_name);

			str_name.Format("MON.PROC.WARNING.MAX.LOOP.%02d", id);
			STD__ADD_STRING(str_name);
			LINK__VAR_STRING_CTRL(sCH__MON_PROC_WARNING_MAX__LOOP_X[i], str_name);

			str_name.Format("MON.PROC.WARNING.CHECK.TIME.LOOP.%02d", id);
			STD__ADD_STRING(str_name);
			LINK__VAR_STRING_CTRL(sCH__MON_PROC_WARNING_CHECK_TIME__LOOP_X[i], str_name);

			str_name.Format("MON.PROC.ABORT.MIN.LOOP.%02d", id);
			STD__ADD_STRING(str_name);
			LINK__VAR_STRING_CTRL(sCH__MON_PROC_ABORT_MIN__LOOP_X[i], str_name);

			str_name.Format("MON.PROC.ABORT.MAX.LOOP.%02d", id);
			STD__ADD_STRING(str_name);
			LINK__VAR_STRING_CTRL(sCH__MON_PROC_ABORT_MAX__LOOP_X[i], str_name);

			str_name.Format("MON.PROC.ABORT.CHECK.TIME.LOOP.%02d", id);
			STD__ADD_STRING(str_name);
			LINK__VAR_STRING_CTRL(sCH__MON_PROC_ABORT_CHECK_TIME__LOOP_X[i], str_name);
		}
	}

	// MON.STABLE_COMMON ...
	{
		for(i=0; i<iLOOP_SIZE; i++)
		{
			int id = i + 1;

			//
			str_name.Format("MON.REF.SET.LOOP.%02d", id);
			STD__ADD_STRING(str_name);
			LINK__VAR_STRING_CTRL(sCH__MON_REF_SET__LOOP_X[i], str_name);

			//
			str_name.Format("MON.TEMP.HIGH_LIMIT.ACTIVE.LOOP.%02d", id);
			STD__ADD_STRING(str_name);
			LINK__VAR_STRING_CTRL(sCH__MON_TEMP_HIGH_LIMIT_ACTIVE__LOOP_X[i], str_name);

			str_name.Format("MON.OP.HIGH_LIMIT.ACTIVE.LOOP.%02d", id);
			STD__ADD_STRING(str_name);
			LINK__VAR_STRING_CTRL(sCH__MON_OP_HIGH_LIMIT_ACTIVE__LOOP_X[i], str_name);

			str_name.Format("MON.MAX_DEVIATION.ACTIVE.LOOP.%02d", id);
			STD__ADD_STRING(str_name);
			LINK__VAR_STRING_CTRL(sCH__MON_MAX_DEVIATION_ACTIVE__LOOP_X[i], str_name);

			//
			str_name.Format("MON.TEMP.HIGH_LIMIT.CHECK.TIME.LOOP.%02d", id);
			STD__ADD_STRING(str_name);
			LINK__VAR_STRING_CTRL(sCH__MON_TEMP_HIGH_LIMIT_CHECK_TIME__LOOP_X[i], str_name);

			str_name.Format("MON.OP.HIGH_LIMIT.CHECK.TIME.LOOP.%02d", id);
			STD__ADD_STRING(str_name);
			LINK__VAR_STRING_CTRL(sCH__MON_OP_HIGH_LIMIT_CHECK_TIME__LOOP_X[i], str_name);

			str_name.Format("MON.MAX_DEVIATION.CHECK.TIME.LOOP.%02d", id);
			STD__ADD_STRING(str_name);
			LINK__VAR_STRING_CTRL(sCH__MON_MAX_DEVIATION_CHECK_TIME_LOOP_X[i], str_name);

			//
			str_name.Format("MON.DI.OVER_TEMP.STATE.LOOP.%02d", id);
			STD__ADD_STRING(str_name);
			LINK__VAR_STRING_CTRL(sCH__MON_DI_OVER_TEMP_STATE_LOOP_X[i], str_name);

			str_name.Format("MON.DI.HIGH_LIMIT.STATE.LOOP.%02d", id);
			STD__ADD_STRING(str_name);
			LINK__VAR_STRING_CTRL(sCH__MON_DI_HIGH_LIMIT_STATE_LOOP_X[i], str_name);

			//
			str_name.Format("MON.DO.HEATER_POWER.LOOP.%02d", id);
			STD__ADD_STRING(str_name);
			LINK__VAR_STRING_CTRL(sCH__MON_DO_HEATER_POWER__LOOP_X[i], str_name);
		}

		// ...
		{
			str_name = "MON.TEMP.HIGH_LIMIT.ACTIVE.LOOP.ALL";
			STD__ADD_STRING(str_name);
			LINK__VAR_STRING_CTRL(sCH__MON_TEMP_HIGH_LIMIT_ACTIVE__LOOP_ALL, str_name);

			str_name = "MON.OP.HIGH_LIMIT.ACTIVE.LOOP.ALL";
			STD__ADD_STRING(str_name);
			LINK__VAR_STRING_CTRL(sCH__MON_OP_HIGH_LIMIT_ACTIVE__LOOP_ALL, str_name);

			str_name = "MON.MAX_DEVIATION.ACTIVE.LOOP.ALL";
			STD__ADD_STRING(str_name);
			LINK__VAR_STRING_CTRL(sCH__MON_MAX_DEVIATION_ACTIVE__LOOP_ALL, str_name);

			//
			str_name = "MON.DI.OVER_TEMP.STATE.LOOP.ALL";
			STD__ADD_STRING(str_name);
			LINK__VAR_STRING_CTRL(sCH__MON_DI_OVER_TEMP_STATE_LOOP_ALL, str_name);

			str_name = "MON.DI.HIGH_LIMIT.STATE.LOOP.ALL";
			STD__ADD_STRING(str_name);
			LINK__VAR_STRING_CTRL(sCH__MON_DI_HIGH_LIMIT_STATE_LOOP_ALL, str_name);
		}
	}

	// ...
	{
		p_variable->Add__MONITORING_PROC(3.0, MON_ID__STATE_CHECK);

		p_variable->Add__MONITORING_PROC(3.0, MON_ID__IDLE_ERROR_CHECK);
		p_variable->Add__MONITORING_PROC(3.0, MON_ID__PROC_ERROR_CHECK);
	}
	return 1;
}


// ...
#define  ACT__CLEAR								\
l_act.RemoveAll();								\
l_act.Add(STR__CLEAR);

int CObj__MINI8_IO::__DEFINE__ALARM(p_alarm)
{
	DECLARE__ALARM;

	// ...
	CString title;
	title.Format("%s : ", sObject_Name);

	CString alarm_title;
	CString alarm_msg;
	CStringArray l_act;
	int alarm_id;

	CString str_bff;
	int i;

	for(i=0; i<CFG__LOOP_SIZE; i++)
	{
		// Loop Warning ...
		{
			alarm_id = ALID__WARNING__LOOP_X + i;

			str_bff.Format("Loop%1d Warning !", i+1);

			alarm_title  = title;
			alarm_title += str_bff;

			alarm_msg  = "";
			alarm_msg += "Please, check the state of loop ! \n";

			ACT__CLEAR;

			ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
		}
		// Loop Fault ...
		{
			alarm_id = ALID__FAULT__LOOP_X + i;

			str_bff.Format("Loop%1d Fault !", i+1);

			alarm_title  = title;
			alarm_title += str_bff;

			alarm_msg  = "";
			alarm_msg += "Please, check the state of loop ! \n";

			ACT__CLEAR;

			ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
		}	

		// DI.OVER_TEMP ...
		{
			alarm_id = ALID__DI_OVER_TEMP__LOOP_X + i;

			str_bff.Format("Loop%1d Over-Temperature (DI) !", i+1);

			alarm_title  = title;
			alarm_title += str_bff;

			alarm_msg  = "";
			alarm_msg += "Please, check the state (DI) of loop ! \n";

			ACT__CLEAR;
		}
		// DI.HIGH_LIMIT ...
		{
			alarm_id = ALID__DI_HIGH_LIMIT__LOOP_X + i;

			str_bff.Format("Loop%1d High-Limit (DI) !", i+1);

			alarm_title  = title;
			alarm_title += str_bff;

			alarm_msg  = "";
			alarm_msg += "Please, check the state (DI) of loop ! \n";

			ACT__CLEAR;
		}
	}

	// ...
	{
		alarm_id = ALID__MAX_DIFF_TEMPERATURE;

		str_bff = "Max. Diff Temperature Error !";

		alarm_title  = title;
		alarm_title += str_bff;

		alarm_msg = "온도차를 확인 바랍니다. \n";

		ACT__CLEAR;

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}
	// ...
	{
		alarm_id = ALID__TEMPERATURE_HIGH_LIMIT;

		str_bff = "Temperature High Limit !";

		alarm_title  = title;
		alarm_title += str_bff;

		alarm_msg = "온도를 확인 바랍니다. \n";

		ACT__CLEAR;

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}
	// ...
	{
		alarm_id = ALID__POWER_HIGH_LIMIT;

		str_bff = "Output-Power High Limit !";

		alarm_title  = title;
		alarm_title += str_bff;

		alarm_msg = "Working Power를 확인 바랍니다. \n";

		ACT__CLEAR;

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}
	// ...
	{
		alarm_id = ALID__INITIAL_HEATING_TIMEOUT;

		str_bff = "Initial-Heating Timeout Occurred !";

		alarm_title  = title;
		alarm_title += str_bff;

		alarm_msg = "온도를 확인 바랍니다. \n";

		ACT__CLEAR;

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}
	// ...
	{
		alarm_id = ALID__HEATING_TIMEOUT;

		str_bff = "Heating Timeout Occurred !";

		alarm_title  = title;
		alarm_title += str_bff;

		alarm_msg = "온도를 확인 바랍니다. \n";

		ACT__CLEAR;

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}
	// ...
	{
		alarm_id = ALID__MAX_DEVIATION_LOOP;

		str_bff = "Max. Deviation Occurred !";

		alarm_title  = title;
		alarm_title += str_bff;

		alarm_msg = "온도를 확인 바랍니다. \n";

		ACT__CLEAR;

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	// BIT : 00...
	{
		alarm_id = ALID__HW_ALARM__BIT_00;

		str_bff = "H/W Alarm Occurred (Bit : 00) !";

		alarm_title  = title;
		alarm_title += str_bff;

		alarm_msg = "H/W Alarm(Bit : 00)이 발생 했습니다. \n";

		ACT__CLEAR;

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}
	// BIT : 01...
	{
		alarm_id = ALID__HW_ALARM__BIT_01;

		str_bff = "H/W Alarm Occurred (Bit : 01) !";

		alarm_title  = title;
		alarm_title += str_bff;

		alarm_msg = "H/W Alarm(Bit : 01)이 발생 했습니다. \n";

		ACT__CLEAR;

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}
	// BIT : 02...
	{
		alarm_id = ALID__HW_ALARM__BIT_02;

		str_bff = "H/W Alarm Occurred (Bit : 02) !";

		alarm_title  = title;
		alarm_title += str_bff;

		alarm_msg = "H/W Alarm(Bit : 02)이 발생 했습니다. \n";

		ACT__CLEAR;

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}
	// BIT : 03...
	{
		alarm_id = ALID__HW_ALARM__BIT_03;

		str_bff = "H/W Alarm Occurred (Bit : 03) !";

		alarm_title  = title;
		alarm_title += str_bff;

		alarm_msg = "H/W Alarm(Bit : 03)이 발생 했습니다. \n";

		ACT__CLEAR;

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}
	// BIT : 04...
	{
		alarm_id = ALID__HW_ALARM__BIT_04;

		str_bff = "H/W Alarm Occurred (Bit : 04) !";

		alarm_title  = title;
		alarm_title += str_bff;

		alarm_msg = "H/W Alarm(Bit : 04)이 발생 했습니다. \n";

		ACT__CLEAR;

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}
	// BIT : 05...
	{
		alarm_id = ALID__HW_ALARM__BIT_05;

		str_bff = "H/W Alarm Occurred (Bit : 05) !";

		alarm_title  = title;
		alarm_title += str_bff;

		alarm_msg = "H/W Alarm(Bit : 05)이 발생 했습니다. \n";

		ACT__CLEAR;

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}
	// BIT : 06...
	{
		alarm_id = ALID__HW_ALARM__BIT_06;

		str_bff = "H/W Alarm Occurred (Bit : 06) !";

		alarm_title  = title;
		alarm_title += str_bff;

		alarm_msg = "H/W Alarm(Bit : 06)이 발생 했습니다. \n";

		ACT__CLEAR;

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	return 1;
}

//-------------------------------------------------------------------------
int CObj__MINI8_IO::__INITIALIZE__OBJECT(p_variable,p_ext_obj_create)
{	
	// ...
	{
		CString file_name;
		CString log_msg;

		file_name.Format("%s.log", sObject_Name);

		log_msg  = "\n\n";
		log_msg += "//------------------------------------------------------------------------";

		xI_LOG_CTRL->CREATE__SUB_DIRECTORY(sObject_Name);
		xI_LOG_CTRL->SET__PROPERTY(file_name,12*1,60);

		xI_LOG_CTRL->DISABLE__TIME_LOG();
		xI_LOG_CTRL->WRITE__LOG(log_msg);

		xI_LOG_CTRL->ENABLE__TIME_LOG();
		xI_LOG_CTRL->WRITE__LOG("   START   \n");
	}

	// ...
	CString def_name;
	CString def_data;

	CString ch_name;
	CString obj_name;
	CString var_name;
	int i;

	// ...
	CCommon_Utility x_utility;

	// OBJ : DB_SYS 
	{
		def_name = "OBJ__DB_SYS";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, obj_name);

		//
		var_name = "MON.SYSTEM.PROCESS.ACTIVE";
		LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__MON_SYSTEM_PROCESS_ACTIVE, obj_name,var_name);
	}

	// LINK : IO_Chammel
	{
		def_name = "DATA.LOOP_SIZE";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, def_data);

		iLOOP_SIZE = atoi(def_data);
		if(iLOOP_SIZE > CFG__LOOP_SIZE)		iLOOP_SIZE = CFG__LOOP_SIZE;

		for(i=0; i<iLOOP_SIZE; i++)
		{
			int id = i + 1;

			// DATA : CTRL_ACTIVE
			{
				def_name.Format("DATA__CTRL_ACTIVE.%1d", id);
				p_ext_obj_create->Get__DEF_CONST_DATA(def_name, def_data);

				if(def_data.CompareNoCase(STR__YES) == 0)		bActive__CTRL_ACTIVE__LOOP_X[i] = true;
				else											bActive__CTRL_ACTIVE__LOOP_X[i] = false;
			}

			// AO : TEMPERATURE.SET
			{
				def_name.Format("CH__AO_TEMPERATURE_SET.%1d", id);
				p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
				p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);

				LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__AO_TEMPERATURE_SET__LOOP_X[i], obj_name,var_name);
			}

			// AI : TEMPERATURE.READ
			{
				def_name.Format("CH__AI_TEMPERATURE_READ.%d", id);
				p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
				p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);

				LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__AI_TEMPERATURE_READ__LOOP_X[i], obj_name,var_name);
			}
			// AI : TEMPERATURE_SET
			{
				def_name.Format("CH__AI_TEMPERATURE_SET.%d", id);
				p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);

				bool def_check = x_utility.Check__Link(ch_name);
				bActive__AI_TEMPERATURE_SET__LOOP_X[i] = def_check;
				
				if(def_check)
				{
					p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
					LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__AI_TEMPERATURE_SET__LOOP_X[i], obj_name,var_name);
				}
			}
			// AI : TEMPERATURE_POWER
			{
				def_name.Format("CH__AI_TEMPERATURE_POWER.%d", id);
				p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);

				bool def_check = x_utility.Check__Link(ch_name);
				bActive__AI_TEMPERATURE_POWER__LOOP_X[i] = def_check;

				if(def_check)
				{
					p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
					LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__AI_TEMPERATURE_POWER__LOOP_X[i], obj_name,var_name);
				}
			}
			// AI : PV.OFFSET
			{
				def_name.Format("CH__AI_PV_OFFSET.%d", id);
				p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);

				bool def_check = x_utility.Check__Link(ch_name);
				bActive__AI_PV_OFFSET__LOOP_X[i] = def_check;

				if(def_check)
				{
					p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
					LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__AI_PV_OFFSET__LOOP_X[i], obj_name,var_name);
				}

			}
			// AI : OP.HIGH_LIMIT
			{
				def_name.Format("CH__AI_OP_HIGH_LIMIT.%d", id);
				p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);

				bool def_check = x_utility.Check__Link(ch_name);
				bActive__AI_OP_HIGH_LIMIT__LOOP_X[i] = def_check;

				if(def_check)
				{
					p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
					LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__AI_OP_HIGH_LIMIT__LOOP_X[i], obj_name,var_name);
				}
			}
			// AI : OP.FORWARD
			{
				def_name.Format("CH__AI_OP_FORWARD.%d", id);
				p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);

				bool def_check = x_utility.Check__Link(ch_name);
				bActive__AI_OP_FORWARD__LOOP_X[i] = def_check;

				if(def_check)
				{
					p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
					LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__AI_OP_FORWARD__LOOP_X[i], obj_name,var_name);
				}
			}

			// DO : POWER ...
			{
				def_name.Format("CH__DO_HEATER_POWER.%1d", id);
				p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);

				bool def_check = x_utility.Check__Link(ch_name);
				bActive__DO_HEATER_POWER__LOOP_X[i] = def_check;

				if(def_check)
				{
					p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
					LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__DO_HEATER_POWER__LOOP_X[i], obj_name,var_name);
				}
			}

			// DI : OVER_TEMP
			{
				def_name.Format("CH__DI_OVER_TEMP.%d", id);
				p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);

				bool def_check = x_utility.Check__Link(ch_name);
				bActive__DI_OVER_TEMP__LOOP_X[i] = def_check;

				if(def_check)
				{
					p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
					LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__DI_OVER_TEMP__LOOP_X[i], obj_name,var_name);
				}
			}
			// DI : HIGH_LIMIT
			{
				def_name.Format("CH__DI_HIGH_LIMIT.%d", id);
				p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);

				bool def_check = x_utility.Check__Link(ch_name);
				bActive__DI_HIGH_LIMIT__LOOP_X[i] = def_check;

				if(def_check)
				{
					p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
					LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__DI_HIGH_LIMIT__LOOP_X[i], obj_name,var_name);
				}
			}
		}

		// SI : ALARM_STATE.HEXA
		{
			def_name = "CH__SI_ALARM_STATE.HEXA";
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);

			bool def_check = x_utility.Check__Link(ch_name);
			bActive__SI_ALARM_STATE_HEXA = def_check;
			
			if(bActive__SI_ALARM_STATE_HEXA)
			{
				p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
				LINK__EXT_VAR_STRING_CTRL(sEXT_CH__SI_ALARM_STATE_HEXA, obj_name,var_name);
			}
		}
		// SO : ALARM_RESET.HEXA
		{
			def_name = "CH__SO_ALARM_RESET.HEXA";
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);

			bool def_check = x_utility.Check__Link(ch_name);
			bActive__SO_ALARM_RESET_HEXA = def_check;

			if(bActive__SO_ALARM_RESET_HEXA)
			{
				p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
				LINK__EXT_VAR_STRING_CTRL(sEXT_CH__SO_ALARM_RESET_HEXA, obj_name,var_name);
			}
		}
	}

	// Parameter Setting ...
	{
		CString ch_data;

		for(i=0; i<CFG__ALARM_BIT_SIZE; i++)
		{
				 if(i == 0)			ch_data = "LP1 Temp High Alarm";
			else if(i == 1)			ch_data = "LP1 Temp Low Alarm";
			else if(i == 2)			ch_data = "LP1 Temp Deviation Alarm";
			else if(i == 3)			ch_data = "LP2 Temp High Alarm";
			else if(i == 4)			ch_data = "LP2 Temp Low Alarm";
			else if(i == 5)			ch_data = "LP2 Temp Deviation Alarm";
			else if(i == 6)			ch_data = "LP1 - L2 Deviation Alarm";
			else					ch_data.Format("Bit_%02d Active", i);

			sCH__MON_IO_GET_ALARM_MESSAGE_BIT_X[i]->Set__DATA(ch_data);
		}	

		if(bActive__SO_ALARM_RESET_HEXA)
		{
			sEXT_CH__SO_ALARM_RESET_HEXA->Set__DATA("00 00");
		}
	}

	// ...
	{
		SCX__SEQ_INFO x_seq_info;
		iActive__SIM_MODE = x_seq_info->Is__SIMULATION_MODE();
	}

	// Mon.Init ...
	{
		for(i=0; i<iLOOP_SIZE; i++)
		{
			sCH__MON_DI_OVER_TEMP_STATE_LOOP_X[i]->Set__DATA("__");
			sCH__MON_DI_HIGH_LIMIT_STATE_LOOP_X[i]->Set__DATA("__");

			sCH__MON_DO_HEATER_POWER__LOOP_X[i]->Set__DATA("__");
		}
	}

	// ACTIVE.PROC_ERROR_CHECK
	{
		def_name = "ACTIVE.PROC_ERROR_CHECK";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, def_data);

		bool def_check = x_utility.Check__Link(def_data);
		bActive__PROC_ERROR_CHECK = def_check;

		if(!def_check)
		{
			p_variable->Stop__MONITORING_PROC(MON_ID__PROC_ERROR_CHECK);

			for(i=0; i<iLOOP_SIZE; i++)
			{
				dCH__MON_PROC_ERROR_CHECK_ACTIVE__LOOP_X[i]->Set__DATA(STR__OFF);
				dCH__MON_PROC_ABORT_ACTIVE__LOOP_X[i]->Set__DATA(STR__OFF);
				dCH__MON_PROC_STABLE_ACTIVE__LOOP_X[i]->Set__DATA(STR__OFF);
			}
		}
	}

	return 1;
}

//-------------------------------------------------------------------------
int CObj__MINI8_IO::__CALL__CONTROL_MODE(mode,p_debug,p_variable,p_alarm)
{
	int flag = -1;

	// ...
	{
		CString log_msg;
		log_msg.Format("Start ... :  [%s]",mode);

		sCH__OBJ_MSG->Set__DATA(log_msg);
		xI_LOG_CTRL->WRITE__LOG(log_msg);
	}

	// ...
	{
		     IF__CTRL_MODE(sMODE__INIT)					flag = Call__INIT(p_variable, p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__ALARM_RESET)			flag = Call__ALARM_RESET(p_variable,p_alarm);

		ELSE_IF__CTRL_MODE(sMODE__HEATING_IDLE)			flag = Call__HEATING_IDLE(p_variable,p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__HEATING_PROC)			flag = Call__HEATING_PROC(p_variable,p_alarm);

		ELSE_IF__CTRL_MODE(sMODE__POWER_OFF)			flag = Call__POWER_OFF(p_variable,p_alarm);

		ELSE_IF__CTRL_MODE(sMODE__STABLE_CHECK)			flag = Call__STABLE_CHECK(p_variable,p_alarm);
	}

	if((flag < 0)||(p_variable->Check__CTRL_ABORT() > 0))
	{
		CString log_msg;
		log_msg.Format("Aborted ... :  [%s]",mode);

		sCH__OBJ_MSG->Set__DATA(log_msg);
		xI_LOG_CTRL->WRITE__LOG(log_msg);		
	}
	else
	{
		CString log_msg;
		log_msg.Format("Completed ... :  [%s]",mode);

		sCH__OBJ_MSG->Set__DATA(log_msg);
		xI_LOG_CTRL->WRITE__LOG(log_msg);
	}

	return flag;
}

int CObj__MINI8_IO::__CALL__MONITORING(id,p_variable,p_alarm)
{
	if(id == MON_ID__STATE_CHECK)			Mon__STATE_CHECK(p_variable, p_alarm);

	if(id == MON_ID__IDLE_ERROR_CHECK)		Mon__IDLE_ERROR_CHECK(p_variable, p_alarm);
	if(id == MON_ID__PROC_ERROR_CHECK)		Mon__PROC_ERROR_CHECK(p_variable, p_alarm);

	return 1;
}
