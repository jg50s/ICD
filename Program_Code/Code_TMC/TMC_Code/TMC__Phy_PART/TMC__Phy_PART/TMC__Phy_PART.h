// TMC__Phy_PART.h : main header file for the TMC__Phy_PART DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CTMC__Phy_PARTApp
// See TMC__Phy_PART.cpp for the implementation of this class
//

class CTMC__Phy_PARTApp : public CWinApp
{
public:
	CTMC__Phy_PARTApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
