#pragma once

#include "Interface_Code.h"
#include "CCommon_Error.h"

#include "CObj__HE_VLV__ALID.h"
#include "CObj__HE_VLV__DEF.h"



class CObj__HE_VLV : public __IOBJ__STD_TYPE
{
private:
	//-------------------------------------------------------------------------
	CString sObject_Name;

	// ...
	CCommon_Error__USER_FNC mERROR__USER_FNC;

	SCX__USER_LOG_CTRL xLOG_CTRL;

	int iActive__SIM_MODE;
	//


	//-------------------------------------------------------------------------
	// INTERNAL PROPERTY

	// OBJ ...
	CX__VAR_STRING_CTRL  sCH__OBJ_MSG;
	//

	//-------------------------------------------------------------------------
	// EXTERNAL PROPERTY

	// LINK_IO.SUPPLY_VLV ...
	int iSIZE__SUPPLY_VLV;
	CX__VAR_DIGITAL_CTRL doEXT_CH__SUPPLY_VLV_X[_CFG__VLV_SIZE];

	// LINK_IO.BYPASS_VLV ...
	int iSIZE__BYPASS_VLV;
	CX__VAR_DIGITAL_CTRL doEXT_CH__BYPASS_VLV_X[_CFG__VLV_SIZE];

	// LINK_IO.DUMP_VLV ...
	int iSIZE__DUMP_VLV;
	CX__VAR_DIGITAL_CTRL doEXT_CH__DUMP_VLV_X[_CFG__VLV_SIZE];

	// LINK_IO.FINAL_VLV ...
	int iSIZE__FINAL_VLV;
	CX__VAR_DIGITAL_CTRL doEXT_CH__FINAL_VLV_X[_CFG__VLV_SIZE];
	//

	//------------------------------------------------------------------------------
	CString sMODE__INIT;
	int  Call__INIT(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm);

	CString sMODE__CLOSE;
	int  Call__CLOSE(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm);

	// SUPPLY_VLV.CTRL ...
	CString sMODE__SUPPLY_VLV_OPEN;
	CString sMODE__SUPPLY_VLV_CLOSE;
	int  Call__SUPPLY_VLV_CTRL(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm, const CString& vlv_ctrl);

	// BYPASS_VLV.CTRL ...
	CString sMODE__BYPASS_VLV_OPEN;
	CString sMODE__BYPASS_VLV_CLOSE;
	int  Call__BYPASS_VLV_CTRL(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm, const CString& vlv_ctrl);

	// DUMP_VLV.CTRL ...
	CString sMODE__DUMP_VLV_OPEN;
	CString sMODE__DUMP_VLV_CLOSE;
	int  Call__DUMP_VLV_CTRL(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm, const CString& vlv_ctrl);

	// FINAL_VLV.CTRL ...
	CString sMODE__FINAL_VLV_OPEN;
	CString sMODE__FINAL_VLV_CLOSE;
	int  Call__FINAL_VLV_CTRL(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm, const CString& vlv_ctrl);

	// ...
	CString sMODE__BYPASS_FLOW;
	int  Call__BYPASS_FLOW(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm);

	CString sMODE__DUMP_FLOW;
	int  Call__DUMP_FLOW(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm);

	CString sMODE__FINAL_FLOW;
	int  Call__FINAL_FLOW(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm);
	//


public:
	CObj__HE_VLV();
	~CObj__HE_VLV();

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
