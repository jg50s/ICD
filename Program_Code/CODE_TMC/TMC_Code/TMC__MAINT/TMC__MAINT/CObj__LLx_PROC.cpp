#include "StdAfx.h"
#include "CObj__LLx_PROC.h"
#include "CObj__LLx_PROC__DEF.h"


//-------------------------------------------------------------------------
CObj__LLx_PROC::CObj__LLx_PROC()
{

}
CObj__LLx_PROC::~CObj__LLx_PROC()
{

}

//-------------------------------------------------------------------------
int CObj__LLx_PROC::__DEFINE__CONTROL_MODE(obj,l_mode)
{
	sObject_Name = obj;

	// ...
	{
		ADD__CTRL_VAR(sMODE__MANUAL_PROCESS, "MANUAL_PROCESS");
	}
	return 1;
}
int CObj__LLx_PROC::__DEFINE__VERSION_HISTORY(version)
{
	version = "JG.Lee \n";

	return 1;
}

int CObj__LLx_PROC::__DEFINE__VARIABLE_STD(p_variable)
{
	DECLARE__STD_VARIABLE;

	CCommon_Error__DEF_VARIABLE m_err_def_variable;
	p_variable->Link__DEF_VARIABLE__ERROR_FEEDBACK(&m_err_def_variable);

	// ...
	CString str_name;

	// ...
	{
		str_name.Format("OBJ.MSG");
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__OBJ_MSG, str_name);
	}

	// ...
	{
		str_name = "CFG.AGING.TEST";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "count", 0, 0, 1000, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_AGING_TEST, str_name);

		str_name = "CUR.AGING.COUNT";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__CUR_AGING_COUNT, str_name);

		//
		str_name = "SEL.RECIPE.NAME";
		STD__ADD_STRING_WITH_X_OPTION(str_name, "");
		LINK__VAR_STRING_CTRL(sCH__SEL_RECIPE_NAME, str_name);

		str_name = "CFG.NEXT_STEP_CTRL.MODE";
		STD__ADD_DIGITAL(str_name, "DISABLE ENABLE");
		LINK__VAR_DIGITAL_CTRL(dCH__CFG_NEXT_STEP_CTRL_MODE, str_name);
	}

	return 1;
}
int CObj__LLx_PROC::__DEFINE__ALARM(p_alarm)
{
	DECLARE__ALARM;

	// ...
	CString title;
	title.Format("%s - ",sObject_Name);

	/*
	CString alarm_title;
	CString alarm_msg;
	CStringArray l_act;

	// Process Recipe does not exist .....
	{
		alarm_title  = title;
		alarm_title += "Process recipe does not exist.";

		alarm_msg = "Please, check process recipe file.\n";

		l_act.RemoveAll();
		l_act.Add("ABORT");
		l_act.Add("RETRY");
	
		ADD__ALARM_EX(ALID__PROCESS_RECIPE_NOT_EXIST,alarm_title,alarm_msg,l_act);
	}
	*/
	return 1;
}

int CObj__LLx_PROC::__Define__USER_FUNCTION(CII_DEFINE__FUNCTION *p_fnc_ctrl)
{
	p_fnc_ctrl->Link__ERROR_FEEDBACK(&mERROR__USER_FNC);
	mERROR__USER_FNC.Set__OBJ_NAME(sObject_Name);

	return 1;
}

//-------------------------------------------------------------------------
int CObj__LLx_PROC::__INITIALIZE__OBJECT(p_variable,p_ext_obj_create)
{
	CString def_name;
	CString obj_name;
	CString var_name;

	// ...
	{
		CString file_name;
		CString log_msg;
		
		file_name.Format("%s_App.log", sObject_Name);
		
		log_msg  = "\n\n";
		log_msg += "//------------------------------------------------------------------------";
		
		xLOG_CTRL->CREATE__SUB_DIRECTORY(sObject_Name);
		xLOG_CTRL->SET__PROPERTY(file_name, 24*5, 60);
		
		xLOG_CTRL->DISABLE__TIME_LOG();
		xLOG_CTRL->WRITE__LOG(log_msg);
		
		xLOG_CTRL->ENABLE__TIME_LOG();
		xLOG_CTRL->WRITE__LOG("   START   \n");
	}

	// DB LLx ...
	{
		def_name = "OBJ__DB_LLx";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, obj_name);

		//
		var_name = "SYSTEM.MSG";
		LINK__EXT_VAR_STRING_CTRL(sEXT_CH__SYSTEM_MSG, obj_name,var_name);

		var_name = "FUNCTION.MSG";		
		LINK__EXT_VAR_STRING_CTRL(sEXT_CH__FNC_MSG, obj_name,var_name);

		//
		var_name = "SLOT01.RECIPE";
		LINK__EXT_VAR_STRING_CTRL(sEXT_CH__RCP_NAME, obj_name,var_name);
	}
	// OBJ PROC .....
	{
		def_name = "OBJ__PROC";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, obj_name);
		
		pOBJ_CTRL__PROC = p_ext_obj_create->Create__OBJECT_CTRL(obj_name);

		//
		var_name = "NEXT_STEP_CTRL.FLAG";
		LINK__EXT_VAR_STRING_CTRL(sEXT_CH__NEXT_STEP_CTRL_FLAG, obj_name,var_name);
		
		var_name = "NEXT_STEP_CTRL.REQ";
		LINK__EXT_VAR_STRING_CTRL(sEXT_CH__NEXT_STEP_CTRL_REQ, obj_name,var_name);
	}

	return 1;
}

//-------------------------------------------------------------------------
int CObj__LLx_PROC::__CALL__CONTROL_MODE(mode,p_debug,p_variable,p_alarm)
{
	// ...
	{
		CString log_msg;
		log_msg.Format("Start ... :  [%s]", mode);

		xLOG_CTRL->WRITE__LOG(log_msg);
		sCH__OBJ_MSG->Set__DATA(log_msg);
	}

	int flag = -1;

	// ...
	{
		IF__CTRL_MODE(sMODE__MANUAL_PROCESS)
		{
			CString ch_data;
			int cur_count = 0;

			sCH__CUR_AGING_COUNT->Set__DATA("");

			while(1)
			{
				// ...
				{
					cur_count++;
					ch_data.Format("%1d", cur_count);

					sCH__CUR_AGING_COUNT->Set__DATA(ch_data);
				}

				sEXT_CH__SYSTEM_MSG->Set__DATA("Manual Process Start ...");
				sEXT_CH__FNC_MSG->Set__DATA("");

				if(dCH__CFG_NEXT_STEP_CTRL_MODE->Check__DATA(STR__ENABLE) > 0)
				{
					sEXT_CH__NEXT_STEP_CTRL_FLAG->Set__DATA(STR__YES);
				}
				else
				{
					sEXT_CH__NEXT_STEP_CTRL_FLAG->Set__DATA("");
				}

				flag = Call__MANUAL_PROCESS(p_variable);

				dCH__CFG_NEXT_STEP_CTRL_MODE->Set__DATA(STR__DISABLE);
				sEXT_CH__NEXT_STEP_CTRL_FLAG->Set__DATA("");

				if((flag < 0)||(p_variable->Check__CTRL_ABORT() > 0))
				{
					break;
				}

				int trg_count = (int) aCH__CFG_AGING_TEST->Get__VALUE();
				if(cur_count >= trg_count)
				{
					break;
				}
			}
		}
	}

	if((flag < 0)||(p_variable->Check__CTRL_ABORT() > 0))
	{
		CString log_msg;
		log_msg.Format("Aborted ... :  [%s]",mode);
		
		xLOG_CTRL->WRITE__LOG(log_msg);
		sCH__OBJ_MSG->Set__DATA(log_msg);
	}
	else
	{
		CString log_msg;
		log_msg.Format("Completed ... :  [%s]",mode);
		
		xLOG_CTRL->WRITE__LOG(log_msg);
		sCH__OBJ_MSG->Set__DATA(log_msg);
	}
	
	sEXT_CH__SYSTEM_MSG->Set__DATA("");
	return flag;
}

int CObj__LLx_PROC::__CALL__MONITORING(id,p_variable,p_alarm)
{

	return 1;
}
