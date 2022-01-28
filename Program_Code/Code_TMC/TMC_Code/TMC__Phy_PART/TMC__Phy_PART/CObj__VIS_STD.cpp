#include "StdAfx.h"
#include "CObj__VIS_STD.h"


//-------------------------------------------------------------------------
CObj__VIS_STD::CObj__VIS_STD()
{

}
CObj__VIS_STD::~CObj__VIS_STD()
{

}

//-------------------------------------------------------------------------
int CObj__VIS_STD::__DEFINE__CONTROL_MODE(obj,l_mode)
{
	sObject_Name = obj;

	// ...
	{
		ADD__CTRL_VAR(sMODE__INIT,           "INIT");
		ADD__CTRL_VAR(sMODE__RUN_START,      "RUN_START");
		ADD__CTRL_VAR(sMODE__PRO_START,      "PRO_START");
		ADD__CTRL_VAR(sMODE__PRO_STOP,       "PRO_STOP");
		ADD__CTRL_VAR(sMODE__DOWNLOAD,       "DOWNLOAD");
		ADD__CTRL_VAR(sMODE__PRO_READY,      "PRO_READY");
		ADD__CTRL_VAR(sMODE__PLACE_READY,    "PLACE_READY");
		ADD__CTRL_VAR(sMODE__PLACE_COMPLETE, "PLACE_COMPLETE");
		ADD__CTRL_VAR(sMODE__PICK_READY,     "PICK_READY");
		ADD__CTRL_VAR(sMODE__PICK_COMPLETE,  "PICK_COMPLETE");
		ADD__CTRL_VAR(sMODE__GET_RESULT,     "GET_RESULT");
		ADD__CTRL_VAR(sMODE__GET_FILE,       "GET_FILE");
		ADD__CTRL_VAR(sMODE__EXCHANGE_READY, "EXCHANGE_READY");
	}
	return 1;
}
int CObj__VIS_STD::__DEFINE__VERSION_HISTORY(version)
{

	return 1;
}


// ...
#define  MON_ID__IO_MONITOR				1


int CObj__VIS_STD::__DEFINE__VARIABLE_STD(p_variable)
{
	DECLARE__STD_VARIABLE;
	
	CCommon_Error__DEF_VARIABLE m_err_def_variable;
	p_variable->Link__DEF_VARIABLE__ERROR_FEEDBACK(&m_err_def_variable);

	// ...
	CString str_name;
	CString dsc_item_list;
	int i;

	// ...
	{
		p_variable->Get__STD_DESCRIPTION(DSP__SLOT_STATUS,dsc_item_list);

		for(i=0;i<CFG_ALx__SLOT_MAX;i++)
		{
			// Slot Status 
			str_name.Format("OTR.OUT.MON.dSLOT%002d.STATUS",i+1);
			STD__ADD_DIGITAL_WITH_X_OPTION(str_name, dsc_item_list,"");
			LINK__VAR_DIGITAL_CTRL(dCH__SLOT_STATUS[i], str_name);

			// Slot Title
			str_name.Format("OTR.OUT.MON.sSLOT%002d.TITLE",i+1);
			STD__ADD_STRING_WITH_X_OPTION(str_name, "");
			LINK__VAR_STRING_CTRL(sCH__SLOT_TITLE[i], str_name);
		}

		//
		str_name = "OTR.IN.MON.sSLOT.NO";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__SLOT_NO,str_name);

		str_name = "OTR.IN.MON.sLOTID";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__LOTID,str_name);

		str_name = "OTR.IN.MON.sPORTID";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__PORTID,str_name);

		str_name = "OTR.IN.MON.sPMID";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__PMID,str_name);

		str_name = "OTR.IN.MON.sSLOTID";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__SLOTID,str_name);

		str_name = "OTR.OUT.MON.sJUDGMENT";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__JUDGMENT,str_name);

		str_name = "OTR.IN.MON.sRECIPE";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__RECIPE,str_name);

		str_name = "OTR.OUT.MON.sRECIPE.LIST";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__RECIPE_LIST,str_name);

		str_name = "OTR.OUT.MON.sRECIPE.UPLOAD";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__RECIPE_UPLOAD,str_name);
	}

	// ...
	{
		p_variable->Add__MONITORING_PROC(1.0, MON_ID__IO_MONITOR);
	}
	return 1;
}

int CObj__VIS_STD::__DEFINE__ALARM(p_alarm)
{
	DECLARE__ALARM;

	return 1;
}

int CObj__VIS_STD::__Define__USER_FUNCTION(CII_DEFINE__FUNCTION *p_fnc_ctrl)
{
	p_fnc_ctrl->Link__ERROR_FEEDBACK(&mERROR__USER_FNC);

	return 1;
}

//-------------------------------------------------------------------------
int CObj__VIS_STD::__INITIALIZE__OBJECT(p_variable,p_ext_obj_create)
{
	CString def_name;
	CString def_data;
	CString str_name;

	// VISx OBJECT ...
	{
		def_name = "OBJ__VIS";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name,def_data);

		pVISx__OBJ_CTRL = p_ext_obj_create->Create__OBJECT_CTRL(def_data);

		//.....
		str_name = "OTR.IN.sVIS1.SLOT.NO";
		LINK__EXT_VAR_STRING_CTRL(sEXT_CH_VIS1__SLOTNO, def_data,str_name);

		str_name = "OTR.IN.sVIS1.LOTID";
		LINK__EXT_VAR_STRING_CTRL(sEXT_CH_VIS1__LOTID, def_data,str_name);

		str_name = "OTR.IN.sVIS1.PORTID";
		LINK__EXT_VAR_STRING_CTRL(sEXT_CH_VIS1__PORTID, def_data,str_name);

		str_name = "OTR.IN.sVIS1.PMID";
		LINK__EXT_VAR_STRING_CTRL(sEXT_CH_VIS1__PMID, def_data,str_name);

		str_name = "OTR.IN.sVIS1.SLOTID";
		LINK__EXT_VAR_STRING_CTRL(sEXT_CH_VIS1__SLOTID, def_data,str_name);

		str_name = "OTR.OUT.sVIS1.JUDGMENT";
		LINK__EXT_VAR_STRING_CTRL(sEXT_CH_VIS1__JUDGMENT, def_data,str_name);

		str_name = "OTR.IN.sVIS1.RECIPE";
		LINK__EXT_VAR_STRING_CTRL(sEXT_CH_VIS1__RECIPE, def_data,str_name);

		str_name = "OTR.OUT.sVIS1.RECIPE.LIST";
		LINK__EXT_VAR_STRING_CTRL(sEXT_CH_VIS1__RECIPE_LIST, def_data, str_name);

		str_name = "OTR.IN.sVIS1.RECIPE.UPLOAD";
		LINK__EXT_VAR_STRING_CTRL(sEXT_CH_VIS1__RECIPE_UPLOAD, def_data, str_name);	
	}

	// ...
	{
		CString file_name;
		CString log_msg;

		file_name.Format("%s_App.log", sObject_Name);

		log_msg  = "\n\n";
		log_msg += "//------------------------------------------------------------------------";

		xLOG_CTRL->CREATE__SUB_DIRECTORY(sObject_Name);
		xLOG_CTRL->SET__PROPERTY(file_name,24*5,60);

		xLOG_CTRL->DISABLE__TIME_LOG();
		xLOG_CTRL->WRITE__LOG(log_msg);

		xLOG_CTRL->ENABLE__TIME_LOG();
		xLOG_CTRL->WRITE__LOG("   START   \n");
	}
	return 1;
}

//-------------------------------------------------------------------------
int CObj__VIS_STD::__CALL__CONTROL_MODE(mode,p_debug,p_variable,p_alarm)
{
	// ...
	{
		CString log_msg;

		log_msg.Format("Start ... :  [%s]", mode);
		xLOG_CTRL->WRITE__LOG(log_msg);
	}

	// ...
	CString szData;

	sCH__LOTID->Get__DATA(szData);
	sEXT_CH_VIS1__LOTID->Set__DATA(szData);

	sCH__PORTID->Get__DATA(szData);
	sEXT_CH_VIS1__PORTID->Set__DATA(szData);

	sCH__PMID->Get__DATA(szData);
	sEXT_CH_VIS1__PMID->Set__DATA(szData);
	
	sCH__SLOTID->Get__DATA(szData);
	sEXT_CH_VIS1__SLOTID->Set__DATA(szData);

	sCH__RECIPE->Get__DATA(szData);
	sEXT_CH_VIS1__RECIPE->Set__DATA(szData);

	sCH__SLOT_NO->Get__DATA(szData);
	sEXT_CH_VIS1__SLOTNO->Set__DATA(szData);

	// ...
	int flag = -1;

	// ...
	{
		     IF__CTRL_MODE(sMODE__INIT)					flag = Call__INIT(p_variable,p_alarm);

		ELSE_IF__CTRL_MODE(sMODE__RUN_START)			flag = Call__RUN_START(p_variable,p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__PRO_START)			flag = Call__PRO_START(p_variable,p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__PRO_STOP)				flag = Call__PRO_STOP(p_variable,p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__DOWNLOAD)				flag = Call__DOWNLOAD(p_variable,p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__PRO_READY)			flag = Call__PRO_READY(p_variable,p_alarm);

		ELSE_IF__CTRL_MODE(sMODE__PLACE_READY)			flag = Call__PLACE_READY(p_variable,p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__PLACE_COMPLETE)		flag = Call__PLACE_COMPLETE(p_variable,p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__PICK_READY)			flag = Call__PICK_READY(p_variable,p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__PICK_COMPLETE)		flag = Call__PICK_COMPLETE(p_variable,p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__EXCHANGE_READY)		flag = Call__EXCHANGE_READY(p_variable,p_alarm);

		ELSE_IF__CTRL_MODE(sMODE__GET_RESULT)			flag = Call__GET_RESULT(p_variable,p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__GET_FILE)				flag = Call__GET_FILE(p_variable,p_alarm);
	}

	if((flag < 0)||(p_variable->Check__CTRL_ABORT() > 0))
	{
		CString log_msg;

		log_msg.Format("Aborted ... :  [%s]",mode);
		xLOG_CTRL->WRITE__LOG(log_msg);
	}
	else
	{
		CString log_msg;

		log_msg.Format("Completed ... :  [%s]",mode);
		xLOG_CTRL->WRITE__LOG(log_msg);
	}

	return flag;
}
int CObj__VIS_STD::__CALL__MONITORING(id,p_variable,p_alarm)
{
	switch(id)
	{
		case MON_ID__IO_MONITOR:
			Mon__IO_MONITOR(p_variable,p_alarm);
			break;
	}

	return 1;
}
