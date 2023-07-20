#include "StdAfx.h"
#include "CObj__DB_INF.h"


//-------------------------------------------------------------------------
CObj__DB_INF::CObj__DB_INF()
{

}
CObj__DB_INF::~CObj__DB_INF()
{

}

//-------------------------------------------------------------------------
int CObj__DB_INF::__DEFINE__CONTROL_MODE(obj,l_mode)
{
	sObject_Name = obj;

	// ...
	{
		ADD__CTRL_VAR(sMODE__POST_ALARM_LIST,    "POST_ALARM.LIST");
		ADD__CTRL_VAR(sMODE__POST_ALARM_CLEAR,   "POST_ALARM.CLEAR");
		ADD__CTRL_VAR(sMODE__POST_ALARM_DB_SIZE, "POST_ALARM.DB_SIZE");
	}
	return 1;
}
int CObj__DB_INF::__DEFINE__VERSION_HISTORY(version)
{

	return 1;
}


// ...
#define  DSP__TRANS_MODE		"ATM  VAC"
#define  DSP__PRC_STS			"IDLE  PROCESSING"
#define  DSP__SV_STS            "UNKNOWN  OPEN  CLOSE"
#define  DSP__SLOT_NO           "1  2  3"

// ...
#define MON_ID__UPDATE_INFO					1


int CObj__DB_INF::__DEFINE__VARIABLE_STD(p_variable)
{
	DECLARE__STD_VARIABLE;

	CCommon_Error__DEF_VARIABLE m_err_def_variable;
	p_variable->Link__DEF_VARIABLE__ERROR_FEEDBACK(&m_err_def_variable);

	// ...
	CString str_name;
	CString dsp_list;
	int i;


	// ...
	{
		str_name = "ACTIVE.CALL_BY_CTC";
		STD__ADD_DIGITAL_WITH_COMMENT(str_name, "OFF ON", "");
		LINK__VAR_DIGITAL_CTRL(dCH__ACTIVE_CALL_BY_CTC, str_name);
	}

	//  PMC -> CTC
	{
		str_name = "CHM.PRC.STS";
		STD__ADD_DIGITAL_WITH_COMMENT(str_name,DSP__PRC_STS,"");
		LINK__VAR_DIGITAL_CTRL(dCH__CHM_PRC_STS, str_name);

		str_name = "CHM.PRC.TOTAL.TIME.TO.CTC";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__CHM_PRC_TOTAL_TIME_TO_CTC, str_name);

		str_name = "CHM.PRC.CHANGE.TIME.TO.CTC";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__CHM_PRC_CHANGE_TIME_TO_CTC, str_name);

		//
		str_name = "CHM.PRESSURE.STATUS";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__CHM_PRESSURE_STATUS, str_name);

		str_name = "CHM.VAC.SNS";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(xCH__CHM_VAC_SNS, str_name);

		str_name = "CHM.ATM.SNS";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(xCH__CHM_ATM_SNS, str_name);

		//
		str_name = "PMC.PROCESS.STATUS";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__PMC_PROCESS_STATUS, str_name);

		//
		str_name = "PMC.SLOT.STATUS";
		STD__ADD_STRING(str_name);

		str_name = "SHUTTER.STATUS";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(xCH__SHUTTER_STATUS, str_name);

		str_name = "LIFT_PIN.STATUS";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(xCH__LIFT_PIN_STATUS, str_name);

		str_name = "RF.ON.STS";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(xCH__RF_ON_STS, str_name);

		//
		str_name = "MFC.TOTAL.FLOW_SET";
		STD__ADD_STRING(str_name);

		str_name = "MFC.TOTAL.FLOW_READ";
		STD__ADD_STRING(str_name);

		//
		str_name = "CHM.STATE.REPORT_TO_CTC";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(xCH__CHM_STAGE_REPORT_TO_CTC, str_name);

		//
		str_name = "CHM.PRESSURE.VALUE";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__CHM_PRESSURE_VALUE, str_name);

		str_name = "CHM.PRESSURE.mTORR";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__CHM_PRESSURE_mTORR, str_name);

		//
		str_name = "PMP.PRESSURE.VALUE";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__PMP_PRESSURE_VALUE, str_name);

		str_name = "PMP.PRESSURE.STATE";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__PMP_PRESSURE_STATE, str_name);

		str_name = "PMP.VAC.SNS";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__PMP_VAC_SNS, str_name);

		//
		str_name = "CFG.DECHUCK.CTRL.MODE";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name, "CONFIG", "");
		LINK__VAR_DIGITAL_CTRL(dCH__CFG_DECHUCK_CTRL_MODE, str_name);

		str_name = "CFG.DECHUCK.RECIPE.ABORT";
		STD__ADD_STRING_WITH_X_OPTION(str_name, "");
		LINK__VAR_STRING_CTRL(sCH__CFG_DECHUCK_RECIPE_ABORT, str_name);

		for(i=0; i<DEF_SIZE__DECHUCK_PROCESS; i++)
		{
			int id = i + 1;

			str_name.Format("CFG.DECHUCK.RECIPE.USE.%1d", id);
			STD__ADD_DIGITAL_WITH_X_OPTION(str_name, "NO YES", "NO");
			LINK__VAR_DIGITAL_CTRL(dCH__CFG_DECHUCK_RECIPE_USE_X[i], str_name);

			str_name.Format("CFG.DECHUCK.RECIPE.PROCESS.%1d", id);
			STD__ADD_STRING_WITH_X_OPTION(str_name, "");
			LINK__VAR_STRING_CTRL(sCH__CFG_DECHUCK_RECIPE_PROCESS_X[i], str_name);

			str_name.Format("CFG.DECHUCK.RECIPE.COMMENT.%1d", id);
			STD__ADD_STRING_WITH_X_OPTION(str_name, "");
			LINK__VAR_STRING_CTRL(sCH__CFG_DECHUCK_RECIPE_COMMENT_X[i], str_name);
		}

		//
		str_name = "CR.POS.STATUS";
		STD__ADD_STRING(str_name);
	}

	//  PMC <-> CTC
	{
		str_name = "TOTAL.PRC_TIME";
		STD__ADD_STRING_WITH_COMMENT(str_name,"");
		LINK__VAR_STRING_CTRL(xCH__TOTAL_PRC_TIME,str_name);

		str_name = "CHANGE.PRC_TIME";
		STD__ADD_STRING_WITH_COMMENT(str_name,"");
		LINK__VAR_STRING_CTRL(xCH__CHANGE_PRC_TIME,str_name);
	}

	//  PMC <- CTC
	{
		str_name = "CFG.TRANSFER.MODE";
		STD__ADD_DIGITAL_WITH_COMMENT(str_name,DSP__TRANS_MODE,"");
		LINK__VAR_DIGITAL_CTRL(xCH__CFG_TRANSFER_MODE,str_name);

		str_name = "CFG.REF.ATM.PRESSURE";
		STD__ADD_STRING_WITH_COMMENT(str_name,"");
		LINK__VAR_STRING_CTRL(xCH__CFG_REF_ATM_PRESSURE,str_name);

		str_name = "CFG.REF.VAC.PRESSURE";
		STD__ADD_STRING_WITH_COMMENT(str_name,"");
		LINK__VAR_STRING_CTRL(xCH__CFG_REF_VAC_PRESSURE,str_name);

		//
		str_name = "MODULE.TIME";
		STD__ADD_STRING_WITH_COMMENT(str_name,"");
		LINK__VAR_STRING_CTRL(xCH__MODULE_TIME,str_name);

		str_name = "SLIT.VLV.STS";
		STD__ADD_DIGITAL_WITH_COMMENT(str_name,DSP__SV_STS,"");
		LINK__VAR_DIGITAL_CTRL(xCH__SLIT_VLV_STS,str_name);

		str_name = "SLOT.NO";
		STD__ADD_DIGITAL_WITH_COMMENT(str_name,DSP__SLOT_NO,"");
		LINK__VAR_DIGITAL_CTRL(xCH__SLOT_NO,str_name);

		// MATERIAL INFO .....
		{
			str_name = "SLOT01.RECIPE";
			STD__ADD_STRING_WITH_COMMENT(str_name,"");
			LINK__VAR_STRING_CTRL(xCH__RECIPE,str_name);

			str_name = "SLOT01.RECIPE.WITHOUT.FOLDERNAME";
			STD__ADD_STRING_WITH_COMMENT(str_name,"");
			LINK__VAR_STRING_CTRL(xCH__RECIPE_WITHOUT_FOLDER_NAME,str_name);

			str_name = "SLOT01.LOTID";
			STD__ADD_STRING_WITH_COMMENT(str_name,"");
			LINK__VAR_STRING_CTRL(xCH__LOTID,str_name);

			str_name = "SLOT01.MATERIALID";
			STD__ADD_STRING_WITH_COMMENT(str_name,"");
			LINK__VAR_STRING_CTRL(xCH__MATERIALID,str_name);

			//
			p_variable->Get__STD_DESCRIPTION(DSP__SLOT_STATUS,dsp_list);

			str_name = "SLOT01.STATUS";
			STD__ADD_DIGITAL_WITH_COMMENT(str_name,dsp_list,"");
			LINK__VAR_DIGITAL_CTRL(xCH__SLOT01_STATUS,str_name);

			str_name = "SLOT01.TITLE";
			STD__ADD_STRING_WITH_COMMENT(str_name,"");
			LINK__VAR_STRING_CTRL(xCH__SLOT01_TITLE,str_name);

			//
			str_name = "SLOT01.PORTID";
			STD__ADD_STRING_WITH_COMMENT(str_name,"");
			LINK__VAR_STRING_CTRL(xCH__SLOT01_PORTID,str_name);

			str_name = "SLOT01.SLOTID";
			STD__ADD_STRING_WITH_COMMENT(str_name,"");
			LINK__VAR_STRING_CTRL(xCH__SLOT01_SLOTID,str_name);

			//
			str_name = "PMC.PROC_READY.FLAG";
			STD__ADD_STRING_WITH_COMMENT(str_name,"");
			LINK__VAR_STRING_CTRL(xCH__PMC_PROC_READY_FLAG,str_name);
		}
	}

	// PMC <-- TMC ...
	{
		str_name = "TMC.LINK_TEST.FLAG";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(xCH__TMC_LINK_TEST_FLAG, str_name);

		//
		str_name = "TMC.ROBOT.ARM.STATE";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__TMC_ROBOT_ARM_STATE, str_name);

		str_name = "TMC.PRESSURE.STATE";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__TMC_PRESSURE_STATE, str_name);

		//
		str_name = "TMC_LINK.DA_REPORT.RESULT.WAFER";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__TMC_LINK_DA_REPORT_RESULT_WAFER, str_name);

		str_name = "TMC_LINK.DA_REPORT.R_OFFSET.WAFER";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__TMC_LINK_DA_REPORT_R_OFFSET_WAFER, str_name);

		str_name = "TMC_LINK.DA_REPORT.T_OFFSET.WAFER";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__TMC_LINK_DA_REPORT_T_OFFSET_WAFER, str_name);
	}

	// ...
	{
		p_variable->Add__MONITORING_PROC(1.0, MON_ID__UPDATE_INFO);
	}
	return 1;
}
int CObj__DB_INF::__DEFINE__ALARM(p_alarm)
{

	return 1;
}

//-------------------------------------------------------------------------
int CObj__DB_INF::__INITIALIZE__OBJECT(p_variable,p_ext_obj_create)
{	
	sCH__PMC_PROCESS_STATUS->Set__DATA("IDLE");

	return 1;
}

//-------------------------------------------------------------------------
int CObj__DB_INF::__CALL__CONTROL_MODE(mode,p_debug,p_variable,p_alarm)
{
	int flag = -1;

		 IF__CTRL_MODE(sMODE__POST_ALARM_LIST)			flag = Call__POST_ALARM_LIST(p_variable, p_alarm);
	ELSE_IF__CTRL_MODE(sMODE__POST_ALARM_CLEAR)			flag = Call__POST_ALARM_CLEAR(p_variable, p_alarm);
	ELSE_IF__CTRL_MODE(sMODE__POST_ALARM_DB_SIZE)		flag = Call__POST_ALARM_DB_SIZE(p_variable, p_alarm);

	return flag;
}

int CObj__DB_INF::__CALL__MONITORING(id,p_variable,p_alarm)
{
	switch(id)
	{
		case MON_ID__UPDATE_INFO:
			Mon__UPDATE_INFO(p_variable);
			return 1;
	}

	return 1;
}
