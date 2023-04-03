#include "StdAfx.h"
#include "CObj_Phy__CHM_STD.h"

#include "CCommon_System.h"


// ...
void CObj_Phy__CHM_STD::
Mon__All_State(CII_OBJECT__VARIABLE *p_variable, 
			   CII_OBJECT__ALARM* p_alarm)
{
	int loop_count = 0;
	int obj_count  = 0;

	double pre_press = -1;
	CString ch_data;
	
	xEXT_CH__TMC_CONNECT_STATUS->Set__DATA(STR__OFFLINE);

	
	while(1)
	{
		p_variable->Wait__SINGLE_OBJECT(0.1);


		loop_count++;
		if(loop_count >= 5)			loop_count = 0;

		// Object Status ...
		if(loop_count == 1)
		{
			if(iPRC_STS < 0)
			{
				CString obj_ctrl = xCH__TMC_CHM_CTRL->Get__STRING();

				if(dEXT_CH__SCH_TEST_CFG_TMC_DUMMY_BY_CTC->Check__DATA(STR__YES) > 0)
				{
					if((obj_ctrl.CompareNoCase(STR__AVAILABLE) == 0)
					|| (obj_ctrl.CompareNoCase(STR__ABORTED)   == 0))
					{
						if(xCH__OBJ_STATUS->Check__DATA(STR__CTCINUSE) > 0)
							xCH__OBJ_STATUS->Set__DATA(STR__STANDBY);
					}
				}
				else
				{
					if((obj_ctrl.CompareNoCase(STR__AVAILABLE) == 0)
					|| (obj_ctrl.CompareNoCase(STR__ABORTED)   == 0))
					{
						if(xCH__OBJ_STATUS->Check__DATA(STR__CTCINUSE) > 0)
						{
							obj_count++;

							if(obj_count > 3)
							{
								obj_count = 0;

								xI_Sync_Ctrl.Thread__LOCK();

								if(iPRC_STS < 0)
									xCH__OBJ_STATUS->Set__DATA(STR__STANDBY);

								xI_Sync_Ctrl.Thread__UNLOCK();
							}
						}
						else
						{
							obj_count = 0;
						}
					}
					else
					{
						obj_count = 0;
					}
				}
			}
		}

		// Module Status ...
		if(loop_count == 1)
		{
			if(dEXT_CH__SCH_TEST_CFG_TMC_DUMMY_BY_CTC->Check__DATA(STR__YES) > 0)
			{
				xEXT_CH__TMC_CONNECT_STATUS->Set__DATA(STR__ONLINE);
			}
			else
			{
				if(xI__MODULE_INFO->Is__ONLINE(iSEQ_ID) < 0)
				{
					xEXT_CH__TMC_CONNECT_STATUS->Set__DATA(STR__OFFLINE);

					CString r_act;

					p_alarm->Check__ALARM(ALID__TMC_OFFLINE,r_act);
					p_alarm->Post__ALARM(ALID__TMC_OFFLINE);
				}
				else
				{
					xEXT_CH__TMC_CONNECT_STATUS->Set__DATA(STR__ONLINE);
				}
			}
		}

		// Pressure Status ...
		{
			double ref_atm_press = aEXT_CH_CFG__REF_ATM_PRESSURE->Get__VALUE();
			double ref_vac_press = aEXT_CH_CFG__REF_VAC_PRESSURE->Get__VALUE();

			ch_data = xCH__PRESSURE_VALUE->Get__STRING();
			double cur_press = atof(ch_data);
			double cur_mtorr = cur_press * 1000.0;
			
			ch_data.Format("%.1f", cur_mtorr);
			xCH__PRESSURE_mTORR->Set__DATA(ch_data);

			if(cur_press != pre_press)
			{
				pre_press = cur_press;
			}

			if(cur_press <= ref_vac_press)
			{
				CString sts_press = "VAC";

				if(xCH__PRESSURE_STATUS->Check__DATA(sts_press) < 0)
					xCH__PRESSURE_STATUS->Set__DATA(sts_press);
			}
			else if(cur_press >= ref_atm_press)
			{
				CString sts_press = "ATM";

				if(xCH__PRESSURE_STATUS->Check__DATA(sts_press) < 0)
					xCH__PRESSURE_STATUS->Set__DATA(sts_press);
			}
			else
			{
				CString sts_press = "BTW";

				if(xCH__PRESSURE_STATUS->Check__DATA(sts_press) < 0)
					xCH__PRESSURE_STATUS->Set__DATA(sts_press);
			}
		}

		// ...
	}
}
