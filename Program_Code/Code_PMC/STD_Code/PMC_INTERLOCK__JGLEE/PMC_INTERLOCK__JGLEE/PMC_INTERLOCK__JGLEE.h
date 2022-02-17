// PMC_INTERLOCK__JGLEE.h : main header file for the PMC_INTERLOCK__JGLEE DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CPMC_INTERLOCK__JGLEEApp
// See PMC_INTERLOCK__JGLEE.cpp for the implementation of this class
//

class CPMC_INTERLOCK__JGLEEApp : public CWinApp
{
public:
	CPMC_INTERLOCK__JGLEEApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
