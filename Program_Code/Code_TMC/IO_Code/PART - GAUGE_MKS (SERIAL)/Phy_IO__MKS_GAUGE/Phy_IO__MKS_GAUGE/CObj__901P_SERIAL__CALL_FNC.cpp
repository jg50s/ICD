#include "StdAfx.h"
#include "CObj__901P_SERIAL.h"


// ...
int  CObj__901P_SERIAL::
Call__INIT(CII_OBJECT__VARIABLE* p_variable,
		   CII_OBJECT__ALARM* p_alarm)
{

	return 1;
}

int  CObj__901P_SERIAL::
Call__TEST(CII_OBJECT__VARIABLE* p_variable,
		   CII_OBJECT__ALARM* p_alarm)
{
	CString r_data = "@253ACK8.31E+2";

	int s_index = r_data.Find("ACK");
	if(s_index == 4)
	{
		r_data.Delete(0,7);

		sCH__DATA_PRESSURE_TORR->Set__DATA(r_data);
	}
	else
	{
		sCH__DATA_PRESSURE_TORR->Set__DATA("???");
	}

	return 1;
}

