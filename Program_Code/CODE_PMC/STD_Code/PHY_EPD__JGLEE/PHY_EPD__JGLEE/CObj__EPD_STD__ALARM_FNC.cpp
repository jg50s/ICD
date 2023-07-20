#include "StdAfx.h"
#include "CObj__EPD_STD.h"



//-------------------------------------------------------------------------
int  CObj__EPD_STD::
Alarm_Post__EPD_MIN_TIMEOUT(CII_OBJECT__ALARM* p_alarm,
							const CString& alarm_msg)
{
	// ...
	{
		int alarm_id = ALID__EPD_DETECT_MIN_TIMEOUT;
		CString r_act;

		p_alarm->Check__ALARM(alarm_id,r_act);
		p_alarm->Post__ALARM_With_MESSAGE(alarm_id,alarm_msg);
	}

	// ...
	{
		CString log_msg;

		log_msg  = "\n";
		log_msg += "EPD - Min. Timeout Error !";
		log_msg += "\n";

		log_msg += alarm_msg;

		Fnc__WRITE_LOG(log_msg);
	}
	return 1;
}

int  CObj__EPD_STD::
Alarm_Post__EPD_MAX_TIMEOUT(CII_OBJECT__ALARM* p_alarm,
							const CString& alarm_msg)
{
	// ...
	{
		int alarm_id = ALID__EPD_DETECT_MAX_TIMEOUT;
		CString r_act;

		p_alarm->Check__ALARM(alarm_id,r_act);
		p_alarm->Post__ALARM_With_MESSAGE(alarm_id,alarm_msg);
	}

	// ...
	{
		CString log_msg;

		log_msg  = "\n";
		log_msg += "EPD - Max. Timeout Error !";
		log_msg += "\n";

		log_msg += alarm_msg;

		Fnc__WRITE_LOG(log_msg);
	}
	return 1;
}
