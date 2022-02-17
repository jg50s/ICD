// PHY_RS232__RF_EN2RA.h : main header file for the PHY_RS232__RF_EN2RA DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CPHY_RS232__RF_EN2RAApp
// See PHY_RS232__RF_EN2RA.cpp for the implementation of this class
//

class CPHY_RS232__RF_EN2RAApp : public CWinApp
{
public:
	CPHY_RS232__RF_EN2RAApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
