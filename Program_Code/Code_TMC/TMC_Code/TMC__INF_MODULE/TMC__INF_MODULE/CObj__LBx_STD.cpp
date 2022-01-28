#include "StdAfx.h"
#include "CObj__LBx_STD.h"


//-------------------------------------------------------------------------
CObj__LBx_STD::CObj__LBx_STD()
{

}
CObj__LBx_STD::~CObj__LBx_STD()
{

}

//-------------------------------------------------------------------------
int CObj__LBx_STD::__DEFINE__CONTROL_MODE(obj,l_mode)
{
	sObject_Name = obj;

	// ...
	{
		ADD__CTRL_VAR(sMODE__INIT,  "INIT");
		ADD__CTRL_VAR(sMODE__MAINT, "MAINT");

		ADD__CTRL_VAR(sMODE__PUMP, "PUMP");
		ADD__CTRL_VAR(sMODE__VENT, "VENT");

		ADD__CTRL_VAR(sMODE__PREPMATER, "PREPMATER");
		ADD__CTRL_VAR(sMODE__COMPMATER, "COMPMATER");
		ADD__CTRL_VAR(sMODE__COMPMATER_EX, "COMPMATER.EX");

		ADD__CTRL_VAR(sMODE__IN_PROC,  "IN_PROC");
		ADD__CTRL_VAR(sMODE__OUT_PROC, "OUT_PROC");

		//
		ADD__CTRL_VAR(sMODE__PROC_READY, "PROC_READY");
		ADD__CTRL_VAR(sMODE__PROC_START, "PROC_START");

		ADD__CTRL_VAR(sMODE__PRE_READY,	"PRE_READY");
		ADD__CTRL_VAR(sMODE__PRE_START,	"PRE_START");

		ADD__CTRL_VAR(sMODE__CLN_READY,	"CLN_READY");
		ADD__CTRL_VAR(sMODE__CLN_START,	"CLN_START");

		ADD__CTRL_VAR(sMODE__MNT_READY,	"MNT_READY");
		ADD__CTRL_VAR(sMODE__MNT_START,	"MNT_START");
	}
	return 1;
}
int CObj__LBx_STD::__DEFINE__VERSION_HISTORY(version)
{

	return 1;
}

int CObj__LBx_STD::__DEFINE__VARIABLE_STD(p_variable)
{
	DECLARE__STD_VARIABLE;

	CCommon_Error__DEF_VARIABLE m_err_def_variable;
	p_variable->Link__DEF_VARIABLE__ERROR_FEEDBACK(&m_err_def_variable);

	// ...
	CString str_name;

	// ...
	{
		str_name = "PARA.PREHEAT.TIME";
		STD__ADD_ANALOG_WITH_COMMENT(str_name,"sec",1,0,9999,"");
		LINK__VAR_ANALOG_CTRL(aCH__PARA_PREHEAT_TIME,str_name);

		str_name = "PARA.COOLING.TIME";
		STD__ADD_ANALOG_WITH_COMMENT(str_name,"sec",1,0,9999,"");
		LINK__VAR_ANALOG_CTRL(aCH__PARA_COOLING_TIME,str_name);

		str_name = "PARA.PREMATERIAL.SLOT";
		STD__ADD_ANALOG_WITH_COMMENT(str_name,"sec",1,0,9999,"");
		LINK__VAR_ANALOG_CTRL(aCH__PARA_PREMATERIAL_SLOT,str_name);
	}
	return 1;
}
int CObj__LBx_STD::__DEFINE__ALARM(p_alarm)
{

	return 1;
}

int CObj__LBx_STD::__Define__USER_FUNCTION(CII_DEFINE__FUNCTION *p_fnc_ctrl)
{
	p_fnc_ctrl->Link__ERROR_FEEDBACK(&mERROR__USER_FNC);

	return 1;
}

//-------------------------------------------------------------------------
int CObj__LBx_STD::__INITIALIZE__OBJECT(p_variable,p_ext_obj_create)
{
	CString def_name;
	CString def_data;
	CString str_name;

	// ...
	{
		def_name = "OBJ__LBx";
		p_variable->Get__DEF_CONST_DATA(def_name, def_data);

		pLBx__OBJ_CTRL = p_ext_obj_create->Create__OBJECT_CTRL(def_data);

		//
		str_name = "OBJ.STATUS";
		LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__OBJ_STATUS, def_data,str_name);

		//
		str_name = "PARA.PREHEAT.TIME";
		LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__PARA_PREHEAT_TIME, def_data,str_name);

		str_name = "PARA.COOLING.TIME";
		LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__PARA_COOLING_TIME, def_data,str_name);

		str_name = "PARA.PREMATERIAL.SLOT";
		LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__PARA_PREMATERIAL_SLOT, def_data,str_name);
	}

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
	return 1;
}

//-------------------------------------------------------------------------
int CObj__LBx_STD::__CALL__CONTROL_MODE(mode,p_debug,p_variable,p_alarm)
{
	int flag = -1;

	// ...
	{
		CString para__preheat_time;
		CString para__cooling_time;
		CString para__prematerial_slot;

		aCH__PARA_PREHEAT_TIME->Get__DATA(para__preheat_time);
		aEXT_CH__PARA_PREHEAT_TIME->Set__DATA(para__preheat_time);

		aCH__PARA_COOLING_TIME->Get__DATA(para__cooling_time);
		aEXT_CH__PARA_COOLING_TIME->Set__DATA(para__cooling_time);

		aCH__PARA_PREMATERIAL_SLOT->Get__DATA(para__prematerial_slot);
		aEXT_CH__PARA_PREMATERIAL_SLOT->Set__DATA(para__prematerial_slot);

		//
		CString log_msg;
		log_msg.Format("Start ... :  [%s] (%s,%s,%s)",
						mode,
						para__preheat_time,
						para__cooling_time,
						para__prematerial_slot);

		xLOG_CTRL->WRITE__LOG(log_msg);
	}

	// ...
	{
			 IF__CTRL_MODE(sMODE__INIT)				flag = Call__INIT(p_variable);
		ELSE_IF__CTRL_MODE(sMODE__MAINT)			flag = Call__MAINT(p_variable);
		
		ELSE_IF__CTRL_MODE(sMODE__PUMP)				flag = Call__PUMP(p_variable);
		ELSE_IF__CTRL_MODE(sMODE__VENT)				flag = Call__VENT(p_variable);
		
		ELSE_IF__CTRL_MODE(sMODE__PREPMATER)		flag = Call__PREPMATER(p_variable);		
		ELSE_IF__CTRL_MODE(sMODE__COMPMATER)		flag = Call__COMPMATER(p_variable, -1);
		ELSE_IF__CTRL_MODE(sMODE__COMPMATER_EX)		flag = Call__COMPMATER(p_variable,  1);
		
		ELSE_IF__CTRL_MODE(sMODE__IN_PROC)			flag = Call__IN_PROC(p_variable);
		ELSE_IF__CTRL_MODE(sMODE__OUT_PROC)			flag = Call__OUT_PROC(p_variable);

		ELSE_IF__CTRL_MODE(sMODE__PROC_READY)		flag = Call__PROC_READY(p_variable, p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__PROC_START)		flag = Call__PROC_START(p_variable, p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__PRE_READY)		flag = Call__PRE_READY(p_variable, p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__PRE_START)		flag = Call__PRE_START(p_variable, p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__CLN_READY)		flag = Call__CLN_READY(p_variable, p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__CLN_START)		flag = Call__CLN_START(p_variable, p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__MNT_READY)		flag = Call__MNT_READY(p_variable, p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__MNT_START)		flag = Call__MNT_START(p_variable, p_alarm);
	}

	if((flag < 0)||(p_variable->Check__CTRL_ABORT() > 0))
	{
		dEXT_CH__OBJ_STATUS->Set__DATA("MAINTMODE");

		CString log_msg;
		log_msg.Format("Aborted ... :  [%s]",mode);

		xLOG_CTRL->WRITE__LOG(log_msg);
	}
	else
	{
		CString log_msg;
		log_msg.Format("Completed ... :  [%s]",mode);

		xLOG_CTRL->WRITE__LOG(log_msg);
	}

	return flag;
}

int CObj__LBx_STD::__CALL__MONITORING(id,p_variable,p_alarm)
{

	return 1;
}
