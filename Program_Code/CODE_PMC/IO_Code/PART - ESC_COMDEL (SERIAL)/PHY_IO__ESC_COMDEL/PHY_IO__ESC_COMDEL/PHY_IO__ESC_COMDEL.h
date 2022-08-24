// PHY_IO__ESC_COMDEL.h : main header file for the PHY_IO__ESC_COMDEL DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CPHY_IO__ESC_COMDELApp
// See PHY_IO__ESC_COMDEL.cpp for the implementation of this class
//

class CPHY_IO__ESC_COMDELApp : public CWinApp
{
public:
	CPHY_IO__ESC_COMDELApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
