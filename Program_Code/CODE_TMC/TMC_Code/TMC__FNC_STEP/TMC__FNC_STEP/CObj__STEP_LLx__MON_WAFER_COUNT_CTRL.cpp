#include "StdAfx.h"
#include "CObj__STEP_LLx.h"
#include "CObj__STEP_LLx__DEF.h"


// ...
void CObj__STEP_LLx::
Mon__Wafer_Count_Ctrl(CII_OBJECT__VARIABLE* p_variable,
					  CII_OBJECT__ALARM* p_alarm)
{
	CString	str_time;
	SYSTEMTIME st;

	// ...
	{
		GetLocalTime(&st);
		str_time.Format("%00004d.%002d.%002d", st.wYear,st.wMonth,st.wDay);

		// WAFER COUNT ...
		{
			if(sCH__TOTAL_COUNT_START_DATE->Check__DATA("") > 0)
			{
				sCH__TOTAL_COUNT_START_DATE->Set__DATA(str_time);

				aCH__WAFER_TOTAL_COUNT->Set__DATA("0");
			}
			if(sCH__CURRENT_COUNT_START_DATE->Check__DATA("") > 0)
			{
				sCH__CURRENT_COUNT_START_DATE->Set__DATA(str_time);
			
				aCH__WAFER_CURRENT_COUNT->Set__DATA("0");
			}
		}
	}

	// ...
	SCX__TIMER_CTRL x_timer_ctrl;
	CString var_data;
	double  cur_value;
	double  cur_sec;

	while(1)
	{
		x_timer_ctrl->WAIT(1.0);

		// WAFER CURRENT COUNT INFO ...
		if(dCH__WAFER_CURRENT_COUNT_RESET->Check__DATA(STR__RESET) > 0)
		{
			dCH__WAFER_CURRENT_COUNT_RESET->Set__DATA(STR__RETURN);

			// ...
			{
				GetLocalTime(&st);	
				
				str_time.Format("%00004d.%002d.%002d", st.wYear,st.wMonth,st.wDay);
				sCH__CURRENT_COUNT_START_DATE->Set__DATA(str_time);

				aCH__WAFER_CURRENT_COUNT->Set__DATA("0");
			}
		}
		// WAFER TOTAL COUNT INFO ...
		if(dCH__WAFER_TOTAL_COUNT_RESET->Check__DATA(STR__RESET) > 0)
		{
			dCH__WAFER_TOTAL_COUNT_RESET->Set__DATA(STR__RETURN);
			
			// ...
			{
				GetLocalTime(&st);	
				
				str_time.Format("%00004d.%002d.%002d", st.wYear,st.wMonth,st.wDay);
				sCH__TOTAL_COUNT_START_DATE->Set__DATA(str_time);

				aCH__WAFER_CURRENT_COUNT->Get__DATA(var_data);
				aCH__WAFER_TOTAL_COUNT->Set__DATA(var_data);
			}
		}

		// ...
	}

	// ...
}
