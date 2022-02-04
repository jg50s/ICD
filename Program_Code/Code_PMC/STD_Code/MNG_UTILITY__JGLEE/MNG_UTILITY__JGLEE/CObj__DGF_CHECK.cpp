#include "StdAfx.h"
#include "CObj__DGF_CHECK.h"



//-------------------------------------------------------------------------
CObj__DGF_CHECK::CObj__DGF_CHECK()
{

}
CObj__DGF_CHECK::~CObj__DGF_CHECK()
{

}


//-------------------------------------------------------------------------
int CObj__DGF_CHECK::__DEFINE__CONTROL_MODE(obj,l_mode)
{
	sObject_Name = obj;

	// ...
	{
		ADD__CTRL_VAR(sMODE__ORIFICE_CHECK, "ORIFICE.CHECK");
	}
	return 1;
}
int CObj__DGF_CHECK::__DEFINE__VERSION_HISTORY(version)
{

	return 1;
}


// ...
#define APP_DSP__GAS_TYPE				\
	"GAS01 GAS02 GAS03 GAS04 GAS05			\
GAS06 GAS07 GAS08 GAS09 GAS10			\
GAS11 GAS12 GAS13 GAS14 GAS15			\
GAS16 GAS17"

// ...
#define  MON_ID__STATUS_CTRL			1


int CObj__DGF_CHECK::__DEFINE__VARIABLE_STD(p_variable)
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
			// ORIFICE SIZE 
			str_name.Format("CFG.ORIFICE.SIZE.%1d", i+1);
			STD__ADD_ANALOG_WITH_X_OPTION(str_name, "mm",3,0,10,"");
			LINK__VAR_ANALOG_CTRL(aCH_CFG__ORIFICE_SIZE[i], str_name);

			// BASELINE
			str_name.Format("CFG.BASELINE.%1d", i+1);
			STD__ADD_ANALOG_WITH_X_OPTION(str_name, "torr",1,0,1000,"");
			LINK__VAR_ANALOG_CTRL(aCH_CFG__BASELINE[i], str_name);

			// CURRENT LIST
			str_name.Format("PARA.CUR.RESULT.LIST.%1d", i+1);
			STD__ADD_STRING_WITH_X_OPTION(str_name, "");
			LINK__VAR_STRING_CTRL(sCH_PARA__CUR_RESULT_LIST[i], str_name);

			// NEW LIST
			str_name.Format("PARA.NEW.RESULT.LIST.%1d", i+1);
			STD__ADD_STRING_WITH_X_OPTION(str_name, "");
			LINK__VAR_STRING_CTRL(sCH_PARA__NEW_RESULT_LIST[i], str_name);

			// DELTA LIST
			str_name.Format("PARA.DELTA.RESULT.LIST.%1d", i+1);
			STD__ADD_STRING_WITH_X_OPTION(str_name, "");
			LINK__VAR_STRING_CTRL(sCH_PARA__DELTA_RESULT_LIST[i], str_name);
		}

		// CHECK TIME COUNT
		str_name = "PARA.CHECK.TIME.COUNT";
		STD__ADD_STRING_WITH_X_OPTION(str_name, "");
		LINK__VAR_STRING_CTRL(sCH_PARA__CHECK_TIME_COUNT, str_name);

		// START & END - PRESSURE
		str_name = "RESULT.START.PRESSURE";
		STD__ADD_STRING_WITH_X_OPTION(str_name, "");
		LINK__VAR_STRING_CTRL(sCH_RESULT__START_PRESSURE, str_name);

		str_name = "RESULT.END.PRESSURE";
		STD__ADD_STRING_WITH_X_OPTION(str_name, "");
		LINK__VAR_STRING_CTRL(sCH_RESULT__END_PRESSURE, str_name);


		// RESULT STRING
		str_name = "RESULT.STRING";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__RESULT_STRING, str_name);

		// REF STRING
		str_name = "REF.STRING";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__REF_STRING, str_name);
	}

	// CONFIG .....
	{
		// HIGH FLOW
		str_name = "CFG.HIGH.FLOW.GAS.NAME";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name, APP_DSP__GAS_TYPE, "");
		LINK__VAR_DIGITAL_CTRL(dCH_CFG__HIGH_FLOW_GAS_NAME, str_name);

		str_name = "CFG.HIGH.FLOW.GAS.SET";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name,"sccm",0,0,10000,"");
		LINK__VAR_ANALOG_CTRL(aCH_CFG__HIGH_FLOW_GAS_SET, str_name);

		// LOW FLOW
		str_name = "CFG.LOW.FLOW.GAS.NAME";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name, APP_DSP__GAS_TYPE, "");
		LINK__VAR_DIGITAL_CTRL(dCH_CFG__LOW_FLOW_GAS_NAME, str_name);

		str_name = "CFG.LOW.FLOW.GAS.SET";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name,"sccm",0,0,10000,"");
		LINK__VAR_ANALOG_CTRL(aCH_CFG__LOW_FLOW_GAS_SET, str_name);

		// 
		str_name = "CFG.BASELINE.TOLERANCE";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name,"%",0,0,100,"");
		LINK__VAR_ANALOG_CTRL(aCH_CFG__BASELINE_TOLERANCE, str_name);

		//
		str_name = "CFG.STABLE.DELAY.SEC";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name,"sec",0,0,10000,"");
		LINK__VAR_ANALOG_CTRL(aCH_CFG__STABLE_DELAY_SEC, str_name);

		str_name = "CFG.CHECK.DELAY.SEC";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name,"sec",0,0,10000,"");
		LINK__VAR_ANALOG_CTRL(aCH_CFG__CHECK_DELAY_SEC, str_name);

		str_name = "CFG.PUMPING.DELAY.SEC";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name,"sec",0,0,100,"");
		LINK__VAR_ANALOG_CTRL(aCH_CFG__PUMPING_DELAY_SEC, str_name);

		//
		str_name = "CFG.TEST.ORDER";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name,"BOTTOM_TO_UP  TOP_TO_DOWN","");
		LINK__VAR_DIGITAL_CTRL(dCH_CFG__TEST_ORDER, str_name);
	}

	//.....
	{
		p_variable->Add__MONITORING_PROC(3.0, MON_ID__STATUS_CTRL);
	}
	return 1;
}
int CObj__DGF_CHECK::__DEFINE__ALARM(p_alarm)
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
		alarm_title += "DGF CHECK : Utility Program Can't run !";

		alarm_msg = "";

		l_act.RemoveAll();
		l_act.Add("CHECK");

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	// ...
	{
		alarm_id = ALID__BASELINE_TOLERANCE_ERROR;

		alarm_title  = title;
		alarm_title += "Orifice Check : Tolerance Error";

		alarm_msg = "";

		l_act.RemoveAll();
		l_act.Add("CHECK");

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	return 1;
}

int CObj__DGF_CHECK::__Define__USER_FUNCTION(CII_DEFINE__FUNCTION *p_fnc_ctrl)
{
	mERROR__USER_FNC.Set__OBJ_NAME(sObject_Name);
	p_fnc_ctrl->Link__ERROR_FEEDBACK(&mERROR__USER_FNC);

	return 1;
}


//-------------------------------------------------------------------------
int CObj__DGF_CHECK::__INITIALIZE__OBJECT(p_variable,p_ext_obj_create)
{
	// ...
	{
		p_ext_obj_create->Link__DEF_VARIABLE__ERROR_FEEDBACK(&mERROR__DEF_VAR);
	}

	// ...
	CString def_name;
	CString def_data;
	CString ch_name;
	CString obj_name;
	CString var_name;

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

	// CH.PRESSURE .....
	{
		def_name = "CH.CHM_PRESSURE";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name,ch_name);

		p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name,obj_name,var_name);
		LINK__EXT_VAR_STRING_CTRL(sEXT_CH__PRESSURE, obj_name,var_name);
	}

	// OBJ - CHM CTRL .....
	{
		def_name = "OBJ.CHM_CTRL";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name,obj_name);

		pOBJ_CTRL__CHM = p_ext_obj_create->Create__OBJECT_CTRL(obj_name);
	}

	// OBJ - FNC MFCx CTRL .....
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

	// OBJ - DGF CTRL .....
	{
		def_name = "OBJ.DGF_CTRL";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name,obj_name);

		pOBJ_CTRL__DGF = p_ext_obj_create->Create__OBJECT_CTRL(obj_name);

		//
		var_name = "PARA.ORIFICE.TYPE";
		LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__PARA_ORIFICE_VLV, obj_name,var_name);
	}

	return 1;
}


//-------------------------------------------------------------------------
int CObj__DGF_CHECK::__CALL__CONTROL_MODE(mode,p_debug,p_variable,p_alarm)
{
	if(sEXT_CH__SYS_FNC_NAME->Check__DATA("") < 0)
	{
		int alarm_id = ALID__FNC_CANNOT_RUN;
		CString alm_msg;
		CString alm_bff;
		CString r_act;
		CString var_data;

		sEXT_CH__SYS_FNC_NAME->Get__DATA(var_data);
		alm_msg.Format("Now, %s is running.\n",var_data);
		alm_bff.Format("Please, after %s is finished, run DGF Utility Program.\n",var_data);
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
		sEXT_CH__SYS_FNC_LOCK->Set__DATA("DGF");

		sEXT_CH__SYSTEM_MSG->Set__DATA("Orifice Check : Started ...");
		sEXT_CH__FNC_MSG->Set__DATA("");
	}

	// ...
	int flag = -1;

	// ...
	{
		IF__CTRL_MODE(sMODE__ORIFICE_CHECK)
		{
			flag = Call__ORIFICE_CHECK(p_variable,p_alarm);
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
		sEXT_CH__SYS_FNC_NAME->Set__DATA("");
		sEXT_CH__SYS_FNC_MSG->Set__DATA("");
		sEXT_CH__SYS_FNC_LOCK->Set__DATA("");

		sEXT_CH__SYSTEM_MSG->Set__DATA("");
		sEXT_CH__FNC_MSG->Set__DATA("");
	}
	return flag;
}
int CObj__DGF_CHECK::__CALL__MONITORING(id,p_variable,p_alarm)
{
	switch(id)
	{
	case MON_ID__STATUS_CTRL:
		Mon__STATUS_CTRL(p_variable);
		break;
	}
	return 1;
}
