#include "StdAfx.h"
#include "CObj__DGF_FLEX.h"


//-------------------------------------------------------------------------
CObj__DGF_FLEX::CObj__DGF_FLEX()
{

}
CObj__DGF_FLEX::~CObj__DGF_FLEX()
{

}

//-------------------------------------------------------------------------
int CObj__DGF_FLEX::__DEFINE__CONTROL_MODE(obj,l_mode)
{
	sObject_Name = obj;

	// ...
	{
		ADD__CTRL_VAR(sMODE__INIT, "INIT");

		ADD__CTRL_VAR(sMODE__ALL_CLOSE,	"ALL_CLOSE");
		ADD__CTRL_VAR(sMODE__CONTROL,	"CONTROL");

		ADD__CTRL_VAR(sMODE__ORIFICE_CTRL, "ORIFICE.CTRL");
		ADD__CTRL_VAR(sMODE__ALL_OPEN,	   "ALL_OPEN");
		ADD__CTRL_VAR(sMODE__GASLINE_PUMP, "GASLINE_PUMP");

		ADD__CTRL_VAR(sMODE__SAVE_LEVEL_VLV, "SAVE.LEVEL_VLV");
	}
	return 1;
}
int CObj__DGF_FLEX::__DEFINE__VERSION_HISTORY(version)
{

	return 1;
}


// ...
#define MON_ID__STATUS					1


int CObj__DGF_FLEX::__DEFINE__VARIABLE_STD(p_variable)
{
	DECLARE__STD_VARIABLE;

	// ...
	CCommon_Error__DEF_VARIABLE m_err_def_variable;
	p_variable->Link__DEF_VARIABLE__ERROR_FEEDBACK(&m_err_def_variable);

	// ...
	CString str_name;
	int i;
	int k;

	//.OBJ ..
	{
		str_name = "OBJ.MSG";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__OBJ_MSG, str_name);
	}

	// PARA ...
	{
		str_name = "PARA.ORIFICE.TYPE";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name,"VLV1  VLV2  VLV3  VLV4  VLV5  VLV6","");
		LINK__VAR_DIGITAL_CTRL(dCH_PARA__ORIFICE_TYPE, str_name);
	}

	// DGF Center Setpoint (%) ...
	{
		str_name = "CENTER.Wt.SETPOINT";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "%", 0, 0, 100, "");
		LINK__VAR_ANALOG_CTRL(aCH__CENTER_Wt_SET_POINT, str_name);
	
		str_name = "CTRL_OPEN.REQ";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__CTRL_OPEN_REQ, str_name);

		//
		str_name = "CUR.CENTER.SETPOINT";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__CUR_CENTER_SETPOINT, str_name);

		str_name = "MON.ALL.CLOSE.ACTIVE";
		STD__ADD_DIGITAL(str_name,"OFF  ON");
		LINK__VAR_DIGITAL_CTRL(dCH__MON_ALL_CLOSE_ACTIVE, str_name);
	}

	//
	for(i=0; i<_CFG__MAX_DGF_LEVEL; i++)
	{
		str_name.Format("MIN.LEVEL%02d", i+1);
		STD__ADD_ANALOG(str_name, "%", 0, 0, 100);
		LINK__VAR_ANALOG_CTRL(aCH__MIN_LEVELx[i], str_name);

		str_name.Format("MAX.LEVEL%02d", i+1);
		STD__ADD_ANALOG(str_name, "%", 0, 0, 100);
		LINK__VAR_ANALOG_CTRL(aCH__MAX_LEVELx[i], str_name);
	}

	for(i=0; i<_CFG__MAX_DGF_LEVEL; i++)
	{
		for(k=0; k<_CFG__MAX_VALVE; k++)
		{
			str_name.Format("CFG.LEVEL%02d.VALVE%02d", i+1, k+1);
			STD__ADD_DIGITAL_WITH_X_OPTION(str_name, "Open  Close", "");
			LINK__VAR_DIGITAL_CTRL(dCFG_CH__VALVE_STATUS[i][k], str_name);
		}
	}

	// CFG ...
	{
		str_name = "CFG.DGF.DEFAULT.CENTER.WEIGHT";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "", 1, 0, 100, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_DGF_DEFAULT_CENTER_WEIGHT, str_name);

		str_name = "CFG.DGF.TEST.ROUTINE.GAS.NUMBER";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "", 0, 0, 24, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_DGF_TEST_ROUTINE_GAS_NUMBER, str_name);

		str_name = "CFG.DGF.TEST.ROUTINE.LOW.FLOW.GAS.NUMBER";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "", 0, 0, 24, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_DGF_TEST_ROUTINE_LOW_FLOW_GAS_NUMBER, str_name);

		str_name = "CFG.DGF.TEST.ROUTINE.LOW.FLOW.ORIFICE.FLOWRATE";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "sccm", 0, 0, 9999, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_DGF_TEST_ROUTINE_LOW_FLOW_ORIFICE_FLOWRATE, str_name);

		str_name = "CFG.DGF.TEST.ROUTINE.HIGH.FLOW.ORIFICE.FLOWRATE";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "sccm", 0, 0, 9999, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_DGF_TEST_ROUTINE_HIGH_FLOW_ORIFICE_FLOWRATE, str_name);

		str_name = "CFG.DGF.TEST.ROUTINE.FLOW.TIME";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "sec", 0, 10, 120, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_DGF_TEST_ROUTINE_FLOW_TIME, str_name);

		str_name = "CFG.DGF.TEST.ROUTINE.BASELINE.TOLERANCE";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "%", 0, 0, 100, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_DGF_TEST_ROUTINE_BASELINE_TOLERANCE, str_name);

		str_name = "CFG.DGF.INLET.PRESSURE.SAVE.TO.RECIPE";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name, "False True", "");
		LINK__VAR_DIGITAL_CTRL(dCH__CFG_DGF_INLET_PRESSURE_SAVE_TO_RECIPE, str_name);

		str_name = "CFG.DGF.INLET.PRESSURE.CHECK";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name, "False True", "");
		LINK__VAR_DIGITAL_CTRL(dCH__CFG_DGF_INLET_PRESSURE_CHECK, str_name);

		str_name = "CFG.DGF.TOLERANCE.CHECK.DELAY";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "sec", 0, 0, 20, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_DGF_TOLERANCE_CHECK_DELAY, str_name);

		str_name = "CFG.DGF.SOFT.TOLERANCE.TIMEOUT";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "sec", 0, 0, 20, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_DGF_SOFT_TOLERANCE_TIMEOUT, str_name);

		str_name = "CFG.DGF.HARD.TOLERANCE.TIMEOUT";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "sec", 0, 0, 20, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_DGF_HARD_TOLERANCE_TIMEOUT, str_name);

		str_name = "CFG.DGF.WAFER.300M.PARTION";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "", 0, 0, 2, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_DGF_WAFER_300M_PARTION, str_name);

		str_name = "CFG.DGF.SOFT.TOLERANCE";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "%", 0, 0, 100, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_DGF_SOFT_TOLERANCE, str_name);

		str_name = "CFG.DGF.HARD.TOLERANCE";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "%", 0, 0, 100, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_DGF_HARD_TOLERANCE, str_name);

		str_name = "CFG.DGF.DELAY.TIMER";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "msec", 0, 0, 2000, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_DGF_DELAY_TIMER, str_name);

		str_name = "CFG.DGF.MANOMETER.TYPE";
		STD__ADD_STRING_WITH_X_OPTION(str_name, "");
		LINK__VAR_STRING_CTRL(sCH__CFG_DGF_MANOMETER_TYPE, str_name);
	}

	// ...
	{
		p_variable->Add__MONITORING_PROC(1.0, MON_ID__STATUS);
	}
	return 1;
}
int CObj__DGF_FLEX::__DEFINE__ALARM(p_alarm)
{
	DECLARE__ALARM;

	return 1;
}


//-------------------------------------------------------------------------
int CObj__DGF_FLEX::__INITIALIZE__OBJECT(p_variable,p_ext_obj_create)
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

	// IO LINK ...
	{
		for(i=0; i<_CFG__MAX_ORIFICE; i++)
		{
			def_name.Format("CH__DGF_ORIFICE.%02d", i+1);
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
			p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
			LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__ORIFICE_VALVE[i], obj_name,var_name);
		}

		//
		def_name = "CH__BRANCH1_CENTER";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
		p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
		LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__BRANCH1_CENTER_VALVE, obj_name,var_name);

		def_name = "CH__BRANCH1_EDGE";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
		p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
		LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__BRANCH1_EDGE_VALVE, obj_name,var_name);

		def_name = "CH__BRANCH2_CENTER";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
		p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
		LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__BRANCH2_CENTER_VALVE, obj_name,var_name);

		def_name = "CH__BRANCH2_EDGE";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
		p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
		LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__BRANCH2_EDGE_VALVE, obj_name,var_name);

		//
		def_name = "CH__CHAMBER_CENTER";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
		p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
		LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__CHAMBER_CENTER_VALVE, obj_name,var_name);

		def_name = "CH__CHAMBER_EDGE";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
		p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
		LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__CHAMBER_EDGE_VALVE, obj_name,var_name);

		//
		def_name = "CH__VLV_2";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
		p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
		LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__VLV_2, obj_name,var_name);

		def_name = "CH__VLV_4";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
		p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
		LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__VLV_4, obj_name,var_name);

		//
		def_name = "CH__VAC_SNS";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
		p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
		LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__IO_VAC_SNS, obj_name,var_name);

		//  For Simulator Interlock Channel Initialize ...
		/*
		str_name.Format("di.GasPerchg.ManVac.PSH2");		// True
		LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__GasPerchg_ManVac_PSH2, obj_name, str_name);		

		str_name.Format("di.Chamber.DeliverVac.PSH3");		// True		
		LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__Chamber_DeliverVac_PSH3, obj_name, str_name);			

		str_name.Format("di.TunningGas.DeliverVac.PSH4");	// True
		LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__TunningGas_DeliverVac_PSH4, obj_name, str_name);	

		str_name.Format("di.Scrubber.Switch.PSH8");			// True
		LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__Scrubber_Switch_PSH8, obj_name, str_name);		

		str_name.Format("di.N2Purge.Supply.PSH9");			// True
		LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__N2Purge_Supply_PSH9, obj_name, str_name);

		str_name.Format("di.CDAPress.Switch.Sts");			// True
		LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__CDAPress_Switch_Sts, obj_name, str_name);

		str_name.Format("di.Customer.GasDetect.Switch");	// True
		LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__Customer_GasDetect_Switch, obj_name, str_name);

		str_name.Format("di.Customer.Intlk.Switch");		// True
		LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__Customer_Intlk_Switch, obj_name, str_name);

		str_name.Format("di.H2.Intlk.Switch");				// True
		LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__H2_Intlk_Switch, obj_name, str_name);

		str_name.Format("di.H2.Intlk.Switch.Installed");	// True
		LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__H2_Intlk_Switch_Installed, obj_name, str_name);

		str_name.Format("di.Conver.Intlk");					// True
		LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__Conver_Intlk, obj_name, str_name);

		str_name.Format("di.WaterLeak.Detection.Sts");		// True
		LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__WaterLeak_Detection_Sts, obj_name, str_name);
		*/
	}

	// ...
	{
		SCX__SEQ_INFO x_seq_info;

		iActive__SIM_MODE = x_seq_info->Is__SIMULATION_MODE();
	}
	return 1;
}


//-------------------------------------------------------------------------
int CObj__DGF_FLEX::__CALL__CONTROL_MODE(mode,p_debug,p_variable,p_alarm)
{
	DECLARE__EXT_CTRL(p_variable);

	int flag = -1;

	// ...
	{
		CString log_msg;
		log_msg.Format("Start [%s] ... Called By %s", mode, p_ext_mode_ctrl->Get__UPPER_OBJECT_NAME());

		sCH__OBJ_MSG->Set__DATA(log_msg);
		xLOG_CTRL->WRITE__LOG(log_msg);
	}

	// ...
	{
			 IF__CTRL_MODE(sMODE__INIT)				 flag = Call__INIT(p_variable, p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__ALL_CLOSE)		 flag = Call__ALL_CLOSE(p_variable, p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__CONTROL)			 flag = Call__CONTROL(p_variable, p_alarm);

		ELSE_IF__CTRL_MODE(sMODE__ORIFICE_CTRL)		 flag = Call__ORIFICE_CTRL(p_variable, p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__ALL_OPEN)			 flag = Call__ALL_OPEN(p_variable, p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__GASLINE_PUMP)		 flag = Call__GASLINE_PUMP(p_variable, p_alarm);

		ELSE_IF__CTRL_MODE(sMODE__SAVE_LEVEL_VLV)	 flag = Call__SAVE_LEVEL_VLV(p_variable, p_alarm);
	}

	if((flag < 0)||(p_variable->Check__CTRL_ABORT() > 0))
	{
		CString log_msg;
		log_msg.Format("Aborted [%d] ... :  [%s]", flag, mode);

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

	return flag;
}
int CObj__DGF_FLEX::__CALL__MONITORING(id,p_variable,p_alarm)
{
	if(id == MON_ID__STATUS)		Mon__STATUS(p_variable, p_alarm);

	return 1;
}
