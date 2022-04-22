#include "StdAfx.h"
#include "CObj__LBx_OneManiFold.h"


//-------------------------------------------------------------------------
CObj__LBx_OneManiFold::CObj__LBx_OneManiFold()
{

}
CObj__LBx_OneManiFold::~CObj__LBx_OneManiFold()
{

}

//-------------------------------------------------------------------------
int CObj__LBx_OneManiFold::__DEFINE__CONTROL_MODE(obj,l_mode)
{
	sObject_Name = obj;

	// ...
	{
		ADD__CTRL_VAR(sMODE__INIT, "INIT");

		// ...
		ADD__CTRL_VAR(sMODE__PICK_READY,    "PICK_READY");
		ADD__CTRL_VAR(sMODE__PICK_EXTEND,   "PICK_EXTEND");
		ADD__CTRL_VAR(sMODE__PICK_COMPLETE, "PICK_COMPLETE");

		ADD__CTRL_VAR(sMODE__PLACE_READY,    "PLACE_READY");
		ADD__CTRL_VAR(sMODE__PLACE_EXTEND,   "PLACE_EXTEND");
		ADD__CTRL_VAR(sMODE__PLACE_COMPLETE, "PLACE_COMPLETE");

		// ...
		ADD__CTRL_VAR(sMODE__PUMP, "PUMP");
		ADD__CTRL_VAR(sMODE__TRANSFER_PUMP, "TRANSFER_PUMP");

		ADD__CTRL_VAR(sMODE__VENT, "VENT");
		ADD__CTRL_VAR(sMODE__LEAK_CHECK, "LEAK_CHECK");
	
		ADD__CTRL_VAR(sMODE__PREPMATER, "PREPMATER");
		ADD__CTRL_VAR(sMODE__COMPMATER, "COMPMATER");

		ADD__CTRL_VAR(sMODE__IN_PROC,  "IN_PROC");
		ADD__CTRL_VAR(sMODE__OUT_PROC, "OUT_PROC");

		ADD__CTRL_VAR(sMODE__DV_OPEN,  "DV_OPEN");
		ADD__CTRL_VAR(sMODE__DV_CLOSE, "DV_CLOSE");

		ADD__CTRL_VAR(sMODE__SV_OPEN,  "SV_OPEN");
		ADD__CTRL_VAR(sMODE__SV_CLOSE, "SV_CLOSE");

		ADD__CTRL_VAR(sMODE__DV_TRANSFER_OPEN,  "DV_TRANSFER.OPEN");
		ADD__CTRL_VAR(sMODE__DV_TRANSFER_CLOSE, "DV_TRANSFER.CLOSE");

		ADD__CTRL_VAR(sMODE__SV_TRANSFER_OPEN,  "SV_TRANSFER.OPEN");
		ADD__CTRL_VAR(sMODE__SV_TRANSFER_CLOSE, "SV_TRANSFER.CLOSE");

		ADD__CTRL_VAR(sMODE__ISOLATE, "ISOLATE");

		ADD__CTRL_VAR(sMODE__CYCLE_PURGE, "CYCLE_PURGE");

		//
		ADD__CTRL_VAR(sMODE__LIFT_PIN_UP,   "LIFT_PIN.UP");
		ADD__CTRL_VAR(sMODE__LIFT_PIN_DOWN, "LIFT_PIN.DOWN");

		ADD__CTRL_VAR(sMODE__CYCLE_LIFT_PIN, "CYCLE.LIFT_PIN");
	}	

	return 1;
}
int CObj__LBx_OneManiFold::__DEFINE__VERSION_HISTORY(version)
{

	return 1;
}


// ...
#define MON_ID__IO_MONITOR				1

// ...
#define APP_DSP__DOOR_STS				\
"UNKNOWN  CLOSE   OPEN"


int CObj__LBx_OneManiFold::__DEFINE__VARIABLE_STD(p_variable)
{
	DECLARE__STD_VARIABLE;
	
	CCommon_Error__DEF_VARIABLE m_err_def_variable;
	p_variable->Link__DEF_VARIABLE__ERROR_FEEDBACK(&m_err_def_variable);

	// ...
	CString str_name;
	int i;

	// ...
	{
		str_name = "OTR.OUT.MON.OBJ.STATUS";
		STD__ADD_STRING_WITH_COMMENT(str_name,"");
		LINK__VAR_STRING_CTRL(sCH__OBJ_STATUS,str_name);

		str_name = "OTR.OUT.MON.OBJ.MSG";
		STD__ADD_STRING_WITH_COMMENT(str_name,"");
		LINK__VAR_STRING_CTRL(sCH__OBJ_MSG,str_name);

		//
		str_name = "OBJ.ACTIVE.MODE";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__OBJ_ACTIVE_MODE,str_name);
	}

	// ...
	{
		str_name = "OTR.IN.PARA.aPREHEAT.TIME";
		STD__ADD_ANALOG_WITH_COMMENT(str_name,"sec",1,0,9999,"");
		LINK__VAR_ANALOG_CTRL(aCH__PARA_PREHEAT_TIME,str_name);

		str_name = "OTR.IN.PARA.aCOOLING.TIME";
		STD__ADD_ANALOG_WITH_COMMENT(str_name,"sec",1,0,9999,"");
		LINK__VAR_ANALOG_CTRL(aCH__PARA_COOLING_TIME,str_name);

		str_name = "OTR.IN.PARA.aPREMATERIAL.SLOT";
		STD__ADD_ANALOG_WITH_COMMENT(str_name,"sec",1,0,9999,"");
		LINK__VAR_ANALOG_CTRL(aCH__PARA_PREMATERIAL_SLOT,str_name);

		//
		str_name = "PARA.HANDSHAKE.SLOT";
		STD__ADD_ANALOG_WITH_COMMENT(str_name, "slot", 0, 1,10,"");
		LINK__VAR_ANALOG_CTRL(aCH__PARA_HANDSHAKE_SLOT, str_name);

		//
		str_name = "OTR.OUT.MON.dPRESSURE.STATUS";
		STD__ADD_STRING_WITH_COMMENT(str_name,"");
		LINK__VAR_STRING_CTRL(sCH__PRESSURE_STATUS, str_name);
	
		str_name = "dOTR.OUT.PUMPING.STS.FLAG";
		STD__ADD_DIGITAL_WITH_COMMENT(str_name, "END PUMPING", "");
		LINK__VAR_DIGITAL_CTRL(dCH__PUMPING_STS_FLAG, str_name);

		str_name = "dOTR.OUT.VENTING.STS.FLAG";
		STD__ADD_DIGITAL_WITH_COMMENT(str_name,  "END VENTING", "");
		LINK__VAR_DIGITAL_CTRL(dCH__VENTING_STS_FLAG, str_name);

		//
		str_name = "OTR.IN.MON.ROBOT.TRANSFER.FLAG";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__ROBOT_TRANSFER_FLAG, str_name);
	}

	// Cycle Purge !! ...
	{
		str_name = "APP.PURGE.PUMPDOWN.TIME.LIMIT";										// AL1_PumpDownTimeLimit
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "sec", 0, 15, 150, "rec : 30 sec");		// Reference 30 sec..
		LINK__VAR_ANALOG_CTRL(aCFG_CH__CYCLE_PURGE_PUMPDOWN_TIME_LIMIT,str_name);

		str_name = "APP.PURGE.CYCLE.COUNT";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "count", 0, 1, 100000, "");				// Reference 15¹ø..
		LINK__VAR_ANALOG_CTRL(aCFG_CH__CYCLE_PURGE_COUNT,str_name);

		str_name = "APP.PURGE.CURRENT.COUNT";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCFG_CH__CYCLE_PURGE_CURRENT_COUNT,str_name);

		str_name = "APP.PURGE.MESSAGE";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCFG_CH__CYCLE_PURGE_SEQ_MSG,str_name);
	}

	// Particle Check ...
	{
		str_name = "CFG.aPARTICLE.CHECK.SV.OP.CL.COUNT";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name,"count",1,1,999,"");
		LINK__VAR_ANALOG_CTRL(aCFG_PARTICLE_CHECK_SV_OP_CL_COUNT,str_name);

		str_name = "CFG.aPARTICLE.CHECK.DV.OP.CL.COUNT";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name,"count",1,1,999,"");
		LINK__VAR_ANALOG_CTRL(aCFG_PARTICLE_CHECK_DV_OP_CL_COUNT,str_name);

		str_name = "CFG.aPARTICLE.CHECK.PUMP.VENT.COUNT";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name,"count",1,1,999,"");
		LINK__VAR_ANALOG_CTRL(aCFG_PARTICLE_CHECK_PUMP_VENT_COUNT,str_name);
	}

	// Cycle Lift_Pin ...
	{
		str_name = "CFG.CYCLE.LIFT_PIN.COUNT";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "count", 0, 1, 999,"");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_CYCLE_LIFT_PIN__COUNT, str_name);

		str_name = "CFG.CYCLE.LIFT_PIN.UP_DELAY.SEC";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "sec", 0, 0, 999,"");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_CYCLE_LIFT_PIN__UP_DELAY_SEC, str_name);

		str_name = "CFG.CYCLE.LIFT_PIN.DOWN_DELAY.SEC";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "sec", 0, 0, 999,"");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_CYCLE_LIFT_PIN__DOWN_DELAY_SEC, str_name);

		//
		str_name = "CUR.CYCLE.LIFT_PIN.COUNT";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__CUR_CYCLE_LIFT_PIN__COUNT, str_name);

		str_name = "CUR.CYCLE.LIFT_PIN.UP_DELAY.SEC";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__CUR_CYCLE_LIFT_PIN__UP_DELAY_SEC, str_name);

		str_name = "CUR.CYCLE.LIFT_PIN.DOWN_DELAY.SEC";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__CUR_CYCLE_LIFT_PIN__DOWN_DELAY_SEC, str_name);

		//
		str_name = "ACTIVE.CYCLE.LIFT_PIN";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__ACTIVE_CYCLE_LIFT_PIN, str_name);

		// 
		for(i=0; i<CFG_ACTION__SIZE; i++)
		{
			CString act_name;

				 if(i == _ACT_INDEX__UP)			act_name = "UP";
			else if(i == _ACT_INDEX__DOWN)			act_name = "DOWN";
			else									continue;

			//
			str_name.Format("RESULT.CYCLE.LIFT_PIN.%s_TIME.CUR", act_name);
			STD__ADD_STRING(str_name);
			LINK__VAR_STRING_CTRL(sCH__RESULT_CYCLE_LIFT_PIN_ACTION_TIME_CUR[i], str_name);

			str_name.Format("RESULT.CYCLE.LIFT_PIN.%s_TIME.AVG", act_name);
			STD__ADD_STRING(str_name);
			LINK__VAR_STRING_CTRL(sCH__RESULT_CYCLE_LIFT_PIN_ACTION_TIME_AVG[i], str_name);
			
			str_name.Format("RESULT.CYCLE.LIFT_PIN.%s_TIME.MIN", act_name);
			STD__ADD_STRING(str_name);
			LINK__VAR_STRING_CTRL(sCH__RESULT_CYCLE_LIFT_PIN_ACTION_TIME_MIN[i], str_name);
			
			str_name.Format("RESULT.CYCLE.LIFT_PIN.%s_TIME.MAX", act_name);
			STD__ADD_STRING(str_name);
			LINK__VAR_STRING_CTRL(sCH__RESULT_CYCLE_LIFT_PIN_ACTION_TIME_MAX[i], str_name);
		}
	}

	// ...
	{
		p_variable->Add__MONITORING_PROC(1.0, MON_ID__IO_MONITOR);
	}
	return 1;
}

int CObj__LBx_OneManiFold::__DEFINE__ALARM(p_alarm)
{
	
	return 1;
}

//-------------------------------------------------------------------------
int CObj__LBx_OneManiFold::__INITIALIZE__OBJECT(p_variable,p_ext_obj_create)
{
	CString def_name;
	CString def_data;
	CString str_name;

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


	// LLx_UTILITY OBJ ...
	{
		def_name = "OBJ__LLx_UTILITY";
		p_variable->Get__DEF_CONST_DATA(def_name,def_data);

		pLLx_UTILITY__OBJ_CTRL = p_ext_obj_create->Create__OBJECT_CTRL(def_data);
	}

	// LLx_CHM OBJ ...
	{
		def_name = "OBJ__LLx_CHM";
		p_variable->Get__DEF_CONST_DATA(def_name,def_data);

		pLLx_CHM__OBJ_CTRL = p_ext_obj_create->Create__OBJECT_CTRL(def_data);

		//
		str_name = "OTR.OUT.MON.OBJ.STATUS";
		LINK__EXT_VAR_STRING_CTRL(sEXT_CH__OBJ_STATUS, def_data,str_name);

		//
		str_name = "OTR.IN.PARA.aPREHEAT.TIME";
		LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__PARA_PREHEAT_TIME, def_data,str_name);

		str_name = "OTR.IN.PARA.aCOOLING.TIME";
		LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__PARA_COOLING_TIME, def_data,str_name);

		str_name = "OTR.IN.PARA.aPREMATERIAL.SLOT";
		LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__PARA_PREMATERIAL_SLOT, def_data,str_name);

		//
		str_name = "OTR.OUT.MON.dPRESSURE.STATUS";
		LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__PRESSURE_STATUS, def_data,str_name);

		//
		str_name = "OTR.OUT.MON.dSLIT.VALVE.STATUS";
		LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__VAC_VLV_STATUS, def_data,str_name);

		str_name = "SLIT_VALVE.LOCK_FLAG";
		LINK__EXT_VAR_STRING_CTRL(sEXT_CH__SLIT_VALVE_LOCK_FLAG, def_data,str_name);
	}

	return 1;
}

//-------------------------------------------------------------------------
int CObj__LBx_OneManiFold::__CALL__CONTROL_MODE(mode,p_debug,p_variable,p_alarm)
{
	DECLARE__EXT_CTRL(p_variable);
	
	// ...
	int flag = -1;

	// ...
	{
		CString para__preheat_time;
		CString para__cooling_time;
		CString para__prematerial_slot;

		aCH__PARA_PREHEAT_TIME->Get__DATA(para__preheat_time);
		aCH__PARA_COOLING_TIME->Get__DATA(para__cooling_time);
		aCH__PARA_PREMATERIAL_SLOT->Get__DATA(para__prematerial_slot);

		aEXT_CH__PARA_PREHEAT_TIME->Set__DATA(para__preheat_time);
		aEXT_CH__PARA_COOLING_TIME->Set__DATA(para__cooling_time);
		aEXT_CH__PARA_PREMATERIAL_SLOT->Set__DATA(para__prematerial_slot);

		// ...
		CString log_msg;

		log_msg.Format("Start ... :  [%s] (%s,%s,%s)",
					   mode,
					   para__preheat_time,
				       para__cooling_time,
					   para__prematerial_slot);

		xLOG_CTRL->WRITE__LOG(log_msg);

		log_msg.Format("Start  [%s] ... Called By %s", 
					   mode,
					   p_ext_mode_ctrl->Get__UPPER_OBJECT_NAME());

		xLOG_CTRL->WRITE__LOG(log_msg);

		sCH__OBJ_MSG->Set__DATA(log_msg);
	}

	sCH__OBJ_ACTIVE_MODE->Set__DATA(mode);

	// ...
	{
			 IF__CTRL_MODE(sMODE__INIT)					flag = Call__INIT(p_variable);

		ELSE_IF__CTRL_MODE(sMODE__PICK_READY)			flag = Call__PICK_READY(p_variable);
		ELSE_IF__CTRL_MODE(sMODE__PICK_EXTEND)			flag = Call__PICK_EXTEND(p_variable);
		ELSE_IF__CTRL_MODE(sMODE__PICK_COMPLETE)		flag = Call__PICK_COMPLETE(p_variable);

		ELSE_IF__CTRL_MODE(sMODE__PLACE_READY)			flag = Call__PLACE_READY(p_variable);
		ELSE_IF__CTRL_MODE(sMODE__PLACE_EXTEND)			flag = Call__PLACE_EXTEND(p_variable);
		ELSE_IF__CTRL_MODE(sMODE__PLACE_COMPLETE)		flag = Call__PLACE_COMPLETE(p_variable);

		ELSE_IF__CTRL_MODE(sMODE__PUMP)					flag = Call__PUMP(p_alarm, p_variable);
		ELSE_IF__CTRL_MODE(sMODE__TRANSFER_PUMP)		flag = Call__TRANSFER_PUMP(p_alarm, p_variable);
		
		ELSE_IF__CTRL_MODE(sMODE__VENT)					flag = Call__VENT(p_variable);
		ELSE_IF__CTRL_MODE(sMODE__LEAK_CHECK)			flag = Call__LEAK_CHECK(p_variable);
		
		ELSE_IF__CTRL_MODE(sMODE__PREPMATER)			flag = Call__PREPMATER(p_variable);
		ELSE_IF__CTRL_MODE(sMODE__COMPMATER)			flag = Call__COMPMATER(p_variable);
		ELSE_IF__CTRL_MODE(sMODE__IN_PROC)				flag = Call__IN_PROC(p_variable);
		ELSE_IF__CTRL_MODE(sMODE__OUT_PROC)				flag = Call__OUT_PROC(p_variable);

		ELSE_IF__CTRL_MODE(sMODE__DV_OPEN)				flag = Call__DV_OPEN(p_variable);
		ELSE_IF__CTRL_MODE(sMODE__DV_CLOSE)				flag = Call__DV_CLOSE(p_variable);

		ELSE_IF__CTRL_MODE(sMODE__SV_OPEN)				flag = Call__SV_OPEN(p_variable);
		ELSE_IF__CTRL_MODE(sMODE__SV_CLOSE)				flag = Call__SV_CLOSE(p_variable);

		ELSE_IF__CTRL_MODE(sMODE__DV_TRANSFER_OPEN)		flag = Call__DV_OPEN(p_variable);
		ELSE_IF__CTRL_MODE(sMODE__DV_TRANSFER_CLOSE)	flag = Call__DV_CLOSE(p_variable);

		ELSE_IF__CTRL_MODE(sMODE__SV_TRANSFER_OPEN)		flag = Call__SV_OPEN(p_variable);
		ELSE_IF__CTRL_MODE(sMODE__SV_TRANSFER_CLOSE)	flag = Call__SV_CLOSE(p_variable);

		ELSE_IF__CTRL_MODE(sMODE__ISOLATE)				flag = Call__ISOLATE(p_variable);
		ELSE_IF__CTRL_MODE(sMODE__CYCLE_PURGE)			flag = Call__CYCLE_PURGE(p_alarm, p_variable);

		ELSE_IF__CTRL_MODE(sMODE__LIFT_PIN_UP)			flag = Call__LIFT_PIN_UP(p_variable);
		ELSE_IF__CTRL_MODE(sMODE__LIFT_PIN_DOWN)		flag = Call__LIFT_PIN_DOWN(p_variable);

		ELSE_IF__CTRL_MODE(sMODE__CYCLE_LIFT_PIN)		flag = Call__CYCLE_LIFT_PIN(p_variable);
	}

	sCH__OBJ_ACTIVE_MODE->Set__DATA("");

	if((flag < 0)||(p_variable->Check__CTRL_ABORT() > 0))
	{
		CString log_msg;
		log_msg.Format("Aborted ... :  [%s]",mode);

		xLOG_CTRL->WRITE__LOG(log_msg);
		sCH__OBJ_MSG->Set__DATA(log_msg);
	}
	else
	{
		CString log_msg;
		log_msg.Format("Completed ... :  [%s]",mode);

		xLOG_CTRL->WRITE__LOG(log_msg);
		sCH__OBJ_MSG->Set__DATA(log_msg);
	}

	dCH__PUMPING_STS_FLAG->Set__DATA("END");
	return flag;
}

int CObj__LBx_OneManiFold::__CALL__MONITORING(id,p_variable,p_alarm)
{
	switch(id)
	{
		case MON_ID__IO_MONITOR:
			Mon__IO_MONITOR(p_variable,p_alarm);
			break;
	}

	return 1;
}
