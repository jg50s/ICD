#include "StdAfx.h"
#include "CMacro_FA.h"


CMacro_FA mFA_Link;


// ...
CMacro_FA::CMacro_FA()
{
	InitializeCriticalSection(&mCS_LOCK);

	iInit_Flag = -1;
}
CMacro_FA::~CMacro_FA()
{

	DeleteCriticalSection(&mCS_LOCK);
}

// ...
int  CMacro_FA::Fnc_Init()
{
	EnterCriticalSection(&mCS_LOCK);

	if(iInit_Flag > 0)
	{
		LeaveCriticalSection(&mCS_LOCK);
		return 1;
	}

	while(1)
	{
		iInit_Flag = xFA_300mm_Link->Open("");

		if(iInit_Flag < 0)
		{
			Sleep(100);
			continue;
		}

		break;
	}

	LeaveCriticalSection(&mCS_LOCK);
	return iInit_Flag;
}
int  CMacro_FA::Check__Address(const void* p_addr,const CString& msg)
{
	if(p_addr != NULL)
	{
		return 1;
	}
	return -1;
}

// ...
CI_FA_VARIABLE_CTRL* CMacro_FA::Get__FA_VAR_CTRL()
{
	if(Fnc_Init() < 0)		return NULL;

	return xFA_300mm_Link->Get_FA_VARIABLE_CTRL();
}
CI_FA_DB__ECID_CTRL* CMacro_FA::Get__FA_ECID_CTRL()
{
	if(Fnc_Init() < 0)		return NULL;

	CI_FA_DB_CTRL *p_db_ctrl = xFA_300mm_Link->Get_FA_DB_CTRL();

	return p_db_ctrl->Get_ECID_CTRL();
}

CI_FA_300mm__E30_CTRL* CMacro_FA::Get__FA_E30_CTRL()
{
	if(Fnc_Init() < 0)		return NULL;

	return xFA_300mm_Link->Get_FA_300mm_CTRL()->Get_E30();
}
CI_FA_300mm__E40_CTRL* CMacro_FA::Get__FA_E40_CTRL()
{
	if(Fnc_Init() < 0)		return NULL;

	return xFA_300mm_Link->Get_FA_300mm_CTRL()->Get_E40();
}
CI_FA_300mm__E94_CTRL* CMacro_FA::Get__FA_E94_CTRL()
{
	if(Fnc_Init() < 0)		return NULL;

	return xFA_300mm_Link->Get_FA_300mm_CTRL()->Get_E94();
}
