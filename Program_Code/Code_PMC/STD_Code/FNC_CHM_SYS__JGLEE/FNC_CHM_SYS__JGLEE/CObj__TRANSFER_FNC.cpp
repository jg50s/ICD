#include "StdAfx.h"
#include "CCommon_Utility.h"

#include "CObj__TRANSFER_FNC.h"
#include "CObj__TRANSFER_FNC__ALID.h"
#include "CObj__TRANSFER_FNC__DEF.h"


//-------------------------------------------------------------------------
CObj__TRANSFER_FNC::CObj__TRANSFER_FNC()
{

}
CObj__TRANSFER_FNC::~CObj__TRANSFER_FNC()
{

}


//-------------------------------------------------------------------------
int CObj__TRANSFER_FNC::__DEFINE__CONTROL_MODE(obj,l_mode)
{
	sObject_Name = obj;

	// ...
	{
		ADD__CTRL_VAR(sMODE__INIT,				"INIT");

		ADD__CTRL_VAR(sMODE__PICK_READY,		"PICK_READY");
		ADD__CTRL_VAR(sMODE__PICK_X_READY,		"PICK_X_READY");
		ADD__CTRL_VAR(sMODE__PICK_COMPLETE,		"PICK_COMPLETE");
		ADD__CTRL_VAR(sMODE__PICK_X_COMPLETE,	"PICK_X_COMPLETE");

		ADD__CTRL_VAR(sMODE__PLACE_READY,		"PLACE_READY");
		ADD__CTRL_VAR(sMODE__PLACE_X_READY,		"PLACE_X_READY");
		ADD__CTRL_VAR(sMODE__PLACE_COMPLETE,	"PLACE_COMPLETE");
		ADD__CTRL_VAR(sMODE__PLACE_X_COMPLETE,	"PLACE_X_COMPLETE");
	}
	return 1;
}
int CObj__TRANSFER_FNC::__DEFINE__VERSION_HISTORY(version)
{

	return 1;
}

int CObj__TRANSFER_FNC::__DEFINE__VARIABLE_STD(p_variable)
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
	}

	return 1;
}
int CObj__TRANSFER_FNC::__DEFINE__ALARM(p_alarm)
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
		alarm_id = ALID__RF_POWER_STS;

		alarm_title  = title;
		alarm_title += "RF POWER STATUS ALARM";

		alarm_msg = "RF Power Status Error.";

		l_act.RemoveAll();
		l_act.Add(ACT__RETRY);
		l_act.Add(ACT__ABORT);

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	// ...
	{
		alarm_id = ALID__ESC_POWER_STS;

		alarm_title = title;
		alarm_title += "ESC POWER STATUS ALARM";

		alarm_msg = "ESC Power Status Error.";
		alarm_msg +="\nPlease Check ESC Power Status.";

		l_act.RemoveAll();
		l_act.Add(ACT__RETRY);
		l_act.Add(ACT__ABORT);

		ADD__ALARM_EX(alarm_id, alarm_title, alarm_msg, l_act);
	}

	return 1;
}


//-------------------------------------------------------------------------
int CObj__TRANSFER_FNC::__INITIALIZE__OBJECT(p_variable,p_ext_obj_create)
{	
	// ...
	{
		CString file_name;
		CString log_msg;

		file_name.Format("%s_App.log", sObject_Name);

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
	bool def_check;

	// OBJ : RFx ...
	{
		def_name = "DATA.RF_SIZE";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, def_data);

		iDATA__RF_SIZE = atoi(def_data);
		if(iDATA__RF_SIZE > _CFG__RF_SIZE)			iDATA__RF_SIZE = _CFG__RF_SIZE;

		for(i=0; i<iDATA__RF_SIZE; i++)
		{
			int id = i + 1;

			def_name.Format("DATA__IO_RF_NAME.%1d", id);
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name, def_data);
			sList__RFx_NAME[i] = def_data;

			def_name.Format("CH__IO_RF_ON_STATUS.%1d", id);
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
			p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
			LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__RFx_ON_STS[i], obj_name,var_name);
		}
	}

	// OBJ : ESC ...
	{
		def_name = "CH__ESC_ON_STS";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);

		def_check = x_utility.Check__Link(ch_name);
		bActive__ESC_ON_STS = def_check;

		if(def_check)
		{
			p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
			LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__ESC_ON_STS, obj_name,var_name);
		}
	}

	return 1;
}


//-------------------------------------------------------------------------
int CObj__TRANSFER_FNC::__CALL__CONTROL_MODE(mode,p_debug,p_variable,p_alarm)
{
	DECLARE__EXT_CTRL(p_variable);

	int flag = -1;

	// ...
	{
		CString log_msg;	
		log_msg.Format("Start [%s] ... By %s \n", mode, p_ext_mode_ctrl->Get__UPPER_OBJECT_NAME());

		sCH__OBJ_MSG->Set__DATA(log_msg);		
		xI_LOG_CTRL->WRITE__LOG(log_msg);
	}

	// ...
	{
			 IF__CTRL_MODE(sMODE__INIT)					flag = Call__INIT(p_variable, p_alarm);

		ELSE_IF__CTRL_MODE(sMODE__PICK_READY)			flag = Call__PICK_READY(p_variable, p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__PICK_X_READY)			flag = Call__PICK_X_READY(p_variable, p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__PICK_COMPLETE)		flag = Call__PICK_COMPLETE(p_variable, p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__PICK_X_COMPLETE)		flag = Call__PICK_X_COMPLETE(p_variable, p_alarm);

		ELSE_IF__CTRL_MODE(sMODE__PLACE_READY)			flag = Call__PLACE_READY(p_variable, p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__PLACE_X_READY)		flag = Call__PLACE_X_READY(p_variable, p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__PLACE_COMPLETE)		flag = Call__PLACE_COMPLETE(p_variable, p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__PLACE_X_COMPLETE)		flag = Call__PLACE_X_COMPLETE(p_variable, p_alarm);
	}

	if((flag < 0)||(p_variable->Check__CTRL_ABORT() > 0))
	{
		CString log_msg;
		log_msg.Format("[%s] Aborted ... ", mode);

		sCH__OBJ_MSG->Set__DATA(log_msg);
		xI_LOG_CTRL->WRITE__LOG(log_msg);		
	}
	else
	{
		CString log_msg;
		log_msg.Format("[%s] Completed ... ", mode);

		sCH__OBJ_MSG->Set__DATA(log_msg);
		xI_LOG_CTRL->WRITE__LOG(log_msg);
	}

	return flag;
}

int CObj__TRANSFER_FNC::__CALL__MONITORING(id,p_variable,p_alarm)
{

	return 1;
}
