#include "StdAfx.h"
#include "CObj__LBx_TEST.h"



//-------------------------------------------------------------------------
CObj__LBx_TEST::CObj__LBx_TEST()
{

}
CObj__LBx_TEST::~CObj__LBx_TEST()
{

}

//-------------------------------------------------------------------------
int CObj__LBx_TEST::__DEFINE__CONTROL_MODE(obj,l_mode)
{
	sObject_Name = obj;

	// ...
	{
		ADD__CTRL_VAR(sMODE__LBA_SV_CYCLE_TEST, "LBA_SV.CYCLE_TEST");
		ADD__CTRL_VAR(sMODE__LBB_SV_CYCLE_TEST, "LBB_SV.CYCLE_TEST");
		ADD__CTRL_VAR(sMODE__LBC_SV_CYCLE_TEST, "LBC_SV.CYCLE_TEST");
		ADD__CTRL_VAR(sMODE__LBD_SV_CYCLE_TEST, "LBD_SV.CYCLE_TEST");

		ADD__CTRL_VAR(sMODE__LBA_DV_CYCLE_TEST, "LBA_DV.CYCLE_TEST");
		ADD__CTRL_VAR(sMODE__LBB_DV_CYCLE_TEST, "LBB_DV.CYCLE_TEST");
		ADD__CTRL_VAR(sMODE__LBC_DV_CYCLE_TEST, "LBC_DV.CYCLE_TEST");
		ADD__CTRL_VAR(sMODE__LBD_DV_CYCLE_TEST, "LBD_DV.CYCLE_TEST");
	}	
	return 1;
}

int CObj__LBx_TEST::__DEFINE__VERSION_HISTORY(version)
{
	// ...
	{

	}
	return 1;
}


// ...
int CObj__LBx_TEST::__DEFINE__VARIABLE_STD(p_variable)
{
	DECLARE__STD_VARIABLE;

	CCommon_Error__DEF_VARIABLE m_err_def_variable;
	p_variable->Link__DEF_VARIABLE__ERROR_FEEDBACK(&m_err_def_variable);

	// ...
	CString str_name;

	// ...
	{
		str_name = "OBJ.MSG";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__OBJ_MSG,str_name);

		str_name = "OBJ.ACTIVE.MODE";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__OBJ_ACTIVE_MODE,str_name);
	}

	// ...
	{
		str_name = "CYCLE_TEST.CFG.CYCLE_COUNT";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name,"count",0,1,9999,"");
		LINK__VAR_ANALOG_CTRL(aCH__CYCLE_TEST_CFG_CYCLE_COUNT,str_name);

		str_name = "CYCLE_TEST.CUR.CYCLE_COUNT";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__CYCLE_TEST_CUR_CYCLE_COUNT,str_name);

		//
		str_name = "CYCLE_TEST.CFG.DELAY_SEC";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name,"sec",0,1,9999,"");
		LINK__VAR_ANALOG_CTRL(aCH__CYCLE_TEST_CFG_DELAY_SEC,str_name);

		str_name = "CYCLE_TEST.CUR.DELAY_SEC";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__CYCLE_TEST_CUR_DELAY_SEC,str_name);
	}

	// ...
	{
		str_name = "CYCLE_TEST.OP_TIME.CUR";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__CYCLE_TEST_OP_TIME_CUR,str_name);

		str_name = "CYCLE_TEST.OP_TIME.AVG";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__CYCLE_TEST_OP_TIME_AVG,str_name);

		str_name = "CYCLE_TEST.OP_TIME.MIN";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__CYCLE_TEST_OP_TIME_MIN,str_name);

		str_name = "CYCLE_TEST.OP_TIME.MAX";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__CYCLE_TEST_OP_TIME_MAX,str_name);

		// 
		str_name = "CYCLE_TEST.CL_TIME.CUR";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__CYCLE_TEST_CL_TIME_CUR,str_name);

		str_name = "CYCLE_TEST.CL_TIME.AVG";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__CYCLE_TEST_CL_TIME_AVG,str_name);

		str_name = "CYCLE_TEST.CL_TIME.MIN";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__CYCLE_TEST_CL_TIME_MIN,str_name);

		str_name = "CYCLE_TEST.CL_TIME.MAX";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__CYCLE_TEST_CL_TIME_MAX,str_name);
	}

	return 1;
}

int CObj__LBx_TEST::__DEFINE__ALARM(p_alarm)
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
		alarm_id = ALID__LBA_STATUS_IS_NOT_MAINT;

		alarm_title  = title;
		alarm_title += "LBA's status is not \"MAINTMODE\".";

		alarm_msg = "Please, convert LBA's status to \"MAINTMODE\" !\n";

		l_act.RemoveAll();
		l_act.Add("CHECK");

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}
	// ...
	{
		alarm_id = ALID__LBB_STATUS_IS_NOT_MAINT;

		alarm_title  = title;
		alarm_title += "LBB's status is not \"MAINTMODE\".";

		alarm_msg = "Please, convert LBB's status to \"MAINTMODE\" !\n";

		l_act.RemoveAll();
		l_act.Add("CHECK");

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}
	// ...
	{
		alarm_id = ALID__LBC_STATUS_IS_NOT_MAINT;

		alarm_title  = title;
		alarm_title += "LBC's status is not \"MAINTMODE\".";

		alarm_msg = "Please, convert LBC's status to \"MAINTMODE\" !\n";

		l_act.RemoveAll();
		l_act.Add("CHECK");

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}
	// ...
	{
		alarm_id = ALID__LBD_STATUS_IS_NOT_MAINT;

		alarm_title  = title;
		alarm_title += "LBD's status is not \"MAINTMODE\".";

		alarm_msg = "Please, convert LBD's status to \"MAINTMODE\" !\n";

		l_act.RemoveAll();
		l_act.Add("CHECK");

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	return 1;
}

//-------------------------------------------------------------------------
int CObj__LBx_TEST::__INITIALIZE__OBJECT(p_variable,p_ext_obj_create)
{
	CString def_name;
	CString def_data;
	CString str_name;

	CString obj_name;
	CString var_name;

	int i;

	// ...
	{
		CString file_name;
		CString log_msg;

		file_name.Format("%s_App.log", sObject_Name);

		log_msg  = "\n\n";
		log_msg += "//------------------------------------------------------------------------";

		xLOG_CTRL->CREATE__SUB_DIRECTORY(sObject_Name);
		xLOG_CTRL->SET__PROPERTY(file_name,24*5,60);

		xLOG_CTRL->DISABLE__TIME_LOG();
		xLOG_CTRL->WRITE__LOG(log_msg);

		xLOG_CTRL->ENABLE__TIME_LOG();
		xLOG_CTRL->WRITE__LOG("   START   \n");
	}
	
	// DATA.LLx_SIZE ...
	{
		def_name = "DATA.LLx_SIZE";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, def_data);

		int llx_size = atoi(def_data);
		if(llx_size > CFG__LLx_SIZE)			llx_size = CFG__LLx_SIZE;

		iLLx_SIZE = llx_size;
	}

	// OBJ.LLx_OPR.X ...
	for(i=0; i<iLLx_SIZE; i++)
	{
		int id = i + 1;

		def_name.Format("OBJ.LLx_OPR.%1d", id);
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, obj_name);

		var_name = "OBJ.STATUS";
		LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__LLx_OBJ_STATUS[i], obj_name,var_name);
	}
	// OBJ.LLx_FNC.X ...
	for(i=0; i<iLLx_SIZE; i++)
	{
		int id = i + 1;

		def_name.Format("OBJ.LLx_FNC.%1d", id);
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, obj_name);

		pOBJ_CTRL__LLx_FNC[i] = p_ext_obj_create->Create__OBJECT_CTRL(obj_name);
	}

	return 1;
}

//-------------------------------------------------------------------------
int CObj__LBx_TEST::__CALL__CONTROL_MODE(mode,p_debug,p_variable,p_alarm)
{
	DECLARE__EXT_CTRL(p_variable);

	// ...
	int flag = -1;

	// ...
	{
		CString log_msg;
		log_msg.Format("Start ... :  [%s]", mode);

		xLOG_CTRL->WRITE__LOG(log_msg);
		sCH__OBJ_MSG->Set__DATA(log_msg);
	}

	// ...
	{
		sCH__OBJ_ACTIVE_MODE->Set__DATA(mode);
	}


	// ...
	{
		     IF__CTRL_MODE(sMODE__LBA_SV_CYCLE_TEST)		flag = Call__LBA_SV_CYCLE_TEST(p_variable, p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__LBB_SV_CYCLE_TEST)		flag = Call__LBB_SV_CYCLE_TEST(p_variable, p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__LBC_SV_CYCLE_TEST)		flag = Call__LBC_SV_CYCLE_TEST(p_variable, p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__LBD_SV_CYCLE_TEST)		flag = Call__LBD_SV_CYCLE_TEST(p_variable, p_alarm);

		ELSE_IF__CTRL_MODE(sMODE__LBA_DV_CYCLE_TEST)		flag = Call__LBA_DV_CYCLE_TEST(p_variable, p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__LBB_DV_CYCLE_TEST)		flag = Call__LBB_DV_CYCLE_TEST(p_variable, p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__LBC_DV_CYCLE_TEST)		flag = Call__LBC_DV_CYCLE_TEST(p_variable, p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__LBD_DV_CYCLE_TEST)		flag = Call__LBD_DV_CYCLE_TEST(p_variable, p_alarm);
	}

	// ...
	{
		sCH__OBJ_ACTIVE_MODE->Set__DATA("");
	}

	if((flag < 0)||(p_variable->Check__CTRL_ABORT() > 0))
	{
		// ...
		{
			CString log_msg;
			log_msg.Format("Aborted ... :  [%s]",mode);

			xLOG_CTRL->WRITE__LOG(log_msg);
			sCH__OBJ_MSG->Set__DATA(log_msg);
		}
	}
	else
	{
		// ...
		{
			CString log_msg;
			log_msg.Format("Completed ... :  [%s]",mode);

			xLOG_CTRL->WRITE__LOG(log_msg);
			sCH__OBJ_MSG->Set__DATA(log_msg);
		}
	}

	return flag;
}
int CObj__LBx_TEST::__CALL__MONITORING(id,p_variable,p_alarm)
{
	// ...
	{

	}
	return 1;
}
