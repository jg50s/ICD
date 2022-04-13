#include "StdAfx.h"
#include "CObj__EPD_STD.h"



//-------------------------------------------------------------------------
CObj__EPD_STD::CObj__EPD_STD()
{

}
CObj__EPD_STD::~CObj__EPD_STD()
{

}


//-------------------------------------------------------------------------
int CObj__EPD_STD::__DEFINE__CONTROL_MODE(obj,l_mode)
{
	sObject_Name = obj;

	// ...
	{
		ADD__CTRL_VAR(sMODE__INIT,		 "INIT");
		ADD__CTRL_VAR(sMODE__EPD_DETECT, "EPD_DETECT");
	}
	return 1;
}
int CObj__EPD_STD::__DEFINE__VERSION_HISTORY(version)
{

	return 1;
}


// ...
#define  APP_DSP__EPD_MODE					\
"ValueChange								\
 PercentChange								\
 ValueSlope									\
 PercentSlope"

int CObj__EPD_STD::__DEFINE__VARIABLE_STD(p_variable)
{
	DECLARE__STD_VARIABLE;

	// ...
	CCommon_Error__DEF_VARIABLE m_err_def_variable;
	p_variable->Link__DEF_VARIABLE__ERROR_FEEDBACK(&m_err_def_variable);

	// ...
	CString str_name, item_list;

	//
	str_name.Format("APP.OBJ.MSG");
	STD__ADD_STRING(str_name);
	LINK__VAR_STRING_CTRL(sCH__OBJ_MSG, str_name);

	// EPD Configuration
	str_name.Format("CFG.EPD.MODE");
	STD__ADD_DIGITAL(str_name, APP_DSP__EPD_MODE);
	LINK__VAR_DIGITAL_CTRL(dCH__CFG_EPD_MODE, str_name);

	//
	str_name.Format("CFG.EPD.TIMEOUT.MINIMUM");
	STD__ADD_ANALOG(str_name, "sec", 3, 0, 3600);
	LINK__VAR_ANALOG_CTRL(aCH__CFG_EPD_TIMEOUT_MINIMUM, str_name);

	str_name.Format("CFG.EPD.TIMEOUT.MAXIMUM");
	STD__ADD_ANALOG(str_name, "sec", 3, 0, 3600);
	LINK__VAR_ANALOG_CTRL(aCH__CFG_EPD_TIMEOUT_MAXIMUM, str_name);

	str_name.Format("CFG.DELAY.TIME");
	STD__ADD_ANALOG(str_name, "sec", 1, 0, 3600);
	LINK__VAR_ANALOG_CTRL(aCH__CFG_DELAY_TIME, str_name);

	//
	str_name.Format("CFG.PARAMETER.VALUE_TO_CHANGE");
	STD__ADD_STRING(str_name);
	LINK__VAR_STRING_CTRL(sCH__CFG_PARAMETER_VALUE_TO_CHANGE, str_name);

	str_name.Format("CFG.PARAMETER.PERCENT_TO_CHANGE");
	STD__ADD_STRING(str_name);
	LINK__VAR_STRING_CTRL(sCH__CFG_PARAMETER_PERCENT_TO_CHANGE, str_name);

	str_name.Format("CFG.PARAMETER.NORMALIZE_TIME");
	STD__ADD_STRING(str_name);
	LINK__VAR_STRING_CTRL(sCH__CFG_PARAMETER_NORMALIZE_TIME, str_name);

	//
	str_name.Format("CFG.PARAMETER.SLOPE_COUNT");
	STD__ADD_STRING(str_name);
	LINK__VAR_STRING_CTRL(sCH__CFG_PARAMETER_SLOPE_COUNT, str_name);

	str_name.Format("CFG.PARAMETER.SLOPE_DIRECTION");
	STD__ADD_STRING(str_name);
	LINK__VAR_STRING_CTRL(sCH__CFG_PARAMETER_SLOPE_DIRECTION, str_name);

	str_name.Format("CFG.PARAMETER.VALIDATION_TIME");
	STD__ADD_STRING(str_name);
	LINK__VAR_STRING_CTRL(sCH__CFG_PARAMETER_VALIDATION_TIME, str_name);

	// INFO ...
	{
		str_name = "INFO.EPD.START.FLAG";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH_INFO__EPD_START_FLAG,str_name);

		str_name = "INFO.CUR.SEQ_MSG";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH_INFO__CUR_SEQ_MSG,str_name);

		str_name = "INFO.CUR.DELAY_TIME_COUNT";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH_INFO__CUR_DELAY_TIME_COUNT,str_name);

		str_name = "INFO.CUR.NORMALIZE_TIME_COUNT";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH_INFO__CUR_NORMALIZE_TIME_COUNT,str_name);

		str_name = "INFO.CUR.EPD_TIME_COUNT";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH_INFO__CUR_EPD_TIME_COUNT,str_name);

		str_name = "INFO.CUR.NORMALIZE_VALUE";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH_INFO__CUR_NORMALIZE_VALUE,str_name);

		str_name = "INFO.CUR.THRESHOLD_VALUE";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH_INFO__CUR_THRESHOLD_VALUE,str_name);

		str_name = "INFO.CUR.CAL_SLOPE_COUNT";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH_INFO__CUR_CAL_SLOPE_COUNT,str_name);

		str_name = "INFO.CUR.IBx_LIST";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH_INFO__CUR_IBx_LIST,str_name);

		str_name = "INFO.CUR.IBx_DATA";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH_INFO__CUR_IBx_DATA,str_name);

		str_name = "INFO.CUR.EPD_START_SEC";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH_INFO__CUR_EPD_START_SEC,str_name);
	}

	// EPD Input Data
	{
		str_name.Format("EPD.EXCEPTION.REQ");
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__EPD_EXCEPTION_REQ, str_name);		
	}

	return 1;
}

int CObj__EPD_STD::__DEFINE__ALARM(p_alarm)
{
	DECLARE__ALARM;

	// ...
	CString title;
	title.Format("%s - ",sObject_Name);
	
	// ...
 	CString alarm_title;
 	CString alarm_msg;
 	CStringArray l_act;
 	int alarm_id;

	// ...
	{
		alarm_id = ALID__EPD_DETECT_MAX_TIMEOUT;

		alarm_title += "EPD Detect Maximum Timeout !";
		alarm_msg   = "";

		l_act.RemoveAll();
		l_act.Add("CHECK");

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}
	// ...
	{
		alarm_id = ALID__EPD_DETECT_UNKNOWN_SLOPE_DIRECTION;

		alarm_title += "EPD Detect : Unknown Slope Direction !";
		alarm_msg   = "";

		l_act.RemoveAll();
		l_act.Add("CHECK");

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}
	// ...
	{
		alarm_id = ALID__EPD_DETECT_MIN_TIMEOUT;
		
		alarm_title += "EPD Detect : Minimum Timeout !";
		alarm_msg   = "";
		
		l_act.RemoveAll();
		l_act.Add("CHECK");
		
		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	return 1;
}


//-------------------------------------------------------------------------
int CObj__EPD_STD::__INITIALIZE__OBJECT(p_variable,p_ext_obj_create)
{	
	// ...
	{
		CString file_name;
		CString log_msg;

		file_name.Format("%s_App.log", sObject_Name);

		log_msg  = "\n\n";
		log_msg += "//------------------------------------------------------------------------";

		xLOG_CTRL->CREATE__SUB_DIRECTORY(sObject_Name);
		xLOG_CTRL->SET__PROPERTY(file_name,12*1,60);

		xLOG_CTRL->DISABLE__TIME_LOG();
		xLOG_CTRL->WRITE__LOG(log_msg);
		
		xLOG_CTRL->ENABLE__TIME_LOG();
		xLOG_CTRL->WRITE__LOG("   START   \n");
	}

	// ...
	CString str_name;
	CString def_name;
	CString def_value;
	CString obj_name;
	int i;

	// OBJ__OES ...
	{
		def_name = "OBJ__OES";
		p_variable->Get__DEF_CONST_DATA(def_name, obj_name);

		pOBJ__OES_CTRL = p_ext_obj_create->Create__OBJECT_CTRL(obj_name);

		// ...
		{
			def_name.Format("VAR__EPD_SIGNAL");
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name, def_value);
			
			LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__EPD_SIGNAL, obj_name, def_value);
		}

		for(i=0; i<MAX__IBx_SPEC_DATA; i++)
		{
			int id = i + 1;

			def_name.Format("VAR__SPEC_IB.%01d", id);
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name, def_value);

			LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__IBx_SPEC_DATA[i], obj_name, def_value);
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
int CObj__EPD_STD::__CALL__CONTROL_MODE(mode,p_debug,p_variable,p_alarm)
{
	int flag = -1;

	// ...
	{
		CString log_msg;
		log_msg.Format("Start ... :  [%s]",mode);

		sCH__OBJ_MSG->Set__DATA(log_msg);
		xLOG_CTRL->WRITE__LOG(log_msg);
	}

	try
	{
		sCH__EPD_EXCEPTION_REQ->Set__DATA("");

		IF__CTRL_MODE(sMODE__INIT)
		{
			flag = Call__INIT(p_variable, p_alarm);
		}
		ELSE_IF__CTRL_MODE(sMODE__EPD_DETECT)
		{
			SCX__ASYNC_TIMER_CTRL x_async_timer;
			CString str_data;

			x_async_timer->REGISTER__COUNT_CHANNEL_NAME(sCH_INFO__CUR_EPD_START_SEC->Get__CHANNEL_NAME());
			
			x_async_timer->Set__START_TIME(0.0);
			sCH_INFO__CUR_EPD_START_SEC->Set__DATA("0.0");
			
			x_async_timer->START__COUNT_UP(99999.0);

			// ...
			{
				sCH_INFO__EPD_START_FLAG->Set__DATA(STR__START);

				flag = Call__EPD_DETECT(p_variable, p_alarm);

				sCH_INFO__EPD_START_FLAG->Set__DATA(STR__STOP);
			}
		}
		else									
		{
			CString log_msg;
			log_msg.Format("Invalid Mode: [%s]", mode);

			flag = -1;
		}
	}
	catch(int err_flag)
	{
		flag = err_flag;

		sCH_INFO__EPD_START_FLAG->Set__DATA(STR__STOP);
	}

	if((flag < 0)||(p_variable->Check__CTRL_ABORT() > 0))
	{
		CString log_msg;
		log_msg.Format("Aborted ... :  [%s]",mode);

		sCH__OBJ_MSG->Set__DATA(log_msg);
		xLOG_CTRL->WRITE__LOG(log_msg);		
	}
	else
	{
		CString log_msg;
		log_msg.Format("Completed ... :  [%s]",mode);

		sCH__OBJ_MSG->Set__DATA(log_msg);
		xLOG_CTRL->WRITE__LOG(log_msg);
	}

	return flag;
}

int CObj__EPD_STD::__CALL__MONITORING(id,p_variable,p_alarm)
{

	return 1;
}
