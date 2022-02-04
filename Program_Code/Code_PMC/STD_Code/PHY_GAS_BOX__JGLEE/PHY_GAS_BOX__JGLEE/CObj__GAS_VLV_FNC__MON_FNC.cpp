#include "StdAfx.h"
#include "CObj__GAS_VLV_FNC.h"


// ...
void CObj__GAS_VLV_FNC::Mon__STATE_CHECK(CII_OBJECT__VARIABLE *p_variable)
{
	CString var_data;
	
	int db_index;
	int pre_index = -1;

	while(1)
	{
		p_variable->Wait__SINGLE_OBJECT(0.5);

		// MFC.TYPE ...
		{
			var_data = dCH__PARA_MFC_TYPE->Get__STRING();
			db_index = Get__MFC_INDEX(var_data);	

			if(db_index >= 0)
			{
				if(db_index != pre_index)
				{
					pre_index = db_index;

					sEXT_CH__CFG_GAS_NAME[db_index]->Get__DATA(var_data);
					sCH__CUR_MFC_GAS_NAME->Set__DATA(var_data);

					//
					double cfg_min = aEXT_CH__CFG_MFC_MIN_VALUE[db_index]->Get__VALUE();
					double cfg_max = aEXT_CH__CFG_MFC_MAX_VALUE[db_index]->Get__VALUE();
					int cfg_dec = (int) aEXT_CH__CFG_MFC_DEC_VALUE[db_index]->Get__VALUE();

					aCH__PARA_MFC_FLOW->Change__MIN_MAX_DEC(cfg_min,cfg_max,cfg_dec);
				}
			}
		}

		// ...
	}
}
