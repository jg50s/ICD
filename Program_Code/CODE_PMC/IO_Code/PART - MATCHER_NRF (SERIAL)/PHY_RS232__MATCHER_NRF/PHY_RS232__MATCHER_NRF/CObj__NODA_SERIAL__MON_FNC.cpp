#include "StdAfx.h"
#include "CObj__NODA_SERIAL.h"


// ...
int CObj__NODA_SERIAL
::Mon__MONITOR(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm)
{
	CString ch_data;

	dCH__MON_COMM_STS->Set__DATA(STR__ONLINE); 


	while(1)
	{
		p_variable->Wait__SINGLE_OBJECT(0.1);

		// ...
		bool active__err_check = true;
		if(dCH__CFG_PART_USE->Check__DATA("YES") < 0)			active__err_check = false;

		//
		if(iActive__SIM_MODE > 0)
		{
			ch_data = sCH__MON_LOAD_POS_SET->Get__STRING();
			sCH__INFO_CUR_LOAD_POSITION->Set__DATA(ch_data);

			ch_data = sCH__MON_TUNE_POS_SET->Get__STRING();
			sCH__INFO_CUR_TUNE_POSITION->Set__DATA(ch_data);
		}

		// IO.Update ...
		{
			siCH__MAT_STATE->Get__STRING();
			siCH__LOAD_PRESET->Get__STRING();
			siCH__TUNE_PRESET->Get__STRING();
			siCH__CUR_LOAD_POSITION->Get__STRING();
			siCH__CUR_TUNE_POSITION->Get__STRING();
			siCH__VPP_VALUE->Get__STRING();		
			siCH__VDD_VALUE->Get__STRING();
			siCH__IRMS_VALUE->Get__STRING();
			
			// siCH__POS_VALUE->Get__STRING();
		}

		if(active__err_check)
		{
			if(dCH__MON_COMM_STS->Check__DATA(STR__OFFLINE) > 0)
			{
				int alarm_id = ALID__MAT_OFFLINE_ALARM;
				CString alm_msg;
				CString	r_act;

				alm_msg = sPROTOCOL_INFO;

				p_alarm->Check__ALARM(alarm_id,r_act);
				p_alarm->Post__ALARM_With_MESSAGE(alarm_id,alm_msg);
			}
		}

		// ...
	}

	return 1;
}
