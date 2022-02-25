#include "StdAfx.h"
#include "CObj_FA__E40_CTRL.h"


#include "CMacro_FA.h"
extern CMacro_FA mFA_Link;


// ...
void CObj_FA__E40_CTRL::Mon__E40_CTRL(CII_OBJECT__VARIABLE* p_variable)
{
	CString pjobid;

	while(1)
	{
		if(xCH__PJOB_ACTION->Check__DATA("CANCEL") < 0)
		{
			Sleep(90);
			continue;
		}

		// ...
		{
			xCH__PJOB_NAME->Get__DATA(pjobid);
			mFA_Link.PJOB__CANCEL(pjobid);

			xCH__PJOB_ACTION->Set__DATA("IDLE");
		}

		Sleep(90);
	}
}
