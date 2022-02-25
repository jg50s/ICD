#pragma once

#include "Interface_Code.h"
#include "CCommon_Error.h"

#include "CObj_Phy__BUFFER_STD__DEF.h"
#include "CObj_Phy__BUFFER_STD__ALID.h"


class CObj_Phy__BUFFER_STD : public __IOBJ__STD_TYPE
{
private:
	//-----------------------------------------------------
	CString sObject_Name;


	//-----------------------------------------------------
	// INTERNAL PROPERTY

	CX__VAR_STRING_CTRL  sCH__OBJ_STATUS;

	// SLOTx INFO ...
	CX__VAR_DIGITAL_CTRL xCH__SLOT_STATUS[CFG_CLx__SLOT_MAX];
	CX__VAR_ANALOG_CTRL  xCH__SLOT_WAIT_SEC[CFG_CLx__SLOT_MAX];

	// CONFIG PARAMETER ...
	CX__VAR_DIGITAL_CTRL xCH__CFG_CST_FLAG;
	CX__VAR_DIGITAL_CTRL xCH__CFG_USE_FLAG;
	CX__VAR_ANALOG_CTRL  xCH__CFG_SLOT_MAX;

	CX__VAR_ANALOG_CTRL  xCH__CFG_SLOT_WAIT_SEC;

	CX__VAR_STRING_CTRL  xCH__APP_CUR_LOTID;
	CX__VAR_ANALOG_CTRL  xCH__APP_NEXT_SLOT_TO_PLACE;
	CX__VAR_ANALOG_CTRL  xCH__APP_NEXT_SLOT_TO_PICK;
	//

	//-----------------------------------------------------
	// EXTERNAL PROPERTY

	//


	// ...
	void Mon__STATUS_CTRL(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm);
	//


public:
	CObj_Phy__BUFFER_STD();
	~CObj_Phy__BUFFER_STD();

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
