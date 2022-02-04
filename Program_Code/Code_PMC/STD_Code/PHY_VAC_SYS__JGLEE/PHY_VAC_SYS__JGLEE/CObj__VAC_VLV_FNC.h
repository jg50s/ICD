#pragma once

#include "Interface_Code.h"

#include "CCommon_Error.h"
#include "CCommon_Def.h"

#include "CObj__VAC_VLV_FNC__DEF.h"


class CObj__VAC_VLV_FNC : public __IOBJ__STD_TYPE
{
private:
	//------------------------------------------------------------
	CString sObject_Name;

	// ...
	CCommon_Error__USER_FNC mERROR__USER_FNC;

	SCX__USER_LOG_CTRL xLOG_CTRL;
	//


	//------------------------------------------------------------
	// INTERNAL PROPERTY

	// OBJ ...
	CX__VAR_STRING_CTRL  sCH__OBJ_MSG;

	// PARA ...
	CX__VAR_ANALOG_CTRL  aCH__PARA_APC_POSITION;

	// MON ...
	CX__VAR_STRING_CTRL  sCH__MON_PUMPING_STATE;

	// 
	CX__VAR_DIGITAL_CTRL dCH__APC_BALLAST_MODE;	
	CX__VAR_STRING_CTRL  sCH__PARA_XFER_BALLAST_WAIT_SKIP_FLAG;
	//


	//------------------------------------------------------------
	// EXTERNAL PROPERTY

	// ...
	CII_EXT_OBJECT__CTRL *pOBJ_CTRL__VAC_VLV;
	
	CX__VAR_STRING_CTRL  sEXT_CH__VAC_VLV__MON_PUMPING_STATE;

	// ...
	CII_EXT_OBJECT__CTRL *pOBJ_CTRL__APC_VLV;

	CX__VAR_ANALOG_CTRL  aEXT_CH__APC_VLV__PARA_PRESSURE;
	CX__VAR_ANALOG_CTRL  aEXT_CH__APC_VLV__PARA_POSITION;
	CX__VAR_STRING_CTRL  sEXT_CH__APC_VLV__MON_POSITION;
	//

	//------------------------------------------------------------
	// ...
	CString sMODE__ALL_CLOSE;
	int Call__ALL_CLOSE(CII_OBJECT__VARIABLE *p_variable);

	CString sMODE__FR_SR_CLOSE;
	int Call__FR_SR_CLOSE(CII_OBJECT__VARIABLE *p_variable);

	//
	CString sMODE__SR_OPEN;
	int Call__SR_OPEN(CII_OBJECT__VARIABLE *p_variable);

	CString sMODE__SR_CLOSE;
	int Call__SR_CLOSE(CII_OBJECT__VARIABLE *p_variable);

	//
	CString sMODE__FR_OPEN_ALL;
	CString sMODE__FR_OPEN_IO;
	int Call__FR_OPEN(CII_OBJECT__VARIABLE *p_variable, const int all_mode);

	CString sMODE__FR_CLOSE;
	int Call__FR_CLOSE(CII_OBJECT__VARIABLE *p_variable);

	//
	CString sMODE__EXHAUST_OPEN;
	int Call__EXHAUST_OPEN(CII_OBJECT__VARIABLE *p_variable);

	CString sMODE__EXHAUST_CLOSE;
	int Call__EXHAUST_CLOSE(CII_OBJECT__VARIABLE *p_variable);

	// ...
	CString sMODE__APC_OPEN;
	int Call__APC_OPEN(CII_OBJECT__VARIABLE *p_variable);

	CString sMODE__APC_CLOSE;
	int Call__APC_CLOSE(CII_OBJECT__VARIABLE *p_variable);

	CString sMODE__APC_POSITION;
	int Call__APC_POSITION(CII_OBJECT__VARIABLE *p_variable);

	// ...
	CString sMODE__APC_BALLAST_CTRL;
	int Call__APC_BALLAST_CTRL(CII_OBJECT__VARIABLE *p_variable);

	CString sMODE__APC_BALLAST_POS;
	int Call__APC_BALLAST_POS(CII_OBJECT__VARIABLE *p_variable);
	//

	//------------------------------------------------------------
	// ...
	int Mon__STATE_CHECK(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm);
	//

public:
	CObj__VAC_VLV_FNC();
	~CObj__VAC_VLV_FNC();

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
