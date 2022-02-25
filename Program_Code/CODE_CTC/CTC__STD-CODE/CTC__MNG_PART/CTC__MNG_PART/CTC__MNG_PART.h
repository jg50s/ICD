// CTC__MNG_PART.h : main header file for the CTC__MNG_PART DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CCTC__MNG_PARTApp
// See CTC__MNG_PART.cpp for the implementation of this class
//

class CCTC__MNG_PARTApp : public CWinApp
{
public:
	CCTC__MNG_PARTApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
