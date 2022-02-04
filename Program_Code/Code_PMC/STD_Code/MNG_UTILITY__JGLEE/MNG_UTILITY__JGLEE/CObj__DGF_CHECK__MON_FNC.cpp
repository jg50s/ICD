#include "StdAfx.h"
#include "CObj__DGF_CHECK.h"



//-------------------------------------------------------------------------
void CObj__DGF_CHECK::
Mon__STATUS_CTRL(CII_OBJECT__VARIABLE *p_variable)
{
	CString var_data;
	int i;

	while(1)
	{
		Sleep(300);

		// ...
		{
			CString str_data;
			CString add_data;

			double y_value = 0.0;

			// DATA
			{
				str_data = "";

				for(i=0;i<CFG__TEST_LIST;i++)	
				{
					sCH_PARA__NEW_RESULT_LIST[i]->Get__DATA(var_data);
					y_value = atof(var_data);

					add_data.Format("%1d/%.3f,", i+1,y_value);
					str_data += add_data;
				}

				sCH__RESULT_STRING->Set__DATA(str_data);
			}

			// REF.
			{
				str_data = "";

				for(i=0;i<CFG__TEST_LIST;i++)
				{
					aCH_CFG__BASELINE[i]->Get__DATA(var_data);
					y_value = atof(var_data);

					add_data.Format("%1d/%.3f,", i+1,y_value);
					str_data += add_data;
				}

				sCH__REF_STRING->Set__DATA(str_data);
			}
		}
	}
}
