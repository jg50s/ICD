#include "StdAfx.h"
#include "CObj__APC_POS_CONDUCT.h"



//-------------------------------------------------------------------------
CObj__APC_POS_CONDUCT::CObj__APC_POS_CONDUCT()
{

}
CObj__APC_POS_CONDUCT::~CObj__APC_POS_CONDUCT()
{

}


//-------------------------------------------------------------------------
int CObj__APC_POS_CONDUCT::__DEFINE__CONTROL_MODE(obj,l_mode)
{
	sObject_Name = obj;

	// ...
	{
		ADD__CTRL_VAR(sMODE__POS_CONDUCT, "POS_CONDUCT");
	}
	return 1;
}
int CObj__APC_POS_CONDUCT::__DEFINE__VERSION_HISTORY(version)
{

	return 1;
}


// ...
#define APP_DSP__GAS_TYPE				\
"GAS01 GAS02 GAS03 GAS04 GAS05			\
 GAS06 GAS07 GAS08 GAS09 GAS10"


#define  MON_ID__STATUS_CTRL			1


int CObj__APC_POS_CONDUCT::__DEFINE__VARIABLE_STD(p_variable)
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

		str_name = "OBJ.ERROR_MSG";
		STD__ADD_STRING_WITH_COMMENT(str_name,"");
		LINK__VAR_STRING_CTRL(xCH__OBJ_ERROR_MSG,str_name);

		//
		str_name = "APP.AUTO_START_CTRL";
		STD__ADD_STRING_WITH_COMMENT(str_name,"");
		LINK__VAR_STRING_CTRL(xCH__AUTO_START_CTRL,str_name);

		str_name = "RESULT.SAVE.REQ";
		STD__ADD_STRING_WITH_COMMENT(str_name,"");
		LINK__VAR_STRING_CTRL(sCH__RESULT_SAVE_REQ,str_name);

		str_name = "CHECK_TYPE.UPDATE.REQ";
		STD__ADD_STRING_WITH_COMMENT(str_name,"");
		LINK__VAR_STRING_CTRL(sCH__CHECK_TYPE_UPDATE_REQ,str_name);

		str_name = "CHECK_TYPE.SAVE.REQ";
		STD__ADD_STRING_WITH_COMMENT(str_name,"");
		LINK__VAR_STRING_CTRL(sCH__CHECK_TYPE_SAVE_REQ,str_name);

		str_name = "CURRENT_REF.COPY.REQ";
		STD__ADD_STRING_WITH_COMMENT(str_name,"");
		LINK__VAR_STRING_CTRL(sCH__CURRENT_REF_COPY_REQ,str_name);

		str_name = "RESULT.ERROR_RANGE.CHECK.REQ";
		STD__ADD_STRING_WITH_COMMENT(str_name,"");
		LINK__VAR_STRING_CTRL(sCH__RESULT_ERROR_RANGE_CHECK_REQ,str_name);
	}

	// PARAMETER .....
	{
		// ... 
		{
			CString item_list;

			// 
			{
				str_name = "CFG.CHECK_TYPE";

				item_list  = STR__Ar_80;
				item_list += " ";
				item_list += STR__N2_5PER;
				item_list += " ";
				item_list += STR__User_Define;

				STD__ADD_DIGITAL_WITH_X_OPTION(str_name,item_list,"");
				LINK__VAR_DIGITAL_CTRL(dCH__CFG_CHECK_TYPE,str_name);
			}

			// 
			{
				str_name = "CFG.RESULT.ERROR_TYPE";
				STD__ADD_DIGITAL_WITH_X_OPTION(str_name,"New_&_Ref. New_&_Current Current_&_Ref.","");
				LINK__VAR_DIGITAL_CTRL(dCH__CFG_RESULT_ERROR_TYPE,str_name);

				str_name = "CFG.RESULT.ERROR_RANGE";
				STD__ADD_ANALOG_WITH_X_OPTION(str_name,"sccm/mtorr",3,0,1000,"");
				LINK__VAR_ANALOG_CTRL(aCH__CFG_RESULT_ERROR_RANGE,str_name);
			}

			//
			{
				str_name = "PARA.TEST.GAS.TYPE";
				STD__ADD_DIGITAL_WITH_X_OPTION(str_name, APP_DSP__GAS_TYPE,"");
				LINK__VAR_DIGITAL_CTRL(dCH_PARA__TEST_GAS_TYPE, str_name);

				str_name = "PARA.TEST.GAS.FLOW";
				STD__ADD_ANALOG_WITH_X_OPTION(str_name,"sccm",0,0,10000,"");
				LINK__VAR_ANALOG_CTRL(aCH_PARA__TEST_GAS_FLOW, str_name);

				str_name = "CUR.TEST.GAS.NAME";
				STD__ADD_STRING_WITH_COMMENT(str_name,"");
				LINK__VAR_STRING_CTRL(sCH__CUR_TEST_GAS_NAME, str_name);
			}
		}

		// ...
		{
			// New
			str_name = "PARA.TEST.DATE";
			STD__ADD_STRING_WITH_X_OPTION(str_name, "");
			LINK__VAR_STRING_CTRL(sCH_PARA__TEST_DATE, str_name);

			str_name = "PARA.TEST.TIME";
			STD__ADD_STRING_WITH_X_OPTION(str_name, "");
			LINK__VAR_STRING_CTRL(sCH_PARA__TEST_TIME, str_name);

			// Current
			str_name = "CUR.TEST.DATE";
			STD__ADD_STRING_WITH_X_OPTION(str_name, "");
			LINK__VAR_STRING_CTRL(sCH__CUR_TEST_DATE, str_name);

			str_name = "CUR.TEST.TIME";
			STD__ADD_STRING_WITH_X_OPTION(str_name, "");
			LINK__VAR_STRING_CTRL(sCH__CUR_TEST_TIME, str_name);
		}

		for(i=0;i<CFG__TEST_LIST;i++)
		{
			// New Parameter ...
			{
				str_name.Format("PARA.VLV.POS.%1d", i+1);
				STD__ADD_ANALOG_WITH_X_OPTION(str_name, "_",0,0,1000,"");
				LINK__VAR_ANALOG_CTRL(aCH_PARA__VLV_POS_LIST[i], str_name);

				str_name.Format("USER.VLV.POS.%1d", i+1);
				STD__ADD_ANALOG_WITH_X_OPTION(str_name, "_",0,0,1000,"");
				LINK__VAR_ANALOG_CTRL(aCH_USER__VLV_POS_LIST[i], str_name);

				//
				str_name.Format("PARA.CONDUCT.RESULT.%1d", i+1);
				STD__ADD_STRING_WITH_X_OPTION(str_name, "");
				LINK__VAR_STRING_CTRL(sCH_PARA__CONDUCT_RESULT[i], str_name);

				for(int k=0; k<_SIZE__TEST_TYPE; k++)
				{
					str_name.Format("PARA.CONDUCT.RESULT.%1d_OF_TYPE.%1d", i+1,k+1);
					STD__ADD_STRING_WITH_X_OPTION(str_name, "");
					LINK__VAR_STRING_CTRL(sCH_PARA__CONDUCT_RESULT_OF_TYPE[k][i], str_name);
				}
			}

			// Current Parameter ...
			{
				for(int k=0; k<_SIZE__TEST_TYPE; k++)
				{
					str_name.Format("CUR.VLV.POS.%1d_OF_TYPE.%1d", i+1,k+1);
					STD__ADD_STRING_WITH_X_OPTION(str_name, "");
					LINK__VAR_STRING_CTRL(sCH__CUR_VLV_POS_LIST_OF_TYPE[k][i], str_name);

					str_name.Format("CUR.CONDUCT.RESULT.%1d_OF_TYPE.%1d", i+1,k+1);
					STD__ADD_STRING_WITH_X_OPTION(str_name, "");
					LINK__VAR_STRING_CTRL(sCH__CUR_CONDUCT_RESULT_OF_TYPE[k][i], str_name);
				}

				//
				str_name.Format("CUR.VLV.POS.%1d", i+1);
				STD__ADD_STRING_WITH_X_OPTION(str_name, "");
				LINK__VAR_STRING_CTRL(sCH__CUR_VLV_POS_LIST[i], str_name);

				str_name.Format("CUR.CONDUCT.RESULT.%1d", i+1);
				STD__ADD_STRING_WITH_X_OPTION(str_name, "");
				LINK__VAR_STRING_CTRL(sCH__CUR_CONDUCT_RESULT[i], str_name);
			}

			// Reference List ...
			{
				str_name.Format("PARA.VLV.REF.%1d", i+1);
				STD__ADD_ANALOG_WITH_X_OPTION(str_name, "_",6,0,1000,"");
				LINK__VAR_ANALOG_CTRL(aCH_PARA__VLV_REF_LIST[i], str_name);

				str_name.Format("N2_5PER.VLV.REF.%1d", i+1);
				STD__ADD_ANALOG_WITH_X_OPTION(str_name, "_",6,0,1000,"");
				LINK__VAR_ANALOG_CTRL(aCH_N2_5PER__VLV_REF_LIST[i], str_name);

				str_name.Format("USER.VLV.REF.%1d", i+1);
				STD__ADD_ANALOG_WITH_X_OPTION(str_name, "_",6,0,1000,"");
				LINK__VAR_ANALOG_CTRL(aCH_USER__VLV_REF_LIST[i], str_name);
			}
		}

		// CHECK TIME COUNT
		str_name = "CUR.CHECK.TIME.COUNT";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__CUR_CHECK_TIME_COUNT, str_name);


		// Result Data ...
		{
			// New Result 
			str_name = "RESULT.STRING";
			STD__ADD_STRING_WITH_X_OPTION(str_name, "");
			LINK__VAR_STRING_CTRL(sCH__RESULT_STRING, str_name);

			// Current Result
			str_name = "CURRENT.STRING";
			STD__ADD_STRING_WITH_X_OPTION(str_name, "");
			LINK__VAR_STRING_CTRL(sCH__CUR_STRING, str_name);

			// Reference 
			str_name = "REF.STRING";
			STD__ADD_STRING(str_name);
			LINK__VAR_STRING_CTRL(sCH__REF_STRING, str_name);
		}
	}

	// CONFIG .....
	{
		str_name = "CFG.FLOW.DELAY.SEC";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name,"sec",0,0,10000,"");
		LINK__VAR_ANALOG_CTRL(aCH_CFG__FLOW_DELAY_SEC, str_name);

		str_name = "CFG.PRESSURE.STABLE.DELAY.SEC";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name,"sec",0,0,10000,"");
		LINK__VAR_ANALOG_CTRL(aCH_CFG__PRESSURE_STABLE_DELAY_SEC, str_name);

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
int CObj__APC_POS_CONDUCT::__DEFINE__ALARM(p_alarm)
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
		alarm_title += "APC Conductance : Utility Program Can't run !";

		alarm_msg = "";

		l_act.RemoveAll();
		l_act.Add("CHECK");

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	// ...
	{
		alarm_id = ALID__VAC_CONDUCTANCE_CHECK_ERROR;

		alarm_title  = title;
		alarm_title += "APC Conductance : Range Error !";

		alarm_msg = "";

		l_act.RemoveAll();
		l_act.Add("CHECK");

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	return 1;
}

int CObj__APC_POS_CONDUCT::__Define__USER_FUNCTION(CII_DEFINE__FUNCTION *p_fnc_ctrl)
{
	mERROR__USER_FNC.Set__OBJ_NAME(sObject_Name);
	p_fnc_ctrl->Link__ERROR_FEEDBACK(&mERROR__USER_FNC);


	return 1;
}


//-------------------------------------------------------------------------
int CObj__APC_POS_CONDUCT::__INITIALIZE__OBJECT(p_variable,p_ext_obj_create)
{
	p_ext_obj_create->Link__DEF_VARIABLE__ERROR_FEEDBACK(&mERROR__DEF_VAR);

	// ...
	CString def_name;
	CString def_data;
	CString ch_name;
	CString obj_name;
	CString var_name;

	// OBJ - VAT CTRL ...
	{
		def_name = "OBJ.VAT_CTRL";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name,obj_name);

		pOBJ_CTRL__VAT = p_ext_obj_create->Create__OBJECT_CTRL(obj_name);

		//
		var_name = "PARA.POSITION";
		LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__PARA_VLV_POS_DATA, obj_name,var_name);
	}

	// CH.CHM.PRESSURE ...
	{
		def_name = "CH.CHM_PRESSURE";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name,ch_name);

		p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name,obj_name,var_name);
		LINK__EXT_VAR_STRING_CTRL(sEXT_CH__CHM_PRESSURE,obj_name,var_name);
	}

	// OBJ - CHM CTRL ...
	{
		def_name = "OBJ.CHM_CTRL";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name,obj_name);

		pOBJ_CTRL__CHM = p_ext_obj_create->Create__OBJECT_CTRL(obj_name);
	}

	// OBJ - GAS_VLV ...
	{
		def_name = "OBJ.GAS_VLV";
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

	// DB - SYS ...
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
			LINK__EXT_VAR_STRING_CTRL(sEXT_CH__MFCx_CFG_GAS_NAME[i], obj_name,var_name);

			var_name = "CFG.MFC.MAX.VALUE";
			LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__MFCx_CFG_GAS_MAX[i], obj_name,var_name);
		}
	}

	return 1;
}


//-------------------------------------------------------------------------
int CObj__APC_POS_CONDUCT::__CALL__CONTROL_MODE(mode,p_debug,p_variable,p_alarm)
{
	CString obj_msg;

	// ...
	{
		obj_msg.Format("%s Started ...", mode);

		xCH__OBJ_MSG->Set__DATA(obj_msg);
	}

	//
	if(sEXT_CH__SYS_FNC_NAME->Check__DATA("") < 0)
	{
		obj_msg.Format("%s Interlocked ...", mode);
		xCH__OBJ_MSG->Set__DATA(obj_msg);

		// ...
		{
			int alarm_id = ALID__FNC_CANNOT_RUN;
			CString alm_msg;
			CString alm_bff;
			CString r_act;
			CString var_data;

			sEXT_CH__SYS_FNC_NAME->Get__DATA(var_data);
			alm_msg.Format("Now, %s is running.\n",var_data);
			alm_bff.Format("Please, after %s is finished, run APC Utility Program.\n",var_data);
			alm_msg += alm_bff;

			p_alarm->Check__ALARM(alarm_id,r_act);
			p_alarm->Post__ALARM_With_MESSAGE(alarm_id,alm_msg);
		}
		return -1;
	}

	// ...
	{
		CString fnc_name;
		CString fnc_msg;

		fnc_name.Format("%s's %s",sObject_Name,mode);
		fnc_msg.Format("%s Started ...", mode);

		sEXT_CH__SYS_FNC_NAME->Set__DATA(fnc_name);
		sEXT_CH__SYS_FNC_MSG->Set__DATA(fnc_msg);
		sEXT_CH__SYS_FNC_LOCK->Set__DATA("APC");

		sEXT_CH__SYSTEM_MSG->Set__DATA("APC Conductance Check : Started ...");
		sEXT_CH__FNC_MSG->Set__DATA("");
	}

	int flag = -1;

	// ...
	{
		IF__CTRL_MODE(sMODE__POS_CONDUCT)
		{
			flag = Call__POS_CONDUCT(p_variable,p_alarm);
		}
	}

	if((flag < 0) || (p_variable->Check__CTRL_ABORT() > 0))
	{
		obj_msg.Format("%s Aborted ...", mode);

		xCH__OBJ_MSG->Set__DATA(obj_msg);
	}
	else
	{
		obj_msg.Format("%s Completed ...", mode);

		xCH__OBJ_MSG->Set__DATA(obj_msg);
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
int CObj__APC_POS_CONDUCT::__CALL__MONITORING(id,p_variable,p_alarm)
{
	if(id == MON_ID__STATUS_CTRL)		Mon__STATUS_CTRL(p_variable,p_alarm);

	return 1;
}
