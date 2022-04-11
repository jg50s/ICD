#include "StdAfx.h"
#include "CObj__STEP_STD.h"

#include "CCommon_Utility.h"


//-------------------------------------------------------------------------
CObj__STEP_STD::CObj__STEP_STD()
{

}
CObj__STEP_STD::~CObj__STEP_STD()
{

}

//-------------------------------------------------------------------------
int CObj__STEP_STD::__DEFINE__CONTROL_MODE(obj,l_mode)
{
	sObject_Name = obj;

	// ...
	{
		ADD__CTRL_VAR(sMODE__INIT,	"INIT");

		ADD__CTRL_VAR(sMODE__READY,	"READY");
		ADD__CTRL_VAR(sMODE__START, "START");
		ADD__CTRL_VAR(sMODE__PROC,	"PROC");
		ADD__CTRL_VAR(sMODE__ABORT,	"ABORT");
		ADD__CTRL_VAR(sMODE__END,	"END");
	}
	return 1;
}
int CObj__STEP_STD::__DEFINE__VERSION_HISTORY(version)
{

	return 1;
}


// ...
#define  APP_DSP__DISABLE_ENABLE					\
	"DISABLE ENABLE"

#define  APP_DSP__ENABLE_DISABLE					\
	"ENABLE DISABLE"


int CObj__STEP_STD::__DEFINE__VARIABLE_STD(p_variable)
{
	DECLARE__STD_VARIABLE;

	// ...
	CCommon_Error__DEF_VARIABLE m_err_def_variable;
	p_variable->Link__DEF_VARIABLE__ERROR_FEEDBACK(&m_err_def_variable);

	// ...
	CString var_name;
	CString list_item;
	int i;

	// OBJ ...
	{
		var_name = "OBJ.MSG";
		STD__ADD_STRING(var_name);
		LINK__VAR_STRING_CTRL(sCH__OBJ_MSG, var_name);

		var_name = "OBJ.SUB.MSG";
		STD__ADD_STRING(var_name);
		LINK__VAR_STRING_CTRL(sCH__OBJ_SUB_MSG, var_name);
	}

	// MON ...
	{
		var_name = "MON.STEP.EXCEPTION.ACT";
		STD__ADD_STRING(var_name);
		LINK__VAR_STRING_CTRL(sCH__MON_STEP_EXCEPTION_ACT, var_name);
	}

	// CFG ...
	{
		var_name = "CFG.STEP.ALARM_TEST.ACTIVE";
		STD__ADD_DIGITAL(var_name, "OFF ON");
		LINK__VAR_DIGITAL_CTRL(dCH__CFG_STEP_ALARM_TEST_ACTIVE, var_name);

		//
		var_name = "CFG.STEP.STABLE.MIN.SEC";
		STD__ADD_ANALOG_WITH_X_OPTION(var_name, "sec", 1, 0, 5, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_STEP_STABLE_MIN_SEC, var_name);

		var_name = "CFG.CHM.PRESSURE.HIGH.LIMIT";
		STD__ADD_ANALOG_WITH_X_OPTION(var_name, "torr", 0, 1, 900, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_CHM_PRESSURE_HIGH_LIMIT, var_name);
	}

	// RCP ...
	{
		// STEP ...
		{
			var_name = "RCP.STEP.MESSAGE";
			STD__ADD_STRING_WITH_OPTION(var_name, 0, "E", "");
			LINK__VAR_STRING_CTRL(sCH__RCP_STEP_MESSAGE, var_name);

			var_name = "RCP.STEP.MODE";
			STD__ADD_DIGITAL_WITH_OPTION(var_name, "Time Stable End", -1, "E", "");
			LINK__VAR_DIGITAL_CTRL(dCH__RCP_STEP_MODE, var_name);

			var_name = "RCP.STEP.TIME";
			STD__ADD_ANALOG_WITH_OPTION(var_name, "sec", 1, 0, 9999, -1, "E", "");
			LINK__VAR_ANALOG_CTRL(aCH__RCP_STEP_TIME, var_name);
		}

		// APC ...
		{
			var_name = "RCP.APC.MODE";		
			STD__ADD_DIGITAL_WITH_OPTION(var_name, "POSITION PRESSURE", -1, "E", "");
			LINK__VAR_DIGITAL_CTRL(dCH__RCP_APC_MODE, var_name);

			//
			var_name = "RCP.APC.POSITION";		
			STD__ADD_ANALOG_WITH_OPTION(var_name, "%", 1, 0.0, 100.0, -1, "E", "");
			LINK__VAR_ANALOG_CTRL(aCH__RCP_APC_POSITION, var_name);

			//
			var_name = "RCP.APC.PRESSURE";		
			STD__ADD_ANALOG_WITH_OPTION(var_name, "torr", 3, 0.0, 10.0, -1, "E", "");
			LINK__VAR_ANALOG_CTRL(aCH__RCP_APC_PRESSURE, var_name);

			var_name = "RCP.APC.LEARNED.POS";
			STD__ADD_STRING_WITH_OPTION(var_name, 0, "E", "");
			LINK__VAR_STRING_CTRL(sCH__RCP_APC_LEARNED_POS, var_name);

			var_name = "RCP.APC.HOLD.DELAY";
			STD__ADD_STRING_WITH_OPTION(var_name, 0, "E", "");
			LINK__VAR_STRING_CTRL(sCH__RCP_APC_HOLD_DELAY, var_name);
		}

		// MFC ...
		for(i=0; i<_CFG__MFC_SIZE; i++)
		{
			var_name.Format("RCP.GAS.%02d.FLOW", i+1);
			STD__ADD_STRING_WITH_OPTION(var_name, -1, "E", "");
			LINK__VAR_STRING_CTRL(sCH__RCP_GAS_FLOW_X[i], var_name);
		}

		// RF.RPS ...
		{
			var_name = "RCP.RF.RPS.POWER";
			STD__ADD_STRING_WITH_OPTION(var_name, -1, "E", "");
			LINK__VAR_STRING_CTRL(sCH__RCP_RF_RPS_POWER, var_name);
		}
		// RF.LF ...
		{
			var_name = "RCP.RF.LF.POWER";
			STD__ADD_STRING_WITH_OPTION(var_name, -1, "E", "");
			LINK__VAR_STRING_CTRL(sCH__RCP_RF_LF_POWER, var_name);
		}
		// RF.HF ...
		{
			var_name = "RCP.RF.HF.POWER";
			STD__ADD_STRING_WITH_OPTION(var_name, -1, "E", "");
			LINK__VAR_STRING_CTRL(sCH__RCP_RF_HF_POWER, var_name);
		}
		// RF.PULSE ...
		{
			var_name = "RCP.RF.PULSE.FREQUENCY";
			STD__ADD_ANALOG_WITH_OPTION(var_name, "hz", 0, 0, 5000, -1, "E", "");
			LINK__VAR_ANALOG_CTRL(aCH__RCP_RF_PULSE_FREQUENCY, var_name);

			var_name = "RCP.RF.PULSE.DUTY";
			STD__ADD_ANALOG_WITH_OPTION(var_name, "%", 0, 0, 100, -1, "E", "");
			LINK__VAR_ANALOG_CTRL(aCH__RCP_RF_PULSE_DUTY, var_name);

			var_name = "RCP.RF.PULSE.EXEC";
			STD__ADD_DIGITAL_WITH_OPTION(var_name, "LOW NORMAL REVERSE", -1, "E", "");
			LINK__VAR_DIGITAL_CTRL(dCH__RCP_RF_PULSE_EXEC, var_name);

			//
			var_name = "RCP.RF.PULSE.ON_TIME";
			STD__ADD_ANALOG_WITH_OPTION(var_name, "sec", 1, 0, 10, -1, "E", "");
			LINK__VAR_ANALOG_CTRL(aCH__RCP_RF_PULSE_ON_TIME, var_name);

			var_name = "RCP.RF.PULSE.OFF_TIME";
			STD__ADD_ANALOG_WITH_OPTION(var_name, "sec", 1, 0, 10, -1, "E", "");
			LINK__VAR_ANALOG_CTRL(aCH__RCP_RF_PULSE_OFF_TIME, var_name);

			var_name = "RCP.RF.PULSE.ON_SHIFT_TIME";
			STD__ADD_ANALOG_WITH_OPTION(var_name, "sec", 1, 0, 10, -1, "E", "");
			LINK__VAR_ANALOG_CTRL(aCH__RCP_RF_PULSE_ON_SHIFT_TIME, var_name);

			var_name = "RCP.RF.PULSE.OFF_SHIFT_TIME";
			STD__ADD_ANALOG_WITH_OPTION(var_name, "sec", 1, 0, 10, -1, "E", "");
			LINK__VAR_ANALOG_CTRL(aCH__RCP_RF_PULSE_OFF_SHIFT_TIME, var_name);
		}

		// MAT.LF ...
		{
			var_name = "RCP.MAT.LF.SHUNT";
			STD__ADD_STRING_WITH_OPTION(var_name, -1, "E", "");
			LINK__VAR_STRING_CTRL(sCH__RCP_MAT_LF_SHUNT, var_name);

			var_name = "RCP.MAT.LF.SERIES";
			STD__ADD_STRING_WITH_OPTION(var_name, -1, "E", "");
			LINK__VAR_STRING_CTRL(sCH__RCP_MAT_LF_SERIES, var_name);
		}
		// MAT.HF ...
		{
			var_name = "RCP.MAT.HF.SHUNT";
			STD__ADD_STRING_WITH_OPTION(var_name, -1, "E", "");
			LINK__VAR_STRING_CTRL(sCH__RCP_MAT_HF_SHUNT, var_name);

			var_name = "RCP.MAT.HF.SERIES";
			STD__ADD_STRING_WITH_OPTION(var_name, -1, "E", "");
			LINK__VAR_STRING_CTRL(sCH__RCP_MAT_HF_SERIES, var_name);
		}

		// ESC ...
		{
			var_name = "RCP.ESC.CTRL.MODE";
			list_item = "NoChange Chuck Chuck1 Chuck2 He.Set Dechuck Dechuck1 Dechuck2";
			STD__ADD_DIGITAL_WITH_OPTION(var_name, list_item, -1, "E", "");
			LINK__VAR_DIGITAL_CTRL(dCH__RCP_ESC_CTRL_MODE, var_name);

			// CENTER ...
			var_name = "RCP.DPC.CENTER.PRESSURE";
			STD__ADD_STRING_WITH_OPTION(var_name, -1, "E", "");
			LINK__VAR_STRING_CTRL(sCH__RCP_DPC_CENTER_PRESSURE, var_name);

			// EDGE ...
			var_name = "RCP.DPC.EDGE.PRESSURE";
			STD__ADD_STRING_WITH_OPTION(var_name, -1, "E", "");
			LINK__VAR_STRING_CTRL(sCH__RCP_DPC_EDGE_PRESSURE, var_name);
		}

		// LIFT_PIN ...
		{
			var_name = "RCP.LIFT_PIN.MODE";
			STD__ADD_DIGITAL_WITH_OPTION(var_name, "Down Middle Up", -1, "E", "");
			LINK__VAR_DIGITAL_CTRL(dCH__RCP_LIFT_PIN_MODE, var_name);
		}
	}

	return 1;
}

int CObj__STEP_STD::__DEFINE__ALARM(p_alarm)
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
		alarm_id = ALID__STEP_OVERTIME;
		alarm_title  = title;
		alarm_title += "STEP OVERTIME ALARM.";

		alarm_msg = "Process Step Time-Over Alarm Message.\n";
		alarm_msg += "Check Process Step time and Control time.";

		l_act.RemoveAll();
		l_act.Add(ACT__CLEAR);

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	// ...
	{
		alarm_id = ALID__STABLE_OVERTIME;
		alarm_title  = title;
		alarm_title += "STABLE OVERTIME ALARM.";

		alarm_msg = "Process Stable Step Time-over Alarm Message.\n";
		alarm_msg += "Check Process Stable Step time and Control time.";

		l_act.RemoveAll();
		l_act.Add(ACT__CLEAR);

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	return 1;
}

int CObj__STEP_STD::__Define__USER_FUNCTION(CII_DEFINE__FUNCTION *p_fnc_ctrl)
{
	p_fnc_ctrl->Link__ERROR_FEEDBACK(&mERROR__USER_FNC);

	return 1;
}

//-------------------------------------------------------------------------
int CObj__STEP_STD::__INITIALIZE__OBJECT(p_variable,p_ext_obj_create)
{
	CString def_name;
	CString def_data;
	CString ch_name;
	CString obj_name;
	CString var_name;
	int i;

	// ...
	{
		CString file_name;
		CString log_msg;

		file_name.Format("%s.log",sObject_Name);

		log_msg  = "\n\n";
		log_msg += "//------------------------------------------------------------------------";

		xLOG_CTRL->CREATE__SUB_DIRECTORY(sObject_Name);
		xLOG_CTRL->SET__PROPERTY(file_name, 24*5, 60);

		xLOG_CTRL->DISABLE__TIME_LOG();
		xLOG_CTRL->WRITE__LOG(log_msg);

		xLOG_CTRL->ENABLE__TIME_LOG();
		xLOG_CTRL->WRITE__LOG("   START   \n");
	}

	// ...
	CCommon_Utility x_utility;
	bool def_check;

	// DB INF ...
	{
		def_name = "OBJ__DB_INF";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name,obj_name);

		//
		var_name = "SLOT01.STATUS";
		LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__SLOT01_STATUS, obj_name,var_name);

		var_name = "SLOT01.LOTID";
		LINK__EXT_VAR_STRING_CTRL(sEXT_CH__CUR_LOTID, obj_name,var_name);
	}

	// OBJ APC ...
	{
		def_name = "OBJ__APC";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name,obj_name);

		def_check = x_utility.Check__Link(obj_name);
		bActive__OBJ_CTRL__APC = def_check;

		if(def_check)
		{
			pOBJ_CTRL__APC = p_ext_obj_create->Create__OBJECT_CTRL(obj_name);

			//
			var_name = "PARA.PRESSURE";
			LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__APC_OBJ__PARA_PRESSURE, obj_name,var_name);

			var_name = "PARA.POSITION";
			LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__APC_OBJ__PARA_POSITION, obj_name,var_name);

			var_name = "PARA.HOLD.SEC";
			LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__APC_OBJ__PARA_HOLD_SEC, obj_name,var_name);

			//
			var_name = "MON.PRESSURE.TORR";
			LINK__EXT_VAR_STRING_CTRL(sEXT_CH__APC_OBJ__MON_PRESSURE_TORR, obj_name,var_name);

			//
			var_name = "MON.PRESSURE.ABORT.ACTIVE";
			LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__APC_OBJ__MON_PRESSURE_ABORT_ACTIVE, obj_name,var_name);

			var_name = "MON.PRESSURE.STABLE.ACTIVE";
			LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__APC_OBJ__MON_PRESSURE_STABLE_ACTIVE, obj_name,var_name);
		}
	}

	// OBJ PT_X ...
	{
		def_name = "DATA.PT_SIZE";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name,def_data);

		iDATA__PT_SIZE = atoi(def_data);
		if(iDATA__PT_SIZE > _CFG__PT_SIZE)			iDATA__PT_SIZE = _CFG__PT_SIZE;

		for(i=0; i<iDATA__PT_SIZE; i++)
		{
			def_name.Format("CH__PT_ERROR.%02d", i+1);
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
			p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);

			LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__PT_X__MON_ABORT_ACTIVE[i], obj_name,var_name);
		}
	}

	// OBJ MFC_X ...
	{
		def_name = "DATA.MFC_SIZE";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name,def_data);

		iDATA__MFC_SIZE = atoi(def_data);
		if(iDATA__MFC_SIZE > _CFG__MFC_SIZE)		iDATA__MFC_SIZE = _CFG__MFC_SIZE;

		for(i=0; i<iDATA__MFC_SIZE; i++)
		{
			def_name.Format("OBJ__MFC.%02d", i+1);
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name,obj_name);

			pOBJ_CTRL__MFC_X[i] = p_ext_obj_create->Create__OBJECT_CTRL(obj_name);

			//
			var_name = "PARA.SET.FLOW";
			LINK__EXT_VAR_STRING_CTRL(sEXT_CH__MFC_X__PARA_SET_FLOW[i], obj_name,var_name);

			var_name = "PARA.RAMP.SEC";
			LINK__EXT_VAR_STRING_CTRL(sEXT_CH__MFC_X__PARA_RAMP_SEC[i], obj_name,var_name);

			//
			var_name = "MON.MFC.ABORT.ACTIVE";
			LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__MFC_X__MON_MFC_ABORT_ACTIVE[i], obj_name,var_name);
		}
	}

	// OBJ RF_RPS ...
	{
		def_name = "OBJ__RF_RPS";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name,obj_name);

		def_check = x_utility.Check__Link(obj_name);
		bActive__OBJ_CTRL__RF_RPS = def_check;

		if(def_check)
		{
			pOBJ_CTRL__RF_RPS = p_ext_obj_create->Create__OBJECT_CTRL(obj_name);

			//
			var_name = "PARA.SET.POWER";
			LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__RF_RPS__PARA_SET_POWER, obj_name,var_name);

			var_name = "PARA.HOLD.TIME";
			LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__RF_RPS__PARA_HOLD_TIME, obj_name,var_name);

			//
			var_name = "MON.POWER.ABORT.ACTIVE";
			LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__RF_RPS__MON_POWER_ABORT_ACTIVE, obj_name,var_name);

			var_name = "MON.REFLECT.HIGH_LIMIT.ACTIVE";
			LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__RF_RPS__MON_REFLECT_HIGH_LIMIT_ACTIVE, obj_name,var_name);

			var_name = "MON.REFLECT.MAX_COEFFICIENT.ACTIVE";
			LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__RF_RPS__MON_REFLECT_MAX_COEFFICIENT_ACTIVE, obj_name,var_name);
		}
	}
	// OBJ RF_PULSE ...
	{
		def_name = "OBJ__RF_PULSE";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name,obj_name);

		def_check = x_utility.Check__Link(obj_name);
		bActive__OBJ_CTRL__RF_PULSE = def_check;

		if(def_check)
		{
			pOBJ_CTRL__RF_PULSE = p_ext_obj_create->Create__OBJECT_CTRL(obj_name);

			//
			var_name = "PARA.RCP.FREQUENCY";
			LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__RF_PULSE__PARA_RCP_FREQUENCY, obj_name,var_name);
			
			var_name = "PARA.RCP.DUTY";
			LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__RF_PULSE__PARA_RCP_DUTY, obj_name,var_name);
			
			var_name = "PARA.RCP.EXEC";
			LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__RF_PULSE__PARA_RCP_EXEC, obj_name,var_name);
			
			//
			var_name = "PARA.RCP.ON_TIME";
			LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__RF_PULSE__PARA_RCP_ON_TIME, obj_name,var_name);
			
			var_name = "PARA.RCP.OFF_TIME";
			LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__RF_PULSE__PARA_RCP_OFF_TIME, obj_name,var_name);
			
			var_name = "PARA.RCP.ON_SHIFT_TIME";
			LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__RF_PULSE__PARA_RCP_ON_SHIFT_TIME, obj_name,var_name);
			
			var_name = "PARA.RCP.OFF_SHIFT_TIME";
			LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__RF_PULSE__PARA_RCP_OFF_SHIFT_TIME, obj_name,var_name);

			//
			var_name = "MON.POWER.ABORT.ACTIVE";
			LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__RF_PULSE__MON_POWER_ABORT_ACTIVE, obj_name,var_name);
		}
	}

	// OBJ RF_LF ...
	{
		def_name = "OBJ__RF_LF";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name,obj_name);

		def_check = x_utility.Check__Link(obj_name);
		bActive__OBJ_CTRL__RF_LF = def_check;

		if(def_check)
		{
			pOBJ_CTRL__RF_LF = p_ext_obj_create->Create__OBJECT_CTRL(obj_name);

			//
			var_name = "PARA.SET.POWER";
			LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__RF_LF__PARA_SET_POWER, obj_name,var_name);

			var_name = "PARA.HOLD.TIME";
			LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__RF_LF__PARA_HOLD_TIME, obj_name,var_name);

			//
			var_name = "MON.POWER.ABORT.ACTIVE";
			LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__RF_LF__MON_POWER_ABORT_ACTIVE, obj_name,var_name);

			var_name = "MON.REFLECT.HIGH_LIMIT.ACTIVE";
			LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__RF_LF__MON_REFLECT_HIGH_LIMIT_ACTIVE, obj_name,var_name);

			var_name = "MON.REFLECT.MAX_COEFFICIENT.ACTIVE";
			LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__RF_LF__MON_REFLECT_MAX_COEFFICIENT_ACTIVE, obj_name,var_name);
		}
	}
	// OBJ RF_HF ...
	{
		def_name = "OBJ__RF_HF";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name,obj_name);

		def_check = x_utility.Check__Link(obj_name);
		bActive__OBJ_CTRL__RF_HF = def_check;

		if(def_check)
		{
			pOBJ_CTRL__RF_HF = p_ext_obj_create->Create__OBJECT_CTRL(obj_name);

			//
			var_name = "PARA.SET.POWER";
			LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__RF_HF__PARA_SET_POWER, obj_name,var_name);

			var_name = "PARA.HOLD.TIME";
			LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__RF_HF__PARA_HOLD_TIME, obj_name,var_name);

			//
			var_name = "MON.POWER.ABORT.ACTIVE";
			LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__RF_HF__MON_POWER_ABORT_ACTIVE, obj_name,var_name);

			var_name = "MON.REFLECT.HIGH_LIMIT.ACTIVE";
			LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__RF_HF__MON_REFLECT_HIGH_LIMIT_ACTIVE, obj_name,var_name);

			var_name = "MON.REFLECT.MAX_COEFFICIENT.ACTIVE";
			LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__RF_HF__MON_REFLECT_MAX_COEFFICIENT_ACTIVE, obj_name,var_name);
		}
	}

	// OBJ MAT_LF ...
	{
		def_name = "OBJ__MAT_LF";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name,obj_name);

		def_check = x_utility.Check__Link(obj_name);
		bActive__OBJ_CTRL__MAT_LF = def_check;

		if(def_check)
		{
			pOBJ_CTRL__MAT_LF = p_ext_obj_create->Create__OBJECT_CTRL(obj_name);

			//
			var_name = "PARA.LOAD_POS";
			LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__MAT_LF__PARA_LOAD_POS, obj_name,var_name);

			var_name = "PARA.TUNE_POS";
			LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__MAT_LF__PARA_TUNE_POS, obj_name,var_name);
		}
	}
	// OBJ MAT_HF ...
	{
		def_name = "OBJ__MAT_HF";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name,obj_name);

		def_check = x_utility.Check__Link(obj_name);
		bActive__OBJ_CTRL__MAT_HF = def_check;

		if(def_check)
		{
			pOBJ_CTRL__MAT_HF = p_ext_obj_create->Create__OBJECT_CTRL(obj_name);

			//
			var_name = "PARA.LOAD_POS";
			LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__MAT_HF__PARA_LOAD_POS, obj_name,var_name);

			var_name = "PARA.TUNE_POS";
			LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__MAT_HF__PARA_TUNE_POS, obj_name,var_name);
		}
	}

	// OBJ ESC ...
	{
		def_name = "OBJ__ESC";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name,obj_name);

		def_check = x_utility.Check__Link(obj_name);
		bActive__OBJ_CTRL__ESC = def_check;

		if(def_check)
		{
			pOBJ_CTRL__ESC = p_ext_obj_create->Create__OBJECT_CTRL(obj_name);

			// CENTER ...
			var_name = "RCP.He_CENTER.PRESSURE_SETPOINT.TORR";
			LINK__EXT_VAR_STRING_CTRL(sEXT_CH__ESC__RCP_He_CENTER_PRESSURE_SETPOINT_TORR, obj_name,var_name);

			var_name = "RCP.He_CENTER.ZONE.FLOW.MAX.THRESHOLD";
			LINK__EXT_VAR_STRING_CTRL(sEXT_CH__ESC__RCP_He_CENTER_FLOW_MAX_THRESHOLD, obj_name,var_name);

			var_name = "RCP.He_CENTER.ZONE.FLOW.MIN.THRESHOLD";
			LINK__EXT_VAR_STRING_CTRL(sEXT_CH__ESC__RCP_He_CENTER_FLOW_MIN_THRESHOLD, obj_name,var_name);

			// EDGE ...
			var_name = "RCP.He_EDGE.PRESSURE_SETPOINT.TORR";
			LINK__EXT_VAR_STRING_CTRL(sEXT_CH__ESC__RCP_He_EDGE_PRESSURE_SETPOINT_TORR, obj_name,var_name);

			var_name = "RCP.He_EDGE.ZONE.FLOW.MAX.THRESHOLD";
			LINK__EXT_VAR_STRING_CTRL(sEXT_CH__ESC__RCP_He_EDGE_FLOW_MAX_THRESHOLD, obj_name,var_name);

			var_name = "RCP.He_EDGE.ZONE.FLOW.MIN.THRESHOLD";
			LINK__EXT_VAR_STRING_CTRL(sEXT_CH__ESC__RCP_He_EDGE_FLOW_MIN_THRESHOLD, obj_name,var_name);
		}
	}

	// OBJ LIFT_PIN ...
	{
		def_name = "OBJ__LIFT_PIN";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name,obj_name);

		def_check = x_utility.Check__Link(obj_name);
		bActive__OBJ_CTRL__LIFT_PIN = def_check;

		if(def_check)
		{
			pOBJ_CTRL__LIFT_PIN = p_ext_obj_create->Create__OBJECT_CTRL(obj_name);
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
int CObj__STEP_STD::__CALL__CONTROL_MODE(mode,p_debug,p_variable,p_alarm)
{
	int flag = -1;

	// ...
	{
		CString log_msg;
		log_msg.Format("[%s] Start ...", mode);

		xLOG_CTRL->WRITE__LOG(log_msg);

		sCH__OBJ_MSG->Set__DATA(log_msg);
		sCH__OBJ_SUB_MSG->Set__DATA("");
	}

	// ...
	{
		IF__CTRL_MODE(sMODE__INIT)
		{
			flag = Call__INIT(p_variable,p_alarm);
		}
		ELSE_IF__CTRL_MODE(sMODE__READY)
		{
			flag = Call__READY(p_variable,p_alarm);
		}
		ELSE_IF__CTRL_MODE(sMODE__START)
		{
			flag = Call__START(p_variable,p_alarm);
		}
		ELSE_IF__CTRL_MODE(sMODE__PROC)
		{
			flag = Call__PROC(p_variable,p_alarm);
		}
		ELSE_IF__CTRL_MODE(sMODE__ABORT)
		{
			flag = Call__ABORT(p_variable,p_alarm);
		}
		ELSE_IF__CTRL_MODE(sMODE__END)
		{
			flag = Call__END(p_variable,p_alarm);
		}
	}

	if((flag < 0)||(p_variable->Check__CTRL_ABORT() > 0))
	{
		CString log_msg;
		log_msg.Format("[%s] Aborted ... [%d]", mode,flag);

		xLOG_CTRL->WRITE__LOG(log_msg);	
		sCH__OBJ_MSG->Set__DATA(log_msg);
	}
	else
	{
		CString log_msg;
		log_msg.Format("[%s] Completed .. [%d]", mode,flag);

		xLOG_CTRL->WRITE__LOG(log_msg);
		sCH__OBJ_MSG->Set__DATA(log_msg);
	}

	return flag;
}

int CObj__STEP_STD::__CALL__MONITORING(id,p_variable,p_alarm)
{

	return 1;
}
