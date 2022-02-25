// FA_LINK__STD.h : main header file for the FA_LINK__STD DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CFA_LINK__STDApp
// See FA_LINK__STD.cpp for the implementation of this class
//

class CFA_LINK__STDApp : public CWinApp
{
public:
	CFA_LINK__STDApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
