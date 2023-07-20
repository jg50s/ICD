#include "StdAfx.h"
#include "CObj__NXA_PULSE.h"


// ...
int CObj__NXA_PULSE
::Mon__MONITOR(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm)
{
	CString ch_data;
	int loop_count = 0;

	dCH__MON_COMM_STS->Set__DATA(STR__ONLINE); 


	while(1)
	{
		p_variable->Wait__SINGLE_OBJECT(0.1);

		loop_count++;
		if(loop_count > 10)			loop_count = 1;

		// ...
		{
			ch_data = dCH__CFG_UNIT__FREQ->Get__STRING();
			dUNIT__FREQ = atof(ch_data);

			ch_data = dCH__CFG_UNIT__DUTY->Get__STRING();
			dUNIT__DUTY = atof(ch_data);

			ch_data = dCH__CFG_UNIT__uSEQ->Get__STRING();
			dUNIT__uSEQ = atof(ch_data);
		}

		// Range Update ...
		if(loop_count == 1)
		{
			double cfg_min = aCH__CFG_FREQUENCY_MIN->Get__VALUE();
			double cfg_max = aCH__CFG_FREQUENCY_MAX->Get__VALUE();

			ch_data = dCH__CFG_FREQUENCY_DEC->Get__STRING();
			int cfg_dec = atoi(ch_data);

			aCH__PARA_A_USER_FREQ->Change__MIN_MAX_DEC(cfg_min, cfg_max, cfg_dec);
			aCH__PARA_RCP_FREQUENCY->Change__MIN_MAX_DEC(cfg_min, cfg_max, cfg_dec);
			aCH__PARA_A_DRV_FREQ->Change__MIN_MAX_DEC(cfg_min, cfg_max, cfg_dec);
		}

		// ...
		bool active__err_check = true;

		if(dCH__CFG_PART_USE->Check__DATA("YES") < 0)		active__err_check = false;

		//
		if(iActive__SIM_MODE > 0)
		{
			ch_data = aCH__PARA_A_DRV_FREQ->Get__STRING();
			sCH__INFO_PARAM_A_FREQ->Set__DATA(ch_data);

			ch_data = aCH__PARA_A_DRV_DUTY->Get__STRING();
			sCH__INFO_PARAM_A_DUTY->Set__DATA(ch_data);

			ch_data = aCH__PARA_A_DRV_ON_TIME->Get__STRING();
			sCH__INFO_PARAM_A_ON_TIME->Set__DATA(ch_data);

			ch_data = aCH__PARA_A_DRV_OFF_TIME->Get__STRING();
			sCH__INFO_PARAM_A_OFF_TIME->Set__DATA(ch_data);

			//
			ch_data = aCH__PARA_B_DRV_ON_SHIFT_TIME->Get__STRING();
			sCH__INFO_PARAM_B_ON_SHIFT_TIME->Set__DATA(ch_data);

			ch_data = aCH__PARA_B_DRV_OFF_SHIFT_TIME->Get__STRING();
			sCH__INFO_PARAM_B_OFF_SHIFT_TIME->Set__DATA(ch_data);

			//
			ch_data = aCH__PARA_C_DRV_ON_SHIFT_TIME->Get__STRING();
			sCH__INFO_PARAM_C_ON_SHIFT_TIME->Set__DATA(ch_data);

			ch_data = aCH__PARA_C_DRV_OFF_SHIFT_TIME->Get__STRING();
			sCH__INFO_PARAM_C_OFF_SHIFT_TIME->Set__DATA(ch_data);

			//
			ch_data = dCH__PARA_A_DRV_CLK_CTRL->Get__STRING();
			sCH__INFO_CLK_A_CTRL->Set__DATA(ch_data);

			ch_data = dCH__PARA_B_DRV_CLK_CTRL->Get__STRING();
			sCH__INFO_CLK_B_CTRL->Set__DATA(ch_data);

			ch_data = dCH__PARA_C_DRV_CLK_CTRL->Get__STRING();
			sCH__INFO_CLK_C_CTRL->Set__DATA(ch_data);
		}

		// IO.Update ...
		{
			siCH__PARAM_A1->Get__STRING();
			siCH__PARAM_A2->Get__STRING();
			siCH__PARAM_B->Get__STRING();
			siCH__PARAM_C->Get__STRING();
		
			siCH__GET_EXEC->Get__STRING();
		}

		if(dCH__MON_COMM_STS->Check__DATA(STR__OFFLINE) > 0)
		{
			if(active__err_check)
			{
				int alarm_id = ALID__GEN_OFFLINE_ALARM;
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
