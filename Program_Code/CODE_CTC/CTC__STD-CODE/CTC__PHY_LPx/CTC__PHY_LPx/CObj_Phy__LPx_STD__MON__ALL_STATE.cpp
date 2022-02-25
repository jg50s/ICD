#include "StdAfx.h"
#include "CMacro_FA.h"

#include "CObj_Phy__LPx_STD.h"
#include "CObj_Phy__LPx_STD__DEF.h"
#include "CObj_Phy__LPx_STD__ALID.h"

#include "Macro_Function.h"


// ...
#define STR__AVAILABLE			"AVAILABLE"
#define STR__ABORTED			"ABORTED"


// ...
void CObj_Phy__LPx_STD
::Mon__ALL_STATE(CII_OBJECT__VARIABLE* p_variable,
				 CII_OBJECT__ALARM* p_alarm)
{
	// PORT STATUS ...
	CString cstid;
	CUIntArray l_slot_sts;

	// MODULE STATUS ...
	CString pre__lp_proc_type;
	dCH__CFG_PROCESS_TYPE->Get__DATA(pre__lp_proc_type);

	// OBJECT STATUS ...
	CString obj_ctrl;
	CString obj_sts;

	int r_count = 0;

	// ...
	CString var_data;


	while(1)
	{
		Sleep(490);


		// PORT STATUS ...
		{
			CString port_sts;
			sCH__PORT_STATUS->Get__DATA(port_sts);

			if(port_sts.CompareNoCase("ABORTED") == 0)
			{
				xCH__LPx_END_REQ_FLAG->Set__DATA("");
				xCH__LPx_RETURN_REQ_FLAG->Set__DATA("");

				xCH__CYCLE_CTRL_FLAG->Set__DATA("");
			}
			else if(port_sts.CompareNoCase("WAITING") == 0)
			{
				xCH__LPx_END_REQ_FLAG->Set__DATA("");
				xCH__LPx_RETURN_REQ_FLAG->Set__DATA("");
			}

			sCH__CID_STRING->Get__DATA(cstid);	
			xI_SCH_MATERIAL_CTRL->Set__LPx_CID(iPTN,cstid);

			if(dCH_CFG__LPx_USE->Check__DATA("PROCESS") > 0)
			{
				xI_SCH_MATERIAL_CTRL->Set__PROCESS_PORT(iPTN);
			}
			else if(dCH_CFG__LPx_USE->Check__DATA("DUMMY") > 0)
			{
				xI_SCH_MATERIAL_CTRL->Set__DUMMY_PORT(iPTN);
			}
			else
			{
				xI_SCH_MATERIAL_CTRL->Set__DISABLE_PORT(iPTN);
			}

			Get__PORT_SLOT_STS(l_slot_sts);
			xI_SCH_MATERIAL_CTRL->Set__PORT_SLOT_STS(iPTN,l_slot_sts);
		}

		// MODULE STATUS ...
		{
			dCH__CFG_PROCESS_TYPE->Get__DATA(var_data);

			if(pre__lp_proc_type.CompareNoCase(var_data) != 0)
			{
				pre__lp_proc_type = var_data;

				if(var_data.CompareNoCase(STR__NORMAL) == 0)
				{
					int alarm_id = ALID__LPx__PROCESS_TYPE_TO_NORMAL;
					CString r_act;

					p_alarm->Check__ALARM(alarm_id,r_act);
					p_alarm->Post__ALARM(alarm_id);
				}
				else if(var_data.CompareNoCase(STR__TEST) == 0)
				{
					int alarm_id = ALID__LPx__PROCESS_TYPE_TO_TEST;
					CString r_act;

					p_alarm->Check__ALARM(alarm_id,r_act);
					p_alarm->Post__ALARM(alarm_id);
				}
			}

			if(xCH__APP_LOCK_FLAG->Check__DATA(STR__YES) > 0)
			{
				xCH__VIRTUAL_PORT_STATUS->Set__DATA("IN.USE");
			}
			else
			{
				sCH__PORT_STATUS->Get__DATA(var_data);
				xCH__VIRTUAL_PORT_STATUS->Set__DATA(var_data);
			}

			if(Check__PORT_STS__Standby_Or_CtcInUse() < 0)
			{
				if(sCH__PORT_STATUS->Check__DATA("WAITING") > 0)
				{
					sCH__PORT_STATUS->Set__DATA("ABORTED");
				}
			}
		}

		// OBJECT STATUS ...
		{
			if(iFLAG__MODULE_OBJ < 0)
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

								if(iFLAG__MODULE_OBJ < 0)
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

			if(dCH_CFG__LPx_USE->Check__DATA(STR__DISABLE) > 0)
			{
				xCH__VIRTUAL_OBJ_STATUS->Set__DATA(STR__DISABLE);
			}
			else
			{
				xCH__OBJ_STATUS->Get__DATA(obj_sts);
				xCH__VIRTUAL_OBJ_STATUS->Set__DATA(obj_sts);				
			}
		}

		// ...
	}
}

