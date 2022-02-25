#pragma once

#include "Interface_Code.h"

#include "CCommon_Error.h"
#include "CCommon_System.h"


#define  ALID__OBJECT_MODE_UNKNOWN					11


class CObj_Phy__ALx_STD : public __IOBJ__STD_TYPE
{
private:
	//-----------------------------------------------------
	CString sObject_Name;

	CCommon_Error__MODULE_OBJ mERROR__MODULE_OBJ;

	// ...
	SCX__CTC__MODULE_OBJ  xI_Module_Obj;
	SCX__CTC__SCH_MATERIAL_CTRL xI_SCH_MATERIAL_CTRL;
	SCX__USER_LOG_CTRL xI_LOG_CTRL;
	//

	
	//-----------------------------------------------------
	// INTERNAL PROPERTY

	// CONTROL   
	CX__VAR_DIGITAL_CTRL xCH__OBJ_CTRL;
	CString dVAR__MODE;

	// STATUS    
	CX__VAR_DIGITAL_CTRL xCH__OBJ_STATUS;

	CX__VAR_STRING_CTRL xCH__PARA_SLOT;
	CX__VAR_STRING_CTRL xCH__PARA_MATERIAL_TYPE;
	CX__VAR_STRING_CTRL xCH__PARA_MODULE_TYPE;	

	CX__VAR_DIGITAL_CTRL xCH__SLOT_STATUS[CFG_AL__SLOT_MAX];
	CX__VAR_STRING_CTRL  xCH__SLOT_TITLE[CFG_AL__SLOT_MAX];

	CString sVAR__SLOT_MATERIAL_SIZE[CFG_AL__SLOT_MAX];

	CX__VAR_STRING_CTRL xCH__ALIGN_RETRY_FLAG;

	// CONFIG PAGE
	CX__VAR_DIGITAL_CTRL xCH__CFG_USE_FLAG;
	CX__VAR_DIGITAL_CTRL xCH__CFG_APPLY_MODE;

	CX__VAR_DIGITAL_CTRL xCH__CFG_PROTOCOL__PICK_READY;
	CX__VAR_DIGITAL_CTRL xCH__CFG_PROTOCOL__PICK_COMPLETE;

	CX__VAR_DIGITAL_CTRL xCH__CFG_PROTOCOL__PLACE_READY;
	CX__VAR_DIGITAL_CTRL xCH__CFG_PROTOCOL__PLACE_COMPLETE;

	// SIM CFG ...
	CX__VAR_ANALOG_CTRL  aCH__SCH_TEST_CFG_INIT_SEC;
	CX__VAR_ANALOG_CTRL  aCH__SCH_TEST_CFG_ALIGN_SEC;
	CX__VAR_ANALOG_CTRL  aCH__SCH_TEST_CFG_PICK_READY_SEC;
	CX__VAR_ANALOG_CTRL  aCH__SCH_TEST_CFG_PICK_COMPLETE_SEC;
	CX__VAR_ANALOG_CTRL  aCH__SCH_TEST_CFG_PLACE_READY_SEC;
	CX__VAR_ANALOG_CTRL  aCH__SCH_TEST_CFG_PLACE_COMPLETE_SEC;

	// TMC LINK ...
	CX__VAR_STRING_CTRL  sCH__LINK_CCD_POS;
	//

	//-----------------------------------------------------
	// EXTERNAL PROPERTY

	CString sSCH_NAME;

	CX__VAR_DIGITAL_CTRL dEXT_CH__SCH_TEST_CFG_TMC_DUMMY_BY_CTC;
	//


	//-----------------------------------------------------
	SCI__THREAD_SYNC_CTRL xI_Sync_Ctrl;
	int iPRC_STS;

	// ...
	CString sMODE__INIT;
	int  Call__INIT(CII_OBJECT__VARIABLE* p_variable);

	CString sMODE__ALIGN;
	int  Call__ALIGN(CII_OBJECT__VARIABLE* p_variable);

	CString sMODE__PICK_READY;
	int  Call__PICK_READY(CII_OBJECT__VARIABLE* p_variable);

	CString sMODE__PICK_COMPLETE;
	int  Call__PICK_COMPLETE(CII_OBJECT__VARIABLE* p_variable);

	CString sMODE__PLACE_READY;
	int  Call__PLACE_READY(CII_OBJECT__VARIABLE* p_variable);

	CString sMODE__PLACE_COMPLETE;
	int  Call__PLACE_COMPLETE(CII_OBJECT__VARIABLE* p_variable);

	void Set__PARAMETER(CII_OBJECT__VARIABLE* p_variable);
	//

	// ...
	int Fnc__MODULE_OBJ(CII_OBJECT__VARIABLE* p_variable,
						const CString obj_mode);
	int Sim__MODULE_OBJ(CII_OBJECT__VARIABLE* p_variable,
						const CString obj_mode);

	int Fnc__WAIT_SEC(CII_OBJECT__VARIABLE* p_variable,
					  CII__VAR_ANALOG_CTRL* pch_analog_cfg);
	//

	// ...
	void Mon__MODULE_STATUS(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm);
	//


public:
	CObj_Phy__ALx_STD();
	~CObj_Phy__ALx_STD();

	//-------------------------------------------------------------------------
	int __DEFINE__CONTROL_MODE(obj,l_mode);
	int __DEFINE__VERSION_HISTORY(version);

	int __DEFINE__VARIABLE_STD(p_variable);
	int __DEFINE__ALARM(p_alarm);

	//-------------------------------------------------------------------------
	int __INITIALIZE__OBJECT(p_variable,p_ext_obj_create);
	int __START__OBJECT();

	//-------------------------------------------------------------------------
	int __CALL__CONTROL_MODE(mode,p_debug,p_variable,p_alarm);
	int __CALL__MONITORING(id,p_variable,p_alarm);
};
