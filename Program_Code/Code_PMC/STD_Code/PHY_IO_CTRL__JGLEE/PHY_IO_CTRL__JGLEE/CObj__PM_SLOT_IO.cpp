#include "StdAfx.h"
#include "CObj__PM_SLOT_IO.h"
#include "CObj__PM_SLOT_IO__ALID.h"


//-------------------------------------------------------------------------
CObj__PM_SLOT_IO::CObj__PM_SLOT_IO()
{

}
CObj__PM_SLOT_IO::~CObj__PM_SLOT_IO()
{

}

//-------------------------------------------------------------------------
int CObj__PM_SLOT_IO::__DEFINE__CONTROL_MODE(obj,l_mode)
{
	sObject_Name = obj;

	// ...
	{
		ADD__CTRL_VAR(sMODE__INIT, "INIT");

		ADD__CTRL_VAR(sMODE__DOOR_CLOSE, "DOOR.CLOSE");
		ADD__CTRL_VAR(sMODE__DOOR_OPEN,  "DOOR.OPEN");
	}
	return 1;
}
int CObj__PM_SLOT_IO::__DEFINE__VERSION_HISTORY(version)
{

	return 1;
}


// ...
#define MON_ID__STATUS							1


int CObj__PM_SLOT_IO::__DEFINE__VARIABLE_STD(p_variable)
{
	DECLARE__STD_VARIABLE;

	CCommon_Error__DEF_VARIABLE m_err_def_variable;
	p_variable->Link__DEF_VARIABLE__ERROR_FEEDBACK(&m_err_def_variable);

	// ...
	CString str_name;
	CString item_list;

	// OBJ ...
	{
		str_name = "OBJ.STATUS";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__OBJ_STATUS, str_name);

		str_name = "OBJ.MSG";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__OBJ_MSG, str_name);

		str_name = "OBJ.TIME.COUNT";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__OBJ_TIME_COUNT, str_name);
	}

	// MON.PART ... 
	{
		str_name = "MON.PART.ERROR.ACTIVE";
		STD__ADD_DIGITAL(str_name, "OFF ON");
		LINK__VAR_DIGITAL_CTRL(dCH__MON_PART_ERROR_ACTIVE, str_name);
	}

	// CFG ...
	{
		str_name = "CFG.OPEN.TIMEOUT";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "sec", 0, 3.0, 10.0, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_OPEN_TIMEOUT, str_name);

		str_name = "CFG.CLOSE.TIMEOUT";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "sec", 0, 3.0, 10.0, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_CLOSE_TIMEOUT, str_name);
	}

	// ...
	{
		SCX__SEQ_INFO seq_info;

		iActive__SIM_MODE = seq_info->Is__SIMULATION_MODE();
	}

	// ...
	{
		p_variable->Add__MONITORING_PROC(1.0, MON_ID__STATUS);
	}
	return 1;
}

int CObj__PM_SLOT_IO::__DEFINE__ALARM(p_alarm)
{
	DECLARE__ALARM;

	// ...
	CString title;
	title.Format("%s - ", sObject_Name);

	CString alarm_title;
	CString alarm_msg;
	CStringArray l_act;
	int alarm_id;

	iLIST_ALID__PART.RemoveAll();

	// ...
	{
		alarm_id = ALID__DOOR_OPEN_TIMEOUT;
		iLIST_ALID__PART.Add(alarm_id);

		alarm_title  = title;
		alarm_title += "Slot.Door Open-Timeout !";

		alarm_msg  = "PM Slot Door가 Open 되지 않았습니다.\n";
		alarm_msg += "PM Slot 관련 Sensor를 확인 바랍니다.\n";

		l_act.RemoveAll();
		l_act.Add(ACT__RETRY);
		l_act.Add(ACT__ABORT);

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}
	// ...
	{
		alarm_id = ALID__DOOR_CLOSE_TIMEOUT;
		iLIST_ALID__PART.Add(alarm_id);

		alarm_title  = title;
		alarm_title += "Slot.Door Close-Timeout !";

		alarm_msg  = "PM Slot Door가 Close 되지 않았습니다.\n";
		alarm_msg += "PM Slot 관련 Sensor를 확인 바랍니다.\n";

		l_act.RemoveAll();
		l_act.Add(ACT__RETRY);
		l_act.Add(ACT__ABORT);

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	// ...
	{
		alarm_id = ALID__RF_POWER_STS;
		iLIST_ALID__PART.Add(alarm_id);

		alarm_title  = title;
		alarm_title += "RF POWER STATUS ALARM";

		alarm_msg = "RF Power Status Error.";

		l_act.RemoveAll();
		l_act.Add(ACT__RETRY);
		l_act.Add(ACT__ABORT);

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	return 1;
}

//-------------------------------------------------------------------------
int CObj__PM_SLOT_IO::__INITIALIZE__OBJECT(p_variable,p_ext_obj_create)
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
	int i;

	// LINK : IO Chammel ...
	{
		def_name = "CH__MON_DOOR_STATE";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
		p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
		LINK__EXT_VAR_STRING_CTRL(sEXT_CH__MON_DOOR_STATE, obj_name,var_name);

		//
		def_name = "CH__DO_DOOR_CLOSE";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
		p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
		LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__DO_DOOR_CLOSE, obj_name,var_name);

		def_name = "CH__DO_DOOR_OPEN";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
		p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
		LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__DO_DOOR_OPEN, obj_name,var_name);

		//
		def_name = "CH__DI_DOOR_CLOSE";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
		p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
		LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__DI_DOOR_CLOSE, obj_name,var_name);

		def_name = "CH__DI_DOOR_OPEN";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
		p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
		LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__DI_DOOR_OPEN, obj_name,var_name);
	}

	// OBJ : RFx ...
	{
		def_name = "DATA.RF_SIZE";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, def_data);

		iDATA__RF_SIZE = atoi(def_data);
		if(iDATA__RF_SIZE > _CFG__RF_SIZE)			iDATA__RF_SIZE = _CFG__RF_SIZE;

		for(i=0; i<iDATA__RF_SIZE; i++)
		{
			int id = i + 1;

			def_name.Format("DATA__IO_RF_NAME.%1d", id);
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name, def_data);
			sList__RFx_NAME[i] = def_data;

			def_name.Format("CH__IO_RF_ON_STATUS.%1d", id);
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
			p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
			LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__RFx_ON_STS[i], obj_name,var_name);
		}
	}

	return 1;
}

//-------------------------------------------------------------------------
int CObj__PM_SLOT_IO::__CALL__CONTROL_MODE(mode,p_debug,p_variable,p_alarm)
{
	int flag = -1;

	// ...
	{
		CString log_msg;
		log_msg.Format("Start ... :  [%s]",mode);

		sCH__OBJ_MSG->Set__DATA(log_msg);
		xI_LOG_CTRL->WRITE__LOG(log_msg);
	}

	// ...
	{
			 IF__CTRL_MODE(sMODE__INIT)				flag = Call__INIT(p_variable, p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__DOOR_CLOSE)		flag = Call__DOOR_CLOSE(p_variable, p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__DOOR_OPEN)		flag = Call__DOOR_OPEN(p_variable, p_alarm);
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

int CObj__PM_SLOT_IO::__CALL__MONITORING(id,p_variable,p_alarm)
{
	if(id == MON_ID__STATUS)		Mon__STATUS(p_variable, p_alarm);

	return 1;
}
