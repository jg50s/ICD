#include "StdAfx.h"
#include "CObj_Phy__SYS_STD.h"

#include "CCommon_System.h"


// ...
void CObj_Phy__SYS_STD
::Mon__Obj_Status(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm)
{
	CString obj_ctrl;
	int r_count = 0;

	while(1)
	{
		Sleep(490);

		if(iPRC_STS < 0)
		{
			xCH__OBJ_CTRL->Get__DATA(obj_ctrl);

			if(dEXT_CH__SCH_TEST_CFG_TMC_DUMMY_BY_CTC->Check__DATA(STR__YES) > 0)
			{
				if((obj_ctrl.CompareNoCase(STR__AVAILABLE) == 0)
				|| (obj_ctrl.CompareNoCase(STR__ABORTED)   == 0))
				{
					if(xCH__OBJ_STATUS->Check__DATA(STR__CTCINUSE) > 0)
					{
						xCH__OBJ_STATUS->Set__DATA(STR__STANDBY);
					}
				}
			}
			else
			{
				if((obj_ctrl.CompareNoCase(STR__AVAILABLE) == 0)
				|| (obj_ctrl.CompareNoCase(STR__ABORTED)   == 0))
				{
					if(xCH__OBJ_STATUS->Check__DATA(STR__CTCINUSE) > 0)
					{
						r_count++;

						if(r_count > 3)
						{
							r_count = 0;

							xI_Sync_Ctrl.Thread__LOCK();

							if(iPRC_STS < 0)
							{
								xCH__OBJ_STATUS->Set__DATA(STR__STANDBY);
							}

							xI_Sync_Ctrl.Thread__UNLOCK();
						}
					}
					else
					{
						r_count = 0;
					}
				}
				else
				{
					r_count = 0;
				}
			}
		}

		// ...
	}
}
