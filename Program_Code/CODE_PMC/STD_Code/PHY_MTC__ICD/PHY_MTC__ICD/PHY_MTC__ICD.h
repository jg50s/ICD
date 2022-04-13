// PHY_MTC__ICD.h : main header file for the PHY_MTC__ICD DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CPHY_MTC__ICDApp
// See PHY_MTC__ICD.cpp for the implementation of this class
//

class CPHY_MTC__ICDApp : public CWinApp
{
public:
	CPHY_MTC__ICDApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
