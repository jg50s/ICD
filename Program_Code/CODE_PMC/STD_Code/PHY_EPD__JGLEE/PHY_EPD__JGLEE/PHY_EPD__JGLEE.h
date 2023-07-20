// PHY_EPD__JGLEE.h : main header file for the PHY_EPD__JGLEE DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CPHY_EPD__JGLEEApp
// See PHY_EPD__JGLEE.cpp for the implementation of this class
//

class CPHY_EPD__JGLEEApp : public CWinApp
{
public:
	CPHY_EPD__JGLEEApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
