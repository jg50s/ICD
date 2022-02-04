#include "StdAfx.h"
#include "CObj__RF_IO.h"
#include "CObj__RF_IO__ALID.h"


//-------------------------------------------------------------------------
CObj__RF_IO::CObj__RF_IO()
{

}
CObj__RF_IO::~CObj__RF_IO()
{

}

//-------------------------------------------------------------------------
int CObj__RF_IO::__DEFINE__CONTROL_MODE(obj,l_mode)
{
	sObject_Name = obj;

	// ...
	{
		ADD__CTRL_VAR(sMODE__INIT,      "INIT");

		ADD__CTRL_VAR(sMODE__OFF,       "OFF");
		ADD__CTRL_VAR(sMODE__SET_POWER, "SET_POWER");
	}
	return 1;
}
int CObj__RF_IO::__DEFINE__VERSION_HISTORY(version)
{

	return 1;
}


// ...
#define MON_ID__STATUS							1


int CObj__RF_IO::__DEFINE__VARIABLE_STD(p_variable)
{
	DECLARE__STD_VARIABLE;

	CCommon_Error__DEF_VARIABLE m_err_def_variable;
	p_variable->Link__DEF_VARIABLE__ERROR_FEEDBACK(&m_err_def_variable);

	// ...
	CString str_name;
	CString item_list;

	// ...
	{
		str_name = "APP.OBJ.MSG";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__OBJ_MSG, str_name);

		str_name = "APP.OBJ.STATUS";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__OBJ_STATUS, str_name);

		//
		str_name = "APP.OBJ.ONLINE";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__OBJ_ONLINE, str_name);

		str_name = "APP.OBJ.CTRL.MODE";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__OBJ_CTRL_MODE, str_name);
	}

	// ...
	{
		str_name = "PARA.POWER.SET";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "W", 0, 0.0, 1250, "");
		LINK__VAR_ANALOG_CTRL(aCH__PARA_POWER_SET, str_name);
	}

	// ...
	{
		str_name = "MON.POWER.ON.SET";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_POWER_ON_SET, str_name);
		
		str_name = "MON.POWER.ON.SNS";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_POWER_ON_SNS, str_name);
		
		str_name = "MON.OVERTEMP.SNS";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_OVERTEMP_SNS, str_name);

		//
		str_name = "MON.POWER.SET";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_POWER_SET, str_name);

		str_name = "MON.FORWARD.POWER";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_FORWARD_POWER, str_name);
		
		str_name = "MON.REFLECT.POWER";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_REFLECT_POWER, str_name);
	}

	// ...
	{
		p_variable->Add__MONITORING_PROC(1.0, MON_ID__STATUS);
	}
	return 1;
}

int CObj__RF_IO::__DEFINE__ALARM(p_alarm)
{
	DECLARE__ALARM;

	/*
	// ...
	CString title;
	title.Format("%s : ", sObject_Name);

	CString alarm_title;
	CString alarm_msg;
	CStringArray l_act;
	int alarm_id;

	// ...
	{
		alarm_id = ALID__LIFT_PIN_UP_TIMEOUT;

		alarm_title  = title;
		alarm_title += "Lift_Pin Up-Timeout !";

		alarm_msg  = "Lift_Pin이 Up되지 않았습니다.\n";
		alarm_msg += "Lift_Pin 관련 Sensor를 확인 바랍니다.\n";

		l_act.RemoveAll();
		l_act.Add(STR__ABORT);
		l_act.Add(STR__RETRY);

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}
	*/

	return 1;
}

//-------------------------------------------------------------------------
int CObj__RF_IO::__INITIALIZE__OBJECT(p_variable,p_ext_obj_create)
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
		def_name = "CH__DO_SOURCE_ON";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
		p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
		LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__DO_SOURCE_ON, obj_name,var_name);

		def_name = "CH__AO_SOURCE_POWER";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
		p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
		LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__AO_SOURCE_POWER, obj_name,var_name);

		//
		def_name = "CH__DI_SOURCE_ON";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
		p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
		LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__DI_SOURCE_ON, obj_name,var_name);

		def_name = "CH__DI_SOURCE_OVERTEMP_ALARM";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
		p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
		LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__DI_SOURCE_OVERTEMP_ALARM, obj_name,var_name);

		//
		def_name = "CH__AI_FORWARD_POWER";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
		p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
		LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__AI_FORWARD_POWER, obj_name,var_name);

		def_name = "CH__AI_REFLECT_POWER";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
		p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
		LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__AI_REFLECT_POWER, obj_name,var_name);
	}

	// ...
	{
		sCH__OBJ_ONLINE->Set__DATA("Online");
		sCH__OBJ_CTRL_MODE->Set__DATA("Remote");
	}

	// ...
	{
		SCX__SEQ_INFO seq_info;

		if(seq_info->Is__SIMULATION_MODE() > 0)			iSIM_MODE =  1;
		else											iSIM_MODE = -1;
	}
	return 1;
}

//-------------------------------------------------------------------------
int CObj__RF_IO::__CALL__CONTROL_MODE(mode,p_debug,p_variable,p_alarm)
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
			 IF__CTRL_MODE(sMODE__INIT)			flag = Call__INIT(p_variable, p_alarm);

		ELSE_IF__CTRL_MODE(sMODE__OFF)			flag = Call__OFF(p_variable, p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__SET_POWER)	flag = Call__SET_POWER(p_variable, p_alarm);
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

int CObj__RF_IO::__CALL__MONITORING(id,p_variable,p_alarm)
{
	if(id == MON_ID__STATUS)		Mon__STATUS(p_variable, p_alarm);

	return 1;
}
