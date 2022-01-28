#include "StdAfx.h"
#include "CObj__ManiFold_TEST.h"



//-------------------------------------------------------------------------
CObj__ManiFold_TEST::CObj__ManiFold_TEST()
{

}
CObj__ManiFold_TEST::~CObj__ManiFold_TEST()
{

}

//-------------------------------------------------------------------------
int CObj__ManiFold_TEST::__DEFINE__CONTROL_MODE(obj,l_mode)
{
	sObject_Name = obj;

	// ...
	{
		ADD__CTRL_VAR(sMODE__PUMPING_CYCLE_TEST, "PUMPING.CYCLE_TEST");
	}	
	return 1;
}

int CObj__ManiFold_TEST::__DEFINE__VERSION_HISTORY(version)
{
	// ...
	{

	}
	return 1;
}


// ...
int CObj__ManiFold_TEST::__DEFINE__VARIABLE_STD(p_variable)
{
	DECLARE__STD_VARIABLE;

	CCommon_Error__DEF_VARIABLE m_err_def_variable;
	p_variable->Link__DEF_VARIABLE__ERROR_FEEDBACK(&m_err_def_variable);

	// ...
	CString str_name;
	int i;

	// ...
	{
		str_name = "OBJ.MSG";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__OBJ_MSG,str_name);

		str_name = "OBJ.ACTIVE.MODE";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__OBJ_ACTIVE_MODE,str_name);
	}

	// CFG ...
	{
		str_name = "CYCLE_TEST.CFG.COUNT.ALL";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "count", 0,1,9999, "");
		LINK__VAR_ANALOG_CTRL(aCH__CYCLE_TEST_CFG_COUNT_ALL, str_name);

		str_name = "CYCLE_TEST.CUR.COUNT.ALL";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__CYCLE_TEST_CUR_COUNT_ALL, str_name);
	}

	for(i=0; i<CFG__MD_SIZE; i++)
	{
		CString ll_name;
		
		if(i == 0)		ll_name = "TMC";
		else			ll_name.Format("LL%1d", i);

		//
		str_name.Format("CYCLE_TEST.CFG.ACTIVE.%s", ll_name);;
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name, "NO YES", "");
		LINK__VAR_DIGITAL_CTRL(dCH__CYCLE_TEST_CFG_ACTIVE_X[i], str_name);

		str_name.Format("CYCLE_TEST.CUR.ACTIVE.%s", ll_name);;
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__CYCLE_TEST_CUR_ACTIVE_X[i], str_name);

		//
		str_name.Format("CYCLE_TEST.CUR.COUNT.%s", ll_name);;
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__CYCLE_TEST_CUR_COUNT_X[i], str_name);

		//
		str_name.Format("CYCLE_TEST.CFG.VENT.%s", ll_name);;
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name, "NO YES", "");
		LINK__VAR_DIGITAL_CTRL(dCH__CYCLE_TEST_CFG_VENT_X[i], str_name);

		str_name.Format("CYCLE_TEST.CUR.VENT.%s", ll_name);;
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__CYCLE_TEST_CUR_VENT_X[i], str_name);
	}

	return 1;
}

int CObj__ManiFold_TEST::__DEFINE__ALARM(p_alarm)
{
	DECLARE__ALARM;

	// ...
	CString title;
	CString str_bff;

	title.Format("%s - ",sObject_Name);

	// ...
	CString alarm_title;
	CString alarm_msg;
	CStringArray l_act;
	int alarm_id;

	for(int i=0; i<CFG__MD_SIZE; i++)
	{
		alarm_id = ALID__MD_X__STATUS_IS_NOT_MAINT + i;

		alarm_title = title;
		str_bff.Format("LL%1d's status is not \"MAINTMODE\".", i+1);		
		alarm_title += str_bff;

		alarm_msg = "Please, convert LL's status to \"MAINTMODE\" !\n";

		l_act.RemoveAll();
		l_act.Add("CHECK");

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	return 1;
}

//-------------------------------------------------------------------------
int CObj__ManiFold_TEST::__INITIALIZE__OBJECT(p_variable,p_ext_obj_create)
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

	// DATA.MODULE_SIZE ...
	{
		def_name = "DATA.MDx_SIZE";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, def_data);

		int md_size = atoi(def_data);
		if(md_size > CFG__MD_SIZE)			md_size = CFG__MD_SIZE;

		iMD_SIZE = md_size;
	}

	// OBJ.MD_FNC.X ...
	for(i=0; i<iMD_SIZE; i++)
	{
		int id = i + 1;

		// NAME ...
		{
			def_name.Format("OBJ.MDx_NAME.%1d", id);
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name, def_data);

			sMD_NAME_X[i] = def_data;
		}

		// OPR ...
		{
			def_name.Format("OBJ.MDx_OPR.%1d", id);
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name, obj_name);

			var_name = "OBJ.STATUS";
			LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__MD_OBJ_STATUS_X[i], obj_name,var_name);
		}
		// FNC ...
		{
			def_name.Format("OBJ.MDx_FNC.%1d", id);
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name, obj_name);

			pOBJ_CTRL__MD_FNC_X[i] = p_ext_obj_create->Create__OBJECT_CTRL(obj_name);
		}
	}

	return 1;
}

//-------------------------------------------------------------------------
int CObj__ManiFold_TEST::__CALL__CONTROL_MODE(mode,p_debug,p_variable,p_alarm)
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
		IF__CTRL_MODE(sMODE__PUMPING_CYCLE_TEST)
		{
			flag = Call__PUMPING_CYCLE_TEST(p_variable, p_alarm);
		}
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
int CObj__ManiFold_TEST::__CALL__MONITORING(id,p_variable,p_alarm)
{
	// ...
	{

	}
	return 1;
}
