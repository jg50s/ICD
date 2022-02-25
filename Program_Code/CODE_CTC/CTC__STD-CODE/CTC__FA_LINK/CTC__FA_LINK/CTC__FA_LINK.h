// CTC__FA_LINK.h : main header file for the CTC__FA_LINK DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CCTC__FA_LINKApp
// See CTC__FA_LINK.cpp for the implementation of this class
//

class CCTC__FA_LINKApp : public CWinApp
{
public:
	CCTC__FA_LINKApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
