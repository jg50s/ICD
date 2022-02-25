#include "StdAfx.h"
#include "CObj_Phy__BUFFER_STD.h"


//-------------------------------------------------------------------------
CObj_Phy__BUFFER_STD::CObj_Phy__BUFFER_STD()
{

}
CObj_Phy__BUFFER_STD::~CObj_Phy__BUFFER_STD()
{

}

//-------------------------------------------------------------------------
int CObj_Phy__BUFFER_STD::__DEFINE__CONTROL_MODE(obj,l_mode)
{
	sObject_Name = obj;
	return 1;
}

int CObj_Phy__BUFFER_STD::__DEFINE__VERSION_HISTORY(version)
{

	return 1;
}


// ...
#define  APP_DSP__CST_FLAG				"EXIST  NONE"
#define  APP_DSP__USE_FLAG				"DISABLE  ENABLE"

#define  MON_ID__STATUS_CTRL			1


int CObj_Phy__BUFFER_STD::__DEFINE__VARIABLE_STD(p_variable)
{
	DECLARE__STD_VARIABLE;

	CString str_name;
	int i;
	
	// ...
	{
		str_name = "OBJ.STATUS";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__OBJ_STATUS, str_name);
	}

	// SLOTx INFO ...
	{
		CString dsp_item;
		p_variable->Get__STD_DESCRIPTION("STD_SLOT_STATUS",dsp_item);

		for(i=0; i<CFG_CLx__SLOT_MAX; i++)
		{
			str_name.Format("SLOT%002d.STATUS", i+1);
			STD__ADD_DIGITAL(str_name,dsp_item);
			LINK__VAR_DIGITAL_CTRL(xCH__SLOT_STATUS[i],str_name);

			str_name.Format("SLOT%002d.TITLE", i+1);
			STD__ADD_STRING(str_name);

			str_name.Format("SLOT%002d.WAIT.SEC", i+1);
			STD__ADD_ANALOG_WITH_COMMENT(str_name,"sec",0,0,9999,"");
			LINK__VAR_ANALOG_CTRL(xCH__SLOT_WAIT_SEC[i],str_name);
		}
	}

	// CONFIG ...
	{
		str_name = "CFG.CST.FLAG";
		STD__ADD_DIGITAL_WITH_COMMENT(str_name,APP_DSP__CST_FLAG,"");
		LINK__VAR_DIGITAL_CTRL(xCH__CFG_CST_FLAG, str_name);

		str_name = "CFG.USE.FLAG";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name,APP_DSP__USE_FLAG,"");
		LINK__VAR_DIGITAL_CTRL(xCH__CFG_USE_FLAG, str_name);

		str_name = "CFG.SLOT.MAX";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name,"slot",0,1,26,"");
		LINK__VAR_ANALOG_CTRL(xCH__CFG_SLOT_MAX, str_name);

		str_name = "CFG.SLOT.WAIT.SEC";
		STD__ADD_ANALOG_WITH_COMMENT(str_name,"sec",0,0,9999,"");
		LINK__VAR_ANALOG_CTRL(xCH__CFG_SLOT_WAIT_SEC, str_name);
	}

	// APP ...
	{
		str_name = "APP.CUR.LOTID";
		STD__ADD_STRING_WITH_COMMENT(str_name,"");
		LINK__VAR_STRING_CTRL(xCH__APP_CUR_LOTID, str_name);

		str_name = "APP.NEXT.SLOT.TO.PLACE";
		STD__ADD_ANALOG_WITH_COMMENT(str_name,"slot",0,1,30,"");
		LINK__VAR_ANALOG_CTRL(xCH__APP_NEXT_SLOT_TO_PLACE, str_name);

		str_name = "APP.NEXT.SLOT.TO.PICK";
		STD__ADD_ANALOG_WITH_COMMENT(str_name,"slot",0,1,30,"");
		LINK__VAR_ANALOG_CTRL(xCH__APP_NEXT_SLOT_TO_PICK, str_name);
	}
	
	// ...
	{
		p_variable->Add__MONITORING_PROC(10.0, MON_ID__STATUS_CTRL);
	}
	return 1;
}

int CObj_Phy__BUFFER_STD::__DEFINE__ALARM(p_alarm)
{
	DECLARE__ALARM;

	// ...
	CString title;
	title.Format("%s - ",sObject_Name);

	CString alarm_title;
	CString alarm_msg;
	CStringArray l_act;

	// ...
	ALARM_DEFINE__MODULE_OBJECT;

	// ...
	{

	}
	return 1;
}

//-------------------------------------------------------------------------
int CObj_Phy__BUFFER_STD::__INITIALIZE__OBJECT(p_variable,p_ext_obj_create)
{
	sCH__OBJ_STATUS->Set__DATA(STR__STANDBY);
	xCH__CFG_CST_FLAG->Set__DATA(STR__EXIST);
	return 1;
}

//-------------------------------------------------------------------------
int CObj_Phy__BUFFER_STD::__CALL__CONTROL_MODE(mode,p_debug,p_variable,p_alarm)
{
	int flag = -1;

	return flag;
}
int CObj_Phy__BUFFER_STD::__CALL__MONITORING(id,p_variable,p_alarm)
{
	switch(id)
	{
		case MON_ID__STATUS_CTRL:
			Mon__STATUS_CTRL(p_variable,p_alarm);
			break;
	}
	return 1;
}
