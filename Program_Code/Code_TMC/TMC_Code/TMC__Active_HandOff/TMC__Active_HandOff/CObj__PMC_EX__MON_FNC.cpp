#include "StdAfx.h"
#include "CObj__PMC_EX.h"


// ...
void CObj__PMC_EX
::Mon__MODULE_STATUS(CII_OBJECT__VARIABLE* p_variable,
					 CII_OBJECT__ALARM* p_alarm)
{
	int i_data = 0;
	
	CString var_data;

	
	while(1)
	{
		Sleep(1000);

		/*
		// ...
		{
			i_data++;
			if(i_data >= 100)		i_data = 1;

			for(int i=0; i<iPMx_SIZE; i++)
			{
				var_data.Format("%1d", i_data);
				sCH__PMx_LINK_COUNT_REPORT_SEND[i]->Set__DATA(var_data);
			}
		}
		*/
	}
}
