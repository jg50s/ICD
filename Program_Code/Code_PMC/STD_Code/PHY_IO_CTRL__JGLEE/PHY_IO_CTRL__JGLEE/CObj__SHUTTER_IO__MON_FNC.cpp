#include "StdAfx.h"
#include "CObj__SHUTTER_IO.h"
#include "CObj__SHUTTER_IO__ALID.h"
#include "CObj__SHUTTER_IO__DEF.h"


// ...
int CObj__SHUTTER_IO
::Mon__STATUS(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm)
{
	CString ch_data;

	if(iSIM_MODE > 0)
	{
		dEXT_CH__DI_SHUTTER_CLOSE->Set__DATA(STR__ON);
		dEXT_CH__DI_SHUTTER_OPEN->Set__DATA(STR__OFF);
	}

	while(1)
	{
		p_variable->Wait__SINGLE_OBJECT(0.1);

		// ...
		{
			if((dEXT_CH__DI_SHUTTER_CLOSE->Check__DATA(STR__ON) > 0)
			&& (dEXT_CH__DI_SHUTTER_OPEN->Check__DATA(STR__OFF) > 0))
			{
				sEXT_CH__SHUTTER_STATE->Set__DATA(STR__CLOSE);
			}
			else if((dEXT_CH__DI_SHUTTER_CLOSE->Check__DATA(STR__OFF) > 0)
				 && (dEXT_CH__DI_SHUTTER_OPEN->Check__DATA(STR__ON)   > 0))
			{
				sEXT_CH__SHUTTER_STATE->Set__DATA(STR__OPEN);
			}
			else
			{
				sEXT_CH__SHUTTER_STATE->Set__DATA(STR__UNKNOWN);
			}
		}
	}

	return 1;
}
