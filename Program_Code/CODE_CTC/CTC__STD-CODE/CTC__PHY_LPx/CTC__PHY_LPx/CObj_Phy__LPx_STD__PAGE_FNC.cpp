#include "STdAfx.h"

#include "CObj_Phy__LPx_STD.h"
#include "CObj_Phy__LPx_STD__DEF.h"
#include "CObj_Phy__LPx_STD__ALID.h"


// ...
int  CObj_Phy__LPx_STD::Popup__WIN_CSTID()
{
	CString win_name = sWIN_CSTID__NAME;
	
	if(win_name.GetLength() < 1)
	{
		return 1;
	}

	// ...
	xCH__SCR__WIN_CSTID->Set__DATA(win_name);

	while(xCH__SCR__WIN_CSTID->Check__DATA(win_name) > 0)
	{
		Sleep(500);
	}

	if(xCH__SCR__WIN_CSTID->Check__DATA("OK") < 0)
	{
		return -1;
	}
	return 1;
}
