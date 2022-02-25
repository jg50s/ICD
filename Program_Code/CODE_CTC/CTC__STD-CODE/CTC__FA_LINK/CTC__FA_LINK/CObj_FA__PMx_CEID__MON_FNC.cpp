#include "StdAfx.h"
#include "CObj_FA__PMx_CEID.h"


#include "CMacro_FA.h"
extern CMacro_FA mFA_Link;


// ...
void CObj_FA__PMx_CEID
::Mon__REPORT_CEID(CII_OBJECT__VARIABLE* p_variable)
{
	CString pre_chm_system[SCH_DB__PM_LIMIT];
	CString pre_chm_door[SCH_DB__PM_LIMIT];
	CString pre_chm_pin[SCH_DB__PM_LIMIT];
	CString var_data;

	int pmc_id;
	int i;

	while(1)
	{
		Sleep(90);

		for(i=0;i<iPMx_SIZE;i++)
		{
			pmc_id = i + 1;

			if(xEXT_CH__PMx_CFG_USE[i]->Check__DATA("ENABLE") < 0)
			{
				continue;
			}

			// CHAMBER STATUS  (ACTIVE -> MAINT)  
			//		:  OFFLINE  UNINIT  NOTREADY  STANDBY  CTCINUSE  MAINTMODE
			{
				xEXT_CH__PMx_OBJ_STATUS[i]->Get__DATA(var_data);

				if(var_data.CompareNoCase(pre_chm_system[i]) != 0)
				{
					if(var_data.CompareNoCase("MAINTMODE") == 0)
					{
						if((pre_chm_system[i].CompareNoCase("STANDBY")  == 0)
						|| (pre_chm_system[i].CompareNoCase("CTCINUSE") == 0))
						{
							mFA_Link.Event__CHM__DOWN(pmc_id);
						}
					}

					pre_chm_system[i] = var_data;
				}
			}

			// DOOR STATE
			//		:  UNKNOWN  CLOSE  OPEN
			{
				xEXT_CH__PMx_DOOR_STS[i]->Get__DATA(var_data);

				if(var_data.CompareNoCase(pre_chm_door[i]) != 0)
				{
					if(var_data.CompareNoCase("CLOSE") == 0)
					{
						mFA_Link.Event__CHM__DOOR_CLOSE(pmc_id);
					}
					else if(var_data.CompareNoCase("OPEN") == 0)
					{
						mFA_Link.Event__CHM__DOOR_OPEN(pmc_id);
					}

					pre_chm_door[i] = var_data;
				}
			}

			// LIFT PIN STATE
			//		:  Unknown  Down  Up
			{
				xEXT_CH__PMx_LIFT_PIN_STS[i]->Get__DATA(var_data);

				if(var_data.CompareNoCase(pre_chm_pin[i]) != 0)
				{
					if(var_data.CompareNoCase("DOWN") == 0)
					{
						mFA_Link.Event__CHM__LIFT_PIN_DOWN(pmc_id);
					}
					else if(var_data.CompareNoCase("UP") == 0)
					{
						mFA_Link.Event__CHM__LIFT_PIN_UP(pmc_id);
					}

					pre_chm_pin[i] = var_data;
				}
			}
		}

		// ...
	}
}
