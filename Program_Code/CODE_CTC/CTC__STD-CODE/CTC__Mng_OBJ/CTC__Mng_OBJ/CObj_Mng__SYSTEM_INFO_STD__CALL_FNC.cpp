#include "StdAfx.h"
#include "CObj_Mng__SYSTEM_INFO_STD.h"


// ...
int  CObj_Mng__SYSTEM_INFO_STD
::Call__TEST_UPEH_DATA(CII_OBJECT__VARIABLE *p_variable,
					   CII_OBJECT__ALARM *p_alarm)
{
	CString var_data;
	int i;
	int k;

	for(i=0; i<CFG__DAY_SIZE; i++)
	{
		for(k=0; k<CFG__HOUR_SIZE; k++)
		{
			var_data.Format("%1d.%1d", i+1,k+1);
			sCH__DAYx__HOURx_UPEH_RESULT[i][k]->Set__DATA(var_data);
		}
	}
	return 1;
}

int  CObj_Mng__SYSTEM_INFO_STD
::Call__CLEAR_UPEH_DATA(CII_OBJECT__VARIABLE *p_variable,
					    CII_OBJECT__ALARM *p_alarm)
{
	for(int i=0; i<CFG__DAY_SIZE; i++)
	{
		for(int k=0; k<CFG__HOUR_SIZE; k++)
		{
			sCH__DAYx__HOURx_UPEH_RESULT[i][k]->Set__DATA("");
		}
	}
	return 1;
}
