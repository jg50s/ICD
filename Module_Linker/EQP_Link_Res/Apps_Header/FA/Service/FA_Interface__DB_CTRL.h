#pragma once

#include "C:\Module_Linker\EQP_Link_Res\Apps_Header\FA\Service\FA_Interface__DB_ALARM_CTRL.h"
#include "C:\Module_Linker\EQP_Link_Res\Apps_Header\FA\Service\FA_Interface__DB_CEID_CTRL.h"
#include "C:\Module_Linker\EQP_Link_Res\Apps_Header\FA\Service\FA_Interface__DB_ECID_CTRL.h"
#include "C:\Module_Linker\EQP_Link_Res\Apps_Header\FA\Service\FA_Interface__DB_FVS_CTRL.h"
#include "C:\Module_Linker\EQP_Link_Res\Apps_Header\FA\Service\FA_Interface__DB_PPBODY_CTRL.h"
#include "C:\Module_Linker\EQP_Link_Res\Apps_Header\FA\Service\FA_Interface__DB_SVID_CTRL.h"
#include "C:\Module_Linker\EQP_Link_Res\Apps_Header\FA\Service\FA_Interface__DB_LIMIT_VID_CTRL.h"
#include "C:\Module_Linker\EQP_Link_Res\Apps_Header\FA\Service\FA_Interface__DB_CEID_RPTID_CTRL.h"
#include "C:\Module_Linker\EQP_Link_Res\Apps_Header\FA\Service\FA_Interface__DB_RPTID_SVID_CTRL.h"

#include "C:\Module_Linker\EQP_Link_Res\Apps_Header\FA\Service\FA_Interface__MODULE_PROPERTY_CTRL.h"


class  CI_FA_DB_CTRL
{
public:
	virtual ~CI_FA_DB_CTRL(){};

	virtual CI_FA_DB__ALARM_CTRL*    Get_ALARM_CTRL()  = 0;
	virtual CI_FA_DB__CEID_CTRL*     Get_CEID_CTRL()   = 0;
	virtual CI_FA_DB__ECID_CTRL*     Get_ECID_CTRL()   = 0;
	virtual CI_FA_DB__FVS_CTRL*      Get_FVS_CTRL()    = 0;
	virtual CI_FA_DB__PPBODY_CTRL*   Get_PPBODY_CTRL() = 0;
	virtual CI_FA_DB__SVID_CTRL*     Get_SVID_CTRL()   = 0;

	virtual CI_FA_DB__CEID_RPTID_CTRL* Get_CEID_RPTID_CTRL() = 0;
	virtual CI_FA_DB__RPTID_SVID_CTRL* Get_RPTID_SVID_CTRL() = 0;

	virtual CI_MODULE_PROPERTY_CTRL* Get_MODULE_PROPERTY_CTRL() = 0;

	virtual CI_FA_DB__LIMIT_VID_CTRL*  Get_LIMIT_VID_CTRL() = 0;
};
