#include "StdAfx.h"
#include "CObj__STEP_STD.h"

#include "CCommon_Utility.h"


//-------------------------------------------------------------------------
CObj__STEP_STD::CObj__STEP_STD()
{

}
CObj__STEP_STD::~CObj__STEP_STD()
{

}

//-------------------------------------------------------------------------
int CObj__STEP_STD::__DEFINE__CONTROL_MODE(obj,l_mode)
{
	sObject_Name = obj;

	// ...
	{
		ADD__CTRL_VAR(sMODE__INIT,	"INIT");

		ADD__CTRL_VAR(sMODE__READY,	"READY");
		ADD__CTRL_VAR(sMODE__START, "START");
		ADD__CTRL_VAR(sMODE__PROC,	"PROC");
		ADD__CTRL_VAR(sMODE__ABORT,	"ABORT");
		ADD__CTRL_VAR(sMODE__END,	"END");
	}
	return 1;
}
int CObj__STEP_STD::__DEFINE__VERSION_HISTORY(version)
{

	return 1;
}


// ...
#define  APP_DSP__DISABLE_ENABLE					\
"DISABLE ENABLE"

#define  APP_DSP__ENABLE_DISABLE					\
"ENABLE DISABLE"


// ...
#define  MON_ID__MONITOR				1


int CObj__STEP_STD::__DEFINE__VARIABLE_STD(p_variable)
{
	DECLARE__STD_VARIABLE;

	// ...
	CCommon_Error__DEF_VARIABLE m_err_def_variable;
	p_variable->Link__DEF_VARIABLE__ERROR_FEEDBACK(&m_err_def_variable);

	// ...
	CString var_name;
	CString list_item;
	int i;

	// OBJ ...
	{
		var_name = "OBJ.MSG";
		STD__ADD_STRING(var_name);
		LINK__VAR_STRING_CTRL(sCH__OBJ_MSG, var_name);

		var_name = "OBJ.SUB.MSG";
		STD__ADD_STRING(var_name);
		LINK__VAR_STRING_CTRL(sCH__OBJ_SUB_MSG, var_name);
	}

	// INFO ...
	{
		var_name = "INFO.STEP.CUR_NUM";
		STD__ADD_STRING(var_name);
		LINK__VAR_STRING_CTRL(sCH__INFO_STEP_CUR_NUM, var_name);

		var_name = "INFO.STEP.PRE_TIME";
		STD__ADD_STRING(var_name);
		LINK__VAR_STRING_CTRL(sCH__INFO_STEP_PRE_TIME, var_name);
	}

	// MON ...
	{
		var_name = "MON.STEP.EXCEPTION.ACT";
		STD__ADD_STRING(var_name);
		LINK__VAR_STRING_CTRL(sCH__MON_STEP_EXCEPTION_ACT, var_name);
	}

	// CFG ...
	{
		var_name = "CFG.STEP.ALARM_TEST.ACTIVE";
		STD__ADD_DIGITAL(var_name, "OFF ON");
		LINK__VAR_DIGITAL_CTRL(dCH__CFG_STEP_ALARM_TEST_ACTIVE, var_name);

		//
		var_name = "CFG.STEP.STABLE.MIN.SEC";
		STD__ADD_ANALOG_WITH_X_OPTION(var_name, "sec", 1, 0, 5, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_STEP_STABLE_MIN_SEC, var_name);

		var_name = "CFG.STEP.OBJECT_OVER_TIME.ERRPR_REF.SEC";
		STD__ADD_ANALOG_WITH_X_OPTION(var_name, "sec", 2, 0.05, 1.0, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_STEP_OBJECT_OVER_TIME_ERRPR_REF_SEC, var_name);

		var_name = "CFG.CHM.PRESSURE.HIGH.LIMIT";
		STD__ADD_ANALOG_WITH_X_OPTION(var_name, "torr", 0, 1, 900, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_CHM_PRESSURE_HIGH_LIMIT, var_name);

		//
		var_name = "CFG.STEP_DELAY.RF_OFF";
		STD__ADD_ANALOG_WITH_X_OPTION(var_name, "sec", 1, 0, 2, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_STEP_DELAY_RF_OFF, var_name);

		var_name = "CFG.STEP_DELAY.MFC_CLOSE";
		STD__ADD_ANALOG_WITH_X_OPTION(var_name, "sec", 1, 0, 2, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_STEP_DELAY_MFC_CLOSE, var_name);

		//
		var_name = "CFG.STEP_READY.HEATER.MODE";
		STD__ADD_DIGITAL_WITH_X_OPTION(var_name, "DISABLE  ONLY.CHECK  CONTROL", "");
		LINK__VAR_DIGITAL_CTRL(dCH__CFG_STEP_READY_HEATER_MODE, var_name);

		var_name = "CFG.STEP_READY.CHECK.TIME.MIN";
		STD__ADD_ANALOG_WITH_X_OPTION(var_name, "sec", 0, 1, 10, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_STEP_READY_CHECK_TIME_MIN, var_name);

		var_name = "CFG.STEP_READY.CHECK.TIME.MAX";
		STD__ADD_ANALOG_WITH_X_OPTION(var_name, "sec", 0, 5, 100, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_STEP_READY_CHECK_TIME_MAX, var_name);

		//
		var_name = "CFG.STEP_CTRL.HEATER.MODE";
		STD__ADD_DIGITAL_WITH_X_OPTION(var_name, "DISABLE  ONLY.CHECK", "");
		LINK__VAR_DIGITAL_CTRL(dCH__CFG_STEP_CTRL_HEATER_MODE, var_name);

		var_name = "CFG.STEP_CTRL.ERROR.CONTROL";
		STD__ADD_DIGITAL_WITH_X_OPTION(var_name, "DISABLE  ENABLE", "");
		LINK__VAR_DIGITAL_CTRL(dCH__CFG_STEP_CTRL_ERROR_CONTROL, var_name);
	}

	// CFG.PARTx ...
	{
		var_name = "CFG.RCP.PART.USE.RFx_RPS";	
		STD__ADD_DIGITAL_WITH_X_OPTION(var_name, "YES  NO", "");
		LINK__VAR_DIGITAL_CTRL(dCH__CFG_RCP_PART_USE_RFx_RPS, var_name);

		var_name = "CFG.RCP.PART.USE.RFx_PULSE";	
		STD__ADD_DIGITAL_WITH_X_OPTION(var_name, "YES  NO", "");
		LINK__VAR_DIGITAL_CTRL(dCH__CFG_RCP_PART_USE_RFx_PULSE, var_name);

		var_name = "CFG.RCP.PART.USE.RFx_HF";	
		STD__ADD_DIGITAL_WITH_X_OPTION(var_name, "YES  NO", "");
		LINK__VAR_DIGITAL_CTRL(dCH__CFG_RCP_PART_USE_RFx_HF, var_name);

		var_name = "CFG.RCP.PART.USE.RFx_LF";	
		STD__ADD_DIGITAL_WITH_X_OPTION(var_name, "YES  NO", "");
		LINK__VAR_DIGITAL_CTRL(dCH__CFG_RCP_PART_USE_RFx_LF, var_name);

		//
		var_name = "CFG.RCP.PART.USE.MATx_HF";	
		STD__ADD_DIGITAL_WITH_X_OPTION(var_name, "YES  NO", "");
		LINK__VAR_DIGITAL_CTRL(dCH__CFG_RCP_PART_USE_MATx_HF, var_name);

		var_name = "CFG.RCP.PART.USE.MATx_LF";	
		STD__ADD_DIGITAL_WITH_X_OPTION(var_name, "YES  NO", "");
		LINK__VAR_DIGITAL_CTRL(dCH__CFG_RCP_PART_USE_MATx_LF, var_name);

		//
		var_name = "CFG.RCP.PART.USE.APC";	
		STD__ADD_DIGITAL_WITH_X_OPTION(var_name, "YES  NO", "");
		LINK__VAR_DIGITAL_CTRL(dCH__CFG_RCP_PART_USE_APC, var_name);
	}

	// CFG.PROCESS_END ...
	{
		var_name = "CFG.PROCESS_END.STATE.RFx_PULSE";	
		STD__ADD_DIGITAL_WITH_X_OPTION(var_name, "NO.CHANGE  NORMAL  INVERSE  OFF", "");
		LINK__VAR_DIGITAL_CTRL(dCH__CFG_PROCESS_END_STATE_RFx_PULSE, var_name);

		//
		var_name = "CFG.PROCESS_END.FREQUENCY.RFx_PULSE";	
		STD__ADD_ANALOG_WITH_X_OPTION(var_name, "hz", 0, 0, 5000, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_PROCESS_END_FREQUENCY_RFx_PULSE, var_name);

		var_name = "CFG.PROCESS_END.DUTY.RFx_PULSE";	
		STD__ADD_ANALOG_WITH_X_OPTION(var_name, "%", 0, 0, 100, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_PROCESS_END_DUTY_RFx_PULSE, var_name);

		//
		var_name = "CFG.PROCESS_END.ON_SHIFT.RFx_PULSE";	
		STD__ADD_ANALOG_WITH_X_OPTION(var_name, "usec", 0, -1000, 1000, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_PROCESS_END_ON_SHIFT_RFx_PULSE, var_name);

		var_name = "CFG.PROCESS_END.OFF_SHIFT.RFx_PULSE";	
		STD__ADD_ANALOG_WITH_X_OPTION(var_name, "usec", 0, -1000, 1000, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_PROCESS_END_OFF_SHIFT_RFx_PULSE, var_name);	
	}

	// RCP ...
	{
		// STEP ...
		{
			var_name = "RCP.STEP.MESSAGE";
			STD__ADD_STRING_WITH_OPTION(var_name, 0, "E", "");
			LINK__VAR_STRING_CTRL(sCH__RCP_STEP_MESSAGE, var_name);

			var_name = "RCP.STEP.MODE";
			STD__ADD_DIGITAL_WITH_OPTION(var_name, "Time  Stable  High.Vac  OverEtch  EndPT  End", -1, "E", "");
			LINK__VAR_DIGITAL_CTRL(dCH__RCP_STEP_MODE, var_name);

			var_name = "RCP.STEP.TIME";
			STD__ADD_ANALOG_WITH_OPTION(var_name, "sec", 1, 0, 9999, -1, "E", "");
			LINK__VAR_ANALOG_CTRL(aCH__RCP_STEP_TIME, var_name);

			var_name = "RCP.STEP.OVERETCH.PERCENT";
			STD__ADD_ANALOG_WITH_OPTION(var_name, "%", 1, 0, 100, -1, "E", "");
			LINK__VAR_ANALOG_CTRL(aCH__RCP_STEP_OVERETCH_PERCENT, var_name);
		}

		// APC ...
		{
			var_name = "RCP.APC.MODE";		
			STD__ADD_DIGITAL_WITH_OPTION(var_name, "POSITION PRESSURE", -1, "E", "");
			LINK__VAR_DIGITAL_CTRL(dCH__RCP_APC_MODE, var_name);

			//
			var_name = "RCP.APC.PRESSURE.mTORR";		
			STD__ADD_ANALOG_WITH_OPTION(var_name, "mtorr", 0, 0.0, 10000.0, -1, "E", "");
			LINK__VAR_ANALOG_CTRL(aCH__RCP_APC_PRESSURE_mTORR, var_name);

			//
			var_name = "RCP.APC.POSITION";		
			STD__ADD_ANALOG_WITH_OPTION(var_name, "%", 1, 0.0, 100.0, -1, "E", "");
			LINK__VAR_ANALOG_CTRL(aCH__RCP_APC_POSITION, var_name);

			var_name = "RCP.APC.LEARNED.POS";
			STD__ADD_STRING_WITH_OPTION(var_name, 0, "E", "");
			LINK__VAR_STRING_CTRL(sCH__RCP_APC_LEARNED_POS, var_name);

			var_name = "RCP.APC.HOLD.DELAY";
			STD__ADD_STRING_WITH_OPTION(var_name, 0, "E", "");
			LINK__VAR_STRING_CTRL(sCH__RCP_APC_HOLD_DELAY, var_name);
		}

		// DGF ...
		{
			var_name = "RCP.DGF.CENTER.PERCENT";
			STD__ADD_ANALOG_WITH_OPTION(var_name, "%", 1, 0.0, 100.0, -1, "E", "");
			LINK__VAR_ANALOG_CTRL(aCH__RCP_DGF_CENTER_PERCENT, var_name);
		}

		// MFC ...
		for(i=0; i<_CFG__MFC_SIZE; i++)
		{
			var_name.Format("RCP.GAS.%02d.FLOW", i+1);
			STD__ADD_STRING_WITH_OPTION(var_name, -1, "E", "");
			LINK__VAR_STRING_CTRL(sCH__RCP_GAS_FLOW_X[i], var_name);
		}

		// RF.RPS ...
		{
			var_name = "RCP.RF.RPS.POWER";
			STD__ADD_STRING_WITH_OPTION(var_name, -1, "E", "");
			LINK__VAR_STRING_CTRL(sCH__RCP_RF_RPS_POWER, var_name);
		}
		// RF.LF ...
		{
			var_name = "RCP.RF.LF.POWER";
			STD__ADD_STRING_WITH_OPTION(var_name, -1, "E", "");
			LINK__VAR_STRING_CTRL(sCH__RCP_RF_LF_POWER, var_name);

			var_name = "RCP.RF.LF.MODE";
			STD__ADD_DIGITAL_WITH_X_OPTION(var_name, "CW  Pulse", "");
			LINK__VAR_DIGITAL_CTRL(dCH__RCP_RF_LF_MODE, var_name);
		}
		// RF.HF ...
		{
			var_name = "RCP.RF.HF.POWER";
			STD__ADD_STRING_WITH_OPTION(var_name, -1, "E", "");
			LINK__VAR_STRING_CTRL(sCH__RCP_RF_HF_POWER, var_name);

			var_name = "RCP.RF.HF.P2";
			STD__ADD_STRING_WITH_OPTION(var_name, -1, "E", "");
			LINK__VAR_STRING_CTRL(sCH__RCP_RF_HF_P2, var_name);

			//
			var_name = "RCP.RF.HF.MODE";
			STD__ADD_DIGITAL_WITH_X_OPTION(var_name, "CW  Pulse", "");
			LINK__VAR_DIGITAL_CTRL(dCH__RCP_RF_HF_MODE, var_name);
		}
		// RF.PULSE ...
		{
			var_name = "RCP.RF.PULSE.FREQUENCY";
			STD__ADD_ANALOG_WITH_OPTION(var_name, "hz", 0, 0, 5000, -1, "E", "");
			LINK__VAR_ANALOG_CTRL(aCH__RCP_RF_PULSE_FREQUENCY, var_name);

			//
			var_name = "RCP.RF.PULSE.DUTY";
			STD__ADD_ANALOG_WITH_OPTION(var_name, "%", 0, 0, 100, -1, "E", "");
			LINK__VAR_ANALOG_CTRL(aCH__RCP_RF_PULSE_DUTY, var_name);

			//
			var_name = "RCP.RF.PULSE.EXEC";
			STD__ADD_DIGITAL_WITH_OPTION(var_name, "NORMAL  INVERSE  OFF  HIGH  LOW", -1, "E", "");
			LINK__VAR_DIGITAL_CTRL(dCH__RCP_RF_PULSE_EXEC, var_name);

			//
			var_name = "RCP.RF.PULSE.ON_SHIFT_TIME";
			STD__ADD_ANALOG_WITH_OPTION(var_name, "usec", 0, -1000, 1000, -1, "E", "");
			LINK__VAR_ANALOG_CTRL(aCH__RCP_RF_PULSE_ON_SHIFT_TIME, var_name);

			var_name = "RCP.RF.PULSE.OFF_SHIFT_TIME";
			STD__ADD_ANALOG_WITH_OPTION(var_name, "usec", 0, -1000, 1000, -1, "E", "");
			LINK__VAR_ANALOG_CTRL(aCH__RCP_RF_PULSE_OFF_SHIFT_TIME, var_name);
		}

		// MAT.LF ...
		{
			var_name = "RCP.MAT.LF.SHUNT";
			STD__ADD_STRING_WITH_OPTION(var_name, -1, "E", "");
			LINK__VAR_STRING_CTRL(sCH__RCP_MAT_LF_SHUNT, var_name);

			var_name = "RCP.MAT.LF.SERIES";
			STD__ADD_STRING_WITH_OPTION(var_name, -1, "E", "");
			LINK__VAR_STRING_CTRL(sCH__RCP_MAT_LF_SERIES, var_name);

			//
			var_name = "RCP.MAT.LF.LEARNED.SHUNT";
			STD__ADD_STRING_WITH_OPTION(var_name, -1, "E", "");
			LINK__VAR_STRING_CTRL(sCH__RCP_MAT_LF_LEARNED_SHUNT, var_name);

			var_name = "RCP.MAT.LF.LEARNED.SERIES";
			STD__ADD_STRING_WITH_OPTION(var_name, -1, "E", "");
			LINK__VAR_STRING_CTRL(sCH__RCP_MAT_LF_LEARNED_SERIES, var_name);
		}
		// MAT.HF ...
		{
			var_name = "RCP.MAT.HF.SHUNT";
			STD__ADD_STRING_WITH_OPTION(var_name, -1, "E", "");
			LINK__VAR_STRING_CTRL(sCH__RCP_MAT_HF_SHUNT, var_name);

			var_name = "RCP.MAT.HF.SERIES";
			STD__ADD_STRING_WITH_OPTION(var_name, -1, "E", "");
			LINK__VAR_STRING_CTRL(sCH__RCP_MAT_HF_SERIES, var_name);

			//
			var_name = "RCP.MAT.HF.LEARNED.SHUNT";
			STD__ADD_STRING_WITH_OPTION(var_name, -1, "E", "");
			LINK__VAR_STRING_CTRL(sCH__RCP_MAT_HF_LEARNED_SHUNT, var_name);

			var_name = "RCP.MAT.HF.LEARNED.SERIES";
			STD__ADD_STRING_WITH_OPTION(var_name, -1, "E", "");
			LINK__VAR_STRING_CTRL(sCH__RCP_MAT_HF_LEARNED_SERIES, var_name);
		}

		// ESC ...
		{
			var_name = "RCP.ESC.CTRL.MODE";
			list_item = "NoChange Chuck Chuck1 Chuck2 He.Set Dechuck Dechuck1 Dechuck2";
			STD__ADD_DIGITAL_WITH_OPTION(var_name, list_item, -1, "E", "");
			LINK__VAR_DIGITAL_CTRL(dCH__RCP_ESC_CTRL_MODE, var_name);

			// CENTER ...
			var_name = "RCP.DPC.CENTER.PRESSURE";
			STD__ADD_STRING_WITH_OPTION(var_name, -1, "E", "");
			LINK__VAR_STRING_CTRL(sCH__RCP_DPC_CENTER_PRESSURE, var_name);

			// EDGE ...
			var_name = "RCP.DPC.EDGE.PRESSURE";
			STD__ADD_STRING_WITH_OPTION(var_name, -1, "E", "");
			LINK__VAR_STRING_CTRL(sCH__RCP_DPC_EDGE_PRESSURE, var_name);
		}

		// LIFT_PIN ...
		{
			var_name = "RCP.LIFT_PIN.MODE";
			STD__ADD_DIGITAL_WITH_OPTION(var_name, "Down Middle Up", -1, "E", "");
			LINK__VAR_DIGITAL_CTRL(dCH__RCP_LIFT_PIN_MODE, var_name);
		}

		// EPD ...
		{
			list_item = "Idle OverValue.Check UnderValue.Check OverValue.Slope UnderValue.Slope Error.Check ValueChange ValueSlope PercentChange PercentSlope";

			var_name = "RCP.EPD.EPD_MODE";
			STD__ADD_DIGITAL_WITH_OPTION(var_name, list_item, -1, "E", "");
			LINK__VAR_DIGITAL_CTRL(dCH__RCP_EPD_EPD_MODE, var_name);

			//
			var_name = "RCP.EPD.VALUE_TO_CHANGE";
			STD__ADD_ANALOG_WITH_OPTION(var_name, "intensity", 1, -1000, 1000, -1, "E", "");
			LINK__VAR_ANALOG_CTRL(aCH__RCP_EPD_VALUE_TO_CHANGE, var_name);

			var_name = "RCP.EPD.PERCENT_TO_CHANGE";
			STD__ADD_ANALOG_WITH_OPTION(var_name, "%", 1, -100, 100, -1, "E", "");
			LINK__VAR_ANALOG_CTRL(aCH__RCP_EPD_PERCENT_TO_CHANGE, var_name);

			//
			var_name = "RCP.EPD.DELAY_TIME";
			STD__ADD_ANALOG_WITH_OPTION(var_name, "sec", 1, 0.0, 30, -1, "E", "");
			LINK__VAR_ANALOG_CTRL(aCH__RCP_EPD_DELAY_TIME, var_name);

			var_name = "RCP.EPD.NORMALIZE_TIME";
			STD__ADD_ANALOG_WITH_OPTION(var_name, "sec", 1, 0.0, 10, -1, "E", "");
			LINK__VAR_ANALOG_CTRL(aCH__RCP_EPD_NORMALIZE_TIME, var_name);

			//
			var_name = "RCP.EPD.MIN_TIME";
			STD__ADD_ANALOG_WITH_OPTION(var_name, "sec", 1, 0.0, 100, -1, "E", "");
			LINK__VAR_ANALOG_CTRL(aCH__RCP_EPD_MIN_TIME, var_name);

			var_name = "RCP.EPD.MAX_TIME";
			STD__ADD_ANALOG_WITH_OPTION(var_name, "sec", 1, 0.0, 100, -1, "E", "");
			LINK__VAR_ANALOG_CTRL(aCH__RCP_EPD_MAX_TIME, var_name);

			//
			var_name = "RCP.EPD.MIN_THRESHOLD";
			STD__ADD_ANALOG_WITH_OPTION(var_name, "intensity", 1, 0.0, 1000, -1, "E", "");
			LINK__VAR_ANALOG_CTRL(aCH__RCP_EPD_MIN_THRESHOLD, var_name);

			var_name = "RCP.EPD.MAX_THRESHOLD";
			STD__ADD_ANALOG_WITH_OPTION(var_name, "intensity", 1, 0.0, 1000, -1, "E", "");
			LINK__VAR_ANALOG_CTRL(aCH__RCP_EPD_MAX_THRESHOLD, var_name);

			//
			var_name = "RCP.EPD.SLOPE_VALUE";
			STD__ADD_ANALOG_WITH_OPTION(var_name, "slope", 1, 0.1, 1.0, -1, "E", "");
			LINK__VAR_ANALOG_CTRL(aCH__RCP_EPD_SLOPE_VALUE, var_name);

			var_name = "RCP.EPD.SLOPE_TYPE";
			STD__ADD_DIGITAL_WITH_OPTION(var_name, "Up Down Flat UpToFlat DownToFlat", -1, "E", "");
			LINK__VAR_DIGITAL_CTRL(dCH__RCP_EPD_SLOPE_TYPE, var_name);

			var_name = "RCP.EPD.SLOPE_VALID_TIME";
			STD__ADD_ANALOG_WITH_OPTION(var_name, "sec", 1, 0.5, 5.0, -1, "E", "");
			LINK__VAR_ANALOG_CTRL(aCH__RCP_EPD_SLOPE_VALID_TIME, var_name);
		}
	}

	// ...
	{
		p_variable->Add__MONITORING_PROC(1.0,MON_ID__MONITOR);
	}
	return 1;
}

int CObj__STEP_STD::__DEFINE__ALARM(p_alarm)
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
		alarm_id = ALID__STEP_OVERTIME;
		alarm_title  = title;
		alarm_title += "STEP OVERTIME ALARM.";

		alarm_msg = "Process Step Time-Over Alarm Message.\n";
		alarm_msg += "Check Process Step time and Control time.";

		l_act.RemoveAll();
		l_act.Add(ACT__CLEAR);

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	// ...
	{
		alarm_id = ALID__STABLE_OVERTIME;
		alarm_title  = title;
		alarm_title += "STABLE OVERTIME ALARM.";

		alarm_msg = "Process Stable Step Time-over Alarm Message.\n";
		alarm_msg += "Check Process Stable Step time and Control time.";

		l_act.RemoveAll();
		l_act.Add(ACT__CLEAR);

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	// ...
	{
		alarm_id = ALID__OBJECT_OVERTIME;

		alarm_title  = title;
		alarm_title += "OBJECT OVERTIME ALARM.";

		alarm_msg  = "Object control time must be less than process step time ! \n";

		l_act.RemoveAll();
		l_act.Add(ACT__CLEAR);

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	// ...
	{
		alarm_id = ALID__STEP_READY__TEMPERATURE_STABLE_TIMEOUT_ERROR;

		alarm_title  = title;
		alarm_title += "Temperature stable timeout error In the step preparation.";

		alarm_msg = "Please, check the current temperature of system and temperature parameter in 1st step recipe ! \n";

		l_act.RemoveAll();
		l_act.Add(ACT__CLEAR);

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}
	// ...
	{
		alarm_id = ALID__STEP_READY__TEMPERATURE_STABLE_TIMEOUT_WARNING;

		alarm_title  = title;
		alarm_title += "Temperature stable timeout warning In the step preparation.";

		alarm_msg = "Please, check the current temperature of system and temperature parameter in 1st step recipe ! \n";

		l_act.RemoveAll();
		l_act.Add(ACT__CLEAR);

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	// ...
	{
		alarm_id = ALID__STEP_PARAMETER__SETTING_ERROR;

		alarm_title  = title;
		alarm_title += "Step parameter setting error !";

		alarm_msg = "Please, check the step parameter in recipe. \n";

		l_act.RemoveAll();
		l_act.Add(ACT__CLEAR);

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	return 1;
}

int CObj__STEP_STD::__Define__USER_FUNCTION(CII_DEFINE__FUNCTION *p_fnc_ctrl)
{
	p_fnc_ctrl->Link__ERROR_FEEDBACK(&mERROR__USER_FNC);

	return 1;
}

//-------------------------------------------------------------------------
int CObj__STEP_STD::__INITIALIZE__OBJECT(p_variable,p_ext_obj_create)
{
	CString def_name;
	CString def_data;
	CString ch_name;
	CString obj_name;
	CString var_name;
	int i;

	// ...
	{
		CString file_name;
		CString log_msg;

		file_name.Format("%s.log",sObject_Name);

		log_msg  = "\n\n";
		log_msg += "//------------------------------------------------------------------------";

		xLOG_CTRL->CREATE__SUB_DIRECTORY(sObject_Name);
		xLOG_CTRL->SET__PROPERTY(file_name, 24*5, 60);

		xLOG_CTRL->DISABLE__TIME_LOG();
		xLOG_CTRL->WRITE__LOG(log_msg);

		xLOG_CTRL->ENABLE__TIME_LOG();
		xLOG_CTRL->WRITE__LOG("   START   \n");
	}

	// ...
	CCommon_Utility x_utility;
	bool def_check;

	// DB INF ...
	{
		def_name = "OBJ__DB_INF";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name,obj_name);

		//
		var_name = "SLOT01.STATUS";
		LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__SLOT01_STATUS, obj_name,var_name);

		var_name = "SLOT01.LOTID";
		LINK__EXT_VAR_STRING_CTRL(sEXT_CH__CUR_LOTID, obj_name,var_name);
	}

	// OBJ APC ...
	{
		def_name = "OBJ__APC";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name,obj_name);

		def_check = x_utility.Check__Link(obj_name);
		bActive__OBJ_CTRL__APC = def_check;

		if(def_check)
		{
			pOBJ_CTRL__APC = p_ext_obj_create->Create__OBJECT_CTRL(obj_name);

			//
			var_name = "PARA.PRESSURE";
			LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__APC_OBJ__PARA_PRESSURE, obj_name,var_name);

			var_name = "PARA.POSITION";
			LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__APC_OBJ__PARA_POSITION, obj_name,var_name);

			var_name = "PARA.HOLD.SEC";
			LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__APC_OBJ__PARA_HOLD_SEC, obj_name,var_name);

			//
			var_name = "MON.PRESSURE.TORR";
			LINK__EXT_VAR_STRING_CTRL(sEXT_CH__APC_OBJ__MON_PRESSURE_TORR, obj_name,var_name);

			//
			var_name = "MON.PROC.PRESSURE.ABORT.ACTIVE";
			LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__APC_OBJ__MON_PROC_PRESSURE_ABORT_ACTIVE, obj_name,var_name);

			var_name = "MON.PROC.PRESSURE.STABLE.ACTIVE";
			LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__APC_OBJ__MON_PROC_PRESSURE_STABLE_ACTIVE, obj_name,var_name);

			//
			var_name = "MON.IDLE.PRESSURE.ABORT.ACTIVE";
			LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__APC_OBJ__MON_IDLE_PRESSURE_ABORT_ACTIVE, obj_name,var_name);

			var_name = "MON.IDLE.PRESSURE.STABLE.ACTIVE";
			LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__APC_OBJ__MON_IDLE_PRESSURE_STABLE_ACTIVE, obj_name,var_name);
		}
	}

	// OBJ PT_X ...
	{
		def_name = "DATA.PT_SIZE";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name,def_data);

		iDATA__PT_SIZE = atoi(def_data);
		if(iDATA__PT_SIZE > _CFG__PT_SIZE)			iDATA__PT_SIZE = _CFG__PT_SIZE;

		for(i=0; i<iDATA__PT_SIZE; i++)
		{
			def_name.Format("CH__PT_ERROR.%02d", i+1);
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
			p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);

			LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__PT_X__MON_ABORT_ACTIVE[i], obj_name,var_name);
		}
	}

	// OBJ.DGF ...
	{
		def_name = "OBJ__DGF";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name,obj_name);

		def_check = x_utility.Check__Link(obj_name);
		bActive__OBJ_CTRL__DGF = def_check;

		if(def_check)
		{
			pOBJ_CTRL__DGF = p_ext_obj_create->Create__OBJECT_CTRL(obj_name);

			//
			var_name = "CENTER.Wt.SETPOINT";
			LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__DGF_OBJ__CENTER_Wt_SETPOINT, obj_name,var_name);
		}
	}

	// OBJ MFC_X ...
	{
		def_name = "DATA.MFC_SIZE";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name,def_data);

		iDATA__MFC_SIZE = atoi(def_data);
		if(iDATA__MFC_SIZE > _CFG__MFC_SIZE)		iDATA__MFC_SIZE = _CFG__MFC_SIZE;

		for(i=0; i<iDATA__MFC_SIZE; i++)
		{
			def_name.Format("OBJ__MFC.%02d", i+1);
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name,obj_name);

			pOBJ_CTRL__MFC_X[i] = p_ext_obj_create->Create__OBJECT_CTRL(obj_name);

			//
			var_name = "PARA.SET.FLOW";
			LINK__EXT_VAR_STRING_CTRL(sEXT_CH__MFC_X__PARA_SET_FLOW[i], obj_name,var_name);

			var_name = "PARA.RAMP.SEC";
			LINK__EXT_VAR_STRING_CTRL(sEXT_CH__MFC_X__PARA_RAMP_SEC[i], obj_name,var_name);

			//
			var_name = "MON.MFC.ABORT.ACTIVE";
			LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__MFC_X__MON_MFC_ABORT_ACTIVE[i], obj_name,var_name);
		}
	}

	// OBJ RF_RPS ...
	{
		def_name = "OBJ__RF_RPS";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name,obj_name);

		def_check = x_utility.Check__Link(obj_name);
		bActive__OBJ_CTRL__RF_RPS = def_check;

		if(def_check)
		{
			pOBJ_CTRL__RF_RPS = p_ext_obj_create->Create__OBJECT_CTRL(obj_name);

			//
			var_name = "PARA.SET.POWER";
			LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__RF_RPS__PARA_SET_POWER, obj_name,var_name);

			var_name = "PARA.HOLD.TIME";
			LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__RF_RPS__PARA_HOLD_TIME, obj_name,var_name);

			//
			var_name = "MON.IDLE.POWER.ABORT.ACTIVE";
			LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__RF_RPS__MON_IDLE_POWER_ABORT_ACTIVE, obj_name,var_name);

			var_name = "MON.PROC.POWER.ABORT.ACTIVE";
			LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__RF_RPS__MON_PROC_POWER_ABORT_ACTIVE, obj_name,var_name);

			//
			var_name = "MON.REFLECT.HIGH_LIMIT.ACTIVE";
			LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__RF_RPS__MON_REFLECT_HIGH_LIMIT_ACTIVE, obj_name,var_name);

			var_name = "MON.REFLECT.MAX_COEFFICIENT.ACTIVE";
			LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__RF_RPS__MON_REFLECT_MAX_COEFFICIENT_ACTIVE, obj_name,var_name);
		}
	}
	// OBJ RF_PULSE ...
	{
		def_name = "OBJ__RF_PULSE";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name,obj_name);

		def_check = x_utility.Check__Link(obj_name);
		bActive__OBJ_CTRL__RF_PULSE = def_check;

		if(def_check)
		{
			pOBJ_CTRL__RF_PULSE = p_ext_obj_create->Create__OBJECT_CTRL(obj_name);

			//
			var_name = "PARA.RCP.FREQUENCY";
			LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__RF_PULSE__PARA_RCP_FREQUENCY, obj_name,var_name);
			
			var_name = "PARA.RCP.DUTY";
			LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__RF_PULSE__PARA_RCP_DUTY, obj_name,var_name);
			
			var_name = "PARA.RCP.EXEC";
			LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__RF_PULSE__PARA_RCP_EXEC, obj_name,var_name);
			
			//
			var_name = "PARA.RCP.ON_TIME";
			LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__RF_PULSE__PARA_RCP_ON_TIME, obj_name,var_name);
			
			var_name = "PARA.RCP.OFF_TIME";
			LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__RF_PULSE__PARA_RCP_OFF_TIME, obj_name,var_name);
			
			var_name = "PARA.RCP.ON_SHIFT_TIME";
			LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__RF_PULSE__PARA_RCP_ON_SHIFT_TIME, obj_name,var_name);
			
			var_name = "PARA.RCP.OFF_SHIFT_TIME";
			LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__RF_PULSE__PARA_RCP_OFF_SHIFT_TIME, obj_name,var_name);

			//
			var_name = "MON.POWER.ABORT.ACTIVE";
			LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__RF_PULSE__MON_POWER_ABORT_ACTIVE, obj_name,var_name);

			//
			var_name = "CFG.FREQUENCY.MIN";
			LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__RF_PULSE__CFG_FREQUENCY_MIN, obj_name,var_name);

			var_name = "CFG.FREQUENCY.MAX";
			LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__RF_PULSE__CFG_FREQUENCY_MAX, obj_name,var_name);

			var_name = "CFG.FREQUENCY.DEC";
			LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__RF_PULSE__CFG_FREQUENCY_DEC, obj_name,var_name);
		}
	}

	// OBJ RF_LF ...
	{
		def_name = "OBJ__RF_LF";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name,obj_name);

		def_check = x_utility.Check__Link(obj_name);
		bActive__OBJ_CTRL__RF_LF = def_check;

		if(def_check)
		{
			pOBJ_CTRL__RF_LF = p_ext_obj_create->Create__OBJECT_CTRL(obj_name);

			//
			var_name = "PARA.SET.POWER";
			LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__RF_LF__PARA_SET_POWER, obj_name,var_name);

			var_name = "PARA.HOLD.TIME";
			LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__RF_LF__PARA_HOLD_TIME, obj_name,var_name);

			//
			var_name = "MON.IDLE.POWER.ABORT.ACTIVE";
			LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__RF_LF__MON_IDLE_POWER_ABORT_ACTIVE, obj_name,var_name);

			var_name = "MON.PROC.POWER.ABORT.ACTIVE";
			LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__RF_LF__MON_PROC_POWER_ABORT_ACTIVE, obj_name,var_name);

			//
			var_name = "MON.REFLECT.HIGH_LIMIT.ACTIVE";
			LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__RF_LF__MON_REFLECT_HIGH_LIMIT_ACTIVE, obj_name,var_name);

			var_name = "MON.REFLECT.MAX_COEFFICIENT.ACTIVE";
			LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__RF_LF__MON_REFLECT_MAX_COEFFICIENT_ACTIVE, obj_name,var_name);
		}

		// CH__DO_LF_PULSE_SET
		{
			def_name = "CH__DO_LF_PULSE_SET";
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
			p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
			LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__DO_RF_LF_PULSE_SET, obj_name,var_name);
		}
	}
	// OBJ RF_HF ...
	{
		def_name = "OBJ__RF_HF";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name,obj_name);

		def_check = x_utility.Check__Link(obj_name);
		bActive__OBJ_CTRL__RF_HF = def_check;

		if(def_check)
		{
			pOBJ_CTRL__RF_HF = p_ext_obj_create->Create__OBJECT_CTRL(obj_name);

			//
			var_name = "PARA.SET.POWER";
			LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__RF_HF__PARA_SET_POWER, obj_name,var_name);

			var_name = "PARA.SET.P2";
			LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__RF_HF__PARA_SET_P2, obj_name,var_name);

			var_name = "PARA.HOLD.TIME";
			LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__RF_HF__PARA_HOLD_TIME, obj_name,var_name);

			//
			var_name = "MON.IDLE.POWER.ABORT.ACTIVE";
			LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__RF_HF__MON_IDLE_POWER_ABORT_ACTIVE, obj_name,var_name);

			var_name = "MON.PROC.POWER.ABORT.ACTIVE";
			LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__RF_HF__MON_PROC_POWER_ABORT_ACTIVE, obj_name,var_name);

			//
			var_name = "MON.REFLECT.HIGH_LIMIT.ACTIVE";
			LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__RF_HF__MON_REFLECT_HIGH_LIMIT_ACTIVE, obj_name,var_name);

			var_name = "MON.REFLECT.MAX_COEFFICIENT.ACTIVE";
			LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__RF_HF__MON_REFLECT_MAX_COEFFICIENT_ACTIVE, obj_name,var_name);
		}

		// CH__DO_HF_PULSE_SET
		{
			def_name = "CH__DO_HF_PULSE_SET";
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
			p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
			LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__DO_RF_HF_PULSE_SET, obj_name,var_name);
		}
	}

	// OBJ MAT_LF ...
	{
		def_name = "OBJ__MAT_LF";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name,obj_name);

		def_check = x_utility.Check__Link(obj_name);
		bActive__OBJ_CTRL__MAT_LF = def_check;

		if(def_check)
		{
			pOBJ_CTRL__MAT_LF = p_ext_obj_create->Create__OBJECT_CTRL(obj_name);

			//
			var_name = "PARA.LOAD_POS";
			LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__MAT_LF__PARA_LOAD_POS, obj_name,var_name);

			var_name = "PARA.TUNE_POS";
			LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__MAT_LF__PARA_TUNE_POS, obj_name,var_name);
		}
	}
	// OBJ MAT_HF ...
	{
		def_name = "OBJ__MAT_HF";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name,obj_name);

		def_check = x_utility.Check__Link(obj_name);
		bActive__OBJ_CTRL__MAT_HF = def_check;

		if(def_check)
		{
			pOBJ_CTRL__MAT_HF = p_ext_obj_create->Create__OBJECT_CTRL(obj_name);

			//
			var_name = "PARA.LOAD_POS";
			LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__MAT_HF__PARA_LOAD_POS, obj_name,var_name);

			var_name = "PARA.TUNE_POS";
			LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__MAT_HF__PARA_TUNE_POS, obj_name,var_name);
		}
	}

	// OBJ ESC ...
	{
		def_name = "OBJ__ESC";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name,obj_name);

		def_check = x_utility.Check__Link(obj_name);
		bActive__OBJ_CTRL__ESC = def_check;

		if(def_check)
		{
			pOBJ_CTRL__ESC = p_ext_obj_create->Create__OBJECT_CTRL(obj_name);

			// ...
			var_name = "MON.FAULT.ACTIVE";
			LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__ESC__MON_FAULT_ACTIVE, obj_name,var_name);

			// CENTER ...
			var_name = "RCP.He_CENTER.PRESSURE_SETPOINT.TORR";
			LINK__EXT_VAR_STRING_CTRL(sEXT_CH__ESC__RCP_He_CENTER_PRESSURE_SETPOINT_TORR, obj_name,var_name);

			var_name = "RCP.He_CENTER.ZONE.FLOW.MAX.THRESHOLD";
			LINK__EXT_VAR_STRING_CTRL(sEXT_CH__ESC__RCP_He_CENTER_FLOW_MAX_THRESHOLD, obj_name,var_name);

			var_name = "RCP.He_CENTER.ZONE.FLOW.MIN.THRESHOLD";
			LINK__EXT_VAR_STRING_CTRL(sEXT_CH__ESC__RCP_He_CENTER_FLOW_MIN_THRESHOLD, obj_name,var_name);

			// EDGE ...
			var_name = "RCP.He_EDGE.PRESSURE_SETPOINT.TORR";
			LINK__EXT_VAR_STRING_CTRL(sEXT_CH__ESC__RCP_He_EDGE_PRESSURE_SETPOINT_TORR, obj_name,var_name);

			var_name = "RCP.He_EDGE.ZONE.FLOW.MAX.THRESHOLD";
			LINK__EXT_VAR_STRING_CTRL(sEXT_CH__ESC__RCP_He_EDGE_FLOW_MAX_THRESHOLD, obj_name,var_name);

			var_name = "RCP.He_EDGE.ZONE.FLOW.MIN.THRESHOLD";
			LINK__EXT_VAR_STRING_CTRL(sEXT_CH__ESC__RCP_He_EDGE_FLOW_MIN_THRESHOLD, obj_name,var_name);
		}
	}

	// OBJ LIFT_PIN ...
	{
		def_name = "OBJ__LIFT_PIN";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name,obj_name);

		def_check = x_utility.Check__Link(obj_name);
		bActive__OBJ_CTRL__LIFT_PIN = def_check;

		if(def_check)
		{
			pOBJ_CTRL__LIFT_PIN = p_ext_obj_create->Create__OBJECT_CTRL(obj_name);

			// ...
			{
				def_name = "DATA.LIFT_PIN.UP";
				p_ext_obj_create->Get__DEF_CONST_DATA(def_name, def_data);
				sDATA__LIFT_PIN__UP = def_data;

				def_name = "DATA.LIFT_PIN.DOWN";
				p_ext_obj_create->Get__DEF_CONST_DATA(def_name, def_data);
				sDATA__LIFT_PIN__DOWN = def_data;
			
				def_name = "DATA.LIFT_PIN.MIDDLE";
				p_ext_obj_create->Get__DEF_CONST_DATA(def_name, def_data);
				sDATA__LIFT_PIN__MIDDLE = def_data;
			}
		}
	}

	// OBJ__HTR_SH ...
	{
		def_name = "OBJ__HTR_SH";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name,obj_name);

		def_check = x_utility.Check__Link(obj_name);
		bActive__OBJ_CTRL__HTR_SH = def_check;

		if(def_check)
		{
			for(i=0; i<_CFG__SH_SIZE; i++)
			{
				int id = i+1;

				var_name.Format("MON.IDLE.STABLE.ACTIVE.LOOP.%02d", id);
				LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__HTR_SH__MON_IDLE_STABLE_ACTIVE_X[i], obj_name,var_name);

				var_name.Format("MON.IDLE.ABORT.ACTIVE.LOOP.%02d", id);
				LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__HTR_SH__MON_IDLE_ABORT_ACTIVE_X[i], obj_name,var_name);
			}
		}
	}
	// OBJ__HTR_WALL ...
	{
		def_name = "OBJ__HTR_WALL";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name,obj_name);

		def_check = x_utility.Check__Link(obj_name);
		bActive__OBJ_CTRL__HTR_WALL = def_check;

		if(def_check)
		{
			for(i=0; i<_CFG__WALL_SIZE; i++)
			{
				int id = i+1;

				var_name.Format("MON.IDLE.STABLE.ACTIVE.LOOP.%02d", id);
				LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__HTR_WALL__MON_IDLE_STABLE_ACTIVE_X[i], obj_name,var_name);

				var_name.Format("MON.IDLE.ABORT.ACTIVE.LOOP.%02d", id);
				LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__HTR_WALL__MON_IDLE_ABORT_ACTIVE_X[i], obj_name,var_name);
			}
		}
	}

	// OBJ.EPD ...
	{
		def_name = "OBJ__EPD";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name,obj_name);

		def_check = x_utility.Check__Link(obj_name);
		bActive__OBJ_CTRL__EPD = def_check;

		if(def_check)
		{
			pOBJ_CTRL__EPD = p_ext_obj_create->Create__OBJECT_CTRL(obj_name);

			//
			var_name = "PARA.EPD.MODE";
			LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__EPD__PARA_EPD_MODE, obj_name,var_name);

			//
			var_name = "PARA.VALUE_TO_CHANGE";
			LINK__EXT_VAR_STRING_CTRL(sEXT_CH__EPD__PARA_VALUE_TO_CHANGE, obj_name,var_name);

			var_name = "PARA.PERCENT_TO_CHANGE";
			LINK__EXT_VAR_STRING_CTRL(sEXT_CH__EPD__PARA_PERCENT_TO_CHANGE, obj_name,var_name);

			//
			var_name = "PARA.DELAY.TIME";
			LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__EPD__PARA_DELAY_TIME, obj_name,var_name);

			var_name = "PARA.NORMALIZE_TIME";
			LINK__EXT_VAR_STRING_CTRL(sEXT_CH__EPD__PARA_NORMALIZE_TIME, obj_name,var_name);

			//
			var_name = "PARA.EPD.TIMEOUT.MINIMUM";
			LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__EPD__PARA_EPD_TIMEOUT_MINIMUM, obj_name,var_name);

			var_name = "PARA.EPD.TIMEOUT.MAXIMUM";
			LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__EPD__PARA_EPD_TIMEOUT_MAXIMUM, obj_name,var_name);

			//
			var_name = "PARA.EPD.THRESHOLD.MIN";
			LINK__EXT_VAR_STRING_CTRL(sEXT_CH__EPD__PARA_EPD_THRESHOLD_MIN, obj_name,var_name);

			var_name = "PARA.EPD.THRESHOLD.MAX";
			LINK__EXT_VAR_STRING_CTRL(sEXT_CH__EPD__PARA_EPD_THRESHOLD_MAX, obj_name,var_name);

			//
			var_name = "PARA.SLOPE_COUNT";
			LINK__EXT_VAR_STRING_CTRL(sEXT_CH__EPD__PARA_SLOPE_COUNT, obj_name,var_name);

			var_name = "PARA.SLOPE_DIRECTION";
			LINK__EXT_VAR_STRING_CTRL(sEXT_CH__EPD__PARA_SLOPE_DIRECTION, obj_name,var_name);

			var_name = "PARA.VALID_TIME";
			LINK__EXT_VAR_STRING_CTRL(sEXT_CH__EPD__PARA_VALID_TIME, obj_name,var_name);

			//
			var_name = "MON.IDLE.INTENSITY.ERROR.ACTIVE";
			LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__EPD__MON_ERROR_ACTIVE, obj_name,var_name);
		}
	}

	// ...
	{
		SCX__SEQ_INFO x_seq_info;

		iActive__SIM_MODE = x_seq_info->Is__SIMULATION_MODE();
	}
	return 1;
}

//-------------------------------------------------------------------------
int CObj__STEP_STD::__CALL__CONTROL_MODE(mode,p_debug,p_variable,p_alarm)
{
	int flag = -1;

	// ...
	{
		CString log_msg;
		log_msg.Format("[%s] Start ...", mode);

		xLOG_CTRL->WRITE__LOG(log_msg);

		sCH__OBJ_MSG->Set__DATA(log_msg);
		sCH__OBJ_SUB_MSG->Set__DATA("");
	}

	// ...
	{
		IF__CTRL_MODE(sMODE__INIT)
		{
			flag = Call__INIT(p_variable,p_alarm);
		}
		ELSE_IF__CTRL_MODE(sMODE__READY)
		{
			flag = Call__READY(p_variable,p_alarm);
		}
		ELSE_IF__CTRL_MODE(sMODE__START)
		{
			flag = Call__START(p_variable,p_alarm);
		}
		ELSE_IF__CTRL_MODE(sMODE__PROC)
		{
			flag = Call__PROC(p_variable,p_alarm);
		}
		ELSE_IF__CTRL_MODE(sMODE__ABORT)
		{
			flag = Call__ABORT(p_variable,p_alarm);
		}
		ELSE_IF__CTRL_MODE(sMODE__END)
		{
			flag = Call__END(p_variable,p_alarm);
		}
	}

	if((flag < 0)||(p_variable->Check__CTRL_ABORT() > 0))
	{
		CString log_msg;
		log_msg.Format("[%s] Aborted ... [%d]", mode,flag);

		xLOG_CTRL->WRITE__LOG(log_msg);	
		sCH__OBJ_MSG->Set__DATA(log_msg);
	}
	else
	{
		CString log_msg;
		log_msg.Format("[%s] Completed .. [%d]", mode,flag);

		xLOG_CTRL->WRITE__LOG(log_msg);
		sCH__OBJ_MSG->Set__DATA(log_msg);
	}

	return flag;
}

int CObj__STEP_STD::__CALL__MONITORING(id,p_variable,p_alarm)
{
	if(id == MON_ID__MONITOR)
	{
		return Mon__MONITOR(p_variable,p_alarm);
	}
	return 1;
}
