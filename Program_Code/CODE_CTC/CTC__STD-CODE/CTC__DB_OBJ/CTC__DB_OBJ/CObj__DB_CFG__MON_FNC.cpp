#include "StdAfx.h"
#include "CObj__DB_CFG.h"
#include "CObj__DB_CFG__ALID.h"


#define STR__YES			"YES"
#define STR__NO				"NO"

#define STR__OFF			"OFF"
#define STR__ON				"ON"

#define STR__HOUR			"HOUR"
#define STR__MINUTE			"MINUTE"


// ...
void CObj__DB_CFG::Mon__INFO_REPORT(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM *p_alarm)
{
	// ...
	{
		xFA_300mm_Link->Open("");	
		xI_SCH_MATERIAL_CTRL->Link__SERVICE_DB("");
	}

	// ...
	int link__ref_time;
	int link__time_count = 0;

	// ...
	CI_FA_VARIABLE_CTRL *p_var_ctrl = xFA_300mm_Link->Get_FA_VARIABLE_CTRL();

	CString main_name;
	CString sub_name;
	CString var_data;

	CStringArray l_data;
	int i;


	while(1)
	{
		p_variable->Wait__SINGLE_OBJECT(1.0);
		link__time_count++;


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

		if(iActive__SIM_MODE > 0)
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

				for(i=0; i<iDATA__PMx_SIZE; i++)
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
			if(dCH__SCH_TEST_CFG_TMC_DUMMY_BY_CTC->Check__DATA(STR__NO) < 0)
			{
				dCH__SCH_TEST_CFG_TMC_DUMMY_BY_CTC->Set__DATA(STR__NO);
			}

			for(i=0; i<iDATA__PMx_SIZE; i++)
			{
				if(dCH__SCH_TEST_CFG_PMX_DUMMY_BY_CTC[i]->Check__DATA(STR__NO) < 0)
				{
					dCH__SCH_TEST_CFG_PMX_DUMMY_BY_CTC[i]->Set__DATA(STR__NO);
				}
			}
		}

		// LINK_TIME ...
		{
			bool active__time_change = false;

			if(dCH__SYNC_LINK_TIME_REQ->Check__DATA(STR__YES) > 0)
			{
				dCH__SYNC_LINK_TIME_REQ->Set__DATA(STR__NO);

				active__time_change = true;
			}

			if(dCH__SYNC_LINK_TIME_CFG_USE->Check__DATA(STR__YES) > 0)
			{
				int cfg_data = (int) aCH__SYNC_LINK_TIME_CFG__REF_TIME->Get__VALUE();

				if(dCH__SYNC_LINK_TIME_CFG__REF_TYPE->Check__DATA(STR__HOUR) > 0)
				{
					link__ref_time = cfg_data * 3600;
				}
				else
				{
					link__ref_time = cfg_data * 60;
				}

				if(link__time_count >= link__ref_time)
				{
					active__time_change = true;
				}
			}
			else
			{
				link__time_count = 0;
			}

			if(active__time_change)
			{
				Fnc__Set_Module_Time();

				link__time_count = 0;
			}

			// ...
			{
				int cur_sec  = link__time_count % 60;
				int cur_min  = link__time_count / 60;
				int cur_hour = cur_min / 60;

				cur_min = cur_min - (cur_hour * 60);

				var_data.Format("%02d:%02d:%02d", cur_hour,cur_min,cur_sec);
				sCH__SYNC_LINK_TIME_INFO->Set__DATA(var_data);
			}	
		}
	}
}

void CObj__DB_CFG::Fnc__Set_Module_Time()
{
	// ...
	{
		SYSTEMTIME cur_time;
		GetLocalTime(&cur_time);

		CString	str_time;
		str_time.Format("%00004d%002d%002d%002d%002d%002d",
						cur_time.wYear,
						cur_time.wMonth, 
						cur_time.wDay,
						cur_time.wHour,
						cur_time.wMinute,
						cur_time.wSecond);

		for(int i=0; i<iDATA__PMx_SIZE; i++)
		{
			sEXT_CH__PMx_MODULE_TIME_X[i]->Set__DATA(str_time);
		}
	}

	// ...
	{
		dCH__SYNC_LINK_TIME_ACTIVE->Set__DATA(STR__ON);
	
		Sleep(1000);	

		dCH__SYNC_LINK_TIME_ACTIVE->Set__DATA(STR__OFF);
	}
}

