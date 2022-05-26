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
#define APP_DSP__CHANGE_FLAG				\
"Unchange  Change"

#define APP_DSP__SAVE_FLAG					\
"Idle  Save  Undo"


int CObj__DB_GUI::__DEFINE__VARIABLE_STD(p_variable)
{
	DECLARE__STD_VARIABLE;

	CCommon_Error__DEF_VARIABLE m_err_def_variable;
	p_variable->Link__DEF_VARIABLE__ERROR_FEEDBACK(&m_err_def_variable);

	// ...
	CString str_name;

	// GUI Channel ...
	{
		str_name = "GUI.PMC.POPUP";
		STD__ADD_STRING(str_name);

		str_name = "GUI.PMC.INIT.POPUP";
		STD__ADD_STRING(str_name);

		str_name = "GUI.PMC.MNT.PUMP.POPUP1";
		STD__ADD_STRING(str_name);

		str_name = "GUI.PMC.MNT.PUMP.POPUP2";
		STD__ADD_STRING(str_name);

		str_name = "GUI.PMC.APC.POPUP";
		STD__ADD_STRING(str_name);

		str_name = "GUI.PMC.CHILLER.POPUP";
		STD__ADD_STRING(str_name);

		str_name = "GUI.PMC.ESC.POPUP";
		STD__ADD_STRING(str_name);

		str_name = "GUI.PMC.WAP.POPUP";
		STD__ADD_STRING(str_name);

		str_name = "GUI.PMC.TEMP.CTRL.POPUP";
		STD__ADD_STRING(str_name);

		str_name = "GUI.PMC.IO.POPUP";
		STD__ADD_STRING(str_name);

		str_name = "GUI.PMC.RF.POPUP";
		STD__ADD_STRING(str_name);

		str_name = "GUI.PMC.RF.IO.POPUP";
		STD__ADD_STRING(str_name);

		str_name = "GUI.PMC.MATCH.POPUP";
		STD__ADD_STRING(str_name);

		// ...
		int i_limit = 3;
		int i;

		for(i=0; i<i_limit; i++)
		{
			int id = i + 1;

			str_name.Format("GUI.PMC.AI.POPUP%1d", id);
			STD__ADD_STRING(str_name);

			str_name.Format("GUI.PMC.AO.POPUP%1d", id);
			STD__ADD_STRING(str_name);

			str_name.Format("GUI.PMC.DI.POPUP%1d", id);
			STD__ADD_STRING(str_name);

			str_name.Format("GUI.PMC.DO.POPUP%1d", id);
			STD__ADD_STRING(str_name);
		}
	}

	// Config Channel ...
	{	
		str_name = "GUI.CONFIG.MODULE.SAVE";
		STD__ADD_DIGITAL(str_name, APP_DSP__CHANGE_FLAG);

		str_name = "GUI.CONFIG.MODULE_PRESSURE.SAVE";
		STD__ADD_DIGITAL(str_name, APP_DSP__CHANGE_FLAG);

		str_name = "GUI.CONFIG.MODULE_PUMP.SAVE";
		STD__ADD_DIGITAL(str_name, APP_DSP__CHANGE_FLAG);

		//
		str_name = "GUI.CONFIG.GAS_MFC.SAVE";
		STD__ADD_DIGITAL(str_name, APP_DSP__CHANGE_FLAG);

		str_name = "GUI.CONFIG.GAS_PT.SAVE";
		STD__ADD_DIGITAL(str_name, APP_DSP__CHANGE_FLAG);

		str_name = "GUI.CONFIG.GAS_INTERLOCK.SAVE";
		STD__ADD_DIGITAL(str_name, APP_DSP__CHANGE_FLAG);

		str_name = "GUI.CONFIG.GAS_OTHER.SAVE";
		STD__ADD_DIGITAL(str_name, APP_DSP__CHANGE_FLAG);

		//
		str_name = "GUI.CONFIG.DGF.SAVE";
		STD__ADD_DIGITAL(str_name, APP_DSP__CHANGE_FLAG);

		//
		str_name = "GUI.CONFIG.RF.SAVE";
		STD__ADD_DIGITAL(str_name, APP_DSP__CHANGE_FLAG);

		str_name = "GUI.CONFIG.PRESSURE.SAVE";
		STD__ADD_DIGITAL(str_name, APP_DSP__CHANGE_FLAG);

		str_name = "GUI.CONFIG.ESC.SAVE";
		STD__ADD_DIGITAL(str_name, APP_DSP__CHANGE_FLAG);

		str_name = "GUI.CONFIG.ETC.SAVE";
		STD__ADD_DIGITAL(str_name, APP_DSP__CHANGE_FLAG);

		str_name = "GUI.CONFIG.EPD.SAVE";
		STD__ADD_DIGITAL(str_name, APP_DSP__CHANGE_FLAG);

		// Shower-Head ...
		str_name = "GUI.CONFIG.HEATER_SH_STABLE.SAVE";
		STD__ADD_DIGITAL(str_name, APP_DSP__CHANGE_FLAG);

		str_name = "GUI.CONFIG.HEATER_SH_INIT.SAVE";
		STD__ADD_DIGITAL(str_name, APP_DSP__CHANGE_FLAG);

		//
		str_name = "GUI.CONFIG.HEATER_CHUCK_STABLE.SAVE";
		STD__ADD_DIGITAL(str_name, APP_DSP__CHANGE_FLAG);

		str_name = "GUI.CONFIG.HEATER_CHUCK_INIT.SAVE";
		STD__ADD_DIGITAL(str_name, APP_DSP__CHANGE_FLAG);

		//
		str_name = "GUI.CONFIG.HEATER_WALL_STABLE.SAVE";
		STD__ADD_DIGITAL(str_name, APP_DSP__CHANGE_FLAG);

		str_name = "GUI.CONFIG.HEATER_WALL_INIT.SAVE";
		STD__ADD_DIGITAL(str_name, APP_DSP__CHANGE_FLAG);

		//
		str_name = "GUI.CONFIG.HEATER_OTHER_STABLE.SAVE";
		STD__ADD_DIGITAL(str_name, APP_DSP__CHANGE_FLAG);

		str_name = "GUI.CONFIG.HEATER_OTHER_INIT.SAVE";
		STD__ADD_DIGITAL(str_name, APP_DSP__CHANGE_FLAG);

		//
		str_name = "GUI.CONFIG.ESC_HELIUM.SAVE";
		STD__ADD_DIGITAL(str_name, APP_DSP__CHANGE_FLAG);

		str_name = "GUI.CONFIG.CHUCK_STEP.SAVE";
		STD__ADD_DIGITAL(str_name, APP_DSP__CHANGE_FLAG);

		str_name = "GUI.CONFIG.DECHUCK_STEP.SAVE";
		STD__ADD_DIGITAL(str_name, APP_DSP__CHANGE_FLAG);

		//
		str_name = "GUI.CONFIG.IO.INTERLOCK.SAVE";
		STD__ADD_DIGITAL(str_name, APP_DSP__CHANGE_FLAG);

		str_name = "GUI.CONFIG.IO.INTERLOCK_MFC.SAVE";
		STD__ADD_DIGITAL(str_name, APP_DSP__CHANGE_FLAG);

		str_name = "GUI.CONFIG.WAP_PID.SAVE";
		STD__ADD_DIGITAL(str_name, APP_DSP__CHANGE_FLAG);
	}

	// RCP Channel ...
	{
		str_name = "GUI.RECIPE.PMC.NAME";
		STD__ADD_STRING_WITH_X_OPTION(str_name, "");

		str_name = "GUI.RECIPE.ALD.NAME";
		STD__ADD_STRING_WITH_X_OPTION(str_name, "");

		//
		str_name = "GUI.RECIPE.PMC.SAVE";
		STD__ADD_DIGITAL(str_name, APP_DSP__CHANGE_FLAG);

		str_name = "GUI.RECIPE.PMC.ACT.SAVE";
		STD__ADD_DIGITAL(str_name, APP_DSP__SAVE_FLAG);

		str_name = "GUI.RECIPE.ALD.SAVE";
		STD__ADD_DIGITAL(str_name, APP_DSP__CHANGE_FLAG);

		str_name = "GUI.RECIPE.ALD.ACT.SAVE";
		STD__ADD_DIGITAL(str_name, APP_DSP__SAVE_FLAG);
	}

	return 1;
}

//-------------------------------------------------------------------------
int CObj__DB_GUI::__INITIALIZE__OBJECT(p_variable,p_ext_obj_create)
{	
	return 1;
}

//-------------------------------------------------------------------------
int CObj__DB_GUI::__CALL__CONTROL_MODE(mode,p_debug,p_variable,p_alarm)
{
	return -1;
}

int CObj__DB_GUI::__CALL__MONITORING(id,p_variable,p_alarm)
{
	return 1;
}
