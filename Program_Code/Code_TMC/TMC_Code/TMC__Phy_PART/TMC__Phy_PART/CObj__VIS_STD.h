#pragma once

#include "Interface_Code.h"

#include "CCommon_Error.h"
#include "CCommon_System.h"


class CObj__VIS_STD : public __IOBJ__STD_TYPE
{
private:
	CCommon_Error__USER_FNC mERROR__USER_FNC;

	//-------------------------------------------------------------------------
	CString sObject_Name;

	SCX__USER_LOG_CTRL xLOG_CTRL;


	//-------------------------------------------------------------------------
	// INTERNAL PROPERTY

	CX__VAR_DIGITAL_CTRL dCH__SLOT_STATUS[CFG_ALx__SLOT_MAX];
	CX__VAR_STRING_CTRL  sCH__SLOT_TITLE[CFG_ALx__SLOT_MAX];

	CX__VAR_STRING_CTRL  sCH__SLOT_NO;
	CX__VAR_STRING_CTRL  sCH__LOTID;
	CX__VAR_STRING_CTRL  sCH__PORTID;
	CX__VAR_STRING_CTRL  sCH__PMID;
	CX__VAR_STRING_CTRL  sCH__SLOTID;
	CX__VAR_STRING_CTRL  sCH__JUDGMENT;
	CX__VAR_STRING_CTRL  sCH__RECIPE;
	CX__VAR_STRING_CTRL  sCH__RECIPE_LIST;
	CX__VAR_STRING_CTRL  sCH__RECIPE_UPLOAD;


	//-------------------------------------------------------------------------
	// EXTERNAL PROPERTY

	CII_EXT_OBJECT__CTRL *pVISx__OBJ_CTRL;

	CX__VAR_STRING_CTRL  sEXT_CH_VIS1__SLOTNO;
	CX__VAR_STRING_CTRL  sEXT_CH_VIS1__LOTID;
	CX__VAR_STRING_CTRL  sEXT_CH_VIS1__PORTID;
	CX__VAR_STRING_CTRL  sEXT_CH_VIS1__PMID;
	CX__VAR_STRING_CTRL  sEXT_CH_VIS1__SLOTID;
	CX__VAR_STRING_CTRL  sEXT_CH_VIS1__JUDGMENT;
	CX__VAR_STRING_CTRL  sEXT_CH_VIS1__RECIPE;
	CX__VAR_STRING_CTRL  sEXT_CH_VIS1__RECIPE_LIST;
	CX__VAR_STRING_CTRL  sEXT_CH_VIS1__RECIPE_UPLOAD;


	//------------------------------------------------------------------------------
	// INIT ----- 
	CString sMODE__INIT;
	int  Call__INIT(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm);

	// RUN_START -----
	CString sMODE__RUN_START;
	int  Call__RUN_START(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm);

	// PRO_START -----
	CString sMODE__PRO_START;
	int  Call__PRO_START(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm);

	// PRO_STOP -----
	CString sMODE__PRO_STOP;
	int  Call__PRO_STOP(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm);

	// DOWNLOAD -----
	CString sMODE__DOWNLOAD;
	int  Call__DOWNLOAD(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm);

	// PRO_READY -----
	CString sMODE__PRO_READY;
	int  Call__PRO_READY(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm);

	// PLACE_READY -----
	CString sMODE__PLACE_READY;
	int  Call__PLACE_READY(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm);

	// PLACE_COMPLETE -----
	CString sMODE__PLACE_COMPLETE;
	int  Call__PLACE_COMPLETE(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm);

	// PICK_READY -----
	CString sMODE__PICK_READY;
	int  Call__PICK_READY(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm);

	// PICK_COMPLETE -----
	CString sMODE__PICK_COMPLETE;
	int  Call__PICK_COMPLETE(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm);

	// GET_RESULT -----
	CString sMODE__GET_RESULT;
	int  Call__GET_RESULT(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm);

	// GET_FILE -----
	CString sMODE__GET_FILE;
	int  Call__GET_FILE(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm);

	// EXCHANGE_READY -----
	CString sMODE__EXCHANGE_READY;
	int  Call__EXCHANGE_READY(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm);


	//-------------------------------------------------------------------------
	void Mon__IO_MONITOR(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm);
	//


public:
	CObj__VIS_STD();
	~CObj__VIS_STD();

	//-------------------------------------------------------------------------
	int __DEFINE__CONTROL_MODE(obj,l_mode);
	int __DEFINE__VERSION_HISTORY(version);

	int __DEFINE__VARIABLE_STD(p_variable);
	int __DEFINE__ALARM(p_alarm);

	int __Define__USER_FUNCTION(CII_DEFINE__FUNCTION *p_fnc_ctrl);

	//-------------------------------------------------------------------------
	int __INITIALIZE__OBJECT(p_variable,p_ext_obj_create);

	//-------------------------------------------------------------------------
	int __CALL__CONTROL_MODE(mode,p_debug,p_variable,p_alarm);
	int __CALL__MONITORING(id,p_variable,p_alarm);
};
