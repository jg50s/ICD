#pragma once

#include "C:\Module_Linker\EQP_Link_Res\Apps_Header\FA\Service\FA_Interface__E30_CTRL.h"
#include "C:\Module_Linker\EQP_Link_Res\Apps_Header\FA\Service\FA_Interface__E39_CTRL.h"
#include "C:\Module_Linker\EQP_Link_Res\Apps_Header\FA\Service\FA_Interface__E40_CTRL.h"
#include "C:\Module_Linker\EQP_Link_Res\Apps_Header\FA\Service\FA_Interface__E87_CTRL.h"
#include "C:\Module_Linker\EQP_Link_Res\Apps_Header\FA\Service\FA_Interface__E90_CTRL.h"
#include "C:\Module_Linker\EQP_Link_Res\Apps_Header\FA\Service\FA_Interface__E94_CTRL.h"
#include "C:\Module_Linker\EQP_Link_Res\Apps_Header\FA\Service\FA_Interface__E99_CTRL.h"


class CI_FA_300mm_CTRL
{
public:
	virtual ~CI_FA_300mm_CTRL(){};

	virtual CI_FA_300mm__E30_CTRL* Get_E30() = 0;
	virtual CI_FA_300mm__E39_CTRL* Get_E39() = 0;
	virtual CI_FA_300mm__E40_CTRL* Get_E40() = 0;
	virtual CI_FA_300mm__E87_CTRL* Get_E87() = 0;
	virtual CI_FA_300mm__E90_CTRL* Get_E90() = 0;
	virtual CI_FA_300mm__E94_CTRL* Get_E94() = 0;
	virtual CI_FA_300mm__E99_CTRL* Get_E99() = 0;

	virtual int Get_Error_Text(const int error_code,CString& error_text) = 0;
};
