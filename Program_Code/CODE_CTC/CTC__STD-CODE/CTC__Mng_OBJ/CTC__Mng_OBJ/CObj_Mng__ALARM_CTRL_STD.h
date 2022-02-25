#pragma once

#include "Interface_Code.h"
#include "CCommon_Error.h"


// ...
#define  ALID__OBJECT_MODE_UNKNOWN					11

#define  MODULE_SIZE								10


class CRES__ALARM_INFO
{
private:
	CRITICAL_SECTION mCS_LOCK;

	CUIntArray   iList__SEQ_ID;
	CUIntArray   iList__ALARM_ID;
	CStringArray sList__ALARM_TYPE;
	CUIntArray   iList__ALARM_LEVEL;
	CStringArray sList__TITLE;

public:
	CRES__ALARM_INFO()
	{
		InitializeCriticalSection(&mCS_LOCK);
	
	}
	~CRES__ALARM_INFO()
	{

		DeleteCriticalSection(&mCS_LOCK);
	}

	void Load__INFO(const CString& str_seq_id,
					const int alarm_id,
					const CString& alarm_type,
					const int alarm_level,
					const CString& alarm_title)
	{
		EnterCriticalSection(&mCS_LOCK);

		int seq_id = 0;

		if(str_seq_id.CompareNoCase("CTC") == 0)
		{
			seq_id = 0;
		}
		else
		{
			CString str_name;

			for(int i=0; i<MODULE_SIZE; i++)
			{
				str_name.Format("MODULE%1d",i);
				
				if(str_seq_id.CompareNoCase(str_name) != 0)
				{
					continue;
				}

				seq_id = i+1;
				break;
			}
		}

		// ...
		{
			iList__SEQ_ID.Add(seq_id);
			iList__ALARM_ID.Add(alarm_id);
			sList__ALARM_TYPE.Add(alarm_type);
			iList__ALARM_LEVEL.Add(alarm_level);
			sList__TITLE.Add(alarm_title);
		}

		// ...
		int db_size = 100;

		if(iList__SEQ_ID.GetSize() > db_size)
		{
			iList__SEQ_ID.RemoveAt(db_size);
			iList__ALARM_ID.RemoveAt(db_size);
			sList__ALARM_TYPE.RemoveAt(db_size);
			iList__ALARM_LEVEL.RemoveAt(db_size);
			sList__TITLE.RemoveAt(db_size);
		}

		LeaveCriticalSection(&mCS_LOCK);
	}
	int  Get__INFO(int& seq_id,
				   int& alarm_id,
				   CString& alarm_type,
				   int& alarm_level,
				   CString& alarm_title)
	{
		EnterCriticalSection(&mCS_LOCK);

		int flag = -1;

		if(iList__SEQ_ID.GetSize() > 0)
		{
			flag = 1;

			seq_id      = (int) iList__SEQ_ID[0];
			alarm_id    = (int) iList__ALARM_ID[0];
			alarm_type  = sList__ALARM_TYPE[0];
			alarm_level = (int) iList__ALARM_LEVEL[0];
			alarm_title = sList__TITLE[0];

			iList__SEQ_ID.RemoveAt(0);
			iList__ALARM_ID.RemoveAt(0);
			sList__ALARM_TYPE.RemoveAt(0);
			iList__ALARM_LEVEL.RemoveAt(0);
			sList__TITLE.RemoveAt(0);
		}

		LeaveCriticalSection(&mCS_LOCK);
		return flag;
	}

	int  Get__TOTAL_SIZE()
	{
		EnterCriticalSection(&mCS_LOCK);

		int total_size = 0;

		int i_limit = iList__SEQ_ID.GetSize();
		int i;

		for(i=0; i<i_limit; i++)
		{
			total_size += iList__SEQ_ID.GetSize();
		}

		LeaveCriticalSection(&mCS_LOCK);
		return total_size;
	}
};


class CObj_Mng__ALARM_CTRL_STD : public __IOBJ__STD_TYPE
{
private:
	//-------------------------------------------------------------------------
	CString sObject_Name;

	CCommon_Error__DEF_VARIABLE mERROR__DEF_VAR;

	CX_FA_300mm_LINK xFA_300mm_Link;
	SCX__CTC__SCH_MATERIAL_CTRL xSCH_MATERIAL_CTRL;

	CRES__ALARM_INFO  mRes__POST_ALARM;
	CRES__ALARM_INFO  mRes__CLEAR_ALARM;


	//-------------------------------------------------------------------------
	//  INTERNAL PROPERTY

	CX__VAR_STRING_CTRL  sCH__CUR_DAY;

	// APP ...
	CX__VAR_STRING_CTRL  xCH__OBJ_MSG;
	CX__VAR_DIGITAL_CTRL xCH__ALARM_FLAG;
	CX__VAR_DIGITAL_CTRL xCH__ALARM_BUZZER;

	CX__VAR_STRING_CTRL  xCH__LAST_ALARM_MSG;

	CX__VAR_STRING_CTRL  xCH__MODULE_ALARM_FLAG[MODULE_SIZE];

	CX__VAR_STRING_CTRL  xCH__1th_SYSTEM_ALARM_COUNT;
	CX__VAR_STRING_CTRL  xCH__2th_SYSTEM_ALARM_COUNT;
	CX__VAR_STRING_CTRL  xCH__3th_SYSTEM_ALARM_COUNT;
	CX__VAR_STRING_CTRL  xCH__1th_MODULE_ALARM_COUNT[MODULE_SIZE];
	CX__VAR_STRING_CTRL  xCH__2th_MODULE_ALARM_COUNT[MODULE_SIZE];
	CX__VAR_STRING_CTRL  xCH__3th_MODULE_ALARM_COUNT[MODULE_SIZE];

	CX__VAR_STRING_CTRL  xCH__POST_ALARM_COUNT;
	CX__VAR_STRING_CTRL  xCH__POST_ALARM_ID;
	CX__VAR_STRING_CTRL  xCH__POST_ALARM_TEXT;

	CX__VAR_STRING_CTRL  xCH__ALARM_FILE_UPLOAD_REQ;
	CX__VAR_STRING_CTRL  xCH__ALARM_FILE_DB_CHECK_FLAG;

	// CFG ...
	CX__VAR_DIGITAL_CTRL xCH__CFG_ALM_WARNING_LIGHT_RED_APPLY_MODE;
	CX__VAR_DIGITAL_CTRL xCH__CFG_MSG_BOX_BUZZER_MODE;

	CX__VAR_DIGITAL_CTRL dCH__CFG_FA_REPORT_WITH_LEVEL_HEAVY;
	CX__VAR_DIGITAL_CTRL dCH__CFG_FA_REPORT_WITH_LEVEL_LIGHT;
	CX__VAR_DIGITAL_CTRL dCH__CFG_FA_REPORT_WITH_LEVEL_WARNING;

	//
	CX__VAR_DIGITAL_CTRL xCH__CFG_ALARM_POSTED_DB_CHECK;
	//

	//-------------------------------------------------------------------------
	//  EXTERNAL PROPERTY

	CString sMODE__CHECK_CURRENT_ALARM;
	int  Call__CHECK_CURRENT_ALARM(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm);
	//

	
	//-------------------------------------------------------------------------
	void Mon__ALARM_CTRL(CII_OBJECT__VARIABLE *p_variable);

	void _Report__ALARM_TO_FA();
	void _Change__DAY_REPORT(int& cur_day);
	void _Reload__ALARM_FILE();
	void _Update__LAST_ALARM(SCI__ALARM_CTRL* p_alarm_ctrl);
	void _Update__ALARM_LOG(SCI__ALARM_CTRL* p_alarm_ctrl);
	//


public:
	CObj_Mng__ALARM_CTRL_STD();
	~CObj_Mng__ALARM_CTRL_STD();

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
