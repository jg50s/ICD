#include "StdAfx.h"
#include "CObj__UNIT_TYPE.h"


// ...
void CObj__UNIT_TYPE
::Mon__STATE_CHECK(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM *p_alarm)
{
	int alm_id;
	int gas_id;
	CString alm_msg;


	while(1)
	{
		p_variable->Wait__SINGLE_OBJECT(0.1);


		while(mDB__ALM_CTRL.Get__ALM_INFO(alm_id,gas_id,alm_msg) > 0)
		{
			CString r_act;

			p_alarm->Check__ALARM(alm_id,r_act);
			p_alarm->Post__ALARM_With_MESSAGE(alm_id,alm_msg);
		}

		// ALARM.TEST ...
		{
			if(sCH__ALM_TEST__OFFLINE->Check__DATA(STR__YES) > 0)
			{	
				sCH__ALM_TEST__OFFLINE->Set__DATA("");

				// ...
				{
					int mac_id = 1;
					int mfc_index = 0;

					CString alm_msg;
					CString alm_bff;

					alm_bff.Format("GasID[%1d] Offline ! \n", mac_id);
					alm_msg += alm_bff;
					alm_bff.Format("   Receive Timeout <- %1d msec \n", 100);
					alm_msg += alm_bff;
					alm_bff.Format("   Retry Count <- %1d \n", 2);
					alm_msg += alm_bff;

					mDB__ALM_CTRL.Load__ALM_OFFLINE(mac_id,mfc_index, alm_msg);
				}
			}
			if(sCH__ALM_TEST__TIMEOUT->Check__DATA(STR__YES) > 0)
			{
				sCH__ALM_TEST__TIMEOUT->Set__DATA("");

				// ...
				{
					int mac_id = 1;
					int mfc_index = 0;

					CString alm_msg;
					CString alm_bff;

					alm_bff.Format("Gas%1d's (%.3f) sccm Setpoint Timeout ! \n", mac_id, 300.0);
					alm_msg += alm_bff;

					alm_bff.Format("   Min(%.3f), Max(%.3f) \n", 0.0,1000.0);
					alm_msg += alm_bff;

					alm_bff.Format("   Retry Count <- [%1d] \n", 5);
					alm_msg += alm_bff;

					mDB__ALM_CTRL.Load__ALM_CTRL_TIMEOUT(mac_id,mfc_index, alm_msg);
				}
			}
		}

		// ...
	}
}
