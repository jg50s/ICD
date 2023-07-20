#include "StdAfx.h"
#include "CObj__NXA_PULSE.h"
#include "CObj__NXA_PULSE__DEF.h"


// ...
int CObj__NXA_PULSE
::Call__PARA_RCP_CTRL(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm, const bool active_on)
{
	CString ch_data;

	if(active_on)
	{
		// PARA.CLK <- LOW ...
		{
			doCH__SET_EXEC->Set__DATA(STR__OFF);
		}

		// PARA.A1
		{
			ch_data = aCH__PARA_RCP_FREQUENCY->Get__STRING();
			aCH__PARA_A_DRV_FREQ->Set__DATA(ch_data);

			ch_data = aCH__PARA_RCP_DUTY->Get__STRING();
			aCH__PARA_A_DRV_DUTY->Set__DATA(ch_data);

			doCH__PARAM_A1->Set__DATA(STR__ON);
		}
		/*
		// PARA.A2
		{
			ch_data = aCH__PARA_RCP_ON_TIME->Get__STRING();
			aCH__PARA_A_DRV_ON_TIME->Set__DATA(ch_data);

			ch_data = aCH__PARA_RCP_OFF_TIME->Get__STRING();
			aCH__PARA_A_DRV_OFF_TIME->Set__DATA(ch_data);

			doCH__PARAM_A2->Set__DATA(STR__ON);
		}
		*/

		// PARA.B
		{
			ch_data = aCH__PARA_RCP_ON_SHIFT_TIME->Get__STRING();
			aCH__PARA_B_DRV_ON_SHIFT_TIME->Set__DATA(ch_data);

			ch_data = aCH__PARA_RCP_OFF_SHIFT_TIME->Get__STRING();
			aCH__PARA_B_DRV_OFF_SHIFT_TIME->Set__DATA(ch_data);

			doCH__PARAM_B->Set__DATA(STR__ON);
		}
		
		// PARA.CLK
		{
			ch_data = dCH__PARA_RCP_EXEC->Get__STRING();

			if(ch_data.CompareNoCase(STR__INVERSE) == 0)
			{
				dCH__PARA_A_DRV_CLK_CTRL->Set__DATA(STR__NORMAL);
				dCH__PARA_B_DRV_CLK_CTRL->Set__DATA(STR__INVERSE);
				dCH__PARA_C_DRV_CLK_CTRL->Set__DATA(STR__NORMAL);
			}
			else if(ch_data.CompareNoCase(STR__OFF) == 0)
			{
				dCH__PARA_A_DRV_CLK_CTRL->Set__DATA(STR__INVERSE);
				dCH__PARA_B_DRV_CLK_CTRL->Set__DATA(STR__NORMAL);
				dCH__PARA_C_DRV_CLK_CTRL->Set__DATA(STR__NORMAL);
			}
			else if(ch_data.CompareNoCase(STR__HIGH) == 0)
			{
				dCH__PARA_A_DRV_CLK_CTRL->Set__DATA(STR__NORMAL);
				dCH__PARA_B_DRV_CLK_CTRL->Set__DATA(STR__HIGH);
				dCH__PARA_C_DRV_CLK_CTRL->Set__DATA(STR__NORMAL);
			}
			else if(ch_data.CompareNoCase(STR__LOW) == 0)
			{
				dCH__PARA_A_DRV_CLK_CTRL->Set__DATA(STR__NORMAL);
				dCH__PARA_B_DRV_CLK_CTRL->Set__DATA(STR__LOW);
				dCH__PARA_C_DRV_CLK_CTRL->Set__DATA(STR__NORMAL);
			}
			else			
			{
				dCH__PARA_A_DRV_CLK_CTRL->Set__DATA(STR__NORMAL);
				dCH__PARA_B_DRV_CLK_CTRL->Set__DATA(STR__NORMAL);
				dCH__PARA_C_DRV_CLK_CTRL->Set__DATA(STR__NORMAL);
			}

			doCH__SET_EXEC->Set__DATA(STR__ON);
		}
	}
	else
	{
		// PARA.A1
		{
			aCH__PARA_A_DRV_FREQ->Set__VALUE(0.0);
			aCH__PARA_A_DRV_DUTY->Set__VALUE(0.0);

			doCH__PARAM_A1->Set__DATA(STR__ON);
		}
		/*
		// PARA.A2
		{
			aCH__PARA_A_DRV_ON_TIME->Set__VALUE(0.0);
			aCH__PARA_A_DRV_OFF_TIME->Set__VALUE(0.0);

			doCH__PARAM_A2->Set__DATA(STR__ON);
		}
		*/

		// PARA.B
		{
			aCH__PARA_B_DRV_ON_SHIFT_TIME->Set__VALUE(0.0);
			aCH__PARA_B_DRV_OFF_SHIFT_TIME->Set__VALUE(0.0);

			doCH__PARAM_B->Set__DATA(STR__ON);
		}

		/*
		// PARA.C
		{
			aCH__PARA_C_DRV_ON_SHIFT_TIME->Set__VALUE(0.0);
			aCH__PARA_C_DRV_OFF_SHIFT_TIME->Set__VALUE(0.0);

			doCH__PARAM_C->Set__DATA(STR__ON);
		}
		*/

		doCH__SET_EXEC->Set__DATA(STR__OFF);
	}

	// RCP.LOG ...
	{
		CString log_msg;
		CString log_bff;

		log_msg = "RCP.PARA ... \n";

		// PARA.A1
		{
			log_bff.Format("  * %s <- %s \n", 
							aCH__PARA_RCP_FREQUENCY->Get__VARIABLE_NAME(),
							aCH__PARA_RCP_FREQUENCY->Get__STRING());
			log_msg += log_bff;
			
			log_bff.Format("  * %s <- %s \n", 
							aCH__PARA_RCP_DUTY->Get__VARIABLE_NAME(),
							aCH__PARA_RCP_DUTY->Get__STRING());
			log_msg += log_bff;
		}

		// PARA.B
		{
			log_bff.Format("  * %s <- %s \n", 
							aCH__PARA_RCP_ON_SHIFT_TIME->Get__VARIABLE_NAME(),
							aCH__PARA_RCP_ON_SHIFT_TIME->Get__STRING());
			log_msg += log_bff;

			log_bff.Format("  * %s <- %s \n", 
							aCH__PARA_RCP_OFF_SHIFT_TIME->Get__VARIABLE_NAME(),
							aCH__PARA_RCP_OFF_SHIFT_TIME->Get__STRING());
			log_msg += log_bff;
		}
		
		// PARA.CLK
		{
			log_bff.Format("  * %s <- %s \n", 
							dCH__PARA_RCP_EXEC->Get__VARIABLE_NAME(),
							dCH__PARA_RCP_EXEC->Get__STRING());
			log_msg += log_bff;
		}

		Write__APP_LOG(log_msg);
	}

	return 1;
}
