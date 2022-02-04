#include "StdAfx.h"
#include "CObj__RF_CONDUCT.h"



//-------------------------------------------------------------------------
CObj__RF_CONDUCT::CObj__RF_CONDUCT()
{

}
CObj__RF_CONDUCT::~CObj__RF_CONDUCT()
{

}


//-------------------------------------------------------------------------
int CObj__RF_CONDUCT::__DEFINE__CONTROL_MODE(obj,l_mode)
{
	sObject_Name = obj;

	// ...
	{
		ADD__CTRL_VAR(sMODE__RF_CHECK, "RF_CHECK");
	}
	return 1;
}
int CObj__RF_CONDUCT::__DEFINE__VERSION_HISTORY(version)
{

	return 1;
}

// ...
#define  MON_ID__STATUS_CTRL			1


int CObj__RF_CONDUCT::__DEFINE__VARIABLE_STD(p_variable)
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
		str_name = "PARA.TEST.MODE";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name,"MANUAL AUTO","");
		LINK__VAR_DIGITAL_CTRL(dCH_PARA__TEST_MODE,str_name);

		//
		str_name = "PARA.ACT.ACTIVE.FLAG";
		STD__ADD_STRING_WITH_COMMENT(str_name, "");
		LINK__VAR_STRING_CTRL(sCH_PARA__ACT_ACTIVE_FLAG,str_name);

		str_name = "PARA.NEXT.TEST.REQ";
		STD__ADD_STRING_WITH_COMMENT(str_name, "");
		LINK__VAR_STRING_CTRL(sCH_PARA__NEXT_TEST_REQ, str_name);

		str_name = "PARA.END.TEST.REQ";
		STD__ADD_STRING_WITH_COMMENT(str_name, "");
		LINK__VAR_STRING_CTRL(sCH_PARA__END_TEST_REQ, str_name);

		//
		str_name = "DB.UPDATE.REQUEST";
		STD__ADD_STRING_WITH_COMMENT(str_name,"");
		LINK__VAR_STRING_CTRL(sCH__DB_UPDATE_REQUEST, str_name);

		//
		str_name = "PARA.RF.TYPE";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name, "RF1 RF2 RF3", "");
		LINK__VAR_DIGITAL_CTRL(dCH_PARA__RF_TYPE, str_name);

		//
		for(i=0;i<CFG__TEST_LIST;i++)
		{
			// SET POWER
			str_name.Format("PARA.SET.POWER.%1d", i+1);
			STD__ADD_ANALOG_WITH_COMMENT(str_name, "W",0,0,10000,"");
			LINK__VAR_ANALOG_CTRL(aCH_PARA__SET_PWR_LIST[i], str_name);

			// NEW POWER 
			str_name.Format("PARA.NEW.POWER.%1d", i+1);
			STD__ADD_STRING_WITH_COMMENT(str_name, "");
			LINK__VAR_STRING_CTRL(sCH_PARA__NEW_POWER_LIST[i], str_name);

			// NEW METER 
			str_name.Format("PARA.NEW.METER.%1d", i+1);
			STD__ADD_STRING_WITH_COMMENT(str_name, "");
			LINK__VAR_STRING_CTRL(sCH_PARA__NEW_METER_LIST[i], str_name);

			// NEW OFFSET 
			str_name.Format("PARA.NEW.OFFSET.%1d", i+1);
			STD__ADD_STRING_WITH_COMMENT(str_name, "");
			LINK__VAR_STRING_CTRL(sCH_PARA__NEW_OFFSET_LIST[i], str_name);

			// NOW POWER 
			str_name.Format("PARA.NOW.POWER.%1d", i+1);
			STD__ADD_STRING_WITH_COMMENT(str_name, "");
			LINK__VAR_STRING_CTRL(sCH_PARA__NOW_POWER_LIST[i], str_name);

			// NOW METER 
			str_name.Format("PARA.NOW.METER.%1d", i+1);
			STD__ADD_STRING_WITH_COMMENT(str_name, "");
			LINK__VAR_STRING_CTRL(sCH_PARA__NOW_METER_LIST[i], str_name);

			// NOW OFFSET 
			str_name.Format("PARA.NOW.OFFSET.%1d", i+1);
			STD__ADD_STRING_WITH_COMMENT(str_name, "");
			LINK__VAR_STRING_CTRL(sCH_PARA__NOW_OFFSET_LIST[i], str_name);
		}

		// CHECK TIME COUNT
		str_name = "PARA.CHECK.TIME.COUNT";
		STD__ADD_STRING_WITH_COMMENT(str_name, "");
		LINK__VAR_STRING_CTRL(sCH_PARA__CHECK_TIME_COUNT, str_name);

		// RESULT STRING
		str_name = "RESULT.STRING";
		STD__ADD_STRING_WITH_COMMENT(str_name, "");
		LINK__VAR_STRING_CTRL(sCH__RESULT_STRING, str_name);

		// REF STRING
		str_name = "REF.STRING";
		STD__ADD_STRING_WITH_COMMENT(str_name, "");
		LINK__VAR_STRING_CTRL(sCH__REF_STRING, str_name);
	}

	// CONFIG .....
	{
		str_name = "CFG.STABLE.DELAY.SEC";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name,"sec",0,0,10000,"");
		LINK__VAR_ANALOG_CTRL(aCH_CFG__STABLE_DELAY_SEC, str_name);
	}

	// Offset CAL ...
	{
		//
		str_name = "OFFSET_CAL.REQ_FLAG";
		STD__ADD_STRING_WITH_COMMENT(str_name,"");
		LINK__VAR_STRING_CTRL(sCH__OFFSET_CAL_REQ_FLAG, str_name);

		str_name = "OFFSET_CAL.ACTIVE_FLAG";
		STD__ADD_STRING_WITH_COMMENT(str_name,"");
		LINK__VAR_STRING_CTRL(sCH__OFFSET_CAL_ACTIVE_FLAG, str_name);

		//
		str_name = "CFG.AVERAGE.NEW.OFFSET";
		STD__ADD_STRING_WITH_COMMENT(str_name,"");
		LINK__VAR_STRING_CTRL(sCH__CFG_AVERAGE_NEW_OFFSET, str_name);

		str_name = "CFG.AVERAGE.NOW.OFFSET";
		STD__ADD_STRING_WITH_COMMENT(str_name,"");
		LINK__VAR_STRING_CTRL(sCH__CFG_AVERAGE_NOW_OFFSET, str_name);
	}

	// RF_SAVE.X ...
	for(i=0; i<_MAX__RF_SIZE; i++)
	{
		int id = i + 1;

		str_name.Format("RF%1d.SAVE.ACTIVE_FLAG", id);
		STD__ADD_STRING_WITH_X_OPTION(str_name,"");
		LINK__VAR_STRING_CTRL(sCH__SAVE_ACTIVE_FLAG__RF_X[i], str_name);

		str_name.Format("RF%1d.SAVE.REQ_FLAG", id);
		STD__ADD_STRING_WITH_COMMENT(str_name,"");
		LINK__VAR_STRING_CTRL(sCH__SAVE_REQ_FLAG__RF_X[i], str_name);
	}

	// ...
	{
		p_variable->Add__MONITORING_PROC(3.0, MON_ID__STATUS_CTRL);
	}
	return 1;
}
int CObj__RF_CONDUCT::__DEFINE__ALARM(p_alarm)
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
		alarm_title += "RFx CHECK : Utility Program Can't run !";

		alarm_msg = "";

		l_act.RemoveAll();
		l_act.Add("CHECK");

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	// ...
	{
		alarm_id = ALID__RF_TYPE__CAN_NOT_CHANGED;

		alarm_title  = title;
		alarm_title += "Now, RF Type can be changed !";

		alarm_msg = "Please, change RF type after RF Checking sequence is completed. \n";

		l_act.RemoveAll();
		l_act.Add("CHECK");

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);		
	}

	// ...
	{
		alarm_id = ALID__CHAMBER_STATUS__NOT_VAC;

		alarm_title  = title;
		alarm_title += "Now, chamber's pressure status is not VAC. \n";

		alarm_msg  = "To check the RF linearity, the chamber's status must be VAC. \n";
		alarm_msg += "Please, check VAC sensor. \n";

		l_act.RemoveAll();
		l_act.Add("CHECK");

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);		
	}

	return 1;
}

int CObj__RF_CONDUCT::__Define__USER_FUNCTION(CII_DEFINE__FUNCTION *p_fnc_ctrl)
{
	mERROR__USER_FNC.Set__OBJ_NAME(sObject_Name);
	p_fnc_ctrl->Link__ERROR_FEEDBACK(&mERROR__USER_FNC);

	return 1;
}


//-------------------------------------------------------------------------
int CObj__RF_CONDUCT::__INITIALIZE__OBJECT(p_variable,p_ext_obj_create)
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

	// SYSTEM CHANNEL ...
	{
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

	// IO SENSOR ...
	{
		def_name = "CH.VAC_IO_SENSOR";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name,ch_name);

		p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name,obj_name,var_name);
		LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__VAC_IO_SENSOR,obj_name,var_name);
	}

	// OBJ.RF_SIZE ...
	{
		def_name = "OBJ.RF_SIZE";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, def_data);

		iRF_SIZE = atoi(def_data);
		if(iRF_SIZE > _MAX__RF_SIZE)			iRF_SIZE = _MAX__RF_SIZE;

		for(int x=0; x<iRF_SIZE; x++)
		{
			int id = x + 1;

			//
			def_name.Format("OBJ.RF_TITLE.%1d", id);
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name, def_data);

			sTITLE__RF_X[x] = def_data;

			//
			def_name.Format("OBJ.RF_NAME.%1d", id);
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name, obj_name);

			pOBJ_CTRL__RF_X[x] = p_ext_obj_create->Create__OBJECT_CTRL(obj_name);

			// ...
			{
				var_name = "PARA.SET.POWER";
				LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__SET_POWER__RF_X[x], obj_name,var_name);

				var_name = "RF.CONDUCTANCE.INTLK.SKIP";
				LINK__EXT_VAR_STRING_CTRL(sEXT_CH__INTERLOCK_SKIP__RF_X[x], obj_name,var_name);
			}

			//
			for(i=0; i<CFG__TEST_LIST; i++)
			{
				var_name.Format("RF_CAL.CFG.SET_POWER.%1d", i+1);
				LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__CAL_CFG_SET_POWER__RF_X[x][i], obj_name,var_name);

				//
				var_name.Format("RF_CAL.CFG.NEW_POWER.%1d", i+1);
				LINK__EXT_VAR_STRING_CTRL(sEXT_CH__CAL_CFG_NEW_POWER__RF_X[x][i], obj_name,var_name);

				var_name.Format("RF_CAL.CFG.NEW_METER.%1d", i+1);
				LINK__EXT_VAR_STRING_CTRL(sEXT_CH__CAL_CFG_NEW_METER__RF_X[x][i], obj_name,var_name);

				var_name.Format("RF_CAL.CFG.NEW_OFFSET.%1d", i+1);
				LINK__EXT_VAR_STRING_CTRL(sEXT_CH__CAL_CFG_NEW_OFFSET__RF_X[x][i], obj_name,var_name);	

				//
				var_name.Format("RF_CAL.CFG.NOW_POWER.%1d", i+1);
				LINK__EXT_VAR_STRING_CTRL(sEXT_CH__CAL_CFG_NOW_POWER__RF_X[x][i], obj_name,var_name);

				var_name.Format("RF_CAL.CFG.NOW_METER.%1d", i+1);
				LINK__EXT_VAR_STRING_CTRL(sEXT_CH__CAL_CFG_NOW_METER__RF_X[x][i], obj_name,var_name);

				var_name.Format("RF_CAL.CFG.NOW_OFFSET.%1d", i+1);
				LINK__EXT_VAR_STRING_CTRL(sEXT_CH__CAL_CFG_NOW_OFFSET__RF_X[x][i], obj_name,var_name);	
			}		

			// ...
			{
				var_name = "RF_CAL.CFG.NEW.AVG_OFFSET";
				LINK__EXT_VAR_STRING_CTRL(sEXT_CH__CAL_CFG_NEW_AVG_OFFSET__RF_X[x], obj_name,var_name);

				var_name = "RF_CAL.CFG.NOW.AVG_OFFSET";
				LINK__EXT_VAR_STRING_CTRL(sEXT_CH__CAL_CFG_NOW_AVG_OFFSET__RF_X[x], obj_name,var_name);		

				//
				var_name = "RF_CAL.OFFSET.SAVE.DATE";
				LINK__EXT_VAR_STRING_CTRL(sEXT_CH__CAL_OFFSET_SAVE_DATE__RF_X[x], obj_name,var_name);

				var_name = "RF_CAL.TEST.FLAG";
				LINK__EXT_VAR_STRING_CTRL(sEXT_CH__CAL_TEST_FLAG__RF_X[x], obj_name,var_name);

				//
				var_name = "MON.IO.FORWARD.POWER";
				LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__GET_POWER__RF_X[x], obj_name,var_name);
			}
		}
	}

	// ...
	{
		CStringArray l__rf_type;

		for(int x=0; x<iRF_SIZE; x++)
		{
			l__rf_type.Add(	sTITLE__RF_X[x] );
		}

		p_variable->Change__DIGITAL_LIST(dCH_PARA__RF_TYPE->Get__VARIABLE_NAME(), l__rf_type);
	}

	iFLAG__RF_CHECK = -1;

	// ...
	{
		sCH__OFFSET_CAL_ACTIVE_FLAG->Check__DATA(STR__LOCK);

		for(int x=0; x<iRF_SIZE; x++)
		{
			if(sCH__SAVE_ACTIVE_FLAG__RF_X[x]->Check__DATA("") > 0)
			{
				sCH__SAVE_ACTIVE_FLAG__RF_X[x]->Set__DATA(STR__LOCK);
			}
		}
	}

	return 1;
}


//-------------------------------------------------------------------------
int CObj__RF_CONDUCT::__CALL__CONTROL_MODE(mode,p_debug,p_variable,p_alarm)
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
		alm_bff.Format("Please, after %s is finished, run RFx Utility Program.\n",var_data);
		alm_msg += alm_bff;

		p_alarm->Check__ALARM(alarm_id,r_act);
		p_alarm->Post__ALARM_With_MESSAGE(alarm_id,alm_msg);
		return -1;
	}

	// ...
	CString rf_type = dCH_PARA__RF_TYPE->Get__STRING();

	// ...
	{
		CString fnc_name;
		CString fnc_msg;

		fnc_name.Format("%s's %s", sObject_Name,mode);
		fnc_msg.Format("%s : Started ...",mode);

		sEXT_CH__SYS_FNC_NAME->Set__DATA(fnc_name);
		sEXT_CH__SYS_FNC_MSG->Set__DATA(fnc_msg);
		sEXT_CH__SYS_FNC_LOCK->Set__DATA("RF");

		sEXT_CH__SYSTEM_MSG->Set__DATA("RF Check : Started ...");
		sEXT_CH__FNC_MSG->Set__DATA("");
	}

	// ...
	int flag = -1;

	int rf_index = -1;
	int x;

	for(x=0; x<iRF_SIZE; x++)
	{
		CString rf_title = sTITLE__RF_X[x];

		if(rf_type.CompareNoCase(rf_title) != 0)			continue;

		sEXT_CH__CAL_TEST_FLAG__RF_X[x]->Set__DATA(STR__YES);
		sEXT_CH__CAL_TEST_FLAG__RF_X[x]->Set__DATA(STR__YES);

		rf_index = x;
		break;
	}

	IF__CTRL_MODE(sMODE__RF_CHECK)
	{
		iFLAG__RF_CHECK = 1;

		// ...
		{
			sCH_PARA__ACT_ACTIVE_FLAG->Set__DATA("");

			flag = Call__RF_CHECK(p_variable,p_alarm);

			sCH_PARA__ACT_ACTIVE_FLAG->Set__DATA("");
			sCH_PARA__NEXT_TEST_REQ->Set__DATA("");
			sCH_PARA__END_TEST_REQ->Set__DATA("");

			if(rf_index >= 0)
			{
				sEXT_CH__INTERLOCK_SKIP__RF_X[rf_index]->Set__DATA("");
			}
		}

		iFLAG__RF_CHECK = -1;
	}

	if(rf_index >= 0)
	{
		sEXT_CH__CAL_TEST_FLAG__RF_X[rf_index]->Set__DATA("");
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

int CObj__RF_CONDUCT::__CALL__MONITORING(id,p_variable,p_alarm)
{
	if(id == MON_ID__STATUS_CTRL)		Mon__STATUS_CTRL(p_variable, p_alarm);

	return 1;
}
