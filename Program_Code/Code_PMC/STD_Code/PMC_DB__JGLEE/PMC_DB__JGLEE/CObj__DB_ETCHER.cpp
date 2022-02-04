#include "StdAfx.h"
#include "CObj__DB_ETCHER.h"


//-------------------------------------------------------------------------
CObj__DB_ETCHER::CObj__DB_ETCHER()
{

}
CObj__DB_ETCHER::~CObj__DB_ETCHER()
{

}

//-------------------------------------------------------------------------
int CObj__DB_ETCHER::__DEFINE__CONTROL_MODE(obj,l_mode)
{
	sObject_Name = obj;

	// ...
	{
		ADD__CTRL_VAR(sMODE__DB_CHECK, "DB_CHECK");
	}
	return 1;
}
int CObj__DB_ETCHER::__DEFINE__VERSION_HISTORY(version)
{

	return 1;
}

int CObj__DB_ETCHER::__DEFINE__VARIABLE_STD(p_variable)
{
	DECLARE__STD_VARIABLE;

	// ...
	CString str_name;

	// SYSTEM CHANNEL ...
	{
		str_name = "SYS.CHM.VOLUMN";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "L", 1, 0.1, 100, "");
		LINK__VAR_ANALOG_CTRL(aCH__SYS_CHM_VOLUMN,str_name);

		str_name = "SYS.CHM.TEMPERATURE";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "C", 1, 0.0, 200, "");
		LINK__VAR_ANALOG_CTRL(aCH__SYS_CHM_TEMPERATURE,str_name);

		//
		str_name = "SYS.CTRL.NAME";
		STD__ADD_STRING_WITH_COMMENT(str_name, "");
		LINK__VAR_STRING_CTRL(sCH__SYS_CTRL_NAME,str_name);
	
		str_name = "SYS.CTRL.MSG";
		STD__ADD_STRING_WITH_COMMENT(str_name, "");
		LINK__VAR_STRING_CTRL(sCH__SYS_CTRL_MSG,str_name);

		str_name = "SYS.CTRL.LOCK";
		STD__ADD_STRING_WITH_COMMENT(str_name, "");
		LINK__VAR_STRING_CTRL(sCH__SYS_CTRL_LOCK,str_name);

		str_name = "SYS.ALWAYS.LOCK.FLAG";
		STD__ADD_STRING_WITH_COMMENT(str_name, "");
		LINK__VAR_STRING_CTRL(sCH__SYS_ALWAYS_LOCK_FLAG,str_name);

		//
		str_name = "SYS.FNC.NAME";
		STD__ADD_STRING_WITH_COMMENT(str_name, "");
		LINK__VAR_STRING_CTRL(sCH__SYS_FNC_NAME,str_name);
	
		str_name = "SYS.FNC.MSG";
		STD__ADD_STRING_WITH_COMMENT(str_name, "");
		LINK__VAR_STRING_CTRL(sCH__SYS_FNC_MSG,str_name);

		str_name = "SYS.FNC.CATEGORY";
		STD__ADD_STRING_WITH_COMMENT(str_name, "");
		LINK__VAR_STRING_CTRL(sCH__SYS_FNC_CATEGORY,str_name);

		str_name = "SYS.FNC.LOCK";
		STD__ADD_STRING_WITH_COMMENT(str_name, "");
		LINK__VAR_STRING_CTRL(sCH__SYS_FNC_LOCK,str_name);
	}
	
	// RECIPE PARAMETER RANGE ...
	{
		str_name = "RCP.EPD.TRIGGER.MIN";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name,"%",0,-200,100,"");
		LINK__VAR_ANALOG_CTRL(aCH_RCP__EPD_TRIGGER_MIN,str_name);

		str_name = "RCP.EPD.TRIGGER.MAX";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name,"%",0,-100,200,"");
		LINK__VAR_ANALOG_CTRL(aCH_RCP__EPD_TRIGGER_MAX,str_name);

		str_name = "RCP.EPD.TRIGGER.DEC";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name,"dec",0,0,3,"");
		LINK__VAR_ANALOG_CTRL(aCH_RCP__EPD_TRIGGER_DEC,str_name);
	}

	return 1;
}
int CObj__DB_ETCHER::__DEFINE__ALARM(p_alarm)
{
	DECLARE__ALARM;

	return 1;
}

//-------------------------------------------------------------------------
int CObj__DB_ETCHER::__INITIALIZE__OBJECT(p_variable,p_ext_obj_create)
{
	
	sCH__SYS_ALWAYS_LOCK_FLAG->Set__DATA("YES");
	return 1;
}

//-------------------------------------------------------------------------
int CObj__DB_ETCHER::__CALL__CONTROL_MODE(mode,p_debug,p_variable,p_alarm)
{
	int flag = -1;

	// ...
	{
		IF__CTRL_MODE(sMODE__DB_CHECK)		flag = Call__DB_CHECK(p_variable,p_alarm);
	}

	return flag;
}
int CObj__DB_ETCHER::__CALL__MONITORING(id,p_variable,p_alarm)
{

	return 1;
}
