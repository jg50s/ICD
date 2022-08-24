#include "StdAfx.h"
#include "CObj__CHM_IO.h"
#include "CObj__CHM_IO__ALID.h"

#include "CCommon_Utility.h"


//-------------------------------------------------------------------------
CObj__CHM_IO::CObj__CHM_IO()
{

}
CObj__CHM_IO::~CObj__CHM_IO()
{

}

//-------------------------------------------------------------------------
int CObj__CHM_IO::__DEFINE__CONTROL_MODE(obj,l_mode)
{
	sObject_Name = obj;

	// ...
	{
		ADD__CTRL_VAR(sMODE__INIT, "INIT");
	}
	return 1;
}
int CObj__CHM_IO::__DEFINE__VERSION_HISTORY(version)
{

	return 1;
}


// ...
#define MON_ID__STATUS							1


int CObj__CHM_IO::__DEFINE__VARIABLE_STD(p_variable)
{
	DECLARE__STD_VARIABLE;

	CCommon_Error__DEF_VARIABLE m_err_def_variable;
	p_variable->Link__DEF_VARIABLE__ERROR_FEEDBACK(&m_err_def_variable);

	// ...
	CString str_name;
	int i;

	// OBJ ...
	{
		str_name = "APP.OBJ.MSG";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__OBJ_MSG, str_name);

		str_name = "APP.OBJ.STATUS";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__OBJ_STATUS, str_name);
	}

	// CFG ...
	{
		str_name = "CFG.PROCESS_MANOMETER.INTERLOCK.HIGH.LIMIT.PRESSURE";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "torr", 0, 10, 100, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_INTERLOCK_HIGH_LIMIT_PRESSURE, str_name);

		for(i=0; i<_CFG__PROC_GAUGE_SIZE; i++)
		{
			int id = i + 1;

			str_name.Format("CFG.PROCESS_MANOMETER.MAX_PRESSURE.mTORR.%1d", id);
			STD__ADD_ANALOG_WITH_X_OPTION(str_name, "mtorr", 0, 1, 10000, "");
			LINK__VAR_ANALOG_CTRL(aCH__CFG_PROCESS_MANOMETER_MAX_PRESSURE_mTORR_X[i], str_name);

			str_name.Format("CFG.PROCESS_MANOMETER.LIMIT_PRESSURE.mTORR.%1d", id);
			STD__ADD_ANALOG_WITH_X_OPTION(str_name, "mtorr", 0, 0, 100000, "");
			LINK__VAR_ANALOG_CTRL(aCH__CFG_PROCESS_MANOMETER_LIMIT_PRESSURE_mTORR_X[i], str_name);
		}
	}

	// MON ...
	{
		str_name = "MON.CHM.PRESSURE.DISPLAY";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_CHM_PRESSURE_DISPLAY, str_name);
	}

	// ...
	{
		p_variable->Add__MONITORING_PROC(1.0, MON_ID__STATUS);
	}
	return 1;
}

int CObj__CHM_IO::__DEFINE__ALARM(p_alarm)
{
	DECLARE__ALARM;

	// ...
	CString title;
	title.Format("%s - ", sObject_Name);

	CString alarm_title;
	CString alarm_msg;
	CStringArray l_act;
	int alarm_id;

	// ...
	{
		alarm_id = ALID__MONITORING_INTERLOCK__DISABLE;

		alarm_title  = title;
		alarm_title += "Monitoring Interlock Disable !";

		alarm_msg  = "Config Page에서 Monitoring Interlock를 Disable 설정했습니다.\n";
		alarm_msg += "이 Object에서 관리하는 모든 Monitoring Alarm들이 정지 됩니다.\n";

		l_act.RemoveAll();
		l_act.Add("CHECK");

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	return 1;
}

//-------------------------------------------------------------------------
int CObj__CHM_IO::__INITIALIZE__OBJECT(p_variable,p_ext_obj_create)
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

	// ...
	CCommon_Utility x_utility;
	bool def_check;

	// OBJ DB_INF ...
	{
		def_name = "OBJ__DB_INF";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, obj_name);

		//
		var_name = "SLIT.VLV.STS";
		LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__CHM_SLOT_VLV_STATE, obj_name,var_name);

		//
		var_name = "CHM.PRESSURE.VALUE";
		LINK__EXT_VAR_STRING_CTRL(sEXT_CH__CHM_PRESSURE_VALUE, obj_name,var_name);

		var_name = "CHM.PRESSURE.mTORR";
		LINK__EXT_VAR_STRING_CTRL(sEXT_CH__CHM_PRESSURE_mTORR, obj_name,var_name);

		//
		var_name = "CHM.VAC.SNS";
		LINK__EXT_VAR_STRING_CTRL(sEXT_CH__CHM_VAC_SNS, obj_name,var_name);

		var_name = "CHM.ATM.SNS";
		LINK__EXT_VAR_STRING_CTRL(sEXT_CH__CHM_ATM_SNS, obj_name,var_name);

		//
		var_name = "PMP.PRESSURE.VALUE";
		LINK__EXT_VAR_STRING_CTRL(sEXT_CH__PMP_PRESSURE_VALUE, obj_name,var_name);

		var_name = "PMP.PRESSURE.STATE";
		LINK__EXT_VAR_STRING_CTRL(sEXT_CH__PMP_PRESSURE_STATE, obj_name,var_name);

		var_name = "PMP.VAC.SNS";
		LINK__EXT_VAR_STRING_CTRL(sEXT_CH__PMP_VAC_SNS, obj_name,var_name);
	}

	// OBJ DB_SYS ...
	{
		def_name = "OBJ__DB_SYS";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, obj_name);

		//
		var_name = "SIM.PRESSURE.TORR";
		LINK__EXT_VAR_STRING_CTRL(sEXT_CH__SIM_PRESSURE_TORR, obj_name,var_name);

		//
		var_name = "CFG.INTERLOCK.USE.MODE";
		LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__CFG_INTERLOCK_USE_MODE, obj_name,var_name);

		var_name = "CFG.INTERLOCK.USE.CHM_MANOMETER_ISO";
		LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__CFG_INTERLOCK_USE__CHM_MANOMETER_ISO, obj_name,var_name);

		//
		var_name = "SYSTEM.SETUP.REQ";
		LINK__EXT_VAR_STRING_CTRL(sEXT_CH__SYSTEM_SETUP_REQ, obj_name,var_name);
	}

	// LINK : IO_Chammel
	{
		// ATM & VAC SNS ...
		{
			def_name = "CH__DI_VAC_SNS";
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
			p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
			LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__DI_VAC_SNS, obj_name,var_name);

			def_name = "CH__DI_ATM_SNS";
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
			p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
			LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__DI_ATM_SNS, obj_name,var_name);
		}

		// SLOT.VLV SNS ...
		{
			def_name = "CH__DI_SLOT_VLV_OPEN";
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name, def_data);

			def_check = x_utility.Check__Link(def_data);
			bActive__DI_SLOT_VLV_OPEN = def_check;

			if(def_check)
			{
				p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(def_data, obj_name,var_name);
				LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__DI_SLOT_VLV_OPEN, obj_name,var_name);
			}
			
			//
			def_name = "CH__DI_SLOT_VLV_CLOSE";
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name, def_data);

			def_check = x_utility.Check__Link(def_data);
			bActive__DI_SLOT_VLV_CLOSE = def_check;

			if(def_check)
			{
				p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(def_data, obj_name,var_name);
				LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__DI_SLOT_VLV_CLOSE, obj_name,var_name);
			}
		}

		//
		def_name = "CH.DO_CHM_CHECK_VLV";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);

		def_check = x_utility.Check__Link(ch_name);
		bActive__DO_CHM_CHECK_VLV = def_check;

		if(def_check)
		{
			p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
			LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__DO_CHM_CHECK_VLV, obj_name,var_name);
		}

		//
		def_name = "DATA.PRC_GAUGE_SIZE";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, def_data);

		iSIZE__PROC_GAUGE = atoi(def_data);
		if(iSIZE__PROC_GAUGE > _CFG__PROC_GAUGE_SIZE)			iSIZE__PROC_GAUGE = _CFG__PROC_GAUGE_SIZE;

		for(i=0; i<iSIZE__PROC_GAUGE; i++)
		{
			int id = i + 1;

			def_name.Format("CH.DO_PRC_GAUGE_VLV.%1d", id);
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
			p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
			LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__DO_PROC_GAUGE_ISO_VLV_X[i], obj_name,var_name);

			//
			def_name.Format("CH.AI_PRC_GAUGE_TORR.%1d", id);
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);

			def_check = x_utility.Check__Link(ch_name);
			bActive__AI_PROC_GAUGE_TORR_X[i] = def_check;

			if(def_check)
			{
				p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
				LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__AI_PROC_GAUGE_TORR_X[i], obj_name,var_name);
			}

			//
			def_name.Format("CH.AI_PRC_GAUGE_mTORR.%1d", id);
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);

			def_check = x_utility.Check__Link(ch_name);
			bActive__AI_PROC_GAUGE_mTORR_X[i] = def_check;

			if(def_check)
			{
				p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
				LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__AI_PROC_GAUGE_mTORR_X[i], obj_name,var_name);
			}
		}

		// CHAMBER.GAUGE ...
		{
			def_name = "CH__AI_CHM_GAUGE_TORR";
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);

			def_check = x_utility.Check__Link(ch_name);
			bActive__AI_CHM_GAUGE_TORR = def_check;

			if(def_check)
			{
				p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
				LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__AI_CHM_GAUGE_TORR, obj_name,var_name);
			}

		}

		// FORELINE.GAUGE ...
		{
			def_name = "CH__AI_FORELINE_GAUGE_TORR";
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);

			def_check = x_utility.Check__Link(ch_name);
			bActive__AI_FORELINE_GAUGE_TORR = def_check;

			if(def_check)
			{
				p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
				LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__AI_FORELINE_GAUGE_TORR, obj_name,var_name);
			}

			//
			def_name = "CH__AI_FORELINE_GAUGE_mTORR";
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);

			def_check = x_utility.Check__Link(ch_name);
			bActive__AI_FORELINE_GAUGE_mTORR = def_check;

			if(def_check)
			{
				p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
				LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__AI_FORELINE_GAUGE_mTORR, obj_name,var_name);
			}
		}
	}

	// RF INFO ...
	{
		def_name = "CH__RF_TOTAL_ON_STATE";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
		p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
		LINK__EXT_VAR_STRING_CTRL(sEXT_CH__RF_TOTAL_ON_STATE, obj_name,var_name);

		//
		def_name = "DATA.RF_SIZE";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, def_data);
		iDATA__RF_SIZE = atoi(def_data);

		if(iDATA__RF_SIZE > _CFG__RF_SIZE)			iDATA__RF_SIZE = _CFG__RF_SIZE;

		for(i=0; i<iDATA__RF_SIZE; i++)
		{
			def_name.Format("CH__RF_ON_STATE.%1d", i+1);
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
			p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
			LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__RF_ON_STATE_X[i], obj_name,var_name);
		}
	}

	/*
	// LINK : State Channel
	{
		def_name = "CH__PROC_STATE";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
		p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
		LINK__EXT_VAR_STRING_CTRL(sEXT_CH__PROC_STATE, obj_name,var_name);
	}
	*/

	// ...
	{
		SCX__SEQ_INFO seq_info;

		iActive__SIM_MODE = seq_info->Is__SIMULATION_MODE();
	}
	return 1;
}

//-------------------------------------------------------------------------
int CObj__CHM_IO::__CALL__CONTROL_MODE(mode,p_debug,p_variable,p_alarm)
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

int CObj__CHM_IO::__CALL__MONITORING(id,p_variable,p_alarm)
{
	if(id == MON_ID__STATUS)		Mon__STATUS(p_variable, p_alarm);

	return 1;
}
