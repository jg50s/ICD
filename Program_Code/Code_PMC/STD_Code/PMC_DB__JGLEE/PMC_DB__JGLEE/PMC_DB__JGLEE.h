// PMC_DB__JGLEE.h : main header file for the PMC_DB__JGLEE DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CPMC_DB__JGLEEApp
// See PMC_DB__JGLEE.cpp for the implementation of this class
//

class CPMC_DB__JGLEEApp : public CWinApp
{
public:
	CPMC_DB__JGLEEApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
