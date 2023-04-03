#include "StdAfx.h"
#include "CObj__DGF_CHECK.h"



//-------------------------------------------------------------------------
void CObj__DGF_CHECK::
Mon__STATUS_CTRL(CII_OBJECT__VARIABLE *p_variable)
{
	CString var_data;
	int i;

	int loop_count = 0;


	while(1)
	{
		p_variable->Wait__SINGLE_OBJECT(0.1);

		loop_count++;
		if(loop_count > 10)		loop_count = 1;

		
		if(loop_count == 1)
		{
			CString str_data;
			CString add_data;

			double y_value = 0.0;

			// NEW.STRING
			{
				str_data = "";

				for(i=0;i<CFG__TEST_LIST;i++)	
				{
					sCH_PARA__NEW_RESULT_mTORR_LIST[i]->Get__DATA(var_data);
					y_value = atof(var_data);

					add_data.Format("%1d/%.0f,", i+1,y_value);
					str_data += add_data;
				}

				sCH__RESULT_STRING->Set__DATA(str_data);
			}

			// REF.STRING
			{
				str_data = "";

				for(i=0;i<CFG__TEST_LIST;i++)
				{
					aCH_CFG__BASELINE_mTORR[i]->Get__DATA(var_data);
					y_value = atof(var_data);

					add_data.Format("%1d/%.0f,", i+1,y_value);
					str_data += add_data;
				}

				sCH__REF_STRING->Set__DATA(str_data);
			}
		}
	}
}
