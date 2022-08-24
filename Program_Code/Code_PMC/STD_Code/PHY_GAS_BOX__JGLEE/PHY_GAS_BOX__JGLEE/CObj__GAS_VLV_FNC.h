#pragma once

#include "Interface_Code.h"

#include "CCommon_Error.h"
#include "CCommon_Def.h"

#include "CObj__GAS_VLV_FNC__DEF.h"


class CObj__GAS_VLV_FNC : public __IOBJ__STD_TYPE
{
private:
	//------------------------------------------------------------
	CString sObject_Name;

	// ...
	CCommon_Error__USER_FNC mERROR__USER_FNC;

	SCX__USER_LOG_CTRL xLOG_CTRL;
	int iActive__SIM_MODE;

	CStringArray sList__GAS_TYPE;
	//


	//------------------------------------------------------------
	// INTERNAL PROPERTY

	// OBJ ...
	CX__VAR_DIGITAL_CTRL dCH__OBJ_CTRL;

	CX__VAR_STRING_CTRL	 sCH__OBJ_STATUS;
	CX__VAR_STRING_CTRL	 sCH__OBJ_MSG;

	// PARA.INTERLOCK ...
	CX__VAR_DIGITAL_CTRL dCH__PARA_INTERLOCK_SKIP;

	// PARA ...
	CX__VAR_DIGITAL_CTRL dCH__PARA_MFC_TYPE;
	CX__VAR_ANALOG_CTRL  aCH__PARA_MFC_FLOW;
	CX__VAR_ANALOG_CTRL  aCH__PARA_N2_FLOW_TIME;
	CX__VAR_ANALOG_CTRL  aCH__PARA_PURGE_CYCLE_COUNT;
	CX__VAR_DIGITAL_CTRL dCH__PARA_PURGE_TEST_MODE;
	CX__VAR_DIGITAL_CTRL dCH__PARA_SINGLE_TEST_GAS_TYPE;
	CX__VAR_ANALOG_CTRL  aCH__PARA_PURGE_DELAY_SEC;

	// CUR ...
	CX__VAR_STRING_CTRL  sCH__CUR_MFC_GAS_NAME;
	CX__VAR_ANALOG_CTRL  aCH__CUR_N2_FLOW_TIME;
	CX__VAR_ANALOG_CTRL  aCH__CUR_PURGE_CYCLE_COUNT;
	CX__VAR_ANALOG_CTRL  aCH__CUR_PURGE_DELAY_SEC;

	// CFG : WAP ...
	CX__VAR_DIGITAL_CTRL dCH__CFG_WAP_AUTO_LEARN_GAS;
	CX__VAR_ANALOG_CTRL  aCH__CFG_WAP_AUTO_LEARN_GAS_FLOW;
	CX__VAR_ANALOG_CTRL  aCH__CFG_WAP_AUTO_LEARN_START_DELAY;

	// CFG : TRANSFER.BALLAST ...
	CX__VAR_ANALOG_CTRL  aCH__CFG_TRANSFER_BALLAST_GAS_FLOW;
	CX__VAR_DIGITAL_CTRL dCH__CFG_TRANSFER_BALLAST_GAS_ID;
	CX__VAR_STRING_CTRL  sCH__CUR_TRANSFER_BALLAST_GAS_NAME;

	// CFG : CHAMBER.BALLAST ...
	CX__VAR_ANALOG_CTRL  aCH__CFG_CHAMBER_BALLAST_GAS_FLOW;
	CX__VAR_DIGITAL_CTRL dCH__CFG_CHAMBER_BALLAST_GAS_ID;
	CX__VAR_STRING_CTRL  sCH__CUR_CHAMBER_BALLAST_GAS_NAME;
	//


	//------------------------------------------------------------
	// EXTERNAL PROPERTY

	// OBJ.DB_INF ...
	CX__VAR_DIGITAL_CTRL dEXT_CH__CFG_TRANSFER_MODE;

	// CH.PUMPING_STATE ...
	CX__VAR_STRING_CTRL  sEXT_CH__CHM_PUMPING_STATE;

	// OBJ.MFC ...
	int iMFC_SIZE;
	CII_EXT_OBJECT__CTRL *pOBJ_CTRL__MFC[_MAX__MFC_OBJ];
	
	CX__VAR_ANALOG_CTRL  aEXT_CH__PARA_SET_FLOW[_MAX__MFC_OBJ];

	CX__VAR_DIGITAL_CTRL dEXT_CH__CFG_MFC_USE[_MAX__MFC_OBJ];
	CX__VAR_STRING_CTRL  sEXT_CH__CFG_GAS_NAME[_MAX__MFC_OBJ];
	CX__VAR_ANALOG_CTRL  aEXT_CH__CFG_MFC_MIN_VALUE[_MAX__MFC_OBJ];
	CX__VAR_ANALOG_CTRL  aEXT_CH__CFG_MFC_MAX_VALUE[_MAX__MFC_OBJ];
	CX__VAR_ANALOG_CTRL  aEXT_CH__CFG_MFC_DEC_VALUE[_MAX__MFC_OBJ];

	// OBJ.GAS ...
	CII_EXT_OBJECT__CTRL *pOBJ_CTRL__GAS;

	// OBJ.FRC_X ...
	int iFRC_SIZE;
	CII_EXT_OBJECT__CTRL *pOBJ_CTRL__FRC_X[_MAX__FRC_OBJ];

	// OBJ.DGF_VLV ...
	bool bActive__DGF_VLV;
	CII_EXT_OBJECT__CTRL *pOBJ_CTRL__DGF_VLV;
	//

	//------------------------------------------------------------
	// ...
	CString sMODE__ALL_CLOSE;
	int Call__ALL_CLOSE(CII_OBJECT__VARIABLE *p_variable);
	int Fnc__ALL_CLOSE(CII_OBJECT__VARIABLE *p_variable);

	CString sMODE__MFC_ALL_CLOSE;
	int Call__MFC_ALL_CLOSE(CII_OBJECT__VARIABLE *p_variable);
	int Fnc__MFC_ALL_CLOSE(CII_OBJECT__VARIABLE *p_variable);

	//
	CString sMODE__PROC_READY;
	int Call__PROC_READY(CII_OBJECT__VARIABLE *p_variable);

	//
	CString sMODE__SV_OPEN;
	int Call__SV_OPEN(CII_OBJECT__VARIABLE *p_variable);

	CString sMODE__SV_CLOSE;
	int Call__SV_CLOSE(CII_OBJECT__VARIABLE *p_variable);

	//
	CString sMODE__FV_OPEN;
	int Call__FV_OPEN(CII_OBJECT__VARIABLE *p_variable);

	CString sMODE__FV_CLOSE;
	int Call__FV_CLOSE(CII_OBJECT__VARIABLE *p_variable);

	//
	CString sMODE__MFC_CONTROL;
	int Call__MFC_CONTROL(CII_OBJECT__VARIABLE *p_variable);

	CString sMODE__MFC_CLOSE;
	int Call__MFC_CLOSE(CII_OBJECT__VARIABLE *p_variable);

	//
	CString sMODE__GAS_LINE_PURGE;
	int Call__GAS_LINE_PURGE(CII_OBJECT__VARIABLE *p_variable);
	int Fnc__GAS_LINE_PURGE(CII_OBJECT__VARIABLE *p_variable);

	CString sMODE__CHM_LINE_PURGE;
	int Call__CHM_LINE_PURGE(CII_OBJECT__VARIABLE *p_variable);
	int Fnc__CHM_LINE_PURGE(CII_OBJECT__VARIABLE *p_variable);

	//
	CString sMODE__LINE_PURGE_WITH_N2;
	int Call__LINE_PURGE_WITH_N2(CII_OBJECT__VARIABLE *p_variable);
	int Fnc__LINE_PURGE_WITH_N2(CII_OBJECT__VARIABLE *p_variable);

	// ...
	CString sMODE__CHM_BALLAST_FLOW;
	int Call__CHM_BALLAST_FLOW(CII_OBJECT__VARIABLE *p_variable);

	CString sMODE__TRANS_BALLAST_FLOW;
	int Call__TRANS_BALLAST_FLOW(CII_OBJECT__VARIABLE *p_variable);

	CString sMODE__BALLAST_CLOSE;
	int Call__BALLAST_CLOSE(CII_OBJECT__VARIABLE *p_variable);
	//

	//------------------------------------------------------------
	int Mon__STATE(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm);

	// ...
	int  Get__MFC_INDEX(const CString& gas_name);
	void Fnc__WRITE_LOG(CString msg);
	//


public:
	CObj__GAS_VLV_FNC();
	~CObj__GAS_VLV_FNC();

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
