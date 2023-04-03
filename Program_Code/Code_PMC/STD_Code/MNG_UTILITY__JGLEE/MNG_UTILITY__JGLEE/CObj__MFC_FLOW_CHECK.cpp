#include "StdAfx.h"
#include "CObj__MFC_FLOW_CHECK.h"



//-------------------------------------------------------------------------
CObj__MFC_FLOW_CHECK::CObj__MFC_FLOW_CHECK()
{

}
CObj__MFC_FLOW_CHECK::~CObj__MFC_FLOW_CHECK()
{

}


//-------------------------------------------------------------------------
int CObj__MFC_FLOW_CHECK::__DEFINE__CONTROL_MODE(obj,l_mode)
{
	sObject_Name = obj;

	// ...
	{
		ADD__CTRL_VAR(sMODE__PARTIAL_PRESSURE, "PARTIAL.PRESSURE");
		ADD__CTRL_VAR(sMODE__MFC_CAL, "MFC.CAL");
		ADD__CTRL_VAR(sMODE__ALL_CHECK, "ALL.CHECK");
	}
	return 1;
}
int CObj__MFC_FLOW_CHECK::__DEFINE__VERSION_HISTORY(version)
{

	return 1;
}


// ...
#define APP_DSP__GAS_TYPE								\
"GAS01 GAS02 GAS03 GAS04 GAS05							\
 GAS06 GAS07 GAS08 GAS09 GAS10							\
 GAS11"

#define APP_DSP__TEST_MODE								\
"MFC.FLOW  MFC.CAL"

#define APP_DSP__FLOW_MODE	 							\
"1_%  5_%  10_%  YSK_%  USER.DEF						\
  5%_1Point  10%_1Point  15%_1Point   20%_1Point		\
 25%_1Point  30%_1Point  35%_1Point   40%_1Point		\
 45%_1Point  50%_1Point  55%_1Point   60%_1Point		\
 65%_1Point  70%_1Point  75%_1Point   80%_1Point		\
 85%_1Point  90%_1Point  95%_1Point  100%_1Point"

#define APP_DSP__NO_YES									\
"NO  YES"

// ...
#define  MON_ID__STATUS_CTRL			1

 
int CObj__MFC_FLOW_CHECK::__DEFINE__VARIABLE_STD(p_variable)
{
	DECLARE__STD_VARIABLE;

	//-------------------------------------------------------------------------
	CString str_name;
	int i;
	int j;

	// SYSTEM CHANNEL ...
	{
		str_name = "OBJ.MSG";
		STD__ADD_STRING_WITH_COMMENT(str_name,"");
		LINK__VAR_STRING_CTRL(xCH__OBJ_MSG,str_name);
	}

	// INFO CHANNEL ...
	{
		str_name = "INFO.CUR.GAS.ID";
		STD__ADD_STRING_WITH_COMMENT(str_name,"");
		LINK__VAR_STRING_CTRL(sCH_INFO__CUR_GAS_ID,str_name);

		str_name = "INFO.CUR.GAS.NAME";
		STD__ADD_STRING_WITH_COMMENT(str_name,"");
		LINK__VAR_STRING_CTRL(sCH_INFO__CUR_GAS_NAME,str_name);

		str_name = "INFO.CUR.GAS.FLOW.SET";
		STD__ADD_STRING_WITH_COMMENT(str_name,"");
		LINK__VAR_STRING_CTRL(sCH_INFO__CUR_GAS_FLOW_SET,str_name);

		//
		str_name = "INFO.CUR.GAS.MIN";
		STD__ADD_STRING_WITH_COMMENT(str_name,"");
		LINK__VAR_STRING_CTRL(sCH_INFO__CUR_GAS_MIN,str_name);

		str_name = "INFO.CUR.GAS.MAX";
		STD__ADD_STRING_WITH_COMMENT(str_name,"");
		LINK__VAR_STRING_CTRL(sCH_INFO__CUR_GAS_MAX,str_name);

		//
		str_name = "INFO.LIST_CTRL";
		STD__ADD_STRING_WITH_COMMENT(str_name,"");
		LINK__VAR_STRING_CTRL(sCH_INFO__LIST_CTRL,str_name);

		str_name = "INFO.ITEM_CTRL";
		STD__ADD_STRING_WITH_COMMENT(str_name,"");
		LINK__VAR_STRING_CTRL(sCH_INFO__ITEM_CTRL,str_name);

		str_name = "INFO.SETPOINT.MODE";
		STD__ADD_STRING_WITH_COMMENT(str_name,"");
		LINK__VAR_STRING_CTRL(sCH_INFO__SETPOINT_MODE,str_name);

		//
		str_name = "INFO.LIST.SEL.REQ";
		STD__ADD_STRING_WITH_COMMENT(str_name,"");
		LINK__VAR_STRING_CTRL(sCH_INFO__LIST_SEL_REQ,str_name);
	
		str_name = "INFO.LIST.SEL.STS";
		STD__ADD_STRING_WITH_COMMENT(str_name,"");
		LINK__VAR_STRING_CTRL(sCH_INFO__LIST_SEL_STS,str_name);
	}

	// PARAMETER .....
	{
		// TEST MODE  :  MFC.FLOW  MFC.CAL
		str_name = "PARA.TEST.MODE";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name,APP_DSP__TEST_MODE,"");
		LINK__VAR_DIGITAL_CTRL(dCH_PARA__TEST_MODE, str_name);

		// MFC SETTING MODE  :  10%  USER.DEF
		str_name = "PARA.MFC.SETTING.MODE";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name,APP_DSP__FLOW_MODE,"");
		LINK__VAR_DIGITAL_CTRL(dCH_PARA__MFC_SETTING_MODE, str_name);

		//
		for(i=0; i<CFG__MFC_SIZE; i++)
		{
			str_name.Format("APP.GAS.USE.FLAG.%1d",i+1);
			STD__ADD_DIGITAL_WITH_X_OPTION(str_name,APP_DSP__NO_YES,"");
			LINK__VAR_DIGITAL_CTRL(dCH_APP__GAS_USE_FLAG[i],str_name);

			str_name.Format("APP.GAS.ID.%1d",i+1);
			STD__ADD_STRING_WITH_X_OPTION(str_name,"");
			LINK__VAR_STRING_CTRL(sCH_APP__GAS_ID[i],str_name);

			str_name.Format("APP.GAS.CHECK_PRESSURE.%1d",i+1);
			STD__ADD_ANALOG_WITH_X_OPTION(str_name,"torr",3,0.0,10,"");
			LINK__VAR_ANALOG_CTRL(aCH_APP__GAS_CHECK_PRESSURE[i],str_name);
				
			str_name.Format("APP.GAS.STATUS.%1d",i+1);
			STD__ADD_STRING_WITH_X_OPTION(str_name,"");
			LINK__VAR_STRING_CTRL(sCH_APP__GAS_STATUS[i],str_name);

			str_name.Format("APP.GAS.VIEW.FLAG.%1d",i+1);
			STD__ADD_STRING_WITH_COMMENT(str_name,"");
			LINK__VAR_STRING_CTRL(sCH_APP__GAS_VIEW_FLAG[i],str_name);

			str_name.Format("APP.GAS.RUN.MODE.%1d",i+1);
			STD__ADD_STRING_WITH_X_OPTION(str_name,"");
			LINK__VAR_STRING_CTRL(sCH_APP__GAS_RUN_MODE[i],str_name);
		}

		//
		for(i=0; i<CFG__GAS_FLOW_LIST; i++)
		{
			str_name.Format("PARA.GAS.SET.AUTO.FLOW.%1d",i+1);
			STD__ADD_ANALOG_WITH_X_OPTION(str_name,"%",1,0.0,100.0,"");
			LINK__VAR_ANALOG_CTRL(aCH_PARA__GAS_SET_AUTO_FLOW[i], str_name);

			str_name.Format("PARA.GAS.SET.USER.FLOW.%1d",i+1);
			STD__ADD_ANALOG_WITH_X_OPTION(str_name,"sccm",1,0.0,10000.0,"");
			LINK__VAR_ANALOG_CTRL(aCH_PARA__GAS_SET_USER_FLOW[i], str_name);
			
			str_name.Format("PARA.GAS.CURRENT.FLOW.%1d",i+1);
			STD__ADD_STRING_WITH_COMMENT(str_name,"");
			LINK__VAR_STRING_CTRL(sCH_PARA__GAS_CURRENT_FLOW[i], str_name);

			str_name.Format("PARA.CAL.ERROR.RESULT.%1d",i+1);
			STD__ADD_STRING_WITH_COMMENT(str_name,"");
			LINK__VAR_STRING_CTRL(sCH_PARA__CAL_ERROR_RESULT[i], str_name);

			str_name.Format("PARA.CURRENT.PRESSURE.%1d",i+1);
			STD__ADD_STRING_WITH_COMMENT(str_name,"");
			LINK__VAR_STRING_CTRL(sCH_PARA__CURRENT_PRESSURE[i], str_name);
		}

		// START PRESSURE
		str_name = "PARA.CHECK.START.PRESSURE";
		STD__ADD_STRING_WITH_COMMENT(str_name,"");
		LINK__VAR_STRING_CTRL(sCH_PARA__CHECK_START_PRESSURE, str_name);

		// END PRESSURE
		str_name = "PARA.CHECK.END.PRESSURE";
		STD__ADD_STRING_WITH_COMMENT(str_name,"");
		LINK__VAR_STRING_CTRL(sCH_PARA__CHECK_END_PRESSURE, str_name);

		// CAL TIME 
		str_name = "PARA.CHECK.CAL.TIME";
		STD__ADD_STRING_WITH_COMMENT(str_name,"");
		LINK__VAR_STRING_CTRL(sCH_PARA__CHECK_CAL_TIME, str_name);

		// CHECK TIME COUNT
		str_name = "PARA.CHECK.TIME.COUNT";
		STD__ADD_STRING_WITH_COMMENT(str_name,"");
		LINK__VAR_STRING_CTRL(sCH_PARA__CHECK_TIME_COUNT, str_name);

		// CHECK DATE
		str_name = "PARA.CHECK.DATE";
		STD__ADD_STRING_WITH_COMMENT(str_name,"");
		LINK__VAR_STRING_CTRL(sCH_PARA__CHECK_DATE, str_name);

		// CHECK TIME
		str_name = "PARA.CHECK.TIME";
		STD__ADD_STRING_WITH_COMMENT(str_name,"");
		LINK__VAR_STRING_CTRL(sCH_PARA__CHECK_TIME, str_name);

		//
		str_name = "PARA.RUN.MODE.CHECK";
		STD__ADD_STRING_WITH_COMMENT(str_name,"");
		LINK__VAR_STRING_CTRL(sCH_PARA__RUN_MODE_CHECK, str_name);
	}

	// CONFIG .....
	{
		str_name = "CFG.PROPORTION.COEFFICENT";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name,"const", 3, 0.0 ,1000.0, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_PROPORTION_COEFFICENT, str_name);

		str_name = "CFG.MFC.MAX.GAS.CAL.FLOW";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name,"sccm",0,0,10000,"");
		LINK__VAR_ANALOG_CTRL(aCH_CFG__MFC_MAX_GAS_CAL_FLOW, str_name);

		//
		str_name = "CFG.OVER_PUMPING.TIME";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name,"sec",0,0,100,"");
		LINK__VAR_ANALOG_CTRL(aCH_CFG__OVER_PUMPING_TIME,str_name);

		str_name = "CFG.MFC.FLOW.STABLE.DELAY.SEC";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name,"sec",0,0,9999,"");
		LINK__VAR_ANALOG_CTRL(aCH_CFG__MFC_FLOW_STABLE_DELAY_SEC, str_name);

		str_name = "CFG.MFC.FLOW.REF.PRESSURE";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name,"torr",3,0.0,800.0,"");
		LINK__VAR_ANALOG_CTRL(aCH_CFG__MFC_FLOW_REF_PRESSURE, str_name);

		str_name = "CFG.MFC.FLOW.CHECK.TIMEOUT";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name,"sec", 3,0,9999,"");
		LINK__VAR_ANALOG_CTRL(aCH_CFG__MFC_FLOW_CHECK_TIMEOUT, str_name);

		for(i=0; i<CFG__MFC_SIZE; i++)
		{
			// Error 
			{
				str_name.Format("CFG.MFC.FLOW.LOW.ERROR.%1d", i+1);
				STD__ADD_ANALOG_WITH_X_OPTION(str_name,"%",1,1,100.0,"");
				LINK__VAR_ANALOG_CTRL(aCH_CFG__MFC_FLOW_LOW_ERROR[i], str_name);

				str_name.Format("CFG.MFC.FLOW.HIGH.ERROR.%1d", i+1);
				STD__ADD_ANALOG_WITH_X_OPTION(str_name,"%",1,1,100.0,"");
				LINK__VAR_ANALOG_CTRL(aCH_CFG__MFC_FLOW_HIGH_ERROR[i], str_name);
			}

			// Warning
			{
				str_name.Format("CFG.MFC.FLOW.LOW.WARNING.%1d", i+1);
				STD__ADD_ANALOG_WITH_X_OPTION(str_name,"%",1,1,100.0,"");
				LINK__VAR_ANALOG_CTRL(aCH_CFG__MFC_FLOW_LOW_WARNING[i], str_name);

				str_name.Format("CFG.MFC.FLOW.HIGH.WARNING.%1d", i+1);
				STD__ADD_ANALOG_WITH_X_OPTION(str_name,"%",1,1,100.0,"");
				LINK__VAR_ANALOG_CTRL(aCH_CFG__MFC_FLOW_HIGH_WARNING[i], str_name);
			}
		}

		//
		str_name = "CFG.TEST.ORDER";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name,"BOTTOM_TO_UP  TOP_TO_DOWN","");
		LINK__VAR_DIGITAL_CTRL(dCH_CFG__TEST_ORDER, str_name);
	}

	// RESULT .....
	{
		for(i=0; i<CFG__MFC_SIZE; i++)
		{
			for(j=0; j<CFG__GAS_FLOW_LIST; j++)
			{
				str_name.Format("RESULT%1d.CURRENT_FLOW.%1d", i+1,j+1);
				STD__ADD_STRING_WITH_X_OPTION(str_name,"");
				LINK__VAR_STRING_CTRL(sCH_RESULT__CURRENT_FLOW[i][j], str_name);

				str_name.Format("RESULT%1d.CURRENT_PRESSURE.%1d", i+1,j+1);
				STD__ADD_STRING_WITH_X_OPTION(str_name,"");
				LINK__VAR_STRING_CTRL(sCH_RESULT__CURRENT_PRESSURE[i][j], str_name);

				str_name.Format("RESULT%1d.CAL_ERROR.%1d", i+1,j+1);
				STD__ADD_STRING_WITH_X_OPTION(str_name,"");
				LINK__VAR_STRING_CTRL(sCH_RESULT__CAL_ERROR[i][j], str_name);
			}
			
			str_name.Format("RESULT%1d.CHECK_DATE",i+1);
			STD__ADD_STRING_WITH_X_OPTION(str_name,"");
			LINK__VAR_STRING_CTRL(sCH_RESULT__CHECK_DATE[i], str_name);

			str_name.Format("RESULT%1d.CHECK_TIME",i+1);
			STD__ADD_STRING_WITH_X_OPTION(str_name,"");
			LINK__VAR_STRING_CTRL(sCH_RESULT__CHECK_TIME[i], str_name);
		}
	}

	// ...
	{
		p_variable->Add__MONITORING_PROC(3.0, MON_ID__STATUS_CTRL);
	}
	return 1;
}
int CObj__MFC_FLOW_CHECK::__DEFINE__ALARM(p_alarm)
{
	DECLARE__ALARM;

	// ...
	CString title;
	title.Format("%s - ",sObject_Name);

	int alarm_id;
	CString alarm_title;
	CString alarm_msg;
	CStringArray l_act;
	int i;
	
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
		alarm_title += "MFC Partial & CAL. : Utility Program Can't run !";

		alarm_msg = "";

		l_act.RemoveAll();
		l_act.Add("CHECK");
	
		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	// ...
	{
		alarm_id = ALID__MFC_FLOW_CHECK_TIMEOUT;

		alarm_title  = title;
		alarm_title += "MFC FLOW CHECK Timeout !";

		alarm_msg = "";

		l_act.RemoveAll();
		l_act.Add("CHECK");

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	// ...
	{
		alarm_id = ALID__MFC_MAX_GAS_CAL_FLOW;

		alarm_title  = title;
		alarm_title += "MFC FLOW MAX. GAS CAL. FLOW : ERROR !";

		alarm_msg = "";

		l_act.RemoveAll();
		l_act.Add("CHECK");

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	// Offset : 20
	{
		CString msg;

		for(i=0;i<CFG__MFC_SIZE;i++)
		{
			alarm_id = ALID__MFC_CAL__WARNING_LOW + i;

			alarm_title  = title;
			msg.Format("MFC%1d's Calibration : Low Warning.", i+1);
			alarm_title += msg;

			alarm_msg = "";

			l_act.RemoveAll();
			l_act.Add("CHECK");

			ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
		}
	}
	// Offset : 20
	{
		CString msg;

		for(i=0;i<CFG__MFC_SIZE;i++)
		{
			alarm_id = ALID__MFC_CAL__WARNING_HIGH + i;

			alarm_title  = title;
			msg.Format("MFC%1d's Calibration : High Warning.", i+1);
			alarm_title += msg;

			alarm_msg = "";
			
			l_act.RemoveAll();
			l_act.Add("CHECK");

			ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
		}
	}
	// Offset : 20
	{
		CString msg;

		for(i=0;i<CFG__MFC_SIZE;i++)
		{
			alarm_id = ALID__MFC_CAL__ERROR_LOW + i;

			alarm_title  = title;
			msg.Format("MFC%1d's Calibration : Low Error.", i+1);
			alarm_title += msg;

			alarm_msg = "";

			l_act.RemoveAll();
			l_act.Add("CHECK");

			ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
		}
	}
	// Offset : 20
	{
		CString msg;

		for(i=0;i<CFG__MFC_SIZE;i++)
		{
			alarm_id = ALID__MFC_CAL__ERROR_HIGH + i;

			alarm_title  = title;			
			msg.Format("MFC%1d's Calibration : High Error.", i+1);
			alarm_title += msg;

			alarm_msg = "";

			l_act.RemoveAll();
			l_act.Add("CHECK");

			ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
		}
	}

	return 1;
}

int CObj__MFC_FLOW_CHECK::__Define__USER_FUNCTION(CII_DEFINE__FUNCTION *p_fnc_ctrl)
{
	mERROR__USER_FNC.Set__OBJ_NAME(sObject_Name);
	p_fnc_ctrl->Link__ERROR_FEEDBACK(&mERROR__USER_FNC);

	return 1;
}


//-------------------------------------------------------------------------
int CObj__MFC_FLOW_CHECK::__INITIALIZE__OBJECT(p_variable,p_ext_obj_create)
{
	p_ext_obj_create->Link__DEF_VARIABLE__ERROR_FEEDBACK(&mERROR__DEF_VAR);

	// ...
	SCX__SEQ_INFO x_seq_info;
	iSIM_MODE = x_seq_info->Is__SIMULATION_MODE();

	// ...
	CString def_name;
	CString def_data;
	CString ch_name;
	CString obj_name;
	CString var_name;
	CString var_data;
	int i;

	// DB - SYS
	{
		def_name = "OBJ.DB_SYS";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name,def_data);

		//
		var_name = "SYSTEM.MSG";
		LINK__EXT_VAR_STRING_CTRL(sEXT_CH__SYSTEM_MSG,def_data,var_name);

		var_name = "FUNCTION.MSG";		
		LINK__EXT_VAR_STRING_CTRL(sEXT_CH__FNC_MSG,def_data,var_name);
	}

	// DB - ETCHER .....
	{
		def_name = "OBJ.DB_ETCHER";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name,obj_name);

		//
		var_name = "SYS.CHM.TEMPERATURE";
		LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__DB_SYS_CHM_TEMPERATURE, obj_name,var_name);

		var_name = "SYS.CHM.VOLUMN";
		LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__DB_SYS_CHM_VOLUMN, obj_name,var_name);
	}

	// SYSTEM CHANNEL .....
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

	// OBJ - CHM CTRL .....
	{
		def_name = "OBJ.CHM_CTRL";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name,obj_name);

		pOBJ_CTRL__CHM = p_ext_obj_create->Create__OBJECT_CTRL(obj_name);

		//
	}
	
	// OBJ - VAT CTRL ...
	{
		def_name = "OBJ.VAT_CTRL";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name,obj_name);

		pOBJ_CTRL__VAT = p_ext_obj_create->Create__OBJECT_CTRL(obj_name);
	}

	// OBJ - GAS_VLV CTRL .....
	{
		def_name = "OBJ.GAS_VALVE";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name,obj_name);

		pOBJ_CTRL__GAS_VLV = p_ext_obj_create->Create__OBJECT_CTRL(obj_name);

		//
		var_name = "PARA.INTERLOCK.SKIP";
		LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__GAS_VLV__PARA_INTERLOCK_SKIP, obj_name,var_name);

		//
		var_name = "PARA.MFC.TYPE";
		LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__GAS_VLV__PARA_MFC_TYPE, obj_name,var_name);

		var_name = "PARA.MFC.FLOW";
		LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__GAS_VLV__PARA_MFC_FLOW, obj_name,var_name);
	}
	
	// OBJ - MFCx CTRL .....
	{
		def_name = "OBJ.MFC_SIZE";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name,def_data);
		int limit = atoi(def_data);

		if(limit > CFG__MFC_SIZE)		limit = CFG__MFC_SIZE;
		iSIZE__OBJ_MFCx = limit;

		for(int i=0; i<limit; i++)
		{
			def_name.Format("OBJ.MFC%1d", i+1);
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name,obj_name);

			pOBJ_CTRL__MFCx[i] = p_ext_obj_create->Create__OBJECT_CTRL(obj_name);
			
			//
			var_name = "PARA.SET.FLOW";
			LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__PARA_MFCx_SET_FLOW[i], obj_name,var_name);

			var_name = "CFG.GAS.NAME";
			LINK__EXT_VAR_STRING_CTRL(sEXT_CH__PARA_MFCx_GAS_NAME[i], obj_name,var_name);

			var_name = "MON.MFC.READ.FLOW";
			LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__PARA_MFCx_GET_FLOW[i], obj_name,var_name);
		}
	}

	// ...
	{
		// CH.CHM_PRESSURE.TORR
		def_name = "CH.CHM_PRESSURE.TORR";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name,ch_name);

		p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name,obj_name,var_name);
		LINK__EXT_VAR_STRING_CTRL(sEXT_CH__CHM_PRESSURE_TORR,obj_name,var_name);

		// CH.CHM_PRESSURE.mTORR
		def_name = "CH.CHM_PRESSURE.mTORR";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name,ch_name);

		p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name,obj_name,var_name);
		LINK__EXT_VAR_STRING_CTRL(sEXT_CH__CHM_PRESSURE_mTORR,obj_name,var_name);

		// CH.ISO_VLV
		def_name = "CH.ISO_VLV";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name,ch_name);

		p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name,obj_name,var_name);
		LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH___ISO_VLV,obj_name,var_name);
	}

	for(i=0; i<CFG__MFC_SIZE; i++)
	{
		var_data.Format("GAS%002d",i+1);
		sCH_APP__GAS_ID[i]->Set__DATA(var_data);
	}

	// ...
	{
		double cfg_value = aCH__CFG_PROPORTION_COEFFICENT->Get__VALUE();
		if(cfg_value < 0.001)		aCH__CFG_PROPORTION_COEFFICENT->Set__VALUE(1.0);

		iPRC_FLAG = -1;
	}
	
	return 1;
}


//-------------------------------------------------------------------------
int CObj__MFC_FLOW_CHECK::__CALL__CONTROL_MODE(mode,p_debug,p_variable,p_alarm)
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
		alm_bff.Format("Please, after %s is finished, run MFC Utility Program.\n",var_data);
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

		sEXT_CH__SYS_FNC_NAME->Set__DATA(fnc_name);
		sEXT_CH__SYS_FNC_MSG->Set__DATA(fnc_msg);
		sEXT_CH__SYS_FNC_LOCK->Set__DATA("MFC");

		//
		sEXT_CH__SYSTEM_MSG->Set__DATA(fnc_msg);
		sEXT_CH__FNC_MSG->Set__DATA("");
	}

	iPRC_FLAG = 1;

	// ...
	{
		IF__CTRL_MODE(sMODE__PARTIAL_PRESSURE)
		{
			iCHECK_MODE = CHECK_MODE__PARTIAL_PRESSURE;

			flag = Call__PARTIAL_PRESSURE(p_variable,p_alarm);
		}
		ELSE_IF__CTRL_MODE(sMODE__MFC_CAL)
		{
			iCHECK_MODE = CHECK_MODE__MFC_CAL;

			flag = Call__MFC_CAL(p_variable,p_alarm);
		}
		ELSE_IF__CTRL_MODE(sMODE__ALL_CHECK)	
		{
			iCHECK_MODE = CHECK_MODE__ALL_CHECK;

			flag = Call__ALL_CHECK(p_variable,p_alarm);
		}
	}

	iPRC_FLAG = -1;

	// ...
	{
		sEXT_CH__SYS_FNC_NAME->Set__DATA("");
		sEXT_CH__SYS_FNC_MSG->Set__DATA("");
		sEXT_CH__SYS_FNC_LOCK->Set__DATA("");

		sEXT_CH__SYSTEM_MSG->Set__DATA("");
		sEXT_CH__FNC_MSG->Set__DATA("");

		sCH_INFO__CUR_GAS_FLOW_SET->Set__DATA("");
	}
	return flag;
}
int CObj__MFC_FLOW_CHECK::__CALL__MONITORING(id,p_variable,p_alarm)
{
	if(id == MON_ID__STATUS_CTRL)		Mon__STATUS_CTRL(p_variable);

	return 1;
}
