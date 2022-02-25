// CTC__PHY_LPx.h : main header file for the CTC__PHY_LPx DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CCTC__PHY_LPxApp
// See CTC__PHY_LPx.cpp for the implementation of this class
//

class CCTC__PHY_LPxApp : public CWinApp
{
public:
	CCTC__PHY_LPxApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
