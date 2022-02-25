#include "StdAfx.h"
#include "CObj_FA__E94_CTRL.h"


#include "CMacro_FA.h"
extern CMacro_FA mFA_Link;


// ...
void CObj_FA__E94_CTRL::Mon__E94_CTRL(CII_OBJECT__VARIABLE* p_variable)
{
	CString var_data;
	CString cjobid;

	while(1)
	{
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
			Sleep(90);
			continue;
		}

		xCH__CJOB_ACTION->Set__DATA("IDLE");
		Sleep(90);
	}
}
