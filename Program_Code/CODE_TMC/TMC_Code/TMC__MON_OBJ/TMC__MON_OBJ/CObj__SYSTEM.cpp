#include "StdAfx.h"
#include "CObj__SYSTEM.h"
#include "CObj__SYSTEM__DEF.h"
#include "CObj__SYSTEM__ALID.h"


//-------------------------------------------------------------------------
CObj__SYSTEM::CObj__SYSTEM()
{

}
CObj__SYSTEM::~CObj__SYSTEM()
{

}

//-------------------------------------------------------------------------
int CObj__SYSTEM::__DEFINE__CONTROL_MODE(obj,l_mode)
{
	sObject_Name = obj;

	return 1;
}
int CObj__SYSTEM::__DEFINE__VERSION_HISTORY(version)
{

	return 1;
}


// ...
#define  MON_ID__IO_MONITOR				1
#define  MON_ID__N2_SNS_MONITOR			2
#define  MON_ID__EFEM_DOORS_MONITOR		3


int CObj__SYSTEM::__DEFINE__VARIABLE_STD(p_variable)
{
	DECLARE__STD_VARIABLE;

	CCommon_Error__DEF_VARIABLE m_err_def_variable;
	p_variable->Link__DEF_VARIABLE__ERROR_FEEDBACK(&m_err_def_variable);

	// ...
	CString str_name;

	str_name.Format("aCFG.FFU.DIFFER.PRESSURE");
	STD__ADD_ANALOG_WITH_X_OPTION(str_name, "torr", 3, 0.0, 1000, "");
	LINK__VAR_ANALOG_CTRL(aCFG_FFU_DIFFERENTIAL_PRESSURE_VAL, str_name);

	str_name.Format("dCFG.N2.CHECK");
	STD__ADD_DIGITAL_WITH_X_OPTION(str_name, "FALSE TRUE", "");
	LINK__VAR_DIGITAL_CTRL(dCFG_N2_CHECK, str_name);

	str_name.Format("dCFG.CDA.CHECK");
	STD__ADD_DIGITAL_WITH_X_OPTION(str_name, "FALSE TRUE", "");
	LINK__VAR_DIGITAL_CTRL(dCFG_CDA_CHECK, str_name);

	// ...
	{
		p_variable->Add__MONITORING_PROC(1.0, MON_ID__IO_MONITOR);
		p_variable->Add__MONITORING_PROC(1.0, MON_ID__N2_SNS_MONITOR);
	}
	return 1;
}


// ...
#define  REG_ACT__CHECK							\
l_act.RemoveAll();								\
l_act.Add("CHECK");


int CObj__SYSTEM::__DEFINE__ALARM(p_alarm)
{
	DECLARE__ALARM;

	// ...
	CString title;
	title.Format("%s - ",sObject_Name);

	CString alarm_title;
	CString alarm_msg;
	CString alarm_bff;
	CStringArray l_act;
	int alarm_id;

	//.....
	alarm_id = ALID__AIR_PRESSURE__ERROR;

	alarm_title  = title;
	alarm_title += "System Air Sensor is not \"ON\".";

	alarm_msg  = "System Air Sensor is not \"ON\".\n";
	alarm_msg += "Please, check system air sensor status.\n";

	REG_ACT__CHECK;
	ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);


	//.....
	alarm_id = ALID__FFU_LOW_PRESSURE__ERROR;

	alarm_title  = title;
	alarm_title += "System FFU Differential Pressure Alarm Occured.";

	alarm_msg  = "1. Please, Check.. EFEM Side Doors Close Status.\n";
	alarm_msg += "2. Please, Check.. FFU Fan Speed.\n";

	REG_ACT__CHECK;
	ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);

	//.....
	alarm_id = ALID__N2_SENSOR__ERROR;

	alarm_title  = title;
	alarm_title += "N2 Sensor is not \"ON\".";

	alarm_msg  = "N2 Sensor is not \"ON\".\n";
	alarm_msg += "Please, check system N2 sensor status.\n";

	REG_ACT__CHECK;
	ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);

	//.....
	alarm_id = ALID__EFEM_SIDE_DOOR_NOT_CLOSE__ERROR;

	alarm_title  = title;
	alarm_title += "EFEM Side Door Is Not Closed Status.";

	alarm_msg   = "1. ATM Robot will be stopped.\n";
	alarm_msg  += "2. Please, Check.. EFEM Left and Right Door.\n";

	REG_ACT__CHECK;
	ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);

	return 1;
}

int CObj__SYSTEM::__Define__USER_FUNCTION(CII_DEFINE__FUNCTION *p_fnc_ctrl)
{
	p_fnc_ctrl->Link__ERROR_FEEDBACK(&mERROR__USER_FNC);

	return 1;
}

//-------------------------------------------------------------------------
int CObj__SYSTEM::__INITIALIZE__OBJECT(p_variable,p_ext_obj_create)
{	
	CString def_name;
	CString def_data;
	CString str_name;

	CString ch_name;
	CString obj_name;
	CString var_name;

	// IO CHANNEL -----
	{
		// 1.
		{
			def_name = "IO_CH__DNET_COMM_STS";
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);

			//....
			p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
			LINK__EXT_VAR_DIGITAL_CTRL(diEXT_CH__IO_DNET_COMM_STS, obj_name,var_name);
		}

		// 2. 
		{
			def_name = "IO_CH__AIR_SNS";
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);

			//....
			p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
			LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__IO_AIR_SNS, obj_name,var_name);
		}

		// 3. 
		{
			def_name = "IO_CH__N2_SENSOR";
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);

			//....
			p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
			LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__IO_N2_SNS, obj_name,var_name);
		}

		// 4. 
		{
			def_name = "IO_CH__EFEM_DOOR";
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);

			//....
			p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
			LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__IO_EFEM_DOOR_SNS, obj_name,var_name);
		}
	}

	return 1;
}

//-------------------------------------------------------------------------
int CObj__SYSTEM::__CALL__CONTROL_MODE(mode,p_debug,p_variable,p_alarm)
{

	return -1;
}

int CObj__SYSTEM::__CALL__MONITORING(id,p_variable,p_alarm)
{
	switch(id)
	{
		case MON_ID__IO_MONITOR:
			Mon__IO_MONITOR(p_variable,p_alarm);
			break;

		case MON_ID__N2_SNS_MONITOR:
			Mon__N2_SENSOR_MONITOR(p_variable,p_alarm);
			break;
	}
	return 1;
}
