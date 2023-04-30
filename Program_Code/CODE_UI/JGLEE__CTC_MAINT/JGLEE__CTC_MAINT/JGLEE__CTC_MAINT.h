// JGLEE__CTC_MAINT.h : main header file for the JGLEE__CTC_MAINT DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CJGLEE__CTC_MAINTApp
// See JGLEE__CTC_MAINT.cpp for the implementation of this class
//

class CJGLEE__CTC_MAINTApp : public CWinApp
{
public:
	CJGLEE__CTC_MAINTApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
