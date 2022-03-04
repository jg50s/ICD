#pragma once

#include "C:\Module_Linker\EQP_Link_Res\Apps_Header\EQP\INTERFACE\OBJECT_INTERFACE.h"


#ifdef _DEBUG
	#pragma comment(lib, "C:\\Module_Linker\\EQP_Link_Res\\EQP_Lib\\EQP__PMC_Link_D.lib")
#else
	#pragma comment(lib, "C:\\Module_Linker\\EQP_Link_Res\\EQP_Lib\\EQP__PMC_Link_R.lib")
#endif


class SCI__PMC__DCOP_CTRL
{
public:
	virtual ~SCI__PMC__DCOP_CTRL(){};

	// ...
	virtual int  Create__PROCESS_DB(const CString& process_db) = 0;
	virtual int  Link__PROCESS_DB(const CString& process_db)   = 0;

	virtual int  Register__DCOP_ITEM_SNS(const CString& ch_sns) = 0;
	
	virtual int  Link__DCOP_ITEM_MIN(const CString& ch_min) = 0;
	virtual int  Link__DCOP_ITEM_AVE(const CString& ch_ave) = 0;
	virtual int  Link__DCOP_ITEM_MAX(const CString& ch_max) = 0;

	virtual int  Report__PROCESS_START() = 0;
	virtual int  Report__PROCESS_END()   = 0;

	virtual int  Report__STEP_START(const int step_id) = 0;
	virtual int  Report__STEP_END(const int step_id)   = 0;

	virtual int  Register__DCOP_ITEM_SNS_EX(const CString& ch_sns,
											const double sec) = 0;  // min : 0.1 sec 
};
