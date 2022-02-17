#pragma once

#include "Interface_Code.h"

#include "CObj__MFC_IO__ALID.h"
#include "CObj__MFC_IO__DEF.h"


class CObj__MFC_IO : public __IOBJ__INTERLOCK_TYPE
{
private:
	//-------------------------------------------------------------------------
	CString	sObject_Name;

	SCX__SEQ_INFO xI_SEQ;
	SCX__USER_LOG_CTRL xI__APP_LOG_CTRL;


	//-------------------------------------------------------------------------
	//  INTERNAL PROPERTY

	CX__VAR_STRING_CTRL sCH__OBJ_MSG;


	//-------------------------------------------------------------------------
	//  EXTERNAL PROPERTY

	// ...
	int iSIZE__MFC_OBJ;

	// DB.CFG ...
	CX__VAR_DIGITAL_CTRL  dEXT_CH__CFG_INTERLOCK_MFC_TYPE[CFG_SIZE__MFC_OBJ][CFG_INTERLOCK__MFC_SIZE];

	// MFC.INFO ...
	CStringArray sList_Channel__MFC_DO_VLV_IN;
	CStringArray sList_Channel__MFC_DO_VLV_OUT;
	CStringArray sList_Channel__MFC_DO_VLV_PURGE;

	bool bActive__MFC_DO_VLV_IN_X[CFG_SIZE__MFC_OBJ];
	CX__VAR_DIGITAL_CTRL  doEXT_CH__MFC_DO_VLV_IN_X[CFG_SIZE__MFC_OBJ];

	bool bActive__MFC_DO_VLV_OUT_X[CFG_SIZE__MFC_OBJ];
	CX__VAR_DIGITAL_CTRL  doEXT_CH__MFC_DO_VLV_OUT_X[CFG_SIZE__MFC_OBJ];

	bool bActive__MFC_DO_VLV_PURGE_X[CFG_SIZE__MFC_OBJ];
	CX__VAR_DIGITAL_CTRL  doEXT_CH__MFC_DO_VLV_PURGE_X[CFG_SIZE__MFC_OBJ];

	// LINK IO ...
	CX__VAR_DIGITAL_CTRL  diEXT_CH__GAS_BOX_CONVER;
	CString sGAS_BOX_COVER__NORMAL_STATE;
	//

	//-------------------------------------------------------------------------
	// ...
	int  Check__MFC_Interlock(const int mfc_id,CString& err_msg);
	int  Get__GAS_Index(const CString& gas_type);

	void Post_Alarm(const int alarm_id,const CString err_msg);
	//

	//-------------------------------------------------------------------------
	CString sMODE__TEST_1;
	int  Call__TEST_1(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm);

	// ...
	void Mon__MONITOR(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm);

	int  ValueLock__MFCx_Valve_Open(const int mfc_id);
	//


public:
	// SetPoint Interlock .....

	// 1. MFCx Purge Valve -> Open
	int IFnc_SetPoint__MFC1_Purge_Valve_Open();
	int IFnc_SetPoint__MFC2_Purge_Valve_Open();
	int IFnc_SetPoint__MFC3_Purge_Valve_Open();
	int IFnc_SetPoint__MFC4_Purge_Valve_Open();
	int IFnc_SetPoint__MFC5_Purge_Valve_Open();
	int IFnc_SetPoint__MFC6_Purge_Valve_Open();
	int IFnc_SetPoint__MFC7_Purge_Valve_Open();
	int IFnc_SetPoint__MFC8_Purge_Valve_Open();
	int IFnc_SetPoint__MFC9_Purge_Valve_Open();
	int IFnc_SetPoint__MFC10_Purge_Valve_Open();
	int IFnc_SetPoint__MFC11_Purge_Valve_Open();
	int IFnc_SetPoint__MFC12_Purge_Valve_Open();
	int IFnc_SetPoint__MFC13_Purge_Valve_Open();
	int IFnc_SetPoint__MFC14_Purge_Valve_Open();
	int IFnc_SetPoint__MFC15_Purge_Valve_Open();
	int IFnc_SetPoint__MFC16_Purge_Valve_Open();
	int IFnc_SetPoint__MFC17_Purge_Valve_Open();

	int SetPoint__MFCx_Purge_Valve_Open(const int mfc_id);

	// 2. MFCx Primary Valve -> Open
	int IFnc_SetPoint__MFC1_Primary_Valve_Open();
	int IFnc_SetPoint__MFC2_Primary_Valve_Open();
	int IFnc_SetPoint__MFC3_Primary_Valve_Open();
	int IFnc_SetPoint__MFC4_Primary_Valve_Open();
	int IFnc_SetPoint__MFC5_Primary_Valve_Open();
	int IFnc_SetPoint__MFC6_Primary_Valve_Open();
	int IFnc_SetPoint__MFC7_Primary_Valve_Open();
	int IFnc_SetPoint__MFC8_Primary_Valve_Open();
	int IFnc_SetPoint__MFC9_Primary_Valve_Open();
	int IFnc_SetPoint__MFC10_Primary_Valve_Open();
	int IFnc_SetPoint__MFC11_Primary_Valve_Open();
	int IFnc_SetPoint__MFC12_Primary_Valve_Open();
	int IFnc_SetPoint__MFC13_Primary_Valve_Open();
	int IFnc_SetPoint__MFC14_Primary_Valve_Open();
	int IFnc_SetPoint__MFC15_Primary_Valve_Open();
	int IFnc_SetPoint__MFC16_Primary_Valve_Open();
	int IFnc_SetPoint__MFC17_Primary_Valve_Open();

	int SetPoint__MFCx_Primary_Valve_Open(const int mfc_id);

	// 3. MFCx Secondary Valve -> Open
	int IFnc_SetPoint__MFC1_Secondary_Valve_Open();
	int IFnc_SetPoint__MFC2_Secondary_Valve_Open();
	int IFnc_SetPoint__MFC3_Secondary_Valve_Open();
	int IFnc_SetPoint__MFC4_Secondary_Valve_Open();
	int IFnc_SetPoint__MFC5_Secondary_Valve_Open();
	int IFnc_SetPoint__MFC6_Secondary_Valve_Open();
	int IFnc_SetPoint__MFC7_Secondary_Valve_Open();
	int IFnc_SetPoint__MFC8_Secondary_Valve_Open();
	int IFnc_SetPoint__MFC9_Secondary_Valve_Open();
	int IFnc_SetPoint__MFC10_Secondary_Valve_Open();
	int IFnc_SetPoint__MFC11_Secondary_Valve_Open();
	int IFnc_SetPoint__MFC12_Secondary_Valve_Open();
	int IFnc_SetPoint__MFC13_Secondary_Valve_Open();
	int IFnc_SetPoint__MFC14_Secondary_Valve_Open();
	int IFnc_SetPoint__MFC15_Secondary_Valve_Open();
	int IFnc_SetPoint__MFC16_Secondary_Valve_Open();
	int IFnc_SetPoint__MFC17_Secondary_Valve_Open();

	int SetPoint__MFCx_Secondary_Valve_Open(const int mfc_id);


public:
	CObj__MFC_IO();
	~CObj__MFC_IO();

	//-------------------------------------------------------------------------
	int __DEFINE__CONTROL_MODE(obj,l_mode);
	int __DEFINE__VERSION_HISTORY(version);

	int __DEFINE__VARIABLE_STD(p_variable);
	int __DEFINE__ALARM(p_alarm);

	int __DEFINE__UI_INTERLOCK(p_interlock);
	int __DEFINE__IO_INTERLOCK(p_interlock);

	//-------------------------------------------------------------------------
	int __INITIALIZE__OBJECT(p_variable,p_ext_obj_create);

	//-------------------------------------------------------------------------
	int __CALL__CONTROL_MODE(mode,p_debug,p_variable,p_alarm);
	int __CALL__MONITORING(id, p_variable, p_alarm);
};
