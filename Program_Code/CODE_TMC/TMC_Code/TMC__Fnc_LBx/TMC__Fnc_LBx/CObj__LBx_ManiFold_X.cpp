#include "StdAfx.h"
#include "CObj__LBx_ManiFold_X.h"


//-------------------------------------------------------------------------
CObj__LBx_ManiFold_X::CObj__LBx_ManiFold_X()
{

}
CObj__LBx_ManiFold_X::~CObj__LBx_ManiFold_X()
{

}

//-------------------------------------------------------------------------
int CObj__LBx_ManiFold_X::__DEFINE__CONTROL_MODE(obj,l_mode)
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

		ADD__CTRL_VAR(sMODE__LIFT_PIN_UP,   "LIFT_PIN.UP");
		ADD__CTRL_VAR(sMODE__LIFT_PIN_DOWN, "LIFT_PIN.DOWN");
	}	

	return 1;
}
int CObj__LBx_ManiFold_X::__DEFINE__VERSION_HISTORY(version)
{

	return 1;
}


// ...
#define MON_ID__IO_MONITOR				1

// ...
#define APP_DSP__DOOR_STS				\
	"UNKNOWN  CLOSE   OPEN"


int CObj__LBx_ManiFold_X::__DEFINE__VARIABLE_STD(p_variable)
{
	DECLARE__STD_VARIABLE;

	CCommon_Error__DEF_VARIABLE m_err_def_variable;
	p_variable->Link__DEF_VARIABLE__ERROR_FEEDBACK(&m_err_def_variable);

	// ...
	CString str_name;

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
		str_name = "PARA.SLOT.ID";
		STD__ADD_ANALOG_WITH_COMMENT(str_name, "ID", 0, 1, 2, "");
		LINK__VAR_ANALOG_CTRL(aCH__PARA_SLOT_ID, str_name);
	}

	// ...
	{
		str_name = "OTR.IN.PARA.aPREHEAT.TIME";
		STD__ADD_ANALOG_WITH_COMMENT(str_name,"sec",1,0,9999,"");
		LINK__VAR_ANALOG_CTRL(aCH__PARA_PREHEAT_TIME, str_name);

		str_name = "OTR.IN.PARA.aCOOLING.TIME";
		STD__ADD_ANALOG_WITH_COMMENT(str_name,"sec",1,0,9999,"");
		LINK__VAR_ANALOG_CTRL(aCH__PARA_COOLING_TIME, str_name);

		str_name = "OTR.IN.PARA.aPREMATERIAL.SLOT";
		STD__ADD_ANALOG_WITH_COMMENT(str_name, "slot", 0, 1,10,"");
		LINK__VAR_ANALOG_CTRL(aCH__PARA_PREMATERIAL_SLOT, str_name);

		//
		str_name = "PARA.HANDSHAKE.SLOT";
		STD__ADD_ANALOG_WITH_COMMENT(str_name, "slot", 0, 1,10,"");
		LINK__VAR_ANALOG_CTRL(aCH__PARA_HANDSHAKE_SLOT, str_name);

		//
		str_name = "OTR.OUT.MON.dPRESSURE.STATUS";
		STD__ADD_STRING_WITH_COMMENT(str_name,"");
		LINK__VAR_STRING_CTRL(sCH__PRESSURE_STATUS,str_name);

		str_name = "dOTR.OUT.PUMPING.STS.FLAG";
		STD__ADD_DIGITAL_WITH_COMMENT(str_name, "END PUMPING", "");
		LINK__VAR_DIGITAL_CTRL(dCH__PUMPING_STS_FLAG,str_name);

		str_name = "dOTR.OUT.VENTING.STS.FLAG";
		STD__ADD_DIGITAL_WITH_COMMENT(str_name,  "END VENTING", "");
		LINK__VAR_DIGITAL_CTRL(dCH__VENTING_STS_FLAG,str_name);

		//
		str_name = "OTR.IN.MON.ROBOT.TRANSFER.FLAG";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__ROBOT_TRANSFER_FLAG, str_name);
	}

	// ...
	{
		str_name = "CFG.LEAK.CHECK";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name, "DISABLE ENABLE", "");
		LINK__VAR_DIGITAL_CTRL(dCH__CFG_LEAK_CHECK, str_name);
	}

	// TMC : LEAK_CHECK PARA -----
	{
		str_name = "MON.LEAK_CHECK.TIME_COUNT";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "sec", 0,0.0,9999, "");
		LINK__VAR_ANALOG_CTRL(aCH__MON_LEAK_CHECK__TIME_COUNT, str_name);

		str_name = "CFG.LEAK_CHECK.OVER.PUMPING.TIME";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "sec", 0,0.0,9999, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_LEAK_CHECK__OVER_PUMPING_TIME, str_name);

		str_name = "CFG.LEAK_CHECK.STABLE.TIME";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "sec", 0,0.0,9999, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_LEAK_CHECK__STABLE_TIME, str_name);

		str_name = "CFG.LEAK_CHECK.CHECK_TIME.MIN";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "sec", 0,1,30, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_LEAK_CHECK__CHECK_TIME_MIN, str_name);

		//
		str_name = "MON.LEAK_CHECK.START.TIME";
		STD__ADD_STRING_WITH_X_OPTION(str_name, "");
		LINK__VAR_STRING_CTRL(sCH__MON_LEAK_CHECK__START_TIME, str_name);

		str_name = "MON.LEAK_CHECK.END.TIME";
		STD__ADD_STRING_WITH_X_OPTION(str_name, "");
		LINK__VAR_STRING_CTRL(sCH__MON_LEAK_CHECK__END_TIME, str_name);

		str_name = "MON.LEAK_CHECK.START.PRESSURE.TORR";
		STD__ADD_STRING_WITH_X_OPTION(str_name, "");
		LINK__VAR_STRING_CTRL(sCH__MON_LEAK_CHECK__START_PRESSURE_TORR, str_name);

		str_name = "MON.LEAK_CHECK.END.PRESSURE.TORR";
		STD__ADD_STRING_WITH_X_OPTION(str_name, "");
		LINK__VAR_STRING_CTRL(sCH__MON_LEAK_CHECK__END_PRESSURE_TORR, str_name);

		str_name = "MON.LEAK_CHECK.TOTAL.LEAK.RATE";
		STD__ADD_STRING_WITH_X_OPTION(str_name, "");
		LINK__VAR_STRING_CTRL(sCH__MON_LEAK_CHECK__TOTAL_LEAK_RATE, str_name);
	}
	// LeakCheck AlarmRate ...
	{
		str_name = "CFG.LEAK_CHECK.ALARM.RATE";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "mtorr_min", 0, 0, 1000, "rec:10");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_LEAK_CHECK__ALARM_RATE, str_name);

		for(int i=0; i<CFG_LEAK_RATE__STEP_SIZE; i++)
		{
			str_name.Format("MON.LEAK_CHECK.STEP%1d.PRESSURE.TORR", i+1);
			STD__ADD_STRING_WITH_X_OPTION(str_name, "");
			LINK__VAR_STRING_CTRL(sCH__MON_LEAK_CHECK__STEP_PRESSURE_TORR[i], str_name);

			str_name.Format("MON.LEAK_CHECK.STEP%1d.LEAK.RATE", i+1);
			STD__ADD_STRING_WITH_X_OPTION(str_name, "");
			LINK__VAR_STRING_CTRL(sCH__MON_LEAK_CHECK__STEP_LEAK_RATE[i], str_name);
		}
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

	// ...
	{
		p_variable->Add__MONITORING_PROC(1.0, MON_ID__IO_MONITOR);
	}
	return 1;
}

int CObj__LBx_ManiFold_X::__DEFINE__ALARM(p_alarm)
{
	DECLARE__ALARM;

	// ...
	CString title;
	title.Format("%s - ",sObject_Name);

	int alarm_id;
	CString alarm_title;
	CString alarm_msg;
	CStringArray l_act;

	// ...
	{
		alarm_id = ALID__SV_DOOR_OPEN_ERROR;

		alarm_title  = title;
		alarm_title += "SV & Door Open Error";

		alarm_msg = "You can't open SV and Door at same time !";

		l_act.RemoveAll();
		l_act.Add("ABORT");
		l_act.Add("RETRY");
		l_act.Add("IGNORE");

		ADD__ALARM_EX(alarm_id, alarm_title,alarm_msg,l_act);
	}

	// ...
	{
		alarm_id = ALID__LEAK_CHECK_BAD_RESULT_ALARM;

		alarm_title  = title;
		alarm_title += "Leak Check is higher than config value !";

		alarm_msg = "";

		l_act.RemoveAll();
		l_act.Add("CHECK");

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	return 1;
}

//-------------------------------------------------------------------------
int CObj__LBx_ManiFold_X::__INITIALIZE__OBJECT(p_variable,p_ext_obj_create)
{
	CString def_name;
	CString def_data;
	CString obj_name;
	CString str_name;
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

	// OBJ INFO ...
	{
		def_name = "LBx_NAME";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name,def_data);

		sLLx_NAME = def_data;
	}

	// LBx SLOT.SIZE ...
	{
		def_name = "LBx_SLOT.SIZE";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name,def_data);

		iLBx_SLOT_SIZE = atoi(def_data);

			 if(iLBx_SLOT_SIZE < 1)							iLBx_SLOT_SIZE = 1;
		else if(iLBx_SLOT_SIZE > CFG_LLx__SLOT_SIZE)		iLBx_SLOT_SIZE = CFG_LLx__SLOT_SIZE;
	}

	// LINK__OBJ_PHY ...
	{
		def_name = "LINK__OBJ_PHY";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name,def_data);

		pLBx_CHM__OBJ_CTRL = p_ext_obj_create->Create__OBJECT_CTRL(def_data);

		//
		str_name = "OTR.OUT.MON.OBJ.STATUS";
		LINK__EXT_VAR_STRING_CTRL(sEXT_CH__OBJ_STATUS, def_data,str_name);

		//
		if(iLBx_SLOT_SIZE  > 1)
		{
			str_name = "PARA.SLOT.ID";
			LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__PARA_SLOT_ID, def_data,str_name);
		}

		//
		str_name = "OTR.IN.PARA.aPREHEAT.TIME";
		LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__PARA_PREHEAT_TIME, def_data,str_name);

		str_name = "OTR.IN.PARA.aCOOLING.TIME";
		LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__PARA_COOLING_TIME, def_data,str_name);

		str_name = "OTR.IN.PARA.aPREMATERIAL.SLOT";
		LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__PARA_PREMATERIAL_SLOT, def_data,str_name);

		//
		str_name = "OTR.OUT.MON.aPRESSURE.TORR";
		LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__PRESSURE_TORR, def_data,str_name);

		str_name = "OTR.OUT.MON.dPRESSURE.STATUS";
		LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__PRESSURE_STATUS, def_data,str_name);

		//
		for(i=0; i<iLBx_SLOT_SIZE; i++)
		{
			if(iLBx_SLOT_SIZE == 1)
			{
				str_name = "OTR.OUT.MON.dDOOR.VALVE.STATUS";
				LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__DOOR_VLV_STATUS_X[i], def_data,str_name);

				str_name = "OTR.OUT.MON.dSLIT.VALVE.STATUS";
				LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__VAC_VLV_STATUS_X[i], def_data,str_name);

				str_name = "SLIT_VALVE.LOCK_FLAG";
				LINK__EXT_VAR_STRING_CTRL(sEXT_CH__SLIT_VALVE_LOCK_FLAG_X[i], def_data,str_name);
			}
			else
			{
				int id = i + 1;

				str_name.Format("OTR.OUT.MON.dDOOR.VALVE.STATUS.%1d", id);
				LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__DOOR_VLV_STATUS_X[i], def_data,str_name);

				str_name.Format("OTR.OUT.MON.dSLIT.VALVE.STATUS.%1d", id);
				LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__VAC_VLV_STATUS_X[i], def_data,str_name);

				str_name.Format("SLIT_VALVE.LOCK_FLAG.%1d", id);
				LINK__EXT_VAR_STRING_CTRL(sEXT_CH__SLIT_VALVE_LOCK_FLAG_X[i], def_data,str_name);
			}
		}

		// ...
		str_name = "CFG.HEATER.USE";
		LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__CFG_HEATER_USE, def_data,str_name);

		str_name = "CFG.HEATING.SOFT_VENT.APPLY";
		LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__CFG_HEATER_SOFT_VENT_USE, def_data,str_name);
	}

	// Other OBJ_CHM ...
	{
		def_name = "DATA.OTHER_CHM_SIZE";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, def_data);

		iOTHER_CHM__SIZE = atoi(def_data);
		if(iOTHER_CHM__SIZE > _CFG__OTHER_CHM_SIZE)			iOTHER_CHM__SIZE = _CFG__OTHER_CHM_SIZE;

		for(i=0; i<iOTHER_CHM__SIZE; i++)
		{
			// OBJ_FNC ...
			{
				def_name.Format("LINK_OTHER_CHM.OBJ_FNC.%1d", i+1);
				p_ext_obj_create->Get__DEF_CONST_DATA(def_name, obj_name);
	
				pOther_CHM__OBJ_FNC_X[i] = p_ext_obj_create->Create__OBJECT_CTRL(obj_name);

				//
				str_name = "OBJ.ACTIVE.MODE";
				LINK__EXT_VAR_STRING_CTRL(sEXT_CH__OTHER_CHM__OBJ_ACTIVE_MODE_X[i], obj_name,str_name);

				str_name = "dOTR.OUT.PUMPING.STS.FLAG";
				LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__OTHER_CHM__PUMPING_STS_FLAG_X[i], obj_name,str_name);
			}

			// OBJ_PHY ...
			{
				def_name.Format("LINK_OTHER_CHM.OBJ_PHY.%1d", i+1);
				p_ext_obj_create->Get__DEF_CONST_DATA(def_name, obj_name);

				pOther_CHM__OBJ_PHY_X[i] = p_ext_obj_create->Create__OBJECT_CTRL(obj_name);

				//
				str_name = "OTR.OUT.MON.PRESSURE.CTRL.FLAG";
				LINK__EXT_VAR_STRING_CTRL(sEXT_CH__Other_CHM__PRESSURE_CTRL_FLAG_X[i], obj_name,str_name);

				str_name = "OTR.OUT.MON.dPRESSURE.STATUS";
				LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__Other_CHM__PRESSURE_STATUS_X[i], obj_name,str_name);
			}
		}
	}

	// DB CFG ...
	{
		def_name = "OBJ__DB";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name,def_data);

		//
		str_name = "CFG.SETUP.TEST.MODE";
		LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__CFG_SETUP_TEST_MODE, def_data,str_name);

		str_name = "CFG.SETUP.AUTO.VENTING_PUMPING";
		LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__CFG_SETUP_AUTO_VENTING_PUMPING, def_data,str_name);

		str_name = "CFG.SETUP.LLx.DOOR_SLOT_VLV.CONTROL";
		LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__CFG_SETUP_LLx_DOOR_SLOT_VLV_CONTROL, def_data,str_name);
	}

	return 1;
}

//-------------------------------------------------------------------------
int CObj__LBx_ManiFold_X::__CALL__CONTROL_MODE(mode,p_debug,p_variable,p_alarm)
{
	DECLARE__EXT_CTRL(p_variable);

	// ...
	int flag = -1;

	// ...
	CStringArray l_para;
	p_variable->Get__FNC_PARAMETER(l_para);

	if(l_para.GetSize() > 0)
	{
		CString log_msg;
		CString log_bff;

		int i_limit = l_para.GetSize();

		log_msg = "\n";
		log_bff.Format("Parameter Limit <- [%1d] ... \n", i_limit); 
		log_msg += log_bff;

		for(int i=0; i<i_limit; i++)
		{
			CString para_data = l_para[i];

			log_bff.Format(" * %1d) [%s] \n", i+1,para_data);
			log_msg += log_bff;

			switch(i)
			{
				case 0:		
					aCH__PARA_SLOT_ID->Set__DATA(para_data);
					break;
			}	
		}

		xLOG_CTRL->WRITE__LOG(log_msg);
	}

	// ...
	{
		CString para__slot_id;

		aCH__PARA_SLOT_ID->Get__DATA(para__slot_id);

		if(aEXT_CH__PARA_SLOT_ID.Get__PTR() != NULL)
			aEXT_CH__PARA_SLOT_ID->Set__DATA(para__slot_id);

		// ...
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

		log_msg.Format("Start ... :  [%s] (%s) (%s,%s,%s)",
						mode,
						para__slot_id,
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
			  IF__CTRL_MODE(sMODE__INIT)				flag = Call__INIT(p_variable);

		ELSE_IF__CTRL_MODE(sMODE__PICK_READY)			flag = Call__PICK_READY(p_variable);
		ELSE_IF__CTRL_MODE(sMODE__PICK_EXTEND)			flag = Call__PICK_EXTEND(p_variable);
		ELSE_IF__CTRL_MODE(sMODE__PICK_COMPLETE)		flag = Call__PICK_COMPLETE(p_variable);

		ELSE_IF__CTRL_MODE(sMODE__PLACE_READY)			flag = Call__PLACE_READY(p_variable);
		ELSE_IF__CTRL_MODE(sMODE__PLACE_EXTEND)			flag = Call__PLACE_EXTEND(p_variable);
		ELSE_IF__CTRL_MODE(sMODE__PLACE_COMPLETE)		flag = Call__PLACE_COMPLETE(p_variable);

		ELSE_IF__CTRL_MODE(sMODE__PUMP)					flag = Call__PUMP(p_alarm, p_variable);
		ELSE_IF__CTRL_MODE(sMODE__TRANSFER_PUMP)		flag = Call__TRANSFER_PUMP(p_alarm, p_variable);

		ELSE_IF__CTRL_MODE(sMODE__VENT)					flag = Call__VENT(p_variable);
		ELSE_IF__CTRL_MODE(sMODE__LEAK_CHECK)			flag = Call__LEAK_CHECK(p_variable, p_alarm);

		ELSE_IF__CTRL_MODE(sMODE__PREPMATER)			flag = Call__PREPMATER(p_variable);
		ELSE_IF__CTRL_MODE(sMODE__COMPMATER)			flag = Call__COMPMATER(p_variable);
		ELSE_IF__CTRL_MODE(sMODE__IN_PROC)				flag = Call__IN_PROC(p_variable);
		ELSE_IF__CTRL_MODE(sMODE__OUT_PROC)				flag = Call__OUT_PROC(p_variable);

		ELSE_IF__CTRL_MODE(sMODE__DV_OPEN)				flag = Call__DV_OPEN(p_variable, p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__DV_CLOSE)				flag = Call__DV_CLOSE(p_variable, p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__SV_OPEN)				flag = Call__SV_OPEN(p_variable, p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__SV_CLOSE)				flag = Call__SV_CLOSE(p_variable, p_alarm);

		ELSE_IF__CTRL_MODE(sMODE__DV_TRANSFER_OPEN)		flag = Call__DV_OPEN(p_variable, p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__DV_TRANSFER_CLOSE)	flag = Call__DV_CLOSE(p_variable, p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__SV_TRANSFER_OPEN)		flag = Call__SV_OPEN(p_variable, p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__SV_TRANSFER_CLOSE)	flag = Call__SV_CLOSE(p_variable, p_alarm);

		ELSE_IF__CTRL_MODE(sMODE__ISOLATE)				flag = Call__ISOLATE(p_variable, p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__CYCLE_PURGE)			flag = Call__CYCLE_PURGE(p_alarm, p_variable);

		ELSE_IF__CTRL_MODE(sMODE__LIFT_PIN_UP)			flag = Call__LIFT_PIN_UP(p_variable);
		ELSE_IF__CTRL_MODE(sMODE__LIFT_PIN_DOWN)		flag = Call__LIFT_PIN_DOWN(p_variable);
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

int CObj__LBx_ManiFold_X::__CALL__MONITORING(id,p_variable,p_alarm)
{
	switch(id)
	{
	case MON_ID__IO_MONITOR:
		Mon__IO_MONITOR(p_variable,p_alarm);
		break;
	}

	return 1;
}
