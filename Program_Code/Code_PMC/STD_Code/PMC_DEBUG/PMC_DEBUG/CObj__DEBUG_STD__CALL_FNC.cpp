#include "StdAfx.h"
#include "CObj__DEBUG_STD.h"


// ...
int CObj__DEBUG_STD
::Call__TEST(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm)
{
	printf(" * %s - Check 1 \n", sObject_Name);

	printf(" * %s - Check 2 \n", sObject_Name);
	return 1;
}
