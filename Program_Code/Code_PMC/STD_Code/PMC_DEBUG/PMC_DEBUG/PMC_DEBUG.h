// PMC_DEBUG.h : main header file for the PMC_DEBUG DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CPMC_DEBUGApp
// See PMC_DEBUG.cpp for the implementation of this class
//

class CPMC_DEBUGApp : public CWinApp
{
public:
	CPMC_DEBUGApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
