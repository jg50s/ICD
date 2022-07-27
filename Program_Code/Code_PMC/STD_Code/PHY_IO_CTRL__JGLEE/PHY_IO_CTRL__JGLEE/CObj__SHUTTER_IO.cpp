#include "StdAfx.h"
#include "CObj__SHUTTER_IO.h"
#include "CObj__SHUTTER_IO__ALID.h"


//-------------------------------------------------------------------------
CObj__SHUTTER_IO::CObj__SHUTTER_IO()
{

}
CObj__SHUTTER_IO::~CObj__SHUTTER_IO()
{

}

//-------------------------------------------------------------------------
int CObj__SHUTTER_IO::__DEFINE__CONTROL_MODE(obj,l_mode)
{
	sObject_Name = obj;

	// ...
	{
		ADD__CTRL_VAR(sMODE__INIT, "INIT");

		ADD__CTRL_VAR(sMODE__SHUTTER_CLOSE, "SHUTTER.CLOSE");
		ADD__CTRL_VAR(sMODE__SHUTTER_OPEN,  "SHUTTER.OPEN");
	}
	return 1;
}
int CObj__SHUTTER_IO::__DEFINE__VERSION_HISTORY(version)
{

	return 1;
}


// ...
#define MON_ID__STATUS							1


int CObj__SHUTTER_IO::__DEFINE__VARIABLE_STD(p_variable)
{
	DECLARE__STD_VARIABLE;

	CCommon_Error__DEF_VARIABLE m_err_def_variable;
	p_variable->Link__DEF_VARIABLE__ERROR_FEEDBACK(&m_err_def_variable);

	// ...
	CString str_name;
	CString item_list;

	// OBJ ...
	{
		str_name = "OBJ.MSG";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__OBJ_MSG, str_name);

		str_name = "OBJ.STATUS";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__OBJ_STATUS, str_name);
	}

	// CFG ...
	{
		str_name = "CFG.OPEN.TIMEOUT";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "sec", 0, 3.0, 10.0, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_OPEN_TIMEOUT, str_name);

		str_name = "CFG.CLOSE.TIMEOUT";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "sec", 0, 3.0, 10.0, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_CLOSE_TIMEOUT, str_name);
	}

	// MON.PART ... 
	{
		str_name = "MON.PART.ERROR.ACTIVE";
		STD__ADD_DIGITAL(str_name, "OFF ON");
		LINK__VAR_DIGITAL_CTRL(dCH__MON_PART_ERROR_ACTIVE, str_name);
	}

	// MON ...
	{
		str_name = "MON.ACT.TIME_COUNT";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_ACT_TIME_COUNT, str_name);
	}

	// ...
	{
		SCX__SEQ_INFO seq_info;

		iActive__SIM_MODE = seq_info->Is__SIMULATION_MODE();
	}

	// ...
	{
		p_variable->Add__MONITORING_PROC(1.0, MON_ID__STATUS);
	}
	return 1;
}

int CObj__SHUTTER_IO::__DEFINE__ALARM(p_alarm)
{
	DECLARE__ALARM;

	// ...
	CString title;
	title.Format("%s : ", sObject_Name);

	CString alarm_title;
	CString alarm_msg;
	CStringArray l_act;
	int alarm_id;

	// ...
	{
		alarm_id = ALID__SHUTTER_OPEN_TIMEOUT;
		iLIST_ALID__PIN.Add(alarm_id);

		alarm_title  = title;
		alarm_title += "Shutter Open-Timeout !";

		alarm_msg  = "Shutter가 Open되지 않았습니다.\n";
		alarm_msg += "Shutter 관련 Sensor를 확인 바랍니다.\n";

		l_act.RemoveAll();
		l_act.Add(STR__ABORT);
		l_act.Add(STR__RETRY);

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	// ...
	{
		alarm_id = ALID__SHUTTER_CLOSE_TIMEOUT;
		iLIST_ALID__PIN.Add(alarm_id);

		alarm_title  = title;
		alarm_title += "Shutter Close-Timeout !";

		alarm_msg  = "Shutter가 Close되지 않았습니다.\n";
		alarm_msg += "Shutter 관련 Sensor를 확인 바랍니다.\n";

		l_act.RemoveAll();
		l_act.Add(STR__ABORT);
		l_act.Add(STR__RETRY);

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	return 1;
}

//-------------------------------------------------------------------------
int CObj__SHUTTER_IO::__INITIALIZE__OBJECT(p_variable,p_ext_obj_create)
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
	CString ch_name;
	CString obj_name;
	CString var_name;

	// LINK : IO_Chammel
	{
		def_name = "CH__SHUTTER_STATE";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
		p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
		LINK__EXT_VAR_STRING_CTRL(sEXT_CH__SHUTTER_STATE, obj_name,var_name);

		//
		def_name = "CH__DO_SHUTTER_CLOSE";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
		p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
		LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__DO_SHUTTER_CLOSE, obj_name,var_name);

		def_name = "CH__DO_SHUTTER_OPEN";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
		p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
		LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__DO_SHUTTER_OPEN, obj_name,var_name);

		//
		def_name = "CH__DI_SHUTTER_CLOSE";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
		p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
		LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__DI_SHUTTER_CLOSE, obj_name,var_name);

		def_name = "CH__DI_SHUTTER_OPEN";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
		p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
		LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__DI_SHUTTER_OPEN, obj_name,var_name);
	}
	return 1;
}

//-------------------------------------------------------------------------
int CObj__SHUTTER_IO::__CALL__CONTROL_MODE(mode,p_debug,p_variable,p_alarm)
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
			 IF__CTRL_MODE(sMODE__INIT)				flag = Call__INIT(p_variable, p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__SHUTTER_CLOSE)	flag = Call__SHUTTER_CLOSE(p_variable, p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__SHUTTER_OPEN)		flag = Call__SHUTTER_OPEN(p_variable, p_alarm);
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

int CObj__SHUTTER_IO::__CALL__MONITORING(id,p_variable,p_alarm)
{
	if(id == MON_ID__STATUS)		Mon__STATUS(p_variable, p_alarm);

	return 1;
}
