#include "StdAfx.h"
#include "CObj_Phy__BUFFER_MNG.h"


//-------------------------------------------------------------------------
CObj_Phy__BUFFER_MNG::CObj_Phy__BUFFER_MNG()
{

}
CObj_Phy__BUFFER_MNG::~CObj_Phy__BUFFER_MNG()
{

}

//-------------------------------------------------------------------------
int CObj_Phy__BUFFER_MNG::__DEFINE__CONTROL_MODE(obj,l_mode)
{
	sObject_Name = obj;
	return 1;
}

int CObj_Phy__BUFFER_MNG::__DEFINE__VERSION_HISTORY(version)
{

	return 1;
}


// ...
#define  MON_ID__STATUS_CTRL			1


int CObj_Phy__BUFFER_MNG::__DEFINE__VARIABLE_STD(p_variable)
{
	DECLARE__STD_VARIABLE;

	CString str_name;
	int i;

	// ...
	{
		str_name = "OBJ.STATUS";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__OBJ_STATUS, str_name);

		//
		str_name = "SEL.BUFFER";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__SEL_BUFFER, str_name);
	}

	// SLOTx INFO ...
	{
		for(i=0; i<CFG_CLx__SLOT_MAX; i++)
		{
			str_name.Format("SLOT%002d.STATUS", i+1);
			STD__ADD_STRING(str_name);
			LINK__VAR_STRING_CTRL(sCH__SLOT_STATUS[i], str_name);

			str_name.Format("SLOT%002d.TITLE", i+1);
			STD__ADD_STRING(str_name);
			LINK__VAR_STRING_CTRL(sCH__SLOT_TITLE[i], str_name);

			str_name.Format("SLOT%002d.WAIT.SEC", i+1);
			STD__ADD_STRING(str_name);
			LINK__VAR_STRING_CTRL(sCH__SLOT_WAIT_SEC[i], str_name);
		}
	}

	// PARAMETER ...
	{
		str_name = "CFG.SLOT.MAX";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__CFG_SLOT_MAX, str_name);

		str_name = "CFG.CST.FLAG";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__CFG_CST_FLAG, str_name);

		//
		str_name = "APP.CUR.LOTID";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__APP_CUR_LOTID, str_name);

		str_name = "APP.NEXT.SLOT.TO.PLACE";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__APP_NEXT_SLOT_TO_PLACE, str_name);

		str_name = "APP.NEXT.SLOT.TO.PICK";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__APP_NEXT_SLOT_TO_PICK, str_name);
	}

	// ...
	{
		p_variable->Add__MONITORING_PROC(10.0, MON_ID__STATUS_CTRL);
	}
	return 1;
}

int CObj_Phy__BUFFER_MNG::__DEFINE__ALARM(p_alarm)
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
int CObj_Phy__BUFFER_MNG::__INITIALIZE__OBJECT(p_variable,p_ext_obj_create)
{
	CString def_name;
	CString def_data;
	CString obj_name;
	CString var_name;

	// ...
	{
		def_name = "BUFFER_SIZE";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, def_data);
		iSIZE__BUFFERx = atoi(def_data);
		if(iSIZE__BUFFERx > _DEF_SIZE__BUFFER_MAX)
			iSIZE__BUFFERx = _DEF_SIZE__BUFFER_MAX;

		int i_limit = iSIZE__BUFFERx;
		int i;

		for(i=0; i<i_limit; i++)
		{
			def_name.Format("OBJ__SIDE_BUFFER%1d", i+1);
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name, obj_name);

			pOBJ_CTRL__BUFFERx[i] = p_ext_obj_create->Create__OBJECT_CTRL(obj_name);

			int k_limit = CFG_CLx__SLOT_MAX;
			int k;

			for(k=0; k<k_limit; k++)
			{
				int id = k + 1;

				var_name.Format("SLOT%002d.STATUS", id);
				LINK__EXT_VAR_STRING_CTRL(sEXT_CH__SLOT_STATUS_X[i][k], obj_name,var_name);

				var_name.Format("SLOT%002d.TITLE", id);
				LINK__EXT_VAR_STRING_CTRL(sEXT_CH__SLOT_TITLE_X[i][k], obj_name,var_name);

				var_name.Format("SLOT%002d.WAIT.SEC", id);
				LINK__EXT_VAR_STRING_CTRL(sEXT_CH__SLOT_WAIT_SEC_X[i][k], obj_name,var_name);
			}

			// PARAMETER ...
			var_name = "CFG.SLOT.MAX";
			LINK__EXT_VAR_STRING_CTRL(sEXT_CH__CFG_SLOT_MAX[i], obj_name,var_name);

			var_name = "CFG.CST.FLAG";
			LINK__EXT_VAR_STRING_CTRL(sEXT_CH__CFG_CST_FLAG[i], obj_name,var_name);

			//
			var_name = "APP.CUR.LOTID";
			LINK__EXT_VAR_STRING_CTRL(sEXT_CH__APP_CUR_LOTID[i], obj_name,var_name);

			var_name = "APP.NEXT.SLOT.TO.PLACE";
			LINK__EXT_VAR_STRING_CTRL(sEXT_CH__APP_NEXT_SLOT_TO_PLACE[i], obj_name,var_name);

			var_name = "APP.NEXT.SLOT.TO.PICK";
			LINK__EXT_VAR_STRING_CTRL(sEXT_CH__APP_NEXT_SLOT_TO_PICK[i], obj_name,var_name);
		}
	}

	// ...
	{
		sCH__SEL_BUFFER->Set__DATA("BUFFER1");
	}
	return 1;
}

//-------------------------------------------------------------------------
int CObj_Phy__BUFFER_MNG::__CALL__CONTROL_MODE(mode,p_debug,p_variable,p_alarm)
{
	int flag = -1;

	return flag;
}
int CObj_Phy__BUFFER_MNG::__CALL__MONITORING(id,p_variable,p_alarm)
{
	switch(id)
	{
		case MON_ID__STATUS_CTRL:
			Mon__STATUS_CTRL(p_variable,p_alarm);
			break;
	}
	return 1;
}
