// FA_LINK__GEM.h : main header file for the FA_LINK__GEM DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CFA_LINK__GEMApp
// See FA_LINK__GEM.cpp for the implementation of this class
//

class CFA_LINK__GEMApp : public CWinApp
{
public:
	CFA_LINK__GEMApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
