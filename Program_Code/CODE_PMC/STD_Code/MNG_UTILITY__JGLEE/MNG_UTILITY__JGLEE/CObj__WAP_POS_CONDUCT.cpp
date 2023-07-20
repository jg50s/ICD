#include "StdAfx.h"
#include "CObj__WAP_POS_CONDUCT.h"


//-------------------------------------------------------------------------
CObj__WAP_POS_CONDUCT::CObj__WAP_POS_CONDUCT()
{

}
CObj__WAP_POS_CONDUCT::~CObj__WAP_POS_CONDUCT()
{

}

//-------------------------------------------------------------------------
int CObj__WAP_POS_CONDUCT::__DEFINE__CONTROL_MODE(obj,l_mode)
{
	sObject_Name = obj;

	// ...
	{
		ADD__CTRL_VAR(sMODE__POS_CONDUCT, "POS_CONDUCT");
		ADD__CTRL_VAR(sMODE__DATA_SIM,    "DATA_SIM");

		ADD__CTRL_VAR(sMODE__POSITION_PRESSURE_CHECK, "POSITION_PRESSURE_CHECK");
		ADD__CTRL_VAR(sMODE__PULSE_SCAN, "PULSE_SCAN");
	}
	return 1;
}
int CObj__WAP_POS_CONDUCT::__DEFINE__VERSION_HISTORY(version)
{

	return 1;
}


// ...
#define APP_DSP__GAS_TYPE				\
"GAS01 GAS02 GAS03 GAS04 GAS05			\
 GAS06 GAS07 GAS08 GAS09 GAS10			\
 GAS11 GAS12 GAS13 GAS14 GAS15			\
 GAS16"


// ...
#define  MON_ID__STATUS_CTRL			1


int CObj__WAP_POS_CONDUCT::__DEFINE__VARIABLE_STD(p_variable)
{
	DECLARE__STD_VARIABLE;

	//-------------------------------------------------------------------------
	CString str_name;
	int i;

	// SYSTEM CHANNEL .....
	{
		str_name = "OBJ.MSG";
		STD__ADD_STRING_WITH_COMMENT(str_name,"");
		LINK__VAR_STRING_CTRL(xCH__OBJ_MSG,str_name);

		str_name = "APP.AUTO_START_CTRL";
		STD__ADD_STRING_WITH_COMMENT(str_name,"");
		LINK__VAR_STRING_CTRL(xCH__AUTO_START_CTRL,str_name);
	}

	// PARAMETER .....
	{
		// C-RING Gap Type
		str_name = "CFG.C_RING.GAP_TYPE";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name, "2.0 2.34 2.5", "");
		LINK__VAR_DIGITAL_CTRL(dCH_CFG__C_RING_GAP_TYPE, str_name);

		// TEST GAS TYPE
		str_name = "PARA.TEST.GAS.TYPE";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name, APP_DSP__GAS_TYPE,"");
		LINK__VAR_DIGITAL_CTRL(dCH_PARA__TEST_GAS_TYPE, str_name);

		str_name = "PARA.TEST.GAS.FLOW";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name,"sccm",0,0,10000,"");
		LINK__VAR_ANALOG_CTRL(aCH_PARA__TEST_GAS_FLOW, str_name);

		str_name = "CUR.TEST.GAS.NAME";
		STD__ADD_STRING_WITH_COMMENT(str_name,"");
		LINK__VAR_STRING_CTRL(sCH__CUR_TEST_GAS_NAME, str_name);

		// TEST INFO
		str_name = "PARA.TEST.DATE";
		STD__ADD_STRING_WITH_X_OPTION(str_name, "");
		LINK__VAR_STRING_CTRL(sCH_PARA__TEST_DATE, str_name);

		str_name = "PARA.TEST.TIME";
		STD__ADD_STRING_WITH_X_OPTION(str_name, "");
		LINK__VAR_STRING_CTRL(sCH_PARA__TEST_TIME, str_name);

		//
		for(i=0;i<CFG__TEST_LIST;i++)
		{
			// VLV POS LIST
			str_name.Format("PARA.VLV.POS.%1d", i+1);
			STD__ADD_ANALOG_WITH_X_OPTION(str_name, "_",0,0,1000,"");
			LINK__VAR_ANALOG_CTRL(aCH_PARA__VLV_POS_LIST[i], str_name);

			// CUR PRESSURE
			str_name.Format("PARA.CUR.PRESSURE.%1d", i+1);
			STD__ADD_STRING_WITH_X_OPTION(str_name, "");
			LINK__VAR_STRING_CTRL(sCH_PARA__CUR_PRESS_LIST[i], str_name);

			// CONDUCT RESULT
			str_name.Format("PARA.CONDUCT.RESULT.%1d", i+1);
			STD__ADD_STRING_WITH_X_OPTION(str_name, "");
			LINK__VAR_STRING_CTRL(sCH_PARA__CONDUCT_RESULT[i], str_name);

			str_name.Format("SIM.CONDUCT.RESULT.%1d", i+1);
			STD__ADD_STRING_WITH_COMMENT(str_name, "");
			LINK__VAR_STRING_CTRL(sCH_SIM__CONDUCT_RESULT[i], str_name);

			str_name.Format("NEW.CONDUCT.RESULT.%1d", i+1);
			STD__ADD_STRING_WITH_X_OPTION(str_name, "");
			LINK__VAR_STRING_CTRL(sCH_NEW__CONDUCT_RESULT[i], str_name);

			// VLV REF LIST
			str_name.Format("PARA.VLV.REF.%1d", i+1);
			STD__ADD_ANALOG_WITH_X_OPTION(str_name, "_",3,0,1000,"");
			LINK__VAR_ANALOG_CTRL(aCH_PARA__VLV_REF_LIST[i], str_name);
		}

		// CHECK TIME COUNT
		{
			str_name = "PARA.CHECK.TIME.COUNT";
			STD__ADD_STRING_WITH_X_OPTION(str_name, "");
			LINK__VAR_STRING_CTRL(sCH_PARA__CHECK_TIME_COUNT, str_name);

			str_name = "PARA.POS_PRESS_CHECK.TIME.COUNT";
			STD__ADD_STRING_WITH_X_OPTION(str_name, "");
			LINK__VAR_STRING_CTRL(sCH_PARA__POS_PRESS_CHECK__TIME_COUNT, str_name);
		}

		// SIM - MOVE
		str_name = "SIM.MOVE.OFFSET";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name,"count",1,-100,100,"");
		LINK__VAR_ANALOG_CTRL(aCH__SIM_MOVE_OFFSET, str_name);

		str_name = "SIM.MOVE.LOOKUP";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name,"YES","");
		LINK__VAR_DIGITAL_CTRL(dCH__SIM_MOVE_LOOKUP, str_name);

		str_name = "SIM.MOVE.DATA.TYPE";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name,"CURRENT REF","");
		LINK__VAR_DIGITAL_CTRL(dCH__SIM_MOVE_DATA_TYPE, str_name);

		str_name = "SIM.MOVE.ERROR.RANGE";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "count",2,0,1,"");
		LINK__VAR_ANALOG_CTRL(aCH__SIM_MOVE_ERROR_RANGE, str_name);

		str_name = "SIM.MOVE.ERROR.X.MIN";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "count",0,0,1000,"");
		LINK__VAR_ANALOG_CTRL(aCH__SIM_MOVE_ERROR_X_MIN, str_name);

		str_name = "SIM.MOVE.ERROR.X.MAX";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "count",0,0,1000,"");
		LINK__VAR_ANALOG_CTRL(aCH__SIM_MOVE_ERROR_X_MAX, str_name);

		str_name = "SIM.MOVE.CHECK.FLAG";
		STD__ADD_STRING_WITH_COMMENT(str_name, "");
		LINK__VAR_STRING_CTRL(sCH__SIM_MOVE_CHECK_FLAG, str_name);

		str_name = "SIM.MOVE.SCAN.FLAG";
		STD__ADD_STRING_WITH_COMMENT(str_name, "");
		LINK__VAR_STRING_CTRL(sCH__SIM_MOVE_SCAN_FLAG, str_name);

		// RESULT 
		str_name = "RESULT.NEW.STRING";
		STD__ADD_STRING_WITH_X_OPTION(str_name, "");
		LINK__VAR_STRING_CTRL(sCH__RESULT_NEW_STRING, str_name);

		str_name = "RESULT.STRING";
		STD__ADD_STRING_WITH_X_OPTION(str_name, "");
		LINK__VAR_STRING_CTRL(sCH__RESULT_CUR_STRING, str_name);

		str_name = "RESULT.MOVE.STRING";
		STD__ADD_STRING_WITH_X_OPTION(str_name, "");
		LINK__VAR_STRING_CTRL(sCH__RESULT_MOVE_STRING, str_name);

		str_name = "RESULT.MSG";
		STD__ADD_STRING_WITH_X_OPTION(str_name, "");
		LINK__VAR_STRING_CTRL(sCH__RESULT_MSG, str_name);

		str_name = "RESULT.SAVE.FLAG";
		STD__ADD_STRING_WITH_X_OPTION(str_name, "");
		LINK__VAR_STRING_CTRL(sCH__RESULT_SAVE_FLAG, str_name);

		str_name = "RESULT.SAVE.DATE";
		STD__ADD_STRING_WITH_X_OPTION(str_name, "");
		LINK__VAR_STRING_CTRL(sCH__RESULT_SAVE_DATE, str_name);

		// REF STRING
		str_name = "REF.STRING";
		STD__ADD_STRING_WITH_COMMENT(str_name, "");
		LINK__VAR_STRING_CTRL(sCH__REF_STRING, str_name);
	}

	// CONFIG .....
	{
		str_name = "CFG.FLOW.DELAY.SEC";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name,"sec",0,0,10000,"");
		LINK__VAR_ANALOG_CTRL(aCH_CFG__FLOW_DELAY_SEC, str_name);

		str_name = "CFG.POS_PRESS_CHECK.FLOW.DELAY.SEC";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name,"sec",0,0,10000,"");
		LINK__VAR_ANALOG_CTRL(aCH_CFG__POS_PRESS_CHECK__FLOW_DELAY_SEC, str_name);

		//
		str_name = "CFG.PRESSURE.STABLE.DELAY.SEC";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name,"sec",0,0,10000,"");
		LINK__VAR_ANALOG_CTRL(aCH_CFG__PRESSURE_STABLE_DELAY_SEC, str_name);

		str_name = "CFG.PRESSURE.STABLE.DELAY.SEC";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name,"sec",0,0,10000,"");
		LINK__VAR_ANALOG_CTRL(aCH_CFG__POS_PRESS_CHECK__PRESSURE_STABLE_DELAY_SEC, str_name);

		//
		str_name = "CFG.TEST.ORDER";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name,"BOTTOM_TO_UP  TOP_TO_DOWN","");
		LINK__VAR_DIGITAL_CTRL(dCH_CFG__TEST_ORDER, str_name);
	}

	// SPEC TEST ...
	{
		str_name = "CFG.WAP_SPEC_TEST.APPLY_MODE";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name, "DISABLE ENABLE","");
		LINK__VAR_DIGITAL_CTRL(dCH_CFG__WAP_SPEC_TEST__APPLY_MODE, str_name);

		str_name = "CFG.WAP_SPEC_TEST.GAS_FLOW";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "sccm",0,0,1000,"");
		LINK__VAR_ANALOG_CTRL(aCH_CFG__WAP_SPEC_TEST__GAS_FLOW, str_name);

		str_name = "CFG.WAP_SPEC_TEST.POSITION";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "count",0,0,1000,"");
		LINK__VAR_ANALOG_CTRL(aCH_CFG__WAP_SPEC_TEST__POSITION, str_name);

		str_name = "CFG.WAP_SPEC_TEST.PRESSURE_MIN";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "mtorr",1,0,200,"");
		LINK__VAR_ANALOG_CTRL(aCH_CFG__WAP_SPEC_TEST__PRESSURE_MIN, str_name);

		str_name = "CFG.WAP_SPEC_TEST.PRESSURE_MAX";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "mtorr",1,0,200,"");
		LINK__VAR_ANALOG_CTRL(aCH_CFG__WAP_SPEC_TEST__PRESSURE_MAX, str_name);

		str_name = "CFG.WAP_SPEC_TEST.STABLE_TIME";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "sec",0,0,100,"");
		LINK__VAR_ANALOG_CTRL(aCH_CFG__WAP_SPEC_TEST__STABLE_TIME, str_name);

		str_name = "CFG.WAP_SPEC_TEST.CHECK_TIME";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "sec",0,0,100,"");
		LINK__VAR_ANALOG_CTRL(aCH_CFG__WAP_SPEC_TEST__CHECK_TIME, str_name);
	}


	// RESULT : POSITION & PRESSURE ...
	{
		str_name = "RESULT.REF.POSITION_PRESSURE.STRING";
		STD__ADD_STRING_WITH_X_OPTION(str_name, "");
		LINK__VAR_STRING_CTRL(sCH__RESULT_REF_POSITION_PRESSURE_STRING, str_name);

		str_name = "RESULT.CUR.POSITION_PRESSURE.STRING";
		STD__ADD_STRING_WITH_X_OPTION(str_name, "");
		LINK__VAR_STRING_CTRL(sCH__RESULT_CUR_POSITION_PRESSURE_STRING, str_name);

		//
		str_name = "CFG.POS_PRESS_CHECK.GAS_TYPE";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name, APP_DSP__GAS_TYPE,"");
		LINK__VAR_DIGITAL_CTRL(dCH_CFG__POS_PRESS_CHECK__GAS_TYPE, str_name);

		str_name = "CFG.POS_PRESS_CHECK.GAS_FLOW";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "sccm",0,0,10000,"");
		LINK__VAR_ANALOG_CTRL(aCH_CFG__POS_PRESS_CHECK__GAS_FLOW, str_name);
	}

	// ...
	{
		p_variable->Add__MONITORING_PROC(3.0, MON_ID__STATUS_CTRL);
	}
	return 1;
}
int CObj__WAP_POS_CONDUCT::__DEFINE__ALARM(p_alarm)
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
		alarm_id = ALID__OBJECT_MODE_UNKNOWN;

		alarm_title  = title;
		alarm_title += "OBJECT MODE : UNKNOWN";

		alarm_msg = "";

		l_act.RemoveAll();
		l_act.Add("ABORT");

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	// ...
	{
		alarm_id = ALID__FNC_CANNOT_RUN;

		alarm_title  = title;
		alarm_title += "WAP Position Conductance : Utility Program Can't run !";

		alarm_msg = "";

		l_act.RemoveAll();
		l_act.Add("CHECK");

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	// ...
	{
		alarm_id = ALID__PRESSURE_READ_ERROR;

		alarm_title  = title;
		alarm_title += "Pressure Reading Error !";

		alarm_msg  = "Please, check pressure gauge (CM1). \n";
		alarm_msg += "\"WAP Conductance\" check funcation was aborted. \n";

		l_act.RemoveAll();
		l_act.Add("CHECK");

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	// ...
	{	
		alarm_id = ALID__WAP_CONDUCTANCE_CHECK_COMPLETE;

		alarm_title  = title;
		alarm_title += "WAP Conductance Checking Completed !";

		alarm_msg  = "WAP Conductance Checking was normally completed ! \n";

		l_act.RemoveAll();
		l_act.Add("CHECK");

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	// ...
	{	
		alarm_id = ALID__SIM_RANGE_ERROR;

		alarm_title  = title;
		alarm_title += "Simulation Move Range Error !";

		alarm_msg  = "Please, select any correct move-offset. \n";

		l_act.RemoveAll();
		l_act.Add("CHECK");

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	// ...
	{	
		alarm_id = ALID__WAP_CONDUCTANCE__AUTO_OFFSET_CHECK__OK;

		alarm_title  = title;
		alarm_title += "WAP Conductance (Auto Offset Check) : Result OK !";

		alarm_msg  = "Do you want to apply the selected offset ? \n";
		alarm_msg += "If you click [YES], the selected offset will be applied. \n";
		alarm_msg += "IF you click [NO],  the selected offset will be not applied. \n";

		l_act.RemoveAll();
		l_act.Add("YES");
		l_act.Add("NO");

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	// ...
	{	
		alarm_id = ALID__WAP_CONDUCTANCE__AUTO_OFFSET_CHECK__ERROR;

		alarm_title  = title;
		alarm_title += "WAP Conductance (Auto Offset Check) : Result Error !";

		alarm_msg  = "Please, check H/W C-Ring. \n";
		alarm_msg += "Currently, H/W C-Ring has any problem. \n";

		l_act.RemoveAll();
		l_act.Add("CHECK");

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}
	return 1;
}

int CObj__WAP_POS_CONDUCT::__Define__USER_FUNCTION(CII_DEFINE__FUNCTION *p_fnc_ctrl)
{
	mERROR__USER_FNC.Set__OBJ_NAME(sObject_Name);
	p_fnc_ctrl->Link__ERROR_FEEDBACK(&mERROR__USER_FNC);

	return 1;
}


//-------------------------------------------------------------------------
int CObj__WAP_POS_CONDUCT::__INITIALIZE__OBJECT(p_variable,p_ext_obj_create)
{
	// ...
	{
		p_ext_obj_create->Link__DEF_VARIABLE__ERROR_FEEDBACK(&mERROR__DEF_VAR);
	}

	// ...
	{
		CString file_name;
		CString log_msg;

		file_name.Format("%s_App.log", sObject_Name);

		log_msg  = "\n\n";
		log_msg += "//------------------------------------------------------------------------";

		xLOG_CTRL->CREATE__SUB_DIRECTORY(sObject_Name);
		xLOG_CTRL->SET__PROPERTY(file_name,12*1,60*12);

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

	// DB - SYS ...
	{
		def_name = "OBJ.DB_SYS";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, def_data);

		//
		var_name = "SYSTEM.MSG";
		LINK__EXT_VAR_STRING_CTRL(sEXT_CH__SYSTEM_MSG, def_data,var_name);

		var_name = "FUNCTION.MSG";		
		LINK__EXT_VAR_STRING_CTRL(sEXT_CH__FNC_MSG, def_data,var_name);

		//
		var_name = "CHM_PM_ITEM.WAP_CONDUCTANCE.FLAG";
		LINK__EXT_VAR_STRING_CTRL(sEXT_CH__CHM_PM_ITEM__WAP_CONDUCTANCE_FLAG, def_data,var_name);
	}

	// SYSTEM CHANNEL ...
	{
		//
		def_name = "CH.FNC.NAME";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name,ch_name);

		p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name,obj_name,var_name);
		LINK__EXT_VAR_STRING_CTRL(sEXT_CH__SYS_FNC_NAME,obj_name,var_name);

		//
		def_name = "CH.FNC.MSG";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name,ch_name);

		p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name,obj_name,var_name);
		LINK__EXT_VAR_STRING_CTRL(sEXT_CH__SYS_FNC_MSG,obj_name,var_name);

		//
		def_name = "CH.FNC.LOCK";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name,ch_name);

		p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name,obj_name,var_name);
		LINK__EXT_VAR_STRING_CTRL(sEXT_CH__SYS_FNC_LOCK,obj_name,var_name);
	}

	// CH.CHM.PRESSURE ...
	{
		def_name = "CH.CHM_PRESSURE";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name,ch_name);

		p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name,obj_name,var_name);
		LINK__EXT_VAR_STRING_CTRL(sEXT_CH__CHM_PRESSURE,obj_name,var_name);
	}

	// CH.DGF_CENTER_WT_SP ...
	{
		def_name = "CH.DGF_CENTER_WT_SP";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name,ch_name);

		p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name,obj_name,var_name);
		LINK__EXT_VAR_STRING_CTRL(sEXT_CH__DGF_CENTER_WT_SP,obj_name,var_name);	
	}

	// OBJ - CHM CTRL ...
	{
		def_name = "OBJ.CHM_CTRL";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name,obj_name);

		pOBJ_CTRL__CHM = p_ext_obj_create->Create__OBJECT_CTRL(obj_name);
	}

	// OBJ - WAP CTRL ...
	{
		def_name = "OBJ.WAP_CTRL";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name,obj_name);

		pOBJ_CTRL__WAP = p_ext_obj_create->Create__OBJECT_CTRL(obj_name);

		//
		var_name = "POS.VALUE";
		LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__PARA_TRG_POS, obj_name,var_name);

		var_name = "PRESET.POS.VALUE";
		LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__PARA_PRESET_POS, obj_name,var_name);

		var_name = "CONTROL.TYPE";
		LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__PARA_CONTROL_TYPE, obj_name,var_name);

		//
		var_name = "CFG.C_Ring.Offset_Move";
		LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__CFG_C_Ring_Offset_Move, obj_name,var_name);

		var_name = "CFG.C_Ring.Offset_Check.Auto_Mode";
		LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__CFG_C_Ring_Offset_Check_Auto_Mode, obj_name,var_name);

		//
		var_name = "PARA.INITIAL_CALL.FLAG";
		LINK__EXT_VAR_STRING_CTRL(sEXT_CH__WAP__PARA_INITIAL_CALL_FLAG, obj_name,var_name);
	}

	// OBJ - FNC MFCx CTRL ...
	{
		def_name = "OBJ.FNC_MFC";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name,obj_name);

		pOBJ_CTRL__FNC_MFC = p_ext_obj_create->Create__OBJECT_CTRL(obj_name);

		//
		var_name = "PARA.MFC.TYPE";
		LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__FNC_MFC__PARA_MFC_TYPE, obj_name,var_name);

		var_name = "PARA.MFC.FLOW";
		LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__FNC_MFC__PARA_MFC_FLOW, obj_name,var_name);
	}

	// OBJ - MFCx CTRL ...
	{
		def_name = "OBJ.MFC_SIZE";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name,def_data);

		int limit = atoi(def_data);
		int i;

		if(limit > CFG__MFC_SIZE)
		{
			limit = CFG__MFC_SIZE;
		}
		iSIZE__OBJ_MFCx = limit;

		for(i=0;i<limit;i++)
		{
			def_name.Format("OBJ.MFC%1d", i+1);
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name,obj_name);

			//
			var_name = "CFG.GAS.NAME";
			LINK__EXT_VAR_STRING_CTRL(sEXT_CH__PARA_MFCx_GAS_NAME[i], obj_name,var_name);
		}
	}

	return 1;
}

//-------------------------------------------------------------------------
int CObj__WAP_POS_CONDUCT::__CALL__CONTROL_MODE(mode,p_debug,p_variable,p_alarm)
{
	int flag = -1;


	if(sEXT_CH__SYS_FNC_NAME->Check__DATA("") < 0)
	{
		int alarm_id = ALID__FNC_CANNOT_RUN;
		CString alm_msg;
		CString alm_bff;
		CString r_act;
		CString var_data;

		sEXT_CH__SYS_FNC_NAME->Get__DATA(var_data);
		alm_msg.Format("Now, %s is running.\n",var_data);
		alm_bff.Format("Please, after %s is finished, run WAP Utility Program.\n",var_data);
		alm_msg += alm_bff;

		p_alarm->Check__ALARM(alarm_id,r_act);
		p_alarm->Post__ALARM_With_MESSAGE(alarm_id,alm_msg);
		return -1;
	}

	// ...
	{
		CString fnc_name;
		CString fnc_msg;

		fnc_name.Format("%s's %s",sObject_Name,mode);
		fnc_msg.Format("%s : Started ...",mode);

		xLOG_CTRL->WRITE__LOG(fnc_msg);

		sEXT_CH__SYS_FNC_NAME->Set__DATA(fnc_name);
		sEXT_CH__SYS_FNC_MSG->Set__DATA(fnc_msg);
		sEXT_CH__SYS_FNC_LOCK->Set__DATA("WAP");

		sEXT_CH__SYSTEM_MSG->Set__DATA("WAP Conductance Check : Started ...");
		sEXT_CH__FNC_MSG->Set__DATA("");

		//
		sEXT_CH__WAP__PARA_INITIAL_CALL_FLAG->Set__DATA(STR__YES);
	}

	// ...
	{
		IF__CTRL_MODE(sMODE__POS_CONDUCT)
		{
			flag = Call__POS_CONDUCT(p_variable,p_alarm);
		}
		ELSE_IF__CTRL_MODE(sMODE__DATA_SIM)
		{
			flag = Call__DATA_SIM(p_variable,p_alarm);
		}
		ELSE_IF__CTRL_MODE(sMODE__POSITION_PRESSURE_CHECK)
		{
			flag = Call__POSITION_PRESSURE_CHECK(p_variable,p_alarm);
		}
		ELSE_IF__CTRL_MODE(sMODE__PULSE_SCAN)
		{
			flag = Call__PULSE_SCAN(p_variable,p_alarm);
		}

	else
	{
		CString bff;
		CString alarm_msg;
		CString r_act;

		bff.Format("Object Name : %s\n",sObject_Name);
		alarm_msg  = bff;
		bff.Format("Unknown Object Mode : \"%s\"\n",mode);
		alarm_msg += bff;

		p_alarm->Popup__ALARM_With_MESSAGE(ALID__OBJECT_MODE_UNKNOWN,alarm_msg,r_act);
	}
	}

	// ...
	{
		CString log_msg;

		if(flag > 0)
		{
			log_msg.Format("%s : Completed ...", mode);
		}
		else
		{
			log_msg.Format("%s : Aborted ...", mode);
		}

		xLOG_CTRL->WRITE__LOG(log_msg);
	}

	// ...
	{
		sEXT_CH__SYS_FNC_NAME->Set__DATA("");
		sEXT_CH__SYS_FNC_MSG->Set__DATA("");
		sEXT_CH__SYS_FNC_LOCK->Set__DATA("");

		sEXT_CH__SYSTEM_MSG->Set__DATA("");
		sEXT_CH__FNC_MSG->Set__DATA("");

		sEXT_CH__WAP__PARA_INITIAL_CALL_FLAG->Set__DATA("");
	}
	return flag;
}

int CObj__WAP_POS_CONDUCT::__CALL__MONITORING(id,p_variable,p_alarm)
{
	switch(id)
	{
		case MON_ID__STATUS_CTRL:
			Mon__STATUS_CTRL(p_variable,p_alarm);
			break;
	}

	return 1;
}
