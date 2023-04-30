// PMC__FNC_STEP-ALPHA.h : main header file for the PMC__FNC_STEP-ALPHA DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CPMC__FNC_STEPALPHAApp
// See PMC__FNC_STEP-ALPHA.cpp for the implementation of this class
//

class CPMC__FNC_STEPALPHAApp : public CWinApp
{
public:
	CPMC__FNC_STEPALPHAApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
