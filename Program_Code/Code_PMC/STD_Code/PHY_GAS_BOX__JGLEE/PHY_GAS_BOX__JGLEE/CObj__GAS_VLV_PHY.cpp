#include "StdAfx.h"
#include "CObj__GAS_VLV_PHY.h"


//-------------------------------------------------------------------------
CObj__GAS_VLV_PHY::CObj__GAS_VLV_PHY()
{

}
CObj__GAS_VLV_PHY::~CObj__GAS_VLV_PHY()
{

}

//-------------------------------------------------------------------------
int CObj__GAS_VLV_PHY::__DEFINE__CONTROL_MODE(obj,l_mode)
{
	sObject_Name = obj;

	// ...
	{
		ADD__CTRL_VAR(sMODE__ALL_CLOSE,	 "ALL_CLOSE");

		ADD__CTRL_VAR(sMODE__SV_OPEN,    "SV_OPEN");
		ADD__CTRL_VAR(sMODE__SV_CLOSE,   "SV_CLOSE");

		ADD__CTRL_VAR(sMODE__FV_OPEN,    "FV_OPEN");
		ADD__CTRL_VAR(sMODE__FV_CLOSE,   "FV_CLOSE");

		ADD__CTRL_VAR(sMODE__GAS_LINE_PURGE,     "GAS_LINE_PURGE");
		ADD__CTRL_VAR(sMODE__CHM_LINE_PURGE,     "CHM_LINE_PURGE");
		ADD__CTRL_VAR(sMODE__LINE_PURGE_WITH_N2, "LINE_PURGE_WITH_N2");
		ADD__CTRL_VAR(sMODE__CLOSE_N2_PURGE,     "CLOSE_N2_PURGE");

		ADD__CTRL_VAR(sMODE__PROC_OPEN,  "PROC_OPEN");
	}
	return 1;
}
int CObj__GAS_VLV_PHY::__DEFINE__VERSION_HISTORY(version)
{

	return 1;
}

// ...
#define  MON_ID__STATE_CHECK			1


int CObj__GAS_VLV_PHY::__DEFINE__VARIABLE_STD(p_variable)
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
		LINK__VAR_STRING_CTRL(sCH__OBJ_MSG, str_name);
	}

	// ...
	{
		p_variable->Add__MONITORING_PROC(1.0, MON_ID__STATE_CHECK);
	}
	return 1;
}
int CObj__GAS_VLV_PHY::__DEFINE__ALARM(p_alarm)
{
	DECLARE__ALARM;

	return 1;
}

//-------------------------------------------------------------------------
int CObj__GAS_VLV_PHY::__INITIALIZE__OBJECT(p_variable,p_ext_obj_create)
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

	// OBJ : DB_SYS ...
	{
		def_name = "OBJ__DB_SYS";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, obj_name);

		var_name = "MON.ACTIVE.PROCESS.VALVE.READY.STATE";
		LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__MON_ACTIVE_PROCESS_VALVE_READY_STATE, obj_name,var_name);
	}
	
	// GAS_LINE : PURGE VLV ...
	{
		def_name = "DATA.GAS_LINE.VLV_PURGE";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, def_data);

		iSIZE__GAS_LINE__VLV_PURGE = atoi(def_data);
		if(iSIZE__GAS_LINE__VLV_PURGE > CFG_SIZE__MFC__VLV_PURGE)		iSIZE__GAS_LINE__VLV_PURGE = CFG_SIZE__MFC__VLV_PURGE;

		for(int i=0; i<iSIZE__GAS_LINE__VLV_PURGE; i++)
		{
			def_name.Format("CH.GAS_LINE.VLV_PURGE.%1d", i+1);
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
			p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
			LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__GAS_LINE__VLV_PURGE[i], obj_name,var_name);
		}
	}
	// CHM_LINE : PURGE VLV ...
	{
		def_name = "DATA.CHM_LINE.VLV_PURGE";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, def_data);

		iSIZE__CHM_LINE__VLV_PURGE = atoi(def_data);
		if(iSIZE__CHM_LINE__VLV_PURGE > CFG_SIZE__MFC__VLV_PURGE)		iSIZE__CHM_LINE__VLV_PURGE = CFG_SIZE__MFC__VLV_PURGE;

		for(int i=0; i<iSIZE__CHM_LINE__VLV_PURGE; i++)
		{
			def_name.Format("CH.CHM_LINE.VLV_PURGE.%1d", i+1);
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
			p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
			LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__CHM_LINE__VLV_PURGE[i], obj_name,var_name);
		}
	}
	// MFC : PURGE VLV ...
	{
		def_name = "DATA.MFC.VLV_PURGE";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, def_data);

		iSIZE__MFC__VLV_PURGE = atoi(def_data);
		if(iSIZE__MFC__VLV_PURGE > CFG_SIZE__MFC__VLV_PURGE)		iSIZE__MFC__VLV_PURGE = CFG_SIZE__MFC__VLV_PURGE;

		for(int i=0; i<iSIZE__MFC__VLV_PURGE; i++)
		{
			def_name.Format("CH.MFC.VLV_PURGE.%1d", i+1);
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
			p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
			LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__MFC__VLV_PURGE[i], obj_name,var_name);
		}
	}

	// TOP_CHM : PROC VLV ...
	{
		def_name = "DATA.TOP_CHM.VLV_PROC";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, def_data);

		iSIZE__TOP_CHM__VLV_PROC = atoi(def_data);
		if(iSIZE__TOP_CHM__VLV_PROC > CFG_SIZE__TOP_CHM__VLV_PROC)		
		{
			iSIZE__TOP_CHM__VLV_PROC = CFG_SIZE__TOP_CHM__VLV_PROC;
		}

		for(int i=0; i<iSIZE__TOP_CHM__VLV_PROC; i++)
		{
			def_name.Format("CH.TOP_CHM.VLV_PROC.%1d", i+1);
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
			p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
			LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__TOP_CHM__VLV_PROC[i], obj_name,var_name);
		}
	}
	// TOP_CHM : PURGE VLV ...
	{
		def_name = "DATA.TOP_CHM.VLV_PURGE";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, def_data);

		iSIZE__TOP_CHM__VLV_PURGE = atoi(def_data);
		if(iSIZE__TOP_CHM__VLV_PURGE > CFG_SIZE__TOP_CHM__VLV_PURGE)		
		{
			iSIZE__TOP_CHM__VLV_PURGE = CFG_SIZE__TOP_CHM__VLV_PURGE;
		}

		for(int i=0; i<iSIZE__TOP_CHM__VLV_PURGE; i++)
		{
			def_name.Format("CH.TOP_CHM.VLV_PURGE.%1d", i+1);
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
			p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
			LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__TOP_CHM__VLV_PURGE[i], obj_name,var_name);
		}
	}

	// SOFT_VENT.OPEN ...
	{
		def_name = "DATA.SOFT_VENT_VLV.OPEN";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, def_data);

		iSIZE__SOFT_VENT__VLV_OPEN = atof(def_data);
		if(iSIZE__SOFT_VENT__VLV_OPEN > CFG_SIZE__SOFT_VENT__VLV_OPEN)
		{
			iSIZE__SOFT_VENT__VLV_OPEN = CFG_SIZE__SOFT_VENT__VLV_OPEN;
		}

		for(int i=0; i<iSIZE__SOFT_VENT__VLV_OPEN; i++)
		{
			def_name.Format("CH.SOFT_VENT_VLV.OPEN.%1d", i+1);
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
			p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
			LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__SOFT_VENT__VLV_OPEN[i], obj_name,var_name);
		}
	}
	// SOFT_VENT.CLOSE ...
	{
		def_name = "DATA.SOFT_VENT_VLV.CLOSE";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, def_data);

		iSIZE__SOFT_VENT__VLV_CLOSE = atof(def_data);
		if(iSIZE__SOFT_VENT__VLV_CLOSE > CFG_SIZE__SOFT_VENT__VLV_CLOSE)
		{
			iSIZE__SOFT_VENT__VLV_CLOSE = CFG_SIZE__SOFT_VENT__VLV_CLOSE;
		}

		for(int i=0; i<iSIZE__SOFT_VENT__VLV_CLOSE; i++)
		{
			def_name.Format("CH.SOFT_VENT_VLV.CLOSE.%1d", i+1);
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
			p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
			LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__SOFT_VENT__VLV_CLOSE[i], obj_name,var_name);
		}
	}

	// FAST_VENT.OPEN ...
	{
		def_name = "DATA.FAST_VENT_VLV.OPEN";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, def_data);

		iSIZE__FAST_VENT__VLV_OPEN = atof(def_data);
		if(iSIZE__FAST_VENT__VLV_OPEN > CFG_SIZE__FAST_VENT__VLV_OPEN)
		{
			iSIZE__FAST_VENT__VLV_OPEN = CFG_SIZE__FAST_VENT__VLV_OPEN;
		}

		for(int i=0; i<iSIZE__FAST_VENT__VLV_OPEN; i++)
		{
			def_name.Format("CH.FAST_VENT_VLV.OPEN.%1d", i+1);
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
			p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
			LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__FAST_VENT__VLV_OPEN[i], obj_name,var_name);
		}
	}
	// FAST_VENT.CLOSE ...
	{
		def_name = "DATA.FAST_VENT_VLV.CLOSE";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, def_data);

		iSIZE__FAST_VENT__VLV_CLOSE = atof(def_data);
		if(iSIZE__FAST_VENT__VLV_CLOSE > CFG_SIZE__FAST_VENT__VLV_CLOSE)
		{
			iSIZE__FAST_VENT__VLV_CLOSE = CFG_SIZE__FAST_VENT__VLV_CLOSE;
		}

		for(int i=0; i<iSIZE__FAST_VENT__VLV_CLOSE; i++)
		{
			def_name.Format("CH.FAST_VENT_VLV.CLOSE.%1d", i+1);
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
			p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
			LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__FAST_VENT__VLV_CLOSE[i], obj_name,var_name);
		}
	}

	return 1;
}

//-------------------------------------------------------------------------
int CObj__GAS_VLV_PHY::__CALL__CONTROL_MODE(mode,p_debug,p_variable,p_alarm)
{
	DECLARE__EXT_CTRL(p_variable);

	int flag = -1;

	CString log_msg;
	CString log_bff;

	// ...
	{
		log_msg.Format("Start [%s] ... By %s", mode, p_ext_mode_ctrl->Get__UPPER_OBJECT_NAME());
		sCH__OBJ_MSG->Set__DATA(log_msg);

		log_msg += "\n";
		xI_LOG_CTRL->WRITE__LOG(log_msg);
	}

	// ...
	{
		     IF__CTRL_MODE(sMODE__ALL_CLOSE)				flag = Call__ALL_CLOSE(p_variable, p_alarm);

		ELSE_IF__CTRL_MODE(sMODE__SV_OPEN)					flag = Call__SV_OPEN(p_variable,p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__SV_CLOSE)					flag = Call__SV_CLOSE(p_variable,p_alarm);

		ELSE_IF__CTRL_MODE(sMODE__FV_OPEN)					flag = Call__FV_OPEN(p_variable,p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__FV_CLOSE)					flag = Call__FV_CLOSE(p_variable,p_alarm);

		ELSE_IF__CTRL_MODE(sMODE__GAS_LINE_PURGE)			flag = Call__GAS_LINE_PURGE(p_variable,p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__CHM_LINE_PURGE)			flag = Call__CHM_LINE_PURGE(p_variable,p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__LINE_PURGE_WITH_N2)		flag = Call__LINE_PURGE_WITH_N2(p_variable,p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__CLOSE_N2_PURGE)			flag = Call__CLOSE_N2_PURGE(p_variable,p_alarm);

		ELSE_IF__CTRL_MODE(sMODE__PROC_OPEN)				flag = Call__PROC_OPEN(p_variable,p_alarm);
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

int CObj__GAS_VLV_PHY::__CALL__MONITORING(id,p_variable,p_alarm)
{
	if(id == MON_ID__STATE_CHECK)		Mon__STATE_CHECK(p_variable,p_alarm);

	return 1;
}
