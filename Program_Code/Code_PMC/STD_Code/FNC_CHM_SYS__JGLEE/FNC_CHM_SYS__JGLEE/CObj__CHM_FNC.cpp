#include "StdAfx.h"
#include "CObj__CHM_FNC__ALID.h"
#include "CObj__CHM_FNC__DEF.h"
#include "CObj__CHM_FNC.h"

#include "CCommon_Utility.h"


//-------------------------------------------------------------------------
CObj__CHM_FNC::CObj__CHM_FNC()
{

}
CObj__CHM_FNC::~CObj__CHM_FNC()
{

}

//-------------------------------------------------------------------------
int CObj__CHM_FNC::__DEFINE__CONTROL_MODE(obj,l_mode)
{
	sObject_Name = obj;

	// ...
	{
		ADD__CTRL_VAR(sMODE__INIT,	           "INIT");
		ADD__CTRL_VAR(sMODE__MAINT,	           "MAINT");

		//
		ADD__CTRL_VAR(sMODE__PUMPING,		   "PUMPING");
		ADD__CTRL_VAR(sMODE__LOW_VAC_PUMP,	   "LOW_VAC_PUMP");
		ADD__CTRL_VAR(sMODE__HIGH_VAC_PUMP,	   "HIGH_VAC_PUMP");

		//
		ADD__CTRL_VAR(sMODE__CLOSE_VAC_LINE,   "CLOSE.VAC_LINE");

		//
		ADD__CTRL_VAR(sMODE__VENT,			   "VENTING");

		ADD__CTRL_VAR(sMODE__LEAK_CHECK,	   "LEAK_CHECK");
		ADD__CTRL_VAR(sMODE__PURGE,			   "PURGE");

		//
		ADD__CTRL_VAR(sMODE__SLOT_OPEN,        "SLOT.OPEN");
		ADD__CTRL_VAR(sMODE__SLOT_CLOSE,       "SLOT.CLOSE");

		// PICK ...
		ADD__CTRL_VAR(sMODE__PICK_READY,       "PICK_READY");
		ADD__CTRL_VAR(sMODE__PICK_X_READY,     "PICK_X_READY");

		ADD__CTRL_VAR(sMODE__PICK_COMPLETE,    "PICK_COMPLETE");
		ADD__CTRL_VAR(sMODE__PICK_X_COMPLETE,  "PICK_X_COMPLETE");

		// PLACE ...
		ADD__CTRL_VAR(sMODE__PLACE_READY,      "PLACE_READY");
		ADD__CTRL_VAR(sMODE__PLACE_X_READY,    "PLACE_X_READY");

		ADD__CTRL_VAR(sMODE__PLACE_COMPLETE,   "PLACE_COMPLETE");
		ADD__CTRL_VAR(sMODE__PLACE_X_COMPLETE, "PLACE_X_COMPLETE");

		//
		ADD__CTRL_VAR(sMODE__CHM_BALLAST_START,	  "CHM_BALLAST_START");
		ADD__CTRL_VAR(sMODE__TRANS_BALLAST_START, "TRANS_BALLAST_START");
		ADD__CTRL_VAR(sMODE__BALLAST_END,		  "BALLAST_END");

		// 
		ADD__CTRL_VAR(sMODE__APC_AUTO_LEARN,   "APC_AUTO_LEARN");
	}
	return 1;
}
int CObj__CHM_FNC::__DEFINE__VERSION_HISTORY(version)
{

	return 1;
}


// ...
#define LIST__DISABLE_ENABLE					"DISABLE ENABLE"
#define LIST__OPEN_CLOSE						"OPEN	CLOSE"
#define LIST__PRESSURE_STS						"VAC BTW ATM"
#define LIST__SOFT_PUMP_MODE					"PRESSURE TIME"

// ...
#define MON_ID__PRESSURE_STATUS							1


int CObj__CHM_FNC::__DEFINE__VARIABLE_STD(p_variable)
{
	DECLARE__STD_VARIABLE;

	CCommon_Error__DEF_VARIABLE m_err_def_variable;
	p_variable->Link__DEF_VARIABLE__ERROR_FEEDBACK(&m_err_def_variable);

	// ...
	CString str_name;
	int i;

	// OBJ PARAMETER ...
	{
		str_name = "OBJ.STATUS";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__OBJ_STATUS, str_name);

		str_name = "OBJ.MSG";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__OBJ_MSG, str_name);

		str_name = "OBJ.TIMER";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__OBJ_TIMER, str_name);
	}

	// MON PART ...
	{
		str_name = "MON.PART.ERROR.ACTIVE";
		STD__ADD_DIGITAL(str_name, "OFF ON");
		LINK__VAR_DIGITAL_CTRL(dCH__MON_PART_ERROR_ACTIVE, str_name);
	}

	// MON PARAMETER ...
	{
		str_name = "MON.PUMPING.STATE";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_PUMPING_STATE, str_name);
	}

	// ...
	{
		str_name = "TRANSFER.BALLAST.FLAG";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__TRANSFER_BALLAST_FLAG,str_name);

		str_name = "PARA.XFER.BALLAST_WAIT_SKIP.FLAG";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__PARA_XFER_BALLAST_WAIT_SKIP_FLAG,str_name);
	}

	// ...
	{
		str_name = "ACTIVE.VENTING.STATE";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__ACTIVE_VENTING_STATE, str_name);
	}

	// REFERENCE PRESSURE ...
	{
		str_name = "CFG.ATM.REF.PRESSURE";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "torr", 0, 600, 800, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_ATM_REF_PRESSURE, str_name);
		
		str_name = "CFG.VAC.REF.PRESSURE";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "torr", 3, 0.1, 10, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_VAC_REF_PRESSURE, str_name);
	}

	// SENSOR PARAMETER ...
	{
		str_name = "CFG.ATM_SNS.REF.PRESSURE";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "torr", 1, 700, 800, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_ATM_SNS_REF_PRESSURE, str_name);

		str_name = "CFG.VAC_SNS.REF.PRESSURE";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "torr", 1, 1, 300, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_VAC_SNS_REF_PRESSURE, str_name);
	}

	// FAST-VENTING PARAMETER ...
	{
		str_name = "CFG.FAST_VENT.PRESSURE";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "torr", 1, 600, 800, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_FAST_VENT_PRESSURE, str_name);

		str_name = "CFG.FAST_VENT.GAUGE.CHECK";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name, "YES  NO","");
		LINK__VAR_DIGITAL_CTRL(dCH__CFG_FAST_VENT_GAUGE_CHECK, str_name);

		str_name.Format("CFG.FAST_VENT.TIMEOUT");
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "sec", 0, 0, 300, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_FAST_VENT_TIMEOUT, str_name);

		str_name = "CFG.FAST_VENT.OVER.TIME";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "sec", 0, 0, 60, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_FAST_VENT_OVER_TIME, str_name);

		str_name = "CFG.FAST_VENT.ATM_SNS_ON.TIMEOUT";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "sec", 0, 1, 600, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_FAST_VENT_ATM_SNS_ON_TIMEOUT, str_name);
	}

	// SOFT-VENTING PARAMETER ...
	{
		str_name = "CFG.SOFT_VENT.PRESSURE";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "torr", 1, 0, 600, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_SOFT_VENT_PRESSURE, str_name);

		str_name = "CFG.SOFT_VENT.TIMEOUT";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "sec", 0, 0, 300, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_SOFT_VENT_TIMEOUT, str_name);

		str_name = "CFG.SOFT_VENT.OVER.TIME";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "sec", 0, 0, 60, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_SOFT_VENT_OVER_TIME, str_name);

		str_name = "CFG.SOFT_VENT.VAC_SNS_OFF.TIMEOUT";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "sec", 0, 0, 10, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_SOFT_VENT_VAC_SNS_OFF_TIMEOUT, str_name);
	}

	// SOFT-PUMPING PARAMETER ...
	{
		str_name = "CFG.SOFT_PUMP.PRESSURE";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "torr", 0, 1, 600, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_SOFT_PUMP_PRESSURE, str_name);

		str_name = "CFG.SOFT_PUMP.OVER.TIME";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "sec", 0, 0, 60, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_SOFT_PUMP_OVER_TIME, str_name);

		str_name = "CFG.SOFT_PUMP.TIMEOUT";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "sec", 0, 0, 300, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_SOFT_PUMP_TIMEOUT, str_name);
	}

	// FAST-PUMPING PARAMETER ...
	{
		str_name = "CFG.FAST_PUMP.PRESSURE";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "torr", 3, 0, 1, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_FAST_PUMP_PRESSURE, str_name);

		str_name = "CFG.FAST_PUMP.TIMEOUT";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "sec", 0, 0, 300, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_FAST_PUMP_TIMEOUT, str_name);
	}

	// HIGH_VAC-PUMPING PARAMETER ...
	{
		str_name = "CFG.HIGH_VAC.PRESSURE";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "torr", 3, 0, 1, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_HIGH_VAC_PRESSURE, str_name);

		str_name = "CFG.HIGH_VAC.TIMEOUT";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "sec", 0, 0, 300, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_HIGH_VAC_TIMEOUT, str_name);
	}

	// FORELINE-PUMPING PARAMETER ...
	{
		str_name = "CFG.FORELINE.PUMPING.TIMEOUT";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "sec", 0, 0, 300, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_FORELINE_PUMPING_TIMEOUT, str_name);
	}

	// PURGE PARAMETER ...
	{
		str_name = "CFG.PURGE.CYCLE_COUNT";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "num", 0, 1, 600, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_PURGE_CYCLE_COUNT, str_name);

		str_name = "CUR.PURGE.CYCLE_COUNT";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__CUR_PURGE_CYCLE_COUNT, str_name);

		//
		str_name = "CFG.PURGE.UP_PRESSURE";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "torr", 1, 0.0, 1000, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_PURGE_UP_PRESSURE, str_name);

		str_name = "CFG.PURGE.DOWN_PRESSURE";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "torr", 3, 0.0, 10, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_PURGE_DOWN_PRESSURE, str_name);

		//
		str_name = "CFG.ADD.PUMP.TIME.SECONDS.FOR.PP";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "sec", 0, 0, 20, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_ADD_PUMP_TIME_SECONDS_FOR_PP, str_name);

		str_name = "CFG.ADD.PURGE.TIME.SECONDS.FOR.PP";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "sec", 0, 0, 20, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_ADD_PURGE_TIME_SECONDS_FOR_PP, str_name);
	}

	// LEAK-CHECK PARAMETER ...
	{
		str_name = "CUR.LEAK_CHECK.TIME_COUNT";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__LEAK_CHECK__CUR_TIME_COUNT, str_name);

		//
		str_name = "CFG.LEAK_CHECK.OVER_PUMPING.TIME";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "sec", 0, 0.0, 9999, "");
		LINK__VAR_ANALOG_CTRL(aCH__LEAK_CHECK__CFG_OVER_PUMPING_TIME, str_name);

		str_name = "CFG.LEAK_CHECK.STABLE.TIME";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "sec", 0, 0.0, 9999, "");
		LINK__VAR_ANALOG_CTRL(aCH__LEAK_CHECK__CFG_STABLE_TIME, str_name);

		str_name = "CFG.LEAK_CHECK.TIME_MIN";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "min", 0, 1, 7, "");
		LINK__VAR_ANALOG_CTRL(aCH__LEAK_CHECK__CFG_TIME_MIN, str_name);

		str_name = "CFG.LEAK_CHECK.VAT_VLV_POS_MOVING";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name, "DISABLE  ENABLE", "");
		LINK__VAR_DIGITAL_CTRL(dCH__LEAK_CHECK__CFG_VAT_VLV_POS_MOVING, str_name);

		//
		str_name = "APP.LEAK_CHECK.DATE.FDC.MONTH";
		STD__ADD_STRING_WITH_X_OPTION(str_name,"");
		LINK__VAR_STRING_CTRL(sCH__LEAK_CHECK__APP_DATE_FDC_MONTH,str_name);

		//
		str_name = "APP.LEAK_CHECK.START.TIME";
		STD__ADD_STRING_WITH_X_OPTION(str_name,"");
		LINK__VAR_STRING_CTRL(sCH__LEAK_CHECK__APP_START_TIME,str_name);

		str_name = "APP.LEAK_CHECK.END.TIME";
		STD__ADD_STRING_WITH_X_OPTION(str_name,"");
		LINK__VAR_STRING_CTRL(sCH__LEAK_CHECK__APP_END_TIME,str_name);

		//
		str_name = "APP.LEAK_CHECK.BASE_PRESSURE";
		STD__ADD_STRING_WITH_X_OPTION(str_name,"");
		LINK__VAR_STRING_CTRL(sCH__LEAK_CHECK__BASE_PRESSURE_mTORR,str_name);

		str_name = "APP.LEAK_CHECK.START_PRESSURE";
		STD__ADD_STRING_WITH_X_OPTION(str_name,"");
		LINK__VAR_STRING_CTRL(sCH__LEAK_CHECK__START_PRESSURE_mTORR,str_name);

		str_name = "APP.LEAK_CHECK.RESULT";
		STD__ADD_STRING_WITH_X_OPTION(str_name,"");
		LINK__VAR_STRING_CTRL(sCH__LEAK_CHECK__RESULT_mTORR_Per_MIN,str_name);

		for(i=0;i<LEAK_CHECK__ITEM_SIZE;i++)
		{
			str_name.Format("APP.LEAK_CHECK.PRESSURE_%1d",i+1);
			STD__ADD_STRING_WITH_X_OPTION(str_name,"");
			LINK__VAR_STRING_CTRL(sCH__LEAK_CHECK__PRESSUREx_mTORR[i],str_name);

			str_name.Format("APP.LEAK_CHECK.RATE_%1d",i+1);
			STD__ADD_STRING_WITH_X_OPTION(str_name,"");
			LINK__VAR_STRING_CTRL(sCH__LEAK_CHECK__RATEx_mTORR_Per_MIN[i],str_name);
		}

		//
		str_name = "APP.LEAK_CHECK.VAT_MOVE.STATR_PRESSURE_mTORR";
		STD__ADD_STRING_WITH_X_OPTION(str_name,"");
		LINK__VAR_STRING_CTRL(sCH__LEAK_CHECK__VAT_MOVE__START_PRESSURE_mTORR,str_name);

		str_name = "APP.LEAK_CHECK.VAT_MOVE.RESULT_PRESSURE_mTORR";
		STD__ADD_STRING_WITH_X_OPTION(str_name,"");
		LINK__VAR_STRING_CTRL(sCH__LEAK_CHECK__VAT_MOVE__RESULT_PRESSURE_mTORR,str_name);

		//
		str_name = "APP.LEAK_CHECK.LOG.MESSAGE";
		STD__ADD_STRING_WITH_OPTION(str_name,-1,"E","");
		LINK__VAR_STRING_CTRL(sCH__LEAK_CHECK__LOG_MESSAGE,str_name);

		str_name = "APP.LEAK_CHECK.LOG.START_PRESSURE";
		STD__ADD_STRING_WITH_OPTION(str_name,-1,"E","");
		LINK__VAR_STRING_CTRL(sCH__LEAK_CHECK__LOG_START_PRESSURE_mTORR,str_name);

		str_name = "APP.LEAK_CHECK.LOG.PRESSURE";
		STD__ADD_STRING_WITH_OPTION(str_name,-1,"E","");
		LINK__VAR_STRING_CTRL(sCH__LEAK_CHECK__LOG_PRESSURE_mTORR,str_name);

		str_name = "APP.LEAK_CHECK.LOG.RATE";
		STD__ADD_STRING_WITH_OPTION(str_name,-1,"E","");
		LINK__VAR_STRING_CTRL(sCH__LEAK_CHECK__LOG_RATE_mTORR_Per_MIN,str_name);

		str_name = "APP.LEAK_CHECK.LOG.RESULT";
		STD__ADD_STRING_WITH_OPTION(str_name,-1,"E","");
		LINK__VAR_STRING_CTRL(sCH__LEAK_CHECK__LOG_RESULT_mTORR_Per_MIN,str_name);

		// Leak.Check 결과가 설정 압력 이상이면, Alarm Posting 한다.
		str_name = "CFG.LEAK_CHECK.MAX_PRESSURE";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "mtorr", 0, 0, 1000, "");
		LINK__VAR_ANALOG_CTRL(aCH__LEAK_CHECK__MAX_PRESSURE_mTORR,str_name);

		str_name = "CFG.LEAK_CHECK.CFG.RESULT.POSTING";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "mtorr/min", 0, 0, 100, "");
		LINK__VAR_ANALOG_CTRL(aCH__LEAK_CHECK__CFG_RESULT_POSTING,str_name);
	}

	// CFG : Transfer.Ballast ...
	{
		str_name = "CFG.TRANSFER.BALLAST.ENABLED";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name, "NO  YES", "");
		LINK__VAR_DIGITAL_CTRL(dCH__CFG_TRANSFER_BALLAST_ENABLED, str_name);
	}
	// CFG : Chamber.Ballast ...
	{
		str_name = "CFG.CHAMBER.BALLAST.ENABLED";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name, "NO  YES", "");
		LINK__VAR_DIGITAL_CTRL(dCH__CFG_CHAMBER_BALLAST_ENABLED, str_name);
	}

	// AUTO.LEARN ...
	{
		str_name.Format("CFG.aBEFORE.AUTO.LEARNING.DELAY.TIME");
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "sec", 0, 1, 60, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_BEFORE_AUTO_LEARNING_DELAY_TIME, str_name);
	}

	// CFG : TMP ...
	{
		str_name = "CFG.BEFORE.VENT.TURBO.PUMP.OFF";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name, "False True","");
		LINK__VAR_DIGITAL_CTRL(dCH__CFG_BEFORE_VENT_TURBO_PUMP_OFF, str_name);

		str_name = "CFG.PUMP.TURBO.STABLE.TIME";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "sec", 0, 0, 20, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_PUMP_TURBO_STABLE_TIME, str_name);
	}

	// ...
	{
		p_variable->Add__MONITORING_PROC(1.0,  MON_ID__PRESSURE_STATUS);
	}
	return 1;
}

int CObj__CHM_FNC::__DEFINE__ALARM(p_alarm)
{
	DECLARE__ALARM;

	// ...
	CString title;
	title.Format("%s - ", sObject_Name);

	// ...
	int alarm_id;
	CString	alarm_title;
	CString	alarm_msg;
	CStringArray l_act;

	iLIST_ALID__PART.RemoveAll();

	// ...
	{
		alarm_id = ALID__ATM_TIMEOUT;
		iLIST_ALID__PART.Add(alarm_id);

		alarm_title  = title;
		alarm_title += "ATM Pressure Time-Out !";

		alarm_msg = "Please, check the chamber's pressure.\n";

		l_act.RemoveAll();
		l_act.Add("RETRY");
		l_act.Add("ABORT");

		ADD__ALARM_EX(alarm_id, alarm_title, alarm_msg, l_act);
	}

	// ...
	{
		alarm_id = ALID__SOFT_VENT_TIMEOUT;
		iLIST_ALID__PART.Add(alarm_id);

		alarm_title  = title;
		alarm_title += "Soft Venting Time-Out !";

		alarm_msg = "Please, check the chamber's pressure.\n";

		l_act.RemoveAll();
		l_act.Add("RETRY");
		l_act.Add("ABORT");

		ADD__ALARM_EX(alarm_id, alarm_title, alarm_msg, l_act);
	}

	// ...
	{
		alarm_id = ALID__SOFT_PUMP_TIMEOUT;
		iLIST_ALID__PART.Add(alarm_id);

		alarm_title  = title;
		alarm_title += "Soft Pumping Time-Out !";

		alarm_msg = "Please, check the chamber's pressure.\n";

		l_act.RemoveAll();
		l_act.Add("RETRY");
		l_act.Add("ABORT");

		ADD__ALARM_EX(alarm_id, alarm_title, alarm_msg, l_act);
	}

	// ...
	{
		alarm_id = ALID__LOW_VAC_TIMEOUT;
		iLIST_ALID__PART.Add(alarm_id);

		alarm_title  = title;
		alarm_title += "Low Vacuum Time-Out !";

		alarm_msg = "Please, check the chamber's pressure.\n";

		l_act.RemoveAll();
		l_act.Add("RETRY");
		l_act.Add("ABORT");

		ADD__ALARM_EX(alarm_id, alarm_title, alarm_msg, l_act);
	}

	// ...
	{
		alarm_id = ALID__HIGH_VAC_TIMEOUT;
		iLIST_ALID__PART.Add(alarm_id);

		alarm_title  = title;
		alarm_title += "High Vacuum Time-Out !";

		alarm_msg = "Please, check the chamber's pressure.\n";

		l_act.RemoveAll();
		l_act.Add("RETRY");
		l_act.Add("ABORT");

		ADD__ALARM_EX(alarm_id, alarm_title, alarm_msg, l_act);
	}

	// ...
	{
		alarm_id = ALID__FORELINE_PUMP_TIMEOUT;
		iLIST_ALID__PART.Add(alarm_id);

		alarm_title  = title;
		alarm_title += "Foreline Pumping Time-Out !";

		alarm_msg = "Please, check the chamber's pressure.\n";

		l_act.RemoveAll();
		l_act.Add("RETRY");
		l_act.Add("ABORT");

		ADD__ALARM_EX(alarm_id, alarm_title, alarm_msg, l_act);
	}

	// ...
	{
		alarm_id = ALID__FORELINE_OVER_PUMP_DELAY;
		iLIST_ALID__PART.Add(alarm_id);

		alarm_title  = title;
		alarm_title += "Foreline Over-Pumping Time-Out !";

		alarm_msg = "Please, check the chamber's pressure.\n";

		l_act.RemoveAll();
		l_act.Add("RETRY");
		l_act.Add("ABORT");

		ADD__ALARM_EX(alarm_id, alarm_title, alarm_msg, l_act);
	}

	// ...
	{
		alarm_id = ALID__FORELINE_SENSOR_AND_VALUE_CHECK_TIMEOUT;
		iLIST_ALID__PART.Add(alarm_id);

		alarm_title  = title;
		alarm_title += "Foreline Pressure Sensor and Value Check Timeout";

		alarm_msg = "Please, check the CM3S1 Sensor and Pressure Value";

		l_act.RemoveAll();
		l_act.Add("RETRY");
		l_act.Add("ABORT");

		ADD__ALARM_EX(alarm_id, alarm_title, alarm_msg, l_act);
	}

	// ...
	{
		alarm_id = ALID__PREPARE_FAST_PUMP_TIMEOUT;
		iLIST_ALID__PART.Add(alarm_id);

		alarm_title  = title;
		alarm_title += "Vacuum Sensor & Foreline Pressure Sensor Check Timeout";

		alarm_msg = "Please, check the Vacuum Sensor & CM3S1 Pressure Sensor";

		l_act.RemoveAll();
		l_act.Add("RETRY");
		l_act.Add("ABORT");

		ADD__ALARM_EX(alarm_id, alarm_title, alarm_msg, l_act);
	}

	// ...
	{
		alarm_id = ALID__LOW_VAC_CHECK_COMPLETE_TIMEOUT;
		iLIST_ALID__PART.Add(alarm_id);

		alarm_title  = title;
		alarm_title += "Chamber Pressure Sensor Check Timeout";

		alarm_msg = "Please, Check the Chamber Vacuum Sensor.";

		l_act.RemoveAll();
		l_act.Add("RETRY");
		l_act.Add("ABORT");

		ADD__ALARM_EX(alarm_id, alarm_title, alarm_msg, l_act);
	}

	// ...
	{
		alarm_id = ALID__HI_VAC_CHECK_COMPLETE_TIMEOUT;
		iLIST_ALID__PART.Add(alarm_id);

		alarm_title  = title;
		alarm_title += "Process Pressure Sensor Check TImeout";

		alarm_msg = "Please, Check the Chamber Vacuum Sensor.";

		l_act.RemoveAll();
		l_act.Add("RETRY");
		l_act.Add("ABORT");

		ADD__ALARM_EX(alarm_id, alarm_title, alarm_msg, l_act);
	}

	// ...
	{
		alarm_id = ALID__VENT_CHECK_COMPLETE_TIMEOUT;
		iLIST_ALID__PART.Add(alarm_id);

		alarm_title  = title;
		alarm_title += "ATM Sensor Check timeout";

		alarm_msg = "Please, check the ATM Sensor";

		l_act.RemoveAll();
		l_act.Add("RETRY");
		l_act.Add("ABORT");

		ADD__ALARM_EX(alarm_id, alarm_title, alarm_msg, l_act);
	}

	// ...
	{
		alarm_id = ALID__CHM_SLOT_VALVE_NOT_CLOSE;
		iLIST_ALID__PART.Add(alarm_id);

		alarm_title  = title;
		alarm_title += "PMC's slot valve is not closed !";

		alarm_msg = "Please, check the pmc's slot valve.\n";

		l_act.RemoveAll();
		l_act.Add("RETRY");
		l_act.Add("ABORT");
		l_act.Add("IGNORE");

		ADD__ALARM_EX(alarm_id, alarm_title, alarm_msg, l_act);
	}

	// ...
	{
		alarm_id = ALID__SHUTTER_VALVE_NOT_CLOSE;
		iLIST_ALID__PART.Add(alarm_id);

		alarm_title  = title;
		alarm_title += "PMC's shutter valve is not closed !";

		alarm_msg = "Please, check the pmc's shutter valve.\n";

		l_act.RemoveAll();
		l_act.Add("RETRY");
		l_act.Add("ABORT");

		ADD__ALARM_EX(alarm_id, alarm_title, alarm_msg, l_act);
	}

	// ...
	{
		alarm_id = ALID__RF_CONTACT_ENABLE_TIMEOUT;
		iLIST_ALID__PART.Add(alarm_id);

		alarm_title  = title;
		alarm_title += "RF Contact Enable Timeout";

		alarm_msg = "Please, RF Contact Status";

		l_act.RemoveAll();
		l_act.Add("RETRY");
		l_act.Add("ABORT");

		ADD__ALARM_EX(alarm_id, alarm_title, alarm_msg, l_act);
	}

	// ...
	{
		alarm_id = ALID__APC_VALVE_CLOSE_CONDITION_OCCUR;
		iLIST_ALID__PART.Add(alarm_id);

		alarm_title  = title;
		alarm_title += "APC Valve Close Condition Occur.";

		alarm_msg  = "Now.. Chamber Pressure is higher than (CM2 SW1) or (CM2 SW2) Config Value..\n";
		alarm_msg += "For Safety, APC Valve Will be Closed !!\n";

		l_act.RemoveAll();
		l_act.Add("CHECK");

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	// ...
	{
		alarm_id = ALID__MANO_ISO_VALVE_CLOSE_CONDITION_OCCUR;
		iLIST_ALID__PART.Add(alarm_id);

		alarm_title  = title;
		alarm_title += "Manometer Isolation Valve Close Condition Occur.";

		alarm_msg = "Now.. Chamber Pressure is higher than (CM2 SW2) Config Value..\n";
		alarm_msg += "For Safety, Manometer Isolation Valve Will be Closed !!\n";

		l_act.RemoveAll();
		l_act.Add("CHECK");

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	// ...
	{
		alarm_id = ALID__VACUUM_SNS_OFF_TIMEOUT;
		iLIST_ALID__PART.Add(alarm_id);

		alarm_title  = title;
		alarm_title += "During Venting, Vacuum Sensor Off Timeout.";

		alarm_msg  = "Now.. Chamber Vacuum Sensor is not False whith a config timeout.\n";
		alarm_msg += "Please, Check Sensor Status !!\n";

		l_act.RemoveAll();
		l_act.Add("RETRY");
		l_act.Add("ABORT");

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	// ...
	{
		alarm_id = ALID__ATM_SNS_ON_TIMEOUT;
		iLIST_ALID__PART.Add(alarm_id);

		alarm_title  = title;
		alarm_title += "During Venting, ATM Sensor On Timeout.";

		alarm_msg  = "Now.. Chamber Atm Sensor is not True whith a config timeout.\n";
		alarm_msg += "Please, Check Sensor Status !!\n";

		l_act.RemoveAll();
		l_act.Add("RETRY");
		l_act.Add("ABORT");

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	// ...
	{
		alarm_id = ALID__LEAK_CHECK_MAX_PRESSURE_ALARM;
		iLIST_ALID__PART.Add(alarm_id);

		alarm_title  = title;
		alarm_title += "Leak Check, Max Pressure Alarm";

		alarm_msg  = "During Leak Checking, Current Chamber Pressure is higher than config value.\n";
		alarm_msg += "Please, Check Chamber Pressure Status !!\n";

		l_act.RemoveAll();
		l_act.Add("ABORT");

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	// ...
	{
		alarm_id = ALID__LEAK_CHECK_RESULT_ALARM;
		iLIST_ALID__PART.Add(alarm_id);

		alarm_title  = title;
		alarm_title += "Leak Check Result Value is abnormal Alarm";

		alarm_msg  = "After Leak Checking, Leak Rate Result is higher than config value.\n";
		alarm_msg += "Please, Check Chamber Pressure Status !!\n";

		l_act.RemoveAll();
		l_act.Add("ABORT");

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	// ...
	{
		alarm_id = ALID__LEAK_CHECK__VAT_MOVE__START_PRESSURE_OVER;
		iLIST_ALID__PART.Add(alarm_id);

		alarm_title  = title;
		alarm_title += "Leak Check with VAT valve position moving is start pressure over !";

		alarm_msg  = "VAT valve관련 H/W를 확인해 주시기 바랍니다. \n";
		alarm_msg += "VAT 관련된 부위에 LEAK이 있는 것 같습니다. \n";

		l_act.RemoveAll();
		l_act.Add("ABORT");

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	// ...
	{
		alarm_id = ALID__MAIN_WATER_LEAK_DETECT_ALARM;
		iLIST_ALID__PART.Add(alarm_id);

		alarm_title  = title;
		alarm_title += "Main Water Leak Detect Alarm";

		alarm_msg = "Please, Check Water Leak Detect Status !!\n";

		l_act.RemoveAll();
		l_act.Add("CHECK");

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	// ...
	{
		alarm_id = ALID__RF_CONTACT_OFF_CONDITION__RF_MATCHER_OFFLINE_ALARM;
		iLIST_ALID__PART.Add(alarm_id);

		alarm_title  = title;
		alarm_title += "RF Contactor Automatically Off Condition Occur.";

		alarm_msg = "Please, Check RF and Matcher Offline Status !!\n";

		l_act.RemoveAll();
		l_act.Add("CHECK");

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	// ...
	{
		alarm_id = ALID__RF_CONTACT_OFF_CONDITION__NOT_VAC_STS_ALARM;
		iLIST_ALID__PART.Add(alarm_id);

		alarm_title  = title;
		alarm_title += "RF Contactor Automatically Off Condition Occur.";

		alarm_msg = "Please, Check Chamber Vacuum Status !!\n";

		l_act.RemoveAll();
		l_act.Add("CHECK");

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	// ...
	{
		alarm_id = ALID__RF_CONTACT_OFF_CONDITION__DRYPUMP_POWER_STS_ALARM;
		iLIST_ALID__PART.Add(alarm_id);

		alarm_title  = title;
		alarm_title += "RF Contactor Automatically Off Condition Occur.";

		alarm_msg = "Please, Check Dry Pump Power Status !!\n";

		l_act.RemoveAll();
		l_act.Add("CHECK");

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	// ...
	{
		alarm_id = ALID__RF_CONTACT_OFF_CONDITION__RF_MATCHER_NOT_NORMAL_ALARM;
		iLIST_ALID__PART.Add(alarm_id);

		alarm_title  = title;
		alarm_title += "RF Matcher Alarm Not Normal Status.";

		alarm_msg = "Please, Check Matcher Alarm Status !!\n";

		l_act.RemoveAll();
		l_act.Add("CHECK");

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	// ...
	{
		alarm_id = ALID__VAC_SENSOR_CHECKING_TIMEOUT;
		iLIST_ALID__PART.Add(alarm_id);

		alarm_title  = title;
		alarm_title += "VAC Sensor Checking Timeout.";

		alarm_msg = "Please, Check VAC Sensor Status !!\n";

		l_act.RemoveAll();
		l_act.Add("CHECK");

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	// ...
	{
		alarm_id = ALID__DRY_PUMP_STATE_NOT_ON;
		iLIST_ALID__PART.Add(alarm_id);

		alarm_title  = title;
		alarm_title += "The state of Dry-Pump is not On !";

		alarm_msg = "Please, Check the state of Dry-Pump ! \n";

		l_act.RemoveAll();
		l_act.Add("ABORT");

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	// ...
	{
		alarm_id = ALID__PLATE_TEMP_INTERLOCK_FOR_VENTING;
		iLIST_ALID__PART.Add(alarm_id);

		alarm_title  = title;
		alarm_title += "Top Plate Temperature must be less than 60 C.";

		alarm_msg  = "If you want to execute \"venting sequence\", \n"; 
		alarm_msg += "You must set the temperature of top plate to less than 60 C. \n";

		l_act.RemoveAll();
		l_act.Add("CHECK");

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	// ...
	{
		alarm_id = ALID__PMC_STATUS__ATM_MAINT;
		iLIST_ALID__PART.Add(alarm_id);

		alarm_title  = title;
		alarm_title += "Current PMC's status is \"ATM MAINT\".";

		alarm_msg  = "Please, convert \"ATM Maint\"'s status from \"YES\" to \"NO\". \n"; 
		alarm_msg += "There is \"ATM Maint\" button in PMC maint page. \n";

		l_act.RemoveAll();
		l_act.Add("CHECK");

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	// ...
	{
		alarm_id = ALID__CHM_SLOT_VLV_NOT_CLOSE;
		iLIST_ALID__PART.Add(alarm_id);

		alarm_title  = title;
		alarm_title += "The slot-valve of chamber is not closed !";

		alarm_msg = "Please, close the slot-valve of chamber. \n"; 

		l_act.RemoveAll();
		l_act.Add(ACT__ABORT);
		l_act.Add(ACT__RETRY);

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}
	// ...
	{
		alarm_id = ALID__CHM_LID_NOT_CLOSE;
		iLIST_ALID__PART.Add(alarm_id);

		alarm_title  = title;
		alarm_title += "The lid of chamber is not closed !";

		alarm_msg = "Please, close the lid of chamber. \n"; 

		l_act.RemoveAll();
		l_act.Add(ACT__ABORT);
		l_act.Add(ACT__RETRY);

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	return 1;
}

int CObj__CHM_FNC::__Define__USER_FUNCTION(CII_DEFINE__FUNCTION *p_fnc_ctrl)
{
	p_fnc_ctrl->Link__ERROR_FEEDBACK(&mERROR__USER_FNC);

	return 1;
}

//-------------------------------------------------------------------------
int CObj__CHM_FNC::__INITIALIZE__OBJECT(p_variable,p_ext_obj_create)
{	
	CString def_name;
	CString def_data;
	CString ch_name;
	CString obj_name;
	CString var_name;
	CString var_data;

	// ...
	{
		CString file_name;
		CString log_msg;

		file_name.Format("%s.log", sObject_Name);

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

	// DB INF ...
	{
		def_name = "OBJ__DB_INF";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, obj_name);

		//
		var_name = "CFG.TRANSFER.MODE";
		LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__SYSTEM_TRANSFER_MODE, obj_name,var_name);

		var_name = "SLIT.VLV.STS";
		LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__PMC_SLIT_VLV_STS, obj_name,var_name);

		//
		var_name = "CHM.PRESSURE.VALUE";
		LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__CHM_PRESSURE_TORR, obj_name,var_name);

		var_name = "CHM.PRESSURE.mTORR";
		LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__CHM_PRESSURE_mTORR, obj_name,var_name);

		var_name = "CHM.PRESSURE.STATUS";
		LINK__EXT_VAR_STRING_CTRL(sEXT_CH__CHM_PRESSURE_STATE, obj_name,var_name);

		//
		var_name = "PMP.PRESSURE.VALUE";
		LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__PMP_PRESSURE_TORR, obj_name,var_name);

		var_name = "PMP.PRESSURE.STATE";
		LINK__EXT_VAR_STRING_CTRL(sEXT_CH__PMP_PRESSURE_STATE, obj_name,var_name);

		var_name = "PMP.VAC.SNS";
		LINK__EXT_VAR_STRING_CTRL(sEXT_CH__PMP_VAC_SNS, obj_name,var_name);

		//
		var_name = "SLOT01.STATUS";
		LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__WAFER_SLOT01_STATE, obj_name,var_name);

		var_name = "CFG.DECHUCK.CTRL.MODE";
		LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__CFG_DECHUCK_CTRL_MODE, obj_name,var_name);
	}
	// DB SYS ...
	{
		def_name = "OBJ__DB_SYS";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, obj_name);

		//
		var_name = "SIM.PRESSURE.TORR";
		LINK__EXT_VAR_STRING_CTRL(sEXT_CH__SIM_PRESSURE_TORR, obj_name,var_name);

		//
		var_name = "CTC.LEAK_CHECK.USE.FLAG";
		LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__CTC_LEAK_CHECK_USE_FLAG, obj_name,var_name);

		var_name = "CTC.LEAK_CHECK.OVER_PUMPING.TIME";
		LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__CTC_LEAK_CHECK_OVER_PUMPING_TIME, obj_name,var_name);

		var_name = "CTC.LEAK_CHECK.STABLE.TIME";
		LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__CTC_LEAK_CHECK_STABLE_TIME, obj_name,var_name);

		var_name = "CTC.LEAK_CHECK.TIME.MIN";
		LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__CTC_LEAK_CHECK_TIME_MIN, obj_name,var_name);

		//
		var_name = "SYSTEM.INTERLOCK.FLAG";
		LINK__EXT_VAR_STRING_CTRL(sEXT_CH__SYSTEM_INTERLOCK_FLAG, obj_name,var_name);

		var_name = "CFG.PMC.ATM_MAINT.FLAG";
		LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__CFG_PMC_ATM_MAINT_FLAG, obj_name,var_name);

		//
		var_name = "CFG.aCHM.MANOMETER.PRESS.SW1.SETTING";
		LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__CFG_CHM_MANOMETER_PRESS_SW1_SETTING, obj_name,var_name);

		var_name = "CFG.aCHM.MANOMETER.PRESS.SW2.SETTING";
		LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__CFG_CHM_MANOMETER_PRESS_SW2_SETTING, obj_name,var_name);
	}

	// OBJ : PMC_LOG
	{
		def_name = "OBJ__PMC_LOG";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, obj_name);

		bool def_check = x_utility.Check__Link(obj_name);
		bActive__PMC_LOG = def_check;

		if(def_check)
		{
			pOBJ_CTRL__PMC_LOG = p_ext_obj_create->Create__OBJECT_CTRL(obj_name);

			//
			LINK__EXT_VAR_STRING_CTRL(xEXT_CH__PMC_LOG__SUB_DIR,         obj_name,"sVAR.SUB_DIR");
			LINK__EXT_VAR_STRING_CTRL(xEXT_CH__PMC_LOG__FILE_NAME,       obj_name,"sVAR.FILE_NAME");
			LINK__EXT_VAR_ANALOG_CTRL(xEXT_CH__PMC_LOG__SAMPLING_PERIOD, obj_name,"LOG.SAMPLING.PERIOD");
		}
	}

	// OBJ : TRANSFER ...
	{
		def_name = "OBJ__TRANSFER";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, obj_name);

		bool def_check = x_utility.Check__Link(obj_name);
		bActive__TRANSFER_OBJ = def_check;

		if(def_check)
		{
			pOBJ_CTRL__TRANSFER = p_ext_obj_create->Create__OBJECT_CTRL(obj_name);
		}
	}

	// OBJ : PHY_VAC_VLV ...
	{
		def_name = "OBJ__VAC_VALVE";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, obj_name);

		bool def_check = x_utility.Check__Link(obj_name);
		bActive__PHY_VAC_VLV = def_check;

		if(def_check)
		{
			pOBJ_CTRL__PHY_VAC_VLV = p_ext_obj_create->Create__OBJECT_CTRL(obj_name);

			//
			var_name = "MON.PUMPING.STATE";
			LINK__EXT_VAR_STRING_CTRL(sEXT_CH__VAC_VLV__MON_PUMPING_STATE, obj_name,var_name);
		}
	}
	// OBJ : VAT ...
	{
		def_name = "OBJ__VAT";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, obj_name);

		bool def_check = x_utility.Check__Link(obj_name);
		bActive__VAT_OBJ = def_check;

		if(def_check)
		{
			pOBJ_CTRL__VAT = p_ext_obj_create->Create__OBJECT_CTRL(obj_name);

			//
			var_name = "PARA.POSITION";
			LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__VAT_PARA_POSITION, obj_name,var_name);

			var_name = "PARA.PRESSURE";
			LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__VAT_PARA_PRESSURE, obj_name,var_name);

			//
			var_name = "MON.POSITION";
			LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__VAT_CUR_POSITION, obj_name,var_name);
		}
	}

	// OBJ : GAS_VLV ...
	{
		def_name = "OBJ__GAS_VALVE";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, obj_name);

		pOBJ_CTRL__GAS_VLV = p_ext_obj_create->Create__OBJECT_CTRL(obj_name);
	}

	// OBJ : ESC
	{
		def_name = "OBJ__ESC";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, obj_name);

		bool def_check = x_utility.Check__Link(obj_name);
		bActive__ESC_OBJ = def_check;

		if(def_check)
		{
			pOBJ_CTRL__ESC = p_ext_obj_create->Create__OBJECT_CTRL(obj_name);

			//
			var_name = "MON.CHUCK_STATUS";
			LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__ESC_MON_CHUCK_STATUS, obj_name,var_name);
		}
	}

	// OBJ : TURBO_PUMP ...
	{
		def_name = "OBJ__TURBO_PUMP";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, obj_name);

		bool def_check = x_utility.Check__Link(obj_name);
		bActive__OBJ_CTRL__TURBO_PUMP = def_check;

		if(def_check)
		{
			pOBJ_CTRL__TURBO_PUMP = p_ext_obj_create->Create__OBJECT_CTRL(obj_name);

			//
			var_name = "MON.PUMP.ON.SNS";
			LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__TURBO_PUMP__POWER_SNS, obj_name,var_name);
		}
	}

	// OBJ : DRY_PUMP
	{
		def_name = "OBJ__DRY_PUMP";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, obj_name);

		bool def_check = x_utility.Check__Link(obj_name);
		bActive__DRY_PUMP = def_check;

		if(def_check)
		{
			pOBJ_CTRL__DRY_PUMP = p_ext_obj_create->Create__OBJECT_CTRL(obj_name);

			//
			var_name = "MON.PUMP.POWER.SNS";
			LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__DRY_PUMP__POWER_SNS, obj_name,var_name);
		}
	}

	// CHM.SLOT_VLV ...
	{
		def_name = "CH__CHM_SLOT_VLV_STATE";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);

		bool def_check = x_utility.Check__Link(ch_name);
		bActive__CHM_SLOT_VLV_STATE = def_check;

		if(def_check)
		{
			p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
			LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__CHM_SLOT_VLV_STATE, obj_name,var_name);
		}
	}
	// CHM.SHUTTER ...
	{
		def_name = "CH__CHM_SHUTTER_STATE";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);

		bool def_check = x_utility.Check__Link(ch_name);
		bActive__CHM_SHUTTER_STATE = def_check;

		if(def_check)
		{
			p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
			LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__CHM_SHUTTER_STATE, obj_name,var_name);
		}
	}

	// Channel Link ...
	{
		def_name = "CH__CHM_VAC_SNS";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
		p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
		LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__CHM_VAC_SNS, obj_name,var_name);

		def_name = "CH__CHM_ATM_SNS";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
		p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
		LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__CHM_ATM_SNS, obj_name,var_name);

		//
		def_name = "CH__CHM_LID_STATE";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);

		bool def_check = x_utility.Check__Link(ch_name);
		bActive__CHM_LID_STATE = def_check;

		if(def_check)
		{
			p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
			LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__CHM_LID_STATE, obj_name,var_name);

			def_name = "CHM_LID.CLOSE_STATE";
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name, def_data);
			sCHM_LID__CLOSE_STATE = def_data;
		}
	}

	// ...
	{
		SCX__SEQ_INFO x_seq_info;

		iActive__SIM_MODE = x_seq_info->Is__SIMULATION_MODE();
	}

	if(sCH__LEAK_CHECK__BASE_PRESSURE_mTORR->Check__DATA("") > 0)
	{
		sCH__LEAK_CHECK__BASE_PRESSURE_mTORR->Set__DATA("0.0");
	}
	return 1;
}

//-------------------------------------------------------------------------
int CObj__CHM_FNC::__CALL__CONTROL_MODE(mode,p_debug,p_variable,p_alarm)
{
	DECLARE__EXT_CTRL(p_variable);

	int flag = -1;

	pOBJ_CTRL__GAS_VLV->Link__UPPER_OBJECT();

	// ...
	{
		CString log_msg;
		log_msg.Format("Start [%s] ... By %s \n", mode, p_ext_mode_ctrl->Get__UPPER_OBJECT_NAME());

		xLOG_CTRL->WRITE__LOG(log_msg);
		sCH__OBJ_MSG->Set__DATA(log_msg);
	}

LOOP_RETRY:

	// ...
	int check__pumping_condition = -1;
	int check__venting_condition = -1;

	if((mode.CompareNoCase(sMODE__INIT)          == 0) 
	|| (mode.CompareNoCase(sMODE__PUMPING)       == 0) 
	|| (mode.CompareNoCase(sMODE__LOW_VAC_PUMP)  == 0) 
	|| (mode.CompareNoCase(sMODE__HIGH_VAC_PUMP) == 0) 
	|| (mode.CompareNoCase(sMODE__LEAK_CHECK)    == 0) 
	|| (mode.CompareNoCase(sMODE__PURGE)         == 0))
	// || (mode.CompareNoCase(sMODE__PURGE_PUMP)    == 0))
	{
		check__pumping_condition = 1;
	}

	if((mode.CompareNoCase(sMODE__VENT)       == 0))
	// || (mode.CompareNoCase(sMODE__PURGE_VENT) == 0))
	{
		check__venting_condition = 1;
	}

	if(check__pumping_condition > 0)
	{
		if(dEXT_CH__CFG_PMC_ATM_MAINT_FLAG->Check__DATA(STR__YES) > 0)
		{
			// ...
			{
				int alarm_id = ALID__PMC_STATUS__ATM_MAINT;
				CString log_msg;
				CString r_act;

				log_msg.Format("Can't execute the \"%s\" mode.\n", mode);

				p_alarm->Popup__ALARM_With_MESSAGE(alarm_id, log_msg, r_act);			// Error
			}
			return OBJ_ABORT;
		}
	}

	if((check__pumping_condition > 0)
	|| (check__venting_condition > 0))
	{
		if(bActive__CHM_SLOT_VLV_STATE)
		{
			int retry_count = 0;

			while(1)
			{
				if(dEXT_CH__CHM_SLOT_VLV_STATE->Check__DATA(STR__CLOSE) < 0)
				{
					if(retry_count < 50)
					{
						retry_count++;

						Sleep(100);
						continue;
					}

					// ...
					{
						int alarm_id = ALID__CHM_SLOT_VALVE_NOT_CLOSE;

						CString log_msg;
						CString r_act;

						log_msg.Format("Can't execute the \"%s\" mode.\n", mode);

						p_alarm->Popup__ALARM_With_MESSAGE(alarm_id, log_msg, r_act);			// Error

						if(r_act.CompareNoCase("RETRY") == 0)
						{
							goto LOOP_RETRY;
						}
						if(r_act.CompareNoCase("IGNORE") == 0)
						{
							break;
						}
						return OBJ_ABORT;
					}
				}

				break;
			}
		}

		if(bActive__CHM_SHUTTER_STATE)
		{
			int retry_count = 0;

			while(1)
			{
				if(dEXT_CH__CHM_SHUTTER_STATE->Check__DATA(STR__CLOSE) < 0)
				{
					if(retry_count < 50)
					{
						retry_count++;

						Sleep(100);
						continue;
					}

					// ...
					{
						int alarm_id = ALID__SHUTTER_VALVE_NOT_CLOSE;
						CString log_msg;
						CString r_act;

						log_msg.Format("Can't execute the \"%s\" mode.\n", mode);

						p_alarm->Popup__ALARM_With_MESSAGE(alarm_id, log_msg, r_act);			// Error

						if(r_act.CompareNoCase("RETRY") == 0)
						{
							return OBJ_RETRY;
						}
						return OBJ_ABORT;
					}
				}

				break;
			}
		}

		// ...
	}

	// ...
	{
		     IF__CTRL_MODE(sMODE__INIT)						flag = Call__INIT(p_variable,p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__MAINT)					flag = Call__MAINTMODE(p_variable,p_alarm);
		
		ELSE_IF__CTRL_MODE(sMODE__PUMPING)					flag = Call__HIGH_VAC_PUMP(p_variable,p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__LOW_VAC_PUMP)				flag = Call__LOW_VAC_PUMP(p_variable,p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__HIGH_VAC_PUMP)			flag = Call__HIGH_VAC_PUMP(p_variable,p_alarm);

		ELSE_IF__CTRL_MODE(sMODE__CLOSE_VAC_LINE)			flag = Call__CLOSE_VAC_LINE(p_variable,p_alarm);

		ELSE_IF__CTRL_MODE(sMODE__VENT)
		{
			sCH__ACTIVE_VENTING_STATE->Set__DATA("ON");

			flag = Call__VENT(p_variable,p_alarm);

			sCH__ACTIVE_VENTING_STATE->Set__DATA("OFF");
		}

		ELSE_IF__CTRL_MODE(sMODE__LEAK_CHECK)				flag = Call__LEAK_CHECK(p_variable, p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__PURGE)					flag = Call__PURGE(p_variable, p_alarm);

		//
		ELSE_IF__CTRL_MODE(sMODE__SLOT_OPEN)				flag = Call__SLOT_OPEN(p_variable, p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__SLOT_CLOSE)				flag = Call__SLOT_CLOSE(p_variable, p_alarm);

		// PICK ...
		ELSE_IF__CTRL_MODE(sMODE__PICK_READY)				flag = Call__PICK_READY(p_variable, p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__PICK_X_READY)				flag = Call__PICK_X_READY(p_variable, p_alarm);

		ELSE_IF__CTRL_MODE(sMODE__PICK_COMPLETE)			flag = Call__PICK_COMPLETE(p_variable, p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__PICK_X_COMPLETE)			flag = Call__PICK_X_COMPLETE(p_variable, p_alarm);

		// PLACE ...
		ELSE_IF__CTRL_MODE(sMODE__PLACE_READY)				flag = Call__PLACE_READY(p_variable, p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__PLACE_X_READY)			flag = Call__PLACE_X_READY(p_variable, p_alarm);

		ELSE_IF__CTRL_MODE(sMODE__PLACE_COMPLETE)			flag = Call__PLACE_COMPLETE(p_variable, p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__PLACE_X_COMPLETE)			flag = Call__PLACE_X_COMPLETE(p_variable, p_alarm);

		//
		ELSE_IF__CTRL_MODE(sMODE__CHM_BALLAST_START)		flag = Call__CHM_BALLAST_START(p_variable,p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__TRANS_BALLAST_START)		flag = Call__TRANS_BALLAST_START(p_variable,p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__BALLAST_END)				flag = Call__BALLAST_END(p_variable,p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__APC_AUTO_LEARN)			flag = Call__APC_AUTO_LEARN(p_variable,p_alarm);
	}

	// ...
	{
		sCH__PARA_XFER_BALLAST_WAIT_SKIP_FLAG->Set__DATA("");
	}

	if((flag < 0)||(p_variable->Check__CTRL_ABORT() > 0))
	{
		// ...
		{
			CString log_msg;
			log_msg.Format("[%s] Aborted (%1d)",mode,flag);

			xLOG_CTRL->WRITE__LOG(log_msg);
			sCH__OBJ_MSG->Set__DATA(log_msg);
		}

		sCH__OBJ_STATUS->Set__DATA(STR__MAINTMODE);
	}
	else
	{
		CString log_msg;
		log_msg.Format("[%s] Completed ...",mode);

		xLOG_CTRL->WRITE__LOG(log_msg);
		sCH__OBJ_MSG->Set__DATA(log_msg);
	}

	return flag;
}

int CObj__CHM_FNC::__CALL__MONITORING(id,p_variable,p_alarm)
{
	switch(id)
	{
		case MON_ID__PRESSURE_STATUS:
			Mon__PRESSURE_STATUS(p_variable, p_alarm);
			return 1;
	}

	return 1;
}
