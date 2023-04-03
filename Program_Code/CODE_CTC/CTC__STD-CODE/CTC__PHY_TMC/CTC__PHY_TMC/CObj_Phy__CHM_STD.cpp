#include "StdAfx.h"
#include "CObj_Phy__CHM_STD.h"


//-------------------------------------------------------------------------
CObj_Phy__CHM_STD::CObj_Phy__CHM_STD()
{

}
CObj_Phy__CHM_STD::~CObj_Phy__CHM_STD()
{

}

//-------------------------------------------------------------------------
int CObj_Phy__CHM_STD::__DEFINE__CONTROL_MODE(obj,l_mode)
{
	sObject_Name = obj;

	// ...
	{
		ADD__CTRL_VAR(sMODE__INIT,    "INIT");
		ADD__CTRL_VAR(sMODE__MAINT,   "MAINT");

		ADD__CTRL_VAR(sMODE__PUMP,    "PUMP");
		ADD__CTRL_VAR(sMODE__VENT,    "VENT");
		ADD__CTRL_VAR(sMODE__ISOLATE, "ISOLATE");
		ADD__CTRL_VAR(sMODE__PURGE,   "PURGE");

		ADD__CTRL_VAR(sMODE__PMx_SV_OPEN,  "PMx.SV_OPEN");
		ADD__CTRL_VAR(sMODE__PMx_SV_CLOSE, "PMx.SV_CLOSE");
	}
	return 1;
}
int CObj_Phy__CHM_STD::__DEFINE__VERSION_HISTORY(version)
{

	return 1;
}


// ...
#define  MON_ID__ALL_STATE						1

#define  DSP__MODE								\
"INIT  MAINT  PUMP  VENT  ISOLATE  PURGE		\
 PMx.SV_OPEN  PMx.SV_CLOSE"


int CObj_Phy__CHM_STD::__DEFINE__VARIABLE_STD(p_variable)
{
	DECLARE__STD_VARIABLE;

	CString str_name;
	CString dsp_item;


	// PARA ...
	{
		str_name = "PARA.PMx.ID";
		STD__ADD_DIGITAL(str_name, "1 2 3 4 5 6 7 8 9 10");
		LINK__VAR_DIGITAL_CTRL(dCH__PARA_PMx_ID, str_name);
	}

	// TMC_CHM ...
	{
		p_variable->Get__STD_DESCRIPTION("STD_OBJ_CTRL",dsp_item);

		str_name = "TMC_CHM.CTRL";
		STD__ADD_DIGITAL(str_name,dsp_item);
		LINK__VAR_DIGITAL_CTRL(xCH__TMC_CHM_CTRL, str_name);

		str_name = "TMC_CHM.MODE";
		STD__ADD_DIGITAL(str_name, DSP__MODE);
		LINK__VAR_DIGITAL_CTRL(xCH__TMC_CHM_MODE, str_name);

		//
		str_name = "TMC_CHM.PARA.PMx.ID";
		STD__ADD_DIGITAL(str_name, "1 2 3 4 5 6 7 8 9 10");
		LINK__VAR_DIGITAL_CTRL(xCH__TMC_CHM_PARA_PMx_ID, str_name);
	}

	// ...
	{
		p_variable->Get__STD_DESCRIPTION("STD_OBJ_STATUS",dsp_item);

		str_name = "OBJ.STATUS";
		STD__ADD_DIGITAL(str_name,dsp_item);
		LINK__VAR_DIGITAL_CTRL(xCH__OBJ_STATUS,str_name);
	}

	// ...
	{
		p_variable->Get__STD_DESCRIPTION("STD_PRESSURE_STATUS",dsp_item);

		str_name = "PRESSURE.STATUS";
		STD__ADD_DIGITAL(str_name,dsp_item);
		LINK__VAR_DIGITAL_CTRL(xCH__PRESSURE_STATUS,str_name);

		//
		str_name = "PRESSURE.VALUE";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(xCH__PRESSURE_VALUE,str_name);

		str_name = "PRESSURE.mTORR";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(xCH__PRESSURE_mTORR,str_name);

		//
		str_name = "VAC.SNS";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(xCH__VAC_SNS,str_name);
	}

	// SIM CFG ...
	{
		str_name = "SCH_TEST.CFG.INIT.SEC";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "sec", 1, 0.0, 100, "");
		LINK__VAR_ANALOG_CTRL(aCH__SCH_TEST_CFG_INIT_SEC, str_name);

		//
		str_name = "SCH_TEST.CFG.PUMP.SEC";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "sec", 1, 0.0, 100, "");
		LINK__VAR_ANALOG_CTRL(aCH__SCH_TEST_CFG_PUMP_SEC, str_name);

		str_name = "SCH_TEST.CFG.VENT.SEC";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "sec", 1, 0.0, 100, "");
		LINK__VAR_ANALOG_CTRL(aCH__SCH_TEST_CFG_VENT_SEC, str_name);
		
		str_name = "SCH_TEST.CFG.ISOLATE.SEC";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "sec", 1, 0.0, 100, "");
		LINK__VAR_ANALOG_CTRL(aCH__SCH_TEST_CFG_ISOLATE_SEC, str_name);
		
		str_name = "SCH_TEST.CFG.PURGE.SEC";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "sec", 1, 0.0, 100, "");
		LINK__VAR_ANALOG_CTRL(aCH__SCH_TEST_CFG_PURGE_SEC, str_name);
	}

	// ...
	{
		p_variable->Add__MONITORING_PROC(3.0,  MON_ID__ALL_STATE);
	}
	return 1;
}

int CObj_Phy__CHM_STD::__DEFINE__ALARM(p_alarm)
{
	DECLARE__ALARM;

	// ...
	CString title;
	title.Format("%s - ",sObject_Name);

	CString alarm_title;
	CString alarm_msg;
	CStringArray l_act;

	// ...
	ALARM_DEFINE__MODULE_OBJECT;

	// ...
	{
		alarm_title  = title;
		alarm_title += "OBJECT MODE : UNKNOWN";

		alarm_msg = "";

		l_act.RemoveAll();
		l_act.Add("ABORT");

		ADD__ALARM_EX(ALID__OBJECT_MODE_UNKNOWN,alarm_title,alarm_msg,l_act);
	}

	// ...
	{
		alarm_title  = title;
		alarm_title += "TMC OFFLINE";

		alarm_msg.Format("Object Name : %s\n",sObject_Name);
		alarm_msg += "TMC OFFLINE";

		l_act.RemoveAll();
		l_act.Add("CHECK");

		ADD__ALARM_EX(ALID__TMC_OFFLINE,alarm_title,alarm_msg,l_act);
	}

	// ...
	{
		alarm_title  = title;
		alarm_title += "VENT ERROR";

		alarm_msg = "";

		l_act.RemoveAll();
		l_act.Add("ABORT");
		l_act.Add("RETRY");

		ADD__ALARM_EX(ALID__VENT_ERROR,alarm_title,alarm_msg,l_act);
	}

	// ...
	{
		alarm_title  = title;
		alarm_title += "PUMP ERROR";

		alarm_msg = "";

		l_act.RemoveAll();
		l_act.Add("ABORT");
		l_act.Add("RETRY");

		ADD__ALARM_EX(ALID__PUMP_ERROR,alarm_title,alarm_msg,l_act);
	}
	return 1;
}

//-------------------------------------------------------------------------
int CObj_Phy__CHM_STD::__INITIALIZE__OBJECT(p_variable,p_ext_obj_create)
{
	p_ext_obj_create->Link__DEF_VARIABLE__ERROR_FEEDBACK(&mERROR__DEF_VAR);

	
	//----------------------------------------------------------------------------
	// EXTERNAL PROPERTY

	CString cfg_db_name;
	CString str_name;

	// ...
	{
		CString file_name;
		CString log_msg;

		file_name.Format("%s.log", sObject_Name);

		log_msg  = "\n\n";
		log_msg += "//------------------------------------------------------------------------";

		xI_LOG_CTRL->CREATE__SUB_DIRECTORY(sObject_Name);
		xI_LOG_CTRL->SET__PROPERTY(file_name,24*7,60);

		xI_LOG_CTRL->DISABLE__TIME_LOG();
		xI_LOG_CTRL->WRITE__LOG(log_msg);

		xI_LOG_CTRL->ENABLE__TIME_LOG();
		xI_LOG_CTRL->WRITE__LOG("   START   \n");
	}

	// ...
	{
		p_ext_obj_create->Get__DEF_CONST_DATA("DB_CFG_NAME",cfg_db_name);

		//
		str_name = "SCH_TEST.CFG.TMC_DUMMY_BY_CTC";
		LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__SCH_TEST_CFG_TMC_DUMMY_BY_CTC, cfg_db_name,str_name);

		//
		str_name = "REF.ATM.PRESSURE";
		LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH_CFG__REF_ATM_PRESSURE, cfg_db_name,str_name);

		str_name = "REF.VAC.PRESSURE";
		LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH_CFG__REF_VAC_PRESSURE, cfg_db_name,str_name);

		str_name = "TRANSFER.MODE";
		LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH_CFG__TRANSFER_MODE, cfg_db_name,str_name);
	}

	// ...
	{
		CString obj_name;

		obj_name = "__EQP";
		str_name = "##SEQ1.CONNECT.STATUS";

		LINK__EXT_VAR_DIGITAL_CTRL(xEXT_CH__TMC_CONNECT_STATUS, obj_name,str_name);
	}

	// ...
	{
		CString def_data;

		iSEQ_ID = 1;
		if(p_ext_obj_create->Get__DEF_CONST_DATA_EX("SEQ_ID",def_data,-1) > 0)
		{
			iSEQ_ID = atoi(def_data);
		}
	}

	// ...
	{
		xI_Module_Obj->Link__ERROR_FEEDBACK(&mERROR__MODULE_OBJ);

		//
		xI_Module_Obj->Link__Object_Name(sObject_Name);

		xI_Module_Obj->Register__Module_Status_Channel(xCH__OBJ_STATUS->Get__VARIABLE_NAME());
		xI_Module_Obj->Register__Module_Mode_Channel(xCH__TMC_CHM_MODE->Get__VARIABLE_NAME());
		xI_Module_Obj->Register__Module_Ctrl_Channel(xCH__TMC_CHM_CTRL->Get__VARIABLE_NAME());

		xI_Module_Obj->Disable__CTCINUSE_TO_STANDBY();

		// ...
		{
			CString data_const;
			p_ext_obj_create->Get__DEF_CONST_DATA_EX("FLAG.REPORT_ABORTED_ALARM",data_const,-1);

			if(data_const.CompareNoCase("DISABLE") == 0)
			{
				xI_Module_Obj->Disable__REPORT_ABORTED_ALARM();
			}
		}
	}

	// ...
	{
		SCX__SEQ_INFO x_seq_info;
		
		iActive__SIM_MODE = x_seq_info->Is__SIMULATION_MODE();
	}

	iPRC_STS = -1;
	return 1;
}

//-------------------------------------------------------------------------
int CObj_Phy__CHM_STD::__CALL__CONTROL_MODE(mode,p_debug,p_variable,p_alarm)
{
	xI_Sync_Ctrl.Thread__LOCK();
	iPRC_STS = 1;

	xI_Module_Obj->Enable__ERROR_CHECK__NOT_STANDBY();

	// ...
	int flag = -1;

	// ...
	{
			 IF__CTRL_MODE(sMODE__INIT)					flag = Call__INIT(p_variable,p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__MAINT)				flag = Call__MAINT(p_variable,p_alarm);

		ELSE_IF__CTRL_MODE(sMODE__PUMP)					flag = Call__PUMP(p_variable,p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__VENT)					flag = Call__VENT(p_variable,p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__ISOLATE)				flag = Call__ISOLATE(p_variable);
		ELSE_IF__CTRL_MODE(sMODE__PURGE)				flag = Call__PURGE(p_variable);

		ELSE_IF__CTRL_MODE(sMODE__PMx_SV_OPEN)			flag = Call__PMx_SV_OPEN(p_variable);
		ELSE_IF__CTRL_MODE(sMODE__PMx_SV_CLOSE)			flag = Call__PMx_SV_CLOSE(p_variable);

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

	iPRC_STS = -1;
	xI_Sync_Ctrl.Thread__UNLOCK();

	return flag;
}

int CObj_Phy__CHM_STD::__CALL__MONITORING(id,p_variable,p_alarm)
{
	switch(id)
	{
		case MON_ID__ALL_STATE:
			Mon__All_State(p_variable, p_alarm);
			break;
	}

	return 1;
}
