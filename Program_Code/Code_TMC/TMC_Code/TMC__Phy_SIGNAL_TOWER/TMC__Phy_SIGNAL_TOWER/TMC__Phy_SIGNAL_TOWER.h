// TMC__Phy_SIGNAL_TOWER.h : main header file for the TMC__Phy_SIGNAL_TOWER DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CTMC__Phy_SIGNAL_TOWERApp
// See TMC__Phy_SIGNAL_TOWER.cpp for the implementation of this class
//

class CTMC__Phy_SIGNAL_TOWERApp : public CWinApp
{
public:
	CTMC__Phy_SIGNAL_TOWERApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
