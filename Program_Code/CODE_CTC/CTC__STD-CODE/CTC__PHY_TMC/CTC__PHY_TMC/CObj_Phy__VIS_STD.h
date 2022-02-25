#pragma once

#include "Interface_Code.h"

#include "CCommon_System.h"
#include "CCommon_Error.h"

#include "CObj_Phy__VIS_STD__DEF.h"


// ...
#define  ALID__OBJECT_MODE_UNKNOWN							11
#define  ALID__MATERIAL_JUDGEMENT							23
#define  ALID__MATERIAL_JUDGEMENT_NON_BLOCKING				24


class CObj_Phy__VIS_STD : public __IOBJ__STD_TYPE
{
private:
	//-----------------------------------------------------------
	CString sObject_Name;
	int iVIS_ID;

	CCommon_Error__MODULE_OBJ mERROR__MODULE_OBJ;

	SCX__CTC__MODULE_OBJ xI_Module_Obj;
	SCX__CTC__SCH_MATERIAL_CTRL xI_SCH_MATERIAL_CTRL;
	SCX__USER_LOG_CTRL xI_LOG_CTRL;

	CString sSCH_NAME;


	//-----------------------------------------------------------
	// INTERNAL PROPERTY

	//  CONTROL  
	CX__VAR_DIGITAL_CTRL xCH__OBJ_CTRL;
	CString dVAR__MODE;

	//  STATUS   
	CX__VAR_DIGITAL_CTRL xCH__OBJ_STATUS;

	CX__VAR_DIGITAL_CTRL xCH__CFG_DUAL_SLOT_USE_FLAG;
	CX__VAR_DIGITAL_CTRL xCH__SLOT_NO;
	CX__VAR_DIGITAL_CTRL xCH__SLOT_STATUS[CFG_VIS__SLOT_MAX];
	CX__VAR_STRING_CTRL  xCH__SLOT_TITLE[CFG_VIS__SLOT_MAX];

	CX__VAR_STRING_CTRL  xCH__RECIPE;
	CX__VAR_STRING_CTRL  xCH__LOTID;
	CX__VAR_STRING_CTRL  xCH__MATERIALID;
	CX__VAR_STRING_CTRL  xCH__PORTID;
	CX__VAR_STRING_CTRL  xCH__SLOTID;
	CX__VAR_STRING_CTRL  xCH__PM_NAME;
	CX__VAR_STRING_CTRL  xCH__PM_ID;
	CX__VAR_STRING_CTRL  xCH__JUDGMENT;

	CX__VAR_STRING_CTRL  xCH__PICK_READY_FLAG;

	//  CFG
	CX__VAR_DIGITAL_CTRL xCH_CFG__USE;						// DISABLE  ENABLE
	CX__VAR_DIGITAL_CTRL xCH_CFG__RECIPE_MODE;				// ROUTE  CONFIG
	CX__VAR_DIGITAL_CTRL xCH_CFG__VISIT_MODE;				// ROUTE  CONFIG
	CX__VAR_DIGITAL_CTRL xCH_CFG__ALARM_BLOCKING_FLAG;		// DISABLE  ENABLE

	CX__VAR_STRING_CTRL  xCH_CFG__CONFIG_RECIPE;
	CX__VAR_STRING_CTRL  xCH_CFG__RECIPE_UPLOAD_REQ;
	CX__VAR_STRING_CTRL  xCH_CFG__RECIPE_LIST;
	CX__VAR_DIGITAL_CTRL xCH_CFG__SLOT_VISIT_LIST[CFG_LP__SLOT_MAX];
	//

	//-----------------------------------------------------------
	SCI__THREAD_SYNC_CTRL xI_Sync_Ctrl;
	int iPRC_STS;

	// ...
	CString sMODE__PLACE_READY;
	int  Call__PLACE_READY(CII_OBJECT__VARIABLE* p_variable);

	CString sMODE__PLACE_COMPLETE;
	int  Call__PLACE_COMPLETE(CII_OBJECT__VARIABLE* p_variable);

	CString sMODE__PICK_READY;
	int  Call__PICK_READY(CII_OBJECT__VARIABLE* p_variable);

	CString sMODE__PICK_COMPLETE;
	int  Call__PICK_COMPLETE(CII_OBJECT__VARIABLE* p_variable);

	CString sMODE__PRO_READY;
	int  Call__PRO_READY(CII_OBJECT__VARIABLE* p_variable);

	CString sMODE__PRO_START;
	int  Call__PRO_START(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm);
	int  Sub__PRO_START(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm);

	CString sMODE__AUTO_PRO;
	int  Call__AUTO_PRO(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm);

	CString sMODE__AUTO_PRO_EX;
	int  Call__AUTO_PRO_EX(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm);

	CString sMODE__EXCHANGE_READY;
	int  Call__EXCHANGE_READY(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm);

	void Set__Prc_Ready_Parameter(CII_OBJECT__VARIABLE *p_variable);
	//

	// ...
	void Mon__All_State(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm);
	//


public:
	CObj_Phy__VIS_STD();
	~CObj_Phy__VIS_STD();

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
