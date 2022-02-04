#include "StdAfx.h"
#include "CObj__PMC_OPR.h"
#include "CObj__PMC_OPR__DEF.h"


// ...
void CObj__PMC_OPR::
Mon__STATUS(CII_OBJECT__VARIABLE *p_variable)
{
	CString ch_data;

	while(1)
	{
		p_variable->Wait__SINGLE_OBJECT(0.1);

		if(sEXT_CH__SYSTEM_SETUP_REQ->Check__DATA(STR__YES) > 0)
		{
			if(xCH__OBJ_STATUS->Check__DATA(STR__MAINTMODE) > 0)
			{
				sCH__OBJ_STATUS_VIRTUAL->Set__DATA("SETUP");
			}
			else
			{
				sCH__OBJ_STATUS_VIRTUAL->Set__DATA("SETUP.UNKNOWN");
			}
		}
		else
		{
			xCH__OBJ_STATUS->Get__DATA(ch_data);
			sCH__OBJ_STATUS_VIRTUAL->Set__DATA(ch_data);
		}
	}
}
