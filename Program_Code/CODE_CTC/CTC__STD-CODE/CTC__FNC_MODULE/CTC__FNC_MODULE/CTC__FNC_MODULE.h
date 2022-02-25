// CTC__FNC_MODULE.h : main header file for the CTC__FNC_MODULE DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CCTC__FNC_MODULEApp
// See CTC__FNC_MODULE.cpp for the implementation of this class
//

class CCTC__FNC_MODULEApp : public CWinApp
{
public:
	CCTC__FNC_MODULEApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
