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

	iInit_Flag = xFA_300mm_Link->Open("");

	LeaveCriticalSection(&mCS_LOCK);
	return iInit_Flag;
}
int  CMacro_FA::Check__Address(const void* p_addr, const CString& msg)
{
	if(p_addr != NULL)		return 1;

	MessageBox(NULL,msg,"CMacro_FA : Address Null !!!",MB_OK|MB_TOPMOST);
	return -1;
}


// ...
#define  MACRO__CHECK_E30(MSG_STR)								\
if(Fnc_Init() < 0)		return -1;								\
																\
CI_FA_300mm__E30_CTRL *p_e30_ctrl								\
= xFA_300mm_Link->Get_FA_300mm_CTRL()->Get_E30();				\
																\
if(Check__Address(p_e30_ctrl,MSG_STR) < 0)						\
{																\
	return -1;													\
}

CI_FA_VARIABLE_CTRL* CMacro_FA::Get__FA_VAR_CTRL()
{
	if(Fnc_Init() < 0)		return NULL;

	return xFA_300mm_Link->Get_FA_VARIABLE_CTRL();
}

int  CMacro_FA::Is__ONLINE()
{
	MACRO__CHECK_E30("Is__ONLINE()");

	return p_e30_ctrl->Is_ONLINE();
}
int  CMacro_FA::Report_CEID(const int ceid)
{
	if(Fnc_Init() < 0)		return -1;

	return xFA_300mm_Link->Send_EVENT(ceid); 
}
