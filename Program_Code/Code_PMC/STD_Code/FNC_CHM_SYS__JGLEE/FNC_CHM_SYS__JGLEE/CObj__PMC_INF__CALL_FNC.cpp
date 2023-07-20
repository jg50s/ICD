#include "StdAfx.h"
#include "CObj__PMC_INF.h"
#include "CObj__PMC_INF__ALID.h"


// ...
int  CObj__PMC_INF
::Call__AUTO_INIT(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM *p_alarm)
{
	Call__TIME_INIT(p_variable, p_alarm);

	return Call__SYSTEM_INIT(p_variable, p_alarm);
}

int  CObj__PMC_INF
::Call__TIME_INIT(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM *p_alarm)
{
	DECLARE__EXT_CTRL(p_variable);

	// ...
	bool active__time_change = true;

	CString str__net_ip = sCH__INFO_EQP_NET_IP->Get__STRING();
	if(str__net_ip.CompareNoCase("127.0.0.1") == 0)			active__time_change = false;

	CString str__link_ip = sCH__LINK_NET_IP->Get__STRING();
	if(str__net_ip.CompareNoCase(str__link_ip) == 0)		active__time_change = false;

	// ...
	int result__time_change = -1;

	if(active__time_change)
	{
		CString str_time = sCH__MODULE_TIME->Get__STRING();
		
		if(str_time.GetLength() >= 14)
		{
			CString year, month, date, hour, minute, second;

			year   = str_time.Mid(0,4);
			month  = str_time.Mid(4,2);
			date   = str_time.Mid(6,2);
			hour   = str_time.Mid(8,2);
			minute = str_time.Mid(10,2);
			second = str_time.Mid(12,2);

			//
			SYSTEMTIME	sys_time;
			GetLocalTime(&sys_time);

			sys_time.wYear   = atoi(year);
			sys_time.wMonth  = atoi(month); 
			sys_time.wDay	 = atoi(date);
			sys_time.wHour   = atoi(hour);
			sys_time.wMinute = atoi(minute); 
			sys_time.wSecond = atoi(second); 

			result__time_change = SetLocalTime(&sys_time);

			if(result__time_change < 1)
			{
				int alm_id = ALID__SYSTEM_TIME_CHANGE_ERROR;
				CString alm_msg;
				CString r_act;

				alm_msg.Format("CHANGE REQUEST TIME <- %s \n", sCH__MODULE_TIME->Get__STRING());

				p_alarm->Check__ALARM(alm_id, r_act);
				p_alarm->Post__ALARM_With_MESSAGE(alm_id, alm_msg);
			}
		}
		else
		{
			int alm_id = ALID__SYSTEM_TIME_CHANGE_ERROR;
			CString alm_msg;
			CString alm_bff;
			CString r_act;

			alm_msg  = "TIME FORMAT ERROR (YYYYMMDDhhmmss)";
			alm_msg += "\n";
			
			alm_bff.Format(" * CHANGE REQUEST TIME <- %s \n", sCH__MODULE_TIME->Get__STRING());
			alm_msg += alm_bff;

			p_alarm->Check__ALARM(alm_id, r_act);
			p_alarm->Post__ALARM_With_MESSAGE(alm_id, alm_msg);
		}
	}			

	// ...
	{
		CString log_msg;
		CString log_bff;

		log_msg = "Time Change Report ... \n";

		log_bff.Format(" * active__time_change <- [%1d] \n", active__time_change);
		log_msg += log_bff;

		log_bff.Format(" * result__time_change <- [%1d] \n", result__time_change);
		log_msg += log_bff;

		log_bff.Format(" * %s <- %s \n",
						sCH__INFO_EQP_NET_IP->Get__CHANNEL_NAME(),
						sCH__INFO_EQP_NET_IP->Get__STRING());
		log_msg += log_bff;

		log_bff.Format(" * %s <- %s \n",
						sCH__LINK_NET_IP->Get__CHANNEL_NAME(),
						sCH__LINK_NET_IP->Get__STRING());
		log_msg += log_bff;

		log_bff.Format(" * %s <- %s \n",
						sCH__MODULE_TIME->Get__CHANNEL_NAME(),
						sCH__MODULE_TIME->Get__STRING());
		log_msg += log_bff;

		xLOG_CTRL->WRITE__LOG(log_msg);
	}
	return 1;
}

// ...
int  CObj__PMC_INF
::Call__SYSTEM_INIT(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM *p_alarm)
{
	DECLARE__EXT_CTRL(p_variable);

	return p_ext_mode_ctrl->Call__FNC_MODE(sEXT_MODE__SYSTEM_INIT);
}
int  CObj__PMC_INF
::Call__SYSTEM_MAINT(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM *p_alarm)
{
	DECLARE__EXT_CTRL(p_variable);

	return p_ext_mode_ctrl->Call__FNC_MODE(sEXT_MODE__SYSTEM_MAINT);
}

// ...
int  CObj__PMC_INF
::Call__PUMP(CII_OBJECT__VARIABLE* p_variable)
{
	DECLARE__EXT_CTRL(p_variable);

	return p_ext_mode_ctrl->Call__FNC_MODE(sEXT_MODE__PUMP);
}

int  CObj__PMC_INF
::Call__VENT(CII_OBJECT__VARIABLE* p_variable)
{
	DECLARE__EXT_CTRL(p_variable);

	return p_ext_mode_ctrl->Call__FNC_MODE(sEXT_MODE__VENT);
}


// ...
int CObj__PMC_INF
::Call__LEAK_CHECK(CII_OBJECT__VARIABLE* p_variable)
{
	DECLARE__EXT_CTRL(p_variable);

	return p_ext_mode_ctrl->Call__FNC_MODE(sEXT_MODE__LEAK_CHECK);
}

int CObj__PMC_INF
::Call__AUTO_PM(CII_OBJECT__VARIABLE* p_variable)
{
	DECLARE__EXT_CTRL(p_variable);

	return p_ext_mode_ctrl->Call__FNC_MODE(sEXT_MODE__AUTO_PM);
}

int CObj__PMC_INF
::Call__PURGE(CII_OBJECT__VARIABLE *p_variable)
{
	DECLARE__EXT_CTRL(p_variable);

	return p_ext_mode_ctrl->Call__FNC_MODE(sEXT_MODE__PURGE);
}


// ...
int CObj__PMC_INF
::Call__SLOT_OPEN(CII_OBJECT__VARIABLE* p_variable)
{
	DECLARE__EXT_CTRL(p_variable);

	return p_ext_mode_ctrl->Call__FNC_MODE(sEXT_MODE__SLOT_OPEN);
}
int CObj__PMC_INF
::Call__SLOT_CLOSE(CII_OBJECT__VARIABLE* p_variable)
{
	DECLARE__EXT_CTRL(p_variable);

	return p_ext_mode_ctrl->Call__FNC_MODE(sEXT_MODE__SLOT_CLOSE);
}

int CObj__PMC_INF
::Call__PIN_UP(CII_OBJECT__VARIABLE* p_variable)
{
	DECLARE__EXT_CTRL(p_variable);

	return p_ext_mode_ctrl->Call__FNC_MODE(sEXT_MODE__PIN_UP);
}
int CObj__PMC_INF
::Call__PIN_DOWN(CII_OBJECT__VARIABLE* p_variable)
{
	DECLARE__EXT_CTRL(p_variable);

	return p_ext_mode_ctrl->Call__FNC_MODE(sEXT_MODE__PIN_DOWN);
}


// ...
int CObj__PMC_INF
::Call__PICK_READY(CII_OBJECT__VARIABLE* p_variable)
{
	DECLARE__EXT_CTRL(p_variable);

	return p_ext_mode_ctrl->Call__FNC_MODE(sEXT_MODE__PICK_READY);
}
int CObj__PMC_INF
::Call__PICK_X_READY(CII_OBJECT__VARIABLE* p_variable)
{
	DECLARE__EXT_CTRL(p_variable);

	return p_ext_mode_ctrl->Call__FNC_MODE(sEXT_MODE__PICK_X_READY);
}
int CObj__PMC_INF
::Call__PICK_COMPLETE(CII_OBJECT__VARIABLE* p_variable)
{
	DECLARE__EXT_CTRL(p_variable);

	//
	return p_ext_mode_ctrl->Call__FNC_MODE(sEXT_MODE__PICK_COMPLETE);
}
int CObj__PMC_INF
::Call__PICK_X_COMPLETE(CII_OBJECT__VARIABLE* p_variable)
{
	DECLARE__EXT_CTRL(p_variable);

	//
	return p_ext_mode_ctrl->Call__FNC_MODE(sEXT_MODE__PICK_X_COMPLETE);
}

int CObj__PMC_INF
::Call__PLACE_READY(CII_OBJECT__VARIABLE* p_variable)
{
	DECLARE__EXT_CTRL(p_variable);

	return p_ext_mode_ctrl->Call__FNC_MODE(sEXT_MODE__PLACE_READY);
}
int CObj__PMC_INF
::Call__PLACE_X_READY(CII_OBJECT__VARIABLE* p_variable)
{
	DECLARE__EXT_CTRL(p_variable);

	return p_ext_mode_ctrl->Call__FNC_MODE(sEXT_MODE__PLACE_X_READY);
}
int CObj__PMC_INF
::Call__PLACE_COMPLETE(CII_OBJECT__VARIABLE* p_variable)
{
	DECLARE__EXT_CTRL(p_variable);

	return p_ext_mode_ctrl->Call__FNC_MODE(sEXT_MODE__PLACE_COMPLETE);
}
int CObj__PMC_INF
::Call__PLACE_X_COMPLETE(CII_OBJECT__VARIABLE* p_variable)
{
	DECLARE__EXT_CTRL(p_variable);

	return p_ext_mode_ctrl->Call__FNC_MODE(sEXT_MODE__PLACE_X_COMPLETE);
}


// ...
int CObj__PMC_INF
::Call__PRO_READY(CII_OBJECT__VARIABLE* p_variable)
{
	DECLARE__EXT_CTRL(p_variable);

	xEXT_CH__STEP_START->Set__DATA("0");
	xEXT_CH__STEP_END->Set__DATA("0");

	return p_ext_mode_ctrl->Call__FNC_MODE(sEXT_MODE__PRO_READY);
}
int CObj__PMC_INF
::Call__PRO_START(CII_OBJECT__VARIABLE* p_variable)
{
	DECLARE__EXT_CTRL(p_variable);

	return p_ext_mode_ctrl->Call__FNC_MODE(sEXT_MODE__PRO_START);
}

int CObj__PMC_INF
::Call__CLN_READY(CII_OBJECT__VARIABLE* p_variable)
{
	DECLARE__EXT_CTRL(p_variable);

	xEXT_CH__STEP_START->Set__DATA("0");
	xEXT_CH__STEP_END->Set__DATA("0");

	return p_ext_mode_ctrl->Call__FNC_MODE(sEXT_MODE__CLN_READY);
}
int CObj__PMC_INF
::Call__CLN_START(CII_OBJECT__VARIABLE* p_variable)
{
	DECLARE__EXT_CTRL(p_variable);

	return p_ext_mode_ctrl->Call__FNC_MODE(sEXT_MODE__CLN_START);
}

int CObj__PMC_INF
::Call__PRE_READY(CII_OBJECT__VARIABLE* p_variable)
{
	DECLARE__EXT_CTRL(p_variable);

	xEXT_CH__STEP_START->Set__DATA("0");
	xEXT_CH__STEP_END->Set__DATA("0");

	return p_ext_mode_ctrl->Call__FNC_MODE(sEXT_MODE__PRE_READY);
}
int CObj__PMC_INF
::Call__PRE_START(CII_OBJECT__VARIABLE* p_variable)
{
	DECLARE__EXT_CTRL(p_variable);

	return p_ext_mode_ctrl->Call__FNC_MODE(sEXT_MODE__PRE_START);
}

int CObj__PMC_INF
::Call__MNT_READY(CII_OBJECT__VARIABLE* p_variable)
{
	DECLARE__EXT_CTRL(p_variable);

	xEXT_CH__STEP_START->Set__DATA("0");
	xEXT_CH__STEP_END->Set__DATA("0");

	return p_ext_mode_ctrl->Call__FNC_MODE(sEXT_MODE__MNT_READY);
}
int CObj__PMC_INF
::Call__MNT_START(CII_OBJECT__VARIABLE* p_variable)
{
	DECLARE__EXT_CTRL(p_variable);

	return p_ext_mode_ctrl->Call__FNC_MODE(sEXT_MODE__MNT_START);
}

// ...
int CObj__PMC_INF
::Call__JOB_START_READY(CII_OBJECT__VARIABLE* p_variable)
{
	DECLARE__EXT_CTRL(p_variable);

	return p_ext_mode_ctrl->Call__FNC_MODE(sEXT_MODE__JOB_START_READY);
}
int CObj__PMC_INF
::Call__JOB_END_READY(CII_OBJECT__VARIABLE* p_variable)
{
	DECLARE__EXT_CTRL(p_variable);

	// p_ext_mode_ctrl->Abort__CTRL_STS();

	return p_ext_mode_ctrl->Call__FNC_MODE(sEXT_MODE__JOB_END_READY);
}
