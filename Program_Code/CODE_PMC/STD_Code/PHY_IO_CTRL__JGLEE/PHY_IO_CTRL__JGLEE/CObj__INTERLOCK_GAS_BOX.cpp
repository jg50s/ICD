#include "StdAfx.h"
#include "CObj__INTERLOCK_GAS_BOX.h"

#include "CCommon_Utility.h"


//-------------------------------------------------------------------------
CObj__INTERLOCK_GAS_BOX::CObj__INTERLOCK_GAS_BOX()
{

}
CObj__INTERLOCK_GAS_BOX::~CObj__INTERLOCK_GAS_BOX()
{

}

//-------------------------------------------------------------------------
int CObj__INTERLOCK_GAS_BOX::__DEFINE__CONTROL_MODE(obj,l_mode)
{
	sObject_Name = obj;

	return 1;
}
int CObj__INTERLOCK_GAS_BOX::__DEFINE__VERSION_HISTORY(version)
{

	return 1;
}


// ...
#define MON_ID__INTERLOCK_SENSOR					1


int CObj__INTERLOCK_GAS_BOX::__DEFINE__VARIABLE_STD(p_variable)
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
	}

	// ERROR ...
	{
		str_name = "ACTIVE.GAS_BOX.DIFF_PRESSURE.ERROR";
		STD__ADD_DIGITAL(str_name, "OFF ON");
		LINK__VAR_DIGITAL_CTRL(dCH__ACTIVE_GAS_BOX_DIFF_PRESSURE_ERROR, str_name);
	}

	// ...
	{
		p_variable->Add__MONITORING_PROC(5.0, MON_ID__INTERLOCK_SENSOR);
	}
	return 1;
}

int CObj__INTERLOCK_GAS_BOX::__DEFINE__ALARM(p_alarm)
{
	DECLARE__ALARM;

	// ...
	CString title;
	title.Format("%s - ", sObject_Name);

	// ...
	int alarm_id;
	CString alarm_title;
	CString alarm_msg;
	CStringArray l_act;

	// ...
	{
		alarm_id = ALID__GAS_BOX_DIFF_PRESSURE_ERROR;

		alarm_title  = title;
		alarm_title += "Gas-Box Diff-Pressure Error !";

		alarm_msg = "Gas-Box의 차압력을 확인 바랍니다.\n";

		l_act.RemoveAll();
		l_act.Add(ACT__CHECK);

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	// ...
	{
		alarm_id = ALID__DGF_ALL_VALVE_CLOSE;

		alarm_title  = title;
		alarm_title += "The all valve of DGF are close !";

		alarm_msg = "Gas를 Flow 시킬 수 없습니다. \n";

		l_act.RemoveAll();
		l_act.Add(ACT__CHECK);

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	//
	for(int i=0; i<DEF_SIZE__INTERLOCK_SENSOR; i++)
	{
		// Heavy Error ...
		{
			alarm_id = ALID__INTERLOCK_HEAVY_ACTIVE + i;

			alarm_title  = title;
			alarm_title += "Heavy Interlock Sensor Active !";

			alarm_msg = "Interlock Sensor 상태를 확인 바랍니다.\n";

			l_act.RemoveAll();
			l_act.Add(ACT__CHECK);

			ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
		}

		// Light Error ...
		{
			alarm_id = ALID__INTERLOCK_LIGHT_ACTIVE + i;

			alarm_title  = title;
			alarm_title += "Light Interlock Sensor Active !";

			alarm_msg = "Interlock Sensor 상태를 확인 바랍니다.\n";

			l_act.RemoveAll();
			l_act.Add(ACT__CHECK);

			ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
		}
	}

	return 1;
}

//-------------------------------------------------------------------------
int CObj__INTERLOCK_GAS_BOX::__INITIALIZE__OBJECT(p_variable,p_ext_obj_create)
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

	// OBJ DB_SYS ...
	{
		def_name = "OBJ__DB_SYS";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, obj_name);

		//
		var_name = "CFG.INTERLOCK.USE.MODE";
		LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__CFG_INTERLOCK_USE_MODE, obj_name,var_name);

		var_name = "CFG.INTERLOCK.USE.INTERLOCK_SNS.ALL";
		LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__CFG_INTERLOCK_USE__INTERLOCK_SNS_ALL, obj_name,var_name);

		var_name = "CFG.INTERLOCK.CHECK.SEC";
		LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__CFG_INTERLOCK_CHECK_SEC, obj_name,var_name);

		//
		var_name = "CFG.GAS_BOX.DIFF_PRESSURE.LOW_PRESSURE";
		LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__CFG_GAS_BOX_DIFF_PRESSURE_LOW_PRESSURE, obj_name,var_name);
	}

	// Channel Link : INTERLOCK ...
	{
		def_name = "CH__INTERLOCK_HEAVY_ACTIVE";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
		p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
		LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__INTERLOCK_HEAVY_ACTIVE, obj_name,var_name);

		def_name = "CH__INTERLOCK_LIGHT_ACTIVE";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
		p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
		LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__INTERLOCK_LIGHT_ACTIVE, obj_name,var_name);		

		//
		def_name = "CH__INTERLOCK_HEAVY_MESSAGE";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
		p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
		LINK__EXT_VAR_STRING_CTRL(sEXT_CH__INTERLOCK_HEAVY_MESSAGE, obj_name,var_name);

		def_name = "CH__INTERLOCK_HEAVY_MESSAGE";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
		p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
		LINK__EXT_VAR_STRING_CTRL(sEXT_CH__INTERLOCK_LIGHT_MESSAGE, obj_name,var_name);
	}

	// Channel Link : GAS_BOX ...
	{
		CCommon_Utility x_utility;

		// GAS_BOX.DIFF_PRESSURE ...
		{
			def_name = "CH__AI_GAS_BOX_DIFF_PRESSURE";
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);

			bool def_check = x_utility.Check__Link(ch_name);
			bActive__Gas_Box_Diff_Pressure = def_check;

			if(def_check)
			{
				p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
				LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__GAS_BOX_DIFF_PRESSURE, obj_name,var_name);
			}
		}

		// DGF.ALL_CLOSE_ACTIVE ...
		{
			def_name = "CH__DI_DGF_ALL_CLOSE_ACTIVE";
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);

			bool def_check = x_utility.Check__Link(ch_name);
			bActive__DGF_All_Close_Active = def_check;

			if(def_check)
			{
				p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
				LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__DGF_ALL_CLOSE_ACTIVE, obj_name,var_name);
			}
		}
	}

	// Interlock Sensor Link ...
	{
		def_name = "DATA.INTERLOCK_SIZE";
		p_variable->Get__DEF_CONST_DATA(def_name, def_data);
		iSIZE__INTERLOCK_SENSOR = atoi(def_data);

		if(iSIZE__INTERLOCK_SENSOR > DEF_SIZE__INTERLOCK_SENSOR)
			iSIZE__INTERLOCK_SENSOR = DEF_SIZE__INTERLOCK_SENSOR;

		for(i=0; i<iSIZE__INTERLOCK_SENSOR; i++)
		{
			int id = i + 1;

			def_name.Format("CH__CFG_USE.%1d", id);
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
			p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
			LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__CFG_USE_X[i], obj_name,var_name);

			def_name.Format("CH__DI_SENSOR.%1d", id);
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
			p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
			LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__DI_SENSOR_X[i], obj_name,var_name);

			//
			def_name.Format("DATA.NORMAL_STATE.%1d", id);
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name, def_data);
			sDATA__NORMAL_STATE_X[i] = def_data;

			def_name.Format("DATA.ERROR_MSG.%1d", id);
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name, def_data);
			sDATA__ERROR_MSG_X[i] = def_data;

			//
			def_name.Format("DATA.ERROR_LEVEL.%1d", id);
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name, def_data);

			if(def_data.CompareNoCase("HEAVY") == 0)		iDATA__ERROR_LEVEL_X[i] = _ERR_LEVEL__HEAVY;
			else											iDATA__ERROR_LEVEL_X[i] = _ERR_LEVEL__LIGHT;
		}
	}

	// ...
	{
		SCX__SEQ_INFO seq_info;

		iActive__SIM_MODE = seq_info->Is__SIMULATION_MODE();
	}
	return 1;
}

//-------------------------------------------------------------------------
int CObj__INTERLOCK_GAS_BOX::__CALL__CONTROL_MODE(mode,p_debug,p_variable,p_alarm)
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

int CObj__INTERLOCK_GAS_BOX::__CALL__MONITORING(id,p_variable,p_alarm)
{
	if(id == MON_ID__INTERLOCK_SENSOR)		Mon__INTERLOCK_SENSOR(p_variable, p_alarm);

	return 1;
}
