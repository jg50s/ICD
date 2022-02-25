#include "StdAfx.h"
#include "CObj_Phy__VIS_STD.h"


// ...
void CObj_Phy__VIS_STD
::Mon__All_State(CII_OBJECT__VARIABLE* p_variable,
				 CII_OBJECT__ALARM* p_alarm)
{
	int loop_count = 0;
	int obj_count  = 0;


	while(1)
	{
		Sleep(100);

		loop_count++;
		if(loop_count >= 5)			loop_count = 0;

		// Module State ...
		if(loop_count == 1)
		{
			CString obj_sts = xCH__OBJ_STATUS->Get__STRING();

			if((obj_sts.CompareNoCase("CTCINUSE") != 0)
			&& (obj_sts.CompareNoCase("STANDBY")  != 0))
			{
				xCH__PICK_READY_FLAG->Set__DATA("");
			}
		}

		// Object State ...
		if(loop_count == 1)
		{
			if(iPRC_STS < 0)
			{
				CString obj_ctrl = xCH__OBJ_CTRL->Get__STRING();

				if((obj_ctrl.CompareNoCase("AVAILABLE") == 0)
				|| (obj_ctrl.CompareNoCase("ABORTED")   == 0))
				{
					if(xCH__OBJ_STATUS->Check__DATA("CTCINUSE") > 0)
					{
						obj_count++;

						if(obj_count > 3)
						{
							obj_count = 0;

							xI_Sync_Ctrl.Thread__LOCK();

							if(iPRC_STS < 0)
								xCH__OBJ_STATUS->Set__DATA("STANDBY");

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

		// VIS Config ...
		{
			if(xCH_CFG__RECIPE_MODE->Check__DATA("CONFIG") > 0)
				xI_SCH_MATERIAL_CTRL->Set__VIS_INFO__CFG_MODE();
			else
				xI_SCH_MATERIAL_CTRL->Clear__VIS_INFO__CFG_MODE();

			if(xCH_CFG__VISIT_MODE->Check__DATA("CONFIG") > 0)
				xI_SCH_MATERIAL_CTRL->Set__VIS_INFO__CFG_VISIT();
			else
				xI_SCH_MATERIAL_CTRL->Clear__VIS_INFO__CFG_VISIT();

			// ...
			CString var_data = xCH_CFG__CONFIG_RECIPE->Get__STRING();
			xI_SCH_MATERIAL_CTRL->Set__VIS_INFO__CFG_RECIPE_NAME(var_data);

			// ...
			CUIntArray l_slot_id;
			CUIntArray l_slot_sts;

			for(int i=0; i<CFG_LP__SLOT_MAX; i++)
			{
				int slot_id  = i + 1;
				int slot_sts = -1;

				if(xCH_CFG__SLOT_VISIT_LIST[i]->Check__DATA("YES") > 0)		
					slot_sts =  1;

				l_slot_id.Add(slot_id);
				l_slot_sts.Add(slot_sts);
			}	

			xI_SCH_MATERIAL_CTRL->Set__VIS_INFO__CFG_VISIT_SLOT(l_slot_id,l_slot_sts);
		}

		// ...
	}
}
