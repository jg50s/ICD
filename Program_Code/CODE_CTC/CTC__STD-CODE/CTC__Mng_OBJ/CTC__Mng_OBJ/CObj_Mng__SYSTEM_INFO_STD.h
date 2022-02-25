#pragma once

#include "Interface_Code.h"
#include "CCommon_Error.h"

#include "CObj_Mng__SYSTEM_INFO_STD__DEF.h"


class CRes__SYSTEM_LOTID
{
private:
	CRITICAL_SECTION mCS_LOCK;
	CStringArray sList_LOTID;

public:
	CRes__SYSTEM_LOTID()
	{
		InitializeCriticalSection(&mCS_LOCK);

	}
	~CRes__SYSTEM_LOTID()
	{

		DeleteCriticalSection(&mCS_LOCK);
	}

	//
	void Init__LOTID_COUNT()
	{
		EnterCriticalSection(&mCS_LOCK);

		sList_LOTID.RemoveAll();

		LeaveCriticalSection(&mCS_LOCK);
	}
	int Check__LOTID_COUNT(const CString& lotid)
	{
		EnterCriticalSection(&mCS_LOCK);

		int flag = -1;

		int limit = sList_LOTID.GetSize();
		int i;

		for(i=0;i<limit;i++)
		{
			if(lotid.CompareNoCase(sList_LOTID[i]) != 0)
			{
				continue;
			}

			flag = 1;
			break;
		}

		if(flag < 0)
		{
			sList_LOTID.Add(lotid);

			if(sList_LOTID.GetSize() > 20)
			{
				sList_LOTID.RemoveAt(0);
			}
		}

		LeaveCriticalSection(&mCS_LOCK);
		return flag;
	}
};

class CObj_Mng__SYSTEM_INFO_STD : public __IOBJ__STD_TYPE
{
private:
	//-------------------------------------------------------------------------
	CString sObject_Name;

	CCommon_Error__DEF_VARIABLE mERROR__DEF_VAR;

	// ...
	SCX__CTC__SCH_MATERIAL_CTRL xSCH_MATERIAL_CTRL;
	CRes__SYSTEM_LOTID mRes__SYSTEM_LOTID;
	//


	//-------------------------------------------------------------------------
	//  INTERNAL PROPERTY

	CX__VAR_STRING_CTRL  sCH__CUR_DAY;

	CX__VAR_STRING_CTRL  sCH__MON_SYS_ALARM_STATE;
	CX__VAR_STRING_CTRL  sCH__MON_SYS_MAINT_STATE;

	// ...
	CX__VAR_STRING_CTRL  sCH__1th_DAY__TOTAL_EQUIPMENT_PROCESS_TIME_SEC;
	CX__VAR_STRING_CTRL  sCH__1th_DAY__TOTAL_EQUIPMENT_IDLE_TIME_SEC;
	CX__VAR_STRING_CTRL  sCH__1th_DAY__TOTAL_EQUIPMENT_DOWN_TIME_SEC;

	// Day : 1 ~ 3 
	CX__VAR_STRING_CTRL  sCH__DAYx__TOTAL_LOT_COUNT[CFG__DAY_SIZE];
	CX__VAR_STRING_CTRL  sCH__DAYx__TOTAL_PROCESSED_WAFER_COUNT[CFG__DAY_SIZE];

	CX__VAR_STRING_CTRL  sCH__DAYx__TOTAL_EQUIPMENT_PROCESS_TIME_FMT[CFG__DAY_SIZE];
	CX__VAR_STRING_CTRL  sCH__DAYx__TOTAL_EQUIPMENT_IDLE_TIME_FMT[CFG__DAY_SIZE];
	CX__VAR_STRING_CTRL  sCH__DAYx__TOTAL_EQUIPMENT_DOWN_TIME_FMT[CFG__DAY_SIZE];

	// UPEH Info ...
	CX__VAR_STRING_CTRL  sCH__CUR_HOUR;
	CX__VAR_STRING_CTRL  sCH__DAYx__HOURx_UPEH_RESULT[CFG__DAY_SIZE][CFG__HOUR_SIZE];
	//

	//-------------------------------------------------------------------------
	//  EXTERNAL PROPERTY

	//


	//-------------------------------------------------------------------------
	CString sMODE__TEST_UPEH_DATA;
	int  Call__TEST_UPEH_DATA(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm);

	CString sMODE__CLEAR_UPEH_DATA;
	int  Call__CLEAR_UPEH_DATA(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm);
	//

	
	//-------------------------------------------------------------------------
	int Mon__SYSTEM_INFO(CII_OBJECT__VARIABLE *p_variable);

	// Alarm & Maint
	int Check__ALARM_Or_MAINT();

	// Process & Idle 
	int Check__PROCESS_Or_IDLE();
	//


public:
	CObj_Mng__SYSTEM_INFO_STD();
	~CObj_Mng__SYSTEM_INFO_STD();

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
