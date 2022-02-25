#include "StdAfx.h"
#include "CObj_Phy__VIS_STD.h"


//-------------------------------------------------------------------------
CObj_Phy__VIS_STD::CObj_Phy__VIS_STD()
{

}
CObj_Phy__VIS_STD::~CObj_Phy__VIS_STD()
{

}

//-------------------------------------------------------------------------
int CObj_Phy__VIS_STD::__DEFINE__CONTROL_MODE(obj,l_mode)
{
	sObject_Name = obj;
	iVIS_ID = 1;

	// ...
	{
		ADD__CTRL_VAR(sMODE__PLACE_READY,    "PLACE_READY");
		ADD__CTRL_VAR(sMODE__PLACE_COMPLETE, "PLACE_COMPLETE");

		ADD__CTRL_VAR(sMODE__PICK_READY,    "PICK_READY");
		ADD__CTRL_VAR(sMODE__PICK_COMPLETE, "PICK_COMPLETE");

		ADD__CTRL_VAR(sMODE__PRO_READY, "PRO_READY");
		ADD__CTRL_VAR(sMODE__PRO_START, "PRO_START");

		ADD__CTRL_VAR(sMODE__AUTO_PRO,    "AUTO_PRO");
		ADD__CTRL_VAR(sMODE__AUTO_PRO_EX, "AUTO_PRO_EX");

		ADD__CTRL_VAR(sMODE__EXCHANGE_READY, "EXCHANGE_READY");
	}
	return 1;
}
int CObj_Phy__VIS_STD::__DEFINE__VERSION_HISTORY(version)
{

	return 1;
}


// ...
#define  MON_ID__ALL_STATE							1

// ...
#define  DSP__MODE									\
"PRO_READY											\
PLACE_READY  PLACE_COMPLETE							\
PRO_START											\
PICK_READY  PICK_COMPLETE							\
EXCHANGE_READY										\
INIT"

#define  DSP__DISABLE_ENABLE		"DISABLE  ENABLE"	 
#define  DSP__RECIPE_MODE			"CONFIG  ROUTE"
#define  DSP__NO_YES				"NO  YES"


int CObj_Phy__VIS_STD::__DEFINE__VARIABLE_STD(p_variable)
{
	DECLARE__STD_VARIABLE;

	CString str_name;
	int i;

	// ...
	{
		CString dsp_item;
		p_variable->Get__STD_DESCRIPTION("STD_OBJ_CTRL",dsp_item);

		str_name = "TMC_VIS.CTRL";
		STD__ADD_DIGITAL(str_name,dsp_item);
		LINK__VAR_DIGITAL_CTRL(xCH__OBJ_CTRL,str_name);

		dVAR__MODE = "TMC_VIS.MODE";
		STD__ADD_DIGITAL(dVAR__MODE,DSP__MODE);
	}

	// ...
	{
		CString dsp_item;
		p_variable->Get__STD_DESCRIPTION("STD_OBJ_STATUS",dsp_item);

		str_name = "OBJ.STATUS";
		STD__ADD_DIGITAL(str_name,dsp_item);
		LINK__VAR_DIGITAL_CTRL(xCH__OBJ_STATUS,str_name);

		//
		str_name = "CFG.DUAL_SLOT.USE.FLAG";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name,DSP__DISABLE_ENABLE,"");
		LINK__VAR_DIGITAL_CTRL(xCH__CFG_DUAL_SLOT_USE_FLAG,str_name);

		str_name = "SLOT.NO";
		STD__ADD_DIGITAL(str_name,"1 2");
		LINK__VAR_DIGITAL_CTRL(xCH__SLOT_NO,str_name);
	}

	// ...
	{
		CString dsp_item;
		p_variable->Get__STD_DESCRIPTION("STD_SLOT_STATUS",dsp_item);

		for(i=0; i<CFG_VIS__SLOT_MAX; i++)
		{
			str_name.Format("SLOT%002d.STATUS",i+1);
			STD__ADD_DIGITAL(str_name,dsp_item);
			LINK__VAR_DIGITAL_CTRL(xCH__SLOT_STATUS[i],str_name);

			str_name.Format("SLOT%002d.TITLE",i+1);
			STD__ADD_STRING(str_name);
			LINK__VAR_STRING_CTRL(xCH__SLOT_TITLE[i],str_name);
		}
	}

	// ...
	{
		str_name = "RECIPE";
		STD__ADD_STRING_WITH_COMMENT(str_name,"");
		LINK__VAR_STRING_CTRL(xCH__RECIPE,str_name);

		str_name = "LOTID";
		STD__ADD_STRING_WITH_COMMENT(str_name,"");
		LINK__VAR_STRING_CTRL(xCH__LOTID,str_name);

		str_name = "MATERIALID";
		STD__ADD_STRING_WITH_COMMENT(str_name,"");
		LINK__VAR_STRING_CTRL(xCH__MATERIALID,str_name);

		str_name = "PORTID";
		STD__ADD_STRING_WITH_COMMENT(str_name,"");
		LINK__VAR_STRING_CTRL(xCH__PORTID,str_name);

		str_name = "SLOTID";
		STD__ADD_STRING_WITH_COMMENT(str_name,"");
		LINK__VAR_STRING_CTRL(xCH__SLOTID,str_name);

		str_name = "PM.NAME";
		STD__ADD_STRING_WITH_COMMENT(str_name,"");
		LINK__VAR_STRING_CTRL(xCH__PM_NAME,str_name);

		str_name = "PM.ID";
		STD__ADD_STRING_WITH_COMMENT(str_name,"");
		LINK__VAR_STRING_CTRL(xCH__PM_ID,str_name);

		str_name = "JUDGMENT";
		STD__ADD_STRING_WITH_COMMENT(str_name,"");
		LINK__VAR_STRING_CTRL(xCH__JUDGMENT,str_name);

		str_name = "PICK.READY.FLAG";
		STD__ADD_STRING_WITH_COMMENT(str_name,"");
		LINK__VAR_STRING_CTRL(xCH__PICK_READY_FLAG,str_name);
	}

	// ...
	{
		str_name = "CFG.USE";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name,DSP__DISABLE_ENABLE,"");
		LINK__VAR_DIGITAL_CTRL(xCH_CFG__USE,str_name);

		str_name = "CFG.ALARM.BLOCKING_FLAG";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name,DSP__DISABLE_ENABLE,"");
		LINK__VAR_DIGITAL_CTRL(xCH_CFG__ALARM_BLOCKING_FLAG,str_name);

		str_name = "CFG.RECIPE_MODE";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name,DSP__RECIPE_MODE,"");
		LINK__VAR_DIGITAL_CTRL(xCH_CFG__RECIPE_MODE,str_name);

		str_name = "CFG.VISIT_MODE";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name,DSP__RECIPE_MODE,"");
		LINK__VAR_DIGITAL_CTRL(xCH_CFG__VISIT_MODE,str_name);

		str_name = "CFG.RECIPE";
		STD__ADD_STRING_WITH_X_OPTION(str_name,"");
		LINK__VAR_STRING_CTRL(xCH_CFG__CONFIG_RECIPE,str_name);

		str_name = "CFG.RECIPE_UPLOAD.REQ";
		STD__ADD_STRING_WITH_COMMENT(str_name,"");
		LINK__VAR_STRING_CTRL(xCH_CFG__RECIPE_UPLOAD_REQ,str_name);

		str_name = "CFG.RECIPE_LIST";
		STD__ADD_STRING_WITH_COMMENT(str_name,"");
		LINK__VAR_STRING_CTRL(xCH_CFG__RECIPE_LIST,str_name);

		//
		for(i=0;i<CFG_LP__SLOT_MAX;i++)
		{
			str_name.Format("CFG.VISIT.SLOT%002d",i+1);
			STD__ADD_DIGITAL_WITH_X_OPTION(str_name,DSP__NO_YES,"");
			LINK__VAR_DIGITAL_CTRL(xCH_CFG__SLOT_VISIT_LIST[i],str_name);
		}
	}

	// ...
	{
		p_variable->Add__MONITORING_PROC(1.0, MON_ID__ALL_STATE);
	}
	return 1;
}

int CObj_Phy__VIS_STD::__DEFINE__ALARM(p_alarm)
{
	DECLARE__ALARM;

	// ...
	CString title;
	title.Format("%s : ",sObject_Name);

	CString alarm_title;
	CString alarm_msg;
	CStringArray l_act;
	CString bff;

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
		alarm_title += "Material Judgment Error !";

		alarm_msg = "";

		l_act.RemoveAll();
		l_act.Add(STR__ALL_ABORT);
		l_act.Add(STR__PMx_ABORT);
		l_act.Add(STR__IGNORE);

		ADD__ALARM_EX(ALID__MATERIAL_JUDGEMENT,alarm_title,alarm_msg,l_act);
	}

	// ...
	{
		alarm_title  = title;
		alarm_title += "Material Judgment Error !";

		alarm_msg = "";

		l_act.RemoveAll();
		l_act.Add(STR__CHECK);

		ADD__ALARM_EX(ALID__MATERIAL_JUDGEMENT_NON_BLOCKING,alarm_title,alarm_msg,l_act);
	}
	return 1;
}

//-------------------------------------------------------------------------
int CObj_Phy__VIS_STD::__INITIALIZE__OBJECT(p_variable,p_ext_obj_create)
{
	CString def_name;
	CString def_data;

	// ...
	{
		sSCH_NAME = "";

		def_name = "OBJ__SCH_NAME";
		if(p_ext_obj_create->Get__DEF_CONST_DATA_EX(def_name,def_data,-1) > 0)
		{
			sSCH_NAME = def_data;
		}
	}

	// ...
	{
		xI_Module_Obj->Link__ERROR_FEEDBACK(&mERROR__MODULE_OBJ);

		//
		xI_Module_Obj->Link__Object_Name(sObject_Name);

		xI_Module_Obj->Register__Module_Status_Channel(xCH__OBJ_STATUS->Get__VARIABLE_NAME());
		xI_Module_Obj->Register__Module_Mode_Channel(dVAR__MODE);
		xI_Module_Obj->Register__Module_Ctrl_Channel(xCH__OBJ_CTRL->Get__VARIABLE_NAME());

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

	iPRC_STS = -1;

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
	return 1;
}

int CObj_Phy__VIS_STD::__START__OBJECT()
{
	xI_SCH_MATERIAL_CTRL->Link__SERVICE_DB("");
	return 1;
}

//-------------------------------------------------------------------------
int CObj_Phy__VIS_STD::__CALL__CONTROL_MODE(mode,p_debug,p_variable,p_alarm)
{
	xI_Sync_Ctrl.Thread__LOCK();
	iPRC_STS = 1;

	// ...
	DECLARE__EXT_CTRL(p_variable);

	CString upper_obj_name = p_ext_mode_ctrl->Get__UPPER_OBJECT_NAME();

	xI_Module_Obj->Enable__ERROR_CHECK__NOT_STANDBY();
	xCH__PICK_READY_FLAG->Set__DATA("");

	// ...
	{
		CString str_slot_no;
		xCH__SLOT_NO->Get__DATA(str_slot_no);

		CString log_string;
		log_string.Format("START : [%s][%s]...  Called By \"%s\".",	mode,str_slot_no, upper_obj_name);

		xI_LOG_CTRL->WRITE__LOG(log_string);
	}

	int flag = -1;

	// ...
	{
		     IF__CTRL_MODE(sMODE__PLACE_READY)			flag = Call__PLACE_READY(p_variable);
		ELSE_IF__CTRL_MODE(sMODE__PLACE_COMPLETE)		flag = Call__PLACE_COMPLETE(p_variable);

		ELSE_IF__CTRL_MODE(sMODE__PICK_READY)			flag = Call__PICK_READY(p_variable);
		ELSE_IF__CTRL_MODE(sMODE__PICK_COMPLETE)		flag = Call__PICK_COMPLETE(p_variable);

		ELSE_IF__CTRL_MODE(sMODE__PRO_READY)			flag = Call__PRO_READY(p_variable);
		ELSE_IF__CTRL_MODE(sMODE__PRO_START)			flag = Call__PRO_START(p_variable,p_alarm);

		ELSE_IF__CTRL_MODE(sMODE__AUTO_PRO)				flag = Call__AUTO_PRO(p_variable,p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__AUTO_PRO_EX)			flag = Call__AUTO_PRO_EX(p_variable,p_alarm);

		ELSE_IF__CTRL_MODE(sMODE__EXCHANGE_READY)		flag = Call__EXCHANGE_READY(p_variable,p_alarm);

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

	if(flag < 0)
	{
		xCH__PICK_READY_FLAG->Set__DATA("");
	}

	// ...
	{
		CString log_string;

		if(flag > 0)		log_string.Format("COMPLETE : [%s]",mode);
		else				log_string.Format("ABORTED  : [%s]",mode);

		xI_LOG_CTRL->WRITE__LOG(log_string);
	}

	iPRC_STS = -1;
	xI_Sync_Ctrl.Thread__UNLOCK();

	return flag;
}

int CObj_Phy__VIS_STD::__CALL__MONITORING(id,p_variable,p_alarm)
{
	switch(id)
	{
		case MON_ID__ALL_STATE:
			Mon__All_State(p_variable,p_alarm);
			break;
	}

	return 1;
}
