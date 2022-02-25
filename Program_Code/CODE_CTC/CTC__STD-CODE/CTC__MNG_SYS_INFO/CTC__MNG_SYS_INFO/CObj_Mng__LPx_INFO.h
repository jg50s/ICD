#pragma once

#include "Interface_Code.h"
#include "CCommon_Error.h"

#include "CObj_Mng__LPx_INFO__DEF.h"


#define  ALID__OBJECT_MODE_UNKNOWN					11


class CObj_Mng__LPx_INFO : public __IOBJ__STD_TYPE
{
private:
	//-------------------------------------------------------------------------
	CString sObject_Name;

	CCommon_Error__DEF_VARIABLE mERROR__DEF_VAR;
	CCommon_Error__USER_FNC     mERROR__USER_FNC;


	//-------------------------------------------------------------------------
	//  INTERNAL PROPERTY

	// LPx CTRL -----
	CX__VAR_STRING_CTRL  sCH__LPx_CTRL__SEL_ID;
	CX__VAR_STRING_CTRL  sCH__LPx_CTRL__LOCK_FLAG[CFG__LPx_SIZE];

	// LPx INFO -----
	CX__VAR_STRING_CTRL  sCH__LPx_INFO__CTRL_MSG;

	CX__VAR_STRING_CTRL  sCH__LPx_INFO__JOBID;
	CX__VAR_STRING_CTRL  sCH__LPx_INFO__PORT_STATUS;
	CX__VAR_STRING_CTRL  sCH__LPx_INFO__MANUAL_START_STATUS;
	CX__VAR_STRING_CTRL  sCH__LPx_INFO__CYCLE_START_STATUS;
	CX__VAR_STRING_CTRL  sCH__LPx_INFO__LOTID;
	CX__VAR_STRING_CTRL  sCH__LPx_INFO__CSTID;	
	CX__VAR_STRING_CTRL  sCH__LPx_INFO__PPID;
	CX__VAR_STRING_CTRL  sCH__LPx_INFO__TRANSFER_PIO;
	CX__VAR_STRING_CTRL  sCH__LPx_INFO__PIO_COMM_READY_STS;
	CX__VAR_STRING_CTRL  sCH__LPx_INFO__CST_STATUS;
	CX__VAR_STRING_CTRL  sCH__LPx_INFO__SLOTx_STATUS[CFG__SLOT_SIZE];

	CX__VAR_STRING_CTRL  sCH__LPx_INFO__DB_LotID;
	CX__VAR_STRING_CTRL  sCH__LPx_INFO__DB_RouteID;
	CX__VAR_ANALOG_CTRL  aCH__LPx_INFO__DB_StartSlot;
	CX__VAR_ANALOG_CTRL  aCH__LPx_INFO__DB_EndSlot;
	CX__VAR_ANALOG_CTRL  aCH__LPx_INFO__DB_CycleCount;

	// LPx DB -----
	CX__VAR_STRING_CTRL  sCH__LPx_DB__LotID[CFG__LPx_SIZE];
	CX__VAR_STRING_CTRL  sCH__LPx_DB__RouteID[CFG__LPx_SIZE];
	CX__VAR_STRING_CTRL  sCH__LPx_DB__StartSlot[CFG__LPx_SIZE];
	CX__VAR_STRING_CTRL  sCH__LPx_DB__EndSlot[CFG__LPx_SIZE];
	CX__VAR_STRING_CTRL  sCH__LPx_DB__CycleCount[CFG__LPx_SIZE];

	// OBJ INFO -----
	CX__VAR_STRING_CTRL  sCH__LPx_INFO__OBJ_CTRL;
	CX__VAR_STRING_CTRL  sCH__LPx_INFO__OBJ_MODE;
	CX__VAR_STRING_CTRL  sCH__LPx_INFO__OBJ_STATUS;

	// OBJ CTRL -----
	CX__VAR_STRING_CTRL  sCH__OBJ_CTRL__PORT_EXCEPTION;
	CX__VAR_STRING_CTRL  sCH__OBJ_CTRL__JOB_SELECT_REQ;

	CX__VAR_STRING_CTRL  sCH__OBJ_CTRL__MANUAL_START_REQ;
	CX__VAR_STRING_CTRL  sCH__OBJ_CTRL__CYCLE_START_REQ;
	//

	//-------------------------------------------------------------------------
	//  EXTERNAL PROPERTY

	int iLPx_SIZE;

	CX__VAR_DIGITAL_CTRL xEXT_CH__LPx_USE_FLAG[CFG__LPx_SIZE];
	CX__VAR_STRING_CTRL  xEXT_CH__LPx_PORT_EXCEPTION[CFG__LPx_SIZE];

	CX__VAR_STRING_CTRL  xEXT_CH__LPx_CH_WIN[CFG__LPx_SIZE];
	CString sDATA__WIN_NAME[CFG__LPx_SIZE];

	CII_EXT_OBJECT__CTRL *pOBJ_CTRL__LPx[CFG__LPx_SIZE];
	CStringArray sLIST__LPx_VARIABLE[CFG__LPx_SIZE];
	//

	// ...
	void Mon__INFO_CTRL(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm);
	//


public:
	CObj_Mng__LPx_INFO();
	~CObj_Mng__LPx_INFO();

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
