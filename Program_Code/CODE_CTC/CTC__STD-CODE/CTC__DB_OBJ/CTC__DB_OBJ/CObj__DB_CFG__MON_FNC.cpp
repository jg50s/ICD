#include "StdAfx.h"
#include "CObj__DB_CFG.h"
#include "CObj__DB_CFG__ALID.h"


#define STR__YES          "YES"


// ...
void CObj__DB_CFG::Mon__INFO_REPORT(CII_OBJECT__ALARM *p_alarm)
{
	SCX__SEQ_INFO x_seq_info;
	int sim_mode = x_seq_info->Is__SIMULATION_MODE();

	// ...
	xFA_300mm_Link->Open("");	
	xI_SCH_MATERIAL_CTRL->Link__SERVICE_DB("");

	// ...
	CI_FA_VARIABLE_CTRL *p_var_ctrl = xFA_300mm_Link->Get_FA_VARIABLE_CTRL();

	CString main_name;
	CString sub_name;
	CString var_data;
	CStringArray l_data;
	int i;


	while(1)
	{
		Sleep(490);

		if(p_var_ctrl != NULL)
		{
			main_name = "EQP_INFO";
			sub_name = "AGVMODE";

			xCH_CFG__AGVMODE->Get__DATA(var_data);
			p_var_ctrl->Set_Variable(main_name,sub_name,var_data);
		}

		// ...
		{
			main_name = "##SYS_INFO##";

			// User ID 
			{
				sub_name = "USER_ID";

				sCH_SYS__USER_ID->Get__DATA(var_data);
				l_data.RemoveAll();
				l_data.Add(var_data);

				xI_SCH_MATERIAL_CTRL->Set__USER_DEF_INFO(main_name,sub_name,l_data);
			}

			// User Level
			{
				sub_name = "USER_LEVEL";

				sCH_SYS__USER_LEVEL->Get__DATA(var_data);
				l_data.RemoveAll();
				l_data.Add(var_data);

				xI_SCH_MATERIAL_CTRL->Set__USER_DEF_INFO(main_name,sub_name,l_data);
			}
		}

		if(sim_mode > 0)
		{
			if(dCH__SCH_TEST_CFG_SIM_ALARM_REPORT->Check__DATA(STR__YES) > 0)
			{
				int alarm_id;
				CString alm_msg;
				CString r_act;

				// ...
				{
					alarm_id = ALID__SIMULATION_MODE_ACTIVE;
					alm_msg  = "";

					p_alarm->Check__ALARM(alarm_id, r_act);
					p_alarm->Post__ALARM_With_MESSAGE(alarm_id, alm_msg);
				}

				if(dCH__SCH_TEST_CFG_TMC_DUMMY_BY_CTC->Check__DATA(STR__YES) > 0)
				{
					alarm_id = ALID__SIMULATION_TMC_DUMMY_MODE_ACTIVE;

					alm_msg.Format(" * \"%s\" <- \"%s\" \n",
								   dCH__SCH_TEST_CFG_TMC_DUMMY_BY_CTC->Get__CHANNEL_NAME(),
								   dCH__SCH_TEST_CFG_TMC_DUMMY_BY_CTC->Get__STRING());

					p_alarm->Check__ALARM(alarm_id, r_act);
					p_alarm->Post__ALARM_With_MESSAGE(alarm_id, alm_msg);
				}

				for(i=0; i<CFG_PM_LIMIT; i++)
				{
					if(dCH__SCH_TEST_CFG_PMX_DUMMY_BY_CTC[i]->Check__DATA(STR__YES) > 0)
					{
						alarm_id = ALID__SIMULATION_PMX_DUMMY_MODE_ACTIVE + i;

						alm_msg.Format(" * \"%s\" <- \"%s\" \n",
									   dCH__SCH_TEST_CFG_PMX_DUMMY_BY_CTC[i]->Get__CHANNEL_NAME(),
									   dCH__SCH_TEST_CFG_PMX_DUMMY_BY_CTC[i]->Get__STRING());
	
						p_alarm->Check__ALARM(alarm_id, r_act);
						p_alarm->Post__ALARM_With_MESSAGE(alarm_id, alm_msg);
					}
				}
			}
		}
		else
		{
			if(dCH__SCH_TEST_CFG_TMC_DUMMY_BY_CTC->Check__DATA("NO") < 0)
			{
				dCH__SCH_TEST_CFG_TMC_DUMMY_BY_CTC->Set__DATA("NO");
			}

			//
			for(i=0; i<CFG_PM_LIMIT; i++)
			{
				if(dCH__SCH_TEST_CFG_PMX_DUMMY_BY_CTC[i]->Check__DATA("NO") < 0)
				{
					dCH__SCH_TEST_CFG_PMX_DUMMY_BY_CTC[i]->Set__DATA("NO");
				}
			}
		}

		// ...
	}
}
