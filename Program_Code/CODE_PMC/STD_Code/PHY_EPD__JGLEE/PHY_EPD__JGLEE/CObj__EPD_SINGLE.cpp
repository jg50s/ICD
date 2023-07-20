#include "StdAfx.h"
#include "CObj__EPD_SINGLE.h"



//-------------------------------------------------------------------------
CObj__EPD_SINGLE::CObj__EPD_SINGLE()
{

}
CObj__EPD_SINGLE::~CObj__EPD_SINGLE()
{

}


//-------------------------------------------------------------------------
int CObj__EPD_SINGLE::__DEFINE__CONTROL_MODE(obj,l_mode)
{
	sObject_Name = obj;

	// ...
	{
		ADD__CTRL_VAR(sMODE__INIT, "INIT");
		ADD__CTRL_VAR(sMODE__IDLE, "IDLE");

		ADD__CTRL_VAR(sMODE__EPD_DETECT,  "EPD.DETECT");
		ADD__CTRL_VAR(sMODE__ERROR_CHECK, "ERROR.CHECK");

		ADD__CTRL_VAR(sMODE__EPD_TEST, "EPD.TEST");
	}
	return 1;
}
int CObj__EPD_SINGLE::__DEFINE__VERSION_HISTORY(version)
{

	return 1;
}


// ...
#define MON_ID__EPD_CHART					1
#define MON_ID__ERROR_CHECK					2

// ...
#define  APP_DSP__EPD_MODE					\
"OverValue.Check							\
UnderValue.Check							\
OverValue.Slope								\
UnderValue.Slope							\
ValueChange									\
PercentChange								\
ValueSlope									\
PercentSlope"


int CObj__EPD_SINGLE::__DEFINE__VARIABLE_STD(p_variable)
{
	DECLARE__STD_VARIABLE;

	// ...
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

	// PARA ...
	{
		str_name = "PARA.EPD.MODE";
		STD__ADD_DIGITAL(str_name, APP_DSP__EPD_MODE);
		LINK__VAR_DIGITAL_CTRL(dCH__PARA_EPD_MODE, str_name);

		//
		str_name = "PARA.VALUE_TO_CHANGE";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__PARA_VALUE_TO_CHANGE, str_name);

		str_name = "PARA.PERCENT_TO_CHANGE";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__PARA_PERCENT_TO_CHANGE, str_name);

		//
		str_name = "PARA.DELAY.TIME";
		STD__ADD_ANALOG(str_name, "sec", 1, 0, 3600);
		LINK__VAR_ANALOG_CTRL(aCH__PARA_DELAY_TIME, str_name);

		str_name = "PARA.NORMALIZE_TIME";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__PARA_NORMALIZE_TIME, str_name);

		//
		str_name = "PARA.EPD.TIMEOUT.MINIMUM";
		STD__ADD_ANALOG(str_name, "sec", 3, 1, 3600);
		LINK__VAR_ANALOG_CTRL(aCH__PARA_EPD_TIMEOUT_MINIMUM, str_name);

		str_name = "PARA.EPD.TIMEOUT.MAXIMUM";
		STD__ADD_ANALOG(str_name, "sec", 3, 1, 3600);
		LINK__VAR_ANALOG_CTRL(aCH__PARA_EPD_TIMEOUT_MAXIMUM, str_name);

		//
		str_name = "PARA.EPD.THRESHOLD.MIN";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__PARA_EPD_THRESHOLD_MIN, str_name);

		str_name = "PARA.EPD.THRESHOLD.MAX";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__PARA_EPD_THRESHOLD_MAX, str_name);

		//
		str_name = "PARA.SLOPE_COUNT";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__PARA_SLOPE_COUNT, str_name);

		str_name = "PARA.SLOPE_DIRECTION";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__PARA_SLOPE_DIRECTION, str_name);

		str_name = "PARA.VALID_TIME";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__PARA_VALID_TIME, str_name);
	}

	// INFO ...
	{
		str_name = "INFO.EPD.START.FLAG";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH_INFO__EPD_START_FLAG, str_name);

		str_name = "INFO.EPD.CHECK.ACTIVE";
		STD__ADD_DIGITAL(str_name, "OFF  ON");
		LINK__VAR_DIGITAL_CTRL(dCH_INFO__EPD_CHECK_ACTIVE, str_name);

		//
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

	// CFG : SYSTEM ...
	{
		str_name = "CFG.USE";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name, "YES NO", "");
		LINK__VAR_DIGITAL_CTRL(dCH__CFG_USE, str_name);

		//
		str_name = "CFG.INTENSITY.MIN.VALUE";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "intensity", 1, 0, 1, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_INTENSITY_MIN_VALUE, str_name);

		str_name = "CFG.INTENSITY.MAX.VALUE";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "intensity", 1, 1, 10000, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_INTENSITY_MAX_VALUE, str_name);

		str_name = "INFO.INTENSITY.MAX.MINUS";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__INFO_INTENSITY_MAX_MINUS, str_name);

		str_name = "CFG.INTENSITY.DEC.VALUE";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "dec", 0, 0, 5, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_INTENSITY_DEC_VALUE, str_name);

		//
		str_name = "CFG.INTENSITY.STABLE.DELAY.TIME";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "sec", 0, 0, 3600, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_INTENSITY_STABLE_DELAY_TIME, str_name);

		str_name = "CFG.INTENSITY.STABLE.CHECK.TIME";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "sec", 1, 0, 10, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_INTENSITY_STABLE_CHECK_TIME, str_name);

		//
		str_name = "CFG.INTENSITY.ERROR.TIMEOUT";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "sec", 0, 0, 3600, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_INTENSITY_ERROR_TIMEOUT, str_name);
	}

	// MON : STABLE_IDLE ...
	{
		str_name = "MON.PART.ERROR.ACTIVE";
		STD__ADD_DIGITAL(str_name, "OFF ON");
		LINK__VAR_DIGITAL_CTRL(dCH__MON_PART_ERROR_ACTIVE, str_name);

		//
		str_name = "MON.IDLE.INTENSITY.CHECK.ACTIVE";
		STD__ADD_DIGITAL(str_name, "OFF ON READY");
		LINK__VAR_DIGITAL_CTRL(dCH__MON_IDLE_INTENSITY_CHECK_ACTIVE, str_name);

		str_name = "MON.IDLE.INTENSITY.STABLE.ACTIVE";
		STD__ADD_DIGITAL(str_name, "OFF ON");
		LINK__VAR_DIGITAL_CTRL(dCH__MON_IDLE_INTENSITY_STABLE_ACTIVE, str_name);

		str_name = "MON.IDLE.INTENSITY.ERROR.ACTIVE";
		STD__ADD_DIGITAL(str_name, "OFF ON");
		LINK__VAR_DIGITAL_CTRL(dCH__MON_IDLE_INTENSITY_ERROR_ACTIVE, str_name);

		//
		str_name = "MON.IDLE.INTENSITY.STABLE.DELAY.TIME";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_IDLE_INTENSITY_STABLE_DELAY_TIME, str_name);

		//
		str_name = "MON.IDLE.INTENSITY.STABLE.MIN";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_IDLE_INTENSITY_STABLE_MIN, str_name);

		str_name = "MON.IDLE.INTENSITY.STABLE.MAX";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_IDLE_INTENSITY_STABLE_MAX, str_name);

		//
		str_name = "MON.IDLE.INTENSITY.STABLE.CHECK.TIME";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_IDLE_INTENSITY_STABLE_CHECK_TIME, str_name);

		str_name = "MON.IDLE.INTENSITY.ERROR.CHECK.TIME";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_IDLE_INTENSITY_ERROR_CHECK_TIME, str_name);
	}

	// CHART ...
	{
		str_name = "CHART.DATE_TIME";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__CHART_DATE_TIME, str_name);

		str_name = "CHART.TIME_COUNT";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__CHART_TIME_COUNT, str_name);

		str_name = "CHART.TEST.INFO";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__CHART_TEST_INFO, str_name);

		// ...
		str_name = "CHART.EPD";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__CHART_EPD, str_name);
		
		for(int i=0; i<_CFG__CHART_INTENSITY; i++)
		{
			int id = i + 1;

			str_name.Format("CHART.INTENSITY.%1d", id);
			STD__ADD_STRING(str_name);
			LINK__VAR_STRING_CTRL(sCH__CHART_INTENSITY_X[i], str_name);
		}

		// ...
		str_name = "REPORT.EPD.RESULT";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__REPORT_EPD_RESULT, str_name);

		str_name = "REPORT.EPD.SEC";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__REPORT_EPD_SEC, str_name);
	}

	// EPD.EXCEPTION.REQ ...
	{
		str_name = "EPD.EXCEPTION.REQ";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__EPD_EXCEPTION_REQ, str_name);		
	}

	// ...
	{
		p_variable->Add__MONITORING_PROC(1.0, MON_ID__EPD_CHART);
		p_variable->Add__MONITORING_PROC(1.0, MON_ID__ERROR_CHECK);
	}
	return 1;
}

int CObj__EPD_SINGLE::__DEFINE__ALARM(p_alarm)
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

	iLIST_ALID__EPD.RemoveAll();

	// ...
	{
		alarm_id = ALID__EPD_DETECT_MAX_TIMEOUT;
		iLIST_ALID__EPD.Add(alarm_id);

		alarm_title  = title;
		alarm_title += "EPD Detect Maximum Timeout !";

		alarm_msg = "";

		l_act.RemoveAll();
		l_act.Add("CHECK");

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}
	// ...
	{
		alarm_id = ALID__EPD_DETECT_UNKNOWN_SLOPE_DIRECTION;
		iLIST_ALID__EPD.Add(alarm_id);

		alarm_title  = title;
		alarm_title += "EPD Detect : Unknown Slope Direction !";

		alarm_msg = "";

		l_act.RemoveAll();
		l_act.Add("CHECK");

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}
	// ...
	{
		alarm_id = ALID__EPD_DETECT_MIN_TIMEOUT;
		iLIST_ALID__EPD.Add(alarm_id);

		alarm_title  = title;
		alarm_title += "EPD Detect : Minimum Timeout !";

		alarm_msg = "";

		l_act.RemoveAll();
		l_act.Add("CHECK");

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	// ...
	{
		alarm_id = ALID__EPD_ERROR_RANGE;
		iLIST_ALID__EPD.Add(alarm_id);

		alarm_title  = title;
		alarm_title += "EPD Error Range !";

		alarm_msg = "Please, check the state of EPD ! \n";

		l_act.RemoveAll();
		l_act.Add("CHECK");

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	return 1;
}


//-------------------------------------------------------------------------
int CObj__EPD_SINGLE::__INITIALIZE__OBJECT(p_variable,p_ext_obj_create)
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
	CString def_name;
	CString def_data;

	CString ch_name;
	CString obj_name;
	CString var_name;

	// EPD.SIGNAL ...
	{
		bActive__EPD_SIGNAL_MAIN = false;

		def_name = "SIZE.EPD_SIGNAL";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, def_data);

		iSIZE__EPD_SIGNAL = atoi(def_data);
		if(iSIZE__EPD_SIGNAL > _CFG__CHART_INTENSITY)			iSIZE__EPD_SIGNAL = _CFG__CHART_INTENSITY;

		for(int i=0; i<iSIZE__EPD_SIGNAL; i++)
		{
			int id = i + 1;

			def_name.Format("CH.EPD_SIGNAL.%1d", id);
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
			p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);

			LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__EPD_SIGNAL_X[i], obj_name,var_name);
			
			if(i == 0)
			{
				bActive__EPD_SIGNAL_MAIN = true;
				LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__EPD_SIGNAL_MAIN, obj_name,var_name);
			}
		}
	}

	// LINK.EPD_CHART ...
	{
		mEPD_CHART.Link__EPD_CHANNEL(sCH__CHART_EPD, dCH_INFO__EPD_CHECK_ACTIVE);

		for(int i=0; i<iSIZE__EPD_SIGNAL; i++)
		{
			mEPD_CHART.Link__INTENSITY_CHANNEL(i, sCH__CHART_INTENSITY_X[i], aEXT_CH__EPD_SIGNAL_X[i]);
		}

		mEPD_CHART.Link__REPORT_CHANNEL(sCH__REPORT_EPD_RESULT, sCH__REPORT_EPD_SEC);
	}

	// ...
	{
		SCX__SEQ_INFO x_seq_info;

		iActive__SIM_MODE = x_seq_info->Is__SIMULATION_MODE();
	}
	return 1;
}


//-------------------------------------------------------------------------
int CObj__EPD_SINGLE::__CALL__CONTROL_MODE(mode,p_debug,p_variable,p_alarm)
{
	DECLARE__EXT_CTRL(p_variable);

	int flag = -1;
	CString ch_data;

	// ...
	{
		CString log_msg;
		log_msg.Format("Start [%s] ... By %s \n", mode, p_ext_mode_ctrl->Get__UPPER_OBJECT_NAME());

		sCH__OBJ_MSG->Set__DATA(log_msg);
		xLOG_CTRL->WRITE__LOG(log_msg);
	}

	// ...
	{
		dCH__MON_IDLE_INTENSITY_STABLE_ACTIVE->Set__DATA(STR__OFF);	
		dCH__MON_IDLE_INTENSITY_ERROR_ACTIVE->Set__DATA(STR__OFF);
	}

	try
	{
		sCH__EPD_EXCEPTION_REQ->Set__DATA("");

		IF__CTRL_MODE(sMODE__INIT)
		{
			dCH__MON_IDLE_INTENSITY_CHECK_ACTIVE->Set__DATA(STR__OFF);

			flag = Call__INIT(p_variable, p_alarm);
		}
		ELSE_IF__CTRL_MODE(sMODE__IDLE)
		{
			flag = 1;

			// ...
			{
				sCH__MON_IDLE_INTENSITY_STABLE_MIN->Set__DATA("0");
				sCH__MON_IDLE_INTENSITY_STABLE_MAX->Set__DATA("0");

				dCH__MON_IDLE_INTENSITY_CHECK_ACTIVE->Set__DATA(STR__OFF);
			}
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
				ch_data = sCH__PARA_EPD_THRESHOLD_MIN->Get__STRING();
				sCH__MON_IDLE_INTENSITY_STABLE_MIN->Set__DATA(ch_data);

				ch_data = sCH__PARA_EPD_THRESHOLD_MAX->Get__STRING();
				sCH__MON_IDLE_INTENSITY_STABLE_MAX->Set__DATA(ch_data);

				//
				dCH__MON_IDLE_INTENSITY_CHECK_ACTIVE->Set__DATA(STR__OFF);
			}

			// ...
			{
				dCH_INFO__EPD_CHECK_ACTIVE->Set__DATA(STR__OFF);
				sCH_INFO__EPD_START_FLAG->Set__DATA(STR__START);

				flag = Call__EPD_DETECT(p_variable, p_alarm);

				if(flag > 0)		dCH_INFO__EPD_CHECK_ACTIVE->Set__DATA(STR__ON);
				sCH_INFO__EPD_START_FLAG->Set__DATA(STR__STOP);
			}

			if(flag > 0)
			{
				ch_data = sCH__PARA_EPD_THRESHOLD_MIN->Get__STRING();
				sCH__MON_IDLE_INTENSITY_STABLE_MIN->Set__DATA(ch_data);

				ch_data = sCH__PARA_EPD_THRESHOLD_MAX->Get__STRING();
				sCH__MON_IDLE_INTENSITY_STABLE_MAX->Set__DATA(ch_data);

				//
				dCH__MON_IDLE_INTENSITY_CHECK_ACTIVE->Set__DATA(STR__READY);
			}
			else
			{
				sCH__MON_IDLE_INTENSITY_STABLE_MIN->Set__DATA("0");
				sCH__MON_IDLE_INTENSITY_STABLE_MAX->Set__DATA("0");

				dCH__MON_IDLE_INTENSITY_CHECK_ACTIVE->Set__DATA(STR__OFF);
			}
		}
		ELSE_IF__CTRL_MODE(sMODE__ERROR_CHECK)
		{
			flag = 1;

			// ...
			{
				ch_data = sCH__PARA_EPD_THRESHOLD_MIN->Get__STRING();
				sCH__MON_IDLE_INTENSITY_STABLE_MIN->Set__DATA(ch_data);

				ch_data = sCH__PARA_EPD_THRESHOLD_MAX->Get__STRING();
				sCH__MON_IDLE_INTENSITY_STABLE_MAX->Set__DATA(ch_data);

				//
				if(dCH__MON_IDLE_INTENSITY_CHECK_ACTIVE->Check__DATA(STR__ON) < 0)
					dCH__MON_IDLE_INTENSITY_CHECK_ACTIVE->Set__DATA(STR__READY);
			}
		}
		ELSE_IF__CTRL_MODE(sMODE__EPD_TEST)
		{
			dCH_INFO__EPD_CHECK_ACTIVE->Set__DATA(STR__OFF);

			flag = Call__EPD_TEST(p_variable, p_alarm);
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

int CObj__EPD_SINGLE::__CALL__MONITORING(id,p_variable,p_alarm)
{
	if(id == MON_ID__EPD_CHART)			Mon__EPD_CHART(p_variable, p_alarm);
	if(id == MON_ID__ERROR_CHECK)		Mon__ERROR_CHECK(p_variable, p_alarm);

	return 1;
}
