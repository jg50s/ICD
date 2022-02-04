#include "StdAfx.h"
#include "CObj__DB_INF.h"


#define STR__UNKNOWN				"UNKNOWN"
#define STR__VAC					"VAC"
#define STR__ATM					"ATM"
#define STR__BTW					"BTW"

#define STR__ON						"ON"
#define STR__OFF					"OFF"


// ...
void CObj__DB_INF
::Mon__UPDATE_INFO(CII_OBJECT__VARIABLE *p_variable)
{
	CString pre__rcp_name;

	// ...
	{
		sCH__CHM_PRESSURE_STATUS->Set__DATA(STR__BTW);
	}


	while(1)
	{
		p_variable->Wait__SINGLE_OBJECT(0.1);


		// RECIPE NAME : FOLDER DELETE ...
		if(xCH__RECIPE->Check__DATA(pre__rcp_name) < 0)
		{
			pre__rcp_name = xCH__RECIPE->Get__STRING();
			
			CString ch_data = pre__rcp_name;
			ch_data.Delete(0, ch_data.Find("\\")+1);

			xCH__RECIPE_WITHOUT_FOLDER_NAME->Set__DATA(ch_data);
		}

		// ...
	}
}

