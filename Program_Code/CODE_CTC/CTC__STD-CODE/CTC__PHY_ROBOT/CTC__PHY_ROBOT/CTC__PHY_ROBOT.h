// CTC__PHY_ROBOT.h : main header file for the CTC__PHY_ROBOT DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CCTC__PHY_ROBOTApp
// See CTC__PHY_ROBOT.cpp for the implementation of this class
//

class CCTC__PHY_ROBOTApp : public CWinApp
{
public:
	CCTC__PHY_ROBOTApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
