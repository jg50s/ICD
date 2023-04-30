#include "StdAfx.h"
#include "CObj_FA__APP_CTRL.h"


#include "CMacro_FA.h"
extern CMacro_FA mFA_Link;


// ...
void CObj_FA__APP_CTRL::Mon__USER_JOB(CII_OBJECT__VARIABLE* p_variable)
{

	while(1)
	{
		p_variable->Wait__SINGLE_OBJECT(0.1);

		Fnc__PJOB_CHECK();
		Fnc__CJOB_CHECK();
	}
}

void CObj_FA__APP_CTRL::Fnc__PJOB_CHECK()
{
	if(xCH__PJOB_ACTION->Check__DATA("CANCEL") < 0)
		return;

	// ...
	CString pjobid;

	xCH__PJOB_NAME->Get__DATA(pjobid);
	mFA_Link.PJOB__CANCEL(pjobid);

	xCH__PJOB_ACTION->Set__DATA("IDLE");
}
void CObj_FA__APP_CTRL::Fnc__CJOB_CHECK()
{
	CString cjobid;
	CString var_data;

	xCH__CJOB_ACTION->Get__DATA(var_data);
	xCH__CJOB_NAME->Get__DATA(cjobid);

	if(var_data.CompareNoCase("START") == 0)
	{
		mFA_Link.CJOB__HOQ(cjobid);
	}
	else if(var_data.CompareNoCase("CANCEL") == 0)
	{
		mFA_Link.CJOB__ABORT_IN_QUEUED_Or_SELECTED(cjobid);
	}
	else
	{
		return;
	}

	xCH__CJOB_ACTION->Set__DATA("IDLE");
}
