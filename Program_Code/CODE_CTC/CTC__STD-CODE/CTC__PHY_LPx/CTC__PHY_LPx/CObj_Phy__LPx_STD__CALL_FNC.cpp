#include "STdAfx.h"
#include "CMacro_FA.h"

#include "CObj_Phy__LPx_STD.h"
#include "CObj_Phy__LPx_STD__DEF.h"
#include "CObj_Phy__LPx_STD__ALID.h"

#include "Macro_Function.h"


extern CMacro_FA mFA_Link;


// ...
int CObj_Phy__LPx_STD::Call__INIT(CII_OBJECT__VARIABLE* p_variable)
{
	return Fnc__INIT(p_variable);
}
int CObj_Phy__LPx_STD::Call__MAP(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm)
{
	return Fnc__MAP(p_variable, p_alarm);
}
int CObj_Phy__LPx_STD::Call__PREPLOAD(CII_OBJECT__VARIABLE* p_variable)
{
	return Fnc__PREPLOAD(p_variable);
}
int CObj_Phy__LPx_STD::Call__CID_READ(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm)
{
	return Fnc__CID_READ(p_variable,p_alarm,1);
}
int CObj_Phy__LPx_STD::Call__LOAD(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm)
{
	if(sCH__PORT_STATUS->Check__DATA("LOAD") > 0)
	{
		xCH__LPx_LOAD_REQ_BY_USER->Set__DATA("YES");
		Sleep(500);
		xCH__LPx_LOAD_REQ_BY_USER->Set__DATA("");

		return 1;
	}

	return Fnc__LOAD(p_variable,p_alarm);
}
int CObj_Phy__LPx_STD::Call__RLSUNLOAD(CII_OBJECT__VARIABLE* p_variable)
{
	return Fnc__RLSUNLOAD(p_variable);
}
int CObj_Phy__LPx_STD::Call__UNLOAD(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm)
{
	CString status;
	sCH__PORT_STATUS->Get__DATA(status);

	if((status.CompareNoCase("LOAD")       == 0)
	|| (status.CompareNoCase("UNLOAD")     == 0)
	|| (status.CompareNoCase("CID_VERIFY") == 0)
	|| (status.CompareNoCase("MAP_VERIFY") == 0)
	|| (status.CompareNoCase("WAITING")    == 0)
	|| (status.CompareNoCase("RESERVE")    == 0)
	|| (status.CompareNoCase("ABORTED")    == 0))
	{
		return Fnc__UNLOAD(p_variable, p_alarm);
	}
	return -1;
}

int CObj_Phy__LPx_STD::Call__RELOAD(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm)
{
	if(sCH__PORT_STATUS->Check__DATA(STR__UNLOAD_REQ) < 0)
	{
		return -1;
	}

	int r_flag = Reload__PORT(p_alarm, 1);
	if(r_flag < 0)		return -11;

	return Fnc__RELOAD(p_variable, p_alarm);
}

int CObj_Phy__LPx_STD::Call__RF_CID_READ(CII_OBJECT__VARIABLE* p_variable)
{
	if(mFA_Link.Is_LP__BYPASS_ID(iPTN) > 0)		return -1;

	return Fnc__RF_CID_READ(p_variable);
}
int CObj_Phy__LPx_STD::Call__RF_PAGE_READ(CII_OBJECT__VARIABLE* p_variable)
{
	if(mFA_Link.Is_LP__BYPASS_ID(iPTN) > 0)		return -1;

	return Fnc__RF_PAGE_READ(p_variable);
}
int CObj_Phy__LPx_STD::Call__RF_CID_WRITE(CII_OBJECT__VARIABLE* p_variable)
{
	if(mFA_Link.Is_LP__BYPASS_ID(iPTN) > 0)		return -1;

	return Fnc__RF_CID_WRITE(p_variable);
}
int CObj_Phy__LPx_STD::Call__RF_PAGE_WRITE(CII_OBJECT__VARIABLE* p_variable)
{
	if(mFA_Link.Is_LP__BYPASS_ID(iPTN) > 0)		return -1;

	return Fnc__RF_PAGE_WRITE(p_variable);
}

int CObj_Phy__LPx_STD::Call__SCH_MAP(CII_OBJECT__VARIABLE* p_variable)
{
	DECLARE__EXT_CTRL(p_variable);

	// ...
	CStringArray l_slot;
	p_ext_mode_ctrl->Get__FNC_PARAMETER(l_slot);

	// ...
	CString str_mapped = "MAPPED";

	int limit = l_slot.GetSize();
	int i;

	for(i=0;i<limit;i++)
	{
		int slot_index = atoi(l_slot[i]) - 1;

		if(slot_index < 0)						continue;
		if(slot_index >= CFG_LP__SLOT_MAX)		continue;

		if(xCH__SLOT_STATUS[slot_index]->Check__DATA("NONE") > 0)
		{
			continue;
		}

		xCH__SLOT_STATUS[slot_index]->Set__DATA(str_mapped);
	}

	return 1;
}
int CObj_Phy__LPx_STD::Call__CHECK_SLOT(CII_OBJECT__VARIABLE* p_variable)
{
	DECLARE__EXT_CTRL(p_variable);

	// ...
	CStringArray l_slot;
	p_ext_mode_ctrl->Get__FNC_PARAMETER(l_slot);

	// ...
	CStringArray l_err_slot;
	CString str_slot;

	int limit = l_slot.GetSize();
	int i;

	for(i=0;i<limit;i++)
	{
		int slot_index = atoi(l_slot[i]) - 1;
		str_slot.Format("%1d",slot_index+1);

		if(slot_index < 0)
		{
			l_err_slot.Add(str_slot);
			continue;
		}
		if(slot_index >= CFG_LP__SLOT_MAX)
		{
			l_err_slot.Add(str_slot);
			continue;
		}

		if(xCH__SLOT_STATUS[slot_index]->Check__DATA("NONE") > 0)
		{
			l_err_slot.Add(str_slot);
			continue;
		}
	}

	p_ext_mode_ctrl->Set__RETURN_FNC_PARAMETER(l_err_slot);
	return 1;
}
