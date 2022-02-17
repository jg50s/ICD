#include "StdAfx.h"
#include "CObj__MFC_IO.h"
#include "CObj__MFC_IO__DEF.h"


//-------------------------------------------------------------------------	
int  CObj__MFC_IO
::Call__TEST_1(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm)
{

	return 1;
}

void CObj__MFC_IO
::Post_Alarm(const int alarm_id, const CString err_msg)
{
	CString r_act;

	pII_ALARM->Check__ALARM(alarm_id, r_act);
	pII_ALARM->Post__ALARM_WITH_MESSAGE(alarm_id, err_msg);
}

int CObj__MFC_IO
::Get__GAS_Index(const CString& gas_type)
{
	CString str_name;
	int i;

	for(i=0; i<iSIZE__MFC_OBJ; i++)
	{
		str_name.Format("GAS%1d", i+1);
		if(gas_type.CompareNoCase(str_name) != 0)			continue;

		return i;
	}
	return -1;
}
int CObj__MFC_IO
::Check__MFC_Interlock(const int mfc_id, CString& err_msg)
{
	err_msg = "";

	// ...
	int mfc_index = mfc_id - 1;

	if((mfc_index < 0) || (mfc_index >= iSIZE__MFC_OBJ))
	{
		err_msg.Format("MFC_ID Error : ID Number (%1d) \n", mfc_id);
		return -1;
	}

	// ...
	int lock_flag = -1;

	// ...
	{
		CString err_bff;
		CString var_data;
		int k;

		for(k=0; k<CFG_INTERLOCK__MFC_SIZE; k++)
		{
			dEXT_CH__CFG_INTERLOCK_MFC_TYPE[mfc_index][k]->Get__DATA(var_data);

			int db_index = Get__GAS_Index(var_data);
			if(db_index < 0)			continue;
			
			if(bActive__MFC_DO_VLV_OUT_X[db_index])
			{
				if(doEXT_CH__MFC_DO_VLV_OUT_X[db_index]->Check__DATA(STR__CLOSE) < 0)
				{
					lock_flag = 1;

					err_bff.Format("MFC%1d's Secondary Valve is not \"Close\". \n", db_index+1);
					err_msg += err_bff;
				}
			}

			if(bActive__MFC_DO_VLV_PURGE_X[db_index])
			{
				if(doEXT_CH__MFC_DO_VLV_PURGE_X[db_index]->Check__DATA(STR__CLOSE) < 0)
				{
					lock_flag = 1;

					err_bff.Format("MFC%1d's Purge Valve is not \"Close\". \n", db_index+1);
					err_msg += err_bff;
				}
			}
		}
	}

	if(lock_flag > 0)
	{
		return -1;
	}
	return 1;
}
