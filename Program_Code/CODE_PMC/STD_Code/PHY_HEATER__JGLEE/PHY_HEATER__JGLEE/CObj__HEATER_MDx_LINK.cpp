#include "StdAfx.h"
#include "CObj__HEATER_MDx_LINK.h"
#include "CObj__HEATER_MDx_LINK__ALID.h"

#include "CCommon_Utility.h"


//-------------------------------------------------------------------------
CObj__HEATER_MDx_LINK::CObj__HEATER_MDx_LINK()
{

}
CObj__HEATER_MDx_LINK::~CObj__HEATER_MDx_LINK()
{

}

//-------------------------------------------------------------------------
int CObj__HEATER_MDx_LINK::__DEFINE__CONTROL_MODE(obj,l_mode)
{
	sObject_Name = obj;

	// ...
	{
		ADD__CTRL_VAR(sMODE__INIT,	"INIT");
	}
	return 1;
}
int CObj__HEATER_MDx_LINK::__DEFINE__VERSION_HISTORY(version)
{

	return 1;
}

int CObj__HEATER_MDx_LINK::__DEFINE__VARIABLE_STD(p_variable)
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

		str_name = "OBJ.STATUS";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__OBJ_STATUS, str_name);

		str_name = "OBJ.TIMER";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__OBJ_TIMER, str_name);
	}

	// LINK.IO ...
	{
		str_name = "MON.IO.TEMPERATURE.SP";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_IO_TEMPERATURE_SP, str_name);

		str_name = "MON.IO.TEMPERATURE.PV";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_IO_TEMPERATURE_PV, str_name);
	}

	return 1;
}

int CObj__HEATER_MDx_LINK::__DEFINE__ALARM(p_alarm)
{
	DECLARE__ALARM;

	// ...
	CString title;
	title.Format("%s : ", sObject_Name);

	CString alarm_title;
	CString alarm_msg;
	CStringArray l_act;
	int alarm_id;

	iLIST_ALID__HTR.RemoveAll();

	// ...
	{

	}

	return 1;
}

//-------------------------------------------------------------------------
int CObj__HEATER_MDx_LINK::__INITIALIZE__OBJECT(p_variable,p_ext_obj_create)
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

	return 1;
}

//-------------------------------------------------------------------------
int CObj__HEATER_MDx_LINK::__CALL__CONTROL_MODE(mode,p_debug,p_variable,p_alarm)
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
	}

	if((flag < 0)||(p_variable->Check__CTRL_ABORT() > 0))
	{
		CString log_msg;
		log_msg.Format("Aborted (%1d) ... :  [%s]", flag,mode);

		sCH__OBJ_MSG->Set__DATA(log_msg);
		xI_LOG_CTRL->WRITE__LOG(log_msg);		
	}
	else
	{
		CString log_msg;
		log_msg.Format("Completed ... :  [%s]", mode);

		sCH__OBJ_MSG->Set__DATA(log_msg);
		xI_LOG_CTRL->WRITE__LOG(log_msg);
	}

	return flag;
}

int CObj__HEATER_MDx_LINK::__CALL__MONITORING(id,p_variable,p_alarm)
{

	return 1;
}
