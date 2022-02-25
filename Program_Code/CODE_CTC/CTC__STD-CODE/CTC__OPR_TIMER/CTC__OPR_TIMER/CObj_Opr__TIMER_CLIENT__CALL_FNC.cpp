#include "StdAfx.h"
#include "CObj_Opr__TIMER_CLIENT.h"


// ...
int  CObj_Opr__TIMER_CLIENT::Call__TIME_SYNC(CII_OBJECT__VARIABLE *p_variable)
{
	SCX__TIMER_CTRL timer_ctrl;

	xCH__SYNC_REQ_FLAG->Set__DATA("YES");
	timer_ctrl->WAIT(1.5);
	xCH__SYNC_REQ_FLAG->Set__DATA("");

	return 1;
}
