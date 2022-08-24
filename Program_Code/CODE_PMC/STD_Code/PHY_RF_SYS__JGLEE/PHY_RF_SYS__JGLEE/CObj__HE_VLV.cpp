#include "StdAfx.h"
#include "CObj__HE_VLV.h"

#include "CCommon_Utility.h"


//-------------------------------------------------------------------------
CObj__HE_VLV::CObj__HE_VLV()
{

}
CObj__HE_VLV::~CObj__HE_VLV()
{

}

//-------------------------------------------------------------------------
int CObj__HE_VLV::__DEFINE__CONTROL_MODE(obj,l_mode)
{
	sObject_Name = obj;

	// ...
	{
		ADD__CTRL_VAR(sMODE__INIT,  "INIT" );
		ADD__CTRL_VAR(sMODE__CLOSE, "CLOSE");

		// SUPPLY_VLV.CTRL ...
		ADD__CTRL_VAR(sMODE__SUPPLY_VLV_OPEN,  "SUPPLY_VLV.OPEN" );
		ADD__CTRL_VAR(sMODE__SUPPLY_VLV_CLOSE, "SUPPLY_VLV.CLOSE");

		// BYPASS_VLV.CTRL ...
		ADD__CTRL_VAR(sMODE__BYPASS_VLV_OPEN,  "BYPASS_VLV.OPEN" );
		ADD__CTRL_VAR(sMODE__BYPASS_VLV_CLOSE, "BYPASS_VLV.CLOSE");

		// DUMP_VLV.CTRL ...
		ADD__CTRL_VAR(sMODE__DUMP_VLV_OPEN,  "DUMP_VLV.OPEN" );
		ADD__CTRL_VAR(sMODE__DUMP_VLV_CLOSE, "DUMP_VLV.CLOSE");

		// FINAL_VLV.CTRL ...
		ADD__CTRL_VAR(sMODE__FINAL_VLV_OPEN,  "FINAL_VLV.OPEN" );
		ADD__CTRL_VAR(sMODE__FINAL_VLV_CLOSE, "FINAL_VLV.CLOSE");

		// ...
		ADD__CTRL_VAR(sMODE__BYPASS_FLOW, "BYPASS.FLOW");
		ADD__CTRL_VAR(sMODE__DUMP_FLOW,   "DUMP.FLOW"  );
		ADD__CTRL_VAR(sMODE__FINAL_FLOW,  "FINAL.FLOW" );
	}
	return 1;
}
int CObj__HE_VLV::__DEFINE__VERSION_HISTORY(version)
{

	return 1;
}

int CObj__HE_VLV::__DEFINE__VARIABLE_STD(p_variable)
{
	DECLARE__STD_VARIABLE;

	// ...
	CCommon_Error__DEF_VARIABLE m_err_def_variable;
	p_variable->Link__DEF_VARIABLE__ERROR_FEEDBACK(&m_err_def_variable);

	// ...
	CString var_name;

	// ...
	{
		var_name = "OBJ.MSG";
		STD__ADD_STRING(var_name);
		LINK__VAR_STRING_CTRL(sCH__OBJ_MSG, var_name);
	}

	return 1;
}

int CObj__HE_VLV::__DEFINE__ALARM(p_alarm)
{
	DECLARE__ALARM;

	// ...
	CString title;
	title.Format("%s - ",sObject_Name);

	CString alarm_title;
	CString alarm_msg;
	CStringArray l_act;
	int alarm_id;

	// ...
	{

	}

	return 1;
}


//-------------------------------------------------------------------------
int CObj__HE_VLV::__INITIALIZE__OBJECT(p_variable,p_ext_obj_create)
{
	CString log_msg;
	CString log_bff;

	// ...
	{
		CString file_name;
		CString log_msg;

		file_name.Format("%s-App.log", sObject_Name);

		log_msg  = "\n\n";
		log_msg += "//------------------------------------------------------------------------";

		xLOG_CTRL->CREATE__SUB_DIRECTORY(sObject_Name);
		xLOG_CTRL->SET__PROPERTY(file_name,24*5,60);

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
	int i;

	// ...
	CCommon_Utility x_utility;
	bool def_check;


	// DB OBJ ...
	{	
		def_name = "OBJ__DB";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, obj_name);

	}

	// LINK_IO.SUPPLY_VLV ...
	{
		def_name = "LINK_SIZE.SUPPLY_VLV";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, def_data);
		
		iSIZE__SUPPLY_VLV = atoi(def_data);

		for(i=0; i<iSIZE__SUPPLY_VLV; i++)
		{
			int id = i + 1;

			def_name.Format("LINK_IO.SUPPLY_VLV.%1d", id);
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
			p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
			LINK__EXT_VAR_DIGITAL_CTRL(doEXT_CH__SUPPLY_VLV_X[i], obj_name,var_name);
		}
	}
	// LINK_IO.BYPASS_VLV ...
	{
		def_name = "LINK_SIZE.BYPASS_VLV";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, def_data);

		iSIZE__BYPASS_VLV = atoi(def_data);

		for(i=0; i<iSIZE__BYPASS_VLV; i++)
		{
			int id = i + 1;

			def_name.Format("LINK_IO.BYPASS_VLV.%1d", id);
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
			p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
			LINK__EXT_VAR_DIGITAL_CTRL(doEXT_CH__BYPASS_VLV_X[i], obj_name,var_name);
		}
	}
	// LINK_IO.DUMP_VLV ...
	{
		def_name = "LINK_SIZE.DUMP_VLV";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, def_data);

		iSIZE__DUMP_VLV = atoi(def_data);

		for(i=0; i<iSIZE__DUMP_VLV; i++)
		{
			int id = i + 1;

			def_name.Format("LINK_IO.DUMP_VLV.%1d", id);
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
			p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
			LINK__EXT_VAR_DIGITAL_CTRL(doEXT_CH__DUMP_VLV_X[i], obj_name,var_name);
		}
	}
	// LINK_IO.FINAL_VLV ...
	{
		def_name = "LINK_SIZE.FINAL_VLV";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, def_data);

		iSIZE__FINAL_VLV = atoi(def_data);

		for(i=0; i<iSIZE__FINAL_VLV; i++)
		{
			int id = i + 1;

			def_name.Format("LINK_IO.FINAL_VLV.%1d", id);
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
			p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
			LINK__EXT_VAR_DIGITAL_CTRL(doEXT_CH__FINAL_VLV_X[i], obj_name,var_name);
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
int CObj__HE_VLV::__CALL__CONTROL_MODE(mode,p_debug,p_variable,p_alarm)
{
	CString log_msg;
	int flag = -1;

	// ...
	{
		log_msg.Format("Start ... : [%s]", mode);
		sCH__OBJ_MSG->Set__DATA(log_msg);

		xLOG_CTRL->WRITE__LOG(log_msg);
	}

	// ...
	{
			 IF__CTRL_MODE(sMODE__INIT)						flag = Call__INIT(p_variable, p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__CLOSE)					flag = Call__CLOSE(p_variable, p_alarm);

		// SUPPLY_VLV.CTRL ...
		ELSE_IF__CTRL_MODE(sMODE__SUPPLY_VLV_OPEN)			flag = Call__SUPPLY_VLV_CTRL(p_variable,p_alarm, STR__OPEN);
		ELSE_IF__CTRL_MODE(sMODE__SUPPLY_VLV_CLOSE)			flag = Call__SUPPLY_VLV_CTRL(p_variable,p_alarm, STR__CLOSE);

		// BYPASS_VLV.CTRL ...
		ELSE_IF__CTRL_MODE(sMODE__BYPASS_VLV_OPEN)			flag = Call__BYPASS_VLV_CTRL(p_variable,p_alarm, STR__OPEN);
		ELSE_IF__CTRL_MODE(sMODE__BYPASS_VLV_CLOSE)			flag = Call__BYPASS_VLV_CTRL(p_variable,p_alarm, STR__CLOSE);

		// DUMP_VLV.CTRL ...
		ELSE_IF__CTRL_MODE(sMODE__DUMP_VLV_OPEN)			flag = Call__DUMP_VLV_CTRL(p_variable,p_alarm, STR__OPEN);
		ELSE_IF__CTRL_MODE(sMODE__DUMP_VLV_CLOSE)			flag = Call__DUMP_VLV_CTRL(p_variable,p_alarm, STR__CLOSE);

		// FINAL_VLV.CTRL ...
		ELSE_IF__CTRL_MODE(sMODE__FINAL_VLV_OPEN)			flag = Call__FINAL_VLV_CTRL(p_variable,p_alarm, STR__OPEN);
		ELSE_IF__CTRL_MODE(sMODE__FINAL_VLV_CLOSE)			flag = Call__FINAL_VLV_CTRL(p_variable,p_alarm, STR__CLOSE);

		// ...
		ELSE_IF__CTRL_MODE(sMODE__BYPASS_FLOW)				flag = Call__BYPASS_FLOW(p_variable, p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__DUMP_FLOW)				flag = Call__DUMP_FLOW(p_variable, p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__FINAL_FLOW)				flag = Call__FINAL_FLOW(p_variable, p_alarm);
	}

	if((flag < 0)||(p_variable->Check__CTRL_ABORT() > 0))
	{
		log_msg.Format("Aborted ... : [%s]", mode);
		sCH__OBJ_MSG->Set__DATA(log_msg);

		xLOG_CTRL->WRITE__LOG(log_msg);
	}
	else
	{
		log_msg.Format("Completed ... : [%s]", mode);
		sCH__OBJ_MSG->Set__DATA(log_msg);

		xLOG_CTRL->WRITE__LOG(log_msg);
	}

	return flag;
}

int CObj__HE_VLV::__CALL__MONITORING(id,p_variable,p_alarm)
{

	return 1;
}
