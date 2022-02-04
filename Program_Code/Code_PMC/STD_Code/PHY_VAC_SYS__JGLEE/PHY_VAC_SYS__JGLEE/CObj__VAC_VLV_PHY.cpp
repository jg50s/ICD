#include "StdAfx.h"
#include "CObj__VAC_VLV_PHY.h"
#include "CObj__VAC_VLV_PHY__ALID.h"

#include "CCommon_Utility.h"


//-------------------------------------------------------------------------
CObj__VAC_VLV_PHY::CObj__VAC_VLV_PHY()
{

}
CObj__VAC_VLV_PHY::~CObj__VAC_VLV_PHY()
{

}

//-------------------------------------------------------------------------
int CObj__VAC_VLV_PHY::__DEFINE__CONTROL_MODE(obj,l_mode)
{
	sObject_Name = obj;

	// ...
	{
		ADD__CTRL_VAR(sMODE__ALL_CLOSE,		"ALL_CLOSE");

		ADD__CTRL_VAR(sMODE__SR_OPEN,		"SR_OPEN");
		ADD__CTRL_VAR(sMODE__SR_CLOSE,		"SR_CLOSE");

		ADD__CTRL_VAR(sMODE__FR_OPEN,		"FR_OPEN");
		ADD__CTRL_VAR(sMODE__FR_CLOSE,		"FR_CLOSE");

		ADD__CTRL_VAR(sMODE__EXHAUST_OPEN,	"EXHAUST_OPEN");
		ADD__CTRL_VAR(sMODE__EXHAUST_CLOSE,	"EXHAUST_CLOSE");
	}
	return 1;
}
int CObj__VAC_VLV_PHY::__DEFINE__VERSION_HISTORY(version)
{
	return 1;
}


// ...
#define MON_ID__STATUS						1


int CObj__VAC_VLV_PHY::__DEFINE__VARIABLE_STD(p_variable)
{
	DECLARE__STD_VARIABLE;

	CCommon_Error__DEF_VARIABLE m_err_def_variable;
	p_variable->Link__DEF_VARIABLE__ERROR_FEEDBACK(&m_err_def_variable);

	// ...
	CString str_name;

	// OBJ ...
	{
		str_name = "OBJ.MSG";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__OBJ_MSG, str_name);
	}

	// MON ...
	{
		str_name = "MON.PUMPING.STATE";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_PUMPING_STATE, str_name);
	}

	// CFG - SR.SNS ...
	{
		str_name = "CFG.USE.SR.OPEN.SNS";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name, "NO YES", "");
		LINK__VAR_DIGITAL_CTRL(dCH__CFG_USE_SR_OPEN_SNS, str_name);

		str_name = "CFG.USE.SR.CLOSE.SNS";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name, "NO YES", "");
		LINK__VAR_DIGITAL_CTRL(dCH__CFG_USE_SR_CLOSE_SNS, str_name);
	}
	// CFG - FR.SNS ...
	{
		str_name = "CFG.USE.FR.OPEN.SNS";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name, "NO YES", "");
		LINK__VAR_DIGITAL_CTRL(dCH__CFG_USE_FR_OPEN_SNS, str_name);

		str_name = "CFG.USE.FR.CLOSE.SNS";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name, "NO YES", "");
		LINK__VAR_DIGITAL_CTRL(dCH__CFG_USE_FR_CLOSE_SNS, str_name);
	}

	// CFG - SR.TO ...
	{
		str_name = "CFG.USE.SR.OPEN.TIMEOUT";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "sec", 0, 1, 5, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_USE_SR_OPEN_TIMEOUT, str_name);

		str_name = "CFG.USE.SR.CLOSE.TIMEOUT";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "sec", 0, 1, 5, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_USE_SR_CLOSE_TIMEOUT, str_name);
	}
	// CFG - FR.TO ...
	{
		str_name = "CFG.USE.FR.OPEN.TIMEOUT";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "sec", 0, 1, 5, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_USE_FR_OPEN_TIMEOUT, str_name);

		str_name = "CFG.USE.FR.CLOSE.TIMEOUT";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "sec", 0, 1, 5, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_USE_FR_CLOSE_TIMEOUT, str_name);
	}

	// ...
	{
		p_variable->Add__MONITORING_PROC(3, MON_ID__STATUS);
	}
	return 1;
}
int CObj__VAC_VLV_PHY::__DEFINE__ALARM(p_alarm)
{
	DECLARE__ALARM;

	// ...
	CString title;
	title.Format("%s - ",sObject_Name);

	int alarm_id;
	CString alarm_title;
	CString alarm_msg;
	CStringArray l_act;

	// ...
	{
		alarm_id = ALID__FR_OPEN_SENSOR_TIMEOUT;

		alarm_title  = title;
		alarm_title += "FR Open Sensor Timeout !";

		alarm_msg = "";

		l_act.RemoveAll();
		l_act.Add("CHECK");

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}
	// ...
	{
		alarm_id = ALID__SR_OPEN_SENSOR_TIMEOUT;

		alarm_title  = title;
		alarm_title += "SR Open Sensor Timeout !";

		alarm_msg = "";

		l_act.RemoveAll();
		l_act.Add("CHECK");

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	// ...
	{
		alarm_id = ALID__FR_CLOSE_SENSOR_TIMEOUT;

		alarm_title  = title;
		alarm_title += "FR Close Sensor Timeout !";

		alarm_msg = "";

		l_act.RemoveAll();
		l_act.Add("CHECK");

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}
	// ...
	{
		alarm_id = ALID__SR_CLOSE_SENSOR_TIMEOUT;

		alarm_title  = title;
		alarm_title += "SR Close Sensor Timeout !";

		alarm_msg = "";

		l_act.RemoveAll();
		l_act.Add("CHECK");

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	return 1;
}

//-------------------------------------------------------------------------
int CObj__VAC_VLV_PHY::__INITIALIZE__OBJECT(p_variable,p_ext_obj_create)
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

	// ...
	CCommon_Utility x_utility;

	// DO VLV ...
	{
		def_name = "CH__DO_FR_VLV";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
		p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
		LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__DO_FR_VALVE_CTRL, obj_name,var_name);

		def_name = "CH__DO_SR_VLV";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
		p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
		LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__DO_SR_VALVE_CTRL, obj_name,var_name);

		//
		def_name = "CH__DO_EXHAUST_VLV";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);

		bool def_check = x_utility.Check__Link(ch_name);
		bActive__DO_EXHAUST_VALVE_CTRL = def_check;

		if(def_check)
		{
			p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
			LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__DO_EXHAUST_VALVE_CTRL, obj_name,var_name);
		}
	}

	// CH__DI_FR_OPEN_SNS ...
	{
		def_name = "CH__DI_FR_OPEN_SNS";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);

		bool def_check = x_utility.Check__Link(ch_name);
		bActive__DI_FR_OPEN_SNS = def_check;

		if(def_check)
		{
			p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
			LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__DI_FR_OPEN_SNS, obj_name,var_name);
		}
	}
	// CH__DI_FR_CLOSE_SNS ...
	{
		def_name = "CH__DI_FR_CLOSE_SNS";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);

		bool def_check = x_utility.Check__Link(ch_name);
		bActive__DI_FR_CLOSE_SNS =  def_check;

		if(def_check)
		{
			p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
			LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__DI_FR_CLOSE_SNS, obj_name,var_name);
		}
	}

	// CH__DI_SR_OPEN_SNS ...
	{
		def_name = "CH__DI_SR_OPEN_SNS";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);

		bool def_check = x_utility.Check__Link(ch_name);
		bActive__DI_SR_OPEN_SNS = def_check;

		if(def_check)
		{
			p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
			LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__DI_SR_OPEN_SNS, obj_name,var_name);
		}
	}
	// CH__DI_SR_CLOSE_SNS ...
	{
		def_name = "CH__DI_SR_CLOSE_SNS";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);

		bool def_check = x_utility.Check__Link(ch_name);
		bActive__DI_SR_CLOSE_SNS = def_check;

		if(def_check)
		{
			p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
			LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__DI_SR_CLOSE_SNS, obj_name,var_name);
		}
	}

	// CH__DI_DRY_PUMP_POWER_SENSOR ...
	{
		def_name = "CH__DI_DRY_PUMP_POWER_SENSOR";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
		p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
		LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__DI_DRY_PMP_PWR_SNS, obj_name,var_name);
	}

	return 1;
}

//-------------------------------------------------------------------------
int CObj__VAC_VLV_PHY::__CALL__CONTROL_MODE(mode,p_debug,p_variable,p_alarm)
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
			 IF__CTRL_MODE(sMODE__ALL_CLOSE)		flag = Call__ALL_CLOSE(p_variable, p_alarm);

		ELSE_IF__CTRL_MODE(sMODE__SR_OPEN)			flag = Call__SR_OPEN(p_variable, p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__SR_CLOSE)			flag = Call__SR_CLOSE(p_variable, p_alarm);

		ELSE_IF__CTRL_MODE(sMODE__FR_OPEN)			flag = Call__FR_OPEN(p_variable, p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__FR_CLOSE)			flag = Call__FR_CLOSE(p_variable, p_alarm);

		ELSE_IF__CTRL_MODE(sMODE__EXHAUST_OPEN)		flag = Call__EXHAUST_OPEN(p_variable, p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__EXHAUST_CLOSE)	flag = Call__EXHAUST_CLOSE(p_variable, p_alarm);
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

int CObj__VAC_VLV_PHY::__CALL__MONITORING(id,p_variable,p_alarm)
{
	if(id == MON_ID__STATUS)		return Mon__STATE_CHECK(p_variable, p_alarm);

	return 1;
}
