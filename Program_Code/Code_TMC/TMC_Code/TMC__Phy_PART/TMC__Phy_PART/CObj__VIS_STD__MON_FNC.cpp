#include "StdAfx.h"
#include "CObj__VIS_STD.h"
#include "CObj__VIS_STD__DEF.h"


//----------------------------------------------------------------------------------------------------
void CObj__VIS_STD
::Mon__IO_MONITOR(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm)
{
	CString var_data;

	while(1)
	{
		Sleep(9);

		if(sCH__RECIPE_UPLOAD->Check__DATA("YES") > 0)
		{
			Call__GET_FILE(p_variable, p_alarm);
		}

		sCH__RECIPE_UPLOAD->Set__DATA("");
	}	
}
