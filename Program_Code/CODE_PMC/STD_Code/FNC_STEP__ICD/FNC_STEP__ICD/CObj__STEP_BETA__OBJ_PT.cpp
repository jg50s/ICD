#include "StdAfx.h"
#include "CObj__STEP_BETA.h"
#include "CObj__STEP_BETA__DEF.h"


// ...
int CObj__STEP_BETA
::PT_OBJ__Check_ERROR()
{
	for(int i=0; i<iDATA__PT_SIZE; i++)
	{
		if(dEXT_CH__PT_X__MON_ABORT_ACTIVE[i]->Check__DATA(STR__ON) > 0)		return 1;
	}

	return -1;
}
