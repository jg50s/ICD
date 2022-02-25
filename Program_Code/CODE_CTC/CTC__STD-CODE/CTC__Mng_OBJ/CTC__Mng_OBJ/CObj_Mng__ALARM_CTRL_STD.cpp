#include "StdAfx.h"
#include "CObj_Mng__ALARM_CTRL_STD.h"


//-------------------------------------------------------------------------
CObj_Mng__ALARM_CTRL_STD::CObj_Mng__ALARM_CTRL_STD()
{

}
CObj_Mng__ALARM_CTRL_STD::~CObj_Mng__ALARM_CTRL_STD()
{

}

//-------------------------------------------------------------------------
int CObj_Mng__ALARM_CTRL_STD::__DEFINE__CONTROL_MODE(obj,l_mode)
{
	sObject_Name = obj;

	// ...
	{
		ADD__CTRL_VAR(sMODE__CHECK_CURRENT_ALARM, "CHECK.CURRENT_ALARM");
	}
	return 1;
}
int CObj_Mng__ALARM_CTRL_STD::__DEFINE__VERSION_HISTORY(version)
{

	return 1;
}


// ...
#define MON_ID__ALARM_CTRL				1

// ...
#define DSP__NO_YES						"NO   YES" 
#define DSP__OFF_ON						"OFF  ON" 
#define MODE__ENABLE_DISABLE			"ENABLE  DISABLE"
#define MODE__DISABLE_ENABLE			"DISABLE  ENABLE"


int CObj_Mng__ALARM_CTRL_STD::__DEFINE__VARIABLE_STD(p_variable)
{
	DECLARE__STD_VARIABLE;

	// ...
	CString str_name;
	int i;

	// ...
	{
		str_name = "CUR.DAY";
		STD__ADD_STRING_WITH_X_OPTION(str_name, "");
		LINK__VAR_STRING_CTRL(sCH__CUR_DAY, str_name);
	}

	// STATUS ...
	{
		str_name = "OBJ.MSG";
		STD__ADD_STRING_WITH_COMMENT(str_name,"");
		LINK__VAR_STRING_CTRL(xCH__OBJ_MSG,str_name);

		str_name = "ALARM.FLAG";		
		STD__ADD_DIGITAL_WITH_COMMENT(str_name,DSP__NO_YES,"");
		LINK__VAR_DIGITAL_CTRL(xCH__ALARM_FLAG,str_name);

		str_name = "ALARM.BUZZER";		
		STD__ADD_DIGITAL_WITH_COMMENT(str_name,DSP__OFF_ON,"");
		LINK__VAR_DIGITAL_CTRL(xCH__ALARM_BUZZER,str_name);

		str_name = "LAST.ALARM.MSG";
		STD__ADD_STRING_WITH_COMMENT(str_name,"");
		LINK__VAR_STRING_CTRL(xCH__LAST_ALARM_MSG,str_name);

		for(i=0;i<MODULE_SIZE;i++)
		{
			str_name.Format("SEQ%1d.ALARM_FLAG", i);
			STD__ADD_STRING_WITH_COMMENT(str_name, "");
			LINK__VAR_STRING_CTRL(xCH__MODULE_ALARM_FLAG[i], str_name);

			//
			str_name.Format("1th.SEQ%1d.ALARM_COUNT", i);
			STD__ADD_STRING_WITH_X_OPTION(str_name, "");
			LINK__VAR_STRING_CTRL(xCH__1th_MODULE_ALARM_COUNT[i], str_name);

			str_name.Format("2th.SEQ%1d.ALARM_COUNT", i);
			STD__ADD_STRING_WITH_X_OPTION(str_name, "");
			LINK__VAR_STRING_CTRL(xCH__2th_MODULE_ALARM_COUNT[i], str_name);

			str_name.Format("3th.SEQ%1d.ALARM_COUNT", i);
			STD__ADD_STRING_WITH_X_OPTION(str_name, "");
			LINK__VAR_STRING_CTRL(xCH__3th_MODULE_ALARM_COUNT[i], str_name);
		}

		// Total Count ...
		{
			str_name = "1th.SYSTEM.ALARM_COUNT";
			STD__ADD_STRING_WITH_X_OPTION(str_name, "");
			LINK__VAR_STRING_CTRL(xCH__1th_SYSTEM_ALARM_COUNT, str_name);
			
			str_name = "2th.SYSTEM.ALARM_COUNT";
			STD__ADD_STRING_WITH_X_OPTION(str_name, "");
			LINK__VAR_STRING_CTRL(xCH__2th_SYSTEM_ALARM_COUNT, str_name);

			str_name = "3th.SYSTEM.ALARM_COUNT";
			STD__ADD_STRING_WITH_X_OPTION(str_name, "");
			LINK__VAR_STRING_CTRL(xCH__3th_SYSTEM_ALARM_COUNT, str_name);
		}

		// ...
		{
			str_name = "POST.ALARM.COUNT";
			STD__ADD_STRING_WITH_COMMENT(str_name,"");
			LINK__VAR_STRING_CTRL(xCH__POST_ALARM_COUNT,str_name);

			str_name = "POST.ALARM.ID";
			STD__ADD_STRING_WITH_COMMENT(str_name,"");
			LINK__VAR_STRING_CTRL(xCH__POST_ALARM_ID,str_name);

			str_name = "POST.ALARM.TEXT";
			STD__ADD_STRING_WITH_COMMENT(str_name,"");
			LINK__VAR_STRING_CTRL(xCH__POST_ALARM_TEXT,str_name);

			//
			str_name = "ALARM_FILE.UPLOAD_REQ";
			STD__ADD_STRING_WITH_COMMENT(str_name,"");
			LINK__VAR_STRING_CTRL(xCH__ALARM_FILE_UPLOAD_REQ,str_name);

			str_name = "ALARM_FILE.DB_CHECK.FLAG";
			STD__ADD_STRING_WITH_COMMENT(str_name,"");
			LINK__VAR_STRING_CTRL(xCH__ALARM_FILE_DB_CHECK_FLAG,str_name);
		}

		for(i=0;i<MODULE_SIZE;i++)
		{
			if(i == 0)
			{
				str_name = "TMC.ALARM.POST.SIZE";
			}
			else
			{
				str_name.Format("PM%1d.ALARM.POST.SIZE",i);
			}
		}
	}

	// CONFIG ...
	{
		str_name = "CFG.ALM_WARNING.LIGHT_RED.APPLY_MODE";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name,MODE__ENABLE_DISABLE,"");
		LINK__VAR_DIGITAL_CTRL(xCH__CFG_ALM_WARNING_LIGHT_RED_APPLY_MODE,str_name);

		str_name = "CFG.MSG.BOX.BUZZER.MODE";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name, MODE__ENABLE_DISABLE,"");
		LINK__VAR_DIGITAL_CTRL(xCH__CFG_MSG_BOX_BUZZER_MODE,str_name);

		//
		str_name = "CFG.FA_REPORT.WITH.LEVEL_HEAVY";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name, MODE__ENABLE_DISABLE,"");
		LINK__VAR_DIGITAL_CTRL(dCH__CFG_FA_REPORT_WITH_LEVEL_HEAVY, str_name);
		
		str_name = "CFG.FA_REPORT.WITH.LEVEL_LIGHT";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name, MODE__ENABLE_DISABLE,"");
		LINK__VAR_DIGITAL_CTRL(dCH__CFG_FA_REPORT_WITH_LEVEL_LIGHT, str_name);
		
		str_name = "CFG.FA_REPORT.WITH.LEVEL_WARNING";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name, MODE__ENABLE_DISABLE,"");
		LINK__VAR_DIGITAL_CTRL(dCH__CFG_FA_REPORT_WITH_LEVEL_WARNING, str_name);

		//
		str_name = "CFG.ALARM.POSTED_DB.CHECK";
		STD__ADD_DIGITAL_WITH_COMMENT(str_name,MODE__DISABLE_ENABLE,"");
		LINK__VAR_DIGITAL_CTRL(xCH__CFG_ALARM_POSTED_DB_CHECK,str_name);
	}

	// ...
	{
		p_variable->Add__MONITORING_PROC(1.0,MON_ID__ALARM_CTRL);
	}
	return 1;
}

int CObj_Mng__ALARM_CTRL_STD::__DEFINE__ALARM(p_alarm)
{
	DECLARE__ALARM;

	// ...
	CString title;
	title.Format("%s - ",sObject_Name);

	CString alarm_title;
	CString alarm_msg;
	CStringArray l_act;
	
	// ...
	{
		alarm_title  = title;
		alarm_title += "OBJECT MODE : UNKNOWN";

		alarm_msg = "";

		l_act.RemoveAll();
		l_act.Add("ABORT");
	
		ADD__ALARM_EX(ALID__OBJECT_MODE_UNKNOWN,alarm_title,alarm_msg,l_act);
	}
	return 1;
}


//-------------------------------------------------------------------------
int CObj_Mng__ALARM_CTRL_STD::__INITIALIZE__OBJECT(p_variable,p_ext_obj_create)
{
	p_ext_obj_create->Link__DEF_VARIABLE__ERROR_FEEDBACK(&mERROR__DEF_VAR);

	// ...
	{
		xSCH_MATERIAL_CTRL->Create__SERVICE_DB("");
		xSCH_MATERIAL_CTRL->Link__SERVICE_DB("");
	}

	return 1;
}


//-------------------------------------------------------------------------
int CObj_Mng__ALARM_CTRL_STD::__CALL__CONTROL_MODE(mode,p_debug,p_variable,p_alarm)
{
	int flag = -1;

	// ...
	IF__CTRL_MODE(sMODE__CHECK_CURRENT_ALARM)			flag = Call__CHECK_CURRENT_ALARM(p_variable,p_alarm);

	else
	{
		CString bff;
		CString alarm_msg;
		CString r_act;

		bff.Format("Object Name : %s\n",sObject_Name);
		alarm_msg  = bff;
		bff.Format("Unknown Object Mode : \"%s\"\n",mode);
		alarm_msg += bff;

		p_alarm->Popup__ALARM_With_MESSAGE(ALID__OBJECT_MODE_UNKNOWN,alarm_msg,r_act);
	}

	return flag;
}
int CObj_Mng__ALARM_CTRL_STD::__CALL__MONITORING(id,p_variable,p_alarm)
{
	switch(id)
	{
		case MON_ID__ALARM_CTRL:
			Mon__ALARM_CTRL(p_variable);
			break;
	}

	return 1;
}
