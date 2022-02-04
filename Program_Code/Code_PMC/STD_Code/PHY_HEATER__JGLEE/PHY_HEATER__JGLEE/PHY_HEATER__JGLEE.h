// PHY_HEATER__JGLEE.h : main header file for the PHY_HEATER__JGLEE DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CPHY_HEATER__JGLEEApp
// See PHY_HEATER__JGLEE.cpp for the implementation of this class
//

class CPHY_HEATER__JGLEEApp : public CWinApp
{
public:
	CPHY_HEATER__JGLEEApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
