#include "StdAfx.h"
#include "CObj__STEP_FNC.h"

#include "CCommon_Utility.h"


//-------------------------------------------------------------------------
CObj__STEP_FNC::CObj__STEP_FNC()
{
	iPRC_FLAG = -1;

	iSTEP_CHANGE_FLAG = -1;
	iSTEP_COUNT = 0;
}
CObj__STEP_FNC::~CObj__STEP_FNC()
{

}

//-------------------------------------------------------------------------
int CObj__STEP_FNC::__DEFINE__CONTROL_MODE(obj,l_mode)
{
	sObject_Name = obj;

	// ...
	{
		ADD__CTRL_VAR(sMODE__INIT,	"INIT");
		ADD__CTRL_VAR(sMODE__RCP_DATA_INIT, "RCP_DATA_INIT");

		ADD__CTRL_VAR(sMODE__READY,	"READY");
		ADD__CTRL_VAR(sMODE__START, "START");
		ADD__CTRL_VAR(sMODE__PROC,	"PROC");
		ADD__CTRL_VAR(sMODE__PROC_SYSTEN_INIT, "PROC.SYSTEM_INIT");
		ADD__CTRL_VAR(sMODE__ABORT,	"ABORT");
		ADD__CTRL_VAR(sMODE__END,	"END");

		ADD__CTRL_VAR(sMODE__STEP_DB_CHECK,	"STEP_DB_CHECK");
	}
	return 1;
}
int CObj__STEP_FNC::__DEFINE__VERSION_HISTORY(version)
{

	return 1;
}


// ...
#define  _FNC_MON_ID__RCP_MATCHER_TOP__CTRL_REQ		101

//
#define  MON_ID__WAFER_COUNT_CTRL					1


// ...
#define  APP_DSP__DISABLE_ENABLE					\
"DISABLE ENABLE"

#define  APP_DSP__ENABLE_DISABLE					\
"ENABLE DISABLE"

#define  APP_DSP__TEMPERATURE_MODE					\
"DISABLE ENABLE STEP_CTRL"

#define  APP_DSP__RETURN_RESET						\
"RETURN RESET"

#define  APP_DSP__NEXT_LEARNED_MODE					\
"DISABLE ENABLE WAP_POS VAT_POS"


int CObj__STEP_FNC::__DEFINE__VARIABLE_STD(p_variable)
{
	DECLARE__STD_VARIABLE;

	// ...
	CCommon_Error__DEF_VARIABLE m_err_def_variable;
	p_variable->Link__DEF_VARIABLE__ERROR_FEEDBACK(&m_err_def_variable);

	// ...
	CString str_name;
	CString item_list;
	int i;
	
	// ...
	{
		str_name = "OBJ.MSG";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__OBJ_MSG, str_name);

		str_name = "OBJ.SUB.MSG";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__OBJ_SUB_MSG, str_name);
	}

	// Config Channel ...
	{
		str_name = "CFG.STEP.TIME.OFFSET_SEC";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "sec", 4, 0.000, 0.005, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_STEP_TIME_OFFSET_SEC, str_name);

		str_name = "CFG.ESC.MAX.TEMP.DIFFERENCE";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "C", 0, 10, 50, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_ESC_MAX_TEMP_DIFFERENCE, str_name);
	}

	// ...
	{
		str_name = "CUR.PROC.TYPE";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__CUR_PROC_TYPE, str_name);
		
		str_name = "XFER.BALLAST_CTRL.FLAG";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__XFER_BALLAST_CTRL_FLAG, str_name);

		//
		str_name = "RCP.FILE.PATH";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__RCP_FILE_PATH, str_name);

		str_name = "RCP.DATA.APP.LOG";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name, "Disable Enable", "");
		LINK__VAR_DIGITAL_CTRL(dCH__RCP_DATA_APP_LOG, str_name);
	
		str_name = "RCP.MON.STEP.NO";
		STD__ADD_ANALOG_WITH_OPTION(str_name, "sec", 0, 0, 10000, -1, "L", "");
		LINK__VAR_ANALOG_CTRL(aCH__RCP_MON_STEP_NO, str_name);

		str_name = "RCP.FDC.STEP.TIME";
		STD__ADD_ANALOG_WITH_OPTION(str_name, "sec", 0, 0, 10000, -1, "L", "");
		LINK__VAR_ANALOG_CTRL(aCH__RCP_FDC_STEP_TIME, str_name);
	}

	// ...
	{
		str_name = "STEP.TIME.COUNT";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__STEP_TIME_COUNT, str_name);
	}

	// ...
	{
		str_name = "EXCEPTION.COMMAND";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__EXCEPTION_COMMAND, str_name);

		//
		str_name = "STEP.STABLE.REQ";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__STEP_STABLE_REQ, str_name);

		//
		str_name = "EXCEPTION_CONTINUE.REQ";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__EXCEPTION_CONTINUE_REQ, str_name);

		str_name = "EXCEPTION_CONTINUE.STEP_OVER_TIME";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__EXCEPTION_CONTINUE_STEP_OVER_TIME, str_name);

		//
		str_name = "STEP.TIME.ABORT.FLAG";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__STEP_TIME_ABORT_FLAG, str_name);
	}

	// ...
	{
		str_name = "STEP.EPD.CHECK.SEC";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__STEP_EDP_CHECK_SEC, str_name);

		str_name = "STEP.OVERETCH.SEC";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__STEP_OVERETCH_SEC, str_name);

		str_name = "STEP.OVERETCH.PERCENT";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__STEP_OVERETCH_PERCENT, str_name);
	}

	// ...
	{
		str_name = "HEADER.TEMP_CHECK.FLAG";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__HEADER_TEMP_CHECK_FLAG, str_name);

		str_name = "HEADER.TEMP_CHECK.RECIPE";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__HEADER_TEMP_CHECK_RECIPE, str_name);
	}

	// ...
	{
		str_name = "FDC.PIN.STATUS";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__FDC_PIN_STATUS, str_name);
	}

	// WAFER INFO ...
	{
		str_name = "TOTAL.COUNT.START.DATE";
		STD__ADD_STRING_WITH_X_OPTION(str_name,"");
		LINK__VAR_STRING_CTRL(sCH__TOTAL_COUNT_START_DATE, str_name);

		str_name = "WAFER.TOTAL.COUNT";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name,"count",0,0,9999999,"");
		LINK__VAR_ANALOG_CTRL(aCH__WAFER_TOTAL_COUNT, str_name);

		//
		str_name = "CURRENT.COUNT.START.DATE";
		STD__ADD_STRING_WITH_X_OPTION(str_name,"");
		LINK__VAR_STRING_CTRL(sCH__CURRENT_COUNT_START_DATE, str_name);

		str_name = "WAFER.CURRENT.COUNT";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name,"count",0,0,9999999,"");
		LINK__VAR_ANALOG_CTRL(aCH__WAFER_CURRENT_COUNT, str_name);

		str_name = "WAFER.COUNT.COUNT.RESET";
		STD__ADD_DIGITAL_WITH_COMMENT(str_name,APP_DSP__RETURN_RESET,"");
		LINK__VAR_DIGITAL_CTRL(dCH__WAFER_CURRENT_COUNT_RESET, str_name);

		str_name = "WAFER.TOTAL.COUNT.RESET";
		STD__ADD_DIGITAL_WITH_COMMENT(str_name,APP_DSP__RETURN_RESET,"");
		LINK__VAR_DIGITAL_CTRL(dCH__WAFER_TOTAL_COUNT_RESET, str_name);
	}

	// RFx REF : RF ON - INFO ...
	{
		CString part_name;
		int i;

		for(i=0; i<CFG__RF_PART_SIZE; i++)
		{
				 if(i == RF_PART_INDEX__BIAS)		part_name = "BIAS";
			else if(i == RF_PART_INDEX__PLASMA)		part_name = "PLASMA";
			else									continue;

			str_name .Format("PART.RF.%s.ON_TIME.START.DATE", part_name);
			STD__ADD_STRING_WITH_X_OPTION(str_name, "");
			LINK__VAR_STRING_CTRL(sCH__RF_PART__ON_TIME_START_DATE_X[i], str_name);

			str_name.Format("PART.RF.%s.ON_TIME.TOTAL_HOUR", part_name);
			STD__ADD_ANALOG_WITH_X_OPTION(str_name, "hour",0,0,9999999,"");
			LINK__VAR_ANALOG_CTRL(aCH__RF_PART__ON_TIME_TOTAL_HOUR_X[i], str_name);

			str_name.Format("PART.RF.%s.ON_TIME.TOTAL_MIN", part_name);
			STD__ADD_ANALOG_WITH_X_OPTION(str_name, "min",0,0,9999999,"");
			LINK__VAR_ANALOG_CTRL(aCH__RF_PART__ON_TIME_TOTAL_MIN_X[i], str_name);

			//
			str_name.Format("PART.RF.%s.ON_TIME.TOTAL_SEC", part_name);
			STD__ADD_ANALOG_WITH_COMMENT(str_name, "sec",0,0,9999999,"");
			LINK__VAR_ANALOG_CTRL(aCH__RF_PART__ON_TIME_TOTAL_SEC_X[i], str_name);

			str_name.Format("PART.RF.%s.ON_TIME.RESET", part_name);
			STD__ADD_DIGITAL_WITH_COMMENT(str_name,APP_DSP__RETURN_RESET,"");
			LINK__VAR_DIGITAL_CTRL(dCH__RF_PART__ON_TIME_RESET_X[i], str_name);
		}
	}

	// ESC ON - INFO ...
	{
		str_name = "ESC.ON_TIME.START.DATE";
		STD__ADD_STRING_WITH_X_OPTION(str_name, "");
		LINK__VAR_STRING_CTRL(sCH__ESC_ON_TIME_START_DATE, str_name);
		
		str_name = "ESC.ON_TIME.TOTAL_HOUR";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "hour",0,0,9999999,"");
		LINK__VAR_ANALOG_CTRL(aCH__ESC_ON_TIME_TOTAL_HOUR, str_name);
		
		str_name = "ESC.ON_TIME.TOTAL_MIN";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "min",0,0,9999999,"");
		LINK__VAR_ANALOG_CTRL(aCH__ESC_ON_TIME_TOTAL_MIN, str_name);
		
		//
		str_name = "ESC.ON_TIME.TOTAL_SEC";
		STD__ADD_ANALOG_WITH_COMMENT(str_name, "sec",0,0,9999999,"");
		LINK__VAR_ANALOG_CTRL(aCH__ESC_ON_TIME_TOTAL_SEC, str_name);
		
		str_name = "ESC.ON_TIME.RESET";
		STD__ADD_DIGITAL_WITH_COMMENT(str_name,APP_DSP__RETURN_RESET,"");
		LINK__VAR_DIGITAL_CTRL(dCH__ESC_ON_TIME_RESET, str_name);
	}

	// ...
	{
		str_name = "ACTIVE.RF.TURN_OFF.DELAY";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__ACTIVE__RF_TURN_OFF_DELAY, str_name);

		str_name = "CFG.STEP_DELAY.RF_OFF";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "sec", 1, 0.0, 1.0, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_STEP_DELAY_RF_OFF, str_name);
	}

	// ...
	{	
		str_name = "ACTIVE.MFC.CLOSE.DELAY";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__ACTIVE__MFC_CLOSE_DELAY, str_name);

		str_name = "CFG.STEP_DELAY.MFC_CLOSE";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "sec", 1, 0.0, 1.0, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_STEP_DELAY_MFC_CLOSE, str_name);
	}

	// LEARNED INFO ... 
	{
		str_name = "CUR.LOTID";
		STD__ADD_STRING_WITH_X_OPTION(str_name, "");
		LINK__VAR_STRING_CTRL(sCH__CUR_LOTID, str_name);

		str_name = "PRE.LOTID";
		STD__ADD_STRING_WITH_X_OPTION(str_name, "");
		LINK__VAR_STRING_CTRL(sCH__PRE_LOTID, str_name);

		str_name = "LEARNED.APPLY.STATUS";
		STD__ADD_STRING_WITH_X_OPTION(str_name,"");
		LINK__VAR_STRING_CTRL(sCH__LEARNED_APPLY_STATUS, str_name);
	}

	// LEARNED DATA ... 
	{
		// APPLY MODE ...
		{
			str_name = "CFG.LEARNED.APPLY.MODE";
			STD__ADD_DIGITAL_WITH_X_OPTION(str_name, "ENABLE DISABLE", "");
			LINK__VAR_DIGITAL_CTRL(dCH__CFG_LEARNED_APPLY_MODE, str_name);
		}
		// RESULT ...
		{
			str_name = "LEARNED_RESULT";
			STD__ADD_STRING_WITH_COMMENT(str_name, "");
			LINK__VAR_STRING_CTRL(sCH__LEARNED_RESULT, str_name);
		}
	}

	// RANGE PARAETER ...
	{
		str_name = "CFG.RANGE.ZERO";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name,"num",0,0,0,"");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_RANGE_ZERO, str_name);
	}
	// Process IO Interlock Check ...
	{
		str_name = "CFG.IO.INTERLOCK.SKIP";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name, "Disable Enable", "");
		LINK__VAR_DIGITAL_CTRL(dCH__CFG_IO_INTERLOCK_SKIP, str_name);
	}

	// HEADER : RCP PARAMETER ...
	{
		// ...
		{
			str_name = "CFG.HEADER.APPLY.MODE";
			STD__ADD_DIGITAL_WITH_X_OPTION(str_name,APP_DSP__TEMPERATURE_MODE,"");
			LINK__VAR_DIGITAL_CTRL(dCH__CFG_HEADER_APPLY_MODE, str_name);

			str_name = "TEMPERATURE_CTRL.MODE";
			STD__ADD_STRING(str_name);
			LINK__VAR_STRING_CTRL(sCH__TEMPERATURE_CTRL_MODE, str_name);

			str_name = "CFG.TEMP_CTRL.STABLE_RANGE";
			STD__ADD_ANALOG_WITH_X_OPTION(str_name,"C",1,1,5,"");
			LINK__VAR_ANALOG_CTRL(aCH__CFG_TEMP_CTRL_STABLE_RANGE, str_name);

			str_name = "CFG.TEMP_CTRL.WAIT_MODE";
			STD__ADD_DIGITAL_WITH_X_OPTION(str_name,"ENABLE DISABLE","");
			LINK__VAR_DIGITAL_CTRL(dCH__CFG_TEMP_CTRL_WAIT_MODE, str_name);
		}

		// ...
	}

	// TOLERANCE : RCP PARAMETER ...
	{
		//
		{
			str_name = "CFG.TOLERANCE.CHECK.CHM.PRESSURE";
			STD__ADD_DIGITAL_WITH_X_OPTION(str_name, APP_DSP__DISABLE_ENABLE,"");
			LINK__VAR_DIGITAL_CTRL(dCH__CFG_TOLERANCE_CHECK_CHM_PRESSURE, str_name);

			str_name = "TOLERANCE.W.CHM.PRESSURE";
			STD__ADD_ANALOG_WITH_OPTION(str_name,"%",1,0,99999,-1,"E","");
			LINK__VAR_ANALOG_CTRL(aCH__TOLERANCE_W_CHM_PRESSURE, str_name);

			str_name = "TOLERANCE.F.CHM.PRESSURE";
			STD__ADD_ANALOG_WITH_OPTION(str_name,"%",1,0,99999,-1,"E","");
			LINK__VAR_ANALOG_CTRL(aCH__TOLERANCE_F_CHM_PRESSURE, str_name);

			str_name = "TOLERANCE.TC.CHM.PRESSURE";
			STD__ADD_ANALOG_WITH_OPTION(str_name,"sec",1,0,99999,-1,"E","");
			LINK__VAR_ANALOG_CTRL(aCH__TOLERANCE_TC_CHM_PRESSURE, str_name);

			str_name = "TOLERANCE.TS.CHM.PRESSURE";
			STD__ADD_ANALOG_WITH_OPTION(str_name,"sec",1,0,99999,-1,"E","");
			LINK__VAR_ANALOG_CTRL(aCH__TOLERANCE_TS_CHM_PRESSURE, str_name);
		}

		for(i=0; i<CFG_SIZE__MFC_OBJ; i++)
		{
			str_name.Format("CFG.TOLERANCE.CHECK.MFC.GAS%1d.FLOW", i+1);
			STD__ADD_DIGITAL_WITH_X_OPTION(str_name, APP_DSP__DISABLE_ENABLE,"");
			LINK__VAR_DIGITAL_CTRL(dCH__CFG_TOLERANCE_CHECK_MFC_GASx_FLOW[i], str_name);

			// 
			str_name.Format("TOLERANCE.W.MFC.GAS%1d.FLOW", i+1);
			STD__ADD_ANALOG_WITH_OPTION(str_name,"%",1,0,99999,-1,"E","");
			LINK__VAR_ANALOG_CTRL(aCH__TOLERANCE_W_MFC_GASx_FLOW[i], str_name);

			str_name.Format("TOLERANCE.F.MFC.GAS%1d.FLOW", i+1);
			STD__ADD_ANALOG_WITH_OPTION(str_name,"%",1,0,99999,-1,"E","");
			LINK__VAR_ANALOG_CTRL(aCH__TOLERANCE_F_MFC_GASx_FLOW[i], str_name);

			str_name.Format("TOLERANCE.TC.MFC.GAS%1d.FLOW", i+1);
			STD__ADD_ANALOG_WITH_OPTION(str_name,"sec",1,0,99999,-1,"E","");
			LINK__VAR_ANALOG_CTRL(aCH__TOLERANCE_TC_MFC_GASx_FLOW[i], str_name);

			str_name.Format("TOLERANCE.TS.MFC.GAS%1d.FLOW", i+1);
			STD__ADD_ANALOG_WITH_OPTION(str_name,"sec",1,0,99999,-1,"E","");
			LINK__VAR_ANALOG_CTRL(aCH__TOLERANCE_TS_MFC_GASx_FLOW[i], str_name);

			//
			str_name.Format("TOLERANCE.W.MFC.GAS%1d.TITLE", i+1);
			STD__ADD_STRING_WITH_COMMENT(str_name,"");
			LINK__VAR_STRING_CTRL(sCH__TOLERANCE_W_MFC_GASx_TITLE[i], str_name);
	
			str_name.Format("TOLERANCE.F.MFC.GAS%1d.TITLE", i+1);
			STD__ADD_STRING_WITH_COMMENT(str_name,"");
			LINK__VAR_STRING_CTRL(sCH__TOLERANCE_F_MFC_GASx_TITLE[i], str_name);
	
			str_name.Format("TOLERANCE.TC.MFC.GAS%1d.TITLE", i+1);
			STD__ADD_STRING_WITH_COMMENT(str_name,"");
			LINK__VAR_STRING_CTRL(sCH__TOLERANCE_TC_MFC_GASx_TITLE[i], str_name);
	
			str_name.Format("TOLERANCE.TS.MFC.GAS%1d.TITLE", i+1);
			STD__ADD_STRING_WITH_COMMENT(str_name,"");
			LINK__VAR_STRING_CTRL(sCH__TOLERANCE_TS_MFC_GASx_TITLE[i], str_name);
		}
	}

	// STEP : RCP PARAMETER ...
	{
		//
		{
			str_name = "RCP.STEP.MESSAGE";
			STD__ADD_STRING_WITH_OPTION(str_name, 0,"E","");
			LINK__VAR_STRING_CTRL(sCH__RCP_STEP_MESSAGE, str_name);

			str_name = "RCP.STEP.MODE";
			STD__ADD_DIGITAL_WITH_OPTION(str_name, "Time Stable Dechuck Chuck End", 0, "E", "");
			LINK__VAR_DIGITAL_CTRL(dCH__RCP_STEP_MODE, str_name);

			str_name = "RCP.STEP.TIME";
			STD__ADD_ANALOG_WITH_OPTION(str_name, "sec", 1, 0, 9999, 0, "E", "");
			LINK__VAR_ANALOG_CTRL(aCH__RCP_STEP_TIME, str_name);
		}

		//
		{
			str_name = "RCP.APC.MODE";
			STD__ADD_DIGITAL_WITH_OPTION(str_name, "Position Pressure", 0, "E", "");
			LINK__VAR_DIGITAL_CTRL(dCH__RCP_APC_MODE, str_name);

			str_name = "RCP.APC.PRESSURE";
			STD__ADD_ANALOG_WITH_OPTION(str_name, "torr", 3, 0, 10, 0, "E", "");
			LINK__VAR_ANALOG_CTRL(aCH__RCP_APC_PRESSURE, str_name);

			str_name = "RCP.APC.POSITION";
			STD__ADD_ANALOG_WITH_OPTION(str_name, "%", 1, 0, 100, 0, "E", "");
			LINK__VAR_ANALOG_CTRL(aCH__RCP_APC_POSITION, str_name);

			str_name = "RCP.APC.PRESET.POS";
			STD__ADD_ANALOG_WITH_OPTION(str_name, "%", 1, 0, 100, 0, "E", "");
			LINK__VAR_ANALOG_CTRL(aCH__RCP_APC_PRESET_POS, str_name);

			str_name = "RCP.APC.LEARNED.POS";
			STD__ADD_ANALOG_WITH_OPTION(str_name, "%", 1, 0, 100, 0, "E", "");
			LINK__VAR_ANALOG_CTRL(aCH__RCP_APC_LEARNED_POS, str_name);

			str_name = "RCP.APC.HOLD.DELAY";
			STD__ADD_ANALOG_WITH_OPTION(str_name, "sec", 1, 0, 10, 0, "E", "");
			LINK__VAR_ANALOG_CTRL(aCH__RCP_APC_HOLD_DELAY, str_name);
		}

		//
		{
			str_name = "RCP.RF.PLASMA.POWER";
			STD__ADD_ANALOG_WITH_OPTION(str_name, "W", 0, 0, 1500, 0, "E", "");
			LINK__VAR_ANALOG_CTRL(aCH__RCP_RF_PLASMA_POWER, str_name);

			str_name = "RCP.RF.PLASMA.PULSE.FREQ";
			STD__ADD_ANALOG_WITH_OPTION(str_name, "kHz", 1, 0, 10000, 0, "E", "");
			LINK__VAR_ANALOG_CTRL(aCH__RCP_RF_PLASMA_PULSE_FREQ, str_name);

			str_name = "RCP.RF.PLASMA.FREQ.LEARNED";
			STD__ADD_ANALOG_WITH_OPTION(str_name, "kHz", 1, 0, 10000, 0, "E", "");
			LINK__VAR_ANALOG_CTRL(aCH__RCP_RF_PLASMA_FREQ_LEARNED, str_name);

			str_name = "RCP.RF.PLASMA.FREQ.PRESET";
			STD__ADD_ANALOG_WITH_OPTION(str_name, "kHz", 1, 0, 10000, 0, "E", "");
			LINK__VAR_ANALOG_CTRL(aCH__RCP_RF_PLASMA_FREQ_PRESET, str_name);

			str_name = "RCP.RF.PLASMA.TUNE.DELAY";
			STD__ADD_ANALOG_WITH_OPTION(str_name, "msec", 1, 0, 30000, 0, "E", "");
			LINK__VAR_ANALOG_CTRL(aCH__RCP_RF_PLASMA_TUNE_DELAY, str_name);

			str_name = "RCP.RF.PLASMA.DUTY";
			STD__ADD_ANALOG_WITH_OPTION(str_name, "%", 1, 0, 100, 0, "E", "");
			LINK__VAR_ANALOG_CTRL(aCH__RCP_RF_PLASMA_DUTY, str_name);

			//
			str_name = "RCP.RF.BAIS.POWER";
			STD__ADD_ANALOG_WITH_OPTION(str_name, "W", 0, 0, 1500, 0, "E", "");
			LINK__VAR_ANALOG_CTRL(aCH__RCP_RF_BIAS_POWER, str_name);

			str_name = "RCP.RF.BAIS.PULSE.FREQ";
			STD__ADD_ANALOG_WITH_OPTION(str_name, "kHz", 1, 0, 10000, 0, "E", "");
			LINK__VAR_ANALOG_CTRL(aCH__RCP_RF_BIAS_PULSE_FREQ, str_name);

			str_name = "RCP.RF.BIAS.FREQ.LEARNED";
			STD__ADD_ANALOG_WITH_OPTION(str_name, "kHz", 1, 0, 10000, 0, "E", "");
			LINK__VAR_ANALOG_CTRL(aCH__RCP_RF_BIAS_FREQ_LEARNED, str_name);

			str_name = "RCP.RF.BIAS.FREQ.PRESET";
			STD__ADD_ANALOG_WITH_OPTION(str_name, "kHz", 1, 0, 10000, 0, "E", "");
			LINK__VAR_ANALOG_CTRL(aCH__RCP_RF_BIAS_FREQ_PRESET, str_name);

			str_name = "RCP.RF.BIAS.TUNE.DELAY";
			STD__ADD_ANALOG_WITH_OPTION(str_name, "msec", 1, 0, 30000, 0, "E", "");
			LINK__VAR_ANALOG_CTRL(aCH__RCP_RF_BIAS_TUNE_DELAY, str_name);

			str_name = "RCP.RF.BAIS.DUTY";
			STD__ADD_ANALOG_WITH_OPTION(str_name, "%", 1, 0, 100, 0, "E", "");
			LINK__VAR_ANALOG_CTRL(aCH__RCP_RF_BIAS_DUTY, str_name);
		}

		// 
		{
			str_name = "RCP.PLASMA.CTRL.MODE";
			STD__ADD_DIGITAL_WITH_OPTION(str_name, "AUTO  PRESET", 0, "E", "");
			LINK__VAR_DIGITAL_CTRL(dCH__RCP_PLASMA_CTRL_MODE, str_name);

			str_name = "RCP.PLASMA.MATCHER.C1";
			STD__ADD_ANALOG_WITH_OPTION(str_name, "%", 1, 0, 100, 0, "E", "");
			LINK__VAR_ANALOG_CTRL(aCH__RCP_PLASMA_MATCHER_C1_OUTPUT, str_name);

			str_name = "RCP.PLASMA.MATCHER.C1.LEARNED";
			STD__ADD_ANALOG_WITH_OPTION(str_name, "%", 1, 0, 100, 0, "E", "");
			LINK__VAR_ANALOG_CTRL(aCH__RCP_PLASMA_MATCHER_C1_LEARNED, str_name);

			str_name = "RCP.PLASMA.MATCHER.C1.PRESET";
			STD__ADD_ANALOG_WITH_OPTION(str_name, "%", 1, 0, 100, 0, "E", "");
			LINK__VAR_ANALOG_CTRL(aCH__RCP_PLASMA_MATCHER_C1_PRESET, str_name);

			str_name = "RCP.PLASMA.MATCHER.C2";
			STD__ADD_ANALOG_WITH_OPTION(str_name, "%", 1, 0, 100, 0, "E", "");
			LINK__VAR_ANALOG_CTRL(aCH__RCP_PLASMA_MATCHER_C2_OUTPUT, str_name);

			str_name = "RCP.PLASMA.MATCHER.C2.LEARNED";
			STD__ADD_ANALOG_WITH_OPTION(str_name, "%", 1, 0, 100, 0, "E", "");
			LINK__VAR_ANALOG_CTRL(aCH__RCP_PLASMA_MATCHER_C2_LEARNED, str_name);

			str_name = "RCP.PLASMA.MATCHER.C2.PRESET";
			STD__ADD_ANALOG_WITH_OPTION(str_name, "%", 1, 0, 100, 0, "E", "");
			LINK__VAR_ANALOG_CTRL(aCH__RCP_PLASMA_MATCHER_C2_PRESET, str_name);

			str_name = "RCP.PLASMA.MATCHER.AUTO.DELAY.TIME";
			STD__ADD_ANALOG_WITH_OPTION(str_name, "sec", 1, 0, 100, 0, "E", "");
			LINK__VAR_ANALOG_CTRL(aCH__RCP_PLASMA_MATCHER_AUTO_DELAY_TIME, str_name);

			//
			str_name = "RCP.BIAS.CTRL.MODE";
			STD__ADD_DIGITAL_WITH_OPTION(str_name, "AUTO  PRESET", 0, "E", "");
			LINK__VAR_DIGITAL_CTRL(dCH__RCP_BIAS_CTRL_MODE, str_name);

			str_name = "RCP.BIAS.MATCHER.C1";
			STD__ADD_ANALOG_WITH_OPTION(str_name, "%", 1, 0, 100, 0, "E", "");
			LINK__VAR_ANALOG_CTRL(aCH__RCP_BIAS_MATCHER_C1_OUTPUT, str_name);

			str_name = "RCP.BIAS.MATCHER.C1.LEARNED";
			STD__ADD_ANALOG_WITH_OPTION(str_name, "%", 1, 0, 100, 0, "E", "");
			LINK__VAR_ANALOG_CTRL(aCH__RCP_BIAS_MATCHER_C1_LEARNED, str_name);

			str_name = "RCP.BIAS.MATCHER.C1.PRESET";
			STD__ADD_ANALOG_WITH_OPTION(str_name, "%", 1, 0, 100, 0, "E", "");
			LINK__VAR_ANALOG_CTRL(aCH__RCP_BIAS_MATCHER_C1_PRESET, str_name);

			str_name = "RCP.BIAS.MATCHER.C2";
			STD__ADD_ANALOG_WITH_OPTION(str_name, "%", 1, 0, 100, 0, "E", "");
			LINK__VAR_ANALOG_CTRL(aCH__RCP_BIAS_MATCHER_C2_OUTPUT, str_name);

			str_name = "RCP.BIAS.MATCHER.C2.LEARNED";
			STD__ADD_ANALOG_WITH_OPTION(str_name, "%", 1, 0, 100, 0, "E", "");
			LINK__VAR_ANALOG_CTRL(aCH__RCP_BIAS_MATCHER_C2_LEARNED, str_name);

			str_name = "RCP.BIAS.MATCHER.C2.PRESET";
			STD__ADD_ANALOG_WITH_OPTION(str_name, "%", 1, 0, 100, 0, "E", "");
			LINK__VAR_ANALOG_CTRL(aCH__RCP_BIAS_MATCHER_C2_PRESET, str_name);

			str_name = "RCP.BIAS.MATCHER.AUTO.DELAY.TIME";
			STD__ADD_ANALOG_WITH_OPTION(str_name, "sec", 1, 0, 100, 0, "E", "");
			LINK__VAR_ANALOG_CTRL(aCH__RCP_BIAS_MATCHER_AUTO_DELAY_TIME, str_name);
		}

		//
		{
			str_name = "RCP.TOP.FRC.CENTER";
			STD__ADD_ANALOG_WITH_OPTION(str_name, "Ratio", 1, 1, 9, 0, "E", "");
			LINK__VAR_ANALOG_CTRL(aCH__RCP_TOP_FRC_CENTER, str_name);
		}

		for(i=0; i<CFG_SIZE__MFC_OBJ; i++)
		{
			str_name.Format("RCP.GAS.%02d.FLOW", i+1);
			STD__ADD_ANALOG_WITH_OPTION(str_name, "sccm", 1, 0, 10000, 0, "E", "");
			LINK__VAR_ANALOG_CTRL(aCH__RCP_GAS_XX_FLOW[i], str_name);
		}

		//
		{
			str_name = "RCP.ESC.CTRL.MODE";
			STD__ADD_DIGITAL_WITH_OPTION(str_name, "DISABLE NoChange CHUCK CHUCK1 CHUCK2 HE.SET DECHUCK DECHUCK1 DECHUCK2", 0, "E", "");
			LINK__VAR_DIGITAL_CTRL(dCH__RCP_ESC_CTRL_MODE, str_name);

			//
			str_name = "RCP.DPC.CENTER";
			STD__ADD_ANALOG_WITH_OPTION(str_name, "torr", 1, 0, 100, 0, "E", "");
			LINK__VAR_ANALOG_CTRL(aCH__RCP_DPC_CENTER, str_name);

			str_name = "RCP.DPC.EDGE";
			STD__ADD_ANALOG_WITH_OPTION(str_name, "torr", 1, 0, 100, 0, "E", "");
			LINK__VAR_ANALOG_CTRL(aCH__RCP_DPC_EDGE, str_name);

			//
			str_name = "RCP.DPC.CENTER.ZONE.FLOW.MAX.THRESHOLD";
			STD__ADD_ANALOG_WITH_OPTION(str_name, "sccm", 1, 0, 100, 0, "E", "");
			LINK__VAR_ANALOG_CTRL(aCH__RCP_DPC_CENTER_FLOW_MAX_THRESHOLD, str_name);

			str_name = "RCP.DPC.CENTER.ZONE.FLOW.MIN.THRESHOLD";
			STD__ADD_ANALOG_WITH_OPTION(str_name, "sccm", 1, 0, 100, 0, "E", "");
			LINK__VAR_ANALOG_CTRL(aCH__RCP_DPC_CENTER_FLOW_MIN_THRESHOLD, str_name);
	
			str_name = "RCP.DPC.EDGE.ZONE.FLOW.MAX.THRESHOLD";
			STD__ADD_ANALOG_WITH_OPTION(str_name, "sccm", 1, 0, 100, 0, "E", "");
			LINK__VAR_ANALOG_CTRL(aCH__RCP_DPC_EDGE_FLOW_MAX_THRESHOLD, str_name);

			str_name = "RCP.DPC.EDGE.ZONE.FLOW.MIN.THRESHOLD";
			STD__ADD_ANALOG_WITH_OPTION(str_name, "sccm", 1, 0, 100, 0, "E", "");
			LINK__VAR_ANALOG_CTRL(aCH__RCP_DPC_EDGE_FLOW_MIN_THRESHOLD, str_name);
		}

		//
		{
			str_name = "RCP.ESC.CENTER.TEMP";
			STD__ADD_ANALOG_WITH_OPTION(str_name, "C", 1, 0, 150, 0, "E", "");
			LINK__VAR_ANALOG_CTRL(aCH__RCP_ESC_CENTER_TEMP, str_name);

			str_name = "RCP.ESC.CENTER.OP_OFFSET";
			STD__ADD_ANALOG_WITH_OPTION(str_name, "%", 1, -50, 50, 0, "E", "");
			LINK__VAR_ANALOG_CTRL(aCH__RCP_ESC_CENTER_OP_OFFSET, str_name);

			//
			str_name = "RCP.ESC.EDGE.TEMP";
			STD__ADD_ANALOG_WITH_OPTION(str_name, "C", 1, 0, 150, 0, "E", "");
			LINK__VAR_ANALOG_CTRL(aCH__RCP_ESC_EDGE_TEMP, str_name);

			str_name = "RCP.ESC.EDGE.OP_OFFSET";
			STD__ADD_ANALOG_WITH_OPTION(str_name, "%", 1, -50, 50, 0, "E", "");
			LINK__VAR_ANALOG_CTRL(aCH__RCP_ESC_EDGE_OP_OFFSET, str_name);
		}

		//
		{
			str_name = "RCP.LIFT_PIN.MODE";
			STD__ADD_DIGITAL_WITH_OPTION(str_name, "Down Middle Up", 0, "E", "");
			LINK__VAR_DIGITAL_CTRL(dCH__RCP_LIFT_PIN_MODE, str_name);
		}

		//
		{
			str_name = "RCP.LOOP_START";
			STD__ADD_ANALOG_WITH_OPTION(str_name, "step", 0, 0, 100, 0, "E", "");
			LINK__VAR_ANALOG_CTRL(aCH__RCP_LOOP_START, str_name);

			str_name = "RCP.LOOP_REPEAT";
			STD__ADD_ANALOG_WITH_OPTION(str_name, "cycle", 0, 0, 1000, 0, "E", "");
			LINK__VAR_ANALOG_CTRL(aCH__RCP_LOOP_REPEAT, str_name);
		}
	}

	// RCP CTRL REQ ...
	{
		str_name = "RCP.MATCHER_TOP.CTRL.REQ";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__RCP_MATCHER_TOP__CTRL_REQ, str_name);
	}

	// STEP : HEATER CONFIG ...
	{
		str_name = "CFG.STEP.ESC_HEATER.STABLE.CHECK";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name, "DIABLE ENABLE", "");
		LINK__VAR_DIGITAL_CTRL(dCH__CFG_STEP_ESC_HEATER_STABLE_CHECK, str_name);

		str_name = "CFG.STEP.ESC_HEATER.FAULT.CHECK";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name, "DIABLE ENABLE", "");
		LINK__VAR_DIGITAL_CTRL(dCH__CFG_STEP_ESC_HEATER_FAULT_CHECK, str_name);
	}

	// APC_CONTROL ...
	{
		str_name = "PRE_RCP.APC.CTRL";	
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__PRE_RCP_APC_CTRL, str_name);
	}

	// MFC ...
	{
		for(i=0; i<CFG_SIZE__MFC_OBJ; i++)
		{
			str_name.Format("PRE_RCP.MFC.GAS%1d.FLOW",i+1);
			STD__ADD_STRING(str_name);
			LINK__VAR_STRING_CTRL(sCH__PRE_RCP_MFC_SET_FLOW[i], str_name);
		}
	}

	// RFx_BIAS
	{
		str_name = "PRE_RCP.RF_BIAS_POWER";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__PRE_RCP_RF_BIAS__POWER, str_name);
	}
	
	// MAT : RF_BIAS
	{
		str_name = "PRE_RCP.MAT_BIAS_CONTROL_MODE";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__PRE_RCP_MAT_BIAS_CONTROL_MODE, str_name);

		str_name = "PRE_RCP.MAT_BIAS_LOAD_POSITION";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__PRE_RCP_MAT_BIAS_LOAD_POSITION, str_name);

		str_name = "PRE_RCP.MAT_BIAS_TUNE_POSITION";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__PRE_RCP_MAT_BIAS_TUNE_POSITION, str_name);

		str_name = "PRE_RCP.MAT_BIAS_AUTO_DELAY_TIME";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__PRE_RCP_MAT_BIAS_AUTO_DELAY_TIME, str_name);
	}

	// ...
	{
		p_variable->Add__MONITORING_PROC(1.0, _FNC_MON_ID__RCP_MATCHER_TOP__CTRL_REQ);
		p_variable->Add__MONITORING_PROC(1.0, MON_ID__WAFER_COUNT_CTRL);
	}
	return 1;
}

int CObj__STEP_FNC::__DEFINE__ALARM(p_alarm)
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
		alarm_id = ALID__PROCESS_STEP_OVERTIME;
		alarm_title  = title;
		alarm_title += " SYSTEM - PROCESS STEP OVERTIME ALARM.";
	
		alarm_msg = "Process Step Time-Over Alarm Message.\n";
		alarm_msg += "Check Process Step time and Control time.";
	
		l_act.RemoveAll();
		l_act.Add("CHECK");
	
		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	// ...
	{
		alarm_id = ALID__PROCESS_STABLE_OVERTIME;
		alarm_title  = title;
		alarm_title += " SYSTEM - PROCESS STEP STABLE OVERTIME ALARM.";
	
		alarm_msg = "Process Stable Step Timeover Alarm Message.\n";
		alarm_msg += "Check Process Stable Step time and Control time.";
	
		l_act.RemoveAll();
		l_act.Add("CHECK");
	
		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	// ...
	{
		alarm_id = ALID__PROCESS_OVERETCH_OVERTIME;
		alarm_title  = title;
		alarm_title += " SYSTEM - OVERETCH OVERTIME ALARM.";
	
		alarm_msg = "Process OverEtch Step Timeover Alarm Message.\n";
		alarm_msg += "Check Process OverEtch time and Step time.";
	
		l_act.RemoveAll();
		l_act.Add("CHECK");
	
		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	// ...
	{
		alarm_id = ALID__PROCESS_CH_INTERLOCK_ALARM;
		alarm_title  = title;
		alarm_title += " SYSTEM - PROCESS INTERLOCK CHANNEL ALARM.";
	
		alarm_msg = "Process Interlock Channel Alarm Message.\n";
		alarm_msg += "Check Interlock Switch Status.";
	
		l_act.RemoveAll();
		l_act.Add("CHECK");
	
		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}
	
	// ...
	{
		alarm_id = ALID__RECIPE_OES_DATA_NULL_ERROR;
		alarm_title  = title;
		alarm_title += " SYSTEM - RECIPE OES DATA NULL ERROR.";
	
		alarm_msg = "Recipe Oes Data Item has no data.\n";
		alarm_msg += "Please, check oes recipe item's data.";
	
		l_act.RemoveAll();
		l_act.Add("CHECK");
	
		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	// ...
	{
		alarm_id = ALID__SYSTEM_INTERLOCK_SENSOR_ERROR;

		alarm_title  = title;
		alarm_title += " SYSTEM - Interlock Sensor Error !";

		alarm_msg = "Please, check interlock sensor. \n";

		l_act.RemoveAll();
		l_act.Add("CHECK");
	
		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	// ...
	{
		alarm_id = ALID__MFC_INTERLOCK_CLOSE_ERROR;

		alarm_title  = title;
		alarm_title += " - MFC Interlock Close Error !";

		alarm_msg = "Please, check mfc interlock page. \n";

		l_act.RemoveAll();
		l_act.Add("CHECK");
	
		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	// ...
	{
		alarm_id = ALID__PROCESS_RECIPE_FILE_CHANGING_NOW;
		
		alarm_title  = title;
		alarm_title += "Process recipe file is being changed, now. \n";
		
		alarm_msg  = "The process will run after recipe file save. \n";
		alarm_msg += "Please, wait or recipe file. \n";
		
		l_act.RemoveAll();
		l_act.Add("CHECK");
		
		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}
	
	// CHM PRESSURE ...
	// ...
	{
		alarm_id = ALID__CHM_PRESSURE_TOLERANCE_WARNING;

		alarm_title  = title;
		alarm_title += "Chamber Pressure Tolerance Warning !";

		alarm_msg  = "During process run, chamber pressure tolerance warning occurred !\n";
		alarm_msg += "Please, check chamber pressure.\n";

		l_act.RemoveAll();
		l_act.Add("CHECK");
	
		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}
	// ...
	{
		alarm_id = ALID__CHM_PRESSURE_TOLERANCE_FAULT;

		alarm_title  = title;
		alarm_title += "Chamber Pressure Tolerance Fault !";

		alarm_msg  = "During process run, chamber pressure tolerance fault occurred !\n";
		alarm_msg += "Please, check chamber pressure.\n";

		l_act.RemoveAll();
		l_act.Add("CHECK");
	
		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	// RF BIAS ...
	{
		// ...
		{
			alarm_id = ALID__RF_BIAS__TOLERANCE_WARNING;

			alarm_title  = title;
			alarm_title += "RF_BIAS Power Tolerance Warning !";

			alarm_msg  = "During process run, RF_BIAS power tolerance warning occurred !\n";
			alarm_msg += "Please, check RF_BIAS power.\n";

			l_act.RemoveAll();
			l_act.Add("CHECK");
		
			ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
		}

		// ...
		{
			alarm_id = ALID__RF_BIAS__TOLERANCE_FAULT;

			alarm_title  = title;
			alarm_title += "RF_BIAS Power Tolerance Fault !";

			alarm_msg  = "During process run, RF_BIAS power tolerance fault occurred !\n";
			alarm_msg += "Please, check RF_BIAS power.\n";

			l_act.RemoveAll();
			l_act.Add("CHECK");
		
			ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
		}
	}

	// ...
	{
		alarm_id = ALID__MIDDLE_PIN_UP_TIMEOUT;
	
		alarm_title  = title;
		alarm_title += "Middle-Pin Up Timeout !";
		
		alarm_msg  = "Please, check recipe step about middle-pin, or pin sensor. \n";
		
		l_act.RemoveAll();
		l_act.Add("CHECK");
		
		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}


	// ------------------------------------------------------------------------------------
	// Header Temperature ...

	// Top Temperature ...
	// ...
	{
		alarm_id = ALID__ALL_TEMP__HEADER_READY_CHECK;

		alarm_title  = title;
		alarm_title += "Header Ctrl - All temperature are checked ...";

		alarm_msg  = "Header recipe is running ...\n";
		alarm_msg += "During process run, all temperature are checked ...\n";
		alarm_msg += "Please, wait until all temperature are ready.\n";

		l_act.RemoveAll();
		l_act.Add("CHECK");
	
		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}
	// ...
	{
		alarm_id = ALID__ALL_TEMP__HEADER_READY_COMPLETE;

		alarm_title  = title;
		alarm_title += "Header Ctrl - All temperature are ready ...";

		alarm_msg  = "Process will start ...\n";

		l_act.RemoveAll();
		l_act.Add("CHECK");
	
		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	// ...
	{
		alarm_id = ALID__TOP_TEMP__HEADER_TOLERANCE_WARNING;

		alarm_title  = title;
		alarm_title += "Header Ctrl - Top Temperature Tolerance Warning !";

		alarm_msg  = "During process run, top temperature (TCU) tolerance warning occurred !\n";
		alarm_msg += "Please, check Top Chiller (TCU).\n";

		l_act.RemoveAll();
		l_act.Add("CHECK");
	
		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}
	// ...
	{
		alarm_id = ALID__TOP_TEMP__HEADER_TOLERANCE_FAULT;

		alarm_title  = title;
		alarm_title += "Header Ctrl - Top Temperature Tolerance Fault !";

		alarm_msg  = "During process run, top temperature (TCU) tolerance fault occurred !\n";
		alarm_msg += "Please, check Top Chiller (TCU).\n";

		l_act.RemoveAll();
		l_act.Add("CHECK");
	
		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}
	// ...
	{
		alarm_id = ALID__TOP_TEMP__HEADER_LOW_LIMIT;

		alarm_title  = title;
		alarm_title += "Header Ctrl - Top Temperature Low-Limit !";

		alarm_msg  = "During process run, top temperature (TCU) low-limit occurred !\n";
		alarm_msg += "Please, check Top Chiller (TCU).\n";

		l_act.RemoveAll();
		l_act.Add("CHECK");
	
		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}
	// ...
	{
		alarm_id = ALID__TOP_TEMP__HEADER_HIGH_LIMIT;

		alarm_title  = title;
		alarm_title += "Header Ctrl - Top Temperature High-Limit !";

		alarm_msg  = "During process run, top temperature (TCU) High-limit occurred !\n";
		alarm_msg += "Please, check Top Chiller (TCU).\n";

		l_act.RemoveAll();
		l_act.Add("CHECK");
	
		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	// Bottom Temperature ...
	// ...
	{
		alarm_id = ALID__BOTTOM_TEMP__HEADER_TOLERANCE_WARNING;

		alarm_title  = title;
		alarm_title += "Header Ctrl - Bottom Temperature Tolerance Warning !";

		alarm_msg  = "During process run, bottom temperature (ESC) tolerance warning occurred !\n";
		alarm_msg += "Please, check Top Chiller (ESC).\n";

		l_act.RemoveAll();
		l_act.Add("CHECK");
	
		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}
	// ...
	{
		alarm_id = ALID__BOTTOM_TEMP__HEADER_TOLERANCE_FAULT;

		alarm_title  = title;
		alarm_title += "Header Ctrl - Bottom Temperature Tolerance Fault !";

		alarm_msg  = "During process run, bottom temperature (ESC) tolerance fault occurred !\n";
		alarm_msg += "Please, check Top Chiller (ESC).\n";

		l_act.RemoveAll();
		l_act.Add("CHECK");
	
		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}
	// ...
	{
		alarm_id = ALID__BOTTOM_TEMP__HEADER_LOW_LIMIT;

		alarm_title  = title;
		alarm_title += "Header Ctrl - Bottom Temperature Low-Limit !";

		alarm_msg  = "During process run, bottom temperature (ESC) low-limit occurred !\n";
		alarm_msg += "Please, check Top Chiller (ESC).\n";

		l_act.RemoveAll();
		l_act.Add("CHECK");
	
		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}
	// ...
	{
		alarm_id = ALID__BOTTOM_TEMP__HEADER_HIGH_LIMIT;

		alarm_title  = title;
		alarm_title += "Header Ctrl - Bottom Temperature High-Limit !";

		alarm_msg  = "During process run, bottom temperature (ESC) high-limit occurred !\n";
		alarm_msg += "Please, check Top Chiller (ESC).\n";

		l_act.RemoveAll();
		l_act.Add("CHECK");
	
		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	// Top Plate Temperature ...
	// ...
	{
		alarm_id = ALID__TOP_PLATE__HEADER_TOLERANCE_WARNING;

		alarm_title  = title;
		alarm_title += "Header Ctrl - Top Plate Temperature Tolerance Warning !";

		alarm_msg  = "During process run, \"top plate\" temperature tolerance warning occurred !\n";
		alarm_msg += "Please, check \"Top Plate Heater\".\n";

		l_act.RemoveAll();
		l_act.Add("CHECK");
	
		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}
	// ...
	{
		alarm_id = ALID__TOP_PLATE__HEADER_TOLERANCE_FAULT;

		alarm_title  = title;
		alarm_title += "Header Ctrl - \"Top Plate\" Temperature Tolerance Fault !";

		alarm_msg  = "During process run, \"top plate\" temperature tolerance fault occurred !\n";
		alarm_msg += "Please, check \"Top Plate Heater\".\n";

		l_act.RemoveAll();
		l_act.Add("CHECK");
	
		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}
	// ...
	{
		alarm_id = ALID__TOP_PLATE__HEADER_LOW_LIMIT;

		alarm_title  = title;
		alarm_title += "Header Ctrl - \"Top Plate\" Temperature Low-Limit !";

		alarm_msg  = "During process run, \"top plate\" temperature low-limit occurred !\n";
		alarm_msg += "Please, check \"Top Plate Heater\".\n";

		l_act.RemoveAll();
		l_act.Add("CHECK");
	
		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}
	// ...
	{
		alarm_id = ALID__TOP_PLATE__HEADER_HIGH_LIMIT;

		alarm_title  = title;
		alarm_title += "Header Ctrl - \"Top Plate\" Temperature High-Limit !";

		alarm_msg  = "During process run, \"top plate\" temperature high-limit occurred !\n";
		alarm_msg += "Please, check \"Top Plate Heater\".\n";

		l_act.RemoveAll();
		l_act.Add("CHECK");
	
		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	// ...
	{
		alarm_id = ALID__TCU__ERROR_SENSOR_DETECTED;

		alarm_title  = title;
		alarm_title += "The error sensor of TCU is detected !";

		alarm_msg  = "If chamber's status is \"processing\", process will be aborted. \n";
		alarm_msg += "If chmaber's status is \"idle\", chamber's status will be \"maint\". \n";
		alarm_msg += "Please, check TCU's status. \n";

		l_act.RemoveAll();
		l_act.Add("CHECK");
		
		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}
	// ...
	{
		alarm_id = ALID__TCU__WARNING_SENSOR_DETECTED;

		alarm_title  = title;
		alarm_title += "The warning sensor of TCU is detected !";
		
		alarm_msg = "Please, check TCU's status. \n";
		
		l_act.RemoveAll();
		l_act.Add("CHECK");
		
		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	// ...
	{
		alarm_id = ALID__GAS_BOX__ERROR_SENSOR_DETECTED;
		
		alarm_title  = title;
		alarm_title += "The door of gas box is not closed !";
		
		alarm_msg  = "If chamber's status is \"processing\", process will be aborted. \n";
		alarm_msg += "If chamber's status is \"idle\", chamber's status will be \"maint\". \n";
		alarm_msg += "Please, check the status of gas box. \n";
		
		l_act.RemoveAll();
		l_act.Add("CHECK");
		
		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}


	// ------------------------------------------------------------------------------------
	// Step Temperature ...

	// Top Temperature ...
	// ...
	{
		alarm_id = ALID__ALL_TEMP__STEP_READY_CHECK;

		alarm_title  = title;
		alarm_title += "Step Ctrl - All temperature are checked ...";

		alarm_msg  = "Header recipe is running ...\n";
		alarm_msg += "During process run, all temperature are checked ...\n";
		alarm_msg += "Please, wait until all temperature are ready.\n";

		l_act.RemoveAll();
		l_act.Add("CHECK");
	
		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}
	// ...
	{
		alarm_id = ALID__ALL_TEMP__STEP_READY_COMPLETE;

		alarm_title  = title;
		alarm_title += "Step Ctrl - All temperature are ready ...";

		alarm_msg  = "Process will start ...\n";

		l_act.RemoveAll();
		l_act.Add("CHECK");
	
		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	// ...
	{
		alarm_id = ALID__TOP_TEMP__STEP_TOLERANCE_WARNING;

		alarm_title  = title;
		alarm_title += "Step Ctrl - Top Temperature Tolerance Warning !";

		alarm_msg  = "During process run, top temperature (TCU) tolerance warning occurred !\n";
		alarm_msg += "Please, check Top Chiller (TCU).\n";

		l_act.RemoveAll();
		l_act.Add("CHECK");
	
		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}
	// ...
	{
		alarm_id = ALID__TOP_TEMP__STEP_TOLERANCE_FAULT;

		alarm_title  = title;
		alarm_title += "Step Ctrl - Top Temperature Tolerance Fault !";

		alarm_msg  = "During process run, top temperature (TCU) tolerance fault occurred !\n";
		alarm_msg += "Please, check Top Chiller (TCU).\n";

		l_act.RemoveAll();
		l_act.Add("CHECK");
	
		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}
	// ...
	{
		alarm_id = ALID__TOP_TEMP__STEP_LOW_LIMIT;

		alarm_title  = title;
		alarm_title += "Step Ctrl - Top Temperature Low-Limit !";

		alarm_msg  = "During process run, top temperature (TCU) low-limit occurred !\n";
		alarm_msg += "Please, check Top Chiller (TCU).\n";

		l_act.RemoveAll();
		l_act.Add("CHECK");
	
		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}
	// ...
	{
		alarm_id = ALID__TOP_TEMP__STEP_HIGH_LIMIT;

		alarm_title  = title;
		alarm_title += "Step Ctrl - Top Temperature High-Limit !";

		alarm_msg  = "During process run, top temperature (TCU) High-limit occurred !\n";
		alarm_msg += "Please, check Top Chiller (TCU).\n";

		l_act.RemoveAll();
		l_act.Add("CHECK");
	
		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	// Bottom Temperature ...
	// ...
	{
		alarm_id = ALID__BOTTOM_TEMP__STEP_TOLERANCE_WARNING;

		alarm_title  = title;
		alarm_title += "Step Ctrl - Bottom Temperature Tolerance Warning !";

		alarm_msg  = "During process run, bottom temperature (ESC) tolerance warning occurred !\n";
		alarm_msg += "Please, check Top Chiller (ESC).\n";

		l_act.RemoveAll();
		l_act.Add("CHECK");
	
		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}
	// ...
	{
		alarm_id = ALID__BOTTOM_TEMP__STEP_TOLERANCE_FAULT;

		alarm_title  = title;
		alarm_title += "Step Ctrl - Bottom Temperature Tolerance Fault !";

		alarm_msg  = "During process run, bottom temperature (ESC) tolerance fault occurred !\n";
		alarm_msg += "Please, check Top Chiller (ESC).\n";

		l_act.RemoveAll();
		l_act.Add("CHECK");
	
		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}
	// ...
	{
		alarm_id = ALID__BOTTOM_TEMP__STEP_LOW_LIMIT;

		alarm_title  = title;
		alarm_title += "Step Ctrl - Bottom Temperature Low-Limit !";

		alarm_msg  = "During process run, bottom temperature (ESC) low-limit occurred !\n";
		alarm_msg += "Please, check Top Chiller (ESC).\n";

		l_act.RemoveAll();
		l_act.Add("CHECK");
	
		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}
	// ...
	{
		alarm_id = ALID__BOTTOM_TEMP__STEP_HIGH_LIMIT;

		alarm_title  = title;
		alarm_title += "Step Ctrl - Bottom Temperature High-Limit !";

		alarm_msg  = "During process run, bottom temperature (ESC) high-limit occurred !\n";
		alarm_msg += "Please, check Top Chiller (ESC).\n";

		l_act.RemoveAll();
		l_act.Add("CHECK");
	
		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	// Top Plate Temperature ...
	// ...
	{
		alarm_id = ALID__TOP_PLATE__STEP_TOLERANCE_WARNING;

		alarm_title  = title;
		alarm_title += "Step Ctrl - Top Plate Temperature Tolerance Warning !";

		alarm_msg  = "During process run, \"top plate\" temperature tolerance warning occurred !\n";
		alarm_msg += "Please, check \"Top Plate Heater\".\n";

		l_act.RemoveAll();
		l_act.Add("CHECK");
	
		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}
	// ...
	{
		alarm_id = ALID__TOP_PLATE__STEP_TOLERANCE_FAULT;

		alarm_title  = title;
		alarm_title += "Step Ctrl - \"Top Plate\" Temperature Tolerance Fault !";

		alarm_msg  = "During process run, \"top plate\" temperature tolerance fault occurred !\n";
		alarm_msg += "Please, check \"Top Plate Heater\".\n";

		l_act.RemoveAll();
		l_act.Add("CHECK");
	
		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}
	// ...
	{
		alarm_id = ALID__TOP_PLATE__STEP_LOW_LIMIT;

		alarm_title  = title;
		alarm_title += "Step Ctrl - \"Top Plate\" Temperature Low-Limit !";

		alarm_msg  = "During process run, \"top plate\" temperature low-limit occurred !\n";
		alarm_msg += "Please, check \"Top Plate Heater\".\n";

		l_act.RemoveAll();
		l_act.Add("CHECK");
	
		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}
	// ...
	{
		alarm_id = ALID__TOP_PLATE__STEP_HIGH_LIMIT;

		alarm_title  = title;
		alarm_title += "Step Ctrl - \"Top Plate\" Temperature High-Limit !";

		alarm_msg  = "During process run, \"top plate\" temperature high-limit occurred !\n";
		alarm_msg += "Please, check \"Top Plate Heater\".\n";

		l_act.RemoveAll();
		l_act.Add("CHECK");
	
		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	// ...
	{
		alarm_id = ALID__STEP_TEMP_CTRL_ABORTED;

		alarm_title  = title;
		alarm_title += "Step Ctrl - Aborted !";

		alarm_msg = "";

		l_act.RemoveAll();
		l_act.Add("CHECK");

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	// ...
	{
		alarm_id = ALID__PROC_RESTART_SYSTEM_INIT_ERROR;

		alarm_title  = title;
		alarm_title += "\"Restart\" Recovery Action : System Init Error";

		alarm_msg = "";

		l_act.RemoveAll();
		l_act.Add("CHECK");

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	// ...
	{
		alarm_id = ALID__WAP_MOVING_COMPLETE__TIMEOUT;
		
		alarm_title  = title;
		alarm_title += "WAP Moving Complete Timeout Error";
		
		alarm_msg = "Please, check the status of C-Ring control board.";
		
		l_act.RemoveAll();
		l_act.Add("CHECK");
		
		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}


	// ------------------------------------------------------------------------------------
	// ...
	{
		alarm_id = ALID__HE_DECHUCK__TIMEOUT;

		alarm_title  = title;
		alarm_title += "\"He Dechuck\" Timeout !";

		alarm_msg  = "Please, don't let lift-pin up. \n";

		l_act.RemoveAll();
		l_act.Add("CHECK");

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	// ...
	{
		alarm_id = ALID__HE_DECHUCK__INIT_ERROR;

		alarm_title  = title;
		alarm_title += "\"He Dechuck\" Initial Error !";

		alarm_msg  = "Please, don't let lift-pin up. \n";
		alarm_msg += "If you click [ABORT],  Init sequence will be aborted. \n";
		alarm_msg += "If you click [IGNORE], Init sequence will be completed. \n";

		l_act.RemoveAll();
		l_act.Add(STR__ABORT);
		l_act.Add(STR__IGNORE);

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	// ...
	{
		int alarm_id = ALID__WAP_CONDUCTANCE__NOT_CHECK;
	
		alarm_title  = title;
		alarm_title += "\"WAP Conductance\" is not checked !";

		alarm_msg  = "You must execute \"WAP Conductance\", after Chamber was open. \n";
		alarm_msg += "Please, execute \"WAP Conductance\" in utility page. \n";
		alarm_msg += "\n";
		alarm_msg += "If you click [ABORT],  Init sequence will be aborted. \n";
		alarm_msg += "If you click [IGNORE], Init sequence will be completed. \n";

		l_act.RemoveAll();
		l_act.Add(STR__ABORT);
		l_act.Add(STR__IGNORE);

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	// ...
	{
		int alarm_id = ALID__CHAMBER_LID__OPEN;
		
		alarm_title  = title;
		alarm_title += "\"Chamber's lid is not close !";
		
		alarm_msg  = "After chamber PM, you must check \"WAP Conductance\". \n";
		alarm_msg += "\n";
		
		l_act.RemoveAll();
		l_act.Add("CHECK");
		
		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	// ...
	{
		int alarm_id = ALID__SYSTEM_INTERLOCK_OCCUR;

		alarm_title  = title;
		alarm_title += "System interlock occurred !";
		
		alarm_msg = "";
		
		l_act.RemoveAll();
		l_act.Add("CHECK");
		
		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}


	// MFCx ...
	{
		CString msg;
		int i;

		for(i=0; i<CFG_SIZE__MFC_OBJ; i++)
		{
			alarm_id = ALID__GAS_FLOW_TOLERANCE_WARNING + i;

			alarm_title  = title;
			msg.Format("Gas%002d's Flow Tolerance Warning !", i+1);
			alarm_title += msg;

			msg.Format("During process run, Gas%002d's flow tolerance warning occurred !\n", i+1);
			alarm_msg  = msg;
			msg.Format("Please, check Gas%002d's flow.\n", i+1);
			alarm_msg += msg;

			l_act.RemoveAll();
			l_act.Add("CHECK");

			ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
		}

		for(i=0; i<CFG_SIZE__MFC_OBJ; i++)
		{
			alarm_id = ALID__GAS_FLOW_TOLERANCE_FAULT + i;

			alarm_title  = title;
			msg.Format("Gas%002d's Flow Tolerance Fault !", i+1);
			alarm_title += msg;

			msg.Format("During process run, Gas%002d's flow tolerance fault occurred !\n", i+1);
			alarm_msg  = msg;
			msg.Format("Please, check Gas%002d's flow.\n", i+1);
			alarm_msg += msg;
			alarm_msg += "Process will be aborted.\n";

			l_act.RemoveAll();
			l_act.Add("CHECK");

			ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
		}
	}

	return 1;
}

int CObj__STEP_FNC::__Define__USER_FUNCTION(CII_DEFINE__FUNCTION *p_fnc_ctrl)
{
	p_fnc_ctrl->Link__ERROR_FEEDBACK(&mERROR__USER_FNC);

	return 1;
}

//-------------------------------------------------------------------------
int CObj__STEP_FNC::__INITIALIZE__OBJECT(p_variable,p_ext_obj_create)
{
	// ...
	{
		hEVENT__RCP_MATCHER_CTRL = CreateEvent(NULL,FALSE,FALSE,NULL);
	}

	// ...
	xI_TIMER->REGISTER__ABORT_OBJECT(sObject_Name);

	// ...
	{
		iDCOP__START_FLAG   = -1;
	}

	// ...
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

	// FNC PROC
	{
		def_name = "OBJ__FNC_PROC";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, obj_name);
		
		pOBJ_CTRL__PROC = p_ext_obj_create->Create__OBJECT_CTRL(obj_name);
		
		LINK__EXT_VAR_STRING_CTRL(sEXT_CH__EXCEPTION_ACT,        obj_name, "EXCEPTION.ACT");
		LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__STEP_CUR_NUM,         obj_name, "STEP.CUR.NUM");
		LINK__EXT_VAR_STRING_CTRL(sEXT_CH__LAST_STEP_FLAG,       obj_name, "LAST.STEP.FLAG");
		LINK__EXT_VAR_STRING_CTRL(sEXT_CH__RCP_FILE_UPLOAD_FLAG, obj_name, "RCP_FILE.UPLOAD_FLAG");
	}

	// DB SYS ...
	{
		CString str_name;

		//
		def_name = "OBJ__DB_SYS";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name,obj_name);

		//
		str_name = "CFG.SCH_TEST.SIM.ALARM_STEP.ACTIVE";
		LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__CFG_SCH_TEST_SIM_ALARM_STEP_ACTIVE, obj_name,str_name);
					
		//
		for(i=0; i<CFG_SIZE__MFC_OBJ; i++)
		{
			for(int k=0; k<CFG_INTERLOCK__MFC_SIZE; k++)
			{
				str_name.Format("CFG.INTERLOCK.MFC%1d.MFC_TYPE%1d", i+1,k+1);
				LINK__EXT_VAR_DIGITAL_CTRL(dCH__CFG_INTERLOCK_MFC_TYPE[i][k], obj_name,str_name);
			}
		}

		//
		str_name = "SYSTEM.INTERLOCK.FLAG";
		LINK__EXT_VAR_STRING_CTRL(sEXT_CH__SYSTEM_INTERLOCK_FLAG, obj_name,str_name);

		str_name = "SYSTEM.PROCESS.STEP.ID";
		LINK__EXT_VAR_STRING_CTRL(sEXT_CH__STEP_ID, obj_name,str_name);
	}

	// DB INF ...
	{
		def_name = "OBJ__DB_INF";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name,obj_name);

		// ...
		LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__SLOT01_STATUS,  obj_name,"SLOT01.STATUS");
		LINK__EXT_VAR_STRING_CTRL(sEXT_CH__CUR_LOTID,       obj_name,"SLOT01.LOTID");
		LINK__EXT_VAR_STRING_CTRL(sEXT_CH__RF_ON_FLAG,      obj_name,"RF.ON.STS");

		LINK__EXT_VAR_STRING_CTRL(xEXT_CH__PMC_PROC_READY_FLAG, obj_name,"PMC.PROC_READY.FLAG");
		LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__CHM_PRESSURE_TORR,   obj_name,"CHM.PRESSURE.VALUE");

		var_name = "CFG.DECHUCK.CTRL.MODE";
		LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__CFG_DECHUCK_CTRL_MODE, obj_name,var_name);
	}

	// OBJ : VAC_VALVE ...
	{
		def_name = "OBJ__VAC_VALVE";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, obj_name);

		def_check = x_utility.Check__Link(obj_name);
		bActive__OBJ_CTRL__VAC_VLV = def_check;

		if(def_check)
		{
			pOBJ_CTRL__VAC_VLV = p_ext_obj_create->Create__OBJECT_CTRL(obj_name);
		}
	}
	// OBJ : APC ...
	{
		def_name = "OBJ__APC";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, obj_name);
	
		def_check = x_utility.Check__Link(obj_name);
		bActive__OBJ_CTRL__APC = def_check;

		if(def_check)
		{
			pOBJ_CTRL__APC = p_ext_obj_create->Create__OBJECT_CTRL(obj_name);

			//
			LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__APC_OBJ__CTRL, obj_name,STR__CTRL);

			LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__APC_OBJ__PARA_PRESSURE,	obj_name,"PARA.PRESSURE");
			LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__APC_OBJ__PARA_POSITION,	obj_name,"PARA.POSITION");

			LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__APC_OBJ__PARA_PRE_POS_VALUE,	obj_name,"PARA.PRE_POS.VALUE");
			LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__APC_OBJ__PARA_PRE_POS_SEC,	obj_name,"PARA.PRE_POS.SEC");

			LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__APC_OBJ__ABORT_FLAG,  obj_name,"INR.OUT.dAPC.ABORT.FLAG");
			LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__APC_OBJ__STABLE_FLAG, obj_name,"APC.STABLE.FLAG");
		}
	}
		
	// OBJ : FRC1 ...
	{	
		def_name = "OBJ__FRC1";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, obj_name);

		def_check = x_utility.Check__Link(obj_name);
		bActive__OBJ_CTRL__FRC1 = def_check;

		if(def_check)
		{
			pOBJ_CTRL__FRC1 = p_ext_obj_create->Create__OBJECT_CTRL(obj_name);

			//
			LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__FRC1__OBJ_CTRL,   obj_name, STR__CTRL);
			LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__FRC1__CENTER_FLOW, obj_name,"PARA.CH2.SET_RATIO");

			LINK__EXT_VAR_STRING_CTRL(sEXT_CH__FRC1__MON_STABLE_FLAG, obj_name,"MON.STABLE.FLAG");
			LINK__EXT_VAR_STRING_CTRL(sEXT_CH__FRC1__MON_FAULT_FLAG,  obj_name,"MON.FAULT.FLAG");
		}
	}

	// OBJ : ESC HEATER ...
	{
		def_name = "OBJ__ESC_HEATER";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, obj_name);

		def_check = x_utility.Check__Link(obj_name);
		bActive__OBJ_CTRL__ESC_HTR = def_check;

		if(def_check)
		{
			pOBJ_CTRL__ESC_HTR = p_ext_obj_create->Create__OBJECT_CTRL(obj_name);

			//
			var_name = "MON.IO.SET.FEEDFORWARD_OP.LOOP.1";
			LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__ESC_HTR__MON_IO_SET_CENTER_FEEDFORWARD_OP, obj_name,var_name);

			var_name = "MON.IO.SET.FEEDFORWARD_OP.LOOP.2";
			LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__ESC_HTR__MON_IO_SET_EDGE_FEEDFORWARD_OP, obj_name,var_name);

			//
			var_name = "MON.HEATING.FLAG";
			LINK__EXT_VAR_STRING_CTRL(sEXT_CH__ESC_HTR__MON_HEATING_FLAG, obj_name,var_name);

			var_name = "MON.STABLE.FLAG";
			LINK__EXT_VAR_STRING_CTRL(sEXT_CH__ESC_HTR__MON_STABLE_FLAG, obj_name,var_name);
	
			var_name = "MON.FAULT.FLAG";
			LINK__EXT_VAR_STRING_CTRL(sEXT_CH__ESC_HTR__MON_FAULT_FLAG, obj_name,var_name);
		}
	}

	// OBJ - MFCx
	{
		def_name = "OBJ_MFC__SIZE";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, def_data);

		iOBJ_MFC__SIZE = atoi(def_data);
		if(iOBJ_MFC__SIZE >= CFG_SIZE__MFC_OBJ)			iOBJ_MFC__SIZE = CFG_SIZE__MFC_OBJ;			

		for(i=0; i<iOBJ_MFC__SIZE; i++)
		{
			def_name.Format("OBJ__MFC%1d",i+1);
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name, obj_name);

			pOBJ_CTRL__MFC[i] = p_ext_obj_create->Create__OBJECT_CTRL(obj_name);

			//
			LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__MFC__OBJ_CTRL[i], obj_name,STR__CTRL);

			//
			LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__MFC__CFG_USE_FLAG[i], obj_name,"CFG.MFC.USE.FLAG");

			// 1. SET FLOW	
			LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__MFC__SET_FLOW[i], obj_name,"PARA.SET.FLOW");

			// 2. GET FLOW
			LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__MFC__GET_FLOW[i], obj_name,"MON.MFC.READ.FLOW");

			// 3. CFG GAS NAME
			LINK__EXT_VAR_STRING_CTRL(sEXT_CH__MFC__CFG_GASx_NAME[i], obj_name,"CFG.GAS.NAME");

			// 4. CFG ABORT FLAG
			LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__MFC__ABORT_FLAG[i], obj_name,"MFC.ABORT.FLAG");

			// 5. STABLE FLAG
			LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__MFC__STABLE_FLAG[i], obj_name,"MFC.STABLE.FLAG");
		}
	}

	// RFx GEN OBJ - FNC .....
	{
		// RF_BIAS ...
		{
			def_name = "OBJ__RF_BIAS";
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name, obj_name);

			def_check = x_utility.Check__Link(obj_name);
			bActive__OBJ_CTRL__RF_BIAS = def_check;

			if(def_check)
			{
				pOBJ_CTRL__RF_BIAS = p_ext_obj_create->Create__OBJECT_CTRL(obj_name);

				//
				var_name = STR__CTRL;
				LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__RF_BIAS__OBJ_CTRL, obj_name,var_name);

				//
				var_name = "PARA.SET.POWER";
				LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__RF_BIAS__PARA_SET_POWER, obj_name,var_name);
	
				var_name = "MON.IO.POWER.SET";
				LINK__EXT_VAR_STRING_CTRL(sEXT_CH__RF_BIAS__MON_IO_POWER_SET, obj_name,var_name);

				//
				var_name = "RF.STABLE.FLAG";
				LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__RF_BIAS__STABLE_FLAG, obj_name,var_name);

				var_name = "RF.ABORT.FLAG";
				LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__RF_BIAS__ABORT_FLAG, obj_name,var_name);
			}
		}

		// RF_PLASMA ...
		{
			def_name = "OBJ__RF_PLASMA";
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name, obj_name);
		
			def_check = x_utility.Check__Link(obj_name);
			bActive__OBJ_CTRL__RF_PLASMA = def_check;

			if(def_check)
			{
				pOBJ_CTRL__RF_PLASMA = p_ext_obj_create->Create__OBJECT_CTRL(obj_name);

				//
				var_name = STR__CTRL;
				LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__RF_PLASMA__OBJ_CTRL, obj_name,var_name);

				//
				var_name = "PARA.SET.POWER";
				LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__RF_PLASMA__PARA_SET_POWER, obj_name,var_name);

				var_name = "MON.IO.POWER.SET";
				LINK__EXT_VAR_STRING_CTRL(sEXT_CH__RF_PLASMA__MON_IO_POWER_SET, obj_name,var_name);

				//
				var_name = "RF.STABLE.FLAG";
				LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__RF_PLASMA__STABLE_FLAG, obj_name,var_name);

				var_name = "RF.ABORT.FLAG";
				LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__RF_PLASMA__ABORT_FLAG, obj_name,var_name);
			}
		}
	}

	// MATCHER TOP : PLASMA ...
	{
		def_name = "OBJ__MATCHER_TOP";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, obj_name);
	
		def_check = x_utility.Check__Link(obj_name);
		bActive__OBJ_CTRL__MAT_TOP = def_check;

		if(def_check)
		{
			pOBJ_CTRL__MAT_TOP = p_ext_obj_create->Create__OBJECT_CTRL(obj_name);

			//
			LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__MAT_TOP__OBJ_CTRL, obj_name,STR__CTRL);

			//
			var_name = "dAPP.Matcher.CH1.Mode.SET";
			LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__MAT_TOP__PLASMA_MODE_SET, obj_name,var_name);

			var_name = "aAPP.Matcher.CH1.Load.SET";
			LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__MAT_TOP__PLASMA_LOAD_POS, obj_name,var_name);

			var_name = "aAPP.Matcher.CH1.Tune.SET";
			LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__MAT_TOP__PLASMA_TUNE_POS, obj_name,var_name);
		}
	}

	// OBJ : LIFT_PIN ...
	{
		def_name = "OBJ__LIFT_PIN";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, obj_name);

		def_check = x_utility.Check__Link(obj_name);
		bActive__OBJ_CTRL__LIFT_PIN = def_check;

		if(def_check)
		{
			pOBJ_CTRL__LIFT_PIN = p_ext_obj_create->Create__OBJECT_CTRL(obj_name);

			//
			LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__LIFT_PIN__OBJ_CTRL, obj_name,STR__CTRL);
		}
	}

	// ESC - FNC_OBJ LINK ...
	{
		def_name = "OBJ__ESC_FNC";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, obj_name);

		def_check = x_utility.Check__Link(obj_name);
		bActive__OBJ_CTRL__ESC_SYS = def_check;

		if(def_check)
		{
			pOBJ_CTRL__ESC = p_ext_obj_create->Create__OBJECT_CTRL(obj_name);

			//
			var_name = "MON.STABLE.FLAG";
			LINK__EXT_VAR_STRING_CTRL(sEXT_CH__ESC__MON_STABLE_FLAG, obj_name,var_name);

			var_name = "MON.FAULT.FLAG";
			LINK__EXT_VAR_STRING_CTRL(sEXT_CH__ESC__MON_FAULT_FLAG, obj_name,var_name);

			//
			var_name = "RCP.He_CENTER.PRESSURE_SETPOINT.TORR";
			LINK__EXT_VAR_STRING_CTRL(sEXT_CH__ESC__RCP_He_CENTER_PRESSURE_SETPOINT_TORR, obj_name,var_name);

			var_name = "RCP.He_EDGE.PRESSURE_SETPOINT.TORR";
			LINK__EXT_VAR_STRING_CTRL(sEXT_CH__ESC__RCP_He_EDGE_PRESSURE_SETPOINT_TORR, obj_name,var_name);

			//
			var_name = "RCP.He_CENTER.ZONE.FLOW.MAX.THRESHOLD";
			LINK__EXT_VAR_STRING_CTRL(sEXT_CH__ESC__RCP_He_CENTER_FLOW_MAX_THRESHOLD, obj_name,var_name);

			var_name = "RCP.He_CENTER.ZONE.FLOW.MIN.THRESHOLD";
			LINK__EXT_VAR_STRING_CTRL(sEXT_CH__ESC__RCP_He_CENTER_FLOW_MIN_THRESHOLD, obj_name,var_name);

			var_name = "RCP.He_EDGE.ZONE.FLOW.MAX.THRESHOLD";
			LINK__EXT_VAR_STRING_CTRL(sEXT_CH__ESC__RCP_He_EDGE_FLOW_MAX_THRESHOLD, obj_name,var_name);

			var_name = "RCP.He_EDGE.ZONE.FLOW.MIN.THRESHOLD";
			LINK__EXT_VAR_STRING_CTRL(sEXT_CH__ESC__RCP_He_EDGE_FLOW_MIN_THRESHOLD, obj_name,var_name);
		}
	}

	// LINK : IO CHANNEL ...
	{
		def_name = "LINK_IO.APC.CUR_VLV_POS";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, def_data);
		p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(def_data, obj_name,var_name);
		LINK__EXT_VAR_STRING_CTRL(sEXT_CH__APC_IO__CUR_VLV_POS, obj_name,var_name);
	}

	// ...
	{
		iHEADER_RCP_START = -1;
		iTEMP_STEP_RCP_START = -1;

		iOBJ_BUSY_FLAG = -1;
	}

	// ...
	{
		SCX__SEQ_INFO x_seq_info;

		iActive__SIM_MODE = x_seq_info->Is__SIMULATION_MODE();
	}
	return 1;
}

//-------------------------------------------------------------------------
int CObj__STEP_FNC::__CALL__CONTROL_MODE(mode,p_debug,p_variable,p_alarm)
{
	int flag = -1;

	// ...
	{
		iOBJ_BUSY_FLAG = 1;
	}

	// ...
	{
		CString log_msg;

		log_msg.Format(" * %s : [%s] started ... \n", sObject_Name,mode);
		printf(log_msg);
	}

	// ...
	{
		CString log_msg;
		CString obj_msg;

		obj_msg.Format("Start ... :  [%s]", mode);

		log_msg.Format("\n%s  --------------------------------------------------------------",
					   obj_msg);

		xLOG_CTRL->WRITE__LOG(log_msg);

		//
		sCH__OBJ_MSG->Set__DATA(obj_msg);
		sCH__OBJ_SUB_MSG->Set__DATA("");
	}

	// ...
	{
		IF__CTRL_MODE(sMODE__INIT)
		{
			flag = Call__INIT(p_variable,p_alarm);
		}
		ELSE_IF__CTRL_MODE(sMODE__RCP_DATA_INIT)
		{
			flag = Call__RCP_DATA_INIT(p_variable,p_alarm);
		}
		ELSE_IF__CTRL_MODE(sMODE__READY)
		{
			flag = Call__READY(p_variable,p_alarm);
		}
		ELSE_IF__CTRL_MODE(sMODE__START)
		{
			flag = Call__START(p_variable,p_alarm);

			iSTEP_COUNT = 0;
		}
		ELSE_IF__CTRL_MODE(sMODE__PROC)
		{
			iSTEP_COUNT++;

			flag = Call__PROC(p_variable,p_alarm);
		}
		ELSE_IF__CTRL_MODE(sMODE__PROC_SYSTEN_INIT)
		{
			flag = Call__PROC_SYSTEM_INIT(p_variable,p_alarm);
		}
		ELSE_IF__CTRL_MODE(sMODE__ABORT)
		{
			iHEADER_RCP_START = -1;
			iTEMP_STEP_RCP_START = -1;

			flag = Call__ABORT(p_variable,p_alarm);
		}
		ELSE_IF__CTRL_MODE(sMODE__END)
		{
			iHEADER_RCP_START = -1;
			iTEMP_STEP_RCP_START = -1;

			flag = Call__END(p_variable,p_alarm);
		}
		ELSE_IF__CTRL_MODE(sMODE__STEP_DB_CHECK)
		{
			flag = Call__STEP_DB_CHECK(p_variable,p_alarm);
		}
	}

	// ...
	{
		sCH__EXCEPTION_CONTINUE_REQ->Set__DATA("");
		sCH__EXCEPTION_CONTINUE_STEP_OVER_TIME->Set__DATA("");
	}

	if((flag < 0)||(p_variable->Check__CTRL_ABORT() > 0))
	{
		CString log_msg;
		
		log_msg.Format("Aborted [%d] ... : [%s] -- Ctrl [%1d]", 
				       flag, 
					   mode,
					   p_variable->Check__CTRL_ABORT());

		xLOG_CTRL->WRITE__LOG(log_msg);	
		sCH__OBJ_MSG->Set__DATA(log_msg);

		//
		log_msg.Format(" * %s : [%s] aborted (%1d) ... \n", sObject_Name,mode,flag);
		printf(log_msg);
	}
	else
	{
		CString log_msg;
		
		log_msg.Format("Completed [%d] ... :  [%s]", flag, mode);

		xLOG_CTRL->WRITE__LOG(log_msg);
		sCH__OBJ_MSG->Set__DATA(log_msg);

		//
		log_msg.Format(" * %s : [%s] completed ... \n", sObject_Name,mode);
		printf(log_msg);
	}

	iOBJ_BUSY_FLAG = -1;
	return flag;
}

int CObj__STEP_FNC::__CALL__MONITORING(id,p_variable,p_alarm)
{
	if(id == _FNC_MON_ID__RCP_MATCHER_TOP__CTRL_REQ)
	{
		_Fnc_Mon__RCP_Matcher_Top__Ctrl_Req(p_variable,p_alarm);
		return 1;
	}
	
	if(id == MON_ID__WAFER_COUNT_CTRL)
	{
		Mon__Wafer_Count_Ctrl(id, p_variable,p_alarm);
		return 1;
	}

	return 1;
}
