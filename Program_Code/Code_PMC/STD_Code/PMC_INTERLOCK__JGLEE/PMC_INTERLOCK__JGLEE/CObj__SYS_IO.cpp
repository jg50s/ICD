#include "StdAfx.h"
#include "CObj__SYS_IO__DEF.h"
#include "CObj__SYS_IO.h"

#include "CCommon_Utility.h"


//--------------------------------------------------------------------------------
CObj__SYS_IO::CObj__SYS_IO()
{
	pII_ALARM = NULL;
}
CObj__SYS_IO::~CObj__SYS_IO()
{

}

//--------------------------------------------------------------------------------
int CObj__SYS_IO::__DEFINE__CONTROL_MODE(obj, l_mode)
{
	sObject_Name = obj;

	// ...
	{
		ADD__CTRL_VAR(sMODE__TEST_1, "TEST.1");
	}
	return 1;
}
int CObj__SYS_IO::__DEFINE__VERSION_HISTORY(version)
{
	version = "JG.Lee \n";

	return 1;
}


// ...
#define MON_ID__MONITOR									1


int CObj__SYS_IO::__DEFINE__VARIABLE_STD(p_variable)
{
	DECLARE__STD_VARIABLE

	CString str_name;

	// OBJ.MSG ...
	{
		str_name = "OBJ.MSG";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__OBJ_MSG, str_name);
	}

	// ...
	CString def_name;
	CString def_data;
	CString ch_name;
	CString obj_name;
	CString var_name;

	CCommon_Utility x_utility;
	bool def_check;

	// IO Channel ...
	{
		def_name = "CH__DO_ROUGH_FORELINE_VLV";
		p_variable->Get__DEF_CONST_DATA(def_name, ch_name);

		sCH_Name__DO_ROUGH_FORELINE_VLV = ch_name;

		def_check = x_utility.Check__Link(ch_name);
		bActive__DO_ROUGH_FORELINE_VLV = def_check;

		//
		def_name = "CH__DO_ROUGH_FAST_VLV";
		p_variable->Get__DEF_CONST_DATA(def_name, ch_name);
		sCH_Name__DO_ROUGH_FAST_VLV = ch_name;

		def_name = "CH__DO_ROUGH_SOFT_VLV";
		p_variable->Get__DEF_CONST_DATA(def_name, ch_name);
		sCH_Name__DO_ROUGH_SOFT_VLV = ch_name;

		//
		def_name = "CH__IO_VAC_SNS";
		p_variable->Get__DEF_CONST_DATA(def_name, ch_name);
		sCH_Name__IO_VAC_SNS = ch_name;

		def_name = "CH__IO_ATM_SNS";
		p_variable->Get__DEF_CONST_DATA(def_name, ch_name);
		sCH_Name__IO_ATM_SNS = ch_name;

		//
		def_name = "CH__APC_VLV_CUR_POS";
		p_variable->Get__DEF_CONST_DATA(def_name, ch_name);
		sCH_Name__APC_VLV_CUR_POS = ch_name;
	}

	// ...
	{
		// p_variable->Add__MONITORING_PROC(1.0, MON_ID__MONITOR);
	}
	return 1;
}
int CObj__SYS_IO::__DEFINE__ALARM(p_alarm)
{
	DECLARE__ALARM;

	// ...
	int	    alarm_id;
	CString	alm_title;
	CString	alm_msg;
	CString alm_bff;
	CStringArray l_act;

	// ...
	{
		alarm_id = ALID__VAC_Foreline_Valve__OPEN;

		// 
		alm_title = "Setpoint Interlock : VAC-Foreline Valve -> Open";

		// 
		alm_msg  = "Interlock Condition \n";	

		alm_msg += "1. VAC-switch is \"ON\". \n";
		alm_msg += "2. When VAC-switch is not \"ON\", APC's valve position is close. \n";
		alm_msg += "3. Vacuum fast valve is close. \n";
		alm_msg += "4. Vacuum slow valve is close. \n";

		//
		l_act.RemoveAll();
		l_act.Add("CHECK");

		//
		ADD__ALARM_EX(alarm_id, alm_title,alm_msg, l_act);
	}

	// ...
	{
		alarm_id = ALID__VAC_Fast_Valve__OPEN;

		// 
		alm_title = "Setpoint Interlock : VAC-Fast Valve -> Open";

		// 
		alm_msg  = "Interlock Condition \n";	

		alm_msg += "1. ATM-switch is not \"ON\". \n";
		alm_msg += "2. TMP foreline valve is closed. \n";

		//
		l_act.RemoveAll();
		l_act.Add("CHECK");

		//
		ADD__ALARM_EX(alarm_id, alm_title,alm_msg, l_act);
	}

	// ...
	{
		alarm_id = ALID__VAC_Slow_Valve__OPEN;

		// 
		alm_title = "Setpoint Interlock : VAC-Slow Valve -> Open";

		// 
		alm_msg  = "Interlock Condition \n";	

		alm_msg += "1. TMP foreline valve is closed. \n";

		//
		l_act.RemoveAll();
		l_act.Add("CHECK");

		//
		ADD__ALARM_EX(alarm_id, alm_title,alm_msg, l_act);
	}
	return 1;
}


//--------------------------------------------------------------------------------
#define LINK__CHANNEL(CLS_CH)							\
ch_name.Format("%s+%s",obj_name,var_name);				\
CLS_CH->Register__CHANNEL_NAME(ch_name);


int CObj__SYS_IO::__INITIALIZE__OBJECT(p_variable,p_ext_obj_create)
{
	// ...
	{
		CString file_name;
		CString log_msg;

		// APP Log ...
		{
			file_name.Format("%s__APP.log", sObject_Name);

			log_msg  = "\n\n";
			log_msg += "//------------------------------------------------------------------------";

			xI__APP_LOG_CTRL->CREATE__SUB_DIRECTORY(sObject_Name);
			xI__APP_LOG_CTRL->SET__PROPERTY(file_name,12*1,60);

			xI__APP_LOG_CTRL->DISABLE__TIME_LOG();
			xI__APP_LOG_CTRL->WRITE__LOG(log_msg);

			xI__APP_LOG_CTRL->ENABLE__TIME_LOG();
			xI__APP_LOG_CTRL->WRITE__LOG("   START   \n");
		}
	}

	// ...
	CString def_name;
	CString def_data;
	CString ch_name;
	CString obj_name;
	CString var_name;

	CCommon_Utility x_utility;
	bool def_check;

	
	// IO Channel ...
	{
		def_name = "CH__DO_ROUGH_FORELINE_VLV";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);

		def_check = x_utility.Check__Link(ch_name);
		bActive__DO_ROUGH_FORELINE_VLV = def_check;

		if(def_check)
		{
			p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
			LINK__EXT_VAR_DIGITAL_CTRL(doEXT_CH__DO_ROUGH_FORELINE_VLV, obj_name,var_name);
		}

		//
		def_name = "CH__DO_ROUGH_FAST_VLV";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
		p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
		LINK__EXT_VAR_DIGITAL_CTRL(doEXT_CH__DO_ROUGH_FAST_VLV, obj_name,var_name);

		def_name = "CH__DO_ROUGH_SOFT_VLV";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
		p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
		LINK__EXT_VAR_DIGITAL_CTRL(doEXT_CH__DO_ROUGH_SOFT_VLV, obj_name,var_name);

		//
		def_name = "CH__IO_VAC_SNS";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
		p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
		LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__IO_VAC_SNS, obj_name,var_name);

		def_name = "DATA__VAC_SNS.ACTIVE_STATE";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, def_data);
		sVAC_SNS__ACTIVE_STATE = def_data;

		//
		def_name = "CH__IO_ATM_SNS";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
		p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
		LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__IO_ATM_SNS, obj_name,var_name);

		def_name = "DATA__ATM_SNS.ACTIVE_STATE";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, def_data);
		sATM_SNS__ACTIVE_STATE = def_data;

		//
		def_name = "CH__APC_VLV_CUR_POS";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
		p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
		LINK__EXT_VAR_STRING_CTRL(sEXT_CH__APC_VLV_CUR_POS, obj_name,var_name);
	}
	
	return 1;
}


//--------------------------------------------------------------------------------
int CObj__SYS_IO
::__CALL__CONTROL_MODE(mode, p_debug, p_variable, p_alarm)
{
	CString msg;

	// ...
	{
		msg.Format("%s Started...",mode);
		sCH__OBJ_MSG->Set__DATA(msg);

		xI__APP_LOG_CTRL->WRITE__LOG(msg);
	}

	int flag = -1;

	// ...
	{
		IF__CTRL_MODE(sMODE__TEST_1)			flag = Call__TEST_1(p_variable, p_alarm);
	}

	if((flag < 0)||(p_variable->Check__CTRL_ABORT() > 0))
	{
		msg.Format("%s Aborted (%1d)", mode, flag);
	}
	else
	{
		msg.Format("%s Completed (%1d)", mode, flag);
	}	

	// ...
	{
		sCH__OBJ_MSG->Set__DATA(msg);

		xI__APP_LOG_CTRL->WRITE__LOG(msg);
	}
	return flag;
}

int CObj__SYS_IO::__CALL__MONITORING(id, p_variable, p_alarm)
{
	if(id == MON_ID__MONITOR)			Mon__MONITOR(p_variable,p_alarm);

	return 1;
}
