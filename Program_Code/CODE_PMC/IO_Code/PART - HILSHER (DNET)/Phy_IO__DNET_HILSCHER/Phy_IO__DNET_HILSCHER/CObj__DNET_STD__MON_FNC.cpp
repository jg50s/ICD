#include "StdAfx.h"
#include "CObj__DNET_STD.h"
#include "CObj__DNET_STD__DEF.h"

#include "cifuser.h"
#include "rcs_user.h"
#include "dnm_user.h"


//------------------------------------------------------------------------------------
void CObj__DNET_STD
::Mon__MONITOR(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm)
{
	CString ch_data;

	// ...
	{
		ch_data.Format("%1d", usOutputOffset);
		sCH__DNET_INFO__OUT_BYTE_SIZE->Set__DATA(ch_data);

		ch_data.Format("%1d", usInputOffset);
		sCH__DNET_INFO__IN_BYTE_SIZE->Set__DATA(ch_data);
	}

	// ...
	SCX__ASYNC_TIMER_CTRL x_heartbeat_timer;

	if(bActive__DO_DNET_HEARTBEAT)
	{
		x_heartbeat_timer->REGISTER__COUNT_CHANNEL_NAME(sCH__DNET_HEARTBEAT_TIME_COUNT->Get__CHANNEL_NAME());
		x_heartbeat_timer->START__COUNT_UP(9999);
	}

	// ...
	int active__link_io = -1;
	double cfg__wait_sec = aCH__CFG_LINK_IO_WAITING_SEC->Get__VALUE();

	SCX__ASYNC_TIMER_CTRL x_link_io_timer;

	if(iSIZE__LINK_IO > 0)
	{
		x_link_io_timer->START__COUNT_UP(9999);
	}


	while(1)
	{
		p_variable->Wait__SINGLE_OBJECT(0.05);


		if(iActive__SIM_MODE > 0)
		{
			diCH__COMM_STS->Set__DATA("ONLINE");
		}

		// LINK : IO ...
		if(iSIZE__LINK_IO > 0)
		{
			if(active__link_io < 0)
			{
				if(x_link_io_timer->Get__CURRENT_TIME() > cfg__wait_sec)
				{
					active__link_io = 1;
					x_link_io_timer->STOP_ZERO();

					int i_limit = iSIZE__LINK_IO;
					for(int i=0; i<i_limit; i++)
					{
						dEXT_CH__DNET_LINK_IO[i]->Set__DATA("ON");
					}
				}
			}
		}

		if(bActive__DO_DNET_HEARTBEAT)
		{
			double cfg_sec = aCH__CFG_DNET_HEARTBEAT_PERIOD->Get__VALUE();

			if(cfg_sec < 1)
			{
				x_heartbeat_timer->STOP_ZERO();
			}
			else
			{
				double cur_sec = x_heartbeat_timer->Get__CURRENT_TIME();

				if(cur_sec >= cfg_sec)
				{
					x_heartbeat_timer->STOP_ZERO();
					x_heartbeat_timer->START__COUNT_UP(9999);

					if(dEXT_CH__DO_DNET_HEARTBEAT->Check__DATA("ON") < 0)
					{
						dEXT_CH__DO_DNET_HEARTBEAT->Set__DATA("ON");
					}
					else
					{
						dEXT_CH__DO_DNET_HEARTBEAT->Set__DATA("OFF");
					}
				}
				else if(cur_sec < 0.001)
				{
					x_heartbeat_timer->START__COUNT_UP(9999);
				}
			}
		}

		if(diCH__COMM_STS->Check__DATA("OFFLINE") > 0)
		{
			int alm_id = ALID__OFFLINE;
			CString alm_msg;
			CString	r_act;

			alm_msg = "";

			p_alarm->Check__ALARM(alm_id, r_act);
			p_alarm->Post__ALARM_With_MESSAGE(alm_id, alm_msg);
		}

		// ...
		{
			EnterCriticalSection(&mLOCK_DNET);

			_DNet__UPDATE_INFO();

			LeaveCriticalSection(&mLOCK_DNET);
		}		
	}

	// ...
}

void CObj__DNET_STD
::_DNet__UPDATE_INFO()
{
	if(iDNet_BoardNumber < 0)
	{
		return;
	}

	// ...
	CString ch_data;

	int dev_id = iDNet_BoardNumber;
	int i;

	// Output Download ...
	{
		mCtrl__DNet_Node.Update__ALL_OUT_BYTE(abOutputData,usOutputOffset);

		if(dCH__DNET_INFO__OUT_BYTE_CHECK_ACTIVE->Check__DATA(STR__YES) > 0)
		{
			for(i=0; i<usOutputOffset; i++)
			{
				if(i < CFG__DNET_OUT_BYTE_LIMIT)
				{
					ch_data.Format("%02X", abOutputData[i]);
					sCH__DNET_INFO__OUT_BYTE_DATA_X[i]->Set__DATA(ch_data);
				}
			}
		}
	}

	DevExchangeIO(dev_id,
					0,
					usOutputOffset,
					&abOutputData,
					0,
					usInputOffset,
					&abInputData,
					500L);

	// Input Upload ...
	{
		mCtrl__DNet_Node.Update__ALL_IN_BYTE(abInputData,usInputOffset);

		if(dCH__DNET_INFO__IN_BYTE_CHECK_ACTIVE->Check__DATA(STR__YES) > 0)
		{
			for(i=0; i<usInputOffset; i++)
			{
				if(i < CFG__DNET_IN_BYTE_LIMIT)
				{
					ch_data.Format("%02X", abInputData[i]);
					sCH__DNET_INFO__IN_BYTE_DATA_X[i]->Set__DATA(ch_data);
				}
			}
		}
	}
}
