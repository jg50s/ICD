#include "StdAfx.h"
#include "CObj__TwoManiFold_TM.h"
#include "CObj__TwoManiFold_TM__ALID.h"


//-------------------------------------------------------------------------
CObj__TwoManiFold_TM::CObj__TwoManiFold_TM()
{

}
CObj__TwoManiFold_TM::~CObj__TwoManiFold_TM()
{

}

//-------------------------------------------------------------------------
int CObj__TwoManiFold_TM::__DEFINE__CONTROL_MODE(obj,l_mode)
{
	sObject_Name = obj;

	// ...
	{
		ADD__CTRL_VAR(sMODE__ALL_PUMP_VLV_CLOSE,     "ALL_PUMP_VLV_CLOSE");

		ADD__CTRL_VAR(sMODE__TMC_CHM_PUMP_VLV_OPEN,  "TMC_CHM_PUMP_VLV_OPEN");

		ADD__CTRL_VAR(sMODE__TMC_CHM_VAC_VLV_OPEN,   "TMC_CHM_VAC_VLV_OPEN" );
		ADD__CTRL_VAR(sMODE__TMC_CHM_VAC_VLV_CLOSE,  "TMC_CHM_VAC_VLV_CLOSE");

		ADD__CTRL_VAR(sMODE__TMC_CHM__VLV_ALL_CLOSE, "TMC_CHM_VLV_ALL_CLOSE");
	}
	return 1;
}
int CObj__TwoManiFold_TM::__DEFINE__VERSION_HISTORY(version)
{

	return 1;
}

int CObj__TwoManiFold_TM::__DEFINE__VARIABLE_STD(p_variable)
{
	DECLARE__STD_VARIABLE;

	CCommon_Error__DEF_VARIABLE m_err_def_variable;
	p_variable->Link__DEF_VARIABLE__ERROR_FEEDBACK(&m_err_def_variable);

	// ...
	CString str_name;

	// ...
	{
		str_name = "OTR.IN.CFG.aPUMP.VALVE.CLOSE.TIMEOUT";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name,"sec",3, 0.3,2.0,"");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_PUMP_VALVE_CLOSE_TIMEOUT, str_name);

		str_name = "OTR.IN.CFG.aVENT.VALVE.CLOSE.TIMEOUT";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name,"sec",3, 0.3,2.0,"");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_VENT_VALVE_CLOSE_TIMEOUT, str_name);
	}

	return 1;
}
int CObj__TwoManiFold_TM::__DEFINE__ALARM(p_alarm)
{
	DECLARE__ALARM;

	return 1;
}

//-------------------------------------------------------------------------
int CObj__TwoManiFold_TM::__INITIALIZE__OBJECT(p_variable,p_ext_obj_create)
{
	CString def_name;
	CString def_data;
	CString str_name;
	CString obj_name, var_name;

	// ...
	{
		CString file_name;
		CString log_msg;

		file_name.Format("%s_App.log", sObject_Name);

		log_msg  = "\n\n";
		log_msg += "//------------------------------------------------------------------------";

		xLOG_CTRL->CREATE__SUB_DIRECTORY(sObject_Name);
		xLOG_CTRL->SET__PROPERTY(file_name,24*5,60);

		xLOG_CTRL->DISABLE__TIME_LOG();
		xLOG_CTRL->WRITE__LOG(log_msg);

		xLOG_CTRL->ENABLE__TIME_LOG();
		xLOG_CTRL->WRITE__LOG("   START   \n");
	}

	// I/O OBJECT
	{
		// TMC_CHM -----
		{
			// PUMP VLV
			def_name = "VAR__IO_DO_TM_FAST_PUMP_VLV";
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name,def_data);
			p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(def_data, obj_name, var_name);
			LINK__EXT_VAR_DIGITAL_CTRL(doEXT_CH__TMC_CHM__FAST_PUMP_VLV__SET, obj_name, var_name);

			// VENT VLV
			def_name = "VAR__IO_DO_TM_FAST_VENT_VLV";
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name,def_data);
			p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(def_data, obj_name, var_name);
			LINK__EXT_VAR_DIGITAL_CTRL(doEXT_CH__TMC_CHM__FAST_VENT_VLV__SET, obj_name, var_name);
		}
	}
	return 1;
}

//-------------------------------------------------------------------------
int CObj__TwoManiFold_TM::__CALL__CONTROL_MODE(mode,p_debug,p_variable,p_alarm)
{
	DECLARE__EXT_CTRL(p_variable);

	// ...
	{
		CString log_msg;

		log_msg.Format("Start  [%s] ... Called By %s", mode,p_ext_mode_ctrl->Get__UPPER_OBJECT_NAME());
		xLOG_CTRL->WRITE__LOG(log_msg);
	}

	int flag = -1;

	// ...
	{
		IF__CTRL_MODE(sMODE__ALL_PUMP_VLV_CLOSE)
		{
			flag = Call__ALL_PUMP_VLV_CLOSE(p_variable,p_alarm);
		}

		ELSE_IF__CTRL_MODE(sMODE__TMC_CHM_PUMP_VLV_OPEN)
		{
			flag = Call__TMC_CHM_PUMP_VLV_OPEN(p_variable,p_alarm);
		}
		ELSE_IF__CTRL_MODE(sMODE__TMC_CHM_VAC_VLV_OPEN)
		{
			flag = Call__TMC_CHM_VLV_OPEN(p_variable,p_alarm);
		}
		ELSE_IF__CTRL_MODE(sMODE__TMC_CHM_VAC_VLV_CLOSE)
		{
			flag = Call__TMC_CHM_VLV_CLOSE(p_variable,p_alarm);
		}

		ELSE_IF__CTRL_MODE(sMODE__TMC_CHM__VLV_ALL_CLOSE)
		{
			flag = Call__TMC_CHM_VLV_ALL_CLOSE(p_variable,p_alarm);
		}
	}

	if((flag < 0)||(p_variable->Check__CTRL_ABORT() > 0))
	{
		CString log_msg;

		log_msg.Format("Aborted ... :  [%s]",mode);
		xLOG_CTRL->WRITE__LOG(log_msg);
	}
	else
	{
		CString log_msg;

		log_msg.Format("Completed ... :  [%s]",mode);
		xLOG_CTRL->WRITE__LOG(log_msg);
	}

	return flag;
}

int CObj__TwoManiFold_TM::__CALL__MONITORING(id,p_variable,p_alarm)
{

	return 1;
}
