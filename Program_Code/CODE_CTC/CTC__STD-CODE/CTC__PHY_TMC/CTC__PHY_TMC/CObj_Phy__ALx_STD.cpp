#include "StdAfx.h"
#include "CObj_Phy__ALx_STD.h"


//-------------------------------------------------------------------------
CObj_Phy__ALx_STD::CObj_Phy__ALx_STD()
{

}
CObj_Phy__ALx_STD::~CObj_Phy__ALx_STD()
{

}


//-------------------------------------------------------------------------
int CObj_Phy__ALx_STD::__DEFINE__CONTROL_MODE(obj,l_mode)
{
	sObject_Name = obj;

	// ...
	{
		ADD__CTRL_VAR(sMODE__INIT,  "INIT");
		ADD__CTRL_VAR(sMODE__ALIGN, "ALIGN");

		ADD__CTRL_VAR(sMODE__PICK_READY,     "PICK_READY");
		ADD__CTRL_VAR(sMODE__PICK_COMPLETE,  "PICK_COMPLETE");
		ADD__CTRL_VAR(sMODE__PLACE_READY,    "PLACE_READY");
		ADD__CTRL_VAR(sMODE__PLACE_COMPLETE, "PLACE_COMPLETE");
	}
	return 1;
}
int CObj_Phy__ALx_STD::__DEFINE__VERSION_HISTORY(version)
{

	return 1;
}


// ...
#define  MON_ID__MODULE_STATUS					1

// ...
#define  APP_DSP__MODE							\
"ALIGN        INIT								\
PICK_READY   PICK_COMPLETE						\
PLACE_READY  PLACE_COMPLETE"	

#define  APP_DSP__DISABLE_ENABLE				\
"DISABLE  ENABLE"

#define  APP_DSP__APPLY_MODE					\
"CONFIG  ROUTE"


int CObj_Phy__ALx_STD::__DEFINE__VARIABLE_STD(p_variable)
{
	DECLARE__STD_VARIABLE;

	CString str_name;
	CString dsp_item;

	// CONTROL ...
	{
		p_variable->Get__STD_DESCRIPTION("STD_OBJ_CTRL",dsp_item);

		str_name = "ALIGNER.CTRL";
		STD__ADD_DIGITAL(str_name,dsp_item);
		LINK__VAR_DIGITAL_CTRL(xCH__OBJ_CTRL,str_name);
	
		dVAR__MODE = "ALIGNER.MODE";
		STD__ADD_DIGITAL(dVAR__MODE,APP_DSP__MODE);
	}

	// STATUS ...
	{
		p_variable->Get__STD_DESCRIPTION("STD_OBJ_STATUS",dsp_item);

		str_name = "OBJ.STATUS";
		STD__ADD_DIGITAL(str_name,dsp_item);
		LINK__VAR_DIGITAL_CTRL(xCH__OBJ_STATUS,str_name);
	}

	// PARAMETER ...
	{
		str_name = "PARA.SLOT";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(xCH__PARA_SLOT,str_name);

		str_name = "PARA.MATERIAL_TYPE";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(xCH__PARA_MATERIAL_TYPE,str_name);

		str_name = "PARA.MODULE_TYPE";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(xCH__PARA_MODULE_TYPE,str_name);
	}

	// ...
	{
		p_variable->Get__STD_DESCRIPTION("STD_SLOT_STATUS",dsp_item);

		for(int i=0; i<CFG_AL__SLOT_MAX; i++)
		{
			str_name.Format("SLOT%002d.STATUS",i+1);
			STD__ADD_DIGITAL(str_name,dsp_item);
			LINK__VAR_DIGITAL_CTRL(xCH__SLOT_STATUS[i],str_name);

			str_name.Format("SLOT%002d.TITLE",i+1);
			STD__ADD_STRING(str_name);
			LINK__VAR_STRING_CTRL(xCH__SLOT_TITLE[i],str_name);

			sVAR__SLOT_MATERIAL_SIZE[i].Format("SLOT%002d.MATERIAL_SIZE",i+1);
			STD__ADD_STRING_WITH_X_OPTION(sVAR__SLOT_MATERIAL_SIZE[i],"");
		}	
	
		str_name = "ALIGN_RETRY.FLAG";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(xCH__ALIGN_RETRY_FLAG,str_name);
	}

	// CONFIG PAGE ...
	{
		p_variable->Get__STD_DESCRIPTION(DSP__ENABLE_DISABLE,dsp_item);

		str_name = "CFG.USE.FLAG";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name,dsp_item,"");
		LINK__VAR_DIGITAL_CTRL(xCH__CFG_USE_FLAG,str_name);

		str_name = "CFG.APPLY.MODE";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name,APP_DSP__APPLY_MODE,"");
		LINK__VAR_DIGITAL_CTRL(xCH__CFG_APPLY_MODE,str_name);

		//
		str_name = "CFG.PROTOCOL.PICK_READY";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name,APP_DSP__DISABLE_ENABLE,"");
		LINK__VAR_DIGITAL_CTRL(xCH__CFG_PROTOCOL__PICK_READY,str_name);
	
		str_name = "CFG.PROTOCOL.PICK_COMPLETE";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name,APP_DSP__DISABLE_ENABLE,"");
		LINK__VAR_DIGITAL_CTRL(xCH__CFG_PROTOCOL__PICK_COMPLETE,str_name);

		//
		str_name = "CFG.PROTOCOL.PLACE_READY";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name,APP_DSP__DISABLE_ENABLE,"");
		LINK__VAR_DIGITAL_CTRL(xCH__CFG_PROTOCOL__PLACE_READY,str_name);

		str_name = "CFG.PROTOCOL.PLACE_COMPLETE";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name,APP_DSP__DISABLE_ENABLE,"");
		LINK__VAR_DIGITAL_CTRL(xCH__CFG_PROTOCOL__PLACE_COMPLETE,str_name);
	}
	
	// SIM CFG ...
	{
		str_name = "SCH_TEST.CFG.INIT.SEC";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "sec", 1, 0.0, 100, "");
		LINK__VAR_ANALOG_CTRL(aCH__SCH_TEST_CFG_INIT_SEC, str_name);

		str_name = "SCH_TEST.CFG.ALIGN.SEC";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "sec", 1, 0.0, 100, "");
		LINK__VAR_ANALOG_CTRL(aCH__SCH_TEST_CFG_ALIGN_SEC, str_name);
	
		str_name = "SCH_TEST.CFG.PICK_READY.SEC";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "sec", 1, 0.0, 100, "");
		LINK__VAR_ANALOG_CTRL(aCH__SCH_TEST_CFG_PICK_READY_SEC, str_name);
		
		str_name = "SCH_TEST.CFG.PICK_COMPLETE.SEC";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "sec", 1, 0.0, 100, "");
		LINK__VAR_ANALOG_CTRL(aCH__SCH_TEST_CFG_PICK_COMPLETE_SEC, str_name);
		
		str_name = "SCH_TEST.CFG.PLACE_READY.SEC";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "sec", 1, 0.0, 100, "");
		LINK__VAR_ANALOG_CTRL(aCH__SCH_TEST_CFG_PLACE_READY_SEC, str_name);
		
		str_name = "SCH_TEST.CFG.PLACE_COMPLETE.SEC";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "sec", 1, 0.0, 100, "");
		LINK__VAR_ANALOG_CTRL(aCH__SCH_TEST_CFG_PLACE_COMPLETE_SEC, str_name);
	}

	// TMC LINK ...
	{
		str_name = "LINK.CCD.POS";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__LINK_CCD_POS, str_name);
	}

	// ...
	{
		p_variable->Add__MONITORING_PROC(3.0, MON_ID__MODULE_STATUS);
	}
	return 1;
}

int CObj_Phy__ALx_STD::__DEFINE__ALARM(p_alarm)
{
	DECLARE__ALARM;

	// ...
	CString title;
	title.Format("%s [CObj_Phy__ALx_STD] : ",sObject_Name);

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

	return 1;
}


//-------------------------------------------------------------------------
int CObj_Phy__ALx_STD::__INITIALIZE__OBJECT(p_variable,p_ext_obj_create)
{
	CString def_name;
	CString def_data;
	CString obj_name;
	CString var_name;

	// ...
	{
		CString file_name;
		CString log_msg;

		file_name.Format("%s.log", sObject_Name);

		log_msg  = "\n\n";
		log_msg += "//------------------------------------------------------------------------";

		xI_LOG_CTRL->CREATE__SUB_DIRECTORY(sObject_Name);
		xI_LOG_CTRL->SET__PROPERTY(file_name,24*5,60);

		xI_LOG_CTRL->DISABLE__TIME_LOG();
		xI_LOG_CTRL->WRITE__LOG(log_msg);

		xI_LOG_CTRL->ENABLE__TIME_LOG();
		xI_LOG_CTRL->WRITE__LOG("   START   \n");
	}

	// ...
	{
		def_name = "DB_CFG_NAME";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, obj_name);

		var_name = "SCH_TEST.CFG.TMC_DUMMY_BY_CTC";
		LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__SCH_TEST_CFG_TMC_DUMMY_BY_CTC, obj_name,var_name);
	}

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
		xCH__PARA_SLOT->Set__DATA("1");
		xCH__PARA_MATERIAL_TYPE->Set__DATA("UNKNOWN");
		xCH__PARA_MODULE_TYPE->Set__DATA("UNKNOWN");
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
	return 1;
}

int CObj_Phy__ALx_STD::__START__OBJECT()
{
	xI_SCH_MATERIAL_CTRL->Link__SERVICE_DB("");

	return 1;
}


//-------------------------------------------------------------------------
int CObj_Phy__ALx_STD::__CALL__CONTROL_MODE(mode,p_debug,p_variable,p_alarm)
{
	xI_Sync_Ctrl.Thread__LOCK();
	iPRC_STS = 1;

	// ...
	int flag = -1;

	xI_Module_Obj->Enable__ERROR_CHECK__NOT_STANDBY();
	xCH__ALIGN_RETRY_FLAG->Set__DATA("");

	// ...
	{
		CString log_msg;
		log_msg.Format("START : [%s]", mode);

		xI_LOG_CTRL->WRITE__LOG(log_msg);
	}

	// ...
	{
			 IF__CTRL_MODE(sMODE__INIT)					flag = Call__INIT(p_variable);
		ELSE_IF__CTRL_MODE(sMODE__ALIGN)				flag = Call__ALIGN(p_variable);

		ELSE_IF__CTRL_MODE(sMODE__PICK_READY)			flag = Call__PICK_READY(p_variable);
		ELSE_IF__CTRL_MODE(sMODE__PICK_COMPLETE)		flag = Call__PICK_COMPLETE(p_variable);

		ELSE_IF__CTRL_MODE(sMODE__PLACE_READY)			flag = Call__PLACE_READY(p_variable);
		ELSE_IF__CTRL_MODE(sMODE__PLACE_COMPLETE)		flag = Call__PLACE_COMPLETE(p_variable);

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

		if(flag > 0)		log_msg.Format("COMPLETE : [%s]",mode);
		else				log_msg.Format("ABORTED  : [%s]",mode);

		xI_LOG_CTRL->WRITE__LOG(log_msg);
	}

	iPRC_STS = -1;
	xI_Sync_Ctrl.Thread__UNLOCK();
	return flag;
}

int CObj_Phy__ALx_STD::__CALL__MONITORING(id,p_variable,p_alarm)
{
	switch(id)
	{
		case MON_ID__MODULE_STATUS:
			Mon__MODULE_STATUS(p_variable,p_alarm);
			break;
	}
	return 1;
}
