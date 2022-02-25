#pragma once

#include "Interface_Code.h"
#include "CCommon_System.h"


#define CFG_PAGE_LIMIT					10
#define CFG_LP_MSG_LIMIT				3
#define CFG_SYSTEM_MSG_LIMIT			3


class CObj__DB_GUI : public __IOBJ__STD_TYPE
{
private:
	//-------------------------------------------------------------------------
	CString sObject_Name;


	//-------------------------------------------------------------------------
	//  INTERNAL PROPERTY

	// CONFIG PAGE ...
	CX__VAR_DIGITAL_CTRL dCH__GUI_CONFIG_CTC_PAGE_X_SAVE[CFG_PAGE_LIMIT];
	CX__VAR_DIGITAL_CTRL dCH__GUI_CONFIG_CTC_PAGE_AUTO_PM_SAVE;

	CX__VAR_STRING_CTRL  sCH__GUI_CONFIG_FILE_CHANGE_FLAG;
	CX__VAR_STRING_CTRL  sCH__GUI_CONFIG_FILE_PATH_STRING;

	// PORT ...
	CX__VAR_STRING_CTRL  sCH__GUI_POPUP_GEM_E84;

	CX__VAR_STRING_CTRL  sCH__GUI_PORT_X_POPUP[CFG_LP_LIMIT];
	CX__VAR_STRING_CTRL  sCH__GUI_PORT_X_RECIPE_POPUP[CFG_LP_LIMIT];
	CX__VAR_STRING_CTRL  sCH__GUI_PORT_X_RESYNC_POPUP[CFG_LP_LIMIT];

	// LPx ...
	CX__VAR_STRING_CTRL  sCH__GUI_LP_X_MSG_POPUP[CFG_LP_LIMIT];
	CX__VAR_STRING_CTRL  sCH__GUI_LP_X_MSG_Y[CFG_LP_LIMIT][CFG_LP_MSG_LIMIT];

	// LBx ...
	CX__VAR_STRING_CTRL  sCH__GUI_LBA_RESYNC_POPUP;
	CX__VAR_STRING_CTRL  sCH__GUI_LBB_RESYNC_POPUP;

	// SYSTEM ...
	CX__VAR_STRING_CTRL  sCH__GUI_POPUP_HOST_MODE;
	CX__VAR_STRING_CTRL  sCH__GUI_SYSTEM_INIT_POPUP;

	CX__VAR_STRING_CTRL  sCH__GUI_ROBOT_RESYNC_POPUP;     

	CX__VAR_STRING_CTRL  sCH__GUI_POPUP_SYSTEM_MESSAGE;
	CX__VAR_STRING_CTRL  sCH__GUI_SYSTEM_MSG_X[CFG_SYSTEM_MSG_LIMIT];
	//

public:
	CObj__DB_GUI();
	~CObj__DB_GUI();

	//-------------------------------------------------------------------------
	int __DEFINE__CONTROL_MODE(obj,l_mode);
	int __DEFINE__VERSION_HISTORY(version);

	int __DEFINE__VARIABLE_STD(p_variable);

	//-------------------------------------------------------------------------
	int __INITIALIZE__OBJECT(p_variable,p_ext_obj_create);

	//-------------------------------------------------------------------------
	int __CALL__CONTROL_MODE(mode,p_debug,p_variable,p_alarm);
	int __CALL__MONITORING(id,p_variable,p_alarm);
};
