#pragma once

#include "Interface_Code.h"

#include "CCommon_Error.h"
#include "CObj__LPx_STD__DEF.h"


class CObj__LPx_STD : public __IOBJ__STD_TYPE
{
private:
	CCommon_Error__USER_FNC mERROR__USER_FNC;

	//------------------------------------------------------------------------------
	CString sObject_Name;

	SCX__USER_LOG_CTRL xLOG_CTRL;


	//------------------------------------------------------------------------------
	// INTERNAL PROPERTY

	CX__VAR_STRING_CTRL   sCH__PIO_TRANSFER;

	CX__VAR_DIGITAL_CTRL  dCH__SHUTTLE_STATUS;
	CX__VAR_DIGITAL_CTRL  dCH__CST_STATUS;
	CX__VAR_DIGITAL_CTRL  dCH__CLAMP_STATUS;
	CX__VAR_DIGITAL_CTRL  dCH__DOOR_STATUS;

	CX__VAR_STRING_CTRL   sCH__CID_STRING;

	CX__VAR_DIGITAL_CTRL  dCH__SLOT_STATUS[CFG_LP_MAX_SLOT];

	//
	CX__VAR_DIGITAL_CTRL  dCH__CFG_CST_INIT_MODE;
	CX__VAR_DIGITAL_CTRL  dCH__CFG_CST_MATERIAL_SIZE;

	CX__VAR_DIGITAL_CTRL  dCH__CFG_LPn_ID_Reader_Disable;
	CX__VAR_DIGITAL_CTRL  dCH__CFG_UNDOCK_POSITION_TAG_READ;


	//------------------------------------------------------------------------------
	// EXTERNAL PROPERTY

	int iLPx_ID;
	CII_EXT_OBJECT__CTRL *pLPx__OBJ_CTRL;


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
	CString sMODE__CLAMP;
	int  Call__CLAMP(const CString& mode,CII_OBJECT__VARIABLE* p_variable);

	CString sMODE__UNCLAMP;
	int  Call__UNCLAMP(const CString& mode,CII_OBJECT__VARIABLE* p_variable);

	CString sMODE__CID_READ;
	int  Call__CID_READ(const CString& mode,CII_OBJECT__VARIABLE* p_variable);

	CString sMODE__RF_PAGE_READ;
	int  Call__RF_PAGE_READ(const CString& mode,CII_OBJECT__VARIABLE* p_variable);

	CString sMODE__RF_CID_WRITE;
	int  Call__RF_CID_WRITE(const CString& mode,CII_OBJECT__VARIABLE* p_variable);

	CString sMODE__RF_PAGE_WRITE;
	int  Call__RF_PAGE_WRITE(const CString& mode,CII_OBJECT__VARIABLE* p_variable);

	CString sMODE__MAP;
	int  Call__MAP(const CString& mode,CII_OBJECT__VARIABLE* p_variable);

	CString sMODE__EXTENDPADDLE;
	int  Call__EXTENDPADDLE(const CString& mode,CII_OBJECT__VARIABLE* p_variable);

	CString sMODE__RETRACTPADDLE;
	int  Call__RETRACTPADDLE(const CString& mode,CII_OBJECT__VARIABLE* p_variable);

	CString sMODE__PADDLEDOWN;
	int  Call__PADDLE_DOWN(const CString& mode,CII_OBJECT__VARIABLE* p_variable);

	CString sMODE__PADDLEUP;
	int  Call__PADDLE_UP(const CString& mode,CII_OBJECT__VARIABLE* p_variable);

	CString sMODE__LATCH;
	int  Call__LATCH(const CString& mode,CII_OBJECT__VARIABLE* p_variable);

	CString sMODE__UNLATCH;
	int  Call__UNLATCH(const CString& mode,CII_OBJECT__VARIABLE* p_variable);

	CString sMODE__CLOSEDOOR;
	int  Call__CLOSEDOOR(const CString& mode,CII_OBJECT__VARIABLE* p_variable);

	CString sMODE__OPENDOOR;
	int  Call__OPENDOOR(const CString& mode,CII_OBJECT__VARIABLE* p_variable);

	CString sMODE__VACON;
	int  Call__VACON(const CString& mode,CII_OBJECT__VARIABLE* p_variable);

	CString sMODE__VACOFF;
	int  Call__VACOFF(const CString& mode,CII_OBJECT__VARIABLE* p_variable);

	CString sMODE__EXTENDSHUTTLE;
	int  Call__EXTENDSHUTTLE(const CString& mode,CII_OBJECT__VARIABLE* p_variable);

	CString sMODE__RETRACTSHUTTLE;
	int  Call__RETRACTSHUTTLE(const CString& mode,CII_OBJECT__VARIABLE* p_variable);

	CString sMODE__HALT;
	int  Call__HALT(const CString& mode,CII_OBJECT__VARIABLE* p_variable);

	// ...
	int  Fnc__LOAD(const int empty_flag,const int material_size);
	int  Fnc__UNLOAD();
	//


public:
	CObj__LPx_STD();
	~CObj__LPx_STD();

	//-------------------------------------------------------------------------
	int __DEFINE__CONTROL_MODE(obj,l_mode);
	int __DEFINE__VERSION_HISTORY(version);

	int __DEFINE__VARIABLE_STD(p_variable);
	int __DEFINE__ALARM(p_alarm);

	//-------------------------------------------------------------------------
	int __INITIALIZE__OBJECT(p_variable,p_ext_obj_create);

	//-------------------------------------------------------------------------
	int __CALL__CONTROL_MODE(mode,p_debug,p_variable,p_alarm);
	int __CALL__MONITORING(id,p_variable,p_alarm);
};
