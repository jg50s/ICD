#include "StdAfx.h"
#include "CObj__UNIT_TYPE.h"



//--------------------------------------------------------------------------------
void CObj__UNIT_TYPE::
Mon__ALM_REPORT(CII_OBJECT__ALARM *p_alarm)
{
	// ...
	int alm_id;
	int gas_id;
	CString alm_msg;


	while(1)
	{
		Sleep(10);

		// ...
		while(mDB__ALM_CTRL.Get__ALM_INFO(alm_id,gas_id,alm_msg) > 0)
		{
			CString r_act;

			p_alarm->Check__ALARM(alm_id,r_act);
			p_alarm->Post__ALARM_With_MESSAGE(alm_id,alm_msg);
		}

		// ...
		{
			if(sCH__ALM_TEST__OFFLINE->Check__DATA(STR__YES) > 0)
			{	
				sCH__ALM_TEST__OFFLINE->Set__DATA("");

				// ...
				{
					int gas_num = 1;

					CString alm_msg;
					CString alm_bff;

					alm_bff.Format("GasID[%1d] Offline ! \n", gas_num);
					alm_msg += alm_bff;
					alm_bff.Format("   Receive Timeount <- %1d msec \n", 100);
					alm_msg += alm_bff;
					alm_bff.Format("   Retry Count <- %1d \n", 2);
					alm_msg += alm_bff;

					mDB__ALM_CTRL.Load__ALM_OFFLINE(gas_num,alm_msg);
				}
			}
			if(sCH__ALM_TEST__TIMEOUT->Check__DATA(STR__YES) > 0)
			{
				sCH__ALM_TEST__TIMEOUT->Set__DATA("");

				// ...
				{
					int gas_num = 20;

					CString alm_msg;
					CString alm_bff;

					alm_bff.Format("Gas%1d's (%.3f) sccm Setpoint Timeout ! \n",
						gas_num, 300.0);
					alm_msg += alm_bff;

					alm_bff.Format("   Min(%.3f), Max(%.3f) \n", 0.0,1000.0);
					alm_msg += alm_bff;

					alm_bff.Format("   Retry Count <- [%1d] \n", 5);
					alm_msg += alm_bff;

					//
					mDB__ALM_CTRL.Load__ALM_CTRL_TIMEOUT(gas_id,alm_msg);
				}
			}
		}
	}
}
