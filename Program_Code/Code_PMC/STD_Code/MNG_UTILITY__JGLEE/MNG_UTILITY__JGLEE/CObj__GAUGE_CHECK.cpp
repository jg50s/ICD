#include "StdAfx.h"
#include "CObj__GAUGE_CHECK.h"



//-------------------------------------------------------------------------
CObj__GAUGE_CHECK::CObj__GAUGE_CHECK()
{

}
CObj__GAUGE_CHECK::~CObj__GAUGE_CHECK()
{

}


//-------------------------------------------------------------------------
int CObj__GAUGE_CHECK::__DEFINE__CONTROL_MODE(obj,l_mode)
{
	sObject_Name = obj;

	// ...
	{
		ADD__CTRL_VAR(sMODE__ALL_CHECK,          "ALL.CHECK");
		ADD__CTRL_VAR(sMODE__LOW_PRESSURE_CHECK, "LOW_PRESSURE.CHECK");
		ADD__CTRL_VAR(sMODE__LINEAR_CHECK,       "LINEAR.CHECK");
	}
	return 1;
}
int CObj__GAUGE_CHECK::__DEFINE__VERSION_HISTORY(version)
{

	return 1;
}


// ...
#define APP_DSP__GAS_TYPE				\
"GAS01 GAS02 GAS03 GAS04 GAS05			\
GAS06 GAS07 GAS08 GAS09 GAS10"

#define  MON_ID__STATUS_CTRL			1


int CObj__GAUGE_CHECK::__DEFINE__VARIABLE_STD(p_variable)
{
	DECLARE__STD_VARIABLE;

	//-------------------------------------------------------------------------
	CString str_name;
	int i;

	// SYSTEM CHANNEL .....
	{
		str_name = "OBJ.MSG";
		STD__ADD_STRING_WITH_COMMENT(str_name,"");
		LINK__VAR_STRING_CTRL(xCH__OBJ_MSG,str_name);

		str_name = "OBJ.ERROR_MSG";
		STD__ADD_STRING_WITH_COMMENT(str_name,"");
		LINK__VAR_STRING_CTRL(xCH__OBJ_ERROR_MSG,str_name);

		//
		str_name = "APP.AUTO_START_CTRL";
		STD__ADD_STRING_WITH_COMMENT(str_name,"");
		LINK__VAR_STRING_CTRL(xCH__AUTO_START_CTRL,str_name);

		str_name = "RESULT.SAVE.REQ";
		STD__ADD_STRING_WITH_COMMENT(str_name,"");
		LINK__VAR_STRING_CTRL(sCH__RESULT_SAVE_REQ,str_name);

		str_name = "CHECK_TYPE.UPDATE.REQ";
		STD__ADD_STRING_WITH_COMMENT(str_name,"");
		LINK__VAR_STRING_CTRL(sCH__CHECK_TYPE_UPDATE_REQ,str_name);

		str_name = "RESULT.ERROR_RANGE.CHECK.REQ";
		STD__ADD_STRING_WITH_COMMENT(str_name,"");
		LINK__VAR_STRING_CTRL(sCH__RESULT_ERROR_RANGE_CHECK_REQ,str_name);
	}

	// PARAMETER .....
	{
		str_name = "PARA.TEST.GAS.TYPE";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name, APP_DSP__GAS_TYPE, "");
		LINK__VAR_DIGITAL_CTRL(dCH_PARA__TEST_GAS_TYPE, str_name);

		str_name = "PARA.TEST.GAS.FLOW";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "sccm", 0, 0, 10000, "");
		LINK__VAR_ANALOG_CTRL(aCH_PARA__TEST_GAS_FLOW, str_name);

		str_name = "CUR.TEST.GAS.NAME";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__CUR_TEST_GAS_NAME, str_name);

		//
		str_name = "CFG.PRESSURE.STABLE.SEC";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name,"sec", 0, 0, 10000, "");
		LINK__VAR_ANALOG_CTRL(aCH_CFG__PRESSURE_STABLE_SEC, str_name);

		str_name = "CUR.CHECK.TIME.COUNT";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__CUR_CHECK_TIME_COUNT, str_name);

		// 
		str_name = "CFG.CHECK.COUNT";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "count", 0, 1, 10, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_CHECK_COUNT, str_name);

		str_name = "CUR.CHECK.COUNT";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__CUR_CHECK_COUNT, str_name);

		str_name = "CUR.LOW_PRESSURE.COUNT";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__CUR_LOW_PRESSURE_COUNT, str_name);

		//
		str_name = "CFG.UPPER.PRESSURE";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "torr", 1, 1, 10, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_UPPER_PRESSURE, str_name);

		str_name = "CUR.UPPER.PRESSURE";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__CUR_UPPER_PRESSURE, str_name);

		//
		str_name = "TEST.INTERVAL.TIME";
		STD__ADD_STRING_WITH_X_OPTION(str_name, "");
		LINK__VAR_STRING_CTRL(sCH__TEST_INTERVAL_TIME, str_name);

		str_name = "TEST.INTERVAL.CUR";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__TEST_INTERVAL_CUR, str_name);

		//
		str_name = "CFG.CHECK.ERROR.PERCENT";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "%", 1, 0, 100, "");
		LINK__VAR_ANALOG_CTRL(aCH_CFG__CHECK_ERROR_PERCENT, str_name);

		str_name = "CUR.CHECK.ERROR.PERCENT";
		STD__ADD_STRING_WITH_X_OPTION(str_name, "");
		LINK__VAR_STRING_CTRL(sCH__CUR_CHECK_ERROR_PERCENT, str_name);
	}

	// CFG : Check List ...
	{
		for(i=0; i<CFG_GAUGE__TEST_LIST; i++)
		{
			int id = i + 1;

			//
			str_name.Format("TEST.TIME.NEW.%1d", id);
			STD__ADD_STRING_WITH_X_OPTION(str_name, "");
			LINK__VAR_STRING_CTRL(sCH__TEST_TIME_NEW_X[i], str_name);

			str_name.Format("TEST.PRESSURE.NEW.%1d", id);
			STD__ADD_STRING_WITH_X_OPTION(str_name, "");
			LINK__VAR_STRING_CTRL(sCH__TEST_PRESS_NEW_X[i], str_name);

			str_name.Format("TEST.RATE.NEW.%1d", id);
			STD__ADD_STRING_WITH_X_OPTION(str_name, "");
			LINK__VAR_STRING_CTRL(sCH__TEST_RATE_NEW_X[i], str_name);

			//
			str_name.Format("TEST.TIME.REF.%1d", id);
			STD__ADD_STRING_WITH_X_OPTION(str_name, "");
			LINK__VAR_STRING_CTRL(sCH__TEST_TIME_REF_X[i], str_name);

			str_name.Format("TEST.PRESSURE.REF.%1d", id);
			STD__ADD_STRING_WITH_X_OPTION(str_name, "");
			LINK__VAR_STRING_CTRL(sCH__TEST_PRESS_REF_X[i], str_name);

			str_name.Format("TEST.RATE.REF.%1d", id);
			STD__ADD_STRING_WITH_X_OPTION(str_name, "");
			LINK__VAR_STRING_CTRL(sCH__TEST_RATE_REF_X[i], str_name);
		}
	}

	// ...
	{
		str_name = "TEST.LOW_PRESS.MIN.NEW";
		STD__ADD_STRING_WITH_X_OPTION(str_name, "");
		LINK__VAR_STRING_CTRL(sCH__TEST_LOW_PRESS_MIN_NEW, str_name);

		str_name = "TEST.LOW_PRESS.AVG.NEW";
		STD__ADD_STRING_WITH_X_OPTION(str_name, "");
		LINK__VAR_STRING_CTRL(sCH__TEST_LOW_PRESS_AVG_NEW, str_name);

		str_name = "TEST.LOW_PRESS.MAX.NEW";
		STD__ADD_STRING_WITH_X_OPTION(str_name, "");
		LINK__VAR_STRING_CTRL(sCH__TEST_LOW_PRESS_MAX_NEW, str_name);

		//
		str_name = "TEST.LOW_PRESS.MIN.REF";
		STD__ADD_STRING_WITH_X_OPTION(str_name, "");
		LINK__VAR_STRING_CTRL(sCH__TEST_LOW_PRESS_MIN_REF, str_name);

		str_name = "TEST.LOW_PRESS.AVG.REF";
		STD__ADD_STRING_WITH_X_OPTION(str_name, "");
		LINK__VAR_STRING_CTRL(sCH__TEST_LOW_PRESS_AVG_REF, str_name);

		str_name = "TEST.LOW_PRESS.MAX.REF";
		STD__ADD_STRING_WITH_X_OPTION(str_name, "");
		LINK__VAR_STRING_CTRL(sCH__TEST_LOW_PRESS_MAX_REF, str_name);

		//
		str_name = "TEST.LINEAR_CHECK.RESULT.NEW";
		STD__ADD_STRING_WITH_X_OPTION(str_name, "");
		LINK__VAR_STRING_CTRL(sCH__TEST_LINEAR_CHECK_RESULT_NEW, str_name);

		str_name = "TEST.LINEAR_CHECK.RESULT.REF";
		STD__ADD_STRING_WITH_X_OPTION(str_name, "");
		LINK__VAR_STRING_CTRL(sCH__TEST_LINEAR_CHECK_RESULT_REF, str_name);

		str_name = "TEST.LINEAR_CHECK.ERROR.NEW";
		STD__ADD_STRING_WITH_X_OPTION(str_name, "");
		LINK__VAR_STRING_CTRL(sCH__TEST_LINEAR_CHECK_ERROR_NEW, str_name);
	}

	// ...
	{
		str_name = "LAST.TEST.DATE";
		STD__ADD_STRING_WITH_X_OPTION(str_name, "");
		LINK__VAR_STRING_CTRL(sCH__LAST_TEST_DATE, str_name);

		str_name = "LAST.TEST.TIME";
		STD__ADD_STRING_WITH_X_OPTION(str_name, "");
		LINK__VAR_STRING_CTRL(sCH__LAST_TEST_TIME, str_name);
	}

	// ...
	{
		str_name = "RESULT.STRING";
		STD__ADD_STRING_WITH_COMMENT(str_name, "");
		LINK__VAR_STRING_CTRL(sCH__RESULT_STRING, str_name);

		str_name = "REF.STRING";
		STD__ADD_STRING_WITH_COMMENT(str_name, "");
		LINK__VAR_STRING_CTRL(sCH__REF_STRING, str_name);
	}

	// ...
	{
		str_name = "CHECK_TYPE.SAVE.REQ";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__CHECK_TYPE_SAVE_REQ, str_name);
	}

	// ...
	{
		p_variable->Add__MONITORING_PROC(3.0, MON_ID__STATUS_CTRL);
	}
	return 1;
}
int CObj__GAUGE_CHECK::__DEFINE__ALARM(p_alarm)
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
		alarm_id = ALID__OBJECT_MODE_UNKNOWN;

		alarm_title  = title;
		alarm_title += "OBJECT MODE : UNKNOWN";

		alarm_msg = "";

		l_act.RemoveAll();
		l_act.Add("ABORT");

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	// ...
	{
		alarm_id = ALID__FNC_CANNOT_RUN;

		alarm_title  = title;
		alarm_title += "APC Conductance : Utility Program Can't run !";

		alarm_msg = "";

		l_act.RemoveAll();
		l_act.Add("CHECK");

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	// ...
	{
		alarm_id = ALID__VAC_CONDUCTANCE_CHECK_ERROR;

		alarm_title  = title;
		alarm_title += "APC Conductance : Range Error !";

		alarm_msg = "";

		l_act.RemoveAll();
		l_act.Add("CHECK");

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	return 1;
}

int CObj__GAUGE_CHECK::__Define__USER_FUNCTION(CII_DEFINE__FUNCTION *p_fnc_ctrl)
{
	mERROR__USER_FNC.Set__OBJ_NAME(sObject_Name);
	p_fnc_ctrl->Link__ERROR_FEEDBACK(&mERROR__USER_FNC);


	return 1;
}


//-------------------------------------------------------------------------
int CObj__GAUGE_CHECK::__INITIALIZE__OBJECT(p_variable,p_ext_obj_create)
{
	p_ext_obj_create->Link__DEF_VARIABLE__ERROR_FEEDBACK(&mERROR__DEF_VAR);

	// ...
	CString def_name;
	CString def_data;
	CString ch_name;
	CString obj_name;
	CString var_name;

	// CH.CHM.PRESSURE ...
	{
		def_name = "CH.CHM_PRESSURE";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);

		p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name,obj_name,var_name);
		LINK__EXT_VAR_STRING_CTRL(sEXT_CH__CHM_PRESSURE,obj_name,var_name);
	}

	// OBJ - CHM CTRL ...
	{
		def_name = "OBJ.CHM_CTRL";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, obj_name);

		pOBJ_CTRL__CHM = p_ext_obj_create->Create__OBJECT_CTRL(obj_name);
	}

	// OBJ - GAS_VLV ...
	{
		def_name = "OBJ.GAS_VLV";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, obj_name);

		pOBJ_CTRL__GAS_VLV = p_ext_obj_create->Create__OBJECT_CTRL(obj_name);
	}

	// DB - SYS ...
	{
		def_name = "OBJ.DB_SYS";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, obj_name);

		//
		var_name = "SYSTEM.MSG";
		LINK__EXT_VAR_STRING_CTRL(sEXT_CH__SYSTEM_MSG, obj_name,var_name);

		var_name = "FUNCTION.MSG";		
		LINK__EXT_VAR_STRING_CTRL(sEXT_CH__FNC_MSG, obj_name,var_name);
	}

	// SYSTEM CHANNEL ...
	{
		//
		def_name = "CH.FNC.NAME";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name,ch_name);

		p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name,obj_name,var_name);
		LINK__EXT_VAR_STRING_CTRL(sEXT_CH__SYS_FNC_NAME,obj_name,var_name);

		//
		def_name = "CH.FNC.MSG";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name,ch_name);

		p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name,obj_name,var_name);
		LINK__EXT_VAR_STRING_CTRL(sEXT_CH__SYS_FNC_MSG,obj_name,var_name);

		//
		def_name = "CH.FNC.LOCK";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name,ch_name);

		p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name,obj_name,var_name);
		LINK__EXT_VAR_STRING_CTRL(sEXT_CH__SYS_FNC_LOCK,obj_name,var_name);
	}

	// OBJ - MFCx CTRL ...
	{
		def_name = "OBJ.MFC_SIZE";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name,def_data);

		int limit = atoi(def_data);
		int i;

		if(limit > CFG__MFC_SIZE)		limit = CFG__MFC_SIZE;
		iSIZE__OBJ_MFCx = limit;

		for(i=0;i<limit;i++)
		{
			def_name.Format("OBJ.MFC%1d", i+1);
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name,obj_name);

			pOBJ_CTRL__MFC_X[i] = p_ext_obj_create->Create__OBJECT_CTRL(obj_name);

			var_name = "PARA.SET.FLOW";
			LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__MFCx_PARA_SET_FLOW[i], obj_name,var_name);

			var_name = "CFG.GAS.NAME";
			LINK__EXT_VAR_STRING_CTRL(sEXT_CH__MFCx_CFG_GAS_NAME[i], obj_name,var_name);

			var_name = "CFG.MFC.MAX.VALUE";
			LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__MFCx_CFG_GAS_MAX[i], obj_name,var_name);
		}
	}

	// ...
	{
		CString str_result = "";
		CString str_ref    = "";

		CString str_data;
		CString ch_data;

		int i_limit = CFG_GAUGE__TEST_LIST - 1;

		for(int i=0; i<i_limit; i++)
		{
			// New ...
			{
				ch_data = sCH__TEST_RATE_NEW_X[i]->Get__STRING();

				str_data.Format("%1d/%s,", i+1,ch_data);
				str_result += str_data;
			}
			// Ref ...
			{
				ch_data = sCH__TEST_RATE_REF_X[i]->Get__STRING();

				str_data.Format("%1d/%s,", i+1,ch_data);
				str_ref += str_data;
			}
		}

		sCH__RESULT_STRING->Set__DATA(str_result);
		sCH__REF_STRING->Set__DATA(str_ref);
	}

	// ...
	{
		SCX__SEQ_INFO x_seq_info;

		iSIM_MODE = x_seq_info->Is__SIMULATION_MODE();
	}
	return 1;
}


//-------------------------------------------------------------------------
int CObj__GAUGE_CHECK::__CALL__CONTROL_MODE(mode,p_debug,p_variable,p_alarm)
{
	if(sEXT_CH__SYS_FNC_NAME->Check__DATA("") < 0)
	{
		int alarm_id = ALID__FNC_CANNOT_RUN;
		CString alm_msg;
		CString alm_bff;
		CString r_act;
		CString var_data;

		sEXT_CH__SYS_FNC_NAME->Get__DATA(var_data);
		alm_msg.Format("Now, %s is running.\n",var_data);
		alm_bff.Format("Please, after %s is finished, run APC Utility Program.\n",var_data);
		alm_msg += alm_bff;

		p_alarm->Check__ALARM(alarm_id,r_act);
		p_alarm->Post__ALARM_With_MESSAGE(alarm_id,alm_msg);
		return -1;
	}

	// ...
	{
		CString fnc_name;
		CString fnc_msg;

		fnc_name.Format("%s's %s",sObject_Name,mode);
		fnc_msg.Format("%s : Started ...",mode);

		sEXT_CH__SYS_FNC_NAME->Set__DATA(fnc_name);
		sEXT_CH__SYS_FNC_MSG->Set__DATA(fnc_msg);

		sEXT_CH__SYS_FNC_LOCK->Set__DATA("GAUGE");

		sEXT_CH__SYSTEM_MSG->Set__DATA("APC Conductance Check : Started ...");
		sEXT_CH__FNC_MSG->Set__DATA("");
	}

	// ...
	CString log_msg;
	int flag = -1;

	log_msg.Format("%s mode started ...", mode);
	xCH__OBJ_MSG->Set__DATA(log_msg);

	// ...
	{
		IF__CTRL_MODE(sMODE__ALL_CHECK)
		{
			flag = Call__ALL_CHECK(p_variable, p_alarm);
		}
		ELSE_IF__CTRL_MODE(sMODE__LOW_PRESSURE_CHECK)
		{
			flag = Call__LOW_PRESSURE_CHECK(p_variable, p_alarm);
		}
		ELSE_IF__CTRL_MODE(sMODE__LINEAR_CHECK)
		{
			flag = Call__LINEAR_CHECK(p_variable, p_alarm);
		}
	}

	if((flag < 0) || (p_variable->Check__CTRL_ABORT() > 0))
	{
		log_msg.Format("%s mode aborted ...", mode);
		xCH__OBJ_MSG->Set__DATA(log_msg);
	}
	else
	{
		log_msg.Format("%s mode completed ...", mode);
		xCH__OBJ_MSG->Set__DATA(log_msg);
	}

	// ...
	{
		sEXT_CH__SYS_FNC_NAME->Set__DATA("");
		sEXT_CH__SYS_FNC_MSG->Set__DATA("");
		sEXT_CH__SYS_FNC_LOCK->Set__DATA("");

		sEXT_CH__SYSTEM_MSG->Set__DATA("");
		sEXT_CH__FNC_MSG->Set__DATA("");
	}
	return flag;
}
int CObj__GAUGE_CHECK::__CALL__MONITORING(id,p_variable,p_alarm)
{
	if(id == MON_ID__STATUS_CTRL)		Mon__STATUS_CTRL(p_variable,p_alarm);

	return 1;
}
