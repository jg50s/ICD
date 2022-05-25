#include "StdAfx.h"
#include "CObj__MTC_FNC__ALID.h"
#include "CObj__MTC_FNC__DEF.h"
#include "CObj__MTC_FNC.h"


//-------------------------------------------------------------------------
CObj__MTC_FNC::CObj__MTC_FNC()
{

}
CObj__MTC_FNC::~CObj__MTC_FNC()
{

}

//-------------------------------------------------------------------------
int CObj__MTC_FNC::__DEFINE__CONTROL_MODE(obj,l_mode)
{
	sObject_Name = obj;

	// ...
	{
		ADD__CTRL_VAR(sMODE__INIT,	     "INIT");
		ADD__CTRL_VAR(sMODE__MAINT,	     "MAINT");
		ADD__CTRL_VAR(sMODE__GATE_OPEN,	 "GATE_OPEN");
		ADD__CTRL_VAR(sMODE__GATE_CLOSE, "GATE_CLOSE");
		ADD__CTRL_VAR(sMODE__PUMPING,	 "PUMPING");
		ADD__CTRL_VAR(sMODE__VENT,	     "VENT");
	}
	return 1;
}
int CObj__MTC_FNC::__DEFINE__VERSION_HISTORY(version)
{

	return 1;
}


// ...
#define LIST__DISABLE_ENABLE					"DISABLE ENABLE"
#define LIST__OPEN_CLOSE						"OPEN	CLOSE"
#define LIST__PRESSURE_STS						"VAC BTW ATM"
#define LIST__SOFT_PUMP_MODE					"PRESSURE TIME"

// ...
#define MON_ID__PRESSURE_STATUS							1


int CObj__MTC_FNC::__DEFINE__VARIABLE_STD(p_variable)
{
	DECLARE__STD_VARIABLE;

	// ...
	CString str_name;

	// OBJ PARAMETER ...
	{
		str_name = "OBJ.STATUS";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__OBJ_STATUS, str_name);

		str_name = "OBJ.MSG";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__OBJ_MSG, str_name);

		str_name = "OBJ.TIMER";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__OBJ_TIMER, str_name);
	}

	// MON PARAMETER ...
	{
		str_name = "MON.PUMPING.STATE";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_PUMPING_STATE, str_name);

		str_name = "MON.MTC.STATUS";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_MTC_STATUS, str_name);

		str_name = "MON.GATE.STATE";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_GATE_STATE, str_name);
	}

	// CFG - VENTING PARAMETER ...
	{
		str_name = "CFG.SOFT_VENT.PRESSURE";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "torr", 0, 1, 500, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_SOFT_VENT_PRESSURE, str_name);

		str_name = "CFG.ATM_VENT.PRESSURE";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "torr", 0, 1, 800, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_ATM_VENT_PRESSURE, str_name);

		//
		str_name = "CFG.SOFT_VENT.TIMEOUT";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "sec", 0, 1, 600, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_SOFT_VENT_TIMEOUT, str_name);

		str_name = "CFG.ATM_VENT.TIMEOUT";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "sec", 0, 1, 600, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_ATM_VENT_TIMEOUT, str_name);
	}
	// CFG - PUMPING PARAMETER ...
	{
		str_name = "CFG.SOFT_PUMP.PRESSURE";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "torr", 0, 1, 600, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_SOFT_PUMP_PRESSURE, str_name);

		str_name = "CFG.VAC_PUMP.PRESSURE";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "torr", 3, 0, 1, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_VAC_PUMP_PRESSURE, str_name);

		//
		str_name = "CFG.SOFT_PUMP.TIMEOUT";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "sec", 0, 1, 600, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_SOFT_PUMP_TIMEOUT, str_name);

		str_name = "CFG.VAC_PUMP.TIMEOUT";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "sec", 0, 1, 600, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_VAC_PUMP_TIMEOUT, str_name);
	}
	// CFG - GATE VLV PARAMETER ...
	{
		str_name = "CFG.GATE_VLV.OPEN.TIMEOUT";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "sec", 0, 1, 10, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_GATE_VLV_OPEN_TIMEOUT, str_name);

		str_name = "CFG.GATE_VLV.CLOSE.TIMEOUT";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "sec", 0, 1, 10, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_GATE_VLV_CLOSE_TIMEOUT, str_name);
	}

	// MTC PRESSURE GAUGE
	{
		str_name = "MON.MTC.PRESSURE.TORR";
		STD__ADD_ANALOG(str_name, "torr", 3, 0, 1000);
		LINK__VAR_ANALOG_CTRL(aCH__MTC_PRESSURE_TORR, str_name);

		str_name = "MON.MTC.PRESSURE.DISPLAY";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MTC_PRESSURE_DISPLAY, str_name);

		//
		str_name = "MON.MTC.PRESSURE.SIM.MODE";
		STD__ADD_ANALOG(str_name, "torr", 3, 0, 1000);
		LINK__VAR_ANALOG_CTRL(aCH__MTC_PRESSURE_SIM_MODE, str_name);
	}

	// ...
	{
		p_variable->Add__MONITORING_PROC(1.0,  MON_ID__PRESSURE_STATUS);
	}
	return 1;
}

int CObj__MTC_FNC::__DEFINE__ALARM(p_alarm)
{
	DECLARE__ALARM;

	// ...
	CString title;
	title.Format("%s - ", sObject_Name);

	// ...
	int alarm_id;
	CString	alarm_title;
	CString	alarm_msg;
	CStringArray l_act;

	// ...
	{
		alarm_id = ALID__SOFTVENT_TIMEOUT;

		alarm_title  = title;
		alarm_title += "Soft Venting Time-Out !";

		alarm_msg = "Please, check the chamber's pressure.\n";

		l_act.RemoveAll();
		l_act.Add("ABORT");

		ADD__ALARM_EX(alarm_id, alarm_title, alarm_msg, l_act);
	}

	// ...
	{
		alarm_id = ALID__SOFTPUMP_TIMEOUT;

		alarm_title  = title;
		alarm_title += "Soft Pumping Time-Out !";

		alarm_msg = "Please, check the chamber's pressure.\n";

		l_act.RemoveAll();
		l_act.Add("ABORT");

		ADD__ALARM_EX(alarm_id, alarm_title, alarm_msg, l_act);
	}

	// ...
	{
		alarm_id = ALID__VENT_TIMEOUT;

		alarm_title  = title;
		alarm_title += "Venting Time-Out !";

		alarm_msg = "Please, check the chamber's pressure.\n";

		l_act.RemoveAll();
		l_act.Add("ABORT");

		ADD__ALARM_EX(alarm_id, alarm_title, alarm_msg, l_act);
	}

	// ...
	{
		alarm_id = ALID__PUMP_TIMEOUT;

		alarm_title  = title;
		alarm_title += "Pumping Time-Out !";

		alarm_msg = "Please, check the chamber's pressure.\n";

		l_act.RemoveAll();
		l_act.Add("ABORT");

		ADD__ALARM_EX(alarm_id, alarm_title, alarm_msg, l_act);
	}

	// ...
	{
		alarm_id = ALID__GATEOPEN_TIMEOUT;

		alarm_title  = title;
		alarm_title += "Gate Open Time-Out !";

		alarm_msg = "Please, check the MTC's Gate Sensor.\n";

		l_act.RemoveAll();
		l_act.Add("ABORT");

		ADD__ALARM_EX(alarm_id, alarm_title, alarm_msg, l_act);
	}

	// ...
	{
		alarm_id = ALID__GATECLOSE_TIMEOUT;

		alarm_title  = title;
		alarm_title += "Gate Close Time-Out !";

		alarm_msg = "Please, check the MTC's Gate Sensor.\n";

		l_act.RemoveAll();
		l_act.Add("ABORT");

		ADD__ALARM_EX(alarm_id, alarm_title, alarm_msg, l_act);
	}

	// ...
	{
		alarm_id = ALID__MTC_GATE_VALVE_NOT_CLOSE;

		alarm_title  = title;
		alarm_title += "Gate's valve is not close !";

		alarm_msg = "Please, check the state of gate valve. \n";

		l_act.RemoveAll();
		l_act.Add("ABORT");

		ADD__ALARM_EX(alarm_id, alarm_title, alarm_msg, l_act);
	}

	// ...
	{
		alarm_id = ALID__MTC_CHM_PRESSURE_ERROR;

		alarm_title  = title;
		alarm_title += "MTC & Chamber pressure error !";

		alarm_msg = "Please, check the pressure in MTC and Chamber. \n";

		l_act.RemoveAll();
		l_act.Add("ABORT");

		ADD__ALARM_EX(alarm_id, alarm_title, alarm_msg, l_act);
	}

	return 1;
}

int CObj__MTC_FNC::__Define__USER_FUNCTION(CII_DEFINE__FUNCTION *p_fnc_ctrl)
{

	return 1;
}

//-------------------------------------------------------------------------
int CObj__MTC_FNC::__INITIALIZE__OBJECT(p_variable,p_ext_obj_create)
{	
	CString def_name;
	CString def_data;
	CString ch_name;
	CString obj_name;
	CString var_name;
	CString var_data;

	// ...
	{
		CString file_name;
		CString log_msg;

		file_name.Format("%s.log", sObject_Name);

		log_msg  = "\n\n";
		log_msg += "//------------------------------------------------------------------------";

		xLOG_CTRL->CREATE__SUB_DIRECTORY(sObject_Name);
		xLOG_CTRL->SET__PROPERTY(file_name, 24*5, 60);

		xLOG_CTRL->DISABLE__TIME_LOG();
		xLOG_CTRL->WRITE__LOG(log_msg);

		xLOG_CTRL->ENABLE__TIME_LOG();
		xLOG_CTRL->WRITE__LOG("   START   \n");
	}

	// Channel Link ...
	{
		def_name = "CH__SLOT_VALVE";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
		p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
		LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__MON_GATE_STATE, obj_name,var_name);
	}

 	// DI Channel Link ...
 	{
		// CHM
		def_name = "CH__DI_CHM_VAC_SNS";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
		p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
		LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__DI_CHM_VAC_SNS, obj_name,var_name);

		def_name = "CH__DI_CHM_ATM_SNS";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
		p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
		LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__DI_CHM_ATM_SNS, obj_name,var_name);
		
		// MTC
 		def_name = "CH__DI_MTC_VAC_SNS";
 		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
 		p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
 		LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__DI_MTC_VAC_SNS, obj_name,var_name);
 
 		def_name = "CH__DI_MTC_ATM_SNS";
 		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
 		p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
 		LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__DI_MTC_ATM_SNS, obj_name,var_name);

		def_name = "CH__DI_MTC_GATE_OPEN_SNS";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
		p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
		LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__DI_MTC_GATE_OPEN_SNS, obj_name,var_name);

		def_name = "CH__DI_MTC_GATE_CLOSE_SNS";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
		p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
		LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__DI_MTC_GATE_CLOSE_SNS, obj_name,var_name);

		//
		def_name = "CH__DI_SLOT_VLV_CLOSE";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
		p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
		LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__DI_SLOT_VLV_CLOSE, obj_name,var_name);
	}

	// DO Channel Link ...
	{
		def_name = "CH__DO_MTC_GATE_OPEN";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
		p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
		LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__DO_MTC_GATE_OPEN, obj_name,var_name);

		def_name = "CH__DO_MTC_GATE_CLOSE";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
		p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
		LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__DO_MTC_GATE_CLOSE, obj_name,var_name);

		def_name = "CH__DO_MTC_2STAGE_SLOW";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
		p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
		LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__DO_MTC_2STAGE_SLOW, obj_name,var_name);

		def_name = "CH__DO_MTC_2STAGE_FAST";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
		p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
		LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__DO_MTC_2STAGE_FAST, obj_name,var_name);

		def_name = "CH__DO_MTC_CHECK_VV";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
		p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
		LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__DO_MTC_CHECK_VV, obj_name,var_name);

		def_name = "CH__DO_MTC_N2PURGE_SLOW";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
		p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
		LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__DO_MTC_N2PURGE_SLOW, obj_name,var_name);

		def_name = "CH__DO_MTC_N2PURGE_FAST";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
		p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
		LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__DO_MTC_N2PURGE_FAST, obj_name,var_name);
	}

	// SI Channel Link ...
	{
		def_name = "CH__SI_MTC_GAUGE_STATUS";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
		p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
		LINK__EXT_VAR_STRING_CTRL(sEXT_CH__SI_MTC_GAUGE_STATUS_HEXA, obj_name,var_name);

		def_name = "CH__SI_MTC_GAUGE_PRESSURE";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
		p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
		LINK__EXT_VAR_STRING_CTRL(sEXT_CH__SI_MTC_GAUGE_PRESSURE_HEXA, obj_name,var_name);
	}

	// ...
	{
		SCX__SEQ_INFO x_seq_info;

		iActive__SIM_MODE = x_seq_info->Is__SIMULATION_MODE();
	}

	if(iActive__SIM_MODE > 0)
	{
		/*dEXT_CH__PMC_SLIT_VLV_STS->Set__DATA(STR__CLOSE);*/
	}
	return 1;
}

//-------------------------------------------------------------------------
int CObj__MTC_FNC::__CALL__CONTROL_MODE(mode,p_debug,p_variable,p_alarm)
{
	int flag = -1;

	// ...
	{
		CString log_msg;
		log_msg.Format("[%s] Started ...",mode);

		xLOG_CTRL->WRITE__LOG(log_msg);
		sCH__OBJ_MSG->Set__DATA(log_msg);
	}

	// ...
	{
		     IF__CTRL_MODE(sMODE__INIT)						flag = Call__INIT(p_variable,p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__MAINT)					flag = Call__MAINTMODE(p_variable,p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__GATE_OPEN)				flag = Call__GATE_CTL(p_variable,p_alarm, true);
		ELSE_IF__CTRL_MODE(sMODE__GATE_CLOSE)				flag = Call__GATE_CTL(p_variable,p_alarm, false);
		ELSE_IF__CTRL_MODE(sMODE__PUMPING)					flag = Call__PUMPING(p_variable,p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__VENT)						flag = Call__VENT(p_variable,p_alarm);
	}

	if((flag < 0)||(p_variable->Check__CTRL_ABORT() > 0))
	{
		// ...
		{
			CString log_msg;
			log_msg.Format("[%s] Aborted (%1d)",mode,flag);

			xLOG_CTRL->WRITE__LOG(log_msg);
			sCH__OBJ_MSG->Set__DATA(log_msg);
		}

		sCH__OBJ_STATUS->Set__DATA(STR__MAINTMODE);
	}
	else
	{
		CString log_msg;
		log_msg.Format("[%s] Completed ...",mode);

		xLOG_CTRL->WRITE__LOG(log_msg);
		sCH__OBJ_MSG->Set__DATA(log_msg);
	}

	return flag;
}

int CObj__MTC_FNC::__CALL__MONITORING(id,p_variable,p_alarm)
{
	switch(id)
	{
		case MON_ID__PRESSURE_STATUS:
			Mon__PRESSURE_STATUS(p_variable, p_alarm);
			return 1;
	}

	return 1;
}
