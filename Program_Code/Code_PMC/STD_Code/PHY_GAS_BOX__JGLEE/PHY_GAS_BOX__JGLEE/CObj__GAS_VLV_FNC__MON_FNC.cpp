#include "StdAfx.h"
#include "CObj__GAS_VLV_FNC.h"


// ...
int CObj__GAS_VLV_FNC::Mon__STATE(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm)
{
	CString ch_data;

	int loop_count = 0;

	while(1)
	{
		p_variable->Wait__SINGLE_OBJECT(0.1);

		loop_count++;
		if(loop_count > 10)			loop_count = 1;

		if(loop_count == 1)
		{
			// CFG : TRANSFER.BALLAST ...
			{
				ch_data = dCH__CFG_TRANSFER_BALLAST_GAS_ID->Get__STRING();
				int mfc_index = Get__MFC_INDEX(ch_data);

				if(mfc_index >= 0)
				{
					ch_data = sEXT_CH__CFG_GAS_NAME[mfc_index]->Get__STRING();
					sCH__CUR_TRANSFER_BALLAST_GAS_NAME->Set__DATA(ch_data);

					//
					double cfg_min = aEXT_CH__CFG_MFC_MIN_VALUE[mfc_index]->Get__VALUE();
					double cfg_max = aEXT_CH__CFG_MFC_MAX_VALUE[mfc_index]->Get__VALUE();
					int cfg_dec = (int) aEXT_CH__CFG_MFC_DEC_VALUE[mfc_index]->Get__VALUE();

					aCH__CFG_TRANSFER_BALLAST_GAS_FLOW->Change__MIN_MAX_DEC(cfg_min, cfg_max, cfg_dec);
				}
				else
				{
					sCH__CUR_TRANSFER_BALLAST_GAS_NAME->Set__DATA("__");
				}
			}

			// CFG : CHAMBER.BALLAST ...
			{
				ch_data = dCH__CFG_CHAMBER_BALLAST_GAS_ID->Get__STRING();
				int mfc_index = Get__MFC_INDEX(ch_data);

				if(mfc_index >= 0)
				{
					ch_data = sEXT_CH__CFG_GAS_NAME[mfc_index]->Get__STRING();
					sCH__CUR_CHAMBER_BALLAST_GAS_NAME->Set__DATA(ch_data);

					//
					double cfg_min = aEXT_CH__CFG_MFC_MIN_VALUE[mfc_index]->Get__VALUE();
					double cfg_max = aEXT_CH__CFG_MFC_MAX_VALUE[mfc_index]->Get__VALUE();
					int cfg_dec = (int) aEXT_CH__CFG_MFC_DEC_VALUE[mfc_index]->Get__VALUE();

					aCH__CFG_CHAMBER_BALLAST_GAS_FLOW->Change__MIN_MAX_DEC(cfg_min, cfg_max, cfg_dec);
				}
				else
				{
					sCH__CUR_CHAMBER_BALLAST_GAS_NAME->Set__DATA("__");
				}
			}
		}

		// ...
	}

	return 1;
}
