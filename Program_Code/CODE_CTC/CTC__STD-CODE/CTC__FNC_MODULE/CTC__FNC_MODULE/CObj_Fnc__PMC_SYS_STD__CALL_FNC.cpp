#include "StdAfx.h"
#include "CObj_Fnc__PMC_SYS_STD.h"


#define STR__ENABLE				"ENABLE"
#define STR__STANDBY			"STANDBY"
#define STR__MAINTMODE			"MAINTMODE"
#define STR__OFFLINE			"OFFLINE"

#define CMMD__TIME_INIT			"TIME_INIT"
#define CMMD__SYSTEM_INIT		"SYSTEM_INIT"
#define CMMD__AUTO_INIT			"AUTO_INIT"
#define CMMD__SYSTEM_MAINT		"SYSTEM_MAINT"


// ...
int  CObj_Fnc__PMC_SYS_STD::Call__ALL_INIT(CII_OBJECT__VARIABLE* p_variable)
{
	if(xCH_CFG__INIT_MODE->Check__DATA("AUTO") > 0)
	{
		if(Fnc__AUTO_INIT(p_variable) < 0)			return -1;
	}
	else if(xCH_CFG__INIT_MODE->Check__DATA("ONLY_SYSTEM") > 0)
	{
		if(Call__SYSTEM_INIT(p_variable) < 0)		return -1;
	}
	else
	{
		if(Call__TIME_INIT(p_variable)   < 0)		return -1;
		Sleep(300);
		if(Call__SYSTEM_INIT(p_variable) < 0)		return -1;
	}
	return 1;
}

int  CObj_Fnc__PMC_SYS_STD::Call__TIME_INIT(CII_OBJECT__VARIABLE* p_variable)
{
	return Fnc__CMMD_ACT(p_variable, CMMD__TIME_INIT);
}
int  CObj_Fnc__PMC_SYS_STD::Call__SYSTEM_INIT(CII_OBJECT__VARIABLE* p_variable)
{
	return Fnc__CMMD_ACT(p_variable, CMMD__SYSTEM_INIT);
}
int  CObj_Fnc__PMC_SYS_STD::Fnc__AUTO_INIT(CII_OBJECT__VARIABLE* p_variable)
{
	return Fnc__CMMD_ACT(p_variable, CMMD__AUTO_INIT);
}

int  CObj_Fnc__PMC_SYS_STD::Call__SYSTEM_MAINT(CII_OBJECT__VARIABLE* p_variable)
{
	return Fnc__CMMD_ACT(p_variable, CMMD__SYSTEM_MAINT, false);
}

int  CObj_Fnc__PMC_SYS_STD::
Fnc__CMMD_ACT(CII_OBJECT__VARIABLE* p_variable, const CString& cmmd_act, const bool active_init)
{
	CString obj_state;
	bool active_pm[CFG_PM_LIMIT];
	int i;

	for(i=0; i<iPMx_SIZE; i++)
	{
		active_pm[i] = false;
		obj_state = xEXT_CH__PMx__OBJ_STATUS[i]->Get__STRING();

		if(active_init)
		{
			if((obj_state.CompareNoCase(STR__MAINTMODE) != 0)
			&& (obj_state.CompareNoCase(STR__OFFLINE)   != 0))
			{
				continue;
			}
		}
		else
		{
			if((obj_state.CompareNoCase(STR__STANDBY) != 0)
			&& (obj_state.CompareNoCase(STR__OFFLINE) != 0))
			{
				continue;
			}
		}

		if(pOBJ_CTRL__PMx[i]->Is__OBJ_BUSY() > 0)
		{
			continue;
		}

		active_pm[i] = true;
		pOBJ_CTRL__PMx[i]->Run__OBJECT(cmmd_act);
	}	

	// ...
	int r_act = 1;

	for(i=0; i<iPMx_SIZE; i++)
	{
		if(active_pm[i])
		{
			if(pOBJ_CTRL__PMx[i]->When__OBJECT() < 0)		
				r_act = -1;
		}
	}	
	return r_act;
}
