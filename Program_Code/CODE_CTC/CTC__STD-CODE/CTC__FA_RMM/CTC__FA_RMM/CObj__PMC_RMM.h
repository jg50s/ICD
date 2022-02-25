#pragma once

#include "Interface_Code.h"


#define  CFG__MFC_SIZE						10
#define  CFG__RFx_SIZE						2


class CObj__PMC_RMM : public __IOBJ__STD_TYPE
{
private:
	//---------------------------------------------------------
	CString sObject_Name;

	int iPM_ID;
	//

	//---------------------------------------------------------
	//  INTERNAL PROPERTY

	// Parameter Channel ...
	CX__VAR_STRING_CTRL  sCH__PARA_ITEM_NAME;

	// MFC ...
	CX__VAR_STRING_CTRL  sCH__MFCx_FLOW_MIN[CFG__MFC_SIZE];
	CX__VAR_STRING_CTRL  sCH__MFCx_FLOW_MAX[CFG__MFC_SIZE];

	CString sPPNAME__MFCx_FLOW[CFG__MFC_SIZE];

	// RFx ...
	CX__VAR_STRING_CTRL  sCH__RFx_FREQ_MIN[CFG__RFx_SIZE];
	CX__VAR_STRING_CTRL  sCH__RFx_FREQ_MAX[CFG__RFx_SIZE];

	CString sPPNAME__RFx_FREQ_PRESET[CFG__RFx_SIZE];
	CString sPPNAME__RFx_FREQ_OUTPUT[CFG__RFx_SIZE];
	CString sPPNAME__RFx_FREQ_LEARNED[CFG__RFx_SIZE];

	// ESC Bias Voltage ...	
	CX__VAR_STRING_CTRL  sCH__ESC_BIAS_VOLTAGE_MAX;

	CString sPPNAME__ESC_BIAS_VOLTAGE_MAX;
	//


	//-------------------------------------------------------------------------	
	CString sMODE__CFG_ITEM_RANGE_CHECK;
	int  Call__CFG_ITEM_RANGE_CHECK(CII_OBJECT__VARIABLE *p_variable,
									CII_OBJECT__ALARM *p_alarm);

	CString sMODE__STEP_ITEM_RANGE_CHECK;
	int  Call__STEP_ITEM_RANGE_CHECK(CII_OBJECT__VARIABLE *p_variable,
									 CII_OBJECT__ALARM *p_alarm);


	//---------------------------------------------------------
	void Mon__PARAMETER_RAMGE_CHANGE(CII_OBJECT__VARIABLE* p_variable);
	//


public:
	CObj__PMC_RMM();
	~CObj__PMC_RMM();

	//-------------------------------------------------------------------------
	int __DEFINE__CONTROL_MODE(obj,l_mode);
	int __DEFINE__VERSION_HISTORY(version);

	int __DEFINE__VARIABLE_STD(p_variable);
	int __DEFINE__ALARM(p_alarm);

	int __Define__USER_FUNCTION(CII_DEFINE__FUNCTION *p_fnc_ctrl);

	//-------------------------------------------------------------------------
	int __INITIALIZE__OBJECT(p_variable,p_ext_obj_create);
	int __START__OBJECT();

	//-------------------------------------------------------------------------
	int __CALL__CONTROL_MODE(mode,p_debug,p_variable,p_alarm);
	int __CALL__MONITORING(id,p_variable,p_alarm);
};
