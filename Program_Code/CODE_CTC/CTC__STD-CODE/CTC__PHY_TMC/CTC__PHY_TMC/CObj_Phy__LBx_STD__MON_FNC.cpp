#include "StdAfx.h"
#include "CObj_Phy__LBx_STD.h"

#include "CCommon_System.h"


// ...
void CObj_Phy__LBx_STD
::Mon__All_State(CII_OBJECT__VARIABLE *p_variable, 
				 CII_OBJECT__ALARM* p_alarm)
{
	int loop_count   = 0;
	int module_count = 0;

	CString	ch_data;
	int i;


	while(1)
	{
		p_variable->Wait__SINGLE_OBJECT(0.1);


		loop_count++;
		if(loop_count > 10)			loop_count = 1;

		// DA Offset ...
		if((loop_count == 1) || (loop_count == 6))
		{
			CString r_offset;
			CString t_offset;

			sCH__FDC_DA_R_OFFSET->Get__DATA(r_offset);
			sCH__FDC_DA_T_OFFSET->Get__DATA(t_offset);

			ch_data.Format("%s___%s", r_offset,t_offset);
			sCH__FDC_DA_RT_OFFSET->Set__DATA(ch_data);
		}

		// Process Time ...
		if((loop_count == 1) || (loop_count == 6))
		{
			if(iActive__PROC_STS > 0)
			{
				ch_data = sCH__PROC_INFO_TOTAL_PROC_TIME->Get__STRING();
				double sec_total = atof(ch_data);

				ch_data = sCH__PROC_INFO_CUR_PROC_TIME->Get__STRING();
				double sec_cur = atof(ch_data);

				double proc_percent = 0;
				if(sec_total > 0)		
					proc_percent = (sec_cur / sec_total) * 100.0;

				ch_data.Format("%.1f", proc_percent);	
				sCH__PROC_INFO_PROCESS_PERCENT->Set__DATA(ch_data);
			}
			else
			{
				sCH__PROC_INFO_CUR_PROC_TIME->Set__DATA("0");

				sCH__PROC_INFO_PROCESS_PERCENT->Set__DATA("0");
			}
		}

		// Pressure Status ...
		{
			aEXT_CH_CFG__REF_ATM_PRESSURE->Get__DATA(ch_data);
			double ref_atm_press = atof(ch_data);

			aEXT_CH_CFG__REF_VAC_PRESSURE->Get__DATA(ch_data);
			double ref_vac_press = atof(ch_data);

			xCH__PRESSURE_VALUE->Get__DATA(ch_data);
			double cur_press = atof(ch_data);

			double cur_mtorr = cur_press * 1000.0;
			ch_data.Format("%.1f", cur_mtorr);
			xCH__PRESSURE_mTORR->Set__DATA(ch_data);

			if(xCH__VENTING_COMP_FLAG->Check__DATA("CHECK") > 0)
			{
				if(cur_press > 500)
					xCH__VENTING_COMP_FLAG->Set__DATA("YES");
			}
			if(xCH__PUMPING_COMP_FLAG->Check__DATA("CHECK") > 0)
			{
				if(cur_press <  100)
					xCH__PUMPING_COMP_FLAG->Set__DATA("YES");
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

		// Module Status ...
		if(loop_count == 1)
		{
			IDS__SCH_MATERIAL_INFO db_info;

			CString obj_ctrl;
			CString sch_name;
			CString var_data;

			if(iActive__CTRL_STS < 0)
			{
				xCH__LBx_CTRL->Get__DATA(obj_ctrl);

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
							module_count++;

							if(module_count > 3)
							{
								module_count = 0;

								xI_Sync_Ctrl.Thread__LOCK();
		
								if(iActive__CTRL_STS < 0)
								{
									xCH__OBJ_STATUS->Set__DATA(STR__STANDBY);
								}

								xI_Sync_Ctrl.Thread__UNLOCK();
							}
						}
						else
						{
							module_count = 0;
						}
					}
					else
					{
						module_count = 0;
					}
				}

				if(xI_SCH_MATERIAL_CTRL->Get__MATERIAL_DB_SIZE() > 0)
				{
					sCH__SCH_IDLE_COUNT->Get__DATA(var_data);
					int i_count = atoi(var_data) + 1;
					var_data.Format("%1d", i_count);
					sCH__SCH_IDLE_COUNT->Set__DATA(var_data);
				}
				else
				{
					sCH__SCH_IDLE_COUNT->Set__DATA("__");
				}
			}

			if(xCH__CFG_USE_FLAG->Check__DATA(STR__DISABLE) > 0)
			{
				xCH__OBJ_VIRTUAL_STATUS->Set__DATA(STR__DISABLE);
			}
			else
			{
				xCH__OBJ_STATUS->Get__DATA(var_data);
				xCH__OBJ_VIRTUAL_STATUS->Set__DATA(var_data);				
			}

			// SLOT_X : VIRTUAL STATUS ...
			for(i=0; i<CFG_LLx__SLOT_MAX; i++)
			{
				if(dEXT_CH__CFG_LL_SLOT_X_STATUS[i]->Check__DATA(STR__DISABLE) > 0)
				{
					xCH__SLOT_X_VIRTUAL_STATUS[i]->Set__DATA(STR__DISABLE);
				}
				else
				{
					ch_data = xCH__OBJ_VIRTUAL_STATUS->Get__STRING();
					xCH__SLOT_X_VIRTUAL_STATUS[i]->Set__DATA(ch_data);
				}
			}

			if((xCH__OBJ_VIRTUAL_STATUS->Check__DATA(STR__CTCINUSE) > 0)
			|| (xCH__OBJ_VIRTUAL_STATUS->Check__DATA(STR__STANDBY)  > 0))
			{
				if(xCH__PRE_MAINT_FLAG->Check__DATA(STR__MAINT) > 0)
				{
					xCH__PRE_MAINT_FLAG->Set__DATA(STR__YES);
				}
			}
			else
			{
				xCH__PRE_MAINT_FLAG->Set__DATA(STR__MAINT);
			}
		}
	
		// ...
	}
}
