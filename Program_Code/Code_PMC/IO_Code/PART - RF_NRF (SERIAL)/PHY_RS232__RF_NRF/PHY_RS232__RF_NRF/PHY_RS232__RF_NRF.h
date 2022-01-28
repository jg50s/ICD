// PHY_RS232__RF_NRF.h : main header file for the PHY_RS232__RF_NRF DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CPHY_RS232__RF_NRFApp
// See PHY_RS232__RF_NRF.cpp for the implementation of this class
//

class CPHY_RS232__RF_NRFApp : public CWinApp
{
public:
	CPHY_RS232__RF_NRFApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
