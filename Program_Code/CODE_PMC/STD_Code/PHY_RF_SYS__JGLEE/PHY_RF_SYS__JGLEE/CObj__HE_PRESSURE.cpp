#include "StdAfx.h"
#include "CObj__HE_PRESSURE.h"
#include "CObj__HE_PRESSURE__ALID.h"


//-------------------------------------------------------------------------
CObj__HE_PRESSURE::CObj__HE_PRESSURE()
{

}
CObj__HE_PRESSURE::~CObj__HE_PRESSURE()
{

}

//-------------------------------------------------------------------------
int CObj__HE_PRESSURE::__DEFINE__CONTROL_MODE(obj,l_mode)
{
	sObject_Name = obj;

	// ...
	{
		ADD__CTRL_VAR(sMODE__INIT,		   "INIT");
		ADD__CTRL_VAR(sMODE__CLOSE,		   "CLOSE");
		ADD__CTRL_VAR(sMODE__PRESSURE_SET, "PRESSURE.SET");
	}
	return 1;
}
int CObj__HE_PRESSURE::__DEFINE__VERSION_HISTORY(version)
{

	return 1;
}


// ...
#define MON_ID__STATUS							1


int CObj__HE_PRESSURE::__DEFINE__VARIABLE_STD(p_variable)
{
	DECLARE__STD_VARIABLE;

	CCommon_Error__DEF_VARIABLE m_err_def_variable;
	p_variable->Link__DEF_VARIABLE__ERROR_FEEDBACK(&m_err_def_variable);

	// ...
	CString str_name;
	int i;

	// OBJ ...
	{
		str_name = "OBJ.MSG";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__OBJ_MSG, str_name);
	}

	//
	for(i=0; i<_CFG__ZONE_SIZE; i++)
	{
		int id = i + 1;

		// CFG...
		{
			str_name.Format("CFG.HE.PRESSURE.CTRL.MODE.%1d", id);
			STD__ADD_DIGITAL_WITH_X_OPTION(str_name, "SET RAMP.%1d", ""); // SET : right away value set, RAMP : ramp Set by Up Time
			LINK__VAR_DIGITAL_CTRL(dCH__CFG_CTRL_MODE[i], str_name);

			str_name.Format("CFG.HE.PRESSURE.RAMP.UP.TIME.%1d", id);
			STD__ADD_ANALOG_WITH_X_OPTION(str_name, "sec", 0, 0, 10, "");
			LINK__VAR_ANALOG_CTRL(aCH__CFG_RAMP_TIME[i], str_name);
		}

		// PARA ...
		{
			str_name.Format("PARA.PRESSURE.SET.%1d", id);
			STD__ADD_ANALOG_WITH_X_OPTION(str_name, "torr", 0, 1.0, 100.0, "");
			LINK__VAR_ANALOG_CTRL(aCH__PARA_PRESSURE_SET_X[i], str_name);
		}
		// USER ...
		{
			str_name.Format("USER.IO.PRESSURE.SET.%1d", id);
			STD__ADD_ANALOG(str_name, "torr", 1, 0.0, 100.0);
			LINK__VAR_ANALOG_CTRL(aCH__USER_IO_PRESSURE_SET_X[i], str_name);
		}

		// MON ...
		{
			str_name.Format("MON.IO.PRESSURE.SET.%1d", id);
			STD__ADD_ANALOG_WITH_OPTION(str_name, "torr", 0, 0.0, 100.0, -1, "L", "");
			LINK__VAR_ANALOG_CTRL(aCH__MON_IO_PRESSURE_SET_X[i], str_name);

			//
			str_name.Format("MON.IO.STATUS.%1d", id);
			STD__ADD_STRING(str_name);
			LINK__VAR_STRING_CTRL(sCH__MON_IO_STATUS_X[i], str_name);

			str_name.Format("MON.IO.PRESSURE.GET.%1d", id);
			STD__ADD_ANALOG_WITH_OPTION(str_name, "torr", 1, 0.0, 100.0, -1, "L", "");
			LINK__VAR_ANALOG_CTRL(aCH__MON_IO_PRESSURE_GET_X[i], str_name);

			str_name.Format("MON.IO.FLOW.%1d", id);
			STD__ADD_ANALOG_WITH_OPTION(str_name, "sccm", 1, 0.0, 100.0, -1, "L", "");
			LINK__VAR_ANALOG_CTRL(aCH__MON_IO_FLOW_X[i], str_name);
		}
	}

	// ...
	{
		p_variable->Add__MONITORING_PROC(1.0, MON_ID__STATUS);
	}
	return 1;
}


// ...
#define  ACT__CLEAR								\
l_act.RemoveAll();								\
l_act.Add(STR__CLEAR);


int CObj__HE_PRESSURE::__DEFINE__ALARM(p_alarm)
{
	DECLARE__ALARM;

	// ...
	CString title;
	title.Format("%s : ", sObject_Name);

	CString alarm_title;
	CString alarm_msg;
	CStringArray l_act;
	int alarm_id;

	/*
	// ...
	{
		alarm_id = ALID__CH1_WARNING;

		alarm_title  = title;
		alarm_title += "CH1 Warning !";

		alarm_msg  = "";
		alarm_msg += "Please, check the ratio of CH1 ! \n";

		ACT__CLEAR;

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}
	*/

	return 1;
}

//-------------------------------------------------------------------------
int CObj__HE_PRESSURE::__INITIALIZE__OBJECT(p_variable,p_ext_obj_create)
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

	// DB OBJ ...
	{	
		def_name = "OBJ__DB";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, obj_name);

	}

	// ...
	{
		def_name = "DATA.ZONE_SIZE";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, def_data);

		iZONE_SIZE = atoi(def_data);
		if(iZONE_SIZE > _CFG__ZONE_SIZE)			iZONE_SIZE = _CFG__ZONE_SIZE;

		for(i=0; i<iZONE_SIZE; i++)
		{
			int id = i +1;

			// Input.HEXA ...
			{
				def_name.Format("CH__SI_STATE_HEXA.%1d", id);
				p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
				p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
				LINK__EXT_VAR_STRING_CTRL(siEXT_CH__STATE_HEXA_X[i], obj_name,var_name);

				def_name.Format("CH__SI_PRESSURE_HEXA.%1d", id);
				p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
				p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
				LINK__EXT_VAR_STRING_CTRL(siEXT_CH__PRESSURE_HEXA_X[i], obj_name,var_name);

				def_name.Format("CH__SI_FLOW_HEXA.%1d", id);
				p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
				p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
				LINK__EXT_VAR_STRING_CTRL(siEXT_CH__FLOW_HEXA_X[i], obj_name,var_name);
			}	
			
			// Output.HEXA ...
			{
				def_name.Format("CH__SO_PRESSURE_HEXA.%1d", id);
				p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
				p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
				LINK__EXT_VAR_STRING_CTRL(soEXT_CH__PRESSURE_HEXA_X[i], obj_name,var_name);
			}
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
int CObj__HE_PRESSURE::__CALL__CONTROL_MODE(mode,p_debug,p_variable,p_alarm)
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
		ELSE_IF__CTRL_MODE(sMODE__CLOSE)			flag = Call__CLOSE(p_variable, p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__PRESSURE_SET)		flag = Call__PRESSURE_SET(p_variable,p_alarm);
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

int CObj__HE_PRESSURE::__CALL__MONITORING(id,p_variable,p_alarm)
{
	if(id == MON_ID__STATUS)		Mon__STATUS(p_variable, p_alarm);

	return 1;
}
