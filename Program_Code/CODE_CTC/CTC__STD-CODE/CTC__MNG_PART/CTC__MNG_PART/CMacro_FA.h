#pragma once

#include "Interface_Code.h"


class CMacro_FA
{
private:
	CRITICAL_SECTION mCS_LOCK;

	// ...
	CX_FA_300mm_LINK xFA_300mm_Link;
	int iInit_Flag;

	// ...
	int Fnc_Init();
	int Check__Address(const void* p_addr,const CString& msg);

public:
	CMacro_FA();
	~CMacro_FA();

	// ...
	CI_FA_VARIABLE_CTRL* Get__FA_VAR_CTRL();

	// ...
	int  Is__ONLINE();
	int  Report_CEID(const int ceid);
};
