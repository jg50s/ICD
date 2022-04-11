#include "StdAfx.h"
#include "CObj__NXA_PULSE.h"


// ...
int CObj__NXA_PULSE
::Call__PARA_USER_CTRL(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm, const bool active_on)
{
	CString ch_data;

	if(active_on)
	{
		// PARA.A1
		{
			ch_data = aCH__PARA_A_USER_FREQ->Get__STRING();
			aCH__PARA_A_DRV_FREQ->Set__DATA(ch_data);

			ch_data = aCH__PARA_A_USER_DUTY->Get__STRING();
			aCH__PARA_A_DRV_DUTY->Set__DATA(ch_data);

			doCH__PARAM_A1->Set__DATA(STR__ON);
		}
		// PARA.A2
		{
			ch_data = aCH__PARA_A_USER_ON_TIME->Get__STRING();
			aCH__PARA_A_DRV_ON_TIME->Set__DATA(ch_data);

			ch_data = aCH__PARA_A_USER_OFF_TIME->Get__STRING();
			aCH__PARA_A_DRV_OFF_TIME->Set__DATA(ch_data);

			doCH__PARAM_A2->Set__DATA(STR__ON);
		}

		// PARA.B
		{
			ch_data = aCH__PARA_B_USER_ON_SHIFT_TIME->Get__STRING();
			aCH__PARA_B_DRV_ON_SHIFT_TIME->Set__DATA(ch_data);

			ch_data = aCH__PARA_B_USER_OFF_SHIFT_TIME->Get__STRING();
			aCH__PARA_B_DRV_OFF_SHIFT_TIME->Set__DATA(ch_data);

			doCH__PARAM_B->Set__DATA(STR__ON);
		}

		// PARA.C
		{
			ch_data = aCH__PARA_C_USER_ON_SHIFT_TIME->Get__STRING();
			aCH__PARA_C_DRV_ON_SHIFT_TIME->Set__DATA(ch_data);

			ch_data = aCH__PARA_C_USER_OFF_SHIFT_TIME->Get__STRING();
			aCH__PARA_C_DRV_OFF_SHIFT_TIME->Set__DATA(ch_data);

			doCH__PARAM_C->Set__DATA(STR__ON);
		}

		// PARA.CLK
		{
			ch_data = dCH__PARA_A_USER_CLK_CTRL->Get__STRING();
			dCH__PARA_A_DRV_CLK_CTRL->Set__DATA(ch_data);

			ch_data = dCH__PARA_B_USER_CLK_CTRL->Get__STRING();
			dCH__PARA_B_DRV_CLK_CTRL->Set__DATA(ch_data);

			ch_data = dCH__PARA_C_USER_CLK_CTRL->Get__STRING();
			dCH__PARA_C_DRV_CLK_CTRL->Set__DATA(ch_data);

			doCH__SET_EXEC->Set__DATA(STR__ON);
		}
	}
	else
	{
		doCH__SET_EXEC->Set__DATA(STR__OFF);
	}

	return 1;
}
