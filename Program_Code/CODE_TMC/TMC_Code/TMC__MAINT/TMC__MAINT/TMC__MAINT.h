// TMC__MAINT.h : main header file for the TMC__MAINT DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CTMC__MAINTApp
// See TMC__MAINT.cpp for the implementation of this class
//

class CTMC__MAINTApp : public CWinApp
{
public:
	CTMC__MAINTApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
