#include "StdAfx.h"
#include "CObj_Mng__TMC_INFO.h"


// ...
void CObj_Mng__TMC_INFO
::Mon__INFO_CTRL(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm)
{
	SCX__MODULE_INFO x_module_info;

	xEXT_CH__TMC_CONNECT_STATUS->Set__DATA(STR__ONLINE);

	while(1)
	{
		Sleep(90);

		if(x_module_info->Is__ONLINE(1) > 0)
		{
			xEXT_CH__TMC_CONNECT_STATUS->Set__DATA(STR__ONLINE);			
		}
		else
		{
			xEXT_CH__TMC_CONNECT_STATUS->Set__DATA(STR__OFFLINE);			
		}
	}
}
