#include "StdAfx.h"
#include "CObj__DGF_FLEX.h"



//------------------------------------------------------------------------------------------
int CObj__DGF_FLEX
::Mon__STATUS(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm)
{
	// ...
	{
		CString log_msg;

		log_msg = "Status Monitoring Thread Start...";
		Fnc__WRITE_LOG(log_msg);
	}

	// ...
	CString cur__wt_setpoint = "~";

	/*
	if(iActive__SIM_MODE > 0)
	{
		dEXT_CH__GasPerchg_ManVac_PSH2->Set__DATA("True");
		dEXT_CH__Chamber_DeliverVac_PSH3->Set__DATA("True");
		dEXT_CH__TunningGas_DeliverVac_PSH4->Set__DATA("True");
		dEXT_CH__Scrubber_Switch_PSH8->Set__DATA("True");
		dEXT_CH__N2Purge_Supply_PSH9->Set__DATA("True");
		dEXT_CH__CDAPress_Switch_Sts->Set__DATA("True");
		dEXT_CH__Customer_GasDetect_Switch->Set__DATA("True");
		dEXT_CH__Customer_Intlk_Switch->Set__DATA("True");
		dEXT_CH__H2_Intlk_Switch->Set__DATA("True");
		dEXT_CH__H2_Intlk_Switch_Installed->Set__DATA("True");
		dEXT_CH__Conver_Intlk->Set__DATA("True");
		dEXT_CH__WaterLeak_Detection_Sts->Set__DATA("True");
	}
	*/

	// ...
	{
		sCH__CTRL_OPEN_REQ->Set__DATA(STR__IDLE);
	}

	while(1)
	{
		p_variable->Wait__SINGLE_OBJECT(0.1);

		// 1. DGF Set-point Present Case ...
		{
			if((aCH__CENTER_Wt_SET_POINT->Check__DATA(cur__wt_setpoint) < 0)
			|| (sCH__CTRL_OPEN_REQ->Check__DATA(STR__YES) > 0))
			{
				aCH__CENTER_Wt_SET_POINT->Get__DATA(cur__wt_setpoint);
				sCH__CTRL_OPEN_REQ->Set__DATA(STR__IDLE);

				Call__CONTROL(p_variable, p_alarm);
			}
		}

		// ...
	}
}
