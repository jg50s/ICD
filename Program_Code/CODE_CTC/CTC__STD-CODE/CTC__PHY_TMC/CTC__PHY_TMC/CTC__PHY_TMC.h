// CTC__PHY_TMC.h : main header file for the CTC__PHY_TMC DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CCTC__PHY_TMCApp
// See CTC__PHY_TMC.cpp for the implementation of this class
//

class CCTC__PHY_TMCApp : public CWinApp
{
public:
	CCTC__PHY_TMCApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
