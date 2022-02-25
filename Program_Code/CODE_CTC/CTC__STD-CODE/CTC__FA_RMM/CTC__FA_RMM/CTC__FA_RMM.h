// CTC__FA_RMM.h : main header file for the CTC__FA_RMM DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CCTC__FA_RMMApp
// See CTC__FA_RMM.cpp for the implementation of this class
//

class CCTC__FA_RMMApp : public CWinApp
{
public:
	CCTC__FA_RMMApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
