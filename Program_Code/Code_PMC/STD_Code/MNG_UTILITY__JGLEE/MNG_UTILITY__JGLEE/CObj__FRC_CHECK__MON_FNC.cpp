#include "StdAfx.h"
#include "CObj__FRC_CHECK.h"



// ...
void CObj__FRC_CHECK
::Mon__STATUS_CTRL(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm)
{
	CString pre__gas_type;
	CString var_data;


	while(1)
	{
		p_variable->Wait__SINGLE_OBJECT(0.1);


		if(dCH_PARA__TEST_GAS_TYPE->Check__DATA(pre__gas_type) < 0)
		{
			pre__gas_type = dCH_PARA__TEST_GAS_TYPE->Get__STRING();

			int db_index = Get__Gas_Type_Index(pre__gas_type);

			if((db_index >= 0)
			&& (db_index <  iSIZE__OBJ_MFCx))
			{
				sEXT_CH__MFCx_CFG_GAS_NAME[db_index]->Get__DATA(var_data);
				sCH__CUR_TEST_GAS_NAME->Set__DATA(var_data);

				double cfg_max = aEXT_CH__MFCx_CFG_GAS_MAX[db_index]->Get__VALUE();
				aCH_PARA__TEST_GAS_FLOW->Change__MIN_MAX_DEC(0, cfg_max, 0);
			}
			else
			{
				sCH__CUR_TEST_GAS_NAME->Set__DATA("");
			}
		}
	}
}

int  CObj__FRC_CHECK
::Get__Gas_Type_Index(const CString& str_gas_type)
{
	CString str_name;
	int i;

	for(i=0; i<CFG__MFC_SIZE; i++)
	{
		str_name.Format("GAS%002d", i+1);

		if(str_name.CompareNoCase(str_gas_type) == 0)
		{
			return (i);
		}
	}
	return -1;
}
