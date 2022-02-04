#include "StdAfx.h"
#include "CObj__RF_IO.h"
#include "CObj__RF_IO__ALID.h"
#include "CObj__RF_IO__DEF.h"


// ...
int CObj__RF_IO
::Mon__STATUS(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm)
{
	CString ch_data;

	while(1)
	{
		p_variable->Wait__SINGLE_OBJECT(0.1);

		// ...
		{
			dEXT_CH__DO_SOURCE_ON->Get__DATA(ch_data);
			sCH__MON_POWER_ON_SET->Set__DATA(ch_data);

			dEXT_CH__DI_SOURCE_ON->Get__DATA(ch_data);
			sCH__MON_POWER_ON_SNS->Set__DATA(ch_data);

			dEXT_CH__DI_SOURCE_OVERTEMP_ALARM->Get__DATA(ch_data);
			sCH__MON_OVERTEMP_SNS->Set__DATA(ch_data);
		}

		// ...
		{
			aEXT_CH__AO_SOURCE_POWER->Get__DATA(ch_data);
			sCH__MON_POWER_SET->Set__DATA(ch_data);

			aEXT_CH__AI_FORWARD_POWER->Get__DATA(ch_data);
			sCH__MON_FORWARD_POWER->Set__DATA(ch_data);

			aEXT_CH__AI_REFLECT_POWER->Get__DATA(ch_data);
			sCH__MON_REFLECT_POWER->Set__DATA(ch_data);
		}
	}

	return 1;
}
