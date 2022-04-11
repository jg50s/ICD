#include "StdAfx.h"
#include "CObj__ALx_STD.h"
#include "CObj__ALx_STD__DEF.h"


// ...
int  CObj__ALx_STD
::Call__INIT(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm)
{
	if(!bActive__AL1_USE)
	{
		return -1;
	}

	return pALx__OBJ_CTRL->Call__OBJECT(sDATA__AL_MODE__INIT);
}

int  CObj__ALx_STD
::Call__ALIGN(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm)
{
	if(!bActive__AL1_USE)
	{
		return -1;
	}

	// ...
	int cfg_max  = aEXT_CH__CFG_SLOT_MAX->Get__VALUE();
	int cur_slot = aCH__PARA_SLOT->Get__VALUE();

	if(cur_slot >  cfg_max)
	{
		// Error 
		return -101;
	}

	// ...
	{
		int al_index = cur_slot - 1;

		int i_limit = cfg_max;
		int i;

		for(i=0; i<i_limit; i++)
		{
			if(i == al_index)	
			{
				continue;
			}

			if(dCH__SLOT_STATUS[i]->Check__DATA(STR__NONE) > 0)
			{
				continue;
			}
			
			// Error
			return -102;
		}
	}

	// ...
	CString ch_data;

	aCH__PARA_SLOT->Get__DATA(ch_data);
	dEXT_CH__ALx_PARA_SLOT->Set__DATA(ch_data);

	sEXT_CH__CUR_AL1_CCD_POS->Get__DATA(ch_data);
	sEXT_CH__ALx_PARA_CCD_POS->Set__DATA(ch_data);

	return pALx__OBJ_CTRL->Call__OBJECT(sDATA__AL_MODE__ALIGN);
}
