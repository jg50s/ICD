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
int  CMacro_FA::Check__Address(const void* p_addr,
							   const CString& msg)
{
	if(p_addr != NULL)		return 1;

	MessageBox(NULL,msg,"CMacro_FA : Address Null !!!",MB_OK|MB_TOPMOST);
	return -1;
}


// ...
CI_FA_DB_CTRL*          
CMacro_FA::Get_FA_DB_CTRL()
{
	if(Fnc_Init() < 0)				return NULL;

	return xFA_300mm_Link->Get_FA_DB_CTRL();
}
CI_FA_DB__PPBODY_CTRL*  
CMacro_FA::Get_PPBODY_CTRL()
{
	if(Fnc_Init() < 0)				return NULL;

	CI_FA_DB_CTRL* x_fa_db_ctrl = xFA_300mm_Link->Get_FA_DB_CTRL();
	if(x_fa_db_ctrl == NULL)		return NULL;

	return x_fa_db_ctrl->Get_PPBODY_CTRL();
}

