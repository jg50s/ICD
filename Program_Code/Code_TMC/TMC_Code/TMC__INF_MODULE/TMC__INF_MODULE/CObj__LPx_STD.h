#pragma once

#include "Interface_Code.h"
#include "CCommon_Error.h"


class CObj__LPx_STD : public __IOBJ__STD_TYPE
{
private:
	CCommon_Error__USER_FNC mERROR__USER_FNC;

	//------------------------------------------------------------------------------
	CString sObject_Name;

	SCX__USER_LOG_CTRL xLOG_CTRL;


	//------------------------------------------------------------------------------
	// INTERNAL PROPERTY
	CX__VAR_DIGITAL_CTRL dCH__OBJ_CTRL;


	//------------------------------------------------------------------------------
	// EXTERNAL PROPERTY

	CII_EXT_OBJECT__CTRL *pLPx__OBJ_CTRL;

	CX__VAR_DIGITAL_CTRL dEXT_CH__OBJ_STATUS;
	CString  sEXT_VAR__LPx_RELOAD_FLAG;


	//------------------------------------------------------------------------------
	CString sMODE__INIT;
	int  Call__INIT(CII_OBJECT__VARIABLE* p_variable);

	CString sMODE__PREPLOAD;
	int  Call__PREPLOAD(const CString& mode,CII_OBJECT__VARIABLE* p_variable);

	CString sMODE__LOAD;
	int  Call__LOAD(const CString& mode,CII_OBJECT__VARIABLE* p_variable);

	//
	CString sMODE__RLSUNLOAD;
	int  Call__RLSUNLOAD(const CString& mode,CII_OBJECT__VARIABLE* p_variable);

	CString sMODE__UNLOAD;
	int  Call__UNLOAD(const CString& mode,CII_OBJECT__VARIABLE* p_variable);

	//
	CString sMODE__CID_READ;
	int  Call__CID_READ(CII_OBJECT__VARIABLE* p_variable);

	CString sMODE__RF_CID_READ;
	int  Call__RF_CID_READ(CII_OBJECT__VARIABLE* p_variable);

	CString sMODE__RF_PAGE_READ;
	int  Call__RF_PAGE_READ(CII_OBJECT__VARIABLE* p_variable);

	CString sMODE__RF_CID_WRITE;
	int  Call__RF_CID_WRITE(CII_OBJECT__VARIABLE* p_variable);

	CString sMODE__RF_PAGE_WRITE;
	int  Call__RF_PAGE_WRITE(CII_OBJECT__VARIABLE* p_variable);


public:
	CObj__LPx_STD();
	~CObj__LPx_STD();

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
