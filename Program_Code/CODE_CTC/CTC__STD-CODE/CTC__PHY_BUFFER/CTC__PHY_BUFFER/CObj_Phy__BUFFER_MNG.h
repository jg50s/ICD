#pragma once

#include "Interface_Code.h"
#include "CCommon_Error.h"

#include "CObj_Phy__BUFFER_MNG__DEF.h"
#include "CObj_Phy__BUFFER_MNG__ALID.h"


// ...
#define _DEF_SIZE__BUFFER_MAX				2


class CObj_Phy__BUFFER_MNG : public __IOBJ__STD_TYPE
{
private:
	//-----------------------------------------------------
	CString sObject_Name;


	//-----------------------------------------------------
	// INTERNAL PROPERTY

	CX__VAR_STRING_CTRL  sCH__OBJ_STATUS;
	CX__VAR_STRING_CTRL  sCH__SEL_BUFFER;

	// SLOTx INFO ...
	CX__VAR_STRING_CTRL  sCH__SLOT_STATUS[CFG_CLx__SLOT_MAX];
	CX__VAR_STRING_CTRL  sCH__SLOT_TITLE[CFG_CLx__SLOT_MAX];
	CX__VAR_STRING_CTRL  sCH__SLOT_WAIT_SEC[CFG_CLx__SLOT_MAX];

	// PARAMETER ...
	CX__VAR_STRING_CTRL  sCH__CFG_SLOT_MAX;
	CX__VAR_STRING_CTRL  sCH__CFG_CST_FLAG;

	CX__VAR_STRING_CTRL  sCH__APP_CUR_LOTID;
	CX__VAR_STRING_CTRL  sCH__APP_NEXT_SLOT_TO_PLACE;
	CX__VAR_STRING_CTRL  sCH__APP_NEXT_SLOT_TO_PICK;
	//

	//-----------------------------------------------------
	// EXTERNAL PROPERTY

	int iSIZE__BUFFERx;
	CII_EXT_OBJECT__CTRL *pOBJ_CTRL__BUFFERx[_DEF_SIZE__BUFFER_MAX];

	CX__VAR_STRING_CTRL  sEXT_CH__CFG_SLOT_MAX[_DEF_SIZE__BUFFER_MAX];
	CX__VAR_STRING_CTRL  sEXT_CH__CFG_CST_FLAG[_DEF_SIZE__BUFFER_MAX];

	CX__VAR_STRING_CTRL  sEXT_CH__APP_CUR_LOTID[_DEF_SIZE__BUFFER_MAX];
	CX__VAR_STRING_CTRL  sEXT_CH__APP_NEXT_SLOT_TO_PLACE[_DEF_SIZE__BUFFER_MAX];
	CX__VAR_STRING_CTRL  sEXT_CH__APP_NEXT_SLOT_TO_PICK[_DEF_SIZE__BUFFER_MAX];

	CX__VAR_STRING_CTRL  sEXT_CH__SLOT_STATUS_X[_DEF_SIZE__BUFFER_MAX][CFG_CLx__SLOT_MAX];
	CX__VAR_STRING_CTRL  sEXT_CH__SLOT_TITLE_X[_DEF_SIZE__BUFFER_MAX][CFG_CLx__SLOT_MAX];
	CX__VAR_STRING_CTRL  sEXT_CH__SLOT_WAIT_SEC_X[_DEF_SIZE__BUFFER_MAX][CFG_CLx__SLOT_MAX];
	//


	// ...
	void Mon__STATUS_CTRL(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm);
	//


public:
	CObj_Phy__BUFFER_MNG();
	~CObj_Phy__BUFFER_MNG();

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
