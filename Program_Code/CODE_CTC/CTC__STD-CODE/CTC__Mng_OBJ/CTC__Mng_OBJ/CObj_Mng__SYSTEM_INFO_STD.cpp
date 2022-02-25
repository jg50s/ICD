#include "StdAfx.h"
#include "CObj_Mng__SYSTEM_INFO_STD.h"


//-------------------------------------------------------------------------
CObj_Mng__SYSTEM_INFO_STD::CObj_Mng__SYSTEM_INFO_STD()
{

}
CObj_Mng__SYSTEM_INFO_STD::~CObj_Mng__SYSTEM_INFO_STD()
{

}

//-------------------------------------------------------------------------
int CObj_Mng__SYSTEM_INFO_STD::__DEFINE__CONTROL_MODE(obj,l_mode)
{
	sObject_Name = obj;

	// ...
	{
		ADD__CTRL_VAR(sMODE__TEST_UPEH_DATA,  "TEST.UPEH_DATA");
		ADD__CTRL_VAR(sMODE__CLEAR_UPEH_DATA, "CLEAR.UPEH_DATA");
	}
	return 1;
}

int CObj_Mng__SYSTEM_INFO_STD::__DEFINE__VERSION_HISTORY(version)
{

	return 1;
}


// ...
#define  MON_ID__SYSTEM_INFO			1


int CObj_Mng__SYSTEM_INFO_STD::__DEFINE__VARIABLE_STD(p_variable)
{
	DECLARE__STD_VARIABLE;

	CString str_name;

	// ...
	{
		str_name = "CUR.DAY";
		STD__ADD_STRING_WITH_X_OPTION(str_name, "");
		LINK__VAR_STRING_CTRL(sCH__CUR_DAY, str_name);

		//
		str_name = "MON.SYS.ALARM.STATE";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_SYS_ALARM_STATE, str_name);
		
		str_name = "MON.SYS.MAINT.STATE";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_SYS_MAINT_STATE, str_name);
	}

	// ...
	{
		str_name = "1th.TOTAL_EQUIPMENT_PROCESS_TIME_SEC";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__1th_DAY__TOTAL_EQUIPMENT_PROCESS_TIME_SEC, str_name);

		str_name = "1th.TOTAL_EQUIPMENT_IDLE_TIME_SEC";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__1th_DAY__TOTAL_EQUIPMENT_IDLE_TIME_SEC, str_name);

		str_name = "1th.TOTAL_EQUIPMENT_DOWN_TIME_SEC";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__1th_DAY__TOTAL_EQUIPMENT_DOWN_TIME_SEC, str_name);
	}

	// Day : 1 ~ 3 ... 
	{
		CString str_day;

		for(int i=0; i<CFG__DAY_SIZE; i++)
		{
			     if(i == DB__1th_INDEX)			str_day = "1th";
			else if(i == DB__2th_INDEX)			str_day = "2th";
			else if(i == DB__3th_INDEX)			str_day = "3th";
			else								continue;

			// ...
			{
				str_name.Format("%s.TOTAL_LOT_COUNT", str_day);
				STD__ADD_STRING_WITH_X_OPTION(str_name, "");
				LINK__VAR_STRING_CTRL(sCH__DAYx__TOTAL_LOT_COUNT[i], str_name);

				str_name.Format("%s.TOTAL_PROCESSED_WAFER_COUNT", str_day);
				STD__ADD_STRING_WITH_X_OPTION(str_name, "");
				LINK__VAR_STRING_CTRL(sCH__DAYx__TOTAL_PROCESSED_WAFER_COUNT[i], str_name);

				//
				str_name.Format("%s.TOTAL_EQUIPMENT_PROCESS_TIME_FMT", str_day);
				STD__ADD_STRING(str_name);
				LINK__VAR_STRING_CTRL(sCH__DAYx__TOTAL_EQUIPMENT_PROCESS_TIME_FMT[i], str_name);

				str_name.Format("%s.TOTAL_EQUIPMENT_IDLE_TIME_FMT", str_day);
				STD__ADD_STRING(str_name);
				LINK__VAR_STRING_CTRL(sCH__DAYx__TOTAL_EQUIPMENT_IDLE_TIME_FMT[i], str_name);

				str_name.Format("%s.TOTAL_EQUIPMENT_DOWN_TIME_FMT", str_day);
				STD__ADD_STRING(str_name);
				LINK__VAR_STRING_CTRL(sCH__DAYx__TOTAL_EQUIPMENT_DOWN_TIME_FMT[i], str_name);
			}

			// UPEH Info ...
			for(int k=0; k<CFG__HOUR_SIZE; k++)
			{
				str_name.Format("%s.%002d.UPEH.RESULT", str_day,k+1);
				STD__ADD_STRING_WITH_X_OPTION(str_name, "");
				LINK__VAR_STRING_CTRL(sCH__DAYx__HOURx_UPEH_RESULT[i][k], str_name);
			}
		}

		// ...
		{
			str_name = "CUR.HOUR";
			STD__ADD_STRING(str_name);
			LINK__VAR_STRING_CTRL(sCH__CUR_HOUR, str_name);
		}
	}

	// ...
	{
		p_variable->Add__MONITORING_PROC(1.0, MON_ID__SYSTEM_INFO);
	}
	return 1;
}

int CObj_Mng__SYSTEM_INFO_STD::__DEFINE__ALARM(p_alarm)
{
	DECLARE__ALARM;

	// ...
	{

	}
	return 1;
}

//-------------------------------------------------------------------------
int CObj_Mng__SYSTEM_INFO_STD::__INITIALIZE__OBJECT(p_variable,p_ext_obj_create)
{
	p_ext_obj_create->Link__DEF_VARIABLE__ERROR_FEEDBACK(&mERROR__DEF_VAR);

	// ...
	{

	}
	return 1;
}

//-------------------------------------------------------------------------
int CObj_Mng__SYSTEM_INFO_STD::__CALL__CONTROL_MODE(mode,p_debug,p_variable,p_alarm)
{
	int flag = -1;

	// ...
	{
			 IF__CTRL_MODE(sMODE__TEST_UPEH_DATA)		flag = Call__TEST_UPEH_DATA(p_variable,p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__CLEAR_UPEH_DATA)		flag = Call__CLEAR_UPEH_DATA(p_variable,p_alarm);
	}
	return flag;
}
int CObj_Mng__SYSTEM_INFO_STD::__CALL__MONITORING(id,p_variable,p_alarm)
{
	switch(id)
	{
		case MON_ID__SYSTEM_INFO:
			Mon__SYSTEM_INFO(p_variable);
			break;
	}

	return 1;
}
