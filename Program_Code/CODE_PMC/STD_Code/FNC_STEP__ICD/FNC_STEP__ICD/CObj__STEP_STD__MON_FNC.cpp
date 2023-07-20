#include "StdAfx.h"
#include "CObj__STEP_STD.h"


// ...
int CObj__STEP_STD
::Mon__MONITOR(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm)
{
	CString ch_data;


	while(1)
	{
		p_variable->Wait__SINGLE_OBJECT(1.0);


		// Range Update ...
		{
			double cfg_min = aEXT_CH__RF_PULSE__CFG_FREQUENCY_MIN->Get__VALUE();
			double cfg_max = aEXT_CH__RF_PULSE__CFG_FREQUENCY_MAX->Get__VALUE();
			int cfg_dec = (int) aEXT_CH__RF_PULSE__CFG_FREQUENCY_DEC->Get__VALUE();

			aCH__CFG_PROCESS_END_FREQUENCY_RFx_PULSE->Change__MIN_MAX_DEC(cfg_min, cfg_max, cfg_dec);
			aCH__RCP_RF_PULSE_FREQUENCY->Change__MIN_MAX_DEC(cfg_min, cfg_max, cfg_dec);
		}

		// ...
	}

	return 1;
}
