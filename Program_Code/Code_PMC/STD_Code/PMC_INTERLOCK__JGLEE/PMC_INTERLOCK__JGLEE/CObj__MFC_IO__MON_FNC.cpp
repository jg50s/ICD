#include "StdAfx.h"
#include "CObj__MFC_IO.h"


//------------------------------------------------------------------------------------
void CObj__MFC_IO
::Mon__MONITOR(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm)
{
	int i;

	while(1)
	{
		p_variable->Wait__SINGLE_OBJECT(0.1);

		//
		for(i=0; i<iSIZE__MFC_OBJ; i++)
		{
			int check_interlock = -1;

			if(bActive__MFC_DO_VLV_IN_X[i])
			{
				if(doEXT_CH__MFC_DO_VLV_IN_X[i]->Check__DATA(STR__OPEN) > 0)		check_interlock = 1;
			}
			if(bActive__MFC_DO_VLV_OUT_X[i])
			{
				if(doEXT_CH__MFC_DO_VLV_OUT_X[i]->Check__DATA(STR__OPEN) > 0)		check_interlock = 1;
			}	
			if(bActive__MFC_DO_VLV_PURGE_X[i])
			{
				if(doEXT_CH__MFC_DO_VLV_PURGE_X[i]->Check__DATA(STR__OPEN) > 0)		check_interlock = 1;
			}

			if(check_interlock > 0)
			{
				int mfc_id = i + 1;

				ValueLock__MFCx_Valve_Open(mfc_id);
			}
		}
	}
}

int CObj__MFC_IO::ValueLock__MFCx_Valve_Open(const int mfc_id)
{
	CString err_msg;

	if(Check__MFC_Interlock(mfc_id,err_msg) < 0)
	{
		// ...
		{
			int alarm_id = ALID__MFCx_VALUE_INTERLOCK + (mfc_id - 1);

			if(mfc_id < 1)
			{
				alarm_id = ALID__MFCx_VALUE_INTERLOCK;
			}

			Post_Alarm(alarm_id,err_msg);
		}

		// ...
		{
			int db_index = mfc_id - 1;

			if((db_index >= 0)
			&& (db_index <  iSIZE__MFC_OBJ))	
			{
				if(bActive__MFC_DO_VLV_IN_X[db_index])			doEXT_CH__MFC_DO_VLV_IN_X[db_index]->Set__DATA(STR__CLOSE);
				if(bActive__MFC_DO_VLV_OUT_X[db_index])			doEXT_CH__MFC_DO_VLV_OUT_X[db_index]->Set__DATA(STR__CLOSE);
				
				if(bActive__MFC_DO_VLV_PURGE_X[db_index])		doEXT_CH__MFC_DO_VLV_PURGE_X[db_index]->Set__DATA(STR__CLOSE);
			}
		}
		return -1;
	}

	return 1;
}
