// FA_LINK__S7Fy.h : main header file for the FA_LINK__S7Fy DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CFA_LINK__S7FyApp
// See FA_LINK__S7Fy.cpp for the implementation of this class
//

class CFA_LINK__S7FyApp : public CWinApp
{
public:
	CFA_LINK__S7FyApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
