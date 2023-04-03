#include "StdAfx.h"
#include "CObj__LIFT_PIN_IO.h"

#include "CCommon_Utility.h"


//-------------------------------------------------------------------------
CObj__LIFT_PIN_IO::CObj__LIFT_PIN_IO()
{

}
CObj__LIFT_PIN_IO::~CObj__LIFT_PIN_IO()
{

}


//-------------------------------------------------------------------------
int CObj__LIFT_PIN_IO::__DEFINE__CONTROL_MODE(obj,l_mode)
{
	sObject_Name = obj;

	// ...
	{
		ADD__CTRL_VAR(sMODE__INIT, "INIT");

		//
		ADD__CTRL_VAR(sMODE__UP,     "UP");
		ADD__CTRL_VAR(sMODE__DOWN,   "DOWN");
		ADD__CTRL_VAR(sMODE__MIDDLE, "MIDDLE");

		//
		ADD__CTRL_VAR(sMODE__TRANSFER_UP,   "TRANSFER_UP");
		ADD__CTRL_VAR(sMODE__TRANSFER_DOWN, "TRANSFER_DOWN");

		ADD__CTRL_VAR(sMODE__MIDDLE_UP,   "MIDDLE_UP");
		ADD__CTRL_VAR(sMODE__MIDDLE_DOWN, "MIDDLE_DOWN");

		//
		ADD__CTRL_VAR(sMODE__CYCLE_UpToDown,	 "CYCLE_UpToDown");
		ADD__CTRL_VAR(sMODE__CYCLE_MiddleToDown, "CYCLE_MiddleToDown");
	}

	return 1;
}
int CObj__LIFT_PIN_IO::__DEFINE__VERSION_HISTORY(version)
{

	return 1;
}


// ...
#define MON_ID__STATE_CHECK						1


int CObj__LIFT_PIN_IO::__DEFINE__VARIABLE_STD(p_variable)
{
	DECLARE__STD_VARIABLE;

	// ...
	CCommon_Error__DEF_VARIABLE m_err_def_variable;
	p_variable->Link__DEF_VARIABLE__ERROR_FEEDBACK(&m_err_def_variable);

	// ...
	CString str_name;
	int i;

	// OBJ ...
	{
		str_name = "OBJ.MSG";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__OBJ_MSG, str_name);

		str_name = "OBJ.TIMER";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__OBJ_TIMER, str_name);
	}

	// MON.PART ... 
	{
		str_name = "MON.PIN.ERROR.ACTIVE";
		STD__ADD_DIGITAL(str_name, "OFF ON");
		LINK__VAR_DIGITAL_CTRL(dCH__MON_PIN_ERROR_ACTIVE, str_name);
	}

	// MON ...
	{
		// ACT.NAME ...
		{
			str_name = "MON.ACT.NAME";
			STD__ADD_STRING(str_name);
			LINK__VAR_STRING_CTRL(sCH__MON_ACT_NAME, str_name);
		}

		// LIFT_PIN ...
		{
			str_name = "MON.LIFT.STATE";
			STD__ADD_STRING(str_name);
			LINK__VAR_STRING_CTRL(sCH__MON_LIFT_STATE, str_name);

			str_name = "LIFT.STATUS.LINK";
			STD__ADD_STRING(str_name);
			LINK__VAR_STRING_CTRL(sCH__LIFT_STS_LINK, str_name);
		}

		for(i=0; i<_CFG__PIN_SIZE; i++)
		{
			int id = i + 1;

			str_name.Format("MON.POS_UP.ACTIVE.PIN.%1d", id);
			STD__ADD_STRING(str_name);
			LINK__VAR_STRING_CTRL(sCH__MON_POS_UP_ACTIVE_PIN_X[i], str_name);

			str_name.Format("MON.POS_DOWN.ACTIVE.PIN.%1d", id);
			STD__ADD_STRING(str_name);
			LINK__VAR_STRING_CTRL(sCH__MON_POS_DOWN_ACTIVE_PIN_X[i], str_name);

			str_name.Format("MON.POS_MIDDLE.ACTIVE.PIN.%1d", id);
			STD__ADD_STRING(str_name);
			LINK__VAR_STRING_CTRL(sCH__MON_POS_MIDDLE_ACTIVE_PIN_X[i], str_name);
		}
	}

	// CFG ...
	{
		// SENSOR.CHECK ...
		{
			str_name = "CFG.LIFT_PIN.SENSOR.CHECK";
			STD__ADD_DIGITAL_WITH_X_OPTION(str_name, "YES NO", "");
			LINK__VAR_DIGITAL_CTRL(dCH__CFG_LIFT_PIN_SENSOR_CHECK, str_name);
		}

		// TIMEOUT ...
		{
			str_name = "CFG.LIFT.PIN.ACTION.TIMEOUT";
			STD__ADD_ANALOG_WITH_X_OPTION(str_name, "sec", 0, 1, 60, "");
			LINK__VAR_ANALOG_CTRL(aCH__CFG_LIFT_PIN_ACTION_TIMEOUT, str_name);
		}

		// ESC.VOLTAGE ...
		{
			str_name = "CFG.ESC.VOLTAGE.PIN.UP.THRESHOLD";
			STD__ADD_ANALOG_WITH_X_OPTION(str_name, "V", 0, 0, 100, "");
			LINK__VAR_ANALOG_CTRL(aCH__CFG_ESC_VOLTAGE_PIN_UP_THRESHOLD, str_name);
		}

		// PIN.POS ...
		for(i=0; i<_CFG__PIN_SIZE; i++)
		{
			int id = i + 1;

			str_name.Format("CFG.DOWN_POS.MIN.PIN.%1d", id);
			STD__ADD_ANALOG_WITH_X_OPTION(str_name, "mm", 2, -100, 4000, "");
			LINK__VAR_ANALOG_CTRL(aCH__CFG_DOWN_POS_MIN__PIN_X[i], str_name);

			str_name.Format("CFG.DOWN_POS.MAX.PIN.%1d", id);
			STD__ADD_ANALOG_WITH_X_OPTION(str_name, "mm", 2, -100, 4000, "");
			LINK__VAR_ANALOG_CTRL(aCH__CFG_DOWN_POS_MAX__PIN_X[i], str_name);

			//
			str_name.Format("CFG.UP_POS.MIN.PIN.%1d", id);
			STD__ADD_ANALOG_WITH_X_OPTION(str_name, "mm", 2, -100, 4000, "");
			LINK__VAR_ANALOG_CTRL(aCH__CFG_UP_POS_MIN__PIN_X[i], str_name);

			str_name.Format("CFG.UP_POS.MAX.PIN.%1d", id);
			STD__ADD_ANALOG_WITH_X_OPTION(str_name, "mm", 2, -100, 4000, "");
			LINK__VAR_ANALOG_CTRL(aCH__CFG_UP_POS_MAX__PIN_X[i], str_name);

			//
			str_name.Format("CFG.MIDDLE_POS.MIN.PIN.%1d", id);
			STD__ADD_ANALOG_WITH_X_OPTION(str_name, "mm", 2, -100, 4000, "");
			LINK__VAR_ANALOG_CTRL(aCH__CFG_MIDDLE_POS_MIN__PIN_X[i], str_name);

			str_name.Format("CFG.MIDDLE_POS.MAX.PIN.%1d", id);
			STD__ADD_ANALOG_WITH_X_OPTION(str_name, "mm", 2, -100, 4000, "");
			LINK__VAR_ANALOG_CTRL(aCH__CFG_MIDDLE_POS_MAX__PIN_X[i], str_name);
		}
	}

	// ...
	{
		str_name = "UPDOWN_TEST.CFG.CYCLE_COUNT";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "count",0,1,99999,"");
		LINK__VAR_ANALOG_CTRL(aCH__UPDOWN_TEST_CFG_CYCLE_COUNT, str_name);

		str_name = "UPDOWN_TEST.CUR.CYCLE_COUNT";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__UPDOWN_TEST_CUR_CYCLE_COUNT, str_name);

		//
		str_name = "UPDOWN_TEST.CFG.UP_STAY_SEC";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "sec",0,0,1000,"");
		LINK__VAR_ANALOG_CTRL(aCH__UPDOWN_TEST_CFG_UP_STAY_SEC, str_name);

		str_name = "UPDOWN_TEST.CUR.UP_STAY_SEC";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__UPDOWN_TEST_CUR_UP_STAY_SEC, str_name);

		//
		str_name = "UPDOWN_TEST.CFG.DOWN_STAY_SEC";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "sec",0,0,1000,"");
		LINK__VAR_ANALOG_CTRL(aCH__UPDOWN_TEST_CFG_DOWN_STAY_SEC, str_name);

		str_name = "UPDOWN_TEST.CUR.DOWN_STAY_SEC";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__UPDOWN_TEST_CUR_DOWN_STAY_SEC, str_name);

		//
		str_name = "UPDOWN_TEST.MSG";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__UPDOWN_TEST_MSG, str_name);
	}

	// Result...
	{
		// Down <-> Up ...
		{
			str_name = "RESULT.MOVE.DOWN_UP.NOW.UP";
			STD__ADD_STRING(str_name);
			LINK__VAR_STRING_CTRL(sCH__RESULT_MOVE_DOWN_UP_NOW_UP, str_name);

			str_name = "RESULT.MOVE.DOWN_UP.AVG.UP";
			STD__ADD_STRING(str_name);
			LINK__VAR_STRING_CTRL(sCH__RESULT_MOVE_DOWN_UP_AVG_UP, str_name);

			str_name = "RESULT.MOVE.DOWN_UP.MIN.UP";
			STD__ADD_STRING(str_name);
			LINK__VAR_STRING_CTRL(sCH__RESULT_MOVE_DOWN_UP_MIN_UP, str_name);

			str_name = "RESULT.MOVE.DOWN_UP.MAX.UP";
			STD__ADD_STRING(str_name);
			LINK__VAR_STRING_CTRL(sCH__RESULT_MOVE_DOWN_UP_MAX_UP, str_name);

			//
			str_name = "RESULT.MOVE.DOWN_UP.NOW.DOWN";
			STD__ADD_STRING(str_name);
			LINK__VAR_STRING_CTRL(sCH__RESULT_MOVE_DOWN_UP_NOW_DOWN, str_name);

			str_name = "RESULT.MOVE.DOWN_UP.AVG.DOWN";
			STD__ADD_STRING(str_name);
			LINK__VAR_STRING_CTRL(sCH__RESULT_MOVE_DOWN_UP_AVG_DOWN, str_name);

			str_name = "RESULT.MOVE.DOWN_UP.MIN.DOWN";
			STD__ADD_STRING(str_name);
			LINK__VAR_STRING_CTRL(sCH__RESULT_MOVE_DOWN_UP_MIN_DOWN, str_name);

			str_name = "RESULT.MOVE.DOWN_UP.MAX.DOWN";
			STD__ADD_STRING(str_name);
			LINK__VAR_STRING_CTRL(sCH__RESULT_MOVE_DOWN_UP_MAX_DOWN, str_name);
		}

		// Down <-> Middle ...
		{
			str_name = "RESULT.MOVE.DOWN_MIDDLE.NOW.MIDDLE";
			STD__ADD_STRING(str_name);
			LINK__VAR_STRING_CTRL(sCH__RESULT_MOVE_DOWN_MIDDLE_NOW_MIDDLE, str_name);

			str_name = "RESULT.MOVE.DOWN_MIDDLE.AVG.MIDDLE";
			STD__ADD_STRING(str_name);
			LINK__VAR_STRING_CTRL(sCH__RESULT_MOVE_DOWN_MIDDLE_AVG_MIDDLE, str_name);

			str_name = "RESULT.MOVE.DOWN_MIDDLE.MIN.MIDDLE";
			STD__ADD_STRING(str_name);
			LINK__VAR_STRING_CTRL(sCH__RESULT_MOVE_DOWN_MIDDLE_MIN_MIDDLE, str_name);

			str_name = "RESULT.MOVE.DOWN_MIDDLE.MAX.MIDDLE";
			STD__ADD_STRING(str_name);
			LINK__VAR_STRING_CTRL(sCH__RESULT_MOVE_DOWN_MIDDLE_MAX_MIDDLE, str_name);

			//
			str_name = "RESULT.MOVE.DOWN_MIDDLE.NOW.DOWN";
			STD__ADD_STRING(str_name);
			LINK__VAR_STRING_CTRL(sCH__RESULT_MOVE_DOWN_MIDDLE_NOW_DOWN, str_name);

			str_name = "RESULT.MOVE.DOWN_MIDDLE.AVG.DOWN";
			STD__ADD_STRING(str_name);
			LINK__VAR_STRING_CTRL(sCH__RESULT_MOVE_DOWN_MIDDLE_AVG_DOWN, str_name);

			str_name = "RESULT.MOVE.DOWN_MIDDLE.MIN.DOWN";
			STD__ADD_STRING(str_name);
			LINK__VAR_STRING_CTRL(sCH__RESULT_MOVE_DOWN_MIDDLE_MIN_DOWN, str_name);

			str_name = "RESULT.MOVE.DOWN_MIDDLE.MAX.DOWN";
			STD__ADD_STRING(str_name);
			LINK__VAR_STRING_CTRL(sCH__RESULT_MOVE_DOWN_MIDDLE_MAX_DOWN, str_name);
		}
	}

	// ...
	{
		p_variable->Add__MONITORING_PROC(1.0, MON_ID__STATE_CHECK);
	}
	return 1;
}

int CObj__LIFT_PIN_IO::__DEFINE__ALARM(p_alarm)
{
	DECLARE__ALARM;

	// ...
	CString title;
	title.Format("%s - ",sObject_Name);

	CString alarm_title;
	CString alarm_msg;
	CStringArray l_act;
	int alarm_id;

	iLIST_ALID__PIN.RemoveAll();

	// ...
	{
		alarm_id = ALID__PIN_LIFTER_ALARM;
		iLIST_ALID__PIN.Add(alarm_id);

		alarm_title  = title;
		alarm_title += " PIN LIFTER - Action Timeout ALARM.";

		alarm_msg = "Lifter pin action does not completed ! \n";
		alarm_msg = "Please, Check the I/O Module & PIN Lifter.";

		l_act.RemoveAll();
		l_act.Add("CHECK");

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	// ...
	{
		alarm_id = ALID__PIN_LIFTER_ALARM__TRANSFER;
		iLIST_ALID__PIN.Add(alarm_id);

		alarm_title  = title;
		alarm_title += " PIN LIFTER - Action Timeout ALARM.";

		alarm_msg = "Lifter pin action does not completed ! \n";
		alarm_msg = "Please, Check the I/O Module & PIN Lifter.";

		l_act.RemoveAll();
		l_act.Add("RETRY");
		l_act.Add("ABORT");

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	// ...
	{
		alarm_id = ALID__CHUCKING_STATUS_ALARM;
		iLIST_ALID__PIN.Add(alarm_id);

		alarm_title  = title;
		alarm_title += " PIN LIFTER - Chuck Status ALARM.";

		alarm_msg = "Pin Lifter can not pperate.\n";
		alarm_msg = "Please, Check the Chucking Status.";

		l_act.RemoveAll();
		l_act.Add("CHECK");

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	// ...
	{
		alarm_id = ALID__ESC_VOLT_PIN_UP_ALARM;
		iLIST_ALID__PIN.Add(alarm_id);

		alarm_title  = title;
		alarm_title += " PIN LIFTER - ESC VOLTAGE PIN UP THRESHOLD ALARM.";

		alarm_msg = "Pin Lifter can not pperate.\n";
		alarm_msg = "Please, Check ESC Voltage.";

		l_act.RemoveAll();
		l_act.Add("CHECK");

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	return 1;
}


//-------------------------------------------------------------------------
int CObj__LIFT_PIN_IO::__INITIALIZE__OBJECT(p_variable,p_ext_obj_create)
{	
	// ...
	{
		CString file_name;
		CString log_msg;

		file_name.Format("%s_App.log", sObject_Name);

		log_msg  = "\n\n";
		log_msg += "//------------------------------------------------------------------------";

		xLOG_CTRL->CREATE__SUB_DIRECTORY(sObject_Name);
		xLOG_CTRL->SET__PROPERTY(file_name,12*1,60);

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

	// IO LINK ...
	{
		// PIN.STATE ...
		{
			def_name = "CH__LIFT_PIN_STATE";
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
			p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
			LINK__EXT_VAR_STRING_CTRL(sEXT_CH__LIFT_PIN_STATE, obj_name,var_name);
		}

		// ESC.CHUCK_STATE ...
		{
			def_name = "CH__ESC_CHUCK_STATE";
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);

			def_check = x_utility.Check__Link(ch_name);
			bActive__ESC_CHUCK_STATE = def_check;

			if(def_check)
			{
				p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
				LINK__EXT_VAR_STRING_CTRL(sEXT_CH__ESC_CHUCK_STATE, obj_name,var_name);
			}
		}
		// ESC.AI_VOLTAGE ...
		{
			def_name = "DATA__ESC_CH_SIZE";
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name, def_data);

			iDATA__ESC_CH_SIZE = atoi(def_data);
			if(iDATA__ESC_CH_SIZE > _CFG__ESC_CH_SIZE)			iDATA__ESC_CH_SIZE = _CFG__ESC_CH_SIZE;

			for(i=0; i<iDATA__ESC_CH_SIZE; i++)
			{
				def_name.Format("CH__ESC_AI_VOLTAGE.%1d", i+1);
				p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
				p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
				LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__ESC_AI_VOLTAGE_X[i], obj_name,var_name);
			}
		}
	}

	// DATA.TYPE ...
	{
		def_name = "DATA__PIN_CTRL_TYPE";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, def_data);

		if(def_data.CompareNoCase("OBJECT") == 0)			iActive__CONTROL_TYPE = _CTRL_TYPE__OBJ;
		else												iActive__CONTROL_TYPE = _CTRL_TYPE__IO;
	}

	if(iActive__CONTROL_TYPE == _CTRL_TYPE__OBJ)
	{
		def_name = "LINK__OBJ_NAME";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, obj_name);

		pLINK_OBJ__CTRL = p_ext_obj_create->Create__OBJECT_CTRL(obj_name);

		//
		def_name = "OBJ_MODE.INIT";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, def_data);
		sLINK_MODE__INIT = def_data;

		def_name = "OBJ_MODE.UP";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, def_data);
		sLINK_MODE__PIN_UP = def_data;

		def_name = "OBJ_MODE.DOWN";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, def_data);
		sLINK_MODE__PIN_DOWN = def_data;

		def_name = "OBJ_MODE.MIDDLE";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, def_data);
		sLINK_MODE__PIN_MIDDLE = def_data;
	}
	else 	// IO
	{
		// TRANSFER.PIN_UP ...
		{
			def_name = "CH__DO_TRANSFER_PIN_UP";
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
			p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
			LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__DO_TRANSFER_PIN_UP, obj_name,var_name);
		}
		// TRANSFER.PIN_DOWN ...
		{
			def_name = "CH__DO_TRANSFER_PIN_DOWN";
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
			p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
			LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__DO_TRANSFER_PIN_DOWN, obj_name,var_name);
		}

		// MIDDLE.PUN_UP ...
		{
			def_name = "CH__DO_MIDDLE_PIN_UP";
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);

			def_check = x_utility.Check__Link(ch_name);
			bActive__DO_MIDDLE_PIN_UP = def_check;

			if(def_check)
			{
				p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);	
				LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__DO_MIDDLE_PIN_UP, obj_name, var_name);
			}
		}
		// MIDDLE.PIN_DOWN ...
		{
			def_name = "CH__DO_MIDDLE_PIN_DOWN";
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);

			def_check = x_utility.Check__Link(ch_name);
			bActive__DO_MIDDLE_PIN_DOWN = def_check;

			if(def_check)
			{
				p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);	
				LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__DO_MIDDLE_PIN_DOWN, obj_name, var_name);
			}
		}
	}

	// PIN.SENSOR ...
	{
		def_name = "DATA__PIN_SENSOR_CHECK_MODE";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, def_data);

		if(def_data.CompareNoCase("TOP") == 0)				iDATA__PIN_SNS_CHECK_MODE = _PIN_CHECK_MODE__TOP;
		else												iDATA__PIN_SNS_CHECK_MODE = _PIN_CHECK_MODE__STD;

		//
		def_name = "DATA__DI_PIN_SENSOR";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, def_data);

		if(def_data.CompareNoCase(STR__YES) == 0)			iDATA__PIN_SNS_TYPE = _PIN_TYPE__DI_SNS;
		else												iDATA__PIN_SNS_TYPE = _PIN_TYPE__AI_SNS;

		// DI.SNS ...
		if(iDATA__PIN_SNS_TYPE == _PIN_TYPE__DI_SNS)
		{
			def_name = "CH__DI_PIN_UP";
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
			p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
			LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__DI_PIN_UP, obj_name,var_name);

			def_name = "CH__DI_PIN_MIDDLE";
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
			p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
			LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__DI_PIN_MIDDLE, obj_name,var_name);

			def_name = "CH__DI_PIN_DOWN";
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
			p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
			LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__DI_PIN_DOWN, obj_name,var_name);
		}
		else	// POS_PIN ...
		{
			def_name = "DATA__PIN_SIZE";
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name, def_data);
			
			iSIZE__AI_PIN__POS = atoi(def_data);
			if(iSIZE__AI_PIN__POS > _CFG__PIN_SIZE)			iSIZE__AI_PIN__POS = _CFG__PIN_SIZE;

			for(i=0; i<iSIZE__AI_PIN__POS; i++)
			{
				int id = i + 1;

				def_name.Format("CH__AI_PIN_POS.%1d", id);
				p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
				p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
				LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__AI_PIN_POS_X[i], obj_name,var_name);
			}
		}
	}

	// ...
	{
		SCX__SEQ_INFO x_seq_info;

		iActive__SIM_MODE = x_seq_info->Is__SIMULATION_MODE();
	}

	// ...
	{
		sCH__MON_LIFT_STATE->Link__UPPER_OBJECT_ABORT(sObject_Name);
	}
	return 1;
}


//-------------------------------------------------------------------------
int CObj__LIFT_PIN_IO::__CALL__CONTROL_MODE(mode,p_debug,p_variable,p_alarm)
{
	int flag = -1;

	// ...
	{
		CString log_msg;
		log_msg.Format("Start ... :  [%s]",mode);

		sCH__OBJ_MSG->Set__DATA(log_msg);
		xLOG_CTRL->WRITE__LOG(log_msg);
	}

	// ...
	SCX__ASYNC_TIMER_CTRL x_timer_ctrl;

	x_timer_ctrl->REGISTER__COUNT_CHANNEL_NAME(sCH__OBJ_TIMER->Get__CHANNEL_NAME());
	x_timer_ctrl->START__COUNT_UP(9999);

	// ...
	{
		     IF__CTRL_MODE(sMODE__INIT)							flag = Call__INIT(p_variable, p_alarm);

		ELSE_IF__CTRL_MODE(sMODE__UP)							flag = Call__UP(p_variable, p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__DOWN)							flag = Call__DOWN(p_variable, p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__MIDDLE)						flag = Call__MIDDLE(p_variable, p_alarm);

		ELSE_IF__CTRL_MODE(sMODE__TRANSFER_UP)					flag = Call__TRANSFER_UP(p_variable, p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__TRANSFER_DOWN)				flag = Call__TRANSFER_DOWN(p_variable, p_alarm);

		ELSE_IF__CTRL_MODE(sMODE__MIDDLE_UP)					flag = Call__MIDDLE_UP(p_variable, p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__MIDDLE_DOWN)					flag = Call__MIDDLE_DOWN(p_variable, p_alarm);

		ELSE_IF__CTRL_MODE(sMODE__CYCLE_UpToDown)				flag = Call__CYCLE_UpToDown(p_variable, p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__CYCLE_MiddleToDown)			flag = Call__CYCLE_MiddleToDown(p_variable, p_alarm);
	}

	sCH__MON_ACT_NAME->Set__DATA("");

	if((flag < 0)||(p_variable->Check__CTRL_ABORT() > 0))
	{
		CString log_msg;
		log_msg.Format("Aborted ... :  [%s]",mode);

		sCH__OBJ_MSG->Set__DATA(log_msg);
		xLOG_CTRL->WRITE__LOG(log_msg);		
	}
	else
	{
		CString log_msg;
		log_msg.Format("Completed ... :  [%s]",mode);

		sCH__OBJ_MSG->Set__DATA(log_msg);
		xLOG_CTRL->WRITE__LOG(log_msg);
	}

	dCH__CFG_LIFT_PIN_SENSOR_CHECK->Set__DATA(STR__YES);
	return flag;
}

int CObj__LIFT_PIN_IO::__CALL__MONITORING(id,p_variable,p_alarm)
{
	if(id == MON_ID__STATE_CHECK)		Mon__STATE_CHECK(p_variable, p_alarm);

	return 1;
}
