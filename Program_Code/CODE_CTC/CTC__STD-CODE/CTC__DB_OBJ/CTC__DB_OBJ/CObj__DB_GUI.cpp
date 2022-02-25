#include "StdAfx.h"
#include "CObj__DB_GUI.h"


//-------------------------------------------------------------------------
CObj__DB_GUI::CObj__DB_GUI()
{

}
CObj__DB_GUI::~CObj__DB_GUI()
{

}

//-------------------------------------------------------------------------
int CObj__DB_GUI::__DEFINE__CONTROL_MODE(obj,l_mode)
{
	sObject_Name = obj;

	return 1;
}
int CObj__DB_GUI::__DEFINE__VERSION_HISTORY(version)
{

	return 1;
}


// ...
#define APP_DSP__CFG_CHANGE_MODE								\
"Unchange  Change"

#define APP_DSP__CFG_SAVE_MODE									\
"Idle  Save  Undo"


int CObj__DB_GUI::__DEFINE__VARIABLE_STD(p_variable)
{
	DECLARE__STD_VARIABLE;

	// ....
	CString str_name;

	// PAGE ...
	{
		for(int i=0; i<CFG_PAGE_LIMIT; i++)
		{
			int id = i + 1;

			str_name.Format("GUI.CONFIG.CTC.PAGE%1d.SAVE", id);
			STD__ADD_DIGITAL_WITH_COMMENT(str_name, APP_DSP__CFG_CHANGE_MODE, "");
			LINK__VAR_DIGITAL_CTRL(dCH__GUI_CONFIG_CTC_PAGE_X_SAVE[i], str_name);
		}

		str_name = "GUI.CONFIG.CTC.SYS_LLx.SAVE";
		STD__ADD_DIGITAL_WITH_COMMENT(str_name, APP_DSP__CFG_CHANGE_MODE, "");

		str_name = "GUI.CONFIG.CTC.SYS_PMx.SAVE";
		STD__ADD_DIGITAL_WITH_COMMENT(str_name, APP_DSP__CFG_CHANGE_MODE, "");

		//
		str_name = "GUI.CONFIG.CTC.PAGE.AUTO_PM.SAVE";
		STD__ADD_DIGITAL_WITH_COMMENT(str_name, APP_DSP__CFG_CHANGE_MODE, "");
		LINK__VAR_DIGITAL_CTRL(dCH__GUI_CONFIG_CTC_PAGE_AUTO_PM_SAVE, str_name);

		//
		str_name = "GUI.CONFIG.FILE.CHANGE.FLAG";
		STD__ADD_STRING_WITH_COMMENT(str_name, "");
		LINK__VAR_STRING_CTRL(sCH__GUI_CONFIG_FILE_CHANGE_FLAG, str_name);
		
		str_name = "GUI.CONFIG.FILE.PATH.STRING";
		STD__ADD_STRING_WITH_COMMENT(str_name, "");
		LINK__VAR_STRING_CTRL(sCH__GUI_CONFIG_FILE_PATH_STRING, str_name);
	}

	// PORT ...
	{
		str_name = "GUI.POPUP.GEM_E84";
		STD__ADD_STRING_WITH_COMMENT(str_name, "");
		LINK__VAR_STRING_CTRL(sCH__GUI_POPUP_GEM_E84, str_name);

		for(int i=0; i<CFG_LP_LIMIT; i++)
		{
			int id = i + 1;

			str_name.Format("GUI.PORT%1d.POPUP", id);
			STD__ADD_STRING_WITH_COMMENT(str_name, "");
			LINK__VAR_STRING_CTRL(sCH__GUI_PORT_X_POPUP[i], str_name);

			str_name.Format("GUI.PORT%1d.RECIPE.POPUP", id);
			STD__ADD_STRING_WITH_COMMENT(str_name, "");
			LINK__VAR_STRING_CTRL(sCH__GUI_PORT_X_RECIPE_POPUP[i], str_name);

			str_name.Format("GUI.PORT%1d.RESYNC.POPUP", id);
			STD__ADD_STRING_WITH_COMMENT(str_name, "");
			LINK__VAR_STRING_CTRL(sCH__GUI_PORT_X_RESYNC_POPUP[i], str_name);
		}
	}

	// LPx ...
	{
		for(int i=0; i<CFG_LP_LIMIT; i++)
		{
			str_name.Format("GUI.LP%1d.MSG.POPUP", i+1);
			STD__ADD_STRING_WITH_COMMENT(str_name, "");
			LINK__VAR_STRING_CTRL(sCH__GUI_LP_X_MSG_POPUP[i], str_name);

			for(int k=0; k<CFG_LP_MSG_LIMIT; k++)
			{
				str_name.Format("GUI.LP%1d.MSG%1d", i+1,k+1);
				STD__ADD_STRING_WITH_COMMENT(str_name, "");
				LINK__VAR_STRING_CTRL(sCH__GUI_LP_X_MSG_Y[i][k], str_name);
			}
		}
	}

	// LBx ...
	{
		str_name = "GUI.LBA.RESYNC.POPUP";
		STD__ADD_STRING_WITH_COMMENT(str_name, "");
		LINK__VAR_STRING_CTRL(sCH__GUI_LBA_RESYNC_POPUP, str_name);

		str_name = "GUI.LBB.RESYNC.POPUP";
		STD__ADD_STRING_WITH_COMMENT(str_name, "");
		LINK__VAR_STRING_CTRL(sCH__GUI_LBB_RESYNC_POPUP, str_name);
	}

	// SYSTEM ...
	{
		str_name = "GUI.POPUP.HOST.MODE";
		STD__ADD_STRING_WITH_COMMENT(str_name, "");
		LINK__VAR_STRING_CTRL(sCH__GUI_POPUP_HOST_MODE, str_name);

		str_name = "GUI.SYSTEM.INIT.POPUP";
		STD__ADD_STRING_WITH_COMMENT(str_name, "");
		LINK__VAR_STRING_CTRL(sCH__GUI_SYSTEM_INIT_POPUP, str_name);

		str_name = "GUI.ROBOT.RESYNC.POPUP";
		STD__ADD_STRING_WITH_COMMENT(str_name, "");
		LINK__VAR_STRING_CTRL(sCH__GUI_ROBOT_RESYNC_POPUP, str_name);

		//
		str_name = "GUI.POPUP.SYSTEM.MESSAGE";
		STD__ADD_STRING_WITH_COMMENT(str_name, "");
		LINK__VAR_STRING_CTRL(sCH__GUI_POPUP_SYSTEM_MESSAGE, str_name);

		for(int i=0; i<CFG_SYSTEM_MSG_LIMIT; i++)
		{
			str_name.Format("GUI.SYSTEM.MSG%1d", i+1);
			STD__ADD_STRING_WITH_COMMENT(str_name, "");
			LINK__VAR_STRING_CTRL(sCH__GUI_SYSTEM_MSG_X[i], str_name);
		}
	}

	// TEST ...
	{
		str_name = "TEST.IMG_STATE";
		STD__ADD_STRING(str_name);
	}

	return 1;
}

//-------------------------------------------------------------------------
int CObj__DB_GUI::__INITIALIZE__OBJECT(p_variable,p_ext_obj_create)
{
	sCH__GUI_POPUP_GEM_E84->Set__DATA("CLOSE");

	return 1;
}

//-------------------------------------------------------------------------
int CObj__DB_GUI::__CALL__CONTROL_MODE(mode,p_debug,p_variable,p_alarm)
{

	return 1;
}
int CObj__DB_GUI::__CALL__MONITORING(id,p_variable,p_alarm)
{

	return 1;
}
