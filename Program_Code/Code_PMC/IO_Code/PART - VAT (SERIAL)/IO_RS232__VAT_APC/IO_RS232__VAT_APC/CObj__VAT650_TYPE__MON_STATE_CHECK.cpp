#include "StdAfx.h"
#include "CObj__VAT650_TYPE.h"

#include "Macro_Function.h"


// ...
void CObj__VAT650_TYPE
::Mon__STATE_CHECK(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm)
{
	CString ch_data;

	int err_id;
	CString err_code;
	CString err_msg;


	while(1)
	{
		p_variable->Wait__SINGLE_OBJECT(0.1);


		if(iACTIVE_SIM > 0)
		{

		}
		else
		{
			if(xCH_diCOMM_STS->Check__DATA(STR__OFFLINE) > 0)
			{
				CString r_act;
				int alarm_id = ALID__APC_OFFLINE_ALARM;

				p_alarm->Check__ALARM(alarm_id,r_act);
				p_alarm->Post__ALARM(alarm_id);
			}
		}

		// Position ...
		{
			double cur_cnt = xCH__aiVALVE_POS->Get__VALUE();
			double cur_pos = cur_cnt * (100.0 / MAX_GUI_RANGE_POSITION);

			ch_data.Format("%.1f", cur_pos);
			sCH__MON_CUR_POSITION_VALUE->Set__DATA(ch_data);
		}
		// Pressure ...
		{
			xCH__aiVALVE_PRESS->Get__DATA(ch_data);
			sCH__MON_PRESSURE_VALUE->Set__DATA(ch_data);
		}

		// Error Check ...
		{
			bool active__err_id = false;

			CString alm_msg;

			while(mRes__ERR_DB.Get__ERR_ID(err_id,err_code) > 0)
			{
				if(dCH__CFG_POS_COUNT_TYPE->Check__DATA(STR__1M_TYPE) > 0)
				{
					Macro__Get_Error_Msg_Of_1M_Type(err_id, err_msg);
				}
				else
				{
					Macro__Get_Error_Msg_Of_1K_Type(err_id, err_msg);
				}

				// ...
				{
					CString alm_bff;

					alm_bff.Format("Error Code <- [%s]\n", err_code);
					alm_msg += alm_bff;
					alm_msg += err_msg;
					alm_msg += "\n";
				}

				active__err_id = true;
			}

			if(active__err_id)
			{
				int alarm_id = ALID__APC_COMM_ERROR_CODE;
				CString r_act;

				p_alarm->Check__ALARM(alarm_id, r_act);
				p_alarm->Post__ALARM_With_MESSAGE(alarm_id, alm_msg);
			}
		}

		// ...
	}	
}

