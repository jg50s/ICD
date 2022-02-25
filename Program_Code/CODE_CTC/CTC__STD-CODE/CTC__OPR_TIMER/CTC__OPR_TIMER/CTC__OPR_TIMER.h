// CTC__OPR_TIMER.h : main header file for the CTC__OPR_TIMER DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CCTC__OPR_TIMERApp
// See CTC__OPR_TIMER.cpp for the implementation of this class
//

class CCTC__OPR_TIMERApp : public CWinApp
{
public:
	CCTC__OPR_TIMERApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
