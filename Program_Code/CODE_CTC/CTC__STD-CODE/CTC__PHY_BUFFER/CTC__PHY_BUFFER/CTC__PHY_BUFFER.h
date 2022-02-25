// CTC__PHY_BUFFER.h : main header file for the CTC__PHY_BUFFER DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CCTC__PHY_BUFFERApp
// See CTC__PHY_BUFFER.cpp for the implementation of this class
//

class CCTC__PHY_BUFFERApp : public CWinApp
{
public:
	CCTC__PHY_BUFFERApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
