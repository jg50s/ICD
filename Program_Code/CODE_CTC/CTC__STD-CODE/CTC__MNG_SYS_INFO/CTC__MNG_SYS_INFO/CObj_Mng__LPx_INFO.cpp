#include "StdAfx.h"
#include "CObj_Mng__LPx_INFO.h"


//-------------------------------------------------------------------------
CObj_Mng__LPx_INFO::CObj_Mng__LPx_INFO()
{

}
CObj_Mng__LPx_INFO::~CObj_Mng__LPx_INFO()
{

}

//-------------------------------------------------------------------------
int CObj_Mng__LPx_INFO::__DEFINE__CONTROL_MODE(obj,l_mode)
{
	sObject_Name = obj;

	/*
	//.....
	CString str_name;

	str_name = "PRO_START";
	ADD__MODE_VAR(sMODE__PRO_START,str_name);
	//
	*/
	return 1;
}
int CObj_Mng__LPx_INFO::__DEFINE__VERSION_HISTORY(version)
{

	return 1;
}


// ...
#define MON_ID__INFO_CTRL							1


int CObj_Mng__LPx_INFO::__DEFINE__VARIABLE_STD(p_variable)
{
	DECLARE__STD_VARIABLE;

	CString str_name;
	int i;

	// LPx CTRL -----
	{
		str_name = "LPx_CTRL.SEL_ID";
		STD__ADD_STRING_WITH_COMMENT(str_name,"");
		LINK__VAR_STRING_CTRL(sCH__LPx_CTRL__SEL_ID,str_name);

		for(i=0;i<CFG__LPx_SIZE;i++)
		{
			str_name.Format("LPx_CTRL.LOCK_FLAG.%1d", i+1);
			STD__ADD_STRING_WITH_COMMENT(str_name,"");
			LINK__VAR_STRING_CTRL(sCH__LPx_CTRL__LOCK_FLAG[i],str_name);
		}
	}

	// LPx INFO -----
	{
		str_name = "LPx_INFO.CTRL_MSG";
		STD__ADD_STRING_WITH_COMMENT(str_name,"");
		LINK__VAR_STRING_CTRL(sCH__LPx_INFO__CTRL_MSG,str_name);

		str_name = "LPx_INFO.JOBID";
		STD__ADD_STRING_WITH_COMMENT(str_name,"");
		LINK__VAR_STRING_CTRL(sCH__LPx_INFO__JOBID,str_name);

		str_name = "LPx_INFO.PORT_STATUS";
		STD__ADD_STRING_WITH_COMMENT(str_name,"");
		LINK__VAR_STRING_CTRL(sCH__LPx_INFO__PORT_STATUS,str_name);

		str_name = "LPx_INFO.MANUAL_START.STATUS";
		STD__ADD_STRING_WITH_COMMENT(str_name,"");
		LINK__VAR_STRING_CTRL(sCH__LPx_INFO__MANUAL_START_STATUS,str_name);
	
		str_name = "LPx_INFO.CYCLE_START.STATUS";
		STD__ADD_STRING_WITH_COMMENT(str_name,"");
		LINK__VAR_STRING_CTRL(sCH__LPx_INFO__CYCLE_START_STATUS,str_name);

		str_name = "LPx_INFO.LOTID";
		STD__ADD_STRING_WITH_COMMENT(str_name,"");
		LINK__VAR_STRING_CTRL(sCH__LPx_INFO__LOTID,str_name);

		str_name = "LPx_INFO.CSTID";
		STD__ADD_STRING_WITH_COMMENT(str_name,"");
		LINK__VAR_STRING_CTRL(sCH__LPx_INFO__CSTID,str_name);

		str_name = "LPx_INFO.PPID";
		STD__ADD_STRING_WITH_COMMENT(str_name,"");
		LINK__VAR_STRING_CTRL(sCH__LPx_INFO__PPID,str_name);

		str_name = "LPx_INFO.TRANSFER_IO";
		STD__ADD_STRING_WITH_COMMENT(str_name,"");
		LINK__VAR_STRING_CTRL(sCH__LPx_INFO__TRANSFER_PIO,str_name);

		str_name = "LPx_INFO.PIO_COMM_READY_STS";
		STD__ADD_STRING_WITH_COMMENT(str_name,"");
		LINK__VAR_STRING_CTRL(sCH__LPx_INFO__PIO_COMM_READY_STS,str_name);

		str_name = "LPx_INFO.CST_STATUS";
		STD__ADD_STRING_WITH_COMMENT(str_name,"");
		LINK__VAR_STRING_CTRL(sCH__LPx_INFO__CST_STATUS,str_name);

		for(i=0;i<CFG__SLOT_SIZE;i++)
		{
			str_name.Format("LPx_INFO.SLOT%002d.STATUS",i+1);
			STD__ADD_STRING_WITH_COMMENT(str_name,"");
			LINK__VAR_STRING_CTRL(sCH__LPx_INFO__SLOTx_STATUS[i],str_name);
		}

		//
		str_name = "LPx_INFO.DB.LotID";
		STD__ADD_STRING_WITH_COMMENT(str_name,"");
		LINK__VAR_STRING_CTRL(sCH__LPx_INFO__DB_LotID,str_name);
		
		str_name = "LPx_INFO.DB.RouteID";
		STD__ADD_STRING_WITH_COMMENT(str_name,"");
		LINK__VAR_STRING_CTRL(sCH__LPx_INFO__DB_RouteID,str_name);
		
		str_name = "LPx_INFO.DB.StartSlot";
		STD__ADD_ANALOG_WITH_COMMENT(str_name,"slot",0,1,25,"");
		LINK__VAR_ANALOG_CTRL(aCH__LPx_INFO__DB_StartSlot,str_name);
		
		str_name = "LPx_INFO.DB.EndSlot";
		STD__ADD_ANALOG_WITH_COMMENT(str_name,"slot",0,1,25,"");
		LINK__VAR_ANALOG_CTRL(aCH__LPx_INFO__DB_EndSlot,str_name);
		
		str_name = "LPx_INFO.DB.CycleCount";
		STD__ADD_ANALOG_WITH_COMMENT(str_name,"num",0,1,99999,"");
		LINK__VAR_ANALOG_CTRL(aCH__LPx_INFO__DB_CycleCount,str_name);
	}

	// LPx DB -----
	{
		for(i=0;i<CFG__LPx_SIZE;i++)
		{
			str_name.Format("LPx_DB.LotID.%1d",i+1);
			STD__ADD_STRING_WITH_COMMENT(str_name,"");
			LINK__VAR_STRING_CTRL(sCH__LPx_DB__LotID[i],str_name);

			str_name.Format("LPx_DB.RouteID.%1d",i+1);
			STD__ADD_STRING_WITH_COMMENT(str_name,"");
			LINK__VAR_STRING_CTRL(sCH__LPx_DB__RouteID[i],str_name);

			str_name.Format("LPx_DB.StartSlot.%1d",i+1);
			STD__ADD_STRING_WITH_COMMENT(str_name,"");
			LINK__VAR_STRING_CTRL(sCH__LPx_DB__StartSlot[i],str_name);

			str_name.Format("LPx_DB.EndSlot.%1d",i+1);
			STD__ADD_STRING_WITH_COMMENT(str_name,"");
			LINK__VAR_STRING_CTRL(sCH__LPx_DB__EndSlot[i],str_name);

			str_name.Format("LPx_DB.CycleCount.%1d",i+1);
			STD__ADD_STRING_WITH_COMMENT(str_name,"");
			LINK__VAR_STRING_CTRL(sCH__LPx_DB__CycleCount[i],str_name);
		}
	}

	// OBJ INFO -----
	{
		str_name = "LPx_INFO.OBJ_CTRL";
		STD__ADD_STRING_WITH_COMMENT(str_name,"");
		LINK__VAR_STRING_CTRL(sCH__LPx_INFO__OBJ_CTRL,str_name);

		str_name = "LPx_INFO.OBJ_MODE";
		STD__ADD_STRING_WITH_COMMENT(str_name,"");
		LINK__VAR_STRING_CTRL(sCH__LPx_INFO__OBJ_MODE,str_name);

		str_name = "LPx_INFO.OBJ_STATUS";
		STD__ADD_STRING_WITH_COMMENT(str_name,"");
		LINK__VAR_STRING_CTRL(sCH__LPx_INFO__OBJ_STATUS,str_name);
	}

	// OBJ CTRL -----
	{
		str_name = "OBJ_CTRL.PORT_EXCEPTION";
		STD__ADD_STRING_WITH_COMMENT(str_name,"");
		LINK__VAR_STRING_CTRL(sCH__OBJ_CTRL__PORT_EXCEPTION,str_name);

		str_name = "OBJ_CTRL.JOB_SELECT.REQ";
		STD__ADD_STRING_WITH_COMMENT(str_name,"");
		LINK__VAR_STRING_CTRL(sCH__OBJ_CTRL__JOB_SELECT_REQ,str_name);

		str_name = "OBJ_CTRL.MANUAL_START.REQ";
		STD__ADD_STRING_WITH_COMMENT(str_name,"");
		LINK__VAR_STRING_CTRL(sCH__OBJ_CTRL__MANUAL_START_REQ,str_name);

		str_name = "OBJ_CTRL.CYCLE_START.REQ";
		STD__ADD_STRING_WITH_COMMENT(str_name,"");
		LINK__VAR_STRING_CTRL(sCH__OBJ_CTRL__CYCLE_START_REQ,str_name);
	}

	// ...
	{
		p_variable->Add__MONITORING_PROC(3.0,MON_ID__INFO_CTRL);
	}
	return 1;
}

int CObj_Mng__LPx_INFO::__DEFINE__ALARM(p_alarm)
{
	DECLARE__ALARM;

	// ...
	CString title;
	title.Format("%s - ",sObject_Name);

	CString alarm_title;
	CString alarm_msg;
	CStringArray l_act;

	// ...
	{
		alarm_title  = title;
		alarm_title += "OBJECT MODE : UNKNOWN";

		alarm_msg = "";

		l_act.RemoveAll();
		l_act.Add("ABORT");
	
		ADD__ALARM_EX(ALID__OBJECT_MODE_UNKNOWN,alarm_title,alarm_msg,l_act);
	}
	return 1;
}

int CObj_Mng__LPx_INFO::__Define__USER_FUNCTION(CII_DEFINE__FUNCTION *p_fnc_ctrl)
{
	mERROR__USER_FNC.Set__OBJ_NAME(sObject_Name);
	p_fnc_ctrl->Link__ERROR_FEEDBACK(&mERROR__USER_FNC);

	return 1;
}

//-------------------------------------------------------------------------
int CObj_Mng__LPx_INFO::__INITIALIZE__OBJECT(p_variable,p_ext_obj_create)
{
	CString def_name;
	CString def_data;
	CString var_name;
	int i;

	// LP SIZE -----
	{
		def_name = "LP_SIZE";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name,def_data);

		iLPx_SIZE = atoi(def_data);
		if(iLPx_SIZE > CFG__LPx_SIZE)		iLPx_SIZE = CFG__LPx_SIZE;
	}

	// LPx INFO -----
	{
		CString ch_name;
		CString obj_name;
		CString var_name;

		for(i=0;i<iLPx_SIZE;i++)
		{
			//
			def_name.Format("LP%1d__CH_WIN",i+1);
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name,ch_name);

			p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name,obj_name,var_name);
			LINK__EXT_VAR_STRING_CTRL(xEXT_CH__LPx_CH_WIN[i], obj_name,var_name);

			//
			def_name.Format("LP%1d__WIN_NAME",i+1);
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name,def_data);

			sDATA__WIN_NAME[i] = def_data;
		}

		for(i=0;i<iLPx_SIZE;i++)
		{
			def_name.Format("OBJ__LP%1d",i+1);
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name,def_data);

			pOBJ_CTRL__LPx[i] = p_ext_obj_create->Create__OBJECT_CTRL(def_data);

			//.....
			var_name = "CFG.USE";
			LINK__EXT_VAR_DIGITAL_CTRL(xEXT_CH__LPx_USE_FLAG[i], def_data,var_name);

			var_name = "APP.PORT.EXCEPTION";
			LINK__EXT_VAR_STRING_CTRL(xEXT_CH__LPx_PORT_EXCEPTION[i], def_data,var_name);

			//.....
			sLIST__LPx_VARIABLE[i].RemoveAll();

			// 1. OBJ STATUS
			var_name = "VIRTUAL.OBJ.STATUS";
			sLIST__LPx_VARIABLE[i].Add(var_name);

			// 2. JOBID
			var_name = "APP.JOB.NAME";
			sLIST__LPx_VARIABLE[i].Add(var_name);

			// 3. PORT STATUS
			var_name = "APP.VIRTUAL.PORT.STATUS";
			// var_name = "APP.PORT.STATUS";
			sLIST__LPx_VARIABLE[i].Add(var_name);

			// 4. LOTID
			var_name = "APP.PORT.LOTID";
			sLIST__LPx_VARIABLE[i].Add(var_name);

			// 5. CSTID
			var_name = "CID.STRING";
			sLIST__LPx_VARIABLE[i].Add(var_name);

			// 6. PPID
			var_name = "APP.PORT.PPID";
			sLIST__LPx_VARIABLE[i].Add(var_name);

			// 7. TRANSFER PIO
			var_name = "PIO.TRANSFER";
			sLIST__LPx_VARIABLE[i].Add(var_name);

			// 8. PIO : COMM READY STS
			var_name = "PIO.COMM.READY.STS";
			sLIST__LPx_VARIABLE[i].Add(var_name);

			// 9. CST STATUS
			var_name = "CST.STATUS";
			sLIST__LPx_VARIABLE[i].Add(var_name);
	
			// 10. SLOTx STATUS
			{
				int k;
			
				for(k=0;k<CFG__SLOT_SIZE;k++)
				{
					var_name.Format("SLOT%002d.STATUS",k+1);
					sLIST__LPx_VARIABLE[i].Add(var_name);
				}
			}
		}
	}

	return 1;
}

//-------------------------------------------------------------------------
int CObj_Mng__LPx_INFO::__CALL__CONTROL_MODE(mode,p_debug,p_variable,p_alarm)
{
	int flag = -1;

	/*
	IF__OBJ_MODE(sMODE__PRO_START)		flag = Call__PRO_START(p_variable);

	else
	*/
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

	return flag;
}
int CObj_Mng__LPx_INFO::__CALL__MONITORING(id,p_variable,p_alarm)
{
	switch(id)
	{
		case MON_ID__INFO_CTRL:
			Mon__INFO_CTRL(p_variable,p_alarm);
			break;
	}

	return 1;
}
