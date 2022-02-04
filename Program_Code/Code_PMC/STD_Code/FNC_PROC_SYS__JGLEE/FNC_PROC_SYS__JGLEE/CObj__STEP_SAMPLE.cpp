#include "StdAfx.h"
#include "CObj__STEP_SAMPLE.h"

#include "CCommon_Utility.h"


//-------------------------------------------------------------------------
CObj__STEP_SAMPLE::CObj__STEP_SAMPLE()
{

}
CObj__STEP_SAMPLE::~CObj__STEP_SAMPLE()
{

}

//-------------------------------------------------------------------------
int CObj__STEP_SAMPLE::__DEFINE__CONTROL_MODE(obj,l_mode)
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
int CObj__STEP_SAMPLE::__DEFINE__VERSION_HISTORY(version)
{

	return 1;
}


// ...
#define  APP_DSP__DISABLE_ENABLE					\
"DISABLE ENABLE"

#define  APP_DSP__ENABLE_DISABLE					\
"ENABLE DISABLE"


int CObj__STEP_SAMPLE::__DEFINE__VARIABLE_STD(p_variable)
{
	DECLARE__STD_VARIABLE;

	// ...
	CCommon_Error__DEF_VARIABLE m_err_def_variable;
	p_variable->Link__DEF_VARIABLE__ERROR_FEEDBACK(&m_err_def_variable);

	// ...
	CString var_name;

	// OBJ ...
	{
		var_name = "OBJ.MSG";
		STD__ADD_STRING(var_name);
		LINK__VAR_STRING_CTRL(sCH__OBJ_MSG, var_name);

		var_name = "OBJ.SUB.MSG";
		STD__ADD_STRING(var_name);
		LINK__VAR_STRING_CTRL(sCH__OBJ_SUB_MSG, var_name);
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

		var_name = "CFG.CHM.PRESSURE.HIGH.LIMIT";
		STD__ADD_ANALOG_WITH_X_OPTION(var_name, "torr", 0, 1, 900, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_CHM_PRESSURE_HIGH_LIMIT, var_name);
	}

	// RCP ...
	{
		// STEP ...
		{
			var_name = "RCP.STEP.MESSAGE";
			STD__ADD_STRING_WITH_OPTION(var_name, 0, "E", "");
			LINK__VAR_STRING_CTRL(sCH__RCP_STEP_MESSAGE, var_name);

			var_name = "RCP.STEP.MODE";
			STD__ADD_DIGITAL_WITH_OPTION(var_name, "Time Stable End", -1, "E", "");
			LINK__VAR_DIGITAL_CTRL(dCH__RCP_STEP_MODE, var_name);

			var_name = "RCP.STEP.TIME";
			STD__ADD_ANALOG_WITH_OPTION(var_name, "sec", 1, 0, 9999, -1, "E", "");
			LINK__VAR_ANALOG_CTRL(aCH__RCP_STEP_TIME, var_name);
		}

		// APC ...
		{
			var_name = "RCP.APC.MODE";		
			STD__ADD_DIGITAL_WITH_OPTION(var_name, "POSITION PRESSURE", -1, "E", "");
			LINK__VAR_DIGITAL_CTRL(dCH__RCP_APC_MODE, var_name);

			var_name = "RCP.APC.POSITION";		
			STD__ADD_ANALOG_WITH_OPTION(var_name, "%", 1, 0.0, 100.0, -1, "E", "");
			LINK__VAR_ANALOG_CTRL(aCH__RCP_APC_POSITION, var_name);

			var_name = "RCP.APC.PRESSURE";		
			STD__ADD_ANALOG_WITH_OPTION(var_name, "torr", 3, 0.0, 10.0, -1, "E", "");
			LINK__VAR_ANALOG_CTRL(aCH__RCP_APC_PRESSURE, var_name);
		}
	}

	return 1;
}

int CObj__STEP_SAMPLE::__DEFINE__ALARM(p_alarm)
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

	return 1;
}

int CObj__STEP_SAMPLE::__Define__USER_FUNCTION(CII_DEFINE__FUNCTION *p_fnc_ctrl)
{
	p_fnc_ctrl->Link__ERROR_FEEDBACK(&mERROR__USER_FNC);

	return 1;
}

//-------------------------------------------------------------------------
int CObj__STEP_SAMPLE::__INITIALIZE__OBJECT(p_variable,p_ext_obj_create)
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
		LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__SLOT01_STATUS, obj_name,"SLOT01.STATUS");
		LINK__EXT_VAR_STRING_CTRL(sEXT_CH__CUR_LOTID,      obj_name,"SLOT01.LOTID");
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

			//
			var_name = "MON.PRESSURE.TORR";
			LINK__EXT_VAR_STRING_CTRL(sEXT_CH__APC_OBJ__MON_PRESSURE_TORR, obj_name,var_name);

			//
			var_name = "MON.PRESSURE.ABORT.ACTIVE";
			LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__APC_OBJ__MON_PRESSURE_ABORT_ACTIVE, obj_name,var_name);

			var_name = "MON.PRESSURE.STABLE.ACTIVE";
			LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__APC_OBJ__MON_PRESSURE_STABLE_ACTIVE, obj_name,var_name);
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
int CObj__STEP_SAMPLE::__CALL__CONTROL_MODE(mode,p_debug,p_variable,p_alarm)
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

int CObj__STEP_SAMPLE::__CALL__MONITORING(id,p_variable,p_alarm)
{

	return 1;
}
